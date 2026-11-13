# Graph Report - tessera  (2026-11-13)

## Corpus Check
- 337 files · ~194,222 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 31 file(s) not represented in the graph (top: .drive 23, (none) 5, .cmake 1)

## Summary
- 3133 nodes · 7828 edges · 131 communities (100 shown, 31 thin omitted)
- Extraction: 85% EXTRACTED · 15% INFERRED · 0% AMBIGUOUS · INFERRED: 1213 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `4674e628`
- Run `git rev-parse HEAD` and compare to check if the graph is stale.
- Run `graphify update .` after code changes (no API cost).

## Community Hubs (Navigation)
- Viewport
- Icons.cpp
- DocCommands.cpp
- tsr
- MainWindow
- run_oracle.py
- Inputs
- Document
- Viewport.cpp
- SketchEditor
- Dimension
- optional
- Kernel.cpp
- PlaneEdges
- Kind
- MainWindowTools.cpp
- CommandDialog
- Io.cpp
- Unit
- SketchGeometry.cpp
- .press
- AddUserParameter
- TEST
- Sketch.cpp
- ViewportSketch.cpp
- SketchPalette
- cmath
- AdskModule.cpp
- Colors
- TopoDS_Shape
- SketchOps.cpp
- ParameterCompleter
- string
- .openMarkingMenu
- Viewport.h
- solve
- UiCommand
- src/main.cpp
- ConstraintType
- TEST
- Pick
- Snap
- Kind
- .updatePreview
- AnalysisSettings
- Document.cpp
- QString
- MainWindowSketch.cpp
- Session.cpp
- InputDef
- .toPixels
- MainWindowArrow.cpp
- Inputs
- Session
- FeatureEffect
- Constraint
- xdrive.py
- DocumentError
- TestFramework.h
- ViewportArrow.cpp
- ext
- CommandRegistry
- PythonHost.cpp
- Vec3
- MainWindow::MainWindow
- FileFormat
- CommandDialog.cpp
- ParametersDialog.cpp
- .showDialog
- TopologyCounts
- InputType
- QDialog
- Theme.cpp
- Feature
- SketchDisplay
- string
- Measurement
- rect
- Entity
- Level
- README.md
- cmath
- qs
- SketchEditor::SketchEditor
- Value.h
- Known differences still to build
- .add
- sketchFor
- BodyFrame
- FakeDoc
- NewComponent
- exportShapes
- Zip.h
- Theme
- DocumentError
- cli_main.cpp
- ConstructionAxis
- SectionState
- Display
- Profile
- Architecture
- Axis
- smoke
- QTabWidget
- Mesh
- uninstall.sh
- install.sh
- BooleanOp
- Column
- ThreadInfo
- MainWindow::setSelectionFilter
- ChamferType
- MarkingMenu
- ChainSegment
- LAB_NOTES.md
- build.sh
- live-test.sh

## God Nodes (most connected - your core abstractions)
1. `Viewport` - 214 edges
2. `MainWindow` - 172 edges
3. `SketchEditor` - 157 edges
4. `Inputs` - 136 edges
5. `Document` - 126 edges
6. `CommandContext` - 102 edges
7. `CommandDialog` - 90 edges
8. `render()` - 87 edges
9. `Command` - 62 edges
10. `CommandDef` - 56 edges

## Surprising Connections (you probably didn't know these)
- `How a command works` --references--> `CommandDef`  [INFERRED]
  docs/ARCHITECTURE.md → modules/core/include/tsr/core/Command.h
- `Tests` --references--> `unit()`  [INFERRED]
  docs/DEVELOPMENT.md → modules/sketch/src/SketchOps.cpp
- `Architecture` --references--> `InputDef`  [INFERRED]
  docs/ARCHITECTURE.md → modules/core/include/tsr/core/Command.h
- `Architecture` --references--> `CommandDef`  [INFERRED]
  docs/ARCHITECTURE.md → modules/core/include/tsr/core/Command.h
- `Architecture` --references--> `CommandRegistry`  [INFERRED]
  docs/ARCHITECTURE.md → modules/core/include/tsr/core/CommandRegistry.h

