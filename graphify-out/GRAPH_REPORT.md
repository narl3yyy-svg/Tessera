# Graph Report - tessera  (2026-11-12)

## Corpus Check
- 333 files · ~191,772 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 28 file(s) not represented in the graph (top: .drive 20, (none) 5, .cmake 1)

## Summary
- 3101 nodes · 7736 edges · 129 communities (106 shown, 23 thin omitted)
- Extraction: 85% EXTRACTED · 15% INFERRED · 0% AMBIGUOUS · INFERRED: 1182 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `6b726c1d`
- Run `git rev-parse HEAD` and compare to check if the graph is stale.
- Run `graphify update .` after code changes (no API cost).

## Community Hubs (Navigation)
- Viewport
- Icons.cpp
- Inputs
- tsr
- MainWindow
- run_oracle.py
- body
- Document
- Viewport.cpp
- SketchEditor
- Expression.cpp
- optional
- Kernel.cpp
- .projectAt
- Kind
- MainWindowTools.cpp
- CommandDialog
- Io.cpp
- Parser
- SketchGeometry.cpp
- DocCommands.cpp
- TEST
- Sketch.cpp
- ViewportSketch.cpp
- SketchPalette
- SketchEditor.cpp
- cmath
- AdskModule.cpp
- Colors
- TopoDS_Shape
- SketchOps.cpp
- Session
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
- .updatePreview
- Zip.cpp
- Document.cpp
- CommandDialog::CommandDialog
- MainWindowSketch.cpp
- Session.cpp
- InputDef
- .toPixels
- MainWindowArrow.cpp
- string
- FeatureEffect
- Constraint
- xdrive.py
- CommandError
- CommandDialog::CommandDialog
- QMouseEvent
- DocumentError
- CommandRegistry
- PythonHost.cpp
- Vec3
- MainWindow::MainWindow
- FileFormat
- CommandDialog.cpp
- ParametersDialog.cpp
- Document::recompute
- TopologyCounts
- .redrawAll
- InputType
- .openMarkingMenu
- UserParameter
- Theme.cpp
- Feature
- SketchDisplay
- string
- Measurement
- Unit
- Entity
- Level
- README.md
- cmath
- Architecture
- SketchEditor::SketchEditor
- ConstructionAxis
- ConstructionPoint
- smoke
- Known differences still to build
- .showDialog
- .add
- sketchFor
- BodyFrame
- FakeDoc
- UiCommand
- TsrModule.cpp
- Zip.h
- Theme
- DocumentError
- cli_main.cpp
- qs
- SectionState
- Display
- ParameterCompleter.cpp
- exportShapes
- Kernel.h
- .motion
- Document::reevaluateParameters
- Mesh
- uninstall.sh
- install.sh
- .rebuild
- Column
- ConstructionPlane
- Profile
- QTabWidget
- MainWindow::setSelectionFilter
- MarkingMenu
- ChainSegment
- LAB_NOTES.md
- build.sh
- live-test.sh

## God Nodes (most connected - your core abstractions)
1. `Viewport` - 203 edges
2. `MainWindow` - 166 edges
3. `SketchEditor` - 154 edges
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

## Communities (129 total, 23 thin omitted)

### Community 0 - "Viewport"
Cohesion: 0.02
Nodes (49): view_, QLineEdit, Viewport, analysis_, analysisObjects_, appliedGridStep_, arrowBoxes_, arrowDragging_ (+41 more)

### Community 1 - "Icons.cpp"
Cohesion: 0.07
Nodes (91): arcIcon(), arrow(), axisIcon(), box(), centerRectIcon(), chamferIcon(), circleIcon(), coilIcon() (+83 more)

### Community 2 - "Inputs"
Cohesion: 0.04
Nodes (57): Adding a tool, Command, CommandContext, CommandDef, feature, icon, id, inputs (+49 more)

### Community 4 - "MainWindow"
Cohesion: 0.03
Nodes (59): writeLiveGeometry(), CommandDialog, MainWindow, active_, arrowInput_, arrowInput2_, bodiesBeforeCommand_, combEdges_ (+51 more)

### Community 5 - "run_oracle.py"
Cohesion: 0.08
Nodes (54): add_point(), arc_poly(), body_at(), body_list(), build_sketch(), chain(), circumcentre(), cm() (+46 more)

