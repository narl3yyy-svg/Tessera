#pragma once
// tsr-kernel: the only module that talks to OCCT modelling algorithms.
// Lengths are internal units (cm) throughout; IO converts at the boundary.
#include <TopoDS_Shape.hxx>

#include <stdexcept>

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

// Axis-aligned box with one corner at the origin. Throws KernelError on
// non-positive sizes or if OCCT fails.
TopoDS_Shape makeBox(double dx, double dy, double dz);

bool isValid(const TopoDS_Shape& s);   // BRepCheck_Analyzer
MassProperties massProperties(const TopoDS_Shape& s);
BoundingBox boundingBox(const TopoDS_Shape& s);
TopologyCounts topologyCounts(const TopoDS_Shape& s);

} // namespace tsr::kernel
