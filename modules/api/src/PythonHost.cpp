#include "tsr/api/PythonHost.h"
#include "Bindings.h"

#include <pybind11/embed.h>

#include <fstream>
#include <memory>
#include <sstream>
#include <stdexcept>

namespace py = pybind11;

// Registered via PyImport_AppendInittab before the interpreter starts. Kept in
// this TU so the linker cannot drop the registrars from the static library.
PYBIND11_EMBEDDED_MODULE(adsk, m) { tsr::api::bindAdsk(m); }
PYBIND11_EMBEDDED_MODULE(tsr, m) { tsr::api::bindTsr(m); }

namespace tsr::api {

namespace {
doc::Session* g_session = nullptr;
std::unique_ptr<py::scoped_interpreter> g_interp;

// Runs fn with sys.stdout/sys.stderr captured into the result.
template <class Fn>
PythonHost::Result captured(Fn&& fn) {
  PythonHost::Result r;
  py::module_ sys = py::module_::import("sys");
  py::object buf = py::module_::import("io").attr("StringIO")();
  py::object oldOut = sys.attr("stdout"), oldErr = sys.attr("stderr");
  sys.attr("stdout") = buf;
  sys.attr("stderr") = buf;
  try {
    fn();
    r.ok = true;
  } catch (py::error_already_set& e) {
    r.error = e.what();
  } catch (const std::exception& e) {
    r.error = e.what();
  }
  sys.attr("stdout") = oldOut;
  sys.attr("stderr") = oldErr;
  r.output = buf.attr("getvalue")().cast<std::string>();
  return r;
}
} // namespace

doc::Session& activeSession() {
  if (!g_session) throw std::runtime_error("no active Tessera session");
  return *g_session;
}

PythonHost::PythonHost(doc::Session& session) {
  if (g_session) throw std::logic_error("only one PythonHost per process");
  g_session = &session;
  g_interp = std::make_unique<py::scoped_interpreter>();
  // `adsk` is a single builtin module; publishing its submodules in
  // sys.modules makes `import adsk.core, adsk.fusion` work unmodified.
  py::module_ adsk = py::module_::import("adsk");
  py::dict modules = py::module_::import("sys").attr("modules");
  for (const char* sub : {"core", "fusion"})
    modules[py::str(std::string("adsk.") + sub)] = adsk.attr(sub);
  adsk.attr("__path__") = py::list();
}

PythonHost::~PythonHost() {
  g_interp.reset();
  g_session = nullptr;
}

PythonHost::Result PythonHost::runScript(const std::filesystem::path& path) {
  std::ifstream f(path, std::ios::binary);
  if (!f) return {false, {}, "cannot open script " + path.string()};
  std::stringstream ss;
  ss << f.rdbuf();
  const std::string code = ss.str();

  return captured([&] {
    py::dict globals;
    globals["__name__"] = "__main__";
    globals["__file__"] = path.string();
    globals["__builtins__"] = py::module_::import("builtins");
    py::exec(code, globals);
    if (globals.contains("run")) {
      py::dict context;
      context["IsApplicationStartup"] = false;
      globals["run"](context);
    }
  });
}

PythonHost::Result PythonHost::exec(const std::string& code) {
  return captured([&] { py::exec(code); });
}

} // namespace tsr::api
