# Graph Report - tessera  (2026-11-13)

## Corpus Check
- 386 files · ~254,930 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 56 file(s) not represented in the graph (top: .drive 48, (none) 5, .cmake 1)

## Summary
- 3709 nodes · 9505 edges · 144 communities (114 shown, 30 thin omitted)
- Extraction: 85% EXTRACTED · 15% INFERRED · 0% AMBIGUOUS · INFERRED: 1461 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `ce2fcd90`
- Run `git rev-parse HEAD` and compare to check if the graph is stale.
- Run `graphify update .` after code changes (no API cost).

## Community Hubs (Navigation)
- Viewport
- Icons.cpp
- Session.cpp
- tsr
- MainWindow
- run_oracle.py
- Unit
- Document
- Viewport.cpp
- SketchEditor
- CommandError
- optional
- Kernel.cpp
- AnalysisSettings
- Kind
- .showDialog
- CommandDialog
- Io.cpp
- Unit
- MainWindowTools.cpp
- Known gaps
- Document
- MainWindow.cpp
- Architecture
- Affine
- ViewportSketch.cpp
- SketchPalette
- .redrawAll
- Inputs
- DocumentError
- Colors
- KernelError
- SketchOps.cpp
- ViewportArrow.cpp
- ParameterCompleter
- Constraint
- DocCommands.cpp
- MainWindow::buildUiCommands
- solve
- Snap
- CommandDialog.cpp
- ConstraintType
- TsrModule.cpp
- Pick
- SketchEditor.cpp
- TEST
- Zip.cpp
- AnalysisSettings
- Sketch.cpp
- ParamSet
- MainWindowSketch.cpp
- InputDef
- HoleSize
- .toPixels
- ViewportAnalysis.cpp
- Document::recompute
- MarkingMenu.cpp
- Profile
- Entity
- xdrive.py
- Session
- Theme.cpp
- BodyFrame
- CommandRegistry
- Sweep
- BodyFrame
- Theme
- PlaneEdges
- Command.cpp
- ParametersDialog.cpp
- TEST
- curve
- Kind
- InputType
- Vec3
- Dimension
- QString
- SketchDisplay
- Command
- Measurement
- SketchCurves.cpp
- UiCommand
- Level
- README.md
- Document.cpp
- test_feature_pattern.py
- rect
- MainWindow::MainWindow
- FileFormat
- Known differences still to build
- TEST
- ReplayStep
- NamedView
- FakeDoc
- fail
- Expression.cpp
- .add
- sstream
- CommandSession
- BoundingBox
- Joints
- SectionState
- Display
- main
- smoke
- TopologyCounts
- QTimer
- Feature
- cachedProfiles
- uninstall.sh
- install.sh
- TestFramework.h
- .rebuild
- bindTsr
- Viewport::setDragArrow
- bindAdsk
- test_incremental_replay.py
- Placement
- ChainSegment
- AddUserParameter
- Icons.h
- ExpressionEnv
- .updatePreview
- Joint
- UserParameter
- Value.h
- Curve2d
- LAB_NOTES.md
- Axis
- BooleanOp
- build.sh
- live-test.sh
- ThreadInfo
- PYBIND11_EMBEDDED_MODULE
- Point
- SplineHandle
- ChamferType

## God Nodes (most connected - your core abstractions)
1. `Viewport` - 255 edges
2. `SketchEditor` - 185 edges
3. `MainWindow` - 184 edges
4. `Inputs` - 149 edges
5. `Document` - 120 edges
6. `render()` - 119 edges
7. `CommandContext` - 108 edges
8. `CommandDialog` - 90 edges
9. `Command` - 65 edges
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

## Communities (144 total, 30 thin omitted)

### Community 0 - "Viewport"
Cohesion: 0.02
Nodes (68): view_, QLineEdit, Viewport, analysis_, analysisObjects_, appliedGridStep_, arrowBoxes_, arrowDragging_ (+60 more)

