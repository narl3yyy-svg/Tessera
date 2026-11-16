# Graph Report - tessera  (2026-11-16)

## Corpus Check
- 388 files · ~257,649 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 57 file(s) not represented in the graph (top: .drive 49, (none) 5, .cmake 1)

## Summary
- 3722 nodes · 9548 edges · 136 communities (107 shown, 29 thin omitted)
- Extraction: 85% EXTRACTED · 15% INFERRED · 0% AMBIGUOUS · INFERRED: 1467 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `eb7c9789`
- Run `git rev-parse HEAD` and compare to check if the graph is stale.
- Run `graphify update .` after code changes (no API cost).

## Community Hubs (Navigation)
- Viewport
- Icons.cpp
- Session.cpp
- MainWindow
- run_oracle.py
- Viewport.h
- Document
- Viewport.cpp
- SketchEditor
- sketchFor
- optional
- Kernel.cpp
- AnalysisSettings
- Kind
- MainWindowArrow.cpp
- CommandDialog
- Io.cpp
- Unit
- .setTool
- Document
- MainWindow.cpp
- MainWindowTools.cpp
- Affine
- ViewportSketch.cpp
- SketchPalette
- .mouseMove
- Inputs
- NewComponent
- Colors
- KernelError
- SketchOps.cpp
- ViewportArrow.cpp
- ParameterCompleter
- Constraint
- DocCommands.cpp
- src/main.cpp
- solve
- Snap
- CommandDialog.cpp
- ConstraintType
- TsrModule.cpp
- Pick
- SketchEditor.cpp
- Handle
- Zip.cpp
- AnalysisSettings
- Sketch.cpp
- Document.cpp
- MainWindowSketch.cpp
- InputDef
- string
- .toPixels
- UserParameter
- Document::recompute
- MarkingMenu.cpp
- TsrModule.cpp
- Entity
- xdrive.py
- Session
- Theme.cpp
- BodyFrame
- CommandRegistry
- Rect
- BodyFrame
- Theme
- PlaneEdges
- Command.cpp
- ParametersDialog.cpp
- Axis
- curve
- Kind
- InputType
- Vec3
- Dimension
- math
- QString
- SketchDisplay
- Command
- Measurement
- SketchCurves.cpp
- Level
- README.md
- string
- test_feature_pattern.py
- rect
- BooleanOp
- TEST
- FileFormat
- Known differences still to build
- TEST
- ReplayStep
- ThreadInfo
- ChamferType
- FakeDoc
- ParamSet
- includeEdges
- .add
- sstream
- test_text_box_path.py
- BoundingBox
- Joints
- SectionState
- Display
- cli_main.cpp
- smoke
- TopologyCounts
- Session::addListener
- NavPreset
- Placement::apply
- uninstall.sh
- install.sh
- TestFramework.h
- .rebuild
- MarkingMenu
- CommandSession
- test_incremental_replay.py
- Placement
- ChainSegment
- Icons.h
- .updatePreview
- Joint
- fail
- Value.h
- LAB_NOTES.md
- build.sh
- live-test.sh
- PYBIND11_EMBEDDED_MODULE
- Point
- SplineHandle

## God Nodes (most connected - your core abstractions)
1. `Viewport` - 257 edges
2. `SketchEditor` - 185 edges
3. `MainWindow` - 184 edges
4. `Inputs` - 152 edges
5. `Document` - 120 edges
6. `render()` - 119 edges
7. `CommandContext` - 111 edges
8. `CommandDialog` - 90 edges
9. `Command` - 66 edges
10. `CommandError` - 61 edges

## Surprising Connections (you probably didn't know these)
- `How a command works` --references--> `CommandDef`  [INFERRED]
  docs/ARCHITECTURE.md → modules/core/include/tsr/core/Command.h
- `Tests` --references--> `unit()`  [INFERRED]
  docs/DEVELOPMENT.md → modules/sketch/src/SketchOps.cpp
