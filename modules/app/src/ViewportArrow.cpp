// Viewport: the in-canvas drag arrows used by Extrude, Press Pull, Fillet,
// Chamfer and Section Analysis. Press on an arrow and drag: the value follows
// the cursor along the arrow's line. The box beside each arrow shows its value
// and takes typed values or expressions (Enter). Arrow 0 is the main one;
// arrow 1 is the second side of a Two Sides extrude.
#include "Viewport.h"

#include <AIS_Shape.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepPrimAPI_MakeCone.hxx>
#include <BRepPrimAPI_MakeCylinder.hxx>
#include <BRepPrimAPI_MakeSphere.hxx>
#include <BRep_Builder.hxx>
#include <Prs3d_LineAspect.hxx>
#include <Prs3d_ShadingAspect.hxx>
#include <TopoDS_Compound.hxx>
#include <gp_Ax1.hxx>
#include <gp_Ax2.hxx>

#include <QLabel>
#include <QApplication>
#include <QLineEdit>
#include <QMouseEvent>
#include <QTimer>

#include <algorithm>
#include <cmath>

namespace tsr::app {

namespace {
Quantity_Color rgb(int r, int g, int b) { return Quantity_Color(r / 255.0, g / 255.0, b / 255.0, Quantity_TOC_sRGB); }

// Distance from p to the segment a-b (widget pixels).
double segmentDistance(const QPointF& p, const QPointF& a, const QPointF& b) {
  const QPointF ab = b - a;
  const double len2 = ab.x() * ab.x() + ab.y() * ab.y();
  double t = len2 > 0 ? ((p - a).x() * ab.x() + (p - a).y() * ab.y()) / len2 : 0;
  t = std::clamp(t, 0.0, 1.0);
  const QPointF q = a + ab * t;
  return std::hypot(p.x() - q.x(), p.y() - q.y());
}

constexpr double kArrowPixels = 64;   // arrow length on screen
} // namespace

void Viewport::setDragArrow(const gp_Pnt& base, const gp_Dir& dir, double value, const QString& text, int which) {
  if (which < 0 || which > 1) return;
  auto& arrow = arrows_[which];
  if (arrowDragging_ == which && arrow) {
    // The value comes from this drag; only follow a changed base or direction.
    arrow->base = base;
    arrow->dir = dir;
  } else if (!(arrow && arrow->ring && which == 0 && arrow->base.IsEqual(base, 1e-12) && arrow->dir.IsEqual(dir, 1e-12))) {
    arrow = DragArrow{base, dir, value};
  }
  QLineEdit*& box = arrowBoxes_[which];
  if (!box) {
    box = new QLineEdit(this);
    box->setObjectName(which == 0 ? QStringLiteral("arrowValue") : QStringLiteral("arrowValue2"));
    box->setAlignment(Qt::AlignCenter);
    box->setFixedWidth(120);
    box->setToolTip(tr("Type a value or an expression and press Enter, or drag the arrow"));
    // White with dark text, the value selected in blue: the familiar look.
    box->setStyleSheet(QStringLiteral(
        "QLineEdit { background: #ffffff; color: #1d1f22; border: 1px solid #9aa3ad; border-radius: 2px;"
        " padding: 2px 4px; selection-background-color: #2f8fe8; selection-color: #ffffff; }"
        " QLineEdit:focus { border: 1px solid #2f8fe8; }"));
    connect(box, &QLineEdit::returnPressed, this, [this, which] {
      const QString t = arrowBoxes_[which]->text().trimmed();
      if (which == 0) emit dragArrowTyped(t);
      else emit secondArrowTyped(t);
    });
  }
  const bool appearing = !box->isVisible();
  if (!box->hasFocus()) box->setText(text);
  box->show();
  rebuildArrow(which);
  // As in the familiar tool, the value is ready to type over the moment the
  // command shows it (the first arrow's box).
  // ... and again after each pick in the canvas (not while a panel field or
  // the box itself is being typed in, nor during a drag).
  if (which == 0 && arrowDragging_ < 0 && (appearing || QApplication::focusWidget() == this)) selectArrowValue();
}

void Viewport::selectArrowValue() {
  QLineEdit* box = arrowBoxes_[0];
  if (!box || !box->isVisible()) return;
  QTimer::singleShot(0, box, [box] {
    if (!box->isVisible()) return;
    box->setFocus(Qt::OtherFocusReason);
    box->selectAll();
  });
}

gp_Pnt Viewport::DragArrow::handle() const {
  if (!ring) return base.Translated(gp_Vec(dir) * value);
  const gp_Vec across = gp_Vec(dir).Crossed(gp_Vec(ref));
  return base.Translated(gp_Vec(ref) * (radius * std::cos(value)) + across * (radius * std::sin(value)));
}

void Viewport::setDragRing(const gp_Ax1& axis, const gp_Dir& ref, double radius, double angle, const QString& text) {
  auto& a = arrows_[0];
  if (arrowDragging_ == 0 && a && a->ring) {
    a->base = axis.Location();
    a->dir = axis.Direction();
    a->ref = ref;
    a->radius = radius;
  } else {
    DragArrow r{axis.Location(), axis.Direction(), angle};
    r.ring = true;
    r.ref = ref;
    r.radius = radius;
    a = r;
  }
  setDragArrow(a->base, a->dir, a->value, text, 0);   // the box and drawing, as for arrows
}

void Viewport::clearArrow(int which) {
  arrows_[which].reset();
  if (arrowDragging_ == which) arrowDragging_ = -1;
  if (arrowHover_ == which) arrowHover_ = -1;
  if (!context_.IsNull())
    for (auto& o : arrowObjects_[which]) context_->Remove(o, false);
  arrowObjects_[which].clear();
  if (arrowBoxes_[which]) arrowBoxes_[which]->hide();
}

void Viewport::clearDragArrow() {
  clearArrow(0);
  clearArrow(1);
  unsetCursor();
  redrawAll();
}

void Viewport::clearSecondArrow() {
  if (!arrows_[1] && arrowObjects_[1].empty()) return;
  clearArrow(1);
  redrawAll();
}

void Viewport::dragArrowForTest(double value, int which) {
  if (which < 0 || which > 1 || !arrows_[which]) return;
  arrows_[which]->value = value;
  rebuildArrow(which);
  emitArrow(which, value, true);
}

void Viewport::emitArrow(int which, double value, bool released) {
  if (which == 0) {
    emit dragArrowMoved(value);
    if (released) {
      emit dragArrowReleased(value);
      selectArrowValue();   // dragged: the new value is ready to type over
    }
  } else {
    emit secondArrowMoved(value);
  }
}

std::optional<QPointF> Viewport::dragArrowHandle(int which) const {
  if (which < 0 || which > 1 || !arrows_[which]) return std::nullopt;
  const auto& a = *arrows_[which];
  if (a.ring) return toWidget(a.handle());
  const gp_Dir d = a.value < 0 ? a.dir.Reversed() : a.dir;
  const gp_Pnt tail = a.base.Translated(gp_Vec(a.dir) * a.value);
  return toWidget(tail.Translated(gp_Vec(d) * modelPerPixel() * kArrowPixels * 0.6));
}

void Viewport::rebuildArrows() {
  rebuildArrow(0);
  rebuildArrow(1);
}

void Viewport::rebuildArrow(int which) {
  if (!arrows_[which]) return;
  placeArrowBoxes();
  if (context_.IsNull() || !glReady_) return;
  auto& objects = arrowObjects_[which];
  for (auto& o : objects) context_->Remove(o, false);
  objects.clear();
  const auto& a = *arrows_[which];

  const double px = modelPerPixel();
  if (a.ring) {
    // The arc swept so far, a faint full circle, and a ball to drag.
    const bool hot = arrowHover_ == which || arrowDragging_ == which;
    const Quantity_Color colour = hot ? rgb(90, 190, 255) : rgb(20, 140, 230);
    const gp_Vec across = gp_Vec(a.dir).Crossed(gp_Vec(a.ref));
    auto at = [&](double t) {
      return a.base.Translated(gp_Vec(a.ref) * (a.radius * std::cos(t)) + across * (a.radius * std::sin(t)));
    };
    auto polyline = [&](double t0, double t1, int n) {
      TopoDS_Compound c;
      BRep_Builder bb;
      bb.MakeCompound(c);
      for (int k = 0; k < n; ++k) {
        const gp_Pnt p = at(t0 + (t1 - t0) * k / n), q = at(t0 + (t1 - t0) * (k + 1) / n);
        if (p.Distance(q) > 1e-12) bb.Add(c, BRepBuilderAPI_MakeEdge(p, q).Shape());
      }
      return c;
    };
    Handle(AIS_Shape) full = new AIS_Shape(polyline(0, 2 * M_PI, 96));
    const Quantity_Color faint = rgb(200, 210, 225);
    full->SetColor(faint);
    full->Attributes()->SetWireAspect(new Prs3d_LineAspect(faint, Aspect_TOL_DOT, 1.5));
    context_->Display(full, AIS_WireFrame, -1, false);
    context_->SetZLayer(full, Graphic3d_ZLayerId_Topmost);
    objects.push_back(full);
    if (std::abs(a.value) > 1e-9) {
      Handle(AIS_Shape) arc = new AIS_Shape(polyline(0, a.value, std::max(8, static_cast<int>(std::abs(a.value) * 24))));
      arc->SetColor(colour);
      arc->Attributes()->SetWireAspect(new Prs3d_LineAspect(colour, Aspect_TOL_SOLID, 4.0));
      context_->Display(arc, AIS_WireFrame, -1, false);
      context_->SetZLayer(arc, Graphic3d_ZLayerId_Topmost);
      objects.push_back(arc);
    }
    Handle(AIS_Shape) ball = new AIS_Shape(BRepPrimAPI_MakeSphere(a.handle(), px * 9).Shape());
    Graphic3d_MaterialAspect m(Graphic3d_NameOfMaterial_UserDefined);
    m.SetDiffuseColor(colour);
    m.SetAmbientColor(colour);
    m.SetEmissiveColor(Quantity_Color(colour.Rgb() * 0.5f));
    ball->SetMaterial(m);
    ball->Attributes()->SetFaceBoundaryDraw(false);
    context_->Display(ball, AIS_Shaded, -1, false);
    context_->SetZLayer(ball, Graphic3d_ZLayerId_Topmost);
    objects.push_back(ball);
    redrawAll();
    return;
  }
  const double len = px * kArrowPixels, headLen = px * 20, headR = px * 8, shaftR = px * 2.2;
  const gp_Dir d = a.value < 0 ? a.dir.Reversed() : a.dir;
  const gp_Pnt tip = a.base.Translated(gp_Vec(a.dir) * a.value);
  // The arrow starts at the moved face and points the way it is moving.
  const gp_Pnt tail = tip;
  const gp_Pnt headStart = tail.Translated(gp_Vec(d) * (len - headLen));
  TopoDS_Compound c;
  BRep_Builder bb;
  bb.MakeCompound(c);
  bb.Add(c, BRepPrimAPI_MakeCylinder(gp_Ax2(tail, d), shaftR, len - headLen).Shape());
  bb.Add(c, BRepPrimAPI_MakeCone(gp_Ax2(headStart, d), headR, 0, headLen).Shape());
  Handle(AIS_Shape) arrow = new AIS_Shape(c);
  const bool hot = arrowHover_ == which || arrowDragging_ == which;
  const Quantity_Color colour = hot ? rgb(90, 190, 255) : rgb(20, 140, 230);
  Graphic3d_MaterialAspect m(Graphic3d_NameOfMaterial_UserDefined);
  m.SetDiffuseColor(colour);
  m.SetAmbientColor(colour);
  m.SetEmissiveColor(Quantity_Color(colour.Rgb() * 0.5f));
  arrow->SetMaterial(m);
  arrow->Attributes()->SetFaceBoundaryDraw(false);
  context_->Display(arrow, AIS_Shaded, -1, false);
  context_->SetZLayer(arrow, Graphic3d_ZLayerId_Topmost);
  objects.push_back(arrow);

  // Dotted line along the drag direction through the start point.
  const gp_Pnt p0 = a.base.Translated(-gp_Vec(a.dir) * len * 0.6);
  const gp_Pnt p1 = tip.Translated(gp_Vec(d) * len * 1.2);
  if (p0.Distance(p1) > 1e-9) {
    Handle(AIS_Shape) line = new AIS_Shape(BRepBuilderAPI_MakeEdge(p0, p1).Shape());
    const Quantity_Color lc = rgb(230, 236, 245);
    line->SetColor(lc);
    line->Attributes()->SetWireAspect(new Prs3d_LineAspect(lc, Aspect_TOL_DOT, 1.5));
    context_->Display(line, AIS_WireFrame, -1, false);
    context_->SetZLayer(line, Graphic3d_ZLayerId_Topmost);
    objects.push_back(line);
  }
  redrawAll();
}

void Viewport::placeArrowBoxes() {
  QRect taken;   // the first box, so the second does not cover it
  for (int which = 0; which < 2; ++which) {
    QLineEdit* box = arrowBoxes_[which];
    if (!arrows_[which] || !box) continue;
    const auto& a = *arrows_[which];
    const QPointF w = toWidget(a.handle());
    // Beside the arrow, on its right unless the command panel is there.
    QPoint at(static_cast<int>(w.x()) + 40, static_cast<int>(w.y()) + 20);
    for (QWidget* child : findChildren<QWidget*>(Qt::FindDirectChildrenOnly))
      if (child->isVisible() && child->property("panel").toBool() &&
          QRect(at, box->size()).adjusted(-8, -8, 8, 8).intersects(child->geometry()))
        at.setX(static_cast<int>(w.x()) - 40 - box->width());
    at.setX(std::clamp(at.x(), 4, std::max(4, width() - box->width() - 4)));
    at.setY(std::clamp(at.y(), 4, std::max(4, height() - box->height() - 4)));
    if (!taken.isNull() && QRect(at, box->size()).intersects(taken)) at.setY(taken.bottom() + 6);
    // Never on top of the navigation bar along the bottom of the canvas.
    if (const auto* nav = findChild<QWidget*>(QStringLiteral("navBar"), Qt::FindDirectChildrenOnly);
        nav && nav->isVisible() && QRect(at, box->size()).adjusted(-4, -4, 4, 4).intersects(nav->geometry()))
      at.setY(std::max(4, nav->y() - box->height() - 8));
    if (!taken.isNull() && QRect(at, box->size()).intersects(taken)) at.setY(std::max(4, taken.top() - box->height() - 6));
    if (box->pos() != at) box->move(at);
    box->raise();
    taken = QRect(at, box->size());
  }
}

int Viewport::arrowAt(const QPointF& pos) const {
  if (view_.IsNull()) return -1;
  const double px = modelPerPixel();
  int best = -1;
  double bestDist = 12;
  for (int which = 0; which < 2; ++which) {
    if (!arrows_[which]) continue;
    const auto& a = *arrows_[which];
    if (a.ring) {
      const QPointF h = toWidget(a.handle());
      const double dist = std::hypot(pos.x() - h.x(), pos.y() - h.y()) - 6;
      if (dist < bestDist) {
        bestDist = dist;
        best = which;
      }
      continue;
    }
    const gp_Dir d = a.value < 0 ? a.dir.Reversed() : a.dir;
    const gp_Pnt tail = a.base.Translated(gp_Vec(a.dir) * a.value);
    const gp_Pnt head = tail.Translated(gp_Vec(d) * px * kArrowPixels);
    const double dist = segmentDistance(pos, toWidget(tail), toWidget(head));
    if (dist < bestDist) {
      bestDist = dist;
      best = which;
    }
  }
  return best;
}

std::optional<double> Viewport::arrowParam(int which, const QPointF& pos) const {
  if (!arrows_[which] || view_.IsNull()) return std::nullopt;
  const auto& a = *arrows_[which];
  // Closest point of the arrow's line to the ray under the cursor.
  const Graphic3d_Vec2i px = toPixels(pos);
  Standard_Real x, y, z, vx, vy, vz;
  view_->ConvertWithProj(px.x(), px.y(), x, y, z, vx, vy, vz);
  if (a.ring) {
    // Where the ray meets the ring's plane, as an angle from `ref`, taken
    // the turn nearest the current value (so it can pass 180 and 360 deg).
    const gp_Vec n(a.dir), v(vx, vy, vz);
    const double den = n.Dot(v);
    if (std::abs(den) < 1e-9) return std::nullopt;   // the ring seen edge-on
    const double t = n.Dot(gp_Vec(gp_Pnt(x, y, z), a.base)) / den;
    const gp_Vec rel(a.base, gp_Pnt(x, y, z).Translated(v * t));
    const gp_Vec across = n.Crossed(gp_Vec(a.ref));
    double ang = std::atan2(rel.Dot(across), rel.Dot(gp_Vec(a.ref)));
    // The turn nearest the current value (remainder: a huge value cannot hang the loop).
    if (std::isfinite(a.value)) ang = a.value + std::remainder(ang - a.value, 2 * M_PI);
    return ang;
  }
  const gp_Vec v(vx, vy, vz), u(a.dir);
  const gp_Vec w0(gp_Pnt(x, y, z), a.base);
  const double b = u.Dot(v), c = v.Dot(v), d = u.Dot(w0), e = v.Dot(w0);
  const double denom = c - b * b;   // |u| = 1
  if (std::abs(denom) < 1e-9 * c) return std::nullopt;   // looking straight along the arrow
  return (b * e - c * d) / denom;
}

bool Viewport::arrowMousePress(QMouseEvent* e) {
  if (e->button() != Qt::LeftButton) return false;
  const int which = arrowAt(e->position());
  if (which < 0) return false;
  const auto t = arrowParam(which, e->position());
  if (!t) return false;
  arrowDragging_ = which;
  arrowGrab_ = arrows_[which]->value - *t;
  if (pickHint_) pickHint_->hide();   // the value box says it all while dragging
  for (QLineEdit* box : arrowBoxes_)
    if (box) box->clearFocus();
  setCursor(Qt::ClosedHandCursor);
  rebuildArrow(which);
  return true;
}

bool Viewport::arrowMouseMove(QMouseEvent* e) {
  if (!arrows_[0] && !arrows_[1]) return false;
  if (arrowDragging_ >= 0) {
    const int which = arrowDragging_;
    if (const auto t = arrowParam(which, e->position()); t && arrows_[which]) {
      double v = *t + arrowGrab_;
      if (!arrows_[which]->ring && std::abs(v) < modelPerPixel() * 0.5) v = 0;
      arrows_[which]->value = v;
      rebuildArrow(which);
      emitArrow(which, v, false);
    }
    return true;
  }
  const int hover = arrowAt(e->position());
  if (hover != arrowHover_) {
    const int old = arrowHover_;
    arrowHover_ = hover;
    if (hover >= 0) setCursor(Qt::OpenHandCursor);
    else unsetCursor();
    if (old >= 0) rebuildArrow(old);
    if (hover >= 0) rebuildArrow(hover);
  }
  if (e->buttons() != Qt::NoButton) QTimer::singleShot(0, this, [this] { placeArrowBoxes(); });
  return false;
}

bool Viewport::arrowMouseRelease(QMouseEvent* e) {
  if (arrowDragging_ < 0 || e->button() != Qt::LeftButton) return false;
  const int which = arrowDragging_;
  arrowDragging_ = -1;
  setCursor(Qt::OpenHandCursor);
  rebuildArrow(which);
  if (which == 0) emit dragArrowReleased(arrows_[0] ? arrows_[0]->value : 0.0);
  return true;
}

} // namespace tsr::app
