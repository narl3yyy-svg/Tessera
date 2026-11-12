// MainWindow: sketch mode (SKETCH ribbon tab, plane picking, finish/cancel)
// and profile picking for features that take profiles (Extrude).
#include "CommandDialog.h"
#include "Icons.h"
#include "MainWindow.h"
#include "SketchEditor.h"
#include "SketchPalette.h"
#include "Viewport.h"

#include "tsr/doc/DocCommands.h"
#include "tsr/kernel/Kernel.h"

#include <BRepGProp.hxx>
#include <GProp_GProps.hxx>
#include "tsr/sketch/SketchGeometry.h"

#include <QButtonGroup>

#include <algorithm>
#include <QFrame>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QMessageBox>
#include <QPushButton>
#include <QShortcut>
#include <QStatusBar>
#include <QTabWidget>
#include <QToolButton>
#include <QTimer>
#include <QVBoxLayout>
#include <gp_Pln.hxx>

namespace tsr::app {

namespace {
QString qs(const std::string& s) { return QString::fromStdString(s); }
} // namespace

bool MainWindow::sketchVisible(const std::string& name) const {
  if (auto it = sketchVisibility_.find(name); it != sketchVisibility_.end()) return it->second;
  // Default: hidden once a later feature uses it (the profile became solid).
  for (const auto& f : session_.document().features()) {
    if (!f.error.empty() || f.suppressed) continue;
    for (const char* key : {"sketch", "path"})
      if (auto it = f.inputs.find(key); it != f.inputs.end())
        if (auto s = std::get_if<std::string>(&it->second); s && *s == name) return false;
    if (auto it = f.inputs.find("sections"); it != f.inputs.end())
      if (auto s = std::get_if<std::string>(&it->second))
        for (const auto& part : QString::fromStdString(*s).split(QLatin1Char(';')))
          if (part.toStdString() == name) return false;
  }
  return true;
}

// ---------------------------------------------------------------------------
void MainWindow::beginSketch() {
  if (editor_ || active_) {
    statusBar()->showMessage(tr("Finish the current command first."), 3000);
    return;
  }
  if (!viewport_->available()) {
    // No 3D view to click in: sketch on the XY plane.
    startSketch(QStringLiteral("XY"));
    return;
  }
  viewport_->setPlanePicking(true);
  statusBar()->showMessage(tr("Create Sketch: click an origin plane or a flat face (Esc cancels)."));
}

SketchEditor* MainWindow::startSketch(const QString& planeSpec) {
  if (editor_ || active_) return nullptr;
  try {
    (void)session_.document().planeFrame(planeSpec.toStdString());
  } catch (const std::exception& e) {
    statusBar()->showMessage(qs(e.what()), 5000);
    return nullptr;
  }
  viewport_->setPlanePicking(false);
  const QString name = qs(session_.document().nextSketchName());
  editor_ = new SketchEditor(session_, viewport_, name, planeSpec, 0.0, -1, sketch::Sketch(), this);
  enterSketchMode();
  return editor_;
}

SketchEditor* MainWindow::editSketch(int featureId) {
  if (editor_ || active_ || session_.document().hasOpenTransaction()) {
    statusBar()->showMessage(tr("Finish the current command first."), 3000);
    return nullptr;
  }
  const auto f = session_.document().feature(featureId);
  if (!f || f->commandId != doc::kCmdSketch) return nullptr;
  auto str = [&](const char* k) {
    auto it = f->inputs.find(k);
    if (it == f->inputs.end()) return std::string();
    auto p = std::get_if<std::string>(&it->second);
    return p ? *p : std::string();
  };
  double offset = 0;
  if (auto it = f->inputs.find("offset"); it != f->inputs.end())
    if (auto p = std::get_if<double>(&it->second)) offset = *p;
  sketch::Sketch s;
  try {
    // Prefer the solved geometry stored by the last recompute.
    const auto rec = session_.document().sketch(f->name);
    s = sketch::Sketch::fromJson(rec ? rec->data : str("data"));
    editor_ = new SketchEditor(session_, viewport_, qs(f->name), qs(str("plane")), offset, featureId, s, this);
  } catch (const sketch::SketchError& e) {
    QMessageBox::warning(this, tr("Edit Sketch"), qs(e.what()));
    return nullptr;
  }
  enterSketchMode();
  return editor_;
}

void MainWindow::enterSketchMode() {
  connect(editor_, &SketchEditor::message, this, [this](const QString& m) { statusBar()->showMessage(m); });
  connect(editor_, &SketchEditor::changed, this, [this] {
    undo_->setEnabled(editor_ && editor_->canUndo());
    redo_->setEnabled(editor_ && editor_->canRedo());
  });
  sketchTab_ = buildSketchTab();
  ribbon_->insertTab(0, ribbonPage(sketchTab_), tr("SKETCH"));
  ribbon_->setCurrentIndex(0);
  for (int i = 1; i < ribbon_->count(); ++i) ribbon_->setTabEnabled(i, false);
  for (QShortcut* s : sketchShortcuts_) s->setEnabled(true);
  timeline_->setEnabled(false);
  viewport_->setBodiesGhosted(true);

  // SKETCH PALETTE, in the canvas on the right like the command panels.
  palette_ = new SketchPalette(editor_, viewport_);
  palette_->setGrid(viewport_->gridVisible(), viewport_->gridSnap());
  connect(palette_, &SketchPalette::lookAtRequested, this, [this] {
    if (editor_) viewport_->lookAt(editor_->frame());
  });
  connect(palette_, &SketchPalette::sliceToggled, this, [this](bool on) {
    if (!editor_) return;
    const gp_Ax3& f = editor_->frame();
    viewport_->setSection(on, gp_Pln(f.Location(), f.Direction()));   // removes what is in front of the plane
  });
  connect(palette_, &SketchPalette::gridToggled, this, [this](bool on) { viewport_->setGridVisible(on); });
  connect(palette_, &SketchPalette::snapToggled, this, [this](bool on) { viewport_->setGridSnap(on); });
  connect(palette_, &SketchPalette::finishRequested, this, [this] {
    QTimer::singleShot(0, this, [this] { finishSketch(); });   // not from inside the palette that closes
  });
  connect(editor_, &SketchEditor::changed, palette_, &SketchPalette::sync);
  connect(editor_, &SketchEditor::toolChanged, this, &MainWindow::syncSketchTools);
  palette_->show();
  placeDialog(palette_);
  syncSketchTools();
  refresh();
  viewport_->setFocus();
}

void MainWindow::exitSketchMode() {
  for (QShortcut* s : sketchShortcuts_) s->setEnabled(false);
  if (sketchTab_) {
    for (int i = 0; i < ribbon_->count(); ++i)
      if (ribbon_->widget(i)->isAncestorOf(sketchTab_)) {
        QWidget* wrapper = ribbon_->widget(i);
        ribbon_->removeTab(i);
        wrapper->deleteLater();
        break;
      }
    sketchTab_->deleteLater();
    sketchTab_ = nullptr;
  }
  toolButtons_.clear();
  constructionButton_ = nullptr;
  for (int i = 0; i < ribbon_->count(); ++i)
    ribbon_->setTabEnabled(i, !ribbon_->tabToolTip(i).startsWith(tr("Planned")));
  timeline_->setEnabled(true);
  viewport_->setBodiesGhosted(false);
  if (palette_) {
    const bool sliced = palette_->sliceOn();
    palette_->hide();
    palette_->deleteLater();
    palette_ = nullptr;
    if (sliced) applySection();   // back to the design's own section analysis, if any
  }
  delete editor_;   // restores the view's grid and mouse handling
  editor_ = nullptr;
  refresh();
}

bool MainWindow::finishSketch() {
  if (!editor_) return false;
  const std::string err = editor_->finish();
  if (!err.empty()) {
    QMessageBox::warning(this, tr("Finish Sketch"), qs(err));
    return false;
  }
  const QString name = editor_->name();
  exitSketchMode();
  statusBar()->showMessage(tr("%1 finished. Use Extrude (E) to give it depth.").arg(name), 6000);
  return true;
}

void MainWindow::cancelSketch() {
  if (!editor_) return;
  exitSketchMode();
  statusBar()->showMessage(tr("Sketch changes discarded."), 3000);
}

QWidget* MainWindow::buildSketchTab() {
  auto* page = new QWidget;
  auto* row = new QHBoxLayout(page);
  row->setContentsMargins(6, 2, 6, 2);
  row->setSpacing(2);
  auto* group = new QButtonGroup(page);
  group->setExclusive(true);
  toolButtons_.clear();

  auto panel = [&](const QString& title) {
    auto* box = new QWidget;
    auto* col = new QVBoxLayout(box);
    col->setContentsMargins(4, 0, 4, 0);
    col->setSpacing(0);
    auto* buttons = new QHBoxLayout;
    buttons->setSpacing(0);
    col->addLayout(buttons);
    auto* label = new QLabel(title);
    QFont f = label->font();
    f.setPointSizeF(f.pointSizeF() * 0.85);
    label->setFont(f);
    label->setAlignment(Qt::AlignHCenter);
    col->addWidget(label);
    row->addWidget(box);
    auto* sep = new QFrame;
    sep->setFrameShape(QFrame::VLine);
    sep->setFrameShadow(QFrame::Sunken);
    row->addWidget(sep);
    return buttons;
  };
  auto toolButton = [&](QHBoxLayout* into, SketchEditor::Tool tool, const QString& iconName, const QString& name,
                        const QString& key) {
    auto* b = new QToolButton;
    b->setObjectName(QStringLiteral("sketch.") + iconName);
    setIcon(b, iconName);
    b->setIconSize(QSize(30, 30));
    b->setAutoRaise(true);
    b->setCheckable(true);
    b->setToolTip(key.isEmpty() ? name : QStringLiteral("%1 (%2)").arg(name, key));
    b->setAccessibleName(name);
    group->addButton(b);
    into->addWidget(b);
    connect(b, &QToolButton::clicked, this, [this, tool] {
      if (editor_) editor_->setTool(tool);
    });
    toolButtons_.emplace_back(static_cast<int>(tool), b);
  };

  using T = SketchEditor::Tool;
  QHBoxLayout* create = panel(tr("CREATE"));
  toolButton(create, T::Select, QStringLiteral("select"), tr("Select / move"), QStringLiteral("Q"));
  toolButton(create, T::Line, QStringLiteral("line"), tr("Line"), QStringLiteral("L"));
  toolButton(create, T::Rectangle, QStringLiteral("rectangle"), tr("2-Point Rectangle"), QStringLiteral("R"));
  toolButton(create, T::CenterRectangle, QStringLiteral("center-rectangle"), tr("Center Rectangle"), {});
  toolButton(create, T::Circle, QStringLiteral("circle"), tr("Center Diameter Circle"), QStringLiteral("C"));
  toolButton(create, T::Arc, QStringLiteral("arc"), tr("Center Point Arc"), QStringLiteral("A"));
  toolButton(create, T::Polygon, QStringLiteral("polygon"), tr("Polygon (inscribed)"), {});
  toolButton(create, T::Slot, QStringLiteral("slot"), tr("Center to Center Slot"), {});
  toolButton(create, T::Spline, QStringLiteral("spline"), tr("Fit Point Spline"), {});
  toolButton(create, T::Mirror, QStringLiteral("sketch-mirror"), tr("Mirror"), {});
  toolButton(create, T::Point, QStringLiteral("point"), tr("Point"), QStringLiteral("P"));
  auto* construction = new QToolButton;
  construction->setObjectName(QStringLiteral("sketch.construction"));
  setIcon(construction, QStringLiteral("construction"));
  construction->setIconSize(QSize(30, 30));
  construction->setAutoRaise(true);
  construction->setCheckable(true);
  construction->setToolTip(tr("Construction geometry (X): new curves are reference only, not profiles"));
  connect(construction, &QToolButton::toggled, this, [this](bool on) {
    if (editor_) editor_->setConstruction(on);
  });
  create->addWidget(construction);
  constructionButton_ = construction;

  QHBoxLayout* modify = panel(tr("MODIFY"));
  toolButton(modify, T::Fillet, QStringLiteral("sketch-fillet"), tr("Fillet"), {});
  toolButton(modify, T::Chamfer, QStringLiteral("sketch-chamfer"), tr("Chamfer"), {});
  toolButton(modify, T::Trim, QStringLiteral("trim"), tr("Trim"), QStringLiteral("T"));
  toolButton(modify, T::Extend, QStringLiteral("extend"), tr("Extend"), {});
  toolButton(modify, T::Offset, QStringLiteral("offset"), tr("Offset"), QStringLiteral("O"));

  QHBoxLayout* constraints = panel(tr("CONSTRAINTS"));
  toolButton(constraints, T::Dimension, QStringLiteral("dimension"), tr("Sketch Dimension"), QStringLiteral("D"));
  toolButton(constraints, T::Coincident, QStringLiteral("c-coincident"), tr("Coincident"), {});
  toolButton(constraints, T::HorizontalVertical, QStringLiteral("c-horizontal-vertical"), tr("Horizontal/Vertical"), {});
  toolButton(constraints, T::Parallel, QStringLiteral("c-parallel"), tr("Parallel"), {});
  toolButton(constraints, T::Perpendicular, QStringLiteral("c-perpendicular"), tr("Perpendicular"), {});
  toolButton(constraints, T::Equal, QStringLiteral("c-equal"), tr("Equal"), {});
  toolButton(constraints, T::Tangent, QStringLiteral("c-tangent"), tr("Tangent"), {});
  toolButton(constraints, T::Concentric, QStringLiteral("c-concentric"), tr("Concentric"), {});
  toolButton(constraints, T::Midpoint, QStringLiteral("c-midpoint"), tr("Midpoint"), {});
  toolButton(constraints, T::Collinear, QStringLiteral("c-collinear"), tr("Collinear"), {});
  toolButton(constraints, T::Symmetry, QStringLiteral("c-symmetry"), tr("Symmetry"), {});
  toolButton(constraints, T::Fix, QStringLiteral("c-fix"), tr("Fix/Unfix"), {});

  QHBoxLayout* view = panel(tr("VIEW"));
  auto* look = new QToolButton;
  setIcon(look, QStringLiteral("sketch"));
  look->setIconSize(QSize(30, 30));
  look->setAutoRaise(true);
  look->setToolTip(tr("Look at the sketch plane"));
  connect(look, &QToolButton::clicked, this, [this] {
    if (editor_) viewport_->lookAt(editor_->frame());
  });
  view->addWidget(look);

  row->addStretch();
  auto* finish = new QPushButton(tr("FINISH SKETCH"));
  setIcon(finish, QStringLiteral("finish"));
  finish->setObjectName(QStringLiteral("finishSketch"));
  finish->setIconSize(QSize(26, 26));
  finish->setToolTip(tr("Save the sketch to the design and leave sketch mode"));
  connect(finish, &QPushButton::clicked, this, [this] { finishSketch(); });
  auto* cancel = new QPushButton(tr("Cancel"));
  cancel->setToolTip(tr("Leave sketch mode without saving changes"));
  connect(cancel, &QPushButton::clicked, this, [this] {
    if (editor_ && (editor_->canUndo()) &&
        QMessageBox::question(this, tr("Cancel Sketch"), tr("Discard the changes made in this sketch?")) !=
            QMessageBox::Yes)
      return;
    cancelSketch();
  });
  row->addWidget(cancel);
  row->addWidget(finish);
  return page;
}

SketchPalette* MainWindow::sketchPalette() const { return palette_; }

void MainWindow::syncSketchTools() {
  if (!editor_) return;
  if (palette_) palette_->sync();
  for (auto& [tool, button] : toolButtons_) button->setChecked(tool == static_cast<int>(editor_->tool()));
  if (constructionButton_) constructionButton_->setChecked(editor_->construction());
}

// ---------------------------------------------------------------------------
// Profile picking (Extrude)

void MainWindow::updateProfilePicking() {
  const bool on = active_ && active_->hasProfilesInput();
  viewport_->setProfilePicking(on);
  if (!on) return;
  QString sketchName = active_->currentSketch();
  const auto& d = session_.document();
  if (sketchName.isEmpty()) {
    const auto all = d.sketches();
    if (all.empty()) return;
    sketchName = qs(all.back().name);
  }
  const auto rec = d.sketch(sketchName.toStdString());
  if (!rec) return;
  std::vector<int> indices;
  try {
    const gp_Ax3 frame = session_.document().planeFrame(rec->plane, rec->offset);
    const auto profiles = sketch::profiles(sketch::Sketch::fromJson(rec->data), frame);
    for (const QString& item : active_->currentProfiles().split(QLatin1Char(';'), Qt::SkipEmptyParts)) {
      const auto xy = item.split(QLatin1Char(','));
      if (xy.size() != 2) continue;
      const int i = sketch::profileAt(profiles, frame, xy[0].toDouble(), xy[1].toDouble());
      if (i >= 0) indices.push_back(i);
    }
  } catch (const std::exception&) {
    return;
  }
  viewport_->setPickedProfiles(sketchName.toStdString(), indices);
}

// ---------------------------------------------------------------------------
// Edge picking (Fillet, Chamfer)

void MainWindow::updateEdgePicking() {
  std::vector<TopAbs_ShapeEnum> types;
  if (active_ && active_->hasEdgesInput()) types.push_back(TopAbs_EDGE);
  if (active_ && active_->hasFacesInput()) types.push_back(TopAbs_FACE);
  if (active_ && active_->hasVerticesInput()) types.push_back(TopAbs_VERTEX);
  if (active_ && active_->hasJointOriginInput()) types = {TopAbs_FACE, TopAbs_EDGE, TopAbs_VERTEX};
  viewport_->setSubShapePicking(types);
  if (!types.empty()) viewport_->setPickedShapes(pickedEdges_);
}

void MainWindow::onEdgeClicked(const QString& body, const TopoDS_Shape& edge) {
  if (!active_) return;
  if (std::find(bodiesBeforeCommand_.begin(), bodiesBeforeCommand_.end(), body.toStdString()) == bodiesBeforeCommand_.end()) {
    statusBar()->showMessage(tr("That is the preview of this command; pick a face or edge of an existing body."), 4000);
    return;
  }
  if (active_->hasJointOriginInput()) {
    // Joint: the face / edge / point clicked becomes the next joint origin.
    const TopoDS_Shape shape = viewport_->bodyShape(body);
    try {
      QString spec;
      switch (edge.ShapeType()) {
        case TopAbs_FACE: spec = body + QStringLiteral("|face|") + QString::fromStdString(kernel::faceReference(shape, edge)); break;
        case TopAbs_EDGE: spec = body + QStringLiteral("|edge|") + QString::fromStdString(kernel::edgeReference(shape, edge)); break;
        case TopAbs_VERTEX: spec = body + QStringLiteral("|vertex|") + QString::fromStdString(kernel::vertexReference(edge)); break;
        default: return;
      }
      active_->pickJointOrigin(spec);
    } catch (const std::exception& e) {
      statusBar()->showMessage(QString::fromUtf8(e.what()), 5000);
    }
    return;
  }
  if (edge.ShapeType() == TopAbs_VERTEX) {
    if (!active_->hasVerticesInput()) return;
    QStringList refs = active_->currentVertices().split(QLatin1Char(';'), Qt::SkipEmptyParts);
    if (!active_->currentBody().isEmpty() && active_->currentBody() != body) refs.clear();
    active_->pickBody(body);
    const QString ref = QString::fromStdString(kernel::vertexReference(edge));
    if (refs.contains(ref)) refs.removeAll(ref);
    else refs << ref;
    active_->setVertices(refs.join(QLatin1Char(';')));
    return;
  }
  const bool isFace = edge.ShapeType() == TopAbs_FACE;
  if (isFace ? !active_->hasFacesInput() : !(edge.ShapeType() == TopAbs_EDGE && active_->hasEdgesInput())) return;
  const TopoDS_Shape shape = viewport_->bodyShape(body);
  if (shape.IsNull()) return;
  auto current = [&] { return isFace ? active_->currentFaces() : active_->currentEdges(); };
  auto store = [&](const QString& v) {
    if (isFace) active_->setFaces(v);
    else active_->setEdges(v);
  };
  auto keyPoint = [](const TopoDS_Shape& s) {
    if (s.ShapeType() == TopAbs_FACE) {
      GProp_GProps g;
      BRepGProp::SurfaceProperties(s, g);
      const gp_Pnt c = g.CentreOfMass();
      return kernel::Vec3{c.X(), c.Y(), c.Z()};
    }
    return kernel::edgeMidpoint(s);
  };
  // Picks from another body start a new selection.
  QStringList refs = current().split(QLatin1Char(';'), Qt::SkipEmptyParts);
  if (!active_->currentBody().isEmpty() && active_->currentBody() != body) {
    refs.clear();
    pickedEdges_.clear();
  }
  active_->pickBody(body);
  // Clicking a picked edge again removes it (compared by position: the
  // preview rebuilds the body, so the shapes are new objects).
  const auto mid = keyPoint(edge);
  for (int i = 0; i < static_cast<int>(pickedEdges_.size()); ++i) {
    if (pickedEdges_[i].IsNull() || pickedEdges_[i].ShapeType() != edge.ShapeType()) continue;
    const auto m = keyPoint(pickedEdges_[i]);
    if (std::abs(m.x - mid.x) + std::abs(m.y - mid.y) + std::abs(m.z - mid.z) < 1e-6) {
      pickedEdges_.erase(pickedEdges_.begin() + i);
      if (i < refs.size()) refs.removeAt(i);
      store(refs.join(QLatin1Char(';')));
      updateEdgePicking();
      return;
    }
  }
  try {
    refs << QString::fromStdString(isFace ? kernel::faceReference(shape, edge) : kernel::edgeReference(shape, edge));
  } catch (const std::exception& e) {
    statusBar()->showMessage(QString::fromUtf8(e.what()), 5000);
    return;
  }
  pickedEdges_.push_back(edge);
  // Extruding a body face adds to that body by default.
  if (isFace && active_->commandId() == QLatin1String(doc::kCmdExtrude) &&
      active_->textInput(QStringLiteral("operation")) == QLatin1String("New Body"))
    active_->setInputForTest(QStringLiteral("operation"), QStringLiteral("Join"));
  store(refs.join(QLatin1Char(';')));
  updateEdgePicking();
  updateDragArrow();
}

void MainWindow::onProfileClicked(const QString& sketchName, int index) {
  if (!active_ || !active_->hasProfilesInput()) return;
  const auto rec = session_.document().sketch(sketchName.toStdString());
  if (!rec) return;
  try {
    const gp_Ax3 frame = session_.document().planeFrame(rec->plane, rec->offset);
    const auto profiles = sketch::profiles(sketch::Sketch::fromJson(rec->data), frame);
    if (index < 0 || index >= static_cast<int>(profiles.size())) return;
    // Current picks on this sketch (picks on another sketch are replaced).
    std::vector<int> picked;
    QString current = active_->currentSketch();
    if (current.isEmpty()) {
      const auto all = session_.document().sketches();
      if (!all.empty()) current = qs(all.back().name);
    }
    if (current == sketchName)
      for (const QString& item : active_->currentProfiles().split(QLatin1Char(';'), Qt::SkipEmptyParts)) {
        const auto xy = item.split(QLatin1Char(','));
        if (xy.size() != 2) continue;
        const int i = sketch::profileAt(profiles, frame, xy[0].toDouble(), xy[1].toDouble());
        if (i >= 0 && std::find(picked.begin(), picked.end(), i) == picked.end()) picked.push_back(i);
      }
    if (auto it = std::find(picked.begin(), picked.end(), index); it != picked.end()) picked.erase(it);
    else picked.push_back(index);
    QStringList items;
    for (int i : picked)
      items << QStringLiteral("%1,%2").arg(profiles[i].x, 0, 'g', 12).arg(profiles[i].y, 0, 'g', 12);
    active_->setProfiles(sketchName, items.join(QLatin1Char(';')));
  } catch (const std::exception&) {
  }
  updateProfilePicking();
}

} // namespace tsr::app
