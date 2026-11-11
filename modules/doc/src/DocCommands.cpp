#include "tsr/doc/DocCommands.h"
#include "tsr/doc/Document.h"

#include "tsr/kernel/Kernel.h"
#include "tsr/sketch/Sketch.h"
#include "tsr/sketch/SketchGeometry.h"

#include <algorithm>
#include <cmath>
#include <optional>

#include <cctype>
#include <functional>
#include <memory>

namespace tsr::doc {

namespace {

Document& docOf(CommandContext& ctx) {
  auto* d = dynamic_cast<Document*>(&ctx);
  if (!d) throw CommandError("command requires a design document");
  return *d;
}

bool isIdentifier(const std::string& s) {
  if (s.empty() || !(std::isalpha(static_cast<unsigned char>(s[0])) || s[0] == '_')) return false;
  for (char c : s)
    if (!(std::isalnum(static_cast<unsigned char>(c)) || c == '_')) return false;
  return true;
}

// ---------------------------------------------------------------------------
class AddUserParameter final : public Command {
public:
  AddUserParameter() {
    def_.id = kCmdAddUserParameter;
    def_.name = "Add User Parameter";
    def_.tooltip = "Creates a named parameter that other features can reference.";
    def_.workspace = "Design";
    def_.tab = "Solid";
    def_.panel = "Modify";
    def_.icon = "parameters";
    def_.inputs = {
        {.id = "name", .label = "Name", .tooltip = "Parameter name (letters, digits, underscore).",
         .type = InputType::String, .defaultValue = std::string{}},
        {.id = "unit", .label = "Unit", .tooltip = "mm, cm, m, in, ft, deg, rad, or empty for unitless.",
         .type = InputType::String, .defaultValue = std::string("mm"), .optional = true},
        {.id = "expression", .label = "Expression", .tooltip = "Value, optionally with a unit, e.g. 10 mm.",
         .type = InputType::String, .defaultValue = std::string("1 mm")},
        {.id = "comment", .label = "Comment", .tooltip = {},
         .type = InputType::String, .defaultValue = std::string{}, .optional = true},
    };
  }
  const CommandDef& def() const override { return def_; }

  std::string validate(const Inputs& in, CommandContext& ctx) const override {
    const std::string name = getString(in, "name");
    if (!isIdentifier(name)) return "Name: must start with a letter or underscore and contain only letters, digits and underscores";
    if (parseUnit(name)) return "Name: '" + name + "' is a unit name";
    if (docOf(ctx).userParameter(name)) return "Name: a parameter named '" + name + "' already exists";
    const auto unit = parseUnit(getString(in, "unit"));
    if (!unit) return "Unit: unknown unit '" + getString(in, "unit") + "'";
    if (!parseQuantity(getString(in, "expression"), *unit))
      return "Expression: cannot evaluate '" + getString(in, "expression") + "' as " +
             (*unit == Unit::None ? std::string("a unitless number") : "a value in " + std::string(unitSymbol(*unit)));
    return {};
  }

