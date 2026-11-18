# Graph Report - tessera  (2026-11-17)

## Corpus Check
- 440 files · ~288,671 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 78 file(s) not represented in the graph (top: .drive 70, (none) 5, .cmake 1)

## Summary
- 4044 nodes · 10427 edges · 139 communities (113 shown, 26 thin omitted)
- Extraction: 85% EXTRACTED · 15% INFERRED · 0% AMBIGUOUS · INFERRED: 1589 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `893b26d5`
- Run `git rev-parse HEAD` and compare to check if the graph is stale.
- Run `graphify update .` after code changes (no API cost).

## Community Hubs (Navigation)
- Viewport
- Icons.cpp
- Session.cpp
- tsr
- MainWindow
- run_oracle.py
- CommandError
- Document
- Viewport.cpp
- SketchEditor
- DocumentError
- optional
- Kernel.cpp
- AnalysisSettings
- Kind
- QMouseEvent
- CommandDialog
- Io.cpp
- Parser
- InputDef
- SketchEditor.cpp
- PhysicalMaterial
- TEST
- Affine
- ViewportSketch.cpp
- SketchPalette
- DocCommands.cpp
- sketchFor
- CommandContext
- Colors
- KernelError
- SketchOps.cpp
- .rebuild
- ParameterCompleter
- Constraint
- SketchGeometry.cpp
- src/main.cpp
- solve
- Column
- BoundaryCell
- ConstraintType
- AdskModule.cpp
- Pick
- TopologyCounts
- Zip.cpp
- AnalysisSettings
- Sketch
- Document.cpp
- .showDialog
- string
- SketchEditor.cpp
- .toPixels
- Snap
- Document::recompute
- MainWindow.cpp
- TEST
- MarkingMenu
- xdrive.py
- adsk_core
- CommandDialog.cpp
- Session
- Theme.cpp
- BodyFrame
- CommandRegistry
- Command.cpp
- Unit
- Theme
- Feature
- InputType
- ParametersDialog.cpp
- MainWindowSketch.cpp
- ViewportArrow.cpp
- CommandSession
- Rect
- Vec3
- CommandDialog::CommandDialog
- math
- CommandDialog::CommandDialog
- SketchDisplay
- Kind
- Measurement
- SketchCurves.cpp
- fail
- Level
- checkPattern
- UiCommand
- test_feature_pattern.py
- MainWindow::MainWindow
- MainWindowTools.cpp
- Expression.cpp
- FileFormat
- Known differences still to build
- ReplayStep
- Session::addListener
- MainWindowArrow.cpp
- FakeDoc
- ParamSet
- BoundingBox
- QPointF
- Document::load
- Placement
- test_rigid_group.py
- Display
- Axis
- Known gaps
- SectionState
- uninstall.sh
- install.sh
- TestFramework.h
- .redrawAll
- UserParameter
- Viewport.h
- SelectionBox
- test_incremental_replay.py
- BooleanOp
- MassProperties
- QScrollArea
- ThreadInfo
- Value.h
- ChamferType
- Inputs
- Icons.h
- LAB_NOTES.md
- build.sh
- live-test.sh
- ChainSegment
- Tool
- SplineHandle
- BodyFrame
- Align
- BRepBody

## God Nodes (most connected - your core abstractions)
1. `Viewport` - 286 edges
2. `SketchEditor` - 198 edges
3. `MainWindow` - 189 edges
4. `Inputs` - 170 edges
5. `render()` - 127 edges
6. `CommandContext` - 125 edges
7. `Document` - 124 edges
8. `CommandDialog` - 101 edges
9. `CommandError` - 75 edges
10. `Command` - 71 edges

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

## Communities (139 total, 26 thin omitted)

### Community 0 - "Viewport"
Cohesion: 0.01
Nodes (79): view_, QLineEdit, Viewport, analysis_, analysisObjects_, appliedGridStep_, arrowBoxes_, arrowDragging_ (+71 more)

### Community 1 - "Icons.cpp"
Cohesion: 0.05
Nodes (130): accessibilityIcon(), alignIcon(), appearanceIcon(), arc3Icon(), arcIcon(), arcTangentIcon(), arrow(), axisIcon() (+122 more)

