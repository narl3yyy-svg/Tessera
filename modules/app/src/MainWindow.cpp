#include "ProfileCache.h"
#include "MainWindow.h"
#include <QInputDialog>
#include <QKeyEvent>
#include "tsr/sketch/Sketch.h"
#include <cstring>
#include "CommandDialog.h"
#include "MarkingMenu.h"
#include "ParametersDialog.h"
#include "SketchPalette.h"

#include <QScrollArea>
#include <QScrollBar>
#include <QWheelEvent>
#include "Icons.h"
#include "Theme.h"
#include "SketchEditor.h"
#include "Viewport.h"

#include "tsr/doc/DocCommands.h"

#include "tsr/kernel/Kernel.h"

#include <QActionGroup>
#include <QCursor>
#include <QSettings>
#include <BRep_Builder.hxx>
#include <TopoDS_Compound.hxx>
#include <TopExp_Explorer.hxx>
#include <QApplication>
#include <QGuiApplication>
#include <QMouseEvent>
#include <QFrame>
#include <QCloseEvent>
#include <QComboBox>
#include <QCompleter>
#include <QDockWidget>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QShortcut>
#include <QStatusBar>
#include <QTabWidget>
#include <QTimer>
#include <QToolBar>
#include <QToolButton>
#include <QTreeWidget>
#include <QVBoxLayout>

#include <algorithm>
#include <cmath>
#include <map>
#include <vector>

