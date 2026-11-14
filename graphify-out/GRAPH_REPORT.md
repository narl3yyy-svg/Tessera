# Graph Report - tessera  (2026-11-13)

## Corpus Check
- 385 files · ~251,760 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 56 file(s) not represented in the graph (top: .drive 48, (none) 5, .cmake 1)

## Summary
- 3664 nodes · 9395 edges · 136 communities (110 shown, 26 thin omitted)
- Extraction: 85% EXTRACTED · 15% INFERRED · 0% AMBIGUOUS · INFERRED: 1443 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `a85267d9`
- Run `git rev-parse HEAD` and compare to check if the graph is stale.
- Run `graphify update .` after code changes (no API cost).

## Community Hubs (Navigation)
- Viewport
- Icons.cpp
- Session.cpp
- tsr
- MainWindow
- run_oracle.py
- .mouseMove
- Document
- Viewport.cpp
- SketchEditor
- Expression.cpp
- optional
- Kernel.cpp
- AnalysisSettings
- Kind
- .openMarkingMenu
- CommandDialog
- Io.cpp
- Parser
- MainWindowTools.cpp
- Known gaps
- Document
- MainWindow.cpp
- Architecture
- Affine
- ViewportSketch.cpp
- SketchPalette
- CommandSession
- Inputs
- string
- Colors
- KernelError
- SketchOps.cpp
- ViewportArrow.cpp
- ParameterCompleter
- Constraint
- .apply
- test_text_box_path.py
- solve
- Snap
- CommandDialog.cpp
- ConstraintType
- AdskModule.cpp
- Pick
- TEST
- Zip.cpp
- AnalysisSettings
- Sketch.cpp
- ParamSet
- MainWindowSketch.cpp
- InputDef
- string
- .toPixels
- ViewportAnalysis.cpp
- Document::recompute
- Command.cpp
- Viewport.h
- Entity
- xdrive.py
- Session
- Theme.cpp
- BodyFrame
- CommandRegistry
- Tool
- BodyFrame
- Theme
- Joint
- ParametersDialog.cpp
- TEST
- curve
- Handle
- InputType
- Vec3
- CommandDialog::CommandDialog
- CommandDialog::CommandDialog
- SketchDisplay
- Command
- Measurement
- SketchCurves.cpp
- UiCommand
- Level
- README.md
- string
- test_feature_pattern.py
- rect
- cachedProfiles
- EntityType
- FileFormat
- Known differences still to build
- MainWindow::MainWindow
- ReplayStep
- bindAdsk
- .press
- FakeDoc
- Icons.h
- MainWindowArrow.cpp
- .add
- sstream
- MarkingMenu
- BoundingBox
- Joints
- SectionState
- Display
- main
- Kernel.h
- TopologyCounts
- UserParameter
- uninstall.sh
- install.sh
- TestFramework.h
- .redrawAll
- Column
- test_incremental_replay.py
- Placement
- ChainSegment
- NewComponent
- Value.h
- Text
- HandleHit
- DocCommands.cpp
- Unit
- LAB_NOTES.md
- src/main.cpp
- build.sh
- live-test.sh
- PYBIND11_EMBEDDED_MODULE
- Point
- SplineHandle

## God Nodes (most connected - your core abstractions)
1. `Viewport` - 251 edges
2. `SketchEditor` - 185 edges
3. `MainWindow` - 180 edges
4. `Inputs` - 148 edges
5. `Document` - 118 edges
6. `render()` - 116 edges
7. `CommandContext` - 108 edges
8. `CommandDialog` - 90 edges
9. `Command` - 65 edges
10. `CommandError` - 60 edges

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

## Communities (136 total, 26 thin omitted)

### Community 0 - "Viewport"
Cohesion: 0.02
Nodes (67): view_, QLineEdit, Viewport, analysis_, analysisObjects_, appliedGridStep_, arrowBoxes_, arrowDragging_ (+59 more)

### Community 1 - "Icons.cpp"
Cohesion: 0.05
Nodes (121): accessibilityIcon(), arc3Icon(), arcIcon(), arcTangentIcon(), arrow(), axisIcon(), box(), breakIcon() (+113 more)

### Community 2 - "Session.cpp"
Cohesion: 0.17
Nodes (24): historyEdit(), plainEdit(), Session::addListener(), Session::addNamedView(), Session::deleteFeature(), Session::deleteNamedView(), Session::deleteParameter(), Session::newDocument() (+16 more)

