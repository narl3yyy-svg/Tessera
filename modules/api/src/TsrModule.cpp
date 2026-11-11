// `tsr`: Tessera-only scripting helpers. Not part of the adsk surface.
// This is the generic path that makes every registered command scriptable
// (plan §4.2: API-callable before UI-callable) and drives scripted tests.
#include "Bindings.h"
#include "tsr/api/PythonHost.h"

#include <pybind11/stl.h>

namespace py = pybind11;

namespace tsr::api {

namespace {
const char* typeName(InputType t) {
  switch (t) {
    case InputType::Real: return "real";
    case InputType::Integer: return "integer";
    case InputType::Bool: return "bool";
    case InputType::String: return "string";
  }
  return "?";
}

py::object toPy(const Value& v) {
  return std::visit([](const auto& x) -> py::object {
    using T = std::decay_t<decltype(x)>;
    if constexpr (std::is_same_v<T, std::monostate>) return py::none();
    else return py::cast(x);
  }, v);
}

Value fromPy(const py::handle& o) {
  if (o.is_none()) return std::monostate{};
  if (py::isinstance<py::bool_>(o)) return o.cast<bool>();
  if (py::isinstance<py::int_>(o)) return o.cast<std::int64_t>();
  if (py::isinstance<py::float_>(o)) return o.cast<double>();
  if (py::isinstance<py::str>(o)) return o.cast<std::string>();
  throw py::type_error("unsupported input value type");
}
} // namespace

void bindTsr(py::module_& m) {
  m.doc() = "Tessera scripting helpers";

  m.def("commands", [] {
    py::list out;
    for (const Command* c : activeSession().commands().all()) {
      const CommandDef& d = c->def();
      py::list inputs;
      for (const auto& i : d.inputs) {
        py::dict di;
        di["id"] = i.id;
        di["label"] = i.label;
        di["type"] = typeName(i.type);
        di["default"] = toPy(i.defaultValue);
        di["unit"] = std::string(unitSymbol(i.unit));
        di["min"] = i.min ? py::cast(*i.min) : py::none();
        di["max"] = i.max ? py::cast(*i.max) : py::none();
        inputs.append(di);
      }
      py::dict dd;
      dd["id"] = d.id;
      dd["name"] = d.name;
      dd["workspace"] = d.workspace;
      dd["tab"] = d.tab;
      dd["panel"] = d.panel;
      dd["inputs"] = inputs;
      out.append(dd);
    }
    return out;
  }, "Metadata for every registered command.");

  m.def("run_command", [](const std::string& id, const py::kwargs& kwargs) {
    Inputs in;
    for (auto [k, v] : kwargs) in[k.cast<std::string>()] = fromPy(v);
    if (auto err = activeSession().run(id, in); !err.empty()) throw std::runtime_error(err);
  }, py::arg("command_id"), "Run a command with keyword inputs (Real inputs in internal units: cm, rad).");

  m.def("undo", [] { return activeSession().undo(); });
  m.def("redo", [] { return activeSession().redo(); });
  m.def("save", [](const std::string& path) { activeSession().save(path); }, py::arg("path"));
  m.def("open", [](const std::string& path) { activeSession().open(path); }, py::arg("path"));
  m.def("new_document", [] { activeSession().newDocument(); });
}

} // namespace tsr::api
