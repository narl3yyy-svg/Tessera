#pragma once
#include "tsr/core/CommandRegistry.h"

namespace tsr::doc {

// Command ids registered by tsr-doc.
inline constexpr const char* kCmdAddUserParameter = "tsr.parameters.addUser";
inline constexpr const char* kCmdBox = "tsr.primitive.box";

// Registers the P0 commands:
//   tsr.parameters.addUser  inputs: name, expression, unit, comment (strings)
//   tsr.primitive.box       inputs: length, width, height (Real, internal cm)
void registerDocCommands(CommandRegistry& registry);

} // namespace tsr::doc