### Community 4 - "MainWindow"
Cohesion: 0.03
Nodes (64): writeLiveGeometry(), CommandDialog, MainWindow, active_, arrowInput_, arrowInput2_, bodiesBeforeCommand_, combEdges_ (+56 more)

### Community 5 - "run_oracle.py"
Cohesion: 0.08
Nodes (54): add_point(), arc_poly(), body_at(), body_list(), build_sketch(), chain(), circumcentre(), cm() (+46 more)

### Community 6 - ".mouseMove"
Cohesion: 0.15
Nodes (7): ext(), fixedColor(), freeColor(), lineEntity(), qc(), rgb(), wire()

### Community 7 - "Document"
Cohesion: 0.03
Nodes (16): Document, effects_, lastReplayed_, lastReused_, modified_, pendingTools_, registry_, replaying_ (+8 more)

### Community 8 - "Viewport.cpp"
Cohesion: 0.05
Nodes (8): hiddenColour(), keys(), qc(), QKeyEvent, rgb(), sharpEdges(), Viewport::Viewport(), wireColour()

### Community 9 - "SketchEditor"
Cohesion: 0.03
Nodes (58): HudField, edit, editing, kind, locked, value, PlaneEdges, arcs (+50 more)

### Community 10 - "Expression.cpp"
Cohesion: 0.14
Nodes (16): ExpressionEnv, lengthUnit, lookup, ExpressionError, evaluateExpression(), evaluateQuantity(), expressionReferences(), isConstantName() (+8 more)

### Community 11 - "optional"
Cohesion: 0.12
Nodes (5): optional, CommandRegistry::all(), Document, fail(), Failure

### Community 12 - "Kernel.cpp"
Cohesion: 0.04
Nodes (5): isoCoarsePitch(), massProperties(), measure(), polygonToCircleLoft(), topologyCounts()

### Community 13 - "AnalysisSettings"
Cohesion: 0.11
Nodes (18): AnalysisKind, Accessibility, CurvatureMap, Draft, Isocurve, MinimumRadius, None, Zebra (+10 more)

### Community 14 - "Kind"
Cohesion: 0.07
Nodes (26): ConstructPlane, def_, kind_, EdgeFeature, def_, kind_, Kind, Angle (+18 more)

### Community 15 - ".openMarkingMenu"
Cohesion: 0.09
Nodes (5): MainWindow::buildSketchTab(), MainWindow::enterSketchMode(), MainWindow::onProfileClicked(), QTimer, Viewport::selectArrowValue()

### Community 16 - "CommandDialog"
Cohesion: 0.05
Nodes (31): CommandDialog, bodiesId_, bodiesLabel_, bodyInput_, buttons_, cmd_, conditional_, edgesId_ (+23 more)

### Community 17 - "Io.cpp"
Cohesion: 0.10
Nodes (19): MainWindow::print3d(), NamedShape, compoundOf(), exportShapes(), fmt(), formatForPath(), fromBrep(), importShape() (+11 more)

### Community 18 - "Parser"
Cohesion: 0.18
Nodes (14): Quantity, angle, length, value, describe(), isIdentChar(), isIdentStart(), Parser (+6 more)

### Community 19 - "MainWindowTools.cpp"
Cohesion: 0.06
Nodes (27): QDialog, MainWindow::checkInterference(), MainWindow::chooseUnits(), MainWindow::driveJoints(), MainWindow::exportDesign(), MainWindow::formatLength(), MainWindow::gridSettings(), MainWindow::insertFile() (+19 more)

### Community 20 - "Known gaps"
Cohesion: 0.33
Nodes (5): Include 3D Geometry, Known gaps, Sketch text, Splines and conics, Visual styles

### Community 21 - "Document"
Cohesion: 0.21
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

### Community 27 - "CommandSession"
Cohesion: 0.12
Nodes (9): CommandSession, inputs_, CommandRegistry::find(), CommandRegistry::run(), OwnedCommand, owned, OwningCommandSession, Session::begin() (+1 more)

### Community 28 - "Inputs"
Cohesion: 0.08
Nodes (20): CommandContext, CommandError, Inputs, CommandSession::CommandSession(), getBool(), getInt(), applyOperation(), bodyCentre() (+12 more)

### Community 29 - "string"
Cohesion: 0.07
Nodes (45): DocumentError, SketchRecord, data, name, offset, plane, checkViewName(), Document::abortTransaction() (+37 more)

