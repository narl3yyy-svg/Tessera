#include "TestFramework.h"
#include "tsr/sketch/Sketch.h"
#include "tsr/sketch/SketchGeometry.h"
#include "tsr/sketch/SketchOps.h"

#include <cmath>

using namespace tsr::sketch;

namespace {
constexpr double kPi = 3.14159265358979323846;

Constraint C(ConstraintType t, std::vector<int> p, std::vector<int> e = {}, double v = 0) {
  Constraint c;
  c.type = t;
  c.points = std::move(p);
  c.entities = std::move(e);
  c.value = v;
  return c;
}

// Rectangle as 4 lines sharing corner points, roughly drawn.
struct Rect {
  int p[4];
  int l[4];
};
Rect rect(Sketch& s, double x0, double y0, double x1, double y1) {
  Rect r;
  r.p[0] = s.addPoint(x0, y0);
  r.p[1] = s.addPoint(x1, y0);
  r.p[2] = s.addPoint(x1, y1);
  r.p[3] = s.addPoint(x0, y1);
  for (int i = 0; i < 4; ++i) r.l[i] = s.addLine(r.p[i], r.p[(i + 1) % 4]);
  return r;
}
} // namespace

TEST(sketch_rectangle_fully_constrained) {
  Sketch s;
  Rect r = rect(s, 0.1, -0.05, 2.9, 2.1);
  CHECK_EQ(solve(s).dof, 8);
  s.addConstraint(C(ConstraintType::Coincident, {0, r.p[0]}));
  s.addConstraint(C(ConstraintType::Horizontal, {}, {r.l[0]}));
  s.addConstraint(C(ConstraintType::Horizontal, {}, {r.l[2]}));
  s.addConstraint(C(ConstraintType::Vertical, {}, {r.l[1]}));
  s.addConstraint(C(ConstraintType::Vertical, {}, {r.l[3]}));
  auto res = solve(s);
  CHECK(res.ok);
  CHECK_EQ(res.dof, 2);
  CHECK(!res.entityFixed[r.l[0]]);
  s.addConstraint(C(ConstraintType::Distance, {}, {r.l[0]}, 3.0));
  s.addConstraint(C(ConstraintType::Distance, {}, {r.l[1]}, 2.0));
  res = solve(s);
  CHECK(res.ok);
  CHECK_EQ(res.dof, 0);
  for (int l : r.l) CHECK(res.entityFixed[l]);
  CHECK_NEAR(s.points[r.p[2]].x, 3.0, 1e-9);
  CHECK_NEAR(s.points[r.p[2]].y, 2.0, 1e-9);
  CHECK_NEAR(s.points[r.p[0]].x, 0.0, 1e-12);
}

TEST(sketch_minimal_change_and_conflicts) {
  Sketch s;
  const int l = s.addLine(1, 1, 4, 1.2);
  s.addConstraint(C(ConstraintType::Horizontal, {}, {l}));
  CHECK(solve(s).ok);
  // Gauss-Newton with minimum-norm steps barely moves an under-constrained line.
  CHECK_NEAR(s.points[1].y, 1.1, 1e-6);
  CHECK_NEAR(s.points[2].y, 1.1, 1e-6);
  CHECK_NEAR(s.points[1].x, 1.0, 1e-6);

  // Vertical on a horizontal line conflicts unless the line collapses; a
  // length dimension makes it a real conflict.
  CHECK_EQ(addConstraintChecked(s, C(ConstraintType::Distance, {}, {l}, 3.0)), std::string());
  const std::string err = addConstraintChecked(s, C(ConstraintType::Vertical, {}, {l}));
  CHECK(!err.empty());
  CHECK_EQ(s.constraints.size(), size_t(2));
  // Redundant: horizontal twice.
  CHECK(!addConstraintChecked(s, C(ConstraintType::Horizontal, {}, {l})).empty());
}