- `Known gaps` --references--> `QTabWidget`  [INFERRED]
  docs/KNOWN_GAPS.md → modules/app/src/MainWindow.h
- `Architecture` --references--> `InputDef`  [INFERRED]
  docs/ARCHITECTURE.md → modules/core/include/tsr/core/Command.h
- `Architecture` --references--> `CommandDef`  [INFERRED]
  docs/ARCHITECTURE.md → modules/core/include/tsr/core/Command.h

## Import Cycles
- None detected.

## Communities (136 total, 29 thin omitted)

### Community 0 - "Viewport"
Cohesion: 0.02
Nodes (69): view_, QLineEdit, Viewport, analysis_, analysisObjects_, appliedGridStep_, arrowBoxes_, arrowDragging_ (+61 more)

### Community 1 - "Icons.cpp"
Cohesion: 0.05
Nodes (124): accessibilityIcon(), appearanceIcon(), arc3Icon(), arcIcon(), arcTangentIcon(), arrow(), axisIcon(), box() (+116 more)

### Community 2 - "Session.cpp"
Cohesion: 0.16
Nodes (27): historyEdit(), plainEdit(), Session::addNamedView(), Session::begin(), Session::computeAll(), Session::deleteFeature(), Session::deleteNamedView(), Session::deleteParameter() (+19 more)

### Community 4 - "MainWindow"
Cohesion: 0.03
Nodes (65): CommandDialog, MainWindow, active_, arrowInput_, arrowInput2_, bodiesBeforeCommand_, combEdges_, combPicking_ (+57 more)

### Community 5 - "run_oracle.py"
Cohesion: 0.08
Nodes (54): add_point(), arc_poly(), body_at(), body_list(), build_sketch(), chain(), circumcentre(), cm() (+46 more)

### Community 6 - "Viewport.h"
Cohesion: 0.09
Nodes (5): MarkingMenu::mouseMoveEvent(), QKeyEvent, QLabel, QMouseEvent, ViewInteractor

### Community 7 - "Document"
Cohesion: 0.03
Nodes (17): Document, effects_, lastReplayed_, lastReused_, modified_, pendingTools_, registry_, replaying_ (+9 more)

### Community 8 - "Viewport.cpp"
Cohesion: 0.05
Nodes (5): glide(), keys(), Viewport::clearDragArrow(), Viewport::clearSecondArrow(), Viewport::setInteractor()

### Community 9 - "SketchEditor"
Cohesion: 0.03
Nodes (50): HandleHit, back, index, spline, SketchEditor, arcDrag_, arcDragMoved_, arcEndsChain_ (+42 more)

### Community 10 - "sketchFor"
Cohesion: 0.13
Nodes (11): Extrude, def_, Pipe, def_, Primitive, build_, def_, Revolve (+3 more)

### Community 13 - "AnalysisSettings"
Cohesion: 0.11
Nodes (18): AnalysisKind, Accessibility, CurvatureMap, Draft, Isocurve, MinimumRadius, None, Zebra (+10 more)

### Community 14 - "Kind"
Cohesion: 0.06
Nodes (32): ConstructPlane, def_, kind_, EdgeFeature, def_, kind_, FaceFeature, def_ (+24 more)

### Community 15 - "MainWindowArrow.cpp"
Cohesion: 0.09
Nodes (15): ArrowPlacement, base, dir, edgePlacement(), facesPlacement(), MainWindow::attachArrowCompleters(), MainWindow::patternCentre(), MainWindow::pickedFaces() (+7 more)

### Community 16 - "CommandDialog"
Cohesion: 0.05
Nodes (31): CommandDialog, bodiesId_, bodiesLabel_, bodyInput_, buttons_, cmd_, conditional_, edgesId_ (+23 more)