### Community 30 - "Colors"
Cohesion: 0.07
Nodes (28): Colors, base, border, cubeBox, cubeText, errorBackground, grid, gridMajor (+20 more)

### Community 31 - "KernelError"
Cohesion: 0.25
Nodes (28): KernelError, asSolid(), boolean(), chamfer(), chamferEx(), deleteFaces(), draft(), extrude() (+20 more)

### Community 32 - "SketchOps.cpp"
Cohesion: 0.20
Nodes (27): at(), chainOf(), chamferCorner(), circularPattern(), copyEntities(), cornerAt(), cross(), dot() (+19 more)

### Community 33 - "ViewportArrow.cpp"
Cohesion: 0.06
Nodes (20): MarkingMenu::mouseMoveEvent(), QMouseEvent, ViewInteractor, Viewport::frontEdgeOwner(), rgb(), segmentDistance(), Viewport::arrowAt(), Viewport::arrowMouseMove() (+12 more)

### Community 34 - "ParameterCompleter"
Cohesion: 0.13
Nodes (9): QObject, ParameterCompleter, completer_, edit_, names_, ParameterCompleter::ParameterCompleter(), public, QCompleter (+1 more)

### Community 35 - "Constraint"
Cohesion: 0.08
Nodes (20): Constraint, driven, entities, expression, hasLabel, labelX, labelY, name (+12 more)

### Community 36 - ".apply"
Cohesion: 0.21
Nodes (8): Coil, def_, Extrude, def_, planeOf(), x, y, z

### Community 38 - "solve"
Cohesion: 0.18
Nodes (13): set, addConstraintChecked(), Layout, n, px, py, rad, makeLayout() (+5 more)

### Community 39 - "Snap"
Cohesion: 0.05
Nodes (35): Hit, index, kind, Kind, Angle, BodyEdge, BodyVertex, Count (+27 more)

### Community 41 - "ConstraintType"
Cohesion: 0.08
Nodes (24): ConstraintType, Angle, Coincident, Collinear, Concentric, Diameter, Distance, Equal (+16 more)

### Community 42 - "AdskModule.cpp"
Cohesion: 0.09
Nodes (17): Application, BRepBodies, Component, Design, Product, raiseIfError(), UserParameter, name (+9 more)

### Community 43 - "Pick"
Cohesion: 0.13
Nodes (14): Pick, bodyArc, bodyPoint, bodySegment, hit, midpointOf, onEntity, onXAxis (+6 more)

### Community 46 - "Zip.cpp"
Cohesion: 0.11
Nodes (14): Entry, data, name, ZipError, crc32(), get16(), get32(), put16() (+6 more)

### Community 47 - "AnalysisSettings"
Cohesion: 0.10
Nodes (16): DragArrow, base, dir, radius, ref, ring, value, PendingLook (+8 more)

### Community 48 - "Sketch.cpp"
Cohesion: 0.09
Nodes (17): SplineKind, Conic, Control, Fit, entityTypeName(), isDimension(), Sketch::addConstraint(), Sketch::addSpline() (+9 more)

### Community 49 - "ParamSet"
Cohesion: 0.07
Nodes (34): ModelParameter, angle, expression, input, label, name, owner, unit (+26 more)

### Community 50 - "MainWindowSketch.cpp"
Cohesion: 0.07
Nodes (14): MainWindow::cancelSketch(), MainWindow::editSketch(), MainWindow::finishSketch(), MainWindow::onEdgeClicked(), MainWindow::originalShape(), MainWindow::sketchPalette(), MainWindow::sketchVisible(), MainWindow::startSketch() (+6 more)

### Community 51 - "InputDef"
Cohesion: 0.09
Nodes (21): InputDef, choices, defaultValue, id, label, max, min, minExclusive (+13 more)

### Community 52 - "string"
Cohesion: 0.11
Nodes (11): checkBody(), checkPattern(), Hole, def_, Pipe, def_, Revolve, def_ (+3 more)

### Community 54 - "ViewportAnalysis.cpp"
Cohesion: 0.14
Nodes (5): packed(), ramp(), shade(), Viewport::buildAnalysis(), f

### Community 55 - "Document::recompute"
Cohesion: 0.16
Nodes (9): Document::expressionEnv(), Document::openTransaction(), Document::recompute(), Document::recordFeature(), Document::removeFeature(), Document::setFeatureInputs(), Document::setFeatureSuppressed(), featureData() (+1 more)

