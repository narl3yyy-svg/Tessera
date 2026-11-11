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
