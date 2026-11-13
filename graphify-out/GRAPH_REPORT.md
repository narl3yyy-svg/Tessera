# Graph Report - tessera  (2026-11-12)

## Corpus Check
- 331 files · ~189,724 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 27 file(s) not represented in the graph (top: .drive 19, (none) 5, .cmake 1)

## Summary
- 3076 nodes · 7670 edges · 127 communities (108 shown, 19 thin omitted)
- Extraction: 85% EXTRACTED · 15% INFERRED · 0% AMBIGUOUS · INFERRED: 1170 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `481217ca`
- Run `git rev-parse HEAD` and compare to check if the graph is stale.
- Run `graphify update .` after code changes (no API cost).

## Community Hubs (Navigation)
- Viewport
- Icons.cpp
- Inputs
- tsr
- MainWindow
- run_oracle.py
- DocCommands.cpp
- Document
- Viewport.cpp
- SketchEditor
- Inputs
- optional
- Kernel.cpp
- .projectAt
- MainWindowSketch.cpp
- MainWindowTools.cpp
- CommandDialog
- Io.cpp
- Parser
- SketchGeometry.cpp
- .mouseMove
- Expression.cpp
- MainWindow.cpp
- TEST
- Sketch.cpp
- ViewportSketch.cpp
- SketchPalette
- SketchEditor.cpp
- QMouseEvent
- AdskModule.cpp
- Colors
- TopoDS_Shape
- SketchOps.cpp
- Unit
- ParameterCompleter
- string
- ConstructAxisPoint
- Viewport.h
- solve
- ViewportArrow.cpp
- src/main.cpp
- ConstraintType
- TEST
- Pick
- Snap
- Kind
- exportShapes
- Zip.cpp
- Document.cpp
- CommandDialog::CommandDialog
- MainWindow::enterSketchMode
- Session.cpp
- InputDef
- .toPixels
- MainWindowArrow.cpp
- .apply
- QObject
- ViewportAnalysis.cpp
- Constraint
- xdrive.py
- TEST
- FeatureEffect
- ParametersDialog
- DocumentError
- CommandRegistry
- PythonHost.cpp
- Vec3
- MainWindow::MainWindow
- FileFormat
- CommandDialog.cpp
- ParametersDialog.cpp
- Document.cpp
- TopologyCounts
- Command.cpp
- InputType
- CommandDef
- TsrModule.cpp
- Theme.cpp
- Feature
- SketchDisplay
- string
- Measurement
- SketchRecord
- Entity
- Level
- README.md
- Sketch.h
- .hitTest
- SketchEditor::SketchEditor
- ConstructionAxis
- ConstructionPoint
- Profile
- Known differences still to build
- CommandSession
- .add
- .motion
- BodyFrame
- FakeDoc
- UiCommand
- Document::reevaluateParameters
- Value.h
- Theme
- DocumentError
- cli_main.cpp
- Session::notifyChanged
- SectionState
- Display
- BRepBody
- Mesh
- Axis
- BooleanOp
- NewComponent
- ThreadInfo
- uninstall.sh
- install.sh
- Column
- ChamferType
- cmath
- Session::addListener
- MarkingMenu
- Dimension
- ChainSegment
- LAB_NOTES.md
- build.sh
- live-test.sh

## God Nodes (most connected - your core abstractions)
1. `Viewport` - 203 edges
2. `MainWindow` - 157 edges
3. `SketchEditor` - 154 edges
4. `Inputs` - 136 edges
5. `Document` - 124 edges
6. `CommandContext` - 102 edges
7. `CommandDialog` - 90 edges
8. `render()` - 86 edges
9. `Command` - 62 edges
10. `CommandDef` - 56 edges

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

## Communities (127 total, 19 thin omitted)

### Community 0 - "Viewport"
Cohesion: 0.02
Nodes (48): view_, Viewport, analysis_, analysisObjects_, appliedGridStep_, arrowBoxes_, arrowDragging_, arrowGrab_ (+40 more)

### Community 1 - "Icons.cpp"
Cohesion: 0.07
Nodes (92): arcIcon(), arrow(), axisIcon(), box(), centerRectIcon(), chamferIcon(), circleIcon(), coilIcon() (+84 more)

### Community 2 - "Inputs"
Cohesion: 0.05
Nodes (36): Command, CommandContext, Inputs, CommandSession::CommandSession(), checkBody(), checkPattern(), CircularPattern, def_ (+28 more)