### Community 1 - "Icons.cpp"
Cohesion: 0.05
Nodes (124): accessibilityIcon(), appearanceIcon(), arc3Icon(), arcIcon(), arcTangentIcon(), arrow(), axisIcon(), box() (+116 more)

### Community 2 - "Session.cpp"
Cohesion: 0.10
Nodes (36): historyEdit(), OwnedCommand, owned, OwningCommandSession, plainEdit(), Session::addListener(), Session::addNamedView(), Session::begin() (+28 more)

### Community 4 - "MainWindow"
Cohesion: 0.03
Nodes (64): writeLiveGeometry(), CommandDialog, MainWindow, active_, arrowInput_, arrowInput2_, bodiesBeforeCommand_, combEdges_ (+56 more)

### Community 5 - "run_oracle.py"
Cohesion: 0.08
Nodes (54): add_point(), arc_poly(), body_at(), body_list(), build_sketch(), chain(), circumcentre(), cm() (+46 more)

### Community 6 - "Unit"
Cohesion: 0.10
Nodes (28): MainWindow::checkInterference(), MainWindow::driveJoints(), MainWindow::formatLength(), MainWindow::gridSettings(), MainWindow::lengthUnit(), MainWindow::openAnalysis(), MainWindow::openSection(), MainWindow::showCenterOfMass() (+20 more)

### Community 7 - "Document"
Cohesion: 0.03
Nodes (15): Document, effects_, lastReplayed_, lastReused_, modified_, pendingTools_, registry_, replaying_ (+7 more)

### Community 8 - "Viewport.cpp"
Cohesion: 0.05
Nodes (5): glide(), keys(), QKeyEvent, QtFrameBuffer, Viewport::Viewport()

### Community 9 - "SketchEditor"
Cohesion: 0.03
Nodes (54): HandleHit, back, index, spline, SketchEditor, arcDrag_, arcDragMoved_, arcEndsChain_ (+46 more)

### Community 10 - "CommandError"
Cohesion: 0.16
Nodes (16): CommandError, getBool(), getReal(), applyOperation(), bodyCentre(), bodyName(), holeSize(), body (+8 more)

### Community 11 - "optional"
Cohesion: 0.11
Nodes (3): optional, CommandRegistry::all(), Document

### Community 13 - "AnalysisSettings"
Cohesion: 0.11
Nodes (18): AnalysisKind, Accessibility, CurvatureMap, Draft, Isocurve, MinimumRadius, None, Zebra (+10 more)

### Community 14 - "Kind"
Cohesion: 0.06
Nodes (32): ConstructPlane, def_, kind_, EdgeFeature, def_, kind_, FaceFeature, def_ (+24 more)

### Community 16 - "CommandDialog"
Cohesion: 0.05
Nodes (31): CommandDialog, bodiesId_, bodiesLabel_, bodyInput_, buttons_, cmd_, conditional_, edgesId_ (+23 more)

### Community 17 - "Io.cpp"
Cohesion: 0.09
Nodes (19): MainWindow::print3d(), NamedShape, compoundOf(), exportShapes(), fmt(), formatForPath(), fromBrep(), importShape() (+11 more)

### Community 18 - "Unit"
Cohesion: 0.16
Nodes (18): ExpressionError, Quantity, angle, length, value, describe(), evaluateExpression(), isIdentChar() (+10 more)

### Community 19 - "MainWindowTools.cpp"
Cohesion: 0.05
Nodes (15): QDialog, MainWindow::chooseUnits(), MainWindow::editAppearance(), MainWindow::editMaterial(), MainWindow::exportDesign(), MainWindow::insertFile(), MainWindow::lookTargets(), MainWindow::measurePick() (+7 more)

### Community 20 - "Known gaps"
Cohesion: 0.33
Nodes (5): Include 3D Geometry, Known gaps, Sketch text, Splines and conics, Visual styles