  void apply(const Inputs& in, CommandContext& ctx) const override {
    const Unit unit = *parseUnit(getString(in, "unit"));
    UserParameter p;
    p.name = getString(in, "name");
    p.unit = std::string(unitSymbol(unit));
    p.expression = getString(in, "expression");
    p.comment = getString(in, "comment");
    p.value = *parseQuantity(p.expression, unit);
    docOf(ctx).addUserParameter(p);
  }

private:
  CommandDef def_;
};

// ---------------------------------------------------------------------------
// Primitives. Each one builds a tool solid and then either adds it as a new
// body or combines it with a target body (Join / Cut / Intersect).

InputDef size(const char* id, const char* label, double defaultCm, const char* tip = "") {
  return InputDef{.id = id, .label = label, .tooltip = tip, .type = InputType::Real,
                  .defaultValue = defaultCm, .unit = Unit::Millimeter, .min = 0.0, .max = std::nullopt,
                  .minExclusive = true};
}

InputDef offset(const char* id, const char* label) {
  return InputDef{.id = id, .label = label, .tooltip = "Position of the primitive's base point.",
                  .type = InputType::Real, .defaultValue = 0.0, .unit = Unit::Millimeter};
}

InputDef choice(const char* id, const char* label, std::vector<std::string> options, const char* tip) {
  std::string first = options.front();
  return InputDef{.id = id, .label = label, .tooltip = tip, .type = InputType::Choice,
                  .defaultValue = first, .choices = std::move(options)};
}

kernel::Vec3 position(const Inputs& in) { return {getReal(in, "x"), getReal(in, "y"), getReal(in, "z")}; }

kernel::Axis axisOf(const Inputs& in) {
  const std::string a = getString(in, "axis");
  return a == "X" ? kernel::Axis::X : a == "Y" ? kernel::Axis::Y : kernel::Axis::Z;
}

// Operation / target inputs shared by everything that makes solid geometry.
void addOperationInputs(CommandDef& d) {
  d.inputs.push_back(choice("operation", "Operation", {"New Body", "Join", "Cut", "Intersect"},
                            "New Body, or combine with the target body."));
  d.inputs.push_back(InputDef{.id = "target", .label = "Target body",
                              .tooltip = "Body to join/cut/intersect. Empty: the most recent body.",
                              .type = InputType::Body, .defaultValue = std::string{}, .optional = true});
}

std::string validateOperation(const Inputs& in, const Document& doc) {
  if (getString(in, "operation") == "New Body") return {};
  const std::string target = getString(in, "target");
  if (target.empty() ? doc.bodies().empty() : !doc.body(target))
    return target.empty() ? "Operation: there is no body to combine with; choose New Body"
                          : "Target body: '" + target + "' does not exist";
  return {};
}

// Adds `tool` as a new body or combines it with the target body.
void applyOperation(Document& doc, const Inputs& in, const TopoDS_Shape& tool, const std::string& what) {
  if (!kernel::isValid(tool)) throw CommandError(what + ": kernel produced an invalid body");
  const std::string op = getString(in, "operation");
  if (op == "New Body") {
    doc.addBody(doc.nextBodyName(), tool);
    return;
  }
  std::string target = getString(in, "target");
  if (target.empty()) {
    const auto bodies = doc.bodies();
    if (bodies.empty()) throw CommandError("Operation: there is no body to combine with; choose New Body");
    target = bodies.back().name;
  }
  const auto body = doc.body(target);
  if (!body) throw CommandError("Target body: '" + target + "' does not exist");
  const auto kind = op == "Join" ? kernel::BooleanOp::Join
                  : op == "Cut"  ? kernel::BooleanOp::Cut
                                 : kernel::BooleanOp::Intersect;
  try {
    doc.replaceBody(target, kernel::boolean(kind, body->shape, tool));
  } catch (const kernel::KernelError& e) {
    throw CommandError(e.what());
  }
}

class Primitive : public Command {
public:
  using Builder = std::function<TopoDS_Shape(const Inputs&)>;

  Primitive(const char* id, const char* name, const char* tooltip, const char* icon, std::vector<InputDef> sizes,
            bool hasAxis, Builder build)
      : build_(std::move(build)) {
    def_.id = id;
    def_.name = name;
    def_.tooltip = tooltip;
    def_.workspace = "Design";
    def_.tab = "Solid";
    def_.panel = "Create";
    def_.icon = icon;
    def_.feature = true;
    def_.inputs = std::move(sizes);
    def_.inputs.push_back(offset("x", "X"));
    def_.inputs.push_back(offset("y", "Y"));
    def_.inputs.push_back(offset("z", "Z"));
    if (hasAxis)
      def_.inputs.push_back(choice("axis", "Direction", {"Z", "Y", "X"}, "Axis the primitive is built along."));
    addOperationInputs(def_);
  }
  const CommandDef& def() const override { return def_; }

  std::string validate(const Inputs& in, CommandContext& ctx) const override {
    return validateOperation(in, docOf(ctx));
  }