## Import Cycles
- None detected.

## Communities (131 total, 31 thin omitted)

### Community 0 - "Viewport"
Cohesion: 0.02
Nodes (51): view_, Viewport, analysis_, analysisObjects_, appliedGridStep_, arrowBoxes_, arrowDragging_, arrowGrab_ (+43 more)

### Community 1 - "Icons.cpp"
Cohesion: 0.07
Nodes (93): arcIcon(), arrow(), axisIcon(), box(), centerRectIcon(), chamferIcon(), circleIcon(), coilIcon() (+85 more)

### Community 2 - "DocCommands.cpp"
Cohesion: 0.04
Nodes (64): Adding a tool, Command, CommandDef, feature, icon, id, inputs, name (+56 more)

### Community 4 - "MainWindow"
Cohesion: 0.03
Nodes (62): writeLiveGeometry(), CommandDialog, MainWindow, active_, arrowInput_, arrowInput2_, bodiesBeforeCommand_, combEdges_ (+54 more)

### Community 5 - "run_oracle.py"
Cohesion: 0.08
Nodes (54): add_point(), arc_poly(), body_at(), body_list(), build_sketch(), chain(), circumcentre(), cm() (+46 more)

### Community 6 - "Inputs"
Cohesion: 0.10
Nodes (26): CommandError, getBool(), getInt(), getReal(), applyOperation(), bodyCentre(), bodyName(), CopyFn (+18 more)

### Community 7 - "Document"
Cohesion: 0.04
Nodes (15): Document, effects_, modified_, pendingTools_, registry_, replaying_, txnBodies_, FromOcaf (+7 more)

### Community 8 - "Viewport.cpp"
Cohesion: 0.05
Nodes (10): keys(), NavPreset, Fusion, SolidWorks, Tinkercad, qc(), QtFrameBuffer, rgb() (+2 more)

### Community 9 - "SketchEditor"
Cohesion: 0.03
Nodes (41): SketchEditor, arcDrag_, arcDragMoved_, arcEndsChain_, arcFrom_, arcRef_, bodyEdges_, boxing_ (+33 more)

### Community 10 - "Dimension"
Cohesion: 0.50
Nodes (4): Dimension, Angle, Length, Unitless

### Community 13 - "PlaneEdges"
Cohesion: 0.29
Nodes (4): PlaneEdges, arcs, segments, vertices

### Community 14 - "Kind"
Cohesion: 0.09
Nodes (22): ConstructPlane, def_, kind_, EdgeFeature, def_, kind_, Kind, Angle (+14 more)

### Community 15 - "MainWindowTools.cpp"
Cohesion: 0.09
Nodes (18): MainWindow::checkInterference(), MainWindow::chooseUnits(), MainWindow::driveJoints(), MainWindow::formatLength(), MainWindow::gridSettings(), MainWindow::insertFile(), MainWindow::openAnalysis(), MainWindow::openSection() (+10 more)

### Community 16 - "CommandDialog"
Cohesion: 0.05
Nodes (31): CommandDialog, bodiesId_, bodiesLabel_, bodyInput_, buttons_, cmd_, conditional_, edgesId_ (+23 more)

### Community 17 - "Io.cpp"
Cohesion: 0.12
Nodes (8): formatForPath(), fromBrep(), importShape(), lower(), meshOf(), scaled(), toBrep(), xmlEscape()

### Community 18 - "Unit"
Cohesion: 0.06
Nodes (51): bindAdsk(), BRepBody, index, MainWindow::lengthUnit(), ExpressionEnv, lengthUnit, lookup, ExpressionError (+43 more)

### Community 19 - "SketchGeometry.cpp"
Cohesion: 0.12
Nodes (9): curve(), curves(), customPlaneSpec(), interiorPoint(), planeFrame(), profileAt(), profiles(), toSketch() (+1 more)

### Community 21 - "AddUserParameter"
Cohesion: 0.18
Nodes (4): AddUserParameter, def_, Push, d

### Community 23 - "TEST"
Cohesion: 0.09
Nodes (6): Sketch, constraints, entities, points, Sketch::addCircle(), TEST()