### Community 21 - "Document"
Cohesion: 0.18
Nodes (7): ConstructAxisPoint, def_, kind_, jointOrigin(), JointPick, frame, revolveAxis()

### Community 22 - "MainWindow.cpp"
Cohesion: 0.09
Nodes (3): commandIcon(), qs(), MainWindow::applySection()

### Community 23 - "Architecture"
Cohesion: 0.40
Nodes (4): Architecture, How a command works, The document, Units

### Community 24 - "Affine"
Cohesion: 0.14
Nodes (13): Affine, a, b, d, e, Builder, byPlace_, k_ (+5 more)

### Community 25 - "ViewportSketch.cpp"
Cohesion: 0.08
Nodes (6): faceStyle(), lineStyle(), rgb(), Viewport::lookAt(), Viewport::planePoint(), Viewport::toWidget()

### Community 26 - "SketchPalette"
Cohesion: 0.06
Nodes (26): flatButton(), QCheckBox, QLabel, QToolButton, QWidget, SketchEditor, SketchPalette, body_ (+18 more)

### Community 27 - ".redrawAll"
Cohesion: 0.11
Nodes (7): NavPreset, Fusion, SolidWorks, Tinkercad, Viewport::clearDragArrow(), Viewport::clearSecondArrow(), Viewport::setInteractor()

### Community 28 - "Inputs"
Cohesion: 0.07
Nodes (19): CommandContext, Inputs, CommandSession::CommandSession(), getInt(), checkBody(), checkPattern(), CircularPattern, def_ (+11 more)

### Community 29 - "DocumentError"
Cohesion: 0.09
Nodes (30): DocumentError, PhysicalMaterial, color, density, name, checkViewName(), Document::abortTransaction(), Document::addBody() (+22 more)

### Community 30 - "Colors"
Cohesion: 0.07
Nodes (28): Colors, base, border, cubeBox, cubeText, errorBackground, grid, gridMajor (+20 more)

### Community 31 - "KernelError"
Cohesion: 0.25
Nodes (28): KernelError, asSolid(), boolean(), chamfer(), chamferEx(), deleteFaces(), draft(), extrude() (+20 more)

### Community 32 - "SketchOps.cpp"
Cohesion: 0.22
Nodes (27): at(), chainOf(), chamferCorner(), circularPattern(), copyEntities(), cornerAt(), cross(), dot() (+19 more)

### Community 33 - "ViewportArrow.cpp"
Cohesion: 0.05
Nodes (17): QLabel, QMouseEvent, ViewInteractor, Viewport::frontEdgeOwner(), rgb(), segmentDistance(), Viewport::arrowAt(), Viewport::arrowMouseMove() (+9 more)

### Community 34 - "ParameterCompleter"
Cohesion: 0.13
Nodes (9): QObject, ParameterCompleter, completer_, edit_, names_, ParameterCompleter::ParameterCompleter(), public, QCompleter (+1 more)

### Community 35 - "Constraint"
Cohesion: 0.10
Nodes (20): Constraint, driven, entities, expression, hasLabel, labelX, labelY, name (+12 more)

### Community 36 - "DocCommands.cpp"
Cohesion: 0.09
Nodes (30): axisOf(), CopyFn, differenceOrNull(), evaluateDimensions(), Loft, def_, makeBox(), makeCone() (+22 more)

### Community 38 - "solve"
Cohesion: 0.18
Nodes (13): set, addConstraintChecked(), Layout, n, px, py, rad, makeLayout() (+5 more)

### Community 39 - "Snap"
Cohesion: 0.11
Nodes (18): Snap, alignX, alignY, bodyArc, bodySegment, entity, fromX, fromY (+10 more)

### Community 41 - "ConstraintType"
Cohesion: 0.09
Nodes (23): ConstraintType, Angle, Coincident, Collinear, Concentric, Diameter, Distance, Equal (+15 more)

