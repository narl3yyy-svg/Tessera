#pragma once
#include "tsr/api/PythonHost.h"
#include "tsr/doc/Session.h"

#include <QDialog>
#include <QMainWindow>
#include <QPointer>

#include <TopAbs_ShapeEnum.hxx>
#include <TopoDS_Shape.hxx>
#include <gp_Ax3.hxx>
#include <gp_Pln.hxx>

#include "tsr/core/Units.h"

#include <functional>

#include <map>
#include <optional>
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
class ParametersDialog;
class SketchEditor;
class SketchPalette;
class MarkingMenu;
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

  // Modify > Change Parameters (non-modal; reuses an open one).
  ParametersDialog* showParameters();
  SketchEditor* sketchEditor() const { return editor_; }
  SketchPalette* sketchPalette() const;
  // The right-click marking menu (also for tests).
  MarkingMenu* openMarkingMenu(const QPoint& globalPos);
  // Section Analysis (tests): the panel, and picking a plane as a click would.
  QDialog* sectionPanel() const { return sectionPanel_; }
  void openSectionAnalysis() { openSection(); }
  bool sectionActive() const { return section_.active; }
  double sectionOffset() const { return section_.offset; }

  QTabWidget* ribbon() const { return ribbon_; }
  QTreeWidget* browser() const { return browser_; }
  QListWidget* timeline() const { return timeline_; }
  // V: shows or hides the selected bodies, else the Browser's current item.
  void toggleSelectedVisibility();
  Viewport* viewport() const { return viewport_; }

signals:
  void combEdgesChanged();
  void sectionPlanePicked(const QString& spec, const QString& label);
  void sectionArrowMoved(double value);

protected:
  void closeEvent(QCloseEvent* e) override;
  bool eventFilter(QObject* watched, QEvent* e) override;

private:
  void buildAppBar();
  void buildRibbon();
  QWidget* ribbonPage(QWidget* page);   // wraps a ribbon tab so it scrolls when the window is narrow
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
  void driveJoints();
public:
  // Inspect > Zebra / Draft / Curvature Map / Curvature Comb (0..3).
  QDialog* openAnalysis(int kind);
  QDialog* analysisPanel() const { return analysisPanel_; }
private:
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
  // In-canvas drag arrow for the open panel (MainWindowArrow.cpp).
  void updateDragArrow();
  void attachArrowCompleters();
  void showBrowserMenu(const QPoint& pos);
  std::optional<gp_Pnt> patternCentre();
  std::map<QString, gp_Pnt> patternCentres_;   // per feature name, while a pattern is open
  void onDragArrow(double value);
  QString arrowInput_;
  QString arrowInput2_;   // the second arrow's input (Two Sides extrude)
  std::vector<std::string> bodiesBeforeCommand_;   // real bodies when the open panel started
  std::vector<TopoDS_Shape> pickedFaces() const;   // the Real input the arrow drives, empty when none
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
  QPointer<SketchPalette> palette_;
  std::vector<std::pair<int, QAbstractButton*>> toolButtons_;
  QAbstractButton* constructionButton_ = nullptr;
  std::vector<QShortcut*> sketchShortcuts_;
  std::map<std::string, bool> sketchVisibility_;   // user overrides from the browser
  std::vector<TopoDS_Shape> pickedEdges_;          // shown highlighted while picking
  std::map<std::string, bool> constructionVisibility_;
  QString lastCommand_;

  struct UiCommand {
    std::string tab, panel, id, name, tooltip, icon, shortcut;
    bool enabled = true;
    std::function<void()> run;
  };
  std::vector<UiCommand> uiCommands_;
  QPointer<QDialog> measure_;
  QPointer<QDialog> analysisPanel_;
  std::vector<TopoDS_Shape> combEdges_;
  double combScale_ = 1.0;
  bool combPicking_ = false;
  QPointer<ParametersDialog> parameters_;
  QLabel* measureLabel_ = nullptr;
  std::vector<TopoDS_Shape> measurePicks_;
  struct SectionState {
    bool active = false;
    bool visible = true;
    QString plane = QStringLiteral("XZ");   // origin plane, construction plane or custom:... (a picked face)
    double offset = 0;                      // along the plane's normal
    double angle = 0;                       // turned about the plane's X axis
    bool flip = false;
  } section_;
  QPointer<QDialog> sectionPanel_;         // open Section Analysis panel
  bool sectionPicking_ = false;            // waiting for a plane or face click
  void updateSectionArrow();
  gp_Ax3 sectionFrame() const;
  bool comShown_ = false;
  QLabel* unitsLabel_ = nullptr;
};

} // namespace tsr::app
