// `tsr`: Tessera-only scripting helpers. Not part of the adsk surface.
// This is the generic path that makes every registered command scriptable
// (plan §4.2: API-callable before UI-callable) and drives scripted tests.
#include "Bindings.h"
#include "tsr/api/PythonHost.h"
#include "tsr/doc/DocCommands.h"
#include "tsr/kernel/Io.h"
#include "tsr/kernel/Kernel.h"
#include "tsr/sketch/SketchGeometry.h"
#include "tsr/sketch/SketchOps.h"

#include <TopExp.hxx>
#include <TopTools_IndexedMapOfShape.hxx>
#include <TopoDS.hxx>

#include <TopoDS_Shape.hxx>

#include <algorithm>
#include <array>
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
    case InputType::Vertices: return "vertices";
    case InputType::Axis: return "axis";
    case InputType::JointOrigin: return "jointOrigin";
    case InputType::Features: return "features";
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
      d["rolled_back"] = f.rolledBack;
      out.append(d);
    }
    return out;
  }, "The design history (timeline), oldest first.");

  m.def("last_replay", [] { return activeSession().document().lastReplay(); },
        "The last recompute: (features restored from memory, features replayed).");
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
  m.def("model_parameters", [] {
    py::list out;
    for (const auto& p : activeSession().document().modelParameters()) {
      py::dict d;
      d["name"] = p.name;
      d["expression"] = p.expression;
      d["owner"] = p.owner;
      d["value"] = p.value;
      d["angle"] = p.angle;
      d["input"] = p.input;   // a feature value's input id; "" for a sketch dimension
      d["label"] = p.label;
      d["unit"] = std::string(unitSymbol(p.unit));
      out.append(d);
    }
    return out;
  }, "Model parameters: sketch dimensions and feature values (d1, d2 ...; values in cm or rad).");
  m.def("rename_parameter", [](const std::string& name, const std::string& newName) {
    if (auto err = activeSession().renameParameter(name, newName); !err.empty()) throw std::runtime_error(err);
  }, py::arg("name"), py::arg("new_name"), "Rename a user or model parameter; expressions that use it follow.");
  m.def("set_favorite", [](const std::string& name, bool favorite) {
    if (auto err = activeSession().setParameterFavorite(name, favorite); !err.empty()) throw std::runtime_error(err);
  }, py::arg("name"), py::arg("favorite") = true, "Star a parameter in Change Parameters.");
  m.def("favorite_parameters", [] { return activeSession().document().favoriteParameters(); });
  m.def("named_views", [] {
    py::list out;
    for (const auto& v : activeSession().document().namedViews()) {
      py::dict d;
      d["name"] = v.name;
      d["eye"] = py::make_tuple(v.eye[0], v.eye[1], v.eye[2]);
      d["target"] = py::make_tuple(v.target[0], v.target[1], v.target[2]);
      d["up"] = py::make_tuple(v.up[0], v.up[1], v.up[2]);
      d["size"] = v.size;
      out.append(d);
    }
    return out;
  }, "The design's named views (eye, target and up in cm; size: the width shown, cm).");
  m.def("add_named_view", [](const std::string& name, std::array<double, 3> eye, std::array<double, 3> target,
                             std::array<double, 3> up, double size) {
    tsr::doc::NamedView v;
    v.name = name;
    for (int i = 0; i < 3; ++i) {
      v.eye[i] = eye[i];
      v.target[i] = target[i];
      v.up[i] = up[i];
    }
    v.size = size;
    if (auto err = activeSession().addNamedView(v); !err.empty()) throw std::runtime_error(err);
  }, py::arg("name"), py::arg("eye"), py::arg("target"), py::arg("up") = std::array<double, 3>{0, 0, 1},
     py::arg("size") = 10.0, "Save a camera as a named view.");
  m.def("rename_named_view", [](const std::string& name, const std::string& newName) {
    if (auto err = activeSession().renameNamedView(name, newName); !err.empty()) throw std::runtime_error(err);
  }, py::arg("name"), py::arg("new_name"));
  m.def("delete_named_view", [](const std::string& name) {
    if (auto err = activeSession().deleteNamedView(name); !err.empty()) throw std::runtime_error(err);
  }, py::arg("name"));
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

  // Sketch editing operations on sketch JSON (as passed to tsr.sketch.create).
  m.def("sketch_fillet", [](const std::string& data, int lineA, int lineB, double radius) {
    sketch::Sketch s = sketch::Sketch::fromJson(data);
    if (auto err = sketch::filletCorner(s, lineA, lineB, radius); !err.empty()) throw std::runtime_error(err);
    return s.toJson();
  }, py::arg("data"), py::arg("line_a"), py::arg("line_b"), py::arg("radius"),
     "Round the corner between two lines (cm); returns the new sketch JSON.");
  m.def("sketch_chamfer", [](const std::string& data, int lineA, int lineB, double distance) {
    sketch::Sketch s = sketch::Sketch::fromJson(data);
    if (auto err = sketch::chamferCorner(s, lineA, lineB, distance); !err.empty()) throw std::runtime_error(err);
    return s.toJson();
  }, py::arg("data"), py::arg("line_a"), py::arg("line_b"), py::arg("distance"));
  m.def("sketch_extend", [](const std::string& data, int line, double x, double y) {
    sketch::Sketch s = sketch::Sketch::fromJson(data);
    if (auto err = sketch::extendCurve(s, line, x, y); !err.empty()) throw std::runtime_error(err);
    return s.toJson();
  }, py::arg("data"), py::arg("line"), py::arg("x"), py::arg("y"), "Extend the line's end nearest (x, y) (cm).");
  m.def("sketch_mirror", [](const std::string& data, const std::vector<int>& entities, int mirrorLine) {
    sketch::Sketch s = sketch::Sketch::fromJson(data);
    if (auto err = sketch::mirrorEntities(s, entities, mirrorLine); !err.empty()) throw std::runtime_error(err);
    return s.toJson();
  }, py::arg("data"), py::arg("entities"), py::arg("mirror_line"));
  m.def("sketch_pattern_rect", [](const std::string& data, const std::vector<int>& entities, double angle, int count1,
                                  double spacing1, int count2, double spacing2) {
    sketch::Sketch s = sketch::Sketch::fromJson(data);
    if (auto err = sketch::rectangularPattern(s, entities, angle, count1, spacing1, count2, spacing2); !err.empty())
      throw std::runtime_error(err);
    return s.toJson();
  }, py::arg("data"), py::arg("entities"), py::arg("angle"), py::arg("count1"), py::arg("spacing1"),
     py::arg("count2") = 1, py::arg("spacing2") = 0.0, "Rectangular sketch pattern (cm, rad).");
  m.def("sketch_pattern_circular", [](const std::string& data, const std::vector<int>& entities, int center, int count,
                                      double total) {
    sketch::Sketch s = sketch::Sketch::fromJson(data);
    if (auto err = sketch::circularPattern(s, entities, center, count, total); !err.empty()) throw std::runtime_error(err);
    return s.toJson();
  }, py::arg("data"), py::arg("entities"), py::arg("center"), py::arg("count"), py::arg("total"),
     "Circular sketch pattern round a point (rad).");
  m.def("sketch_place", [](const std::string& data, const std::vector<int>& entities, double dx, double dy, double angle,
                           double scale, double cx, double cy, bool copy) {
    sketch::Sketch s = sketch::Sketch::fromJson(data);
    sketch::Placement p;
    p.dx = dx, p.dy = dy, p.angle = angle, p.scale = scale, p.cx = cx, p.cy = cy;
    if (auto err = copy ? sketch::copyEntities(s, entities, p) : sketch::placeEntities(s, entities, p); !err.empty())
      throw std::runtime_error(err);
    return s.toJson();
  }, py::arg("data"), py::arg("entities"), py::arg("dx") = 0.0, py::arg("dy") = 0.0, py::arg("angle") = 0.0,
     py::arg("scale") = 1.0, py::arg("cx") = 0.0, py::arg("cy") = 0.0, py::arg("copy") = false,
     "Move / turn / scale sketch curves (or copies of them).");
  m.def("sketch_offset", [](const std::string& data, int entity, double distance) {
    sketch::Sketch s = sketch::Sketch::fromJson(data);
    if (auto err = sketch::offsetChain(s, entity, distance); !err.empty()) throw std::runtime_error(err);
    return s.toJson();
  }, py::arg("data"), py::arg("entity"), py::arg("distance"),
     "Offset the chain through an entity (cm; closed chains: positive is outward); returns the new sketch JSON.");
  m.def("sketch_trim", [](const std::string& data, int entity, double x, double y, bool breakOnly) {
    sketch::Sketch s = sketch::Sketch::fromJson(data);
    if (auto err = sketch::trimCurve(s, entity, x, y, breakOnly); !err.empty()) throw std::runtime_error(err);
    return s.toJson();
  }, py::arg("data"), py::arg("entity"), py::arg("x"), py::arg("y"), py::arg("break_only") = false,
     "Trim (or Break) a spline, conic or ellipse at the point (x, y) (cm) up to the nearest crossings.");
  m.def("sketch_crossings", [](const std::string& data, int entity) {
    std::vector<std::pair<double, double>> out;
    for (const auto& p : sketch::crossings(sketch::Sketch::fromJson(data), entity)) out.emplace_back(p.x, p.y);
    return out;
  }, py::arg("data"), py::arg("entity"), "Where other curves cross an entity (cm).");
  m.def("sketch_spline_handle", [](const std::string& data, int spline, int index, double tx, double ty) {
    sketch::Sketch s = sketch::Sketch::fromJson(data);
    if (auto err = sketch::setSplineHandle(s, spline, index, tx, ty); !err.empty()) throw std::runtime_error(err);
    return s.toJson();
  }, py::arg("data"), py::arg("spline"), py::arg("index"), py::arg("tx"), py::arg("ty"),
     "Set a fit point spline's tangent handle (derivative; 1 = natural speed; (0, 0) frees it).");
  m.def("sketch_spline_handles", [](const std::string& data, int spline) {
    std::vector<py::tuple> out;
    for (const auto& h : sketch::splineHandles(sketch::Sketch::fromJson(data), spline))
      out.push_back(py::make_tuple(h.index, h.x, h.y, h.tx, h.ty, h.set));
    return out;
  }, py::arg("data"), py::arg("spline"), "Tangent handles: (index, x, y, tx, ty, set) per fit point.");
  m.def("sketch_include", [](const std::string& data, const std::string& plane, const std::string& body,
                             const std::vector<int>& edges, double offset) {
    const auto b = activeSession().document().body(body);
    if (!b) throw std::runtime_error("no body named '" + body + "'");
    TopTools_IndexedMapOfShape map;
    TopExp::MapShapes(b->shape, TopAbs_EDGE, map);
    std::vector<TopoDS_Edge> picked;
    if (edges.empty())
      for (int i = 1; i <= map.Extent(); ++i) picked.push_back(TopoDS::Edge(map(i)));
    for (int i : edges) {
      if (i < 0 || i >= map.Extent()) throw std::runtime_error("the body has no edge " + std::to_string(i));
      picked.push_back(TopoDS::Edge(map(i + 1)));
    }
    sketch::Sketch s = sketch::Sketch::fromJson(data);
    if (sketch::includeEdges(s, sketch::planeFrame(plane, offset), picked) == 0)
      throw std::runtime_error("Include 3D Geometry: nothing to include");
    return s.toJson();
  }, py::arg("data"), py::arg("plane"), py::arg("body"), py::arg("edges") = std::vector<int>{}, py::arg("offset") = 0.0,
     "Include 3D Geometry: a body's edges (all, or by index) in the sketch, as they are in space.");

  m.def("bounding_box", [](const std::string& name) {
    const auto b = activeSession().document().body(name);
    if (!b) throw std::runtime_error("no body named '" + name + "'");
    const auto bb = kernel::boundingBox(b->shape);
    return py::make_tuple(py::make_tuple(bb.min.x, bb.min.y, bb.min.z), py::make_tuple(bb.max.x, bb.max.y, bb.max.z));
  }, py::arg("body"), "A body's bounding box ((xmin, ymin, zmin), (xmax, ymax, zmax)) in cm.");
  m.def("sketch_data", [](const std::string& name) {
    const auto rec = activeSession().document().sketch(name);
    if (!rec) throw std::runtime_error("no sketch named '" + name + "'");
    return rec->data;
  }, py::arg("sketch"), "A sketch as solved (JSON: points in cm, entities, constraints).");
  m.def("roll_history", [](int marker) {
    if (auto err = activeSession().rollHistory(marker); !err.empty()) throw std::runtime_error(err);
  }, py::arg("position"), "Move the timeline's history marker: replay only the first `position` features.");
  m.def("history_marker", [] { return activeSession().document().historyMarker(); },
        "How many features the history marker replays.");
  m.def("move_feature", [](const std::string& name, int position) {
    std::vector<int> order;
    int id = -1;
    for (const auto& f : activeSession().document().features()) {
      if (f.name == name) id = f.id;
      else order.push_back(f.id);
    }
    if (id < 0) throw std::runtime_error("no feature named '" + name + "'");
    const int marker = activeSession().document().historyMarker();
    position = std::clamp(position, 0, static_cast<int>(order.size()));
    order.insert(order.begin() + position, id);
    if (auto err = activeSession().setTimeline(order, marker); !err.empty()) throw std::runtime_error(err);
  }, py::arg("name"), py::arg("position"), "Move a feature to another place in the timeline.");
  m.def("rename", [](const std::string& kind, const std::string& name, const std::string& newName) {
    std::string err;
    if (kind == "body") err = activeSession().renameBody(name, newName);
    else if (kind == "sketch") err = activeSession().renameSketch(name, newName);
    else if (kind == "feature") {
      int id = -1;
      for (const auto& f : activeSession().document().features())
        if (f.name == name) id = f.id;
      err = id < 0 ? "no feature named '" + name + "'" : activeSession().renameFeature(id, newName);
    } else {
      err = "rename: kind is body, sketch or feature";
    }
    if (!err.empty()) throw std::runtime_error(err);
  }, py::arg("kind"), py::arg("name"), py::arg("new_name"), "Rename a body, sketch or timeline feature (one undo step).");
  m.def("mass_properties", [](const std::string& name) {
    const auto b = activeSession().document().body(name);
    if (!b) throw std::runtime_error("no body named '" + name + "'");
    const auto mp = kernel::massProperties(b->shape);
    py::dict d;
    d["volume"] = mp.volume;
    d["area"] = mp.area;
    d["center"] = py::make_tuple(mp.centerOfMass.x, mp.centerOfMass.y, mp.centerOfMass.z);
    d["faces"] = kernel::topologyCounts(b->shape).faces;
    d["patches"] = kernel::smoothPatchCount(b->shape);
    return d;
  }, py::arg("body"), "A body's volume (cm3), area (cm2), centre of mass (cm), face count, and smooth patches (faces on one "
     "surface that meet count once).");
  m.def("components", [] {
    py::list out;
    for (const auto& c : activeSession().document().components()) {
      py::dict d;
      d["name"] = c.name;
      d["bodies"] = c.bodies;
      out.append(d);
    }
    return out;
  });

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
