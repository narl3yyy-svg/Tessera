// Sketch constraint solver.
//
// Unknowns: x, y of every point except the origin and locked points, and the
// radius of every circle/arc. Each constraint contributes one or two residual
// equations. Gauss-Newton with minimum-norm steps (complete orthogonal
// decomposition) moves the geometry as little as possible, which is what
// makes an under-constrained sketch keep its drawn shape. The Jacobian is
// numeric (central differences); sketches are small.
//
// Degrees of freedom: n - rank(J). A parameter is fully determined when its
// row of the Jacobian's null space is zero.
#include "tsr/sketch/Sketch.h"

#include <Eigen/Dense>

#include <cmath>
#include <set>

namespace tsr::sketch {

namespace {

constexpr double kPi = 3.14159265358979323846;
constexpr double kTol = 1e-10;   // residual (cm / rad)
constexpr double kRankTol = 1e-7;

struct Layout {
  std::vector<int> px, py;   // param index per point, -1 if not a parameter
  std::vector<int> rad;      // param index per entity radius, -1 if none
  int n = 0;
};

Layout makeLayout(const Sketch& s, const std::set<int>& locked) {
  Layout L;
  L.px.assign(s.points.size(), -1);
  L.py.assign(s.points.size(), -1);
  L.rad.assign(s.entities.size(), -1);
  for (size_t i = 1; i < s.points.size(); ++i)
    if (!locked.count(static_cast<int>(i))) {
      L.px[i] = L.n++;
      L.py[i] = L.n++;
    }
  for (size_t i = 0; i < s.entities.size(); ++i)
    if (isRound(s.entities[i].type) || s.entities[i].type == EntityType::Ellipse) L.rad[i] = L.n++;
  return L;
}

Eigen::VectorXd pack(const Sketch& s, const Layout& L) {
  Eigen::VectorXd q(L.n);
  for (size_t i = 0; i < s.points.size(); ++i) {
    if (L.px[i] >= 0) q[L.px[i]] = s.points[i].x;
    if (L.py[i] >= 0) q[L.py[i]] = s.points[i].y;
  }
  for (size_t i = 0; i < s.entities.size(); ++i)
    if (L.rad[i] >= 0) q[L.rad[i]] = s.entities[i].radius;
  return q;
}

void unpack(Sketch& s, const Layout& L, const Eigen::VectorXd& q) {
  for (size_t i = 0; i < s.points.size(); ++i) {
    if (L.px[i] >= 0) s.points[i].x = q[L.px[i]];
    if (L.py[i] >= 0) s.points[i].y = q[L.py[i]];
  }
  for (size_t i = 0; i < s.entities.size(); ++i)
    if (L.rad[i] >= 0) s.entities[i].radius = q[L.rad[i]];
}

double wrapAngle(double a) {
  // remainder, not a loop: a huge typed angle must not spin forever.
  return std::isfinite(a) ? std::remainder(a, 2 * kPi) : a;
}

// Evaluates every residual for the geometry in `s`.
class Residuals {
public:
  explicit Residuals(const Sketch& s) : s_(s) {}

  std::vector<double> operator()() const {
    std::vector<double> r;
    // Arcs: both ends lie on the arc's circle.
    for (size_t i = 0; i < s_.entities.size(); ++i) {
      const Entity& e = s_.entities[i];
      if (e.type != EntityType::Arc) continue;
      r.push_back(dist(e.a, e.center) - e.radius);
      r.push_back(dist(e.b, e.center) - e.radius);
    }
    // Elliptical arcs: both ends lie on the ellipse.
    for (size_t i = 0; i < s_.entities.size(); ++i)
      if (s_.entities[i].isEllipticalArc())
        for (int p : s_.entities[i].fit) r.push_back(onEllipse(p, static_cast<int>(i)));
    for (const auto& c : s_.constraints) add(c, r);
    return r;
  }

