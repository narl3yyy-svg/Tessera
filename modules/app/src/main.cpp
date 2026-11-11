#include "CommandDialog.h"
#include "MainWindow.h"
#include "Viewport.h"

#include "tsr/doc/DocCommands.h"

#include <QApplication>
#include <QCommandLineParser>
#include <QListWidget>
#include <QTabWidget>
#include <QTimer>
#include <QToolButton>
#include <QTreeWidget>

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
  for (const tsr::Command* c : s.commands().all())
    if (!w.ribbon()->findChild<QToolButton*>(QString::fromStdString(c->def().id))) return fail("ribbon button missing");

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
  if (parser.isSet(shotOpt)) {
    const QString out = parser.value(shotOpt);
    QTimer::singleShot(1500, &window, [&window, out] {
      const bool ok = window.grab().save(out);
      std::fprintf(ok ? stdout : stderr, "screenshot %s: %s\n", ok ? "saved" : "FAILED", qPrintable(out));
      const bool view3d = window.viewport()->available();
      if (!view3d) std::fprintf(stderr, "screenshot: %s\n", qPrintable(window.viewport()->unavailableReason()));
      QApplication::exit(!ok ? 1 : view3d ? 0 : 3); // 3: window fine, but no 3D view
    });
  }
  return app.exec();
}
