#include "Icons.h"

#include <QHash>

#include <array>
#include <QPainter>
#include <QPainterPath>
#include <QPixmap>

namespace tsr::app {

namespace {

// All command icons are drawn here from simple geometry, so the project
// ships no third-party artwork. 64x64 logical canvas.
const QColor kLine(40, 52, 68);
const QColor kTop(170, 205, 240);
const QColor kLeft(110, 160, 215);
const QColor kRight(70, 125, 190);
const QColor kAccent(246, 116, 0);

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
  else if (name == QLatin1String("undo")) arrow(p, false);
  else if (name == QLatin1String("redo")) arrow(p, true);
  else if (name == QLatin1String("save")) save(p);
  else if (name == QLatin1String("file")) document(p);
  else fallback(p, name);
  return pm;
}

} // namespace

QIcon themed(const QString& themeName, const QString& fallbackName) {
  return QIcon::fromTheme(themeName, icon(fallbackName));
}

QIcon icon(const QString& name) {
  static QHash<QString, QIcon> cache;
  auto it = cache.find(name);
  if (it != cache.end()) return *it;
  QIcon ic;
  for (int s : {16, 24, 32, 48, 64}) ic.addPixmap(render(name, s));
  cache.insert(name, ic);
  return ic;
}

} // namespace tsr::app
