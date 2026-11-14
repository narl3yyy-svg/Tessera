#include "tsr/sketch/SketchGeometry.h"

#include <BOPAlgo_Builder.hxx>
#include <BOPAlgo_Tools.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <NCollection_String.hxx>
#include <Font_BRepTextBuilder.hxx>
#include <Font_BRepFont.hxx>
#include <BRepClass_FaceClassifier.hxx>
#include <BRepGProp.hxx>
#include <BRepMesh_IncrementalMesh.hxx>
#include <BRep_Builder.hxx>
#include <BRep_Tool.hxx>
#include <GC_MakeArcOfCircle.hxx>
#include <GC_MakeArcOfEllipse.hxx>
#include <TColStd_HArray1OfBoolean.hxx>
#include <TColgp_Array1OfVec.hxx>
#include <GeomAPI_ProjectPointOnCurve.hxx>
#include <GeomAPI_Interpolate.hxx>
#include <NCollection_UtfIterator.hxx>
#include <BRepAdaptor_Curve.hxx>
#include <GCPnts_AbscissaPoint.hxx>
#include <Font_TextFormatter.hxx>
#include <TColStd_Array1OfInteger.hxx>
#include <TColStd_Array1OfReal.hxx>
#include <TColgp_Array1OfPnt.hxx>
#include <Geom_BSplineCurve.hxx>
#include <Geom_BezierCurve.hxx>
#include <TColgp_HArray1OfPnt.hxx>
#include <GProp_GProps.hxx>
#include <Poly_Triangulation.hxx>
#include <Standard_Failure.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS_Vertex.hxx>
#include <TopExp.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Compound.hxx>
#include <gp_Circ.hxx>
#include <gp_Elips.hxx>

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
  // Included 3D geometry stands `z` above the plane.
  auto P = [&](int i) {
    const Point& q = s.points.at(i);
    return toWorld(f, q.x, q.y).Translated(gp_Vec(f.Direction()) * q.z);
  };
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
      case EntityType::Ellipse: {
        const gp_Pnt c = P(e.center), a = P(e.a);
        const double A = c.Distance(a), B = std::abs(e.radius);
        if (A < 1e-7 || B < 1e-7) return {};
        // OCCT wants the major radius first: if the drawn axis is the short
        // one, the long axis runs across it.
        gp_Dir major(gp_Vec(c, a));
        if (A < B) major = f.Direction().Crossed(major);
        const gp_Elips el(gp_Ax2(c, f.Direction(), major), std::max(A, B), std::min(A, B));
        if (e.isEllipticalArc()) {
          if (P(e.fit[0]).Distance(P(e.fit[1])) < 1e-7) return {};
          GC_MakeArcOfEllipse arc(el, P(e.fit[0]), P(e.fit[1]), true);
          if (!arc.IsDone()) return {};
          return BRepBuilderAPI_MakeEdge(arc.Value()).Edge();
        }
        return BRepBuilderAPI_MakeEdge(el).Edge();
      }
      case EntityType::Spline: {
        if (e.kind == SplineKind::Conic) {
          // A rational quadratic Bezier: start, vertex, end; the vertex's
          // weight rho / (1 - rho) gives the conic its rho.
          const double rho = e.radius;
          if (e.fit.size() != 3 || !(rho > 0 && rho < 1)) return {};
          TColgp_Array1OfPnt poles(1, 3);
          TColStd_Array1OfReal weights(1, 3);
          for (int i = 0; i < 3; ++i) poles.SetValue(i + 1, P(e.fit[i]));
          if (poles(1).Distance(poles(3)) < 1e-7) return {};
          weights.SetValue(1, 1);
          weights.SetValue(2, rho / (1 - rho));
          weights.SetValue(3, 1);
          return BRepBuilderAPI_MakeEdge(Handle(Geom_BezierCurve)(new Geom_BezierCurve(poles, weights))).Edge();
        }
        if (e.kind == SplineKind::Control) {
          // A clamped B-spline of degree 3 (less with fewer points) on its
          // control frame: it starts and ends on the frame's ends.
          std::vector<gp_Pnt> pts;
          for (int i : e.fit) pts.push_back(P(i));
          const int n = static_cast<int>(pts.size());
          if (n < 2 || (n < 4 && pts.front().Distance(pts.back()) < 1e-7)) return {};
          const int deg = std::min(3, n - 1);
          TColgp_Array1OfPnt poles(1, n);
          for (int i = 0; i < n; ++i) poles.SetValue(i + 1, pts[i]);
          const int nk = n - deg + 1;
          TColStd_Array1OfReal knots(1, nk);
          TColStd_Array1OfInteger mults(1, nk);
          for (int i = 1; i <= nk; ++i) {
            knots.SetValue(i, static_cast<double>(i - 1));
            mults.SetValue(i, (i == 1 || i == nk) ? deg + 1 : 1);
          }
          return BRepBuilderAPI_MakeEdge(Handle(Geom_BSplineCurve)(new Geom_BSplineCurve(poles, knots, mults, deg))).Edge();
        }
        // Fit points, without repeats; a closed spline is periodic. Tangent
        // handles that are set fix the derivative there (chord-length
        // parameters, so length 1 is the natural speed).
        const bool closed = e.fit.size() > 2 && e.fit.front() == e.fit.back();
        std::vector<gp_Pnt> pts;
        std::vector<gp_Vec> tans;
        bool anyTangent = false;
        for (size_t i = 0; i < e.fit.size() - (closed ? 1 : 0); ++i) {
          const gp_Pnt p = P(e.fit[i]);
          gp_Vec t(0, 0, 0);
          if (i < e.handles.size()) t = gp_Vec(f.XDirection()) * e.handles[i].x + gp_Vec(f.YDirection()) * e.handles[i].y;
          if (pts.empty() || pts.back().Distance(p) > 1e-7) {
            pts.push_back(p);
            tans.push_back(t);
            anyTangent = anyTangent || t.Magnitude() > 1e-9;
          }
        }
        if (closed && pts.size() > 1 && pts.back().Distance(pts.front()) < 1e-7) {
          pts.pop_back();
          tans.pop_back();
        }
        if (pts.size() < 2) return {};
        if (pts.size() == 2 && !closed && !anyTangent) return BRepBuilderAPI_MakeEdge(pts[0], pts[1]).Edge();
        if (closed && pts.size() < 3) return {};
        const int n = static_cast<int>(pts.size());
        Handle(TColgp_HArray1OfPnt) arr = new TColgp_HArray1OfPnt(1, n);
        for (int i = 0; i < n; ++i) arr->SetValue(i + 1, pts[i]);
        if (anyTangent) {
          TColgp_Array1OfVec tv(1, n);
          Handle(TColStd_HArray1OfBoolean) flags = new TColStd_HArray1OfBoolean(1, n);
          for (int i = 0; i < n; ++i) {
            const bool set = tans[i].Magnitude() > 1e-9;
            tv.SetValue(i + 1, set ? tans[i] : gp_Vec(1, 0, 0));
            flags->SetValue(i + 1, set);
          }
          GeomAPI_Interpolate withTangents(arr, closed, 1e-7);
          withTangents.Load(tv, flags, false);
          withTangents.Perform();
          if (withTangents.IsDone()) return BRepBuilderAPI_MakeEdge(withTangents.Curve()).Edge();
        }
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

namespace {
TopoDS_Shape entityCurves(const Sketch& s, const gp_Ax3& f, bool construction, bool planarOnly = false) {
  TopoDS_Compound c;
  BRep_Builder b;
  b.MakeCompound(c);
  for (int i = 0; i < static_cast<int>(s.entities.size()); ++i) {
    if (s.entities[i].construction != construction) continue;
    if (planarOnly && s.entities[i].included) continue;   // 3D reference geometry bounds no profile
    const TopoDS_Shape e = curve(s, f, i);
    if (!e.IsNull()) b.Add(c, e);
  }
  return c;
}
} // namespace

TopoDS_Shape textShape(const Sketch& s, const gp_Ax3& f, int id) {
  const Text& t = s.texts.at(id);
  if (t.text.empty() || !(t.height > 0)) return {};
  try {
    Font_BRepFont font;
    const TCollection_AsciiString family(t.font.empty() ? "sans-serif" : t.font.c_str());
    if (!font.FindAndInit(family, Font_FontAspect_Regular, t.height, Font_StrictLevel_Any)) return {};
    const Point& p = s.points.at(t.point);
    Font_BRepTextBuilder builder;
    if (t.path >= 0) {
      // Text on a path: each letter stands on the curve, upright to it.
      const TopoDS_Shape c = curve(s, f, t.path);
      if (c.IsNull()) return {};
      BRepAdaptor_Curve ac(TopoDS::Edge(c));
      const double L = GCPnts_AbscissaPoint::Length(ac);
      // Letters and their advances.
      std::vector<Standard_Utf32Char> chars;
      for (NCollection_Utf8Iter it(t.text.c_str()); *it != 0; ++it) chars.push_back(*it);
      std::vector<double> adv(chars.size());
      double width = 0;
      for (size_t i = 0; i < chars.size(); ++i) {
        adv[i] = font.AdvanceX(chars[i], i + 1 < chars.size() ? chars[i + 1] : 0);
        width += adv[i];
      }
      double at = t.hAlign == "center" ? (L - width) / 2 : t.hAlign == "right" ? L - width : 0;
      TopoDS_Compound out;
      BRep_Builder bb;
      bb.MakeCompound(out);
      for (size_t i = 0; i < chars.size(); ++i) {
        const double s0 = std::clamp(at, 0.0, L);
        const double along = t.flip ? L - s0 : s0;
        GCPnts_AbscissaPoint ap(ac, along, ac.FirstParameter());
        if (!ap.IsDone()) break;
        gp_Pnt q;
        gp_Vec d;
        ac.D1(ap.Parameter(), q, d);
        if (d.Magnitude() < 1e-12) break;
        if (t.flip) d.Reverse();
        if (chars[i] != ' ') {
          char32_t one[2] = {chars[i], 0};
          const NCollection_String letter(reinterpret_cast<const Standard_Utf32Char*>(one));
          const TopoDS_Shape g = builder.Perform(font, letter, gp_Ax3(q, f.Direction(), gp_Dir(d)), Graphic3d_HTA_LEFT,
                                                 Graphic3d_VTA_BOTTOM);
          if (!g.IsNull()) bb.Add(out, g);
        }
        at += adv[i];
      }
      return out;
    }
    gp_Dir x = f.XDirection();
    x.Rotate(gp_Ax1(f.Location(), f.Direction()), t.angle);
    const gp_Dir y = f.Direction().Crossed(x);
    if (t.corner >= 0) {
      // A text box: the lines aligned between its corners (in the text's
      // own, possibly turned, frame).
      const Point& c = s.points.at(t.corner);
      const gp_Vec d(toWorld(f, p.x, p.y), toWorld(f, c.x, c.y));
      const double u = d.Dot(gp_Vec(x)), v = d.Dot(gp_Vec(y));
      const double u0 = std::min(0.0, u), u1 = std::max(0.0, u), v0 = std::min(0.0, v), v1 = std::max(0.0, v);
      const double au = t.hAlign == "center" ? (u0 + u1) / 2 : t.hAlign == "right" ? u1 : u0;
      const double av = t.vAlign == "middle" ? (v0 + v1) / 2 : t.vAlign == "top" ? v1 : v0;
      const gp_Pnt anchor = toWorld(f, p.x, p.y).Translated(gp_Vec(x) * au + gp_Vec(y) * av);
      Handle(Font_TextFormatter) fmt = new Font_TextFormatter();
      fmt->SetupAlignment(t.hAlign == "center" ? Graphic3d_HTA_CENTER : t.hAlign == "right" ? Graphic3d_HTA_RIGHT
                                                                                            : Graphic3d_HTA_LEFT,
                         t.vAlign == "middle" ? Graphic3d_VTA_CENTER : t.vAlign == "top" ? Graphic3d_VTA_TOP
                                                                                        : Graphic3d_VTA_BOTTOM);
      fmt->Append(NCollection_String(t.text.c_str()), *font.FTFont());
      fmt->Format();
      return builder.Perform(font, fmt, gp_Ax3(anchor, f.Direction(), x));
    }
    const gp_Ax3 pen(toWorld(f, p.x, p.y), f.Direction(), x);
    return builder.Perform(font, NCollection_String(t.text.c_str()), pen, Graphic3d_HTA_LEFT, Graphic3d_VTA_BOTTOM);
  } catch (const Standard_Failure&) {
    return {};
  }
}

TopoDS_Shape curves(const Sketch& s, const gp_Ax3& f, bool construction) {
  const TopoDS_Shape base = entityCurves(s, f, construction);
  if (construction || s.texts.empty()) return base;
  TopoDS_Compound c;
  BRep_Builder b;
  b.MakeCompound(c);
  if (!base.IsNull())
    for (TopExp_Explorer it(base, TopAbs_EDGE); it.More(); it.Next()) b.Add(c, it.Current());
  for (int i = 0; i < static_cast<int>(s.texts.size()); ++i)
    if (const TopoDS_Shape ts = textShape(s, f, i); !ts.IsNull())
      for (TopExp_Explorer it(ts, TopAbs_EDGE); it.More(); it.Next()) b.Add(c, it.Current());
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
  // Text: each letter's face (with its holes) is a profile of its own.
  for (int i = 0; i < static_cast<int>(s.texts.size()); ++i) {
    const TopoDS_Shape ts = textShape(s, f, i);
    if (ts.IsNull()) continue;
    for (TopExp_Explorer it(ts, TopAbs_FACE); it.More(); it.Next()) {
      Profile p;
      p.face = TopoDS::Face(it.Current());
      GProp_GProps g;
      BRepGProp::SurfaceProperties(p.face, g);
      p.area = g.Mass();
      if (p.area > 1e-9 && interiorPoint(p.face, f, p.x, p.y)) out.push_back(p);
    }
  }
  const TopoDS_Shape edges = entityCurves(s, f, false, true);
  if (!TopExp_Explorer(edges, TopAbs_EDGE).More()) {
    std::stable_sort(out.begin(), out.end(), [](const Profile& a, const Profile& b) { return a.area > b.area; });
    return out;
  }
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
    // Dangling pieces bound no region (a line ending inside a circle, the
    // tail of a line past a corner): drop edges with a free end, again and
    // again, so only closed loops remain.
    std::vector<TopoDS_Edge> kept;
    for (TopExp_Explorer it(splitEdges, TopAbs_EDGE); it.More(); it.Next()) kept.push_back(TopoDS::Edge(it.Current()));
    for (bool changed = true; changed;) {
      changed = false;
      std::vector<TopoDS_Edge> next;
      for (const auto& e : kept) {
        TopoDS_Vertex v0, v1;
        TopExp::Vertices(e, v0, v1);
        auto degree = [&](const TopoDS_Vertex& v) {
          int d = 0;
          for (const auto& k : kept)
            for (TopExp_Explorer vx(k, TopAbs_VERTEX); vx.More(); vx.Next())
              if (vx.Current().IsSame(v)) ++d;
          return d;
        };
        const bool closed = !v0.IsNull() && v0.IsSame(v1);
        if (!closed && (v0.IsNull() || v1.IsNull() || degree(v0) < 2 || degree(v1) < 2)) {
          changed = true;
          continue;
        }
        next.push_back(e);
      }
      kept.swap(next);
    }
    if (kept.empty()) return out;
    TopoDS_Compound loops;
    BRep_Builder lb;
    lb.MakeCompound(loops);
    for (const auto& e : kept) lb.Add(loops, e);
    splitEdges = loops;
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

std::vector<SplineHandle> splineHandles(const Sketch& s, int entity) {
  std::vector<SplineHandle> out;
  if (entity < 0 || entity >= static_cast<int>(s.entities.size())) return out;
  const Entity& e = s.entities[entity];
  if (e.type != EntityType::Spline || e.kind != SplineKind::Fit) return out;
  const gp_Ax3 xy(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1), gp_Dir(1, 0, 0));
  const TopoDS_Shape sh = curve(s, xy, entity);
  if (sh.IsNull()) return out;
  double t0 = 0, t1 = 0;
  const Handle(Geom_Curve) gc = BRep_Tool::Curve(TopoDS::Edge(sh), t0, t1);
  if (gc.IsNull()) return out;
  const bool closed = e.fit.size() > 2 && e.fit.front() == e.fit.back();
  const int n = static_cast<int>(e.fit.size()) - (closed ? 1 : 0);
  for (int i = 0; i < n; ++i) {
    SplineHandle h;
    h.index = i;
    const Point& q = s.points.at(e.fit[i]);
    h.x = q.x;
    h.y = q.y;
    // Drawn a third of the shorter neighbouring chord long, as a Bezier handle.
    double arm = 1e300;
    for (int j : {i - 1, i + 1}) {
      const int k = closed ? (j + n) % n : j;
      if (k < 0 || k >= static_cast<int>(e.fit.size())) continue;
      const Point& o = s.points.at(e.fit[k]);
      const double d = std::hypot(o.x - q.x, o.y - q.y);
      if (d > 1e-9) arm = std::min(arm, d / 3);
    }
    h.arm = arm < 1e299 ? arm : 1.0;
    h.set = i < static_cast<int>(e.handles.size()) && std::hypot(e.handles[i].x, e.handles[i].y) > 1e-9;
    if (h.set) {
      h.tx = e.handles[i].x;
      h.ty = e.handles[i].y;
    } else {
      // The direction the curve runs there.
      try {
        GeomAPI_ProjectPointOnCurve proj(gp_Pnt(q.x, q.y, 0), gc, t0, t1);
        if (proj.NbPoints() > 0) {
          gp_Pnt p;
          gp_Vec d;
          gc->D1(proj.LowerDistanceParameter(), p, d);
          const double m = d.Magnitude();
          if (m > 1e-12) {
            h.tx = d.X() / m;
            h.ty = d.Y() / m;
          }
        }
      } catch (const Standard_Failure&) {
      }
    }
    out.push_back(h);
  }
  return out;
}

std::string toDxf(const Sketch& s, bool construction) {
  const double mm = 10.0;   // internal cm
  std::ostringstream o;
  o.precision(10);
  auto pair = [&](int code, const std::string& v) { o << code << '\n' << v << '\n'; };
  auto num = [&](int code, double v) { o << code << '\n' << v << '\n'; };
  pair(0, "SECTION");
  pair(2, "HEADER");
  pair(9, "$ACADVER");
  pair(1, "AC1009");
  pair(9, "$INSUNITS");
  pair(70, "4");   // millimetres
  pair(0, "ENDSEC");
  pair(0, "SECTION");
  pair(2, "ENTITIES");
  const gp_Ax3 xy(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1), gp_Dir(1, 0, 0));
  auto P = [&](int i) { return s.points.at(i); };
  auto polyline = [&](const std::vector<std::pair<double, double>>& pts, const char* layer, bool closed) {
    if (pts.size() < 2) return;
    pair(0, "POLYLINE");
    pair(8, layer);
    pair(66, "1");
    pair(70, closed ? "1" : "0");
    for (const auto& [x, y] : pts) {
      pair(0, "VERTEX");
      pair(8, layer);
      num(10, x * mm);
      num(20, y * mm);
      num(30, 0);
    }
    pair(0, "SEQEND");
    pair(8, layer);
  };
  auto sampled = [&](const TopoDS_Shape& edge, std::vector<std::pair<double, double>>& pts) {
    BRepAdaptor_Curve c(TopoDS::Edge(edge));
    const double a = c.FirstParameter(), b = c.LastParameter();
    const int n = 96;
    for (int k = 0; k <= n; ++k) {
      const gp_Pnt q = c.Value(a + (b - a) * k / n);
      pts.emplace_back(q.X(), q.Y());
    }
  };
  for (int i = 0; i < static_cast<int>(s.entities.size()); ++i) {
    const Entity& e = s.entities[i];
    if (e.construction && !construction) continue;
    if (e.included) continue;   // 3D reference geometry is not part of the drawing
    const char* layer = e.construction ? "CONSTRUCTION" : "0";
    switch (e.type) {
      case EntityType::Line:
        pair(0, "LINE");
        pair(8, layer);
        num(10, P(e.a).x * mm);
        num(20, P(e.a).y * mm);
        num(30, 0);
        num(11, P(e.b).x * mm);
        num(21, P(e.b).y * mm);
        num(31, 0);
        break;
      case EntityType::Circle:
        pair(0, "CIRCLE");
        pair(8, layer);
        num(10, P(e.center).x * mm);
        num(20, P(e.center).y * mm);
        num(30, 0);
        num(40, e.radius * mm);
        break;
      case EntityType::Arc: {
        const Point c = P(e.center);
        const double deg = 180.0 / 3.14159265358979323846;
        pair(0, "ARC");
        pair(8, layer);
        num(10, c.x * mm);
        num(20, c.y * mm);
        num(30, 0);
        num(40, e.radius * mm);
        num(50, std::atan2(P(e.a).y - c.y, P(e.a).x - c.x) * deg);   // anticlockwise from start to end
        num(51, std::atan2(P(e.b).y - c.y, P(e.b).x - c.x) * deg);
        break;
      }
      default: {
        const TopoDS_Shape edge = curve(s, xy, i);
        if (edge.IsNull()) break;
        std::vector<std::pair<double, double>> pts;
        sampled(edge, pts);
        const bool closed = pts.size() > 2 && std::hypot(pts.front().first - pts.back().first,
                                                         pts.front().second - pts.back().second) < 1e-9;
        if (closed) pts.pop_back();
        polyline(pts, layer, closed);
      }
    }
  }
  for (int i = 0; i < static_cast<int>(s.texts.size()); ++i) {
    const TopoDS_Shape t = textShape(s, xy, i);
    if (t.IsNull()) continue;
    for (TopExp_Explorer x(t, TopAbs_EDGE); x.More(); x.Next()) {
      std::vector<std::pair<double, double>> pts;
      sampled(x.Current(), pts);
      polyline(pts, "TEXT", false);
    }
  }
  pair(0, "ENDSEC");
  pair(0, "EOF");
  return o.str();
}

} // namespace tsr::sketch
