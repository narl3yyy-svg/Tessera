// Viewport: the in-canvas drag arrow used by Extrude, Press Pull, Fillet and
// Chamfer. Press on the arrow and drag: the value follows the cursor along
// the arrow's line. The box beside the arrow shows the value and takes typed
// values or expressions (Enter).
#include "Viewport.h"

#include <AIS_Shape.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepPrimAPI_MakeCone.hxx>
#include <BRepPrimAPI_MakeCylinder.hxx>
#include <BRep_Builder.hxx>
#include <Prs3d_LineAspect.hxx>
#include <Prs3d_ShadingAspect.hxx>
#include <TopoDS_Compound.hxx>
#include <gp_Ax2.hxx>

#include <QLabel>
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

void Viewport::setDragArrow(const gp_Pnt& base, const gp_Dir& dir, double value, const QString& text) {
  if (arrowDragging_ && arrow_) {
    // The value comes from this drag; only follow a changed base or direction.
    arrow_->base = base;
    arrow_->dir = dir;
  } else {
    arrow_ = DragArrow{base, dir, value};
  }
  if (!arrowBox_) {
    arrowBox_ = new QLineEdit(this);
    arrowBox_->setObjectName(QStringLiteral("arrowValue"));
    arrowBox_->setAlignment(Qt::AlignCenter);
    arrowBox_->setFixedWidth(120);
    arrowBox_->setToolTip(tr("Type a value or an expression and press Enter, or drag the arrow"));
    arrowBox_->setStyleSheet(QStringLiteral(
        "QLineEdit { background: rgba(30,34,40,225); color: #f0f2f5; border: 1px solid #5b6472; border-radius: 2px;"
        " padding: 2px; } QLineEdit:focus { border-bottom: 2px solid #3d8ee8; }"));
    connect(arrowBox_, &QLineEdit::returnPressed, this, [this] { emit dragArrowTyped(arrowBox_->text().trimmed()); });
  }
  if (!arrowBox_->hasFocus()) arrowBox_->setText(text);
  arrowBox_->show();
  rebuildArrow();
}

void Viewport::clearDragArrow() {
  arrow_.reset();
  arrowDragging_ = false;
  arrowHover_ = false;
  if (!context_.IsNull())
    for (auto& o : arrowObjects_) context_->Remove(o, false);
  arrowObjects_.clear();
  if (arrowBox_) arrowBox_->hide();
  unsetCursor();
  redrawAll();
}

void Viewport::dragArrowForTest(double value) {
  if (!arrow_) return;
  arrow_->value = value;
  rebuildArrow();
  emit dragArrowMoved(value);
  emit dragArrowReleased(value);
}

std::optional<QPointF> Viewport::dragArrowHandle() const {
  if (!arrow_) return std::nullopt;
  const gp_Dir d = arrow_->value < 0 ? arrow_->dir.Reversed() : arrow_->dir;
  const gp_Pnt tail = arrow_->base.Translated(gp_Vec(arrow_->dir) * arrow_->value);
  return toWidget(tail.Translated(gp_Vec(d) * modelPerPixel() * kArrowPixels * 0.6));
}

void Viewport::rebuildArrow() {
  if (!arrow_) return;
  placeArrowBox();
  if (context_.IsNull() || !glReady_) return;
  for (auto& o : arrowObjects_) context_->Remove(o, false);
  arrowObjects_.clear();

  const double px = modelPerPixel();
  const double len = px * kArrowPixels, headLen = px * 20, headR = px * 8, shaftR = px * 2.2;
  const gp_Dir d = arrow_->value < 0 ? arrow_->dir.Reversed() : arrow_->dir;
  const gp_Pnt tip = arrow_->base.Translated(gp_Vec(arrow_->dir) * arrow_->value);
  // The arrow starts at the moved face and points the way it is moving.
  const gp_Pnt tail = tip;
  const gp_Pnt headStart = tail.Translated(gp_Vec(d) * (len - headLen));
  TopoDS_Compound c;
  BRep_Builder bb;
  bb.MakeCompound(c);
  bb.Add(c, BRepPrimAPI_MakeCylinder(gp_Ax2(tail, d), shaftR, len - headLen).Shape());
  bb.Add(c, BRepPrimAPI_MakeCone(gp_Ax2(headStart, d), headR, 0, headLen).Shape());
  Handle(AIS_Shape) arrow = new AIS_Shape(c);
  const Quantity_Color colour = arrowHover_ || arrowDragging_ ? rgb(90, 190, 255) : rgb(20, 140, 230);
  Graphic3d_MaterialAspect m(Graphic3d_NameOfMaterial_UserDefined);
  m.SetDiffuseColor(colour);
  m.SetAmbientColor(colour);
  m.SetEmissiveColor(Quantity_Color(colour.Rgb() * 0.5f));
  arrow->SetMaterial(m);
  arrow->Attributes()->SetFaceBoundaryDraw(false);
  context_->Display(arrow, AIS_Shaded, -1, false);
  context_->SetZLayer(arrow, Graphic3d_ZLayerId_Topmost);
  arrowObjects_.push_back(arrow);

  // Dotted line along the drag direction through the start point.
  const gp_Pnt a = arrow_->base.Translated(-gp_Vec(arrow_->dir) * len * 0.6);
  const gp_Pnt b = tip.Translated(gp_Vec(d) * len * 1.2);
  if (a.Distance(b) > 1e-9) {
    Handle(AIS_Shape) line = new AIS_Shape(BRepBuilderAPI_MakeEdge(a, b).Shape());
    const Quantity_Color lc = rgb(230, 236, 245);
    line->SetColor(lc);
    line->Attributes()->SetWireAspect(new Prs3d_LineAspect(lc, Aspect_TOL_DOT, 1.5));
    context_->Display(line, AIS_WireFrame, -1, false);
    context_->SetZLayer(line, Graphic3d_ZLayerId_Topmost);
    arrowObjects_.push_back(line);
  }
  redrawAll();
}

