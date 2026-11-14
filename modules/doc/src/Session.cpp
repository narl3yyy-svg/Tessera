#include "tsr/doc/Session.h"
#include "tsr/doc/DocCommands.h"

#include <map>

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
  } catch (...) {
    doc.abortTransaction();
    return std::string(name) + ": the geometry kernel failed";
  }
  doc.commitTransaction();
  return {};
}

} // namespace

Session::Session() : doc_(std::make_unique<Document>()) {
  registerDocCommands(commands_);
  doc_->setRegistry(&commands_);
}

void Session::newDocument() {
  doc_ = std::make_unique<Document>();
  doc_->setRegistry(&commands_);
  path_.reset();
  notifyChanged();
}

void Session::open(const std::filesystem::path& path) {
  auto d = Document::load(path); // throws before we drop the current document
  doc_ = std::move(d);
  doc_->setRegistry(&commands_);
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

std::string Session::renameBody(const std::string& name, const std::string& newName) {
  if (doc_->hasOpenTransaction()) return "finish the current command first";
  doc_->openTransaction("Rename body");
  try {
    doc_->renameBody(name, newName);
  } catch (const std::exception& e) {
    doc_->abortTransaction();
    return e.what();
  }
  doc_->commitTransaction();
  notifyChanged();
  return {};
}

std::string Session::setBodyLooks(const std::vector<std::string>& bodies, const std::string* color,
                                  const std::string* material) {
  if (doc_->hasOpenTransaction()) return "finish the current command first";
  doc_->openTransaction(material ? "Physical Material" : "Appearance");
  try {
    for (const auto& b : bodies) {
      if (color) doc_->setBodyColor(b, *color);
      if (material) doc_->setBodyMaterial(b, *material);
    }
  } catch (const std::exception& e) {
    doc_->abortTransaction();
    return e.what();
  }
  doc_->commitTransaction();
  notifyChanged();
  return {};
}

std::string Session::renameSketch(const std::string& name, const std::string& newName) {
  auto err = historyEdit(*doc_, commands_, "Rename sketch", [&] { doc_->renameSketch(name, newName); });
  if (err.empty()) notifyChanged();
  return err;
}

// A change outside the history: its own undo step, nothing replayed.
template <typename F>
static std::string plainEdit(Document& doc, const char* name, F&& change) {
  if (doc.hasOpenTransaction()) return "finish the current command first";
  doc.openTransaction(name);
  try {
    change();
  } catch (const std::exception& e) {
    doc.abortTransaction();
    return e.what();
  }
  doc.commitTransaction();
  return {};
}

std::string Session::addNamedView(const NamedView& v) {
  auto err = plainEdit(*doc_, "New Named View", [&] { doc_->addNamedView(v); });
  if (err.empty()) notifyChanged();
  return err;
}

std::string Session::renameNamedView(const std::string& name, const std::string& newName) {
  auto err = plainEdit(*doc_, "Rename view", [&] { doc_->renameNamedView(name, newName); });
  if (err.empty()) notifyChanged();
  return err;
}

std::string Session::deleteNamedView(const std::string& name) {
  auto err = plainEdit(*doc_, "Delete view", [&] { doc_->removeNamedView(name); });
  if (err.empty()) notifyChanged();
  return err;
}

std::string Session::renameFeature(int featureId, const std::string& newName) {
  auto err = historyEdit(*doc_, commands_, "Rename feature", [&] { doc_->renameFeature(featureId, newName); });
  if (err.empty()) notifyChanged();
  return err;
}

std::string Session::setTimeline(const std::vector<int>& order, int marker) {
  // A reorder that would break a feature (moved before what it uses) is
  // refused, as the familiar timeline refuses the drop.
  std::map<int, std::string> errorsBefore;
  for (const auto& f : doc_->features()) errorsBefore[f.id] = f.error;
  std::string broken;
  auto err = historyEdit(*doc_, commands_, "Timeline", [&] {
    doc_->setTimeline(order, marker);
    doc_->recompute(commands_);
    for (const auto& f : doc_->features())
      if (!f.rolledBack && !f.error.empty() && errorsBefore[f.id].empty()) {
        broken = f.name + ": " + f.error;
        throw DocumentError("that order breaks " + broken);
      }
  });
  if (err.empty()) notifyChanged();
  return err;
}

std::string Session::computeAll() {
  if (doc_->hasOpenTransaction()) return "finish the current command first";
  doc_->openTransaction("Compute All");
  try {
    doc_->recompute(commands_, true);   // once, nothing reused
  } catch (const std::exception& e) {
    doc_->abortTransaction();
    return e.what();
  }
  doc_->commitTransaction();
  notifyChanged();
  return {};
}

std::string Session::rollHistory(int marker) {
  std::vector<int> order;
  for (const auto& f : doc_->features()) order.push_back(f.id);
  return setTimeline(order, marker);
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

std::string Session::setParameter(const std::string& name, const std::string& expression,
                                  const std::string& comment) {
  auto err = historyEdit(*doc_, commands_, "Change parameter",
                         [&] { doc_->setUserParameter(name, expression, comment); });
  if (err.empty()) notifyChanged();
  return err;
}

std::string Session::deleteParameter(const std::string& name) {
  auto err = historyEdit(*doc_, commands_, "Delete parameter", [&] { doc_->removeUserParameter(name); });
  if (err.empty()) notifyChanged();
  return err;
}

std::string Session::renameParameter(const std::string& name, const std::string& newName) {
  auto err = historyEdit(*doc_, commands_, "Rename parameter", [&] { doc_->renameParameter(name, newName); });
  if (err.empty()) notifyChanged();
  return err;
}

std::string Session::setParameterFavorite(const std::string& name, bool favorite) {
  auto err = plainEdit(*doc_, "Favorite", [&] { doc_->setParameterFavorite(name, favorite); });
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