### Community 42 - "TsrModule.cpp"
Cohesion: 0.12
Nodes (13): Application, BRepBodies, Component, Design, Product, raiseIfError(), UserParameter, name (+5 more)

### Community 43 - "Pick"
Cohesion: 0.11
Nodes (17): Hit, index, kind, Pick, bodyArc, bodyPoint, bodySegment, hit (+9 more)

### Community 44 - "SketchEditor.cpp"
Cohesion: 0.11
Nodes (4): angleInArc(), ccwContains(), circumcircle(), segDistance()

### Community 46 - "Zip.cpp"
Cohesion: 0.20
Nodes (13): Entry, data, name, ZipError, crc32(), deflateRaw(), get16(), get32() (+5 more)

### Community 47 - "AnalysisSettings"
Cohesion: 0.10
Nodes (16): DragArrow, base, dir, radius, ref, ring, value, PendingLook (+8 more)

### Community 48 - "Sketch.cpp"
Cohesion: 0.06
Nodes (29): EntityType, Arc, Circle, Ellipse, Line, Spline, isRound(), SketchError (+21 more)

### Community 49 - "ParamSet"
Cohesion: 0.07
Nodes (35): ModelParameter, angle, expression, input, label, name, owner, unit (+27 more)

### Community 50 - "MainWindowSketch.cpp"
Cohesion: 0.06
Nodes (14): grabWindowWithPanels(), MainWindow::cancelSketch(), MainWindow::editSketch(), MainWindow::finishSketch(), MainWindow::onEdgeClicked(), MainWindow::onProfileClicked(), MainWindow::originalShape(), MainWindow::sketchPalette() (+6 more)

### Community 51 - "InputDef"
Cohesion: 0.09
Nodes (21): InputDef, choices, defaultValue, id, label, max, min, minExclusive (+13 more)

### Community 52 - "HoleSize"
Cohesion: 0.50
Nodes (4): HoleSize, modeled, pitch, radius

### Community 54 - "ViewportAnalysis.cpp"
Cohesion: 0.06
Nodes (14): ArrowPlacement, base, dir, edgePlacement(), facesPlacement(), MainWindow::attachArrowCompleters(), MainWindow::patternCentre(), MainWindow::pickedFaces() (+6 more)

### Community 55 - "Document::recompute"
Cohesion: 0.18
Nodes (8): Document::expressionEnv(), Document::recompute(), Document::recordFeature(), Document::removeFeature(), Document::setFeatureInputs(), Document::setFeatureSuppressed(), featureData(), toJson()

### Community 56 - "MarkingMenu.cpp"
Cohesion: 0.08
Nodes (16): MarkingMenu, enabled, MarkingMenu::keyPressEvent(), MarkingMenu::mouseMoveEvent(), MarkingMenu::paintEvent(), MarkingMenu::popupAt(), public, MarkingMenu::ringIndexAt() (+8 more)

### Community 57 - "Profile"
Cohesion: 0.33
Nodes (5): Profile, area, face, x, y

### Community 58 - "Entity"
Cohesion: 0.10
Nodes (12): Entity, a, b, center, construction, fit, handles, included (+4 more)

### Community 59 - "xdrive.py"
Cohesion: 0.28
Nodes (15): button(), canvas(), click(), drag(), flush(), geometry(), key(), keycode() (+7 more)

### Community 62 - "Session"
Cohesion: 0.07
Nodes (7): PythonHost::PythonHost(), Session, commands_, doc_, listeners_, nextListener_, path_

### Community 63 - "Theme.cpp"
Cohesion: 0.19
Nodes (6): setIconTheme(), darkColors(), darkPalette(), darkStyleSheet(), lightColors(), lightStyleSheet()

### Community 64 - "BodyFrame"
Cohesion: 0.10
Nodes (33): boundingBox(), completeEdgeReferences(), completeFaceReferences(), decode(), decodeFaces(), dot(), edgeReference(), EdgeSig (+25 more)

