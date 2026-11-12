#include "CommandDialog.h"
#include "MainWindow.h"
#include "MarkingMenu.h"
#include "ParametersDialog.h"
#include "SketchEditor.h"
#include "SketchPalette.h"
#include "Theme.h"
#include "Viewport.h"

#include "tsr/doc/DocCommands.h"
#include "tsr/kernel/Kernel.h"

#include <QAbstractButton>
#include <QApplication>
#include <QAbstractSlider>
#include <QAbstractSpinBox>
#include <QComboBox>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QKeyEvent>
#include <QLineEdit>

#include <BRepGProp.hxx>
#include <GProp_GProps.hxx>
#include <TopExp_Explorer.hxx>
#include <QCommandLineParser>
#include <QListWidget>
#include <QTreeWidgetItemIterator>
#include <QPainter>
#include <QPixmap>
#include <QTabWidget>
#include <QTimer>
#include <QToolButton>
#include <QTreeWidget>

#include <cmath>
#include <cstdio>

namespace {

// --smoke: drive the real window through commands end to end and exit.
// Used by CI under QT_QPA_PLATFORM=offscreen (tests/gui).
int smoke(tsr::app::MainWindow& w, tsr::doc::Session& s) {
  auto fail = [](const char* what) {
    std::fprintf(stderr, "smoke: FAIL %s\n", what);
    return 1;
  };
  // Exact positions in these steps: no grid snapping.
  w.viewport()->setGridSnap(false);
  // Ribbon must expose every registered command.
  for (const tsr::Command* c : s.commands().all()) {
    const QString id = QString::fromStdString(c->def().id);
    if (c->def().panel.empty()) continue;
    if (!w.ribbon()->findChild<QToolButton*>(id) && !w.ribbon()->findChild<QAction*>(id)) return fail("ribbon entry missing");
  }

  auto* button = w.ribbon()->findChild<QToolButton*>(QStringLiteral("tsr.primitive.box"));
  button->click();
  auto* dlg = w.findChild<tsr::app::CommandDialog*>(QStringLiteral("tsr.primitive.box"));
  if (!dlg) return fail("box dialog did not open");
  if (w.startCommand(QStringLiteral("tsr.primitive.sphere"))) return fail("second command started while one is open");
  if (!dlg->setInputForTest(QStringLiteral("length"), 20.0)) return fail("cannot set length");
  if (s.document().bodies().size() != 1) return fail("preview did not create a body");
  dlg->accept();
  QApplication::processEvents();
  if (s.document().bodies().size() != 1 || s.document().hasOpenTransaction()) return fail("execute");
  if (w.browser()->findItems(QStringLiteral("Body1"), Qt::MatchStartsWith | Qt::MatchRecursive).isEmpty())
    return fail("browser not refreshed");
  if (w.timeline()->count() != 1) return fail("timeline not refreshed");

  // Cut a hole with a cylinder chosen through the Operation dropdown and a
  // body picked as in the 3D view.
  auto* cyl = w.startCommand(QStringLiteral("tsr.primitive.cylinder"));
  if (!cyl) return fail("cylinder dialog did not open");
  if (!cyl->setInputForTest(QStringLiteral("operation"), QStringLiteral("Cut"))) return fail("cannot set operation");
  if (!cyl->pickBody(QStringLiteral("Body1"))) return fail("cannot pick target body");
  if (!cyl->setInputForTest(QStringLiteral("x"), 10.0) || !cyl->setInputForTest(QStringLiteral("y"), 5.0) ||
      !cyl->setInputForTest(QStringLiteral("diameter"), 4.0))   // a hole, narrower than the box
    return fail("cannot set position");
  cyl->accept();
  QApplication::processEvents();
  if (s.document().bodies().size() != 1 || w.timeline()->count() != 2) return fail("cut");

  // Edit the box from the timeline: the cut must be replayed.
  const int boxId = s.document().features().front().id;
  auto* edit = w.editFeature(boxId);
  if (!edit) return fail("edit dialog did not open");
  if (!edit->setInputForTest(QStringLiteral("height"), 30.0)) return fail("cannot edit height");
  edit->accept();
  QApplication::processEvents();
  if (s.document().features().size() != 2 || !s.document().features()[1].error.empty()) return fail("replay");

  if (!s.undo() || !s.undo() || s.document().bodies().size() != 1) return fail("undo");
  if (!s.redo() || s.document().features().size() != 2) return fail("redo");

  // Sketch mode: rectangle from the origin with a hole, one dimension, finish.
  s.newDocument();
  using Tool = tsr::app::SketchEditor::Tool;
  auto* ed = w.startSketch(QStringLiteral("XY"));
  if (!ed) return fail("sketch mode did not start");
  if (w.startCommand(QStringLiteral("tsr.primitive.box"))) return fail("command started during sketch");
  ed->setTool(Tool::Rectangle);
  ed->clickAt(0, 0);   // snaps to the sketch origin
  ed->clickAt(4, 3);
  ed->setTool(Tool::Circle);
  ed->clickAt(2, 1.5);
  ed->clickAt(2.5, 1.5);
  if (ed->sketch().entities.size() != 5) return fail("rectangle + circle not drawn");
  ed->setTool(Tool::Dimension);
  ed->clickAt(2, 0);     // bottom edge
  ed->clickAt(9, 9);     // empty space: its length
  if (!ed->submitValue(QStringLiteral("50 mm"))) return fail("dimension box did not open");
  if (std::abs(ed->sketch().points[2].x - 5.0) > 1e-6) return fail("dimension did not drive the geometry");
  ed->undo();
  ed->redo();
  if (!w.finishSketch()) return fail("finish sketch");
  if (w.sketchEditor() || s.document().sketches().size() != 1) return fail("sketch not stored");

  // Extrude only the plate (not the disc) by 10 mm.
  auto* ex = w.startCommand(QStringLiteral("tsr.feature.extrude"));
  if (!ex || !ex->hasProfilesInput()) return fail("extrude dialog");
  ex->setProfiles(QStringLiteral("Sketch1"), QStringLiteral("0.3,0.3"));
  if (!ex->setInputForTest(QStringLiteral("distance"), 10.0)) return fail("extrude distance");
  ex->accept();
  QApplication::processEvents();
  const double pi = 3.14159265358979323846;
  auto volume = [&] {
    const auto b = s.document().bodies();
    return b.size() == 1 ? tsr::kernel::massProperties(b[0].shape).volume : -1.0;
  };
  if (std::abs(volume() - (15 - pi * 0.25)) > 1e-6) return fail("extrude volume");

  // Edit the sketch: make the hole 20 mm; the extrude follows.
  const int sketchId = s.document().features().front().id;
  ed = w.editSketch(sketchId);
  if (!ed) return fail("edit sketch");
  ed->setTool(Tool::Dimension);
  ed->clickAt(2.5, 1.5);   // the circle
  if (!ed->submitValue(QStringLiteral("20"))) return fail("diameter box");
  if (!w.finishSketch()) return fail("finish edited sketch");
  if (std::abs(volume() - (15 - pi)) > 1e-6) return fail("extrude did not follow the sketch edit");
  if (!s.undo() || std::abs(volume() - (15 - pi * 0.25)) > 1e-6) return fail("undo sketch edit");

  // Typed values while drawing: a 30 mm line and a 40 x 20 rectangle.
  s.newDocument();
  ed = w.startSketch(QStringLiteral("XY"));
  if (!ed) return fail("sketch for typed values");
  ed->setTool(Tool::Line);
  ed->clickAt(1, 1);
  if (!ed->typeValue(QStringLiteral("30"))) return fail("typed line length");
  ed->escape();
  ed->setTool(Tool::Rectangle);
  ed->clickAt(-5, -5);
  if (!ed->typeValue(QStringLiteral("40 x 20"))) return fail("typed rectangle");
  const auto& sk = ed->sketch();
  if (sk.entities.size() != 5) return fail("typed geometry count");
  const auto& l0 = sk.entities[0];
  if (std::abs(std::hypot(sk.points[l0.b].x - sk.points[l0.a].x, sk.points[l0.b].y - sk.points[l0.a].y) - 3.0) > 1e-9)
    return fail("typed line is not 30 mm");
  w.cancelSketch();

  // Sizes typed into the boxes before the shape exists.
  s.newDocument();
  ed = w.startSketch(QStringLiteral("XY"));
  ed->setTool(Tool::CenterRectangle);
  ed->clickAt(0, 0);
  if (!ed->typeValue(QStringLiteral("60 x 30"))) return fail("center rectangle sizes");
  ed->setTool(Tool::Polygon);
  ed->clickAt(10, 10);
  if (!ed->typeValue(QStringLiteral("20, 8"))) return fail("polygon diameter and sides");
  ed->setTool(Tool::Slot);
  ed->clickAt(-10, -10);
  if (!ed->typeValue(QStringLiteral("30 x 8"))) return fail("slot length and width");
  if (!ed->status().ok) return fail("typed shapes do not solve");
  {
    const auto& sk2 = ed->sketch();
    double minx = 1e9, maxx = -1e9;
    for (const auto& e : sk2.entities)
      if (e.type == tsr::sketch::EntityType::Line && !e.construction && std::abs(sk2.points[e.a].y - sk2.points[e.b].y) < 1e-9 &&
          std::abs(sk2.points[e.a].x) < 4 && std::abs(sk2.points[e.b].x) < 4) {
        minx = std::min({minx, sk2.points[e.a].x, sk2.points[e.b].x});
        maxx = std::max({maxx, sk2.points[e.a].x, sk2.points[e.b].x});
      }
    if (std::abs(maxx - minx - 6.0) > 1e-6) return fail("center rectangle is not 60 mm wide");
  }
  // Trim: a line across a circle loses its middle part.
  const size_t before = ed->sketch().entities.size();
  ed->setTool(Tool::Line);
  ed->clickAt(20, 0);
  ed->clickAt(40, 0);
  ed->escape();
  ed->setTool(Tool::Circle);
  ed->clickAt(30, 0);
  ed->clickAt(32, 0);
  ed->setTool(Tool::Trim);
  ed->clickAt(30.5, 0);   // on the line, inside the circle
  if (ed->sketch().entities.size() != before + 3) return fail("trim did not split the line");
  w.cancelSketch();

  // Fillet an edge through the dialog (edge picked as the canvas would).
  s.newDocument();
  if (!s.run("tsr.primitive.box", {{"length", 2.0}, {"width", 2.0}, {"height", 2.0}}).empty()) return fail("box");
  auto* fl = w.startCommand(QStringLiteral("tsr.feature.fillet"));
  if (!fl || !fl->hasEdgesInput()) return fail("fillet dialog");
  fl->setEdges(QStringLiteral("1,0,2"));
  if (!fl->setInputForTest(QStringLiteral("radius"), 5.0)) return fail("fillet radius");
  fl->accept();
  QApplication::processEvents();
  if (std::abs(volume() - (8 - (0.25 - pi * 0.25 / 4) * 2)) > 1e-6) return fail("fillet volume");
  if (s.document().features().back().name != "Fillet1") return fail("fillet feature");

  // Parameters: expressions typed into a panel's fields, Change Parameters
  // driving the model, and a sketch dimension given as an expression.
  s.newDocument();
  auto* pd = w.showParameters();
  if (!pd) return fail("parameters dialog");
  if (!pd->addParameter(QStringLiteral("size"), QStringLiteral("mm"), QStringLiteral("20 mm"), QString()).isEmpty())
    return fail("add parameter");
  QApplication::processEvents();
  auto* bx = w.startCommand(QStringLiteral("tsr.primitive.box"));
  if (!bx || !bx->setInputForTest(QStringLiteral("length"), QStringLiteral("size * 2")) ||
      !bx->setInputForTest(QStringLiteral("width"), QStringLiteral("size")) ||
      !bx->setInputForTest(QStringLiteral("height"), QStringLiteral("size / 2")))
    return fail("box expressions");
  bx->accept();
  QApplication::processEvents();
  if (std::abs(volume() - 4 * 2 * 1) > 1e-9) return fail("box from expressions");
  if (tsr::inputExpression(s.document().features()[0].inputs, "length") != "size * 2")
    return fail("expression not recorded");
  if (!pd->setExpressionForTest(QStringLiteral("size"), QStringLiteral("30 mm"))) return fail("parameter row");
  QApplication::processEvents();
  if (std::abs(volume() - 6 * 3 * 1.5) > 1e-9) return fail("box did not follow the parameter");
  if (!pd->setExpressionForTest(QStringLiteral("Box1.height"), QStringLiteral("size"))) return fail("model parameter row");
  QApplication::processEvents();
  if (std::abs(volume() - 6 * 3 * 3) > 1e-9) return fail("model parameter edit");
  pd->setExpressionForTest(QStringLiteral("size"), QStringLiteral("size + 1"));
  if (pd->errorText().isEmpty()) return fail("circular parameter accepted");
  QApplication::processEvents();
  pd->close();
  ed = w.startSketch(QStringLiteral("XY"));
  ed->setTool(Tool::Rectangle);
  ed->clickAt(20, 20);   // clear of the box, whose bottom edges would snap
  ed->clickAt(24, 23);
  ed->setTool(Tool::Dimension);
  ed->clickAt(22, 20);
  ed->clickAt(29, 29);
  if (!ed->submitValue(QStringLiteral("size * 2"))) return fail("dimension expression box");
  {
    const auto& sk = ed->sketch();
    const auto& bottom = sk.entities[0];
    if (std::abs(std::abs(sk.points[bottom.b].x - sk.points[bottom.a].x) - 6.0) > 1e-6)
      return fail("dimension expression did not drive the geometry");
  }
  if (ed->sketch().constraints.back().expression != "size * 2") return fail("dimension expression not kept");
  w.cancelSketch();

  // Rectangle size boxes: Tab from the canvas reaches the boxes, Tab moves
  // from width to height, Enter creates the rectangle.
  s.newDocument();
  ed = w.startSketch(QStringLiteral("XY"));
  ed->setTool(Tool::Rectangle);
  QApplication::processEvents();   // drop size boxes of earlier sketches (deleteLater)
  QCoreApplication::sendPostedEvents(nullptr, QEvent::DeferredDelete);
  ed->clickAt(0, 0);
  ed->hoverAt(1, 1);
  {
    auto key = [](QObject* to, int k) {
      QKeyEvent press(QEvent::KeyPress, k, Qt::NoModifier);
      QCoreApplication::sendEvent(to, &press);
    };
    key(w.viewport(), Qt::Key_Tab);   // must not move focus out of the canvas
    auto* wbox = w.viewport()->findChild<QLineEdit*>(QStringLiteral("hudWidth"));
    auto* hbox = w.viewport()->findChild<QLineEdit*>(QStringLiteral("hudHeight"));
    if (!wbox || !hbox) return fail("rectangle size boxes");
    wbox->setText(QStringLiteral("40"));
    emit wbox->textEdited(wbox->text());
    key(wbox, Qt::Key_Tab);
    hbox->setText(QStringLiteral("20"));
    emit hbox->textEdited(hbox->text());
    key(hbox, Qt::Key_Return);
  }
  if (ed->sketch().entities.size() != 4) return fail("Tab / Enter in the size boxes did not create the rectangle");
  if (!w.finishSketch()) return fail("finish rectangle sketch");

  // Extrude by dragging the arrow, then pull a face of the result.
  auto* ex2 = w.startCommand(QStringLiteral("tsr.feature.extrude"));
  if (!ex2 || !w.viewport()->dragArrowActive()) return fail("extrude arrow");
  w.viewport()->dragArrowForTest(1.5);
  if (std::abs(ex2->realInput(QStringLiteral("distance")).value_or(0) - 1.5) > 1e-9) return fail("arrow did not set the distance");
  ex2->accept();
  QApplication::processEvents();
  if (std::abs(volume() - 4 * 2 * 1.5) > 1e-6) return fail("arrow extrude volume");
  auto* ex3 = w.startCommand(QStringLiteral("tsr.feature.extrude"));
  {
    TopoDS_Shape top;
    double zmax = -1e9;
    for (TopExp_Explorer it(s.document().bodies().front().shape, TopAbs_FACE); it.More(); it.Next()) {
      GProp_GProps g;
      BRepGProp::SurfaceProperties(it.Current(), g);
      if (g.CentreOfMass().Z() > zmax) {
        zmax = g.CentreOfMass().Z();
        top = it.Current();
      }
    }
    emit w.viewport()->subShapeClicked(QStringLiteral("Body1"), top);   // as a click on the top face
  }
  if (ex3->currentFaces().isEmpty() || ex3->textInput(QStringLiteral("operation")) != QLatin1String("Join"))
    return fail("face pick for extrude");
  if (!w.viewport()->dragArrowActive()) return fail("face extrude arrow");
  w.viewport()->dragArrowForTest(0.5);
  ex3->accept();
  QApplication::processEvents();
  if (s.document().bodies().size() != 1 || std::abs(volume() - 4 * 2 * 2.0) > 1e-6) return fail("face extrude volume");

  // Sketch Palette: feature options, linetype, display options, Finish.
  s.newDocument();
  ed = w.startSketch(QStringLiteral("XY"));
  auto* pal = w.sketchPalette();
  if (!ed || !pal || !pal->isVisible()) return fail("sketch palette");
  auto paletteButton = [&](const char* name) { return pal->findChild<QAbstractButton*>(QString::fromLatin1(name)); };
  ed->setTool(Tool::Rectangle);
  pal->sync();
  paletteButton("palette.rectCenter")->click();
  if (ed->tool() != Tool::CenterRectangle) return fail("palette feature option");
  paletteButton("palette.linetypeConstruction")->click();
  if (!ed->construction()) return fail("palette linetype");
  paletteButton("palette.linetypeNormal")->click();
  paletteButton("palette.dimensions")->click();
  paletteButton("palette.points")->click();
  if (ed->display().dimensions || ed->display().points || !ed->display().profiles) return fail("palette display options");
  paletteButton("palette.grid")->click();
  if (w.viewport()->gridVisible()) return fail("palette sketch grid");
  paletteButton("palette.grid")->click();
  ed->clickAt(0, 0);
  ed->clickAt(2, 1);
  paletteButton("palette.finish")->click();
  QApplication::processEvents();
  if (w.sketchEditor() || w.sketchPalette() || s.document().sketches().size() != 1) return fail("palette Finish Sketch");

  // Sketch Fillet, Offset and Spline through the tools and size boxes.
  s.newDocument();
  ed = w.startSketch(QStringLiteral("XY"));
  ed->setTool(Tool::Rectangle);
  ed->clickAt(0, 0);
  ed->clickAt(4, 3);
  ed->setTool(Tool::Fillet);
  ed->clickAt(4, 3);   // the corner
  ed->hoverAt(4.5, 3.5);
  if (!ed->typeValue(QStringLiteral("5"))) return fail("fillet radius box");
  {
    int arcs = 0;
    for (const auto& e : ed->sketch().entities) arcs += e.type == tsr::sketch::EntityType::Arc;
    if (arcs != 1 || !ed->status().ok) return fail("fillet did not round the corner");
  }
  const size_t beforeOffset = ed->sketch().entities.size();
  ed->setTool(Tool::Offset);
  ed->clickAt(2, 0);   // bottom edge: the whole outline is offset
  ed->hoverAt(2, -1);  // outside
  if (!ed->typeValue(QStringLiteral("10"))) return fail("offset box");
  if (ed->sketch().entities.size() != beforeOffset + 5 || !ed->status().ok) return fail("offset of the outline");
  ed->setTool(Tool::Spline);
  ed->clickAt(10, 0);
  ed->clickAt(12, 3);
  ed->clickAt(11, 6);
  ed->escape();
  if (ed->sketch().entities.back().type != tsr::sketch::EntityType::Spline || ed->sketch().entities.back().fit.size() != 3)
    return fail("spline");
  if (!w.finishSketch()) return fail("finish sketch with fillet/offset/spline");

  // Line tool snapping: to a line's midpoint (with a midpoint constraint)
  // and horizontal from the previous point.
  s.newDocument();
  ed = w.startSketch(QStringLiteral("XY"));
  ed->setTool(Tool::Line);
  ed->clickAt(0, 0);
  ed->clickAt(4, 0);
  ed->escape();
  ed->clickAt(2.02, 0.01);   // near the middle of that line
  ed->clickAt(2, 2);
  ed->clickAt(4.5, 2.03);    // nearly level with the previous point
  ed->escape();
  {
    const auto& sk = ed->sketch();
    bool mid = false;
    for (const auto& c : sk.constraints) mid = mid || c.type == tsr::sketch::ConstraintType::Midpoint;
    if (!mid) return fail("line did not snap to the midpoint");
    const auto& last = sk.entities.back();
    if (std::abs(sk.points[last.a].y - sk.points[last.b].y) > 1e-9) return fail("line did not snap horizontal");
  }
  w.cancelSketch();

  // Line tool: drag from the end for a tangent arc; tangent and
  // perpendicular inference; snapping onto a body edge projects it.
  s.newDocument();
  if (!s.run("tsr.primitive.box", {{"length", 2.0}, {"width", 2.0}, {"height", 2.0}, {"x", 10.0}}).empty()) return fail("box for projection");
  if (!s.run("tsr.primitive.cylinder", {{"diameter", 2.0}, {"height", 1.0}, {"x", 30.0}}).empty()) return fail("cylinder for projection");
  ed = w.startSketch(QStringLiteral("XY"));
  ed->setTool(Tool::Line);
  ed->clickAt(0, 0);
  ed->clickAt(4, 0);
  if (!ed->dragTangentArcForTest(6, 2)) return fail("tangent arc drag");
  {
    const auto& sk = ed->sketch();
    const auto& arc = sk.entities.back();
    if (arc.type != tsr::sketch::EntityType::Arc || std::abs(arc.radius - 2) > 1e-6 || !ed->status().ok)
      return fail("tangent arc geometry");
  }
  ed->clickAt(6.03, 4);   // straight on from the arc's end: tangent
  {
    const auto& sk = ed->sketch();
    const auto& l = sk.entities.back();
    if (std::abs(sk.points[l.a].x - sk.points[l.b].x) > 1e-6) return fail("tangent inference");
    int tangents = 0;
    for (const auto& c : sk.constraints) tangents += c.type == tsr::sketch::ConstraintType::Tangent;
    if (tangents < 2) return fail("tangent constraints from the arc");
  }
  ed->escape();
  ed->clickAt(0, 6);
  ed->clickAt(3, 7);
  ed->clickAt(2.35, 9.0);   // close to perpendicular to the previous line (exact: 2.333, 9)
  {
    const auto& sk = ed->sketch();
    bool perp = false;
    for (const auto& c : sk.constraints) perp = perp || c.type == tsr::sketch::ConstraintType::Perpendicular;
    if (!perp) return fail("perpendicular inference");
  }
  ed->escape();
  ed->clickAt(0, 20);
  ed->clickAt(3, 21);       // an oblique line
  ed->escape();
  ed->clickAt(0, 23);
  ed->clickAt(3.02, 24.0);  // nearly parallel to it
  ed->escape();
  {
    bool par = false;
    for (const auto& c : ed->sketch().constraints) par = par || c.type == tsr::sketch::ConstraintType::Parallel;
    if (!par) return fail("parallel inference");
  }
  ed->clickAt(11, 0.01);    // on the box's bottom edge (in the sketch plane)
  ed->clickAt(11, -2);
  ed->escape();
  {
    bool projected = false;
    for (const auto& e : ed->sketch().entities) projected = projected || e.projected;
    if (!projected || !ed->status().ok) return fail("body edge projection");
  }
  ed->clickAt(30, 1.01);    // on the cylinder's bottom circle
  ed->clickAt(30, 3);
  ed->escape();
  {
    bool circle = false;
    for (const auto& e : ed->sketch().entities) circle = circle || (e.projected && e.type == tsr::sketch::EntityType::Circle);
    if (!circle || !ed->status().ok) return fail("curved body edge projection");
  }
  w.cancelSketch();

  // Regression: picking a face of the extrude's own preview, then Two Sides
  // and dragging, must not crash (the preview body is not a real body).
  s.newDocument();
  ed = w.startSketch(QStringLiteral("XY"));
  ed->setTool(Tool::Rectangle);
  ed->clickAt(0, 0);
  ed->clickAt(2, 1);
  if (!w.finishSketch()) return fail("sketch for two-sided extrude");
  {
    auto* ex4 = w.startCommand(QStringLiteral("tsr.feature.extrude"));
    if (!ex4 || s.document().bodies().size() != 1) return fail("extrude preview body");
    TopoDS_Shape face;
    for (TopExp_Explorer it(s.document().bodies().front().shape, TopAbs_FACE); it.More(); it.Next()) face = it.Current();
    emit w.viewport()->subShapeClicked(QString::fromStdString(s.document().bodies().front().name), face);
    QApplication::processEvents();
    if (!ex4->currentFaces().isEmpty()) return fail("a face of the extrude's own preview was picked");
    ex4->setInputForTest(QStringLiteral("direction"), QStringLiteral("Two Sides"));
    w.viewport()->dragArrowForTest(1.5);
    w.viewport()->dragArrowForTest(-1.0);   // past side 2: reported, not a crash
    ex4->setInputForTest(QStringLiteral("distance2"), 5.0);   // panel units: mm
    w.viewport()->dragArrowForTest(1.0);
    // Two Sides shows a second arrow, pointing the other way, for side 2.
    if (!w.viewport()->dragArrowActive(1)) return fail("two-sided extrude second arrow");
    w.viewport()->dragArrowForTest(0.8, 1);
    QApplication::processEvents();
    if (std::abs(ex4->realInput(QStringLiteral("distance2")).value_or(0) - 0.8) > 1e-9) return fail("second arrow sets side 2");
    ex4->accept();
    QApplication::processEvents();
    if (s.document().bodies().size() != 1 || std::abs(volume() - 2 * 1 * 1.8) > 1e-6) return fail("two-sided extrude volume");
  }
  // Section Analysis: pick a plane, then drag the arrow to set the depth.
  w.openSectionAnalysis();
  if (!w.sectionPanel()) return fail("section panel");
  emit w.viewport()->planePicked(QStringLiteral("XY"), QStringLiteral("XY plane"));
  if (!w.sectionActive() || !w.viewport()->dragArrowActive()) return fail("section after picking a plane");
  w.viewport()->dragArrowForTest(0.5);
  if (std::abs(w.sectionOffset() - 0.5) > 1e-9) return fail("section arrow did not move the plane");
  w.sectionPanel()->accept();
  QApplication::processEvents();
  if (w.sectionPanel() || w.viewport()->dragArrowActive()) return fail("section panel close");
  // Inspect analyses: each opens, shows, and Remove clears it.
  for (int k = 0; k < 4; ++k) {
    auto* panel = w.openAnalysis(k);
    if (!panel) return fail("analysis panel");
    if (k < 3 && w.viewport()->analysis().kind == tsr::app::AnalysisKind::None) return fail("analysis not shown");
    if (auto* rm = panel->findChild<QAbstractButton*>(QStringLiteral("analysisRemove"))) rm->click();
    QApplication::processEvents();
    if (w.analysisPanel() || w.viewport()->analysis().kind != tsr::app::AnalysisKind::None) return fail("analysis remove");
  }
  // Symmetry on two circles about a line: mirrored centres, equal sizes.
  s.newDocument();
  {
    auto* se = w.startSketch(QStringLiteral("XY"));
    if (!se) return fail("sketch for symmetry");
    se->setTool(Tool::Circle);
    se->clickAt(-2, 1);
    se->clickAt(-1.5, 1);     // r 0.5
    se->setTool(Tool::Circle);
    se->clickAt(3, 1.5);
    se->clickAt(3.8, 1.5);    // r 0.8
    se->setTool(Tool::Line);
    se->clickAt(0.3, -3);
    se->clickAt(0.3, 4);
    se->escape();
    int c1 = -1, c2 = -1, ln = -1;
    for (int i = 0; i < static_cast<int>(se->sketch().entities.size()); ++i) {
      const auto& e = se->sketch().entities[i];
      if (e.type == tsr::sketch::EntityType::Circle) (c1 < 0 ? c1 : c2) = i;
      if (e.type == tsr::sketch::EntityType::Line) ln = i;
    }
    if (c1 < 0 || c2 < 0 || ln < 0) return fail("symmetry geometry");
    se->setTool(Tool::Symmetry);
    se->clickAt(-1.5, 1);     // on the first circle
    se->clickAt(3.8, 1.5);    // on the second
    se->clickAt(0.3, 2);      // the line
    const auto& sk = se->sketch();
    const auto& a = sk.entities[c1];
    const auto& b = sk.entities[c2];
    const auto& pa = sk.points[a.center];
    const auto& pb = sk.points[b.center];
    const auto& l0 = sk.points[sk.entities[ln].a];
    if (std::abs(a.radius - b.radius) > 1e-6 || std::abs(pa.y - pb.y) > 1e-6 ||
        std::abs((pa.x + pb.x) / 2 - l0.x) > 1e-6)
      return fail("symmetry of two circles");
    w.cancelSketch();
  }
  // Browser: a fully defined sketch shows a lock; V hides the current body;
  // a construction plane's double-click no longer opens Change Parameters.
  s.newDocument();
  {
    if (!s.run("tsr.primitive.box", {{"length", 1.0}, {"width", 1.0}, {"height", 1.0}}).empty()) return fail("box for browser");
    const std::string data =
        R"({"points":[[0,0],[1,0]],"entities":[{"type":"line","p":[0,1]}],)"
        R"("constraints":[{"type":"horizontal","e":[0]},{"type":"distance","e":[0],"v":1.0}]})";
    if (const auto err = s.run("tsr.sketch.create", {{"plane", std::string("XY")}, {"data", data}}); !err.empty())
      return fail(("defined sketch: " + err).c_str());
    QApplication::processEvents();
    QTreeWidgetItem* skItem = nullptr;
    QTreeWidgetItem* bodyItem = nullptr;
    for (QTreeWidgetItemIterator it(w.browser()); *it; ++it) {
      if ((*it)->text(0) == QLatin1String("Sketch1")) skItem = *it;
      if ((*it)->text(0) == QLatin1String("Body1")) bodyItem = *it;
    }
    if (!skItem || !skItem->data(0, Qt::UserRole + 9).toBool()) return fail("fully defined sketch has no lock");
    if (!bodyItem) return fail("browser body item");
    w.browser()->setCurrentItem(bodyItem);
    w.toggleSelectedVisibility();
    QApplication::processEvents();
    if (w.viewport()->isBodyVisible(QStringLiteral("Body1"))) return fail("V did not hide the body");
    w.toggleSelectedVisibility();
    QApplication::processEvents();
  }
  // Marking menu: Create Sketch from the ring starts plane picking / sketch.
  s.newDocument();
  {
    auto* mm = w.openMarkingMenu(QPoint(400, 400));
    if (!mm || !mm->triggerForTest(QStringLiteral("Extrude"))) return fail("marking menu Extrude");
    QApplication::processEvents();
    auto* exm = w.findChild<tsr::app::CommandDialog*>(QStringLiteral("tsr.feature.extrude"));
    if (!exm) return fail("marking menu did not start Extrude");
    exm->reject();
    QApplication::processEvents();
  }
  std::puts("smoke: OK");
  return 0;
}

} // namespace

