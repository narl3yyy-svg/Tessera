#include "tsr/sketch/SketchOps.h"

#include <algorithm>
#include <cmath>
#include <map>
#include <numbers>

namespace tsr::sketch {

namespace {

constexpr double kPi = std::numbers::pi;

// Points joined by coincident constraints (or at the same place) count as one.
class Joints {
public:
  explicit Joints(const Sketch& s) : parent_(s.points.size()) {
    for (size_t i = 0; i < parent_.size(); ++i) parent_[i] = static_cast<int>(i);
    for (const auto& c : s.constraints)
      if (c.type == ConstraintType::Coincident && c.points.size() == 2) unite(c.points[0], c.points[1]);
  }
  int root(int p) {
    while (parent_[p] != p) p = parent_[p] = parent_[parent_[p]];
    return p;
  }
  bool same(int a, int b) { return root(a) == root(b); }

private:
  void unite(int a, int b) { parent_[root(a)] = root(b); }
  std::vector<int> parent_;
};

struct V {
  double x = 0, y = 0;
};
V operator-(V a, V b) { return {a.x - b.x, a.y - b.y}; }
V operator+(V a, V b) { return {a.x + b.x, a.y + b.y}; }
V operator*(V a, double k) { return {a.x * k, a.y * k}; }
double len(V a) { return std::hypot(a.x, a.y); }
V unit(V a) {
  const double l = len(a);
  return l > 0 ? a * (1 / l) : V{1, 0};
}
double cross(V a, V b) { return a.x * b.y - a.y * b.x; }
double dot(V a, V b) { return a.x * b.x + a.y * b.y; }
V at(const Sketch& s, int p) { return {s.points.at(p).x, s.points.at(p).y}; }

bool isLine(const Sketch& s, int e) {
  return e >= 0 && e < static_cast<int>(s.entities.size()) && s.entities[e].type == EntityType::Line;
}

} // namespace

std::optional<std::pair<int, int>> cornerAt(const Sketch& s, int point) {
  if (point < 0 || point >= static_cast<int>(s.points.size())) return std::nullopt;
  Joints j(s);
  std::vector<int> lines;
  for (int i = 0; i < static_cast<int>(s.entities.size()); ++i) {
    const Entity& e = s.entities[i];
    if (e.type == EntityType::Line && !e.construction && (j.same(e.a, point) || j.same(e.b, point))) lines.push_back(i);
  }
  if (lines.size() != 2) return std::nullopt;
  return std::make_pair(lines[0], lines[1]);
}

std::string filletCorner(Sketch& s, int la, int lb, double radius, int* arcOut) {
  if (!isLine(s, la) || !isLine(s, lb) || la == lb) return "Fillet: pick two lines that meet at a corner";
  if (!(radius > 0)) return "Fillet: the radius must be greater than zero";
  Joints j(s);
  const Entity A = s.entities[la], B = s.entities[lb];
  int ea = -1, eb = -1;
  for (int pa : {A.a, A.b})
    for (int pb : {B.a, B.b})
      if (ea < 0 && j.same(pa, pb)) {
        ea = pa;
        eb = pb;
      }
  if (ea < 0) return "Fillet: the two lines do not meet at a corner";
  const int fa = ea == A.a ? A.b : A.a, fb = eb == B.a ? B.b : B.a;
  const V p = at(s, ea);
  const V u1 = unit(at(s, fa) - p), u2 = unit(at(s, fb) - p);
  const double theta = std::acos(std::clamp(dot(u1, u2), -1.0, 1.0));
  if (theta < 1e-3 || theta > kPi - 1e-3) return "Fillet: the lines are parallel";
  const double t = radius / std::tan(theta / 2);
  if (t >= len(at(s, fa) - p) - 1e-9 || t >= len(at(s, fb) - p) - 1e-9) return "Fillet: the radius is too large for these lines";
  const V t1 = p + u1 * t, t2 = p + u2 * t;
  const V c = p + unit(u1 + u2) * (radius / std::sin(theta / 2));

  const Sketch backup = s;
  int pt1 = ea, pt2 = eb;
  bool dropCorner = false;
  if (ea == eb) {
    // One shared point: give each line its own end at its tangent point.
    pt1 = s.addPoint(t1.x, t1.y);
    pt2 = s.addPoint(t2.x, t2.y);
    Entity& ra = s.entities[la];
    Entity& rb = s.entities[lb];
    (ra.a == ea ? ra.a : ra.b) = pt1;
    (rb.a == eb ? rb.a : rb.b) = pt2;
    dropCorner = true;
  } else {
    s.points[ea] = {t1.x, t1.y};
    s.points[eb] = {t2.x, t2.y};
  }
  // The corner no longer exists: drop what tied the two ends together there
  // and the lines' length dimensions, which measured to it.
  std::vector<Constraint> kept;
  for (const auto& k : s.constraints) {
    const bool joinsEnds = k.type == ConstraintType::Coincident && k.points.size() == 2 &&
                           ((j.same(k.points[0], ea) && j.same(k.points[1], ea)));
    const bool lengthDim = (k.type == ConstraintType::Distance || k.type == ConstraintType::HorizontalDistance ||
                            k.type == ConstraintType::VerticalDistance) &&
                           k.points.empty() && k.entities.size() == 1 && (k.entities[0] == la || k.entities[0] == lb);
    if (!joinsEnds && !lengthDim) kept.push_back(k);
  }
  s.constraints = std::move(kept);

  const int pc = s.addPoint(c.x, c.y);
  const bool ccw = cross(t1 - c, t2 - c) > 0;
  const int arc = s.addArc(pc, ccw ? pt1 : pt2, ccw ? pt2 : pt1);
  s.entities[arc].radius = radius;
  s.addConstraint({ConstraintType::Tangent, {}, {la, arc}});
  s.addConstraint({ConstraintType::Tangent, {}, {lb, arc}});
  s.addConstraint({ConstraintType::Radius, {}, {arc}, radius});
  if (dropCorner) {
    bool used = false;
    for (int i = 0; i < static_cast<int>(s.entities.size()); ++i)
      for (int q : s.entityPoints(i)) used = used || q == ea;
    if (!used) s.removePoints({ea});   // entity indices are unchanged: nothing is built on it now
  }
  const SolveResult r = solve(s);
  if (!r.ok) {
    s = backup;
    return "Fillet: " + (r.message.empty() ? std::string("the result cannot be solved") : r.message);
  }
  if (arcOut) *arcOut = arc;
  return {};
}

std::string chamferCorner(Sketch& s, int la, int lb, double distance, int* lineOut) {
  if (!isLine(s, la) || !isLine(s, lb) || la == lb) return "Chamfer: pick two lines that meet at a corner";
  if (!(distance > 0)) return "Chamfer: the distance must be greater than zero";
  Joints j(s);
  const Entity A = s.entities[la], B = s.entities[lb];
  int ea = -1, eb = -1;
  for (int pa : {A.a, A.b})
    for (int pb : {B.a, B.b})
      if (ea < 0 && j.same(pa, pb)) {
        ea = pa;
        eb = pb;
      }
  if (ea < 0) return "Chamfer: the two lines do not meet at a corner";
  const int fa = ea == A.a ? A.b : A.a, fb = eb == B.a ? B.b : B.a;
  const V p = at(s, ea);
  const V u1 = unit(at(s, fa) - p), u2 = unit(at(s, fb) - p);
  if (std::abs(cross(u1, u2)) < 1e-6) return "Chamfer: the lines are parallel";
  if (distance >= len(at(s, fa) - p) - 1e-9 || distance >= len(at(s, fb) - p) - 1e-9)
    return "Chamfer: the distance is too large for these lines";
  const V t1 = p + u1 * distance, t2 = p + u2 * distance;
  const Sketch backup = s;
  int pt1 = ea, pt2 = eb;
  if (ea == eb) {
    pt1 = s.addPoint(t1.x, t1.y);
    pt2 = s.addPoint(t2.x, t2.y);
    Entity& ra = s.entities[la];
    Entity& rb = s.entities[lb];
    (ra.a == ea ? ra.a : ra.b) = pt1;
    (rb.a == eb ? rb.a : rb.b) = pt2;
  } else {
    s.points[ea] = {t1.x, t1.y};
    s.points[eb] = {t2.x, t2.y};
  }
  std::vector<Constraint> kept;
  for (const auto& k : s.constraints) {
    const bool joinsEnds = k.type == ConstraintType::Coincident && k.points.size() == 2 &&
                           j.same(k.points[0], ea) && j.same(k.points[1], ea);
    const bool lengthDim = (k.type == ConstraintType::Distance || k.type == ConstraintType::HorizontalDistance ||
                            k.type == ConstraintType::VerticalDistance) &&
                           k.points.empty() && k.entities.size() == 1 && (k.entities[0] == la || k.entities[0] == lb);
    if (!joinsEnds && !lengthDim) kept.push_back(k);
  }
  s.constraints = std::move(kept);
  const int line = s.addLine(pt1, pt2, A.construction);
  if (ea == eb) {
    bool used = false;
    for (int i = 0; i < static_cast<int>(s.entities.size()); ++i)
      for (int q : s.entityPoints(i)) used = used || q == ea;
    if (!used) s.removePoints({ea});
  }
  const SolveResult r = solve(s);
  if (!r.ok) {
    s = backup;
    return "Chamfer: " + (r.message.empty() ? std::string("the result cannot be solved") : r.message);
  }
  if (lineOut) *lineOut = line;
  return {};
}

std::string extendLine(Sketch& s, int line, double x, double y) {
  if (!isLine(s, line)) return "Extend: click a line near the end to extend";
  const Entity e = s.entities[line];
  const V pa = at(s, e.a), pb = at(s, e.b);
  // The end nearest the click, pointing outward.
  const bool atB = len(V{x, y} - pb) < len(V{x, y} - pa);
  const int endPt = atB ? e.b : e.a;
  for (int i = 0; i < static_cast<int>(s.entities.size()); ++i)
    if (i != line)
      for (int q : s.entityPoints(i))
        if (q == endPt) return "Extend: that end is connected to another curve";
  const V from = atB ? pb : pa, dir = unit(atB ? pb - pa : pa - pb);
  double best = 1e300;
  int target = -1;
  for (int i = 0; i < static_cast<int>(s.entities.size()); ++i) {
    if (i == line) continue;
    const Entity& o = s.entities[i];
    if (o.type == EntityType::Line) {
      const V c = at(s, o.a), d = at(s, o.b) - at(s, o.a);
      const double den = cross(dir, d);
      if (std::abs(den) < 1e-12) continue;
      const double t = cross(c - from, d) / den, u = cross(c - from, dir) / den;
      if (t > 1e-9 && u >= -1e-9 && u <= 1 + 1e-9 && t < best) {
        best = t;
        target = i;
      }
    } else if (isRound(o.type)) {
      const V c = at(s, o.center);
      const V f = from - c;
      const double B = 2 * dot(f, dir), C = dot(f, f) - o.radius * o.radius, disc = B * B - 4 * C;
      if (disc < 0) continue;
      for (double sg : {-1.0, 1.0}) {
        const double t = (-B + sg * std::sqrt(disc)) / 2;
        if (t <= 1e-9 || t >= best) continue;
        if (o.type == EntityType::Arc) {
          const V q = from + dir * t;
          const double ang = std::atan2(q.y - c.y, q.x - c.x);
          const double a0 = std::atan2(at(s, o.a).y - c.y, at(s, o.a).x - c.x);
          double a1 = std::atan2(at(s, o.b).y - c.y, at(s, o.b).x - c.x), aa = ang;
          while (a1 <= a0) a1 += 2 * kPi;
          while (aa < a0) aa += 2 * kPi;
          if (aa > a1 + 1e-9) continue;
        }
        best = t;
        target = i;
      }
    }
  }
  if (target < 0) return "Extend: nothing to extend to in that direction";
  const Sketch backup = s;
  const V to = from + dir * best;
  s.points[endPt] = {to.x, to.y};
  // Remove a length dimension on the line (it changes), keep the end on the target.
  std::erase_if(s.constraints, [&](const Constraint& k) {
    return k.type == ConstraintType::Distance && k.points.empty() && k.entities.size() == 1 && k.entities[0] == line;
  });
  s.addConstraint({ConstraintType::PointOnEntity, {endPt}, {target}});
  const SolveResult r = solve(s);
  if (!r.ok) {
    s = backup;
    return "Extend: " + (r.message.empty() ? std::string("the result cannot be solved") : r.message);
  }
  return {};
}

std::string mirrorEntities(Sketch& s, const std::vector<int>& entities, int mirrorLine, std::vector<int>* created) {
  if (!isLine(s, mirrorLine)) return "Mirror: pick a line to mirror across";
  if (entities.empty()) return "Mirror: pick the curves to mirror";
  const V m0 = at(s, s.entities[mirrorLine].a), md = unit(at(s, s.entities[mirrorLine].b) - m0);
  auto reflect = [&](V p) {
    const V v = p - m0;
    const V along = md * dot(v, md);
    return m0 + along * 2 - v;
  };
  const Sketch backup = s;
  std::map<int, int> twin;   // original point -> mirrored point
  auto mirrored = [&](int p) {
    if (auto it = twin.find(p); it != twin.end()) return it->second;
    const V q = at(s, p);
    const V v = q - m0;
    if (std::abs(cross(md, v)) < 1e-9) return twin[p] = p;   // on the mirror line: shared
    const V r = reflect(q);
    const int n = s.addPoint(r.x, r.y);
    s.addConstraint({ConstraintType::Symmetry, {p, n}, {mirrorLine}});
    return twin[p] = n;
  };
  std::vector<int> made;
  for (int id : entities) {
    if (id == mirrorLine || id < 0 || id >= static_cast<int>(s.entities.size())) continue;
    const Entity e = s.entities[id];
    Entity c = e;
    switch (e.type) {
      case EntityType::Line:
        c.a = mirrored(e.a);
        c.b = mirrored(e.b);
        break;
      case EntityType::Circle:
        c.center = mirrored(e.center);
        break;
      case EntityType::Arc:
        // A mirror turns anticlockwise into clockwise: swap the ends.
        c.center = mirrored(e.center);
        c.a = mirrored(e.b);
        c.b = mirrored(e.a);
        break;
      case EntityType::Spline:
        for (int& f : c.fit) f = mirrored(f);
        c.a = c.fit.front();
        c.b = c.fit.back();
        break;
    }
    c.projected = false;
    s.entities.push_back(c);
    const int ni = static_cast<int>(s.entities.size()) - 1;
    made.push_back(ni);
    if (e.type == EntityType::Circle || e.type == EntityType::Arc)
      s.addConstraint({ConstraintType::Equal, {}, {id, ni}});
  }
  if (made.empty()) return "Mirror: pick the curves to mirror (not the mirror line itself)";
  const SolveResult r = solve(s);
  if (!r.ok) {
    s = backup;
    return "Mirror: " + (r.message.empty() ? std::string("the result cannot be solved") : r.message);
  }
  if (created) *created = made;
  return {};
}

std::vector<ChainSegment> chainOf(const Sketch& s, int entity, bool* closed) {
  if (closed) *closed = false;
  if (entity < 0 || entity >= static_cast<int>(s.entities.size())) return {};
  const Entity& e0 = s.entities[entity];
  if (e0.type == EntityType::Circle) {
    if (closed) *closed = true;
    return {{entity, true}};
  }
  if (e0.type == EntityType::Spline) return {};
  Joints j(s);
  std::vector<bool> used(s.entities.size(), false);
  used[entity] = true;
  auto eligible = [&](int i) {
    const Entity& e = s.entities[i];
    return !used[i] && (e.type == EntityType::Line || e.type == EntityType::Arc) && e.construction == e0.construction;
  };
  std::vector<ChainSegment> chain = {{entity, true}};
  auto endOf = [&](const ChainSegment& c) { return c.forward ? s.entities[c.entity].b : s.entities[c.entity].a; };
  auto startOf = [&](const ChainSegment& c) { return c.forward ? s.entities[c.entity].a : s.entities[c.entity].b; };
  // Forward from the end, then backward from the start.
  for (bool grew = true; grew;) {
    grew = false;
    const int end = endOf(chain.back());
    if (j.same(end, startOf(chain.front())) && chain.size() > 1) {
      if (closed) *closed = true;
      return chain;
    }
    for (int i = 0; i < static_cast<int>(s.entities.size()) && !grew; ++i)
      if (eligible(i)) {
        if (j.same(s.entities[i].a, end)) chain.push_back({i, true}), used[i] = grew = true;
        else if (j.same(s.entities[i].b, end)) chain.push_back({i, false}), used[i] = grew = true;
      }
  }
  if (j.same(endOf(chain.back()), startOf(chain.front())) && chain.size() > 1) {
    if (closed) *closed = true;
    return chain;
  }
  for (bool grew = true; grew;) {
    grew = false;
    const int start = startOf(chain.front());
    for (int i = 0; i < static_cast<int>(s.entities.size()) && !grew; ++i)
      if (eligible(i)) {
        if (j.same(s.entities[i].b, start)) chain.insert(chain.begin(), {i, true}), used[i] = grew = true;
        else if (j.same(s.entities[i].a, start)) chain.insert(chain.begin(), {i, false}), used[i] = grew = true;
      }
  }
  return chain;
}

std::string offsetChain(Sketch& s, int entity, double distance, std::vector<int>* created) {
  if (std::abs(distance) < 1e-9) return "Offset: the distance must not be zero";
  bool closed = false;
  const auto chain = chainOf(s, entity, &closed);
  if (chain.empty()) return "Offset: pick a line, arc or circle (splines cannot be offset yet)";
  const Sketch backup = s;
  std::vector<int> made;

  if (s.entities[chain[0].entity].type == EntityType::Circle) {
    const Entity c = s.entities[chain[0].entity];
    const double r = c.radius + distance;
    if (r <= 1e-9) return "Offset: the distance is larger than the circle";
    made.push_back(s.addCircleAt(c.center, r, c.construction));
  } else {
    // Each segment in traversal order: start, end, and its offset copy.
    struct Seg {
      int e;
      bool forward;
      bool line;
      V p, q;     // traversal start / end
      V c;        // arc centre
      double r2;  // offset arc radius
      V p2, q2;   // offset ends
      V dir;      // line direction
    };
    std::vector<Seg> segs;
    double area = 0;
    for (const auto& cs : chain) {
      const Entity& e = s.entities[cs.entity];
      Seg g{cs.entity, cs.forward, e.type == EntityType::Line, {}, {}, {}, 0, {}, {}, {}};
      g.p = at(s, cs.forward ? e.a : e.b);
      g.q = at(s, cs.forward ? e.b : e.a);
      if (!g.line) g.c = at(s, e.center);
      segs.push_back(g);
      // Signed area of the outline, arcs sampled.
      const int n = g.line ? 1 : 8;
      V prev = g.p;
      for (int k = 1; k <= n; ++k) {
        V cur = g.q;
        if (!g.line) {
          const double a0 = std::atan2(g.p.y - g.c.y, g.p.x - g.c.x);
          double a1 = std::atan2(g.q.y - g.c.y, g.q.x - g.c.x);
          double sweep = a1 - a0;
          if (g.forward) { while (sweep <= 0) sweep += 2 * kPi; }
          else { while (sweep >= 0) sweep -= 2 * kPi; }
          const double r = len(g.p - g.c);
          cur = g.c + V{std::cos(a0 + sweep * k / n), std::sin(a0 + sweep * k / n)} * r;
        }
        area += cross(prev, cur);
        prev = cur;
      }
    }
    // The right-hand side is outward for an anticlockwise outline.
    const double d = closed && area < 0 ? -distance : distance;
    for (auto& g : segs) {
      if (g.line) {
        g.dir = unit(g.q - g.p);
        const V n{g.dir.y, -g.dir.x};
        g.p2 = g.p + n * d;
        g.q2 = g.q + n * d;
      } else {
        const double r = len(g.p - g.c);
        g.r2 = g.forward ? r + d : r - d;
        if (g.r2 <= 1e-9) return "Offset: the distance is larger than an arc's radius";
        g.p2 = g.c + unit(g.p - g.c) * g.r2;
        g.q2 = g.c + unit(g.q - g.c) * g.r2;
      }
    }
    // Shared points where consecutive offset curves meet.
    const size_t n = segs.size();
    std::vector<int> joins(n + 1, -1);   // joins[i] = start of segment i
    auto meet = [&](const Seg& a, const Seg& b) {
      if (a.line && b.line && std::abs(cross(a.dir, b.dir)) > 1e-9) {
        const double t = cross(b.p2 - a.p2, b.dir) / cross(a.dir, b.dir);
        return a.p2 + a.dir * t;
      }
      return (a.q2 + b.p2) * 0.5;
    };
    for (size_t i = 1; i < n; ++i) {
      const V m = meet(segs[i - 1], segs[i]);
      joins[i] = s.addPoint(m.x, m.y);
    }
    if (closed) {
      const V m = meet(segs[n - 1], segs[0]);
      joins[0] = joins[n] = s.addPoint(m.x, m.y);
    } else {
      joins[0] = s.addPoint(segs[0].p2.x, segs[0].p2.y);
      joins[n] = s.addPoint(segs[n - 1].q2.x, segs[n - 1].q2.y);
    }
    const bool construction = s.entities[entity].construction;
    bool dimensioned = false;
    for (size_t i = 0; i < n; ++i) {
      const Seg& g = segs[i];
      const int a = joins[i], b = joins[i + 1];
      if (g.line) {
        const int l = s.addLine(a, b, construction);
        made.push_back(l);
        s.addConstraint({ConstraintType::Parallel, {}, {g.e, l}});
        if (!dimensioned) {   // one offset distance; the rest follows through the shared corners
          s.addConstraint({ConstraintType::Distance, {a}, {g.e}, std::abs(distance)});
          dimensioned = true;
        }
      } else {
        const int arc = s.addArc(s.entities[g.e].center, g.forward ? a : b, g.forward ? b : a, construction);
        s.entities[arc].radius = g.r2;
        made.push_back(arc);
      }
    }
  }
  const SolveResult r = solve(s);
  if (!r.ok) {
    s = backup;
    return "Offset: " + (r.message.empty() ? std::string("the result cannot be solved") : r.message);
  }
  if (created) *created = made;
  return {};
}

} // namespace tsr::sketch