### Community 24 - "Sketch.cpp"
Cohesion: 0.09
Nodes (16): Point, x, y, SketchError, entityTypeName(), isDimension(), Sketch::addSpline(), Sketch::checkIndices() (+8 more)

### Community 25 - "ViewportSketch.cpp"
Cohesion: 0.07
Nodes (17): faceStyle(), lineStyle(), rgb(), Viewport::lookAt(), Viewport::planePoint(), Viewport::toWidget(), Entry, data (+9 more)

### Community 26 - "SketchPalette"
Cohesion: 0.06
Nodes (26): flatButton(), QCheckBox, QLabel, QToolButton, QWidget, SketchEditor, SketchPalette, body_ (+18 more)

### Community 28 - "cmath"
Cohesion: 0.14
Nodes (6): MarkingMenu::MarkingMenu(), MarkingMenu::mouseMoveEvent(), MarkingMenu::paintEvent(), MarkingMenu::popupAt(), MarkingMenu::ringIndexAt(), MarkingMenu::run()

### Community 29 - "AdskModule.cpp"
Cohesion: 0.12
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

### Community 34 - "ParameterCompleter"
Cohesion: 0.12
Nodes (9): MainWindow::attachArrowCompleters(), ParameterCompleter, completer_, edit_, names_, ParameterCompleter::ParameterCompleter(), public, QCompleter (+1 more)

### Community 35 - "string"
Cohesion: 0.10
Nodes (30): completeEdgeReferences(), completeFaceReferences(), decode(), decodeFaces(), dot(), edgeReference(), EdgeSig, full (+22 more)

### Community 36 - ".openMarkingMenu"
Cohesion: 0.11
Nodes (3): MainWindow::beginSketch(), MainWindow::buildSketchTab(), MainWindow::buildUiCommands()

### Community 37 - "Viewport.h"
Cohesion: 0.08
Nodes (6): MarkingMenu::keyPressEvent(), QKeyEvent, QLabel, QLineEdit, QMouseEvent, ViewInteractor

### Community 38 - "solve"
Cohesion: 0.18
Nodes (12): addConstraintChecked(), Layout, n, px, py, rad, makeLayout(), pack() (+4 more)

### Community 39 - "UiCommand"
Cohesion: 0.09
Nodes (13): UiCommand, enabled, icon, id, name, panel, run, shortcut (+5 more)

### Community 41 - "ConstraintType"
Cohesion: 0.09
Nodes (23): ConstraintType, Angle, Coincident, Collinear, Concentric, Diameter, Distance, Equal (+15 more)

### Community 42 - "TEST"
Cohesion: 0.09
Nodes (3): param(), TEST(), tmp()

### Community 43 - "Pick"
Cohesion: 0.12
Nodes (15): Hit, index, kind, Pick, bodyArc, bodyPoint, bodySegment, hit (+7 more)

### Community 44 - "Snap"
Cohesion: 0.10
Nodes (18): Snap, alignX, alignY, bodyArc, bodySegment, entity, fromX, fromY (+10 more)

### Community 45 - "Kind"
Cohesion: 0.09
Nodes (21): HudField, edit, editing, kind, locked, value, Kind, Angle (+13 more)

### Community 46 - ".updatePreview"
Cohesion: 0.15
Nodes (7): ext(), fixedColor(), freeColor(), qc(), rgb(), wire(), Sketch::addLine()

### Community 47 - "AnalysisSettings"
Cohesion: 0.08
Nodes (21): AnalysisKind, CurvatureMap, Draft, None, Zebra, AnalysisSettings, curvatureScale, draftAngle (+13 more)

### Community 48 - "Document.cpp"
Cohesion: 0.08
Nodes (29): ConstructionPlane, name, spec, Document::addUserParameter(), Document::axes(), Document::bodies(), Document::body(), Document::bodyName() (+21 more)

### Community 49 - "QString"
Cohesion: 0.11
Nodes (6): ExpressionSpinBox, eval_, expression_, shown_, formatNumber(), dimensionOf()