### Community 4 - "MainWindow"
Cohesion: 0.03
Nodes (55): CommandDialog, MainWindow, active_, arrowInput_, arrowInput2_, bodiesBeforeCommand_, combEdges_, combPicking_ (+47 more)

### Community 5 - "run_oracle.py"
Cohesion: 0.08
Nodes (54): add_point(), arc_poly(), body_at(), body_list(), build_sketch(), chain(), circumcentre(), cm() (+46 more)

### Community 6 - "DocCommands.cpp"
Cohesion: 0.15
Nodes (17): axisOf(), Combine, def_, makeBox(), makeCone(), makeCylinder(), makeSphere(), makeTorus() (+9 more)

### Community 7 - "Document"
Cohesion: 0.05
Nodes (13): Document, effects_, modified_, pendingTools_, registry_, replaying_, txnBodies_, FromOcaf (+5 more)

### Community 8 - "Viewport.cpp"
Cohesion: 0.04
Nodes (10): keys(), NavPreset, Fusion, SolidWorks, Tinkercad, qc(), QtFrameBuffer, rgb() (+2 more)

### Community 9 - "SketchEditor"
Cohesion: 0.04
Nodes (39): SketchEditor, arcDrag_, arcDragMoved_, arcEndsChain_, arcFrom_, arcRef_, bodyEdges_, chainStart_ (+31 more)

### Community 10 - "Inputs"
Cohesion: 0.13
Nodes (16): CommandError, getBool(), getInt(), getReal(), bodyCentre(), bodyName(), CopyFn, defaultBody() (+8 more)

### Community 11 - "optional"
Cohesion: 0.12
Nodes (8): optional, CommandRegistry::all(), UserParameter, comment, expression, name, unit, value

### Community 13 - ".projectAt"
Cohesion: 0.14
Nodes (5): PlaneEdges, arcs, segments, vertices, edges

### Community 14 - "MainWindowSketch.cpp"
Cohesion: 0.07
Nodes (13): MainWindow::cancelSketch(), MainWindow::editSketch(), MainWindow::finishSketch(), MainWindow::onEdgeClicked(), MainWindow::onProfileClicked(), MainWindow::originalShape(), MainWindow::sketchPalette(), MainWindow::sketchVisible() (+5 more)

### Community 15 - "MainWindowTools.cpp"
Cohesion: 0.06
Nodes (24): QDialog, MainWindow::checkInterference(), MainWindow::chooseUnits(), MainWindow::driveJoints(), MainWindow::exportDesign(), MainWindow::formatLength(), MainWindow::gridSettings(), MainWindow::insertFile() (+16 more)

### Community 16 - "CommandDialog"
Cohesion: 0.05
Nodes (31): CommandDialog, bodiesId_, bodiesLabel_, bodyInput_, buttons_, cmd_, conditional_, edgesId_ (+23 more)

### Community 17 - "Io.cpp"
Cohesion: 0.12
Nodes (8): formatForPath(), fromBrep(), importShape(), lower(), meshOf(), scaled(), toBrep(), xmlEscape()

### Community 18 - "Parser"
Cohesion: 0.18
Nodes (14): Quantity, angle, length, value, describe(), isIdentChar(), isIdentStart(), Parser (+6 more)

### Community 19 - "SketchGeometry.cpp"
Cohesion: 0.12
Nodes (9): curve(), curves(), customPlaneSpec(), interiorPoint(), planeFrame(), profileAt(), profiles(), toSketch() (+1 more)

### Community 21 - "Expression.cpp"
Cohesion: 0.13
Nodes (16): ExpressionEnv, lengthUnit, lookup, ExpressionError, evaluateExpression(), evaluateQuantity(), expressionReferences(), isConstantName() (+8 more)

### Community 22 - "MainWindow.cpp"
Cohesion: 0.08
Nodes (6): commandIcon(), qs(), run, MainWindow::applySection(), MarkingMenu::mouseReleaseEvent(), MarkingMenu::triggerForTest()

### Community 23 - "TEST"
Cohesion: 0.09
Nodes (6): Sketch, constraints, entities, points, Sketch::addCircle(), TEST()

### Community 24 - "Sketch.cpp"
Cohesion: 0.09
Nodes (16): Point, x, y, SketchError, entityTypeName(), isDimension(), Sketch::addSpline(), Sketch::checkIndices() (+8 more)

### Community 25 - "ViewportSketch.cpp"
Cohesion: 0.09
Nodes (6): faceStyle(), lineStyle(), rgb(), Viewport::lookAt(), Viewport::planePoint(), Viewport::toWidget()