TEST(sketch_circles_arcs_tangent) {
  Sketch s;
  const int c = s.addCircle(2, 2, 0.7);
  s.addConstraint(C(ConstraintType::Coincident, {0, s.entities[c].center}));
  s.addConstraint(C(ConstraintType::Diameter, {}, {c}, 3.0));
  auto res = solve(s);
  CHECK(res.ok);
  CHECK_EQ(res.dof, 0);
  CHECK_NEAR(s.entities[c].radius, 1.5, 1e-9);

  const int l = s.addLine(-3, 1.4, 3, 1.6);
  s.addConstraint(C(ConstraintType::Horizontal, {}, {l}));
  s.addConstraint(C(ConstraintType::Tangent, {}, {l, c}));
  CHECK(solve(s).ok);
  CHECK_NEAR(s.points[s.entities[l].a].y, 1.5, 1e-8);

  // Quarter arc from (2,0) to (0,2) about the origin-ish centre.
  const int ce = s.addPoint(0.1, 0.1), a = s.addPoint(2, 0), b = s.addPoint(0, 2);
  const int arc = s.addArc(ce, a, b);
  s.addConstraint(C(ConstraintType::Radius, {}, {arc}, 2.5));
  CHECK(solve(s).ok);
  CHECK_NEAR(std::hypot(s.points[a].x - s.points[ce].x, s.points[a].y - s.points[ce].y), 2.5, 1e-8);
  CHECK_NEAR(std::hypot(s.points[b].x - s.points[ce].x, s.points[b].y - s.points[ce].y), 2.5, 1e-8);

  const int l2 = s.addLine(0, 0, 3, 0.2), l3 = s.addLine(0, 0, 0.1, 3);
  s.addConstraint(C(ConstraintType::Angle, {}, {l2, l3}, kPi / 3));
  CHECK(solve(s).ok);
  double x1 = s.points[s.entities[l2].b].x - s.points[s.entities[l2].a].x;
  double y1 = s.points[s.entities[l2].b].y - s.points[s.entities[l2].a].y;
  double x2 = s.points[s.entities[l3].b].x - s.points[s.entities[l3].a].x;
  double y2 = s.points[s.entities[l3].b].y - s.points[s.entities[l3].a].y;
  CHECK_NEAR(std::atan2(x1 * y2 - y1 * x2, x1 * x2 + y1 * y2), kPi / 3, 1e-8);
}

TEST(sketch_json_round_trip_and_remove) {
  Sketch s;
  Rect r = rect(s, 0, 0, 3, 2);
  const int c = s.addCircle(1.5, 1, 0.5, true);
  s.addConstraint(C(ConstraintType::Horizontal, {}, {r.l[0]}));
  s.addConstraint(C(ConstraintType::Diameter, {}, {c}, 1.0));
  const Sketch t = Sketch::fromJson(s.toJson());
  CHECK_EQ(t.points.size(), s.points.size());
  CHECK_EQ(t.entities.size(), size_t(5));
  CHECK(t.entities[c].construction);
  CHECK_EQ(t.constraints.size(), size_t(2));
  CHECK_NEAR(t.constraints[1].value, 1.0, 0);
  CHECK_EQ(t.toJson(), s.toJson());
  CHECK_THROWS(Sketch::fromJson("{\"entities\":[{\"type\":\"line\",\"p\":[0,7]}]}"));

  Sketch u = t;
  u.removeEntities({r.l[0]});   // drops the horizontal constraint too
  CHECK_EQ(u.entities.size(), size_t(4));
  CHECK_EQ(u.constraints.size(), size_t(1));
  CHECK_EQ(u.points.size(), t.points.size()); // corners still used by other lines
  u.removeEntities({c - 1}); // indices compacted by the first removal
  CHECK(u.constraints.empty());
  CHECK_EQ(u.points.size(), t.points.size() - 1);
  u.checkIndices();
}