  void apply(const Inputs& in, CommandContext& ctx) const override {
    TopoDS_Shape tool;
    try {
      tool = build_(in);
    } catch (const kernel::KernelError& e) {
      throw CommandError(def_.name + ": " + e.what());
    }
    applyOperation(docOf(ctx), in, tool, def_.name);
  }

private:
  CommandDef def_;
  Builder build_;
};

// ---------------------------------------------------------------------------
// Sketch: a feature that stores solved 2D geometry on a plane. The GUI edits
// it in sketch mode; scripts pass the geometry as JSON (tsr::sketch format).
class CreateSketch final : public Command {
public:
  CreateSketch() {
    def_.id = kCmdSketch;
    def_.name = "Create Sketch";
    def_.tooltip = "Creates a 2D sketch on a plane or a flat face. Draw lines, rectangles, circles and arcs, "
                   "then add constraints and dimensions.";
    def_.workspace = "Design";
    def_.tab = "Solid";
    def_.panel = "Create";
    def_.icon = "sketch";
    def_.feature = true;
    def_.nameInput = "name";
    def_.inputs = {
        {.id = "name", .label = "Name", .tooltip = "Empty: Sketch<n>.", .type = InputType::String,
         .defaultValue = std::string{}, .optional = true},
        {.id = "plane", .label = "Plane", .tooltip = "XY, XZ, YZ or custom:... (see SketchGeometry.h).",
         .type = InputType::String, .defaultValue = std::string("XY")},
        {.id = "offset", .label = "Offset", .tooltip = "Moves the plane along its normal.", .type = InputType::Real,
         .defaultValue = 0.0, .unit = Unit::Millimeter},
        {.id = "data", .label = "Geometry", .tooltip = "Sketch geometry and constraints (JSON).",
         .type = InputType::String, .defaultValue = std::string{}, .optional = true},
    };
  }
  const CommandDef& def() const override { return def_; }

  std::string validate(const Inputs& in, CommandContext&) const override {
    try {
      (void)sketch::planeFrame(getString(in, "plane"), getReal(in, "offset"));
      (void)sketch::Sketch::fromJson(getString(in, "data"));
    } catch (const sketch::SketchError& e) {
      return e.what();
    }
    const std::string name = getString(in, "name");
    if (!name.empty() && !isIdentifier(name)) return "Name: letters, digits and underscores only";
    return {};
  }

  void prepare(Inputs& in, CommandContext& ctx) const override {
    if (getString(in, "name").empty()) in["name"] = docOf(ctx).nextSketchName();
  }

