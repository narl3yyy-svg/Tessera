#include "MarkingMenu.h"

#include <QGuiApplication>
#include <QKeyEvent>
#include <QScreen>
#include <QMouseEvent>
#include <QPainter>
#include <QToolButton>
#include <QVBoxLayout>

#include <algorithm>
#include <cmath>
#include <numbers>

namespace tsr::app {

namespace {
constexpr int kRadius = 118;
constexpr int kButtonW = 150;
constexpr int kButtonH = 30;
constexpr int kListW = 190;
constexpr int kListRowH = 26;
} // namespace

MarkingMenu::MarkingMenu(std::vector<Item> ring, std::vector<Item> list, QWidget* parent)
    : QWidget(parent, Qt::Popup | Qt::FramelessWindowHint), ring_(std::move(ring)), list_(std::move(list)) {
  setObjectName(QStringLiteral("markingMenu"));
  setAttribute(Qt::WA_TranslucentBackground);
  setAttribute(Qt::WA_DeleteOnClose);
  setMouseTracking(true);
  const int w = 2 * kRadius + kButtonW + 20;
  const int listH = static_cast<int>(list_.size()) * kListRowH + (list_.empty() ? 0 : 12);
  const int h = 2 * kRadius + kButtonH + 20 + listH;
  resize(w, h);
  centre_ = QPoint(w / 2, kRadius + kButtonH / 2 + 10);
  const QString ringStyle = QStringLiteral(
      "QToolButton { background: rgba(40,44,52,235); color: #e8eaee; border: 1px solid #5b6472; border-radius: 4px;"
      " padding: 2px 8px; text-align: left; }"
      "QToolButton:hover { background: #2f6db5; border-color: #4d8de0; }"
      "QToolButton:disabled { color: #6c7380; }");
  for (int i = 0; i < static_cast<int>(ring_.size()) && i < 8; ++i) {
    if (ring_[i].text.isEmpty()) continue;
    const double a = -std::numbers::pi / 2 + i * std::numbers::pi / 4;   // clockwise from the top
    const QPoint c = centre_ + QPoint(static_cast<int>(std::lround(std::cos(a) * kRadius)),
                                      static_cast<int>(std::lround(std::sin(a) * kRadius)));
    auto* b = new QToolButton(this);
    b->setObjectName(QStringLiteral("ring_") + ring_[i].text);
    b->setText(ring_[i].text);
    b->setIcon(ring_[i].icon);
    b->setIconSize(QSize(18, 18));
    b->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    b->setEnabled(ring_[i].enabled);
    b->setStyleSheet(ringStyle);
    b->setFixedSize(kButtonW, kButtonH);
    // Buttons on the left grow leftwards from the ring, on the right rightwards.
    const double cx = std::cos(a);
    const int x = cx < -0.3 ? c.x() - kButtonW + 20 : cx > 0.3 ? c.x() - 20 : c.x() - kButtonW / 2;
    b->move(x, c.y() - kButtonH / 2);
    const Item item = ring_[i];
    connect(b, &QToolButton::clicked, this, [this, item] { run(item); });
  }
  // The list below the ring.
  int y = centre_.y() + kRadius + kButtonH / 2 + 12;
  for (const auto& it : list_) {
    auto* b = new QToolButton(this);
    b->setObjectName(QStringLiteral("list_") + it.text);
    b->setText(it.text);
    b->setIcon(it.icon);
    b->setIconSize(QSize(16, 16));
    b->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    b->setEnabled(it.enabled);
    b->setStyleSheet(ringStyle + QStringLiteral("QToolButton { border-radius: 0; }"));
    b->setFixedSize(kListW, kListRowH);
    b->move(centre_.x() - kListW / 2, y);
    y += kListRowH;
    const Item item = it;
    connect(b, &QToolButton::clicked, this, [this, item] { run(item); });
  }
}

void MarkingMenu::popupAt(const QPoint& globalCentre) {
  // Centred on the cursor, but kept on the screen near its edges.
  QPoint at = globalCentre - centre_;
  if (QScreen* sc = QGuiApplication::screenAt(globalCentre)) {
    const QRect avail = sc->availableGeometry();
    at.setX(std::clamp(at.x(), avail.left(), std::max(avail.left(), avail.right() - width())));
    at.setY(std::clamp(at.y(), avail.top(), std::max(avail.top(), avail.bottom() - height())));
  }
  move(at);
  show();
  setFocus();
}

bool MarkingMenu::triggerForTest(const QString& text) {
  for (const auto& i : ring_)
    if (i.text == text && i.enabled) {
      run(i);
      return true;
    }
  for (const auto& i : list_)
    if (i.text == text && i.enabled) {
      run(i);
      return true;
    }
  return false;
}

void MarkingMenu::run(const Item& item) {
  close();
  if (item.run) item.run();
}

int MarkingMenu::ringIndexAt(const QPoint& p) const {
  const QPoint d = p - centre_;
  if (std::hypot(d.x(), d.y()) < 25) return -1;
  double a = std::atan2(d.y(), d.x()) + std::numbers::pi / 2;   // 0 at the top, clockwise
  if (a < 0) a += 2 * std::numbers::pi;
  const int i = static_cast<int>(std::lround(a / (std::numbers::pi / 4))) % 8;
  return i < static_cast<int>(ring_.size()) && !ring_[i].text.isEmpty() && ring_[i].enabled ? i : -1;
}

void MarkingMenu::paintEvent(QPaintEvent*) {
  QPainter p(this);
  p.setRenderHint(QPainter::Antialiasing);
  // A small hub with a pointer towards the item the cursor is heading for.
  p.setPen(QPen(QColor(120, 128, 140, 200), 1.5));
  p.setBrush(QColor(40, 44, 52, 200));
  p.drawEllipse(centre_, 14, 14);
  if (hover_ >= 0) {
    const double a = -std::numbers::pi / 2 + hover_ * std::numbers::pi / 4;
    p.setPen(QPen(QColor(77, 141, 224), 3, Qt::SolidLine, Qt::RoundCap));
    p.drawLine(centre_, centre_ + QPoint(static_cast<int>(std::cos(a) * 30), static_cast<int>(std::sin(a) * 30)));
  }
}

void MarkingMenu::keyPressEvent(QKeyEvent* e) {
  if (e->key() == Qt::Key_Escape) {
    close();
    return;
  }
  QWidget::keyPressEvent(e);
}

void MarkingMenu::mouseMoveEvent(QMouseEvent* e) {
  const int h = ringIndexAt(e->position().toPoint());
  if (h != hover_) {
    hover_ = h;
    update();
  }
}

void MarkingMenu::mouseReleaseEvent(QMouseEvent* e) {
  // A right-button flick: released while pointing at a ring item.
  if (e->button() == Qt::RightButton && hover_ >= 0) {
    run(ring_[hover_]);
    return;
  }
  QWidget::mouseReleaseEvent(e);
}

} // namespace tsr::app