### Community 50 - "MainWindowSketch.cpp"
Cohesion: 0.09
Nodes (12): MainWindow::cancelSketch(), MainWindow::editSketch(), MainWindow::finishSketch(), MainWindow::onProfileClicked(), MainWindow::originalShape(), MainWindow::sketchPalette(), MainWindow::sketchVisible(), MainWindow::startSketch() (+4 more)

### Community 51 - "Session.cpp"
Cohesion: 0.05
Nodes (43): CommandSession, inputs_, expressionKey(), checkInputValue(), CommandContext::evaluateExpression(), CommandDef::input(), CommandSession::applyInTransaction(), CommandSession::cancel() (+35 more)

### Community 52 - "InputDef"
Cohesion: 0.08
Nodes (24): InputDef, choices, defaultValue, id, label, max, min, minExclusive (+16 more)

### Community 54 - "MainWindowArrow.cpp"
Cohesion: 0.07
Nodes (12): ArrowPlacement, base, dir, edgePlacement(), facesPlacement(), MainWindow::patternCentre(), MainWindow::pickedFaces(), packed() (+4 more)

### Community 55 - "Inputs"
Cohesion: 0.07
Nodes (14): CommandContext, Inputs, CommandSession::CommandSession(), checkBody(), checkPattern(), defaultBody(), Extrude, def_ (+6 more)

### Community 56 - "Session"
Cohesion: 0.10
Nodes (7): PythonHost::PythonHost(), Session, commands_, doc_, listeners_, nextListener_, path_

### Community 57 - "FeatureEffect"
Cohesion: 0.06
Nodes (28): Body, display, name, shape, Component, bodies, name, ConstructionPoint (+20 more)

### Community 58 - "Constraint"
Cohesion: 0.11
Nodes (17): Constraint, entities, expression, points, type, value, value2, SolveResult (+9 more)

### Community 59 - "xdrive.py"
Cohesion: 0.32
Nodes (14): button(), canvas(), click(), drag(), flush(), geometry(), key(), keycode() (+6 more)

### Community 61 - "DocumentError"
Cohesion: 0.15
Nodes (14): DocumentError, Document::abortTransaction(), Document::addBody(), Document::axisFrame(), Document::bodyShapes(), Document::commitTransaction(), Document::effectOf(), Document::removeBody() (+6 more)

### Community 62 - "TestFramework.h"
Cohesion: 0.13
Nodes (6): Case, fn, name, fail(), Failure, Register

### Community 63 - "ViewportArrow.cpp"
Cohesion: 0.07
Nodes (16): rgb(), segmentDistance(), Viewport::arrowAt(), Viewport::arrowMouseMove(), Viewport::arrowMousePress(), Viewport::arrowMouseRelease(), Viewport::arrowParam(), Viewport::clearDragArrow() (+8 more)

### Community 64 - "ext"
Cohesion: 0.13
Nodes (18): SketchRecord, data, name, offset, plane, Document::openTransaction(), Document::recompute(), Document::recordFeature() (+10 more)

### Community 65 - "CommandRegistry"
Cohesion: 0.12
Nodes (4): CommandRegistry, cmds_, CommandRegistry::add(), TEST()

### Community 66 - "PythonHost.cpp"
Cohesion: 0.21
Nodes (7): Result, error, ok, output, captured(), PythonHost::exec(), PythonHost::runScript()

### Community 67 - "Vec3"
Cohesion: 0.16
Nodes (23): SurfacePoint, normal, point, Vec3, asSolid(), boundingBox(), edgeMidpoint(), edgesNear() (+15 more)

### Community 68 - "MainWindow::MainWindow"
Cohesion: 0.15
Nodes (4): PythonHost, MainWindow::MainWindow(), MainWindow::exitSketchMode(), MainWindow::showPreferences()

### Community 69 - "FileFormat"
Cohesion: 0.17
Nodes (12): FileFormat, Brep, Iges, Obj, Step, Stl, ThreeMF, FormatInfo (+4 more)

### Community 71 - "ParametersDialog.cpp"
Cohesion: 0.09
Nodes (14): number(), ParametersDialog, building_, error_, listener_, ParametersDialog::ParametersDialog(), public, rebuildPending_ (+6 more)