  void apply(const Inputs& in, CommandContext& ctx) const override {
    Document& doc = docOf(ctx);
    SketchRecord rec;
    rec.name = getString(in, "name");
    if (rec.name.empty()) rec.name = doc.nextSketchName();
    rec.plane = getString(in, "plane");
    rec.offset = getReal(in, "offset");
    try {
      (void)sketch::planeFrame(rec.plane, rec.offset);
      sketch::Sketch s = sketch::Sketch::fromJson(getString(in, "data"));
      const auto res = sketch::solve(s);
      if (!res.ok) throw CommandError(rec.name + ": " + res.message);
      rec.data = s.toJson();
    } catch (const sketch::SketchError& e) {
      throw CommandError(rec.name + ": " + e.what());
    }
    doc.setSketch(rec);
  }

private:
  CommandDef def_;
};

// Profiles of a stored sketch, with its plane.
struct SketchProfiles {
  gp_Ax3 frame;
  std::vector<sketch::Profile> profiles;
};

SketchProfiles profilesOf(const SketchRecord& rec) {
  SketchProfiles out;
  out.frame = sketch::planeFrame(rec.plane, rec.offset);
  out.profiles = sketch::profiles(sketch::Sketch::fromJson(rec.data), out.frame);
  return out;
}

std::optional<SketchRecord> sketchFor(const Document& doc, const std::string& name) {
  if (!name.empty()) return doc.sketch(name);
  const auto all = doc.sketches();
  if (all.empty()) return std::nullopt;
  return all.back();
}

// "x,y;x,y" -> points
std::vector<std::pair<double, double>> parsePoints(const std::string& text) {
  std::vector<std::pair<double, double>> out;
  size_t start = 0;
  while (start < text.size()) {
    size_t end = text.find(';', start);
    if (end == std::string::npos) end = text.size();
    const std::string item = text.substr(start, end - start);
    const size_t comma = item.find(',');
    if (comma == std::string::npos) throw CommandError("Profiles: expected x,y pairs separated by ';'");
    try {
      out.emplace_back(std::stod(item.substr(0, comma)), std::stod(item.substr(comma + 1)));
    } catch (const std::exception&) {
      throw CommandError("Profiles: '" + item + "' is not an x,y pair");
    }
    start = end + 1;
  }
  return out;
}

// The faces of the picked profiles; all of them when none are picked.
std::vector<TopoDS_Shape> pickedFaces(const SketchProfiles& sp, const std::string& picked, const std::string& sketchName) {
  std::vector<TopoDS_Shape> faces;
  if (picked.empty()) {
    for (const auto& p : sp.profiles) faces.push_back(p.face);
    return faces;
  }
  std::vector<int> used;
  for (const auto& [x, y] : parsePoints(picked)) {
    const int i = sketch::profileAt(sp.profiles, sp.frame, x, y);
    if (i < 0) throw CommandError("Profiles: a picked profile no longer exists in " + sketchName);
    if (std::find(used.begin(), used.end(), i) == used.end()) {
      used.push_back(i);
      faces.push_back(sp.profiles[i].face);
    }
  }
  return faces;
}

class Extrude final : public Command {
public:
  Extrude() {
    def_.id = kCmdExtrude;
    def_.name = "Extrude";
    def_.tooltip = "Adds depth to sketch profiles. Pick the profiles in the canvas, set the distance.";
    def_.workspace = "Design";
    def_.tab = "Solid";
    def_.panel = "Create";
    def_.icon = "extrude";
    def_.shortcut = "E";
    def_.feature = true;
    def_.inputs = {
        {.id = "sketch", .label = "Sketch", .tooltip = "Empty: the most recent sketch.", .type = InputType::Sketch,
         .defaultValue = std::string{}, .optional = true},
        {.id = "profiles", .label = "Profiles", .tooltip = "Click regions of the sketch. None picked: all of them.",
         .type = InputType::Profiles, .defaultValue = std::string{}, .optional = true},
        choice("direction", "Direction", {"One Side", "Symmetric"}, "Symmetric extrudes the distance both ways."),
        {.id = "distance", .label = "Distance", .tooltip = "Negative extrudes the other way.",
         .type = InputType::Real, .defaultValue = 1.0, .unit = Unit::Millimeter},
    };
    addOperationInputs(def_);
  }
  const CommandDef& def() const override { return def_; }

  std::string validate(const Inputs& in, CommandContext& ctx) const override {
    const Document& doc = docOf(ctx);
    const std::string name = getString(in, "sketch");
    if (!sketchFor(doc, name))
      return name.empty() ? "Sketch: there is no sketch to extrude; create one first"
                          : "Sketch: '" + name + "' does not exist";
    if (std::abs(getReal(in, "distance")) < 1e-9) return "Distance: must not be zero";
    return validateOperation(in, doc);
  }

  void prepare(Inputs& in, CommandContext& ctx) const override {
    // Record which sketch was meant, so later sketches do not change it.
    if (getString(in, "sketch").empty())
      if (auto rec = sketchFor(docOf(ctx), "")) in["sketch"] = rec->name;
  }

