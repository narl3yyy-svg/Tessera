// Sketch operations on curves without a simple closed form: crossings of any
// two curves, Trim / Break and Offset of splines and ellipses, spline tangent
// handles, and Include 3D Geometry.
#include "tsr/sketch/SketchGeometry.h"
#include "tsr/sketch/SketchOps.h"

#include <BRepAdaptor_Curve.hxx>
#include <BRep_Tool.hxx>
#include <GeomAPI.hxx>
#include <Geom2dAPI_InterCurveCurve.hxx>
#include <Geom2dAPI_ProjectPointOnCurve.hxx>
#include <Geom2d_Curve.hxx>
#include <Geom2d_TrimmedCurve.hxx>
#include <Geom_Curve.hxx>
#include <Standard_Failure.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Edge.hxx>
#include <gp_Circ.hxx>
#include <gp_Pln.hxx>

#include <algorithm>
#include <cmath>
#include <numbers>
#include <optional>

namespace tsr::sketch {

namespace {

constexpr double kPi = std::numbers::pi;

const gp_Ax3& xyFrame() {
  static const gp_Ax3 f(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1), gp_Dir(1, 0, 0));
  return f;
}

// A curve in sketch coordinates (heights of included geometry dropped:
// crossings are seen along the sketch normal).
struct Curve2d {
  Handle(Geom2d_Curve) c;   // trimmed to the entity
  double t0 = 0, t1 = 0;
  bool periodic = false;    // a closed curve (circle, ellipse, closed spline)
};

std::optional<Curve2d> curve2d(const Sketch& flat, int entity) {
  try {
    const TopoDS_Shape sh = curve(flat, xyFrame(), entity);
    if (sh.IsNull()) return std::nullopt;
    const TopoDS_Edge edge = TopoDS::Edge(sh);
    double t0 = 0, t1 = 0;
    const Handle(Geom_Curve) g = BRep_Tool::Curve(edge, t0, t1);
    if (g.IsNull()) return std::nullopt;
    Curve2d out;
    const Handle(Geom2d_Curve) basis = GeomAPI::To2d(g, gp_Pln(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)));
    if (basis.IsNull()) return std::nullopt;
    out.c = new Geom2d_TrimmedCurve(basis, t0, t1);
    out.t0 = t0;
    out.t1 = t1;
    const gp_Pnt2d a = out.c->Value(t0), b = out.c->Value(t1);
    out.periodic = a.Distance(b) < 1e-7 && t1 - t0 > 1e-9;
    if (!(t1 > t0)) return std::nullopt;
    return out;
  } catch (const Standard_Failure&) {
    return std::nullopt;
  }
}

Sketch flattened(const Sketch& s) {
  Sketch f = s;
  for (auto& p : f.points) p.z = 0;
  return f;
}

double paramOf(const Curve2d& c, double x, double y) {
  try {
    Geom2dAPI_ProjectPointOnCurve proj(gp_Pnt2d(x, y), c.c, c.t0, c.t1);
    if (proj.NbPoints() > 0) return proj.LowerDistanceParameter();
  } catch (const Standard_Failure&) {
  }
  return c.t0;
}

std::vector<Point> crossingsOf(const Sketch& flat, int entity, const Curve2d& target, int only) {
  std::vector<Point> out;
  for (int j = 0; j < static_cast<int>(flat.entities.size()); ++j) {
    if (j == entity || (only >= 0 && j != only)) continue;
    const auto other = curve2d(flat, j);
    if (!other) continue;
    try {
      Geom2dAPI_InterCurveCurve inter(target.c, other->c, 1e-9);
      for (int k = 1; k <= inter.NbPoints(); ++k) {
        const gp_Pnt2d p = inter.Point(k);
        bool dup = false;
        for (const auto& q : out) dup = dup || std::hypot(q.x - p.X(), q.y - p.Y()) < 1e-7;
        if (!dup) out.push_back({p.X(), p.Y()});
      }
    } catch (const Standard_Failure&) {
    }
  }
  return out;
}

int newPoint(Sketch& s, const gp_Pnt2d& p) { return s.addPoint(p.X(), p.Y()); }