### Community 6 - "body"
Cohesion: 0.15
Nodes (14): getBool(), bodyCentre(), bodyName(), Combine, def_, CopyFn, differenceOrNull(), body (+6 more)

### Community 7 - "Document"
Cohesion: 0.04
Nodes (11): Document, effects_, modified_, pendingTools_, registry_, replaying_, txnBodies_, FromOcaf (+3 more)

### Community 8 - "Viewport.cpp"
Cohesion: 0.05
Nodes (5): keys(), qc(), QtFrameBuffer, rgb(), Viewport::Viewport()

### Community 9 - "SketchEditor"
Cohesion: 0.04
Nodes (39): SketchEditor, arcDrag_, arcDragMoved_, arcEndsChain_, arcFrom_, arcRef_, bodyEdges_, chainStart_ (+31 more)

### Community 10 - "Expression.cpp"
Cohesion: 0.10
Nodes (20): ExpressionEnv, lengthUnit, lookup, ExpressionError, Dimension, Angle, Length, Unitless (+12 more)

### Community 13 - ".projectAt"
Cohesion: 0.16
Nodes (4): PlaneEdges, arcs, segments, vertices

### Community 14 - "Kind"
Cohesion: 0.10
Nodes (19): EdgeFeature, def_, kind_, Kind, Angle, AxisCylinder, AxisEdge, AxisTwoPlanes (+11 more)

### Community 15 - "MainWindowTools.cpp"
Cohesion: 0.07
Nodes (25): QDialog, MainWindow::checkInterference(), MainWindow::chooseUnits(), MainWindow::driveJoints(), MainWindow::exportDesign(), MainWindow::formatLength(), MainWindow::gridSettings(), MainWindow::insertFile() (+17 more)

### Community 16 - "CommandDialog"
Cohesion: 0.05
Nodes (31): CommandDialog, bodiesId_, bodiesLabel_, bodyInput_, buttons_, cmd_, conditional_, edgesId_ (+23 more)

### Community 17 - "Io.cpp"
Cohesion: 0.10
Nodes (4): fromBrep(), lower(), toBrep(), xmlEscape()

### Community 18 - "Parser"
Cohesion: 0.17
Nodes (15): Quantity, angle, length, value, describe(), isIdentChar(), isIdentStart(), Parser (+7 more)

### Community 19 - "SketchGeometry.cpp"
Cohesion: 0.14
Nodes (9): curve(), curves(), customPlaneSpec(), interiorPoint(), planeFrame(), profileAt(), profiles(), toSketch() (+1 more)

### Community 21 - "DocCommands.cpp"
Cohesion: 0.19
Nodes (11): axisOf(), InsertGeometry, def_, makeBox(), makeCone(), makeCylinder(), makeSphere(), makeTorus() (+3 more)

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

### Community 28 - "cmath"
Cohesion: 0.12
Nodes (9): run, MarkingMenu::MarkingMenu(), MarkingMenu::mouseMoveEvent(), MarkingMenu::mouseReleaseEvent(), MarkingMenu::paintEvent(), MarkingMenu::popupAt(), MarkingMenu::ringIndexAt(), MarkingMenu::run() (+1 more)

### Community 29 - "AdskModule.cpp"
Cohesion: 0.10
Nodes (16): Application, bindAdsk(), BRepBodies, BRepBody, index, Component, Design, Product (+8 more)

### Community 30 - "Colors"
Cohesion: 0.07
Nodes (28): Colors, base, border, cubeBox, cubeText, errorBackground, grid, gridMajor (+20 more)

### Community 31 - "TopoDS_Shape"
Cohesion: 0.24
Nodes (25): KernelError, WallSide, Center, Side1, Side2, boolean(), chamfer(), chamferEx() (+17 more)

### Community 32 - "SketchOps.cpp"
Cohesion: 0.21
Nodes (19): at(), chainOf(), chamferCorner(), cornerAt(), cross(), dot(), extendLine(), filletCorner() (+11 more)

### Community 33 - "Session"
Cohesion: 0.10
Nodes (7): PythonHost::PythonHost(), Session, commands_, doc_, listeners_, nextListener_, path_

