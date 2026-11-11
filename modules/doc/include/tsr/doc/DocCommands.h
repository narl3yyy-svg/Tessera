#pragma once
#include "tsr/core/CommandRegistry.h"

namespace tsr::doc {

// Command ids registered by tsr-doc.
inline constexpr const char* kCmdAddUserParameter = "tsr.parameters.addUser";
inline constexpr const char* kCmdBox = "tsr.primitive.box";
inline constexpr const char* kCmdSketch = "tsr.sketch.create";
inline constexpr const char* kCmdExtrude = "tsr.feature.extrude";
inline constexpr const char* kCmdRevolve = "tsr.feature.revolve";
inline constexpr const char* kCmdFillet = "tsr.feature.fillet";
inline constexpr const char* kCmdChamfer = "tsr.feature.chamfer";
inline constexpr const char* kCmdCylinder = "tsr.primitive.cylinder";
inline constexpr const char* kCmdSphere = "tsr.primitive.sphere";
inline constexpr const char* kCmdTorus = "tsr.primitive.torus";
inline constexpr const char* kCmdCone = "tsr.primitive.cone";

// Registers:
//   tsr.parameters.addUser   name, expression, unit, comment (strings)
//   tsr.primitive.*          sizes (Real, internal cm), x/y/z position, axis
//                            ("Z"/"Y"/"X", round primitives), operation
//                            ("New Body"/"Join"/"Cut"/"Intersect"), target (body name)
//   tsr.sketch.create        name (empty: Sketch<n>), plane ("XY"/"XZ"/"YZ"/custom:...),
//                            offset, data (sketch JSON, solved on apply)
//   tsr.feature.extrude      sketch (empty: latest), profiles ("x,y;..." inside
//                            the regions, empty: all), direction, distance,
//                            operation, target
//   tsr.feature.revolve      sketch, profiles, axis ("Sketch Y axis", "Sketch X axis",
//                            "Construction line", "X", "Y", "Z"), angle (rad),
//                            direction, operation, target
//   tsr.feature.fillet       body (empty: latest), edges ("x,y,z;..." points on
//                            the edges), radius
//   tsr.feature.chamfer      body, edges, distance
// All of these except the parameter command are timeline features.
void registerDocCommands(CommandRegistry& registry);

} // namespace tsr::doc