### Community 2 - "Session.cpp"
Cohesion: 0.17
Nodes (26): historyEdit(), plainEdit(), Session::addNamedView(), Session::computeAll(), Session::deleteFeature(), Session::deleteNamedView(), Session::deleteParameter(), Session::newDocument() (+18 more)

### Community 4 - "MainWindow"
Cohesion: 0.03
Nodes (67): CommandDialog, MainWindow, active_, appearanceColour_, appearanceFaces_, appearancePanel_, arrowInput_, arrowInput2_ (+59 more)

### Community 5 - "run_oracle.py"
Cohesion: 0.08
Nodes (54): add_point(), arc_poly(), body_at(), body_list(), build_sketch(), chain(), circumcentre(), cm() (+46 more)

### Community 6 - "CommandError"
Cohesion: 0.10
Nodes (37): CommandError, getBool(), getInt(), getReal(), Align::apply(), applyOperation(), applyToParticipants(), bodyCentre() (+29 more)

### Community 7 - "Document"
Cohesion: 0.03
Nodes (15): Document, effects_, lastReplayed_, lastReused_, modified_, pendingTools_, registry_, replaying_ (+7 more)

### Community 8 - "Viewport.cpp"
Cohesion: 0.05
Nodes (5): glide(), keys(), QKeyEvent, QtFrameBuffer, Viewport::Viewport()

### Community 9 - "SketchEditor"
Cohesion: 0.03
Nodes (53): HandleHit, back, index, spline, SketchEditor, arcDrag_, arcDragMoved_, arcEndsChain_ (+45 more)

### Community 10 - "DocumentError"
Cohesion: 0.09
Nodes (30): DocumentError, SketchRecord, data, name, offset, plane, checkViewName(), Document::abortTransaction() (+22 more)

### Community 11 - "optional"
Cohesion: 0.08
Nodes (10): optional, CommandRegistry::all(), Document, EntityType, Arc, Circle, Ellipse, Line (+2 more)

### Community 12 - "Kernel.cpp"
Cohesion: 0.03
Nodes (4): isoCoarsePitch(), topologyCounts(), touching(), wrapOntoCylinder()

### Community 13 - "AnalysisSettings"
Cohesion: 0.11
Nodes (18): AnalysisKind, Accessibility, CurvatureMap, Draft, Isocurve, MinimumRadius, None, Zebra (+10 more)

### Community 14 - "Kind"
Cohesion: 0.07
Nodes (29): ConstructAxisPoint, def_, kind_, EdgeFeature, def_, kind_, Kind, Angle (+21 more)

### Community 15 - "QMouseEvent"
Cohesion: 0.08
Nodes (11): QMouseEvent, ViewInteractor, Viewport::arrowMouseMove(), Viewport::arrowMousePress(), Viewport::arrowMouseRelease(), Viewport::DragArrow::handle(), Viewport::dragArrowForTest(), Viewport::emitArrow() (+3 more)

### Community 16 - "CommandDialog"
Cohesion: 0.04
Nodes (39): CommandDialog, bodiesId_, bodiesLabel_, bodyInput_, buttons_, cellsId_, cellsList_, cmd_ (+31 more)

### Community 17 - "Io.cpp"
Cohesion: 0.10
Nodes (19): MainWindow::print3d(), NamedShape, compoundOf(), exportShapes(), fmt(), formatForPath(), fromBrep(), importShape() (+11 more)

### Community 18 - "Parser"
Cohesion: 0.18
Nodes (15): Quantity, angle, length, value, describe(), isIdentChar(), Parser, ang_ (+7 more)

### Community 19 - "InputDef"
Cohesion: 0.09
Nodes (22): InputDef, choices, defaultValue, id, label, max, min, minExclusive (+14 more)

### Community 20 - "SketchEditor.cpp"
Cohesion: 0.08
Nodes (11): Entity, a, b, center, construction, fit, handles, included (+3 more)

