#include "tsr/kernel/Kernel.h"

#include <BRepBndLib.hxx>
#include <BRepCheck_Analyzer.hxx>
#include <BRepGProp.hxx>
#include <BRepPrimAPI_MakeBox.hxx>
#include <Bnd_Box.hxx>
#include <GProp_GProps.hxx>
#include <Standard_Failure.hxx>
#include <TopAbs_ShapeEnum.hxx>
#include <TopTools_IndexedMapOfShape.hxx>
#include <TopExp.hxx>

namespace tsr::kernel {

TopoDS_Shape makeBox(double dx, double dy, double dz) {
  if (!(dx > 0 && dy > 0 && dz > 0)) throw KernelError("box dimensions must be positive");
  try {
    BRepPrimAPI_MakeBox mk(dx, dy, dz);
    mk.Build();
    if (!mk.IsDone()) throw KernelError("BRepPrimAPI_MakeBox failed");
    return mk.Shape();
  } catch (const Standard_Failure& f) {
    throw KernelError(std::string("OCCT: ") + f.GetMessageString());
  }
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