TEST(sketch_profiles) {
  Sketch s;
  rect(s, 0, 0, 4, 3);
  s.addCircle(2, 1.5, 0.5);
  s.addLine(5, 0, 6, 1);   // dangling line: no region
  const gp_Ax3 f = planeFrame("XY");
  auto ps = profiles(s, f);
  CHECK_EQ(ps.size(), size_t(2));
  CHECK_NEAR(ps[0].area, 12 - kPi * 0.25, 1e-6);
  CHECK_NEAR(ps[1].area, kPi * 0.25, 1e-6);
  CHECK_EQ(profileAt(ps, f, 2, 1.5), 1);
  CHECK_EQ(profileAt(ps, f, 0.3, 0.3), 0);
  CHECK_EQ(profileAt(ps, f, 9, 9), -1);
  CHECK_EQ(profileAt(ps, f, ps[0].x, ps[0].y), 0);

  // Two overlapping rectangles: three regions.
  Sketch o;
  rect(o, 0, 0, 2, 2);
  rect(o, 1, 1, 3, 3);
  CHECK_EQ(profiles(o, f).size(), size_t(3));

  // Construction geometry does not make profiles; other planes work.
  Sketch k;
  k.addCircle(0, 0, 1, true);
  CHECK(profiles(k, f).empty());
  Sketch d;
  d.addCircle(1, 2, 1);
  const gp_Ax3 xz = planeFrame("XZ", 0.5);
  auto pd = profiles(d, xz);
  CHECK_EQ(pd.size(), size_t(1));
  const gp_Pnt c = toWorld(xz, 1, 2);
  CHECK_NEAR(c.X(), 1, 1e-12);
  CHECK_NEAR(c.Y(), -0.5, 1e-12);
  CHECK_NEAR(c.Z(), 2, 1e-12);
  CHECK_THROWS(planeFrame("QQ"));
  const gp_Ax3 back = planeFrame(customPlaneSpec(xz));
  CHECK(back.Location().Distance(xz.Location()) < 1e-9);
}

TEST(sketch_remove_points_keeps_standalone_points) {
  Sketch s;
  const int lone = s.addPoint(5, 5);
  const int l = s.addLine(0, 0, 1, 1);
  const int c = s.addCircle(3, 3, 1);
  Constraint fix;
  fix.type = ConstraintType::Fix;
  fix.points = {lone};
  fix.value = 5;
  fix.value2 = 5;
  s.addConstraint(fix);
  s.removeEntities({l});
  CHECK_EQ(s.points.size(), size_t(3));   // origin, lone point, circle centre
  CHECK_EQ(s.constraints.size(), size_t(1));
  CHECK_NEAR(s.points[1].x, 5, 0);
  s.removePoints({s.entities[c - 1].center});   // removes the circle with its centre
  CHECK(s.entities.empty());
  CHECK_EQ(s.points.size(), size_t(2));
  s.removePoints({1});
  CHECK_EQ(s.points.size(), size_t(1));
  CHECK(s.constraints.empty());
  s.removePoints({0});   // the origin stays
  CHECK_EQ(s.points.size(), size_t(1));
}

TEST(sketch_collinear_and_symmetry) {
  Sketch s;
  const int a = s.addLine(0, 0, 2, 0.1);
  const int b = s.addLine(3, 0.5, 5, 0.7);
  s.addConstraint(C(ConstraintType::Collinear, {}, {a, b}));
  CHECK(solve(s).ok);
  const auto& la = s.entities[a];
  const auto& lb = s.entities[b];
  auto cross = [&](int p) {
    const double dx = s.points[la.b].x - s.points[la.a].x, dy = s.points[la.b].y - s.points[la.a].y;
    return dx * (s.points[p].y - s.points[la.a].y) - dy * (s.points[p].x - s.points[la.a].x);
  };
  CHECK_NEAR(cross(lb.a), 0, 1e-8);
  CHECK_NEAR(cross(lb.b), 0, 1e-8);

  Sketch t;
  const int axis = t.addLine(0, -2, 0.01, 2, true);
  const int p = t.addPoint(-1.2, 0.5), q = t.addPoint(0.9, 0.7);
  t.addConstraint(C(ConstraintType::Vertical, {}, {axis}));
  t.addConstraint(C(ConstraintType::Symmetry, {p, q}, {axis}));
  CHECK(solve(t).ok);
  CHECK_NEAR(t.points[p].x + t.points[q].x, 2 * t.points[t.entities[axis].a].x, 1e-8);
  CHECK_NEAR(t.points[p].y, t.points[q].y, 1e-8);
}

