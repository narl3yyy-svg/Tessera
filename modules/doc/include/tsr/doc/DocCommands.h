#pragma once
#include <gp_Ax1.hxx>
#include "tsr/core/CommandRegistry.h"

#include <string>

namespace tsr::doc {

class Document;

// Command ids registered by tsr-doc.
inline constexpr const char* kCmdAddUserParameter = "tsr.parameters.addUser";
inline constexpr const char* kCmdBox = "tsr.primitive.box";
inline constexpr const char* kCmdSketch = "tsr.sketch.create";
inline constexpr const char* kCmdExtrude = "tsr.feature.extrude";
inline constexpr const char* kCmdRevolve = "tsr.feature.revolve";
inline constexpr const char* kCmdFillet = "tsr.feature.fillet";
inline constexpr const char* kCmdChamfer = "tsr.feature.chamfer";
inline constexpr const char* kCmdShell = "tsr.feature.shell";
inline constexpr const char* kCmdCombine = "tsr.feature.combine";
inline constexpr const char* kCmdSplitBody = "tsr.feature.splitBody";
inline constexpr const char* kCmdMove = "tsr.feature.move";
inline constexpr const char* kCmdMirror = "tsr.feature.mirror";
inline constexpr const char* kCmdScale = "tsr.feature.scale";
inline constexpr const char* kCmdRemove = "tsr.feature.remove";
inline constexpr const char* kCmdUnits = "tsr.document.units";
inline constexpr const char* kCmdInsert = "tsr.feature.insert";
inline constexpr const char* kCmdHole = "tsr.feature.hole";
inline constexpr const char* kCmdSweep = "tsr.feature.sweep";
inline constexpr const char* kCmdLoft = "tsr.feature.loft";
inline constexpr const char* kCmdPressPull = "tsr.feature.pressPull";
inline constexpr const char* kCmdPipe = "tsr.feature.pipe";
inline constexpr const char* kCmdNewComponent = "tsr.assemble.newComponent";
inline constexpr const char* kCmdJoint = "tsr.assemble.joint";
inline constexpr const char* kCmdAsBuiltJoint = "tsr.assemble.asBuiltJoint";
inline constexpr const char* kCmdThread = "tsr.feature.thread";
inline constexpr const char* kCmdOffsetFace = "tsr.feature.offsetFace";
inline constexpr const char* kCmdDraft = "tsr.feature.draft";
inline constexpr const char* kCmdDeleteFaces = "tsr.feature.deleteFaces";
inline constexpr const char* kCmdSplitFace = "tsr.feature.splitFace";
inline constexpr const char* kCmdCoil = "tsr.feature.coil";
inline constexpr const char* kCmdThicken = "tsr.feature.thicken";
inline constexpr const char* kCmdRib = "tsr.feature.rib";
inline constexpr const char* kCmdWeb = "tsr.feature.web";
inline constexpr const char* kCmdOffsetPlane = "tsr.construct.offsetPlane";
inline constexpr const char* kCmdPlaneAtAngle = "tsr.construct.planeAtAngle";
inline constexpr const char* kCmdMidplane = "tsr.construct.midplane";
inline constexpr const char* kCmdAxisCylinder = "tsr.construct.axisCylinder";
inline constexpr const char* kCmdAxisEdge = "tsr.construct.axisEdge";
inline constexpr const char* kCmdAxisTwoPoints = "tsr.construct.axisTwoPoints";
inline constexpr const char* kCmdAxisTwoPlanes = "tsr.construct.axisTwoPlanes";
inline constexpr const char* kCmdPointVertex = "tsr.construct.pointVertex";
inline constexpr const char* kCmdPointTwoEdges = "tsr.construct.pointTwoEdges";
inline constexpr const char* kCmdPointThreePlanes = "tsr.construct.pointThreePlanes";
inline constexpr const char* kCmdPointCenter = "tsr.construct.pointCenter";
inline constexpr const char* kCmdPointEdgePlane = "tsr.construct.pointEdgePlane";
inline constexpr const char* kCmdPlaneThreePoints = "tsr.construct.planeThreePoints";
inline constexpr const char* kCmdPlaneTangent = "tsr.construct.tangentPlane";
inline constexpr const char* kCmdPlaneTwoEdges = "tsr.construct.planeTwoEdges";
inline constexpr const char* kCmdPlaneFacePoint = "tsr.construct.planeFacePoint";
inline constexpr const char* kCmdAxisNormalAtPoint = "tsr.construct.axisNormalAtPoint";
inline constexpr const char* kCmdRectPattern = "tsr.feature.rectangularPattern";
inline constexpr const char* kCmdCircPattern = "tsr.feature.circularPattern";
inline constexpr const char* kCmdPathPattern = "tsr.feature.pathPattern";
inline constexpr const char* kCmdCylinder = "tsr.primitive.cylinder";
inline constexpr const char* kCmdSphere = "tsr.primitive.sphere";

// The world axis Revolve turns about, from its inputs (sketch, axis choice,
// construction axis). Throws CommandError when it cannot be found.
gp_Ax1 revolveAxis(const Document& doc, const std::string& sketch, const std::string& axis,
                   const std::string& constructionAxis);
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
//   tsr.feature.shell        body, faces (open faces; empty: closed hollow), thickness, direction
//   tsr.feature.combine      target, tools ("Body2;Body3"), operation, keep (tools)
//   tsr.feature.splitBody    body, plane ("XY"/"XZ"/"YZ"), offset
//   tsr.feature.move         body, x/y/z, axis, angle (rad), copy
//   tsr.feature.mirror       body, plane, offset, operation ("New Body"/"Join")
//   tsr.feature.scale        body, factor, about ("Body centre"/"Origin")
//   tsr.feature.remove       body
//   tsr.feature.offsetFace   body, faces, distance
//   tsr.feature.draft        body, faces, plane (pull direction = its normal; neutral plane), angle, flip
//   tsr.feature.thread       body, faces (one cylinder), pitch (0: ISO coarse), fullLength, length, offset,
//                            hand ("Right"/"Left")
//   tsr.assemble.newComponent  name, bodies ("Body1;Body2")
//   tsr.assemble.joint       origin1, origin2 (JointOrigin), type ("Rigid"/"Revolute"/"Slider"/"Cylindrical"),
//                            angle, offset, flip, rotation (motion, rad), slide (motion, cm)
//   tsr.feature.pipe         path (sketch), section, size, hollow ("No"/"Yes"), thickness, operation
//   tsr.feature.coil         plane, x, y, diameter, type, revolutions, height, pitch, angle,
//                            section, position, size, operation
//   tsr.construct.axis*      name; body + faces (cylinder/cone/torus) | edges | vertices (2) | plane + plane2
//   tsr.construct.point*     name; body + vertices | edges (2) | plane, plane2, plane3 |
//                            edges or faces (circle / sphere centre) | edges + plane
// All of these except the parameter command are timeline features.
// Every Real/Integer input also takes an expression string ("width / 2");
// see tsr::expressionKey and Document::recompute.
void registerDocCommands(CommandRegistry& registry);

} // namespace tsr::doc
