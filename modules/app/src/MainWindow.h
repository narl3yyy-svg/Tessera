#pragma once
#include "tsr/api/PythonHost.h"
#include "tsr/doc/Session.h"

#include <QMainWindow>
#include <QPointer>

#include <TopAbs_ShapeEnum.hxx>
#include <TopoDS_Shape.hxx>
#include <gp_Pln.hxx>

#include "tsr/core/Units.h"

#include <functional>

#include <map>
#include <vector>

class QTabWidget;
class QTreeWidget;
class QTreeWidgetItem;
class QListWidget;
class QAction;
class QLineEdit;
class QWidget;
class QShortcut;
class QAbstractButton;
class QDialog;
class QLabel;

namespace tsr::app {

class CommandDialog;
class SketchEditor;
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

  // Sketch mode. beginSketch() asks for a plane in the canvas; startSketch()
  // starts on a given plane spec ("XY", "custom:..."); editSketch() reopens a
  // sketch feature. Finish commits one undo step.
  void beginSketch();
  SketchEditor* startSketch(const QString& planeSpec);
  SketchEditor* editSketch(int featureId);
  bool finishSketch();
  void cancelSketch();
  SketchEditor* sketchEditor() const { return editor_; }

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
  void styleNavBar();
  // Tools (MainWindowTools.cpp)
  void buildUiCommands();
  void setSelectionFilter(const std::vector<TopAbs_ShapeEnum>& types);
  void chooseUnits(const QPoint& globalPos);
  void exportDesign();
  void print3d();
  void insertFile();
  void captureImage();
  void applyPreferences();
  void showPreferences();
  void gridSettings();
  void openMeasure();
  void measurePick(const TopoDS_Shape& s);
  void updateMeasure();
  void openSection();
  void applySection();
  gp_Pln sectionPlane() const;
  void showCenterOfMass();
  void checkInterference();
  Unit lengthUnit() const;
  QString formatLength(double cm) const;
  void enterSketchMode();
  void exitSketchMode();
  QWidget* buildSketchTab();
  void syncSketchTools();
  void updateProfilePicking();
  void onProfileClicked(const QString& sketch, int index);
  void onEdgeClicked(const QString& body, const TopoDS_Shape& edge);
  void updateEdgePicking();
  bool sketchVisible(const std::string& name) const;
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
  QPointer<SketchEditor> editor_;
  QWidget* sketchTab_ = nullptr;
  std::vector<std::pair<int, QAbstractButton*>> toolButtons_;
  QAbstractButton* constructionButton_ = nullptr;
  std::vector<QShortcut*> sketchShortcuts_;
  std::map<std::string, bool> sketchVisibility_;   // user overrides from the browser
  std::vector<TopoDS_Shape> pickedEdges_;          // shown highlighted while picking
  QString lastCommand_;

  struct UiCommand {
    std::string tab, panel, id, name, tooltip, icon, shortcut;
    bool enabled = true;
    std::function<void()> run;
  };
  std::vector<UiCommand> uiCommands_;
  QPointer<QDialog> measure_;
  QLabel* measureLabel_ = nullptr;
  std::vector<TopoDS_Shape> measurePicks_;
  struct SectionState {
    bool active = false;
    bool visible = true;
    QString plane = QStringLiteral("XZ");
    double offset = 0;
    bool flip = false;
  } section_;
  bool comShown_ = false;
  QLabel* unitsLabel_ = nullptr;
};

} // namespace tsr::app