  // Number of residual rows a constraint contributes.
  int rows(const Constraint& c) const {
    std::vector<double> r;
    add(c, r);
    return static_cast<int>(r.size());
  }

private:
  const Point& P(int i) const { return s_.points.at(i); }
  const Entity& E(int i) const { return s_.entities.at(i); }
  double dist(int a, int b) const { return std::hypot(P(a).x - P(b).x, P(a).y - P(b).y); }
  void dir(int line, double& dx, double& dy) const {
    const Entity& e = E(line);
    dx = P(e.b).x - P(e.a).x;
    dy = P(e.b).y - P(e.a).y;
  }
  double len(int line) const {
    double dx, dy;
    dir(line, dx, dy);
    return std::hypot(dx, dy);
  }
  double pointLineDistance(int p, int line) const {   // signed
    double dx, dy;
    dir(line, dx, dy);
    const double l = std::max(std::hypot(dx, dy), 1e-12);
    const Point& a = P(E(line).a);
    return (dx * (P(p).y - a.y) - dy * (P(p).x - a.x)) / l;
  }
  bool isRound(int e) const { return sketch::isRound(E(e).type); }
  // How far a point is off an ellipse: in its own axes (s/A)^2 + (t/B)^2 = 1,
  // scaled to a distance.
  double onEllipse(int p, int ellipse) const {
    const Entity& el = E(ellipse);
    const double ux = P(el.a).x - P(el.center).x, uy = P(el.a).y - P(el.center).y;
    const double A = std::max(std::hypot(ux, uy), 1e-12), B = std::max(std::abs(el.radius), 1e-12);
    const double dx = P(p).x - P(el.center).x, dy = P(p).y - P(el.center).y;
    const double s = (dx * ux + dy * uy) / A, t = (-dx * uy + dy * ux) / A;
    return (std::hypot(s / A, t / B) - 1) * std::min(A, B);
  }
  // An end point two lines/arcs have in common, or -1.
  int sharedEnd(int e0, int e1) const {
    const Entity &a = E(e0), &b = E(e1);
    if (a.type == EntityType::Circle || b.type == EntityType::Circle) return -1;
    for (int p : {a.a, a.b})
      if (p >= 0 && (p == b.a || p == b.b)) return p;
    return -1;
  }

  // Two points from a constraint: explicit points, or a line's ends.
  bool pointPair(const Constraint& c, int& a, int& b) const {
    if (c.points.size() >= 2) {
      a = c.points[0];
      b = c.points[1];
      return true;
    }
    if (c.entities.size() == 1 && E(c.entities[0]).type == EntityType::Line) {
      a = E(c.entities[0]).a;
      b = E(c.entities[0]).b;
      return true;
    }
    return false;
  }

