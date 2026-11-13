#include "tsr/kernel/Kernel.h"

#include <BRepBndLib.hxx>
#include <BRepCheck_Analyzer.hxx>
#include <BRepGProp.hxx>
#include <BRepAlgoAPI_Common.hxx>
#include <BRepAlgoAPI_Cut.hxx>
#include <BRepAlgoAPI_Fuse.hxx>
#include <BRepPrimAPI_MakeBox.hxx>
#include <BRepPrimAPI_MakeCone.hxx>
#include <BRepPrimAPI_MakeCylinder.hxx>
#include <BRepPrimAPI_MakeSphere.hxx>
#include <BRepPrimAPI_MakeTorus.hxx>
#include <BRepPrimAPI_MakePrism.hxx>
#include <LocOpe_DPrism.hxx>
#include <BRepOffsetAPI_MakePipe.hxx>
#include <BRepOffsetAPI_MakePipeShell.hxx>
#include <TopoDS_Vertex.hxx>
#include <BRepOffsetAPI_MakeOffset.hxx>
#include <BRepOffsetAPI_ThruSections.hxx>
#include <BRepTools.hxx>
#include <ShapeAnalysis_FreeBounds.hxx>
#include <TopTools_HSequenceOfShape.hxx>
#include <TopoDS_Wire.hxx>
#include <BRepPrimAPI_MakeRevol.hxx>
#include <BRepAdaptor_Curve.hxx>
#include <BRepBuilderAPI_MakeVertex.hxx>
#include <BRepExtrema_DistShapeShape.hxx>
#include <BRepFilletAPI_MakeChamfer.hxx>
#include <BRepFilletAPI_MakeFillet.hxx>
#include <TopoDS.hxx>
#include <BRepAdaptor_Surface.hxx>
#include <BRepLProp_SLProps.hxx>
#include <BRep_Tool.hxx>
#include <Geom_Surface.hxx>
#include <ShapeAnalysis_Surface.hxx>
#include <TopTools_IndexedDataMapOfShapeListOfShape.hxx>
#include <gp_Pnt2d.hxx>

#include <cstdio>
#include <cmath>

#include <BRepAlgoAPI_Splitter.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepBuilderAPI_MakeSolid.hxx>
#include <BRepClass_FaceClassifier.hxx>
#include <BRepMesh_IncrementalMesh.hxx>
#include <BRepOffsetAPI_MakeOffsetShape.hxx>
#include <BRepOffsetAPI_DraftAngle.hxx>
#include <BRepOffset_MakeOffset.hxx>
#include <BRepTools.hxx>
#include <gp_Cylinder.hxx>
#include <BRepOffsetAPI_MakeThickSolid.hxx>
#include <Poly_Triangulation.hxx>
#include <TopoDS_Shell.hxx>
#include <gp_Pln.hxx>
#include <gp_Trsf.hxx>
#include <BRepBuilderAPI_Transform.hxx>
#include <ShapeUpgrade_UnifySameDomain.hxx>
#include <TopExp_Explorer.hxx>
#include <gp_Ax2.hxx>
#include <Bnd_Box.hxx>
#include <GProp_GProps.hxx>
#include <Standard_Failure.hxx>
#include <TopAbs_ShapeEnum.hxx>
#include <TopTools_IndexedMapOfShape.hxx>
#include <TopExp.hxx>
#include <optional>
#include <GeomAPI_ProjectPointOnSurf.hxx>
#include <ShapeFix_Solid.hxx>
#include <TColStd_Array1OfReal.hxx>
#include <TColgp_Array1OfPnt.hxx>
#include <TColStd_Array2OfReal.hxx>
#include <TColgp_Array2OfPnt.hxx>
#include <Geom_BezierCurve.hxx>
#include <Geom_BezierSurface.hxx>
#include <BRepBuilderAPI_Sewing.hxx>
#include <BRepTools_WireExplorer.hxx>
#include <TopLoc_Location.hxx>
#include <functional>
#include <BRepAdaptor_CompCurve.hxx>
#include <BRepPrimAPI_MakeHalfSpace.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <TopoDS_Solid.hxx>
#include <gp_Pln.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepBuilderAPI_MakePolygon.hxx>
#include <BRepLib.hxx>
#include <Geom2d_Line.hxx>
#include <Geom_ConicalSurface.hxx>
#include <Geom_CylindricalSurface.hxx>
#include <gp_Ax3.hxx>
#include <gp_Circ.hxx>
#include <gp_Vec2d.hxx>
#include <sstream>

#include <memory>

