#include "tsr/core/CommandRegistry.h"

#include <stdexcept>

namespace tsr {

void CommandRegistry::add(std::unique_ptr<Command> cmd) {
  if (!cmd || cmd->def().id.empty()) throw std::invalid_argument("command without id");
  if (find(cmd->def().id)) throw std::invalid_argument("duplicate command id " + cmd->def().id);
  cmds_.push_back(std::move(cmd));
}

const Command* CommandRegistry::find(const std::string& id) const {
  for (const auto& c : cmds_)
    if (c->def().id == id) return c.get();
  return nullptr;
}

std::vector<const Command*> CommandRegistry::all() const {
  std::vector<const Command*> out;
  out.reserve(cmds_.size());
  for (const auto& c : cmds_) out.push_back(c.get());
  return out;
}

std::string CommandRegistry::run(const std::string& id, const Inputs& inputs, CommandContext& ctx) const {
  const Command* cmd = find(id);
  if (!cmd) return "unknown command '" + id + "'";
  CommandSession s(*cmd, ctx);
  for (const auto& [k, v] : inputs)
    if (auto err = s.setInput(k, v); !err.empty()) return err;
  return s.execute();
}

} // namespace tsr