### Community 17 - "Io.cpp"
Cohesion: 0.09
Nodes (19): MainWindow::print3d(), NamedShape, compoundOf(), exportShapes(), fmt(), formatForPath(), fromBrep(), importShape() (+11 more)

### Community 18 - "Unit"
Cohesion: 0.07
Nodes (45): MainWindow::lengthUnit(), ExpressionEnv, lengthUnit, lookup, ExpressionError, Quantity, angle, length (+37 more)

### Community 19 - ".setTool"
Cohesion: 0.16
Nodes (6): SketchEditor::SketchEditor(), edges, Tool, op, shape, target

### Community 21 - "Document"
Cohesion: 0.23
Nodes (5): bodyCentre(), ConstructAxisPoint, def_, kind_, storeBodies()

### Community 22 - "MainWindow.cpp"
Cohesion: 0.04
Nodes (10): PythonHost, commandIcon(), MainWindow::MainWindow(), qs(), MainWindow::beginSketch(), MainWindow::buildSketchTab(), MainWindow::enterSketchMode(), MainWindow::exitSketchMode() (+2 more)

### Community 23 - "MainWindowTools.cpp"
Cohesion: 0.06
Nodes (29): QDialog, MainWindow::checkInterference(), MainWindow::chooseUnits(), MainWindow::driveJoints(), MainWindow::editAppearance(), MainWindow::editMaterial(), MainWindow::exportDesign(), MainWindow::formatLength() (+21 more)

### Community 24 - "Affine"
Cohesion: 0.14
Nodes (13): Affine, a, b, d, e, Builder, byPlace_, k_ (+5 more)

### Community 25 - "ViewportSketch.cpp"
Cohesion: 0.05
Nodes (12): packed(), ramp(), shade(), Viewport::buildAnalysis(), Viewport::setCurvatureComb(), faceStyle(), lineStyle(), rgb() (+4 more)

### Community 26 - "SketchPalette"
Cohesion: 0.06
Nodes (26): flatButton(), QCheckBox, QLabel, QToolButton, QWidget, SketchEditor, SketchPalette, body_ (+18 more)

### Community 27 - ".mouseMove"
Cohesion: 0.18
Nodes (6): ext(), fixedColor(), freeColor(), qc(), rgb(), wire()

### Community 28 - "Inputs"
Cohesion: 0.09
Nodes (16): CommandContext, CommandError, Inputs, CommandSession::CommandSession(), getBool(), getInt(), getReal(), applyOperation() (+8 more)

### Community 29 - "NewComponent"
Cohesion: 0.14
Nodes (7): AddUserParameter, def_, isIdentifier(), NewComponent, def_, RigidGroup, def_

### Community 30 - "Colors"
Cohesion: 0.07
Nodes (28): Colors, base, border, cubeBox, cubeText, errorBackground, grid, gridMajor (+20 more)

### Community 31 - "KernelError"
Cohesion: 0.25
Nodes (29): KernelError, asSolid(), boolean(), chamfer(), chamferEx(), deleteFaces(), draft(), extrude() (+21 more)

### Community 32 - "SketchOps.cpp"
Cohesion: 0.23
Nodes (26): at(), chainOf(), chamferCorner(), circularPattern(), copyEntities(), cornerAt(), cross(), dot() (+18 more)

### Community 33 - "ViewportArrow.cpp"
Cohesion: 0.06
Nodes (19): QTimer, Viewport::frontEdgeOwner(), rgb(), segmentDistance(), Viewport::arrowAt(), Viewport::arrowMouseMove(), Viewport::arrowMousePress(), Viewport::arrowMouseRelease() (+11 more)

### Community 34 - "ParameterCompleter"
Cohesion: 0.13
Nodes (9): QObject, ParameterCompleter, completer_, edit_, names_, ParameterCompleter::ParameterCompleter(), public, QCompleter (+1 more)

### Community 35 - "Constraint"
Cohesion: 0.09
Nodes (20): Constraint, driven, entities, expression, hasLabel, labelX, labelY, name (+12 more)

