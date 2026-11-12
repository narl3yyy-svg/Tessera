#pragma once
#include <QIcon>
#include <QWidget>

#include <functional>
#include <vector>

namespace tsr::app {

// The right-click marking menu of the familiar CAD tool: up to eight
// commands in a ring around the cursor (click one, or press and flick the
// right button towards it and release), and a list of further commands
// below. Closes on Escape or a click elsewhere.
class MarkingMenu : public QWidget {
  Q_OBJECT
public:
  struct Item {
    QString text;
    QIcon icon;
    std::function<void()> run;
    bool enabled = true;
  };
  // ring: clockwise from the top (N, NE, E, SE, S, SW, W, NW); empty text = gap.
  MarkingMenu(std::vector<Item> ring, std::vector<Item> list, QWidget* parent = nullptr);

  void popupAt(const QPoint& globalCentre);
  // Tests: run the ring item with this text, as a click would.
  bool triggerForTest(const QString& text);

protected:
  void paintEvent(QPaintEvent* e) override;
  void keyPressEvent(QKeyEvent* e) override;
  void mouseMoveEvent(QMouseEvent* e) override;
  void mouseReleaseEvent(QMouseEvent* e) override;

private:
  void run(const Item& item);
  int ringIndexAt(const QPoint& p) const;   // the ring item a flick points at, or -1

  std::vector<Item> ring_;
  std::vector<Item> list_;
  QPoint centre_;   // in widget coordinates
  int hover_ = -1;
};

} // namespace tsr::app
