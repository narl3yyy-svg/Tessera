#include "MainWindow.h"
#include "CommandDialog.h"

#include "tsr/kernel/Kernel.h"

#include <QCloseEvent>
#include <QDockWidget>
#include <QFileDialog>
#include <QFileInfo>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>
#include <QTabWidget>
#include <QToolBar>
#include <QToolButton>
#include <QTreeWidget>

#include <algorithm>
#include <map>
#include <vector>

namespace tsr::app {

namespace {
const QString kFilter = QStringLiteral("Tessera documents (*.tsr)");
}

MainWindow::MainWindow(doc::Session& session, api::PythonHost& python, QWidget* parent)
    : QMainWindow(parent), session_(session), python_(python) {
  setObjectName(QStringLiteral("MainWindow"));
  resize(1280, 800);

  buildMenus();

  ribbon_ = new QTabWidget;
  ribbon_->setObjectName(QStringLiteral("ribbon"));
  ribbon_->setDocumentMode(true);
  buildRibbon();
  // P0 ribbon: a fixed top toolbar holding the tab widget. KDDockWidgets
  // replaces this later (SPEC/DIVERGENCES.md, P0-2).
  auto* ribbonBar = new QToolBar(tr("Ribbon"));
  ribbonBar->setObjectName(QStringLiteral("ribbonBar"));
  ribbonBar->setMovable(false);
  ribbonBar->setFloatable(false);
  ribbonBar->addWidget(ribbon_);
  addToolBar(Qt::TopToolBarArea, ribbonBar);

  browser_ = new QTreeWidget;
  browser_->setObjectName(QStringLiteral("browser"));
  browser_->setHeaderHidden(true);
  browser_->setAccessibleName(tr("Browser"));
  auto* dock = new QDockWidget(tr("Browser"));
  dock->setObjectName(QStringLiteral("browserDock"));
  dock->setWidget(browser_);
  addDockWidget(Qt::LeftDockWidgetArea, dock);

  // P0 has no 3D viewport yet (tsr-view lands with P2).
  auto* placeholder = new QLabel(tr("Viewport"));
  placeholder->setAlignment(Qt::AlignCenter);
  placeholder->setEnabled(false);
  setCentralWidget(placeholder);

  listener_ = session_.addListener([this] { refresh(); });
  refresh();
}

MainWindow::~MainWindow() { session_.removeListener(listener_); }

void MainWindow::buildMenus() {
  QMenu* file = menuBar()->addMenu(tr("&File"));
  file->addAction(tr("&New Design"), QKeySequence::New, this, [this] {
    if (maybeSave()) session_.newDocument();
  });
  file->addAction(tr("&Open…"), QKeySequence::Open, this, [this] { openFile(); });
  file->addAction(tr("&Save"), QKeySequence::Save, this, [this] {
    if (session_.path()) saveTo(QString::fromStdString(session_.path()->string()));
    else saveAs();
  });
  file->addAction(tr("Save &As…"), QKeySequence::SaveAs, this, [this] { saveAs(); });
  file->addSeparator();
  file->addAction(tr("&Run Script…"), this, [this] { runScript(); });
  file->addSeparator();
  file->addAction(tr("&Quit"), QKeySequence::Quit, this, &QWidget::close);

  QMenu* edit = menuBar()->addMenu(tr("&Edit"));
  undo_ = edit->addAction(tr("&Undo"), QKeySequence::Undo, this, [this] { session_.undo(); });
  redo_ = edit->addAction(tr("&Redo"), QKeySequence::Redo, this, [this] { session_.redo(); });
}

void MainWindow::buildRibbon() {
  // tab -> panel -> commands, each in first-registered order.
  std::vector<std::string> tabs;
  std::map<std::string, std::vector<std::string>> panels;
  std::map<std::pair<std::string, std::string>, std::vector<const Command*>> cmds;
  for (const Command* c : session_.commands().all()) {
    const CommandDef& d = c->def();
    if (!panels.count(d.tab)) tabs.push_back(d.tab);
    auto& ps = panels[d.tab];
    if (std::find(ps.begin(), ps.end(), d.panel) == ps.end()) ps.push_back(d.panel);
    cmds[{d.tab, d.panel}].push_back(c);
  }

  for (const auto& tab : tabs) {
    auto* page = new QWidget;
    auto* row = new QHBoxLayout(page);
    row->setContentsMargins(4, 4, 4, 4);
    for (const auto& panel : panels[tab]) {
      auto* box = new QGroupBox(QString::fromStdString(panel));
      box->setObjectName(QString::fromStdString(tab + "." + panel));
      auto* buttons = new QHBoxLayout(box);
      for (const Command* c : cmds[{tab, panel}]) {
        const CommandDef& d = c->def();
        auto* b = new QToolButton;
        b->setObjectName(QString::fromStdString(d.id));
        b->setText(QString::fromStdString(d.name));
        b->setToolTip(QString::fromStdString(d.tooltip));
        b->setAccessibleName(QString::fromStdString(d.name));
        b->setToolButtonStyle(Qt::ToolButtonTextOnly); // icons are rebuilt from spec later
        const QString id = QString::fromStdString(d.id);
        connect(b, &QToolButton::clicked, this, [this, id] { startCommand(id); });
        buttons->addWidget(b);
      }
      row->addWidget(box);
    }
    row->addStretch();
    ribbon_->addTab(page, QString::fromStdString(tab));
  }
}

CommandDialog* MainWindow::startCommand(const QString& commandId) {
  if (session_.document().hasOpenTransaction()) {
    statusBar()->showMessage(tr("Finish the current command first."), 3000);
    return nullptr;
  }
  auto cmd = session_.begin(commandId.toStdString());
  if (!cmd) return nullptr;
  auto* dlg = new CommandDialog(session_, std::move(cmd), this);
  dlg->setAttribute(Qt::WA_DeleteOnClose);
  dlg->show();
  return dlg;
}

void MainWindow::refresh() {
  doc::Document& d = session_.document();
  const QString name = session_.path() ? QFileInfo(QString::fromStdString(session_.path()->string())).completeBaseName()
                                       : tr("Untitled");
  setWindowTitle(name + (d.isModified() ? QStringLiteral("*") : QString()) + QStringLiteral(" — Tessera"));
  undo_->setEnabled(d.canUndo());
  redo_->setEnabled(d.canRedo());

  browser_->clear();
  auto* root = new QTreeWidgetItem(browser_, {name});
  auto* params = new QTreeWidgetItem(root, {tr("User Parameters")});
  for (const auto& p : d.userParameters())
    new QTreeWidgetItem(params, {QString::fromStdString(p.name + " = " + p.expression)});
  auto* bodies = new QTreeWidgetItem(root, {tr("Bodies")});
  for (const auto& b : d.bodies()) {
    const double v = kernel::massProperties(b.shape).volume;
    new QTreeWidgetItem(bodies, {QString::fromStdString(b.name) +
                                 QStringLiteral("  (%1 cm³)").arg(v, 0, 'g', 6)});
  }
  browser_->expandAll();
}

bool MainWindow::maybeSave() {
  if (!session_.document().isModified()) return true;
  const auto r = QMessageBox::question(this, tr("Tessera"), tr("Save changes to this design?"),
                                       QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
  if (r == QMessageBox::Cancel) return false;
  if (r == QMessageBox::Discard) return true;
  return session_.path() ? saveTo(QString::fromStdString(session_.path()->string())) : saveAs();
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
  if (maybeSave()) e->accept();
  else e->ignore();
}

} // namespace tsr::app
