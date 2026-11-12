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
  planned("Assemble", "ui.newComponent", "New Component", "component");
  planned("Assemble", "ui.joint", "Joint", "joint", "J");
  planned("Assemble", "ui.asBuiltJoint", "As-Built Joint", "joint", "Shift+J");
  planned("Assemble", "ui.jointOrigin", "Joint Origin", "joint-origin");
  planned("Assemble", "ui.rigidGroup", "Rigid Group", "rigid");
  planned("Assemble", "ui.driveJoints", "Drive Joints", "motion");
  planned("Assemble", "ui.motionLink", "Motion Link", "motion");
  planned("Configure", "ui.configure", "Configurations", "configure");
  planned("Construct", "ui.tangentPlane", "Tangent Plane", "plane");
  add("Inspect", "ui.measure", "Measure", "measure", "Distance, angle, length, area and volume of picked items.", "I",
      [this] { openMeasure(); });
  add("Inspect", "ui.interference", "Interference", "interference", "Finds bodies that overlap.", "",
      [this] { checkInterference(); });
  add("Inspect", "ui.section", "Section Analysis", "section", "Cuts the view with a plane to look inside.", "",
      [this] { openSection(); });
  add("Inspect", "ui.centerOfMass", "Center of Mass", "com", "Shows the center of mass of the selected body.", "",
      [this] { showCenterOfMass(); });
  planned("Inspect", "ui.curvature", "Curvature Comb Analysis", "curvature");
  planned("Inspect", "ui.zebra", "Zebra Analysis", "zebra");
  planned("Inspect", "ui.draftAnalysis", "Draft Analysis", "draft");
  add("Insert", "ui.insert", "Insert Mesh / CAD File", "insert", "Adds bodies from a STEP, IGES, STL or BREP file.", "",
      [this] { insertFile(); });
  planned("Insert", "ui.insertSvg", "Insert SVG / DXF", "insert-2d");
  planned("Insert", "ui.canvas", "Canvas", "image");
  planned("Insert", "ui.decal", "Decal", "image");
  add("Select", "ui.select", "Select", "select", "Window selection of bodies (Esc clears).", "",
      [this] { viewport_->setOrbitTool(false); viewport_->setPanTool(false); });
  add("Select", "ui.filterBodies", "Select Bodies", "body", "Selection filter: whole bodies.", "",
      [this] { setSelectionFilter({}); });
  add("Select", "ui.filterFaces", "Select Faces", "face", "Selection filter: faces.", "",
      [this] { setSelectionFilter({TopAbs_FACE}); });
  add("Select", "ui.filterEdges", "Select Edges", "edge", "Selection filter: edges.", "",
      [this] { setSelectionFilter({TopAbs_EDGE}); });
  add("Select", "ui.filterVertices", "Select Vertices", "vertex", "Selection filter: vertices.", "",
      [this] { setSelectionFilter({TopAbs_VERTEX}); });
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
  const char* what = types.empty() ? "bodies" : types[0] == TopAbs_FACE ? "faces" : types[0] == TopAbs_EDGE ? "edges" : "vertices";
  statusBar()->showMessage(tr("Selection filter: %1.").arg(QString::fromLatin1(what)), 3000);
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
  const Unit u = lengthUnit();
  const double current = fromInternal(viewport_->gridSpacing(), u);
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