### Community 36 - "DocCommands.cpp"
Cohesion: 0.10
Nodes (30): axisOf(), CopyFn, differenceOrNull(), evaluateDimensions(), HoleSize, modeled, pitch, radius (+22 more)

### Community 38 - "solve"
Cohesion: 0.18
Nodes (13): set, addConstraintChecked(), Layout, n, px, py, rad, makeLayout() (+5 more)

### Community 39 - "Snap"
Cohesion: 0.11
Nodes (18): Snap, alignX, alignY, bodyArc, bodySegment, entity, fromX, fromY (+10 more)

### Community 41 - "ConstraintType"
Cohesion: 0.08
Nodes (24): ConstraintType, Angle, Coincident, Collinear, Concentric, Diameter, Distance, Equal (+16 more)

### Community 42 - "TsrModule.cpp"
Cohesion: 0.09
Nodes (16): Application, bindAdsk(), BRepBodies, BRepBody, index, Component, Design, Product (+8 more)

### Community 43 - "Pick"
Cohesion: 0.12
Nodes (14): Pick, bodyArc, bodyPoint, bodySegment, hit, midpointOf, onEntity, onXAxis (+6 more)

### Community 44 - "SketchEditor.cpp"
Cohesion: 0.11
Nodes (5): angleInArc(), ccwContains(), circumcircle(), lineEntity(), segDistance()

### Community 46 - "Zip.cpp"
Cohesion: 0.20
Nodes (13): Entry, data, name, ZipError, crc32(), deflateRaw(), get16(), get32() (+5 more)

### Community 47 - "AnalysisSettings"
Cohesion: 0.10
Nodes (16): DragArrow, base, dir, radius, ref, ring, value, PendingLook (+8 more)

### Community 48 - "Sketch.cpp"
Cohesion: 0.07
Nodes (22): SketchError, SplineKind, Conic, Control, Fit, entityTypeName(), isDimension(), Sketch::addConic() (+14 more)

### Community 49 - "Document.cpp"
Cohesion: 0.06
Nodes (42): ConstructionPlane, name, spec, SketchRecord, data, name, offset, plane (+34 more)

### Community 50 - "MainWindowSketch.cpp"
Cohesion: 0.06
Nodes (17): MainWindow::cancelSketch(), MainWindow::editSketch(), MainWindow::finishSketch(), MainWindow::onProfileClicked(), MainWindow::originalShape(), MainWindow::sketchPalette(), MainWindow::sketchVisible(), MainWindow::startSketch() (+9 more)

### Community 51 - "InputDef"
Cohesion: 0.09
Nodes (21): InputDef, choices, defaultValue, id, label, max, min, minExclusive (+13 more)

### Community 52 - "string"
Cohesion: 0.08
Nodes (24): checkBody(), checkPattern(), CircularPattern, def_, Hole, def_, jointOrigin(), JointPick (+16 more)

### Community 53 - ".toPixels"
Cohesion: 0.08
Nodes (3): toVKeys(), Viewport::environmentNames(), Viewport::Viewport()

### Community 54 - "UserParameter"
Cohesion: 0.33
Nodes (6): UserParameter, comment, expression, name, unit, value

### Community 55 - "Document::recompute"
Cohesion: 0.17
Nodes (8): Document::expressionEnv(), Document::recompute(), Document::recordFeature(), Document::removeFeature(), Document::setFeatureInputs(), Document::setFeatureSuppressed(), featureData(), toJson()

### Community 56 - "MarkingMenu.cpp"
Cohesion: 0.07
Nodes (22): UiCommand, enabled, icon, id, name, panel, run, shortcut (+14 more)

### Community 57 - "TsrModule.cpp"
Cohesion: 0.29
Nodes (4): bindTsr(), fromPy(), toPy(), typeName()

