// Viewport: Move/Copy's triad, as in the familiar tool. Arrows along X, Y and
// Z (red, green, blue) move the body along them; a quarter ring about each
// axis turns it; a small square in each plane moves it in that plane. The box
// beside the last handle used shows its value and takes typing.
#include "Viewport.h"

#include <AIS_Shape.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakePolygon.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepPrimAPI_MakeCone.hxx>
#include <BRepPrimAPI_MakeCylinder.hxx>
#include <BRepPrimAPI_MakeSphere.hxx>
#include <BRep_Builder.hxx>
#include <Prs3d_LineAspect.hxx>
#include <TopoDS_Compound.hxx>
#include <gp_Ax2.hxx>

#include <QLineEdit>
#include <QMouseEvent>
#include <QPolygonF>
#include <QTimer>

#include <algorithm>
#include <cmath>

namespace tsr::app {

namespace {
Quantity_Color rgb(int r, int g, int b) { return Quantity_Color(r / 255.0, g / 255.0, b / 255.0, Quantity_TOC_sRGB); }

const gp_Dir kAxes[3] = {gp::DX(), gp::DY(), gp::DZ()};

// Handle colours: X red, Y green, Z blue; brighter when hot.
Quantity_Color axisColour(int k, bool hot) {
  if (k == 0) return hot ? rgb(255, 120, 110) : rgb(220, 60, 50);
  if (k == 1) return hot ? rgb(120, 230, 120) : rgb(60, 180, 70);
  return hot ? rgb(110, 170, 255) : rgb(40, 110, 230);
}

double segmentDistance(const QPointF& p, const QPointF& a, const QPointF& b) {
  const QPointF ab = b - a;
  const double len2 = ab.x() * ab.x() + ab.y() * ab.y();
  double t = len2 > 0 ? ((p - a).x() * ab.x() + (p - a).y() * ab.y()) / len2 : 0;
  t = std::clamp(t, 0.0, 1.0);
  const QPointF q = a + ab * t;
  return std::hypot(p.x() - q.x(), p.y() - q.y());
}

constexpr double kArrowPx = 95, kArrowStartPx = 16, kRingPx = 62, kSquareLoPx = 22, kSquareHiPx = 38;
constexpr double kRingT0 = 0.12, kRingT1 = 1.45;   // the quarter ring's ends (rad), clear of the arrows

// Plane handle m (6 + m): its normal is axis m; its two axes in order.
int planeU(int m) { return (m + 1) % 3; }
int planeV(int m) { return (m + 2) % 3; }
} // namespace

void Viewport::setTriad(const gp_Pnt& origin, const std::array<double, 6>& values, const QStringList& texts) {
  const bool appearing = !triad_;
  triad_ = Triad{origin, values, texts};
  if (!triadBox_) {
    triadBox_ = new QLineEdit(this);
    triadBox_->setObjectName(QStringLiteral("triadValue"));
    triadBox_->setAlignment(Qt::AlignCenter);
    triadBox_->setFixedWidth(110);
    triadBox_->setToolTip(tr("Type a value and press Enter, or drag the handle"));
    triadBox_->setStyleSheet(QStringLiteral(
        "QLineEdit { background: #ffffff; color: #1d1f22; border: 1px solid #9aa3ad; border-radius: 2px;"
        " padding: 2px 4px; selection-background-color: #2f8fe8; selection-color: #ffffff; }"
        " QLineEdit:focus { border: 1px solid #2f8fe8; }"));
    connect(triadBox_, &QLineEdit::textEdited, this, [this](const QString& t) {
      if (triadActive_ < 6) emit triadTyped(triadActive_, t.trimmed());
    });
    connect(triadBox_, &QLineEdit::returnPressed, this, [this] {
      if (triadActive_ < 6) emit triadTyped(triadActive_, triadBox_->text().trimmed());
      setFocus();
    });
  }
  if (appearing) triadActive_ = 0;
  if (!triadBox_->hasFocus() && triadActive_ < 6 && triadActive_ < texts.size()) triadBox_->setText(texts[triadActive_]);
  rebuildTriad();
}

void Viewport::clearTriad() {
  if (!triad_ && triadObjects_.empty()) return;
  triad_.reset();
  triadDrag_ = triadHover_ = -1;
  if (!context_.IsNull())
    for (auto& o : triadObjects_) context_->Remove(o, false);
  triadObjects_.clear();
  if (triadBox_) triadBox_->hide();
  unsetCursor();
  redrawAll();
}

void Viewport::setTriadActive(int handle) {
  triadActive_ = std::clamp(handle, 0, 8);
  if (triad_ && triadActive_ < 6 && triadActive_ < triad_->texts.size()) triadBox_->setText(triad_->texts[triadActive_]);
  rebuildTriad();
}

gp_Pnt Viewport::triadPoint(int handle) const {
  const gp_Pnt o = triad_ ? triad_->origin : gp_Pnt();
  const double px = modelPerPixel();
  if (handle < 3) return o.Translated(gp_Vec(kAxes[handle]) * px * kArrowPx * 0.8);
  if (handle < 6) {
    const int k = handle - 3;
    const double t = (kRingT0 + kRingT1) / 2;
    return o.Translated(gp_Vec(kAxes[planeU(k)]) * (px * kRingPx * std::cos(t)) +
                        gp_Vec(kAxes[planeV(k)]) * (px * kRingPx * std::sin(t)));
  }
  const int m = handle - 6;
  const double mid = px * (kSquareLoPx + kSquareHiPx) / 2;
  return o.Translated(gp_Vec(kAxes[planeU(m)]) * mid + gp_Vec(kAxes[planeV(m)]) * mid);
}

std::optional<QPointF> Viewport::triadHandle(int handle) const {
  if (!triad_ || handle < 0 || handle > 8) return std::nullopt;
  return toWidget(triadPoint(handle));
}

void Viewport::rebuildTriad() {
  if (!triad_) return;
  placeTriadBox();
  if (context_.IsNull() || !glReady_) return;
  for (auto& o : triadObjects_) context_->Remove(o, false);
  triadObjects_.clear();
  const gp_Pnt o = triad_->origin;
  const double px = modelPerPixel();
  auto show = [&](const TopoDS_Shape& s, const Quantity_Color& c, bool shaded, double width = 1.0) {
    Handle(AIS_Shape) a = new AIS_Shape(s);
    if (shaded) {
      Graphic3d_MaterialAspect m(Graphic3d_NameOfMaterial_UserDefined);
      m.SetDiffuseColor(c);
      m.SetAmbientColor(c);
      m.SetEmissiveColor(Quantity_Color(c.Rgb() * 0.5f));
      a->SetMaterial(m);
      a->Attributes()->SetFaceBoundaryDraw(false);
    } else {
      a->SetColor(c);
      a->Attributes()->SetWireAspect(new Prs3d_LineAspect(c, Aspect_TOL_SOLID, width));
    }
    context_->Display(a, shaded ? AIS_Shaded : AIS_WireFrame, -1, false);
    context_->SetZLayer(a, Graphic3d_ZLayerId_Topmost);
    triadObjects_.push_back(a);
  };
  auto hot = [&](int h) { return triadHover_ == h || triadDrag_ == h || triadActive_ == h; };
  // Arrows.
  for (int k = 0; k < 3; ++k) {
    const gp_Dir d = kAxes[k];
    const gp_Pnt start = o.Translated(gp_Vec(d) * px * kArrowStartPx);
    const double len = px * (kArrowPx - kArrowStartPx), head = px * 18;
    TopoDS_Compound c;
    BRep_Builder bb;
    bb.MakeCompound(c);
    bb.Add(c, BRepPrimAPI_MakeCylinder(gp_Ax2(start, d), px * 2.0, len - head).Shape());
    bb.Add(c, BRepPrimAPI_MakeCone(gp_Ax2(start.Translated(gp_Vec(d) * (len - head)), d), px * 7, 0, head).Shape());
    show(c, axisColour(k, hot(k)), true);
  }
  // Quarter rings, each with a ball to grab.
  for (int k = 0; k < 3; ++k) {
    const gp_Vec u(kAxes[planeU(k)]), v(kAxes[planeV(k)]);
    TopoDS_Compound c;
    BRep_Builder bb;
    bb.MakeCompound(c);
    const int n = 16;
    for (int i = 0; i < n; ++i) {
      const double t0 = kRingT0 + (kRingT1 - kRingT0) * i / n, t1 = kRingT0 + (kRingT1 - kRingT0) * (i + 1) / n;
      bb.Add(c, BRepBuilderAPI_MakeEdge(o.Translated(u * (px * kRingPx * std::cos(t0)) + v * (px * kRingPx * std::sin(t0))),
                                        o.Translated(u * (px * kRingPx * std::cos(t1)) + v * (px * kRingPx * std::sin(t1))))
                     .Shape());
    }
    show(c, axisColour(k, hot(3 + k)), false, hot(3 + k) ? 4.0 : 3.0);
    show(BRepPrimAPI_MakeSphere(triadPoint(3 + k), px * 6).Shape(), axisColour(k, hot(3 + k)), true);
  }
  // Plane squares, coloured by their normal.
  for (int m = 0; m < 3; ++m) {
    const gp_Vec u(kAxes[planeU(m)]), v(kAxes[planeV(m)]);
    const double a = px * kSquareLoPx, b = px * kSquareHiPx;
    BRepBuilderAPI_MakePolygon poly(o.Translated(u * a + v * a), o.Translated(u * b + v * a), o.Translated(u * b + v * b),
                                    o.Translated(u * a + v * b), true);
    show(BRepBuilderAPI_MakeFace(poly.Wire(), true).Face(), axisColour(m, hot(6 + m)), true);
  }
  redrawAll();
}

void Viewport::placeTriadBox() {
  if (!triadBox_ || !triad_) return;
  if (triadActive_ >= 6) {
    triadBox_->hide();
    return;
  }
  const QPointF w = toWidget(triadPoint(triadActive_));
  QPoint at(static_cast<int>(w.x()) + 24, static_cast<int>(w.y()) + 14);
  for (QWidget* child : findChildren<QWidget*>(Qt::FindDirectChildrenOnly))
    if (child->isVisible() && child->property("panel").toBool() &&
        QRect(at, triadBox_->size()).adjusted(-8, -8, 8, 8).intersects(child->geometry()))
      at.setX(static_cast<int>(w.x()) - 24 - triadBox_->width());
  at.setX(std::clamp(at.x(), 4, std::max(4, width() - triadBox_->width() - 4)));
  at.setY(std::clamp(at.y(), 4, std::max(4, height() - triadBox_->height() - 4)));
  triadBox_->move(at);
  triadBox_->show();
  triadBox_->raise();
}

int Viewport::triadAt(const QPointF& pos) const {
  if (!triad_ || view_.IsNull()) return -1;
  const gp_Pnt o = triad_->origin;
  const double px = modelPerPixel();
  int best = -1;
  double bestDist = 10;
  auto consider = [&](int h, double d) {
    if (d < bestDist) bestDist = d, best = h;
  };
  // Squares first: a cursor inside one takes it.
  for (int m = 0; m < 3; ++m) {
    const gp_Vec u(kAxes[planeU(m)]), v(kAxes[planeV(m)]);
    const double a = px * kSquareLoPx, b = px * kSquareHiPx;
    const QPolygonF q({toWidget(o.Translated(u * a + v * a)), toWidget(o.Translated(u * b + v * a)),
                       toWidget(o.Translated(u * b + v * b)), toWidget(o.Translated(u * a + v * b))});
    if (q.containsPoint(pos, Qt::OddEvenFill)) consider(6 + m, 0);
  }
  for (int k = 0; k < 3; ++k) {
    consider(k, segmentDistance(pos, toWidget(o.Translated(gp_Vec(kAxes[k]) * px * kArrowStartPx)),
                                toWidget(o.Translated(gp_Vec(kAxes[k]) * px * kArrowPx))));
    const gp_Vec u(kAxes[planeU(k)]), v(kAxes[planeV(k)]);
    QPointF prev;
    for (int i = 0; i <= 16; ++i) {
      const double t = kRingT0 + (kRingT1 - kRingT0) * i / 16;
      const QPointF p = toWidget(o.Translated(u * (px * kRingPx * std::cos(t)) + v * (px * kRingPx * std::sin(t))));
      if (i > 0) consider(3 + k, segmentDistance(pos, prev, p) - 1);
      prev = p;
    }
  }
  return best;
}

// Where the ray under `pos` meets the plane through `p0` with normal `n`.
std::optional<gp_Pnt> Viewport::rayOnPlane(const QPointF& pos, const gp_Pnt& p0, const gp_Dir& n) const {
  const Graphic3d_Vec2i pix = toPixels(pos);
  Standard_Real x, y, z, vx, vy, vz;
  view_->ConvertWithProj(pix.x(), pix.y(), x, y, z, vx, vy, vz);
  const gp_Vec v(vx, vy, vz), nn(n);
  const double den = nn.Dot(v);
  if (std::abs(den) < 1e-9) return std::nullopt;   // seen edge-on
  const double t = nn.Dot(gp_Vec(gp_Pnt(x, y, z), p0)) / den;
  return gp_Pnt(x, y, z).Translated(v * t);
}

// The drag's reading for `handle`: arrows, the distance along the axis;
// rings, the angle round it (unwrapped from the last reading); squares,
// the two distances in the plane.
std::optional<std::pair<double, double>> Viewport::triadReading(int handle, const QPointF& pos) const {
  const gp_Pnt o = triadDragOrigin_;
  if (handle < 3) {
    const Graphic3d_Vec2i pix = toPixels(pos);
    Standard_Real x, y, z, vx, vy, vz;
    view_->ConvertWithProj(pix.x(), pix.y(), x, y, z, vx, vy, vz);
    const gp_Vec v(vx, vy, vz), u(kAxes[handle]), w0(gp_Pnt(x, y, z), o);
    const double b = u.Dot(v), c = v.Dot(v), d = u.Dot(w0), e = v.Dot(w0);
    const double denom = c - b * b;
    if (std::abs(denom) < 1e-9 * c) return std::nullopt;   // looking straight along the arrow
    return std::make_pair((b * e - c * d) / denom, 0.0);
  }
  if (handle < 6) {
    const int k = handle - 3;
    const auto p = rayOnPlane(pos, o, kAxes[k]);
    if (!p) return std::nullopt;
    const gp_Vec rel(o, *p);
    double ang = std::atan2(rel.Dot(gp_Vec(kAxes[planeV(k)])), rel.Dot(gp_Vec(kAxes[planeU(k)])));
    ang = triadLastAngle_ + std::remainder(ang - triadLastAngle_, 2 * M_PI);
    return std::make_pair(ang, 0.0);
  }
  const int m = handle - 6;
  const auto p = rayOnPlane(pos, o, kAxes[m]);
  if (!p) return std::nullopt;
  const gp_Vec rel(o, *p);
  return std::make_pair(rel.Dot(gp_Vec(kAxes[planeU(m)])), rel.Dot(gp_Vec(kAxes[planeV(m)])));
}

bool Viewport::triadMousePress(QMouseEvent* e) {
  if (!triad_ || e->button() != Qt::LeftButton) return false;
  const int h = triadAt(e->position());
  if (h < 0) return false;
  triadDragOrigin_ = triad_->origin;
  triadLastAngle_ = 0;
  if (h >= 3 && h < 6) {
    // The angle starts where the cursor first is on the ring.
    if (const auto r = triadReading(h, e->position())) triadLastAngle_ = r->first;
  }
  const auto r = triadReading(h, e->position());
  if (!r) return false;
  triadDrag_ = h;
  triadGrab_ = *r;
  triadStart_ = triad_->values;
  triadActive_ = h;
  if (triadBox_) triadBox_->clearFocus();
  setCursor(Qt::ClosedHandCursor);
  rebuildTriad();
  return true;
}

bool Viewport::triadMouseMove(QMouseEvent* e) {
  if (!triad_) return false;
  if (triadDrag_ >= 0) {
    const int h = triadDrag_;
    if (const auto r = triadReading(h, e->position())) {
      std::array<double, 6> v = triadStart_;
      if (h < 3) {
        v[h] = triadStart_[h] + (r->first - triadGrab_.first);
      } else if (h < 6) {
        triadLastAngle_ = r->first;
        v[h] = triadStart_[h] + (r->first - triadGrab_.first);
      } else {
        const int m = h - 6;
        v[planeU(m)] = triadStart_[planeU(m)] + (r->first - triadGrab_.first);
        v[planeV(m)] = triadStart_[planeV(m)] + (r->second - triadGrab_.second);
      }
      triad_->values = v;
      emit triadDragged(h, QVector<double>(v.begin(), v.end()));
    }
    return true;
  }
  const int hover = triadAt(e->position());
  if (hover != triadHover_) {
    triadHover_ = hover;
    if (hover >= 0) setCursor(Qt::OpenHandCursor);
    else unsetCursor();
    rebuildTriad();
  }
  return false;
}

bool Viewport::triadMouseRelease(QMouseEvent* e) {
  if (triadDrag_ < 0 || e->button() != Qt::LeftButton) return false;
  triadDrag_ = -1;
  setCursor(Qt::OpenHandCursor);
  rebuildTriad();
  // The dragged value is ready to type over.
  if (triadBox_ && triadActive_ < 6)
    QTimer::singleShot(0, triadBox_, [this] {
      triadBox_->setFocus(Qt::OtherFocusReason);
      triadBox_->selectAll();
    });
  return true;
}

} // namespace tsr::app