### Community 34 - "ParameterCompleter"
Cohesion: 0.18
Nodes (8): QObject, ParameterCompleter, completer_, edit_, names_, public, QCompleter, QLineEdit

### Community 35 - "string"
Cohesion: 0.10
Nodes (30): completeEdgeReferences(), completeFaceReferences(), decode(), decodeFaces(), dot(), edgeReference(), EdgeSig, full (+22 more)

### Community 36 - "ConstructAxisPoint"
Cohesion: 0.26
Nodes (5): ConstructAxisPoint, def_, kind_, JointPick, frame

### Community 37 - "Viewport.h"
Cohesion: 0.07
Nodes (16): MarkingMenu::keyPressEvent(), AnalysisKind, CurvatureMap, Draft, None, Zebra, AnalysisSettings, curvatureScale (+8 more)

### Community 38 - "solve"
Cohesion: 0.18
Nodes (12): addConstraintChecked(), Layout, n, px, py, rad, makeLayout(), pack() (+4 more)

### Community 39 - "ViewportArrow.cpp"
Cohesion: 0.08
Nodes (11): packed(), ramp(), shade(), Viewport::buildAnalysis(), rgb(), segmentDistance(), Viewport::arrowAt(), Viewport::arrowParam() (+3 more)

### Community 41 - "ConstraintType"
Cohesion: 0.09
Nodes (23): ConstraintType, Angle, Coincident, Collinear, Concentric, Diameter, Distance, Equal (+15 more)

### Community 42 - "TEST"
Cohesion: 0.09
Nodes (3): param(), TEST(), tmp()

### Community 43 - "Pick"
Cohesion: 0.13
Nodes (15): Hit, index, kind, Pick, bodyArc, bodyPoint, bodySegment, hit (+7 more)

### Community 44 - "Snap"
Cohesion: 0.11
Nodes (18): Snap, alignX, alignY, bodyArc, bodySegment, entity, fromX, fromY (+10 more)

### Community 45 - "Kind"
Cohesion: 0.09
Nodes (21): HudField, edit, editing, kind, locked, value, Kind, Angle (+13 more)

### Community 46 - ".updatePreview"
Cohesion: 0.16
Nodes (4): ext(), wire(), Sketch::addLine(), rect()

### Community 47 - "Zip.cpp"
Cohesion: 0.19
Nodes (11): Entry, data, name, ZipError, crc32(), get16(), get32(), put16() (+3 more)

### Community 48 - "Document.cpp"
Cohesion: 0.12
Nodes (20): Document::axes(), Document::bodies(), Document::body(), Document::bodyName(), Document::components(), Document::features(), Document::historyMarker(), Document::lengthUnit() (+12 more)

### Community 49 - "CommandDialog::CommandDialog"
Cohesion: 0.12
Nodes (5): ExpressionSpinBox, eval_, expression_, shown_, formatNumber()

### Community 50 - "MainWindowSketch.cpp"
Cohesion: 0.09
Nodes (11): MainWindow::cancelSketch(), MainWindow::editSketch(), MainWindow::finishSketch(), MainWindow::onProfileClicked(), MainWindow::originalShape(), MainWindow::sketchPalette(), MainWindow::sketchVisible(), MainWindow::startSketch() (+3 more)

### Community 51 - "Session.cpp"
Cohesion: 0.06
Nodes (42): CommandSession, inputs_, expressionKey(), checkInputValue(), CommandContext::evaluateExpression(), CommandDef::input(), CommandSession::applyInTransaction(), CommandSession::cancel() (+34 more)

### Community 52 - "InputDef"
Cohesion: 0.08
Nodes (24): InputDef, choices, defaultValue, id, label, max, min, minExclusive (+16 more)

### Community 54 - "MainWindowArrow.cpp"
Cohesion: 0.13
Nodes (7): ArrowPlacement, base, dir, edgePlacement(), facesPlacement(), MainWindow::patternCentre(), MainWindow::pickedFaces()

### Community 55 - "string"
Cohesion: 0.11
Nodes (10): AddUserParameter, def_, isIdentifier(), Loft, def_, NewComponent, def_, Sweep (+2 more)