// The source curve from parameter u0 to u1 (u1 > u0; may run past the end of
// a periodic curve) as a new entity with the given end points.
int makePiece(Sketch& s, const Entity& src, const Curve2d& c, double u0, double u1, int start, int end) {
  const double period = c.t1 - c.t0;
  auto wrap = [&](double u) {
    if (!c.periodic) return u;
    return c.t0 + std::fmod(std::fmod(u - c.t0, period) + period, period);
  };
  if (src.type == EntityType::Ellipse) return s.addEllipticalArc(src.center, src.a, src.radius, start, end, src.construction);
  // A spline: a fit point spline through its own fit points that lie on the
  // piece (or points sampled along it), starting and ending in the
  // directions the original runs there.
  std::vector<int> fit = {start};
  std::vector<Point> handles = {{0, 0}};
  if (src.kind == SplineKind::Fit) {
    std::vector<std::pair<double, int>> inner;
    const bool closed = src.fit.size() > 2 && src.fit.front() == src.fit.back();
    for (size_t i = 0; i < src.fit.size() - (closed ? 1 : 0); ++i) {
      const Point& q = s.points.at(src.fit[i]);
      double u = paramOf(c, q.x, q.y);
      if (c.periodic && u < u0) u += period * std::ceil((u0 - u) / period);
      if (u > u0 + 1e-7 && u < u1 - 1e-7) inner.emplace_back(u, static_cast<int>(i));
    }
    std::sort(inner.begin(), inner.end());
    for (const auto& [u, i] : inner) {
      fit.push_back(src.fit[i]);
      handles.push_back(i < static_cast<int>(src.handles.size()) ? src.handles[i] : Point{0, 0});
    }
  }
  if (fit.size() == 1) {
    const int n = src.kind == SplineKind::Fit ? 2 : 6;
    for (int k = 1; k <= n; ++k) {
      fit.push_back(newPoint(s, c.c->Value(wrap(u0 + (u1 - u0) * k / (n + 1)))));
      handles.push_back({0, 0});
    }
  }
  fit.push_back(end);
  handles.push_back({0, 0});
  for (auto [u, slot] : {std::pair{u0, size_t{0}}, std::pair{u1, handles.size() - 1}}) {
    gp_Pnt2d p;
    gp_Vec2d d;
    c.c->D1(wrap(u), p, d);
    if (d.Magnitude() > 1e-12) handles[slot] = {d.X() / d.Magnitude(), d.Y() / d.Magnitude()};
  }
  const int id = s.addSpline(fit, src.construction, SplineKind::Fit);
  s.entities[id].handles = handles;
  return id;
}

} // namespace

std::vector<Point> crossings(const Sketch& s, int entity, int other) {
  if (entity < 0 || entity >= static_cast<int>(s.entities.size())) return {};
  const Sketch flat = flattened(s);
  const auto c = curve2d(flat, entity);
  if (!c) return {};
  return crossingsOf(flat, entity, *c, other);
}

std::string trimCurve(Sketch& s, int entity, double x, double y, bool breakOnly) {
  const char* what = breakOnly ? "Break" : "Trim";
  if (entity < 0 || entity >= static_cast<int>(s.entities.size())) return std::string(what) + ": click a curve";
  const Entity src = s.entities[entity];
  if (src.type != EntityType::Spline && src.type != EntityType::Ellipse)
    return std::string(what) + ": this works on splines, conics and ellipses";
  if (src.projected) return std::string(what) + ": projected geometry cannot be cut";
  const Sketch flat = flattened(s);
  const auto c = curve2d(flat, entity);
  if (!c) return std::string(what) + ": that curve has no shape";
  const double period = c->t1 - c->t0;
  std::vector<double> cuts;
  for (const auto& p : crossingsOf(flat, entity, *c, -1)) {
    const double u = paramOf(*c, p.x, p.y);
    if (!c->periodic && (u < c->t0 + 1e-7 || u > c->t1 - 1e-7)) continue;   // at an end: nothing to cut
    cuts.push_back(u);
  }
  const double uc = paramOf(*c, x, y);
  // The crossings either side of the click, as parameters (lo < uc < hi;
  // on a closed curve hi may run past the end).
  std::optional<double> lo, hi;
  for (double u : cuts) {
    if (c->periodic) {
      double after = u, before = u;
      if (after <= uc + 1e-9) after += period * (std::floor((uc + 1e-9 - after) / period) + 1);
      if (before >= uc - 1e-9) before -= period * (std::floor((before - (uc - 1e-9)) / period) + 1);
      if (!hi || after < *hi) hi = after;
      if (!lo || before > *lo) lo = before;
    } else {
      if (u < uc - 1e-9 && (!lo || u > *lo)) lo = u;
      if (u > uc + 1e-9 && (!hi || u < *hi)) hi = u;
    }
  }
  const Sketch backup = s;
  auto pointAt = [&](double u) {
    if (c->periodic) u = c->t0 + std::fmod(std::fmod(u - c->t0, period) + period, period);
    return newPoint(s, c->c->Value(u));
  };
  std::vector<int> pieces;
  if (c->periodic) {
    // A closed curve needs two crossings to cut a piece out.
    std::vector<double> distinct;
    for (double u : cuts) {
      bool dup = false;
      for (double v : distinct) dup = dup || std::abs(std::remainder(u - v, period)) < 1e-7;
      if (!dup) distinct.push_back(u);
    }
    if (distinct.size() < 2) {
      if (breakOnly) return "Break: a closed curve must cross others twice to break";
      s.removeEntities({entity});
      return {};
    }
    const int pl = pointAt(*lo), ph = pointAt(*hi);
    // The rest: from the crossing after the click round to the one before.
    pieces.push_back(makePiece(s, src, *c, *hi, *lo + period, ph, pl));
    if (breakOnly) pieces.push_back(makePiece(s, src, *c, *lo, *hi, pl, ph));
  } else {
    if (!lo && !hi) {
      if (breakOnly) return "Break: nothing crosses that curve there";
      s.removeEntities({entity});
      return {};
    }
    const int startPt = src.type == EntityType::Ellipse ? src.fit[0] : src.fit.front();
    const int endPt = src.type == EntityType::Ellipse ? src.fit[1] : src.fit.back();
    const int pl = lo ? pointAt(*lo) : -1, ph = hi ? pointAt(*hi) : -1;
    if (lo) pieces.push_back(makePiece(s, src, *c, c->t0, *lo, startPt, pl));
    if (breakOnly) {
      if (lo && hi) pieces.push_back(makePiece(s, src, *c, *lo, *hi, pl, ph));
      else if (lo) pieces.push_back(makePiece(s, src, *c, *lo, c->t1, pl, endPt));
      else pieces.push_back(makePiece(s, src, *c, c->t0, *hi, startPt, ph));
    }
    if (hi) pieces.push_back(makePiece(s, src, *c, *hi, c->t1, ph, endPt));
  }
  // Points kept on an ellipse stay on its pieces (they share the ellipse).
  if (src.type == EntityType::Ellipse && !pieces.empty())
    for (auto& k : s.constraints)
      if (k.type == ConstraintType::PointOnEntity || k.type == ConstraintType::Radius)
        for (int& e : k.entities)
          if (e == entity) e = pieces.front();
  s.removeEntities({entity});
  const SolveResult r = solve(s);
  if (!r.ok) {
    s = backup;
    return std::string(what) + ": " + (r.message.empty() ? std::string("the result cannot be solved") : r.message);
  }
  return {};
}