  void add(const Constraint& c, std::vector<double>& r) const {
    if (c.driven) return;   // reference only: it follows the geometry
    const auto& p = c.points;
    const auto& e = c.entities;
    auto bad = [&] { throw SketchError(std::string("malformed '") + typeName(c.type) + "' constraint"); };
    // Splines follow their fit points; constraints act on those points only.
    for (int i : e)
      if (E(i).type == EntityType::Spline)
        throw SketchError(std::string("'") + typeName(c.type) + "' cannot apply to a spline; constrain its points");
    // Ellipses: a point can lie on one; other relations act on its centre
    // and axis point.
    for (int i : e)
      if (E(i).type == EntityType::Ellipse && c.type != ConstraintType::PointOnEntity && c.type != ConstraintType::Radius)
        throw SketchError(std::string("'") + typeName(c.type) + "' cannot apply to an ellipse; constrain its centre and axis point");
    switch (c.type) {
      case ConstraintType::Coincident:
        if (p.size() != 2) bad();
        r.push_back(P(p[0]).x - P(p[1]).x);
        r.push_back(P(p[0]).y - P(p[1]).y);
        return;
      case ConstraintType::Horizontal:
      case ConstraintType::Vertical: {
        int a, b;
        if (!pointPair(c, a, b)) bad();
        r.push_back(c.type == ConstraintType::Horizontal ? P(b).y - P(a).y : P(b).x - P(a).x);
        return;
      }
      case ConstraintType::Parallel:
      case ConstraintType::Perpendicular: {
        if (e.size() != 2) bad();
        double x1, y1, x2, y2;
        dir(e[0], x1, y1);
        dir(e[1], x2, y2);
        const double n = std::max(std::hypot(x1, y1) * std::hypot(x2, y2), 1e-12);
        r.push_back(c.type == ConstraintType::Parallel ? (x1 * y2 - y1 * x2) / n : (x1 * x2 + y1 * y2) / n);
        return;
      }
      case ConstraintType::Equal:
        if (e.size() != 2) bad();
        if (isRound(e[0]) && isRound(e[1])) r.push_back(E(e[0]).radius - E(e[1]).radius);
        else if (!isRound(e[0]) && !isRound(e[1])) r.push_back(len(e[0]) - len(e[1]));
        else bad();
        return;
      case ConstraintType::Tangent: {
        if (e.size() != 2) bad();
        const bool r0 = isRound(e[0]), r1 = isRound(e[1]);
        // Curves that share an end point: at that point the radius is
        // perpendicular to the line (or both centres lie on one line through
        // it). The distance form below is redundant at first order there, so
        // the solver would not see the constraint at all.
        if (const int sp = sharedEnd(e[0], e[1]); sp >= 0) {
          const Point& q = P(sp);
          if (r0 != r1) {
            const int line = r0 ? e[1] : e[0];
            const Point& c0 = P(E(r0 ? e[0] : e[1]).center);
            double dx, dy;
            dir(line, dx, dy);
            const double l = std::max(std::hypot(dx, dy), 1e-12);
            r.push_back(((c0.x - q.x) * dx + (c0.y - q.y) * dy) / l);
            return;
          }
          if (r0 && r1) {
            const Point& c0 = P(E(e[0]).center);
            const Point& c1 = P(E(e[1]).center);
            const double l = std::max(std::max(E(e[0]).radius, E(e[1]).radius), 1e-12);
            r.push_back(((c0.x - q.x) * (c1.y - q.y) - (c0.y - q.y) * (c1.x - q.x)) / l);
            return;
          }
        }
        if (r0 && r1) {
          const double d = dist(E(e[0]).center, E(e[1]).center);
          r.push_back(c.value != 0 ? d - std::abs(E(e[0]).radius - E(e[1]).radius) : d - (E(e[0]).radius + E(e[1]).radius));
        } else if (r0 != r1) {
          const int line = r0 ? e[1] : e[0];
          const int circ = r0 ? e[0] : e[1];
          r.push_back(std::abs(pointLineDistance(E(circ).center, line)) - E(circ).radius);
        } else {
          bad();
        }
        return;
      }
      case ConstraintType::PointOnEntity:
        if (p.size() != 1 || e.size() != 1) bad();
        if (isRound(e[0])) {
          r.push_back(dist(p[0], E(e[0]).center) - E(e[0]).radius);
        } else if (E(e[0]).type == EntityType::Ellipse) {
          r.push_back(onEllipse(p[0], e[0]));
        } else {
          r.push_back(pointLineDistance(p[0], e[0]));
        }
        return;
      case ConstraintType::Midpoint: {
        if (p.size() != 1 || e.size() != 1 || isRound(e[0])) bad();
        const Entity& l = E(e[0]);
        r.push_back(P(p[0]).x - (P(l.a).x + P(l.b).x) / 2);
        r.push_back(P(p[0]).y - (P(l.a).y + P(l.b).y) / 2);
        return;
      }
      case ConstraintType::Concentric:
        if (e.size() != 2 || !isRound(e[0]) || !isRound(e[1])) bad();
        r.push_back(P(E(e[0]).center).x - P(E(e[1]).center).x);
        r.push_back(P(E(e[0]).center).y - P(E(e[1]).center).y);
        return;
      case ConstraintType::Collinear: {
        if (e.size() != 2 || isRound(e[0]) || isRound(e[1])) bad();
        r.push_back(pointLineDistance(E(e[1]).a, e[0]));
        r.push_back(pointLineDistance(E(e[1]).b, e[0]));
        return;
      }
      case ConstraintType::Symmetry: {
        if (p.size() != 2 || e.size() != 1 || isRound(e[0])) bad();
        // The midpoint lies on the line and the pair is perpendicular to it.
        const Entity& l = E(e[0]);
        double dx, dy;
        dir(e[0], dx, dy);
        const double n = std::max(std::hypot(dx, dy), 1e-12);
        const double mx = (P(p[0]).x + P(p[1]).x) / 2, my = (P(p[0]).y + P(p[1]).y) / 2;
        r.push_back((dx * (my - P(l.a).y) - dy * (mx - P(l.a).x)) / n);
        r.push_back((dx * (P(p[1]).x - P(p[0]).x) + dy * (P(p[1]).y - P(p[0]).y)) / n);
        return;
      }
      case ConstraintType::Fix:
        if (p.size() != 1) bad();
        r.push_back(P(p[0]).x - c.value);
        r.push_back(P(p[0]).y - c.value2);
        return;
      case ConstraintType::Distance: {
        if (p.size() == 1 && e.size() == 1 && !isRound(e[0])) {
          r.push_back(std::abs(pointLineDistance(p[0], e[0])) - c.value);
          return;
        }
        int a, b;
        if (!pointPair(c, a, b)) bad();
        r.push_back(dist(a, b) - c.value);
        return;
      }
      case ConstraintType::HorizontalDistance:
      case ConstraintType::VerticalDistance: {
        int a, b;
        if (!pointPair(c, a, b)) bad();
        r.push_back((c.type == ConstraintType::HorizontalDistance ? P(b).x - P(a).x : P(b).y - P(a).y) - c.value);
        return;
      }
      case ConstraintType::Radius:
      case ConstraintType::Diameter:
        // An ellipse's radius is its second half axis (the first is the
        // distance from the centre to its axis point).
        if (e.size() != 1 || !(isRound(e[0]) || (E(e[0]).type == EntityType::Ellipse && c.type == ConstraintType::Radius))) bad();
        r.push_back((c.type == ConstraintType::Diameter ? 2 : 1) * E(e[0]).radius - c.value);
        return;
      case ConstraintType::Angle: {
        if (e.size() != 2) bad();
        double x1, y1, x2, y2;
        dir(e[0], x1, y1);
        dir(e[1], x2, y2);
        r.push_back(wrapAngle(std::atan2(x1 * y2 - y1 * x2, x1 * x2 + y1 * y2) - c.value));
        return;
      }
    }
    bad();
  }

