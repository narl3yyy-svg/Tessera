# Graph Report - tessera  (2026-11-17)

## Corpus Check
- 421 files · ~280,327 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 71 file(s) not represented in the graph (top: .drive 63, (none) 5, .cmake 1)

## Summary
- 3963 nodes · 10185 edges · 135 communities (109 shown, 26 thin omitted)
- Extraction: 85% EXTRACTED · 15% INFERRED · 0% AMBIGUOUS · INFERRED: 1562 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `54fa9fe4`
- Run `git rev-parse HEAD` and compare to check if the graph is stale.
- Run `graphify update .` after code changes (no API cost).

## Community Hubs (Navigation)
- Viewport
- Icons.cpp
- Session.cpp
- MainWindow
- run_oracle.py
- NewComponent
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
- CommandError
- Document
- Snap
- Affine
- ViewportSketch.cpp
- SketchPalette
- Constraint
- Inputs
- Command
- Colors
- KernelError
- TEST
- MainWindowSketch.cpp
- ParameterCompleter
- Pick
- Document::recompute
- MainWindow.cpp
- solve
- QObject
- SketchGeometry.cpp
- ConstraintType
- AdskModule.cpp
- optional
- Column
- Zip.cpp
- AnalysisSettings
- Sketch
- Document.cpp
- MarkingMenu.cpp
- InputDef
- SketchEditor.cpp
- .toPixels
- Development
- Document.cpp
- Dimension
- BoundingBox
- TsrModule.cpp
- xdrive.py
- CommandDialog.cpp
- Session
- Theme.cpp
- BodyFrame
- CommandRegistry
- Expression.cpp
- TEST
- Theme
- Feature
- InputType
- ParametersDialog.cpp
- ViewportArrow.cpp
- HoleSize
- .mouseMove
- Vec3
- CommandDialog::CommandDialog
- math
- CommandDialog::CommandDialog
- SketchDisplay
- Kind
- Measurement
- SketchCurves.cpp
- Level
- README.md
- .showDialog
- test_feature_pattern.py
- QDialog
- test_text_box_path.py
- FileFormat
- Known differences still to build
- Unit
- ReplayStep
- src/main.cpp
- MainWindowArrow.cpp
- FakeDoc
- ModelParameter
- .openMarkingMenu
- Viewport::setDragArrow
- Document::load
- UserParameter
- test_rigid_group.py
- Entity
- Display
- main
- Kernel.h
- Known gaps
- .redrawAll
- SectionState
- uninstall.sh
- install.sh
- TestFramework.h
- MainWindow::MainWindow
- SelectionBox
- test_incremental_replay.py
- TEST
- QScrollArea
- Joint
- LAB_NOTES.md
- build.sh
- live-test.sh
- SplineHandle
- ChainSegment
- BodyFrame
- EntityType
- test_extrude_participants.py
- Value.h
- Architecture
- cmath

## God Nodes (most connected - your core abstractions)
1. `Viewport` - 286 edges
2. `SketchEditor` - 198 edges
3. `MainWindow` - 189 edges
4. `Inputs` - 161 edges
5. `render()` - 124 edges
6. `Document` - 122 edges
7. `CommandContext` - 116 edges
8. `CommandDialog` - 98 edges
9. `CommandError` - 70 edges
10. `Command` - 68 edges

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

## Communities (135 total, 26 thin omitted)

### Community 0 - "Viewport"
Cohesion: 0.01
Nodes (79): view_, QLineEdit, Viewport, analysis_, analysisObjects_, appliedGridStep_, arrowBoxes_, arrowDragging_ (+71 more)

### Community 1 - "Icons.cpp"
Cohesion: 0.05
Nodes (127): accessibilityIcon(), appearanceIcon(), arc3Icon(), arcIcon(), arcTangentIcon(), arrow(), axisIcon(), boundaryFillIcon() (+119 more)

### Community 2 - "Session.cpp"
Cohesion: 0.06
Nodes (49): CommandSession, inputs_, expressionKey(), checkInputValue(), CommandContext::evaluateExpression(), CommandDef::input(), CommandSession::applyInTransaction(), CommandSession::cancel() (+41 more)

### Community 4 - "MainWindow"
Cohesion: 0.03
Nodes (68): CommandDialog, MainWindow, active_, appearanceColour_, appearanceFaces_, appearancePanel_, arrowInput_, arrowInput2_ (+60 more)