### Community 73 - "TopologyCounts"
Cohesion: 0.15
Nodes (19): Section, Circular, Square, Triangular, TopologyCounts, edges, faces, shells (+11 more)

### Community 75 - "InputType"
Cohesion: 0.09
Nodes (21): bindTsr(), fromPy(), toPy(), typeName(), InputType, Axis, Bodies, Body (+13 more)

### Community 76 - "QDialog"
Cohesion: 0.18
Nodes (5): QDialog, MainWindow::exportDesign(), MainWindow::measurePick(), MainWindow::openMeasure(), toolWindow()

### Community 78 - "Theme.cpp"
Cohesion: 0.19
Nodes (6): setIconTheme(), darkColors(), darkPalette(), darkStyleSheet(), lightColors(), lightStyleSheet()

### Community 79 - "Feature"
Cohesion: 0.22
Nodes (9): Feature, commandId, error, id, inputs, name, rolledBack, suppressed (+1 more)

### Community 80 - "SketchDisplay"
Cohesion: 0.13
Nodes (10): ProfileObject, index, sketch, SketchDisplay, construction, curves, frame, name (+2 more)

### Community 81 - "string"
Cohesion: 0.22
Nodes (14): bodyNumber(), Document::component(), Document::componentOfBody(), Document::nextAxisName(), Document::nextBodyName(), Document::nextComponentName(), Document::nextPlaneName(), Document::nextPointName() (+6 more)

### Community 82 - "Measurement"
Cohesion: 0.09
Nodes (20): BoundingBox, max, min, Kind, Angle, Area, Length, Volume (+12 more)

### Community 84 - "Entity"
Cohesion: 0.22
Nodes (9): Entity, a, b, center, construction, fit, projected, radius (+1 more)

### Community 85 - "Level"
Cohesion: 0.16
Nodes (13): debug(), error(), info(), Level, Debug, Error, Info, Warning (+5 more)

### Community 86 - "README.md"
Cohesion: 0.11
Nodes (15): Build, Conventions, Development, Tests, Reference parts, Fusion feature checklist, Roadmap, Contents (+7 more)

### Community 87 - "cmath"
Cohesion: 0.22
Nodes (6): EntityType, Arc, Circle, Line, Spline, isRound()

### Community 88 - "qs"
Cohesion: 0.33
Nodes (3): commandIcon(), qs(), MainWindow::applySection()

### Community 89 - "SketchEditor::SketchEditor"
Cohesion: 0.14
Nodes (7): QObject, SketchEditor::SketchEditor(), edges, Tool, op, shape, target

### Community 93 - "Known differences still to build"
Cohesion: 0.15
Nodes (12): Data and files, Findings from the videos, Fusion study list, Interface, Known differences still to build, Navigation and display, Selection and the canvas, Sketch (+4 more)

### Community 96 - "sketchFor"
Cohesion: 0.17
Nodes (8): Hole, def_, Loft, def_, Pipe, def_, sectionOf(), sketchFor()

### Community 97 - "BodyFrame"
Cohesion: 0.15
Nodes (14): BodyFrame, diag, dx, dy, dz, x0, y0, z0 (+6 more)

### Community 98 - "FakeDoc"
Cohesion: 0.17
Nodes (6): FakeDoc, aborts, commits, items, open, snapshot

### Community 100 - "exportShapes"
Cohesion: 0.57
Nodes (6): NamedShape, compoundOf(), exportShapes(), fmt(), write3mf(), writeObj()

### Community 101 - "Zip.h"
Cohesion: 0.22
Nodes (3): slurp(), TEST(), tmp()

### Community 102 - "Theme"
Cohesion: 0.22
Nodes (4): Theme, colors_, public, styled_

### Community 103 - "DocumentError"
Cohesion: 0.17
Nodes (5): doc_(), Document::Document(), Document::ocafBytes(), ocafApplication(), Document::load()

### Community 104 - "cli_main.cpp"
Cohesion: 0.36
Nodes (4): listCommands(), main(), usage(), main()

### Community 105 - "ConstructionAxis"
Cohesion: 0.33
Nodes (5): ConstructionAxis, axis, name, Document::axis(), Document::setAxis()

