// MainWindow: tools that are not timeline features. INSPECT (Measure,
// Interference, Section Analysis, Center of Mass), INSERT, SELECT, the File
// menu's Export / 3D Print / Capture Image, Preferences, grid and units.
#include "CommandDialog.h"
#include "Icons.h"
#include "MainWindow.h"
#include "ParametersDialog.h"
#include "SketchEditor.h"
#include "Theme.h"
#include "Viewport.h"

#include "tsr/core/Units.h"
#include "tsr/doc/DocCommands.h"
#include "tsr/kernel/Io.h"
#include "tsr/kernel/Kernel.h"
#include "tsr/sketch/SketchGeometry.h"

#include <QCheckBox>
#include <QComboBox>
#include <QDialog>
#include <QDialogButtonBox>
#include <QDoubleSpinBox>
#include <QFileDialog>
#include <QFileInfo>
#include <QFormLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QMenu>
#include <QMessageBox>
#include <QPushButton>
#include <QSettings>
#include <QSlider>
#include <QSpinBox>
#include <QTimer>
#include <QStatusBar>
#include <QVBoxLayout>

#include <BRepAlgoAPI_Common.hxx>
#include <TopExp_Explorer.hxx>

#include <cmath>

namespace tsr::app {

namespace {
QString qs(const std::string& s) { return QString::fromStdString(s); }

QDialog* toolWindow(QWidget* parent, const QString& title) {
  auto* d = new QDialog(parent);
  d->setWindowTitle(title);
  d->setWindowFlag(Qt::Tool);
  d->setAttribute(Qt::WA_DeleteOnClose);
  return d;
}
} // namespace

Unit MainWindow::lengthUnit() const {
  return parseUnit(session_.document().lengthUnit()).value_or(Unit::Millimeter);
}

QString MainWindow::formatLength(double cm) const {
  const Unit u = lengthUnit();
  return QStringLiteral("%1 %2").arg(fromInternal(cm, u), 0, 'f', u == Unit::Inch ? 4 : 3).arg(qs(std::string(unitSymbol(u))));
}

// ---------------------------------------------------------------------------
// Ribbon entries that are not document commands. Planned ones are shown
// disabled so the layout matches the familiar one, with a note.

void MainWindow::buildUiCommands() {
  auto add = [this](const char* panel, const char* id, const char* name, const char* icon, const char* tip,
                    const char* shortcut, std::function<void()> run) {
    uiCommands_.push_back({"Solid", panel, id, name, tip, icon, shortcut, static_cast<bool>(run), std::move(run)});
  };
  auto planned = [&](const char* panel, const char* id, const char* name, const char* icon, const char* shortcut = "") {
    add(panel, id, name, icon, "Planned: see docs/ROADMAP.md.", shortcut, nullptr);
  };
  add("Modify", "ui.changeParameters", "Change Parameters", "parameters",
      "User parameters and every feature's values in one table; expressions such as width / 2 + 3 mm.", "",
      [this] { showParameters(); });
  planned("Assemble", "ui.asBuiltJoint", "As-Built Joint", "joint", "Shift+J");
  planned("Assemble", "ui.jointOrigin", "Joint Origin", "joint-origin");
  planned("Assemble", "ui.rigidGroup", "Rigid Group", "rigid");
  add("Assemble", "ui.driveJoints", "Drive Joints", "motion", "Moves a joint through its range; Play animates it.", "",
      [this] { driveJoints(); });
  planned("Assemble", "ui.motionLink", "Motion Link", "motion");
  planned("Configure", "ui.configure", "Configurations", "configure");
  add("Inspect", "ui.measure", "Measure", "measure", "Distance, angle, length, area and volume of picked items.", "I",
      [this] { openMeasure(); });
  add("Inspect", "ui.interference", "Interference", "interference", "Finds bodies that overlap.", "",
      [this] { checkInterference(); });
  add("Inspect", "ui.section", "Section Analysis", "section", "Cuts the view with a plane to look inside.", "",
      [this] { openSection(); });
  add("Inspect", "ui.centerOfMass", "Center of Mass", "com", "Shows the center of mass of the selected body.", "",
      [this] { showCenterOfMass(); });
  add("Inspect", "ui.zebra", "Zebra Analysis", "zebra", "Stripes that show how smoothly faces meet.", "",
      [this] { openAnalysis(0); });
  add("Inspect", "ui.draftAnalysis", "Draft Analysis", "draft",
      "Green: enough draft to release from a mould; yellow: not enough; red: undercut.", "", [this] { openAnalysis(1); });
  add("Inspect", "ui.curvatureMap", "Curvature Map Analysis", "curvature", "Colours faces by how curved they are.", "",
      [this] { openAnalysis(2); });
  add("Inspect", "ui.curvature", "Curvature Comb Analysis", "curvature", "Teeth along edges show their curvature.", "",
      [this] { openAnalysis(3); });
  add("Inspect", "ui.accessibility", "Accessibility Analysis", "accessibility",
      "Green: faces a tool from the chosen direction can reach; red: faces turned away.", "", [this] { openAnalysis(4); });
  add("Inspect", "ui.minimumRadius", "Minimum Radius Analysis", "min-radius",
      "Red where the surface curves tighter than a radius (a cutter that size cannot reach).", "", [this] { openAnalysis(5); });
  add("Inspect", "ui.isocurve", "Isocurve Analysis", "isocurve", "Shows the faces' surface lines (U and V).", "",
      [this] { openAnalysis(6); });
  add("Insert", "ui.insert", "Insert Mesh / CAD File", "insert", "Adds bodies from a STEP, IGES, STL or BREP file.", "",
      [this] { insertFile(); });
  add("Insert", "ui.insertDxf", "Insert DXF", "insert-2d", "A new sketch from a DXF drawing (lines, arcs, polylines, splines).",
      "", [this] { insertDxf(); });
  add("Insert", "ui.insertSvg", "Insert SVG", "insert-2d", "A new sketch from an SVG drawing (paths, shapes; curves exact).",
      "", [this] { insertDxf(true); });
  planned("Insert", "ui.canvas", "Canvas", "image");
  planned("Insert", "ui.decal", "Decal", "image");
  add("Select", "ui.select", "Select", "select",
      "Click a face or edge; drag a window (left to right) or crossing (right to left) box; click and hold for "
      "everything under the cursor (Select Other). Esc clears.", "",
      [this] { viewport_->setOrbitTool(false); viewport_->setPanTool(false); });
  add("Select", "ui.filterDefault", "No Selection Priority", "face", "The default: a click picks the face or edge under the cursor.", "",
      [this] { setSelectionFilter({TopAbs_FACE, TopAbs_EDGE}); });
  add("Select", "ui.filterBodies", "Select Body Priority", "body", "A click picks whole bodies.", "",
      [this] { setSelectionFilter({}); });
  add("Select", "ui.filterFaces", "Select Face Priority", "face", "A click picks faces only.", "",
      [this] { setSelectionFilter({TopAbs_FACE}); });
  add("Select", "ui.filterEdges", "Select Edge Priority", "edge", "A click picks edges only.", "",
      [this] { setSelectionFilter({TopAbs_EDGE}); });
  add("Select", "ui.filterVertices", "Select Vertex Priority", "vertex", "A click picks vertices only.", "",
      [this] { setSelectionFilter({TopAbs_VERTEX}); });
}

// Drive Joints: pick a joint, move it with the slider (live preview), Play
// sweeps it back and forth; OK keeps the position as one undo step.
void MainWindow::driveJoints() {
  if (editor_ || active_) {
    statusBar()->showMessage(tr("Finish the current command first."), 3000);
    return;
  }
  std::vector<doc::Feature> joints;
  for (const auto& f : session_.document().features())
    if (f.commandId == doc::kCmdJoint && !f.suppressed) joints.push_back(f);
  if (joints.empty()) {
    statusBar()->showMessage(tr("Drive Joints: there is no joint yet (Assemble > Joint)."), 4000);
    return;
  }
  auto* d = new QDialog(viewport_);
  d->setParent(viewport_, Qt::Widget);
  d->setProperty("panel", true);
  d->setAutoFillBackground(true);
  d->setObjectName(QStringLiteral("drivePanel"));
  d->setAttribute(Qt::WA_DeleteOnClose);
  auto* title = new QLabel(QStringLiteral("\u2014  ") + tr("DRIVE JOINTS"));
  title->setObjectName(QStringLiteral("panelTitle"));
  auto* jointBox = new QComboBox;
  jointBox->setObjectName(QStringLiteral("driveJoint"));
  for (const auto& j : joints) jointBox->addItem(qs(j.name), j.id);
  auto* slider = new QSlider(Qt::Horizontal);
  slider->setObjectName(QStringLiteral("driveSlider"));
  slider->setRange(-3600, 3600);   // tenths of a degree, or of a millimetre
  slider->setMinimumWidth(240);
  auto* value = new QLabel;
  auto* play = new QPushButton(tr("Play"));
  play->setObjectName(QStringLiteral("drivePlay"));
  play->setCheckable(true);
  auto* buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
  buttons->button(QDialogButtonBox::Ok)->setObjectName(QStringLiteral("driveOk"));
  auto* form = new QFormLayout;
  form->addRow(tr("Joint"), jointBox);
  form->addRow(tr("Motion"), slider);
  form->addRow(QString(), value);
  form->addRow(QString(), play);
  auto* lay = new QVBoxLayout(d);
  lay->setContentsMargins(10, 6, 10, 8);
  lay->addWidget(title);
  lay->addLayout(form);
  lay->addWidget(buttons);

  struct State {
    std::unique_ptr<CommandSession> edit;
    std::string input;   // "rotation" or "slide"
    double start = 0;
  };
  auto st = std::make_shared<State>();
  auto* timer = new QTimer(d);
  const Unit u = lengthUnit();
  auto begin = [this, st, jointBox, slider, value, u] {
    if (st->edit) st->edit->cancel();
    st->edit = session_.editFeature(jointBox->currentData().toInt());
    if (!st->edit) return;
    const auto& in = st->edit->inputs();
    const std::string type = std::get<std::string>(in.at("type"));
    st->input = type == "Slider" ? "slide" : "rotation";
    if (type == "Rigid") value->setText(tr("A rigid joint does not move."));
    st->start = std::get<double>(in.at(st->input));
    const QSignalBlocker b(slider);
    // Motion limits, when the joint has them, bound the slider.
    auto on = [&](const char* id) {
      const auto it = in.find(id);
      return it != in.end() && std::holds_alternative<bool>(it->second) && std::get<bool>(it->second);
    };
    auto val = [&](const char* id) {
      const auto it = in.find(id);
      return it != in.end() && std::holds_alternative<double>(it->second) ? std::get<double>(it->second) : 0.0;
    };
    auto tick = [&](double v) {
      return static_cast<int>(std::lround(st->input == "slide" ? fromInternal(v, u) * 10 : v * 1800.0 / 3.14159265358979323846));
    };
    if (st->input == "slide" && on("slideLimits")) slider->setRange(tick(val("slideMin")), tick(val("slideMax")));
    else if (st->input == "rotation" && on("rotationLimits")) slider->setRange(tick(val("rotationMin")), tick(val("rotationMax")));
    else slider->setRange(-3600, 3600);
    slider->setValue(static_cast<int>(std::lround(
        st->input == "slide" ? fromInternal(st->start, u) * 10 : st->start * 1800.0 / 3.14159265358979323846)));
  };
  auto apply = [this, st, slider, value, u] {
    if (!st->edit) return;
    const double v = st->input == "slide" ? toInternal(slider->value() / 10.0, u)
                                          : slider->value() / 10.0 * 3.14159265358979323846 / 180.0;
    value->setText(st->input == "slide" ? formatLength(v) : QStringLiteral("%1 deg").arg(slider->value() / 10.0, 0, 'f', 1));
    if (!st->edit->setInput(st->input, v).empty()) return;
    const std::string err = st->edit->preview();
    if (!err.empty()) statusBar()->showMessage(qs(err), 3000);
    session_.notifyChanged();
  };
  connect(jointBox, &QComboBox::currentIndexChanged, d, [begin, apply] {
    begin();
    apply();
  });
  connect(slider, &QSlider::valueChanged, d, apply);
  // Play: sweep forwards and back.
  auto step = std::make_shared<int>(30);
  connect(timer, &QTimer::timeout, d, [slider, step] {
    int v = slider->value() + *step;
    if (v > slider->maximum() || v < slider->minimum()) {
      *step = -*step;
      v = slider->value() + *step;
    }
    slider->setValue(v);
  });
  connect(play, &QPushButton::toggled, d, [timer, play](bool on) {
    play->setText(on ? QObject::tr("Stop") : QObject::tr("Play"));
    if (on) timer->start(40);
    else timer->stop();
  });
  connect(buttons, &QDialogButtonBox::accepted, d, [this, st, d] {
    if (st->edit) {
      const std::string err = st->edit->execute();
      if (!err.empty()) statusBar()->showMessage(qs(err), 5000);
      st->edit.reset();
    }
    d->accept();
  });
  connect(buttons, &QDialogButtonBox::rejected, d, &QDialog::reject);
  connect(d, &QDialog::finished, this, [this, st, timer, d] {
    timer->stop();
    if (st->edit) {
      st->edit->cancel();
      st->edit.reset();
    }
    d->hide();
    d->deleteLater();
    session_.notifyChanged();
  });
  begin();
  apply();
  d->show();
  placeDialog(d);
}

QDialog* MainWindow::openAnalysis(int kind) {
  if (editor_ || active_ || sectionPanel_) {
    statusBar()->showMessage(tr("Finish the current command first."), 3000);
    return nullptr;
  }
  if (analysisPanel_) analysisPanel_->reject();
  static const char* titles[] = {"ZEBRA ANALYSIS", "DRAFT ANALYSIS", "CURVATURE MAP ANALYSIS", "CURVATURE COMB ANALYSIS",
                                 "ACCESSIBILITY ANALYSIS", "MINIMUM RADIUS ANALYSIS", "ISOCURVE ANALYSIS"};
  auto* d = new QDialog(viewport_);
  d->setParent(viewport_, Qt::Widget);
  d->setProperty("panel", true);
  d->setAutoFillBackground(true);
  d->setObjectName(QStringLiteral("analysisPanel"));
  d->setAttribute(Qt::WA_DeleteOnClose);
  analysisPanel_ = d;
  auto* title = new QLabel(QStringLiteral("\u2014  ") + tr(titles[kind]));
  title->setObjectName(QStringLiteral("panelTitle"));
  auto* form = new QFormLayout;
  auto* lay = new QVBoxLayout(d);
  lay->setContentsMargins(10, 6, 10, 8);
  lay->addWidget(title);
  lay->addLayout(form);
  auto* buttons = new QDialogButtonBox(QDialogButtonBox::Ok);
  auto* remove = buttons->addButton(tr("Remove"), QDialogButtonBox::DestructiveRole);
  buttons->button(QDialogButtonBox::Ok)->setObjectName(QStringLiteral("analysisOk"));
  remove->setObjectName(QStringLiteral("analysisRemove"));

  AnalysisSettings base;
  if (kind == 0) {
    auto* stripes = new QSpinBox;
    stripes->setObjectName(QStringLiteral("zebraStripes"));
    stripes->setRange(2, 60);
    stripes->setValue(12);
    auto* dir = new QComboBox;
    dir->setObjectName(QStringLiteral("zebraDirection"));
    dir->addItems({tr("Horizontal"), tr("Vertical")});
    form->addRow(tr("Stripes"), stripes);
    form->addRow(tr("Direction"), dir);
    auto apply = [this, stripes, dir] {
      AnalysisSettings a;
      a.kind = AnalysisKind::Zebra;
      a.stripes = stripes->value();
      a.stripeAxis = dir->currentIndex() == 0 ? gp::DZ() : gp::DX();
      viewport_->setAnalysis(a);
    };
    connect(stripes, &QSpinBox::valueChanged, d, apply);
    connect(dir, &QComboBox::currentIndexChanged, d, apply);
    apply();
  } else if (kind == 1) {
    auto* plane = new QComboBox;
    plane->setObjectName(QStringLiteral("draftPlane"));
    plane->addItems({QStringLiteral("XY"), QStringLiteral("XZ"), QStringLiteral("YZ")});
    for (const auto& pl : session_.document().planes()) plane->addItem(qs(pl.name));
    auto* angle = new QDoubleSpinBox;
    angle->setObjectName(QStringLiteral("draftAngle"));
    angle->setRange(0, 45);
    angle->setDecimals(1);
    angle->setValue(1.0);
    angle->setSuffix(QStringLiteral(" deg"));
    auto* flip = new QCheckBox(tr("Flip pull direction"));
    form->addRow(tr("Pull direction"), plane);
    form->addRow(tr("Draft angle"), angle);
    form->addRow(QString(), flip);
    auto apply = [this, plane, angle, flip] {
      AnalysisSettings a;
      a.kind = AnalysisKind::Draft;
      try {
        gp_Dir n = session_.document().planeFrame(plane->currentText().toStdString()).Direction();
        if (flip->isChecked()) n.Reverse();
        a.pull = n;
      } catch (const std::exception&) {
      }
      a.draftAngle = angle->value() * 3.14159265358979323846 / 180.0;
      viewport_->setAnalysis(a);
    };
    connect(plane, &QComboBox::currentIndexChanged, d, apply);
    connect(angle, &QDoubleSpinBox::valueChanged, d, apply);
    connect(flip, &QCheckBox::toggled, d, apply);
    apply();
  } else if (kind == 2) {
    auto* scale = new QSlider(Qt::Horizontal);
    scale->setObjectName(QStringLiteral("curvatureScale"));
    scale->setRange(1, 100);
    scale->setValue(20);
    scale->setMinimumWidth(200);
    form->addRow(tr("Scale"), scale);
    auto* legend = new QLabel(tr("<span style='color:#3a8cff'>concave</span> \u2013 "
                                 "<span style='color:#40c050'>flat</span> \u2013 <span style='color:#ff5040'>convex</span>"));
    form->addRow(QString(), legend);
    auto apply = [this, scale] {
      AnalysisSettings a;
      a.kind = AnalysisKind::CurvatureMap;
      a.curvatureScale = scale->value() / 10.0;
      viewport_->setAnalysis(a);
    };
    connect(scale, &QSlider::valueChanged, d, apply);
    apply();
  } else if (kind == 4) {
    auto* plane = new QComboBox;
    plane->setObjectName(QStringLiteral("accessPlane"));
    plane->addItems({QStringLiteral("XY"), QStringLiteral("XZ"), QStringLiteral("YZ")});
    for (const auto& pl : session_.document().planes()) plane->addItem(qs(pl.name));
    auto* flip = new QCheckBox(tr("Flip direction"));
    form->addRow(tr("Direction (normal of)"), plane);
    form->addRow(QString(), flip);
    auto apply = [this, plane, flip] {
      AnalysisSettings a;
      a.kind = AnalysisKind::Accessibility;
      try {
        gp_Dir n = session_.document().planeFrame(plane->currentText().toStdString()).Direction();
        if (flip->isChecked()) n.Reverse();
        a.pull = n;
      } catch (const std::exception&) {
      }
      viewport_->setAnalysis(a);
    };
    connect(plane, &QComboBox::currentIndexChanged, d, apply);
    connect(flip, &QCheckBox::toggled, d, apply);
    apply();
  } else if (kind == 5) {
    auto* radius = new QDoubleSpinBox;
    radius->setObjectName(QStringLiteral("minRadius"));
    const Unit u = lengthUnit();
    radius->setRange(0.001, 1000);
    radius->setDecimals(3);
    radius->setValue(fromInternal(0.1, u));
    radius->setSuffix(QStringLiteral(" ") + qs(session_.document().lengthUnit()));
    form->addRow(tr("Minimum radius"), radius);
    auto apply = [this, radius, u] {
      AnalysisSettings a;
      a.kind = AnalysisKind::MinimumRadius;
      a.minRadius = toInternal(radius->value(), u);
      viewport_->setAnalysis(a);
    };
    connect(radius, &QDoubleSpinBox::valueChanged, d, apply);
    apply();
  } else if (kind == 6) {
    auto* lines = new QSpinBox;
    lines->setObjectName(QStringLiteral("isoLines"));
    lines->setRange(1, 50);
    lines->setValue(8);
    form->addRow(tr("Lines each way"), lines);
    auto apply = [this, lines] {
      AnalysisSettings a;
      a.kind = AnalysisKind::Isocurve;
      a.isoLines = lines->value();
      viewport_->setAnalysis(a);
    };
    connect(lines, &QSpinBox::valueChanged, d, apply);
    apply();
  } else {
    auto* info = new QLabel(tr("Click edges in the canvas."));
    info->setObjectName(QStringLiteral("combInfo"));
    auto* scale = new QSlider(Qt::Horizontal);
    scale->setObjectName(QStringLiteral("combScale"));
    scale->setRange(1, 100);
    scale->setValue(20);
    scale->setMinimumWidth(200);
    auto* clear = new QPushButton(tr("Clear"));
    form->addRow(tr("Edges"), info);
    form->addRow(tr("Comb scale"), scale);
    form->addRow(QString(), clear);
    combEdges_.clear();
    combPicking_ = true;
    viewport_->setSubShapePicking({TopAbs_EDGE});
    auto redraw = [this, scale, info] {
      combScale_ = scale->value() / 10.0;
      viewport_->setCurvatureComb(combEdges_, combScale_);
      info->setText(combEdges_.empty() ? tr("Click edges in the canvas.") : tr("%n edge(s)", nullptr, static_cast<int>(combEdges_.size())));
    };
    connect(scale, &QSlider::valueChanged, d, redraw);
    connect(clear, &QPushButton::clicked, d, [this, redraw] {
      combEdges_.clear();
      redraw();
    });
    connect(this, &MainWindow::combEdgesChanged, d, redraw);
  }
  lay->addWidget(buttons);
  connect(buttons, &QDialogButtonBox::accepted, d, &QDialog::accept);   // keeps the analysis shown
  connect(remove, &QPushButton::clicked, d, [this, d] {
    viewport_->setAnalysis({});
    viewport_->setCurvatureComb({}, 1.0);
    combEdges_.clear();
    d->reject();
  });
  connect(d, &QDialog::finished, this, [this, d] {
    if (combPicking_) {
      combPicking_ = false;
      viewport_->setSubShapePicking({});
    }
    analysisPanel_ = nullptr;
    d->hide();
    d->deleteLater();
  });
  d->show();
  placeDialog(d);
  return d;
}

ParametersDialog* MainWindow::showParameters() {
  if (!parameters_) parameters_ = new ParametersDialog(session_, this);
  parameters_->show();
  parameters_->raise();
  parameters_->activateWindow();
  return parameters_;
}

void MainWindow::setSelectionFilter(const std::vector<TopAbs_ShapeEnum>& types) {
  viewport_->setSelectionFilter(types);
  const QString what = types.empty()            ? tr("Body priority")
                        : types.size() > 1         ? tr("No priority (faces and edges)")
                        : types[0] == TopAbs_FACE  ? tr("Face priority")
                        : types[0] == TopAbs_EDGE  ? tr("Edge priority")
                                                   : tr("Vertex priority");
  statusBar()->showMessage(tr("Selection: %1.").arg(what), 3000);
}

// ---------------------------------------------------------------------------
// Units (Document Settings)

void MainWindow::chooseUnits(const QPoint& globalPos) {
  QMenu m(this);
  const QString current = qs(session_.document().lengthUnit());
  for (const char* u : {"mm", "in", "cm", "m"}) {
    QAction* a = m.addAction(QString::fromLatin1(u));
    a->setCheckable(true);
    a->setChecked(current == QLatin1String(u));
  }
  QAction* picked = m.exec(globalPos);
  if (!picked || picked->text() == current) return;
  if (auto err = session_.run(doc::kCmdUnits, {{"unit", picked->text().toStdString()}}); !err.empty())
    statusBar()->showMessage(qs(err), 5000);
}

// ---------------------------------------------------------------------------
// File: Export, 3D Print, Insert, Capture Image

void MainWindow::exportDesign() {
  auto* d = new QDialog(this);
  d->setWindowTitle(tr("Export"));
  d->setAttribute(Qt::WA_DeleteOnClose);
  d->setMinimumWidth(520);
  auto* lay = new QVBoxLayout(d);
  auto* name = new QLineEdit(session_.path() ? QFileInfo(qs(session_.path()->string())).completeBaseName() : tr("Untitled"));
  auto* types = new QListWidget;
  types->addItem(tr("Tessera Design (*.tsr)"));
  for (const auto& f : kernel::fileFormats())
    types->addItem(QStringLiteral("%1 (%2)").arg(QString::fromLatin1(f.name), QString::fromLatin1(f.extensions)));
  types->setCurrentRow(2);   // STEP, the usual exchange format
  types->setMaximumHeight(170);
  auto* refinement = new QComboBox;
  refinement->addItems({tr("Low"), tr("Medium"), tr("High")});
  refinement->setCurrentIndex(1);
  auto* refinementLabel = new QLabel(tr("Mesh refinement:"));
  auto updateRefinement = [=] {
    const int row = types->currentRow();
    const bool mesh = row >= 1 && (kernel::fileFormats()[row - 1].format == kernel::FileFormat::Stl ||
                                   kernel::fileFormats()[row - 1].format == kernel::FileFormat::Obj ||
                                   kernel::fileFormats()[row - 1].format == kernel::FileFormat::ThreeMF);
    refinement->setVisible(mesh);
    refinementLabel->setVisible(mesh);
  };
  connect(types, &QListWidget::currentRowChanged, d, updateRefinement);
  lay->addWidget(new QLabel(tr("Name:")));
  lay->addWidget(name);
  lay->addWidget(new QLabel(tr("Type:")));
  lay->addWidget(types);
  auto* row = new QHBoxLayout;
  row->addWidget(refinementLabel);
  row->addWidget(refinement);
  row->addStretch();
  lay->addLayout(row);
  auto* buttons = new QDialogButtonBox;
  buttons->addButton(tr("Export"), QDialogButtonBox::AcceptRole);
  buttons->addButton(QDialogButtonBox::Cancel);
  lay->addWidget(buttons);
  updateRefinement();
  connect(buttons, &QDialogButtonBox::rejected, d, &QDialog::reject);
  connect(buttons, &QDialogButtonBox::accepted, d, [=, this] {
    const int rowIndex = types->currentRow();
    const QString ext = rowIndex == 0 ? QStringLiteral("tsr")
                                      : QString::fromLatin1(kernel::fileFormats()[rowIndex - 1].extensions).section(QLatin1Char(' '), 0, 0).mid(2);
    QString path = QFileDialog::getSaveFileName(this, tr("Export"), name->text() + QLatin1Char('.') + ext,
                                                types->currentItem()->text());
    if (path.isEmpty()) return;
    if (!path.endsWith(QLatin1Char('.') + ext, Qt::CaseInsensitive)) path += QLatin1Char('.') + ext;
    try {
      if (rowIndex == 0) {
        session_.document().save(path.toStdString());
      } else {
        std::vector<kernel::NamedShape> bodies;
        for (const auto& b : session_.document().bodies())
          if (viewport_->isBodyVisible(qs(b.name))) bodies.emplace_back(b.name, b.shape);
        kernel::exportShapes(path.toStdString(), bodies, kernel::fileFormats()[rowIndex - 1].format,
                             refinement->currentIndex());
      }
      statusBar()->showMessage(tr("Exported %1").arg(path), 5000);
      d->accept();
    } catch (const std::exception& e) {
      QMessageBox::warning(this, tr("Export"), qs(e.what()));
    }
  });
  d->show();
}

void MainWindow::print3d() {
  const auto bodies = session_.document().bodies();
  if (bodies.empty()) {
    statusBar()->showMessage(tr("There is no body to print."), 4000);
    return;
  }
  QStringList names;
  for (const auto& b : bodies) names << qs(b.name);
  bool ok = false;
  const QString which = QInputDialog::getItem(this, tr("3D Print"), tr("Body (exported in mm):"),
                                              QStringList{tr("All visible bodies")} + names, 0, false, &ok);
  if (!ok) return;
  QString path = QFileDialog::getSaveFileName(this, tr("3D Print"), which.startsWith(tr("All")) ? tr("print.3mf") : which + QStringLiteral(".3mf"),
                                              tr("3MF (*.3mf);;STL (*.stl)"));
  if (path.isEmpty()) return;
  std::vector<kernel::NamedShape> out;
  for (const auto& b : bodies)
    if ((which.startsWith(tr("All")) && viewport_->isBodyVisible(qs(b.name))) || qs(b.name) == which)
      out.emplace_back(b.name, b.shape);
  try {
    const auto fmt = kernel::formatForPath(path.toStdString());
    kernel::exportShapes(path.toStdString(), out, fmt ? *fmt : kernel::FileFormat::ThreeMF, 2);
    statusBar()->showMessage(tr("Saved %1 for printing").arg(path), 5000);
  } catch (const std::exception& e) {
    QMessageBox::warning(this, tr("3D Print"), qs(e.what()));
  }
}

void MainWindow::insertFile() {
  if (editor_ || active_) return;
  const QString path = QFileDialog::getOpenFileName(this, tr("Insert Mesh / CAD File"), QString(),
                                                    tr("CAD and mesh files (*.step *.stp *.iges *.igs *.stl *.brep)"));
  if (path.isEmpty()) return;
  try {
    const TopoDS_Shape s = kernel::importShape(path.toStdString());
    if (auto err = session_.run(doc::kCmdInsert, {{"source", path.toStdString()}, {"brep", kernel::toBrep(s)}});
        !err.empty())
      throw std::runtime_error(err);
    viewport_->fitAll();
    statusBar()->showMessage(tr("Inserted %1").arg(QFileInfo(path).fileName()), 5000);
  } catch (const std::exception& e) {
    QMessageBox::warning(this, tr("Insert"), qs(e.what()));
  }
}

void MainWindow::captureImage() {
  const QString path = QFileDialog::getSaveFileName(this, tr("Capture Image"), tr("capture.png"), tr("PNG image (*.png)"));
  if (path.isEmpty()) return;
  if (viewport_->capture().save(path)) statusBar()->showMessage(tr("Saved %1").arg(path), 4000);
  else QMessageBox::warning(this, tr("Capture Image"), tr("Could not save the image."));
}

// ---------------------------------------------------------------------------
// Preferences (navigation, camera, theme, grid)

void MainWindow::applyPreferences() {
  QSettings s;
  const auto preset = static_cast<Viewport::NavPreset>(s.value(QStringLiteral("nav/preset"), 0).toInt());
  viewport_->setNavigation(preset, s.value(QStringLiteral("nav/reverseZoom"), false).toBool(),
                           s.value(QStringLiteral("nav/constrainedOrbit"), false).toBool(),
                           s.value(QStringLiteral("nav/perspective"), false).toBool());
  viewport_->setGridSpacing(s.value(QStringLiteral("grid/spacing"), 1.0).toDouble());
  viewport_->setGridSnap(s.value(QStringLiteral("grid/snap"), true).toBool());
  viewport_->setAdaptiveGrid(s.value(QStringLiteral("grid/adaptive"), true).toBool());
}

void MainWindow::showPreferences() {
  QDialog d(this);
  d.setWindowTitle(tr("Preferences"));
  d.setMinimumWidth(460);
  QSettings s;
  auto* lay = new QVBoxLayout(&d);

  auto* nav = new QGroupBox(tr("Navigation"));
  auto* nf = new QFormLayout(nav);
  auto* preset = new QComboBox;
  preset->addItems({tr("Fusion style (middle pan, Shift+middle orbit)"), tr("SolidWorks style (middle orbit, Ctrl+middle pan)"),
                    tr("Tinkercad style (right orbit, middle pan)")});
  preset->setCurrentIndex(s.value(QStringLiteral("nav/preset"), 0).toInt());
  auto* reverse = new QCheckBox(tr("Reverse zoom direction"));
  reverse->setChecked(s.value(QStringLiteral("nav/reverseZoom"), false).toBool());
  auto* orbit = new QComboBox;
  orbit->addItems({tr("Free orbit"), tr("Constrained orbit (Z stays up)")});
  orbit->setCurrentIndex(s.value(QStringLiteral("nav/constrainedOrbit"), false).toBool() ? 1 : 0);
  auto* camera = new QComboBox;
  camera->addItems({tr("Orthographic"), tr("Perspective")});
  camera->setCurrentIndex(s.value(QStringLiteral("nav/perspective"), false).toBool() ? 1 : 0);
  nf->addRow(tr("Pan, Zoom, Orbit shortcuts"), preset);
  nf->addRow(QString(), reverse);
  nf->addRow(tr("Orbit type"), orbit);
  nf->addRow(tr("Default camera"), camera);
  lay->addWidget(nav);

  auto* gen = new QGroupBox(tr("General"));
  auto* gf = new QFormLayout(gen);
  auto* theme = new QComboBox;
  theme->addItems({tr("Dark"), tr("Light")});
  theme->setCurrentIndex(Theme::instance().dark() ? 0 : 1);
  auto* units = new QComboBox;
  units->addItems({QStringLiteral("mm"), QStringLiteral("in")});
  units->setCurrentText(s.value(QStringLiteral("doc/defaultUnits"), QStringLiteral("mm")).toString());
  gf->addRow(tr("Theme"), theme);
  gf->addRow(tr("Default units for new designs"), units);
  lay->addWidget(gen);

  auto* buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
  lay->addWidget(buttons);
  connect(buttons, &QDialogButtonBox::accepted, &d, &QDialog::accept);
  connect(buttons, &QDialogButtonBox::rejected, &d, &QDialog::reject);
  if (d.exec() != QDialog::Accepted) return;
  s.setValue(QStringLiteral("nav/preset"), preset->currentIndex());
  s.setValue(QStringLiteral("nav/reverseZoom"), reverse->isChecked());
  s.setValue(QStringLiteral("nav/constrainedOrbit"), orbit->currentIndex() == 1);
  s.setValue(QStringLiteral("nav/perspective"), camera->currentIndex() == 1);
  s.setValue(QStringLiteral("doc/defaultUnits"), units->currentText());
  Theme::instance().apply(theme->currentIndex() == 0 ? Theme::Mode::Dark : Theme::Mode::Light);
  applyPreferences();
}

void MainWindow::gridSettings() {
  bool ok = false;
  // Adaptive (follows the zoom, the default) or a fixed spacing.
  const QStringList kinds{tr("Adaptive"), tr("Fixed")};
  const QString kind = QInputDialog::getItem(this, tr("Grid Settings"), tr("Grid:"), kinds,
                                             viewport_->adaptiveGrid() ? 0 : 1, false, &ok);
  if (!ok) return;
  const bool adaptive = kind == kinds[0];
  QSettings().setValue(QStringLiteral("grid/adaptive"), adaptive);
  viewport_->setAdaptiveGrid(adaptive);
  if (adaptive) return;
  const Unit u = lengthUnit();
  const double current = fromInternal(viewport_->fixedGridSpacing(), u);
  const double v = QInputDialog::getDouble(this, tr("Grid Settings"), tr("Grid spacing (%1):").arg(qs(std::string(unitSymbol(u)))),
                                           current, 0.001, 100000, u == Unit::Inch ? 4 : 3, &ok);
  if (!ok) return;
  QSettings().setValue(QStringLiteral("grid/spacing"), toInternal(v, u));
  viewport_->setGridSpacing(toInternal(v, u));
}

// ---------------------------------------------------------------------------
// INSPECT: Measure

void MainWindow::openMeasure() {
  if (measure_) {
    measure_->raise();
    return;
  }
  if (editor_) return;
  auto* d = toolWindow(this, tr("MEASURE"));
  measure_ = d;
  auto* lay = new QVBoxLayout(d);
  auto* filter = new QComboBox;
  filter->addItems({tr("Faces, edges, vertices"), tr("Bodies")});
  auto* form = new QFormLayout;
  form->addRow(tr("Selection filter"), filter);
  lay->addLayout(form);
  measureLabel_ = new QLabel(tr("Click one or two items in the canvas."));
  measureLabel_->setTextFormat(Qt::RichText);
  measureLabel_->setMinimumWidth(280);
  measureLabel_->setTextInteractionFlags(Qt::TextSelectableByMouse);
  lay->addWidget(measureLabel_);
  auto* buttons = new QDialogButtonBox;
  auto* clear = buttons->addButton(tr("Clear"), QDialogButtonBox::ResetRole);
  buttons->addButton(QDialogButtonBox::Close);
  lay->addWidget(buttons);
  auto applyFilter = [this, filter] {
    measurePicks_.clear();
    viewport_->setSubShapePicking(filter->currentIndex() == 0
                                      ? std::vector<TopAbs_ShapeEnum>{TopAbs_VERTEX, TopAbs_EDGE, TopAbs_FACE}
                                      : std::vector<TopAbs_ShapeEnum>{});
    updateMeasure();
  };
  connect(filter, &QComboBox::currentIndexChanged, d, applyFilter);
  connect(clear, &QPushButton::clicked, d, [this] {
    measurePicks_.clear();
    updateMeasure();
  });
  connect(buttons, &QDialogButtonBox::rejected, d, &QDialog::close);
  connect(d, &QObject::destroyed, this, [this] {
    measurePicks_.clear();
    viewport_->setSubShapePicking({});
    viewport_->setMeasureLine(false);
    viewport_->setPickedShapes({});
  });
  d->show();
  placeDialog(d);
  applyFilter();
}

void MainWindow::measurePick(const TopoDS_Shape& s) {
  if (measurePicks_.size() >= 2) measurePicks_.clear();
  measurePicks_.push_back(s);
  updateMeasure();
}

void MainWindow::updateMeasure() {
  if (!measure_ || !measureLabel_) return;
  viewport_->setPickedShapes(measurePicks_);
  if (measurePicks_.empty()) {
    measureLabel_->setText(tr("Click one or two items in the canvas."));
    viewport_->setMeasureLine(false);
    return;
  }
  kernel::Measurement m;
  try {
    m = kernel::measure(measurePicks_);
  } catch (const std::exception& e) {
    measureLabel_->setText(qs(e.what()));
    return;
  }
  const Unit u = lengthUnit();
  const double f = fromInternal(1.0, u);
  const QString sym = qs(std::string(unitSymbol(u)));
  QString html = QStringLiteral("<table cellspacing='4'>");
  QString lineLabel;
  for (const auto& v : m.values) {
    QString text;
    switch (v.kind) {
      case kernel::Measurement::Kind::Length: text = QStringLiteral("%1 %2").arg(v.value * f, 0, 'f', u == Unit::Inch ? 4 : 3).arg(sym); break;
      case kernel::Measurement::Kind::Area: text = QStringLiteral("%1 %2²").arg(v.value * f * f, 0, 'f', 3).arg(sym); break;
      case kernel::Measurement::Kind::Volume: text = QStringLiteral("%1 %2³").arg(v.value * f * f * f, 0, 'f', 3).arg(sym); break;
      case kernel::Measurement::Kind::Angle: text = QStringLiteral("%1°").arg(v.value * 180.0 / M_PI, 0, 'f', 2); break;
    }
    if (v.name == "Distance") lineLabel = text;
    html += QStringLiteral("<tr><td><b>%1</b></td><td align='right'>%2</td></tr>").arg(qs(v.name), text);
  }
  html += QStringLiteral("</table>");
  measureLabel_->setText(html);
  if (m.hasLine)
    viewport_->setMeasureLine(true, gp_Pnt(m.from.x, m.from.y, m.from.z), gp_Pnt(m.to.x, m.to.y, m.to.z), lineLabel);
  else
    viewport_->setMeasureLine(false);
  measure_->adjustSize();
}

// ---------------------------------------------------------------------------
// INSPECT: Section Analysis, Center of Mass, Interference

gp_Ax3 MainWindow::sectionFrame() const {
  gp_Ax3 f;
  try {
    f = session_.document().planeFrame(section_.plane.toStdString());
  } catch (const std::exception&) {
    f = sketch::planeFrame("XZ");
  }
  if (std::abs(section_.angle) > 1e-12) f.Rotate(gp_Ax1(f.Location(), f.XDirection()), section_.angle);
  f.Translate(gp_Vec(f.Direction()) * section_.offset);
  return f;
}

gp_Pln MainWindow::sectionPlane() const {
  const gp_Ax3 f = sectionFrame();
  gp_Dir n = f.Direction();
  if (section_.flip) n.Reverse();
  return gp_Pln(f.Location(), n);
}

// The section's drag arrow: on the plane where it crosses the middle of the
// model, along the plane's normal (before the offset).
void MainWindow::updateSectionArrow() {
  if (!sectionPanel_ || sectionPicking_ || !section_.active) return;
  const gp_Ax3 f = sectionFrame();
  const gp_Dir n = f.Direction();
  gp_Pnt c = f.Location();
  bool any = false;
  double x0 = 1e300, y0 = 1e300, z0 = 1e300, x1 = -1e300, y1 = -1e300, z1 = -1e300;
  for (const auto& b : session_.document().bodies()) {
    const auto bb = kernel::boundingBox(b.shape);
    x0 = std::min(x0, bb.min.x), y0 = std::min(y0, bb.min.y), z0 = std::min(z0, bb.min.z);
    x1 = std::max(x1, bb.max.x), y1 = std::max(y1, bb.max.y), z1 = std::max(z1, bb.max.z);
    any = true;
  }
  if (any) {
    const gp_Pnt mid((x0 + x1) / 2, (y0 + y1) / 2, (z0 + z1) / 2);
    c = mid.Translated(-gp_Vec(n) * gp_Vec(f.Location(), mid).Dot(gp_Vec(n)));   // onto the section plane
  }
  const gp_Pnt base = c.Translated(-gp_Vec(n) * section_.offset);
  viewport_->setDragArrow(base, n, section_.offset, formatLength(section_.offset));
}

void MainWindow::applySection() {
  viewport_->setSection(section_.active && section_.visible, sectionPlane());
  refresh();
}

void MainWindow::openSection() {
  if (editor_ || active_ || sectionPanel_) return;
  const auto saved = section_;
  // Like the familiar tool: first click a face or plane, then drag the arrow.
  auto* d = new QDialog(viewport_);
  d->setParent(viewport_, Qt::Widget);
  d->setProperty("panel", true);
  d->setAutoFillBackground(true);
  d->setObjectName(QStringLiteral("sectionPanel"));
  d->setAttribute(Qt::WA_DeleteOnClose);
  sectionPanel_ = d;
  sectionPicking_ = true;
  auto* title = new QLabel(QStringLiteral("\u2014  ") + tr("SECTION ANALYSIS"));
  title->setObjectName(QStringLiteral("panelTitle"));
  auto* form = new QFormLayout;
  auto* pickRow = new QWidget;
  auto* pickLay = new QHBoxLayout(pickRow);
  pickLay->setContentsMargins(0, 0, 0, 0);
  auto* pickLabel = new QLabel(tr("Click a face or plane"));
  auto* repick = new QPushButton(tr("Select"));
  repick->setObjectName(QStringLiteral("sectionSelect"));
  pickLay->addWidget(pickLabel, 1);
  pickLay->addWidget(repick);
  auto* plane = new QComboBox;
  plane->setObjectName(QStringLiteral("sectionPlane"));
  plane->addItems({QStringLiteral("XY"), QStringLiteral("XZ"), QStringLiteral("YZ")});
  for (const auto& pl : session_.document().planes()) plane->addItem(qs(pl.name));
  plane->setVisible(false);
  const Unit u = lengthUnit();
  auto* offset = new QDoubleSpinBox;
  offset->setRange(-1e6, 1e6);
  offset->setDecimals(u == Unit::Inch ? 4 : 2);
  offset->setSuffix(QStringLiteral(" ") + qs(std::string(unitSymbol(u))));
  offset->setValue(fromInternal(section_.offset, u));
  // Slider across the design's extent along the plane normal.
  double lo = -10, hi = 10;
  for (const auto& b : session_.document().bodies()) {
    const auto bb = kernel::boundingBox(b.shape);
    lo = std::min({lo, bb.min.x, bb.min.y, bb.min.z});
    hi = std::max({hi, bb.max.x, bb.max.y, bb.max.z});
  }
  auto* slider = new QSlider(Qt::Horizontal);
  slider->setRange(static_cast<int>(lo * 100), static_cast<int>(hi * 100));
  slider->setValue(static_cast<int>(section_.offset * 100));
  auto* flip = new QCheckBox(tr("Flip side"));
  flip->setChecked(section_.flip);
  offset->setObjectName(QStringLiteral("sectionDistance"));
  auto* angle = new QDoubleSpinBox;
  angle->setObjectName(QStringLiteral("sectionAngle"));
  angle->setRange(-360, 360);
  angle->setDecimals(1);
  angle->setSuffix(QStringLiteral(" deg"));
  angle->setValue(section_.angle * 180.0 / 3.14159265358979323846);
  form->addRow(tr("Face/Plane"), pickRow);
  form->addRow(QString(), plane);
  form->addRow(tr("Distance"), offset);
  form->addRow(QString(), slider);
  form->addRow(tr("Angle"), angle);
  form->addRow(QString(), flip);
  auto* lay = new QVBoxLayout(d);
  lay->setContentsMargins(10, 6, 10, 8);
  lay->addWidget(title);
  lay->addLayout(form);
  auto* buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
  auto* remove = buttons->addButton(tr("Remove"), QDialogButtonBox::DestructiveRole);
  buttons->button(QDialogButtonBox::Ok)->setObjectName(QStringLiteral("sectionOk"));
  remove->setObjectName(QStringLiteral("sectionRemove"));
  lay->addWidget(buttons);

  auto update = [this, offset, angle, flip, u] {
    if (sectionPicking_) return;
    section_.offset = toInternal(offset->value(), u);
    section_.angle = angle->value() * 3.14159265358979323846 / 180.0;
    section_.flip = flip->isChecked();
    section_.active = true;
    section_.visible = true;
    applySection();
    updateSectionArrow();
  };
  // A plane chosen (clicked in the canvas or from the list): the section starts there.
  auto usePlane = [this, offset, angle, pickLabel, update](const QString& spec, const QString& label) {
    section_.plane = spec;
    sectionPicking_ = false;
    viewport_->setPlanePicking(false);
    pickLabel->setText(label);
    {
      const QSignalBlocker a(offset), b(angle);
      offset->setValue(0);
      angle->setValue(0);
    }
    update();
  };
  connect(plane, &QComboBox::textActivated, d, [usePlane](const QString& t) { usePlane(t, t); });
  connect(repick, &QPushButton::clicked, d, [this, pickLabel] {
    sectionPicking_ = true;
    pickLabel->setText(tr("Click a face or plane"));
    viewport_->clearDragArrow();
    viewport_->setPlanePicking(true);
  });
  connect(this, &MainWindow::sectionPlanePicked, d, usePlane);
  connect(this, &MainWindow::sectionArrowMoved, d, [offset, u](double v) {
    offset->setValue(fromInternal(v, u));   // runs update()
  });
  connect(offset, &QDoubleSpinBox::valueChanged, d, update);
  connect(angle, &QDoubleSpinBox::valueChanged, d, update);
  connect(flip, &QCheckBox::toggled, d, update);
  connect(slider, &QSlider::valueChanged, d, [offset, slider, u] {
    const QSignalBlocker b(slider);
    offset->setValue(fromInternal(slider->value() / 100.0, u));
  });
  connect(buttons, &QDialogButtonBox::accepted, d, &QDialog::accept);
  connect(buttons, &QDialogButtonBox::rejected, d, [this, d, saved] {
    section_ = saved;
    applySection();
    d->reject();
  });
  connect(remove, &QPushButton::clicked, d, [this, d] {
    section_.active = false;
    applySection();
    d->reject();
  });
  connect(d, &QDialog::finished, this, [this, d] {
    sectionPanel_ = nullptr;   // closed now, deleted later
    sectionPicking_ = false;
    viewport_->setPlanePicking(false);
    viewport_->clearDragArrow();
    d->hide();
    d->deleteLater();
  });
  d->show();
  placeDialog(d);
  viewport_->setPlanePicking(true);
  statusBar()->showMessage(tr("Section Analysis: click a face or plane, then drag the arrow."), 5000);
}

void MainWindow::showCenterOfMass() {
  if (comShown_) {
    comShown_ = false;
    viewport_->setMarker(false);
    statusBar()->clearMessage();
    return;
  }
  const auto bodies = session_.document().bodies();
  if (bodies.empty()) {
    statusBar()->showMessage(tr("There is no body."), 3000);
    return;
  }
  const QStringList sel = viewport_->selectedBodies();
  const doc::Body* body = &bodies.back();
  for (const auto& b : bodies)
    if (!sel.isEmpty() && qs(b.name) == sel.first()) body = &b;
  const auto mp = kernel::massProperties(body->shape);
  const auto& c = mp.centerOfMass;
  const QString text = tr("%1 center of mass: X %2, Y %3, Z %4")
                           .arg(qs(body->name), formatLength(c.x), formatLength(c.y), formatLength(c.z));
  viewport_->setMarker(true, gp_Pnt(c.x, c.y, c.z), tr("Center of mass"));
  comShown_ = true;
  statusBar()->showMessage(text);
}

void MainWindow::checkInterference() {
  const auto bodies = session_.document().bodies();
  std::vector<TopoDS_Shape> overlaps;
  QStringList lines;
  const Unit u = lengthUnit();
  const double f = fromInternal(1.0, u);
  for (size_t i = 0; i < bodies.size(); ++i)
    for (size_t j = i + 1; j < bodies.size(); ++j) {
      BRepAlgoAPI_Common common(bodies[i].shape, bodies[j].shape);
      if (!common.IsDone()) continue;
      const double v = kernel::massProperties(common.Shape()).volume;
      if (v > 1e-9) {
        overlaps.push_back(common.Shape());
        lines << tr("%1 and %2 overlap by %3 %4³").arg(qs(bodies[i].name), qs(bodies[j].name))
                     .arg(v * f * f * f, 0, 'f', 3).arg(qs(std::string(unitSymbol(u))));
      }
    }
  viewport_->setPickedShapes(overlaps);
  QMessageBox::information(this, tr("Interference"),
                           lines.isEmpty() ? tr("No interference between %n bodies.", nullptr, static_cast<int>(bodies.size()))
                                           : lines.join(QLatin1Char('\n')));
  viewport_->setPickedShapes({});
}

} // namespace tsr::app