### Community 5 - "run_oracle.py"
Cohesion: 0.08
Nodes (54): add_point(), arc_poly(), body_at(), body_list(), build_sketch(), chain(), circumcentre(), cm() (+46 more)

### Community 6 - "NewComponent"
Cohesion: 0.15
Nodes (7): AddUserParameter, def_, isIdentifier(), NewComponent, def_, RigidGroup, def_

### Community 7 - "Document"
Cohesion: 0.03
Nodes (14): Document, effects_, lastReplayed_, lastReused_, modified_, pendingTools_, registry_, replaying_ (+6 more)

### Community 8 - "Viewport.cpp"
Cohesion: 0.04
Nodes (16): glide(), hiddenColour(), keys(), qc(), QtFrameBuffer, rgb(), sharpEdges(), Style (+8 more)

### Community 9 - "SketchEditor"
Cohesion: 0.03
Nodes (54): PlaneEdges, arcs, curves, segments, vertices, SketchEditor, arcDrag_, arcDragMoved_ (+46 more)

### Community 10 - "DocumentError"
Cohesion: 0.10
Nodes (27): DocumentError, checkViewName(), Document::abortTransaction(), Document::addBody(), Document::addNamedView(), Document::addUserParameter(), Document::commitTransaction(), Document::openTransaction() (+19 more)

### Community 11 - "optional"
Cohesion: 0.11
Nodes (7): Document, Profile, area, face, x, y, tmp()

### Community 12 - "Kernel.cpp"
Cohesion: 0.04
Nodes (4): isoCoarsePitch(), topologyCounts(), touching(), wrapOntoCylinder()

### Community 13 - "AnalysisSettings"
Cohesion: 0.11
Nodes (18): AnalysisKind, Accessibility, CurvatureMap, Draft, Isocurve, MinimumRadius, None, Zebra (+10 more)

### Community 14 - "Kind"
Cohesion: 0.06
Nodes (29): ConstructPlane, def_, kind_, EdgeFeature, def_, kind_, Kind, Angle (+21 more)

### Community 15 - "QMouseEvent"
Cohesion: 0.07
Nodes (9): QKeyEvent, QLabel, QMouseEvent, ViewInteractor, Viewport::arrowMouseMove(), Viewport::arrowMousePress(), Viewport::arrowMouseRelease(), Viewport::dragArrowForTest() (+1 more)

### Community 16 - "CommandDialog"
Cohesion: 0.05
Nodes (36): CommandDialog, bodiesId_, bodiesLabel_, bodyInput_, buttons_, cellsId_, cellsList_, cmd_ (+28 more)

### Community 17 - "Io.cpp"
Cohesion: 0.10
Nodes (19): MainWindow::print3d(), NamedShape, compoundOf(), exportShapes(), fmt(), formatForPath(), fromBrep(), importShape() (+11 more)

### Community 18 - "Parser"
Cohesion: 0.18
Nodes (14): Quantity, angle, length, value, describe(), isIdentChar(), isIdentStart(), Parser (+6 more)

### Community 19 - "CommandError"
Cohesion: 0.10
Nodes (35): CommandError, getBool(), getReal(), applyOperation(), applyToParticipants(), bodyCentre(), bodyName(), boundaryFillCells() (+27 more)

### Community 21 - "Document"
Cohesion: 0.24
Nodes (7): ConstructAxisPoint, def_, kind_, jointOrigin(), JointPick, frame, revolveAxis()

### Community 22 - "Snap"
Cohesion: 0.11
Nodes (18): Snap, alignX, alignY, bodyArc, bodySegment, entity, fromX, fromY (+10 more)

### Community 24 - "Affine"
Cohesion: 0.13
Nodes (13): Affine, a, b, d, e, Builder, byPlace_, k_ (+5 more)

### Community 25 - "ViewportSketch.cpp"
Cohesion: 0.09
Nodes (6): faceStyle(), lineStyle(), rgb(), Viewport::lookAt(), Viewport::planePoint(), Viewport::toWidget()

### Community 26 - "SketchPalette"
Cohesion: 0.06
Nodes (26): flatButton(), QCheckBox, QLabel, QToolButton, QWidget, SketchEditor, SketchPalette, body_ (+18 more)

### Community 27 - "Constraint"
Cohesion: 0.08
Nodes (21): Constraint, driven, entities, expression, hasLabel, labelX, labelY, name (+13 more)