namespace tsr::app {

namespace {
const QString kFilter = QStringLiteral("Tessera designs (*.tsr)");
constexpr int kFeatureIdRole = Qt::UserRole + 1;
constexpr int kBodyRole = Qt::UserRole + 2;
constexpr int kSketchRole = Qt::UserRole + 3;
constexpr int kUnitsRole = Qt::UserRole + 4;
constexpr int kAnalysisRole = Qt::UserRole + 5;
constexpr int kParametersRole = Qt::UserRole + 6;
constexpr int kPlaneRole = Qt::UserRole + 7;
constexpr int kOriginRole = Qt::UserRole + 8;   // an origin plane: its spec ("XY")
constexpr int kSketchLockedRole = Qt::UserRole + 9;   // a fully defined sketch
constexpr int kMarkerRole = Qt::UserRole + 10;        // the timeline's history marker
constexpr int kViewRole = Qt::UserRole + 11;          // a named view: its name ("TOP" ... or the design's)
constexpr int kViewsFolderRole = Qt::UserRole + 12;   // the Named Views folder

QString qs(const std::string& s) { return QString::fromStdString(s); }

QString commandIcon(const doc::Session& s, const std::string& commandId) {
  const Command* c = s.commands().find(commandId);
  return c ? qs(c->def().icon) : QStringLiteral("?");
}

QToolButton* flatButton(const QString& iconName, const QString& tip) {
  auto* b = new QToolButton;
  if (!iconName.isEmpty()) setIcon(b, iconName);
  b->setToolTip(tip);
  b->setAutoRaise(true);
  b->setIconSize(QSize(22, 22));
  return b;
}
} // namespace

MainWindow::MainWindow(doc::Session& session, api::PythonHost& python, QWidget* parent)
    : QMainWindow(parent), session_(session), python_(python) {
  setObjectName(QStringLiteral("MainWindow"));
  resize(1440, 900);
  setDockOptions(QMainWindow::AnimatedDocks | QMainWindow::AllowNestedDocks);

  buildUiCommands();
  buildAppBar();
  addToolBarBreak();
  buildRibbon();

  // Browser.
  browser_ = new QTreeWidget;
  browser_->setObjectName(QStringLiteral("browser"));
  browser_->setHeaderHidden(true);
  browser_->setAccessibleName(tr("Browser"));
  // Renaming in place, as in the familiar Browser: click a selected name again, or F2.
  browser_->setEditTriggers(QAbstractItemView::SelectedClicked | QAbstractItemView::EditKeyPressed);
  connect(browser_, &QTreeWidget::itemChanged, this, [this](QTreeWidgetItem* item, int) {
    {
      const QString text = item->text(0).trimmed();
      if (const QString view = item->data(0, kViewRole).toString(); !view.isEmpty()) {
        if (view != text)
          QTimer::singleShot(0, this, [this, view, text] {
            const std::string err = session_.renameNamedView(view.toStdString(), text.toStdString());
            if (!err.empty()) statusBar()->showMessage(qs(err), 5000);
            refresh();
          });
        return;
      }
      const QString body = item->data(0, kBodyRole).toString();
      const QString sketch = item->data(0, kSketchRole).toString();
      // Renamed: done after this signal returns, because the rename refreshes
      // the Browser, which deletes the item being edited.
      const auto b = body.isEmpty() ? std::nullopt : session_.document().body(body.toStdString());
      const bool renameBody = b && qs(b->display) != text;
      const bool renameSketch = body.isEmpty() && !sketch.isEmpty() && sketch != text;
      if (renameBody || renameSketch) {
        QTimer::singleShot(0, this, [this, body, sketch, text, renameBody] {
          const std::string err = renameBody ? session_.renameBody(body.toStdString(), text.toStdString())
                                             : session_.renameSketch(sketch.toStdString(), text.toStdString());
          if (!err.empty()) statusBar()->showMessage(qs(err), 5000);
          refresh();
        });
        return;
      }
    }
    const QString body = item->data(0, kBodyRole).toString();
    if (!body.isEmpty()) viewport_->setBodyVisible(body, item->checkState(0) == Qt::Checked);
    const QString sketch = item->data(0, kSketchRole).toString();
    if (!sketch.isEmpty()) {
      sketchVisibility_[sketch.toStdString()] = item->checkState(0) == Qt::Checked;
      QTimer::singleShot(0, this, [this] { refresh(); });
    }
    if (item->data(0, kAnalysisRole).toBool()) {
      section_.visible = item->checkState(0) == Qt::Checked;
      QTimer::singleShot(0, this, [this] { applySection(); });
    }
    const QString plane = item->data(0, kPlaneRole).toString();
    if (!plane.isEmpty()) {
      constructionVisibility_[plane.toStdString()] = item->checkState(0) == Qt::Checked;
      QTimer::singleShot(0, this, [this] { refresh(); });
    }
  });
  connect(browser_, &QTreeWidget::itemClicked, this, [this](QTreeWidgetItem* item, int) {
    if (item->data(0, kUnitsRole).toBool())
      QTimer::singleShot(0, this, [this, item] { chooseUnits(QCursor::pos()); });
  });
  connect(browser_, &QTreeWidget::itemDoubleClicked, this, [this](QTreeWidgetItem* item, int) {
    if (item->data(0, kAnalysisRole).toBool()) {
      QTimer::singleShot(0, this, [this] { openSection(); });
      return;
    }
    if (item->data(0, kParametersRole).toBool()) {
      QTimer::singleShot(0, this, [this] { showParameters(); });
      return;
    }
    if (const QString view = item->data(0, kViewRole).toString(); !view.isEmpty()) {
      goToNamedView(view);
      return;
    }
    const QString sketch = item->data(0, kSketchRole).toString();
    if (sketch.isEmpty()) return;
    for (const auto& f : session_.document().features())
      if (f.commandId == doc::kCmdSketch && f.name == sketch.toStdString()) {
        editSketch(f.id);
        return;
      }
  });
  connect(browser_, &QTreeWidget::itemExpanded, this, [this](QTreeWidgetItem* it) {
    if (it->data(0, kViewsFolderRole).toBool()) namedViewsOpen_ = true;
  });
  connect(browser_, &QTreeWidget::itemCollapsed, this, [this](QTreeWidgetItem* it) {
    if (it->data(0, kViewsFolderRole).toBool()) namedViewsOpen_ = false;
  });
  browser_->setContextMenuPolicy(Qt::CustomContextMenu);
  connect(browser_, &QTreeWidget::customContextMenuRequested, this, &MainWindow::showBrowserMenu);
  auto* browserDock = new QDockWidget(tr("BROWSER"));
  browserDock->setObjectName(QStringLiteral("browserDock"));
  browserDock->setWidget(browser_);
  browserDock->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
  addDockWidget(Qt::LeftDockWidgetArea, browserDock);

  // Timeline.
  timeline_ = new QListWidget;
  timeline_->setObjectName(QStringLiteral("timeline"));
  // Left to right, icons only; features and the history marker can be
  // dragged to reorder or roll back, as in the familiar timeline.
  timeline_->setViewMode(QListView::ListMode);
  timeline_->setFlow(QListView::LeftToRight);
  timeline_->setWrapping(false);
  timeline_->setIconSize(QSize(28, 28));
  timeline_->setSpacing(3);
  // Dragging is done here (see timelineDrag): a blue bar shows where the
  // feature or the marker goes, and the drop is applied as one undo step.
  timeline_->setDragDropMode(QAbstractItemView::NoDragDrop);
  timeline_->viewport()->installEventFilter(this);
  timelineDropBar_ = new QFrame(timeline_->viewport());
  timelineDropBar_->setStyleSheet(QStringLiteral("background:#2f8fe8;"));
  timelineDropBar_->hide();
  timeline_->setFixedHeight(52);
  timeline_->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  timeline_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  timeline_->setContextMenuPolicy(Qt::CustomContextMenu);
  timeline_->setAccessibleName(tr("Timeline"));
  connect(timeline_, &QListWidget::itemDoubleClicked, this,
          [this](QListWidgetItem* it) {
            if (!it->data(kMarkerRole).toBool()) editFeature(it->data(kFeatureIdRole).toInt());
          });
  connect(timeline_, &QListWidget::customContextMenuRequested, this, &MainWindow::showTimelineMenu);
  // While a pattern wants features, a click on the timeline picks one.
  connect(timeline_, &QListWidget::itemClicked, this, [this](QListWidgetItem* it) {
    if (!active_ || !active_->wantsFeatures()) return;
    if (const auto f = session_.document().feature(it->data(kFeatureIdRole).toInt())) {
      active_->toggleFeature(qs(f->name));
      updateDragArrow();
    }
  });
  // Playback, as the familiar timeline: to the start, a step back, a step
  // forward, to the end (they move the history marker).
  auto* timelineBox = new QWidget;
  auto* timelineRow = new QHBoxLayout(timelineBox);
  timelineRow->setContentsMargins(0, 0, 0, 0);
  timelineRow->setSpacing(1);
  const std::pair<const char*, const char*> steps[] = {{"timeline.start", "\u23EE"}, {"timeline.back", "\u23F4"},
                                                       {"timeline.forward", "\u23F5"}, {"timeline.end", "\u23ED"}};
  const char* tips[] = {QT_TR_NOOP("Go to the start"), QT_TR_NOOP("Step back"), QT_TR_NOOP("Step forward"),
                        QT_TR_NOOP("Go to the end")};
  for (int i = 0; i < 4; ++i) {
    auto* b = new QToolButton;
    b->setObjectName(QString::fromLatin1(steps[i].first));
    b->setText(QString::fromUtf8(steps[i].second));
    b->setToolTip(tr(tips[i]));
    b->setAutoRaise(true);
    b->setFixedSize(24, 40);
    connect(b, &QToolButton::clicked, this, [this, i] {
      if (editor_ || active_) return;
      const int total = static_cast<int>(session_.document().features().size());
      const int now = session_.document().historyMarker();
      const int to = i == 0 ? 0 : i == 1 ? std::max(0, now - 1) : i == 2 ? std::min(total, now + 1) : total;
      if (to == now) return;
      if (auto err = session_.rollHistory(to); !err.empty()) statusBar()->showMessage(qs(err), 5000);
    });
    timelineRow->addWidget(b);
  }
  timelineRow->addWidget(timeline_, 1);
  auto* timelineDock = new QDockWidget(tr("TIMELINE"));
  timelineDock->setObjectName(QStringLiteral("timelineDock"));
  timelineDock->setWidget(timelineBox);
  timelineDock->setFeatures(QDockWidget::DockWidgetMovable);
  addDockWidget(Qt::BottomDockWidgetArea, timelineDock);

  // Canvas.
  viewport_ = new Viewport;
  setCentralWidget(viewport_);
  connect(viewport_, &Viewport::contextMenuRequested, this, &MainWindow::showContextMenu);
  connect(viewport_, &Viewport::profileClicked, this, &MainWindow::onProfileClicked);
  connect(viewport_, &Viewport::dragArrowMoved, this, &MainWindow::onDragArrow);
  connect(viewport_, &Viewport::dragArrowTyped, this, [this](const QString& text) {
    if (sectionPanel_ && !sectionPicking_) {
      try {
        emit sectionArrowMoved(session_.document().evaluate(text.toStdString(), Unit::Millimeter));
      } catch (const std::exception& e) {
        statusBar()->showMessage(QString::fromUtf8(e.what()), 4000);
      }
    } else if (active_ && !arrowInput_.isEmpty()) {
      active_->setInputForTest(arrowInput_, text);
    }
    viewport_->setFocus();
  });
  // The second arrow (Two Sides extrude) drives its own input.
  connect(viewport_, &Viewport::secondArrowMoved, this, [this](double value) {
    if (!active_ || arrowInput2_.isEmpty()) return;
    if (arrowInput2_ == QLatin1String("offset")) {   // thread offset: from the face's end
      active_->setRealInput(arrowInput2_, std::max(value, 0.0));
      return;
    }
    if (std::abs(value) < 1e-9) return;
    active_->setRealInput(arrowInput2_, value);
  });
  connect(viewport_, &Viewport::secondArrowTyped, this, [this](const QString& text) {
    if (active_ && !arrowInput2_.isEmpty()) active_->setInputForTest(arrowInput2_, text);
    viewport_->setFocus();
  });
  connect(viewport_, &Viewport::subShapeClicked, this, [this](const QString& body, const TopoDS_Shape& shape) {
    (void)body;
    if (measure_) {
      measurePick(shape);
    } else if (combPicking_ && shape.ShapeType() == TopAbs_EDGE) {
      // Curvature Comb: clicking an edge adds it (or removes it again).
      auto it = std::find_if(combEdges_.begin(), combEdges_.end(), [&](const TopoDS_Shape& e) { return e.IsSame(shape); });
      if (it != combEdges_.end()) combEdges_.erase(it);
      else combEdges_.push_back(shape);
      emit combEdgesChanged();
    } else {
      onEdgeClicked(body, shape);
    }
  });
  connect(viewport_, &Viewport::planePicked, this, [this](const QString& spec, const QString& label) {
    if (sectionPanel_ && sectionPicking_) {
      emit sectionPlanePicked(spec, label);
      return;
    }
    if (active_ && active_->planeInputShown()) {
      active_->pickPlane(spec, label);
      return;
    }
    viewport_->setPlanePicking(false);
    if (startSketch(spec)) statusBar()->showMessage(tr("Sketching on %1.").arg(label), 4000);
  });
  connect(viewport_, &Viewport::statusMessage, this, [this](const QString& m) { statusBar()->showMessage(m, 5000); });
  connect(viewport_, &Viewport::bodyClicked, this, [this](const QString& name) {
    if (measure_) {
      measurePick(viewport_->bodyShape(name));
      viewport_->clearSelection();
      return;
    }
    if (active_ && active_->hasBodiesInput() &&
        (!active_->hasBodyInput() || (!active_->currentBody().isEmpty() && active_->currentBody() != name))) {
      // Combine: further bodies toggle in the tool list.
      QStringList tools = active_->currentTools().split(QLatin1Char(';'), Qt::SkipEmptyParts);
      if (tools.contains(name)) tools.removeAll(name);
      else tools << name;
      active_->setTools(tools.join(QLatin1Char(';')));
      viewport_->clearSelection();
      return;
    }
    if (active_ && active_->pickBody(name)) viewport_->clearSelection();
  });
  connect(viewport_, &Viewport::selectionChanged, this, [this] {
    // A click elsewhere (without Shift / Ctrl) drops the profiles picked before.
    if (!active_ && !editor_ && !preProfiles_.isEmpty() &&
        !(QGuiApplication::keyboardModifiers() & (Qt::ShiftModifier | Qt::ControlModifier))) {
      preSketch_.clear();
      preProfiles_.clear();
      updateProfilePicking();
    }
    QStringList sel = viewport_->selectedBodies();
    sel.removeDuplicates();
    if (sel.isEmpty()) {
      statusBar()->clearMessage();
      return;
    }
    // Faces / edges picked: say how many, and on which bodies.
    int faces = 0, edges = 0, vertices = 0;
    for (const auto& [body, shape] : viewport_->selectedSubShapes()) {
      if (shape.ShapeType() == TopAbs_FACE) ++faces;
      else if (shape.ShapeType() == TopAbs_EDGE) ++edges;
      else ++vertices;
    }
    QStringList what;
    if (faces) what << tr("%n face(s)", nullptr, faces);
    if (edges) what << tr("%n edge(s)", nullptr, edges);
    if (vertices) what << tr("%n vertex(es)", nullptr, vertices);
    const QString bodies = sel.join(QStringLiteral(", "));
    statusBar()->showMessage(what.isEmpty() ? tr("Selected: %1").arg(bodies)
                                            : tr("Selected: %1 (%2)").arg(what.join(QStringLiteral(", ")), bodies));
  });
  if (!viewport_->unavailableReason().isEmpty()) statusBar()->showMessage(viewport_->unavailableReason());
  buildNavBar();
  buildShortcuts();

  unitsLabel_ = new QLabel;
  unitsLabel_->setContentsMargins(8, 0, 8, 0);
  statusBar()->addPermanentWidget(unitsLabel_);
  applyPreferences();

  connect(&Theme::instance(), &Theme::changed, this, [this] {
    retintIcons(this);
    styleNavBar();
    refresh();
  });
  listener_ = session_.addListener([this] { refresh(); });
  refresh();
}

MainWindow::~MainWindow() {
  session_.removeListener(listener_);
  // Panels and tools are children of the canvas; take them down before the
  // window's own members go, without their callbacks into this window.
  for (QObject* o : {static_cast<QObject*>(active_.data()), static_cast<QObject*>(measure_.data())})
    if (o) {
      disconnect(o, nullptr, this, nullptr);
      delete o;
    }
}

// ---------------------------------------------------------------------------
void MainWindow::buildAppBar() {
  menuBar()->hide(); // all of it lives in the application bar's File menu
  auto* bar = new QToolBar(tr("Application bar"));
  bar->setObjectName(QStringLiteral("appBar"));
  bar->setMovable(false);
  bar->setIconSize(QSize(20, 20));
  addToolBar(Qt::TopToolBarArea, bar);

  auto* fileMenu = new QMenu(this);
  fileMenu->addAction(QIcon::fromTheme(QStringLiteral("document-new")), tr("&New Design"), QKeySequence::New, this,
                      [this] {
                        if (!maybeSave()) return;
                        session_.newDocument();
                        const QString u = QSettings().value(QStringLiteral("doc/defaultUnits"), QStringLiteral("mm")).toString();
                        if (u != QLatin1String("mm")) (void)session_.run(doc::kCmdUnits, {{"unit", u.toStdString()}});
                      });
  fileMenu->addAction(QIcon::fromTheme(QStringLiteral("document-open")), tr("&Open…"), QKeySequence::Open, this,
                      [this] { openFile(); });
  auto* recent = fileMenu->addMenu(QIcon::fromTheme(QStringLiteral("document-open-recent")), tr("Open &Recent"));
  recent->setObjectName(QStringLiteral("file.recent"));
  connect(recent, &QMenu::aboutToShow, this, [this, recent] { fillRecentMenu(recent); });
  QAction* save = fileMenu->addAction(icon(QStringLiteral("save")), tr("&Save"),
                                      QKeySequence::Save, this, [this] {
                                        if (session_.path()) saveTo(qs(session_.path()->string()));
                                        else saveAs();
                                      });
  fileMenu->addAction(QIcon::fromTheme(QStringLiteral("document-save-as")), tr("Save &As…"), QKeySequence::SaveAs,
                      this, [this] { saveAs(); });
  setIcon(fileMenu->addAction(tr("Export…"), this, [this] { exportDesign(); }), QStringLiteral("export"));
  setIcon(fileMenu->addAction(tr("Insert Mesh / CAD File…"), this, [this] { insertFile(); }), QStringLiteral("insert"));
  fileMenu->addSeparator();
  setIcon(fileMenu->addAction(tr("3D Print…"), this, [this] { print3d(); }), QStringLiteral("print"));
  setIcon(fileMenu->addAction(tr("Capture Image…"), this, [this] { captureImage(); }), QStringLiteral("image"));
  fileMenu->addSeparator();
  setIcon(fileMenu->addAction(tr("Preferences…"), this, [this] { showPreferences(); }), QStringLiteral("preferences"));
  fileMenu->addSeparator();
  fileMenu->addAction(QIcon::fromTheme(QStringLiteral("text-x-python")), tr("&Run Script…"), this,
                      [this] { runScript(); });
  fileMenu->addSeparator();
  fileMenu->addAction(QIcon::fromTheme(QStringLiteral("application-exit")), tr("&Quit"), QKeySequence::Quit, this,
                      &QWidget::close);
  addActions(fileMenu->actions()); // keep shortcuts active while the menu is closed

  auto* fileButton = new QToolButton;
  fileButton->setText(tr("File"));
  setIcon(fileButton, QStringLiteral("file"));
  fileButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
  fileButton->setPopupMode(QToolButton::InstantPopup);
  fileButton->setMenu(fileMenu);
  bar->addWidget(fileButton);
  bar->addAction(save);

  undo_ = new QAction(tr("Undo"), this);
  setIcon(undo_, QStringLiteral("undo"));
  undo_->setShortcut(QKeySequence::Undo);
  connect(undo_, &QAction::triggered, this, [this] {
    if (editor_) editor_->undo();
    else session_.undo();
  });
  redo_ = new QAction(tr("Redo"), this);
  setIcon(redo_, QStringLiteral("redo"));
  redo_->setShortcuts({QKeySequence::Redo, QKeySequence(Qt::CTRL | Qt::Key_Y)});
  connect(redo_, &QAction::triggered, this, [this] {
    if (editor_) editor_->redo();
    else session_.redo();
  });
  bar->addAction(undo_);
  bar->addAction(redo_);

  auto* spacer = new QWidget;
  spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  bar->addWidget(spacer);

  // Command search (S): type part of a command name, press Enter.
  search_ = new QLineEdit;
  search_->setObjectName(QStringLiteral("commandSearch"));
  search_->setPlaceholderText(tr("Search commands  (S)"));
  search_->setClearButtonEnabled(true);
  search_->setFixedWidth(260);
  QStringList names;
  for (const Command* c : session_.commands().all()) names << qs(c->def().name);
  auto* completer = new QCompleter(names, search_);
  completer->setCaseSensitivity(Qt::CaseInsensitive);
  completer->setFilterMode(Qt::MatchContains);
  search_->setCompleter(completer);
  auto run = [this](const QString& text) {
    for (const Command* c : session_.commands().all())
      if (qs(c->def().name).compare(text, Qt::CaseInsensitive) == 0) {
        search_->clear();
        startCommand(qs(c->def().id));
        return;
      }
  };
  connect(completer, qOverload<const QString&>(&QCompleter::activated), this, run);
  connect(search_, &QLineEdit::returnPressed, this, [this, run] { run(search_->text()); });
  bar->addWidget(search_);
}

void MainWindow::buildRibbon() {
  ribbon_ = new QTabWidget;
  ribbon_->setObjectName(QStringLiteral("ribbon"));
  ribbon_->setDocumentMode(true);

  auto* workspace = new QComboBox;
  workspace->setObjectName(QStringLiteral("workspace"));
  workspace->addItem(tr("DESIGN"));
  workspace->setToolTip(tr("Workspace"));
  workspace->setMinimumWidth(110);
  QFont wf = workspace->font();
  wf.setBold(true);
  workspace->setFont(wf);

  // Entries: document commands plus tool commands, grouped by tab and panel
  // in the familiar order. A panel shows its first few entries as large
  // buttons; its title opens a menu with all of them and their shortcuts.
  struct Entry {
    QString id, name, tooltip, icon, shortcut;
    bool enabled;
    std::function<void()> run;
  };
  const std::vector<std::string> panelOrder = {"Create", "Modify", "Assemble", "Configure", "Construct", "Inspect", "Insert", "Select"};
  std::map<std::string, std::vector<Entry>> panels;
  for (const Command* c : session_.commands().all()) {
    const CommandDef& d = c->def();
    if (d.panel.empty()) continue;   // reached another way (Document Settings, Insert)
    const QString id = qs(d.id);
    panels[d.panel].push_back({id, qs(d.name), qs(d.tooltip), qs(d.icon), qs(d.shortcut), true,
                               [this, id] { startCommand(id); }});
  }
  for (const auto& u : uiCommands_)
    panels[u.panel].push_back({qs(u.id), qs(u.name), qs(u.tooltip), qs(u.icon), qs(u.shortcut), u.enabled, u.run});

  auto* page = new QWidget;
  auto* row = new QHBoxLayout(page);
  row->setContentsMargins(6, 2, 6, 2);
  row->setSpacing(2);
  for (const auto& panel : panelOrder) {
    const auto it = panels.find(panel);
    if (it == panels.end()) continue;
    auto* box = new QWidget;
    box->setObjectName(qs("Solid." + panel));
    auto* col = new QVBoxLayout(box);
    col->setContentsMargins(4, 0, 4, 0);
    col->setSpacing(0);
    auto* buttons = new QHBoxLayout;
    buttons->setSpacing(0);
    auto* menu = new QMenu(box);
    const size_t maxButtons = panel == "Create" || panel == "Modify" ? 7 : 3;
    size_t shown = 0;
    for (const Entry& e : it->second) {
      const QString tip = QStringLiteral("<b>%1</b>%2<br>%3")
                              .arg(e.name, e.shortcut.isEmpty() ? QString() : QStringLiteral(" &nbsp;(%1)").arg(e.shortcut),
                                   e.tooltip);
      if (e.enabled && shown < maxButtons) {
        auto* btn = new QToolButton;
        btn->setObjectName(e.id);
        btn->setText(e.name);
        setIcon(btn, e.icon);
        btn->setIconSize(QSize(30, 30));
        btn->setToolButtonStyle(Qt::ToolButtonIconOnly);
        btn->setAutoRaise(true);
        btn->setToolTip(tip);
        btn->setAccessibleName(e.name);
        auto run = e.run;
        connect(btn, &QToolButton::clicked, this, [run] { run(); });
        buttons->addWidget(btn);
        ++shown;
      }
      // The text after a tab is shown as the shortcut column.
      QAction* a = menu->addAction(e.shortcut.isEmpty() ? e.name : e.name + QLatin1Char('\t') + e.shortcut);
      a->setObjectName(e.id);
      a->setToolTip(tip);
      setIcon(a, e.icon);
      a->setEnabled(e.enabled);
      if (e.enabled) {
        auto run = e.run;
        connect(a, &QAction::triggered, this, [run] { run(); });
      } else {
        a->setText(a->text() + tr("  (planned)"));
      }
    }
    if (shown == 0) {
      // Planned-only panel: one greyed button keeps the layout recognisable.
      auto* btn = new QToolButton;
      setIcon(btn, it->second.front().icon);
      btn->setIconSize(QSize(30, 30));
      btn->setAutoRaise(true);
      btn->setEnabled(false);
      btn->setToolTip(tr("Planned: see docs/ROADMAP.md."));
      buttons->addWidget(btn);
    }
    col->addLayout(buttons);
    auto* title = new QToolButton;
    title->setText(qs(panel).toUpper() + QStringLiteral(" \u25BE"));
    title->setPopupMode(QToolButton::InstantPopup);
    title->setObjectName(qs("panel." + panel));
    title->setMenu(menu);
    title->setAutoRaise(true);
    title->setToolButtonStyle(Qt::ToolButtonTextOnly);
    QFont f = title->font();
    f.setPointSizeF(f.pointSizeF() * 0.85);
    title->setFont(f);
    col->addWidget(title, 0, Qt::AlignHCenter);
    row->addWidget(box);
    auto* sep = new QFrame;
    sep->setFrameShape(QFrame::VLine);
    sep->setFrameShadow(QFrame::Sunken);
    row->addWidget(sep);
  }
  row->addStretch();
  ribbon_->addTab(ribbonPage(page), QStringLiteral("SOLID"));
  // Workspace tabs that are planned, disabled like the planned panels.
  for (const char* t : {"SURFACE", "MESH", "SHEET METAL", "PLASTIC", "MANAGE", "UTILITIES"}) {
    const int i = ribbon_->addTab(new QWidget, QString::fromLatin1(t));
    ribbon_->setTabEnabled(i, false);
    ribbon_->setTabToolTip(i, tr("Planned: see docs/ROADMAP.md."));
  }

  auto* bar = new QToolBar(tr("Ribbon"));
  bar->setObjectName(QStringLiteral("ribbonBar"));
  bar->setMovable(false);
  bar->setFloatable(false);
  bar->addWidget(workspace);
  bar->addSeparator();
  // The ribbon takes the toolbar's remaining width; a QToolBar would
  // otherwise move a too-wide ribbon into its overflow menu and show nothing.
  ribbon_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  ribbon_->setMinimumWidth(240);
  bar->addWidget(ribbon_);
  addToolBar(Qt::TopToolBarArea, bar);
}

QWidget* MainWindow::ribbonPage(QWidget* page) {
  // Narrow windows: the panels scroll sideways (mouse wheel) instead of the
  // whole ribbon disappearing.
  auto* scroll = new QScrollArea;
  scroll->setObjectName(page->objectName().isEmpty() ? QStringLiteral("ribbonPage") : page->objectName() + QStringLiteral("Scroll"));
  scroll->setFrameShape(QFrame::NoFrame);
  scroll->setWidgetResizable(true);
  scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  scroll->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  scroll->setFixedHeight(page->sizeHint().height());
  scroll->setMinimumWidth(200);
  scroll->setWidget(page);
  scroll->viewport()->setAutoFillBackground(false);
  page->setAutoFillBackground(false);
  scroll->installEventFilter(this);
  scroll->viewport()->installEventFilter(this);
  return scroll;
}

void MainWindow::buildNavBar() {
  navBar_ = new QWidget(viewport_);
  navBar_->setObjectName(QStringLiteral("navBar"));
  navBar_->setAutoFillBackground(true);
  styleNavBar();
  auto* row = new QHBoxLayout(navBar_);
  row->setContentsMargins(6, 2, 6, 2);
  row->setSpacing(2);

  auto* orbit = flatButton(QStringLiteral("orbit"), tr("Orbit (left-drag). Shift+middle-drag also orbits."));
  orbit->setCheckable(true);
  auto* pan = flatButton(QStringLiteral("pan"), tr("Pan (left-drag). Middle-drag also pans."));
  pan->setCheckable(true);
  connect(orbit, &QToolButton::toggled, this, [this, pan](bool on) {
    if (on) pan->setChecked(false);
    viewport_->setOrbitTool(on);
  });
  connect(pan, &QToolButton::toggled, this, [this, orbit](bool on) {
    if (on) orbit->setChecked(false);
    viewport_->setPanTool(on);
  });
  {
    // Orbit type, like the orbit button's dropdown.
    auto* orbitMenu = new QMenu(orbit);
    auto* group = new QActionGroup(orbitMenu);
    QAction* free = orbitMenu->addAction(tr("Free Orbit"));
    QAction* constrained = orbitMenu->addAction(tr("Constrained Orbit"));
    for (QAction* a : {free, constrained}) {
      a->setCheckable(true);
      group->addAction(a);
    }
    const bool c = QSettings().value(QStringLiteral("nav/constrainedOrbit"), false).toBool();
    (c ? constrained : free)->setChecked(true);
    auto setOrbit = [this](bool constrainedOrbit) {
      QSettings().setValue(QStringLiteral("nav/constrainedOrbit"), constrainedOrbit);
      applyPreferences();
    };
    connect(free, &QAction::triggered, this, [setOrbit] { setOrbit(false); });
    connect(constrained, &QAction::triggered, this, [setOrbit] { setOrbit(true); });
    orbit->setMenu(orbitMenu);
    orbit->setPopupMode(QToolButton::MenuButtonPopup);
  }
  auto* fitB = flatButton(QStringLiteral("fit"), tr("Fit (F6)"));
  connect(fitB, &QToolButton::clicked, viewport_, &Viewport::fitAll);
  auto* homeB = flatButton(QStringLiteral("home"), tr("Home view (Home)"));
  connect(homeB, &QToolButton::clicked, viewport_, &Viewport::home);

  auto* views = flatButton(QString(), tr("Standard views"));
  views->setText(tr("Views"));
  views->setToolButtonStyle(Qt::ToolButtonTextOnly);
  views->setPopupMode(QToolButton::InstantPopup);
  auto* viewMenu = new QMenu(views);
  const std::pair<QString, V3d_TypeOfOrientation> std_views[] = {
      {tr("Front"), V3d_TypeOfOrientation_Zup_Front}, {tr("Back"), V3d_TypeOfOrientation_Zup_Back},
      {tr("Top"), V3d_TypeOfOrientation_Zup_Top},     {tr("Bottom"), V3d_TypeOfOrientation_Zup_Bottom},
      {tr("Left"), V3d_TypeOfOrientation_Zup_Left},   {tr("Right"), V3d_TypeOfOrientation_Zup_Right},
      {tr("Isometric"), V3d_TypeOfOrientation_Zup_AxoRight}};
  for (const auto& [name, o] : std_views) {
    const auto orient = o;
    viewMenu->addAction(name, this, [this, orient] { viewport_->viewFrom(orient); });
  }
  views->setMenu(viewMenu);

  auto* display = flatButton(QString(), tr("Display settings"));
  display->setObjectName(QStringLiteral("view.display"));
  display->setText(tr("Display"));
  display->setToolButtonStyle(Qt::ToolButtonTextOnly);
  display->setPopupMode(QToolButton::InstantPopup);
  auto* displayMenu = new QMenu(display);
  auto* styles = new QActionGroup(displayMenu);
  // Visual Style, with the familiar tool's names and order.
  using St = Viewport::Style;
  const std::tuple<QString, St, QString> styleList[] = {
      {tr("Shaded"), St::Shaded, QStringLiteral("view.style-shaded")},
      {tr("Shaded with Hidden Edges"), St::ShadedHidden, QStringLiteral("view.style-shaded-hidden")},
      {tr("Shaded with Visible Edges Only"), St::ShadedEdges, QStringLiteral("view.style-shaded-edges")},
      {tr("Wireframe"), St::Wireframe, QStringLiteral("view.style-wireframe")},
      {tr("Wireframe with Hidden Edges"), St::WireframeHidden, QStringLiteral("view.style-wireframe-hidden")},
      {tr("Wireframe with Visible Edges Only"), St::WireframeVisible, QStringLiteral("view.style-wireframe-visible")}};
  QMenu* styleMenu = displayMenu->addMenu(tr("Visual Style"));
  styleMenu->menuAction()->setObjectName(QStringLiteral("view.visual-style"));
  for (const auto& [name, st, id] : styleList) {
    const auto s = st;
    QAction* a = styleMenu->addAction(name, this, [this, s] { viewport_->setStyle(s); });
    a->setObjectName(id);
    a->setCheckable(true);
    a->setChecked(s == viewport_->style());
    styles->addAction(a);
  }
  displayMenu->addSeparator();
  auto* cameraGroup = new QActionGroup(displayMenu);
  QAction* ortho = displayMenu->addAction(tr("Orthographic"));
  QAction* persp = displayMenu->addAction(tr("Perspective"));
  for (QAction* a : {ortho, persp}) {
    a->setCheckable(true);
    cameraGroup->addAction(a);
  }
  (QSettings().value(QStringLiteral("nav/perspective"), false).toBool() ? persp : ortho)->setChecked(true);
  connect(ortho, &QAction::triggered, this, [this] {
    QSettings().setValue(QStringLiteral("nav/perspective"), false);
    applyPreferences();
  });
  connect(persp, &QAction::triggered, this, [this] {
    QSettings().setValue(QStringLiteral("nav/perspective"), true);
    applyPreferences();
  });

  // Grid and snaps.
  auto* gridButton = flatButton(QStringLiteral("grid"), tr("Grid and snaps"));
  gridButton->setPopupMode(QToolButton::InstantPopup);
  auto* gridMenu = new QMenu(gridButton);
  QAction* grid = gridMenu->addAction(tr("Layout Grid"));
  grid->setCheckable(true);
  grid->setChecked(true);
  connect(grid, &QAction::toggled, viewport_, &Viewport::setGridVisible);
  QAction* snap = gridMenu->addAction(tr("Snap to Grid"));
  snap->setCheckable(true);
  snap->setChecked(QSettings().value(QStringLiteral("grid/snap"), false).toBool());
  connect(snap, &QAction::toggled, this, [this](bool on) {
    QSettings().setValue(QStringLiteral("grid/snap"), on);
    viewport_->setGridSnap(on);
  });
  setIcon(gridMenu->addAction(tr("Grid Settings…"), this, [this] { gridSettings(); }), QStringLiteral("grid"));
  gridButton->setMenu(gridMenu);
  displayMenu->addSeparator();
  // Environment: background and light presets, kept in the settings.
  QMenu* envMenu = displayMenu->addMenu(tr("Environment"));
  envMenu->setObjectName(QStringLiteral("environmentMenu"));
  auto* envGroup = new QActionGroup(envMenu);
  const int savedEnv = QSettings().value(QStringLiteral("view/environment"), 0).toInt();
  const QStringList envNames = Viewport::environmentNames();
  for (int i = 0; i < envNames.size(); ++i) {
    QAction* a = envMenu->addAction(envNames[i]);
    a->setObjectName(QStringLiteral("environment%1").arg(i));
    a->setCheckable(true);
    a->setChecked(i == savedEnv);
    envGroup->addAction(a);
    connect(a, &QAction::triggered, this, [this, i] {
      QSettings().setValue(QStringLiteral("view/environment"), i);
      viewport_->setEnvironment(i);
    });
  }
  viewport_->setEnvironment(savedEnv);
  QAction* darkTheme = displayMenu->addAction(tr("Dark theme"));
  darkTheme->setObjectName(QStringLiteral("darkTheme"));
  darkTheme->setCheckable(true);
  darkTheme->setChecked(Theme::instance().dark());
  connect(darkTheme, &QAction::toggled, this, [](bool on) {
    Theme::instance().apply(on ? Theme::Mode::Dark : Theme::Mode::Light);
  });
  display->setMenu(displayMenu);

  for (QWidget* w : std::initializer_list<QWidget*>{orbit, pan, fitB, homeB, views, display, gridButton}) row->addWidget(w);
  navBar_->adjustSize();
  viewport_->installEventFilter(this);
  qApp->installEventFilter(this);   // Ctrl while picking edges (see ctrlFilter)
}

void MainWindow::styleNavBar() {
  if (!navBar_) return;
  const auto& c = themeColors();
  navBar_->setStyleSheet(QStringLiteral("#navBar { background: rgba(%1,%2,%3,%4); border: 1px solid rgba(%5,%6,%7,%8); "
                                        "border-radius: 6px; }")
                             .arg(c.navBackground.red()).arg(c.navBackground.green()).arg(c.navBackground.blue())
                             .arg(c.navBackground.alpha()).arg(c.navBorder.red()).arg(c.navBorder.green())
                             .arg(c.navBorder.blue()).arg(c.navBorder.alpha()));
}

void MainWindow::buildShortcuts() {
  auto add = [this](const QKeySequence& k, auto fn) {
    auto* s = new QShortcut(k, this);
    s->setContext(Qt::WindowShortcut);
    connect(s, &QShortcut::activated, this, fn);
    globalShortcuts_.push_back(s);
  };
  add(QKeySequence(Qt::Key_S), [this] { focusSearch(); });
  add(QKeySequence(Qt::Key_F6), [this] { viewport_->fitAll(); });
  add(QKeySequence(Qt::Key_Home), [this] { viewport_->home(); });
  add(QKeySequence(Qt::Key_Escape), [this] {
    if (measure_) measure_->close();
    else if (editor_) editor_->escape();
    else if (viewport_->planePicking()) {
      viewport_->setPlanePicking(false);
      statusBar()->showMessage(tr("Create Sketch cancelled."), 3000);
    } else if (active_) active_->reject();
    else clearPreSelection();
  });
  // Space: the last command again (in a sketch, the last sketch tool).
  add(QKeySequence(Qt::Key_Space), [this] {
    if (editor_) {
      if (editor_->tool() == SketchEditor::Tool::Select) {
        editor_->repeatLastTool();
        syncSketchTools();
      }
    } else if (!active_ && !lastCommand_.isEmpty()) {
      startCommand(lastCommand_);
    }
  });
  add(QKeySequence(Qt::Key_V), [this] {
    if (!editor_ && !active_) toggleSelectedVisibility();
  });
  add(QKeySequence(Qt::Key_Delete), [this] {
    if (editor_) {
      editor_->deleteSelection();
    } else if (!active_ && timeline_->hasFocus() && timeline_->currentItem()) {
      // A feature selected in the timeline (undo brings it back).
      const int id = timeline_->currentItem()->data(kFeatureIdRole).toInt();
      if (auto err = session_.deleteFeature(id); !err.empty()) statusBar()->showMessage(qs(err), 5000);
    }
  });
  // Sketch tool keys, active only in sketch mode.
  const std::pair<Qt::Key, SketchEditor::Tool> keys[] = {
      {Qt::Key_L, SketchEditor::Tool::Line},      {Qt::Key_R, SketchEditor::Tool::Rectangle},
      {Qt::Key_C, SketchEditor::Tool::Circle},    {Qt::Key_A, SketchEditor::Tool::Arc},
      {Qt::Key_P, SketchEditor::Tool::Project},     {Qt::Key_D, SketchEditor::Tool::Dimension},
      {Qt::Key_Q, SketchEditor::Tool::Select},    {Qt::Key_T, SketchEditor::Tool::Trim},
      {Qt::Key_O, SketchEditor::Tool::Offset}};
  for (const auto& [key, tool] : keys) {
    auto* s = new QShortcut(QKeySequence(key), this);
    s->setEnabled(false);
    const auto t = tool;
    connect(s, &QShortcut::activated, this, [this, t] {
      if (!editor_) return;
      editor_->setTool(t);
      syncSketchTools();
    });
    sketchShortcuts_.push_back(s);
  }
  auto* x = new QShortcut(QKeySequence(Qt::Key_X), this);
  x->setEnabled(false);
  connect(x, &QShortcut::activated, this, [this] {
    // Selected curves flip; with none selected, X switches the drawing mode.
    if (editor_ && !editor_->toggleSelectedConstruction() && constructionButton_) constructionButton_->click();
  });
  sketchShortcuts_.push_back(x);
  for (const auto& u : uiCommands_)
    if (u.enabled && !u.shortcut.empty()) {
      auto run = u.run;
      add(QKeySequence(qs(u.shortcut)), [this, run] {
        if (!editor_) run();
      });
    }
  for (const Command* c : session_.commands().all())
    if (!c->def().shortcut.empty()) {
      const QString id = qs(c->def().id);
      add(QKeySequence(qs(c->def().shortcut)), [this, id] { startCommand(id); });
    }
}

bool MainWindow::ctrlFilter(QEvent* e) {
  if (e->type() != QEvent::KeyPress && e->type() != QEvent::KeyRelease) return false;
  auto* k = static_cast<QKeyEvent*>(e);
  if (k->key() != Qt::Key_Control || k->isAutoRepeat()) return false;
  const bool picking = active_ && (active_->hasEdgesInput() || active_->hasFacesInput());
  setShowOriginal(e->type() == QEvent::KeyPress && picking);
  return false;
}

void MainWindow::focusSearch() {
  search_->setFocus(Qt::ShortcutFocusReason);
  search_->selectAll();
}

bool MainWindow::eventFilter(QObject* watched, QEvent* e) {
  // Ctrl held while a command picks edges or faces: the plain bodies show (no
  // preview). Key events reach this application-wide filter addressed to
  // whichever widget has the focus, so look at every one.
  if (e->type() == QEvent::KeyPress || e->type() == QEvent::KeyRelease) (void)ctrlFilter(e);
  if (watched == qApp) return false;
  if (timeline_ && watched == timeline_->viewport() && timelineDrag(e)) return true;
  if (watched == viewport_ && (e->type() == QEvent::Resize || e->type() == QEvent::Show) && navBar_) {
    navBar_->adjustSize();
    navBar_->move((viewport_->width() - navBar_->width()) / 2, viewport_->height() - navBar_->height() - 10);
    navBar_->raise();
    if (active_) placeDialog(active_);
    if (palette_) placeDialog(palette_);
  }
  if (e->type() == QEvent::Wheel) {
    // A ribbon too wide for the window scrolls sideways with the wheel.
    QWidget* w = qobject_cast<QWidget*>(watched);
    auto* scroll = w ? qobject_cast<QScrollArea*>(w) : nullptr;
    if (!scroll && w) scroll = qobject_cast<QScrollArea*>(w->parentWidget());
    if (scroll && scroll->horizontalScrollBar()->maximum() > 0) {
      auto* we = static_cast<QWheelEvent*>(e);
      const int delta = we->angleDelta().y() != 0 ? we->angleDelta().y() : we->angleDelta().x();
      scroll->horizontalScrollBar()->setValue(scroll->horizontalScrollBar()->value() - delta / 2);
      return true;
    }
  }
  return QMainWindow::eventFilter(watched, e);
}

// ---------------------------------------------------------------------------
CommandDialog* MainWindow::startCommand(const QString& commandId) {
  if (editor_) {
    statusBar()->showMessage(tr("Finish the sketch first (FINISH SKETCH)."), 3000);
    return nullptr;
  }
  if (commandId == QLatin1String(doc::kCmdSketch)) {
    beginSketch();
    return nullptr;
  }
  if (active_ || session_.document().hasOpenTransaction()) {
    statusBar()->showMessage(tr("Finish the current command first (OK or Esc)."), 3000);
    return nullptr;
  }
  // What was selected before: goes into the command.
  const auto preSubs = viewport_->selectedSubShapes();
  const QStringList preBodies = preSubs.empty() ? viewport_->selectedBodies() : QStringList();
  const QString preSketch = preSketch_;
  const QStringList preProfiles = preProfiles_;
  auto cmd = session_.begin(commandId.toStdString());
  if (!cmd) return nullptr;
  lastCommand_ = commandId;
  editingFeature_ = -1;
  skipAutoProfile_ = !preSubs.empty() || !preProfiles.isEmpty();
  auto* dlg = showDialog(std::move(cmd));
  skipAutoProfile_ = false;
  if (dlg) applyPreSelection(dlg, preSketch, preProfiles, preSubs, preBodies);
  else clearPreSelection();
  return dlg;
}

void MainWindow::clearPreSelection() {
  const bool had = !preProfiles_.isEmpty();
  preSketch_.clear();
  preProfiles_.clear();
  viewport_->clearSelection();
  if (had) updateProfilePicking();
}

void MainWindow::applyPreSelection(CommandDialog* dlg, const QString& sketch, const QStringList& profiles,
                                   const std::vector<std::pair<QString, TopoDS_Shape>>& subs,
                                   const QStringList& bodies) {
  preSketch_.clear();
  preProfiles_.clear();
  viewport_->clearSelection();
  if (!profiles.isEmpty() && dlg->hasProfilesInput()) dlg->setProfiles(sketch, profiles.join(QLatin1Char(';')));
  for (const auto& [body, shape] : subs) {
    if (active_ != dlg) return;
    onEdgeClicked(body, shape);
  }
  // Commands that take bodies (no faces / edges / vertices) get the bodies
  // of the faces and edges picked.
  QStringList bodyPicks = bodies;
  if (!dlg->hasFacesInput() && !dlg->hasEdgesInput() && !dlg->hasVerticesInput())
    for (const auto& [body, shape] : subs)
      if (!bodyPicks.contains(body)) bodyPicks << body;
  for (const QString& body : bodyPicks) {
    if (active_ != dlg) return;
    emit viewport_->bodyClicked(body);
  }
  if (active_ != dlg) return;
  updateProfilePicking();
  syncPickedShapes();
  updateDragArrow();
}

CommandDialog* MainWindow::editFeature(int featureId) {
  if (const auto f = session_.document().feature(featureId); f && f->commandId == doc::kCmdSketch) {
    editSketch(featureId);
    return nullptr;
  }
  if (editor_ || active_ || session_.document().hasOpenTransaction()) {
    statusBar()->showMessage(tr("Finish the current command first (OK or Esc)."), 3000);
    return nullptr;
  }
  // The bodies before this feature (picks refer to them), known from the replay.
  std::map<std::string, TopoDS_Shape> before;
  for (const auto& b : session_.document().bodies()) before[b.name] = b.shape;
  if (const auto* eff = session_.document().featureEffect(featureId))
    for (const auto& [name, change] : eff->bodies)
      if (!change.first.IsNull()) before[name] = change.first;
  auto cmd = session_.editFeature(featureId);
  if (!cmd) return nullptr;
  editingFeature_ = featureId;
  auto* dlg = showDialog(std::move(cmd));
  shapesBeforeCommand_ = std::move(before);
  if (dlg) syncPickedShapes();
  return dlg;
}

CommandDialog* MainWindow::showDialog(std::unique_ptr<CommandSession> cmd) {
  const bool extrudeDialog = cmd->def().id == doc::kCmdExtrude;
  // Decided before the panel previews (a preview would count as using the sketch).
  std::pair<QString, QString> autoProfile;
  if (cmd->def().id == doc::kCmdExtrude) {
    const auto& d = session_.document();
    const auto sketches = d.sketches();
    if (!sketches.empty() && sketchVisible(sketches.back().name)) {
      try {
        const auto& rec = sketches.back();
        const gp_Ax3 frame = d.planeFrame(rec.plane, rec.offset);
        const auto profiles = cachedProfiles(sketch::Sketch::fromJson(rec.data), frame);
        if (profiles.size() == 1)
          autoProfile = {qs(rec.name), QStringLiteral("%1,%2").arg(profiles[0].x, 0, 'g', 12).arg(profiles[0].y, 0, 'g', 12)};
      } catch (const std::exception&) {
      }
    }
  }
  bodiesBeforeCommand_.clear();
  shapesBeforeCommand_.clear();
  for (const auto& b : session_.document().bodies()) {
    bodiesBeforeCommand_.push_back(b.name);
    shapesBeforeCommand_[b.name] = b.shape;
  }
  auto* dlg = new CommandDialog(session_, std::move(cmd), this);
  dlg->setAttribute(Qt::WA_DeleteOnClose);
  // Command panels live inside the canvas, top right, like the familiar layout.
  dlg->setParent(viewport_, Qt::Widget);
  dlg->setProperty("panel", true);
  dlg->setAutoFillBackground(true);
  active_ = dlg;
  connect(dlg, &CommandDialog::inputsChanged, this, [this, dlg] {
    updateProfilePicking();
    syncPickedShapes();   // Clear, typed or edited picks: the highlight follows
    updateDragArrow();
    // Inputs that appear with an option (Extrude: To Object) switch plane picking.
    if (dlg->hasPlaneInput() && dlg->planeInputShown() != viewport_->planePicking())
      viewport_->setPlanePicking(dlg->planeInputShown());
  });
  // Embedded panels are not windows, so closing does not delete them: finish
  // here, synchronously, so the next command can start at once.
  connect(dlg, &QDialog::finished, this, [this, dlg] {
    if (active_ == dlg) active_ = nullptr;
    dlg->hide();
    dlg->deleteLater();
    viewport_->setProfilePicking(false);
    viewport_->setSubShapePicking({});
    viewport_->setPlanePicking(false);
    viewport_->clearDragArrow();
    viewport_->setCursorHint(QString());
    patternCentres_.clear();
    arrowInput_.clear();
    arrowInput2_.clear();
    pickedEdges_.clear();
    if (showingOriginal_) setShowOriginal(false);
    shapesBeforeCommand_.clear();
    refresh();
  });
  dlg->show();
  placeDialog(dlg);
  refresh();
  updateProfilePicking();
  if (dlg->planeInputShown()) viewport_->setPlanePicking(true);   // click a plane or flat face
  viewport_->setBodyPlanePicks(extrudeDialog);
  // Editing an existing feature: show its edges (one entry per reference,
  // null when the reference does not resolve on the current body).
  syncPickedShapes();
  // Started fresh (not editing): Extrude waits for a pick, except that the
  // single profile of a just-finished sketch is taken at once.
  if (dlg->commandId() == QLatin1String(doc::kCmdExtrude) && !dlg->isEditingFeature()) {
    if (!autoProfile.second.isEmpty() && !skipAutoProfile_) dlg->setProfiles(autoProfile.first, autoProfile.second);
    dlg->setRequireSelection(true);   // satisfied while something is picked
  }
  updateDragArrow();
  return dlg;
}

void MainWindow::placeDialog(QWidget* dlg) {
  dlg->adjustSize();
  if (dlg->parentWidget() == viewport_ && !dlg->isWindow()) {
    // Embedded panel: right edge of the canvas, below the ViewCube.
    dlg->move(viewport_->width() - dlg->width() - 12, 150);
    dlg->raise();
    return;
  }
  // Separate tool window: upper right of the canvas, clear of the ViewCube.
  const QPoint topRight = viewport_->mapToGlobal(QPoint(viewport_->width(), 0));
  dlg->move(topRight.x() - dlg->width() - 170, topRight.y() + 16);
}

void MainWindow::showContextMenu(const QPoint& globalPos) { (void)openMarkingMenu(globalPos); }

// The right-click marking menu: a ring of the most used commands around the
// cursor and a list below, different in sketch mode and inside a command.
MarkingMenu* MainWindow::openMarkingMenu(const QPoint& globalPos) {
  using Item = MarkingMenu::Item;
  auto cmd = [this](const char* id, const QString& text = QString()) -> Item {
    const Command* c = session_.commands().find(id);
    if (!c) return {};
    const QString cid = QString::fromLatin1(id);
    return {text.isEmpty() ? qs(c->def().name) : text, icon(qs(c->def().icon)), [this, cid] { startCommand(cid); },
            !active_ && !editor_};
  };
  auto ui = [this](const QString& text, const char* iconName, std::function<void()> run, bool enabled = true) -> Item {
    return {text, icon(QString::fromLatin1(iconName)), std::move(run), enabled};
  };
  std::vector<Item> ring, list;
  if (editor_) {
    using T = SketchEditor::Tool;
    // Right-click on a curve, point or constraint acts on it (Delete,
    // Normal / Construction), as in the familiar tool.
    const bool picked = editor_->tool() == T::Select && editor_->selectAt(viewport_->mapFromGlobal(globalPos));
    auto tool = [this, &ui](const QString& text, const char* iconName, T t) {
      return ui(text, iconName, [this, t] {
        if (!editor_) return;
        editor_->setTool(t);
        syncSketchTools();
      });
    };
    ring = {tool(tr("Line"), "line", T::Line),
            ui(tr("Undo"), "undo", [this] { if (editor_) editor_->undo(); }, editor_->canUndo()),
            tool(tr("Trim"), "trim", T::Trim),
            tool(tr("Offset"), "offset", T::Offset),
            ui(tr("Finish Sketch"), "finish", [this] { QTimer::singleShot(0, this, [this] { finishSketch(); }); }),
            tool(tr("Circle"), "circle", T::Circle),
            tool(tr("Rectangle"), "rectangle", T::Rectangle),
            tool(tr("Sketch Dimension"), "dimension", T::Dimension)};
    list = {tool(tr("Arc"), "arc", T::Arc), tool(tr("Spline"), "spline", T::Spline), tool(tr("Fillet"), "sketch-fillet", T::Fillet),
            tool(tr("Mirror"), "sketch-mirror", T::Mirror),
            ui(tr("Normal / Construction"), "construction", [this] {
              if (!editor_) return;
              if (!editor_->toggleSelectedConstruction()) editor_->setConstruction(!editor_->construction());
              syncSketchTools();
            }),
            ui(tr("Look At"), "look-at", [this] { if (editor_) viewport_->lookAt(editor_->frame()); }),
            ui(tr("Cancel Sketch"), "undo", [this] { QTimer::singleShot(0, this, [this] { cancelSketch(); }); })};
    if (picked) list.insert(list.begin(), ui(tr("Delete"), "remove", [this] { if (editor_) editor_->deleteSelection(); }));
  } else if (active_) {
    QPointer<CommandDialog> dlg = active_;
    ring = {ui(tr("OK"), "finish", [dlg] { if (dlg) dlg->accept(); }), {}, {}, {}, ui(tr("Cancel"), "undo", [dlg] { if (dlg) dlg->reject(); })};
  } else {
    Item repeat;
    if (!lastCommand_.isEmpty())
      if (const Command* c = session_.commands().find(lastCommand_.toStdString())) {
        const QString id = lastCommand_;
        repeat = {tr("Repeat %1").arg(qs(c->def().name)), icon(qs(c->def().icon)), [this, id] { startCommand(id); }};
      }
    // Over a flat face, Create Sketch sketches right on it.
    const QString facePlane = viewport_->sketchPlaneAt(viewport_->mapFromGlobal(globalPos));
    ring = {repeat,
            ui(tr("Undo"), "undo", [this] { session_.undo(); }, session_.document().canUndo()),
            cmd(doc::kCmdPressPull),
            cmd(doc::kCmdHole),
            ui(tr("Create Sketch"), "sketch",
               [this, facePlane] {
                 if (facePlane.isEmpty()) beginSketch();
                 else if (startSketch(facePlane)) statusBar()->showMessage(tr("Sketching on the face."), 3000);
               }),
            cmd(doc::kCmdExtrude),
            cmd(doc::kCmdFillet),
            cmd(doc::kCmdMove)};
    list = {ui(tr("Redo"), "redo", [this] { session_.redo(); }, session_.document().canRedo()),
            ui(tr("Measure"), "measure", [this] { openMeasure(); }),
            ui(tr("Section Analysis"), "section", [this] { openSection(); }),
            ui(tr("Change Parameters"), "parameters", [this] { showParameters(); }),
            ui(tr("Fit"), "fit", [this] { viewport_->fitAll(); }),
            ui(tr("Home View"), "home", [this] { viewport_->home(); }),
            ui(tr("Command Search"), "select", [this] { focusSearch(); })};
  }
  auto* m = new MarkingMenu(std::move(ring), std::move(list), this);
  m->popupAt(globalPos);
  return m;
}

void MainWindow::showTimelineMenu(const QPoint& pos) {
  QListWidgetItem* it = timeline_->itemAt(pos);
  if (!it) return;
  const int markerPos = session_.document().historyMarker();
  const int total = static_cast<int>(session_.document().features().size());
  if (it->data(kMarkerRole).toBool()) {
    QMenu m(this);
    m.addAction(tr("Roll to End"), this, [this, total] {
      if (auto err = session_.rollHistory(total); !err.empty()) statusBar()->showMessage(qs(err), 5000);
    })->setEnabled(!active_ && markerPos < total);
    m.exec(timeline_->viewport()->mapToGlobal(pos));
    return;
  }
  const int id = it->data(kFeatureIdRole).toInt();
  const auto f = session_.document().feature(id);
  if (!f) return;
  QMenu m(this);
  m.addAction(tr("Edit Feature"), this, [this, id] { editFeature(id); });
  m.addAction(tr("Rename"), this, [this, id, f] {
    bool ok = false;
    const QString name = QInputDialog::getText(this, tr("Rename"), tr("Name:"), QLineEdit::Normal, qs(f->name), &ok).trimmed();
    if (ok && !name.isEmpty() && name != qs(f->name))
      if (auto err = session_.renameFeature(id, name.toStdString()); !err.empty()) statusBar()->showMessage(qs(err), 5000);
  });
  // Features made from a sketch: open that sketch.
  if (auto s = f->inputs.find("sketch"); s != f->inputs.end())
    if (auto name = std::get_if<std::string>(&s->second); name && !name->empty())
      for (const auto& g : session_.document().features())
        if (g.commandId == doc::kCmdSketch && g.name == *name) {
          const int sid = g.id;
          m.addAction(icon(QStringLiteral("sketch")), tr("Edit Profile Sketch"), this, [this, sid] { editSketch(sid); });
          break;
        }
  m.addAction(f->suppressed ? tr("Unsuppress Feature") : tr("Suppress Feature"), this, [this, id, f] {
    if (auto err = session_.setFeatureSuppressed(id, !f->suppressed); !err.empty())
      statusBar()->showMessage(qs(err), 5000);
  });
  m.addSeparator();
  {
    // Roll the marker to just after this feature (it stays active).
    int index = 0;
    for (const auto& g : session_.document().features()) {
      ++index;
      if (g.id == id) break;
    }
    m.addAction(tr("Roll History Marker Here"), this, [this, index] {
      if (auto err = session_.rollHistory(index); !err.empty()) statusBar()->showMessage(qs(err), 5000);
    });
    if (markerPos < total)
      m.addAction(tr("Roll to End"), this, [this, total] {
        if (auto err = session_.rollHistory(total); !err.empty()) statusBar()->showMessage(qs(err), 5000);
      });
  }
  m.addSeparator();
  m.addAction(QIcon::fromTheme(QStringLiteral("edit-delete")), tr("Delete"), this, [this, id] {
    if (auto err = session_.deleteFeature(id); !err.empty()) statusBar()->showMessage(qs(err), 5000);
  });
  for (QAction* a : m.actions()) a->setEnabled(!active_);
  m.exec(timeline_->viewport()->mapToGlobal(pos));
}

// ---------------------------------------------------------------------------
void MainWindow::refresh() {
  doc::Document& d = session_.document();
  const QString name = session_.path() ? QFileInfo(qs(session_.path()->string())).completeBaseName() : tr("Untitled");
  setWindowTitle(name + (d.isModified() ? QStringLiteral("*") : QString()) + QStringLiteral(" — Tessera"));
  const bool idle = !active_ && !d.hasOpenTransaction();
  undo_->setEnabled(editor_ ? editor_->canUndo() : idle && d.canUndo());
  redo_->setEnabled(editor_ ? editor_->canRedo() : idle && d.canRedo());
  viewport_->setBodies(d.bodies());
  if (unitsLabel_) unitsLabel_->setText(tr("Units: %1").arg(qs(d.lengthUnit())));

  std::vector<SketchDisplay> sketches;
  for (const auto& rec : d.sketches()) {
    SketchDisplay sd;
    sd.name = rec.name;
    sd.visible = sketchVisible(rec.name) && !(editor_ && editor_->name().toStdString() == rec.name);
    if (sd.visible) {
      try {
        sd.frame = d.planeFrame(rec.plane, rec.offset);
        const auto s = sketch::Sketch::fromJson(rec.data);
        // Fully defined curves apart from the rest, as the familiar tool
        // shows them (the solver says which are fixed).
        sketch::Sketch solvedCopy = s;
        const auto solved = sketch::solve(solvedCopy);
        TopoDS_Compound freeC, fixedC;
        BRep_Builder bb;
        bb.MakeCompound(freeC);
        bb.MakeCompound(fixedC);
        bool anyFixed = false;
        for (int i = 0; i < static_cast<int>(s.entities.size()); ++i) {
          if (s.entities[i].construction) continue;
          const TopoDS_Shape e = sketch::curve(s, sd.frame, i);
          if (e.IsNull()) continue;
          const bool fixed = solved.ok && i < static_cast<int>(solved.entityFixed.size()) && solved.entityFixed[i];
          bb.Add(fixed ? fixedC : freeC, e);
          anyFixed = anyFixed || fixed;
        }
        for (int i = 0; i < static_cast<int>(s.texts.size()); ++i)
          if (const TopoDS_Shape t = sketch::textShape(s, sd.frame, i); !t.IsNull())
            for (TopExp_Explorer x(t, TopAbs_EDGE); x.More(); x.Next()) bb.Add(freeC, x.Current());
        sd.curves = freeC;
        if (anyFixed) sd.fixedCurves = fixedC;
        sd.construction = sketch::curves(s, sd.frame, true);
        sd.profiles = cachedProfiles(s, sd.frame);
      } catch (const std::exception&) {
        sd.visible = false;
      }
    }
    sketches.push_back(std::move(sd));
  }
  viewport_->setSketches(std::move(sketches));
  std::vector<std::pair<std::string, gp_Ax3>> planes;
  for (const auto& pl : d.planes()) {
    auto vis = constructionVisibility_.find(pl.name);
    if (vis != constructionVisibility_.end() && !vis->second) continue;
    try {
      planes.emplace_back(pl.name, d.planeFrame(pl.name));
    } catch (const std::exception&) {
    }
  }
  viewport_->setConstructionPlanes(planes);
  {
    std::vector<std::pair<std::string, gp_Ax1>> axes;
    std::vector<std::pair<std::string, gp_Pnt>> points;
    auto shown = [&](const std::string& n) {
      auto vis = constructionVisibility_.find(n);
      return vis == constructionVisibility_.end() || vis->second;
    };
    for (const auto& a : d.axes())
      if (shown(a.name)) axes.emplace_back(a.name, a.axis);
    for (const auto& p : d.points())
      if (shown(p.name)) points.emplace_back(p.name, p.point);
    viewport_->setConstructionAxesPoints(axes, points);
  }
  refreshBrowser(name);
  refreshTimeline();
  updateProfilePicking();   // profiles stay clickable with no command running
}

// Right-click in the Browser: Create Sketch on a plane, Edit Sketch, and
// Show / Hide (V) for anything with a visibility box.
void MainWindow::showBrowserMenu(const QPoint& pos) {
  QTreeWidgetItem* it = browser_->itemAt(pos);
  if (!it) return;
  browser_->setCurrentItem(it);
  QMenu m(this);
  m.setObjectName(QStringLiteral("browserMenu"));
  QString planeSpec = it->data(0, kOriginRole).toString();
  if (planeSpec.isEmpty()) {
    const QString name = it->data(0, kPlaneRole).toString();
    if (!name.isEmpty() && session_.document().plane(name.toStdString())) planeSpec = name;
  }
  if (!planeSpec.isEmpty() && !editor_ && !active_) {
    QAction* a = m.addAction(icon(QStringLiteral("sketch")), tr("Create Sketch"));
    a->setObjectName(QStringLiteral("browserCreateSketch"));
    connect(a, &QAction::triggered, this, [this, planeSpec] {
      if (startSketch(planeSpec)) statusBar()->showMessage(tr("Sketching on %1.").arg(planeSpec), 3000);
    });
  }
  if (it->data(0, kViewsFolderRole).toBool() && !active_) {
    QAction* a = m.addAction(icon(QStringLiteral("look-at")), tr("New Named View"));
    a->setObjectName(QStringLiteral("browserNewView"));
    connect(a, &QAction::triggered, this, [this] { newNamedView(); });
  }
  if (const QString view = it->data(0, kViewRole).toString(); !view.isEmpty()) {
    QAction* go = m.addAction(tr("Go To"), this, [this, view] { goToNamedView(view); });
    go->setObjectName(QStringLiteral("browserGoToView"));
    if (it->flags() & Qt::ItemIsEditable) {
      QAction* ren = m.addAction(tr("Rename"), this, [this, it] { browser_->editItem(it, 0); });
      ren->setObjectName(QStringLiteral("browserRenameView"));
      QAction* del = m.addAction(QIcon::fromTheme(QStringLiteral("edit-delete")), tr("Delete"), this, [this, view] {
        if (auto err = session_.deleteNamedView(view.toStdString()); !err.empty()) statusBar()->showMessage(qs(err), 5000);
      });
      del->setObjectName(QStringLiteral("browserDeleteView"));
      del->setEnabled(!active_);
    }
  }
  const QString sketch = it->data(0, kSketchRole).toString();
  if (!sketch.isEmpty() && !editor_ && !active_)
    for (const auto& f : session_.document().features())
      if (f.commandId == doc::kCmdSketch && qs(f.name) == sketch) {
        const int id = f.id;
        m.addAction(icon(QStringLiteral("sketch")), tr("Edit Sketch"), this, [this, id] { editSketch(id); });
        m.addAction(icon(QStringLiteral("export")), tr("Save As DXF…"), this, [this, sketch] { saveSketchDxf(sketch); });
        break;
      }
  if (it->flags() & Qt::ItemIsUserCheckable) {
    const bool shown = it->checkState(0) == Qt::Checked;
    QAction* a = m.addAction(shown ? tr("Hide\tV") : tr("Show\tV"));
    connect(a, &QAction::triggered, this, [it, shown] { it->setCheckState(0, shown ? Qt::Unchecked : Qt::Checked); });
  }
  if (m.isEmpty()) return;
  m.exec(browser_->viewport()->mapToGlobal(pos));
}

void MainWindow::goToNamedView(const QString& name) {
  if (name == QStringLiteral("TOP")) return viewport_->glideTo(V3d_TypeOfOrientation_Zup_Top);
  if (name == QStringLiteral("FRONT")) return viewport_->glideTo(V3d_TypeOfOrientation_Zup_Front);
  if (name == QStringLiteral("RIGHT")) return viewport_->glideTo(V3d_TypeOfOrientation_Zup_Right);
  if (name == QStringLiteral("HOME")) return viewport_->glideTo(V3d_TypeOfOrientation_Zup_AxoRight);
  for (const auto& v : session_.document().namedViews())
    if (qs(v.name) == name) {
      Viewport::ViewCamera c;
      c.eye = gp_Pnt(v.eye[0], v.eye[1], v.eye[2]);
      c.target = gp_Pnt(v.target[0], v.target[1], v.target[2]);
      c.up = gp_Dir(v.up[0], v.up[1], v.up[2]);
      c.size = v.size;
      viewport_->glideTo(c);
      return;
    }
}

// Saves the current camera as the next free "Named View N".
void MainWindow::newNamedView() {
  const auto existing = session_.document().namedViews();
  QString name;
  for (int n = 1;; ++n) {
    name = tr("Named View %1").arg(n);
    bool taken = false;
    for (const auto& v : existing) taken = taken || qs(v.name) == name;
    if (!taken) break;
  }
  const Viewport::ViewCamera c = viewport_->camera();
  doc::NamedView v;
  v.name = name.toStdString();
  for (int i = 0; i < 3; ++i) {
    v.eye[i] = c.eye.Coord(i + 1);
    v.target[i] = c.target.Coord(i + 1);
    v.up[i] = c.up.Coord(i + 1);
  }
  v.size = c.size;
  namedViewsOpen_ = true;
  if (auto err = session_.addNamedView(v); !err.empty()) statusBar()->showMessage(qs(err), 5000);
  else statusBar()->showMessage(tr("Saved the view as %1.").arg(name), 3000);
}

// V: shows or hides what is selected (bodies in the canvas, else the
// Browser's current item).
void MainWindow::toggleSelectedVisibility() {
  const QStringList bodies = viewport_->selectedBodies();
  if (!bodies.isEmpty()) {
    for (const QString& b : bodies) viewport_->setBodyVisible(b, !viewport_->isBodyVisible(b));
    viewport_->clearSelection();
    refresh();
    return;
  }
  QTreeWidgetItem* it = browser_->currentItem();
  if (it && (it->flags() & Qt::ItemIsUserCheckable))
    it->setCheckState(0, it->checkState(0) == Qt::Checked ? Qt::Unchecked : Qt::Checked);
}

void MainWindow::refreshBrowser(const QString& docName) {
  const QSignalBlocker block(browser_);
  doc::Document& d = session_.document();
  browser_->clear();
  auto* root = new QTreeWidgetItem(browser_, {docName});
  root->setIcon(0, QIcon::fromTheme(QStringLiteral("document-edit")));

  auto* settings = new QTreeWidgetItem(root, {tr("Document Settings")});
  settings->setIcon(0, icon(QStringLiteral("preferences")));
  auto* units = new QTreeWidgetItem(settings, {tr("Units: %1").arg(qs(d.lengthUnit()))});
  units->setIcon(0, icon(QStringLiteral("units")));
  units->setData(0, kUnitsRole, true);
  units->setToolTip(0, tr("Click to change the design's units"));
  settings->setExpanded(true);

  // Named Views: the four standard ones, then the design's own (renamable).
  auto* views = new QTreeWidgetItem(root, {tr("Named Views")});
  views->setIcon(0, icon(QStringLiteral("look-at")));
  views->setData(0, kViewsFolderRole, true);
  views->setToolTip(0, tr("Double-click a view to go to it; right-click to save the current one"));
  for (const char* fixed : {"TOP", "FRONT", "RIGHT", "HOME"}) {
    auto* it = new QTreeWidgetItem(views, {QString::fromLatin1(fixed)});
    it->setIcon(0, icon(QString::fromLatin1(fixed) == QStringLiteral("HOME") ? QStringLiteral("home")
                                                                              : QStringLiteral("look-at")));
    it->setData(0, kViewRole, QString::fromLatin1(fixed));
  }
  for (const auto& v : d.namedViews()) {
    auto* it = new QTreeWidgetItem(views, {qs(v.name)});
    it->setIcon(0, icon(QStringLiteral("look-at")));
    it->setData(0, kViewRole, qs(v.name));
    it->setFlags(it->flags() | Qt::ItemIsEditable);   // click again (or F2) to rename
  }
  views->setExpanded(namedViewsOpen_);
  if (section_.active) {
    auto* analysis = new QTreeWidgetItem(root, {tr("Analysis")});
    analysis->setIcon(0, icon(QStringLiteral("section")));
    auto* sec = new QTreeWidgetItem(analysis, {tr("Section Analysis")});
    sec->setIcon(0, icon(QStringLiteral("section")));
    sec->setData(0, kAnalysisRole, true);
    sec->setFlags(sec->flags() | Qt::ItemIsUserCheckable);
    sec->setCheckState(0, section_.visible ? Qt::Checked : Qt::Unchecked);
    sec->setToolTip(0, tr("Double-click to edit"));
    analysis->setExpanded(true);
  }

  auto* origin = new QTreeWidgetItem(root, {tr("Origin")});
  origin->setIcon(0, QIcon::fromTheme(QStringLiteral("crosshairs")));
  for (const char* o : {"O", "X", "Y", "Z", "XY", "XZ", "YZ"}) {
    auto* it = new QTreeWidgetItem(origin, {QString::fromLatin1(o)});
    if (std::strlen(o) == 2) {
      it->setData(0, kOriginRole, QString::fromLatin1(o));
      it->setIcon(0, icon(QStringLiteral("plane")));
      it->setToolTip(0, tr("Right-click > Create Sketch"));
    } else {
      it->setIcon(0, icon(std::strlen(o) == 1 && o[0] == 'O' ? QStringLiteral("point") : QStringLiteral("axis")));
    }
  }

  const auto bodies = d.bodies();
  auto* bodiesItem = new QTreeWidgetItem(root, {tr("Bodies (%1)").arg(bodies.size())});
  bodiesItem->setIcon(0, icon(QStringLiteral("box")));
  for (const auto& b : bodies) {
    const QString n = qs(b.name);
    const double v = kernel::massProperties(b.shape).volume * 1000.0; // cm³ -> mm³
    auto* it = new QTreeWidgetItem(bodiesItem, {qs(b.display)});
    it->setFlags(it->flags() | Qt::ItemIsEditable);   // click again (or F2) to rename
    it->setToolTip(0, tr("Volume %1 mm³").arg(v, 0, 'g', 6));
    it->setData(0, kBodyRole, n);
    it->setFlags(it->flags() | Qt::ItemIsUserCheckable);
    it->setCheckState(0, viewport_->isBodyVisible(n) ? Qt::Checked : Qt::Unchecked);
  }

  const auto comps = d.components();
  if (!comps.empty()) {
    auto* folder = new QTreeWidgetItem(root, {tr("Components (%1)").arg(comps.size())});
    folder->setIcon(0, icon(QStringLiteral("component")));
    for (const auto& c : comps) {
      auto* it = new QTreeWidgetItem(folder, {qs(c.name)});
      it->setIcon(0, icon(QStringLiteral("component")));
      for (const auto& b : c.bodies) {
        auto* bi = new QTreeWidgetItem(it, {qs(b)});
        bi->setIcon(0, icon(QStringLiteral("body")));
      }
      it->setExpanded(true);
    }
    folder->setExpanded(true);
  }
  {
    std::vector<std::pair<int, std::string>> joints;
    for (const auto& f : d.features())
      if (f.commandId == doc::kCmdJoint || f.commandId == doc::kCmdAsBuiltJoint) joints.emplace_back(f.id, f.name);
    if (!joints.empty()) {
      auto* folder = new QTreeWidgetItem(root, {tr("Joints (%1)").arg(joints.size())});
      folder->setIcon(0, icon(QStringLiteral("joint")));
      for (const auto& [id, name] : joints) {
        auto* it = new QTreeWidgetItem(folder, {qs(name)});
        it->setIcon(0, icon(QStringLiteral("joint")));
      }
      folder->setExpanded(true);
    }
  }

  const auto sketches = d.sketches();
  if (!sketches.empty()) {
    auto* sk = new QTreeWidgetItem(root, {tr("Sketches (%1)").arg(sketches.size())});
    sk->setIcon(0, icon(QStringLiteral("sketch")));
    for (const auto& s : sketches) {
      const QString n = qs(s.name);
      auto* it = new QTreeWidgetItem(sk, {n});
      it->setFlags(it->flags() | Qt::ItemIsEditable);
      // Fully defined sketches show a lock, as in the familiar Browser.
      bool locked = false;
      try {
        auto sketchCopy = sketch::Sketch::fromJson(s.data);
        const auto r = sketch::solve(sketchCopy);
        locked = r.ok && r.dof == 0 && !sketchCopy.entities.empty();
      } catch (const std::exception&) {
      }
      it->setIcon(0, icon(locked ? QStringLiteral("sketch-locked") : QStringLiteral("sketch")));
      it->setData(0, kSketchLockedRole, locked);
      it->setToolTip(0, locked ? tr("Fully defined. Double-click to edit") : tr("Double-click to edit"));
      it->setData(0, kSketchRole, n);
      it->setFlags(it->flags() | Qt::ItemIsUserCheckable);
      it->setCheckState(0, sketchVisible(s.name) ? Qt::Checked : Qt::Unchecked);
    }
    sk->setExpanded(true);
  }

  // Construction: planes, axes and points, each with a visibility box.
  std::vector<std::pair<std::string, const char*>> cons;
  for (const auto& pl : d.planes()) cons.emplace_back(pl.name, "plane");
  for (const auto& a : d.axes()) cons.emplace_back(a.name, "axis");
  for (const auto& p : d.points()) cons.emplace_back(p.name, "point");
  if (!cons.empty()) {
    auto* folder = new QTreeWidgetItem(root, {tr("Construction (%1)").arg(cons.size())});
    folder->setIcon(0, icon(QStringLiteral("plane")));
    for (const auto& [name, iconName] : cons) {
      const QString n = qs(name);
      auto* it = new QTreeWidgetItem(folder, {n});
      it->setIcon(0, icon(QString::fromLatin1(iconName)));
      it->setData(0, kPlaneRole, n);
      it->setFlags(it->flags() | Qt::ItemIsUserCheckable);
      const auto vis = constructionVisibility_.find(name);
      it->setCheckState(0, vis == constructionVisibility_.end() || vis->second ? Qt::Checked : Qt::Unchecked);
    }
    folder->setExpanded(true);
  }

  auto* params = new QTreeWidgetItem(root, {tr("User Parameters")});
  params->setIcon(0, icon(QStringLiteral("parameters")));
  params->setData(0, kParametersRole, true);
  params->setToolTip(0, tr("Double-click to change parameters"));
  for (const auto& p : d.userParameters()) {
    auto* it = new QTreeWidgetItem(params, {qs(p.name + " = " + p.expression)});
    it->setData(0, kParametersRole, true);
    it->setToolTip(0, qs(p.comment.empty() ? p.unit : p.comment));
  }

  root->setExpanded(true);
  bodiesItem->setExpanded(true);
  params->setExpanded(true);
}

// Where a drop at x goes: the number of items whose centre is left of x.
int MainWindow::timelineSlot(int x) const {
  int slot = 0;
  for (int i = 0; i < timeline_->count(); ++i)
    if (timeline_->visualItemRect(timeline_->item(i)).center().x() < x) slot = i + 1;
  return slot;
}

// Press, drag past the start distance, release: the item moves to the slot
// under the pointer. Returns true when the event was used.
bool MainWindow::timelineDrag(QEvent* e) {
  // Only mouse events are cast (every other event passes through here too).
  if (e->type() != QEvent::MouseButtonPress && e->type() != QEvent::MouseMove &&
      e->type() != QEvent::MouseButtonRelease)
    return false;
  auto* me = static_cast<QMouseEvent*>(e);
  switch (e->type()) {
    case QEvent::MouseButtonPress:
      timelineDragRow_ = -1;
      timelineDragging_ = false;
      if (me->button() == Qt::LeftButton)
        if (QListWidgetItem* it = timeline_->itemAt(me->position().toPoint())) {
          timelineDragRow_ = timeline_->row(it);
          timelineDragStart_ = me->position().toPoint();
        }
      return false;
    case QEvent::MouseMove: {
      if (timelineDragRow_ < 0 || !(me->buttons() & Qt::LeftButton)) return false;
      const QPoint p = me->position().toPoint();
      if (!timelineDragging_ && (p - timelineDragStart_).manhattanLength() < QApplication::startDragDistance())
        return false;
      timelineDragging_ = true;
      const int slot = timelineSlot(p.x());
      int x = 0;
      if (slot < timeline_->count()) x = timeline_->visualItemRect(timeline_->item(slot)).left() - 2;
      else if (timeline_->count() > 0) x = timeline_->visualItemRect(timeline_->item(timeline_->count() - 1)).right() + 1;
      timelineDropBar_->setGeometry(x, 2, 3, timeline_->viewport()->height() - 4);
      timelineDropBar_->show();
      timelineDropBar_->raise();
      timeline_->viewport()->setCursor(Qt::ClosedHandCursor);
      return true;
    }
    case QEvent::MouseButtonRelease: {
      const bool dragged = timelineDragging_ && me->button() == Qt::LeftButton;
      const int from = timelineDragRow_;
      timelineDragRow_ = -1;
      timelineDragging_ = false;
      timelineDropBar_->hide();
      timeline_->viewport()->unsetCursor();
      if (!dragged || from < 0) return false;
      int to = timelineSlot(me->position().toPoint().x());
      if (to > from) --to;   // after taking the item out
      if (to != from) QTimer::singleShot(0, this, [this, from, to] { applyTimelineFromList(from, to); });
      return true;
    }
    default:
      return false;
  }
}

// The timeline after moving row `from` to row `to`: feature order and where
// the marker is; refused (and the list restored) if a feature would break.
void MainWindow::applyTimelineFromList(int from, int to) {
  std::vector<QListWidgetItem*> items;
  for (int i = 0; i < timeline_->count(); ++i) items.push_back(timeline_->item(i));
  if (from < 0 || from >= static_cast<int>(items.size())) return;
  QListWidgetItem* moved = items[from];
  items.erase(items.begin() + from);
  items.insert(items.begin() + std::clamp(to, 0, static_cast<int>(items.size())), moved);
  std::vector<int> order;
  int marker = -1;
  for (QListWidgetItem* it : items) {
    if (it->data(kMarkerRole).toBool()) marker = static_cast<int>(order.size());
    else order.push_back(it->data(kFeatureIdRole).toInt());
  }
  if (marker < 0) marker = static_cast<int>(order.size());
  std::vector<int> current;
  for (const auto& f : session_.document().features()) current.push_back(f.id);
  if (order == current && marker == session_.document().historyMarker()) return;
  if (active_ || editor_) {
    statusBar()->showMessage(tr("Finish the current command first."), 4000);
    refresh();
    return;
  }
  if (const auto err = session_.setTimeline(order, marker); !err.empty()) {
    statusBar()->showMessage(qs(err), 6000);
    refresh();   // the list goes back to the timeline as it is
  }
}

void MainWindow::refreshTimeline() {
  // (Not blocking the model's signals: the view must see the new rows.
  // Clearing and adding never emit rowsMoved.)
  timeline_->clear();
  const auto features = session_.document().features();
  const int marker = session_.document().historyMarker();
  auto addMarker = [this] {
    auto* m = new QListWidgetItem(icon(QStringLiteral("history-marker")), QString());
    m->setData(kMarkerRole, true);
    m->setData(Qt::AccessibleTextRole, tr("History Marker"));
    m->setToolTip(tr("<b>History marker</b><br>Drag it back to roll the design back; features made then go in here."));
    m->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);
    timeline_->addItem(m);
  };
  int index = 0;
  for (const auto& f : features) {
    if (index++ == marker) addMarker();
    auto* it = new QListWidgetItem(icon(commandIcon(session_, f.commandId)), QString());
    it->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);
    it->setData(kFeatureIdRole, f.id);
    it->setData(Qt::AccessibleTextRole, qs(f.name));
    QString tip = QStringLiteral("<b>%1</b>").arg(qs(f.name));
    if (f.rolledBack) {   // after the marker: shown faded, not replayed
      tip += tr("<br>Rolled back (after the history marker)");
      it->setIcon(QIcon(it->icon().pixmap(28, 28, QIcon::Disabled)));
    }
    if (f.suppressed) {
      tip += tr("<br>Suppressed");
      it->setForeground(Qt::gray);
      it->setIcon(QIcon(it->icon().pixmap(28, 28, QIcon::Disabled)));
    }
    if (!f.error.empty() && !f.rolledBack) {
      tip += QStringLiteral("<br><span style='color:#c0392b'>%1</span>").arg(qs(f.error).toHtmlEscaped());
      it->setBackground(themeColors().errorBackground);
    }
    tip += tr("<br><i>Double-click to edit; drag to move</i>");
    it->setToolTip(tip);
    timeline_->addItem(it);
  }
  if (marker >= static_cast<int>(features.size())) addMarker();
  timeline_->scrollToBottom();
}