### Community 106 - "SectionState"
Cohesion: 0.25
Nodes (7): SectionState, active, angle, flip, offset, plane, visible

### Community 107 - "Display"
Cohesion: 0.25
Nodes (7): Display, constraints, construction, dimensions, points, profiles, projected

### Community 108 - "Profile"
Cohesion: 0.33
Nodes (5): Profile, area, face, x, y

### Community 109 - "Architecture"
Cohesion: 0.40
Nodes (4): Architecture, How a command works, The document, Units

### Community 110 - "Axis"
Cohesion: 0.50
Nodes (4): Axis, X, Y, Z

### Community 111 - "smoke"
Cohesion: 0.40
Nodes (5): smoke(), MassProperties, area, centerOfMass, volume

### Community 113 - "Mesh"
Cohesion: 0.40
Nodes (3): Mesh, nodes, triangles

### Community 114 - "uninstall.sh"
Cohesion: 0.52
Nodes (6): die(), manifest_for(), refresh(), uninstall.sh script, step(), usage()

### Community 115 - "install.sh"
Cohesion: 0.60
Nodes (5): die(), refresh(), install.sh script, step(), usage()

### Community 116 - "BooleanOp"
Cohesion: 0.50
Nodes (4): BooleanOp, Cut, Intersect, Join

### Community 117 - "Column"
Cohesion: 0.33
Nodes (6): Column, kComment, kExpression, kParameter, kUnit, kValue

### Community 118 - "ThreadInfo"
Cohesion: 0.50
Nodes (4): ThreadInfo, diameter, internal, pitch

### Community 120 - "ChamferType"
Cohesion: 0.67
Nodes (3): ChamferType, DistanceAngle, TwoDistances

### Community 123 - "MarkingMenu"
Cohesion: 0.40
Nodes (3): MarkingMenu, enabled, public

### Community 132 - "ChainSegment"
Cohesion: 0.67
Nodes (3): ChainSegment, entity, forward

## Knowledge Gaps
- **633 isolated node(s):** `ok`, `output`, `error`, `isReal`, `real` (+628 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 1199 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **31 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `optional` connect `optional` to `Viewport`, `DocCommands.cpp`, `MainWindow`, `Kernel.cpp`, `Io.cpp`, `Unit`, `.press`, `ViewportSketch.cpp`, `SketchEditor.cpp`, `SketchOps.cpp`, `Viewport.h`, `AnalysisSettings`, `Document.cpp`, `QString`, `InputDef`, `MainWindowArrow.cpp`, `Session`, `FeatureEffect`, `ViewportArrow.cpp`, `ext`, `Vec3`, `CommandDialog.cpp`, `Feature`, `string`, `sketchFor`, `ConstructionAxis`?**
  _High betweenness centrality (0.122) - this node is a cross-community bridge._
- **What connects `ok`, `output`, `error` to the rest of the system?**
  _633 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Viewport` be split into smaller, more focused modules?**
  _Cohesion score 0.018822393822393823 - nodes in this community are weakly interconnected._
- **Why does `Viewport` connect `Viewport` to `Viewport.h`, `Viewport.cpp`, `optional`, `.initializeGL`, `AnalysisSettings`, `SketchDisplay`, `MainWindowTools.cpp`, `rect`, `.toPixels`, `MainWindowArrow.cpp`, `.selectedSubShapes`, `ViewportArrow.cpp`?**
  _High betweenness centrality (0.117) - this node is a cross-community bridge._
- **Should `Icons.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.06538461538461539 - nodes in this community are weakly interconnected._
- **Why does `MainWindow` connect `MainWindow` to `ParameterCompleter`, `MainWindow::MainWindow`, `.openMarkingMenu`, `UiCommand`, `.showDialog`, `SectionState`, `optional`, `QDialog`, `smoke`, `MainWindowTools.cpp`, `QTabWidget`, `MainWindowSketch.cpp`, `MainWindow.cpp`, `qs`, `Session`?**
  _High betweenness centrality (0.097) - this node is a cross-community bridge._
- **Should `DocCommands.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.04336043360433604 - nodes in this community are weakly interconnected._