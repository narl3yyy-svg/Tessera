#include "tsr/doc/Session.h"
#include "tsr/doc/DocCommands.h"

namespace tsr::doc {

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