// ---------------------------------------------------------------------------
// Spline, Fillet, Offset

TEST(sketch_spline_round_trip_and_profile) {
  Sketch s;
  std::vector<int> fit;
  for (auto [x, y] : {std::pair{0.0, 0.0}, {2.0, -0.5}, {3.0, 1.5}, {1.0, 2.5}}) fit.push_back(s.addPoint(x, y));
  fit.push_back(fit.front());   // closed
  const int sp = s.addSpline(fit);
  const Sketch back = Sketch::fromJson(s.toJson());
  CHECK(back.entities[sp].type == EntityType::Spline);
  CHECK_EQ(back.entities[sp].fit.size(), size_t(5));
  CHECK(solve(s).ok);
  const gp_Ax3 xy = planeFrame("XY");
  CHECK(!curve(s, xy, sp).IsNull());
  const auto ps = profiles(s, xy);
  CHECK_EQ(ps.size(), size_t(1));
  CHECK(ps[0].area > 3.0);
  // Dragging a fit point moves the curve; constraints on the spline itself are refused.
  CHECK(!addConstraintChecked(s, C(ConstraintType::Horizontal, {}, {sp})).empty());
}

TEST(sketch_fillet_corner) {
  Sketch s;
  const Rect r = rect(s, 0, 0, 4, 3);
  s.addConstraint(C(ConstraintType::Distance, {}, {r.l[0]}, 4));
  CHECK(solve(s).ok);
  int arc = -1;
  CHECK_EQ(filletCorner(s, r.l[0], r.l[1], 0.5, &arc), std::string());
  CHECK(arc >= 0 && s.entities[arc].type == EntityType::Arc);
  CHECK_NEAR(s.entities[arc].radius, 0.5, 1e-6);
  const auto ps = profiles(s, planeFrame("XY"));
  CHECK_EQ(ps.size(), size_t(1));
  CHECK_NEAR(ps[0].area, 12 - (1 - kPi / 4) * 0.25, 1e-4);
  // Too large a radius leaves the sketch unchanged.
  const size_t before = s.entities.size();
  CHECK(!filletCorner(s, r.l[2], r.l[3], 5.0).empty());
  CHECK_EQ(s.entities.size(), before);
  // A corner found from its point.
  const auto corner = cornerAt(s, s.entities[r.l[2]].b);
  CHECK(corner.has_value());
}

TEST(sketch_offset_chain) {
  Sketch s;
  const Rect r = rect(s, 0, 0, 4, 3);
  CHECK(solve(s).ok);
  bool closed = false;
  CHECK_EQ(chainOf(s, r.l[1], &closed).size(), size_t(4));
  CHECK(closed);
  std::vector<int> made;
  CHECK_EQ(offsetChain(s, r.l[2], 1.0, &made), std::string());   // outward
  CHECK_EQ(made.size(), size_t(4));
  const auto ps = profiles(s, planeFrame("XY"));
  CHECK_EQ(ps.size(), size_t(2));   // the ring and the inner rectangle
  CHECK_NEAR(ps[0].area + ps[1].area, 6 * 5, 1e-6);
  CHECK_EQ(offsetChain(s, r.l[0], -1.0, &made), std::string());   // inward
  // A circle grows concentrically.
  Sketch c;
  const int circle = c.addCircle(1, 1, 2);
  CHECK_EQ(offsetChain(c, circle, 0.5, &made), std::string());
  CHECK_NEAR(c.entities[made[0]].radius, 2.5, 1e-9);
  CHECK(!offsetChain(c, circle, -3, &made).empty());
}