std::string offsetCurve(Sketch& s, int entity, double distance, std::vector<int>* created) {
  if (entity < 0 || entity >= static_cast<int>(s.entities.size())) return "Offset: pick a curve";
  const Entity src = s.entities[entity];
  if (src.type != EntityType::Spline && src.type != EntityType::Ellipse) return "Offset: pick a spline or an ellipse";
  if (std::abs(distance) < 1e-9) return "Offset: the distance must not be zero";
  const Sketch flat = flattened(s);
  const auto c = curve2d(flat, entity);
  if (!c) return "Offset: that curve has no shape";
  int n = 24;
  if (!c->periodic) n = src.type == EntityType::Spline ? std::max(8, 4 * static_cast<int>(src.fit.size() - 1)) : 12;
  std::vector<gp_Pnt2d> pts;
  std::vector<gp_Vec2d> tans;
  const int count = c->periodic ? n : n + 1;
  for (int k = 0; k < count; ++k) {
    gp_Pnt2d p;
    gp_Vec2d d;
    c->c->D1(c->t0 + (c->t1 - c->t0) * k / n, p, d);
    if (d.Magnitude() < 1e-12) return "Offset: the curve has a sharp point";
    pts.push_back(p);
    tans.push_back(d / d.Magnitude());
  }
  double d = distance;
  if (c->periodic) {
    double area = 0;
    for (int k = 0; k < count; ++k) {
      const gp_Pnt2d &p = pts[k], &q = pts[(k + 1) % count];
      area += p.X() * q.Y() - p.Y() * q.X();
    }
    if (area < 0) d = -d;   // the right-hand side is outward for an anticlockwise loop
  }
  if (src.type == EntityType::Ellipse) {
    const Point &o = s.points[src.center], &a = s.points[src.a];
    const double A = std::hypot(a.x - o.x, a.y - o.y), B = std::abs(src.radius);
    // Inside an ellipse the offset folds over once it passes the tightest
    // curvature, B^2 / A at the ends of the long axis. Anticlockwise, the
    // right-hand side is outside.
    const double tight = std::min(A, B) * std::min(A, B) / std::max(A, B);
    if (d < 0 && -d >= tight - 1e-9) return "Offset: the distance is larger than the ellipse's tightest curve";
  }
  const Sketch backup = s;
  std::vector<int> fit;
  std::vector<Point> handles;
  for (int k = 0; k < count; ++k) {
    const gp_Vec2d nrm(tans[k].Y(), -tans[k].X());
    const gp_Pnt2d q = pts[k].Translated(nrm * d);
    fit.push_back(newPoint(s, q));
    handles.push_back({0, 0});
  }
  if (c->periodic) {
    fit.push_back(fit.front());
    handles.push_back({0, 0});
  } else {
    handles.front() = {tans.front().X(), tans.front().Y()};
    handles.back() = {tans.back().X(), tans.back().Y()};
  }
  const int id = s.addSpline(fit, src.construction, SplineKind::Fit);
  s.entities[id].handles = handles;
  if (curve(s, xyFrame(), id).IsNull()) {
    s = backup;
    return "Offset: the offset curve cannot be made at that distance";
  }
  const SolveResult r = solve(s);
  if (!r.ok) {
    s = backup;
    return "Offset: " + (r.message.empty() ? std::string("the result cannot be solved") : r.message);
  }
  if (created) *created = {id};
  return {};
}

