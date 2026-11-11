#include "tsr/doc/Session.h"
#include "tsr/doc/DocCommands.h"

namespace tsr::doc {

namespace {

// Wraps a feature's command so a CommandSession can edit it: same inputs and
// validation, but apply() stores the inputs on the feature and replays.
class EditFeature final : public Command {
public:
  EditFeature(const Command& base, const Feature& f, const CommandRegistry& registry)
      : base_(base), registry_(registry), featureId_(f.id) {
    def_ = base.def();
    def_.name = "Edit " + f.name;
    def_.feature = false;
  }
  const CommandDef& def() const override { return def_; }
  std::string validate(const Inputs& in, CommandContext& ctx) const override { return base_.validate(in, ctx); }
  void apply(const Inputs& in, CommandContext& ctx) const override {
    auto& doc = dynamic_cast<Document&>(ctx);
    doc.setFeatureInputs(featureId_, in);
    doc.recompute(registry_);
    if (auto f = doc.feature(featureId_); f && !f->error.empty()) throw CommandError(f->error);
  }

private:
  const Command& base_;
  const CommandRegistry& registry_;
  int featureId_;
  CommandDef def_;
};

struct OwnedCommand {
  std::unique_ptr<Command> owned;
};

// A CommandSession that owns its (temporary) command. OwnedCommand is the
// first base so the command outlives the session's destructor.
class OwningCommandSession final : private OwnedCommand, public CommandSession {
public:
  OwningCommandSession(std::unique_ptr<Command> cmd, CommandContext& ctx, const Inputs& initial)
      : OwnedCommand{std::move(cmd)}, CommandSession(*owned, ctx, initial) {}
};

template <class F>
std::string historyEdit(Document& doc, const CommandRegistry& reg, const char* name, F&& change) {
  if (doc.hasOpenTransaction()) return "finish the current command first";
  doc.openTransaction(name);
  try {
    change();
    doc.recompute(reg);
  } catch (const std::exception& e) {
    doc.abortTransaction();
    return e.what();
  }
  doc.commitTransaction();
  return {};
}

} // namespace

Session::Session() : doc_(std::make_unique<Document>()) { registerDocCommands(commands_); }

void Session::newDocument() {
  doc_ = std::make_unique<Document>();
  path_.reset();
  notifyChanged();
}

void Session::open(const std::filesystem::path& path) {
  auto d = Document::load(path); // throws before we drop the current document
  doc_ = std::move(d);
  path_ = path;
  notifyChanged();
}

void Session::save(const std::filesystem::path& path) {
  doc_->save(path);
  path_ = path;
  notifyChanged();
}

std::string Session::run(const std::string& commandId, const Inputs& inputs) {
  std::string err = commands_.run(commandId, inputs, *doc_);
  if (err.empty()) notifyChanged();
  return err;
}

std::unique_ptr<CommandSession> Session::begin(const std::string& commandId) {
  const Command* cmd = commands_.find(commandId);
  if (!cmd) return nullptr;
  return std::make_unique<CommandSession>(*cmd, *doc_);
}

std::unique_ptr<CommandSession> Session::editFeature(int featureId) {
  const auto f = doc_->feature(featureId);
  if (!f) return nullptr;
  const Command* base = commands_.find(f->commandId);
  if (!base) return nullptr;
  return std::make_unique<OwningCommandSession>(std::make_unique<EditFeature>(*base, *f, commands_), *doc_,
                                                f->inputs);
}

std::string Session::editFeature(int featureId, const Inputs& changes) {
  auto s = editFeature(featureId);
  if (!s) return "no feature with id " + std::to_string(featureId);
  for (const auto& [k, v] : changes)
    if (auto err = s->setInput(k, v); !err.empty()) return err;
  auto err = s->execute();
  if (err.empty()) notifyChanged();
  return err;
}

std::string Session::deleteFeature(int featureId) {
  auto err = historyEdit(*doc_, commands_, "Delete feature", [&] { doc_->removeFeature(featureId); });
  if (err.empty()) notifyChanged();
  return err;
}

std::string Session::setFeatureSuppressed(int featureId, bool suppressed) {
  auto err = historyEdit(*doc_, commands_, suppressed ? "Suppress feature" : "Unsuppress feature",
                         [&] { doc_->setFeatureSuppressed(featureId, suppressed); });
  if (err.empty()) notifyChanged();
  return err;
}

bool Session::undo() {
  const bool ok = doc_->undo();
  if (ok) notifyChanged();
  return ok;
}

bool Session::redo() {
  const bool ok = doc_->redo();
  if (ok) notifyChanged();
  return ok;
}

int Session::addListener(Listener l) {
  const int id = nextListener_++;
  listeners_.emplace(id, std::move(l));
  return id;
}

void Session::removeListener(int id) { listeners_.erase(id); }

void Session::notifyChanged() {
  // Copy: a listener may add/remove listeners.
  auto copy = listeners_;
  for (auto& [id, l] : copy) l();
}

} // namespace tsr::doc