void Viewport::placeArrowBox() {
  if (!arrow_ || !arrowBox_) return;
  const gp_Pnt tip = arrow_->base.Translated(gp_Vec(arrow_->dir) * arrow_->value);
  const QPointF w = toWidget(tip);
  // Beside the arrow, on its right unless the command panel is there.
  QPoint at(static_cast<int>(w.x()) + 40, static_cast<int>(w.y()) + 20);
  for (QWidget* child : findChildren<QWidget*>(Qt::FindDirectChildrenOnly))
    if (child->isVisible() && child->property("panel").toBool() &&
        QRect(at, arrowBox_->size()).adjusted(-8, -8, 8, 8).intersects(child->geometry()))
      at.setX(static_cast<int>(w.x()) - 40 - arrowBox_->width());
  at.setX(std::clamp(at.x(), 4, std::max(4, width() - arrowBox_->width() - 4)));
  at.setY(std::clamp(at.y(), 4, std::max(4, height() - arrowBox_->height() - 4)));
  if (arrowBox_->pos() != at) arrowBox_->move(at);
  arrowBox_->raise();
}

bool Viewport::nearArrow(const QPointF& pos) const {
  if (!arrow_ || view_.IsNull()) return false;
  const double px = modelPerPixel();
  const gp_Dir d = arrow_->value < 0 ? arrow_->dir.Reversed() : arrow_->dir;
  const gp_Pnt tail = arrow_->base.Translated(gp_Vec(arrow_->dir) * arrow_->value);
  const gp_Pnt head = tail.Translated(gp_Vec(d) * px * kArrowPixels);
  return segmentDistance(pos, toWidget(tail), toWidget(head)) < 12;
}

std::optional<double> Viewport::arrowParam(const QPointF& pos) const {
  if (!arrow_ || view_.IsNull()) return std::nullopt;
  // Closest point of the arrow's line to the ray under the cursor.
  const Graphic3d_Vec2i px = toPixels(pos);
  Standard_Real x, y, z, vx, vy, vz;
  view_->ConvertWithProj(px.x(), px.y(), x, y, z, vx, vy, vz);
  const gp_Vec v(vx, vy, vz), u(arrow_->dir);
  const gp_Vec w0(gp_Pnt(x, y, z), arrow_->base);
  const double b = u.Dot(v), c = v.Dot(v), d = u.Dot(w0), e = v.Dot(w0);
  const double denom = c - b * b;   // |u| = 1
  if (std::abs(denom) < 1e-9 * c) return std::nullopt;   // looking straight along the arrow
  return (b * e - c * d) / denom;
}

bool Viewport::arrowMousePress(QMouseEvent* e) {
  if (!arrow_ || e->button() != Qt::LeftButton || !nearArrow(e->position())) return false;
  const auto t = arrowParam(e->position());
  if (!t) return false;
  arrowDragging_ = true;
  arrowGrab_ = arrow_->value - *t;
  if (pickHint_) pickHint_->hide();   // the value box says it all while dragging
  if (arrowBox_) arrowBox_->clearFocus();
  setCursor(Qt::ClosedHandCursor);
  rebuildArrow();
  return true;
}

bool Viewport::arrowMouseMove(QMouseEvent* e) {
  if (!arrow_) return false;
  if (arrowDragging_) {
    if (const auto t = arrowParam(e->position())) {
      double v = *t + arrowGrab_;
      if (std::abs(v) < modelPerPixel() * 0.5) v = 0;
      arrow_->value = v;
      rebuildArrow();
      emit dragArrowMoved(v);
    }
    return true;
  }
  const bool hover = nearArrow(e->position());
  if (hover != arrowHover_) {
    arrowHover_ = hover;
    if (hover) setCursor(Qt::OpenHandCursor);
    else unsetCursor();
    rebuildArrow();
  }
  if (e->buttons() != Qt::NoButton) QTimer::singleShot(0, this, [this] { placeArrowBox(); });
  return false;
}

bool Viewport::arrowMouseRelease(QMouseEvent* e) {
  if (!arrowDragging_ || e->button() != Qt::LeftButton) return false;
  arrowDragging_ = false;
  setCursor(Qt::OpenHandCursor);
  rebuildArrow();
  emit dragArrowReleased(arrow_ ? arrow_->value : 0.0);
  return true;
}

} // namespace tsr::app
