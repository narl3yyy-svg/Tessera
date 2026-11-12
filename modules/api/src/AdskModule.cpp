// adsk.* compatibility shim (plan §4.5), P0 subset.
//
// Only names and signatures confirmed in Autodesk's public API reference are
// bound here; anything else is left out rather than guessed. Behavioural
// details (e.g. exact error text) are UNRESOLVED until Phase R6 records them
// from the reference — see SPEC/api-surface.md.
//
// Units follow the adsk convention: lengths in cm, angles in radians.
#include "Bindings.h"
#include "tsr/api/PythonHost.h"
#include "tsr/doc/DocCommands.h"
#include "tsr/kernel/Kernel.h"

#include <pybind11/stl.h>

#include <stdexcept>

namespace py = pybind11;

namespace tsr::api {

namespace {

// ---- adsk.core -------------------------------------------------------------
struct ValueInput {
  bool isReal = true;
  double real = 0;
  std::string text;
};

struct Product {
  virtual ~Product() = default;
};

struct Application {};

// ---- adsk.fusion -----------------------------------------------------------
struct Design : Product {};

struct UserParameter {
  std::string name;
  doc::UserParameter get() const {
    auto p = activeSession().document().userParameter(name);
    if (!p) throw std::runtime_error("parameter '" + name + "' no longer exists");
    return *p;
  }
};

struct UserParameters {};

struct BRepBody {
  std::size_t index;
  doc::Body get() const {
    auto bodies = activeSession().document().bodies();
    if (index >= bodies.size()) throw std::runtime_error("body no longer exists");
    return bodies[index];
  }
};

struct BRepBodies {};
struct Component {};

void raiseIfError(const std::string& err) {
  if (!err.empty()) throw std::runtime_error(err);
}

} // namespace

void bindAdsk(py::module_& adsk) {
  adsk.doc() = "Tessera implementation of the adsk API (Fusion-compatible)";
  py::module_ core = adsk.def_submodule("core");
  py::module_ fusion = adsk.def_submodule("fusion");

  // ---- adsk.core ----
  py::class_<ValueInput>(core, "ValueInput")
      .def_static("createByReal", [](double v) { return ValueInput{true, v, {}}; }, py::arg("realValue"))
      .def_static("createByString", [](std::string s) { return ValueInput{false, 0, std::move(s)}; },
                  py::arg("stringValue"))
      .def_property_readonly("realValue", [](const ValueInput& v) { return v.isReal ? v.real : 0.0; })
      .def_property_readonly("stringValue", [](const ValueInput& v) { return v.isReal ? std::string{} : v.text; });

  py::class_<Product>(core, "Product");

  py::class_<Application>(core, "Application")
      .def_static("get", [] { return Application{}; })
      .def_property_readonly("activeProduct", [](const Application&) -> py::object {
        return py::cast(Design{});
      })
      .def_property_readonly("version", [](const Application&) { return std::string(TSR_VERSION_STRING); });

  // ---- adsk.fusion ----
  py::class_<UserParameter>(fusion, "UserParameter")
      .def_property_readonly("name", [](const UserParameter& p) { return p.get().name; })
      .def_property("expression", [](const UserParameter& p) { return p.get().expression; },
                    [](const UserParameter& p, const std::string& e) {
                      raiseIfError(activeSession().setParameter(p.name, e, p.get().comment));
                    })
      .def_property_readonly("unit", [](const UserParameter& p) { return p.get().unit; })
      .def_property("comment", [](const UserParameter& p) { return p.get().comment; },
                    [](const UserParameter& p, const std::string& c) {
                      raiseIfError(activeSession().setParameter(p.name, p.get().expression, c));
                    })
      .def_property("value", [](const UserParameter& p) { return p.get().value; },
                    [](const UserParameter& p, double v) {
                      const auto cur = p.get();
                      const std::string e = formatQuantity(v, parseUnit(cur.unit).value_or(Unit::None));
                      raiseIfError(activeSession().setParameter(p.name, e, cur.comment));
                    })
      .def_property_readonly("isDeletable",
                             [](const UserParameter& p) {
                               return activeSession().document().parameterUsers(p.name).empty();
                             })
      .def("deleteMe", [](const UserParameter& p) { return activeSession().deleteParameter(p.name).empty(); });

  py::class_<UserParameters>(fusion, "UserParameters")
      .def("add",
           [](const UserParameters&, const std::string& name, const ValueInput& value, const std::string& units,
              const std::string& comment) {
             const auto unit = parseUnit(units);
             if (!unit) throw std::runtime_error("unknown unit '" + units + "'");
             const std::string expression = value.isReal ? formatQuantity(value.real, *unit) : value.text;
             raiseIfError(activeSession().run(
                 doc::kCmdAddUserParameter,
                 {{"name", name}, {"expression", expression}, {"unit", units}, {"comment", comment}}));
             return UserParameter{name};
           },
           py::arg("name"), py::arg("value"), py::arg("units"), py::arg("comment"))
      .def_property_readonly("count",
                             [](const UserParameters&) { return activeSession().document().userParameters().size(); })
      .def("item",
           [](const UserParameters&, std::size_t i) -> py::object {
             auto ps = activeSession().document().userParameters();
             return i < ps.size() ? py::cast(UserParameter{ps[i].name}) : py::none();
           },
           py::arg("index"))
      .def("itemByName",
           [](const UserParameters&, const std::string& name) -> py::object {
             return activeSession().document().userParameter(name) ? py::cast(UserParameter{name}) : py::none();
           },
           py::arg("name"))
      .def("__len__", [](const UserParameters&) { return activeSession().document().userParameters().size(); })
      .def("__iter__", [](const UserParameters&) {
        py::list out;
        for (const auto& p : activeSession().document().userParameters()) out.append(UserParameter{p.name});
        return py::iter(out);
      });

  py::class_<BRepBody>(fusion, "BRepBody")
      .def_property_readonly("name", [](const BRepBody& b) { return b.get().name; })
      .def_property_readonly("volume", [](const BRepBody& b) { return kernel::massProperties(b.get().shape).volume; })
      .def_property_readonly("area", [](const BRepBody& b) { return kernel::massProperties(b.get().shape).area; });

  py::class_<BRepBodies>(fusion, "BRepBodies")
      .def_property_readonly("count", [](const BRepBodies&) { return activeSession().document().bodies().size(); })
      .def("item",
           [](const BRepBodies&, std::size_t i) -> py::object {
             return i < activeSession().document().bodies().size() ? py::cast(BRepBody{i}) : py::none();
           },
           py::arg("index"))
      .def("__len__", [](const BRepBodies&) { return activeSession().document().bodies().size(); });

  py::class_<Component>(fusion, "Component")
      .def_property_readonly("bRepBodies", [](const Component&) { return BRepBodies{}; });

  py::class_<Design, Product>(fusion, "Design")
      .def_static("cast", [](py::object o) -> py::object {
        return py::isinstance<Design>(o) ? o : py::none();
      })
      .def_property_readonly("userParameters", [](const Design&) { return UserParameters{}; })
      .def_property_readonly("rootComponent", [](const Design&) { return Component{}; });
}

} // namespace tsr::api