### Community 56 - "Command.cpp"
Cohesion: 0.22
Nodes (11): expressionKey(), checkInputValue(), CommandContext::evaluateExpression(), CommandDef::input(), CommandSession::applyInTransaction(), CommandSession::cancel(), CommandSession::execute(), CommandSession::preview() (+3 more)

### Community 57 - "Viewport.h"
Cohesion: 0.10
Nodes (6): QLabel, Profile, area, face, x, y

### Community 58 - "Entity"
Cohesion: 0.12
Nodes (12): Entity, a, b, center, construction, fit, handles, included (+4 more)

### Community 59 - "xdrive.py"
Cohesion: 0.28
Nodes (15): button(), canvas(), click(), drag(), flush(), geometry(), key(), keycode() (+7 more)

### Community 62 - "Session"
Cohesion: 0.08
Nodes (6): Session, commands_, doc_, listeners_, nextListener_, path_

### Community 63 - "Theme.cpp"
Cohesion: 0.19
Nodes (6): setIconTheme(), darkColors(), darkPalette(), darkStyleSheet(), lightColors(), lightStyleSheet()

### Community 64 - "BodyFrame"
Cohesion: 0.10
Nodes (31): completeEdgeReferences(), completeFaceReferences(), decode(), decodeFaces(), dot(), edgeReference(), EdgeSig, full (+23 more)

### Community 65 - "CommandRegistry"
Cohesion: 0.10
Nodes (7): CommandRegistry, cmds_, CommandRegistry::add(), EditFeature, def_, featureId_, TEST()

### Community 66 - "Tool"
Cohesion: 0.16
Nodes (6): SketchEditor::SketchEditor(), edges, Tool, op, shape, target

### Community 67 - "BodyFrame"
Cohesion: 0.14
Nodes (15): BodyFrame, diag, dx, dy, dz, x0, y0, z0 (+7 more)

### Community 68 - "Theme"
Cohesion: 0.22
Nodes (4): Theme, colors_, public, styled_

### Community 69 - "Joint"
Cohesion: 0.23
Nodes (4): Joint, def_, Sweep, def_

### Community 71 - "ParametersDialog.cpp"
Cohesion: 0.08
Nodes (16): number(), ParametersDialog, building_, error_, filter_, listener_, ParametersDialog::ParametersDialog(), public (+8 more)

### Community 72 - "TEST"
Cohesion: 0.09
Nodes (3): param(), TEST(), tmp()

### Community 73 - "curve"
Cohesion: 0.31
Nodes (10): curve(), curves(), entityCurves(), interiorPoint(), profileAt(), profiles(), splineHandles(), textShape() (+2 more)

### Community 75 - "InputType"
Cohesion: 0.12
Nodes (17): InputType, Axis, Bodies, Body, Bool, Choice, Edges, Faces (+9 more)

### Community 76 - "Vec3"
Cohesion: 0.18
Nodes (20): SurfacePoint, normal, point, Vec3, boundingBox(), edgeMidpoint(), edgesNear(), frame() (+12 more)

### Community 79 - "CommandDialog::CommandDialog"
Cohesion: 0.13
Nodes (5): ExpressionSpinBox, eval_, expression_, shown_, formatNumber()

### Community 80 - "SketchDisplay"
Cohesion: 0.12
Nodes (11): ProfileObject, index, sketch, SketchDisplay, construction, curves, fixedCurves, frame (+3 more)

### Community 81 - "Command"
Cohesion: 0.04
Nodes (57): Adding a tool, Command, CommandDef, feature, icon, id, inputs, name (+49 more)

### Community 82 - "Measurement"
Cohesion: 0.13
Nodes (14): Kind, Angle, Area, Length, Volume, Measurement, from, hasLine (+6 more)

### Community 83 - "SketchCurves.cpp"
Cohesion: 0.11
Nodes (18): crossings(), crossingsOf(), Curve2d, curve2d(), periodic, t0, t1, endIsFree() (+10 more)

### Community 84 - "UiCommand"
Cohesion: 0.07
Nodes (22): UiCommand, enabled, icon, id, name, panel, run, shortcut (+14 more)

### Community 85 - "Level"
Cohesion: 0.16
Nodes (13): debug(), error(), info(), Level, Debug, Error, Info, Warning (+5 more)

