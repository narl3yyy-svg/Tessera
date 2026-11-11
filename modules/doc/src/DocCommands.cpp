#include "tsr/doc/DocCommands.h"
#include "tsr/doc/Document.h"

#include "tsr/kernel/Kernel.h"

#include <cctype>
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
class Box final : public Command {
public:
  Box() {
    def_.id = kCmdBox;
    def_.name = "Box";
    def_.tooltip = "Creates a solid box with one corner at the origin.";
    def_.workspace = "Design";
    def_.tab = "Solid";
    def_.panel = "Create";
    def_.icon = "box";
    auto length = [](const char* id, const char* label) {
      return InputDef{.id = id, .label = label, .tooltip = {}, .type = InputType::Real,
                      .defaultValue = 1.0, .unit = Unit::Millimeter, .min = 0.0, .max = std::nullopt,
                      .minExclusive = true};
    };
    def_.inputs = {length("length", "Length"), length("width", "Width"), length("height", "Height")};
  }
  const CommandDef& def() const override { return def_; }

  void apply(const Inputs& in, CommandContext& ctx) const override {
    Document& doc = docOf(ctx);
    TopoDS_Shape shape;
    try {
      shape = kernel::makeBox(getReal(in, "length"), getReal(in, "width"), getReal(in, "height"));
    } catch (const kernel::KernelError& e) {
      throw CommandError(e.what());
    }
    if (!kernel::isValid(shape)) throw CommandError("Box: kernel produced an invalid body");
    doc.addBody("Body" + std::to_string(doc.bodies().size() + 1), shape);
  }

private:
  CommandDef def_;
};

} // namespace

void registerDocCommands(CommandRegistry& registry) {
  registry.add(std::make_unique<Box>());
  registry.add(std::make_unique<AddUserParameter>());
}

} // namespace tsr::doc
