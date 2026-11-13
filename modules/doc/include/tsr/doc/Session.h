#pragma once
#include "tsr/core/CommandRegistry.h"
#include "tsr/doc/Document.h"

#include <filesystem>
#include <functional>
#include <map>
#include <memory>
#include <optional>

namespace tsr::doc {

// The running application minus the UI: command registry + active document.
// The Qt shell, the Python API and headless tests all drive this one object,
// and listeners let the UI refresh when a script changes the document.
class Session {
public:
  Session();

  CommandRegistry& commands() { return commands_; }
  const CommandRegistry& commands() const { return commands_; }
  Document& document() { return *doc_; }

  void newDocument();
  void open(const std::filesystem::path& path);   // throws DocumentError
  void save(const std::filesystem::path& path);   // throws DocumentError
  const std::optional<std::filesystem::path>& path() const { return path_; }

  // Run a command start to finish. Returns empty on success, else the error.
  std::string run(const std::string& commandId, const Inputs& inputs = {});

  // Start an interactive run (dialog). Returns nullptr for an unknown id.
  // The caller calls notifyChanged() after preview/execute/cancel.
  std::unique_ptr<CommandSession> begin(const std::string& commandId);

  // Editing the design history. editFeature() starts an interactive edit of a
  // feature's inputs (the dialog's preview/OK/cancel drive it like a new
  // command); OK replaces the inputs and replays the timeline as one undo step.
  std::unique_ptr<CommandSession> editFeature(int featureId);
  std::string editFeature(int featureId, const Inputs& changes);   // non-interactive
  std::string deleteFeature(int featureId);
  // Timeline: feature order (ids) and the history marker (features before it
  // are replayed). Refused if a feature would break. rollHistory keeps the order.
  std::string setTimeline(const std::vector<int>& order, int marker);
  std::string rollHistory(int marker);
  // Renames (one undo step each); empty on success, else why not.
  std::string renameBody(const std::string& name, const std::string& newName);
  std::string renameSketch(const std::string& name, const std::string& newName);
  std::string renameFeature(int featureId, const std::string& newName);
  std::string setFeatureSuppressed(int featureId, bool suppressed);

  // User parameters (Change Parameters). Each call is one undo step that
  // re-evaluates the parameters and replays the timeline.
  std::string setParameter(const std::string& name, const std::string& expression, const std::string& comment);
  std::string deleteParameter(const std::string& name);
  // Any parameter, user or model (d1 ... or a feature's value); expressions follow.
  std::string renameParameter(const std::string& name, const std::string& newName);
  std::string setParameterFavorite(const std::string& name, bool favorite);

  // Named views: one undo step each, no replay (a view is not history).
  std::string addNamedView(const NamedView& v);
  std::string renameNamedView(const std::string& name, const std::string& newName);
  std::string deleteNamedView(const std::string& name);

  bool undo();
  bool redo();

  using Listener = std::function<void()>;
  int addListener(Listener l);
  void removeListener(int id);
  void notifyChanged();

private:
  CommandRegistry commands_;
  std::unique_ptr<Document> doc_;
  std::optional<std::filesystem::path> path_;
  std::map<int, Listener> listeners_;
  int nextListener_ = 1;
};

} // namespace tsr::doc
