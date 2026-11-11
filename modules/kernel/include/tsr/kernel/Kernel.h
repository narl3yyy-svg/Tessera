#pragma once
// tsr-kernel: the only module that talks to OCCT modelling algorithms.
// Lengths are internal units (cm) throughout; IO converts at the boundary.
#include <TopoDS_Shape.hxx>

#include <stdexcept>
#include <string>
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

// Revolves planar faces about the axis through `origin` along `dir` by
// `angle` radians (2*pi for a full turn). Symmetric: half the angle each way.
TopoDS_Shape revolve(const std::vector<TopoDS_Shape>& faces, Vec3 origin, Vec3 dir, double angle, bool symmetric);

// Edges are referred to by a point on them: each point selects the edge of
// `shape` nearest to it. Throws KernelError if a point is not near any edge
// (farther than `tolerance`).
std::vector<TopoDS_Shape> edgesNear(const TopoDS_Shape& shape, const std::vector<Vec3>& points, double tolerance);

// Edge references that survive edits of earlier features. A reference is
// "x,y,z" (a point on the edge) or that plus a signature recorded when the
// edge was picked: curve type, position relative to the body's bounding box,
// direction and the normals of the two faces that meet there. On replay the
// best-matching edge of the (possibly resized) body is chosen. References
// are separated by ';'.
std::string edgeReference(const TopoDS_Shape& body, const TopoDS_Shape& edge);
// Upgrades plain points to full references against `body`.
std::string completeEdgeReferences(const TopoDS_Shape& body, const std::string& refs);
std::vector<TopoDS_Shape> resolveEdges(const TopoDS_Shape& body, const std::string& refs);
// A point on the middle of an edge, for referring to it later.
Vec3 edgeMidpoint(const TopoDS_Shape& edge);

// Rounds / bevels edges (tangent-continuous neighbours are included). Throws
// KernelError, e.g. when the size does not fit the adjacent faces.
TopoDS_Shape fillet(const TopoDS_Shape& shape, const std::vector<TopoDS_Shape>& edges, double radius);
TopoDS_Shape chamfer(const TopoDS_Shape& shape, const std::vector<TopoDS_Shape>& edges, double distance);

enum class BooleanOp { Join, Cut, Intersect };
// Boolean of `target` with `tool`, faces merged afterwards. Throws KernelError
// if OCCT fails or the result is empty (e.g. a cut that removes everything).
TopoDS_Shape boolean(BooleanOp op, const TopoDS_Shape& target, const TopoDS_Shape& tool);

bool isValid(const TopoDS_Shape& s);   // BRepCheck_Analyzer
MassProperties massProperties(const TopoDS_Shape& s);
BoundingBox boundingBox(const TopoDS_Shape& s);
TopologyCounts topologyCounts(const TopoDS_Shape& s);

} // namespace tsr::kernel
