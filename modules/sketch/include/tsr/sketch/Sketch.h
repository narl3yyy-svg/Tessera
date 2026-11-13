#pragma once
// tsr-sketch: 2D sketch geometry, constraints and the constraint solver.
//
// Coordinates are sketch-plane coordinates in internal units (cm). Point 0 is
// the sketch origin; it always exists and never moves, so geometry can be
// tied to it.
//
// Entities reference points by index:
//   Line    a -> b
//   Circle  center, radius
//   Arc     center, a = start, b = end, radius; runs counter-clockwise a -> b
//   Spline  fit = points the curve passes through, in order (a = first,
//           b = last; closed when first == last)
//   Ellipse center, a = the end of one axis (its direction and half
//           length), radius = the other half axis (b = -1)
#include <set>
#include <stdexcept>
#include <string>
#include <vector>

namespace tsr::sketch {

class SketchError : public std::runtime_error {
public:
  using std::runtime_error::runtime_error;
};

struct Point {
  double x = 0, y = 0;
};

enum class EntityType { Line, Circle, Arc, Spline, Ellipse };
// A spline's points: ones it passes through (Fit), the frame it is drawn
// in (Control: a cubic B-spline through its ends), or a conic's start,
// vertex (where the end tangents meet) and end (Conic: rho in `radius`).
enum class SplineKind { Fit, Control, Conic };
inline bool isRound(EntityType t) { return t == EntityType::Circle || t == EntityType::Arc; }

struct Entity {
  EntityType type = EntityType::Line;
  int a = -1, b = -1;     // line ends / arc start, end
  int center = -1;        // circle, arc
  double radius = 0;      // circle, arc
  bool construction = false;
  bool projected = false;   // copied from a body edge (drawn purple, its points fixed)
  std::vector<int> fit;   // spline fit points
  SplineKind kind = SplineKind::Fit;   // splines: what `fit` holds
};

enum class ConstraintType {
  Coincident,         // points[0], points[1]
  Horizontal,         // entities[0] (line)  or points[0], points[1]
  Vertical,           // same
  Parallel,           // entities[0], entities[1] (lines)
  Perpendicular,      // entities[0], entities[1] (lines)
  Equal,              // two lines (length) or two circles/arcs (radius)
  Tangent,            // line + circle/arc, or two circles/arcs; value 1 = internal
  PointOnEntity,      // points[0] on entities[0]
  Midpoint,           // points[0] at the middle of entities[0] (line)
  Concentric,         // entities[0], entities[1] (circles/arcs)
  Fix,                // points[0] stays at (value, value2)
  Collinear,          // entities[0], entities[1] (lines) on one infinite line
  Symmetry,           // points[0], points[1] mirror images across line entities[0]
  // Dimensions (value in cm or radians):
  Distance,           // points[0]-points[1]; or a line's length; or points[0] to line entities[0]
  HorizontalDistance, // signed x distance points[0] -> points[1] (or along a line)
  VerticalDistance,   // signed y distance
  Radius,             // entities[0]
  Diameter,           // entities[0]
  Angle,              // entities[0] -> entities[1], counter-clockwise, radians
};

struct Constraint {
  ConstraintType type = ConstraintType::Coincident;
  std::vector<int> points;
  std::vector<int> entities;
  double value = 0;
  double value2 = 0;
  // Dimensions only: the expression the value came from ("width / 2"), empty
  // for a plain number. Evaluated again when the design recomputes.
  std::string expression;
  // Dimensions only: where the value is shown, as an offset (cm) from the
  // dimension's base point (the middle of what it measures, a circle's
  // centre, the lines' crossing), so it moves with the geometry. Unset: a
  // default place next to the geometry.
  bool hasLabel = false;
  double labelX = 0, labelY = 0;
  // Dimensions only: a driven (reference) dimension shows what the geometry
  // measures and does not drive it; the solver ignores it.
  bool driven = false;
  // Dimensions only: the model parameter name (d1, d2 ... as in the familiar
  // tool), usable in other expressions. Empty: unnamed.
  std::string name;
};

bool isDimension(ConstraintType t);
const char* typeName(ConstraintType t);

// Sketch text: letters standing on a point (bottom left of the first line),
// as closed outlines that are profiles. `height` is the font size (cm),
// `angle` turns the text about its point (radians, from the sketch's X).
struct Text {
  int point = -1;
  std::string text;
  double height = 0.5;
  double angle = 0;
  std::string font;   // a font family; empty: the default sans-serif
};

class Sketch {
public:
  Sketch();

  std::vector<Point> points;     // points[0] is the origin
  std::vector<Text> texts;
  std::vector<Entity> entities;
  std::vector<Constraint> constraints;

  int addPoint(double x, double y);
  int addLine(int a, int b, bool construction = false);
  int addLine(double x1, double y1, double x2, double y2, bool construction = false);
  int addCircleAt(int center, double radius, bool construction = false);
  int addCircle(double cx, double cy, double radius, bool construction = false);
  int addArc(int center, int start, int end, bool construction = false);
  // A smooth curve through the points (at least 2). Closed if the first and
  // last are the same point.
  int addSpline(const std::vector<int>& fitPoints, bool construction = false, SplineKind kind = SplineKind::Fit);
  // A conic from `start` to `end` whose end tangents meet at `vertex`;
  // rho in (0, 1): below 0.5 an ellipse's arc, 0.5 a parabola, above a hyperbola.
  int addConic(int start, int vertex, int end, double rho, bool construction = false);
  int addEllipse(int center, int axisEnd, double otherRadius, bool construction = false);
  int addText(int point, const std::string& text, double height, double angle = 0, const std::string& font = {});
  int addConstraint(Constraint c);   // no solving; see SolveResult / addConstraintChecked

  // Removes entities (and constraints that reference them), then the points
  // they owned that nothing else uses. Indices of the remaining items are
  // compacted.
  void removeEntities(std::vector<int> ids);
  // Removes points (never the origin), the entities built on them and the
  // constraints that reference any of those.
  void removePoints(std::vector<int> ids);
  // Both at once (indices refer to the sketch before the call).
  void removeItems(const std::vector<int>& entities, const std::vector<int>& points);
  void removeConstraint(int index);

  // Points an entity owns, in order (line: a, b; circle: center; arc: center, a, b).
  std::vector<int> entityPoints(int entity) const;

  std::string toJson() const;
  static Sketch fromJson(const std::string& text);   // empty text -> empty sketch; throws SketchError

  void checkIndices() const;   // throws SketchError on a dangling reference

private:
  void removeImpl(const std::set<int>& entities, const std::set<int>& points);
};

struct SolveResult {
  bool ok = false;
  int dof = 0;                        // remaining degrees of freedom
  int iterations = 0;
  double residual = 0;
  std::vector<bool> pointFixed;       // fully determined by constraints
  std::vector<bool> entityFixed;
  std::string message;
};

// Moves geometry to satisfy every constraint, changing it as little as
// possible. `locked` points keep their current position (used while dragging).
// On failure the sketch is left unchanged and ok is false.
SolveResult solve(Sketch& s, const std::vector<int>& locked = {});

// Adds a constraint only if the sketch stays solvable and the constraint
// actually removes a degree of freedom. Returns empty on success, else why not.
std::string addConstraintChecked(Sketch& s, const Constraint& c);

} // namespace tsr::sketch