  void apply(const Inputs& in, CommandContext& ctx) const override {
    Document& doc = docOf(ctx);
    const auto rec = sketchFor(doc, getString(in, "sketch"));
    if (!rec) throw CommandError("Sketch: '" + getString(in, "sketch") + "' does not exist");
    SketchProfiles sp;
    try {
      sp = profilesOf(*rec);
    } catch (const sketch::SketchError& e) {
      throw CommandError(e.what());
    }
    if (sp.profiles.empty()) throw CommandError(rec->name + " has no closed profile to extrude");

    const auto faces = pickedFaces(sp, getString(in, "profiles"), rec->name);
    const gp_Dir n = sp.frame.Direction();
    TopoDS_Shape tool;
    try {
      tool = kernel::extrude(faces, {n.X(), n.Y(), n.Z()}, getReal(in, "distance"),
                             getString(in, "direction") == "Symmetric");
    } catch (const kernel::KernelError& e) {
      throw CommandError("Extrude: " + std::string(e.what()));
    }
    applyOperation(doc, in, tool, "Extrude");
  }

private:
  CommandDef def_;
};

std::unique_ptr<Command> makeBox() {
  return std::make_unique<Primitive>(
      kCmdBox, "Box", "Creates a solid box. X/Y/Z is its minimum corner.", "box",
      std::vector<InputDef>{size("length", "Length", 1.0, "Size along X."), size("width", "Width", 1.0, "Size along Y."),
                            size("height", "Height", 1.0, "Size along Z.")},
      false, [](const Inputs& in) {
        return kernel::makeBox(getReal(in, "length"), getReal(in, "width"), getReal(in, "height"), position(in));
      });
}

std::unique_ptr<Command> makeCylinder() {
  return std::make_unique<Primitive>(
      kCmdCylinder, "Cylinder", "Creates a solid cylinder. X/Y/Z is the centre of its base.", "cylinder",
      std::vector<InputDef>{size("diameter", "Diameter", 1.0), size("height", "Height", 1.0)}, true,
      [](const Inputs& in) {
        return kernel::makeCylinder(getReal(in, "diameter") / 2, getReal(in, "height"), position(in), axisOf(in));
      });
}

std::unique_ptr<Command> makeSphere() {
  return std::make_unique<Primitive>(
      kCmdSphere, "Sphere", "Creates a solid sphere. X/Y/Z is its centre.", "sphere",
      std::vector<InputDef>{size("diameter", "Diameter", 1.0)}, false,
      [](const Inputs& in) { return kernel::makeSphere(getReal(in, "diameter") / 2, position(in)); });
}

std::unique_ptr<Command> makeTorus() {
  return std::make_unique<Primitive>(
      kCmdTorus, "Torus", "Creates a solid torus (ring). X/Y/Z is its centre.", "torus",
      std::vector<InputDef>{size("diameter", "Diameter", 2.0, "Diameter of the ring, through the tube centres."),
                            size("section", "Section diameter", 0.5, "Diameter of the tube.")},
      true, [](const Inputs& in) {
        return kernel::makeTorus(getReal(in, "diameter") / 2, getReal(in, "section") / 2, position(in), axisOf(in));
      });
}

std::unique_ptr<Command> makeCone() {
  return std::make_unique<Primitive>(
      kCmdCone, "Cone", "Creates a solid cone or frustum. X/Y/Z is the centre of its base.", "cone",
      std::vector<InputDef>{size("diameter", "Base diameter", 1.0),
                            InputDef{.id = "top", .label = "Top diameter", .tooltip = "0 for a pointed cone.",
                                     .type = InputType::Real, .defaultValue = 0.0, .unit = Unit::Millimeter,
                                     .min = 0.0},
                            size("height", "Height", 1.0)},
      true, [](const Inputs& in) {
        return kernel::makeCone(getReal(in, "diameter") / 2, getReal(in, "top") / 2, getReal(in, "height"),
                                position(in), axisOf(in));
      });
}


// ---------------------------------------------------------------------------
// Revolve: profiles of a sketch turned about an axis.
class Revolve final : public Command {
public:
  Revolve() {
    def_.id = kCmdRevolve;
    def_.name = "Revolve";
    def_.tooltip = "Turns sketch profiles about an axis: shafts, knobs, rings, bottles.";
    def_.workspace = "Design";
    def_.tab = "Solid";
    def_.panel = "Create";
    def_.icon = "revolve";
    def_.feature = true;
    def_.inputs = {
        {.id = "sketch", .label = "Sketch", .tooltip = "Empty: the most recent sketch.", .type = InputType::Sketch,
         .defaultValue = std::string{}, .optional = true},
        {.id = "profiles", .label = "Profiles", .tooltip = "Click regions of the sketch. None picked: all of them.",
         .type = InputType::Profiles, .defaultValue = std::string{}, .optional = true},
        choice("axis", "Axis", {"Sketch Y axis", "Sketch X axis", "Construction line", "X", "Y", "Z"},
               "Axis to turn about. Construction line: the sketch's first construction line."),
        choice("direction", "Direction", {"One Side", "Symmetric"}, "Symmetric turns half the angle each way."),
        {.id = "angle", .label = "Angle", .tooltip = "360 deg for a full turn.", .type = InputType::Real,
         .defaultValue = 2 * 3.14159265358979323846, .unit = Unit::Degree},
    };
    addOperationInputs(def_);
  }
  const CommandDef& def() const override { return def_; }

