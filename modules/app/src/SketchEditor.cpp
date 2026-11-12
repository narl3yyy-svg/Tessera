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
#include <QKeyEvent>
#include <QLineEdit>
#include <QRegularExpression>
#include <QMouseEvent>

#include <algorithm>
#include <cmath>

namespace tsr::app {

using sketch::Constraint;
using sketch::ConstraintType;
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
    case Tool::Line: emit message(tr("Line: click points. Click the first point to close; double-click or Esc to stop.")); break;
    case Tool::Rectangle: emit message(tr("Rectangle: click two opposite corners.")); break;
    case Tool::Circle: emit message(tr("Circle: click the centre, then a point on the circle.")); break;
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
  }
  rebuild();
}

void SketchEditor::resetSteps() {
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
      const int a = materialize(steps_.back());
      const Pick end = pickPoint(x, y, a);
      if (std::hypot(end.x - sk_.points[a].x, end.y - sk_.points[a].y) < tolerance() / 2) {
        undo_.pop_back();
        return;
      }
      const int b = materialize(end);
      if (chainStart_ < 0) chainStart_ = a;
      const int l = sk_.addLine(a, b, construction_);
      autoHorizontalVertical(l);
      const bool closed = end.hit.kind == Hit::Point && b == chainStart_;
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
      const Pick c = pickPoint(x, y);
      if (std::abs(c.x - a.x) < tolerance() / 2 || std::abs(c.y - a.y) < tolerance() / 2) return;
      checkpoint();
      const int p0 = materialize(a);
      const int p2 = materialize(c);
      const int p1 = sk_.addPoint(sk_.points[p2].x, sk_.points[p0].y);
      const int p3 = sk_.addPoint(sk_.points[p0].x, sk_.points[p2].y);
      const int l0 = sk_.addLine(p0, p1, construction_), l1 = sk_.addLine(p1, p2, construction_);
      const int l2 = sk_.addLine(p2, p3, construction_), l3 = sk_.addLine(p3, p0, construction_);
      for (int l : {l0, l2}) sk_.addConstraint({ConstraintType::Horizontal, {}, {l}});
      for (int l : {l1, l3}) sk_.addConstraint({ConstraintType::Vertical, {}, {l}});
      resetSteps();
      solveAndShow();
      if (!res_.ok) undo();
      return;
    }
    case Tool::Circle: {
      if (steps_.empty()) {
        steps_.push_back(pickPoint(x, y));
        return;
      }
      const Pick c = steps_.front();
      const double r = std::hypot(x - c.x, y - c.y);
      if (r < tolerance() / 2) return;
      checkpoint();
      sk_.addCircleAt(materialize(c), r, construction_);
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

bool SketchEditor::keyPress(QKeyEvent* e) {
  const QString t = e->text();
  if (steps_.empty() || t.isEmpty() || valueBox_) return false;
  if (!(t[0].isDigit() || t[0] == QLatin1Char('.') || t[0] == QLatin1Char('-'))) return false;
  if (tool_ != Tool::Line && tool_ != Tool::Circle && tool_ != Tool::Rectangle) return false;
  openTypedBox(t);
  return true;
}

void SketchEditor::openTypedBox(const QString& initial) {
  auto* box = new QLineEdit(view_);
  valueBox_ = box;
  box->setObjectName(QStringLiteral("typedValue"));
  box->setFixedWidth(150);
  box->setPlaceholderText(tool_ == Tool::Rectangle ? tr("width x height") : QString());
  box->move(view_->mapFromGlobal(QCursor::pos()) + QPoint(16, 8));
  box->setText(initial);
  box->show();
  box->setFocus();
  connect(box, &QLineEdit::returnPressed, this, [this, box] {
    const QString text = box->text();
    valueBox_ = nullptr;
    box->deleteLater();
    typeValue(text);
  });
  connect(box, &QLineEdit::editingFinished, this, [this, box] {
    if (valueBox_ == box) valueBox_ = nullptr;
    box->deleteLater();
  });
}

bool SketchEditor::typeValue(const QString& text) {
  if (steps_.empty()) return false;
  auto parse = [this](const QString& s) { return parseQuantity(s.trimmed().toStdString(), unit_); };
  const Pick a = steps_.back();
  if (tool_ == Tool::Line) {
    const auto len = parse(text);
    if (!len || *len <= 0) {
      emit message(tr("'%1' is not a length.").arg(text));
      return false;
    }
    double dx = cursorX_ - a.x, dy = cursorY_ - a.y;
    const double n = std::hypot(dx, dy);
    if (n < 1e-12) dx = 1, dy = 0;
    else dx /= n, dy /= n;
    checkpoint();
    const int pa = materialize(a);
    const int pb = sk_.addPoint(sk_.points[pa].x + dx * *len, sk_.points[pa].y + dy * *len);
    if (chainStart_ < 0) chainStart_ = pa;
    const int l = sk_.addLine(pa, pb, construction_);
    autoHorizontalVertical(l);
    (void)sketch::addConstraintChecked(sk_, {ConstraintType::Distance, {}, {l}, *len});
    steps_ = {Pick{{Hit::Point, pb}, sk_.points[pb].x, sk_.points[pb].y}};
    solveAndShow();
    return true;
  }
  if (tool_ == Tool::Circle) {
    const auto dia = parse(text);
    if (!dia || *dia <= 0) {
      emit message(tr("'%1' is not a diameter.").arg(text));
      return false;
    }
    checkpoint();
    const int c = sk_.addCircleAt(materialize(steps_.front()), *dia / 2, construction_);
    (void)sketch::addConstraintChecked(sk_, {ConstraintType::Diameter, {}, {c}, *dia});
    resetSteps();
    solveAndShow();
    return true;
  }
  if (tool_ == Tool::Rectangle) {
    QStringList parts = text.split(QRegularExpression(QStringLiteral("[xX*,]")), Qt::SkipEmptyParts);
    if (parts.size() == 1) parts << parts[0];
    const auto w = parts.size() == 2 ? parse(parts[0]) : std::nullopt;
    const auto h = parts.size() == 2 ? parse(parts[1]) : std::nullopt;
    if (!w || !h || *w <= 0 || *h <= 0) {
      emit message(tr("Type the size as width x height, e.g. 40 x 20."));
      return false;
    }
    const Pick c0 = steps_.front();
    const double sx = cursorX_ >= c0.x ? 1 : -1, sy = cursorY_ >= c0.y ? 1 : -1;
    checkpoint();
    const int p0 = materialize(c0);
    const double x0 = sk_.points[p0].x, y0 = sk_.points[p0].y;
    const int p1 = sk_.addPoint(x0 + sx * *w, y0);
    const int p2 = sk_.addPoint(x0 + sx * *w, y0 + sy * *h);
    const int p3 = sk_.addPoint(x0, y0 + sy * *h);
    const int l0 = sk_.addLine(p0, p1, construction_), l1 = sk_.addLine(p1, p2, construction_);
    const int l2 = sk_.addLine(p2, p3, construction_), l3 = sk_.addLine(p3, p0, construction_);
    for (int l : {l0, l2}) sk_.addConstraint({ConstraintType::Horizontal, {}, {l}});
    for (int l : {l1, l3}) sk_.addConstraint({ConstraintType::Vertical, {}, {l}});
    (void)sketch::addConstraintChecked(sk_, {ConstraintType::Distance, {}, {l0}, *w});
    (void)sketch::addConstraintChecked(sk_, {ConstraintType::Distance, {}, {l1}, *h});
    resetSteps();
    solveAndShow();
    return true;
  }
  return false;
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
  const Pick snap = pickPoint(x, y);
  x = snap.x;
  y = snap.y;
  sketch::Sketch tmp;
  const auto& a = steps_.front();
  switch (tool_) {
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
    // Live size of what is being drawn; type a number to set it exactly.
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