### Community 28 - "Inputs"
Cohesion: 0.06
Nodes (19): CommandContext, Inputs, CommandSession::CommandSession(), getInt(), checkBody(), checkPattern(), defaultBody(), Hole (+11 more)

### Community 29 - "Command"
Cohesion: 0.03
Nodes (75): Adding a tool, Command, CommandDef, feature, icon, id, inputs, name (+67 more)

### Community 30 - "Colors"
Cohesion: 0.07
Nodes (28): Colors, base, border, cubeBox, cubeText, errorBackground, grid, gridMajor (+20 more)

### Community 31 - "KernelError"
Cohesion: 0.22
Nodes (34): KernelError, asSolid(), boolean(), boundaryCells(), chamfer(), chamferEx(), deleteFaces(), draft() (+26 more)

### Community 32 - "TEST"
Cohesion: 0.08
Nodes (38): Placement, angle, cx, cy, dx, dy, scale, at() (+30 more)

### Community 33 - "MainWindowSketch.cpp"
Cohesion: 0.10
Nodes (12): MainWindow::cancelSketch(), MainWindow::editSketch(), MainWindow::finishSketch(), MainWindow::onProfileClicked(), MainWindow::originalShape(), MainWindow::sketchPalette(), MainWindow::sketchVisible(), MainWindow::startSketch() (+4 more)

### Community 34 - "ParameterCompleter"
Cohesion: 0.12
Nodes (8): ParameterCompleter, completer_, edit_, names_, ParameterCompleter::ParameterCompleter(), public, QCompleter, QLineEdit

### Community 35 - "Pick"
Cohesion: 0.12
Nodes (15): Pick, bodyArc, bodyPoint, bodySegment, hit, midpointOf, onEntity, onXAxis (+7 more)

### Community 36 - "Document::recompute"
Cohesion: 0.17
Nodes (8): Document::expressionEnv(), Document::recompute(), Document::recordFeature(), Document::removeFeature(), Document::setFeatureInputs(), Document::setFeatureSuppressed(), featureData(), toJson()

### Community 37 - "MainWindow.cpp"
Cohesion: 0.08
Nodes (5): commandIcon(), qs(), MainWindow::applySection(), cachedProfiles(), keyOf()

### Community 38 - "solve"
Cohesion: 0.11
Nodes (13): addConstraintChecked(), Layout, n, px, py, rad, makeLayout(), pack() (+5 more)

### Community 39 - "QObject"
Cohesion: 0.13
Nodes (4): QObject, SketchEditor::SketchEditor(), edges, type

### Community 40 - "SketchGeometry.cpp"
Cohesion: 0.07
Nodes (18): conditionedSpline(), curve(), curves(), entityCurves(), G2End, d1, d2, set (+10 more)

### Community 41 - "ConstraintType"
Cohesion: 0.07
Nodes (27): ConstraintType, Angle, Coincident, Collinear, Concentric, Curvature, Diameter, Distance (+19 more)

### Community 42 - "AdskModule.cpp"
Cohesion: 0.09
Nodes (16): Application, bindAdsk(), BRepBodies, BRepBody, index, Component, Design, Product (+8 more)

### Community 43 - "optional"
Cohesion: 0.14
Nodes (4): Hit, index, kind, optional

### Community 45 - "Column"
Cohesion: 0.25
Nodes (8): Column, kComment, kExpression, kName, kParameter, kStar, kUnit, kValue

### Community 46 - "Zip.cpp"
Cohesion: 0.18
Nodes (13): Entry, data, name, ZipError, crc32(), deflateRaw(), get16(), get32() (+5 more)

### Community 47 - "AnalysisSettings"
Cohesion: 0.08
Nodes (20): DragArrow, base, dir, radius, ref, ring, value, PendingLook (+12 more)

### Community 48 - "Sketch"
Cohesion: 0.05
Nodes (34): Point, x, y, z, Sketch, constraints, entities, points (+26 more)

### Community 49 - "Document.cpp"
Cohesion: 0.10
Nodes (31): ConstructionPlane, name, spec, SketchRecord, data, name, offset, plane (+23 more)

### Community 50 - "MarkingMenu.cpp"
Cohesion: 0.06
Nodes (26): UiCommand, enabled, icon, id, name, panel, run, shortcut (+18 more)

### Community 51 - "InputDef"
Cohesion: 0.09
Nodes (22): InputDef, choices, defaultValue, id, label, max, min, minExclusive (+14 more)