### Community 86 - "README.md"
Cohesion: 0.11
Nodes (15): Build, Conventions, Development, Tests, Reference parts, Fusion feature checklist, Roadmap, Contents (+7 more)

### Community 87 - "string"
Cohesion: 0.07
Nodes (31): ConstructionPlane, name, spec, bodyNumber(), Document::axes(), Document::bodies(), Document::body(), Document::bodyName() (+23 more)

### Community 89 - "rect"
Cohesion: 0.10
Nodes (8): SelectionBox, crossing, Session::notifyChanged(), height, Rect, rect(), l, p

### Community 90 - "cachedProfiles"
Cohesion: 0.18
Nodes (4): MainWindow::updateDragArrow(), MainWindow::updateProfilePicking(), cachedProfiles(), keyOf()

### Community 91 - "EntityType"
Cohesion: 0.20
Nodes (7): EntityType, Arc, Circle, Ellipse, Line, Spline, isRound()

### Community 92 - "FileFormat"
Cohesion: 0.17
Nodes (12): FileFormat, Brep, Iges, Obj, Step, Stl, ThreeMF, FormatInfo (+4 more)

### Community 93 - "Known differences still to build"
Cohesion: 0.15
Nodes (12): Data and files, Findings from the videos, Fusion study list, Interface, Known differences still to build, Navigation and display, Selection and the canvas, Sketch (+4 more)

### Community 94 - "MainWindow::MainWindow"
Cohesion: 0.12
Nodes (5): PythonHost, MainWindow::MainWindow(), MainWindow::beginSketch(), MainWindow::exitSketchMode(), MainWindow::showPreferences()

### Community 95 - "ReplayStep"
Cohesion: 0.05
Nodes (40): Body, display, name, shape, Component, bodies, name, ConstructionAxis (+32 more)

### Community 96 - "bindAdsk"
Cohesion: 0.29
Nodes (3): bindAdsk(), BRepBody, index

### Community 97 - ".press"
Cohesion: 0.17
Nodes (4): angleInArc(), ccwContains(), circumcircle(), segDistance()

### Community 98 - "FakeDoc"
Cohesion: 0.17
Nodes (6): FakeDoc, aborts, commits, items, open, snapshot

### Community 100 - "MainWindowArrow.cpp"
Cohesion: 0.13
Nodes (8): ArrowPlacement, base, dir, edgePlacement(), facesPlacement(), MainWindow::attachArrowCompleters(), MainWindow::patternCentre(), MainWindow::pickedFaces()

### Community 102 - "sstream"
Cohesion: 0.17
Nodes (5): doc_(), Document::Document(), Document::ocafBytes(), ocafApplication(), Document::load()

### Community 103 - "MarkingMenu"
Cohesion: 0.40
Nodes (3): MarkingMenu, enabled, public

### Community 104 - "BoundingBox"
Cohesion: 0.24
Nodes (13): BoundingBox, max, min, WallSide, Center, Side1, Side2, extendedWire() (+5 more)

### Community 106 - "SectionState"
Cohesion: 0.25
Nodes (7): SectionState, active, angle, flip, offset, plane, visible

### Community 107 - "Display"
Cohesion: 0.25
Nodes (7): Display, constraints, construction, dimensions, points, profiles, projected

### Community 108 - "main"
Cohesion: 0.27
Nodes (6): listCommands(), main(), usage(), main(), smoke(), key

### Community 109 - "Kernel.h"
Cohesion: 0.10
Nodes (19): Axis, X, Y, Z, BooleanOp, Cut, Intersect, Join (+11 more)

### Community 110 - "TopologyCounts"
Cohesion: 0.17
Nodes (17): Section, Circular, Square, Triangular, TopologyCounts, edges, faces, shells (+9 more)

### Community 111 - "UserParameter"
Cohesion: 0.33
Nodes (6): UserParameter, comment, expression, name, unit, value

### Community 114 - "uninstall.sh"
Cohesion: 0.52
Nodes (6): die(), manifest_for(), refresh(), uninstall.sh script, step(), usage()

### Community 115 - "install.sh"
Cohesion: 0.60
Nodes (5): die(), refresh(), install.sh script, step(), usage()

### Community 116 - "TestFramework.h"
Cohesion: 0.14
Nodes (12): Result, error, ok, output, captured(), PythonHost::exec(), PythonHost::PythonHost(), PythonHost::runScript() (+4 more)

