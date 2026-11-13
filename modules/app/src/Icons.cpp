#include "Icons.h"

#include <QAbstractButton>
#include <QAction>
#include <QHash>

#include <array>
#include <cmath>
#include <QPainter>
#include <QPainterPath>
#include <QPixmap>

namespace tsr::app {

namespace {

// All command icons are drawn here from simple geometry, so the project
// ships no third-party artwork. 64x64 logical canvas.
QColor kLine(40, 52, 68);
QColor kTop(170, 205, 240);
QColor kLeft(110, 160, 215);
QColor kRight(70, 125, 190);
QColor kAccent(246, 116, 0);
bool gDark = false;
QHash<QString, QIcon>& cache() {
  static QHash<QString, QIcon> c;
  return c;
}

void face(QPainter& p, const QPolygonF& poly, const QColor& c) {
  p.setBrush(c);
  p.drawPolygon(poly);
}

void box(QPainter& p) {
  const QPointF t(32, 8), l(8, 20), r(56, 20), c(32, 32), bl(8, 46), br(56, 46), b(32, 58);
  face(p, {t, r, c, l}, kTop);
  face(p, {l, c, b, bl}, kLeft);
  face(p, {c, r, br, b}, kRight);
}

void cylinder(QPainter& p, double topW = 22) {
  QPainterPath body;
  body.moveTo(32 - 22, 16);
  body.lineTo(32 - 22, 48);
  body.arcTo(QRectF(10, 40, 44, 16), 180, 180);
  body.lineTo(32 + 22, 16);
  body.closeSubpath();
  QLinearGradient g(10, 0, 54, 0);
  g.setColorAt(0, kLeft);
  g.setColorAt(1, kRight);
  p.setBrush(g);
  p.drawPath(body);
  p.setBrush(kTop);
  p.drawEllipse(QRectF(32 - topW, 8, 2 * topW, 16));
}

void cone(QPainter& p) {
  QPainterPath body;
  body.moveTo(32, 6);
  body.lineTo(10, 48);
  body.arcTo(QRectF(10, 40, 44, 16), 180, 180);
  body.closeSubpath();
  QLinearGradient g(10, 0, 54, 0);
  g.setColorAt(0, kLeft);
  g.setColorAt(1, kRight);
  p.setBrush(g);
  p.drawPath(body);
}

void sphere(QPainter& p) {
  QRadialGradient g(QPointF(24, 22), 34);
  g.setColorAt(0, QColor(225, 238, 252));
  g.setColorAt(0.5, kLeft);
  g.setColorAt(1, kRight.darker(120));
  p.setBrush(g);
  p.drawEllipse(QRectF(8, 8, 48, 48));
  p.setBrush(Qt::NoBrush);
  p.setPen(QPen(kLine, 1.2, Qt::DotLine));
  p.drawEllipse(QRectF(8, 26, 48, 12));
}

void torus(QPainter& p) {
  QPainterPath ring;
  ring.addEllipse(QRectF(4, 16, 56, 32));
  ring.addEllipse(QRectF(20, 26, 24, 12));
  ring.setFillRule(Qt::OddEvenFill);
  QLinearGradient g(0, 16, 0, 48);
  g.setColorAt(0, kTop);
  g.setColorAt(1, kRight);
  p.setBrush(g);
  p.drawPath(ring);
}

void parameters(QPainter& p) {
  p.setBrush(QColor(250, 250, 252));
  p.drawRoundedRect(QRectF(8, 8, 48, 48), 4, 4);
  QFont f = p.font();
  f.setPixelSize(30);
  f.setItalic(true);
  f.setBold(true);
  p.setFont(f);
  p.setPen(kRight);
  p.drawText(QRectF(8, 4, 48, 48), Qt::AlignCenter, QStringLiteral("fx"));
  p.setPen(QPen(kAccent, 3));
  p.drawLine(QPointF(16, 48), QPointF(48, 48));
}

void orbit(QPainter& p) {
  p.setBrush(Qt::NoBrush);
  p.setPen(QPen(kLine, 3));
  p.drawEllipse(QRectF(8, 20, 48, 24));
  p.setBrush(kLeft);
  p.setPen(QPen(kLine, 2));
  p.drawEllipse(QRectF(22, 22, 20, 20));
  p.setBrush(kLine);
  p.drawPolygon(QPolygonF({QPointF(50, 40), QPointF(58, 34), QPointF(58, 46)}));
}

void pan(QPainter& p) {
  p.setPen(QPen(kLine, 3));
  p.drawLine(QPointF(32, 8), QPointF(32, 56));
  p.drawLine(QPointF(8, 32), QPointF(56, 32));
  p.setBrush(kLine);
  for (auto [x, y, dx, dy] : {std::array<double, 4>{32, 6, 0, 1}, {32, 58, 0, -1}, {6, 32, 1, 0}, {58, 32, -1, 0}})
    p.drawPolygon(QPolygonF({QPointF(x, y), QPointF(x + 8 * dx + 6 * dy, y + 8 * dy + 6 * dx),
                             QPointF(x + 8 * dx - 6 * dy, y + 8 * dy - 6 * dx)}));
}

void home(QPainter& p) {
  face(p, {QPointF(32, 8), QPointF(58, 30), QPointF(6, 30)}, kRight);
  face(p, {QPointF(14, 30), QPointF(50, 30), QPointF(50, 56), QPointF(14, 56)}, kTop);
  face(p, {QPointF(27, 40), QPointF(37, 40), QPointF(37, 56), QPointF(27, 56)}, kLeft);
}

void fit(QPainter& p) {
  p.setBrush(Qt::NoBrush);
  p.setPen(QPen(kLine, 3));
  for (auto [x, y, sx, sy] : {std::array<int, 4>{6, 6, 1, 1}, {58, 6, -1, 1}, {6, 58, 1, -1}, {58, 58, -1, -1}}) {
    p.drawLine(x, y, x + 14 * sx, y);
    p.drawLine(x, y, x, y + 14 * sy);
  }
  p.setPen(QPen(kLine, 2));
  box(p);
}

void arrow(QPainter& p, bool mirrored) {
  if (mirrored) {
    p.translate(64, 0);
    p.scale(-1, 1);
  }
  QPainterPath path;
  path.moveTo(16, 26);
  path.cubicTo(30, 10, 56, 14, 54, 40);
  p.setBrush(Qt::NoBrush);
  p.setPen(QPen(kRight, 6, Qt::SolidLine, Qt::RoundCap));
  p.drawPath(path);
  p.setPen(Qt::NoPen);
  p.setBrush(kRight);
  p.drawPolygon(QPolygonF({QPointF(6, 14), QPointF(26, 36), QPointF(4, 38)}));
}

void save(QPainter& p) {
  face(p, {QPointF(8, 8), QPointF(48, 8), QPointF(56, 16), QPointF(56, 56), QPointF(8, 56)}, kRight);
  face(p, {QPointF(18, 8), QPointF(44, 8), QPointF(44, 24), QPointF(18, 24)}, QColor(235, 240, 246));
  face(p, {QPointF(16, 34), QPointF(48, 34), QPointF(48, 56), QPointF(16, 56)}, QColor(250, 250, 252));
}

void document(QPainter& p) {
  face(p, {QPointF(14, 6), QPointF(40, 6), QPointF(52, 18), QPointF(52, 58), QPointF(14, 58)}, QColor(250, 250, 252));
  p.setPen(QPen(kLeft, 3));
  for (int y : {26, 36, 46}) p.drawLine(22, y, 44, y);
}

// Sketch-style icons: dark strokes, blue accents, on a transparent tile.
void stroke(QPainter& p, double w = 4, const QColor& c = kLine) {
  p.setBrush(Qt::NoBrush);
  p.setPen(QPen(c, w, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
}
void dot(QPainter& p, double x, double y, const QColor& c = kRight) {
  p.setPen(Qt::NoPen);
  p.setBrush(c);
  p.drawEllipse(QPointF(x, y), 5, 5);
}

void sketchIcon(QPainter& p) {
  face(p, {QPointF(4, 40), QPointF(32, 26), QPointF(60, 40), QPointF(32, 54)}, QColor(225, 235, 248));
  stroke(p, 3, kRight);
  p.drawRect(QRectF(22, 33, 18, 10));
  stroke(p, 4, kLine);
  p.drawLine(QPointF(40, 8), QPointF(26, 36));
  p.setBrush(kAccent);
  p.drawPolygon(QPolygonF({QPointF(26, 36), QPointF(24, 42), QPointF(30, 38)}));
}

// A fully defined sketch: the sketch icon with a small red lock.
void sketchLockedIcon(QPainter& p) {
  sketchIcon(p);
  const QColor red(210, 50, 45);
  p.setBrush(Qt::NoBrush);
  p.setPen(QPen(red, 4));
  p.drawArc(QRectF(41, 30, 14, 16), 0, 180 * 16);
  p.drawLine(QPointF(41, 38), QPointF(41, 42));
  p.drawLine(QPointF(55, 38), QPointF(55, 42));
  p.setPen(Qt::NoPen);
  p.setBrush(red);
  p.drawRoundedRect(QRectF(37, 40, 22, 18), 3, 3);
}

// Project: an edge above, dashed down onto the sketch plane.
void projectIcon(QPainter& p) {
  face(p, {QPointF(4, 44), QPointF(32, 30), QPointF(60, 44), QPointF(32, 58)}, QColor(225, 235, 248));
  stroke(p, 4, kAccent);
  p.drawLine(QPointF(14, 18), QPointF(44, 8));
  QPen dash(QColor(150, 90, 200), 3, Qt::DashLine);
  p.setPen(dash);
  p.drawLine(QPointF(14, 18), QPointF(14, 44));
  p.drawLine(QPointF(44, 8), QPointF(44, 36));
  p.setPen(QPen(QColor(150, 90, 200), 4));
  p.drawLine(QPointF(14, 44), QPointF(44, 36));
}

// Pattern on Path: three blocks along a curve.
void pathPatternIcon(QPainter& p) {
  stroke(p, 3, kLine);
  QPainterPath path(QPointF(6, 50));
  path.cubicTo(QPointF(20, 10), QPointF(44, 10), QPointF(58, 50));
  p.setBrush(Qt::NoBrush);
  p.drawPath(path);
  p.setPen(Qt::NoPen);
  p.setBrush(kAccent);
  for (const QPointF c : {QPointF(10, 42), QPointF(32, 20), QPointF(54, 42)}) p.drawRect(QRectF(c.x() - 6, c.y() - 6, 12, 12));
}

void extrudeIcon(QPainter& p) {
  face(p, {QPointF(8, 44), QPointF(32, 32), QPointF(56, 44), QPointF(32, 56)}, kTop);
  face(p, {QPointF(8, 44), QPointF(8, 22), QPointF(32, 10), QPointF(32, 32)}, kLeft);
  face(p, {QPointF(32, 32), QPointF(32, 10), QPointF(56, 22), QPointF(56, 44)}, kRight);
  stroke(p, 4, kAccent);
  p.drawLine(QPointF(32, 30), QPointF(32, 4));
  p.setBrush(kAccent);
  p.drawPolygon(QPolygonF({QPointF(26, 10), QPointF(32, 2), QPointF(38, 10)}));
}

void lineIcon(QPainter& p) {
  stroke(p);
  p.drawLine(QPointF(12, 50), QPointF(52, 14));
  dot(p, 12, 50);
  dot(p, 52, 14);
}

void rectIcon(QPainter& p) {
  stroke(p);
  p.drawRect(QRectF(10, 16, 44, 32));
  dot(p, 10, 48);
  dot(p, 54, 16);
}

void circleIcon(QPainter& p) {
  stroke(p);
  p.drawEllipse(QPointF(32, 32), 22, 22);
  dot(p, 32, 32);
}

void arcIcon(QPainter& p) {
  stroke(p);
  p.drawArc(QRectF(10, 10, 44, 44), 0, 180 * 16);
  dot(p, 32, 32);
  dot(p, 54, 32);
  dot(p, 10, 32);
}

void pointIcon(QPainter& p) {
  stroke(p, 2, kLine);
  p.drawLine(QPointF(32, 14), QPointF(32, 50));
  p.drawLine(QPointF(14, 32), QPointF(50, 32));
  dot(p, 32, 32, kAccent);
}

void dimensionIcon(QPainter& p) {
  stroke(p, 3);
  p.drawLine(QPointF(8, 22), QPointF(8, 46));
  p.drawLine(QPointF(56, 22), QPointF(56, 46));
  p.drawLine(QPointF(10, 34), QPointF(54, 34));
  p.setBrush(kLine);
  p.drawPolygon(QPolygonF({QPointF(10, 34), QPointF(18, 30), QPointF(18, 38)}));
  p.drawPolygon(QPolygonF({QPointF(54, 34), QPointF(46, 30), QPointF(46, 38)}));
  QFont f = p.font();
  f.setPixelSize(16);
  f.setBold(true);
  p.setFont(f);
  p.setPen(kRight);
  p.drawText(QRectF(8, 6, 48, 24), Qt::AlignCenter, QStringLiteral("10"));
}

void constraintIcon(QPainter& p, const QString& kind) {
  stroke(p, 4);
  if (kind == QLatin1String("coincident")) {
    p.drawLine(QPointF(8, 50), QPointF(32, 32));
    p.drawLine(QPointF(32, 32), QPointF(56, 44));
    dot(p, 32, 32, kAccent);
  } else if (kind == QLatin1String("horizontal-vertical")) {
    p.drawLine(QPointF(8, 46), QPointF(40, 46));
    p.drawLine(QPointF(50, 10), QPointF(50, 46));
    dot(p, 8, 46);
    dot(p, 50, 10);
  } else if (kind == QLatin1String("parallel")) {
    p.drawLine(QPointF(10, 40), QPointF(40, 10));
    p.drawLine(QPointF(24, 54), QPointF(54, 24));
  } else if (kind == QLatin1String("perpendicular")) {
    p.drawLine(QPointF(10, 52), QPointF(54, 52));
    p.drawLine(QPointF(32, 52), QPointF(32, 10));
    stroke(p, 2, kAccent);
    p.drawRect(QRectF(32, 42, 10, 10));
  } else if (kind == QLatin1String("equal")) {
    p.drawLine(QPointF(14, 24), QPointF(50, 24));
    p.drawLine(QPointF(14, 40), QPointF(50, 40));
  } else if (kind == QLatin1String("tangent")) {
    p.drawEllipse(QPointF(30, 36), 16, 16);
    p.drawLine(QPointF(6, 20), QPointF(58, 20));
  } else if (kind == QLatin1String("fix")) {
    p.setBrush(kTop);
    p.drawRoundedRect(QRectF(14, 28, 36, 26), 4, 4);
    p.setBrush(Qt::NoBrush);
    p.drawArc(QRectF(20, 10, 24, 30), 0, 180 * 16);
    p.drawLine(QPointF(20, 25), QPointF(20, 28));
    p.drawLine(QPointF(44, 25), QPointF(44, 28));
  } else if (kind == QLatin1String("midpoint")) {
    p.drawLine(QPointF(8, 44), QPointF(56, 20));
    dot(p, 32, 32, kAccent);
  } else if (kind == QLatin1String("collinear")) {
    p.drawLine(QPointF(4, 46), QPointF(26, 34));
    p.drawLine(QPointF(38, 28), QPointF(60, 16));
    p.setPen(QPen(kAccent, 1.5, Qt::DashLine));
    p.drawLine(QPointF(26, 34), QPointF(38, 28));
  } else if (kind == QLatin1String("symmetry")) {
    p.setPen(QPen(kAccent, 2, Qt::DashLine));
    p.drawLine(QPointF(32, 4), QPointF(32, 60));
    dot(p, 14, 30);
    dot(p, 50, 30);
    p.setPen(QPen(kLine, 2.5));
    p.drawLine(QPointF(8, 46), QPointF(24, 46));
    p.drawLine(QPointF(40, 46), QPointF(56, 46));
  } else if (kind == QLatin1String("concentric")) {
    p.drawEllipse(QPointF(32, 32), 24, 24);
    p.drawEllipse(QPointF(32, 32), 12, 12);
    dot(p, 32, 32, kAccent);
  }
}

void selectIcon(QPainter& p) {
  p.setPen(QPen(kLine, 2.5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
  p.setBrush(QColor(250, 250, 252));
  p.drawPolygon(QPolygonF({QPointF(18, 8), QPointF(18, 50), QPointF(28, 40), QPointF(36, 56), QPointF(42, 53),
                           QPointF(34, 37), QPointF(48, 37)}));
}

void filletIcon(QPainter& p) {
  QPainterPath path;
  path.moveTo(8, 58);
  path.lineTo(8, 30);
  path.cubicTo(8, 16, 18, 8, 34, 8);
  path.lineTo(58, 8);
  path.lineTo(58, 58);
  path.closeSubpath();
  p.setBrush(kTop);
  p.setPen(QPen(kLine, 2.5));
  p.drawPath(path);
  p.setPen(QPen(kAccent, 4, Qt::SolidLine, Qt::RoundCap));
  p.setBrush(Qt::NoBrush);
  p.drawArc(QRectF(8, 8, 52, 44), 90 * 16, 90 * 16);
}

void chamferIcon(QPainter& p) {
  p.setBrush(kTop);
  p.setPen(QPen(kLine, 2.5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
  p.drawPolygon(QPolygonF({QPointF(8, 58), QPointF(8, 30), QPointF(30, 8), QPointF(58, 8), QPointF(58, 58)}));
  p.setPen(QPen(kAccent, 4, Qt::SolidLine, Qt::RoundCap));
  p.drawLine(QPointF(8, 30), QPointF(30, 8));
}

void revolveIcon(QPainter& p) {
  QLinearGradient g(8, 0, 56, 0);
  g.setColorAt(0, kLeft);
  g.setColorAt(0.5, kTop);
  g.setColorAt(1, kRight);
  p.setBrush(g);
  p.setPen(QPen(kLine, 2.5));
  QPainterPath vase;
  vase.moveTo(22, 8);
  vase.cubicTo(10, 24, 30, 30, 12, 56);
  vase.lineTo(52, 56);
  vase.cubicTo(34, 30, 54, 24, 42, 8);
  vase.closeSubpath();
  p.drawPath(vase);
  p.setPen(QPen(kAccent, 2, Qt::DashLine));
  p.drawLine(QPointF(32, 2), QPointF(32, 62));
}

void finishIcon(QPainter& p) {
  p.setPen(Qt::NoPen);
  p.setBrush(QColor(40, 160, 90));
  p.drawEllipse(QRectF(6, 6, 52, 52));
  p.setPen(QPen(Qt::white, 7, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
  p.setBrush(Qt::NoBrush);
  p.drawPolyline(QPolygonF({QPointF(18, 33), QPointF(28, 43), QPointF(46, 22)}));
}

void constructionIcon(QPainter& p) {
  p.setBrush(Qt::NoBrush);
  p.setPen(QPen(kAccent, 4, Qt::DashLine, Qt::RoundCap));
  p.drawLine(QPointF(10, 50), QPointF(54, 14));
}


// ---- Modify, inspect, insert, select and planned tools. Each has its own
// silhouette so they can be told apart at a glance.
void cube(QPainter& p, double x, double y, double w, const QColor& top, const QColor& left, const QColor& right) {
  const double h = w * 0.5;
  face(p, {QPointF(x + w / 2, y), QPointF(x + w, y + h / 2), QPointF(x + w / 2, y + h), QPointF(x, y + h / 2)}, top);
  face(p, {QPointF(x, y + h / 2), QPointF(x + w / 2, y + h), QPointF(x + w / 2, y + h + w * 0.55), QPointF(x, y + h / 2 + w * 0.55)}, left);
  face(p, {QPointF(x + w / 2, y + h), QPointF(x + w, y + h / 2), QPointF(x + w, y + h / 2 + w * 0.55), QPointF(x + w / 2, y + h + w * 0.55)}, right);
}

void shellIcon(QPainter& p) {
  cube(p, 6, 6, 52, kTop, kLeft, kRight);
  // the open top shows the hollow inside
  face(p, {QPointF(32, 13), QPointF(49, 21), QPointF(32, 29), QPointF(15, 21)}, kLine.lighter(150));
}

void combineIcon(QPainter& p) {
  cube(p, 4, 14, 34, kTop, kLeft, kRight);
  cube(p, 24, 4, 34, kAccent.lighter(130), kAccent, kAccent.darker(130));
}

void splitIcon(QPainter& p) {
  cube(p, 4, 18, 28, kTop, kLeft, kRight);
  cube(p, 30, 6, 28, kTop, kLeft, kRight);
  p.setPen(QPen(kAccent, 3, Qt::DashLine));
  p.drawLine(QPointF(8, 58), QPointF(58, 8));
}

void moveIcon(QPainter& p) {
  p.setPen(QPen(kLine, 3.5, Qt::SolidLine, Qt::RoundCap));
  p.drawLine(QPointF(32, 8), QPointF(32, 56));
  p.drawLine(QPointF(8, 32), QPointF(56, 32));
  p.setPen(Qt::NoPen);
  p.setBrush(kAccent);
  for (auto [x, y, dx, dy] : {std::array<double, 4>{32, 4, 0, 1}, {32, 60, 0, -1}, {4, 32, 1, 0}, {60, 32, -1, 0}})
    p.drawPolygon(QPolygonF({QPointF(x, y), QPointF(x + 9 * dx + 7 * dy, y + 9 * dy + 7 * dx), QPointF(x + 9 * dx - 7 * dy, y + 9 * dy - 7 * dx)}));
}

void scaleIcon(QPainter& p) {
  cube(p, 4, 26, 22, kTop, kLeft, kRight);
  p.setPen(QPen(kLine, 2, Qt::DashLine));
  p.setBrush(Qt::NoBrush);
  p.drawRect(QRectF(22, 6, 36, 36));
  p.setPen(QPen(kAccent, 3.5, Qt::SolidLine, Qt::RoundCap));
  p.drawLine(QPointF(26, 34), QPointF(52, 10));
  p.drawLine(QPointF(52, 10), QPointF(42, 11));
  p.drawLine(QPointF(52, 10), QPointF(51, 20));
}

void removeIcon(QPainter& p) {
  cube(p, 8, 10, 40, kTop, kLeft, kRight);
  p.setPen(QPen(QColor(220, 60, 50), 6, Qt::SolidLine, Qt::RoundCap));
  p.drawLine(QPointF(34, 34), QPointF(56, 56));
  p.drawLine(QPointF(56, 34), QPointF(34, 56));
}

void mirrorIcon(QPainter& p) {
  face(p, {QPointF(8, 14), QPointF(26, 22), QPointF(26, 50), QPointF(8, 42)}, kLeft);
  face(p, {QPointF(56, 14), QPointF(38, 22), QPointF(38, 50), QPointF(56, 42)}, kTop);
  p.setPen(QPen(kAccent, 3, Qt::DashLine));
  p.drawLine(QPointF(32, 4), QPointF(32, 60));
}

void measureIcon(QPainter& p) {
  p.setBrush(QColor(240, 196, 60));
  p.setPen(QPen(kLine, 2));
  p.drawRect(QRectF(4, 24, 56, 18));
  p.setPen(QPen(kLine, 2));
  for (int i = 0; i < 9; ++i) p.drawLine(QPointF(9 + i * 6, 24), QPointF(9 + i * 6, i % 2 ? 31 : 35));
}

void interferenceIcon(QPainter& p) {
  p.setBrush(kLeft);
  p.drawEllipse(QRectF(4, 14, 34, 34));
  p.setBrush(kTop);
  p.drawEllipse(QRectF(26, 14, 34, 34));
  QPainterPath a, b;
  a.addEllipse(QRectF(4, 14, 34, 34));
  b.addEllipse(QRectF(26, 14, 34, 34));
  p.setBrush(QColor(220, 60, 50));
  p.drawPath(a.intersected(b));
}

void sectionIcon(QPainter& p) {
  cube(p, 6, 8, 52, kTop, kLeft, kRight);
  face(p, {QPointF(32, 34), QPointF(58, 21), QPointF(58, 50), QPointF(32, 62)}, QColor(214, 96, 70));
  p.setPen(QPen(kLine, 1.2));
  for (int i = 0; i < 4; ++i) p.drawLine(QPointF(34 + i * 6, 58 - i * 3), QPointF(38 + i * 6, 30 - i * 3));
}

void comIcon(QPainter& p) {
  p.setBrush(Qt::NoBrush);
  p.setPen(QPen(kLine, 3));
  p.drawEllipse(QRectF(10, 10, 44, 44));
  p.setPen(Qt::NoPen);
  p.setBrush(kLine);
  p.drawPie(QRectF(10, 10, 44, 44), 0, 90 * 16);
  p.drawPie(QRectF(10, 10, 44, 44), 180 * 16, 90 * 16);
  p.setBrush(kAccent);
  p.drawEllipse(QPointF(32, 32), 4, 4);
}

void insertIcon(QPainter& p, bool flat) {
  document(p);
  if (flat) {
    p.setPen(QPen(kRight, 2.5));
    p.drawRect(QRectF(20, 24, 22, 16));
  } else {
    cube(p, 18, 22, 26, kTop, kLeft, kRight);
  }
  p.setPen(QPen(kAccent, 4, Qt::SolidLine, Qt::RoundCap));
  p.drawLine(QPointF(52, 4), QPointF(52, 22));
  p.drawLine(QPointF(52, 22), QPointF(46, 16));
  p.drawLine(QPointF(52, 22), QPointF(58, 16));
}

void exportIcon(QPainter& p) {
  document(p);
  p.setPen(QPen(kAccent, 4, Qt::SolidLine, Qt::RoundCap));
  p.drawLine(QPointF(34, 40), QPointF(58, 40));
  p.drawLine(QPointF(58, 40), QPointF(50, 32));
  p.drawLine(QPointF(58, 40), QPointF(50, 48));
}

void printIcon(QPainter& p) {
  p.setBrush(kLeft);
  p.drawRect(QRectF(6, 50, 52, 8));
  p.setPen(QPen(kLine, 3));
  p.drawLine(QPointF(10, 8), QPointF(54, 8));
  p.drawLine(QPointF(32, 8), QPointF(32, 22));
  p.setBrush(kAccent);
  p.setPen(QPen(kLine, 2));
  p.drawPolygon(QPolygonF({QPointF(26, 22), QPointF(38, 22), QPointF(32, 30)}));
  face(p, {QPointF(20, 50), QPointF(44, 50), QPointF(40, 36), QPointF(24, 36)}, kTop);
}

void imageIcon(QPainter& p) {
  p.setBrush(QColor(250, 250, 252));
  p.drawRoundedRect(QRectF(6, 12, 52, 40), 4, 4);
  face(p, {QPointF(10, 48), QPointF(26, 28), QPointF(36, 40), QPointF(44, 32), QPointF(54, 48)}, kLeft);
  p.setBrush(kAccent);
  p.drawEllipse(QPointF(46, 22), 4, 4);
}

void gearIcon(QPainter& p) {
  p.setBrush(kLeft);
  p.setPen(QPen(kLine, 2));
  QPolygonF g;
  for (int i = 0; i < 16; ++i) {
    const double a = i * M_PI / 8, r = i % 2 ? 22 : 28;
    g << QPointF(32 + r * std::cos(a), 32 + r * std::sin(a));
  }
  p.drawPolygon(g);
  p.setBrush(QColor(250, 250, 252));
  p.drawEllipse(QPointF(32, 32), 9, 9);
}

void unitsIcon(QPainter& p) {
  measureIcon(p);
  QFont f = p.font();
  f.setPixelSize(17);
  f.setBold(true);
  p.setFont(f);
  p.setPen(kLine);
  p.drawText(QRectF(0, 0, 64, 22), Qt::AlignCenter, QStringLiteral("mm"));
}

void gridIcon(QPainter& p) {
  p.setPen(QPen(kLine, 2));
  for (int i = 0; i < 4; ++i) {
    p.drawLine(QPointF(10 + i * 14.6, 8), QPointF(10 + i * 14.6, 56));
    p.drawLine(QPointF(8, 10 + i * 14.6), QPointF(56, 10 + i * 14.6));
  }
}

void filterIcon(QPainter& p, const QString& what) {
  if (what == QLatin1String("body")) {
    cube(p, 8, 6, 48, kTop, kLeft, kRight);
  } else if (what == QLatin1String("face")) {
    cube(p, 8, 6, 48, kLine.lighter(170), kLine.lighter(150), kLine.lighter(130));
    face(p, {QPointF(32, 6), QPointF(56, 18), QPointF(32, 30), QPointF(8, 18)}, kAccent);
  } else if (what == QLatin1String("edge")) {
    cube(p, 8, 6, 48, kLine.lighter(170), kLine.lighter(150), kLine.lighter(130));
    p.setPen(QPen(kAccent, 5, Qt::SolidLine, Qt::RoundCap));
    p.drawLine(QPointF(8, 18), QPointF(32, 30));
  } else {
    cube(p, 8, 6, 48, kLine.lighter(170), kLine.lighter(150), kLine.lighter(130));
    p.setPen(Qt::NoPen);
    p.setBrush(kAccent);
    p.drawEllipse(QPointF(32, 30), 6, 6);
  }
}

void componentIcon(QPainter& p) {
  cube(p, 4, 20, 26, kTop, kLeft, kRight);
  cube(p, 34, 20, 26, kTop, kLeft, kRight);
  cube(p, 19, 2, 26, kAccent.lighter(130), kAccent, kAccent.darker(130));
}

void jointIcon(QPainter& p, bool origin) {
  p.setBrush(kLeft);
  p.drawRect(QRectF(6, 36, 24, 18));
  p.setBrush(kTop);
  p.drawRect(QRectF(34, 12, 24, 18));
  p.setPen(QPen(kAccent, 3));
  p.setBrush(Qt::NoBrush);
  p.drawEllipse(QPointF(32, 33), 9, 9);
  if (origin) {
    p.drawLine(QPointF(32, 20), QPointF(32, 46));
    p.drawLine(QPointF(19, 33), QPointF(45, 33));
  }
}

void rigidIcon(QPainter& p) {
  cube(p, 6, 16, 30, kTop, kLeft, kRight);
  cube(p, 28, 16, 30, kTop, kLeft, kRight);
  p.setBrush(QColor(220, 60, 50));
  p.drawRoundedRect(QRectF(22, 4, 20, 14), 3, 3);
}

void motionIcon(QPainter& p) {
  p.setPen(QPen(kLine, 3));
  p.setBrush(Qt::NoBrush);
  p.drawArc(QRectF(8, 8, 48, 48), 30 * 16, 300 * 16);
  p.setBrush(kAccent);
  p.setPen(Qt::NoPen);
  p.drawPolygon(QPolygonF({QPointF(52, 14), QPointF(58, 30), QPointF(42, 26)}));
}

void configureIcon(QPainter& p) {
  p.setBrush(kTop);
  p.drawRect(QRectF(6, 8, 52, 48));
  p.setPen(QPen(kLine, 2));
  for (int i = 1; i < 4; ++i) p.drawLine(QPointF(6, 8 + i * 12), QPointF(58, 8 + i * 12));
  p.drawLine(QPointF(24, 8), QPointF(24, 56));
}

void planeIcon(QPainter& p) {
  face(p, {QPointF(4, 40), QPointF(30, 20), QPointF(60, 26), QPointF(34, 46)}, QColor(240, 160, 60, 200));
  face(p, {QPointF(4, 30), QPointF(30, 10), QPointF(60, 16), QPointF(34, 36)}, kTop);
}

// A sheet seen face-on with an eye-line arrow pointing straight at it.
void lookAtIcon(QPainter& p) {
  p.setPen(QPen(kLine, 2));
  p.setBrush(kTop);
  p.drawRect(QRectF(26, 8, 32, 40));
  p.setPen(QPen(kAccent, 4, Qt::SolidLine, Qt::RoundCap));
  p.drawLine(QPointF(4, 46), QPointF(20, 32));
  p.setPen(Qt::NoPen);
  p.setBrush(kAccent);
  p.drawPolygon(QPolygonF({QPointF(26, 27), QPointF(13, 30), QPointF(22, 39)}));
}

void axisIcon(QPainter& p) {
  p.setPen(QPen(kAccent, 4, Qt::DashLine, Qt::RoundCap));
  p.drawLine(QPointF(32, 2), QPointF(32, 62));
  p.setPen(QPen(kLine, 2));
  p.setBrush(kLeft);
  p.drawEllipse(QRectF(16, 16, 32, 10));
  p.drawRect(QRectF(16, 21, 32, 26));
}

void curvatureIcon(QPainter& p) {
  p.setPen(QPen(kLine, 3));
  QPainterPath c;
  c.moveTo(6, 50);
  c.cubicTo(22, 10, 42, 10, 58, 50);
  p.drawPath(c);
  p.setPen(QPen(kAccent, 2));
  for (int i = 0; i < 6; ++i) {
    const double t = 0.15 + i * 0.14;
    const QPointF pt = c.pointAtPercent(t);
    p.drawLine(pt, pt + QPointF(0, -10 - 8 * std::sin(t * M_PI)));
  }
}

void zebraIcon(QPainter& p) {
  p.setBrush(QColor(250, 250, 252));
  p.drawEllipse(QRectF(6, 6, 52, 52));
  p.setPen(Qt::NoPen);
  p.setBrush(kLine);
  for (int i = 0; i < 4; ++i) p.drawRect(QRectF(10 + i * 12, 8, 6, 48));
}

void draftIcon(QPainter& p) {
  face(p, {QPointF(10, 56), QPointF(20, 8), QPointF(44, 8), QPointF(54, 56)}, kLeft);
  face(p, {QPointF(10, 56), QPointF(20, 8), QPointF(28, 8), QPointF(18, 56)}, QColor(80, 190, 120));
  face(p, {QPointF(54, 56), QPointF(44, 8), QPointF(36, 8), QPointF(46, 56)}, QColor(220, 80, 70));
}


void centerRectIcon(QPainter& p) {
  stroke(p);
  p.drawRect(QRectF(10, 16, 44, 32));
  p.setPen(QPen(kAccent, 1.5, Qt::DashLine));
  p.drawLine(QPointF(10, 16), QPointF(54, 48));
  p.drawLine(QPointF(54, 16), QPointF(10, 48));
  dot(p, 32, 32);
}

void polygonIcon(QPainter& p) {
  stroke(p);
  QPolygonF hex;
  for (int i = 0; i < 6; ++i) hex << QPointF(32 + 24 * std::cos(i * M_PI / 3), 32 + 24 * std::sin(i * M_PI / 3));
  p.drawPolygon(hex);
  dot(p, 32, 32);
}

void slotIcon(QPainter& p) {
  stroke(p);
  p.drawRoundedRect(QRectF(6, 20, 52, 24), 12, 12);
  dot(p, 18, 32);
  dot(p, 46, 32);
}

void trimIcon(QPainter& p) {
  stroke(p);
  p.drawLine(QPointF(8, 40), QPointF(30, 40));
  p.setPen(QPen(QColor(220, 60, 50), 3, Qt::DashLine));
  p.drawLine(QPointF(30, 40), QPointF(56, 40));
  // scissors
  p.setPen(QPen(kLine, 2.5));
  p.setBrush(Qt::NoBrush);
  p.drawEllipse(QPointF(20, 16), 6, 6);
  p.drawEllipse(QPointF(38, 16), 6, 6);
  p.drawLine(QPointF(24, 20), QPointF(36, 34));
  p.drawLine(QPointF(34, 20), QPointF(22, 34));
}

void pipeIcon(QPainter& p) {
  QPainterPath path;
  path.moveTo(8, 50);
  path.cubicTo(8, 20, 28, 14, 56, 14);
  p.setBrush(Qt::NoBrush);
  p.setPen(QPen(kLine, 14, Qt::SolidLine, Qt::FlatCap));
  p.drawPath(path);
  p.setPen(QPen(kLeft, 10, Qt::SolidLine, Qt::FlatCap));
  p.drawPath(path);
  p.setPen(QPen(kLine, 2));
  p.setBrush(kTop);
  p.drawEllipse(QPointF(8, 52), 6, 3);
}

void offsetFaceIcon(QPainter& p) {
  cube(p, 6, 18, 40, kTop, kLeft, kRight);
  p.setPen(QPen(kAccent, 2.5, Qt::DashLine));
  p.setBrush(Qt::NoBrush);
  p.drawPolygon(QPolygonF({QPointF(30, 4), QPointF(58, 16), QPointF(58, 30), QPointF(30, 18)}));
  p.setPen(QPen(kAccent, 2.5));
  p.drawLine(QPointF(44, 26), QPointF(52, 20));
}

void threadIcon(QPainter& p) {
  p.setPen(QPen(kLine, 2));
  QLinearGradient g(14, 0, 50, 0);
  g.setColorAt(0, kLeft);
  g.setColorAt(1, kRight);
  p.setBrush(g);
  p.drawRect(QRectF(18, 6, 28, 52));
  p.setPen(QPen(kLine, 2.5));
  for (int i = 0; i < 6; ++i) {
    const double y = 10 + i * 8;
    p.drawLine(QPointF(14, y + 6), QPointF(50, y));
  }
}

void coilIcon(QPainter& p) {
  p.setBrush(Qt::NoBrush);
  for (int i = 0; i < 4; ++i) {
    const double y = 12 + i * 11;
    p.setPen(QPen(kLine, 6, Qt::SolidLine, Qt::RoundCap));
    p.drawArc(QRectF(12, y, 40, 12), 0, 180 * 16);
    p.setPen(QPen(kLeft, 4, Qt::SolidLine, Qt::RoundCap));
    p.drawArc(QRectF(12, y, 40, 12), 180 * 16, 180 * 16);
  }
}

void splineIcon(QPainter& p) {
  stroke(p);
  QPainterPath c;
  c.moveTo(6, 48);
  c.cubicTo(18, 4, 34, 60, 58, 14);
  p.setBrush(Qt::NoBrush);
  p.drawPath(c);
  p.setPen(QPen(kLine, 1.5));
  p.setBrush(kAccent);
  for (QPointF q : {QPointF(6, 48), QPointF(23, 30), QPointF(40, 34), QPointF(58, 14)}) p.drawEllipse(q, 4, 4);
}

void sketchFilletIcon(QPainter& p) {
  stroke(p);
  p.setBrush(Qt::NoBrush);
  p.drawLine(QPointF(10, 56), QPointF(10, 30));
  p.drawLine(QPointF(30, 10), QPointF(56, 10));
  p.setPen(QPen(kAccent, 4, Qt::SolidLine, Qt::RoundCap));
  p.drawArc(QRectF(10, 10, 40, 40), 90 * 16, 90 * 16);
  p.setPen(QPen(kLine, 1.5, Qt::DashLine));
  p.drawLine(QPointF(10, 10), QPointF(24, 24));
}

void sketchChamferIcon(QPainter& p) {
  stroke(p);
  p.setBrush(Qt::NoBrush);
  p.drawLine(QPointF(10, 56), QPointF(10, 30));
  p.drawLine(QPointF(30, 10), QPointF(56, 10));
  p.setPen(QPen(kAccent, 4, Qt::SolidLine, Qt::RoundCap));
  p.drawLine(QPointF(10, 30), QPointF(30, 10));
}

void extendIcon(QPainter& p) {
  stroke(p);
  p.drawLine(QPointF(6, 40), QPointF(30, 40));
  p.setPen(QPen(kAccent, 3, Qt::DashLine));
  p.drawLine(QPointF(30, 40), QPointF(50, 40));
  p.setPen(QPen(kLine, 4));
  p.drawLine(QPointF(54, 12), QPointF(54, 58));
  p.setBrush(kAccent);
  p.setPen(Qt::NoPen);
  p.drawPolygon(QPolygonF({QPointF(52, 40), QPointF(42, 34), QPointF(42, 46)}));
}

void sketchMirrorIcon(QPainter& p) {
  p.setPen(QPen(kAccent, 2.5, Qt::DashDotLine));
  p.drawLine(QPointF(32, 4), QPointF(32, 60));
  stroke(p);
  p.setBrush(Qt::NoBrush);
  p.drawPolyline(QPolygonF({QPointF(26, 14), QPointF(8, 30), QPointF(26, 50)}));
  p.setPen(QPen(kLeft, 3, Qt::DashLine));
  p.drawPolyline(QPolygonF({QPointF(38, 14), QPointF(56, 30), QPointF(38, 50)}));
}

void offsetIcon(QPainter& p) {
  stroke(p);
  p.setBrush(Qt::NoBrush);
  p.drawRoundedRect(QRectF(20, 20, 24, 24), 3, 3);
  p.setPen(QPen(kAccent, 3, Qt::DashLine));
  p.drawRoundedRect(QRectF(8, 8, 48, 48), 8, 8);
}

void holeIcon(QPainter& p) {
  cube(p, 6, 10, 52, kTop, kLeft, kRight);
  p.setBrush(kLine);
  p.drawEllipse(QRectF(24, 17, 16, 8));
  p.setPen(QPen(kAccent, 2, Qt::DashLine));
  p.drawLine(QPointF(32, 4), QPointF(32, 30));
}

void patternIcon(QPainter& p, bool circular) {
  if (circular) {
    for (int i = 0; i < 6; ++i) {
      const double a = i * M_PI / 3;
      cube(p, 26 + 20 * std::cos(a), 24 + 20 * std::sin(a), 12, kTop, kLeft, kRight);
    }
    p.setPen(QPen(kAccent, 2, Qt::DashLine));
    p.setBrush(Qt::NoBrush);
    p.drawEllipse(QPointF(32, 32), 20, 20);
  } else {
    for (int i = 0; i < 3; ++i)
      for (int j = 0; j < 2; ++j) cube(p, 4 + i * 20, 8 + j * 26, 16, kTop, kLeft, kRight);
  }
}

void sweepIcon(QPainter& p) {
  QPainterPath path;
  path.moveTo(10, 54);
  path.cubicTo(10, 20, 30, 10, 56, 12);
  p.setPen(QPen(kLeft, 14, Qt::SolidLine, Qt::RoundCap));
  p.setBrush(Qt::NoBrush);
  p.drawPath(path);
  p.setPen(QPen(kAccent, 2, Qt::DashLine));
  p.drawPath(path);
  p.setPen(QPen(kLine, 2));
  p.setBrush(kTop);
  p.drawEllipse(QRectF(2, 48, 16, 12));
}

void loftIcon(QPainter& p) {
  face(p, {QPointF(14, 54), QPointF(24, 12), QPointF(40, 12), QPointF(50, 54)}, kLeft);
  p.setBrush(kTop);
  p.drawEllipse(QRectF(22, 6, 20, 10));
  p.setPen(QPen(kAccent, 2.5));
  p.setBrush(Qt::NoBrush);
  p.drawRect(QRectF(10, 50, 44, 8));
}

void pressPullIcon(QPainter& p) {
  cube(p, 6, 18, 52, kTop, kLeft, kRight);
  face(p, {QPointF(32, 18), QPointF(58, 31), QPointF(32, 44), QPointF(6, 31)}, kAccent.lighter(140));
  p.setPen(QPen(kAccent, 4, Qt::SolidLine, Qt::RoundCap));
  p.drawLine(QPointF(32, 30), QPointF(32, 4));
  p.drawLine(QPointF(32, 4), QPointF(25, 11));
  p.drawLine(QPointF(32, 4), QPointF(39, 11));
}

void fallback(QPainter& p, const QString& name) {
  p.setBrush(kTop);
  p.drawRoundedRect(QRectF(6, 6, 52, 52), 8, 8);
  QFont f = p.font();
  f.setPixelSize(30);
  f.setBold(true);
  p.setFont(f);
  p.drawText(QRectF(6, 6, 52, 52), Qt::AlignCenter, name.left(1).toUpper());
}

QPixmap render(const QString& name, int size) {
  QPixmap pm(size, size);
  pm.fill(Qt::transparent);
  QPainter p(&pm);
  p.setRenderHint(QPainter::Antialiasing);
  p.scale(size / 64.0, size / 64.0);
  p.setPen(QPen(kLine, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
  if (name == QLatin1String("box")) box(p);
  else if (name == QLatin1String("cylinder")) cylinder(p);
  else if (name == QLatin1String("cone")) cone(p);
  else if (name == QLatin1String("sphere")) sphere(p);
  else if (name == QLatin1String("torus")) torus(p);
  else if (name == QLatin1String("parameters")) parameters(p);
  else if (name == QLatin1String("orbit")) orbit(p);
  else if (name == QLatin1String("pan")) pan(p);
  else if (name == QLatin1String("home")) home(p);
  else if (name == QLatin1String("fit")) fit(p);
  else if (name == QLatin1String("sketch")) sketchIcon(p);
  else if (name == QLatin1String("sketch-locked")) sketchLockedIcon(p);
  else if (name == QLatin1String("project")) projectIcon(p);
  else if (name == QLatin1String("extrude")) extrudeIcon(p);
  else if (name == QLatin1String("line")) lineIcon(p);
  else if (name == QLatin1String("rectangle")) rectIcon(p);
  else if (name == QLatin1String("circle")) circleIcon(p);
  else if (name == QLatin1String("arc")) arcIcon(p);
  else if (name == QLatin1String("point")) pointIcon(p);
  else if (name == QLatin1String("dimension")) dimensionIcon(p);
  else if (name == QLatin1String("finish")) finishIcon(p);
  else if (name == QLatin1String("fillet")) filletIcon(p);
  else if (name == QLatin1String("chamfer")) chamferIcon(p);
  else if (name == QLatin1String("revolve")) revolveIcon(p);
  else if (name == QLatin1String("select")) selectIcon(p);
  else if (name == QLatin1String("construction")) constructionIcon(p);
  else if (name.startsWith(QLatin1String("c-"))) constraintIcon(p, name.mid(2));
  else if (name == QLatin1String("shell")) shellIcon(p);
  else if (name == QLatin1String("sweep")) sweepIcon(p);
  else if (name == QLatin1String("loft")) loftIcon(p);
  else if (name == QLatin1String("presspull")) pressPullIcon(p);
  else if (name == QLatin1String("center-rectangle")) centerRectIcon(p);
  else if (name == QLatin1String("polygon")) polygonIcon(p);
  else if (name == QLatin1String("slot")) slotIcon(p);
  else if (name == QLatin1String("trim")) trimIcon(p);
  else if (name == QLatin1String("spline")) splineIcon(p);
  else if (name == QLatin1String("pipe")) pipeIcon(p);
  else if (name == QLatin1String("coil")) coilIcon(p);
  else if (name == QLatin1String("thread")) threadIcon(p);
  else if (name == QLatin1String("offset-face")) offsetFaceIcon(p);
  else if (name == QLatin1String("sketch-fillet")) sketchFilletIcon(p);
  else if (name == QLatin1String("offset")) offsetIcon(p);
  else if (name == QLatin1String("sketch-chamfer")) sketchChamferIcon(p);
  else if (name == QLatin1String("extend")) extendIcon(p);
  else if (name == QLatin1String("sketch-mirror")) sketchMirrorIcon(p);
  else if (name == QLatin1String("hole")) holeIcon(p);
  else if (name == QLatin1String("pattern-rect")) patternIcon(p, false);
  else if (name == QLatin1String("pattern-path")) pathPatternIcon(p);
  else if (name == QLatin1String("pattern-circ")) patternIcon(p, true);
  else if (name == QLatin1String("combine")) combineIcon(p);
  else if (name == QLatin1String("split")) splitIcon(p);
  else if (name == QLatin1String("move")) moveIcon(p);
  else if (name == QLatin1String("scale")) scaleIcon(p);
  else if (name == QLatin1String("remove")) removeIcon(p);
  else if (name == QLatin1String("mirror")) mirrorIcon(p);
  else if (name == QLatin1String("measure")) measureIcon(p);
  else if (name == QLatin1String("interference")) interferenceIcon(p);
  else if (name == QLatin1String("section")) sectionIcon(p);
  else if (name == QLatin1String("com")) comIcon(p);
  else if (name == QLatin1String("insert")) insertIcon(p, false);
  else if (name == QLatin1String("insert-2d")) insertIcon(p, true);
  else if (name == QLatin1String("export")) exportIcon(p);
  else if (name == QLatin1String("print")) printIcon(p);
  else if (name == QLatin1String("image")) imageIcon(p);
  else if (name == QLatin1String("preferences")) gearIcon(p);
  else if (name == QLatin1String("units")) unitsIcon(p);
  else if (name == QLatin1String("grid")) gridIcon(p);
  else if (name == QLatin1String("body") || name == QLatin1String("face") || name == QLatin1String("edge") ||
           name == QLatin1String("vertex")) filterIcon(p, name);
  else if (name == QLatin1String("component")) componentIcon(p);
  else if (name == QLatin1String("joint")) jointIcon(p, false);
  else if (name == QLatin1String("joint-origin")) jointIcon(p, true);
  else if (name == QLatin1String("rigid")) rigidIcon(p);
  else if (name == QLatin1String("motion")) motionIcon(p);
  else if (name == QLatin1String("configure")) configureIcon(p);
  else if (name == QLatin1String("plane")) planeIcon(p);
  else if (name == QLatin1String("look-at")) lookAtIcon(p);
  else if (name == QLatin1String("plane-angle")) {
    planeIcon(p);
    p.setPen(QPen(kAccent, 3));
    p.setBrush(Qt::NoBrush);
    p.drawArc(QRectF(36, 30, 24, 24), 0, 90 * 16);
  } else if (name == QLatin1String("plane-mid")) {
    face(p, {QPointF(4, 50), QPointF(30, 34), QPointF(60, 40), QPointF(34, 56)}, kTop);
    face(p, {QPointF(4, 34), QPointF(30, 18), QPointF(60, 24), QPointF(34, 40)}, QColor(240, 160, 60, 220));
    face(p, {QPointF(4, 18), QPointF(30, 2), QPointF(60, 8), QPointF(34, 24)}, kTop);
  }
  else if (name == QLatin1String("axis")) axisIcon(p);
  else if (name == QLatin1String("curvature")) curvatureIcon(p);
  else if (name == QLatin1String("zebra")) zebraIcon(p);
  else if (name == QLatin1String("draft")) draftIcon(p);
  else if (name == QLatin1String("undo")) arrow(p, false);
  else if (name == QLatin1String("redo")) arrow(p, true);
  else if (name == QLatin1String("save")) save(p);
  else if (name == QLatin1String("file")) document(p);
  else fallback(p, name);
  return pm;
}

} // namespace

QIcon themed(const QString& themeName, const QString& fallbackName) {
  // Desktop icon themes are drawn for light panels; use ours on dark ones.
  return gDark ? icon(fallbackName) : QIcon::fromTheme(themeName, icon(fallbackName));
}

QIcon icon(const QString& name) {
  auto it = cache().find(name);
  if (it != cache().end()) return *it;
  QIcon ic;
  for (int s : {16, 24, 32, 48, 64}) ic.addPixmap(render(name, s));
  cache().insert(name, ic);
  return ic;
}

void setIconTheme(const Theme::Colors& c) {
  kLine = c.iconLine;
  kTop = c.iconTop;
  kLeft = c.iconLeft;
  kRight = c.iconRight;
  kAccent = c.iconAccent;
  gDark = c.window.lightness() < 128;
  cache().clear();
}

void setIcon(QAbstractButton* button, const QString& name) {
  button->setProperty("tsrIcon", name);
  button->setIcon(icon(name));
}

void setIcon(QAction* action, const QString& name) {
  action->setProperty("tsrIcon", name);
  action->setIcon(icon(name));
}

void retintIcons(QObject* root) {
  for (QAbstractButton* b : root->findChildren<QAbstractButton*>()) {
    const QString n = b->property("tsrIcon").toString();
    if (!n.isEmpty()) b->setIcon(icon(n));
  }
  for (QAction* a : root->findChildren<QAction*>()) {
    const QString n = a->property("tsrIcon").toString();
    if (!n.isEmpty()) a->setIcon(icon(n));
  }
}

} // namespace tsr::app
