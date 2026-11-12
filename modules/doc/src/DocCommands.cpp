#include "tsr/doc/DocCommands.h"
#include "tsr/doc/Document.h"

#include "tsr/kernel/Io.h"
#include "tsr/kernel/Kernel.h"

#include <BRepPrimAPI_MakeCone.hxx>
#include <BRepPrimAPI_MakeCylinder.hxx>
#include <Standard_Failure.hxx>
#include <TopExp_Explorer.hxx>
#include <gp_Ax2.hxx>
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
  return InputDef{.id = id, .label = label, .tooltip = tip ? tip : "", .type = InputType::Choice,
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
        {.id = "plane", .label = "Plane", .tooltip = "XY, XZ, YZ, a construction plane (Plane1) or custom:...",
         .type = InputType::Plane, .defaultValue = std::string("XY")},
        {.id = "offset", .label = "Offset", .tooltip = "Moves the plane along its normal.", .type = InputType::Real,
         .defaultValue = 0.0, .unit = Unit::Millimeter},
        {.id = "data", .label = "Geometry", .tooltip = "Sketch geometry and constraints (JSON).",
         .type = InputType::String, .defaultValue = std::string{}, .optional = true},
    };
  }
  const CommandDef& def() const override { return def_; }

  std::string validate(const Inputs& in, CommandContext& ctx) const override {
    try {
      (void)docOf(ctx).planeFrame(getString(in, "plane"), getReal(in, "offset"));
      (void)sketch::Sketch::fromJson(getString(in, "data"));
    } catch (const sketch::SketchError& e) {
      return e.what();
    } catch (const DocumentError& e) {
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
      (void)doc.planeFrame(rec.plane, rec.offset);
      sketch::Sketch s = sketch::Sketch::fromJson(getString(in, "data"));
      const auto res = sketch::solve(s);
      if (!res.ok) throw CommandError(rec.name + ": " + res.message);
      rec.data = s.toJson();
    } catch (const sketch::SketchError& e) {
      throw CommandError(rec.name + ": " + e.what());
    } catch (const DocumentError& e) {
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

SketchProfiles profilesOf(const Document& doc, const SketchRecord& rec) {
  SketchProfiles out;
  try {
    out.frame = doc.planeFrame(rec.plane, rec.offset);
  } catch (const DocumentError& e) {
    throw sketch::SketchError(e.what());
  }
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
        choice("start", "Start", {"Profile Plane", "Offset"}, "Where the extrude starts."),
        {.id = "startOffset", .label = "Offset", .tooltip = "Distance from the profile plane to the start.",
         .type = InputType::Real, .defaultValue = 0.0, .unit = Unit::Millimeter, .visibleWhen = "start=Offset"},
        choice("direction", "Direction", {"One Side", "Two Sides", "Symmetric"},
               "Symmetric: the distance both ways. Two Sides: a distance each way."),
        choice("extent", "Extent Type", {"Distance", "All"}, "All: through everything in the design."),
        {.id = "distance", .label = "Distance", .tooltip = "Negative extrudes the other way.",
         .type = InputType::Real, .defaultValue = 1.0, .unit = Unit::Millimeter, .visibleWhen = "extent=Distance"},
        {.id = "distance2", .label = "Distance (side 2)", .tooltip = "Two Sides only.", .type = InputType::Real,
         .defaultValue = 1.0, .unit = Unit::Millimeter, .visibleWhen = "direction=Two Sides"},
        {.id = "taper", .label = "Taper Angle", .tooltip = "One side only. Positive widens.", .type = InputType::Real,
         .defaultValue = 0.0, .unit = Unit::Degree, .min = -1.5, .max = 1.5, .visibleWhen = "direction=One Side"},
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
    if (getString(in, "extent") == "Distance" && std::abs(getReal(in, "distance")) < 1e-9)
      return "Distance: must not be zero";
    if (std::abs(getReal(in, "taper")) > 1e-9 && getString(in, "direction") != "One Side")
      return "Taper Angle: only with Direction One Side";
    return validateOperation(in, doc);
  }

  void prepare(Inputs& in, CommandContext& ctx) const override {
    // Inputs added after a feature was created get their defaults.
    for (const auto& d : def_.inputs)
      if (!in.count(d.id)) in[d.id] = d.defaultValue;
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
      sp = profilesOf(doc, *rec);
    } catch (const sketch::SketchError& e) {
      throw CommandError(e.what());
    }
    if (sp.profiles.empty()) throw CommandError(rec->name + " has no closed profile to extrude");

    const auto faces = pickedFaces(sp, getString(in, "profiles"), rec->name);
    const gp_Dir n = sp.frame.Direction();
    auto real = [&](const char* id, double fallback) {
      auto it = in.find(id);
      return it == in.end() ? fallback : getReal(in, id);
    };
    auto str = [&](const char* id, const char* fallback) {
      auto it = in.find(id);
      return it == in.end() ? std::string(fallback) : getString(in, id);
    };
    double d1 = real("distance", 1.0);
    if (str("extent", "Distance") == "All") {
      // Far enough to pass through every body (and the sketch) in both senses.
      double size = 10;
      for (const auto& b : doc.bodies()) {
        const auto bb = kernel::boundingBox(b.shape);
        size = std::max(size, std::hypot(bb.max.x - bb.min.x, bb.max.y - bb.min.y, bb.max.z - bb.min.z) +
                                  std::hypot(bb.max.x, bb.max.y, bb.max.z) + std::hypot(bb.min.x, bb.min.y, bb.min.z));
      }
      d1 = d1 < 0 ? -size : size;
    }
    const std::string dir = str("direction", "One Side");
    const double back = dir == "Symmetric" ? d1 : dir == "Two Sides" ? real("distance2", 1.0) : 0.0;
    const double start = str("start", "Profile Plane") == "Offset" ? real("startOffset", 0.0) : 0.0;
    TopoDS_Shape tool;
    try {
      tool = kernel::extrudeEx(faces, {n.X(), n.Y(), n.Z()}, d1, back, real("taper", 0.0), start);
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
      sp = profilesOf(doc, *rec);
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

gp_Ax3 planeOf(const Document& doc, const Inputs& in, const char* id = "plane", const char* offsetId = "offset") {
  try {
    return doc.planeFrame(getString(in, id), in.count(offsetId) ? getReal(in, offsetId) : 0.0);
  } catch (const DocumentError& e) {
    throw CommandError(e.what());
  }
}

InputDef planeChoice(const char* tip, const char* id = "plane", const char* label = "Plane") {
  return InputDef{.id = id, .label = label, .tooltip = tip, .type = InputType::Plane, .defaultValue = std::string("XY")};
}
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
    const gp_Ax3 f = planeOf(doc, in);
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
    const gp_Ax3 f = planeOf(doc, in);
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

// Document Settings > Units. Not a feature (no timeline entry) but undoable.
class DocumentUnits final : public Command {
public:
  DocumentUnits() {
    def_.id = kCmdUnits;
    def_.name = "Change Units";
    def_.tooltip = "Default length unit for this design.";
    def_.workspace = "Design";
    def_.icon = "units";
    def_.inputs = {choice("unit", "Default units", {"mm", "in", "cm", "m"}, "Shown in dialogs, dimensions and measurements.")};
  }
  const CommandDef& def() const override { return def_; }
  void apply(const Inputs& in, CommandContext& ctx) const override {
    try {
      docOf(ctx).setLengthUnit(getString(in, "unit"));
    } catch (const DocumentError& e) {
      throw CommandError(e.what());
    }
  }

private:
  CommandDef def_;
};

// Insert > geometry from a file, stored in the timeline as BREP text.
class InsertGeometry final : public Command {
public:
  InsertGeometry() {
    def_.id = kCmdInsert;
    def_.name = "Insert";
    def_.tooltip = "Geometry inserted from a STEP, IGES, STL or BREP file.";
    def_.workspace = "Design";
    def_.icon = "insert";
    def_.feature = true;
    def_.inputs = {
        {.id = "source", .label = "Source file", .tooltip = {}, .type = InputType::String,
         .defaultValue = std::string{}, .optional = true},
        {.id = "brep", .label = "Geometry", .tooltip = "BREP text (internal units).", .type = InputType::String,
         .defaultValue = std::string{}},
    };
  }
  const CommandDef& def() const override { return def_; }
  void apply(const Inputs& in, CommandContext& ctx) const override {
    Document& doc = docOf(ctx);
    TopoDS_Shape s;
    try {
      s = kernel::fromBrep(getString(in, "brep"));
    } catch (const kernel::KernelError& e) {
      throw CommandError(e.what());
    }
    // One body per solid; shells/faces (open meshes) become one body.
    int solids = 0;
    for (TopExp_Explorer it(s, TopAbs_SOLID); it.More(); it.Next(), ++solids) doc.addBody(doc.nextBodyName(), it.Current());
    if (solids == 0) doc.addBody(doc.nextBodyName(), s);
  }

private:
  CommandDef def_;
};

// ---------------------------------------------------------------------------
// Hole: drilled at every point of a sketch (points not used by curves), into
// the material on the side opposite the sketch plane's normal.
class Hole final : public Command {
public:
  Hole() {
    commonDef(def_, kCmdHole, "Hole", "Simple, counterbore or countersink holes at the points of a sketch.", "hole", "Create");
    def_.shortcut = "H";
    auto len = [](const char* id, const char* label, double v, const char* when = "") {
      return InputDef{.id = id, .label = label, .tooltip = {}, .type = InputType::Real, .defaultValue = v,
                      .unit = Unit::Millimeter, .min = 0.0, .max = std::nullopt, .minExclusive = true,
                      .visibleWhen = when};
    };
    def_.inputs = {
        {.id = "sketch", .label = "Sketch (points)", .tooltip = "Holes go at this sketch's points. Empty: latest sketch.",
         .type = InputType::Sketch, .defaultValue = std::string{}, .optional = true},
        choice("holeType", "Hole Type", {"Simple", "Counterbore", "Countersink"}, {}),
        len("diameter", "Diameter", 0.5),
        choice("extent", "Extents", {"Distance", "All"}, "All: through the whole body."),
        len("depth", "Depth", 1.0, "extent=Distance"),
        len("cboreDiameter", "Counterbore Diameter", 0.9, "holeType=Counterbore"),
        len("cboreDepth", "Counterbore Depth", 0.3, "holeType=Counterbore"),
        len("csinkDiameter", "Countersink Diameter", 1.0, "holeType=Countersink"),
        InputDef{.id = "csinkAngle", .label = "Countersink Angle", .tooltip = {}, .type = InputType::Real,
                 .defaultValue = 1.5707963267948966, .unit = Unit::Degree, .min = 0.1, .max = 3.0,
                 .visibleWhen = "holeType=Countersink"},
        choice("flip", "Direction", {"Into material", "Flipped"}, "Holes go opposite the sketch plane's normal; Flipped reverses."),
        bodyInput("target", "Body"),
    };
  }
  const CommandDef& def() const override { return def_; }
  std::string validate(const Inputs& in, CommandContext& ctx) const override {
    const Document& doc = docOf(ctx);
    if (!sketchFor(doc, getString(in, "sketch"))) return "Sketch: there is no sketch with hole points";
    return checkBody(in, doc, "target");
  }
  void prepare(Inputs& in, CommandContext& ctx) const override {
    const Document& doc = docOf(ctx);
    if (getString(in, "sketch").empty())
      if (auto rec = sketchFor(doc, "")) in["sketch"] = rec->name;
    defaultBody(in, doc, "target");
  }
  void apply(const Inputs& in, CommandContext& ctx) const override {
    Document& doc = docOf(ctx);
    const auto rec = sketchFor(doc, getString(in, "sketch"));
    if (!rec) throw CommandError("Sketch: '" + getString(in, "sketch") + "' does not exist");
    const std::string target = bodyName(in, doc, "target");
    sketch::Sketch sk;
    gp_Ax3 frame;
    try {
      sk = sketch::Sketch::fromJson(rec->data);
      frame = doc.planeFrame(rec->plane, rec->offset);
    } catch (const sketch::SketchError& e) {
      throw CommandError(e.what());
    } catch (const DocumentError& e) {
      throw CommandError(e.what());
    }
    std::vector<bool> used(sk.points.size(), false);
    used[0] = true;
    for (const auto& e : sk.entities)
      for (int p : {e.a, e.b, e.center})
        if (p >= 0) used[p] = true;
    std::vector<gp_Pnt> centres;
    for (size_t i = 0; i < sk.points.size(); ++i)
      if (!used[i]) centres.push_back(sketch::toWorld(frame, sk.points[i].x, sk.points[i].y));
    if (centres.empty()) throw CommandError(rec->name + " has no points: add points (P) where the holes go");

    TopoDS_Shape body = doc.body(target)->shape;
    const auto bb = kernel::boundingBox(body);
    const double size = std::hypot(bb.max.x - bb.min.x, bb.max.y - bb.min.y, bb.max.z - bb.min.z) +
                        std::hypot(bb.max.x, bb.max.y, bb.max.z) + std::hypot(bb.min.x, bb.min.y, bb.min.z) + 1;
    gp_Dir into = frame.Direction().Reversed();
    if (getString(in, "flip") == "Flipped") into.Reverse();
    const double depth = getString(in, "extent") == "All" ? size : getReal(in, "depth");
    const double r = getReal(in, "diameter") / 2;
    const std::string type = getString(in, "holeType");
    const double eps = 1e-3;   // start just outside the face so the cut is clean
    try {
      for (const gp_Pnt& c : centres) {
        const gp_Pnt start = c.Translated(-gp_Vec(into) * eps);
        auto cyl = [&](double radius, double length) {
          const gp_Ax2 ax(start, into);
          return BRepPrimAPI_MakeCylinder(ax, radius, length + eps).Shape();
        };
        TopoDS_Shape tool = cyl(r, depth);
        if (type == "Counterbore") {
          const double cr = getReal(in, "cboreDiameter") / 2;
          if (cr <= r) throw CommandError("Counterbore Diameter must be larger than the hole");
          tool = kernel::boolean(kernel::BooleanOp::Join, tool, cyl(cr, getReal(in, "cboreDepth")));
        } else if (type == "Countersink") {
          const double sr = getReal(in, "csinkDiameter") / 2;
          if (sr <= r) throw CommandError("Countersink Diameter must be larger than the hole");
          const double h = (sr - r) / std::tan(getReal(in, "csinkAngle") / 2);
          const TopoDS_Shape cone = BRepPrimAPI_MakeCone(gp_Ax2(start, into), sr + eps, r, h + eps).Shape();
          tool = kernel::boolean(kernel::BooleanOp::Join, tool, cone);
        }
        body = kernel::boolean(kernel::BooleanOp::Cut, body, tool);
      }
    } catch (const kernel::KernelError& e) {
      throw CommandError(std::string("Hole: ") + e.what() + " (are the points on the body?)");
    } catch (const Standard_Failure& f) {
      throw CommandError(std::string("Hole: ") + f.GetMessageString());
    }
    doc.replaceBody(target, body);
  }

private:
  CommandDef def_;
};

// ---------------------------------------------------------------------------
// Patterns of a body.
kernel::Vec3 axisVec(const std::string& a) {
  return a == "X" ? kernel::Vec3{1, 0, 0} : a == "Y" ? kernel::Vec3{0, 1, 0} : kernel::Vec3{0, 0, 1};
}

void placeCopies(Document& doc, const std::string& name, const std::vector<TopoDS_Shape>& copies, bool join) {
  if (join) {
    TopoDS_Shape all = doc.body(name)->shape;
    for (const auto& c : copies) all = kernel::boolean(kernel::BooleanOp::Join, all, c);
    doc.replaceBody(name, all);
  } else {
    for (const auto& c : copies) doc.addBody(doc.nextBodyName(), c);
  }
}

class RectangularPattern final : public Command {
public:
  RectangularPattern() {
    commonDef(def_, kCmdRectPattern, "Rectangular Pattern", "Copies a body in rows and columns.", "pattern-rect", "Create");
    auto count = [](const char* id, const char* label, std::int64_t v) {
      return InputDef{.id = id, .label = label, .tooltip = "Including the original.", .type = InputType::Integer,
                      .defaultValue = v, .unit = Unit::None, .min = 1.0, .max = 1000.0};
    };
    auto spacing = [](const char* id, const char* label) {
      return InputDef{.id = id, .label = label, .tooltip = "Distance between copies.", .type = InputType::Real,
                      .defaultValue = 2.0, .unit = Unit::Millimeter};
    };
    def_.inputs = {bodyInput(),
                   choice("direction1", "Direction 1", {"X", "Y", "Z"}, {}), count("quantity1", "Quantity", 3),
                   spacing("distance1", "Spacing"),
                   choice("direction2", "Direction 2", {"Y", "Z", "X"}, {}), count("quantity2", "Quantity 2", 1),
                   spacing("distance2", "Spacing 2"),
                   choice("result", "Result", {"Join", "New Bodies"}, "Join: one body; New Bodies: separate copies.")};
  }
  const CommandDef& def() const override { return def_; }
  std::string validate(const Inputs& in, CommandContext& ctx) const override { return checkBody(in, docOf(ctx)); }
  void prepare(Inputs& in, CommandContext& ctx) const override { defaultBody(in, docOf(ctx)); }
  void apply(const Inputs& in, CommandContext& ctx) const override {
    Document& doc = docOf(ctx);
    const std::string name = bodyName(in, doc);
    const TopoDS_Shape s = doc.body(name)->shape;
    const auto d1 = axisVec(getString(in, "direction1")), d2 = axisVec(getString(in, "direction2"));
    const double s1 = getReal(in, "distance1"), s2 = getReal(in, "distance2");
    std::vector<TopoDS_Shape> copies;
    try {
      for (std::int64_t i = 0; i < getInt(in, "quantity1"); ++i)
        for (std::int64_t j = 0; j < getInt(in, "quantity2"); ++j) {
          if (i == 0 && j == 0) continue;
          const kernel::Vec3 off{d1.x * s1 * i + d2.x * s2 * j, d1.y * s1 * i + d2.y * s2 * j, d1.z * s1 * i + d2.z * s2 * j};
          copies.push_back(kernel::moved(s, off, {}, {0, 0, 1}, 0));
        }
      placeCopies(doc, name, copies, getString(in, "result") == "Join");
    } catch (const kernel::KernelError& e) {
      throw CommandError(e.what());
    }
  }

private:
  CommandDef def_;
};

class CircularPattern final : public Command {
public:
  CircularPattern() {
    commonDef(def_, kCmdCircPattern, "Circular Pattern", "Copies a body around an axis through the origin.", "pattern-circ", "Create");
    def_.inputs = {bodyInput(),
                   choice("axis", "Axis", {"Z", "Y", "X"}, "World axis through the origin."),
                   InputDef{.id = "quantity", .label = "Quantity", .tooltip = "Including the original.",
                            .type = InputType::Integer, .defaultValue = std::int64_t{6}, .unit = Unit::None,
                            .min = 2.0, .max = 1000.0},
                   InputDef{.id = "angle", .label = "Total Angle", .tooltip = "360 deg: evenly around.",
                            .type = InputType::Real, .defaultValue = 2 * 3.14159265358979323846, .unit = Unit::Degree},
                   choice("result", "Result", {"Join", "New Bodies"}, {})};
  }
  const CommandDef& def() const override { return def_; }
  std::string validate(const Inputs& in, CommandContext& ctx) const override { return checkBody(in, docOf(ctx)); }
  void prepare(Inputs& in, CommandContext& ctx) const override { defaultBody(in, docOf(ctx)); }
  void apply(const Inputs& in, CommandContext& ctx) const override {
    Document& doc = docOf(ctx);
    const std::string name = bodyName(in, doc);
    const TopoDS_Shape s = doc.body(name)->shape;
    const auto n = getInt(in, "quantity");
    const double total = getReal(in, "angle");
    const bool full = std::abs(std::abs(total) - 2 * 3.14159265358979323846) < 1e-9;
    const double step = full ? total / n : total / std::max<std::int64_t>(n - 1, 1);
    std::vector<TopoDS_Shape> copies;
    try {
      for (std::int64_t i = 1; i < n; ++i) copies.push_back(kernel::moved(s, {}, {}, axisVec(getString(in, "axis")), step * i));
      placeCopies(doc, name, copies, getString(in, "result") == "Join");
    } catch (const kernel::KernelError& e) {
      throw CommandError(e.what());
    }
  }

private:
  CommandDef def_;
};

// ---------------------------------------------------------------------------
// Construct: named construction planes.
class ConstructPlane final : public Command {
public:
  enum class Kind { Offset, Angle, Mid };
  explicit ConstructPlane(Kind kind) : kind_(kind) {
    const char* id = kind == Kind::Offset ? kCmdOffsetPlane : kind == Kind::Angle ? kCmdPlaneAtAngle : kCmdMidplane;
    const char* name = kind == Kind::Offset ? "Offset Plane" : kind == Kind::Angle ? "Plane at Angle" : "Midplane";
    const char* tip = kind == Kind::Offset ? "A plane parallel to another, at a distance."
                    : kind == Kind::Angle  ? "A plane turned about an axis of another plane."
                                           : "The plane halfway between two parallel planes.";
    commonDef(def_, id, name, tip, kind == Kind::Offset ? "plane" : kind == Kind::Angle ? "plane-angle" : "plane-mid",
              "Construct");
    def_.nameInput = "name";
    def_.inputs = {{.id = "name", .label = "Name", .tooltip = "Empty: Plane<n>.", .type = InputType::String,
                    .defaultValue = std::string{}, .optional = true},
                   planeChoice("Plane to start from.")};
    if (kind == Kind::Offset)
      def_.inputs.push_back({.id = "distance", .label = "Distance", .tooltip = {}, .type = InputType::Real,
                             .defaultValue = 1.0, .unit = Unit::Millimeter});
    if (kind == Kind::Angle) {
      def_.inputs.push_back(choice("axis", "Axis", {"Plane X axis", "Plane Y axis"}, "Axis of the plane to turn about."));
      def_.inputs.push_back({.id = "angle", .label = "Angle", .tooltip = {}, .type = InputType::Real,
                             .defaultValue = 0.7853981633974483, .unit = Unit::Degree});
    }
    if (kind == Kind::Mid) def_.inputs.push_back(planeChoice("Second plane (parallel to the first).", "plane2", "Plane 2"));
  }
  const CommandDef& def() const override { return def_; }

  std::string validate(const Inputs& in, CommandContext& ctx) const override {
    try {
      (void)frame(docOf(ctx), in);
    } catch (const std::exception& e) {
      return e.what();
    }
    return {};
  }
  void prepare(Inputs& in, CommandContext& ctx) const override {
    if (getString(in, "name").empty()) in["name"] = docOf(ctx).nextPlaneName();
  }
  void apply(const Inputs& in, CommandContext& ctx) const override {
    Document& doc = docOf(ctx);
    std::string name = getString(in, "name");
    if (name.empty()) name = doc.nextPlaneName();
    doc.setPlane({name, sketch::customPlaneSpec(frame(doc, in))});
  }

private:
  gp_Ax3 frame(const Document& doc, const Inputs& in) const {
    gp_Ax3 f = planeOf(doc, in);
    if (kind_ == Kind::Offset) {
      f.Translate(gp_Vec(f.Direction()) * getReal(in, "distance"));
    } else if (kind_ == Kind::Angle) {
      const gp_Dir axis = getString(in, "axis") == "Plane Y axis" ? f.YDirection() : f.XDirection();
      f.Rotate(gp_Ax1(f.Location(), axis), getReal(in, "angle"));
    } else {
      const gp_Ax3 g = planeOf(doc, in, "plane2");
      if (!f.Direction().IsParallel(g.Direction(), 1e-6)) throw CommandError("Plane 2: must be parallel to the first plane");
      const double d = gp_Vec(f.Location(), g.Location()).Dot(gp_Vec(f.Direction()));
      f.Translate(gp_Vec(f.Direction()) * (d / 2));
    }
    return f;
  }
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
  registry.add(std::make_unique<Hole>());
  registry.add(std::make_unique<RectangularPattern>());
  registry.add(std::make_unique<CircularPattern>());
  registry.add(std::make_unique<Mirror>());
  registry.add(std::make_unique<EdgeFeature>(EdgeFeature::Kind::Fillet));
  registry.add(std::make_unique<EdgeFeature>(EdgeFeature::Kind::Chamfer));
  registry.add(std::make_unique<Shell>());
  registry.add(std::make_unique<Scale>());
  registry.add(std::make_unique<Combine>());
  registry.add(std::make_unique<SplitBody>());
  registry.add(std::make_unique<MoveCopy>());
  registry.add(std::make_unique<RemoveBody>());
  registry.add(std::make_unique<ConstructPlane>(ConstructPlane::Kind::Offset));
  registry.add(std::make_unique<ConstructPlane>(ConstructPlane::Kind::Angle));
  registry.add(std::make_unique<ConstructPlane>(ConstructPlane::Kind::Mid));
  registry.add(std::make_unique<AddUserParameter>());
  registry.add(std::make_unique<DocumentUnits>());
  registry.add(std::make_unique<InsertGeometry>());
}

} // namespace tsr::doc
