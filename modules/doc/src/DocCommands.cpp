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


// ---------------------------------------------------------------------------
// Body-level modify features.

InputDef bodyInput(const char* id = "body", const char* label = "Body", bool optional = true) {
  return InputDef{.id = id, .label = label,
                  .tooltip = optional ? "Empty: the most recent body. Click a body to choose." : "Click a body.",
                  .type = InputType::Body, .defaultValue = std::string{}, .optional = optional};
}

// Resolves the "body" input (empty: most recent) and records it.
std::string bodyName(const Inputs& in, const Document& doc, const char* id = "body") {
  std::string name = getString(in, id);
  if (name.empty()) {
    const auto bodies = doc.bodies();
    if (bodies.empty()) throw CommandError("there is no body");
    name = bodies.back().name;
  }
  if (!doc.body(name)) throw CommandError("Body: '" + name + "' does not exist");
  return name;
}

std::string checkBody(const Inputs& in, const Document& doc, const char* id = "body") {
  const std::string name = getString(in, id);
  if (name.empty() ? doc.bodies().empty() : !doc.body(name))
    return name.empty() ? "Body: there is no body yet" : "Body: '" + name + "' does not exist";
  return {};
}

void defaultBody(Inputs& in, const Document& doc, const char* id = "body") {
  if (getString(in, id).empty()) {
    const auto bodies = doc.bodies();
    if (!bodies.empty()) in[id] = bodies.back().name;
  }
}

kernel::Vec3 bodyCentre(const TopoDS_Shape& s) {
  const auto b = kernel::boundingBox(s);
  return {(b.min.x + b.max.x) / 2, (b.min.y + b.max.y) / 2, (b.min.z + b.max.z) / 2};
}

std::vector<std::string> splitNames(const std::string& text) {
  std::vector<std::string> out;
  size_t start = 0;
  while (start <= text.size()) {
    size_t end = text.find(';', start);
    if (end == std::string::npos) end = text.size();
    if (end > start) out.push_back(text.substr(start, end - start));
    start = end + 1;
  }
  return out;
}

void commonDef(CommandDef& d, const char* id, const char* name, const char* tip, const char* icon, const char* panel = "Modify") {
  d.id = id;
  d.name = name;
  d.tooltip = tip;
  d.workspace = "Design";
  d.tab = "Solid";
  d.panel = panel;
  d.icon = icon;
  d.feature = true;
}

class Shell final : public Command {
public:
  Shell() {
    commonDef(def_, kCmdShell, "Shell", "Hollows a body to a wall thickness. Click faces to leave open; none: a closed hollow.", "shell");
    def_.inputs = {
        bodyInput(),
        {.id = "faces", .label = "Open faces", .tooltip = "Faces to remove. None: closed hollow.",
         .type = InputType::Faces, .defaultValue = std::string{}, .optional = true},
        {.id = "thickness", .label = "Thickness", .tooltip = {}, .type = InputType::Real, .defaultValue = 0.2,
         .unit = Unit::Millimeter, .min = 0.0, .max = std::nullopt, .minExclusive = true},
        choice("direction", "Direction", {"Inside", "Outside"}, "Where the wall goes relative to the surface."),
    };
  }
  const CommandDef& def() const override { return def_; }
  std::string validate(const Inputs& in, CommandContext& ctx) const override { return checkBody(in, docOf(ctx)); }
  void prepare(Inputs& in, CommandContext& ctx) const override {
    const Document& doc = docOf(ctx);
    defaultBody(in, doc);
    if (const auto b = doc.body(getString(in, "body"))) {
      try {
        in["faces"] = kernel::completeFaceReferences(b->shape, getString(in, "faces"));
      } catch (const kernel::KernelError& e) {
        throw CommandError(std::string("Open faces: ") + e.what());
      }
    }
  }
  void apply(const Inputs& in, CommandContext& ctx) const override {
    Document& doc = docOf(ctx);
    const std::string name = bodyName(in, doc);
    const auto body = doc.body(name);
    try {
      const std::string refs = getString(in, "faces");
      const auto faces = refs.empty() ? std::vector<TopoDS_Shape>{} : kernel::resolveFaces(body->shape, refs);
      doc.replaceBody(name, kernel::shell(body->shape, faces, getReal(in, "thickness"),
                                          getString(in, "direction") == "Outside"));
    } catch (const kernel::KernelError& e) {
      throw CommandError(e.what());
    }
  }

private:
  CommandDef def_;
};