// ---------------------------------------------------------------------------
bool MainWindow::maybeSave() {
  if (!session_.document().isModified()) return true;
  const auto r = QMessageBox::question(this, tr("Tessera"), tr("Save changes to this design?"),
                                       QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
  if (r == QMessageBox::Cancel) return false;
  if (r == QMessageBox::Discard) return true;
  return session_.path() ? saveTo(qs(session_.path()->string())) : saveAs();
}

// Insert DXF / SVG: the drawing becomes a new sketch on a plane picked from a
// list (the origin planes and construction planes).
void MainWindow::insertDxf(bool svg) {
  if (editor_ || active_) {
    statusBar()->showMessage(tr("Finish the current command first."), 3000);
    return;
  }
  const QString title = svg ? tr("Insert SVG") : tr("Insert DXF");
  const QString path = QFileDialog::getOpenFileName(this, title, QString(),
                                                    svg ? tr("SVG drawing (*.svg)") : tr("DXF drawing (*.dxf)"));
  if (path.isEmpty()) return;
  QStringList planes = {QStringLiteral("XY"), QStringLiteral("XZ"), QStringLiteral("YZ")};
  for (const auto& p : session_.document().planes()) planes << qs(p.name);
  bool ok = false;
  const QString plane = QInputDialog::getItem(this, title, tr("Sketch plane:"), planes, 0, false, &ok);
  if (!ok) return;
  try {
    QFile f(path);
    if (!f.open(QIODevice::ReadOnly)) throw std::runtime_error("cannot read " + path.toStdString());
    const std::string data = f.readAll().toStdString();
    const sketch::Sketch s = svg ? sketch::fromSvg(data) : sketch::fromDxf(data);
    Inputs in{{"plane", plane.toStdString()}, {"data", s.toJson()}};
    if (auto err = session_.run(doc::kCmdSketch, in); !err.empty()) throw std::runtime_error(err);
    viewport_->fitAll();
  } catch (const std::exception& e) {
    QMessageBox::critical(this, title, QString::fromStdString(e.what()));
  }
}

void MainWindow::saveSketchDxf(const QString& name) {
  const auto rec = session_.document().sketch(name.toStdString());
  if (!rec) return;
  QString path = QFileDialog::getSaveFileName(this, tr("Save Sketch As DXF"), name + QStringLiteral(".dxf"),
                                              tr("DXF drawing (*.dxf)"));
  if (path.isEmpty()) return;
  if (!path.endsWith(QStringLiteral(".dxf"), Qt::CaseInsensitive)) path += QStringLiteral(".dxf");
  try {
    QFile f(path);
    if (!f.open(QIODevice::WriteOnly)) throw std::runtime_error("cannot write " + path.toStdString());
    f.write(QByteArray::fromStdString(sketch::toDxf(sketch::Sketch::fromJson(rec->data))));
    statusBar()->showMessage(tr("Saved %1").arg(path), 3000);
  } catch (const std::exception& e) {
    QMessageBox::critical(this, tr("Save failed"), QString::fromStdString(e.what()));
  }
}

// Recent designs: newest first, at most ten, kept in the settings.
void MainWindow::noteRecent(const QString& path) {
  QSettings st;
  QStringList list = st.value(QStringLiteral("files/recent")).toStringList();
  const QString abs = QFileInfo(path).absoluteFilePath();
  list.removeAll(abs);
  list.prepend(abs);
  while (list.size() > 10) list.removeLast();
  st.setValue(QStringLiteral("files/recent"), list);
}

void MainWindow::fillRecentMenu(QMenu* menu) {
  menu->clear();
  const QStringList list = QSettings().value(QStringLiteral("files/recent")).toStringList();
  for (const QString& p : list) {
    if (!QFileInfo::exists(p)) continue;
    QAction* a = menu->addAction(QFileInfo(p).fileName(), this, [this, p] { openPath(p); });
    a->setToolTip(p);
    a->setStatusTip(p);
  }
  if (menu->isEmpty()) menu->addAction(tr("(none yet)"))->setEnabled(false);
  else {
    menu->addSeparator();
    menu->addAction(tr("Clear List"), this, [] { QSettings().remove(QStringLiteral("files/recent")); });
  }
}

void MainWindow::openPath(const QString& path) {
  if (!maybeSave()) return;
  try {
    session_.open(path.toStdString());
    noteRecent(path);
    viewport_->fitAll();
  } catch (const std::exception& e) {
    QMessageBox::critical(this, tr("Open failed"), QString::fromStdString(e.what()));
  }
}

bool MainWindow::saveAs() {
  QString path = QFileDialog::getSaveFileName(this, tr("Save Design"), QString(), kFilter);
  if (path.isEmpty()) return false;
  if (!path.endsWith(QStringLiteral(".tsr"), Qt::CaseInsensitive)) path += QStringLiteral(".tsr");
  return saveTo(path);
}

bool MainWindow::saveTo(const QString& path) {
  try {
    session_.save(path.toStdString());
    noteRecent(path);
    statusBar()->showMessage(tr("Saved %1").arg(path), 3000);
    return true;
  } catch (const std::exception& e) {
    QMessageBox::critical(this, tr("Save failed"), QString::fromStdString(e.what()));
    return false;
  }
}

void MainWindow::openFile() {
  if (!maybeSave()) return;
  const QString path = QFileDialog::getOpenFileName(this, tr("Open Design"), QString(), kFilter);
  if (path.isEmpty()) return;
  try {
    session_.open(path.toStdString());
    noteRecent(path);
    viewport_->fitAll();
  } catch (const std::exception& e) {
    QMessageBox::critical(this, tr("Open failed"), QString::fromStdString(e.what()));
  }
}

void MainWindow::runScript() {
  const QString path = QFileDialog::getOpenFileName(this, tr("Run Script"), QString(), tr("Python (*.py)"));
  if (path.isEmpty()) return;
  const auto r = python_.runScript(path.toStdString());
  if (!r.ok)
    QMessageBox::warning(this, tr("Script failed"), QString::fromStdString(r.output + r.error));
  else if (!r.output.empty())
    QMessageBox::information(this, tr("Script output"), QString::fromStdString(r.output));
}

void MainWindow::closeEvent(QCloseEvent* e) {
  if (editor_) cancelSketch();
  if (active_) active_->reject();
  if (maybeSave()) e->accept();
  else e->ignore();
}

} // namespace tsr::app