### Community 21 - "PhysicalMaterial"
Cohesion: 0.22
Nodes (13): PhysicalMaterial, color, density, name, checkMaterial(), Document::designMaterials(), Document::material(), Document::setBodyMaterial() (+5 more)

### Community 22 - "TEST"
Cohesion: 0.07
Nodes (10): Sketch, constraints, entities, points, texts, Sketch::addCircle(), Sketch::addEllipticalArc(), Sketch::addLine() (+2 more)

### Community 24 - "Affine"
Cohesion: 0.14
Nodes (13): Affine, a, b, d, e, Builder, byPlace_, k_ (+5 more)

### Community 25 - "ViewportSketch.cpp"
Cohesion: 0.08
Nodes (6): faceStyle(), lineStyle(), rgb(), Viewport::lookAt(), Viewport::planePoint(), Viewport::toWidget()

### Community 26 - "SketchPalette"
Cohesion: 0.06
Nodes (26): QCheckBox, QLabel, QToolButton, QWidget, SketchEditor, SketchPalette, body_, constraints_ (+18 more)

### Community 27 - "DocCommands.cpp"
Cohesion: 0.14
Nodes (15): axisOf(), HoleSize, modeled, pitch, radius, JointPick, frame, makeBox() (+7 more)

### Community 28 - "sketchFor"
Cohesion: 0.11
Nodes (12): Emboss, def_, Extrude, def_, Hole, def_, Pipe, def_ (+4 more)

### Community 29 - "CommandContext"
Cohesion: 0.03
Nodes (57): Adding a tool, Command, CommandContext, CommandDef, feature, icon, id, inputs (+49 more)

### Community 30 - "Colors"
Cohesion: 0.07
Nodes (28): Colors, base, border, cubeBox, cubeText, errorBackground, grid, gridMajor (+20 more)

### Community 31 - "KernelError"
Cohesion: 0.23
Nodes (35): KernelError, asSolid(), boolean(), boundaryCells(), chamfer(), chamferEx(), deleteFaces(), draft() (+27 more)

### Community 32 - "SketchOps.cpp"
Cohesion: 0.16
Nodes (29): at(), chainOf(), chamferCorner(), circularPattern(), copyEntities(), cornerAt(), cross(), dot() (+21 more)

### Community 33 - ".rebuild"
Cohesion: 0.10
Nodes (12): hiddenColour(), qc(), rgb(), sharpEdges(), Style, Shaded, ShadedEdges, ShadedHidden (+4 more)

### Community 34 - "ParameterCompleter"
Cohesion: 0.13
Nodes (8): ParameterCompleter, completer_, edit_, names_, ParameterCompleter::ParameterCompleter(), public, QCompleter, QLineEdit

### Community 35 - "Constraint"
Cohesion: 0.06
Nodes (29): Constraint, driven, entities, expression, hasLabel, labelX, labelY, name (+21 more)

### Community 36 - "SketchGeometry.cpp"
Cohesion: 0.06
Nodes (25): Point, x, y, z, conditionedSpline(), curve(), curves(), customPlaneSpec() (+17 more)

### Community 38 - "solve"
Cohesion: 0.12
Nodes (14): addConstraintChecked(), Layout, n, px, py, rad, makeLayout(), pack() (+6 more)

### Community 39 - "Column"
Cohesion: 0.25
Nodes (8): Column, kComment, kExpression, kName, kParameter, kStar, kUnit, kValue

### Community 40 - "BoundaryCell"
Cohesion: 0.29
Nodes (4): BoundaryCell, ref, shape, volume

### Community 41 - "ConstraintType"
Cohesion: 0.07
Nodes (27): ConstraintType, Angle, Coincident, Collinear, Concentric, Curvature, Diameter, Distance (+19 more)

### Community 42 - "AdskModule.cpp"
Cohesion: 0.12
Nodes (13): Application, BRepBodies, Component, Design, Product, raiseIfError(), UserParameter, name (+5 more)

### Community 43 - "Pick"
Cohesion: 0.12
Nodes (15): Pick, bodyArc, bodyPoint, bodySegment, hit, midpointOf, onEntity, onXAxis (+7 more)

