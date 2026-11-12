#include "CommandDialog.h"
#include "MainWindow.h"
#include "ParametersDialog.h"
#include "SketchEditor.h"
#include "Theme.h"
#include "Viewport.h"

#include "tsr/doc/DocCommands.h"
#include "tsr/kernel/Kernel.h"

#include <QApplication>
#include <QCommandLineParser>
#include <QListWidget>
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
  if (!cyl->setInputForTest(QStringLiteral("x"), 10.0) || !cyl->setInputForTest(QStringLiteral("y"), 5.0))
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
  ed->clickAt(0, 0);
  ed->clickAt(4, 3);
  ed->setTool(Tool::Dimension);
  ed->clickAt(2, 0);
  ed->clickAt(9, 9);
  if (!ed->submitValue(QStringLiteral("size * 2"))) return fail("dimension expression box");
  if (std::abs(ed->sketch().points[2].x - 6.0) > 1e-6) return fail("dimension expression did not drive the geometry");
  if (ed->sketch().constraints.back().expression != "size * 2") return fail("dimension expression not kept");
  w.cancelSketch();
  std::puts("smoke: OK");
  return 0;
}

} // namespace

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
      QPixmap shot = window.grab();
      {
        QPainter p(&shot);
        for (QWidget* top : QApplication::topLevelWidgets())
          if (top != &window && top->isVisible() && top->parentWidget() == &window)
            p.drawPixmap(top->frameGeometry().topLeft() - window.frameGeometry().topLeft(), top->grab());
      }
      const bool ok = shot.save(out);
      std::fprintf(ok ? stdout : stderr, "screenshot %s: %s\n", ok ? "saved" : "FAILED", qPrintable(out));
      const bool view3d = window.viewport()->available();
      if (!view3d) std::fprintf(stderr, "screenshot: %s\n", qPrintable(window.viewport()->unavailableReason()));
      QApplication::exit(!ok ? 1 : view3d ? 0 : 3); // 3: window fine, but no 3D view
    });
  }
  return app.exec();
}
