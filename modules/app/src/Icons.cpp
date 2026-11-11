#include "Icons.h"

#include <QAbstractButton>
#include <QAction>
#include <QHash>

#include <array>
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