### Community 26 - "SketchPalette"
Cohesion: 0.06
Nodes (26): flatButton(), QCheckBox, QLabel, QToolButton, QWidget, SketchEditor, SketchPalette, body_ (+18 more)

### Community 28 - "QMouseEvent"
Cohesion: 0.09
Nodes (10): MarkingMenu::keyPressEvent(), MarkingMenu::MarkingMenu(), MarkingMenu::mouseMoveEvent(), MarkingMenu::paintEvent(), MarkingMenu::popupAt(), MarkingMenu::ringIndexAt(), MarkingMenu::run(), QKeyEvent (+2 more)

### Community 29 - "AdskModule.cpp"
Cohesion: 0.14
Nodes (13): Application, BRepBodies, Component, Design, Product, raiseIfError(), UserParameter, name (+5 more)

### Community 30 - "Colors"
Cohesion: 0.07
Nodes (28): Colors, base, border, cubeBox, cubeText, errorBackground, grid, gridMajor (+20 more)

### Community 31 - "TopoDS_Shape"
Cohesion: 0.24
Nodes (25): KernelError, WallSide, Center, Side1, Side2, boolean(), chamfer(), chamferEx() (+17 more)

### Community 32 - "SketchOps.cpp"
Cohesion: 0.21
Nodes (19): at(), chainOf(), chamferCorner(), cornerAt(), cross(), dot(), extendLine(), filletCorner() (+11 more)

### Community 33 - "Unit"
Cohesion: 0.12
Nodes (18): bindAdsk(), MainWindow::lengthUnit(), Unit, Centimeter, Degree, Foot, Inch, Meter (+10 more)

### Community 34 - "ParameterCompleter"
Cohesion: 0.12
Nodes (9): MainWindow::attachArrowCompleters(), ParameterCompleter, completer_, edit_, names_, ParameterCompleter::ParameterCompleter(), public, QCompleter (+1 more)

### Community 35 - "string"
Cohesion: 0.10
Nodes (30): completeEdgeReferences(), completeFaceReferences(), decode(), decodeFaces(), dot(), edgeReference(), EdgeSig, full (+22 more)

### Community 36 - "ConstructAxisPoint"
Cohesion: 0.18
Nodes (5): ConstructAxisPoint, def_, kind_, JointPick, frame

### Community 37 - "Viewport.h"
Cohesion: 0.07
Nodes (15): AnalysisKind, CurvatureMap, Draft, None, Zebra, AnalysisSettings, curvatureScale, draftAngle (+7 more)

### Community 38 - "solve"
Cohesion: 0.18
Nodes (12): addConstraintChecked(), Layout, n, px, py, rad, makeLayout(), pack() (+4 more)

### Community 39 - "ViewportArrow.cpp"
Cohesion: 0.07
Nodes (16): rgb(), segmentDistance(), Viewport::arrowAt(), Viewport::arrowMouseMove(), Viewport::arrowMousePress(), Viewport::arrowMouseRelease(), Viewport::arrowParam(), Viewport::clearDragArrow() (+8 more)

### Community 40 - "src/main.cpp"
Cohesion: 0.11
Nodes (8): grabWindowWithPanels(), main(), smoke(), writeLiveGeometry(), MassProperties, area, centerOfMass, volume

### Community 41 - "ConstraintType"
Cohesion: 0.09
Nodes (23): ConstraintType, Angle, Coincident, Collinear, Concentric, Diameter, Distance, Equal (+15 more)

### Community 42 - "TEST"
Cohesion: 0.06
Nodes (10): PythonHost::PythonHost(), Session, commands_, doc_, listeners_, nextListener_, path_, param() (+2 more)

### Community 43 - "Pick"
Cohesion: 0.12
Nodes (17): fixedColor(), freeColor(), Pick, bodyArc, bodyPoint, bodySegment, hit, midpointOf (+9 more)

### Community 44 - "Snap"
Cohesion: 0.11
Nodes (18): Snap, alignX, alignY, bodyArc, bodySegment, entity, fromX, fromY (+10 more)

### Community 45 - "Kind"
Cohesion: 0.09
Nodes (21): HudField, edit, editing, kind, locked, value, Kind, Angle (+13 more)

### Community 46 - "exportShapes"
Cohesion: 0.47
Nodes (7): MainWindow::print3d(), NamedShape, compoundOf(), exportShapes(), fmt(), write3mf(), writeObj()