  std::string validate(const Inputs& in, CommandContext& ctx) const override {
    const Document& doc = docOf(ctx);
    const std::string name = getString(in, "sketch");
    if (!sketchFor(doc, name))
      return name.empty() ? "Sketch: there is no sketch to revolve; create one first"
                          : "Sketch: '" + name + "' does not exist";
    if (std::abs(getReal(in, "angle")) < 1e-9) return "Angle: must not be zero";
    return validateOperation(in, doc);
  }

  void prepare(Inputs& in, CommandContext& ctx) const override {
    if (getString(in, "sketch").empty())
      if (auto rec = sketchFor(docOf(ctx), "")) in["sketch"] = rec->name;
  }

  void apply(const Inputs& in, CommandContext& ctx) const override {
    Document& doc = docOf(ctx);
    const auto rec = sketchFor(doc, getString(in, "sketch"));
    if (!rec) throw CommandError("Sketch: '" + getString(in, "sketch") + "' does not exist");
    SketchProfiles sp;
    sketch::Sketch sk;
    try {
      sp = profilesOf(*rec);
      sk = sketch::Sketch::fromJson(rec->data);
    } catch (const sketch::SketchError& e) {
      throw CommandError(e.what());
    }
    if (sp.profiles.empty()) throw CommandError(rec->name + " has no closed profile to revolve");
    const auto faces = pickedFaces(sp, getString(in, "profiles"), rec->name);

    // Axis in world coordinates.
    gp_Pnt o(0, 0, 0);
    gp_Dir d(0, 0, 1);
    const std::string axis = getString(in, "axis");
    if (axis == "Sketch Y axis") {
      o = sp.frame.Location();
      d = sp.frame.YDirection();
    } else if (axis == "Sketch X axis") {
      o = sp.frame.Location();
      d = sp.frame.XDirection();
    } else if (axis == "Construction line") {
      bool found = false;
      for (const auto& e : sk.entities)
        if (e.construction && e.type == sketch::EntityType::Line) {
          const gp_Pnt a = sketch::toWorld(sp.frame, sk.points[e.a].x, sk.points[e.a].y);
          const gp_Pnt b = sketch::toWorld(sp.frame, sk.points[e.b].x, sk.points[e.b].y);
          if (a.Distance(b) < 1e-9) continue;
          o = a;
          d = gp_Dir(gp_Vec(a, b));
          found = true;
          break;
        }
      if (!found) throw CommandError("Axis: " + rec->name + " has no construction line (press X while drawing a line)");
    } else if (axis == "X") {
      d = gp_Dir(1, 0, 0);
    } else if (axis == "Y") {
      d = gp_Dir(0, 1, 0);
    }
    TopoDS_Shape tool;
    try {
      tool = kernel::revolve(faces, {o.X(), o.Y(), o.Z()}, {d.X(), d.Y(), d.Z()}, getReal(in, "angle"),
                             getString(in, "direction") == "Symmetric");
    } catch (const kernel::KernelError& e) {
      throw CommandError(e.what());
    }
    applyOperation(doc, in, tool, "Revolve");
  }

private:
  CommandDef def_;
};

// ---------------------------------------------------------------------------
// Fillet / Chamfer: change the edges of one body.

class EdgeFeature final : public Command {
public:
  enum class Kind { Fillet, Chamfer };