class Combine final : public Command {
public:
  Combine() {
    commonDef(def_, kCmdCombine, "Combine", "Joins, cuts or intersects bodies: a target body and one or more tool bodies.", "combine");
    def_.inputs = {
        bodyInput("target", "Target body", false),
        {.id = "tools", .label = "Tool bodies", .tooltip = "Click the tool bodies.", .type = InputType::Bodies,
         .defaultValue = std::string{}},
        choice("operation", "Operation", {"Join", "Cut", "Intersect"}, "Join merges, Cut subtracts the tools, Intersect keeps the overlap."),
        {.id = "keep", .label = "Keep tools", .tooltip = "Keep the tool bodies instead of consuming them.",
         .type = InputType::Bool, .defaultValue = false},
    };
  }
  const CommandDef& def() const override { return def_; }
  std::string validate(const Inputs& in, CommandContext& ctx) const override {
    const Document& doc = docOf(ctx);
    const std::string target = getString(in, "target");
    if (!doc.body(target)) return "Target body: '" + target + "' does not exist";
    for (const auto& t : splitNames(getString(in, "tools"))) {
      if (t == target) return "Tool bodies: the target cannot also be a tool";
      if (!doc.body(t)) return "Tool bodies: '" + t + "' does not exist";
    }
    return {};
  }
  void apply(const Inputs& in, CommandContext& ctx) const override {
    Document& doc = docOf(ctx);
    const std::string target = getString(in, "target");
    auto shape = doc.body(target);
    if (!shape) throw CommandError("Target body: '" + target + "' does not exist");
    const std::string op = getString(in, "operation");
    const auto kind = op == "Join" ? kernel::BooleanOp::Join : op == "Cut" ? kernel::BooleanOp::Cut : kernel::BooleanOp::Intersect;
    TopoDS_Shape result = shape->shape;
    const auto tools = splitNames(getString(in, "tools"));
    if (tools.empty()) throw CommandError("Tool bodies: select one or more bodies");
    for (const auto& t : tools) {
      const auto tb = doc.body(t);
      if (!tb) throw CommandError("Tool bodies: '" + t + "' does not exist");
      try {
        result = kernel::boolean(kind, result, tb->shape);
      } catch (const kernel::KernelError& e) {
        throw CommandError(e.what());
      }
    }
    doc.replaceBody(target, result);
    if (!getBool(in, "keep"))
      for (const auto& t : tools) doc.removeBody(t);
  }

private:
  CommandDef def_;
};

gp_Ax3 planeOf(const Inputs& in) {
  try {
    return sketch::planeFrame(getString(in, "plane"), getReal(in, "offset"));
  } catch (const sketch::SketchError& e) {
    throw CommandError(e.what());
  }
}

InputDef planeChoice(const char* tip) { return choice("plane", "Plane", {"XY", "XZ", "YZ"}, tip); }
InputDef planeOffset() {
  return InputDef{.id = "offset", .label = "Offset", .tooltip = "Moves the plane along its normal.",
                  .type = InputType::Real, .defaultValue = 0.0, .unit = Unit::Millimeter};
}