### Community 45 - "TopologyCounts"
Cohesion: 0.15
Nodes (18): Section, Circular, Square, Triangular, TopologyCounts, edges, faces, shells (+10 more)

### Community 46 - "Zip.cpp"
Cohesion: 0.11
Nodes (16): Entry, data, name, ZipError, crc32(), deflateRaw(), get16(), get32() (+8 more)

### Community 47 - "AnalysisSettings"
Cohesion: 0.08
Nodes (20): DragArrow, base, dir, radius, ref, ring, value, PendingLook (+12 more)

### Community 48 - "Sketch"
Cohesion: 0.08
Nodes (20): SketchError, SplineKind, Conic, Control, Fit, entityTypeName(), isDimension(), Sketch::addConic() (+12 more)

### Community 49 - "Document.cpp"
Cohesion: 0.07
Nodes (40): ConstructionPlane, name, spec, bodyNumber(), Document::addBody(), Document::axisFrame(), Document::bodies(), Document::body() (+32 more)

### Community 51 - "string"
Cohesion: 0.12
Nodes (9): AddUserParameter, def_, Combine, def_, isIdentifier(), NewComponent, def_, RigidGroup (+1 more)

### Community 52 - "SketchEditor.cpp"
Cohesion: 0.12
Nodes (4): angleInArc(), ccwContains(), circumcircle(), segDistance()

### Community 54 - "Snap"
Cohesion: 0.08
Nodes (25): ext(), fixedColor(), freeColor(), lineEntity(), qc(), rgb(), Snap, alignX (+17 more)

### Community 55 - "Document::recompute"
Cohesion: 0.18
Nodes (8): Document::expressionEnv(), Document::recompute(), Document::recordFeature(), Document::removeFeature(), Document::setFeatureInputs(), Document::setFeatureSuppressed(), featureData(), toJson()

### Community 56 - "MainWindow.cpp"
Cohesion: 0.09
Nodes (3): commandIcon(), qs(), MainWindow::applySection()

### Community 57 - "TEST"
Cohesion: 0.10
Nodes (3): param(), TEST(), tmp()

### Community 58 - "MarkingMenu"
Cohesion: 0.40
Nodes (3): MarkingMenu, enabled, public

### Community 59 - "xdrive.py"
Cohesion: 0.28
Nodes (15): button(), canvas(), click(), drag(), flush(), geometry(), key(), keycode() (+7 more)

### Community 62 - "Session"
Cohesion: 0.06
Nodes (13): listCommands(), main(), usage(), PythonHost::PythonHost(), main(), smoke(), key, Session (+5 more)

### Community 63 - "Theme.cpp"
Cohesion: 0.19
Nodes (6): setIconTheme(), darkColors(), darkPalette(), darkStyleSheet(), lightColors(), lightStyleSheet()

### Community 64 - "BodyFrame"
Cohesion: 0.08
Nodes (34): boundingBox(), completeEdgeReferences(), completeFaceReferences(), decode(), decodeFaces(), dot(), edgeReference(), EdgeSig (+26 more)

### Community 65 - "CommandRegistry"
Cohesion: 0.09
Nodes (8): Architecture, How a command works, The document, Units, CommandRegistry, cmds_, CommandRegistry::add(), TEST()

### Community 66 - "Command.cpp"
Cohesion: 0.33
Nodes (7): expressionKey(), checkInputValue(), CommandContext::evaluateExpression(), CommandDef::input(), CommandSession::applyInTransaction(), CommandSession::setInput(), CommandSession::validate()

### Community 67 - "Unit"
Cohesion: 0.11
Nodes (28): MainWindow::checkInterference(), MainWindow::driveJoints(), MainWindow::formatLength(), MainWindow::gridSettings(), MainWindow::lengthUnit(), MainWindow::openAnalysis(), MainWindow::openSection(), MainWindow::showCenterOfMass() (+20 more)

### Community 68 - "Theme"
Cohesion: 0.20
Nodes (5): MainWindow::showPreferences(), Theme, colors_, public, styled_