### Community 52 - "SketchEditor.cpp"
Cohesion: 0.11
Nodes (5): angleInArc(), ccwContains(), circumcircle(), lineEntity(), segDistance()

### Community 54 - "Development"
Cohesion: 0.40
Nodes (4): Build, Conventions, Development, Tests

### Community 55 - "Document.cpp"
Cohesion: 0.07
Nodes (20): bodyNumber(), Document::axisFrame(), Document::bodyShapes(), Document::effectOf(), Document::evaluate(), Document::historyMarker(), Document::nameFeatureParameters(), Document::nextAxisName() (+12 more)

### Community 56 - "Dimension"
Cohesion: 0.50
Nodes (4): Dimension, Angle, Length, Unitless

### Community 57 - "BoundingBox"
Cohesion: 0.20
Nodes (15): BoundingBox, max, min, WallSide, Center, Side1, Side2, extendedWire() (+7 more)

### Community 58 - "TsrModule.cpp"
Cohesion: 0.17
Nodes (4): bindTsr(), fromPy(), toPy(), typeName()

### Community 59 - "xdrive.py"
Cohesion: 0.28
Nodes (15): button(), canvas(), click(), drag(), flush(), geometry(), key(), keycode() (+7 more)

### Community 62 - "Session"
Cohesion: 0.07
Nodes (6): Session, commands_, doc_, listeners_, nextListener_, path_

### Community 63 - "Theme.cpp"
Cohesion: 0.19
Nodes (6): setIconTheme(), darkColors(), darkPalette(), darkStyleSheet(), lightColors(), lightStyleSheet()

### Community 64 - "BodyFrame"
Cohesion: 0.09
Nodes (32): boundingBox(), completeEdgeReferences(), completeFaceReferences(), decode(), decodeFaces(), dot(), edgeReference(), EdgeSig (+24 more)

### Community 65 - "CommandRegistry"
Cohesion: 0.12
Nodes (4): CommandRegistry, cmds_, CommandRegistry::add(), TEST()

### Community 66 - "Expression.cpp"
Cohesion: 0.18
Nodes (14): ExpressionEnv, lengthUnit, lookup, ExpressionError, evaluateExpression(), evaluateQuantity(), expressionReferences(), isConstantName() (+6 more)

### Community 68 - "Theme"
Cohesion: 0.20
Nodes (5): MainWindow::showPreferences(), Theme, colors_, public, styled_

### Community 69 - "Feature"
Cohesion: 0.11
Nodes (16): Feature, commandId, error, id, inputs, name, parameterNames, rolledBack (+8 more)

### Community 70 - "InputType"
Cohesion: 0.12
Nodes (17): InputType, Axis, Bodies, Body, Bool, Choice, Edges, Faces (+9 more)

### Community 71 - "ParametersDialog.cpp"
Cohesion: 0.08
Nodes (16): number(), ParametersDialog, building_, error_, filter_, listener_, ParametersDialog::ParametersDialog(), public (+8 more)

### Community 73 - "ViewportArrow.cpp"
Cohesion: 0.05
Nodes (32): Viewport::frontEdgeOwner(), packed(), ramp(), shade(), Viewport::buildAnalysis(), rgb(), segmentDistance(), Viewport::arrowAt() (+24 more)

### Community 74 - "HoleSize"
Cohesion: 0.50
Nodes (4): HoleSize, modeled, pitch, radius

### Community 75 - ".mouseMove"
Cohesion: 0.13
Nodes (11): ext(), fixedColor(), freeColor(), HandleHit, back, index, spline, qc() (+3 more)

### Community 76 - "Vec3"
Cohesion: 0.17
Nodes (22): SurfacePoint, normal, point, Vec3, containsPoint(), edgeMidpoint(), edgesNear(), extrudeToFace() (+14 more)

### Community 77 - "CommandDialog::CommandDialog"
Cohesion: 0.13
Nodes (5): CommandDialog::CommandDialog(), BoundaryCell, ref, shape, volume

### Community 78 - "math"
Cohesion: 0.06
Nodes (3): dist(), check_regular(), dist_to_line()

### Community 79 - "CommandDialog::CommandDialog"
Cohesion: 0.15
Nodes (5): ExpressionSpinBox, eval_, expression_, shown_, formatNumber()

### Community 80 - "SketchDisplay"
Cohesion: 0.12
Nodes (11): ProfileObject, index, sketch, SketchDisplay, construction, curves, fixedCurves, frame (+3 more)

