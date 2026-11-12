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
      const auto e = edgesNear(body, {s.point}, std::max(0.05, 0.2 * frame.diag));
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
  TopoDS_Shape r;
  try {
    if (!openFaces.empty()) {
      TopTools_ListOfShape faces;
      for (const auto& f : openFaces) faces.Append(f);
      BRepOffsetAPI_MakeThickSolid mk;
      mk.MakeThickSolidByJoin(body, faces, outside ? thickness : -thickness, 1e-4);
      if (mk.IsDone()) r = mk.Shape();
    } else {
      // Closed hollow: offset the whole body and subtract.
      BRepOffsetAPI_MakeOffsetShape off;
      off.PerformByJoin(body, outside ? thickness : -thickness, 1e-4);
      if (off.IsDone()) {
        const TopoDS_Shape other = asSolid(off.Shape());
        if (!other.IsNull()) r = outside ? boolean(BooleanOp::Cut, other, body) : boolean(BooleanOp::Cut, body, other);
      }
    }
  } catch (const Standard_Failure& f) {
    throw KernelError(std::string("Shell: ") + f.GetMessageString());
  } catch (const KernelError&) {
    r.Nullify();
  }
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