class SplitBody final : public Command {
public:
  SplitBody() {
    commonDef(def_, kCmdSplitBody, "Split Body", "Cuts a body into separate bodies with a plane.", "split");
    def_.inputs = {bodyInput(), planeChoice("Splitting plane (origin plane, moved by Offset)."), planeOffset()};
  }
  const CommandDef& def() const override { return def_; }
  std::string validate(const Inputs& in, CommandContext& ctx) const override { return checkBody(in, docOf(ctx)); }
  void prepare(Inputs& in, CommandContext& ctx) const override { defaultBody(in, docOf(ctx)); }
  void apply(const Inputs& in, CommandContext& ctx) const override {
    Document& doc = docOf(ctx);
    const std::string name = bodyName(in, doc);
    const gp_Ax3 f = planeOf(in);
    const gp_Pnt o = f.Location();
    const gp_Dir n = f.Direction();
    std::vector<TopoDS_Shape> parts;
    try {
      parts = kernel::splitByPlane(doc.body(name)->shape, {o.X(), o.Y(), o.Z()}, {n.X(), n.Y(), n.Z()});
    } catch (const kernel::KernelError& e) {
      throw CommandError(e.what());
    }
    doc.replaceBody(name, parts[0]);
    for (size_t i = 1; i < parts.size(); ++i) doc.addBody(doc.nextBodyName(), parts[i]);
  }

private:
  CommandDef def_;
};

class MoveCopy final : public Command {
public:
  MoveCopy() {
    commonDef(def_, kCmdMove, "Move/Copy", "Moves or copies a body: translate, then rotate about an axis through its centre.", "move");
    def_.shortcut = "M";
    auto len = [](const char* id, const char* label) {
      return InputDef{.id = id, .label = label, .tooltip = {}, .type = InputType::Real, .defaultValue = 0.0,
                      .unit = Unit::Millimeter};
    };
    def_.inputs = {bodyInput(), len("x", "X distance"), len("y", "Y distance"), len("z", "Z distance"),
                   choice("axis", "Rotate about", {"Z", "Y", "X"}, "Axis through the body centre."),
                   {.id = "angle", .label = "Angle", .tooltip = {}, .type = InputType::Real, .defaultValue = 0.0,
                    .unit = Unit::Degree},
                   {.id = "copy", .label = "Create copy", .tooltip = "Keep the original and add a moved copy.",
                    .type = InputType::Bool, .defaultValue = false}};
  }
  const CommandDef& def() const override { return def_; }
  std::string validate(const Inputs& in, CommandContext& ctx) const override { return checkBody(in, docOf(ctx)); }
  void prepare(Inputs& in, CommandContext& ctx) const override { defaultBody(in, docOf(ctx)); }
  void apply(const Inputs& in, CommandContext& ctx) const override {
    Document& doc = docOf(ctx);
    const std::string name = bodyName(in, doc);
    const TopoDS_Shape s = doc.body(name)->shape;
    const std::string a = getString(in, "axis");
    const kernel::Vec3 dir = a == "X" ? kernel::Vec3{1, 0, 0} : a == "Y" ? kernel::Vec3{0, 1, 0} : kernel::Vec3{0, 0, 1};
    TopoDS_Shape r;
    try {
      r = kernel::moved(s, {getReal(in, "x"), getReal(in, "y"), getReal(in, "z")}, bodyCentre(s), dir, getReal(in, "angle"));
    } catch (const kernel::KernelError& e) {
      throw CommandError(e.what());
    }
    if (getBool(in, "copy")) doc.addBody(doc.nextBodyName(), r);
    else doc.replaceBody(name, r);
  }

private:
  CommandDef def_;
};

