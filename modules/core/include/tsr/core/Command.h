#pragma once
#include "tsr/core/Units.h"
#include "tsr/core/Value.h"

#include <map>
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

namespace tsr {

// ---------------------------------------------------------------------------
// Command metadata. The ribbon, the dialogs, the Python API and scripted tests
// are all generated from / driven through this one description.
// ---------------------------------------------------------------------------

// Choice: a string that must be one of InputDef::choices (a dropdown).
// Body:   the name of a body in the document, picked in the viewport; empty
//         means "the most recent body" when the input is optional.
// Sketch: the name of a sketch; empty means "the most recent sketch".
// Profiles: regions of a sketch, as "x,y;x,y" points inside them (sketch
//         coordinates, cm), picked in the viewport; empty means all of them.
enum class InputType { Real, Integer, Bool, String, Choice, Body, Sketch, Profiles };

struct InputDef {
  std::string id;
  std::string label;
  std::string tooltip;
  InputType type = InputType::Real;
  Value defaultValue;           // Real: internal units
  Unit unit = Unit::None;       // display unit for Real inputs
  std::optional<double> min;    // internal units, inclusive
  std::optional<double> max;
  bool minExclusive = false;
  bool optional = false;        // may be left empty (String/Body)
  std::vector<std::string> choices; // Choice only
};

struct CommandDef {
  std::string id;          // "tsr.primitive.box"
  std::string name;        // "Box"
  std::string tooltip;
  std::string workspace;   // "Design"
  std::string tab;         // "Solid"
  std::string panel;       // "Create"
  std::string icon;        // icon name (see app/Icons.cpp), may be empty
  std::string shortcut;    // e.g. "E"; empty for none
  // A feature is recorded in the design history (timeline) together with its
  // inputs, can be edited later and is replayed on recompute.
  bool feature = false;
  // For features: the String input whose value names the feature in the
  // timeline (e.g. a sketch's name). Empty: "<Name><n>".
  std::string nameInput;
  std::vector<InputDef> inputs;

  const InputDef* input(const std::string& inputId) const;
};

using Inputs = std::map<std::string, Value>;

// Typed accessors; throw std::invalid_argument on a missing/mistyped input.
double getReal(const Inputs& in, const std::string& id);
std::int64_t getInt(const Inputs& in, const std::string& id);
bool getBool(const Inputs& in, const std::string& id);
const std::string& getString(const Inputs& in, const std::string& id);

// ---------------------------------------------------------------------------
// The document side of a command. Implemented by tsr::doc::Document over
// OCAF transactions; tests use a fake.
// ---------------------------------------------------------------------------
class Command;

class CommandContext {
public:
  virtual ~CommandContext() = default;
  virtual void openTransaction(const std::string& name) = 0;
  virtual void commitTransaction() = 0;
  virtual void abortTransaction() = 0;
  virtual bool hasOpenTransaction() const = 0;
  // Called inside the command's transaction after a successful apply() of a
  // feature command (CommandDef::feature).
  virtual void recordFeature(const Command&, const Inputs&) {}
};

class CommandError : public std::runtime_error {
public:
  using std::runtime_error::runtime_error;
};

// A command implementation. Stateless: all state lives in Inputs and the
// document, which is what lets the same command run from UI, API and tests.
class Command {
public:
  virtual ~Command() = default;
  virtual const CommandDef& def() const = 0;
  // Cross-input / document-dependent validation. Return an empty string when
  // valid, else a user-facing message. Per-input type/range checks are done by
  // CommandSession before this is called.
  virtual std::string validate(const Inputs&, CommandContext&) const { return {}; }
  // Mutate the document. Called inside an open transaction. Throw
  // CommandError to fail; the transaction is then aborted.
  virtual void apply(const Inputs&, CommandContext&) const = 0;
  virtual bool supportsPreview() const { return true; }
  // Fills in derived inputs before apply() (e.g. a generated name) so they
  // are recorded with the feature. Runs inside the transaction.
  virtual void prepare(Inputs&, CommandContext&) const {}
};

// ---------------------------------------------------------------------------
// One run of a command: start -> (setInput -> preview)* -> execute | cancel.
// Preview applies the command inside a transaction that is aborted on the
// next change, on cancel, or right before execute re-applies it for real.
// ---------------------------------------------------------------------------
class CommandSession {
public:
  CommandSession(const Command& cmd, CommandContext& ctx);
  // Starts from the given inputs instead of the defaults (editing a feature).
  CommandSession(const Command& cmd, CommandContext& ctx, const Inputs& initial);
  virtual ~CommandSession(); // cancels a pending preview

  CommandSession(const CommandSession&) = delete;
  CommandSession& operator=(const CommandSession&) = delete;

  const CommandDef& def() const { return cmd_.def(); }
  const Inputs& inputs() const { return inputs_; }

  // Sets an input. Returns an error message for a wrong type/out-of-range
  // value (and leaves the input unchanged), else empty. Drops the preview.
  std::string setInput(const std::string& id, const Value& v);

  // Empty if all inputs are valid and the command's validate() passes.
  std::string validate();

  // Returns empty on success, else the validation/apply error. A failed
  // preview leaves no trace in the document.
  std::string preview();
  bool previewActive() const { return previewActive_; }

  // Commits the command as one undoable transaction. Returns empty on success.
  std::string execute();
  void cancel();
  bool finished() const { return finished_; }

private:
  void dropPreview();
  std::string applyInTransaction(const std::string& name);
  std::string checkInput(const InputDef& d, const Value& v) const;

  const Command& cmd_;
  CommandContext& ctx_;
  Inputs inputs_;
  bool previewActive_ = false;
  bool finished_ = false;
};

} // namespace tsr
