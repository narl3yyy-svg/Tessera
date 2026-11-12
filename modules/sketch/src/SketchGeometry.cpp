#include "tsr/sketch/SketchGeometry.h"

#include <BOPAlgo_Builder.hxx>
#include <BOPAlgo_Tools.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepClass_FaceClassifier.hxx>
#include <BRepGProp.hxx>
#include <BRepMesh_IncrementalMesh.hxx>
#include <BRep_Builder.hxx>
#include <BRep_Tool.hxx>
#include <GC_MakeArcOfCircle.hxx>
#include <GeomAPI_Interpolate.hxx>
#include <TColgp_HArray1OfPnt.hxx>
#include <GProp_GProps.hxx>
#include <Poly_Triangulation.hxx>
#include <Standard_Failure.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Compound.hxx>
#include <gp_Circ.hxx>

#include <algorithm>
#include <cmath>
#include <sstream>

namespace tsr::sketch {

gp_Ax3 planeFrame(const std::string& spec, double offset) {
  gp_Ax3 f;
  if (spec == "XY" || spec.empty()) f = gp_Ax3(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1), gp_Dir(1, 0, 0));
  else if (spec == "XZ") f = gp_Ax3(gp_Pnt(0, 0, 0), gp_Dir(0, -1, 0), gp_Dir(1, 0, 0));
  else if (spec == "YZ") f = gp_Ax3(gp_Pnt(0, 0, 0), gp_Dir(1, 0, 0), gp_Dir(0, 1, 0));
  else if (spec.rfind("custom:", 0) == 0) {
    std::vector<double> v;
    std::stringstream ss(spec.substr(7));
    std::string tok;
    while (std::getline(ss, tok, ',')) {
      try {
        v.push_back(std::stod(tok));
      } catch (...) {
        throw SketchError("bad plane '" + spec + "'");
      }
    }
    if (v.size() != 9) throw SketchError("bad plane '" + spec + "'");
    try {
      f = gp_Ax3(gp_Pnt(v[0], v[1], v[2]), gp_Dir(v[3], v[4], v[5]), gp_Dir(v[6], v[7], v[8]));
    } catch (const Standard_Failure&) {
      throw SketchError("bad plane '" + spec + "' (degenerate directions)");
    }
  } else {
    throw SketchError("unknown sketch plane '" + spec + "'");
  }
  if (offset != 0) f.Translate(gp_Vec(f.Direction()) * offset);
  return f;
}

std::string customPlaneSpec(const gp_Ax3& f) {
  std::ostringstream os;
  os.precision(12);
  const gp_Pnt o = f.Location();
  const gp_Dir n = f.Direction(), x = f.XDirection();
  os << "custom:" << o.X() << ',' << o.Y() << ',' << o.Z() << ',' << n.X() << ',' << n.Y() << ',' << n.Z() << ','
     << x.X() << ',' << x.Y() << ',' << x.Z();
  return os.str();
}

gp_Pnt toWorld(const gp_Ax3& f, double x, double y) {
  return f.Location().Translated(gp_Vec(f.XDirection()) * x + gp_Vec(f.YDirection()) * y);
}

void toSketch(const gp_Ax3& f, const gp_Pnt& p, double& x, double& y) {
  const gp_Vec d(f.Location(), p);
  x = d.Dot(gp_Vec(f.XDirection()));
  y = d.Dot(gp_Vec(f.YDirection()));
}

TopoDS_Shape curve(const Sketch& s, const gp_Ax3& f, int id) {
  const Entity& e = s.entities.at(id);
  auto P = [&](int i) { return toWorld(f, s.points.at(i).x, s.points.at(i).y); };
  try {
    switch (e.type) {
      case EntityType::Line: {
        const gp_Pnt a = P(e.a), b = P(e.b);
        if (a.Distance(b) < 1e-7) return {};
        return BRepBuilderAPI_MakeEdge(a, b).Edge();
      }
      case EntityType::Circle: {
        if (e.radius < 1e-7) return {};
        return BRepBuilderAPI_MakeEdge(gp_Circ(gp_Ax2(P(e.center), f.Direction(), f.XDirection()), e.radius)).Edge();
      }
      case EntityType::Arc: {
        if (e.radius < 1e-7 || P(e.a).Distance(P(e.b)) < 1e-7) return {};
        const gp_Circ c(gp_Ax2(P(e.center), f.Direction(), f.XDirection()), e.radius);
        GC_MakeArcOfCircle arc(c, P(e.a), P(e.b), true);
        if (!arc.IsDone()) return {};
        return BRepBuilderAPI_MakeEdge(arc.Value()).Edge();
      }
      case EntityType::Spline: {
        // Fit points, without repeats; a closed spline is periodic.
        const bool closed = e.fit.size() > 2 && e.fit.front() == e.fit.back();
        std::vector<gp_Pnt> pts;
        for (size_t i = 0; i < e.fit.size() - (closed ? 1 : 0); ++i) {
          const gp_Pnt p = P(e.fit[i]);
          if (pts.empty() || pts.back().Distance(p) > 1e-7) pts.push_back(p);
        }
        if (closed && pts.size() > 1 && pts.back().Distance(pts.front()) < 1e-7) pts.pop_back();
        if (pts.size() < 2) return {};
        if (pts.size() == 2 && !closed) return BRepBuilderAPI_MakeEdge(pts[0], pts[1]).Edge();
        if (closed && pts.size() < 3) return {};
        Handle(TColgp_HArray1OfPnt) arr = new TColgp_HArray1OfPnt(1, static_cast<int>(pts.size()));
        for (size_t i = 0; i < pts.size(); ++i) arr->SetValue(static_cast<int>(i) + 1, pts[i]);
        GeomAPI_Interpolate interp(arr, closed, 1e-7);
        interp.Perform();
        if (!interp.IsDone()) return {};
        return BRepBuilderAPI_MakeEdge(interp.Curve()).Edge();
      }
    }
  } catch (const Standard_Failure&) {
  }
  return {};
}