### Community 57 - "FeatureEffect"
Cohesion: 0.09
Nodes (17): Body, display, name, shape, Component, bodies, name, FeatureEffect (+9 more)

### Community 58 - "Constraint"
Cohesion: 0.11
Nodes (17): Constraint, entities, expression, points, type, value, value2, SolveResult (+9 more)

### Community 59 - "xdrive.py"
Cohesion: 0.32
Nodes (14): button(), canvas(), click(), drag(), flush(), geometry(), key(), keycode() (+6 more)

### Community 61 - "CommandError"
Cohesion: 0.10
Nodes (21): CommandError, getInt(), getReal(), applyOperation(), Coil, def_, evaluateDimensions(), Extrude (+13 more)

### Community 63 - "QMouseEvent"
Cohesion: 0.11
Nodes (9): QMouseEvent, ViewInteractor, Viewport::arrowMouseMove(), Viewport::arrowMousePress(), Viewport::arrowMouseRelease(), Viewport::dragArrowForTest(), Viewport::emitArrow(), Viewport::rebuildArrows() (+1 more)

### Community 64 - "DocumentError"
Cohesion: 0.12
Nodes (15): DocumentError, Document::abortTransaction(), Document::addBody(), Document::addUserParameter(), Document::axisFrame(), Document::bodyShapes(), Document::commitTransaction(), Document::effectOf() (+7 more)

### Community 65 - "CommandRegistry"
Cohesion: 0.12
Nodes (4): CommandRegistry, cmds_, CommandRegistry::add(), TEST()

### Community 66 - "PythonHost.cpp"
Cohesion: 0.23
Nodes (7): Result, error, ok, output, captured(), PythonHost::exec(), PythonHost::runScript()

### Community 67 - "Vec3"
Cohesion: 0.16
Nodes (23): SurfacePoint, normal, point, Vec3, asSolid(), boundingBox(), edgeMidpoint(), edgesNear() (+15 more)

### Community 68 - "MainWindow::MainWindow"
Cohesion: 0.14
Nodes (3): PythonHost, MainWindow::MainWindow(), MainWindow::showPreferences()

### Community 69 - "FileFormat"
Cohesion: 0.15
Nodes (13): FileFormat, Brep, Iges, Obj, Step, Stl, ThreeMF, FormatInfo (+5 more)

### Community 71 - "ParametersDialog.cpp"
Cohesion: 0.09
Nodes (14): number(), ParametersDialog, building_, error_, listener_, ParametersDialog::ParametersDialog(), public, rebuildPending_ (+6 more)

### Community 72 - "Document::recompute"
Cohesion: 0.12
Nodes (18): SketchRecord, data, name, offset, plane, Document::openTransaction(), Document::recompute(), Document::recordFeature() (+10 more)

### Community 73 - "TopologyCounts"
Cohesion: 0.15
Nodes (19): Section, Circular, Square, Triangular, TopologyCounts, edges, faces, shells (+11 more)

### Community 74 - ".redrawAll"
Cohesion: 0.10
Nodes (8): NavPreset, Fusion, SolidWorks, Tinkercad, Viewport::setCurvatureComb(), Viewport::clearDragArrow(), Viewport::clearSecondArrow(), Viewport::setInteractor()

### Community 75 - "InputType"
Cohesion: 0.12
Nodes (17): InputType, Axis, Bodies, Body, Bool, Choice, Edges, Faces (+9 more)

### Community 76 - ".openMarkingMenu"
Cohesion: 0.10
Nodes (4): MainWindow::beginSketch(), MainWindow::buildSketchTab(), MainWindow::enterSketchMode(), MainWindow::buildUiCommands()

### Community 77 - "UserParameter"
Cohesion: 0.33
Nodes (6): UserParameter, comment, expression, name, unit, value

### Community 78 - "Theme.cpp"
Cohesion: 0.19
Nodes (6): setIconTheme(), darkColors(), darkPalette(), darkStyleSheet(), lightColors(), lightStyleSheet()

### Community 79 - "Feature"
Cohesion: 0.22
Nodes (9): Feature, commandId, error, id, inputs, name, rolledBack, suppressed (+1 more)