### Community 65 - "CommandRegistry"
Cohesion: 0.12
Nodes (4): CommandRegistry, cmds_, CommandRegistry::add(), TEST()

### Community 67 - "BodyFrame"
Cohesion: 0.13
Nodes (14): BodyFrame, diag, dx, dy, dz, x0, y0, z0 (+6 more)

### Community 68 - "Theme"
Cohesion: 0.22
Nodes (4): Theme, colors_, public, styled_

### Community 69 - "PlaneEdges"
Cohesion: 0.16
Nodes (5): PlaneEdges, arcs, curves, segments, vertices

### Community 70 - "Command.cpp"
Cohesion: 0.24
Nodes (11): expressionKey(), checkInputValue(), CommandContext::evaluateExpression(), CommandDef::input(), CommandSession::applyInTransaction(), CommandSession::cancel(), CommandSession::execute(), CommandSession::preview() (+3 more)

### Community 71 - "ParametersDialog.cpp"
Cohesion: 0.06
Nodes (24): Column, kComment, kExpression, kName, kParameter, kStar, kUnit, kValue (+16 more)

### Community 72 - "TEST"
Cohesion: 0.09
Nodes (3): param(), TEST(), tmp()

### Community 73 - "curve"
Cohesion: 0.29
Nodes (11): curve(), curves(), entityCurves(), interiorPoint(), profileAt(), profiles(), splineHandles(), textShape() (+3 more)

### Community 74 - "Kind"
Cohesion: 0.09
Nodes (21): HudField, edit, editing, kind, locked, value, Kind, Angle (+13 more)

### Community 75 - "InputType"
Cohesion: 0.12
Nodes (17): InputType, Axis, Bodies, Body, Bool, Choice, Edges, Faces (+9 more)

### Community 76 - "Vec3"
Cohesion: 0.19
Nodes (19): SurfacePoint, normal, point, Vec3, edgeMidpoint(), edgesNear(), frame(), makeBox() (+11 more)

### Community 77 - "Dimension"
Cohesion: 0.50
Nodes (4): Dimension, Angle, Length, Unitless

### Community 79 - "QString"
Cohesion: 0.11
Nodes (7): CommandDialog::CommandDialog(), ExpressionSpinBox, eval_, expression_, shown_, formatNumber(), dimensionOf()

### Community 80 - "SketchDisplay"
Cohesion: 0.12
Nodes (11): ProfileObject, index, sketch, SketchDisplay, construction, curves, fixedCurves, frame (+3 more)

### Community 81 - "Command"
Cohesion: 0.04
Nodes (55): Adding a tool, Command, CommandDef, feature, icon, id, inputs, name (+47 more)

### Community 82 - "Measurement"
Cohesion: 0.13
Nodes (14): Kind, Angle, Area, Length, Volume, Measurement, from, hasLine (+6 more)

### Community 83 - "SketchCurves.cpp"
Cohesion: 0.15
Nodes (14): crossings(), crossingsOf(), curve2d(), endIsFree(), extendCurve(), finishExtend(), flattened(), includeEdges() (+6 more)

### Community 84 - "UiCommand"
Cohesion: 0.11
Nodes (13): UiCommand, enabled, icon, id, name, panel, run, shortcut (+5 more)

### Community 85 - "Level"
Cohesion: 0.16
Nodes (13): debug(), error(), info(), Level, Debug, Error, Info, Warning (+5 more)

### Community 86 - "README.md"
Cohesion: 0.11
Nodes (15): Build, Conventions, Development, Tests, Reference parts, Fusion feature checklist, Roadmap, Contents (+7 more)

### Community 87 - "Document.cpp"
Cohesion: 0.07
Nodes (37): ConstructionPlane, name, spec, bodyNumber(), Document::axisFrame(), Document::bodies(), Document::body(), Document::bodyName() (+29 more)

