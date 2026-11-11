#pragma once
#include "tsr/core/CommandRegistry.h"

namespace tsr::doc {

// Command ids registered by tsr-doc.
inline constexpr const char* kCmdAddUserParameter = "tsr.parameters.addUser";
inline constexpr const char* kCmdBox = "tsr.primitive.box";
inline constexpr const char* kCmdCylinder = "tsr.primitive.cylinder";
inline constexpr const char* kCmdSphere = "tsr.primitive.sphere";
inline constexpr const char* kCmdTorus = "tsr.primitive.torus";
inline constexpr const char* kCmdCone = "tsr.primitive.cone";

// Registers:
//   tsr.parameters.addUser   name, expression, unit, comment (strings)
//   tsr.primitive.*          sizes (Real, internal cm), x/y/z position, axis
//                            ("Z"/"Y"/"X", round primitives), operation
//                            ("New Body"/"Join"/"Cut"/"Intersect"), target (body name)
// The primitives are features: they are recorded in the timeline.
void registerDocCommands(CommandRegistry& registry);

} // namespace tsr::doc
