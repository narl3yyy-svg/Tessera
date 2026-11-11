#pragma once
#include "tsr/api/PythonHost.h"
#include "tsr/doc/Session.h"

#include <QMainWindow>
#include <QPointer>

class QTabWidget;
class QTreeWidget;
class QTreeWidgetItem;
class QListWidget;
class QAction;
class QLineEdit;
class QWidget;

namespace tsr::app {

class CommandDialog;
class Viewport;

// Layout (familiar to users of mainstream parametric CAD):
//   top     application bar (file, save, undo/redo, command search) and the
//           ribbon: workspace selector, tabs, panels of commands
//   left    browser: document settings, origin, bodies (visibility), parameters
//   centre  3D viewport with ViewCube and a navigation bar
//   bottom  timeline of features; double-click to edit, right-click for more
class MainWindow : public QMainWindow {
  Q_OBJECT
public:
  MainWindow(doc::Session& session, api::PythonHost& python, QWidget* parent = nullptr);
  ~MainWindow() override;

  // Opens the generated dialog for a command (non-modal). Returns it so
  // scripted GUI tests can drive it; nullptr if it cannot start.
  CommandDialog* startCommand(const QString& commandId);
  // Opens the dialog to edit an existing feature from the timeline.
  CommandDialog* editFeature(int featureId);

  QTabWidget* ribbon() const { return ribbon_; }
  QTreeWidget* browser() const { return browser_; }
  QListWidget* timeline() const { return timeline_; }
  Viewport* viewport() const { return viewport_; }

protected:
  void closeEvent(QCloseEvent* e) override;
  bool eventFilter(QObject* watched, QEvent* e) override;

private:
  void buildAppBar();
  void buildRibbon();
  void buildNavBar();
  void buildShortcuts();
  CommandDialog* showDialog(std::unique_ptr<CommandSession> cmd);
  void placeDialog(QWidget* dlg);
  void refresh();
  void refreshBrowser(const QString& docName);
  void refreshTimeline();
  void showContextMenu(const QPoint& globalPos);
  void showTimelineMenu(const QPoint& pos);
  void focusSearch();
  bool maybeSave();
  bool saveAs();
  bool saveTo(const QString& path);
  void openFile();
  void runScript();

  doc::Session& session_;
  api::PythonHost& python_;
  int listener_ = 0;
  QTabWidget* ribbon_ = nullptr;
  QTreeWidget* browser_ = nullptr;
  QListWidget* timeline_ = nullptr;
  Viewport* viewport_ = nullptr;
  QWidget* navBar_ = nullptr;
  QLineEdit* search_ = nullptr;
  QAction* undo_ = nullptr;
  QAction* redo_ = nullptr;
  QPointer<CommandDialog> active_;
  QString lastCommand_;
};

} // namespace tsr::app
