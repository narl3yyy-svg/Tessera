// `tsr`: Tessera-only scripting helpers. Not part of the adsk surface.
// This is the generic path that makes every registered command scriptable
// (plan §4.2: API-callable before UI-callable) and drives scripted tests.
#include "Bindings.h"
#include "tsr/api/PythonHost.h"
#include "tsr/doc/DocCommands.h"
#include "tsr/kernel/Io.h"

#include <TopoDS_Shape.hxx>

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
    case InputType::Choice: return "choice";
    case InputType::Body: return "body";
    case InputType::Sketch: return "sketch";
    case InputType::Profiles: return "profiles";
    case InputType::Edges: return "edges";
    case InputType::Faces: return "faces";
    case InputType::Bodies: return "bodies";
    case InputType::Plane: return "plane";
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
        if (i.type == InputType::Choice) di["choices"] = i.choices;
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

  m.def("features", [] {
    py::list out;
    for (const auto& f : activeSession().document().features()) {
      py::dict d;
      d["id"] = f.id;
      d["name"] = f.name;
      d["command"] = f.commandId;
      py::dict in;
      for (const auto& [k, v] : f.inputs) in[py::str(k)] = toPy(v);
      d["inputs"] = in;
      d["error"] = f.error;
      d["suppressed"] = f.suppressed;
      out.append(d);
    }
    return out;
  }, "The design history (timeline), oldest first.");

  m.def("edit_feature", [](int id, const py::kwargs& kwargs) {
    Inputs in;
    for (auto [k, v] : kwargs) in[k.cast<std::string>()] = fromPy(v);
    if (auto err = activeSession().editFeature(id, in); !err.empty()) throw std::runtime_error(err);
  }, py::arg("feature_id"), "Change a feature's inputs and replay the timeline.");
  m.def("delete_feature", [](int id) {
    if (auto err = activeSession().deleteFeature(id); !err.empty()) throw std::runtime_error(err);
  }, py::arg("feature_id"));
  m.def("suppress_feature", [](int id, bool suppressed) {
    if (auto err = activeSession().setFeatureSuppressed(id, suppressed); !err.empty()) throw std::runtime_error(err);
  }, py::arg("feature_id"), py::arg("suppressed") = true);

  m.def("parameters", [] {
    py::list out;
    for (const auto& p : activeSession().document().userParameters()) {
      py::dict d;
      d["name"] = p.name;
      d["expression"] = p.expression;
      d["unit"] = p.unit;
      d["value"] = p.value;
      d["comment"] = p.comment;
      out.append(d);
    }
    return out;
  }, "User parameters (values in internal units: cm, rad).");
  m.def("set_parameter", [](const std::string& name, const std::string& expression, py::object comment) {
    auto p = activeSession().document().userParameter(name);
    if (!p) throw std::runtime_error("no parameter named '" + name + "'");
    const std::string c = comment.is_none() ? p->comment : comment.cast<std::string>();
    if (auto err = activeSession().setParameter(name, expression, c); !err.empty()) throw std::runtime_error(err);
  }, py::arg("name"), py::arg("expression"), py::arg("comment") = py::none(),
     "Change a parameter's expression; dependent parameters and features update.");
  m.def("delete_parameter", [](const std::string& name) {
    if (auto err = activeSession().deleteParameter(name); !err.empty()) throw std::runtime_error(err);
  }, py::arg("name"));
  m.def("evaluate", [](const std::string& text, const std::string& unit) {
    const auto u = parseUnit(unit);
    if (!u) throw std::runtime_error("unknown unit '" + unit + "'");
    try {
      return activeSession().document().evaluate(text, *u);
    } catch (const std::exception& e) {
      throw std::runtime_error(e.what());
    }
  }, py::arg("expression"), py::arg("unit") = "mm",
     "Evaluate an expression as an input in `unit` would (internal units out; lengths use the document unit).");

  m.def("export", [](const std::string& path, int refinement) {
    const auto format = kernel::formatForPath(path);
    if (!format) throw std::runtime_error("unsupported export type: " + path);
    std::vector<kernel::NamedShape> bodies;
    for (const auto& b : activeSession().document().bodies()) bodies.emplace_back(b.name, b.shape);
    kernel::exportShapes(path, bodies, *format, refinement);
  }, py::arg("path"), py::arg("refinement") = 1, "Export all bodies (STEP, IGES, STL, OBJ, 3MF, BREP; mm).");
  m.def("insert", [](const std::string& path) {
    const TopoDS_Shape s = kernel::importShape(path);
    if (auto err = activeSession().run(doc::kCmdInsert, {{"source", path}, {"brep", kernel::toBrep(s)}}); !err.empty())
      throw std::runtime_error(err);
  }, py::arg("path"), "Insert a STEP, IGES, STL or BREP file as bodies.");
  m.def("set_units", [](const std::string& unit) {
    if (auto err = activeSession().run(doc::kCmdUnits, {{"unit", unit}}); !err.empty()) throw std::runtime_error(err);
  }, py::arg("unit"));
  m.def("units", [] { return activeSession().document().lengthUnit(); });

  m.def("undo", [] { return activeSession().undo(); });
  m.def("redo", [] { return activeSession().redo(); });
  m.def("save", [](const std::string& path) { activeSession().save(path); }, py::arg("path"));
  m.def("open", [](const std::string& path) { activeSession().open(path); }, py::arg("path"));
  m.def("new_document", [] { activeSession().newDocument(); });
}

} // namespace tsr::api