### Community 81 - "Kind"
Cohesion: 0.09
Nodes (21): HudField, edit, editing, kind, locked, value, Kind, Angle (+13 more)

### Community 82 - "Measurement"
Cohesion: 0.13
Nodes (14): Kind, Angle, Area, Length, Volume, Measurement, from, hasLine (+6 more)

### Community 83 - "SketchCurves.cpp"
Cohesion: 0.13
Nodes (19): crossings(), crossingsOf(), Curve2d, curve2d(), periodic, t0, t1, endIsFree() (+11 more)

### Community 85 - "Level"
Cohesion: 0.16
Nodes (13): debug(), error(), info(), Level, Debug, Error, Info, Warning (+5 more)

### Community 86 - "README.md"
Cohesion: 0.13
Nodes (11): Reference parts, Fusion feature checklist, Roadmap, Contents, Development, Features, Install, License (+3 more)

### Community 90 - "QDialog"
Cohesion: 0.06
Nodes (30): QDialog, MainWindow::checkInterference(), MainWindow::chooseUnits(), MainWindow::driveJoints(), MainWindow::editMaterial(), MainWindow::exportDesign(), MainWindow::formatLength(), MainWindow::gridSettings() (+22 more)

### Community 92 - "FileFormat"
Cohesion: 0.17
Nodes (12): FileFormat, Brep, Iges, Obj, Step, Stl, ThreeMF, FormatInfo (+4 more)

### Community 93 - "Known differences still to build"
Cohesion: 0.15
Nodes (12): Data and files, Findings from the videos, Fusion study list, Interface, Known differences still to build, Navigation and display, Selection and the canvas, Sketch (+4 more)

### Community 94 - "Unit"
Cohesion: 0.12
Nodes (14): MainWindow::lengthUnit(), Unit, Centimeter, Degree, Foot, Inch, Meter, Millimeter (+6 more)

### Community 95 - "ReplayStep"
Cohesion: 0.05
Nodes (39): Body, color, display, faceColors, material, name, shape, Component (+31 more)

### Community 96 - "src/main.cpp"
Cohesion: 0.08
Nodes (7): QAbstractButton, QAction, grabWindowWithPanels(), writeLiveGeometry(), MarkingMenu, enabled, public

### Community 97 - "MainWindowArrow.cpp"
Cohesion: 0.13
Nodes (8): ArrowPlacement, base, dir, edgePlacement(), facesPlacement(), MainWindow::attachArrowCompleters(), MainWindow::patternCentre(), MainWindow::pickedFaces()

### Community 98 - "FakeDoc"
Cohesion: 0.17
Nodes (6): FakeDoc, aborts, commits, items, open, snapshot

### Community 99 - "ModelParameter"
Cohesion: 0.08
Nodes (34): ModelParameter, angle, expression, input, label, name, owner, unit (+26 more)

### Community 100 - ".openMarkingMenu"
Cohesion: 0.13
Nodes (4): MainWindow::beginSketch(), MainWindow::buildSketchTab(), MainWindow::enterSketchMode(), QTimer

### Community 101 - "Viewport::setDragArrow"
Cohesion: 0.18
Nodes (4): Viewport::DragArrow::handle(), Viewport::emitArrow(), Viewport::setDragArrow(), Viewport::setDragRing()

### Community 102 - "Document::load"
Cohesion: 0.11
Nodes (7): doc_(), Document::Document(), Document::ocafBytes(), Document::reevaluateParameters(), ocafApplication(), Document::load(), Document::save()

### Community 103 - "UserParameter"
Cohesion: 0.33
Nodes (6): UserParameter, comment, expression, name, unit, value

### Community 106 - "Entity"
Cohesion: 0.09
Nodes (20): Entity, a, b, center, construction, fit, handles, included (+12 more)

### Community 107 - "Display"
Cohesion: 0.25
Nodes (7): Display, constraints, construction, dimensions, points, profiles, projected

### Community 108 - "main"
Cohesion: 0.27
Nodes (6): listCommands(), main(), usage(), main(), smoke(), key

### Community 110 - "Kernel.h"
Cohesion: 0.07
Nodes (35): Axis, X, Y, Z, BooleanOp, Cut, Intersect, Join (+27 more)

### Community 111 - "Known gaps"
Cohesion: 0.15
Nodes (13): 3D Sketch, Appearance, Boundary Fill, Curvature (G2), Emboss, Face patterns, Include 3D Geometry, Known gaps (+5 more)

