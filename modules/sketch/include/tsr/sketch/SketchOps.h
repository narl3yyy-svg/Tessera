#pragma once
// Sketch editing operations that change several curves at once: Fillet
// (round the corner between two lines) and Offset (a parallel copy of a
// connected chain of curves). Both keep the sketch solvable or leave it
// unchanged and report why.
#include "tsr/sketch/Sketch.h"

#include <optional>
#include <string>
#include <utility>
#include <vector>

namespace tsr::sketch {

// The two lines that meet at `point` (sharing it or coincident with it), if
// exactly two do.
std::optional<std::pair<int, int>> cornerAt(const Sketch& s, int point);

// Rounds the corner where two lines meet with an arc of `radius`: the lines
// are shortened to the tangent points and the arc gets tangent constraints
// and a radius dimension. Dimensions of the two lines' lengths are dropped
// (the corner they measured is gone). Returns empty on success, else why
// not (the sketch is then unchanged). `arcOut` receives the new arc.
std::string filletCorner(Sketch& s, int lineA, int lineB, double radius, int* arcOut = nullptr);

// The connected chain of lines and arcs through `entity` (ends joined by
// shared or coincident points), in order. A circle is a chain of one.
struct ChainSegment {
  int entity = -1;
  bool forward = true;   // traversed a -> b
};
std::vector<ChainSegment> chainOf(const Sketch& s, int entity, bool* closed = nullptr);

// Adds a copy of the chain through `entity` moved `distance` sideways (for a
// closed chain positive is outward; for an open one, to the right of its
// first curve's a -> b direction). New lines are parallel to the originals
// and new arcs share their centres. Returns empty on success, else why not.
// `created` receives the new entities.
std::string offsetChain(Sketch& s, int entity, double distance, std::vector<int>* created = nullptr);

} // namespace tsr::sketch