### Community 58 - "Entity"
Cohesion: 0.10
Nodes (12): Entity, a, b, center, construction, fit, handles, included (+4 more)

### Community 59 - "xdrive.py"
Cohesion: 0.28
Nodes (15): button(), canvas(), click(), drag(), flush(), geometry(), key(), keycode() (+7 more)

### Community 62 - "Session"
Cohesion: 0.05
Nodes (11): PythonHost::PythonHost(), main(), Session, commands_, doc_, listeners_, nextListener_, path_ (+3 more)

### Community 63 - "Theme.cpp"
Cohesion: 0.19
Nodes (6): setIconTheme(), darkColors(), darkPalette(), darkStyleSheet(), lightColors(), lightStyleSheet()

### Community 64 - "BodyFrame"
Cohesion: 0.09
Nodes (31): completeEdgeReferences(), completeFaceReferences(), decode(), decodeFaces(), dot(), edgeReference(), EdgeSig, full (+23 more)

### Community 65 - "CommandRegistry"
Cohesion: 0.09
Nodes (8): Architecture, How a command works, The document, Units, CommandRegistry, cmds_, CommandRegistry::add(), TEST()

### Community 66 - "Rect"
Cohesion: 0.50
Nodes (4): Session::notifyChanged(), Rect, l, p

### Community 67 - "BodyFrame"
Cohesion: 0.14
Nodes (15): BodyFrame, diag, dx, dy, dz, x0, y0, z0 (+7 more)

### Community 68 - "Theme"
Cohesion: 0.22
Nodes (4): Theme, colors_, public, styled_

### Community 69 - "PlaneEdges"
Cohesion: 0.20
Nodes (5): PlaneEdges, arcs, curves, segments, vertices

### Community 70 - "Command.cpp"
Cohesion: 0.22
Nodes (11): expressionKey(), checkInputValue(), CommandContext::evaluateExpression(), CommandDef::input(), CommandSession::applyInTransaction(), CommandSession::cancel(), CommandSession::execute(), CommandSession::preview() (+3 more)

### Community 71 - "ParametersDialog.cpp"
Cohesion: 0.06
Nodes (24): Column, kComment, kExpression, kName, kParameter, kStar, kUnit, kValue (+16 more)

### Community 72 - "Axis"
Cohesion: 0.50
Nodes (4): Axis, X, Y, Z

### Community 73 - "curve"
Cohesion: 0.31
Nodes (10): curve(), curves(), entityCurves(), interiorPoint(), profileAt(), profiles(), splineHandles(), textShape() (+2 more)

### Community 74 - "Kind"
Cohesion: 0.08
Nodes (24): Hit, index, kind, HudField, edit, editing, kind, locked (+16 more)

### Community 75 - "InputType"
Cohesion: 0.12
Nodes (17): InputType, Axis, Bodies, Body, Bool, Choice, Edges, Faces (+9 more)

### Community 76 - "Vec3"
Cohesion: 0.18
Nodes (20): SurfacePoint, normal, point, Vec3, boundingBox(), edgeMidpoint(), edgesNear(), frame() (+12 more)

### Community 77 - "Dimension"
Cohesion: 0.50
Nodes (4): Dimension, Angle, Length, Unitless

### Community 79 - "QString"
Cohesion: 0.11
Nodes (6): ExpressionSpinBox, eval_, expression_, shown_, formatNumber(), dimensionOf()

### Community 80 - "SketchDisplay"
Cohesion: 0.09
Nodes (16): ProfileObject, index, sketch, SketchDisplay, construction, curves, fixedCurves, frame (+8 more)

### Community 81 - "Command"
Cohesion: 0.04
Nodes (42): Adding a tool, Command, CommandDef, feature, icon, id, inputs, name (+34 more)

### Community 82 - "Measurement"
Cohesion: 0.13
Nodes (14): Kind, Angle, Area, Length, Volume, Measurement, from, hasLine (+6 more)

