#include "Theme.h"
#include "Icons.h"

#include <QApplication>
#include <QPalette>
#include <QSettings>
#include <QStyle>
#include <QStyleFactory>

namespace tsr::app {

namespace {

Theme::Colors darkColors() {
  Theme::Colors c;
  c.window = QColor(0x35, 0x3a, 0x43);
  c.panel = QColor(0x3b, 0x41, 0x4c);
  c.base = QColor(0x2c, 0x30, 0x37);
  c.text = QColor(0xdd, 0xe1, 0xe7);
  c.mutedText = QColor(0x9a, 0xa1, 0xac);
  c.border = QColor(0x24, 0x28, 0x2e);
  c.highlight = QColor(0x2f, 0x7b, 0xd8);
  c.iconLine = QColor(0xf0, 0xf3, 0xf7);     // bright, bold sketch strokes on the dark ribbon
  c.iconTop = QColor(0xc4, 0xdf, 0xfb);
  c.iconLeft = QColor(0x7a, 0xb4, 0xf0);
  c.iconRight = QColor(0x43, 0x86, 0xd9);
  c.iconAccent = QColor(0xff, 0x9a, 0x2e);
  c.viewTop = QColor(0x4a, 0x51, 0x5e);
  c.viewBottom = QColor(0x33, 0x38, 0x41);
  c.grid = QColor(0x4b, 0x52, 0x5f);
  c.gridMajor = QColor(0x5f, 0x67, 0x76);
  c.cubeBox = QColor(0xc9, 0xce, 0xd6);
  c.cubeText = QColor(0x44, 0x4a, 0x54);
  c.edges = QColor(0x1e, 0x22, 0x28);
  c.overlayText = QColor(0xc8, 0xcd, 0xd5);
  c.sketchFree = QColor(0x4d, 0xa6, 0xff);
  c.sketchFixed = QColor(0xf2, 0xf4, 0xf7);
  c.sketchLabel = QColor(0xf0, 0xf2, 0xf5);
  c.sketchGlyph = QColor(0xa8, 0xb0, 0xbc);
  c.sketchFinished = QColor(0x8c, 0xb8, 0xe8);
  c.navBackground = QColor(0x2f, 0x34, 0x3c, 235);
  c.navBorder = QColor(255, 255, 255, 35);
  c.errorBackground = QColor(0x7a, 0x34, 0x30);
  return c;
}

Theme::Colors lightColors() {
  Theme::Colors c;
  c.window = QColor(0xef, 0xf0, 0xf1);
  c.panel = QColor(0xf5, 0xf6, 0xf7);
  c.base = QColor(0xff, 0xff, 0xff);
  c.text = QColor(0x23, 0x26, 0x29);
  c.mutedText = QColor(0x6a, 0x70, 0x78);
  c.border = QColor(0xc4, 0xc8, 0xcc);
  c.highlight = QColor(0x3d, 0xae, 0xe9);
  c.iconLine = QColor(40, 52, 68);
  c.iconTop = QColor(170, 205, 240);
  c.iconLeft = QColor(110, 160, 215);
  c.iconRight = QColor(70, 125, 190);
  c.iconAccent = QColor(246, 116, 0);
  c.viewTop = QColor(250, 251, 253);
  c.viewBottom = QColor(196, 206, 218);
  c.grid = QColor(205, 211, 218);
  c.gridMajor = QColor(160, 168, 178);
  c.cubeBox = QColor(236, 239, 243);
  c.cubeText = QColor(60, 66, 74);
  c.edges = QColor(30, 34, 40);
  c.overlayText = QColor(90, 98, 110);
  c.sketchFree = QColor(0, 110, 220);
  c.sketchFixed = QColor(25, 25, 25);
  c.sketchLabel = QColor(20, 20, 20);
  c.sketchGlyph = QColor(110, 115, 125);
  c.sketchFinished = QColor(40, 70, 120);
  c.navBackground = QColor(245, 247, 250, 235);
  c.navBorder = QColor(0, 0, 0, 40);
  c.errorBackground = QColor(240, 180, 175);
  return c;
}

QString darkStyleSheet(const Theme::Colors& c) {
  auto hex = [](const QColor& q) { return q.name(QColor::HexRgb); };
  QString s = QStringLiteral(R"(
QMainWindow, QDialog { background: %WINDOW%; }
QToolBar { background: %PANEL%; border: none; spacing: 2px; padding: 2px; }
QToolBar QToolButton { color: %TEXT%; }
QDockWidget { color: %MUTED%; titlebar-close-icon: none; }
QDockWidget::title { background: %BASE%; padding: 5px 8px; text-align: left; }
QTreeWidget, QListWidget { background: %WINDOW%; border: none; color: %TEXT%; }
QTreeWidget::item:selected, QListWidget::item:selected { background: %HIGHLIGHT%; color: white; }
QTreeWidget::indicator { width: 11px; height: 11px; border-radius: 2px; }
QTreeWidget::indicator:unchecked { border: 1px solid #8b929d; background: %BASE%; }
QTreeWidget::indicator:checked { border: 1px solid #6fb0ff; background: %HIGHLIGHT%; }
QTabWidget#ribbon::pane { border: none; background: %PANEL%; }
QTabWidget#ribbon > QTabBar::tab { background: transparent; color: %MUTED%; padding: 3px 16px; border: none;
                                   border-bottom: 2px solid transparent; }
QTabWidget#ribbon > QTabBar::tab:selected { color: white; border-bottom: 2px solid %HIGHLIGHT%; }
QTabWidget#ribbon > QTabBar::tab:hover { color: white; }
QTabWidget#ribbon > QTabBar::tab:disabled { color: #6b727d; }
QToolButton { border: 1px solid transparent; border-radius: 3px; padding: 2px; }
QToolButton:hover { background: #4a5260; border-color: #566070; }
QToolButton:checked, QToolButton:pressed { background: #2c5a92; border-color: #3d7cc4; }
QStatusBar { background: %BASE%; color: %MUTED%; }
QStatusBar QLabel { color: %MUTED%; }
QMenu { background: %BASE%; border: 1px solid %BORDER%; color: %TEXT%; padding: 4px; }
QMenu::item { padding: 4px 22px 4px 22px; border-radius: 3px; }
QMenu::item:selected { background: %HIGHLIGHT%; color: white; }
QMenu::item:disabled { color: #6b727d; }
QMenu::separator { height: 1px; background: #474e59; margin: 4px 6px; }
QLineEdit, QComboBox, QDoubleSpinBox, QSpinBox { background: %BASE%; border: 1px solid #4b525e; border-radius: 3px;
                                                 padding: 2px 5px; color: %TEXT%; selection-background-color: %HIGHLIGHT%; }
QLineEdit:focus, QComboBox:focus, QDoubleSpinBox:focus, QSpinBox:focus { border-color: %HIGHLIGHT%; }
QComboBox#workspace { background: %WINDOW%; border: 1px solid #4b525e; padding: 6px 10px; font-weight: bold; }
QComboBox QAbstractItemView { background: %BASE%; color: %TEXT%; selection-background-color: %HIGHLIGHT%; }
QPushButton { background: #454c58; border: 1px solid #58606d; border-radius: 3px; padding: 4px 14px; color: %TEXT%; }
QPushButton:hover { background: #505866; }
QPushButton:pressed { background: #3a414c; }
QPushButton#finishSketch { background: #2b6e47; border-color: #3c8c5d; color: white; font-weight: bold; }
QPushButton#finishSketch:hover { background: #33804f; }
QCheckBox, QLabel { color: %TEXT%; }
QCheckBox::indicator:unchecked { width: 12px; height: 12px; border: 1px solid #8a93a0; border-radius: 2px; background: transparent; }
QCheckBox::indicator:unchecked:disabled { border: 1px solid #5b6472; }
QDialog[panel="true"] { background: %BASE%; border: 1px solid #4b525e; border-radius: 4px; }
QLabel#panelTitle { color: %MUTED%; font-weight: bold; padding: 2px 0 6px 0; border-bottom: 1px solid #4b525e; }
QToolTip { background: #23272d; color: #e6e9ee; border: 1px solid #4b525e; padding: 4px; }
QScrollBar:horizontal, QScrollBar:vertical { background: %WINDOW%; border: none; height: 10px; width: 10px; }
QScrollBar::handle { background: #59616e; border-radius: 4px; min-width: 24px; min-height: 24px; }
QScrollBar::add-line, QScrollBar::sub-line { width: 0; height: 0; }
QFrame[frameShape="5"] { color: #4b525e; }
)");
  s.replace(QStringLiteral("%WINDOW%"), hex(c.window));
  s.replace(QStringLiteral("%PANEL%"), hex(c.panel));
  s.replace(QStringLiteral("%BASE%"), hex(c.base));
  s.replace(QStringLiteral("%TEXT%"), hex(c.text));
  s.replace(QStringLiteral("%MUTED%"), hex(c.mutedText));
  s.replace(QStringLiteral("%BORDER%"), hex(c.border));
  s.replace(QStringLiteral("%HIGHLIGHT%"), hex(c.highlight));
  return s;
}

QString lightStyleSheet(const Theme::Colors& c) {
  return QStringLiteral(R"(
QTabWidget#ribbon::pane { border: none; }
QTabWidget#ribbon > QTabBar::tab { padding: 3px 16px; border: none; border-bottom: 2px solid transparent; background: transparent; }
QTabWidget#ribbon > QTabBar::tab:selected { border-bottom: 2px solid %1; }
QPushButton#finishSketch { background: #2e8b57; color: white; font-weight: bold; padding: 4px 14px; border-radius: 3px; }
QDialog[panel="true"] { background: palette(window); border: 1px solid palette(mid); border-radius: 4px; }
QLabel#panelTitle { font-weight: bold; padding: 2px 0 6px 0; }
)").arg(c.highlight.name());
}

QPalette darkPalette(const Theme::Colors& c) {
  QPalette p;
  p.setColor(QPalette::Window, c.window);
  p.setColor(QPalette::WindowText, c.text);
  p.setColor(QPalette::Base, c.base);
  p.setColor(QPalette::AlternateBase, c.window);
  p.setColor(QPalette::Text, c.text);
  p.setColor(QPalette::Button, QColor(0x45, 0x4c, 0x58));
  p.setColor(QPalette::ButtonText, c.text);
  p.setColor(QPalette::BrightText, Qt::white);
  p.setColor(QPalette::Highlight, c.highlight);
  p.setColor(QPalette::HighlightedText, Qt::white);
  p.setColor(QPalette::ToolTipBase, QColor(0x23, 0x27, 0x2d));
  p.setColor(QPalette::ToolTipText, QColor(0xe6, 0xe9, 0xee));
  p.setColor(QPalette::PlaceholderText, QColor(0x85, 0x8c, 0x97));
  p.setColor(QPalette::Link, QColor(0x6a, 0xa8, 0xf0));
  p.setColor(QPalette::Light, QColor(0x55, 0x5c, 0x68));
  p.setColor(QPalette::Midlight, QColor(0x4a, 0x51, 0x5c));
  p.setColor(QPalette::Mid, QColor(0x30, 0x35, 0x3d));
  p.setColor(QPalette::Dark, QColor(0x25, 0x29, 0x2f));
  p.setColor(QPalette::Shadow, QColor(0x18, 0x1b, 0x1f));
  for (auto role : {QPalette::WindowText, QPalette::Text, QPalette::ButtonText})
    p.setColor(QPalette::Disabled, role, QColor(0x6f, 0x76, 0x80));
  return p;
}

} // namespace

Theme& Theme::instance() {
  static Theme* t = new Theme;
  return *t;
}

Theme::Mode Theme::saved() {
  const QByteArray env = qgetenv("TSR_THEME").toLower();
  if (env == "light") return Mode::Light;
  if (env == "dark") return Mode::Dark;
  QSettings s;
  return s.value(QStringLiteral("ui/theme"), QStringLiteral("dark")).toString() == QLatin1String("light") ? Mode::Light
                                                                                                         : Mode::Dark;
}

void Theme::apply(Mode m, bool save) {
  mode_ = m;
  colors_ = m == Mode::Dark ? darkColors() : lightColors();
  setIconTheme(colors_);
  if (auto* app = qobject_cast<QApplication*>(QCoreApplication::instance())) {
    if (!styled_) {
      // One consistent widget style on every desktop, so the palette below
      // is honoured exactly.
      if (QStyle* fusion = QStyleFactory::create(QStringLiteral("Fusion"))) app->setStyle(fusion);
      styled_ = true;
    }
    app->setPalette(m == Mode::Dark ? darkPalette(colors_) : app->style()->standardPalette());
    app->setStyleSheet(m == Mode::Dark ? darkStyleSheet(colors_) : lightStyleSheet(colors_));
  }
  if (save) {
    QSettings s;
    s.setValue(QStringLiteral("ui/theme"), m == Mode::Dark ? QStringLiteral("dark") : QStringLiteral("light"));
  }
  emit changed();
}

} // namespace tsr::app