namespace tsr::kernel {

namespace {
gp_Pnt pnt(Vec3 v) { return gp_Pnt(v.x, v.y, v.z); }

gp_Ax2 frame(Vec3 origin, Axis axis) {
  switch (axis) {
    case Axis::X: return gp_Ax2(pnt(origin), gp::DX(), gp::DY());
    case Axis::Y: return gp_Ax2(pnt(origin), gp::DY(), gp::DZ());
    case Axis::Z: break;
  }
  return gp_Ax2(pnt(origin), gp::DZ(), gp::DX());
}

template <class F>
TopoDS_Shape guarded(const char* what, F&& build) {
  try {
    TopoDS_Shape s = build();
    if (s.IsNull()) throw KernelError(std::string(what) + " failed");
    return s;
  } catch (const Standard_Failure& f) {
    throw KernelError(std::string(what) + ": " + f.GetMessageString());
  }
}

void requirePositive(double v, const char* what) {
  if (!(v > 0)) throw KernelError(std::string(what) + " must be positive");
}
} // namespace

TopoDS_Shape makeBox(double dx, double dy, double dz, Vec3 corner) {
  if (!(dx > 0 && dy > 0 && dz > 0)) throw KernelError("box dimensions must be positive");
  return guarded("Box", [&] { return BRepPrimAPI_MakeBox(pnt(corner), dx, dy, dz).Shape(); });
}

TopoDS_Shape makeCylinder(double radius, double height, Vec3 base, Axis axis) {
  requirePositive(radius, "cylinder radius");
  requirePositive(height, "cylinder height");
  return guarded("Cylinder", [&] { return BRepPrimAPI_MakeCylinder(frame(base, axis), radius, height).Shape(); });
}

TopoDS_Shape makeSphere(double radius, Vec3 center) {
  requirePositive(radius, "sphere radius");
  return guarded("Sphere", [&] { return BRepPrimAPI_MakeSphere(pnt(center), radius).Shape(); });
}

TopoDS_Shape makeTorus(double major, double minor, Vec3 center, Axis axis) {
  requirePositive(major, "torus radius");
  requirePositive(minor, "torus section radius");
  if (minor >= major) throw KernelError("torus section radius must be smaller than the torus radius");
  return guarded("Torus", [&] { return BRepPrimAPI_MakeTorus(frame(center, axis), major, minor).Shape(); });
}

TopoDS_Shape makeCone(double r1, double r2, double height, Vec3 base, Axis axis) {
  requirePositive(height, "cone height");
  if (r1 < 0 || r2 < 0 || (r1 == 0 && r2 == 0)) throw KernelError("cone radii must be >= 0 and not both 0");
  if (r1 == r2) throw KernelError("cone radii must differ (use a cylinder)");
  return guarded("Cone", [&] { return BRepPrimAPI_MakeCone(frame(base, axis), r1, r2, height).Shape(); });
}

TopoDS_Shape extrude(const std::vector<TopoDS_Shape>& faces, Vec3 dir, double distance, bool symmetric) {
  if (faces.empty()) throw KernelError("nothing to extrude: no profile selected");
  if (!(std::abs(distance) > 1e-9)) throw KernelError("extrude distance must not be zero");
  const gp_Vec d = gp_Vec(dir.x, dir.y, dir.z).Normalized() * distance;
  TopoDS_Shape result;
  for (const TopoDS_Shape& f : faces) {
    TopoDS_Shape prism = guarded("Extrude", [&]() -> TopoDS_Shape {
      TopoDS_Shape base = f;
      gp_Vec v = d;
      if (symmetric) {
        gp_Trsf t;
        t.SetTranslation(-d);
        base = BRepBuilderAPI_Transform(f, t, true).Shape();
        v = d * 2;
      }
      BRepPrimAPI_MakePrism mk(base, v);
      return mk.IsDone() ? mk.Shape() : TopoDS_Shape();
    });
    result = result.IsNull() ? prism : boolean(BooleanOp::Join, result, prism);
  }
  return result;
}

TopoDS_Shape revolve(const std::vector<TopoDS_Shape>& faces, Vec3 origin, Vec3 dir, double angle, bool symmetric) {
  if (faces.empty()) throw KernelError("nothing to revolve: no profile selected");
  if (!(std::abs(angle) > 1e-9)) throw KernelError("revolve angle must not be zero");
  const gp_Ax1 axis(pnt(origin), gp_Dir(dir.x, dir.y, dir.z));
  TopoDS_Shape result;
  for (const TopoDS_Shape& f : faces) {
    TopoDS_Shape solid;
    try {
      solid = guarded("Revolve", [&]() -> TopoDS_Shape {
      TopoDS_Shape base = f;
      if (symmetric) {
        gp_Trsf t;
        t.SetRotation(axis, -angle / 2);
        base = BRepBuilderAPI_Transform(f, t, true).Shape();
      }
      BRepPrimAPI_MakeRevol mk(base, axis, angle, true);
      return mk.IsDone() ? mk.Shape() : TopoDS_Shape();
      });
    } catch (const KernelError&) {
      solid.Nullify();
    }
    if (solid.IsNull() || !isValid(solid))
      throw KernelError("Revolve: the profile crosses the axis (a profile may touch the axis but not cross it)");
    result = result.IsNull() ? solid : boolean(BooleanOp::Join, result, solid);
  }
  return result;
}

std::vector<TopoDS_Shape> edgesNear(const TopoDS_Shape& shape, const std::vector<Vec3>& points, double tolerance) {
  TopTools_IndexedMapOfShape edges;
  TopExp::MapShapes(shape, TopAbs_EDGE, edges);
  std::vector<TopoDS_Shape> out;
  for (const Vec3& p : points) {
    const TopoDS_Shape v = BRepBuilderAPI_MakeVertex(pnt(p)).Shape();
    int best = 0;
    double bestD = tolerance;
    for (int i = 1; i <= edges.Extent(); ++i) {
      BRepExtrema_DistShapeShape d(v, edges(i));
      if (d.IsDone() && d.Value() < bestD) {
        bestD = d.Value();
        best = i;
      }
    }
    if (best == 0) throw KernelError("a selected edge no longer exists (the body changed too much)");
    bool dup = false;
    for (const auto& e : out) dup = dup || e.IsSame(edges(best));
    if (!dup) out.push_back(edges(best));
  }
  return out;
}

std::string vertexReference(const TopoDS_Shape& vertex) {
  if (vertex.IsNull() || vertex.ShapeType() != TopAbs_VERTEX) throw KernelError("not a vertex");
  const gp_Pnt p = BRep_Tool::Pnt(TopoDS::Vertex(vertex));
  std::ostringstream os;
  os.precision(12);
  os << p.X() << ',' << p.Y() << ',' << p.Z();
  return os.str();
}

std::vector<TopoDS_Shape> resolveVertices(const TopoDS_Shape& body, const std::string& refs) {
  TopTools_IndexedMapOfShape vertices;
  TopExp::MapShapes(body, TopAbs_VERTEX, vertices);
  Bnd_Box box;
  BRepBndLib::Add(body, box);
  double tol = 0.05;
  if (!box.IsVoid()) {
    double x0, y0, z0, x1, y1, z1;
    box.Get(x0, y0, z0, x1, y1, z1);
    tol = std::max(tol, 0.2 * std::hypot(x1 - x0, y1 - y0, z1 - z0));
  }
  std::vector<TopoDS_Shape> out;
  std::stringstream all(refs);
  std::string item;
  while (std::getline(all, item, ';')) {
    if (item.empty()) continue;
    std::vector<double> v;
    std::stringstream ss(item);
    std::string tok;
    while (std::getline(ss, tok, ',')) {
      try {
        v.push_back(std::stod(tok));
      } catch (...) {
        throw KernelError("bad vertex reference '" + item + "'");
      }
    }
    if (v.size() != 3) throw KernelError("bad vertex reference '" + item + "'");
    const gp_Pnt want(v[0], v[1], v[2]);
    int best = 0;
    double bestD = tol;
    for (int i = 1; i <= vertices.Extent(); ++i) {
      const double d = BRep_Tool::Pnt(TopoDS::Vertex(vertices(i))).Distance(want);
      if (d < bestD) {
        bestD = d;
        best = i;
      }
    }
    if (best == 0) throw KernelError("a selected vertex no longer exists (the body changed too much)");
    out.push_back(vertices(best));
  }
  if (out.empty()) throw KernelError("select at least one vertex");
  return out;
}

Vec3 edgeMidpoint(const TopoDS_Shape& edge) {
  BRepAdaptor_Curve c(TopoDS::Edge(edge));
  const gp_Pnt p = c.Value((c.FirstParameter() + c.LastParameter()) / 2);
  return {p.X(), p.Y(), p.Z()};
}


// ---------------------------------------------------------------------------
// Edge references

namespace {
struct EdgeSig {
  Vec3 point;
  bool full = false;
  int type = 0;
  Vec3 rel, tangent;
  std::vector<Vec3> normals;
};

gp_Vec vec(Vec3 v) { return gp_Vec(v.x, v.y, v.z); }

struct BodyFrame {
  double x0, y0, z0, dx, dy, dz, diag;
  explicit BodyFrame(const TopoDS_Shape& s) {
    const BoundingBox b = boundingBox(s);
    x0 = b.min.x, y0 = b.min.y, z0 = b.min.z;
    dx = b.max.x - b.min.x, dy = b.max.y - b.min.y, dz = b.max.z - b.min.z;
    diag = std::max(std::sqrt(dx * dx + dy * dy + dz * dz), 1e-6);
  }
  Vec3 rel(const gp_Pnt& p) const {
    auto r = [](double v, double o, double d) { return d > 1e-9 ? (v - o) / d : 0.5; };
    return {r(p.X(), x0, dx), r(p.Y(), y0, dy), r(p.Z(), z0, dz)};
  }
};

EdgeSig signature(const TopoDS_Shape& body, const TopoDS_Edge& edge, const TopTools_IndexedDataMapOfShapeListOfShape& faces,
                  const BodyFrame& frame) {
  EdgeSig s;
  s.full = true;
  BRepAdaptor_Curve c(edge);
  const double mid = (c.FirstParameter() + c.LastParameter()) / 2;
  gp_Pnt p;
  gp_Vec t;
  c.D1(mid, p, t);
  s.point = {p.X(), p.Y(), p.Z()};
  s.type = static_cast<int>(c.GetType());
  s.rel = frame.rel(p);
  if (t.Magnitude() > 1e-12) t.Normalize();
  s.tangent = {t.X(), t.Y(), t.Z()};
  if (const TopTools_ListOfShape* adj = faces.Seek(edge)) {
    for (const TopoDS_Shape& fs : *adj) {
      const TopoDS_Face& f = TopoDS::Face(fs);
      const Handle(Geom_Surface) surf = BRep_Tool::Surface(f);
      if (surf.IsNull()) continue;
      ShapeAnalysis_Surface sas(surf);
      const gp_Pnt2d uv = sas.ValueOfUV(p, 1e-7);
      BRepAdaptor_Surface bs(f, false);
      BRepLProp_SLProps props(bs, uv.X(), uv.Y(), 1, 1e-7);
      if (!props.IsNormalDefined()) continue;
      gp_Dir n = props.Normal();
      if (f.Orientation() == TopAbs_REVERSED) n.Reverse();
      bool dup = false;
      for (const auto& m : s.normals) dup = dup || std::abs(m.x - n.X()) + std::abs(m.y - n.Y()) + std::abs(m.z - n.Z()) < 1e-9;
      if (!dup && s.normals.size() < 2) s.normals.push_back({n.X(), n.Y(), n.Z()});
    }
  }
  (void)body;
  return s;
}

std::string fmt(double v) {
  char buf[32];
  std::snprintf(buf, sizeof buf, "%.9g", std::abs(v) < 1e-12 ? 0.0 : v);
  return buf;
}
std::string fmt(Vec3 v) { return fmt(v.x) + "," + fmt(v.y) + "," + fmt(v.z); }

std::string encode(const EdgeSig& s) {
  std::string out = fmt(s.point);
  if (!s.full) return out;
  out += "@" + std::to_string(s.type) + ":" + fmt(s.rel) + ":" + fmt(s.tangent);
  for (const auto& n : s.normals) out += ":" + fmt(n);
  return out;
}

Vec3 parseVec(const std::string& text) {
  double v[3] = {0, 0, 0};
  size_t pos = 0;
  for (int k = 0; k < 3; ++k) {
    const size_t end = k < 2 ? text.find(',', pos) : text.size();
    if (end == std::string::npos) throw KernelError("bad edge reference '" + text + "'");
    try {
      v[k] = std::stod(text.substr(pos, end - pos));
    } catch (const std::exception&) {
      throw KernelError("bad edge reference '" + text + "'");
    }
    pos = end + 1;
  }
  return {v[0], v[1], v[2]};
}

std::vector<EdgeSig> decode(const std::string& refs) {
  std::vector<EdgeSig> out;
  size_t start = 0;
  while (start < refs.size()) {
    size_t end = refs.find(';', start);
    if (end == std::string::npos) end = refs.size();
    const std::string item = refs.substr(start, end - start);
    start = end + 1;
    if (item.empty()) continue;
    EdgeSig s;
    const size_t at = item.find('@');
    s.point = parseVec(item.substr(0, at));
    if (at != std::string::npos) {
      std::vector<std::string> parts;
      size_t p = at + 1;
      while (p <= item.size()) {
        size_t q = item.find(':', p);
        if (q == std::string::npos) q = item.size();
        parts.push_back(item.substr(p, q - p));
        p = q + 1;
      }
      if (parts.size() < 3) throw KernelError("bad edge reference '" + item + "'");
      s.full = true;
      s.type = std::stoi(parts[0]);
      s.rel = parseVec(parts[1]);
      s.tangent = parseVec(parts[2]);
      for (size_t i = 3; i < parts.size(); ++i) s.normals.push_back(parseVec(parts[i]));
    }
    out.push_back(s);
  }
  return out;
}

double dot(Vec3 a, Vec3 b) { return a.x * b.x + a.y * b.y + a.z * b.z; }

// Lower is better.
double score(const EdgeSig& want, const EdgeSig& have, double diag) {
  const double absDist = (vec(want.point) - vec(have.point)).Magnitude() / diag;
  if (!want.full) return absDist;
  double s = 0;
  if (want.type != have.type) s += 10;
  s += 5 * (1 - std::abs(dot(want.tangent, have.tangent)));
  if (!want.normals.empty()) {
    double best = 1e9;
    // Match face normals as an unordered set.
    auto cost = [&](const std::vector<Vec3>& a, const std::vector<Vec3>& b) {
      double c = 0;
      for (size_t i = 0; i < a.size(); ++i) c += i < b.size() ? 1 - dot(a[i], b[i]) : 2;
      return c;
    };
    best = cost(want.normals, have.normals);
    if (have.normals.size() == 2) best = std::min(best, cost(want.normals, {have.normals[1], have.normals[0]}));
    s += 3 * best;
  }
  s += 4 * (vec(want.rel) - vec(have.rel)).Magnitude();
  s += absDist;
  return s;
}
} // namespace

std::string edgeReference(const TopoDS_Shape& body, const TopoDS_Shape& edge) {
  TopTools_IndexedDataMapOfShapeListOfShape faces;
  TopExp::MapShapesAndAncestors(body, TopAbs_EDGE, TopAbs_FACE, faces);
  return encode(signature(body, TopoDS::Edge(edge), faces, BodyFrame(body)));
}

std::string completeEdgeReferences(const TopoDS_Shape& body, const std::string& refs) {
  const auto sigs = decode(refs);
  std::string out;
  const BodyFrame frame(body);
  for (const auto& s : sigs) {
    std::string item = encode(s);
    if (!s.full) {
      // The same rule as resolving a plain point (one rule everywhere: a
      // point on a vertex prefers the edge it lies inside of, not a seam).
      const auto e = resolveEdges(body, encode(s));
      item = edgeReference(body, e.front());
      // Keep the picked point (the signature midpoint may differ).
      item = encode(s) + item.substr(item.find('@'));
    }
    out += (out.empty() ? "" : ";") + item;
  }
  return out;
}

std::vector<TopoDS_Shape> resolveEdges(const TopoDS_Shape& body, const std::string& refs) {
  const auto wants = decode(refs);
  if (wants.empty()) throw KernelError("select at least one edge");
  TopTools_IndexedMapOfShape edges;
  TopExp::MapShapes(body, TopAbs_EDGE, edges);
  TopTools_IndexedDataMapOfShapeListOfShape faces;
  TopExp::MapShapesAndAncestors(body, TopAbs_EDGE, TopAbs_FACE, faces);
  const BodyFrame frame(body);
  std::vector<EdgeSig> have;
  for (int i = 1; i <= edges.Extent(); ++i) {
    const TopoDS_Edge& e = TopoDS::Edge(edges(i));
    if (BRep_Tool::Degenerated(e)) {
      have.push_back({});
      have.back().point = {1e30, 1e30, 1e30};
      continue;
    }
    have.push_back(signature(body, e, faces, frame));
  }
  std::vector<TopoDS_Shape> out;
  for (const auto& w : wants) {
    int best = -1;
    double bestScore = 1e300;
    for (int i = 0; i < static_cast<int>(have.size()); ++i) {
      double sc;
      if (!w.full) {
        // Plain point: true distance to the edge.
        const TopoDS_Shape v = BRepBuilderAPI_MakeVertex(pnt(w.point)).Shape();
        BRepExtrema_DistShapeShape d(v, edges(i + 1));
        sc = d.IsDone() ? d.Value() / frame.diag : 1e300;
        // A point at an edge's end vertex also touches the edges meeting
        // there (on a cylinder: the seam). Prefer an edge the point lies
        // inside of, then a non-seam edge.
        if (d.IsDone() && d.NbSolution() > 0 && d.SupportTypeShape2(1) == BRepExtrema_IsVertex) sc += 1e-7;
        if (const int fi = faces.FindIndex(edges(i + 1)); fi > 0)
          for (const auto& f : faces(fi))
            if (BRep_Tool::IsClosed(TopoDS::Edge(edges(i + 1)), TopoDS::Face(f))) {
              sc += 1e-7;
              break;
            }
      } else {
        sc = score(w, have[i], frame.diag);
      }
      if (sc < bestScore) {
        bestScore = sc;
        best = i;
      }
    }
    const double limit = w.full ? 3.0 : 0.2;
    if (best < 0 || bestScore > limit) throw KernelError("a selected edge no longer exists (the body changed too much)");
    bool dup = false;
    for (const auto& e : out) dup = dup || e.IsSame(edges(best + 1));
    if (!dup) out.push_back(edges(best + 1));
  }
  return out;
}

// ---------------------------------------------------------------------------
// Face references

namespace {
struct FaceSig {
  Vec3 point;
  bool full = false;
  int type = 0;
  Vec3 rel, normal;
  double area = 0;
};

// A point inside the face: the UV centre if it lies on the face, else the
// centroid of its largest mesh triangle.
gp_Pnt pointOnFace(const TopoDS_Face& f) {
  BRepAdaptor_Surface s(f);
  const double u = (s.FirstUParameter() + s.LastUParameter()) / 2;
  const double v = (s.FirstVParameter() + s.LastVParameter()) / 2;
  BRepClass_FaceClassifier cls(f, gp_Pnt2d(u, v), 1e-7);
  if (cls.State() == TopAbs_IN) return s.Value(u, v);
  BRepMesh_IncrementalMesh mesh(f, 0.05, false, 0.5, false);
  TopLoc_Location loc;
  const Handle(Poly_Triangulation) tri = BRep_Tool::Triangulation(f, loc);
  if (tri.IsNull() || tri->NbTriangles() == 0) return s.Value(u, v);
  double best = -1;
  gp_Pnt bestP = s.Value(u, v);
  for (int i = 1; i <= tri->NbTriangles(); ++i) {
    int n1, n2, n3;
    tri->Triangle(i).Get(n1, n2, n3);
    const gp_Pnt a = tri->Node(n1).Transformed(loc), b = tri->Node(n2).Transformed(loc),
                 c = tri->Node(n3).Transformed(loc);
    const double ar = gp_Vec(a, b).Crossed(gp_Vec(a, c)).Magnitude();
    if (ar > best) {
      best = ar;
      bestP = gp_Pnt((a.XYZ() + b.XYZ() + c.XYZ()) / 3);
    }
  }
  return bestP;
}

gp_Dir faceNormalAt(const TopoDS_Face& f, const gp_Pnt& p) {
  const Handle(Geom_Surface) surf = BRep_Tool::Surface(f);
  ShapeAnalysis_Surface sas(surf);
  const gp_Pnt2d uv = sas.ValueOfUV(p, 1e-7);
  BRepAdaptor_Surface bs(f, false);
  BRepLProp_SLProps props(bs, uv.X(), uv.Y(), 1, 1e-7);
  gp_Dir n = props.IsNormalDefined() ? props.Normal() : gp_Dir(0, 0, 1);
  if (f.Orientation() == TopAbs_REVERSED) n.Reverse();
  return n;
}

FaceSig faceSignature(const TopoDS_Face& f, const BodyFrame& frame) {
  FaceSig s;
  s.full = true;
  const gp_Pnt p = pointOnFace(f);
  s.point = {p.X(), p.Y(), p.Z()};
  s.type = static_cast<int>(BRepAdaptor_Surface(f).GetType());
  s.rel = frame.rel(p);
  const gp_Dir n = faceNormalAt(f, p);
  s.normal = {n.X(), n.Y(), n.Z()};
  GProp_GProps g;
  BRepGProp::SurfaceProperties(f, g);
  s.area = g.Mass();
  return s;
}

std::string encodeFace(const FaceSig& s) {
  std::string out = fmt(s.point);
  if (s.full) out += "@" + std::to_string(s.type) + ":" + fmt(s.rel) + ":" + fmt(s.normal) + ":" + fmt(s.area);
  return out;
}

std::vector<FaceSig> decodeFaces(const std::string& refs) {
  std::vector<FaceSig> out;
  size_t start = 0;
  while (start < refs.size()) {
    size_t end = refs.find(';', start);
    if (end == std::string::npos) end = refs.size();
    const std::string item = refs.substr(start, end - start);
    start = end + 1;
    if (item.empty()) continue;
    FaceSig s;
    const size_t at = item.find('@');
    s.point = parseVec(item.substr(0, at));
    if (at != std::string::npos) {
      std::vector<std::string> parts;
      size_t p = at + 1;
      while (p <= item.size()) {
        size_t q = item.find(':', p);
        if (q == std::string::npos) q = item.size();
        parts.push_back(item.substr(p, q - p));
        p = q + 1;
      }
      if (parts.size() != 4) throw KernelError("bad face reference '" + item + "'");
      s.full = true;
      s.type = std::stoi(parts[0]);
      s.rel = parseVec(parts[1]);
      s.normal = parseVec(parts[2]);
      s.area = std::stod(parts[3]);
    }
    out.push_back(s);
  }
  return out;
}

double faceScore(const FaceSig& want, const FaceSig& have, double diag) {
  const double absDist = (vec(want.point) - vec(have.point)).Magnitude() / diag;
  if (!want.full) return absDist;
  double s = 0;
  if (want.type != have.type) s += 10;
  s += 5 * (1 - dot(want.normal, have.normal));
  s += 4 * (vec(want.rel) - vec(have.rel)).Magnitude();
  if (want.area > 0 && have.area > 0) s += 0.5 * std::abs(std::log(have.area / want.area));
  s += absDist;
  return s;
}

TopoDS_Shape nearestFace(const TopoDS_Shape& body, const gp_Pnt& p, double tol) {
  const TopoDS_Shape v = BRepBuilderAPI_MakeVertex(p).Shape();
  TopoDS_Shape best;
  double bestD = tol;
  for (TopExp_Explorer it(body, TopAbs_FACE); it.More(); it.Next()) {
    BRepExtrema_DistShapeShape d(v, it.Current());
    if (d.IsDone() && d.Value() < bestD) {
      bestD = d.Value();
      best = it.Current();
    }
  }
  return best;
}
} // namespace

std::string faceReference(const TopoDS_Shape& body, const TopoDS_Shape& face) {
  return encodeFace(faceSignature(TopoDS::Face(face), BodyFrame(body)));
}

std::string completeFaceReferences(const TopoDS_Shape& body, const std::string& refs) {
  const BodyFrame frame(body);
  std::string out;
  for (const auto& s : decodeFaces(refs)) {
    std::string item = encodeFace(s);
    if (!s.full) {
      const TopoDS_Shape f = nearestFace(body, pnt(s.point), std::max(0.05, 0.2 * frame.diag));
      if (f.IsNull()) throw KernelError("no face near the given point");
      FaceSig full = faceSignature(TopoDS::Face(f), frame);
      full.point = s.point;
      item = encodeFace(full);
    }
    out += (out.empty() ? "" : ";") + item;
  }
  return out;
}

std::vector<TopoDS_Shape> resolveFaces(const TopoDS_Shape& body, const std::string& refs) {
  const auto wants = decodeFaces(refs);
  const BodyFrame frame(body);
  std::vector<TopoDS_Shape> faces;
  std::vector<FaceSig> have;
  for (TopExp_Explorer it(body, TopAbs_FACE); it.More(); it.Next()) {
    faces.push_back(it.Current());
    have.push_back(faceSignature(TopoDS::Face(it.Current()), frame));
  }
  std::vector<TopoDS_Shape> out;
  for (const auto& w : wants) {
    int best = -1;
    double bestScore = 1e300;
    for (int i = 0; i < static_cast<int>(faces.size()); ++i) {
      double sc;
      if (!w.full) {
        const TopoDS_Shape v = BRepBuilderAPI_MakeVertex(pnt(w.point)).Shape();
        BRepExtrema_DistShapeShape d(v, faces[i]);
        sc = d.IsDone() ? d.Value() / frame.diag : 1e300;
      } else {
        sc = faceScore(w, have[i], frame.diag);
      }
      if (sc < bestScore) {
        bestScore = sc;
        best = i;
      }
    }
    if (best < 0 || bestScore > (w.full ? 3.0 : 0.2))
      throw KernelError("a selected face no longer exists (the body changed too much)");
    bool dup = false;
    for (const auto& f : out) dup = dup || f.IsSame(faces[best]);
    if (!dup) out.push_back(faces[best]);
  }
  return out;
}

// ---------------------------------------------------------------------------
// Shell, split

namespace {
TopoDS_Shape asSolid(const TopoDS_Shape& s) {
  if (s.ShapeType() == TopAbs_SOLID) return s;
  TopExp_Explorer solid(s, TopAbs_SOLID);
  if (solid.More()) return solid.Current();
  TopExp_Explorer shellIt(s, TopAbs_SHELL);
  if (shellIt.More()) return BRepBuilderAPI_MakeSolid(TopoDS::Shell(shellIt.Current())).Solid();
  return {};
}
} // namespace

TopoDS_Shape shell(const TopoDS_Shape& body, const std::vector<TopoDS_Shape>& openFaces, double thickness, bool outside) {
  requirePositive(thickness, "shell thickness");
  // Walls meet with sharp corners, as in the familiar tool: the offset faces
  // are extended until they intersect (GeomAbs_Intersection). Rounded joins
  // (GeomAbs_Arc) are the fallback for shapes where that cannot be solved.
  auto attempt = [&](GeomAbs_JoinType join) -> TopoDS_Shape {
    TopoDS_Shape out;
    try {
      if (!openFaces.empty()) {
        TopTools_ListOfShape faces;
        for (const auto& f : openFaces) faces.Append(f);
        BRepOffsetAPI_MakeThickSolid mk;
        mk.MakeThickSolidByJoin(body, faces, outside ? thickness : -thickness, 1e-4, BRepOffset_Skin, join == GeomAbs_Intersection,
                                false, join);
        if (mk.IsDone()) out = mk.Shape();
      } else {
        // Closed hollow: offset the whole body and subtract.
        BRepOffsetAPI_MakeOffsetShape off;
        off.PerformByJoin(body, outside ? thickness : -thickness, 1e-4, BRepOffset_Skin, join == GeomAbs_Intersection, false,
                          join);
        if (off.IsDone()) {
          const TopoDS_Shape other = asSolid(off.Shape());
          if (!other.IsNull()) out = outside ? boolean(BooleanOp::Cut, other, body) : boolean(BooleanOp::Cut, body, other);
        }
      }
    } catch (const Standard_Failure&) {
      out.Nullify();
    } catch (const KernelError&) {
      out.Nullify();
    }
    if (!out.IsNull() && !isValid(out)) out.Nullify();
    return out;
  };
  TopoDS_Shape r = attempt(GeomAbs_Intersection);
  if (r.IsNull()) r = attempt(GeomAbs_Arc);
  if (r.IsNull() || !isValid(r))
    throw KernelError("Shell: could not hollow the body with that thickness (try a smaller thickness)");
  return r;
}

std::vector<TopoDS_Shape> splitByPlane(const TopoDS_Shape& body, Vec3 origin, Vec3 normal) {
  const BoundingBox bb = boundingBox(body);
  const double diag = std::sqrt(std::pow(bb.max.x - bb.min.x, 2) + std::pow(bb.max.y - bb.min.y, 2) +
                                std::pow(bb.max.z - bb.min.z, 2));
  const double half = std::max(1.0, diag) * 2;
  const gp_Dir n(normal.x, normal.y, normal.z);
  // Centre the cutting face where the body is.
  const gp_Pnt c((bb.min.x + bb.max.x) / 2, (bb.min.y + bb.max.y) / 2, (bb.min.z + bb.max.z) / 2);
  const gp_Pnt o = pnt(origin);
  const gp_Pnt onPlane = c.Translated(-gp_Vec(n) * gp_Vec(o, c).Dot(gp_Vec(n)));
  const gp_Pln pln(onPlane, n);
  std::vector<TopoDS_Shape> out;
  try {
    const TopoDS_Face tool = BRepBuilderAPI_MakeFace(pln, -half, half, -half, half).Face();
    BRepAlgoAPI_Splitter split;
    TopTools_ListOfShape args, tools;
    args.Append(body);
    tools.Append(tool);
    split.SetArguments(args);
    split.SetTools(tools);
    split.Build();
    if (!split.IsDone() || split.HasErrors()) throw KernelError("Split: the operation failed");
    for (TopExp_Explorer it(split.Shape(), TopAbs_SOLID); it.More(); it.Next()) out.push_back(it.Current());
  } catch (const Standard_Failure& f) {
    throw KernelError(std::string("Split: ") + f.GetMessageString());
  }
  if (out.size() < 2) throw KernelError("Split: the plane does not cross the body");
  return out;
}

// ---------------------------------------------------------------------------
// Transforms

TopoDS_Shape moved(const TopoDS_Shape& s, Vec3 offset, Vec3 pivot, Vec3 axisDir, double angle) {
  gp_Trsf rot, tr;
  if (std::abs(angle) > 1e-12) rot.SetRotation(gp_Ax1(pnt(pivot), gp_Dir(axisDir.x, axisDir.y, axisDir.z)), angle);
  tr.SetTranslation(gp_Vec(offset.x, offset.y, offset.z));
  return guarded("Move", [&] { return BRepBuilderAPI_Transform(s, tr * rot, true).Shape(); });
}

TopoDS_Shape mirrored(const TopoDS_Shape& s, Vec3 origin, Vec3 normal) {
  gp_Trsf t;
  t.SetMirror(gp_Ax2(pnt(origin), gp_Dir(normal.x, normal.y, normal.z)));
  return guarded("Mirror", [&] { return BRepBuilderAPI_Transform(s, t, true).Shape(); });
}

TopoDS_Shape scaled(const TopoDS_Shape& s, double factor, Vec3 center) {
  requirePositive(factor, "scale factor");
  gp_Trsf t;
  t.SetScale(pnt(center), factor);
  return guarded("Scale", [&] { return BRepBuilderAPI_Transform(s, t, true).Shape(); });
}

// ---------------------------------------------------------------------------
// Measure

Measurement measure(const std::vector<TopoDS_Shape>& picks) {
  using K = Measurement::Kind;
  Measurement m;
  auto add = [&](const std::string& name, double v, K k) { m.values.push_back({name, v, k}); };
  auto describe = [&](const TopoDS_Shape& s, const std::string& prefix) {
    switch (s.ShapeType()) {
      case TopAbs_VERTEX: {
        const gp_Pnt p = BRep_Tool::Pnt(TopoDS::Vertex(s));
        add(prefix + "X", p.X(), K::Length);
        add(prefix + "Y", p.Y(), K::Length);
        add(prefix + "Z", p.Z(), K::Length);
        break;
      }
      case TopAbs_EDGE: {
        GProp_GProps g;
        BRepGProp::LinearProperties(s, g);
        add(prefix + "Length", g.Mass(), K::Length);
        BRepAdaptor_Curve c(TopoDS::Edge(s));
        if (c.GetType() == GeomAbs_Circle) add(prefix + "Radius", c.Circle().Radius(), K::Length);
        break;
      }
      case TopAbs_FACE: {
        GProp_GProps g;
        BRepGProp::SurfaceProperties(s, g);
        add(prefix + "Area", g.Mass(), K::Area);
        BRepAdaptor_Surface a(TopoDS::Face(s));
        if (a.GetType() == GeomAbs_Cylinder) add(prefix + "Radius", a.Cylinder().Radius(), K::Length);
        if (a.GetType() == GeomAbs_Sphere) add(prefix + "Radius", a.Sphere().Radius(), K::Length);
        break;
      }
      default: {
        const MassProperties mp = massProperties(s);
        add(prefix + "Volume", mp.volume, K::Volume);
        add(prefix + "Area", mp.area, K::Area);
        break;
      }
    }
  };
  if (picks.empty()) return m;
  if (picks.size() == 1) {
    describe(picks[0], "");
    return m;
  }
  const TopoDS_Shape& a = picks[0];
  const TopoDS_Shape& b = picks[1];
  BRepExtrema_DistShapeShape d(a, b);
  if (d.IsDone() && d.NbSolution() > 0) {
    const gp_Pnt p = d.PointOnShape1(1), q = d.PointOnShape2(1);
    add("Distance", d.Value(), K::Length);
    add("dX", std::abs(q.X() - p.X()), K::Length);
    add("dY", std::abs(q.Y() - p.Y()), K::Length);
    add("dZ", std::abs(q.Z() - p.Z()), K::Length);
    m.hasLine = d.Value() > 1e-9;
    m.from = {p.X(), p.Y(), p.Z()};
    m.to = {q.X(), q.Y(), q.Z()};
  }
  // Angle between two flat faces or two straight edges.
  auto direction = [](const TopoDS_Shape& s, gp_Dir& out) {
    if (s.ShapeType() == TopAbs_FACE) {
      BRepAdaptor_Surface a(TopoDS::Face(s));
      if (a.GetType() != GeomAbs_Plane) return false;
      out = a.Plane().Axis().Direction();
      if (s.Orientation() == TopAbs_REVERSED) out.Reverse();
      return true;
    }
    if (s.ShapeType() == TopAbs_EDGE) {
      BRepAdaptor_Curve c(TopoDS::Edge(s));
      if (c.GetType() != GeomAbs_Line) return false;
      out = c.Line().Direction();
      return true;
    }
    return false;
  };
  gp_Dir da, db;
  if (direction(a, da) && direction(b, db) && a.ShapeType() == b.ShapeType()) {
    double ang = da.Angle(db);
    if (a.ShapeType() == TopAbs_EDGE && ang > M_PI / 2) ang = M_PI - ang;
    add("Angle", ang, K::Angle);
  }
  return m;
}

TopoDS_Shape fillet(const TopoDS_Shape& shape, const std::vector<TopoDS_Shape>& edges, double radius) {
  requirePositive(radius, "fillet radius");
  if (edges.empty()) throw KernelError("Fillet: select at least one edge");
  TopoDS_Shape r;
  try {
    r = guarded("Fillet", [&]() -> TopoDS_Shape {
    BRepFilletAPI_MakeFillet mk(shape);
    for (const auto& e : edges) mk.Add(radius, TopoDS::Edge(e));
    mk.Build();
    return mk.IsDone() ? mk.Shape() : TopoDS_Shape();
    });
  } catch (const KernelError& e) {
    throw KernelError(std::string("Fillet: the radius is too large for the selected edges, or they cannot be rounded (") + e.what() + ")");
  }
  if (!isValid(r)) throw KernelError("Fillet: the radius is too large for the selected edges");
  return r;
}

TopoDS_Shape chamfer(const TopoDS_Shape& shape, const std::vector<TopoDS_Shape>& edges, double distance) {
  requirePositive(distance, "chamfer distance");
  if (edges.empty()) throw KernelError("Chamfer: select at least one edge");
  TopoDS_Shape r;
  try {
    r = guarded("Chamfer", [&]() -> TopoDS_Shape {
    BRepFilletAPI_MakeChamfer mk(shape);
    for (const auto& e : edges) mk.Add(distance, TopoDS::Edge(e));
    mk.Build();
    return mk.IsDone() ? mk.Shape() : TopoDS_Shape();
    });
  } catch (const KernelError& e) {
    throw KernelError(std::string("Chamfer: the distance is too large for the selected edges, or they cannot be bevelled (") + e.what() + ")");
  }
  if (!isValid(r)) throw KernelError("Chamfer: the distance is too large for the selected edges");
  return r;
}

TopoDS_Shape chamferEx(const TopoDS_Shape& shape, const std::vector<TopoDS_Shape>& edges, ChamferType type,
                       double first, double second, bool flip) {
  requirePositive(first, "chamfer distance");
  if (type == ChamferType::TwoDistances) requirePositive(second, "second chamfer distance");
  if (type == ChamferType::DistanceAngle && !(second > 1e-9 && second < M_PI / 2 - 1e-9))
    throw KernelError("Chamfer: the angle must be between 0 and 90 degrees");
  if (edges.empty()) throw KernelError("Chamfer: select at least one edge");
  TopTools_IndexedDataMapOfShapeListOfShape faces;
  TopExp::MapShapesAndAncestors(shape, TopAbs_EDGE, TopAbs_FACE, faces);
  TopoDS_Shape r;
  try {
    r = guarded("Chamfer", [&]() -> TopoDS_Shape {
      BRepFilletAPI_MakeChamfer mk(shape);
      for (const auto& e : edges) {
        const int i = faces.FindIndex(e);
        if (i == 0 || faces(i).Extent() < 2) throw KernelError("Chamfer: an edge is not between two faces");
        const TopoDS_Face f = TopoDS::Face(flip ? faces(i).Last() : faces(i).First());
        if (type == ChamferType::TwoDistances) mk.Add(first, second, TopoDS::Edge(e), f);
        else mk.AddDA(first, second, TopoDS::Edge(e), f);
      }
      mk.Build();
      return mk.IsDone() ? mk.Shape() : TopoDS_Shape();
    });
  } catch (const KernelError& e) {
    throw KernelError(std::string("Chamfer: the size is too large for the selected edges, or they cannot be bevelled (") +
                      e.what() + ")");
  }
  if (!isValid(r)) throw KernelError("Chamfer: the size is too large for the selected edges");
  return r;
}

namespace {
// One loop (a face without holes) offset by d (outward if positive),
// mitred; null if it vanishes.
TopoDS_Shape offsetLoop(const TopoDS_Face& face, double d) {
  if (std::abs(d) < 1e-12) return face;
  // A loop of one closed edge: OCCT's offset crashes on it. A circle is
  // offset exactly; any other closed curve is split in two first.
  TopoDS_Face work = face;
  {
    std::vector<TopoDS_Edge> edges;
    for (TopExp_Explorer e(BRepTools::OuterWire(face), TopAbs_EDGE); e.More(); e.Next()) edges.push_back(TopoDS::Edge(e.Current()));
    if (edges.size() == 1) {
      BRepAdaptor_Curve c(edges.front());
      const gp_Pln pln = BRepAdaptor_Surface(face).Plane();
      if (c.GetType() == GeomAbs_Circle) {
        gp_Circ circ = c.Circle();
        const double r = circ.Radius() + d;
        if (r <= 1e-9) return {};
        circ.SetRadius(r);
        return BRepBuilderAPI_MakeFace(pln, BRepBuilderAPI_MakeWire(BRepBuilderAPI_MakeEdge(circ).Edge()).Wire(), true).Face();
      }
      double a0 = 0, a1 = 0;
      const Handle(Geom_Curve) g = BRep_Tool::Curve(edges.front(), a0, a1);
      if (g.IsNull()) return {};
      const double tm = (a0 + a1) / 2;
      BRepBuilderAPI_MakeWire mw;
      mw.Add(BRepBuilderAPI_MakeEdge(g, a0, tm).Edge());
      mw.Add(BRepBuilderAPI_MakeEdge(g, tm, a1).Edge());
      if (!mw.IsDone()) return {};
      work = BRepBuilderAPI_MakeFace(pln, mw.Wire(), true).Face();
    }
  }
  BRepOffsetAPI_MakeOffset off(work, GeomAbs_Intersection);
  off.Perform(d);
  if (!off.IsDone() || off.Shape().IsNull()) return {};
  // Each loop as a filled face; a loop inside an odd number of others is a
  // hole (loops from one offset never cross).
  const gp_Pln pln = BRepAdaptor_Surface(face).Plane();
  std::vector<TopoDS_Face> loops;
  std::vector<gp_Pnt> onLoop;
  for (TopExp_Explorer w(off.Shape(), TopAbs_WIRE); w.More(); w.Next()) {
    const TopoDS_Wire wire = TopoDS::Wire(w.Current());
    BRepBuilderAPI_MakeFace mf(pln, wire, true);
    if (!mf.IsDone()) continue;
    TopoDS_Face f = mf.Face();
    BRepLib::BuildCurves3d(f);
    GProp_GProps g;
    BRepGProp::SurfaceProperties(f, g);
    if (std::abs(g.Mass()) < 1e-12) continue;
    if (g.Mass() < 0) f.Reverse();
    TopExp_Explorer v(wire, TopAbs_VERTEX);
    if (!v.More()) {   // a single closed curve (circle): a point on it
      BRepAdaptor_Curve c(TopoDS::Edge(TopExp_Explorer(wire, TopAbs_EDGE).Current()));
      onLoop.push_back(c.Value(c.FirstParameter()));
    } else {
      onLoop.push_back(BRep_Tool::Pnt(TopoDS::Vertex(v.Current())));
    }
    loops.push_back(f);
  }
  TopoDS_Shape region;
  std::vector<TopoDS_Shape> holes;
  for (size_t i = 0; i < loops.size(); ++i) {
    int inside = 0;
    for (size_t k = 0; k < loops.size(); ++k)
      if (k != i && BRepClass_FaceClassifier(loops[k], onLoop[i], 1e-7).State() == TopAbs_IN) ++inside;
    if (inside % 2 == 1) holes.push_back(loops[i]);
    else region = region.IsNull() ? TopoDS_Shape(loops[i]) : BRepAlgoAPI_Fuse(region, loops[i]).Shape();
  }
  for (const auto& h : holes)
    if (!region.IsNull()) region = BRepAlgoAPI_Cut(region, h).Shape();
  return region;
}

// A region offset by d: its outer loop grows by d and each hole, taken as a
// filled loop, shrinks by d. (OCCT's offset of a face with holes is not
// reliable, so loops are offset one at a time.)
TopoDS_Shape offsetRegion(const TopoDS_Face& face, double d) {
  if (std::abs(d) < 1e-12) return face;
  const gp_Pln pln = BRepAdaptor_Surface(face).Plane();
  const TopoDS_Wire outerWire = BRepTools::OuterWire(face);
  BRepBuilderAPI_MakeFace of(pln, outerWire, true);
  if (!of.IsDone()) return {};
  TopoDS_Shape region = offsetLoop(of.Face(), d);
  if (region.IsNull()) return {};
  for (TopExp_Explorer w(face, TopAbs_WIRE); w.More(); w.Next()) {
    if (w.Current().IsSame(outerWire)) continue;
    BRepBuilderAPI_MakeFace hf(pln, TopoDS::Wire(w.Current()), true);
    if (!hf.IsDone()) continue;
    TopoDS_Face holeFace = hf.Face();
    GProp_GProps g;
    BRepGProp::SurfaceProperties(holeFace, g);
    if (g.Mass() < 0) holeFace.Reverse();
    const TopoDS_Shape hole = offsetLoop(holeFace, -d);   // null: the hole closed up
    if (!hole.IsNull() && TopExp_Explorer(hole, TopAbs_FACE).More()) region = BRepAlgoAPI_Cut(region, hole).Shape();
  }
  return region;
}
} // namespace

std::vector<TopoDS_Shape> wallBand(const TopoDS_Shape& faceShape, WallSide side, double thickness) {
  requirePositive(thickness, "wall thickness");
  if (faceShape.IsNull() || faceShape.ShapeType() != TopAbs_FACE) throw KernelError("Thin Extrude: needs a flat profile");
  const TopoDS_Face face = TopoDS::Face(faceShape);
  if (BRepAdaptor_Surface(face).GetType() != GeomAbs_Plane) throw KernelError("Thin Extrude: needs a flat profile");
  const double outer = side == WallSide::Side1 ? 0 : side == WallSide::Center ? thickness / 2 : thickness;
  const double inner = side == WallSide::Side2 ? 0 : side == WallSide::Center ? thickness / 2 : thickness;
  TopoDS_Shape band = guarded("Thin Extrude", [&]() -> TopoDS_Shape {
    const TopoDS_Shape big = offsetRegion(face, outer);
    if (big.IsNull()) return {};
    const TopoDS_Shape small = offsetRegion(face, -inner);   // null: the wall fills the region
    if (small.IsNull() || !TopExp_Explorer(small, TopAbs_FACE).More()) return big;
    return BRepAlgoAPI_Cut(big, small).Shape();
  });
  std::vector<TopoDS_Shape> out;
  for (TopExp_Explorer f(band, TopAbs_FACE); f.More(); f.Next()) out.push_back(f.Current());
  if (out.empty()) throw KernelError("Thin Extrude: the wall thickness does not fit this profile");
  return out;
}

TopoDS_Shape extrudeEx(const std::vector<TopoDS_Shape>& faces, Vec3 dir, double forward, double back, double taper,
                       double startOffset) {
  if (faces.empty()) throw KernelError("nothing to extrude: no profile selected");
  if (!(std::abs(forward + back) > 1e-9)) throw KernelError("extrude distance must not be zero");
  if (back > 0 && forward + back <= 1e-9) throw KernelError("Extrude: the two sides overlap (side 1 goes past side 2)");
  const gp_Vec n = gp_Vec(dir.x, dir.y, dir.z).Normalized();
  TopoDS_Shape result;
  for (const TopoDS_Shape& f : faces) {
    TopoDS_Shape solid = guarded("Extrude", [&]() -> TopoDS_Shape {
      gp_Trsf t;
      t.SetTranslation(n * (startOffset - back));
      const TopoDS_Shape base = BRepBuilderAPI_Transform(f, t, true).Shape();
      const double length = forward + back;
      if (std::abs(taper) > 1e-9) {
        if (back != 0) throw KernelError("taper works with one-sided extrudes only");
        // LocOpe_DPrism sweeps along the face normal; flip for negative lengths.
        TopoDS_Face face = TopoDS::Face(base);
        gp_Dir fn = BRepAdaptor_Surface(face).Plane().Axis().Direction();
        if (face.Orientation() == TopAbs_REVERSED) fn.Reverse();
        const bool along = gp_Vec(fn).Dot(n * length) > 0;
        // A profile without holes: the outline offset by length * tan(taper)
        // (sharp corners) at the far end, joined by flat or ruled sides. This
        // gives the exact frustum the familiar tool makes.
        int wires = 0;
        for (TopExp_Explorer w(face, TopAbs_WIRE); w.More(); w.Next()) ++wires;
        if (wires == 1) {
          const TopoDS_Wire outer = BRepTools::OuterWire(face);
          const TopoDS_Shape grown = offsetLoop(face, std::abs(length) * std::tan(taper));
          if (!grown.IsNull() && TopExp_Explorer(grown, TopAbs_FACE).More()) {
            TopoDS_Wire top = BRepTools::OuterWire(TopoDS::Face(TopExp_Explorer(grown, TopAbs_FACE).Current()));
            if (!top.IsNull()) {
              gp_Trsf up;
              up.SetTranslation(n * length);
              top = TopoDS::Wire(BRepBuilderAPI_Transform(top, up, true).Shape());
              BRepOffsetAPI_ThruSections loft(true, true);
              loft.AddWire(outer);
              loft.AddWire(top);
              loft.CheckCompatibility(false);
              loft.Build();
              if (loft.IsDone() && isValid(loft.Shape())) return loft.Shape();
            }
          }
        }
        // Its height runs along the slanted side: divide by cos so the
        // extrude is `length` tall, measured along the profile normal.
        LocOpe_DPrism dp(face, std::abs(length) / std::cos(taper), -taper);
        TopoDS_Shape s = dp.Shape();
        if (!along) {
          gp_Trsf m;
          m.SetMirror(gp_Ax2(BRepAdaptor_Surface(face).Plane().Location(), fn));
          s = BRepBuilderAPI_Transform(s, m, true).Shape();
        }
        return s;
      }
      BRepPrimAPI_MakePrism mk(base, n * length);
      return mk.IsDone() ? mk.Shape() : TopoDS_Shape();
    });
    if (!isValid(solid))
      throw KernelError(std::abs(taper) > 1e-9 ? "Extrude: the taper angle is too steep for this profile and distance"
                                               : "Extrude: could not build a solid from this profile");
    result = result.IsNull() ? solid : boolean(BooleanOp::Join, result, solid);
  }
  return result;
}

namespace {
// One closed wire swept along the path into a solid (rounded at sharp corners).
TopoDS_Shape sweepWire(const TopoDS_Wire& path, const TopoDS_Wire& profile) {
  BRepOffsetAPI_MakePipeShell pipe(path);
  pipe.SetMode(false);   // corrected Frenet
  pipe.SetTransitionMode(BRepBuilderAPI_RoundCorner);
  pipe.Add(profile, false, false);
  pipe.Build();
  if (!pipe.IsDone() || !pipe.MakeSolid()) return {};
  return pipe.Shape();
}
} // namespace

TopoDS_Shape sweep(const std::vector<TopoDS_Shape>& faces, const std::vector<TopoDS_Shape>& pathEdges) {
  if (faces.empty()) throw KernelError("Sweep: no profile selected");
  if (pathEdges.empty()) throw KernelError("Sweep: the path has no curves");
  Handle(TopTools_HSequenceOfShape) edges = new TopTools_HSequenceOfShape;
  for (const auto& e : pathEdges) edges->Append(e);
  Handle(TopTools_HSequenceOfShape) wires;
  ShapeAnalysis_FreeBounds::ConnectEdgesToWires(edges, 1e-6, false, wires);
  if (wires.IsNull() || wires->Length() != 1) throw KernelError("Sweep: the path must be one connected chain of curves");
  TopoDS_Wire path = TopoDS::Wire(wires->Value(1));
  // Start the path at the end nearest the first profile.
  {
    TopoDS_Vertex v1, v2;
    TopExp::Vertices(path, v1, v2);
    if (!v1.IsNull() && !v2.IsNull()) {
      GProp_GProps g;
      BRepGProp::SurfaceProperties(faces.front(), g);
      const gp_Pnt c = g.CentreOfMass();
      if (c.Distance(BRep_Tool::Pnt(v2)) < c.Distance(BRep_Tool::Pnt(v1))) path = TopoDS::Wire(path.Reversed());
    }
  }
  TopoDS_Shape result;
  for (const auto& fs : faces) {
    const TopoDS_Face& f = TopoDS::Face(fs);
    TopoDS_Shape s = guarded("Sweep", [&]() -> TopoDS_Shape {
      const TopoDS_Wire outer = BRepTools::OuterWire(f);
      TopoDS_Shape solid = sweepWire(path, outer);
      if (solid.IsNull()) return solid;
      // Holes in the profile are swept too and taken away.
      for (TopExp_Explorer w(f, TopAbs_WIRE); w.More(); w.Next()) {
        const TopoDS_Wire inner = TopoDS::Wire(w.Current());
        if (inner.IsSame(outer)) continue;
        const TopoDS_Shape hole = sweepWire(path, inner);
        if (!hole.IsNull()) solid = boolean(BooleanOp::Cut, solid, hole);
      }
      return solid;
    });
    if (!isValid(s)) throw KernelError("Sweep: the result is not a valid solid (is the profile at the start of the path?)");
    result = result.IsNull() ? s : boolean(BooleanOp::Join, result, s);
  }
  return result;
}

TopoDS_Shape extrudeToPlane(const std::vector<TopoDS_Shape>& faces, Vec3 dirV, Vec3 originV, Vec3 normalV) {
  if (faces.empty()) throw KernelError("Extrude: no profile selected");
  gp_Dir dir(dirV.x, dirV.y, dirV.z);
  const gp_Pnt p0(originV.x, originV.y, originV.z);
  const gp_Dir np(normalV.x, normalV.y, normalV.z);
  GProp_GProps g;
  for (const auto& f : faces) {
    GProp_GProps one;
    BRepGProp::SurfaceProperties(f, one);
    g.Add(one);
  }
  const gp_Pnt c = g.CentreOfMass();
  const double along = gp_Vec(dir).Dot(gp_Vec(np));
  if (std::abs(along) < 1e-9) throw KernelError("Extrude: the object is parallel to the extrude direction");
  double t = gp_Vec(c, p0).Dot(gp_Vec(np)) / along;   // distance along dir to the plane
  if (std::abs(t) < 1e-9) throw KernelError("Extrude: the profile already lies on that object");
  if (t < 0) {
    dir.Reverse();
    t = -t;
  }
  Bnd_Box box;
  for (const auto& f : faces) BRepBndLib::Add(f, box);
  double x0, y0, z0, x1, y1, z1;
  box.Get(x0, y0, z0, x1, y1, z1);
  const double reach = t + 2 * std::hypot(x1 - x0, y1 - y0, z1 - z0) + 1.0;
  TopoDS_Shape result = guarded("Extrude", [&]() -> TopoDS_Shape {
    const TopoDS_Shape prism = extrudeEx(faces, {dir.X(), dir.Y(), dir.Z()}, reach, 0, 0, 0);
    // Keep what lies on the profile's side of the plane.
    const double big = reach * 4 + 10;
    const TopoDS_Face cutter = BRepBuilderAPI_MakeFace(gp_Pln(p0, np), -big, big, -big, big).Face();
    const TopoDS_Solid half = BRepPrimAPI_MakeHalfSpace(cutter, c).Solid();
    return boolean(BooleanOp::Intersect, prism, half);
  });
  if (!isValid(result)) throw KernelError("Extrude: could not reach that object");
  return result;
}

namespace {
// A closed section wire centred at p, in the plane normal to t; `u` (in that
// plane) is where a square's side faces and a triangle's tip points.
TopoDS_Wire sectionWire(Section section, double size, const gp_Pnt& p, const gp_Dir& t, const gp_Dir& u) {
  const gp_Dir v = t.Crossed(u);
  if (section == Section::Circular)
    return BRepBuilderAPI_MakeWire(BRepBuilderAPI_MakeEdge(gp_Circ(gp_Ax2(p, t, u), size / 2)).Edge()).Wire();
  BRepBuilderAPI_MakePolygon poly;
  if (section == Section::Square) {
    const double h = size / 2;
    for (auto [a, b] : {std::pair{h, h}, {-h, h}, {-h, -h}, {h, -h}})
      poly.Add(p.Translated(gp_Vec(u) * a + gp_Vec(v) * b));
  } else {
    // Equilateral triangle of side `size`, tip along u.
    const double r = size / std::sqrt(3.0);
    for (int k = 0; k < 3; ++k) {
      const double ang = 2 * 3.14159265358979323846 * k / 3;
      poly.Add(p.Translated(gp_Vec(u) * (r * std::cos(ang)) + gp_Vec(v) * (r * std::sin(ang))));
    }
  }
  poly.Close();
  return poly.Wire();
}

gp_Dir anyPerpendicular(const gp_Dir& t) {
  const gp_Vec a = std::abs(t.Z()) < 0.9 ? gp_Vec(0, 0, 1) : gp_Vec(1, 0, 0);
  return gp_Dir(gp_Vec(t).Crossed(a));
}

TopoDS_Shape solidSweep(const TopoDS_Wire& path, const TopoDS_Wire& profile, const gp_Dir* binormal) {
  BRepOffsetAPI_MakePipeShell pipe(path);
  if (binormal) pipe.SetMode(*binormal);   // helices: keep the section's orientation about the axis
  else pipe.SetMode(false);
  pipe.SetTransitionMode(BRepBuilderAPI_RoundCorner);
  pipe.Add(profile, false, false);
  pipe.Build();
  if (!pipe.IsDone() || !pipe.MakeSolid()) return {};
  return pipe.Shape();
}
} // namespace

TopoDS_Shape pipe(const std::vector<TopoDS_Shape>& pathEdges, Section section, double size, double wall) {
  if (pathEdges.empty()) throw KernelError("Pipe: the path has no curves");
  if (!(size > 0)) throw KernelError("Pipe: the section size must be greater than zero");
  if (wall > 0 && 2 * wall >= size) throw KernelError("Pipe: the wall is too thick for the section size");
  Handle(TopTools_HSequenceOfShape) edges = new TopTools_HSequenceOfShape;
  for (const auto& e : pathEdges) edges->Append(e);
  Handle(TopTools_HSequenceOfShape) wires;
  ShapeAnalysis_FreeBounds::ConnectEdgesToWires(edges, 1e-6, false, wires);
  if (wires.IsNull() || wires->Length() != 1) throw KernelError("Pipe: the path must be one connected chain of curves");
  const TopoDS_Wire path = TopoDS::Wire(wires->Value(1));
  TopoDS_Shape result = guarded("Pipe", [&]() -> TopoDS_Shape {
    BRepAdaptor_CompCurve c(path);
    gp_Pnt p;
    gp_Vec t;
    c.D1(c.FirstParameter(), p, t);
    if (t.Magnitude() < 1e-12) return {};
    const gp_Dir td(t);
    const gp_Dir u = anyPerpendicular(td);
    TopoDS_Shape solid = solidSweep(path, sectionWire(section, size, p, td, u), nullptr);
    if (solid.IsNull() || wall <= 0) return solid;
    const TopoDS_Shape inner = solidSweep(path, sectionWire(section, size - 2 * wall, p, td, u), nullptr);
    return inner.IsNull() ? TopoDS_Shape() : boolean(BooleanOp::Cut, solid, inner);
  });
  if (!isValid(result)) throw KernelError("Pipe: could not build a valid solid (is the section too big for the path's bends?)");
  return result;
}

TopoDS_Shape coil(Vec3 origin, Vec3 axis, Vec3 xdir, double diameter, double turns, double height, double taper,
                  Section section, double size, int position) {
  if (!(diameter > 0) || !(turns > 0) || !(size > 0)) throw KernelError("Coil: diameter, revolutions and section size must be greater than zero");
  if (!(std::abs(height) > 1e-9)) throw KernelError("Coil: the height must not be zero");
  if (std::abs(taper) >= 1.5) throw KernelError("Coil: the angle must be between -85 and 85 degrees");
  const double pitch = std::abs(height) / turns;
  if (pitch < size * (section == Section::Triangular ? 0.866 : 1.0) * 1.0001)
    throw KernelError("Coil: the turns would overlap; make the pitch larger than the section size");
  double r = diameter / 2 + (position == 1 ? -size / 2 : position == 2 ? size / 2 : 0.0);
  if (r <= size / 2) throw KernelError("Coil: the diameter is too small for the section");
  TopoDS_Shape result = guarded("Coil", [&]() -> TopoDS_Shape {
    const gp_Dir z(axis.x, axis.y, axis.z);
    gp_Vec xv(xdir.x, xdir.y, xdir.z);
    xv -= gp_Vec(z) * xv.Dot(gp_Vec(z));
    const gp_Ax3 frame(gp_Pnt(origin.x, origin.y, origin.z), z, gp_Dir(xv));
    // The helix as a straight 2D line on a cylinder (or cone, when tapered).
    Handle(Geom_Surface) surf;
    double vLen = height;
    if (std::abs(taper) > 1e-9) {
      surf = new Geom_ConicalSurface(frame, taper, r);
      vLen = height / std::cos(taper);
    } else {
      surf = new Geom_CylindricalSurface(frame, r);
    }
    const gp_Vec2d d(2 * 3.14159265358979323846 * turns, vLen);
    Handle(Geom2d_Line) line = new Geom2d_Line(gp_Pnt2d(0, 0), gp_Dir2d(d));
    TopoDS_Edge helix = BRepBuilderAPI_MakeEdge(line, surf, 0.0, d.Magnitude()).Edge();
    BRepLib::BuildCurves3d(helix);
    const TopoDS_Wire path = BRepBuilderAPI_MakeWire(helix).Wire();
    BRepAdaptor_Curve c(helix);
    gp_Pnt p;
    gp_Vec t;
    c.D1(c.FirstParameter(), p, t);
    gp_Vec radial(frame.Location(), p);
    radial -= gp_Vec(z) * radial.Dot(gp_Vec(z));
    gp_Vec u = radial - t.Normalized() * radial.Dot(t.Normalized());
    if (u.Magnitude() < 1e-12) u = gp_Vec(anyPerpendicular(gp_Dir(t)));
    return solidSweep(path, sectionWire(section, size, p, gp_Dir(t), gp_Dir(u)), &z);
  });
  if (!isValid(result)) throw KernelError("Coil: could not build a valid solid from these values");
  return result;
}

namespace {
// A loft from a straight-sided polygon to a circle on its axis, built exactly: the circle
// is split at the directions of the polygon's corners (seen from the
// polygon's centre) and each side is ruled onto its arc,
//   S(u, t) = (1 - t) L(u) + t C(u),
// with L the side (linear in u) and C the arc as a rational quadratic Bezier
// (weights 1, cos(D/2), 1). Written over C's weight function W(u) both rows
// are degree 3 with the same weights, so each side is one exact rational
// Bezier patch. Returns a null shape when the sections are not of this kind.
TopoDS_Shape polygonToCircleLoft(const TopoDS_Wire& poly, const TopoDS_Edge& circleEdge) {
  BRepAdaptor_Curve cc(circleEdge);
  if (cc.GetType() != GeomAbs_Circle || !BRep_Tool::IsClosed(circleEdge)) return {};
  const gp_Circ circ = cc.Circle();
  const gp_Dir n = circ.Axis().Direction();
  std::vector<gp_Pnt> corners;
  for (BRepTools_WireExplorer x(poly); x.More(); x.Next()) {
    BRepAdaptor_Curve c(x.Current());
    if (c.GetType() != GeomAbs_Line) return {};
    corners.push_back(BRep_Tool::Pnt(x.CurrentVertex()));
  }
  const size_t N = corners.size();
  if (N < 3) return {};
  gp_XYZ g(0, 0, 0);
  for (const auto& p : corners) g += p.XYZ();
  g /= static_cast<double>(N);
  // The polygon must lie in a plane parallel to the circle, centred on the
  // circle's axis: only then do the corner directions, seen from the common
  // centre, say where the circle splits. Offset circles use the general loft.
  for (const auto& p : corners)
    if (std::abs(gp_Vec(gp_Pnt(g), p).Dot(gp_Vec(n))) > 1e-7) return {};
  {
    gp_Vec off(circ.Location(), gp_Pnt(g));
    off -= gp_Vec(n) * off.Dot(gp_Vec(n));
    if (off.Magnitude() > 1e-7) return {};
  }
  const gp_Dir xd = circ.XAxis().Direction(), yd = circ.YAxis().Direction();
  std::vector<double> ang(N);
  for (size_t i = 0; i < N; ++i) {
    const gp_Vec d(gp_Pnt(g), corners[i]);
    ang[i] = std::atan2(d.Dot(gp_Vec(yd)), d.Dot(gp_Vec(xd)));
  }
  // Corners must go round the same way as the circle; reverse them if not.
  double turn = 0;
  for (size_t i = 0; i < N; ++i) {
    double dA = ang[(i + 1) % N] - ang[i];
    while (dA <= -M_PI) dA += 2 * M_PI;
    while (dA > M_PI) dA -= 2 * M_PI;
    turn += dA;
  }
  if (turn < 0) {
    std::reverse(corners.begin(), corners.end());
    std::reverse(ang.begin(), ang.end());
  }
  const double r = circ.Radius();
  const gp_Pnt c = circ.Location();
  auto onCircle = [&](double a) { return c.Translated(gp_Vec(xd) * (r * std::cos(a)) + gp_Vec(yd) * (r * std::sin(a))); };
  BRepBuilderAPI_Sewing sew(1e-6);
  BRepBuilderAPI_MakeWire top;
  for (size_t i = 0; i < N; ++i) {
    const double a0 = ang[i];
    double D = ang[(i + 1) % N] - a0;
    while (D <= 0) D += 2 * M_PI;
    if (D >= M_PI - 1e-9) return {};   // one rational quadratic arc spans less than half a turn
    const double w = std::cos(D / 2);
    const gp_Pnt Q0 = onCircle(a0), Q2 = onCircle(a0 + D);
    const gp_Pnt Q1 = c.Translated((gp_Vec(xd) * std::cos(a0 + D / 2) + gp_Vec(yd) * std::sin(a0 + D / 2)) * (r / w));
    const gp_Pnt A = corners[i], B = corners[(i + 1) % N];
    // Degree-3 weights (W elevated) and homogeneous rows.
    const double om[4] = {1, (1 + 2 * w) / 3, (2 * w + 1) / 3, 1};
    const gp_XYZ h0[4] = {A.XYZ(), (A.XYZ() * (2 * w) + B.XYZ()) / 3, (A.XYZ() + B.XYZ() * (2 * w)) / 3, B.XYZ()};
    const gp_XYZ h1[4] = {Q0.XYZ(), (Q0.XYZ() + Q1.XYZ() * (2 * w)) / 3, (Q1.XYZ() * (2 * w) + Q2.XYZ()) / 3, Q2.XYZ()};
    TColgp_Array2OfPnt poles(1, 4, 1, 2);
    TColStd_Array2OfReal weights(1, 4, 1, 2);
    for (int k = 0; k < 4; ++k) {
      poles(k + 1, 1) = gp_Pnt(h0[k] / om[k]);
      poles(k + 1, 2) = gp_Pnt(h1[k] / om[k]);
      weights(k + 1, 1) = weights(k + 1, 2) = om[k];
    }
    Handle(Geom_BezierSurface) patch = new Geom_BezierSurface(poles, weights);
    BRepBuilderAPI_MakeFace side(patch, 1e-7);
    if (!side.IsDone()) return {};
    sew.Add(side.Face());
    // The same arc as an edge of the top face.
    TColgp_Array1OfPnt ap(1, 3);
    TColStd_Array1OfReal aw(1, 3);
    ap(1) = Q0, ap(2) = Q1, ap(3) = Q2;
    aw(1) = 1, aw(2) = w, aw(3) = 1;
    top.Add(BRepBuilderAPI_MakeEdge(Handle(Geom_BezierCurve)(new Geom_BezierCurve(ap, aw))).Edge());
  }
  if (!top.IsDone()) return {};
  sew.Add(BRepBuilderAPI_MakeFace(poly, true).Face());
  sew.Add(BRepBuilderAPI_MakeFace(top.Wire(), true).Face());
  sew.Perform();
  TopoDS_Shell shell;
  for (TopExp_Explorer x(sew.SewedShape(), TopAbs_SHELL); x.More(); x.Next()) shell = TopoDS::Shell(x.Current());
  if (shell.IsNull()) return {};
  BRepBuilderAPI_MakeSolid ms(shell);
  if (!ms.IsDone()) return {};
  Handle(ShapeFix_Solid) fix = new ShapeFix_Solid(ms.Solid());
  fix->Perform();
  const TopoDS_Shape solid = fix->Solid();
  if (!isValid(solid) || massProperties(solid).volume <= 0) return {};
  return solid;
}
} // namespace

TopoDS_Shape loft(const std::vector<TopoDS_Shape>& sections, bool ruled) {
  if (sections.size() < 2) throw KernelError("Loft: pick at least two profiles");
  // Two sections, a polygon and a circle: the exact construction.
  if (sections.size() == 2 && sections[0].ShapeType() != TopAbs_VERTEX && sections[1].ShapeType() != TopAbs_VERTEX) {
    auto wireOf = [](const TopoDS_Shape& s) {
      return s.ShapeType() == TopAbs_FACE ? BRepTools::OuterWire(TopoDS::Face(s)) : TopoDS::Wire(s);
    };
    const TopoDS_Wire w0 = wireOf(sections[0]), w1 = wireOf(sections[1]);
    auto single = [](const TopoDS_Wire& w) {
      TopoDS_Edge only;
      int n = 0;
      for (TopExp_Explorer x(w, TopAbs_EDGE); x.More(); x.Next(), ++n) only = TopoDS::Edge(x.Current());
      return n == 1 ? only : TopoDS_Edge();
    };
    TopoDS_Shape exact;
    try {
      if (const TopoDS_Edge e = single(w1); !e.IsNull()) exact = polygonToCircleLoft(w0, e);
      else if (const TopoDS_Edge e0 = single(w0); !e0.IsNull()) exact = polygonToCircleLoft(w1, e0);
    } catch (const Standard_Failure&) {
      exact.Nullify();
    }
    if (!exact.IsNull()) return exact;
  }
  TopoDS_Shape r = guarded("Loft", [&]() -> TopoDS_Shape {
    BRepOffsetAPI_ThruSections ts(true, ruled, 1e-6);
    ts.CheckCompatibility(true);   // match up sections with different numbers of edges
    for (size_t i = 0; i < sections.size(); ++i) {
      const TopoDS_Shape& s = sections[i];
      if (s.ShapeType() == TopAbs_VERTEX) {   // loft to a point: first or last only
        if (i != 0 && i + 1 != sections.size()) throw KernelError("Loft: a point can be only the first or last profile");
        ts.AddVertex(TopoDS::Vertex(s));
        continue;
      }
      ts.AddWire(s.ShapeType() == TopAbs_FACE ? BRepTools::OuterWire(TopoDS::Face(s)) : TopoDS::Wire(s));
    }
    ts.Build();
    return ts.IsDone() ? ts.Shape() : TopoDS_Shape();
  });
  if (!isValid(r)) throw KernelError("Loft: the profiles could not be joined into a valid solid");
  return r;
}

double isoCoarsePitch(double diameter) {
  // ISO 261 coarse series, (nominal mm, pitch mm).
  static const double table[][2] = {{1, 0.25},   {1.2, 0.25}, {1.6, 0.35}, {2, 0.4},   {2.5, 0.45}, {3, 0.5},
                                    {3.5, 0.6},  {4, 0.7},    {5, 0.8},    {6, 1.0},   {8, 1.25},   {10, 1.5},
                                    {12, 1.75},  {14, 2.0},   {16, 2.0},   {18, 2.5},  {20, 2.5},   {22, 2.5},
                                    {24, 3.0},   {27, 3.0},   {30, 3.5},   {36, 4.0},  {42, 4.5},   {48, 5.0},
                                    {56, 5.5},   {64, 6.0}};
  const double mm = diameter * 10;
  double best = table[0][1], bestD = 1e300;
  for (const auto& row : table)
    if (std::abs(row[0] - mm) < bestD) {
      bestD = std::abs(row[0] - mm);
      best = row[1];
    }
  return best / 10;
}

TopoDS_Shape thread(const TopoDS_Shape& body, const TopoDS_Shape& faceShape, double pitch, double offset, double length,
                    bool rightHand, ThreadInfo* info) {
  if (faceShape.IsNull() || faceShape.ShapeType() != TopAbs_FACE) throw KernelError("Thread: select a cylindrical face");
  const TopoDS_Face face = TopoDS::Face(faceShape);
  BRepAdaptor_Surface s(face, true);
  if (s.GetType() != GeomAbs_Cylinder) throw KernelError("Thread: select a cylindrical face (a shaft or a hole)");
  const gp_Cylinder cyl = s.Cylinder();
  const double r = cyl.Radius();
  if (pitch <= 0) pitch = isoCoarsePitch(2 * r);
  double u0, u1, v0, v1;
  BRepTools::UVBounds(face, u0, u1, v0, v1);
  const gp_Ax1 axis = cyl.Axis();
  // Shaft or hole: does the face's outward normal point away from the axis?
  gp_Pnt p;
  gp_Vec du, dv;
  s.D1((u0 + u1) / 2, (v0 + v1) / 2, p, du, dv);
  gp_Vec n = du.Crossed(dv);
  if (face.Orientation() == TopAbs_REVERSED) n.Reverse();
  gp_Vec radial(axis.Location(), p);
  radial -= gp_Vec(axis.Direction()) * radial.Dot(gp_Vec(axis.Direction()));
  const bool internal = n.Dot(radial) < 0;
  const double faceLen = v1 - v0;
  if (offset < 0 || offset >= faceLen) throw KernelError("Thread: the offset is outside the face");
  if (length <= 0 || offset + length > faceLen) length = faceLen - offset;
  if (length < pitch) throw KernelError("Thread: the face is shorter than one pitch");
  if (info) *info = {2 * r, pitch, internal};

  TopoDS_Shape result = guarded("Thread", [&]() -> TopoDS_Shape {
    // Frame on the axis where the thread starts, X towards the face point.
    const gp_Dir z = axis.Direction();
    const gp_Pnt start = axis.Location().Translated(gp_Vec(z) * (v0 + offset));
    const gp_Dir x(radial);
    const gp_Ax3 frame(start, z, x);
    // Helix on the cylinder; one extra pitch so the cut runs out cleanly.
    const double h = 0.61343 * pitch;   // ISO external thread depth
    const double e = 0.15 * pitch;      // the tool reaches past the surface
    const double turns = length / pitch;
    Handle(Geom_Surface) surf = new Geom_CylindricalSurface(frame, r);
    const gp_Vec2d d((rightHand ? 1.0 : -1.0) * 2 * 3.14159265358979323846 * turns, length);
    Handle(Geom2d_Line) line = new Geom2d_Line(gp_Pnt2d(0, 0), gp_Dir2d(d));
    TopoDS_Edge helix = BRepBuilderAPI_MakeEdge(line, surf, 0.0, d.Magnitude()).Edge();
    BRepLib::BuildCurves3d(helix);
    const TopoDS_Wire path = BRepBuilderAPI_MakeWire(helix).Wire();
    // 60 degree V in the axial plane at the helix start, tip into the material.
    const double tipR = internal ? r + h : r - h;
    const double baseR = internal ? r - e : r + e;
    const double half = std::abs(baseR - tipR) * std::tan(30.0 * 3.14159265358979323846 / 180.0);
    auto at = [&](double rr, double zz) {
      return start.Translated(gp_Vec(x) * rr + gp_Vec(z) * zz);
    };
    BRepBuilderAPI_MakePolygon tri(at(tipR, 0), at(baseR, half), at(baseR, -half), true);
    const TopoDS_Shape tool = solidSweep(path, tri.Wire(), &z);
    if (tool.IsNull()) return tool;
    return boolean(BooleanOp::Cut, body, tool);
  });
  if (!isValid(result)) throw KernelError("Thread: could not cut the thread into this face");
  return result;
}

TopoDS_Shape offsetFaces(const TopoDS_Shape& body, const std::vector<TopoDS_Shape>& faces, double distance) {
  if (faces.empty()) throw KernelError("Offset Face: select a face");
  if (std::abs(distance) < 1e-9) throw KernelError("Offset Face: the distance must not be zero");
  TopoDS_Shape result = guarded("Offset Face", [&]() -> TopoDS_Shape {
    BRepOffset_MakeOffset mo;
    mo.Initialize(body, 0.0, 1e-6, BRepOffset_Skin, Standard_False, Standard_False, GeomAbs_Intersection);
    for (const auto& f : faces) mo.SetOffsetOnFace(TopoDS::Face(f), distance);
    mo.MakeOffsetShape();
    if (!mo.IsDone()) return TopoDS_Shape();
    TopoDS_Shape s = mo.Shape();
    ShapeUpgrade_UnifySameDomain unify(s, true, true, false);
    unify.Build();
    return unify.Shape();
  });
  if (!isValid(result) || !TopExp_Explorer(result, TopAbs_SOLID).More())
    throw KernelError("Offset Face: could not move those faces that far (try a smaller distance)");
  return result;
}

TopoDS_Shape draft(const TopoDS_Shape& body, const std::vector<TopoDS_Shape>& faces, Vec3 pullDir, Vec3 planeOrigin,
                   double angle) {
  if (faces.empty()) throw KernelError("Draft: select the faces to tilt");
  if (std::abs(angle) < 1e-9) throw KernelError("Draft: the angle must not be zero");
  if (std::abs(angle) >= 1.5) throw KernelError("Draft: the angle must be less than 85 degrees");
  const gp_Dir dir(pullDir.x, pullDir.y, pullDir.z);
  const gp_Pln neutral(gp_Pnt(planeOrigin.x, planeOrigin.y, planeOrigin.z), dir);
  TopoDS_Shape result = guarded("Draft", [&]() -> TopoDS_Shape {
    BRepOffsetAPI_DraftAngle d(body);
    for (const auto& f : faces) {
      d.Add(TopoDS::Face(f), dir, angle, neutral);
      if (!d.AddDone()) throw KernelError("Draft: a face cannot be drafted in that direction (is it parallel to the plane?)");
    }
    d.Build();
    return d.IsDone() ? d.Shape() : TopoDS_Shape();
  });
  if (!isValid(result)) throw KernelError("Draft: could not tilt those faces by that angle");
  return result;
}

TopoDS_Shape pressPull(const TopoDS_Shape& body, const std::vector<TopoDS_Shape>& faces, double distance) {
  if (faces.empty()) throw KernelError("Press Pull: select a face");
  if (std::abs(distance) < 1e-9) throw KernelError("Press Pull: the distance must not be zero");
  // Curved faces are offset (as Offset Face does); flat ones are pushed or pulled.
  for (const auto& fs : faces)
    if (BRepAdaptor_Surface(TopoDS::Face(fs)).GetType() != GeomAbs_Plane) return offsetFaces(body, faces, distance);
  TopoDS_Shape result = body;
  for (const auto& fs : faces) {
    const TopoDS_Face& f = TopoDS::Face(fs);
    BRepAdaptor_Surface surf(f);
    gp_Dir n = surf.Plane().Axis().Direction();
    if (f.Orientation() == TopAbs_REVERSED) n.Reverse();
    const TopoDS_Shape prism = guarded("Press Pull", [&] { return BRepPrimAPI_MakePrism(f, gp_Vec(n) * distance).Shape(); });
    result = boolean(distance > 0 ? BooleanOp::Join : BooleanOp::Cut, result, prism);
  }
  return result;
}

TopoDS_Shape boolean(BooleanOp op, const TopoDS_Shape& target, const TopoDS_Shape& tool) {
  if (target.IsNull() || tool.IsNull()) throw KernelError("boolean needs two bodies");
  const char* what = op == BooleanOp::Join ? "Join" : op == BooleanOp::Cut ? "Cut" : "Intersect";
  TopoDS_Shape result = guarded(what, [&]() -> TopoDS_Shape {
    std::unique_ptr<BRepAlgoAPI_BooleanOperation> algo;
    switch (op) {
      case BooleanOp::Join: algo = std::make_unique<BRepAlgoAPI_Fuse>(target, tool); break;
      case BooleanOp::Cut: algo = std::make_unique<BRepAlgoAPI_Cut>(target, tool); break;
      case BooleanOp::Intersect: algo = std::make_unique<BRepAlgoAPI_Common>(target, tool); break;
    }
    if (!algo->IsDone() || algo->HasErrors()) return TopoDS_Shape();
    ShapeUpgrade_UnifySameDomain unify(algo->Shape(), true, true, false);
    unify.Build();
    return unify.Shape();
  });
  if (!TopExp_Explorer(result, TopAbs_SOLID).More())
    throw KernelError(std::string(what) + " leaves no solid");
  return result;
}

bool isValid(const TopoDS_Shape& s) {
  if (s.IsNull()) return false;
  BRepCheck_Analyzer a(s);
  return a.IsValid();
}

MassProperties massProperties(const TopoDS_Shape& s) {
  MassProperties m;
  if (s.IsNull()) return m;
  GProp_GProps vol, surf;
  BRepGProp::VolumeProperties(s, vol);
  BRepGProp::SurfaceProperties(s, surf);
  m.volume = vol.Mass();
  m.area = surf.Mass();
  const gp_Pnt c = vol.CentreOfMass();
  m.centerOfMass = {c.X(), c.Y(), c.Z()};
  return m;
}

BoundingBox boundingBox(const TopoDS_Shape& s) {
  BoundingBox b;
  if (s.IsNull()) return b;
  Bnd_Box box;
  BRepBndLib::AddOptimal(s, box, /*useTriangulation=*/false, /*useShapeTolerance=*/false);
  double x0, y0, z0, x1, y1, z1;
  box.Get(x0, y0, z0, x1, y1, z1);
  b.min = {x0, y0, z0};
  b.max = {x1, y1, z1};
  return b;
}

std::optional<SurfacePoint> pointOnBody(const TopoDS_Shape& body, Vec3 p) {
  const TopoDS_Vertex v = BRepBuilderAPI_MakeVertex(pnt(p)).Vertex();
  TopoDS_Face best;
  double bestD = 1e300;
  for (TopExp_Explorer f(body, TopAbs_FACE); f.More(); f.Next()) {
    BRepExtrema_DistShapeShape d(v, f.Current());
    if (d.IsDone() && d.NbSolution() > 0 && d.Value() < bestD) {
      bestD = d.Value();
      best = TopoDS::Face(f.Current());
    }
  }
  if (best.IsNull()) return std::nullopt;
  BRepAdaptor_Surface s(best, true);
  GeomAPI_ProjectPointOnSurf proj(pnt(p), BRep_Tool::Surface(best));
  if (proj.NbPoints() == 0) return std::nullopt;
  double u = 0, w = 0;
  proj.LowerDistanceParameters(u, w);
  BRepLProp_SLProps props(s, u, w, 1, 1e-7);
  if (!props.IsNormalDefined()) return std::nullopt;
  gp_Dir n = props.Normal();
  if (best.Orientation() == TopAbs_REVERSED) n.Reverse();
  const gp_Pnt q = props.Value();
  return SurfacePoint{{q.X(), q.Y(), q.Z()}, {n.X(), n.Y(), n.Z()}};
}

int smoothPatchCount(const TopoDS_Shape& s) {
  TopTools_IndexedMapOfShape faces;
  TopExp::MapShapes(s, TopAbs_FACE, faces);
  const int n = faces.Extent();
  std::vector<int> parent(n + 1);
  for (int i = 0; i <= n; ++i) parent[i] = i;
  std::function<int(int)> root = [&](int i) { return parent[i] == i ? i : parent[i] = root(parent[i]); };
  // Same surface: the same geometry object at the same placement.
  auto sameSurface = [&](int a, int b) {
    TopLoc_Location la, lb;
    const Handle(Geom_Surface) sa = BRep_Tool::Surface(TopoDS::Face(faces(a)), la);
    const Handle(Geom_Surface) sb = BRep_Tool::Surface(TopoDS::Face(faces(b)), lb);
    return !sa.IsNull() && sa == sb && la.IsEqual(lb);
  };
  TopTools_IndexedDataMapOfShapeListOfShape edgeFaces;
  TopExp::MapShapesAndAncestors(s, TopAbs_EDGE, TopAbs_FACE, edgeFaces);
  for (int e = 1; e <= edgeFaces.Extent(); ++e) {
    std::vector<int> fs;
    for (const auto& f : edgeFaces(e)) {
      const int k = faces.FindIndex(f);
      if (k > 0 && std::find(fs.begin(), fs.end(), k) == fs.end()) fs.push_back(k);
    }
    for (size_t a = 0; a < fs.size(); ++a)
      for (size_t b = a + 1; b < fs.size(); ++b)
        if (sameSurface(fs[a], fs[b])) parent[root(fs[a])] = root(fs[b]);
  }
  int count = 0;
  for (int i = 1; i <= n; ++i) count += root(i) == i;
  return count;
}

TopologyCounts topologyCounts(const TopoDS_Shape& s) {
  TopologyCounts t;
  if (s.IsNull()) return t;
  auto count = [&](TopAbs_ShapeEnum type) {
    TopTools_IndexedMapOfShape map;
    TopExp::MapShapes(s, type, map);
    return map.Extent();
  };
  t.solids = count(TopAbs_SOLID);
  t.shells = count(TopAbs_SHELL);
  t.faces = count(TopAbs_FACE);
  t.edges = count(TopAbs_EDGE);
  t.vertices = count(TopAbs_VERTEX);
  return t;
}

} // namespace tsr::kernel