### Community 83 - "SketchCurves.cpp"
Cohesion: 0.15
Nodes (17): crossings(), crossingsOf(), Curve2d, curve2d(), periodic, t0, t1, endIsFree() (+9 more)

### Community 85 - "Level"
Cohesion: 0.12
Nodes (13): debug(), error(), info(), Level, Debug, Error, Info, Warning (+5 more)

### Community 86 - "README.md"
Cohesion: 0.08
Nodes (20): Build, Conventions, Development, Tests, Include 3D Geometry, Known gaps, Sketch text, Splines and conics (+12 more)

### Community 87 - "string"
Cohesion: 0.08
Nodes (43): DocumentError, PhysicalMaterial, color, density, name, bodyNumber(), checkViewName(), Document::abortTransaction() (+35 more)

### Community 89 - "rect"
Cohesion: 0.14
Nodes (4): SelectionBox, crossing, height, rect()

### Community 90 - "BooleanOp"
Cohesion: 0.50
Nodes (4): BooleanOp, Cut, Intersect, Join

### Community 92 - "FileFormat"
Cohesion: 0.17
Nodes (12): FileFormat, Brep, Iges, Obj, Step, Stl, ThreeMF, FormatInfo (+4 more)

### Community 93 - "Known differences still to build"
Cohesion: 0.15
Nodes (12): Data and files, Findings from the videos, Fusion study list, Interface, Known differences still to build, Navigation and display, Selection and the canvas, Sketch (+4 more)

### Community 94 - "TEST"
Cohesion: 0.20
Nodes (3): slurp(), TEST(), tmp()

### Community 95 - "ReplayStep"
Cohesion: 0.04
Nodes (46): Body, color, display, material, name, shape, Component, bodies (+38 more)

### Community 96 - "ThreadInfo"
Cohesion: 0.50
Nodes (4): ThreadInfo, diameter, internal, pitch

### Community 97 - "ChamferType"
Cohesion: 0.67
Nodes (3): ChamferType, DistanceAngle, TwoDistances

### Community 98 - "FakeDoc"
Cohesion: 0.17
Nodes (6): FakeDoc, aborts, commits, items, open, snapshot

### Community 99 - "ParamSet"
Cohesion: 0.09
Nodes (29): ModelParameter, angle, expression, input, label, name, owner, unit (+21 more)

### Community 102 - "sstream"
Cohesion: 0.17
Nodes (5): doc_(), Document::Document(), Document::ocafBytes(), ocafApplication(), Document::load()

### Community 104 - "BoundingBox"
Cohesion: 0.16
Nodes (18): BoundingBox, max, min, WallSide, Center, Side1, Side2, extendedWire() (+10 more)

### Community 106 - "SectionState"
Cohesion: 0.25
Nodes (7): SectionState, active, angle, flip, offset, plane, visible

### Community 107 - "Display"
Cohesion: 0.25
Nodes (7): Display, constraints, construction, dimensions, points, profiles, projected

### Community 108 - "cli_main.cpp"
Cohesion: 0.60
Nodes (3): listCommands(), main(), usage()

### Community 109 - "smoke"
Cohesion: 0.33
Nodes (6): smoke(), key, MassProperties, area, centerOfMass, volume

### Community 110 - "TopologyCounts"
Cohesion: 0.17
Nodes (15): Section, Circular, Square, Triangular, TopologyCounts, edges, faces, shells (+7 more)

### Community 112 - "NavPreset"
Cohesion: 0.40
Nodes (4): NavPreset, Fusion, SolidWorks, Tinkercad

### Community 114 - "uninstall.sh"
Cohesion: 0.52
Nodes (6): die(), manifest_for(), refresh(), uninstall.sh script, step(), usage()

### Community 115 - "install.sh"
Cohesion: 0.60
Nodes (5): die(), refresh(), install.sh script, step(), usage()

