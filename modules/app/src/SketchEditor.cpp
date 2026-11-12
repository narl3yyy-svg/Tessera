#include "SketchEditor.h"
#include "Theme.h"

#include "tsr/core/Units.h"
#include "tsr/doc/DocCommands.h"

#include <AIS_Point.hxx>
#include <AIS_Shape.hxx>
#include <AIS_TextLabel.hxx>
#include <Geom_CartesianPoint.hxx>
#include <Prs3d_LineAspect.hxx>
#include <Prs3d_PointAspect.hxx>

#include <QCursor>
#include <QStyle>
#include <QKeyEvent>
#include <QLineEdit>
#include <QRegularExpression>
#include <QMouseEvent>

#include <algorithm>
#include <optional>
#include <tuple>
#include <cmath>

namespace tsr::app {

using sketch::Constraint;
using sketch::ConstraintType;
using sketch::Entity;
using sketch::EntityType;

namespace {
constexpr double kPi = 3.14159265358979323846;
constexpr double kHVTolerance = 0.0524; // tan(3 degrees): draw "almost horizontal" -> horizontal

Quantity_Color rgb(int r, int g, int b) { return Quantity_Color(r / 255.0, g / 255.0, b / 255.0, Quantity_TOC_sRGB); }

Quantity_Color qc(const QColor& c) { return rgb(c.red(), c.green(), c.blue()); }
// Free / fully constrained colours depend on the theme (blue/black on a
// light canvas, light blue/white on a dark one).
Quantity_Color freeColor() { return qc(themeColors().sketchFree); }
Quantity_Color fixedColor() { return qc(themeColors().sketchFixed); }
const Quantity_Color kConstruction = rgb(235, 130, 30);
const Quantity_Color kSelected = rgb(0, 190, 255);
const Quantity_Color kHover = rgb(255, 170, 0);
const Quantity_Color kPreview = rgb(90, 160, 240);

Handle(AIS_Shape) wire(const TopoDS_Shape& s, const Quantity_Color& c, double width, Aspect_TypeOfLine type) {
  Handle(AIS_Shape) a = new AIS_Shape(s);
  a->SetColor(c);
  a->SetWidth(width);
  a->Attributes()->SetWireAspect(new Prs3d_LineAspect(c, type, width));
  a->Attributes()->SetLineAspect(new Prs3d_LineAspect(c, type, width));
  a->Attributes()->SetFreeBoundaryAspect(new Prs3d_LineAspect(c, type, width));
  a->Attributes()->SetUnFreeBoundaryAspect(new Prs3d_LineAspect(c, type, width));
  return a;
}

TCollection_ExtendedString ext(const QString& s) {
  return TCollection_ExtendedString(s.toUtf8().constData(), /*isMultiByte=*/true);
}

double segDistance(double px, double py, double ax, double ay, double bx, double by) {
  const double dx = bx - ax, dy = by - ay;
  const double l2 = dx * dx + dy * dy;
  double t = l2 > 0 ? ((px - ax) * dx + (py - ay) * dy) / l2 : 0;
  t = std::clamp(t, 0.0, 1.0);
  return std::hypot(px - (ax + t * dx), py - (ay + t * dy));
}

bool angleInArc(double a, double from, double to) {
  auto norm = [](double v) {
    while (v < 0) v += 2 * kPi;
    while (v >= 2 * kPi) v -= 2 * kPi;
    return v;
  };
  const double span = norm(to - from);
  return norm(a - from) <= span;
}
} // namespace

SketchEditor::SketchEditor(doc::Session& session, Viewport* viewport, const QString& name, const QString& plane,
                           double offset, int featureId, const sketch::Sketch& initial, QObject* parent)
    : QObject(parent), session_(session), view_(viewport), name_(name), plane_(plane), offset_(offset),
      featureId_(featureId), sk_(initial) {
  frame_ = sketch::planeFrame(plane.toStdString(), offset);
  unit_ = parseUnit(session_.document().lengthUnit()).value_or(Unit::Millimeter);
  res_ = sketch::solve(sk_);
  view_->setInteractor(this);
  view_->setGridPlane(frame_);
  // Frame the existing geometry (a new sketch keeps the current zoom).
  if (sk_.points.size() > 1) {
    double x0 = 0, y0 = 0, x1 = 0, y1 = 0;
    for (const auto& p : sk_.points) {
      x0 = std::min(x0, p.x), y0 = std::min(y0, p.y), x1 = std::max(x1, p.x), y1 = std::max(y1, p.y);
    }
    for (const auto& e : sk_.entities)
      if (e.type != EntityType::Line) {
        const auto& c = sk_.points[e.center];
        x0 = std::min(x0, c.x - e.radius), y0 = std::min(y0, c.y - e.radius);
        x1 = std::max(x1, c.x + e.radius), y1 = std::max(y1, c.y + e.radius);
      }
    const double size = std::max({x1 - x0, y1 - y0, 1.0}) * 1.6;
    view_->lookAt(frame_, size, sketch::toWorld(frame_, (x0 + x1) / 2, (y0 + y1) / 2));
  } else {
    view_->lookAt(frame_);
  }
  setTool(Tool::Line);
  connect(&Theme::instance(), &Theme::changed, this, [this] { rebuild(); });
  rebuild();
}

SketchEditor::~SketchEditor() {
  delete valueBox_.data();   // its callbacks refer to this editor
  if (!view_) return;
  clearPreview();
  const auto& ctx = view_->aisContext();
  if (!ctx.IsNull())
    for (auto& o : objects_) ctx->Remove(o, false);
  objects_.clear();
  view_->setInteractor(nullptr);
  view_->setGridPlane(sketch::planeFrame("XY"));
  view_->redraw();
}

// ---------------------------------------------------------------------------
void SketchEditor::setTool(Tool t) {
  resetSteps();
  tool_ = t;
  selection_.clear();
  clearPreview();
  switch (t) {
    case Tool::Select: emit message(tr("Select: click to select, drag points or lines to move them, Delete removes.")); break;
    case Tool::Line: emit message(tr("Line: click points, or type the length (Tab: angle) and press Enter. Click the first point to close.")); break;
    case Tool::Rectangle: emit message(tr("Rectangle: click a corner; type width, Tab, height, Enter (or click the other corner).")); break;
    case Tool::Circle: emit message(tr("Circle: click the centre; type the diameter and press Enter (or click).")); break;
    case Tool::Arc: emit message(tr("Arc: click the centre, the start, then the end (counter-clockwise).")); break;
    case Tool::Point: emit message(tr("Point: click to place points.")); break;
    case Tool::Dimension: emit message(tr("Dimension: click a line, circle or arc; or two points/lines. Type the value, Enter.")); break;
    case Tool::Coincident: emit message(tr("Coincident: click two points, or a point and a curve.")); break;
    case Tool::HorizontalVertical: emit message(tr("Horizontal/Vertical: click a line.")); break;
    case Tool::Parallel: emit message(tr("Parallel: click two lines.")); break;
    case Tool::Perpendicular: emit message(tr("Perpendicular: click two lines.")); break;
    case Tool::Equal: emit message(tr("Equal: click two lines, or two circles/arcs.")); break;
    case Tool::Tangent: emit message(tr("Tangent: click a line and a circle/arc, or two circles/arcs.")); break;
    case Tool::Fix: emit message(tr("Fix: click a point or curve to lock it in place.")); break;
    case Tool::Midpoint: emit message(tr("Midpoint: click a point, then a line.")); break;
    case Tool::Concentric: emit message(tr("Concentric: click two circles/arcs.")); break;
    case Tool::CenterRectangle: emit message(tr("Center Rectangle: click the centre, then a corner. Type sizes in the boxes (Tab, Enter).")); break;
    case Tool::Polygon: emit message(tr("Polygon: click the centre, then a corner. The boxes take the diameter and the number of sides.")); break;
    case Tool::Slot: emit message(tr("Slot: click one end centre, then the other. The boxes take length and width.")); break;
    case Tool::Trim: emit message(tr("Trim: click the part of a curve to remove (up to the nearest crossings).")); break;
    case Tool::Collinear: emit message(tr("Collinear: click two lines.")); break;
    case Tool::Symmetry: emit message(tr("Symmetry: click two points, then the line of symmetry.")); break;
  }
  rebuild();
}

void SketchEditor::resetSteps() {
  clearHud();
  steps_.clear();
  picks_.clear();
  chainStart_ = -1;
  clearPreview();
}

void SketchEditor::escape() {
  if (valueBox_) {
    valueBox_->deleteLater();
    valueBox_ = nullptr;
    return;
  }
  if (!steps_.empty() || !picks_.empty()) {
    resetSteps();
    rebuild();
  } else if (!selection_.empty()) {
    selection_.clear();
    rebuild();
  } else if (tool_ != Tool::Select) {
    setTool(Tool::Select);
  }
}

void SketchEditor::checkpoint() {
  undo_.push_back(sk_);
  if (undo_.size() > 300) undo_.erase(undo_.begin());
  redo_.clear();
}

void SketchEditor::undo() {
  if (undo_.empty()) return;
  redo_.push_back(sk_);
  sk_ = undo_.back();
  undo_.pop_back();
  resetSteps();
  selection_.clear();
  solveAndShow();
}

void SketchEditor::redo() {
  if (redo_.empty()) return;
  undo_.push_back(sk_);
  sk_ = redo_.back();
  redo_.pop_back();
  resetSteps();
  selection_.clear();
  solveAndShow();
}

void SketchEditor::solveAndShow() {
  res_ = sketch::solve(sk_);
  rebuild();
  if (res_.ok)
    emit message(res_.dof == 0 ? tr("Fully constrained.") : tr("%n degree(s) of freedom left.", nullptr, res_.dof));
  else
    emit message(QString::fromStdString(res_.message));
  emit changed();
}

std::string SketchEditor::constrain(const Constraint& c) {
  checkpoint();
  const std::string err = sketch::addConstraintChecked(sk_, c);
  if (!err.empty()) {
    undo_.pop_back();
    emit message(QString::fromStdString(err));
    rebuild();
    return err;
  }
  solveAndShow();
  return {};
}

std::string SketchEditor::finish() {
  if (valueBox_) valueBox_->deleteLater();
  const std::string data = sk_.toJson();
  if (featureId_ < 0)
    return session_.run(doc::kCmdSketch, {{"name", name_.toStdString()},
                                         {"plane", plane_.toStdString()},
                                         {"offset", offset_},
                                         {"data", data}});
  return session_.editFeature(featureId_, {{"data", data}});
}

// ---------------------------------------------------------------------------
// Picking

bool SketchEditor::toSketch(const QPointF& pos, double& x, double& y) const {
  gp_Pnt p;
  if (!view_ || !view_->planePoint(pos, frame_, p)) return false;
  sketch::toSketch(frame_, p, x, y);
  return true;
}

double SketchEditor::tolerance() const { return (view_ ? view_->modelPerPixel() : 0.01) * 8.0; }

int SketchEditor::snapPoint(double x, double y, int exclude) const {
  int best = -1;
  double bestD = tolerance();
  for (int i = 0; i < static_cast<int>(sk_.points.size()); ++i) {
    if (i == exclude) continue;
    const double d = std::hypot(sk_.points[i].x - x, sk_.points[i].y - y);
    if (d < bestD) {
      bestD = d;
      best = i;
    }
  }
  return best;
}

void SketchEditor::snapToGrid(double& x, double& y) const {
  if (!view_ || !view_->gridSnap()) return;
  const double g = view_->gridSpacing();
  if (g <= 0) return;
  x = std::round(x / g) * g;
  y = std::round(y / g) * g;
}

QString SketchEditor::lengthText(double cm) const {
  return QStringLiteral("%1 %2").arg(fromInternal(cm, unit_), 0, 'f', unit_ == Unit::Inch ? 3 : 2)
      .arg(QString::fromUtf8(unitSymbol(unit_).data()));
}

SketchEditor::Pick SketchEditor::pickPoint(double x, double y, int exclude) const {
  Pick p;
  snapToGrid(x, y);
  p.x = x;
  p.y = y;
  const int s = snapPoint(x, y, exclude);
  if (s >= 0) {
    p.hit = {Hit::Point, s};
    p.x = sk_.points[s].x;
    p.y = sk_.points[s].y;
  }
  return p;
}

int SketchEditor::materialize(const Pick& p) {
  if (p.hit.kind == Hit::Point && p.hit.index >= 0 && p.hit.index < static_cast<int>(sk_.points.size()))
    return p.hit.index;
  return sk_.addPoint(p.x, p.y);
}

SketchEditor::Hit SketchEditor::hitEntity(double x, double y) const {
  Hit best;
  double bestD = tolerance();
  for (int i = 0; i < static_cast<int>(sk_.entities.size()); ++i) {
    const auto& e = sk_.entities[i];
    double d = 1e300;
    if (e.type == EntityType::Line) {
      const auto& a = sk_.points[e.a];
      const auto& b = sk_.points[e.b];
      d = segDistance(x, y, a.x, a.y, b.x, b.y);
    } else {
      const auto& c = sk_.points[e.center];
      d = std::abs(std::hypot(x - c.x, y - c.y) - e.radius);
      if (e.type == EntityType::Arc) {
        const double a = std::atan2(y - c.y, x - c.x);
        const auto& s = sk_.points[e.a];
        const auto& t = sk_.points[e.b];
        if (!angleInArc(a, std::atan2(s.y - c.y, s.x - c.x), std::atan2(t.y - c.y, t.x - c.x))) d = 1e300;
      }
    }
    if (d < bestD) {
      bestD = d;
      best = {Hit::Entity, i};
    }
  }
  return best;
}

SketchEditor::Hit SketchEditor::hitTest(double x, double y, bool pointsFirst) const {
  if (pointsFirst) {
    const int p = snapPoint(x, y);
    if (p >= 0) return {Hit::Point, p};
  }
  // Labels and curves: whichever is nearer wins, so a glyph next to a line
  // does not steal clicks meant for the line.
  Hit label;
  double labelD = tolerance();
  for (int i = 0; i < static_cast<int>(sk_.constraints.size()); ++i)
    if (auto a = labelAnchor(i)) {
      const double d = std::hypot(a->first - x, a->second - y);
      if (d < labelD) {
        labelD = d;
        label = {Hit::Label, i};
      }
    }
  const Hit e = hitEntity(x, y);
  if (e.kind != Hit::None) {
    double ed = 0;
    const auto& en = sk_.entities[e.index];
    if (en.type == EntityType::Line) {
      const auto& a = sk_.points[en.a];
      const auto& b = sk_.points[en.b];
      ed = segDistance(x, y, a.x, a.y, b.x, b.y);
    } else {
      const auto& c = sk_.points[en.center];
      ed = std::abs(std::hypot(x - c.x, y - c.y) - en.radius);
    }
    if (label.kind == Hit::None || ed <= labelD) return e;
  }
  if (label.kind != Hit::None) return label;
  if (!pointsFirst) {
    const int p = snapPoint(x, y);
    if (p >= 0) return {Hit::Point, p};
  }
  return {};
}

// ---------------------------------------------------------------------------
// Mouse

void SketchEditor::mousePress(QMouseEvent* e) {
  pressPos_ = e->position();
  double x, y;
  if (!toSketch(e->position(), x, y)) return;
  press(x, y, e->modifiers(), e->position());
}

void SketchEditor::clickAt(double x, double y) {
  press(x, y, Qt::NoModifier, QPointF(60, 60));
  if (tool_ == Tool::Select) {
    dragged_ = false;
    const Hit h = hitTest(x, y);
    selection_.clear();
    if (h.kind != Hit::None) selection_.push_back(h);
    dragPoint_ = dragLine_ = -1;
    rebuild();
  }
}

void SketchEditor::press(double x, double y, Qt::KeyboardModifiers, const QPointF& widgetPos) {
  // Typed sizes override the cursor (the cursor still gives the direction).
  const bool locked = hudTool() && !steps_.empty() && hudAnyLocked();
  if (hudTool() && !steps_.empty()) std::tie(x, y) = hudTarget(x, y);
  auto exact = [&](double px, double py, int exclude = -1) {
    return locked ? Pick{{}, px, py} : pickPoint(px, py, exclude);
  };
  switch (tool_) {
    case Tool::Select: {
      const Hit h = hitTest(x, y);
      dragged_ = false;
      dragX_ = x;
      dragY_ = y;
      dragPoint_ = (h.kind == Hit::Point && h.index > 0) ? h.index : -1;
      dragLine_ = (h.kind == Hit::Entity && sk_.entities[h.index].type == EntityType::Line) ? h.index : -1;
      return;
    }
    case Tool::Line: {
      if (steps_.empty()) {
        steps_.push_back(pickPoint(x, y));
        return;
      }
      checkpoint();
      const bool lockLen = hudLocked(0);
      const double len = hudValue(0);
      const int a = materialize(steps_.back());
      const Pick end = exact(x, y, a);
      if (std::hypot(end.x - sk_.points[a].x, end.y - sk_.points[a].y) < tolerance() / 2) {
        undo_.pop_back();
        return;
      }
      const int b = materialize(end);
      if (chainStart_ < 0) chainStart_ = a;
      const int l = sk_.addLine(a, b, construction_);
      autoHorizontalVertical(l);
      if (lockLen) (void)sketch::addConstraintChecked(sk_, {ConstraintType::Distance, {}, {l}, len});
      const bool closed = end.hit.kind == Hit::Point && b == chainStart_;
      clearHud();
      solveAndShow();
      if (closed) {
        resetSteps();
      } else {
        steps_ = {Pick{{Hit::Point, b}, sk_.points[b].x, sk_.points[b].y}};
      }
      return;
    }
    case Tool::Rectangle: {
      if (steps_.empty()) {
        steps_.push_back(pickPoint(x, y));
        return;
      }
      const Pick a = steps_.front();
      const Pick c = exact(x, y);
      if (std::abs(c.x - a.x) < tolerance() / 2 || std::abs(c.y - a.y) < tolerance() / 2) return;
      const bool lockW = hudLocked(0), lockH = hudLocked(1);
      const double w = hudValue(0), h = hudValue(1);
      checkpoint();
      const int p0 = materialize(a);
      const int p2 = materialize(c);
      const int p1 = sk_.addPoint(sk_.points[p2].x, sk_.points[p0].y);
      const int p3 = sk_.addPoint(sk_.points[p0].x, sk_.points[p2].y);
      const int l0 = sk_.addLine(p0, p1, construction_), l1 = sk_.addLine(p1, p2, construction_);
      const int l2 = sk_.addLine(p2, p3, construction_), l3 = sk_.addLine(p3, p0, construction_);
      for (int l : {l0, l2}) sk_.addConstraint({ConstraintType::Horizontal, {}, {l}});
      for (int l : {l1, l3}) sk_.addConstraint({ConstraintType::Vertical, {}, {l}});
      if (lockW) (void)sketch::addConstraintChecked(sk_, {ConstraintType::Distance, {}, {l0}, w});
      if (lockH) (void)sketch::addConstraintChecked(sk_, {ConstraintType::Distance, {}, {l1}, h});
      resetSteps();
      solveAndShow();
      if (!res_.ok) undo();
      return;
    }
    case Tool::CenterRectangle: {
      if (steps_.empty()) {
        steps_.push_back(pickPoint(x, y));
        return;
      }
      const Pick c = steps_.front();
      const double hx = std::abs(x - c.x), hy = std::abs(y - c.y);
      if (hx < tolerance() / 4 || hy < tolerance() / 4) return;
      const bool lockW = hudLocked(0), lockH = hudLocked(1);
      const double w = hudValue(0), h = hudValue(1);
      checkpoint();
      const int pc = materialize(c);
      const double cx = sk_.points[pc].x, cy = sk_.points[pc].y;
      const int p0 = sk_.addPoint(cx - hx, cy - hy), p1 = sk_.addPoint(cx + hx, cy - hy);
      const int p2 = sk_.addPoint(cx + hx, cy + hy), p3 = sk_.addPoint(cx - hx, cy + hy);
      const int l0 = sk_.addLine(p0, p1, construction_), l1 = sk_.addLine(p1, p2, construction_);
      const int l2 = sk_.addLine(p2, p3, construction_), l3 = sk_.addLine(p3, p0, construction_);
      const int d0 = sk_.addLine(p0, p2, true);
      sk_.addLine(p1, p3, true);
      for (int l : {l0, l2}) sk_.addConstraint({ConstraintType::Horizontal, {}, {l}});
      for (int l : {l1, l3}) sk_.addConstraint({ConstraintType::Vertical, {}, {l}});
      sk_.addConstraint({ConstraintType::Midpoint, {pc}, {d0}});
      if (lockW) (void)sketch::addConstraintChecked(sk_, {ConstraintType::Distance, {}, {l0}, w});
      if (lockH) (void)sketch::addConstraintChecked(sk_, {ConstraintType::Distance, {}, {l1}, h});
      resetSteps();
      solveAndShow();
      if (!res_.ok) undo();
      return;
    }
    case Tool::Polygon: {
      if (steps_.empty()) {
        steps_.push_back(pickPoint(x, y));
        return;
      }
      const Pick c = steps_.front();
      const double r = std::hypot(x - c.x, y - c.y);
      if (r < tolerance() / 2) return;
      const int n = polygonSides();
      const bool lockD = hudLocked(0);
      const double d = hudValue(0);
      const double a0 = std::atan2(y - c.y, x - c.x);
      checkpoint();
      const int pc = materialize(c);
      const int circle = sk_.addCircleAt(pc, r, true);
      std::vector<int> pts, lines;
      for (int i = 0; i < n; ++i) {
        const double a = a0 + 2 * kPi * i / n;
        pts.push_back(sk_.addPoint(sk_.points[pc].x + r * std::cos(a), sk_.points[pc].y + r * std::sin(a)));
      }
      for (int i = 0; i < n; ++i) lines.push_back(sk_.addLine(pts[i], pts[(i + 1) % n], construction_));
      for (int p : pts) sk_.addConstraint({ConstraintType::PointOnEntity, {p}, {circle}});
      for (int i = 1; i < n; ++i) sk_.addConstraint({ConstraintType::Equal, {}, {lines[0], lines[i]}});
      if (lockD) (void)sketch::addConstraintChecked(sk_, {ConstraintType::Diameter, {}, {circle}, d});
      resetSteps();
      solveAndShow();
      if (!res_.ok) undo();
      return;
    }
    case Tool::Slot: {
      if (steps_.empty()) {
        steps_.push_back(pickPoint(x, y));
        return;
      }
      const Pick c1 = steps_.front();
      const double len = std::hypot(x - c1.x, y - c1.y);
      if (len < tolerance() / 2) return;
      const bool lockL = hudLocked(0), lockW = hudLocked(1);
      const double width = lockW ? hudValue(1) : len / 3;
      const double r = width / 2;
      const double ux = (x - c1.x) / len, uy = (y - c1.y) / len, nx = -uy, ny = ux;
      checkpoint();
      const int pc1 = materialize(c1);
      const double x1 = sk_.points[pc1].x, y1 = sk_.points[pc1].y;
      const int pc2 = sk_.addPoint(x1 + ux * len, y1 + uy * len);
      const double x2 = sk_.points[pc2].x, y2 = sk_.points[pc2].y;
      const int a1 = sk_.addPoint(x1 + nx * r, y1 + ny * r), a2 = sk_.addPoint(x2 + nx * r, y2 + ny * r);
      const int b1 = sk_.addPoint(x1 - nx * r, y1 - ny * r), b2 = sk_.addPoint(x2 - nx * r, y2 - ny * r);
      const int la = sk_.addLine(a1, a2, construction_), lb = sk_.addLine(b2, b1, construction_);
      const int arc2 = sk_.addArc(pc2, b2, a2, construction_), arc1 = sk_.addArc(pc1, a1, b1, construction_);
      const int axis = sk_.addLine(pc1, pc2, true);
      for (int l : {la, lb})
        for (int arc : {arc1, arc2}) sk_.addConstraint({ConstraintType::Tangent, {}, {l, arc}});
      sk_.addConstraint({ConstraintType::Equal, {}, {arc1, arc2}});
      autoHorizontalVertical(axis);
      if (lockL) (void)sketch::addConstraintChecked(sk_, {ConstraintType::Distance, {}, {axis}, hudValue(0)});
      if (lockW) (void)sketch::addConstraintChecked(sk_, {ConstraintType::Radius, {}, {arc1}, r});
      resetSteps();
      solveAndShow();
      if (!res_.ok) undo();
      return;
    }
    case Tool::Trim:
      trimAt(x, y);
      return;
    case Tool::Circle: {
      if (steps_.empty()) {
        steps_.push_back(pickPoint(x, y));
        return;
      }
      const Pick c = steps_.front();
      const double r = std::hypot(x - c.x, y - c.y);
      if (r < tolerance() / 2) return;
      const bool lockD = hudLocked(0);
      checkpoint();
      const int circle = sk_.addCircleAt(materialize(c), r, construction_);
      if (lockD) (void)sketch::addConstraintChecked(sk_, {ConstraintType::Diameter, {}, {circle}, hudValue(0)});
      resetSteps();
      solveAndShow();
      return;
    }
    case Tool::Arc: {
      if (steps_.size() < 2) {
        steps_.push_back(pickPoint(x, y));
        return;
      }
      const Pick c = steps_[0], s = steps_[1];
      const double r = std::hypot(s.x - c.x, s.y - c.y);
      if (r < tolerance() / 2) {
        resetSteps();
        return;
      }
      // The end lies on the circle through the start.
      const double a = std::atan2(y - c.y, x - c.x);
      Pick end = pickPoint(c.x + r * std::cos(a), c.y + r * std::sin(a));
      checkpoint();
      const int pc = materialize(c), ps = materialize(s), pe = materialize(end);
      if (pe == ps) {
        undo_.pop_back();
        return;
      }
      sk_.addArc(pc, ps, pe, construction_);
      resetSteps();
      solveAndShow();
      return;
    }
    case Tool::Point: {
      if (snapPoint(x, y) >= 0) return;
      checkpoint();
      sk_.addPoint(x, y);
      solveAndShow();
      return;
    }
    case Tool::Dimension:
      dimensionPick(x, y, widgetPos);
      return;
    default:
      constraintPick(x, y);
      return;
  }
}

void SketchEditor::mouseMove(QMouseEvent* e) {
  double x, y;
  if (!toSketch(e->position(), x, y)) return;
  if ((e->buttons() & Qt::LeftButton) && (dragPoint_ >= 0 || dragLine_ >= 0)) {
    if (!dragged_) {
      if ((e->position() - pressPos_).manhattanLength() < 4) return;
      dragged_ = true;
      checkpoint();
    }
    sketch::Sketch trial = sk_;
    std::vector<int> locked;
    if (dragPoint_ >= 0) {
      trial.points[dragPoint_] = {x, y};
      locked = {dragPoint_};
    } else {
      const auto& l = trial.entities[dragLine_];
      for (int p : {l.a, l.b})
        if (p > 0) {
          trial.points[p].x += x - dragX_;
          trial.points[p].y += y - dragY_;
          locked.push_back(p);
        }
    }
    // Locked points that the constraints do not let move: fall back to a
    // free solve so the sketch follows as far as it can.
    auto r = sketch::solve(trial, locked);
    if (!r.ok) {
      trial = sk_;
      if (dragPoint_ >= 0) trial.points[dragPoint_] = {x, y};
      r = sketch::solve(trial);
    }
    if (r.ok) {
      sk_ = std::move(trial);
      res_ = r;
      dragX_ = x;
      dragY_ = y;
      rebuild();
    }
    return;
  }
  cursorX_ = x;
  cursorY_ = y;
  const Hit h = hitTest(x, y);
  const bool changedHover = h.kind != hover_.kind || h.index != hover_.index;
  hover_ = h;
  updatePreview(x, y);
  if (changedHover) rebuild();
}

void SketchEditor::mouseRelease(QMouseEvent* e) {
  if (tool_ != Tool::Select) return;
  const bool wasDrag = dragged_;
  dragPoint_ = dragLine_ = -1;
  dragged_ = false;
  if (wasDrag) {
    solveAndShow();
    return;
  }
  double x, y;
  if (!toSketch(e->position(), x, y)) return;
  const Hit h = hitTest(x, y);
  const bool add = e->modifiers() & (Qt::ShiftModifier | Qt::ControlModifier);
  if (!add) selection_.clear();
  if (h.kind != Hit::None) {
    auto it = std::find_if(selection_.begin(), selection_.end(),
                           [&](const Hit& s) { return s.kind == h.kind && s.index == h.index; });
    if (it != selection_.end()) selection_.erase(it);
    else selection_.push_back(h);
  }
  rebuild();
}

void SketchEditor::mouseDoubleClick(QMouseEvent* e) {
  double x, y;
  if (!toSketch(e->position(), x, y)) return;
  if (tool_ == Tool::Line) {
    resetSteps();
    rebuild();
    return;
  }
  const Hit h = hitTest(x, y);
  if (h.kind == Hit::Label && sketch::isDimension(sk_.constraints[h.index].type))
    askValue(sk_.constraints[h.index], e->position(), h.index);
}

void SketchEditor::autoHorizontalVertical(int line) {
  const auto& l = sk_.entities[line];
  const double dx = sk_.points[l.b].x - sk_.points[l.a].x;
  const double dy = sk_.points[l.b].y - sk_.points[l.a].y;
  std::optional<ConstraintType> t;
  if (std::abs(dy) <= kHVTolerance * std::abs(dx)) t = ConstraintType::Horizontal;
  else if (std::abs(dx) <= kHVTolerance * std::abs(dy)) t = ConstraintType::Vertical;
  if (t) (void)sketch::addConstraintChecked(sk_, {*t, {}, {line}});
}

// ---------------------------------------------------------------------------
// Constraints and dimensions

void SketchEditor::constraintPick(double x, double y) {
  const bool wantsEntity = tool_ == Tool::Parallel || tool_ == Tool::Perpendicular || tool_ == Tool::Equal ||
                           tool_ == Tool::Collinear || (tool_ == Tool::Symmetry && picks_.size() == 2) ||
                           tool_ == Tool::Tangent || tool_ == Tool::Concentric || tool_ == Tool::HorizontalVertical ||
                           (tool_ == Tool::Midpoint && !picks_.empty());
  Hit h = wantsEntity ? hitEntity(x, y) : hitTest(x, y);
  if (h.kind == Hit::Label || h.kind == Hit::None) return;
  picks_.push_back({h, x, y});
  rebuild();

  auto isLine = [&](const Hit& p) { return p.kind == Hit::Entity && sk_.entities[p.index].type == EntityType::Line; };
  auto isRound = [&](const Hit& p) { return p.kind == Hit::Entity && sk_.entities[p.index].type != EntityType::Line; };
  auto done = [&](std::vector<Constraint> cs) {
    picks_.clear();
    if (cs.size() == 1) {
      constrain(cs.front());
      return;
    }
    checkpoint();
    for (auto& c : cs) sk_.addConstraint(c);
    const auto r = sketch::solve(sk_);
    if (!r.ok) {
      sk_ = undo_.back();
      undo_.pop_back();
      emit message(QString::fromStdString(r.message));
    }
    solveAndShow();
  };
  auto fail = [&](const QString& why) {
    picks_.clear();
    emit message(why);
    rebuild();
  };

  const Hit a = picks_[0].hit;
  switch (tool_) {
    case Tool::HorizontalVertical: {
      if (!isLine(a)) return fail(tr("Horizontal/Vertical needs a line."));
      const auto& l = sk_.entities[a.index];
      const double dx = sk_.points[l.b].x - sk_.points[l.a].x, dy = sk_.points[l.b].y - sk_.points[l.a].y;
      return done({{std::abs(dx) >= std::abs(dy) ? ConstraintType::Horizontal : ConstraintType::Vertical, {}, {a.index}}});
    }
    case Tool::Fix: {
      if (a.kind == Hit::Point) {
        const auto& p = sk_.points[a.index];
        return done({{ConstraintType::Fix, {a.index}, {}, p.x, p.y}});
      }
      std::vector<Constraint> cs;
      for (int p : sk_.entityPoints(a.index)) cs.push_back({ConstraintType::Fix, {p}, {}, sk_.points[p].x, sk_.points[p].y});
      if (sk_.entities[a.index].type == EntityType::Circle)
        cs.push_back({ConstraintType::Radius, {}, {a.index}, sk_.entities[a.index].radius});
      return done(cs);
    }
    default:
      break;
  }
  if (picks_.size() < 2) {
    emit message(tr("Now pick the second item."));
    return;
  }
  const Hit b = picks_[1].hit;
  switch (tool_) {
    case Tool::Coincident:
      if (a.kind == Hit::Point && b.kind == Hit::Point) {
        if (a.index == b.index) return fail(tr("Pick two different points."));
        return done({{ConstraintType::Coincident, {a.index, b.index}}});
      }
      if (a.kind == Hit::Point && b.kind == Hit::Entity) return done({{ConstraintType::PointOnEntity, {a.index}, {b.index}}});
      if (a.kind == Hit::Entity && b.kind == Hit::Point) return done({{ConstraintType::PointOnEntity, {b.index}, {a.index}}});
      return fail(tr("Coincident needs a point and a point or curve."));
    case Tool::Parallel:
    case Tool::Perpendicular:
      if (!isLine(a) || !isLine(b) || a.index == b.index) return fail(tr("Pick two different lines."));
      return done({{tool_ == Tool::Parallel ? ConstraintType::Parallel : ConstraintType::Perpendicular, {}, {a.index, b.index}}});
    case Tool::Equal:
      if (a.index == b.index || !((isLine(a) && isLine(b)) || (isRound(a) && isRound(b))))
        return fail(tr("Pick two lines, or two circles/arcs."));
      return done({{ConstraintType::Equal, {}, {a.index, b.index}}});
    case Tool::Tangent: {
      if (a.index == b.index || (isLine(a) && isLine(b))) return fail(tr("Pick a line and a circle/arc, or two circles/arcs."));
      double internal = 0;
      if (isRound(a) && isRound(b)) {
        const auto& e1 = sk_.entities[a.index];
        const auto& e2 = sk_.entities[b.index];
        const double d = std::hypot(sk_.points[e1.center].x - sk_.points[e2.center].x,
                                    sk_.points[e1.center].y - sk_.points[e2.center].y);
        internal = d < std::max(e1.radius, e2.radius) ? 1 : 0;
      }
      return done({{ConstraintType::Tangent, {}, {a.index, b.index}, internal}});
    }
    case Tool::Concentric:
      if (!isRound(a) || !isRound(b) || a.index == b.index) return fail(tr("Pick two circles/arcs."));
      return done({{ConstraintType::Concentric, {}, {a.index, b.index}}});
    case Tool::Collinear:
      if (!isLine(a) || !isLine(b) || a.index == b.index) return fail(tr("Pick two different lines."));
      return done({{ConstraintType::Collinear, {}, {a.index, b.index}}});
    case Tool::Symmetry: {
      if (picks_.size() < 3) {
        if (a.kind != Hit::Point || b.kind != Hit::Point) return fail(tr("Pick two points first, then the line."));
        emit message(tr("Now pick the line of symmetry."));
        return;
      }
      const Hit l = picks_[2].hit;
      if (!isLine(l)) return fail(tr("The third pick must be a line."));
      return done({{ConstraintType::Symmetry, {a.index, b.index}, {l.index}}});
    }
    case Tool::Midpoint:
      if (a.kind != Hit::Point || !isLine(b)) return fail(tr("Pick a point, then a line."));
      return done({{ConstraintType::Midpoint, {a.index}, {b.index}}});
    default:
      return fail(QString());
  }
}

void SketchEditor::dimensionPick(double x, double y, const QPointF& widgetPos) {
  const Hit h = hitTest(x, y);
  auto isLine = [&](const Hit& p) { return p.kind == Hit::Entity && sk_.entities[p.index].type == EntityType::Line; };

  if (picks_.empty()) {
    if (h.kind == Hit::None) return;
    if (h.kind == Hit::Label) {
      if (sketch::isDimension(sk_.constraints[h.index].type)) askValue(sk_.constraints[h.index], widgetPos, h.index);
      return;
    }
    if (h.kind == Hit::Entity && !isLine(h)) {
      const bool arc = sk_.entities[h.index].type == EntityType::Arc;
      askValue({arc ? ConstraintType::Radius : ConstraintType::Diameter, {}, {h.index}}, widgetPos);
      return;
    }
    picks_.push_back({h, x, y});
    emit message(isLine(h) ? tr("Click empty space for the line's length, or another line (angle) or point (distance).")
                           : tr("Pick a second point or a line."));
    rebuild();
    return;
  }
  const Hit a = picks_[0].hit;
  picks_.clear();
  rebuild();
  if (h.kind == Hit::None || h.kind == Hit::Label || (h.kind == a.kind && h.index == a.index)) {
    if (isLine(a)) askValue({ConstraintType::Distance, {}, {a.index}}, widgetPos);
    return;
  }
  if (isLine(a) && isLine(h)) {
    askValue({ConstraintType::Angle, {}, {a.index, h.index}}, widgetPos);
  } else if (a.kind == Hit::Point && h.kind == Hit::Point) {
    // Mostly horizontal or vertical pairs get the matching dimension.
    const auto& p = sk_.points[a.index];
    const auto& q = sk_.points[h.index];
    const double dx = std::abs(q.x - p.x), dy = std::abs(q.y - p.y);
    ConstraintType t = ConstraintType::Distance;
    if (dy < 1e-9 * (1 + dx) || dy < 0.05 * dx) t = ConstraintType::HorizontalDistance;
    else if (dx < 0.05 * dy) t = ConstraintType::VerticalDistance;
    askValue({t, {a.index, h.index}}, widgetPos);
  } else if (a.kind == Hit::Point && isLine(h)) {
    askValue({ConstraintType::Distance, {a.index}, {h.index}}, widgetPos);
  } else if (isLine(a) && h.kind == Hit::Point) {
    askValue({ConstraintType::Distance, {h.index}, {a.index}}, widgetPos);
  }
}

double SketchEditor::currentValue(const Constraint& c) const {
  const auto& P = sk_.points;
  auto len = [&](int l) {
    const auto& e = sk_.entities[l];
    return std::hypot(P[e.b].x - P[e.a].x, P[e.b].y - P[e.a].y);
  };
  switch (c.type) {
    case ConstraintType::Distance:
      if (c.points.size() == 2) return std::hypot(P[c.points[1]].x - P[c.points[0]].x, P[c.points[1]].y - P[c.points[0]].y);
      if (c.points.size() == 1) {
        const auto& e = sk_.entities[c.entities[0]];
        const double dx = P[e.b].x - P[e.a].x, dy = P[e.b].y - P[e.a].y;
        const auto& p = P[c.points[0]];
        return std::abs(dx * (p.y - P[e.a].y) - dy * (p.x - P[e.a].x)) / std::max(std::hypot(dx, dy), 1e-12);
      }
      return len(c.entities[0]);
    case ConstraintType::HorizontalDistance: return P[c.points[1]].x - P[c.points[0]].x;
    case ConstraintType::VerticalDistance: return P[c.points[1]].y - P[c.points[0]].y;
    case ConstraintType::Radius: return sk_.entities[c.entities[0]].radius;
    case ConstraintType::Diameter: return 2 * sk_.entities[c.entities[0]].radius;
    case ConstraintType::Angle: {
      const auto& e1 = sk_.entities[c.entities[0]];
      const auto& e2 = sk_.entities[c.entities[1]];
      const double x1 = P[e1.b].x - P[e1.a].x, y1 = P[e1.b].y - P[e1.a].y;
      const double x2 = P[e2.b].x - P[e2.a].x, y2 = P[e2.b].y - P[e2.a].y;
      return std::atan2(x1 * y2 - y1 * x2, x1 * x2 + y1 * y2);
    }
    default:
      return c.value;
  }
}

void SketchEditor::askValue(const Constraint& c, const QPointF& widgetPos, int editIndex) {
  if (valueBox_) valueBox_->deleteLater();
  const bool angle = c.type == ConstraintType::Angle;
  const Unit unit = angle ? Unit::Degree : unit_;
  const double v = editIndex >= 0 ? c.value : currentValue(c);
  auto* box = new QLineEdit(view_);
  valueBox_ = box;
  box->setObjectName(QStringLiteral("dimensionValue"));
  box->setText(QString::number(fromInternal(v, unit), 'f', angle ? 2 : 3) + QStringLiteral(" ") +
               QString::fromUtf8(unitSymbol(unit).data()));
  box->setFixedWidth(120);
  box->move(widgetPos.toPoint() + QPoint(12, -12));
  box->show();
  box->setFocus();
  box->selectAll();
  emit message(tr("Type the value (units optional) and press Enter; Esc cancels."));

  const Constraint base = c;
  connect(box, &QLineEdit::returnPressed, this, [this, box, base, unit, editIndex] {
    const auto value = parseQuantity(box->text().toStdString(), unit);
    if (!value) {
      emit message(tr("'%1' is not a valid value.").arg(box->text()));
      return;
    }
    if (base.type != ConstraintType::Angle && base.type != ConstraintType::HorizontalDistance &&
        base.type != ConstraintType::VerticalDistance && *value <= 0) {
      emit message(tr("The value must be greater than zero."));
      return;
    }
    valueBox_ = nullptr;
    box->deleteLater();
    if (editIndex >= 0) {
      checkpoint();
      sk_.constraints[editIndex].value = *value;
      const auto r = sketch::solve(sk_);
      if (!r.ok) {
        sk_ = undo_.back();
        undo_.pop_back();
        emit message(tr("That value cannot be met by the other constraints."));
        rebuild();
        return;
      }
      solveAndShow();
      return;
    }
    Constraint c2 = base;
    c2.value = *value;
    constrain(c2);
  });
  connect(box, &QLineEdit::editingFinished, this, [this, box] {
    if (valueBox_ == box) valueBox_ = nullptr;
    box->deleteLater();
  });
}

// ---------------------------------------------------------------------------
// On-canvas size boxes

bool SketchEditor::hudTool() const {
  switch (tool_) {
    case Tool::Line:
    case Tool::Rectangle:
    case Tool::CenterRectangle:
    case Tool::Circle:
    case Tool::Polygon:
    case Tool::Slot:
      return true;
    default:
      return false;
  }
}

bool SketchEditor::hudAnyLocked() const {
  for (size_t i = 0; i < hud_.size(); ++i)
    if (hud_[i].locked && hud_[i].kind != HudField::Count) return true;
  return false;
}

int SketchEditor::polygonSides() const {
  if (tool_ == Tool::Polygon && hud_.size() > 1 && hud_[1].locked) return std::clamp(static_cast<int>(hud_[1].value), 3, 64);
  return 6;
}

void SketchEditor::clearHud() {
  for (auto& f : hud_)
    if (f.edit) {
      f.edit->removeEventFilter(this);
      f.edit->deleteLater();
    }
  hud_.clear();
  if (view_) view_->setFocus();
}

void SketchEditor::ensureHud() {
  if (!view_ || !hudTool() || steps_.empty()) {
    if (!hud_.empty()) clearHud();
    return;
  }
  if (!hud_.empty()) return;
  std::vector<std::pair<HudField::Kind, QString>> fields;
  switch (tool_) {
    case Tool::Line: fields = {{HudField::Length, tr("Length")}, {HudField::Angle, tr("Angle")}}; break;
    case Tool::Rectangle:
    case Tool::CenterRectangle: fields = {{HudField::Length, tr("Width")}, {HudField::Length, tr("Height")}}; break;
    case Tool::Circle: fields = {{HudField::Length, tr("Diameter")}}; break;
    case Tool::Polygon: fields = {{HudField::Length, tr("Diameter")}, {HudField::Count, tr("Sides")}}; break;
    case Tool::Slot: fields = {{HudField::Length, tr("Length")}, {HudField::Length, tr("Width")}}; break;
    default: return;
  }
  for (const auto& [kind, name] : fields) {
    HudField f;
    f.kind = kind;
    auto* e = new QLineEdit(view_);
    e->setObjectName(QStringLiteral("hud") + name);
    e->setToolTip(tr("%1: type a value, Tab for the next box, Enter to create").arg(name));
    e->setAlignment(Qt::AlignCenter);
    e->setFixedWidth(kind == HudField::Count ? 60 : 110);
    e->setStyleSheet(QStringLiteral("QLineEdit { background: rgba(30,34,40,215); color: #f0f2f5; border: 1px solid #5b6472;"
                                    " border-radius: 3px; padding: 2px; }"
                                    "QLineEdit[locked=\"true\"] { border: 2px solid #3d8ee8; font-weight: bold; }"));
    e->installEventFilter(this);
    const size_t index = hud_.size();
    connect(e, &QLineEdit::textEdited, this, [this, index] {
      if (index < hud_.size()) hud_[index].editing = true;
    });
    e->show();
    f.edit = e;
    hud_.push_back(f);
  }
}

bool SketchEditor::lockField(size_t i) {
  if (i >= hud_.size() || !hud_[i].edit || !hud_[i].editing) return i < hud_.size() && hud_[i].locked;
  HudField& f = hud_[i];
  const std::string text = f.edit->text().trimmed().toStdString();
  std::optional<double> v;
  if (f.kind == HudField::Count) {
    try {
      v = static_cast<double>(std::stoi(text));
    } catch (...) {
    }
  } else {
    v = parseQuantity(text, f.kind == HudField::Angle ? Unit::Degree : unit_);
  }
  f.editing = false;
  if (!v || (f.kind != HudField::Angle && *v <= 0)) {
    emit message(tr("'%1' is not a valid value.").arg(f.edit->text()));
    f.locked = false;
    f.edit->setProperty("locked", false);
    return false;
  }
  f.value = *v;
  f.locked = true;
  f.edit->setProperty("locked", true);
  f.edit->style()->unpolish(f.edit);
  f.edit->style()->polish(f.edit);
  return true;
}

std::pair<double, double> SketchEditor::hudTarget(double x, double y) const {
  if (steps_.empty()) return {x, y};
  const Pick& a = steps_.back();
  double dx = x - a.x, dy = y - a.y;
  const double dist = std::hypot(dx, dy);
  const double ux = dist > 1e-12 ? dx / dist : 1, uy = dist > 1e-12 ? dy / dist : 0;
  switch (tool_) {
    case Tool::Line: {
      const double len = hudLocked(0) ? hudValue(0) : dist;
      double ang = std::atan2(uy, ux);
      if (hudLocked(1)) ang = hudValue(1);
      return {a.x + len * std::cos(ang), a.y + len * std::sin(ang)};
    }
    case Tool::Rectangle:
    case Tool::CenterRectangle: {
      const double scale = tool_ == Tool::CenterRectangle ? 0.5 : 1.0;
      const double sx = dx < 0 ? -1 : 1, sy = dy < 0 ? -1 : 1;
      const double w = hudLocked(0) ? hudValue(0) * scale : std::abs(dx);
      const double h = hudLocked(1) ? hudValue(1) * scale : std::abs(dy);
      return {a.x + sx * w, a.y + sy * h};
    }
    case Tool::Circle:
    case Tool::Polygon: {
      const double r = hudLocked(0) ? hudValue(0) / 2 : dist;
      return {a.x + ux * r, a.y + uy * r};
    }
    case Tool::Slot: {
      const double len = hudLocked(0) ? hudValue(0) : dist;
      return {a.x + ux * len, a.y + uy * len};
    }
    default:
      return {x, y};
  }
}

void SketchEditor::updateHud(double x, double y) {
  if (hud_.empty() || steps_.empty() || !view_) return;
  const Pick& a = steps_.back();
  const double dx = x - a.x, dy = y - a.y;
  const double dist = std::hypot(dx, dy);
  // Live values and where each box sits (sketch coordinates).
  std::vector<std::pair<double, std::pair<double, double>>> live;
  const double off = view_->modelPerPixel() * 22;
  switch (tool_) {
    case Tool::Line:
      live = {{dist, {(a.x + x) / 2, (a.y + y) / 2 + off}}, {std::atan2(dy, dx), {a.x + off * 2, a.y - off}}};
      break;
    case Tool::Rectangle:
      live = {{std::abs(dx), {(a.x + x) / 2, std::max(a.y, y) + off}}, {std::abs(dy), {std::max(a.x, x) + off * 3, (a.y + y) / 2}}};
      break;
    case Tool::CenterRectangle:
      live = {{2 * std::abs(dx), {a.x, a.y + std::abs(dy) + off}}, {2 * std::abs(dy), {a.x + std::abs(dx) + off * 3, a.y}}};
      break;
    case Tool::Circle:
      live = {{2 * dist, {a.x + dist * 0.7071 + off, a.y + dist * 0.7071 + off}}};
      break;
    case Tool::Polygon:
      live = {{2 * dist, {a.x + dist + off * 3, a.y}}, {static_cast<double>(polygonSides()), {a.x, a.y - off * 1.5}}};
      break;
    case Tool::Slot:
      live = {{dist, {(a.x + x) / 2, (a.y + y) / 2 + off * 2}},
              {hudLocked(1) ? hudValue(1) : dist / 3, {x + off * 3, y}}};
      break;
    default:
      return;
  }
  for (size_t i = 0; i < hud_.size() && i < live.size(); ++i) {
    HudField& f = hud_[i];
    if (!f.edit) continue;
    if (!f.locked && !f.editing) {
      if (f.kind == HudField::Angle)
        f.edit->setText(QStringLiteral("%1 deg").arg(live[i].first * 180.0 / kPi, 0, 'f', 1));
      else if (f.kind == HudField::Count)
        f.edit->setText(QString::number(static_cast<int>(live[i].first)));
      else
        f.edit->setText(lengthText(live[i].first));
    }
    const QPointF w = view_->toWidget(sketch::toWorld(frame_, live[i].second.first, live[i].second.second));
    f.edit->move(QPoint(static_cast<int>(w.x() - f.edit->width() / 2), static_cast<int>(w.y() - f.edit->height() / 2)));
    f.edit->raise();
  }
}

void SketchEditor::commitHud() {
  for (size_t i = 0; i < hud_.size(); ++i) lockField(i);
  const QPointF centre = view_ ? QPointF(view_->width() / 2.0, view_->height() / 2.0) : QPointF(60, 60);
  press(cursorX_, cursorY_, Qt::NoModifier, centre);
}

bool SketchEditor::eventFilter(QObject* watched, QEvent* e) {
  if (e->type() != QEvent::KeyPress) return QObject::eventFilter(watched, e);
  size_t i = 0;
  while (i < hud_.size() && hud_[i].edit != watched) ++i;
  if (i == hud_.size()) return QObject::eventFilter(watched, e);
  auto* k = static_cast<QKeyEvent*>(e);
  switch (k->key()) {
    case Qt::Key_Tab:
    case Qt::Key_Backtab: {
      lockField(i);
      const size_t next = k->key() == Qt::Key_Tab ? (i + 1) % hud_.size() : (i + hud_.size() - 1) % hud_.size();
      if (hud_[next].edit) {
        hud_[next].edit->setFocus();
        hud_[next].edit->selectAll();
      }
      updatePreview(cursorX_, cursorY_);
      return true;
    }
    case Qt::Key_Return:
    case Qt::Key_Enter:
      commitHud();
      return true;
    case Qt::Key_Escape:
      escape();
      return true;
    default:
      return false;
  }
}

bool SketchEditor::keyPress(QKeyEvent* e) {
  // Typing while drawing goes into the first size box (like the on-canvas input).
  if (!hudTool() || steps_.empty()) return false;
  ensureHud();
  if (hud_.empty() || !hud_[0].edit) return false;
  if (e->key() == Qt::Key_Tab) {
    hud_[0].edit->setFocus();
    hud_[0].edit->selectAll();
    return true;
  }
  const QString t = e->text();
  if (t.isEmpty() || !(t[0].isDigit() || t[0] == QLatin1Char('.') || t[0] == QLatin1Char('-'))) return false;
  hud_[0].edit->setFocus();
  hud_[0].edit->setText(t);
  hud_[0].editing = true;
  return true;
}

bool SketchEditor::typeValue(const QString& text) {
  if (steps_.empty() || !hudTool()) return false;
  ensureHud();
  const QStringList parts = text.split(QRegularExpression(QStringLiteral("[xX*,]")), Qt::SkipEmptyParts);
  if (parts.isEmpty()) return false;
  for (int i = 0; i < parts.size() && i < static_cast<int>(hud_.size()); ++i) {
    if (!hud_[i].edit) continue;
    hud_[i].edit->setText(parts[i].trimmed());
    hud_[i].editing = true;
    if (!lockField(i)) return false;
  }
  // A single value for a rectangle means a square.
  if ((tool_ == Tool::Rectangle || tool_ == Tool::CenterRectangle) && parts.size() == 1 && hud_.size() > 1) {
    hud_[1].value = hud_[0].value;
    hud_[1].locked = true;
  }
  const size_t before = sk_.entities.size();
  commitHud();
  return sk_.entities.size() > before;
}

// ---------------------------------------------------------------------------
// Trim

void SketchEditor::trimAt(double x, double y) {
  const Hit h = hitEntity(x, y);
  if (h.kind != Hit::Entity) return;
  const int ei = h.index;
  const auto& P = sk_.points;
  const Entity target = sk_.entities[ei];

  // Intersections of the picked curve with every other curve, as parameters
  // along it: t in [0,1] for lines, angle for circles/arcs.
  std::vector<double> cuts;
  auto lineCircle = [&](double ax, double ay, double bx, double by, double cx, double cy, double r,
                        std::vector<std::pair<double, double>>& out) {
    const double dx = bx - ax, dy = by - ay;
    const double fx = ax - cx, fy = ay - cy;
    const double A = dx * dx + dy * dy, B = 2 * (fx * dx + fy * dy), Cc = fx * fx + fy * fy - r * r;
    const double disc = B * B - 4 * A * Cc;
    if (A < 1e-18 || disc < 0) return;
    for (double sgn : {-1.0, 1.0}) {
      const double t = (-B + sgn * std::sqrt(disc)) / (2 * A);
      out.emplace_back(t, std::atan2(ay + t * dy - cy, ax + t * dx - cx));
    }
  };
  auto onArc = [&](const Entity& e, double ang) {
    if (e.type != EntityType::Arc) return true;
    const auto& c = P[e.center];
    return angleInArc(ang, std::atan2(P[e.a].y - c.y, P[e.a].x - c.x), std::atan2(P[e.b].y - c.y, P[e.b].x - c.x));
  };
  for (int j = 0; j < static_cast<int>(sk_.entities.size()); ++j) {
    if (j == ei) continue;
    const Entity& o = sk_.entities[j];
    if (target.type == EntityType::Line) {
      const auto &a = P[target.a], &b = P[target.b];
      if (o.type == EntityType::Line) {
        const auto &c = P[o.a], &d = P[o.b];
        const double den = (b.x - a.x) * (d.y - c.y) - (b.y - a.y) * (d.x - c.x);
        if (std::abs(den) < 1e-14) continue;
        const double t = ((c.x - a.x) * (d.y - c.y) - (c.y - a.y) * (d.x - c.x)) / den;
        const double u = ((c.x - a.x) * (b.y - a.y) - (c.y - a.y) * (b.x - a.x)) / den;
        if (u >= -1e-9 && u <= 1 + 1e-9) cuts.push_back(t);
      } else {
        std::vector<std::pair<double, double>> hits;
        lineCircle(a.x, a.y, b.x, b.y, P[o.center].x, P[o.center].y, o.radius, hits);
        for (const auto& [t, ang] : hits)
          if (onArc(o, ang)) cuts.push_back(t);
      }
    } else {
      const auto& c = P[target.center];
      if (o.type == EntityType::Line) {
        std::vector<std::pair<double, double>> hits;
        lineCircle(P[o.a].x, P[o.a].y, P[o.b].x, P[o.b].y, c.x, c.y, target.radius, hits);
        for (const auto& [t, ang] : hits)
          if (t >= -1e-9 && t <= 1 + 1e-9) cuts.push_back(ang);
      } else {
        const auto& c2 = P[o.center];
        const double d = std::hypot(c2.x - c.x, c2.y - c.y);
        if (d < 1e-12 || d > target.radius + o.radius || d < std::abs(target.radius - o.radius)) continue;
        const double base = std::atan2(c2.y - c.y, c2.x - c.x);
        const double half = std::acos(std::clamp((target.radius * target.radius + d * d - o.radius * o.radius) /
                                                     (2 * target.radius * d), -1.0, 1.0));
        for (double ang : {base - half, base + half}) {
          const double px = c.x + target.radius * std::cos(ang), py = c.y + target.radius * std::sin(ang);
          if (onArc(o, std::atan2(py - c2.y, px - c2.x))) cuts.push_back(ang);
        }
      }
    }
  }

  checkpoint();
  auto detachPoint = [&](int pt) {
    // Remove a point that no curve uses any more.
    for (const auto& e : sk_.entities)
      if (e.a == pt || e.b == pt || e.center == pt) return;
    if (pt > 0) sk_.removePoints({pt});
  };
  // Constraints that only hold for the whole curve are dropped.
  auto dropDimensions = [&](int entity) {
    for (int k = static_cast<int>(sk_.constraints.size()) - 1; k >= 0; --k) {
      const auto& c = sk_.constraints[k];
      const bool refs = std::find(c.entities.begin(), c.entities.end(), entity) != c.entities.end();
      const bool keep = c.type == ConstraintType::Horizontal || c.type == ConstraintType::Vertical ||
                        c.type == ConstraintType::Parallel || c.type == ConstraintType::Perpendicular ||
                        c.type == ConstraintType::Collinear || c.type == ConstraintType::Concentric ||
                        c.type == ConstraintType::Radius || c.type == ConstraintType::Diameter;
      if (refs && !keep) sk_.removeConstraint(k);
    }
  };

  if (target.type == EntityType::Line) {
    const auto a = P[target.a], b = P[target.b];
    const double dx = b.x - a.x, dy = b.y - a.y, l2 = dx * dx + dy * dy;
    const double t0 = l2 > 0 ? ((x - a.x) * dx + (y - a.y) * dy) / l2 : 0;
    double lo = -1, hi = 2;
    for (double t : cuts) {
      if (t > 1e-6 && t < t0 && t > lo) lo = t;
      if (t < 1 - 1e-6 && t > t0 && t < hi) hi = t;
    }
    const bool hasLo = lo > 0, hasHi = hi < 1;
    if (!hasLo && !hasHi) {
      sk_.removeEntities({ei});
    } else {
      dropDimensions(ei);
      const int oldA = target.a, oldB = target.b;
      if (hasLo && hasHi) {
        const int pl = sk_.addPoint(a.x + dx * lo, a.y + dy * lo);
        const int ph = sk_.addPoint(a.x + dx * hi, a.y + dy * hi);
        sk_.entities[ei].b = pl;
        sk_.addLine(ph, oldB, target.construction);
      } else if (hasLo) {
        sk_.entities[ei].b = sk_.addPoint(a.x + dx * lo, a.y + dy * lo);
        detachPoint(oldB);
      } else {
        sk_.entities[ei].a = sk_.addPoint(a.x + dx * hi, a.y + dy * hi);
        detachPoint(oldA);
      }
    }
  } else {
    const auto c = P[target.center];
    const double r = target.radius;
    const double clickAng = std::atan2(y - c.y, x - c.x);
    auto norm = [](double v) {
      while (v < 0) v += 2 * kPi;
      while (v >= 2 * kPi) v -= 2 * kPi;
      return v;
    };
    if (target.type == EntityType::Circle) {
      if (cuts.size() < 2) {
        sk_.removeEntities({ei});
      } else {
        // Keep the arc from the first crossing after the click round to the last one before it.
        double after = 1e9, before = 1e9, angAfter = 0, angBefore = 0;
        for (double ang : cuts) {
          const double da = norm(ang - clickAng), db = norm(clickAng - ang);
          if (da > 1e-9 && da < after) after = da, angAfter = ang;
          if (db > 1e-9 && db < before) before = db, angBefore = ang;
        }
        dropDimensions(ei);
        Entity& e = sk_.entities[ei];
        e.type = EntityType::Arc;
        e.a = sk_.addPoint(c.x + r * std::cos(angAfter), c.y + r * std::sin(angAfter));
        e.b = sk_.addPoint(c.x + r * std::cos(angBefore), c.y + r * std::sin(angBefore));
      }
    } else {
      const double start = std::atan2(P[target.a].y - c.y, P[target.a].x - c.x);
      const double span = norm(std::atan2(P[target.b].y - c.y, P[target.b].x - c.x) - start);
      const double u0 = norm(clickAng - start);
      double lo = -1, hi = 1e9;
      for (double ang : cuts) {
        const double u = norm(ang - start);
        if (u <= 1e-6 || u >= span - 1e-6) continue;
        if (u < u0 && u > lo) lo = u;
        if (u > u0 && u < hi) hi = u;
      }
      const bool hasLo = lo > 0, hasHi = hi < 1e8;
      if (!hasLo && !hasHi) {
        sk_.removeEntities({ei});
      } else {
        dropDimensions(ei);
        const int oldA = target.a, oldB = target.b, centre = target.center;
        auto at = [&](double u) { return sk_.addPoint(c.x + r * std::cos(start + u), c.y + r * std::sin(start + u)); };
        if (hasLo && hasHi) {
          const int pl = at(lo), ph = at(hi);
          sk_.entities[ei].b = pl;
          sk_.addArc(centre, ph, oldB, target.construction);
        } else if (hasLo) {
          sk_.entities[ei].b = at(lo);
          detachPoint(oldB);
        } else {
          sk_.entities[ei].a = at(hi);
          detachPoint(oldA);
        }
      }
    }
  }
  selection_.clear();
  solveAndShow();
}

bool SketchEditor::submitValue(const QString& text) {
  if (!valueBox_) return false;
  valueBox_->setText(text);
  emit valueBox_->returnPressed();
  return true;
}

void SketchEditor::deleteSelection() {
  if (selection_.empty()) return;
  std::vector<int> ents, pts, cons;
  for (const auto& h : selection_) {
    if (h.kind == Hit::Entity) ents.push_back(h.index);
    else if (h.kind == Hit::Point && h.index > 0) pts.push_back(h.index);
    else if (h.kind == Hit::Label) cons.push_back(h.index);
  }
  checkpoint();
  std::sort(cons.rbegin(), cons.rend());
  for (int c : cons) sk_.removeConstraint(c);
  sk_.removeItems(ents, pts);
  selection_.clear();
  solveAndShow();
}

// ---------------------------------------------------------------------------
// Display

std::optional<std::pair<double, double>> SketchEditor::labelAnchor(int ci) const {
  const Constraint& c = sk_.constraints.at(ci);
  const double px = view_ ? view_->modelPerPixel() : 0.01;
  const auto& P = sk_.points;
  auto lineMid = [&](int l, double off, double& x, double& y) {
    const auto& e = sk_.entities[l];
    const double dx = P[e.b].x - P[e.a].x, dy = P[e.b].y - P[e.a].y;
    const double n = std::max(std::hypot(dx, dy), 1e-12);
    x = (P[e.a].x + P[e.b].x) / 2 - dy / n * off;
    y = (P[e.a].y + P[e.b].y) / 2 + dx / n * off;
  };
  // Stack geometric glyphs on the same entity.
  int stack = 0;
  for (int i = 0; i < ci; ++i)
    if (!sketch::isDimension(sk_.constraints[i].type) && !c.entities.empty() && !sk_.constraints[i].entities.empty() &&
        sk_.constraints[i].entities[0] == c.entities[0])
      ++stack;
  double x = 0, y = 0;
  switch (c.type) {
    case ConstraintType::Coincident:
    case ConstraintType::PointOnEntity:
      return std::nullopt;   // shown by the geometry itself
    case ConstraintType::Fix:
      return std::make_pair(P[c.points[0]].x + 10 * px, P[c.points[0]].y + 10 * px);
    case ConstraintType::Distance:
    case ConstraintType::HorizontalDistance:
    case ConstraintType::VerticalDistance:
      if (c.points.size() == 2) {
        const auto& p = P[c.points[0]];
        const auto& q = P[c.points[1]];
        if (c.type == ConstraintType::HorizontalDistance)   // above the pair
          return std::make_pair((p.x + q.x) / 2, std::max(p.y, q.y) + 14 * px);
        if (c.type == ConstraintType::VerticalDistance)     // left of the pair
          return std::make_pair(std::min(p.x, q.x) - 24 * px, (p.y + q.y) / 2);
        return std::make_pair((p.x + q.x) / 2, (p.y + q.y) / 2 + 14 * px);
      }
      if (c.points.size() == 1) {
        lineMid(c.entities[0], 0, x, y);
        return std::make_pair((x + P[c.points[0]].x) / 2, (y + P[c.points[0]].y) / 2);
      }
      lineMid(c.entities[0], 16 * px, x, y);
      return std::make_pair(x, y);
    case ConstraintType::Radius:
    case ConstraintType::Diameter:
    case ConstraintType::Concentric: {
      const auto& e = sk_.entities[c.entities[0]];
      const double r = e.radius + (c.type == ConstraintType::Concentric ? 10 * px : 14 * px);
      return std::make_pair(P[e.center].x + r * 0.7071, P[e.center].y + r * 0.7071);
    }
    case ConstraintType::Angle: {
      double x2, y2;
      lineMid(c.entities[0], 0, x, y);
      lineMid(c.entities[1], 0, x2, y2);
      return std::make_pair((x + x2) / 2 + 10 * px, (y + y2) / 2 + 10 * px);
    }
    case ConstraintType::Midpoint:
      return std::make_pair(P[c.points[0]].x + 9 * px, P[c.points[0]].y - 9 * px);
    default: {
      if (c.entities.empty()) {   // e.g. horizontal between two points
        if (c.points.size() < 2) return std::nullopt;
        return std::make_pair((P[c.points[0]].x + P[c.points[1]].x) / 2,
                              (P[c.points[0]].y + P[c.points[1]].y) / 2 + 10 * px);
      }
      const int e = c.entities[0];
      if (sk_.entities[e].type == EntityType::Line) {
        lineMid(e, -(10 + 12 * stack) * px, x, y);
      } else {
        const auto& en = sk_.entities[e];
        x = P[en.center].x - (en.radius + (10 + 12 * stack) * px) * 0.7071;
        y = P[en.center].y + (en.radius + (10 + 12 * stack) * px) * 0.7071;
      }
      return std::make_pair(x, y);
    }
  }
}

QString SketchEditor::labelText(const Constraint& c) const {
  switch (c.type) {
    case ConstraintType::Horizontal: return QStringLiteral("H");
    case ConstraintType::Vertical: return QStringLiteral("V");
    case ConstraintType::Parallel: return QStringLiteral("//");
    case ConstraintType::Perpendicular: return QString::fromUtf8("⊥");
    case ConstraintType::Equal: return QStringLiteral("=");
    case ConstraintType::Tangent: return QStringLiteral("T");
    case ConstraintType::Concentric: return QString::fromUtf8("◎");
    case ConstraintType::Fix: return QString::fromUtf8("⌖");
    case ConstraintType::Midpoint: return QStringLiteral("M");
    case ConstraintType::Distance:
    case ConstraintType::HorizontalDistance:
    case ConstraintType::VerticalDistance:
      return QString::number(fromInternal(std::abs(c.value), unit_), 'f', unit_ == Unit::Inch ? 3 : 2);
    case ConstraintType::Radius:
      return QStringLiteral("R") + QString::number(fromInternal(c.value, unit_), 'f', unit_ == Unit::Inch ? 3 : 2);
    case ConstraintType::Diameter:
      return QString::fromUtf8("⌀") + QString::number(fromInternal(c.value, unit_), 'f', unit_ == Unit::Inch ? 3 : 2);
    case ConstraintType::Angle:
      return QString::number(fromInternal(c.value, Unit::Degree), 'f', 1) + QString::fromUtf8("°");
    default:
      return {};
  }
}

void SketchEditor::rebuild() {
  if (!view_) return;
  const auto& ctx = view_->aisContext();
  if (ctx.IsNull()) return;
  for (auto& o : objects_) ctx->Remove(o, false);
  objects_.clear();

  auto selected = [&](Hit::Kind k, int i) {
    for (const auto& s : selection_)
      if (s.kind == k && s.index == i) return true;
    for (const auto& p : picks_)
      if (p.hit.kind == k && p.hit.index == i) return true;
    return false;
  };
  auto hovered = [&](Hit::Kind k, int i) { return hover_.kind == k && hover_.index == i; };
  auto colorFor = [&](Hit::Kind k, int i, bool fixed, bool construction) {
    if (selected(k, i)) return kSelected;
    if (hovered(k, i)) return kHover;
    if (construction) return kConstruction;
    return fixed ? fixedColor() : freeColor();
  };

  for (int i = 0; i < static_cast<int>(sk_.entities.size()); ++i) {
    const TopoDS_Shape s = sketch::curve(sk_, frame_, i);
    if (s.IsNull()) continue;
    const auto& e = sk_.entities[i];
    const bool fixed = res_.ok && i < static_cast<int>(res_.entityFixed.size()) && res_.entityFixed[i];
    const bool hl = selected(Hit::Entity, i) || hovered(Hit::Entity, i);
    Handle(AIS_Shape) a = wire(s, colorFor(Hit::Entity, i, fixed, e.construction), hl ? 3.0 : 2.0,
                               e.construction ? Aspect_TOL_DASH : Aspect_TOL_SOLID);
    ctx->Display(a, AIS_WireFrame, -1, false);
    ctx->SetZLayer(a, Graphic3d_ZLayerId_Topmost);   // never hidden behind bodies
    objects_.push_back(a);
  }
  for (int i = 0; i < static_cast<int>(sk_.points.size()); ++i) {
    const bool fixed = res_.ok && i < static_cast<int>(res_.pointFixed.size()) && res_.pointFixed[i];
    Handle(AIS_Point) p = new AIS_Point(new Geom_CartesianPoint(sketch::toWorld(frame_, sk_.points[i].x, sk_.points[i].y)));
    const Quantity_Color c = i == 0 && !selected(Hit::Point, 0) && !hovered(Hit::Point, 0)
                                 ? rgb(200, 40, 40)
                                 : colorFor(Hit::Point, i, fixed, false);
    const bool big = selected(Hit::Point, i) || hovered(Hit::Point, i);
    p->Attributes()->SetPointAspect(new Prs3d_PointAspect(big ? Aspect_TOM_O_POINT : Aspect_TOM_POINT, c, big ? 2.5 : 4.0));
    ctx->Display(p, 0, -1, false);
    ctx->SetZLayer(p, Graphic3d_ZLayerId_Topmost);
    objects_.push_back(p);
  }
  for (int i = 0; i < static_cast<int>(sk_.constraints.size()); ++i) {
    const auto anchor = labelAnchor(i);
    if (!anchor) continue;
    const auto& c = sk_.constraints[i];
    Handle(AIS_TextLabel) t = new AIS_TextLabel();
    t->SetText(ext(labelText(c)));
    t->SetPosition(sketch::toWorld(frame_, anchor->first, anchor->second));
    t->SetHeight(sketch::isDimension(c.type) ? 14 : 12);
    t->SetColor(selected(Hit::Label, i) ? kSelected
                : hovered(Hit::Label, i) ? kHover
                : sketch::isDimension(c.type) ? qc(themeColors().sketchLabel)
                                             : qc(themeColors().sketchGlyph));
    t->SetHJustification(Graphic3d_HTA_CENTER);
    t->SetVJustification(Graphic3d_VTA_CENTER);
    ctx->Display(t, 0, -1, false);
    ctx->SetZLayer(t, Graphic3d_ZLayerId_Topmost);
    objects_.push_back(t);
  }
  view_->redraw();
}

void SketchEditor::clearPreview() {
  if (!view_) return;
  const auto& ctx = view_->aisContext();
  if (!ctx.IsNull())
    for (auto& o : preview_) ctx->Remove(o, false);
  preview_.clear();
}

void SketchEditor::updatePreview(double x, double y) {
  clearPreview();
  if (!view_ || steps_.empty()) {
    if (view_) view_->redraw();
    return;
  }
  if (hudTool()) {
    ensureHud();
    std::tie(x, y) = hudTarget(x, y);
    if (!hudAnyLocked()) {
      const Pick snap = pickPoint(x, y);
      x = snap.x;
      y = snap.y;
    }
    updateHud(x, y);
  } else {
    const Pick snap = pickPoint(x, y);
    x = snap.x;
    y = snap.y;
  }
  sketch::Sketch tmp;
  const auto& a = steps_.front();
  switch (tool_) {
    case Tool::CenterRectangle: {
      const double hx = std::abs(x - a.x), hy = std::abs(y - a.y);
      if (hx > 1e-9 && hy > 1e-9) {
        tmp.addLine(a.x - hx, a.y - hy, a.x + hx, a.y - hy);
        tmp.addLine(a.x + hx, a.y - hy, a.x + hx, a.y + hy);
        tmp.addLine(a.x + hx, a.y + hy, a.x - hx, a.y + hy);
        tmp.addLine(a.x - hx, a.y + hy, a.x - hx, a.y - hy);
      }
      break;
    }
    case Tool::Polygon: {
      const double r = std::hypot(x - a.x, y - a.y);
      const int n = polygonSides();
      const double a0 = std::atan2(y - a.y, x - a.x);
      if (r > 1e-9)
        for (int i = 0; i < n; ++i) {
          const double t0 = a0 + 2 * kPi * i / n, t1 = a0 + 2 * kPi * (i + 1) / n;
          tmp.addLine(a.x + r * std::cos(t0), a.y + r * std::sin(t0), a.x + r * std::cos(t1), a.y + r * std::sin(t1));
        }
      break;
    }
    case Tool::Slot: {
      const double len = std::hypot(x - a.x, y - a.y);
      if (len > 1e-9) {
        const double r = (hudLocked(1) ? hudValue(1) : len / 3) / 2;
        const double ux = (x - a.x) / len, uy = (y - a.y) / len, nx = -uy, ny = ux;
        tmp.addLine(a.x + nx * r, a.y + ny * r, x + nx * r, y + ny * r);
        tmp.addLine(a.x - nx * r, a.y - ny * r, x - nx * r, y - ny * r);
        const int c2 = tmp.addPoint(x, y), s2 = tmp.addPoint(x - nx * r, y - ny * r), e2 = tmp.addPoint(x + nx * r, y + ny * r);
        tmp.addArc(c2, s2, e2);
        const int c1 = tmp.addPoint(a.x, a.y), s1 = tmp.addPoint(a.x + nx * r, a.y + ny * r), e1 = tmp.addPoint(a.x - nx * r, a.y - ny * r);
        tmp.addArc(c1, s1, e1);
      }
      break;
    }
    case Tool::Line: {
      const auto& b = steps_.back();
      if (std::hypot(x - b.x, y - b.y) > 1e-9) tmp.addLine(b.x, b.y, x, y);
      break;
    }
    case Tool::Rectangle:
      if (std::abs(x - a.x) > 1e-9 && std::abs(y - a.y) > 1e-9) {
        tmp.addLine(a.x, a.y, x, a.y);
        tmp.addLine(x, a.y, x, y);
        tmp.addLine(x, y, a.x, y);
        tmp.addLine(a.x, y, a.x, a.y);
      }
      break;
    case Tool::Circle: {
      const double r = std::hypot(x - a.x, y - a.y);
      if (r > 1e-9) tmp.addCircle(a.x, a.y, r);
      break;
    }
    case Tool::Arc:
      if (steps_.size() == 1) {
        tmp.addLine(a.x, a.y, x, y);
      } else {
        const auto& s = steps_[1];
        const double r = std::hypot(s.x - a.x, s.y - a.y);
        const double ang = std::atan2(y - a.y, x - a.x);
        const int c = tmp.addPoint(a.x, a.y);
        const int ps = tmp.addPoint(s.x, s.y);
        const int pe = tmp.addPoint(a.x + r * std::cos(ang), a.y + r * std::sin(ang));
        if (r > 1e-9) tmp.addArc(c, ps, pe);
      }
      break;
    default:
      break;
  }
  const TopoDS_Shape s = sketch::curves(tmp, frame_, false);
  const auto& ctx = view_->aisContext();
  if (!s.IsNull() && !ctx.IsNull()) {
    Handle(AIS_Shape) w = wire(s, kPreview, 1.5, Aspect_TOL_DASH);
    ctx->Display(w, AIS_WireFrame, -1, false);
    ctx->SetZLayer(w, Graphic3d_ZLayerId_Topmost);
    preview_.push_back(w);
    // Tools with size boxes show their sizes there; the rest get a label.
    QString text;
    double lx = x, ly = y;
    switch (tool_) {
      case Tool::Line: {
        const auto& b = steps_.back();
        text = lengthText(std::hypot(x - b.x, y - b.y));
        const double ang = std::atan2(y - b.y, x - b.x) * 180.0 / kPi;
        text += QStringLiteral("   %1\u00B0").arg(ang, 0, 'f', 1);
        lx = (x + b.x) / 2;
        ly = (y + b.y) / 2;
        break;
      }
      case Tool::Rectangle:
        text = lengthText(std::abs(x - a.x)) + QStringLiteral(" \u00D7 ") + lengthText(std::abs(y - a.y));
        lx = (x + a.x) / 2;
        ly = (y + a.y) / 2;
        break;
      case Tool::Circle:
        text = QString::fromUtf8("\u2300 ") + lengthText(2 * std::hypot(x - a.x, y - a.y));
        break;
      case Tool::Arc:
        if (steps_.size() > 1) text = QStringLiteral("R ") + lengthText(std::hypot(steps_[1].x - a.x, steps_[1].y - a.y));
        break;
      default:
        break;
    }
    if (hudTool()) text.clear();   // sizes are shown in the boxes
    if (!text.isEmpty()) {
      Handle(AIS_TextLabel) t = new AIS_TextLabel();
      t->SetText(ext(text));
      t->SetPosition(sketch::toWorld(frame_, lx, ly));
      t->SetHeight(14);
      t->SetColor(qc(themeColors().sketchLabel));
      t->SetHJustification(Graphic3d_HTA_CENTER);
      t->SetVJustification(Graphic3d_VTA_BOTTOM);
      ctx->Display(t, 0, -1, false);
      ctx->SetZLayer(t, Graphic3d_ZLayerId_Topmost);
      preview_.push_back(t);
    }
  }
  view_->redraw();
}

} // namespace tsr::app