### Community 80 - "SketchDisplay"
Cohesion: 0.08
Nodes (18): DragArrow, base, dir, value, PendingLook, center, frame, size (+10 more)

### Community 81 - "string"
Cohesion: 0.17
Nodes (15): bodyNumber(), Document::component(), Document::componentOfBody(), Document::nextAxisName(), Document::nextBodyName(), Document::nextComponentName(), Document::nextPlaneName(), Document::nextPointName() (+7 more)

### Community 82 - "Measurement"
Cohesion: 0.09
Nodes (20): BoundingBox, max, min, Kind, Angle, Area, Length, Volume (+12 more)

### Community 83 - "Unit"
Cohesion: 0.13
Nodes (14): MainWindow::lengthUnit(), Unit, Centimeter, Degree, Foot, Inch, Meter, Millimeter (+6 more)

### Community 84 - "Entity"
Cohesion: 0.22
Nodes (9): Entity, a, b, center, construction, fit, projected, radius (+1 more)

### Community 85 - "Level"
Cohesion: 0.12
Nodes (13): debug(), error(), info(), Level, Debug, Error, Info, Warning (+5 more)

### Community 86 - "README.md"
Cohesion: 0.11
Nodes (15): Build, Conventions, Development, Tests, Reference parts, Fusion feature checklist, Roadmap, Contents (+7 more)

### Community 87 - "cmath"
Cohesion: 0.09
Nodes (13): CommandRegistry::all(), EntityType, Arc, Circle, Line, Spline, isRound(), Case (+5 more)

### Community 88 - "Architecture"
Cohesion: 0.40
Nodes (4): Architecture, How a command works, The document, Units

### Community 90 - "ConstructionAxis"
Cohesion: 0.29
Nodes (5): ConstructionAxis, axis, name, Document::axis(), Document::setAxis()

### Community 91 - "ConstructionPoint"
Cohesion: 0.29
Nodes (5): ConstructionPoint, name, point, Document::point(), Document::setPoint()

### Community 92 - "smoke"
Cohesion: 0.40
Nodes (5): smoke(), MassProperties, area, centerOfMass, volume

### Community 93 - "Known differences still to build"
Cohesion: 0.15
Nodes (12): Data and files, Findings from the videos, Fusion study list, Interface, Known differences still to build, Navigation and display, Selection and the canvas, Sketch (+4 more)

### Community 96 - "sketchFor"
Cohesion: 0.20
Nodes (7): Hole, def_, Pipe, def_, Revolve, def_, sketchFor()

### Community 97 - "BodyFrame"
Cohesion: 0.15
Nodes (14): BodyFrame, diag, dx, dy, dz, x0, y0, z0 (+6 more)

### Community 98 - "FakeDoc"
Cohesion: 0.17
Nodes (6): FakeDoc, aborts, commits, items, open, snapshot

### Community 99 - "UiCommand"
Cohesion: 0.18
Nodes (9): UiCommand, enabled, icon, id, name, panel, shortcut, tab (+1 more)

### Community 100 - "TsrModule.cpp"
Cohesion: 0.23
Nodes (4): bindTsr(), fromPy(), toPy(), typeName()

### Community 101 - "Zip.h"
Cohesion: 0.13
Nodes (5): isEmpty(), Value, slurp(), TEST(), tmp()

### Community 102 - "Theme"
Cohesion: 0.14
Nodes (6): QAbstractButton, QAction, Theme, colors_, public, styled_

### Community 103 - "DocumentError"
Cohesion: 0.17
Nodes (5): doc_(), Document::Document(), Document::ocafBytes(), ocafApplication(), Document::load()

### Community 104 - "cli_main.cpp"
Cohesion: 0.36
Nodes (4): listCommands(), main(), usage(), main()

### Community 105 - "qs"
Cohesion: 0.27
Nodes (4): commandIcon(), qs(), MainWindow::exitSketchMode(), MainWindow::applySection()

### Community 106 - "SectionState"
Cohesion: 0.25
Nodes (7): SectionState, active, angle, flip, offset, plane, visible

### Community 107 - "Display"
Cohesion: 0.25
Nodes (7): Display, constraints, construction, dimensions, points, profiles, projected