  explicit EdgeFeature(Kind kind) : kind_(kind) {
    const bool f = kind == Kind::Fillet;
    def_.id = f ? kCmdFillet : kCmdChamfer;
    def_.name = f ? "Fillet" : "Chamfer";
    def_.tooltip = f ? "Rounds the selected edges of a body. Connected smooth edges are included."
                     : "Bevels the selected edges of a body with an equal-distance chamfer.";
    def_.workspace = "Design";
    def_.tab = "Solid";
    def_.panel = "Modify";
    def_.icon = f ? "fillet" : "chamfer";
    def_.shortcut = f ? "F" : "";
    def_.feature = true;
    def_.inputs = {
        {.id = "body", .label = "Body", .tooltip = "Empty: the most recent body. Picking an edge sets it.",
         .type = InputType::Body, .defaultValue = std::string{}, .optional = true},
        {.id = "edges", .label = "Edges", .tooltip = "Click the edges in the canvas.", .type = InputType::Edges,
         .defaultValue = std::string{}},
        {.id = f ? "radius" : "distance", .label = f ? "Radius" : "Distance", .tooltip = {},
         .type = InputType::Real, .defaultValue = 0.1, .unit = Unit::Millimeter, .min = 0.0, .max = std::nullopt,
         .minExclusive = true},
    };
  }
  const CommandDef& def() const override { return def_; }

  std::string validate(const Inputs& in, CommandContext& ctx) const override {
    const Document& doc = docOf(ctx);
    const std::string body = getString(in, "body");
    if (body.empty() ? doc.bodies().empty() : !doc.body(body))
      return body.empty() ? "Body: there is no body to " + std::string(kind_ == Kind::Fillet ? "fillet" : "chamfer")
                          : "Body: '" + body + "' does not exist";
    return {};
  }

  void prepare(Inputs& in, CommandContext& ctx) const override {
    const Document& doc = docOf(ctx);
    if (getString(in, "body").empty()) {
      const auto bodies = doc.bodies();
      if (!bodies.empty()) in["body"] = bodies.back().name;
    }
    // Record a signature for each picked edge so replays find it again.
    if (const auto body = doc.body(getString(in, "body"))) {
      try {
        in["edges"] = kernel::completeEdgeReferences(body->shape, getString(in, "edges"));
      } catch (const kernel::KernelError& e) {
        throw CommandError(std::string("Edges: ") + e.what());
      }
    }
  }

  void apply(const Inputs& in, CommandContext& ctx) const override {
    Document& doc = docOf(ctx);
    std::string name = getString(in, "body");
    if (name.empty()) {
      const auto bodies = doc.bodies();
      if (bodies.empty()) throw CommandError("Body: there is no body");
      name = bodies.back().name;
    }
    const auto body = doc.body(name);
    if (!body) throw CommandError("Body: '" + name + "' does not exist");
    try {
      const auto edges = kernel::resolveEdges(body->shape, getString(in, "edges"));
      const TopoDS_Shape result = kind_ == Kind::Fillet ? kernel::fillet(body->shape, edges, getReal(in, "radius"))
                                                        : kernel::chamfer(body->shape, edges, getReal(in, "distance"));
      doc.replaceBody(name, result);
    } catch (const kernel::KernelError& e) {
      throw CommandError(e.what());
    }
  }

private:
  Kind kind_;
  CommandDef def_;
};

} // namespace

void registerDocCommands(CommandRegistry& registry) {
  registry.add(std::make_unique<CreateSketch>());
  registry.add(std::make_unique<Extrude>());
  registry.add(std::make_unique<Revolve>());
  registry.add(makeBox());
  registry.add(makeCylinder());
  registry.add(makeSphere());
  registry.add(makeTorus());
  registry.add(makeCone());
  registry.add(std::make_unique<EdgeFeature>(EdgeFeature::Kind::Fillet));
  registry.add(std::make_unique<EdgeFeature>(EdgeFeature::Kind::Chamfer));
  registry.add(std::make_unique<AddUserParameter>());
}

} // namespace tsr::doc