class Mirror final : public Command {
public:
  Mirror() {
    commonDef(def_, kCmdMirror, "Mirror", "Mirrors a body across a plane, as a new body or joined to the original.", "mirror", "Create");
    def_.inputs = {bodyInput(), planeChoice("Mirror plane (origin plane, moved by Offset)."), planeOffset(),
                   choice("operation", "Operation", {"New Body", "Join"}, "Join merges the mirror image with the original.")};
  }
  const CommandDef& def() const override { return def_; }
  std::string validate(const Inputs& in, CommandContext& ctx) const override { return checkBody(in, docOf(ctx)); }
  void prepare(Inputs& in, CommandContext& ctx) const override { defaultBody(in, docOf(ctx)); }
  void apply(const Inputs& in, CommandContext& ctx) const override {
    Document& doc = docOf(ctx);
    const std::string name = bodyName(in, doc);
    const gp_Ax3 f = planeOf(in);
    const TopoDS_Shape s = doc.body(name)->shape;
    try {
      const TopoDS_Shape m = kernel::mirrored(s, {f.Location().X(), f.Location().Y(), f.Location().Z()},
                                              {f.Direction().X(), f.Direction().Y(), f.Direction().Z()});
      if (getString(in, "operation") == "Join") doc.replaceBody(name, kernel::boolean(kernel::BooleanOp::Join, s, m));
      else doc.addBody(doc.nextBodyName(), m);
    } catch (const kernel::KernelError& e) {
      throw CommandError(e.what());
    }
  }

private:
  CommandDef def_;
};

class Scale final : public Command {
public:
  Scale() {
    commonDef(def_, kCmdScale, "Scale", "Scales a body uniformly.", "scale");
    def_.inputs = {bodyInput(),
                   {.id = "factor", .label = "Scale factor", .tooltip = "2 doubles every size.", .type = InputType::Real,
                    .defaultValue = 1.0, .unit = Unit::None, .min = 0.0, .max = std::nullopt, .minExclusive = true},
                   choice("about", "About", {"Body centre", "Origin"}, "Point that stays fixed.")};
  }
  const CommandDef& def() const override { return def_; }
  std::string validate(const Inputs& in, CommandContext& ctx) const override { return checkBody(in, docOf(ctx)); }
  void prepare(Inputs& in, CommandContext& ctx) const override { defaultBody(in, docOf(ctx)); }
  void apply(const Inputs& in, CommandContext& ctx) const override {
    Document& doc = docOf(ctx);
    const std::string name = bodyName(in, doc);
    const TopoDS_Shape s = doc.body(name)->shape;
    try {
      const kernel::Vec3 c = getString(in, "about") == "Origin" ? kernel::Vec3{} : bodyCentre(s);
      doc.replaceBody(name, kernel::scaled(s, getReal(in, "factor"), c));
    } catch (const kernel::KernelError& e) {
      throw CommandError(e.what());
    }
  }

private:
  CommandDef def_;
};

class RemoveBody final : public Command {
public:
  RemoveBody() {
    commonDef(def_, kCmdRemove, "Remove", "Removes a body from the design (as a timeline step, so it can be undone or edited).", "remove");
    def_.inputs = {bodyInput()};
  }
  const CommandDef& def() const override { return def_; }
  std::string validate(const Inputs& in, CommandContext& ctx) const override { return checkBody(in, docOf(ctx)); }
  void prepare(Inputs& in, CommandContext& ctx) const override { defaultBody(in, docOf(ctx)); }
  void apply(const Inputs& in, CommandContext& ctx) const override {
    Document& doc = docOf(ctx);
    doc.removeBody(bodyName(in, doc));
  }

private:
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
  registry.add(std::make_unique<Mirror>());
  registry.add(std::make_unique<EdgeFeature>(EdgeFeature::Kind::Fillet));
  registry.add(std::make_unique<EdgeFeature>(EdgeFeature::Kind::Chamfer));
  registry.add(std::make_unique<Shell>());
  registry.add(std::make_unique<Scale>());
  registry.add(std::make_unique<Combine>());
  registry.add(std::make_unique<SplitBody>());
  registry.add(std::make_unique<MoveCopy>());
  registry.add(std::make_unique<RemoveBody>());
  registry.add(std::make_unique<AddUserParameter>());
}

} // namespace tsr::doc