### Community 47 - "Zip.cpp"
Cohesion: 0.21
Nodes (11): Entry, data, name, ZipError, crc32(), get16(), get32(), put16() (+3 more)

### Community 48 - "Document.cpp"
Cohesion: 0.11
Nodes (24): ConstructionPlane, name, spec, Document::axes(), Document::bodies(), Document::body(), Document::bodyName(), Document::components() (+16 more)

### Community 49 - "CommandDialog::CommandDialog"
Cohesion: 0.11
Nodes (6): ExpressionSpinBox, eval_, expression_, shown_, formatNumber(), dimensionOf()

### Community 51 - "Session.cpp"
Cohesion: 0.22
Nodes (16): historyEdit(), Session::deleteFeature(), Session::deleteParameter(), Session::editFeature(), Session::newDocument(), Session::open(), Session::redo(), Session::renameBody() (+8 more)

### Community 52 - "InputDef"
Cohesion: 0.06
Nodes (37): InputDef, choices, defaultValue, id, label, max, min, minExclusive (+29 more)

### Community 54 - "MainWindowArrow.cpp"
Cohesion: 0.13
Nodes (7): ArrowPlacement, base, dir, edgePlacement(), facesPlacement(), MainWindow::patternCentre(), MainWindow::pickedFaces()

### Community 55 - ".apply"
Cohesion: 0.09
Nodes (21): applyOperation(), Coil, def_, Extrude, def_, Loft, def_, Pipe (+13 more)

### Community 57 - "ViewportAnalysis.cpp"
Cohesion: 0.13
Nodes (5): packed(), ramp(), shade(), Viewport::buildAnalysis(), Viewport::setCurvatureComb()

### Community 58 - "Constraint"
Cohesion: 0.11
Nodes (17): Constraint, entities, expression, points, type, value, value2, SolveResult (+9 more)

### Community 59 - "xdrive.py"
Cohesion: 0.32
Nodes (14): button(), canvas(), click(), drag(), flush(), geometry(), key(), keycode() (+6 more)

### Community 61 - "TEST"
Cohesion: 0.19
Nodes (3): slurp(), TEST(), tmp()

### Community 62 - "FeatureEffect"
Cohesion: 0.09
Nodes (13): Body, display, name, shape, Component, bodies, name, FeatureEffect (+5 more)

### Community 63 - "ParametersDialog"
Cohesion: 0.19
Nodes (10): ParametersDialog, building_, error_, listener_, public, rebuildPending_, tree_, QLabel (+2 more)

### Community 64 - "DocumentError"
Cohesion: 0.14
Nodes (15): DocumentError, Document::abortTransaction(), Document::addBody(), Document::addUserParameter(), Document::bodyShapes(), Document::commitTransaction(), Document::effectOf(), Document::removeBody() (+7 more)

### Community 65 - "CommandRegistry"
Cohesion: 0.12
Nodes (4): CommandRegistry, cmds_, CommandRegistry::add(), TEST()

### Community 66 - "PythonHost.cpp"
Cohesion: 0.19
Nodes (8): Result, error, ok, output, captured(), PythonHost::exec(), PythonHost::runScript(), fn

### Community 67 - "Vec3"
Cohesion: 0.16
Nodes (23): SurfacePoint, normal, point, Vec3, asSolid(), boundingBox(), edgeMidpoint(), edgesNear() (+15 more)

### Community 68 - "MainWindow::MainWindow"
Cohesion: 0.12
Nodes (5): PythonHost, MainWindow::MainWindow(), MainWindow::beginSketch(), MainWindow::exitSketchMode(), MainWindow::showPreferences()

### Community 69 - "FileFormat"
Cohesion: 0.17
Nodes (12): FileFormat, Brep, Iges, Obj, Step, Stl, ThreeMF, FormatInfo (+4 more)

### Community 71 - "ParametersDialog.cpp"
Cohesion: 0.13
Nodes (3): number(), ParametersDialog::ParametersDialog(), qs()

### Community 72 - "Document.cpp"
Cohesion: 0.10
Nodes (10): Document::openTransaction(), Document::recompute(), Document::recordFeature(), Document::redo(), Document::removeFeature(), Document::setFeatureInputs(), Document::setFeatureSuppressed(), Document::undo() (+2 more)

### Community 73 - "TopologyCounts"
Cohesion: 0.15
Nodes (19): Section, Circular, Square, Triangular, TopologyCounts, edges, faces, shells (+11 more)