### Community 90 - "MainWindow::MainWindow"
Cohesion: 0.12
Nodes (5): PythonHost, MainWindow::MainWindow(), MainWindow::beginSketch(), MainWindow::exitSketchMode(), MainWindow::showPreferences()

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
Cohesion: 0.06
Nodes (34): Body, color, display, material, name, shape, Component, bodies (+26 more)

### Community 97 - "NamedView"
Cohesion: 0.12
Nodes (15): NamedView, eye, name, size, target, up, Document::bodyShapes(), Document::effectOf() (+7 more)

### Community 98 - "FakeDoc"
Cohesion: 0.17
Nodes (6): FakeDoc, aborts, commits, items, open, snapshot

### Community 100 - "Expression.cpp"
Cohesion: 0.21
Nodes (7): evaluateQuantity(), expressionReferences(), isConstantName(), isFunctionName(), isPlainQuantity(), isValidParameterName(), TEST()

### Community 102 - "sstream"
Cohesion: 0.17
Nodes (5): doc_(), Document::Document(), Document::ocafBytes(), ocafApplication(), Document::load()

### Community 103 - "CommandSession"
Cohesion: 0.15
Nodes (4): CommandSession, inputs_, CommandRegistry::find(), CommandRegistry::run()

### Community 104 - "BoundingBox"
Cohesion: 0.16
Nodes (17): BoundingBox, max, min, WallSide, Center, Side1, Side2, extendedWire() (+9 more)

### Community 106 - "SectionState"
Cohesion: 0.25
Nodes (7): SectionState, active, angle, flip, offset, plane, visible

### Community 107 - "Display"
Cohesion: 0.25
Nodes (7): Display, constraints, construction, dimensions, points, profiles, projected

### Community 108 - "main"
Cohesion: 0.36
Nodes (4): listCommands(), main(), usage(), main()

### Community 109 - "smoke"
Cohesion: 0.33
Nodes (6): smoke(), key, MassProperties, area, centerOfMass, volume

### Community 110 - "TopologyCounts"
Cohesion: 0.18
Nodes (16): Section, Circular, Square, Triangular, TopologyCounts, edges, faces, shells (+8 more)

### Community 112 - "Feature"
Cohesion: 0.17
Nodes (10): Feature, commandId, error, id, inputs, name, parameterNames, rolledBack (+2 more)

### Community 113 - "cachedProfiles"
Cohesion: 0.15
Nodes (3): MainWindow::updateDragArrow(), cachedProfiles(), keyOf()

### Community 114 - "uninstall.sh"
Cohesion: 0.52
Nodes (6): die(), manifest_for(), refresh(), uninstall.sh script, step(), usage()

### Community 115 - "install.sh"
Cohesion: 0.60
Nodes (5): die(), refresh(), install.sh script, step(), usage()

### Community 116 - "TestFramework.h"
Cohesion: 0.15
Nodes (11): Result, error, ok, output, captured(), PythonHost::exec(), PythonHost::runScript(), Case (+3 more)

### Community 117 - ".rebuild"
Cohesion: 0.10
Nodes (12): hiddenColour(), qc(), rgb(), sharpEdges(), Style, Shaded, ShadedEdges, ShadedHidden (+4 more)

### Community 118 - "bindTsr"
Cohesion: 0.29
Nodes (4): bindTsr(), fromPy(), toPy(), typeName()

### Community 120 - "Viewport::setDragArrow"
Cohesion: 0.18
Nodes (4): Viewport::DragArrow::handle(), Viewport::emitArrow(), Viewport::setDragArrow(), Viewport::setDragRing()

### Community 121 - "bindAdsk"
Cohesion: 0.29
Nodes (3): bindAdsk(), BRepBody, index

### Community 123 - "Placement"
Cohesion: 0.25
Nodes (7): Placement, angle, cx, cy, dx, dy, scale