// Where things are on screen, for an external input driver: the window, the
// canvas, every named visible button / field / combo, open panels, and (in
// a sketch) where sketch points (0,0), (1,0) and (0,1) cm appear.
// The window plus any tool windows / panels drawn over it.
QPixmap grabWindowWithPanels(QWidget& window) {
  QPixmap shot = window.grab();
  QPainter p(&shot);
  for (QWidget* top : QApplication::topLevelWidgets())
    if (top != &window && top->isVisible() && top->parentWidget() == &window)
      p.drawPixmap(top->frameGeometry().topLeft() - window.frameGeometry().topLeft(), top->grab());
  return shot;
}

void writeLiveGeometry(tsr::app::MainWindow& w, const QString& file) {
  // Requests from the driver: a screenshot, or quitting.
  if (QFile req(file + QStringLiteral(".shot")); req.exists() && req.open(QIODevice::ReadOnly)) {
    const QString out = QString::fromUtf8(req.readAll()).trimmed();
    req.close();
    grabWindowWithPanels(w).save(out);
    QFile::remove(file + QStringLiteral(".shot"));
  }
  if (QFile::exists(file + QStringLiteral(".quit"))) {
    QFile::remove(file + QStringLiteral(".quit"));
    QApplication::exit(0);
    return;
  }
  auto rect = [](QWidget* x) {
    const QPoint p = x->mapToGlobal(QPoint(0, 0));
    return QJsonArray{p.x(), p.y(), x->width(), x->height()};
  };
  QJsonObject o;
  o[QStringLiteral("window")] = rect(&w);
  o[QStringLiteral("viewport")] = rect(w.viewport());
  QJsonObject widgets;
  for (QWidget* x : w.findChildren<QWidget*>()) {
    if (x->objectName().isEmpty() || !x->isVisible()) continue;
    if (!qobject_cast<QAbstractButton*>(x) && !qobject_cast<QLineEdit*>(x) && !qobject_cast<QComboBox*>(x) &&
        !qobject_cast<QAbstractSpinBox*>(x) && !qobject_cast<QAbstractSlider*>(x) && !x->property("panel").toBool())
      continue;
    // The first visible one of a name wins (ribbon buttons before menu copies).
    if (!widgets.contains(x->objectName())) widgets[x->objectName()] = rect(x);
  }
  // Popups (menus, value suggestions) are windows of their own.
  for (QWidget* top : QApplication::topLevelWidgets())
    if (top != &w && top->isVisible() && !top->objectName().isEmpty() && !widgets.contains(top->objectName()))
      widgets[top->objectName()] = rect(top);
  o[QStringLiteral("widgets")] = widgets;
  {
    // Timeline items by feature name (centre, global coordinates).
    QJsonObject items;
    QListWidget* tl = w.timeline();
    for (int i = 0; i < tl->count(); ++i) {
      QListWidgetItem* it = tl->item(i);
      const QRect r = tl->visualItemRect(it);
      const QPoint g = tl->viewport()->mapToGlobal(r.center());
      items[it->data(Qt::AccessibleTextRole).toString()] = QJsonArray{g.x(), g.y()};
    }
    o[QStringLiteral("timeline")] = items;
    // Browser items by text (first visible one wins), centre in global coordinates.
    QJsonObject tree;
    QTreeWidget* br = w.browser();
    for (QTreeWidgetItemIterator it(br); *it; ++it) {
      const QRect r = br->visualItemRect(*it);
      if (r.isEmpty() || tree.contains((*it)->text(0))) continue;
      const QPoint g = br->viewport()->mapToGlobal(r.center());
      tree[(*it)->text(0)] = QJsonArray{g.x(), g.y()};
    }
    o[QStringLiteral("browser")] = tree;
  }
  {
    // World axes (1 cm each) on screen: an affine map for the (orthographic) view.
    auto at = [&](double x, double y, double z) {
      const QPoint g = w.viewport()->mapToGlobal(w.viewport()->toWidget(gp_Pnt(x, y, z)).toPoint());
      return QJsonArray{g.x(), g.y()};
    };
    o[QStringLiteral("world")] = QJsonObject{{QStringLiteral("o"), at(0, 0, 0)}, {QStringLiteral("x"), at(1, 0, 0)},
                                             {QStringLiteral("y"), at(0, 1, 0)}, {QStringLiteral("z"), at(0, 0, 1)}};
  }
  if (const auto h = w.viewport()->dragArrowHandle()) {
    const QPoint g = w.viewport()->mapToGlobal(h->toPoint());
    o[QStringLiteral("arrow")] = QJsonArray{g.x(), g.y()};
  }
  if (const auto h = w.viewport()->dragArrowHandle(1)) {
    const QPoint g = w.viewport()->mapToGlobal(h->toPoint());
    o[QStringLiteral("arrow2")] = QJsonArray{g.x(), g.y()};
  }
  if (w.viewport()->planePicking()) {
    QJsonObject planes;
    for (const auto& [spec, p] : w.viewport()->planeCentres()) {
      const QPoint g = w.viewport()->mapToGlobal(w.viewport()->toWidget(p).toPoint());
      planes[QString::fromStdString(spec)] = QJsonArray{g.x(), g.y()};
    }
    o[QStringLiteral("planes")] = planes;
  }
  if (auto* ed = w.sketchEditor()) {
    auto at = [&](double x, double y) {
      const QPointF p = w.viewport()->toWidget(tsr::sketch::toWorld(ed->frame(), x, y));
      const QPoint g = w.viewport()->mapToGlobal(p.toPoint());
      return QJsonArray{g.x(), g.y()};
    };
    o[QStringLiteral("sketch")] = QJsonObject{{QStringLiteral("o"), at(0, 0)}, {QStringLiteral("x"), at(1, 0)},   // 1 cm = 10 mm
                                              {QStringLiteral("y"), at(0, 1)}};
  }
  QFile f(file + QStringLiteral(".tmp"));
  if (f.open(QIODevice::WriteOnly)) {
    f.write(QJsonDocument(o).toJson(QJsonDocument::Compact));
    f.close();
    QFile::remove(file);
    QFile::rename(file + QStringLiteral(".tmp"), file);
  }
}