### Community 69 - "Feature"
Cohesion: 0.10
Nodes (17): Feature, commandId, error, id, inputs, name, parameterNames, rolledBack (+9 more)

### Community 70 - "InputType"
Cohesion: 0.08
Nodes (21): bindTsr(), fromPy(), toPy(), typeName(), InputType, Axis, Bodies, Body (+13 more)

### Community 71 - "ParametersDialog.cpp"
Cohesion: 0.09
Nodes (16): number(), ParametersDialog, building_, error_, filter_, listener_, ParametersDialog::ParametersDialog(), public (+8 more)

### Community 72 - "MainWindowSketch.cpp"
Cohesion: 0.05
Nodes (20): MainWindow::updateDragArrow(), MainWindow::cancelSketch(), MainWindow::editSketch(), MainWindow::exitSketchMode(), MainWindow::finishSketch(), MainWindow::onProfileClicked(), MainWindow::originalShape(), MainWindow::sketchPalette() (+12 more)

### Community 73 - "ViewportArrow.cpp"
Cohesion: 0.06
Nodes (27): Viewport::frontEdgeOwner(), rgb(), segmentDistance(), Viewport::arrowAt(), Viewport::arrowParam(), Viewport::dragArrowHandle(), Viewport::placeArrowBoxes(), Viewport::rebuildArrow() (+19 more)

### Community 74 - "CommandSession"
Cohesion: 0.10
Nodes (12): CommandSession, inputs_, CommandSession::cancel(), CommandSession::execute(), CommandSession::preview(), CommandRegistry::find(), CommandRegistry::run(), OwnedCommand (+4 more)

### Community 75 - "Rect"
Cohesion: 0.50
Nodes (4): Session::notifyChanged(), Rect, l, p

### Community 76 - "Vec3"
Cohesion: 0.17
Nodes (22): SurfacePoint, normal, point, Vec3, containsPoint(), edgeMidpoint(), edgesNear(), extrudeToFace() (+14 more)

### Community 77 - "CommandDialog::CommandDialog"
Cohesion: 0.12
Nodes (7): CommandDialog::CommandDialog(), Dimension, Angle, Length, Unitless, inputExpression(), dimensionOf()

### Community 78 - "math"
Cohesion: 0.04
Nodes (4): dist(), up_to_underside(), check_regular(), dist_to_line()

### Community 79 - "CommandDialog::CommandDialog"
Cohesion: 0.13
Nodes (5): ExpressionSpinBox, eval_, expression_, shown_, formatNumber()

### Community 80 - "SketchDisplay"
Cohesion: 0.12
Nodes (11): ProfileObject, index, sketch, SketchDisplay, construction, curves, fixedCurves, frame (+3 more)

### Community 81 - "Kind"
Cohesion: 0.08
Nodes (24): Hit, index, kind, HudField, edit, editing, kind, locked (+16 more)

### Community 82 - "Measurement"
Cohesion: 0.12
Nodes (15): Kind, Angle, Area, Length, Volume, Measurement, from, hasLine (+7 more)

### Community 83 - "SketchCurves.cpp"
Cohesion: 0.13
Nodes (19): crossings(), crossingsOf(), Curve2d, curve2d(), periodic, t0, t1, endIsFree() (+11 more)

### Community 85 - "Level"
Cohesion: 0.16
Nodes (13): debug(), error(), info(), Level, Debug, Error, Info, Warning (+5 more)

### Community 86 - "checkPattern"
Cohesion: 0.13
Nodes (10): checkPattern(), CircularPattern, def_, Mirror, def_, PathPattern, def_, preparePattern() (+2 more)

### Community 87 - "UiCommand"
Cohesion: 0.07
Nodes (22): UiCommand, enabled, icon, id, name, panel, run, shortcut (+14 more)

### Community 89 - "MainWindow::MainWindow"
Cohesion: 0.09
Nodes (8): PythonHost, retintIcons(), setIcon(), flatButton(), MainWindow::MainWindow(), MainWindow::buildSketchTab(), MainWindow::enterSketchMode(), MainWindow::editAppearance()