### Community 124 - "ChainSegment"
Cohesion: 0.30
Nodes (4): ChainSegment, entity, forward, Placement::apply()

### Community 127 - "ExpressionEnv"
Cohesion: 0.29
Nodes (5): ExpressionEnv, lengthUnit, lookup, env(), mm()

### Community 128 - ".updatePreview"
Cohesion: 0.06
Nodes (26): ext(), fixedColor(), freeColor(), lineEntity(), qc(), rgb(), SketchEditor::SketchEditor(), wire() (+18 more)

### Community 130 - "UserParameter"
Cohesion: 0.33
Nodes (6): UserParameter, comment, expression, name, unit, value

### Community 132 - "Curve2d"
Cohesion: 0.40
Nodes (4): Curve2d, periodic, t0, t1

### Community 134 - "Axis"
Cohesion: 0.50
Nodes (4): Axis, X, Y, Z

### Community 135 - "BooleanOp"
Cohesion: 0.50
Nodes (4): BooleanOp, Cut, Intersect, Join

### Community 139 - "ThreadInfo"
Cohesion: 0.50
Nodes (4): ThreadInfo, diameter, internal, pitch

### Community 141 - "Point"
Cohesion: 0.47
Nodes (5): Point, x, y, z, customPlaneSpec()

### Community 142 - "SplineHandle"
Cohesion: 0.29
Nodes (7): SplineHandle, arm, index, tx, ty, x, y

### Community 143 - "ChamferType"
Cohesion: 0.67
Nodes (3): ChamferType, DistanceAngle, TwoDistances

## Knowledge Gaps
- **772 isolated node(s):** `ok`, `output`, `error`, `isReal`, `real` (+767 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 1439 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **30 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `optional` connect `optional` to `.updatePreview`, `Viewport`, `MainWindow`, `Unit`, `Kernel.cpp`, `Io.cpp`, `Unit`, `ViewportSketch.cpp`, `Inputs`, `SketchOps.cpp`, `ViewportArrow.cpp`, `DocCommands.cpp`, `CommandDialog.cpp`, `SketchEditor.cpp`, `AnalysisSettings`, `ParamSet`, `InputDef`, `ViewportAnalysis.cpp`, `Entity`, `Session`, `Vec3`, `QString`, `SketchCurves.cpp`, `Document.cpp`, `ReplayStep`, `Feature`, `ExpressionEnv`?**
  _High betweenness centrality (0.102) - this node is a cross-community bridge._
- **What connects `ok`, `output`, `error` to the rest of the system?**
  _772 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Viewport` be split into smaller, more focused modules?**
  _Cohesion score 0.01624015748031496 - nodes in this community are weakly interconnected._
- **Why does `Viewport` connect `Viewport` to `ViewportArrow.cpp`, `MainWindow`, `Unit`, `Viewport.cpp`, `optional`, `AnalysisSettings`, `AnalysisSettings`, `SketchDisplay`, `QTimer`, `SketchCurves.cpp`, `.rebuild`, `.toPixels`, `ViewportAnalysis.cpp`, `Viewport::setDragArrow`, `rect`, `.redrawAll`?**
  _High betweenness centrality (0.092) - this node is a cross-community bridge._
- **Should `Icons.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.05337690631808279 - nodes in this community are weakly interconnected._
- **Why does `SketchEditor` connect `SketchEditor` to `.updatePreview`, `Viewport`, `ParameterCompleter`, `ViewportArrow.cpp`, `Constraint`, `PlaneEdges`, `Unit`, `Snap`, `Kind`, `Display`, `optional`, `Pick`, `SketchEditor.cpp`, `Entity`, `.solveAndShow`, `Session`?**
  _High betweenness centrality (0.084) - this node is a cross-community bridge._
- **Should `Session.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.10303030303030303 - nodes in this community are weakly interconnected._