TopoDS_Shape curves(const Sketch& s, const gp_Ax3& f, bool construction) {
  TopoDS_Compound c;
  BRep_Builder b;
  b.MakeCompound(c);
  for (int i = 0; i < static_cast<int>(s.entities.size()); ++i) {
    if (s.entities[i].construction != construction) continue;
    const TopoDS_Shape e = curve(s, f, i);
    if (!e.IsNull()) b.Add(c, e);
  }
  return c;
}

namespace {
// A point inside the face: the centroid of one of its mesh triangles.
bool interiorPoint(const TopoDS_Face& face, const gp_Ax3& f, double& x, double& y) {
  BRepMesh_IncrementalMesh mesh(face, 0.01, false, 0.5, false);
  TopLoc_Location loc;
  const Handle(Poly_Triangulation) tri = BRep_Tool::Triangulation(face, loc);
  if (tri.IsNull() || tri->NbTriangles() == 0) return false;
  // Largest triangle: its centroid is far from the boundary.
  double best = -1;
  gp_Pnt bestP;
  for (int i = 1; i <= tri->NbTriangles(); ++i) {
    int n1, n2, n3;
    tri->Triangle(i).Get(n1, n2, n3);
    const gp_Pnt a = tri->Node(n1).Transformed(loc), b = tri->Node(n2).Transformed(loc),
                 c = tri->Node(n3).Transformed(loc);
    const double area = gp_Vec(a, b).Crossed(gp_Vec(a, c)).Magnitude();
    if (area > best) {
      best = area;
      bestP = gp_Pnt((a.XYZ() + b.XYZ() + c.XYZ()) / 3);
    }
  }
  toSketch(f, bestP, x, y);
  return true;
}
} // namespace

std::vector<Profile> profiles(const Sketch& s, const gp_Ax3& f) {
  std::vector<Profile> out;
  const TopoDS_Shape edges = curves(s, f, false);
  if (!TopExp_Explorer(edges, TopAbs_EDGE).More()) return out;
  try {
    // Split the curves at every crossing, chain them into wires, and let
    // OCCT build the faces of the planar arrangement.
    int count = 0;
    for (TopExp_Explorer it(edges, TopAbs_EDGE); it.More(); it.Next()) ++count;
    TopoDS_Shape splitEdges = edges;
    if (count > 1) {
      BOPAlgo_Builder split;
      for (TopExp_Explorer it(edges, TopAbs_EDGE); it.More(); it.Next()) split.AddArgument(it.Current());
      split.SetRunParallel(false);
      split.Perform();
      if (split.HasErrors()) return out;
      splitEdges = split.Shape();
    }
    TopoDS_Shape wires, faces;
    BOPAlgo_Tools::EdgesToWires(splitEdges, wires, /*shared=*/true);
    if (!BOPAlgo_Tools::WiresToFaces(wires, faces)) return out;
    for (TopExp_Explorer it(faces, TopAbs_FACE); it.More(); it.Next()) {
      Profile p;
      p.face = TopoDS::Face(it.Current());
      GProp_GProps g;
      BRepGProp::SurfaceProperties(p.face, g);
      p.area = g.Mass();
      if (p.area < 1e-9 || !interiorPoint(p.face, f, p.x, p.y)) continue;
      out.push_back(p);
    }
  } catch (const Standard_Failure&) {
    return {};
  }
  std::stable_sort(out.begin(), out.end(), [](const Profile& a, const Profile& b) { return a.area > b.area; });
  return out;
}

int profileAt(const std::vector<Profile>& ps, const gp_Ax3& f, double x, double y) {
  const gp_Pnt p = toWorld(f, x, y);
  // Smallest region containing the point (regions do not overlap, but be safe).
  int best = -1;
  for (int i = 0; i < static_cast<int>(ps.size()); ++i) {
    BRepClass_FaceClassifier cls(ps[i].face, p, 1e-6);
    if (cls.State() == TopAbs_IN && (best < 0 || ps[i].area < ps[best].area)) best = i;
  }
  return best;
}

} // namespace tsr::sketch
