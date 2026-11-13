#pragma once
// Sketch <-> 3D: the plane a sketch lives on, its curves as OCCT edges, and
// its profiles (the closed regions the curves enclose).
#include "tsr/sketch/Sketch.h"

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

// Index of the profile containing sketch point (x, y), or -1.
int profileAt(const std::vector<Profile>& ps, const gp_Ax3& frame, double x, double y);

} // namespace tsr::sketch