### Community 74 - "Command.cpp"
Cohesion: 0.22
Nodes (11): expressionKey(), checkInputValue(), CommandContext::evaluateExpression(), CommandDef::input(), CommandSession::applyInTransaction(), CommandSession::cancel(), CommandSession::execute(), CommandSession::preview() (+3 more)

### Community 75 - "InputType"
Cohesion: 0.12
Nodes (17): InputType, Axis, Bodies, Body, Bool, Choice, Edges, Faces (+9 more)

### Community 76 - "CommandDef"
Cohesion: 0.07
Nodes (26): Adding a tool, CommandDef, feature, icon, id, inputs, name, nameInput (+18 more)

### Community 77 - "TsrModule.cpp"
Cohesion: 0.25
Nodes (4): bindTsr(), fromPy(), toPy(), typeName()

### Community 78 - "Theme.cpp"
Cohesion: 0.19
Nodes (6): setIconTheme(), darkColors(), darkPalette(), darkStyleSheet(), lightColors(), lightStyleSheet()

### Community 79 - "Feature"
Cohesion: 0.25
Nodes (8): Feature, commandId, error, id, inputs, name, suppressed, Document::feature()

### Community 80 - "SketchDisplay"
Cohesion: 0.08
Nodes (18): DragArrow, base, dir, value, PendingLook, center, frame, size (+10 more)

### Community 81 - "string"
Cohesion: 0.13
Nodes (16): bodyNumber(), Document::axisFrame(), Document::component(), Document::componentOfBody(), Document::nextAxisName(), Document::nextBodyName(), Document::nextComponentName(), Document::nextPlaneName() (+8 more)

### Community 82 - "Measurement"
Cohesion: 0.09
Nodes (20): BoundingBox, max, min, Kind, Angle, Area, Length, Volume (+12 more)

### Community 83 - "SketchRecord"
Cohesion: 0.25
Nodes (8): SketchRecord, data, name, offset, plane, Document::setSketch(), Document::sketch(), Document::sketches()

### Community 84 - "Entity"
Cohesion: 0.22
Nodes (9): Entity, a, b, center, construction, fit, projected, radius (+1 more)

### Community 85 - "Level"
Cohesion: 0.16
Nodes (13): debug(), error(), info(), Level, Debug, Error, Info, Warning (+5 more)

### Community 86 - "README.md"
Cohesion: 0.08
Nodes (20): Architecture, How a command works, The document, Units, Build, Conventions, Development, Tests (+12 more)

### Community 87 - "Sketch.h"
Cohesion: 0.29
Nodes (6): EntityType, Arc, Circle, Line, Spline, isRound()

### Community 88 - ".hitTest"
Cohesion: 0.18
Nodes (4): Hit, index, kind, segDistance()

### Community 89 - "SketchEditor::SketchEditor"
Cohesion: 0.15
Nodes (5): SketchEditor::SketchEditor(), Tool, op, shape, target

### Community 90 - "ConstructionAxis"
Cohesion: 0.29
Nodes (5): ConstructionAxis, axis, name, Document::axis(), Document::setAxis()

### Community 91 - "ConstructionPoint"
Cohesion: 0.29
Nodes (5): ConstructionPoint, name, point, Document::point(), Document::setPoint()

### Community 92 - "Profile"
Cohesion: 0.33
Nodes (5): Profile, area, face, x, y

### Community 93 - "Known differences still to build"
Cohesion: 0.15
Nodes (12): Data and files, Findings from the videos, Fusion study list, Interface, Known differences still to build, Navigation and display, Selection and the canvas, Sketch (+4 more)

### Community 94 - "CommandSession"
Cohesion: 0.12
Nodes (8): CommandSession, inputs_, CommandRegistry::find(), CommandRegistry::run(), OwnedCommand, owned, OwningCommandSession, Session::begin()

### Community 97 - "BodyFrame"
Cohesion: 0.15
Nodes (14): BodyFrame, diag, dx, dy, dz, x0, y0, z0 (+6 more)

### Community 98 - "FakeDoc"
Cohesion: 0.17
Nodes (6): FakeDoc, aborts, commits, items, open, snapshot

### Community 99 - "UiCommand"
Cohesion: 0.18
Nodes (9): UiCommand, enabled, icon, id, name, panel, shortcut, tab (+1 more)

### Community 100 - "Document::reevaluateParameters"
Cohesion: 0.38
Nodes (3): Document::expressionEnv(), Document::reevaluateParameters(), Document::save()

### Community 102 - "Theme"
Cohesion: 0.22
Nodes (4): Theme, colors_, public, styled_