  const Sketch& s_;
};

struct System {
  Sketch& s;
  Layout L;

  Eigen::VectorXd residual(const Eigen::VectorXd& q) {
    unpack(s, L, q);
    const auto r = Residuals(s)();
    return Eigen::Map<const Eigen::VectorXd>(r.data(), static_cast<Eigen::Index>(r.size()));
  }

  Eigen::MatrixXd jacobian(const Eigen::VectorXd& q, Eigen::Index m) {
    Eigen::MatrixXd J(m, L.n);
    Eigen::VectorXd qq = q;
    for (int j = 0; j < L.n; ++j) {
      const double h = 1e-7 * std::max(1.0, std::abs(q[j]));
      qq[j] = q[j] + h;
      const Eigen::VectorXd rp = residual(qq);
      qq[j] = q[j] - h;
      const Eigen::VectorXd rm = residual(qq);
      qq[j] = q[j];
      J.col(j) = (rp - rm) / (2 * h);
    }
    unpack(s, L, q);
    return J;
  }
};

} // namespace

SolveResult solve(Sketch& s, const std::vector<int>& lockedList) {
  SolveResult res;
  s.checkIndices();
  const Sketch original = s;
  System sys{s, makeLayout(s, std::set<int>(lockedList.begin(), lockedList.end()))};
  Eigen::VectorXd q = pack(s, sys.L);

  Eigen::VectorXd r;
  try {
    r = sys.residual(q);
  } catch (const SketchError& e) {
    s = original;
    res.message = e.what();
    return res;
  }
  const Eigen::Index m = r.size();

  for (res.iterations = 0; res.iterations < 100; ++res.iterations) {
    if (m == 0 || r.lpNorm<Eigen::Infinity>() < kTol) break;
    const Eigen::MatrixXd J = sys.jacobian(q, m);
    const Eigen::VectorXd step = J.completeOrthogonalDecomposition().solve(-r);
    // Backtracking: accept the first step length that reduces the residual.
    double t = 1.0;
    Eigen::VectorXd qn, rn;
    for (;;) {
      qn = q + t * step;
      rn = sys.residual(qn);
      if (rn.norm() < r.norm() || t < 1e-6) break;
      t /= 2;
    }
    if (rn.norm() >= r.norm()) break; // stalled
    q = qn;
    r = rn;
  }

  res.residual = m ? r.lpNorm<Eigen::Infinity>() : 0.0;
  if (res.residual > 1e-8) {
    s = original;
    res.message = "The sketch constraints conflict; they cannot all be met.";
    return res;
  }
  unpack(s, sys.L, q);
  // Keep radii positive (a negative radius solves the equations too).
  for (auto& e : s.entities) e.radius = std::abs(e.radius);
  res.ok = true;

  // Degrees of freedom and which items are fully determined.
  res.pointFixed.assign(s.points.size(), true);
  res.entityFixed.assign(s.entities.size(), true);
  if (sys.L.n == 0) return res;
  Eigen::MatrixXd J = m ? sys.jacobian(q, m) : Eigen::MatrixXd::Zero(1, sys.L.n);
  Eigen::JacobiSVD<Eigen::MatrixXd> svd(J, Eigen::ComputeFullV);
  const auto& sv = svd.singularValues();
  int rank = 0;
  for (Eigen::Index i = 0; i < sv.size(); ++i)
    if (sv[i] > kRankTol) ++rank;
  res.dof = sys.L.n - rank;
  const Eigen::MatrixXd null = svd.matrixV().rightCols(res.dof);
  auto determined = [&](int param) { return param < 0 || null.row(param).norm() < 1e-6; };
  for (size_t i = 0; i < s.points.size(); ++i)
    res.pointFixed[i] = determined(sys.L.px[i]) && determined(sys.L.py[i]);
  for (size_t i = 0; i < s.entities.size(); ++i) {
    bool fixed = determined(sys.L.rad[i]);
    for (int p : s.entityPoints(static_cast<int>(i))) fixed = fixed && res.pointFixed[p];
    res.entityFixed[i] = fixed;
  }
  return res;
}

std::string addConstraintChecked(Sketch& s, const Constraint& c) {
  if (c.driven) {   // constrains nothing: always fits
    s.constraints.push_back(c);
    return {};
  }
  Sketch trial = s;
  const SolveResult before = solve(trial);
  if (!before.ok) return before.message;
  trial.constraints.push_back(c);
  const SolveResult after = solve(trial);
  if (!after.ok) return "That would over-constrain the sketch (it conflicts with existing constraints).";
  if (after.dof >= before.dof) return "That constraint is already implied by the existing ones.";
  s = std::move(trial);
  return {};
}

} // namespace tsr::sketch