### Community 117 - ".redrawAll"
Cohesion: 0.09
Nodes (8): NavPreset, Fusion, SolidWorks, Tinkercad, Viewport::setCurvatureComb(), Viewport::clearDragArrow(), Viewport::clearSecondArrow(), Viewport::setInteractor()

### Community 118 - "Column"
Cohesion: 0.25
Nodes (8): Column, kComment, kExpression, kName, kParameter, kStar, kUnit, kValue

### Community 123 - "Placement"
Cohesion: 0.25
Nodes (7): Placement, angle, cx, cy, dx, dy, scale

### Community 124 - "ChainSegment"
Cohesion: 0.67
Nodes (3): ChainSegment, entity, forward

### Community 125 - "NewComponent"
Cohesion: 0.19
Nodes (5): AddUserParameter, def_, isIdentifier(), NewComponent, def_

### Community 128 - "Text"
Cohesion: 0.07
Nodes (19): Sketch, constraints, entities, points, texts, Text, angle, corner (+11 more)

### Community 129 - "HandleHit"
Cohesion: 0.40
Nodes (4): HandleHit, back, index, spline

### Community 131 - "DocCommands.cpp"
Cohesion: 0.11
Nodes (25): getReal(), axisOf(), evaluateDimensions(), HoleSize, modeled, pitch, radius, Loft (+17 more)

### Community 132 - "Unit"
Cohesion: 0.13
Nodes (18): MainWindow::lengthUnit(), Dimension, Angle, Length, Unitless, Unit, Centimeter, Degree (+10 more)

### Community 141 - "Point"
Cohesion: 0.27
Nodes (9): Point, x, y, z, SketchError, Sketch::checkIndices(), customPlaneSpec(), planeFrame() (+1 more)

### Community 142 - "SplineHandle"
Cohesion: 0.29
Nodes (7): SplineHandle, arm, index, tx, ty, x, y

## Knowledge Gaps
- **756 isolated node(s):** `ok`, `output`, `error`, `isReal`, `real` (+751 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 1422 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **26 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `optional` connect `optional` to `Viewport`, `DocCommands.cpp`, `MainWindow`, `Unit`, `Expression.cpp`, `Kernel.cpp`, `Io.cpp`, `Parser`, `ViewportSketch.cpp`, `string`, `SketchOps.cpp`, `ViewportArrow.cpp`, `Constraint`, `CommandDialog.cpp`, `SketchEditor.cpp`, `AnalysisSettings`, `ParamSet`, `InputDef`, `string`, `Viewport.h`, `Session`, `Vec3`, `CommandDialog::CommandDialog`, `SketchCurves.cpp`, `string`, `ReplayStep`, `.press`, `MainWindowArrow.cpp`, `Kernel.h`?**
  _High betweenness centrality (0.095) - this node is a cross-community bridge._
- **What connects `ok`, `output`, `error` to the rest of the system?**
  _756 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Viewport` be split into smaller, more focused modules?**
  _Cohesion score 0.01664516129032258 - nodes in this community are weakly interconnected._
- **Why does `MainWindow` connect `MainWindow` to `Icons.h`, `cachedProfiles`, `ParametersDialog.cpp`, `SectionState`, `optional`, `main`, `.openMarkingMenu`, `MainWindowSketch.cpp`, `MainWindowTools.cpp`, `UiCommand`, `MainWindow.cpp`, `Session`, `Viewport.h`, `SketchPalette`, `MainWindow::MainWindow`?**
  _High betweenness centrality (0.090) - this node is a cross-community bridge._
- **Should `Icons.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.05468215994531784 - nodes in this community are weakly interconnected._
- **Why does `Viewport` connect `Viewport` to `rect`, `ViewportArrow.cpp`, `MainWindow`, `src/main.cpp`, `Viewport.cpp`, `Handle`, `optional`, `AnalysisSettings`, `AnalysisSettings`, `SketchDisplay`, `.openMarkingMenu`, `SketchCurves.cpp`, `MainWindowTools.cpp`, `.redrawAll`, `.toPixels`, `ViewportAnalysis.cpp`, `Viewport.h`?**
  _High betweenness centrality (0.088) - this node is a cross-community bridge._
- **Should `tsr` be split into smaller, more focused modules?**
  _Cohesion score 0.04918032786885246 - nodes in this community are weakly interconnected._