#include "MainWindow.h"
#include "CommandDialog.h"
#include "Icons.h"
#include "Theme.h"
#include "SketchEditor.h"
#include "Viewport.h"

#include "tsr/doc/DocCommands.h"

#include "tsr/kernel/Kernel.h"

#include <QActionGroup>
#include <QCursor>
#include <QSettings>
#include <QApplication>
#include <QCloseEvent>
#include <QComboBox>
#include <QCompleter>
#include <QDockWidget>
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
  connect(browser_, &QTreeWidget::itemChanged, this, [this](QTreeWidgetItem* item, int) {
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
    const QString sketch = item->data(0, kSketchRole).toString();
    if (sketch.isEmpty()) return;
    for (const auto& f : session_.document().features())
      if (f.commandId == doc::kCmdSketch && f.name == sketch.toStdString()) {
        editSketch(f.id);
        return;
      }
  });
  auto* browserDock = new QDockWidget(tr("BROWSER"));
  browserDock->setObjectName(QStringLiteral("browserDock"));
  browserDock->setWidget(browser_);
  browserDock->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
  addDockWidget(Qt::LeftDockWidgetArea, browserDock);

  // Timeline.
  timeline_ = new QListWidget;
  timeline_->setObjectName(QStringLiteral("timeline"));
  timeline_->setViewMode(QListView::IconMode);
  timeline_->setFlow(QListView::LeftToRight);
  timeline_->setWrapping(false);
  timeline_->setMovement(QListView::Static);
  timeline_->setIconSize(QSize(28, 28));
  timeline_->setGridSize(QSize(40, 40));
  timeline_->setFixedHeight(52);
  timeline_->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  timeline_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  timeline_->setContextMenuPolicy(Qt::CustomContextMenu);
  timeline_->setAccessibleName(tr("Timeline"));
  connect(timeline_, &QListWidget::itemDoubleClicked, this,
          [this](QListWidgetItem* it) { editFeature(it->data(kFeatureIdRole).toInt()); });
  connect(timeline_, &QListWidget::customContextMenuRequested, this, &MainWindow::showTimelineMenu);
  auto* timelineDock = new QDockWidget(tr("TIMELINE"));
  timelineDock->setObjectName(QStringLiteral("timelineDock"));
  timelineDock->setWidget(timeline_);
  timelineDock->setFeatures(QDockWidget::DockWidgetMovable);
  addDockWidget(Qt::BottomDockWidgetArea, timelineDock);

  // Canvas.
  viewport_ = new Viewport;
  setCentralWidget(viewport_);
  connect(viewport_, &Viewport::contextMenuRequested, this, &MainWindow::showContextMenu);
  connect(viewport_, &Viewport::profileClicked, this, &MainWindow::onProfileClicked);
  connect(viewport_, &Viewport::subShapeClicked, this, [this](const QString& body, const TopoDS_Shape& shape) {
    if (measure_) measurePick(shape);
    else onEdgeClicked(body, shape);
  });
  connect(viewport_, &Viewport::planePicked, this, [this](const QString& spec, const QString& label) {
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
    if (active_ && active_->hasBodiesInput() && !active_->currentBody().isEmpty() && active_->currentBody() != name) {
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
    const QStringList sel = viewport_->selectedBodies();
    if (sel.isEmpty()) statusBar()->clearMessage();
    else statusBar()->showMessage(tr("Selected: %1").arg(sel.join(QStringLiteral(", "))));
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
      btn->setToolTip(tr("Planned: see ROADMAP.md."));
      buttons->addWidget(btn);
    }
    col->addLayout(buttons);
    auto* title = new QToolButton;
    title->setText(qs(panel).toUpper() + QStringLiteral(" \u25BE"));
    title->setPopupMode(QToolButton::InstantPopup);
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
  ribbon_->addTab(page, QStringLiteral("SOLID"));
  // Workspace tabs that are planned, disabled like the planned panels.
  for (const char* t : {"SURFACE", "MESH", "SHEET METAL", "PLASTIC", "MANAGE", "UTILITIES"}) {
    const int i = ribbon_->addTab(new QWidget, QString::fromLatin1(t));
    ribbon_->setTabEnabled(i, false);
    ribbon_->setTabToolTip(i, tr("Planned: see ROADMAP.md."));
  }

  auto* bar = new QToolBar(tr("Ribbon"));
  bar->setObjectName(QStringLiteral("ribbonBar"));
  bar->setMovable(false);
  bar->setFloatable(false);
  bar->addWidget(workspace);
  bar->addSeparator();
  bar->addWidget(ribbon_);
  addToolBar(Qt::TopToolBarArea, bar);
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
  display->setText(tr("Display"));
  display->setToolButtonStyle(Qt::ToolButtonTextOnly);
  display->setPopupMode(QToolButton::InstantPopup);
  auto* displayMenu = new QMenu(display);
  auto* styles = new QActionGroup(displayMenu);
  const std::pair<QString, Viewport::Style> styleList[] = {{tr("Shaded"), Viewport::Style::Shaded},
                                                          {tr("Shaded with visible edges"), Viewport::Style::ShadedEdges},
                                                          {tr("Wireframe"), Viewport::Style::Wireframe}};
  for (const auto& [name, st] : styleList) {
    const auto s = st;
    QAction* a = displayMenu->addAction(name, this, [this, s] { viewport_->setStyle(s); });
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
    else viewport_->clearSelection();
  });
  add(QKeySequence(Qt::Key_Delete), [this] {
    if (editor_) editor_->deleteSelection();
  });
  // Sketch tool keys, active only in sketch mode.
  const std::pair<Qt::Key, SketchEditor::Tool> keys[] = {
      {Qt::Key_L, SketchEditor::Tool::Line},      {Qt::Key_R, SketchEditor::Tool::Rectangle},
      {Qt::Key_C, SketchEditor::Tool::Circle},    {Qt::Key_A, SketchEditor::Tool::Arc},
      {Qt::Key_P, SketchEditor::Tool::Point},     {Qt::Key_D, SketchEditor::Tool::Dimension},
      {Qt::Key_Q, SketchEditor::Tool::Select}};
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
    if (editor_ && constructionButton_) constructionButton_->click();
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

void MainWindow::focusSearch() {
  search_->setFocus(Qt::ShortcutFocusReason);
  search_->selectAll();
}

bool MainWindow::eventFilter(QObject* watched, QEvent* e) {
  if (watched == viewport_ && (e->type() == QEvent::Resize || e->type() == QEvent::Show) && navBar_) {
    navBar_->adjustSize();
    navBar_->move((viewport_->width() - navBar_->width()) / 2, viewport_->height() - navBar_->height() - 10);
    navBar_->raise();
    if (active_) placeDialog(active_);
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
  auto cmd = session_.begin(commandId.toStdString());
  if (!cmd) return nullptr;
  lastCommand_ = commandId;
  return showDialog(std::move(cmd));
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
  auto cmd = session_.editFeature(featureId);
  if (!cmd) return nullptr;
  return showDialog(std::move(cmd));
}

CommandDialog* MainWindow::showDialog(std::unique_ptr<CommandSession> cmd) {
  auto* dlg = new CommandDialog(session_, std::move(cmd), this);
  dlg->setAttribute(Qt::WA_DeleteOnClose);
  // Command panels live inside the canvas, top right, like the familiar layout.
  dlg->setParent(viewport_, Qt::Widget);
  dlg->setProperty("panel", true);
  dlg->setAutoFillBackground(true);
  active_ = dlg;
  connect(dlg, &CommandDialog::inputsChanged, this, [this] { updateProfilePicking(); });
  // Embedded panels are not windows, so closing does not delete them: finish
  // here, synchronously, so the next command can start at once.
  connect(dlg, &QDialog::finished, this, [this, dlg] {
    if (active_ == dlg) active_ = nullptr;
    dlg->hide();
    dlg->deleteLater();
    viewport_->setProfilePicking(false);
    viewport_->setSubShapePicking({});
    pickedEdges_.clear();
    refresh();
  });
  dlg->show();
  placeDialog(dlg);
  refresh();
  updateProfilePicking();
  // Editing an existing feature: show its edges (one entry per reference,
  // null when the reference does not resolve on the current body).
  pickedEdges_.clear();
  if (dlg->hasEdgesInput()) {
    const TopoDS_Shape body = viewport_->bodyShape(dlg->currentBody());
    for (const QString& ref : dlg->currentEdges().split(QLatin1Char(';'), Qt::SkipEmptyParts)) {
      TopoDS_Shape e;
      try {
        if (!body.IsNull()) e = kernel::resolveEdges(body, ref.toStdString()).front();
      } catch (const std::exception&) {
      }
      pickedEdges_.push_back(e);
    }
  }
  updateEdgePicking();
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

void MainWindow::showContextMenu(const QPoint& globalPos) {
  QMenu m(this);
  if (!lastCommand_.isEmpty() && !active_)
    if (const Command* c = session_.commands().find(lastCommand_.toStdString())) {
      const QString id = lastCommand_;
      m.addAction(icon(qs(c->def().icon)), tr("Repeat %1").arg(qs(c->def().name)), this,
                  [this, id] { startCommand(id); });
      m.addSeparator();
    }
  m.addAction(undo_);
  m.addAction(redo_);
  m.addSeparator();
  QMenu* create = m.addMenu(tr("Create"));
  for (const Command* c : session_.commands().all())
    if (c->def().panel == "Create") {
      const QString id = qs(c->def().id);
      create->addAction(icon(qs(c->def().icon)), qs(c->def().name), this, [this, id] { startCommand(id); });
    }
  create->setEnabled(!active_);
  m.addSeparator();
  m.addAction(icon(QStringLiteral("fit")), tr("Fit"), viewport_, &Viewport::fitAll);
  m.addAction(icon(QStringLiteral("home")), tr("Home view"), viewport_, &Viewport::home);
  m.addAction(tr("Command search…"), this, [this] { focusSearch(); });
  m.exec(globalPos);
}

void MainWindow::showTimelineMenu(const QPoint& pos) {
  QListWidgetItem* it = timeline_->itemAt(pos);
  if (!it) return;
  const int id = it->data(kFeatureIdRole).toInt();
  const auto f = session_.document().feature(id);
  if (!f) return;
  QMenu m(this);
  m.addAction(tr("Edit Feature"), this, [this, id] { editFeature(id); });
  m.addAction(f->suppressed ? tr("Unsuppress Feature") : tr("Suppress Feature"), this, [this, id, f] {
    if (auto err = session_.setFeatureSuppressed(id, !f->suppressed); !err.empty())
      statusBar()->showMessage(qs(err), 5000);
  });
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
        sd.frame = sketch::planeFrame(rec.plane, rec.offset);
        const auto s = sketch::Sketch::fromJson(rec.data);
        sd.curves = sketch::curves(s, sd.frame, false);
        sd.construction = sketch::curves(s, sd.frame, true);
        sd.profiles = sketch::profiles(s, sd.frame);
      } catch (const sketch::SketchError&) {
        sd.visible = false;
      }
    }
    sketches.push_back(std::move(sd));
  }
  viewport_->setSketches(std::move(sketches));
  refreshBrowser(name);
  refreshTimeline();
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
  for (const char* o : {"O", "X", "Y", "Z", "XY", "XZ", "YZ"}) new QTreeWidgetItem(origin, {QString::fromLatin1(o)});

  const auto bodies = d.bodies();
  auto* bodiesItem = new QTreeWidgetItem(root, {tr("Bodies (%1)").arg(bodies.size())});
  bodiesItem->setIcon(0, icon(QStringLiteral("box")));
  for (const auto& b : bodies) {
    const QString n = qs(b.name);
    const double v = kernel::massProperties(b.shape).volume * 1000.0; // cm³ -> mm³
    auto* it = new QTreeWidgetItem(bodiesItem, {n});
    it->setToolTip(0, tr("Volume %1 mm³").arg(v, 0, 'g', 6));
    it->setData(0, kBodyRole, n);
    it->setFlags(it->flags() | Qt::ItemIsUserCheckable);
    it->setCheckState(0, viewport_->isBodyVisible(n) ? Qt::Checked : Qt::Unchecked);
  }

  const auto sketches = d.sketches();
  if (!sketches.empty()) {
    auto* sk = new QTreeWidgetItem(root, {tr("Sketches (%1)").arg(sketches.size())});
    sk->setIcon(0, icon(QStringLiteral("sketch")));
    for (const auto& s : sketches) {
      const QString n = qs(s.name);
      auto* it = new QTreeWidgetItem(sk, {n});
      it->setToolTip(0, tr("Double-click to edit"));
      it->setData(0, kSketchRole, n);
      it->setFlags(it->flags() | Qt::ItemIsUserCheckable);
      it->setCheckState(0, sketchVisible(s.name) ? Qt::Checked : Qt::Unchecked);
    }
    sk->setExpanded(true);
  }

  auto* params = new QTreeWidgetItem(root, {tr("User Parameters")});
  params->setIcon(0, icon(QStringLiteral("parameters")));
  for (const auto& p : d.userParameters()) new QTreeWidgetItem(params, {qs(p.name + " = " + p.expression)});

  root->setExpanded(true);
  bodiesItem->setExpanded(true);
  params->setExpanded(true);
}