### Community 103 - "DocumentError"
Cohesion: 0.17
Nodes (5): doc_(), Document::Document(), Document::ocafBytes(), ocafApplication(), Document::load()

### Community 104 - "cli_main.cpp"
Cohesion: 0.22
Nodes (3): listCommands(), main(), usage()

### Community 106 - "SectionState"
Cohesion: 0.25
Nodes (7): SectionState, active, angle, flip, offset, plane, visible

### Community 107 - "Display"
Cohesion: 0.25
Nodes (7): Display, constraints, construction, dimensions, points, profiles, projected

### Community 109 - "Mesh"
Cohesion: 0.40
Nodes (3): Mesh, nodes, triangles

### Community 110 - "Axis"
Cohesion: 0.50
Nodes (4): Axis, X, Y, Z

### Community 111 - "BooleanOp"
Cohesion: 0.50
Nodes (4): BooleanOp, Cut, Intersect, Join

### Community 112 - "NewComponent"
Cohesion: 0.13
Nodes (7): AddUserParameter, def_, CreateSketch, def_, isIdentifier(), NewComponent, def_

### Community 113 - "ThreadInfo"
Cohesion: 0.50
Nodes (4): ThreadInfo, diameter, internal, pitch

### Community 114 - "uninstall.sh"
Cohesion: 0.52
Nodes (6): die(), manifest_for(), refresh(), uninstall.sh script, step(), usage()

### Community 115 - "install.sh"
Cohesion: 0.60
Nodes (5): die(), refresh(), install.sh script, step(), usage()

### Community 116 - "Column"
Cohesion: 0.33
Nodes (6): Column, kComment, kExpression, kParameter, kUnit, kValue

### Community 117 - "ChamferType"
Cohesion: 0.67
Nodes (3): ChamferType, DistanceAngle, TwoDistances

### Community 118 - "cmath"
Cohesion: 0.13
Nodes (8): Rect, rect(), p, Case, name, fail(), Failure, Register

### Community 123 - "MarkingMenu"
Cohesion: 0.29
Nodes (3): MarkingMenu, enabled, public

### Community 125 - "Dimension"
Cohesion: 0.50
Nodes (4): Dimension, Angle, Length, Unitless

### Community 132 - "ChainSegment"
Cohesion: 0.67
Nodes (3): ChainSegment, entity, forward

## Knowledge Gaps
- **621 isolated node(s):** `ok`, `output`, `error`, `isReal`, `real` (+616 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 1182 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **19 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `optional` connect `optional` to `Viewport`, `MainWindow`, `DocCommands.cpp`, `Kernel.cpp`, `Io.cpp`, `Parser`, `Expression.cpp`, `ViewportSketch.cpp`, `SketchEditor.cpp`, `SketchOps.cpp`, `Unit`, `Viewport.h`, `ViewportArrow.cpp`, `TEST`, `Document.cpp`, `CommandDialog::CommandDialog`, `InputDef`, `MainWindowArrow.cpp`, `.apply`, `Vec3`, `CommandDialog.cpp`, `Feature`, `SketchDisplay`, `string`, `SketchRecord`, `.hitTest`, `ConstructionAxis`, `ConstructionPoint`?**
  _High betweenness centrality (0.141) - this node is a cross-community bridge._
- **What connects `ok`, `output`, `error` to the rest of the system?**
  _621 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Viewport` be split into smaller, more focused modules?**
  _Cohesion score 0.019182652210175146 - nodes in this community are weakly interconnected._
- **Why does `Viewport` connect `Viewport` to `Viewport.h`, `ViewportArrow.cpp`, `Viewport.cpp`, `optional`, `MainWindowTools.cpp`, `SketchDisplay`, `.toPixels`, `ViewportAnalysis.cpp`, `QMouseEvent`?**
  _High betweenness centrality (0.134) - this node is a cross-community bridge._
- **Should `Icons.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.0660941000746826 - nodes in this community are weakly interconnected._
- **Why does `MainWindow` connect `MainWindow` to `UiCommand`, `MainWindow::MainWindow`, `src/main.cpp`, `SectionState`, `optional`, `TEST`, `MainWindowSketch.cpp`, `MainWindowTools.cpp`, `MainWindow::enterSketchMode`, `MainWindow.cpp`, `SketchPalette`?**
  _High betweenness centrality (0.098) - this node is a cross-community bridge._
- **Should `Inputs` be split into smaller, more focused modules?**
  _Cohesion score 0.05063291139240506 - nodes in this community are weakly interconnected._