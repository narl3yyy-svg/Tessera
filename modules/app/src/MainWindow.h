#pragma once
#include "tsr/api/PythonHost.h"
#include "tsr/doc/Session.h"

#include <QMainWindow>

class QTabWidget;
class QTreeWidget;
class QAction;

namespace tsr::app {

class CommandDialog;

class MainWindow : public QMainWindow {
  Q_OBJECT
public:
  MainWindow(doc::Session& session, api::PythonHost& python, QWidget* parent = nullptr);
  ~MainWindow() override;

  // Opens the generated dialog for a command (non-modal). Returns it so
  // scripted GUI tests can drive it; nullptr for an unknown id.
  CommandDialog* startCommand(const QString& commandId);

  QTabWidget* ribbon() const { return ribbon_; }
  QTreeWidget* browser() const { return browser_; }

protected:
  void closeEvent(QCloseEvent* e) override;

private:
  void buildMenus();
  void buildRibbon();
  void refresh();
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
  QAction* undo_ = nullptr;
  QAction* redo_ = nullptr;
};

} // namespace tsr::app
