// MainWindow: sketch mode (SKETCH ribbon tab, plane picking, finish/cancel)
// and profile picking for features that take profiles (Extrude).
#include "CommandDialog.h"
#include "Icons.h"
#include "MainWindow.h"

#include <QGuiApplication>
#include <limits>
#include <TopoDS.hxx>
#include <BRepAdaptor_Curve.hxx>
#include <BRep_Tool.hxx>
#include <TopExp.hxx>
#include <TopTools_IndexedMapOfShape.hxx>
#include <BRepBuilderAPI_MakeVertex.hxx>
#include <BRepExtrema_DistShapeShape.hxx>
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
  toolButton(create, T::Point, QStringLiteral("point"), tr("Point"), {});
  toolButton(create, T::Project, QStringLiteral("project"), tr("Project"), QStringLiteral("P"));
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
  // Profiles are clickable while a command wants them, and with no command
  // running (picked first, then E extrudes them).
  const bool idle = !active_ && !editor_;
  const bool on = idle || (active_ && active_->hasProfilesInput());
  viewport_->setProfilePicking(on);
  if (!on) return;
  QString sketchName = idle ? preSketch_ : active_->currentSketch();
  const QString picks = idle ? preProfiles_.join(QLatin1Char(';')) : active_->currentProfiles();
  const auto& d = session_.document();
  if (idle && sketchName.isEmpty()) {
    viewport_->setPickedProfiles({}, {});
    return;
  }
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
    for (const QString& item : picks.split(QLatin1Char(';'), Qt::SkipEmptyParts)) {
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

TopoDS_Shape MainWindow::originalShape(const QString& body) const {
  if (auto it = shapesBeforeCommand_.find(body.toStdString()); it != shapesBeforeCommand_.end()) return it->second;
  return viewport_->bodyShape(body);
}

// The edge or face of the original body a click on the (preview) body means:
// the same one when it is still there, else the nearest one of that kind. A
// click on a fillet's edge therefore means the edge it rounds, as in the
// familiar tool, where clicking it again deselects it.
TopoDS_Shape MainWindow::toOriginal(const QString& body, const TopoDS_Shape& picked) const {
  const TopoDS_Shape orig = originalShape(body);
  if (orig.IsNull() || picked.IsNull()) return picked;
  TopTools_IndexedMapOfShape subs;
  TopExp::MapShapes(orig, picked.ShapeType(), subs);
  if (subs.Contains(picked)) return picked;
  // A point well inside the picked shape.
  gp_Pnt probe;
  if (picked.ShapeType() == TopAbs_EDGE) {
    BRepAdaptor_Curve c(TopoDS::Edge(picked));
    probe = c.Value((c.FirstParameter() + c.LastParameter()) / 2);
  } else if (picked.ShapeType() == TopAbs_FACE) {
    GProp_GProps g;
    BRepGProp::SurfaceProperties(picked, g);
    probe = g.CentreOfMass();
  } else if (picked.ShapeType() == TopAbs_VERTEX) {
    probe = BRep_Tool::Pnt(TopoDS::Vertex(picked));
  } else {
    return picked;
  }
  const TopoDS_Vertex pv = BRepBuilderAPI_MakeVertex(probe).Vertex();
  TopoDS_Shape best;
  double bestD = std::numeric_limits<double>::max();
  for (int i = 1; i <= subs.Extent(); ++i) {
    BRepExtrema_DistShapeShape d(pv, subs(i));
    if (d.IsDone() && d.NbSolution() > 0 && d.Value() < bestD) {
      bestD = d.Value();
      best = subs(i);
    }
  }
  return best.IsNull() ? picked : best;
}

// The highlighted edges / faces are always what the panel holds, resolved on
// the original bodies (so Clear, edits and re-picks all show correctly).
void MainWindow::syncPickedShapes() {
  pickedEdges_.clear();
  if (!active_) return;
  const QString body = active_->currentBody();
  const TopoDS_Shape shape = originalShape(body.isEmpty() && !shapesBeforeCommand_.empty()
                                               ? QString::fromStdString(shapesBeforeCommand_.rbegin()->first)
                                               : body);
  auto add = [&](const QString& refs, bool faces) {
    if (shape.IsNull()) return;
    for (const QString& ref : refs.split(QLatin1Char(';'), Qt::SkipEmptyParts)) {
      try {
        const auto r = faces ? kernel::resolveFaces(shape, ref.toStdString()) : kernel::resolveEdges(shape, ref.toStdString());
        if (!r.empty()) pickedEdges_.push_back(r.front());
      } catch (const std::exception&) {
      }
    }
  };
  if (active_->hasEdgesInput()) add(active_->currentEdges(), false);
  if (active_->hasFacesInput()) add(active_->currentFaces(), true);
  updateEdgePicking();
}

// Ctrl held while picking edges or faces: the bodies as they were, without
// the preview, so the picked edges are easy to see.
void MainWindow::setShowOriginal(bool on) {
  if (on == showingOriginal_) return;
  showingOriginal_ = on;
  viewport_->setBodyOverrides(on ? shapesBeforeCommand_ : std::map<std::string, TopoDS_Shape>{});
}

void MainWindow::updateEdgePicking() {
  std::vector<TopAbs_ShapeEnum> types;
  if (active_ && active_->hasEdgesInput()) types.push_back(TopAbs_EDGE);
  if (active_ && active_->hasFacesInput()) types.push_back(TopAbs_FACE);
  if (active_ && active_->hasVerticesInput()) types.push_back(TopAbs_VERTEX);
  if (active_ && active_->hasJointOriginInput()) types = {TopAbs_FACE, TopAbs_EDGE, TopAbs_VERTEX};
  if (active_ && active_->commandId() == QLatin1String(doc::kCmdHole) &&
      active_->textInput(QStringLiteral("placement")) == QLatin1String("On Face"))
    types = {TopAbs_FACE};   // a click on the body places a hole
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
  // Hole, On Face: the clicked spot (on any face) is a hole position.
  if (active_->commandId() == QLatin1String(doc::kCmdHole) &&
      active_->textInput(QStringLiteral("placement")) == QLatin1String("On Face") && edge.ShapeType() == TopAbs_FACE) {
    const auto p = viewport_->pointAt(viewport_->lastPressPos());
    if (!p) return;
    QStringList pts = active_->textInput(QStringLiteral("points")).split(QLatin1Char(';'), Qt::SkipEmptyParts);
    pts << QStringLiteral("%1,%2,%3").arg(p->X(), 0, 'g', 12).arg(p->Y(), 0, 'g', 12).arg(p->Z(), 0, 'g', 12);
    active_->pickBody(body);
    active_->setInputForTest(QStringLiteral("points"), pts.join(QLatin1Char(';')));
    return;
  }
  if (edge.ShapeType() == TopAbs_VERTEX) {
    if (!active_->hasVerticesInput()) return;
    QStringList refs = active_->currentVertices().split(QLatin1Char(';'), Qt::SkipEmptyParts);
    if (!active_->currentBody().isEmpty() && active_->currentBody() != body) refs.clear();
    active_->pickBody(body);
    const QString ref = QString::fromStdString(kernel::vertexReference(edge));
    if (refs.contains(ref)) {
      if (viewport_->boxPicking()) return;   // a box adds, never removes
      refs.removeAll(ref);
    }
    else refs << ref;
    active_->setVertices(refs.join(QLatin1Char(';')));
    return;
  }
  const bool isFace = edge.ShapeType() == TopAbs_FACE;
  if (isFace ? !active_->hasFacesInput() : !(edge.ShapeType() == TopAbs_EDGE && active_->hasEdgesInput())) return;
  const TopoDS_Shape shape = originalShape(body);
  if (shape.IsNull()) return;
  const TopoDS_Shape picked = toOriginal(body, edge);
  auto current = [&] { return isFace ? active_->currentFaces() : active_->currentEdges(); };
  auto store = [&](const QString& v) {
    if (isFace) active_->setFaces(v);
    else active_->setEdges(v);
  };
  // Picks from another body start a new selection.
  QStringList refs = current().split(QLatin1Char(';'), Qt::SkipEmptyParts);
  if (!active_->currentBody().isEmpty() && active_->currentBody() != body) {
    refs.clear();
    pickedEdges_.clear();
  }
  active_->pickBody(body);
  // Fillet and Chamfer take the whole tangent chain of an edge (the kernel
  // rounds all of it anyway), as with the familiar Tangent Chain option.
  std::vector<TopoDS_Shape> group{picked};
  if (!isFace && (active_->commandId() == QLatin1String(doc::kCmdFillet) ||
                  active_->commandId() == QLatin1String(doc::kCmdChamfer)))
    group = kernel::tangentChain(shape, picked);
  auto inGroup = [&](const TopoDS_Shape& s) {
    return std::any_of(group.begin(), group.end(), [&](const TopoDS_Shape& g) { return g.IsSame(s); });
  };
  // Clicking a picked edge again removes it, with its chain (the picks
  // resolved on the original body are compared with the clicked one).
  std::vector<bool> resolvedInGroup(refs.size(), false);
  bool hit = false;
  for (int i = 0; i < static_cast<int>(refs.size()); ++i) {
    try {
      const auto r = isFace ? kernel::resolveFaces(shape, refs[i].toStdString())
                            : kernel::resolveEdges(shape, refs[i].toStdString());
      if (!r.empty() && inGroup(r.front())) {
        resolvedInGroup[i] = true;
        hit = hit || r.front().IsSame(picked);
      }
    } catch (const std::exception&) {
    }
  }
  if (hit) {
    if (viewport_->boxPicking()) return;   // a box adds, never removes
    QStringList kept;
    for (int i = 0; i < static_cast<int>(refs.size()); ++i)
      if (!resolvedInGroup[i]) kept << refs[i];
    store(kept.join(QLatin1Char(';')));
    syncPickedShapes();
    updateDragArrow();
    return;
  }
  try {
    // Every edge of the group not picked yet.
    const int before = static_cast<int>(refs.size());
    for (const TopoDS_Shape& g : group) {
      bool already = false;
      for (int i = 0; i < before && !already; ++i)
        if (resolvedInGroup[i]) {
          const auto r = kernel::resolveEdges(shape, refs[i].toStdString());
          already = !r.empty() && r.front().IsSame(g);
        }
      if (!already)
        refs << QString::fromStdString(isFace ? kernel::faceReference(shape, g) : kernel::edgeReference(shape, g));
    }
  } catch (const std::exception& e) {
    statusBar()->showMessage(QString::fromUtf8(e.what()), 5000);
    return;
  }
  // Extruding a body face adds to that body by default.
  if (isFace && active_->commandId() == QLatin1String(doc::kCmdExtrude) &&
      active_->textInput(QStringLiteral("operation")) == QLatin1String("New Body"))
    active_->setInputForTest(QStringLiteral("operation"), QStringLiteral("Join"));
  store(refs.join(QLatin1Char(';')));
  syncPickedShapes();
  updateDragArrow();
}

void MainWindow::onProfileClicked(const QString& sketchName, int index) {
  if (!active_ && !editor_) {
    // No command: the profile is selected for the next one (Shift / Ctrl add).
    const auto rec = session_.document().sketch(sketchName.toStdString());
    if (!rec) return;
    try {
      const gp_Ax3 frame = session_.document().planeFrame(rec->plane, rec->offset);
      const auto profiles = sketch::profiles(sketch::Sketch::fromJson(rec->data), frame);
      if (index < 0 || index >= static_cast<int>(profiles.size())) return;
      const QString item = QStringLiteral("%1,%2").arg(profiles[index].x, 0, 'g', 12).arg(profiles[index].y, 0, 'g', 12);
      const bool add = viewport_->boxPicking() ||
                       (QGuiApplication::keyboardModifiers() & (Qt::ShiftModifier | Qt::ControlModifier));
      if (!add || preSketch_ != sketchName) {
        const bool same = preSketch_ == sketchName && preProfiles_ == QStringList{item};
        preProfiles_.clear();
        viewport_->clearSelection();
        if (same && !viewport_->boxPicking()) {   // clicking the one picked profile again deselects it
          preSketch_.clear();
          updateProfilePicking();
          return;
        }
      }
      preSketch_ = sketchName;
      if (preProfiles_.contains(item)) {
        if (!viewport_->boxPicking()) preProfiles_.removeAll(item);
      } else {
        preProfiles_ << item;
      }
      statusBar()->showMessage(tr("%n profile(s) selected.", nullptr, static_cast<int>(preProfiles_.size())), 3000);
    } catch (const std::exception&) {
      return;
    }
    updateProfilePicking();
    return;
  }
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
    if (auto it = std::find(picked.begin(), picked.end(), index); it != picked.end()) {
      if (!viewport_->boxPicking()) picked.erase(it);
    } else {
      picked.push_back(index);
    }
    QStringList items;
    for (int i : picked)
      items << QStringLiteral("%1,%2").arg(profiles[i].x, 0, 'g', 12).arg(profiles[i].y, 0, 'g', 12);
    active_->setProfiles(sketchName, items.join(QLatin1Char(';')));
  } catch (const std::exception&) {
  }
  updateProfilePicking();
}

} // namespace tsr::app