std::string setSplineHandle(Sketch& s, int spline, int index, double tx, double ty) {
  if (spline < 0 || spline >= static_cast<int>(s.entities.size()) || s.entities[spline].type != EntityType::Spline ||
      s.entities[spline].kind != SplineKind::Fit)
    return "tangent handles belong to fit point splines";
  Entity& e = s.entities[spline];
  if (index < 0 || index >= static_cast<int>(e.fit.size())) return "the spline has no such point";
  if (!std::isfinite(tx) || !std::isfinite(ty)) return "the handle must be a finite direction";
  e.handles.resize(e.fit.size(), Point{0, 0});
  e.handles[index] = {tx, ty};
  const bool closed = e.fit.size() > 2 && e.fit.front() == e.fit.back();
  if (closed && (index == 0 || index + 1 == static_cast<int>(e.fit.size()))) e.handles.front() = e.handles.back() = {tx, ty};
  bool any = false;
  for (const auto& h : e.handles) any = any || std::hypot(h.x, h.y) > 1e-12;
  if (!any) e.handles.clear();
  return {};
}

int includeEdges(Sketch& s, const gp_Ax3& frame, const std::vector<TopoDS_Edge>& edges) {
  int made = 0;
  auto fixedPoint = [&](const gp_Pnt& p) {
    double x, y;
    toSketch(frame, p, x, y);
    const int i = s.addPoint(x, y);
    s.points[i].z = gp_Vec(frame.Location(), p).Dot(gp_Vec(frame.Direction()));
    s.addConstraint({ConstraintType::Fix, {i}, {}, x, y});
    return i;
  };
  auto mark = [&](int e) {
    s.entities[e].projected = true;
    s.entities[e].included = true;
    ++made;
  };
  for (const auto& edge : edges) {
    if (edge.IsNull() || BRep_Tool::Degenerated(edge)) continue;
    try {
      BRepAdaptor_Curve c(edge);
      const double t0 = c.FirstParameter(), t1 = c.LastParameter();
      const gp_Pnt p0 = c.Value(t0), p1 = c.Value(t1);
      if (c.GetType() == GeomAbs_Line) {
        if (p0.Distance(p1) < 1e-7) continue;
        mark(s.addLine(fixedPoint(p0), fixedPoint(p1)));
        continue;
      }
      if (c.GetType() == GeomAbs_Circle && std::abs(c.Circle().Axis().Direction().Dot(frame.Direction())) > 1 - 1e-9) {
        const gp_Circ circ = c.Circle();
        const int centre = fixedPoint(circ.Location());
        if (p0.Distance(p1) < 1e-7) {
          const int e = s.addCircleAt(centre, circ.Radius());
          s.addConstraint({ConstraintType::Radius, {}, {e}, circ.Radius()});
          mark(e);
          continue;
        }
        // Stored anticlockwise seen from the sketch normal.
        double cx, cy, x0, y0, xm, ym, x1, y1;
        toSketch(frame, circ.Location(), cx, cy);
        toSketch(frame, p0, x0, y0);
        toSketch(frame, c.Value((t0 + t1) / 2), xm, ym);
        toSketch(frame, p1, x1, y1);
        auto ang = [&](double px, double py) { return std::atan2(py - cy, px - cx); };
        double sm = ang(xm, ym) - ang(x0, y0), s1 = ang(x1, y1) - ang(x0, y0);
        while (sm <= 0) sm += 2 * kPi;
        while (s1 <= 0) s1 += 2 * kPi;
        const int a = fixedPoint(p0), b = fixedPoint(p1);
        mark(sm < s1 ? s.addArc(centre, a, b) : s.addArc(centre, b, a));
        continue;
      }
      // Anything else: a fixed spline through points along it, in 3D.
      const int n = 32;
      const bool closed = p0.Distance(p1) < 1e-7;
      std::vector<int> fit;
      for (int k = 0; k < (closed ? n : n + 1); ++k) fit.push_back(fixedPoint(c.Value(t0 + (t1 - t0) * k / n)));
      if (closed) fit.push_back(fit.front());
      mark(s.addSpline(fit));
    } catch (const Standard_Failure&) {
    }
  }
  return made;
}

} // namespace tsr::sketch
