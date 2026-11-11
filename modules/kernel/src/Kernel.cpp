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