### Community 90 - "MainWindowTools.cpp"
Cohesion: 0.06
Nodes (18): QObject, QDialog, editMaterialDialog(), MainWindow::chooseUnits(), MainWindow::editMaterial(), MainWindow::exportDesign(), MainWindow::insertFile(), MainWindow::lookTargets() (+10 more)

### Community 91 - "Expression.cpp"
Cohesion: 0.13
Nodes (15): ExpressionEnv, lengthUnit, lookup, ExpressionError, evaluateExpression(), evaluateQuantity(), expressionReferences(), isConstantName() (+7 more)

### Community 92 - "FileFormat"
Cohesion: 0.17
Nodes (12): FileFormat, Brep, Iges, Obj, Step, Stl, ThreeMF, FormatInfo (+4 more)

### Community 93 - "Known differences still to build"
Cohesion: 0.15
Nodes (12): Data and files, Findings from the videos, Fusion study list, Interface, Known differences still to build, Navigation and display, Selection and the canvas, Sketch (+4 more)

### Community 95 - "ReplayStep"
Cohesion: 0.05
Nodes (38): MainWindow::paintBody(), Body, color, display, faceColors, material, name, shape (+30 more)

### Community 97 - "MainWindowArrow.cpp"
Cohesion: 0.07
Nodes (13): ArrowPlacement, base, dir, edgePlacement(), facesPlacement(), MainWindow::attachArrowCompleters(), MainWindow::patternCentre(), MainWindow::pickedFaces() (+5 more)

### Community 98 - "FakeDoc"
Cohesion: 0.17
Nodes (6): FakeDoc, aborts, commits, items, open, snapshot

### Community 99 - "ParamSet"
Cohesion: 0.07
Nodes (36): ModelParameter, angle, expression, input, label, name, owner, unit (+28 more)

### Community 100 - "BoundingBox"
Cohesion: 0.23
Nodes (14): BoundingBox, max, min, WallSide, Center, Side1, Side2, extendedWire() (+6 more)

### Community 101 - "QPointF"
Cohesion: 0.11
Nodes (5): PlaneEdges, arcs, curves, segments, vertices

### Community 102 - "Document::load"
Cohesion: 0.17
Nodes (5): doc_(), Document::Document(), Document::ocafBytes(), ocafApplication(), Document::load()

### Community 104 - "Placement"
Cohesion: 0.25
Nodes (7): Placement, angle, cx, cy, dx, dy, scale

### Community 108 - "Display"
Cohesion: 0.25
Nodes (7): Display, constraints, construction, dimensions, points, profiles, projected

### Community 110 - "Axis"
Cohesion: 0.50
Nodes (4): Axis, X, Y, Z

### Community 111 - "Known gaps"
Cohesion: 0.05
Nodes (35): Build, Conventions, Development, Tests, 3D Sketch, Align, Appearance, Boundary Fill (+27 more)

### Community 113 - "SectionState"
Cohesion: 0.25
Nodes (7): SectionState, active, angle, flip, offset, plane, visible

### Community 114 - "uninstall.sh"
Cohesion: 0.52
Nodes (6): die(), manifest_for(), refresh(), uninstall.sh script, step(), usage()

### Community 115 - "install.sh"
Cohesion: 0.60
Nodes (5): die(), refresh(), install.sh script, step(), usage()

### Community 116 - "TestFramework.h"
Cohesion: 0.15
Nodes (11): Result, error, ok, output, captured(), PythonHost::exec(), PythonHost::runScript(), Case (+3 more)

### Community 117 - ".redrawAll"
Cohesion: 0.09
Nodes (9): NavPreset, Fusion, SolidWorks, Tinkercad, Viewport::setCurvatureComb(), Viewport::clearDragArrow(), Viewport::clearSecondArrow(), Viewport::setInteractor() (+1 more)

### Community 119 - "UserParameter"
Cohesion: 0.33
Nodes (6): UserParameter, comment, expression, name, unit, value

### Community 120 - "Viewport.h"
Cohesion: 0.10
Nodes (6): QLabel, Profile, area, face, x, y

### Community 121 - "SelectionBox"
Cohesion: 0.28
Nodes (3): SelectionBox, crossing, rect()