TEST(sketch_tangent_at_shared_end_is_a_real_constraint) {
  // A line ending where an arc starts, already tangent: the constraint must
  // still count (it fixes the arc's centre to the line's normal there).
  Sketch s;
  const int a = s.addPoint(0, 0), b = s.addPoint(4, 0), c = s.addPoint(4, 2), e = s.addPoint(6, 2);
  const int line = s.addLine(a, b);
  const int arc = s.addArc(c, b, e);
  CHECK(solve(s).ok);
  CHECK_EQ(addConstraintChecked(s, C(ConstraintType::Tangent, {}, {line, arc})), std::string());
  // Drag the arc's end: it stays tangent (radius at the shared end is
  // perpendicular to the line).
  s.points[e] = {6.5, 3};
  CHECK(solve(s, {e}).ok);
  const double dot = (s.points[c].x - s.points[b].x) * (s.points[b].x - s.points[a].x) +
                     (s.points[c].y - s.points[b].y) * (s.points[b].y - s.points[a].y);
  CHECK_NEAR(dot, 0.0, 1e-7);
}

TEST(sketch_chamfer_corner) {
  Sketch s;
  const Rect r = rect(s, 0, 0, 4, 3);
  CHECK(solve(s).ok);
  int line = -1;
  CHECK_EQ(chamferCorner(s, r.l[0], r.l[1], 0.5, &line), std::string());
  CHECK(line >= 0);
  const auto ps = profiles(s, planeFrame("XY"));
  CHECK_EQ(ps.size(), size_t(1));
  CHECK_NEAR(ps[0].area, 12 - 0.125, 1e-6);
  CHECK(!chamferCorner(s, r.l[2], r.l[3], 9.0).empty());
}

TEST(sketch_extend_line) {
  Sketch s;
  const int wall = s.addLine(5, -1, 5, 5);   // a vertical line at x = 5
  const int l = s.addLine(0, 1, 2, 1);       // stops short of it
  const int c = s.addCircle(-3, 1, 1);       // a circle on the other side
  CHECK(solve(s).ok);
  CHECK_EQ(extendLine(s, l, 1.9, 1), std::string());
  CHECK_NEAR(s.points[s.entities[l].b].x, 5.0, 1e-7);
  CHECK_EQ(extendLine(s, l, 0.1, 1), std::string());   // the other end reaches the circle
  CHECK_NEAR(s.points[s.entities[l].a].x, -2.0, 1e-7);
  (void)wall;
  (void)c;
}

TEST(sketch_mirror) {
  Sketch s;
  const int axis = s.addLine(0, -5, 0, 5, true);   // the Y axis, construction, held in place
  for (int q : {s.entities[axis].a, s.entities[axis].b}) s.addConstraint(C(ConstraintType::Fix, {q}, {}, 0));
  s.constraints[0].value2 = -5;
  s.constraints[1].value2 = 5;
  const int a = s.addLine(1, 0, 3, 2);
  const int arc = s.addArc(s.addPoint(2, -2), s.addPoint(3, -2), s.addPoint(2, -1));
  std::vector<int> made;
  CHECK_EQ(mirrorEntities(s, {a, arc}, axis, &made), std::string());
  CHECK_EQ(made.size(), size_t(2));
  const auto& m = s.entities[made[0]];
  CHECK_NEAR(s.points[m.a].x, -1.0, 1e-7);
  CHECK_NEAR(s.points[m.b].x, -3.0, 1e-7);
  CHECK_NEAR(s.points[m.b].y, 2.0, 1e-7);
  // Moving an original moves its mirror.
  s.points[s.entities[a].b] = {4, 2};
  CHECK(solve(s, {s.entities[a].b}).ok);
  CHECK_NEAR(s.points[m.b].x, -4.0, 1e-6);
}