### Community 109 - "exportShapes"
Cohesion: 0.40
Nodes (7): MainWindow::print3d(), NamedShape, compoundOf(), exportShapes(), fmt(), write3mf(), writeObj()

### Community 110 - "Kernel.h"
Cohesion: 0.12
Nodes (15): Axis, X, Y, Z, BooleanOp, Cut, Intersect, Join (+7 more)

### Community 111 - ".motion"
Cohesion: 0.31
Nodes (3): Joint, def_, jointOrigin()

### Community 112 - "Document::reevaluateParameters"
Cohesion: 0.28
Nodes (4): Document::expressionEnv(), Document::reevaluateParameters(), Document::userParameter(), Document::save()

### Community 113 - "Mesh"
Cohesion: 0.28
Nodes (6): importShape(), Mesh, nodes, triangles, meshOf(), scaled()

### Community 114 - "uninstall.sh"
Cohesion: 0.52
Nodes (6): die(), manifest_for(), refresh(), uninstall.sh script, step(), usage()

### Community 115 - "install.sh"
Cohesion: 0.60
Nodes (5): die(), refresh(), install.sh script, step(), usage()

### Community 116 - ".rebuild"
Cohesion: 0.46
Nodes (4): fixedColor(), freeColor(), qc(), rgb()

### Community 117 - "Column"
Cohesion: 0.33
Nodes (6): Column, kComment, kExpression, kParameter, kUnit, kValue

### Community 118 - "ConstructionPlane"
Cohesion: 0.33
Nodes (5): ConstructionPlane, name, spec, Document::plane(), Document::setPlane()

### Community 119 - "Profile"
Cohesion: 0.33
Nodes (5): Profile, area, face, x, y

### Community 123 - "MarkingMenu"
Cohesion: 0.40
Nodes (3): MarkingMenu, enabled, public

### Community 132 - "ChainSegment"
Cohesion: 0.67
Nodes (3): ChainSegment, entity, forward

## Knowledge Gaps
- **626 isolated node(s):** `ok`, `output`, `error`, `isReal`, `real` (+621 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 1192 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **23 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `Viewport` connect `Viewport` to `MainWindow`, `Viewport.h`, `ViewportArrow.cpp`, `Viewport.cpp`, `.redrawAll`, `optional`, `MainWindowTools.cpp`, `SketchDisplay`, `.toPixels`, `.setBodyOverrides`, `QMouseEvent`?**
  _High betweenness centrality (0.130) - this node is a cross-community bridge._
- **What connects `ok`, `output`, `error` to the rest of the system?**
  _626 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Viewport` be split into smaller, more focused modules?**
  _Cohesion score 0.018983268983268985 - nodes in this community are weakly interconnected._
- **Why does `optional` connect `optional` to `Viewport`, `MainWindow`, `Expression.cpp`, `Kernel.cpp`, `Parser`, `.applyToSelection`, `DocCommands.cpp`, `ViewportSketch.cpp`, `SketchEditor.cpp`, `SketchOps.cpp`, `Session`, `Viewport.h`, `ViewportArrow.cpp`, `Document.cpp`, `CommandDialog::CommandDialog`, `InputDef`, `MainWindowArrow.cpp`, `Vec3`, `FileFormat`, `CommandDialog.cpp`, `Document::recompute`, `Feature`, `SketchDisplay`, `string`, `Unit`, `ConstructionAxis`, `ConstructionPoint`, `sketchFor`, `Kernel.h`, `Document::reevaluateParameters`, `ConstructionPlane`?**
  _High betweenness centrality (0.114) - this node is a cross-community bridge._
- **Should `Icons.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.06853038245000971 - nodes in this community are weakly interconnected._
- **Why does `MainWindow` connect `MainWindow` to `Session`, `UiCommand`, `MainWindow::MainWindow`, `qs`, `SectionState`, `optional`, `.openMarkingMenu`, `MainWindowTools.cpp`, `MainWindowSketch.cpp`, `MainWindow.cpp`, `QTabWidget`, `SketchPalette`, `smoke`, `.showDialog`?**
  _High betweenness centrality (0.108) - this node is a cross-community bridge._
- **Should `Inputs` be split into smaller, more focused modules?**
  _Cohesion score 0.03783783783783784 - nodes in this community are weakly interconnected._