### Community 112 - ".redrawAll"
Cohesion: 0.09
Nodes (9): NavPreset, Fusion, SolidWorks, Tinkercad, Viewport::setCurvatureComb(), Viewport::clearDragArrow(), Viewport::clearSecondArrow(), Viewport::setInteractor() (+1 more)

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
Cohesion: 0.17
Nodes (9): Result, error, ok, output, captured(), PYBIND11_EMBEDDED_MODULE(), PythonHost::exec(), PythonHost::PythonHost() (+1 more)

### Community 120 - "MainWindow::MainWindow"
Cohesion: 0.10
Nodes (6): PythonHost, retintIcons(), setIcon(), MainWindow::MainWindow(), MainWindow::exitSketchMode(), MainWindow::editAppearance()

### Community 124 - "TEST"
Cohesion: 0.20
Nodes (3): slurp(), TEST(), tmp()

### Community 129 - "Joint"
Cohesion: 0.19
Nodes (5): Joint, asBuilt_, def_, Sweep, def_

### Community 142 - "SplineHandle"
Cohesion: 0.25
Nodes (8): SplineHandle, arm, index, set, tx, ty, x, y

### Community 144 - "ChainSegment"
Cohesion: 0.67
Nodes (3): ChainSegment, entity, forward

### Community 145 - "BodyFrame"
Cohesion: 0.14
Nodes (15): BodyFrame, diag, dx, dy, dz, x0, y0, z0 (+7 more)

### Community 147 - "EntityType"
Cohesion: 0.17
Nodes (8): CommandRegistry::all(), EntityType, Arc, Circle, Ellipse, Line, Spline, isRound()

### Community 152 - "Architecture"
Cohesion: 0.40
Nodes (4): Architecture, How a command works, The document, Units

### Community 155 - "cmath"
Cohesion: 0.08
Nodes (12): Rect, rect(), p, Case, fn, name, fail(), Failure (+4 more)

## Knowledge Gaps
- **808 isolated node(s):** `ok`, `output`, `error`, `isReal`, `real` (+803 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 1546 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **26 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `Viewport` connect `Viewport` to `MainWindow`, `.openMarkingMenu`, `Viewport::setDragArrow`, `Viewport.cpp`, `ViewportArrow.cpp`, `optional`, `optional`, `AnalysisSettings`, `AnalysisSettings`, `SketchDisplay`, `QMouseEvent`, `.redrawAll`, `SketchCurves.cpp`, `.initializeGL`, `.toPixels`, `SelectionBox`, `QDialog`?**
  _High betweenness centrality (0.133) - this node is a cross-community bridge._
- **What connects `ok`, `output`, `error` to the rest of the system?**
  _808 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Viewport` be split into smaller, more focused modules?**
  _Cohesion score 0.013855001742767515 - nodes in this community are weakly interconnected._
- **Why does `optional` connect `optional` to `Viewport`, `MainWindow`, `SketchEditor`, `optional`, `Kernel.cpp`, `QMouseEvent`, `CommandDialog`, `Io.cpp`, `Parser`, `CommandDialog.cpp`, `ViewportSketch.cpp`, `Inputs`, `Command`, `TEST`, `SketchGeometry.cpp`, `AnalysisSettings`, `Document.cpp`, `InputDef`, `SketchEditor.cpp`, `CommandDialog.cpp`, `Session`, `Expression.cpp`, `Feature`, `ViewportArrow.cpp`, `Vec3`, `CommandDialog::CommandDialog`, `SketchCurves.cpp`, `Unit`, `ReplayStep`, `MainWindowArrow.cpp`, `ModelParameter`, `Kernel.h`?**
  _High betweenness centrality (0.127) - this node is a cross-community bridge._
- **Should `Icons.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.05435729847494553 - nodes in this community are weakly interconnected._
- **Why does `SketchEditor` connect `SketchEditor` to `Viewport`, `Pick`, `QObject`, `Entity`, `Display`, `.mouseMove`, `optional`, `optional`, `QMouseEvent`, `Kind`, `Entity`, `SketchEditor.cpp`, `Snap`, `Session`, `Constraint`, `Unit`, `ReplayStep`?**
  _High betweenness centrality (0.091) - this node is a cross-community bridge._
- **Should `Session.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.05621621621621622 - nodes in this community are weakly interconnected._