#pragma once
// tsr-kernel: the only module that talks to OCCT modelling algorithms.
// Lengths are internal units (cm) throughout; IO converts at the boundary.
#include <TopoDS_Shape.hxx>

#include <stdexcept>
#include <vector>

namespace tsr::kernel {

class KernelError : public std::runtime_error {
public:
  using std::runtime_error::runtime_error;
};

struct Vec3 { double x = 0, y = 0, z = 0; };

struct BoundingBox { Vec3 min, max; };

struct MassProperties {
  double volume = 0;
  double area = 0;
  Vec3 centerOfMass;
};

struct TopologyCounts {
  int solids = 0, shells = 0, faces = 0, edges = 0, vertices = 0;
};

enum class Axis { X, Y, Z };

// Primitives. Sizes must be positive (KernelError otherwise).
// Box: axis-aligned, `corner` is its minimum corner.
TopoDS_Shape makeBox(double dx, double dy, double dz, Vec3 corner = {});
// Cylinder: base circle centred on `base`, extruded `height` along `axis`.
TopoDS_Shape makeCylinder(double radius, double height, Vec3 base = {}, Axis axis = Axis::Z);
TopoDS_Shape makeSphere(double radius, Vec3 center = {});
// Torus: ring of radius `major` around `axis` through `center`; tube radius `minor` < `major`.
TopoDS_Shape makeTorus(double major, double minor, Vec3 center = {}, Axis axis = Axis::Z);
// Cone (or frustum): base radius r1 at `base`, top radius r2 (may be 0) at `height` along `axis`.
TopoDS_Shape makeCone(double r1, double r2, double height, Vec3 base = {}, Axis axis = Axis::Z);

// Sweeps planar faces along `dir` (unit vector) by `distance` (may be
// negative). Symmetric: `distance` on each side. Faces are fused into one
// solid where they touch. Throws KernelError.
TopoDS_Shape extrude(const std::vector<TopoDS_Shape>& faces, Vec3 dir, double distance, bool symmetric);

enum class BooleanOp { Join, Cut, Intersect };
// Boolean of `target` with `tool`, faces merged afterwards. Throws KernelError
// if OCCT fails or the result is empty (e.g. a cut that removes everything).
TopoDS_Shape boolean(BooleanOp op, const TopoDS_Shape& target, const TopoDS_Shape& tool);

bool isValid(const TopoDS_Shape& s);   // BRepCheck_Analyzer
MassProperties massProperties(const TopoDS_Shape& s);
BoundingBox boundingBox(const TopoDS_Shape& s);
TopologyCounts topologyCounts(const TopoDS_Shape& s);

} // namespace tsr::kernel
