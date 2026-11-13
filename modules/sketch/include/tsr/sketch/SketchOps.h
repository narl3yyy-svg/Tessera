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

// Bevels the corner where two lines meet: both lines are shortened by
// `distance` and joined by a new line. Line length dimensions on the two are
// dropped. Returns empty on success (lineOut: the new line), else why not.
std::string chamferCorner(Sketch& s, int lineA, int lineB, double distance, int* lineOut = nullptr);

// Extends a line's free end nearest (x, y) to the first curve it meets,
// leaving the new end on that curve. Returns empty on success, else why not.
std::string extendLine(Sketch& s, int line, double x, double y);

// Mirror copies of `entities` across the line `mirrorLine`, tied to the
// originals with symmetry constraints (points on the mirror line are
// shared). Returns empty on success (`created`: the new entities).
std::string mirrorEntities(Sketch& s, const std::vector<int>& entities, int mirrorLine, std::vector<int>* created = nullptr);

// A placement of sketch geometry: p -> scale * R(angle) * p + (dx, dy).
struct Placement {
  double angle = 0, scale = 1, dx = 0, dy = 0;
  double cx = 0, cy = 0;   // rotation and scale centre
  Point apply(const Point& p) const;
};

// Copies of `entities` placed by `place`. Constraints among the copied
// geometry come with it when they still hold: shape relations always,
// horizontal / vertical ones when there is no turn, dimensions scaled.
// Returns empty on success (`created`: the new entities), else why not (the
// sketch is then unchanged).
std::string copyEntities(Sketch& s, const std::vector<int>& entities, const Placement& place,
                         std::vector<int>* created = nullptr);
// Moves (turns, scales) `entities` in place. Relations tying them to geometry
// that stays are dropped, as are horizontal / vertical ones when turning;
// dimensions among them scale. Returns empty on success, else why not.
std::string placeEntities(Sketch& s, const std::vector<int>& entities, const Placement& place);
// count1 x count2 copies (the originals included) along a direction at
// `angle` and across it. Returns empty on success, else why not.
std::string rectangularPattern(Sketch& s, const std::vector<int>& entities, double angle, int count1, double spacing1,
                               int count2, double spacing2, std::vector<int>* created = nullptr);
// `count` copies (the originals included) round the point `center`, spread
// over `totalAngle` (a full turn: evenly, without doubling the first).
std::string circularPattern(Sketch& s, const std::vector<int>& entities, int center, int count, double totalAngle,
                            std::vector<int>* created = nullptr);

} // namespace tsr::sketch