void MainWindow::refreshTimeline() {
  timeline_->clear();
  for (const auto& f : session_.document().features()) {
    auto* it = new QListWidgetItem(icon(commandIcon(session_, f.commandId)), QString());
    it->setData(kFeatureIdRole, f.id);
    it->setData(Qt::AccessibleTextRole, qs(f.name));
    QString tip = QStringLiteral("<b>%1</b>").arg(qs(f.name));
    if (f.suppressed) {
      tip += tr("<br>Suppressed");
      it->setForeground(Qt::gray);
      it->setIcon(QIcon(it->icon().pixmap(28, 28, QIcon::Disabled)));
    }
    if (!f.error.empty()) {
      tip += QStringLiteral("<br><span style='color:#c0392b'>%1</span>").arg(qs(f.error).toHtmlEscaped());
      it->setBackground(themeColors().errorBackground);
    }
    tip += tr("<br><i>Double-click to edit</i>");
    it->setToolTip(tip);
    timeline_->addItem(it);
  }
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

bool MainWindow::saveAs() {
  QString path = QFileDialog::getSaveFileName(this, tr("Save Design"), QString(), kFilter);
  if (path.isEmpty()) return false;
  if (!path.endsWith(QStringLiteral(".tsr"), Qt::CaseInsensitive)) path += QStringLiteral(".tsr");
  return saveTo(path);
}

bool MainWindow::saveTo(const QString& path) {
  try {
    session_.save(path.toStdString());
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