### Community 116 - "TestFramework.h"
Cohesion: 0.14
Nodes (11): Result, error, ok, output, captured(), PythonHost::exec(), PythonHost::runScript(), Case (+3 more)

### Community 117 - ".rebuild"
Cohesion: 0.10
Nodes (12): hiddenColour(), qc(), rgb(), sharpEdges(), Style, Shaded, ShadedEdges, ShadedHidden (+4 more)

### Community 118 - "MarkingMenu"
Cohesion: 0.40
Nodes (3): MarkingMenu, enabled, public

### Community 120 - "CommandSession"
Cohesion: 0.12
Nodes (8): CommandSession, inputs_, CommandRegistry::all(), CommandRegistry::find(), CommandRegistry::run(), OwnedCommand, owned, OwningCommandSession

### Community 123 - "Placement"
Cohesion: 0.25
Nodes (7): Placement, angle, cx, cy, dx, dy, scale

### Community 124 - "ChainSegment"
Cohesion: 0.67
Nodes (3): ChainSegment, entity, forward

### Community 128 - ".updatePreview"
Cohesion: 0.08
Nodes (17): Sketch, constraints, entities, points, texts, Text, angle, corner (+9 more)

### Community 129 - "Joint"
Cohesion: 0.21
Nodes (5): Joint, asBuilt_, def_, Sweep, def_

### Community 141 - "Point"
Cohesion: 0.52
Nodes (6): Point, x, y, z, customPlaneSpec(), toDxf()

### Community 142 - "SplineHandle"
Cohesion: 0.29
Nodes (7): SplineHandle, arm, index, tx, ty, x, y

## Knowledge Gaps
- **776 isolated node(s):** `ok`, `output`, `error`, `isReal`, `real` (+771 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 1444 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **29 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `optional` connect `optional` to `Viewport`, `MainWindow`, `Viewport.h`, `sketchFor`, `Kernel.cpp`, `MainWindowArrow.cpp`, `Io.cpp`, `Unit`, `ViewportSketch.cpp`, `SketchOps.cpp`, `ViewportArrow.cpp`, `Constraint`, `DocCommands.cpp`, `CommandDialog.cpp`, `SketchEditor.cpp`, `AnalysisSettings`, `Document.cpp`, `InputDef`, `Entity`, `Session`, `Vec3`, `QString`, `SketchCurves.cpp`, `string`, `ReplayStep`?**
  _High betweenness centrality (0.108) - this node is a cross-community bridge._
- **What connects `ok`, `output`, `error` to the rest of the system?**
  _776 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Viewport` be split into smaller, more focused modules?**
  _Cohesion score 0.0159809183064997 - nodes in this community are weakly interconnected._
- **Why does `Viewport` connect `Viewport` to `ViewportArrow.cpp`, `MainWindow`, `Viewport.h`, `Viewport.cpp`, `optional`, `AnalysisSettings`, `Handle`, `AnalysisSettings`, `SketchDisplay`, `NavPreset`, `SketchCurves.cpp`, `.rebuild`, `.toPixels`, `MainWindowTools.cpp`, `rect`, `ViewportSketch.cpp`?**
  _High betweenness centrality (0.098) - this node is a cross-community bridge._
- **Should `Icons.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.05337690631808279 - nodes in this community are weakly interconnected._
- **Why does `SketchEditor` connect `SketchEditor` to `Viewport`, `ParameterCompleter`, `Constraint`, `PlaneEdges`, `Viewport.h`, `Snap`, `Kind`, `Display`, `optional`, `Pick`, `SketchEditor.cpp`, `Unit`, `.setTool`, `.solveAndShow`, `Entity`, `.mouseMove`, `Session`?**
  _High betweenness centrality (0.085) - this node is a cross-community bridge._
- **Should `tsr` be split into smaller, more focused modules?**
  _Cohesion score 0.05388471177944862 - nodes in this community are weakly interconnected._