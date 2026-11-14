#pragma once
// Sketch profiles for drawing and picking, remembered by the sketch's shape.
//
// Splitting every curve at every crossing is the slowest step of drawing a
// sketch, and the canvas asks for it on every hover change and every
// document change, mostly for sketches that did not change. Only the app
// uses this: features compute their own profiles so their faces are never
// shared between bodies.
#include "tsr/sketch/SketchGeometry.h"

#include <vector>

namespace tsr::app {

std::vector<sketch::Profile> cachedProfiles(const sketch::Sketch& s, const gp_Ax3& frame);

} // namespace tsr::app
