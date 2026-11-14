#pragma once
// Sketch <-> 3D: the plane a sketch lives on, its curves as OCCT edges, and
// its profiles (the closed regions the curves enclose).
#include "tsr/sketch/Sketch.h"

#include <TopoDS_Edge.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Shape.hxx>
#include <gp_Ax3.hxx>
#include <gp_Pnt.hxx>

#include <string>
#include <vector>

namespace tsr::sketch {

// Plane spec: "XY", "XZ", "YZ" (origin planes; Z is up, so XZ is the front
// plane and YZ the right plane), or
// "custom:ox,oy,oz,nx,ny,nz,xx,xy,xz" (origin, normal, sketch X direction).
// `offset` moves the plane along its normal. Throws SketchError.
gp_Ax3 planeFrame(const std::string& spec, double offset = 0);
std::string customPlaneSpec(const gp_Ax3& frame);

gp_Pnt toWorld(const gp_Ax3& frame, double x, double y);
void toSketch(const gp_Ax3& frame, const gp_Pnt& p, double& x, double& y);   // projects onto the plane

// Edges of the sketch in 3D. Construction geometry only when asked.
TopoDS_Shape curves(const Sketch& s, const gp_Ax3& frame, bool construction = false);
TopoDS_Shape curve(const Sketch& s, const gp_Ax3& frame, int entity);
// A text's letters as planar faces (outlines with their holes), in 3D.
TopoDS_Shape textShape(const Sketch& s, const gp_Ax3& frame, int text);

struct Profile {
  TopoDS_Face face;
  double x = 0, y = 0;   // a point strictly inside the region, sketch coordinates
  double area = 0;
};

// Every closed region bounded by non-construction curves, each the smallest
// such region (a circle inside a rectangle gives the ring and the disc).
// Ordered by decreasing area.
std::vector<Profile> profiles(const Sketch& s, const gp_Ax3& frame);

// A fit point spline's tangent handles, one per fit point (a closed spline's
// repeated end once): where it sits, its direction (tx, ty) as the curve's
// derivative there (1 = the natural speed; a handle not set shows the
// curve's own unit direction), and `arm`, how long a handle of length 1 is
// drawn (cm). Empty for other curves.
struct SplineHandle {
  int index = 0;   // into the spline's fit points
  double x = 0, y = 0;
  double tx = 1, ty = 0;
  double arm = 1;
  bool set = false;
};
std::vector<SplineHandle> splineHandles(const Sketch& s, int entity);

// Include 3D Geometry: body edges copied into the sketch as they are in
// space (points keep their height above the plane), fixed and marked
// projected + included. Lines and circles / arcs parallel to the plane stay
// exact; other curves become fit point splines through points along them.
// Returns how many curves were added.
int includeEdges(Sketch& s, const gp_Ax3& frame, const std::vector<TopoDS_Edge>& edges);

// The sketch as a DXF drawing (AutoCAD R12 text, which every CAD and laser /
// CNC program reads), in millimetres, in the sketch's own coordinates:
// lines, circles and arcs exactly, other curves and text outlines as
// polylines. Construction geometry goes on its own layer when asked.
std::string toDxf(const Sketch& s, bool construction = false);

// Reads a DXF drawing (ASCII, any version) into sketch geometry: LINE,
// CIRCLE, ARC, LWPOLYLINE / POLYLINE (bulges become arcs), SPLINE (fit or
// control points) and ELLIPSE. Units from $INSUNITS (default millimetres);
// `scale` multiplies on top. Ends that meet share a point, so closed shapes
// are profiles. Throws SketchError when nothing can be read.
Sketch fromDxf(const std::string& text, double scale = 1.0);

// Index of the profile containing sketch point (x, y), or -1.
int profileAt(const std::vector<Profile>& ps, const gp_Ax3& frame, double x, double y);

} // namespace tsr::sketch
