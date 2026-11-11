#pragma once
#include "tsr/core/Command.h"

#include <memory>
#include <string>
#include <vector>

namespace tsr {

// Ordered registry of command implementations. Registration order is the
// order commands appear within their ribbon panel.
class CommandRegistry {
public:
  // Throws std::invalid_argument on a duplicate or empty id.
  void add(std::unique_ptr<Command> cmd);
  const Command* find(const std::string& id) const;
  std::vector<const Command*> all() const;

  // Runs a command start-to-finish with the given inputs (defaults fill the
  // rest). Returns empty on success, else the error. This is the single path
  // the API and scripted tests use.
  std::string run(const std::string& id, const Inputs& inputs, CommandContext& ctx) const;

private:
  std::vector<std::unique_ptr<Command>> cmds_;
};

} // namespace tsr