### Community 123 - "BooleanOp"
Cohesion: 0.50
Nodes (4): BooleanOp, Cut, Intersect, Join

### Community 124 - "MassProperties"
Cohesion: 0.50
Nodes (4): MassProperties, area, centerOfMass, volume

### Community 126 - "ThreadInfo"
Cohesion: 0.50
Nodes (4): ThreadInfo, diameter, internal, pitch

### Community 128 - "ChamferType"
Cohesion: 0.67
Nodes (3): ChamferType, DistanceAngle, TwoDistances

### Community 129 - "Inputs"
Cohesion: 0.09
Nodes (17): Inputs, Coil, def_, ConstructPlane, def_, kind_, Joint, asBuilt_ (+9 more)

### Community 140 - "ChainSegment"
Cohesion: 0.67
Nodes (3): ChainSegment, entity, forward

### Community 141 - "Tool"
Cohesion: 0.11
Nodes (7): SketchEditor::SketchEditor(), edges, Tool, op, shape, target, type

### Community 142 - "SplineHandle"
Cohesion: 0.25
Nodes (8): SplineHandle, arm, index, set, tx, ty, x, y

### Community 145 - "BodyFrame"
Cohesion: 0.13
Nodes (16): BodyFrame, diag, dx, dy, dz, x0, y0, z0 (+8 more)

### Community 149 - "BRepBody"
Cohesion: 0.29
Nodes (3): bindAdsk(), BRepBody, index

## Knowledge Gaps
- **813 isolated node(s):** `ok`, `output`, `error`, `isReal`, `real` (+808 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 1576 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **26 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `optional` connect `optional` to `Viewport`, `MainWindow`, `SketchEditor`, `DocumentError`, `Kernel.cpp`, `Io.cpp`, `Parser`, `InputDef`, `SketchEditor.cpp`, `PhysicalMaterial`, `ViewportSketch.cpp`, `DocCommands.cpp`, `sketchFor`, `SketchOps.cpp`, `SketchGeometry.cpp`, `AnalysisSettings`, `Document.cpp`, `SketchEditor.cpp`, `CommandDialog.cpp`, `Session`, `Unit`, `Feature`, `ViewportArrow.cpp`, `Vec3`, `CommandDialog::CommandDialog`, `CommandDialog::CommandDialog`, `SketchCurves.cpp`, `MainWindowTools.cpp`, `Expression.cpp`, `ReplayStep`, `MainWindowArrow.cpp`, `ParamSet`, `QPointF`, `Viewport.h`?**
  _High betweenness centrality (0.141) - this node is a cross-community bridge._
- **What connects `ok`, `output`, `error` to the rest of the system?**
  _813 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Viewport` be split into smaller, more focused modules?**
  _Cohesion score 0.014071381977448514 - nodes in this community are weakly interconnected._
- **Why does `Viewport` connect `Viewport` to `.rebuild`, `MainWindowArrow.cpp`, `Unit`, `MainWindow`, `Viewport.cpp`, `ViewportArrow.cpp`, `optional`, `AnalysisSettings`, `AnalysisSettings`, `SketchDisplay`, `QMouseEvent`, `SketchCurves.cpp`, `.redrawAll`, `.toPixels`, `Viewport.h`, `SelectionBox`, `SketchPalette`, `QTimer`?**
  _High betweenness centrality (0.123) - this node is a cross-community bridge._
- **Should `Icons.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.05317485142320926 - nodes in this community are weakly interconnected._
- **Why does `SketchEditor` connect `SketchEditor` to `Viewport`, `Constraint`, `Unit`, `QPointF`, `optional`, `Display`, `Pick`, `Tool`, `QMouseEvent`, `Kind`, `SketchEditor.cpp`, `SketchEditor.cpp`, `Snap`, `MainWindowTools.cpp`, `Session`?**
  _High betweenness centrality (0.099) - this node is a cross-community bridge._
- **Should `tsr` be split into smaller, more focused modules?**
  _Cohesion score 0.03368083400160385 - nodes in this community are weakly interconnected._