int main(int argc, char** argv) {
  // OCCT's OpenGL driver on Kubuntu talks GLX, so on a Wayland desktop run
  // through XWayland unless the user chose a platform explicitly.
  if (!qEnvironmentVariableIsSet("QT_QPA_PLATFORM") && qEnvironmentVariableIsSet("WAYLAND_DISPLAY") &&
      qEnvironmentVariableIsSet("DISPLAY"))
    qputenv("QT_QPA_PLATFORM", "xcb");
  QApplication::setAttribute(Qt::AA_ShareOpenGLContexts);

  QApplication app(argc, argv);
  QApplication::setApplicationName(QStringLiteral("Tessera"));
  QApplication::setOrganizationDomain(QStringLiteral("tessera.org"));
  QApplication::setApplicationVersion(QStringLiteral(TSR_VERSION_STRING));
  QApplication::setDesktopFileName(QStringLiteral("org.tessera.Tessera"));
  QApplication::setWindowIcon(QIcon::fromTheme(QStringLiteral("org.tessera.Tessera")));
  tsr::app::Theme::instance().apply(tsr::app::Theme::saved(), /*save=*/false);

  QCommandLineParser parser;
  parser.setApplicationDescription(QStringLiteral("Tessera — precision, joined."));
  parser.addHelpOption();
  parser.addVersionOption();
  QCommandLineOption smokeOpt(QStringLiteral("smoke"), QStringLiteral("Run the GUI smoke test and exit."));
  QCommandLineOption scriptOpt(QStringLiteral("script"), QStringLiteral("Run a Python script after startup."),
                               QStringLiteral("file.py"));
  QCommandLineOption shotOpt(QStringLiteral("screenshot"),
                             QStringLiteral("Save a PNG of the window once it has rendered, then exit."),
                             QStringLiteral("file.png"));
  QCommandLineOption editSketchOpt(QStringLiteral("edit-sketch"),
                                   QStringLiteral("Open this sketch in sketch mode after startup (screenshots)."),
                                   QStringLiteral("name"));
  parser.addOption(editSketchOpt);
  QCommandLineOption commandOpt(QStringLiteral("start-command"),
                                QStringLiteral("Open this command's dialog after startup (screenshots)."), QStringLiteral("id"));
  parser.addOption(commandOpt);
  QCommandLineOption hudOpt(QStringLiteral("demo-hud"), QStringLiteral("Start a rectangle with its size boxes (screenshots)."));
  parser.addOption(hudOpt);
  // Live GUI testing on a (virtual) X display: an external driver injects real
  // mouse/keyboard events (scripts/xdrive.py) and reads where things are.
  QCommandLineOption geometryOpt(QStringLiteral("live-geometry"),
                                 QStringLiteral("Keep writing widget and sketch positions (screen pixels) to this JSON file."),
                                 QStringLiteral("file"));
  parser.addOption(geometryOpt);
  QCommandLineOption saveExitOpt(QStringLiteral("save-on-exit"), QStringLiteral("Save the design here when quitting."),
                                 QStringLiteral("file"));
  parser.addOption(saveExitOpt);
  QCommandLineOption quitOpt(QStringLiteral("quit-after"), QStringLiteral("Quit after this many milliseconds."),
                             QStringLiteral("ms"));
  parser.addOption(quitOpt);
  parser.addOption(smokeOpt);
  parser.addOption(scriptOpt);
  parser.addOption(shotOpt);
  parser.addPositionalArgument(QStringLiteral("file"), QStringLiteral("Design to open (.tsr)."), QStringLiteral("[file]"));
  parser.process(app);

  tsr::doc::Session session;
  tsr::api::PythonHost python(session);
  tsr::app::MainWindow window(session, python);

  if (!parser.positionalArguments().isEmpty()) {
    try {
      session.open(parser.positionalArguments().first().toStdString());
    } catch (const std::exception& e) {
      std::fprintf(stderr, "tessera: %s\n", e.what());
    }
  }

  if (parser.isSet(smokeOpt)) {
    window.show();
    return smoke(window, session);
  }

  window.show();
  if (parser.isSet(geometryOpt)) {
    const QString file = parser.value(geometryOpt);
    auto* timer = new QTimer(&window);
    QObject::connect(timer, &QTimer::timeout, &window, [&window, file] { writeLiveGeometry(window, file); });
    timer->start(200);
  }
  if (parser.isSet(saveExitOpt)) {
    const std::string out = parser.value(saveExitOpt).toStdString();
    QObject::connect(&app, &QCoreApplication::aboutToQuit, &window, [&session, out] {
      try {
        session.save(out);
      } catch (const std::exception& e) {
        std::fprintf(stderr, "tessera: save-on-exit: %s\n", e.what());
      }
    });
  }
  if (parser.isSet(quitOpt))
    QTimer::singleShot(parser.value(quitOpt).toInt(), &app, [] { QApplication::exit(0); });
  if (parser.isSet(scriptOpt)) {
    const auto r = python.runScript(parser.value(scriptOpt).toStdString());
    std::fputs(r.output.c_str(), stdout);
    if (!r.ok) {
      std::fprintf(stderr, "tessera: script failed: %s\n", r.error.c_str());
      return 1;
    }
    window.viewport()->fitAll();
  }
  if (parser.isSet(hudOpt)) {
    QTimer::singleShot(500, &window, [&window] {
      if (auto* ed = window.startSketch(QStringLiteral("XY"))) {
        ed->setTool(tsr::app::SketchEditor::Tool::Rectangle);
        ed->clickAt(0, 0);
        ed->hoverAt(4.0, 2.5);
      }
    });
  }
  if (parser.isSet(commandOpt)) {
    const QString id = parser.value(commandOpt);
    QTimer::singleShot(400, &window, [&window, id] {
      // Ribbon tools that are not document commands ("ui.changeParameters").
      if (id.startsWith(QLatin1String("ui."))) {
        if (auto* a = window.ribbon()->findChild<QAction*>(id)) a->trigger();
        return;
      }
      window.startCommand(id);
    });
  }
  if (parser.isSet(editSketchOpt)) {
    // After the window is up, as when a user double-clicks the sketch.
    const std::string name = parser.value(editSketchOpt).toStdString();
    QTimer::singleShot(400, &window, [&window, &session, name] {
      for (const auto& f : session.document().features())
        if (f.name == name) window.editSketch(f.id);
    });
  }
  if (parser.isSet(shotOpt)) {
    const QString out = parser.value(shotOpt);
    QTimer::singleShot(1500, &window, [&window, out] {
      // The window plus any tool windows open over it (Parameters, Measure).
      const bool ok = grabWindowWithPanels(window).save(out);
      std::fprintf(ok ? stdout : stderr, "screenshot %s: %s\n", ok ? "saved" : "FAILED", qPrintable(out));
      const bool view3d = window.viewport()->available();
      if (!view3d) std::fprintf(stderr, "screenshot: %s\n", qPrintable(window.viewport()->unavailableReason()));
      QApplication::exit(!ok ? 1 : view3d ? 0 : 3); // 3: window fine, but no 3D view
    });
  }
  return app.exec();
}
