# Graph Report - tessera  (2026-11-13)

## Corpus Check
- 338 files · ~195,975 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 32 file(s) not represented in the graph (top: .drive 24, (none) 5, .cmake 1)

## Summary
- 3151 nodes · 7885 edges · 135 communities (101 shown, 34 thin omitted)
- Extraction: 85% EXTRACTED · 15% INFERRED · 0% AMBIGUOUS · INFERRED: 1222 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `dd07121a`
- Run `git rev-parse HEAD` and compare to check if the graph is stale.
- Run `graphify update .` after code changes (no API cost).

## Community Hubs (Navigation)
- Viewport
- Icons.cpp
- Command
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
- .projectAt
- Kind
- MainWindowTools.cpp
- CommandDialog
- Io.cpp
- Unit
- Profile
- .rebuild
- Unit
- MainWindow.cpp
- TEST
- Sketch.cpp
- ViewportSketch.cpp
- SketchPalette
- .hitTest
- CommandError
- AdskModule.cpp
- Colors
- TopoDS_Shape
- SketchOps.cpp
- Session.cpp
- ParameterCompleter
- .showDialog
- Viewport.h
- solve
- MarkingMenu.cpp
- src/main.cpp
- ConstraintType
- TEST
- Pick
- Snap
- Kind
- .press
- fromInternal
- Document.cpp
- Session
- MainWindowSketch.cpp
- InputDef
- .toPixels
- ViewportAnalysis.cpp
- AddUserParameter
- Theme.cpp
- FeatureEffect
- Constraint
- xdrive.py
- SketchGeometry.cpp
- cmath
- ViewportArrow.cpp
- .openMarkingMenu
- CommandRegistry
- PythonHost.cpp
- Vec3
- Theme
- FileFormat
- CommandDialog.cpp
- ParametersDialog.cpp
- MainWindow::MainWindow
- TopologyCounts
- QString
- InputType
- .redrawAll
- TEST
- SketchDisplay
- string
- Measurement
- rect
- Entity
- Level
- README.md
- QDialog
- QObject
- Value.h
- Sketch.h
- Known differences still to build
- SketchEditor::SketchEditor
- .add
- TsrModule.cpp
- string
- FakeDoc
- DocCommands.cpp
- Zip.cpp
- Feature
- Axis
- DocumentError
- BooleanOp
- ConstructionAxis
- SectionState
- Display
- ThreadInfo
- .requireTransaction
- openWallBand
- exportShapes
- ConstructionPoint
- main
- uninstall.sh
- install.sh
- NewComponent
- Column
- ChamferType
- functional
- Document::reevaluateParameters
- Architecture
- BRepBody
- smoke
- Mesh
- ChainSegment
- LAB_NOTES.md
- build.sh
- live-test.sh

## God Nodes (most connected - your core abstractions)
1. `Viewport` - 225 edges
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
- `Known gaps` --references--> `QTabWidget`  [INFERRED]
  docs/KNOWN_GAPS.md → modules/app/src/MainWindow.h
- `Architecture` --references--> `InputDef`  [INFERRED]
  docs/ARCHITECTURE.md → modules/core/include/tsr/core/Command.h
- `Architecture` --references--> `CommandDef`  [INFERRED]
  docs/ARCHITECTURE.md → modules/core/include/tsr/core/Command.h

## Import Cycles
- None detected.

## Communities (135 total, 34 thin omitted)

### Community 0 - "Viewport"
Cohesion: 0.02
Nodes (55): view_, Viewport, analysis_, analysisObjects_, appliedGridStep_, arrowBoxes_, arrowDragging_, arrowGrab_ (+47 more)

### Community 1 - "Icons.cpp"
Cohesion: 0.07
Nodes (93): arcIcon(), arrow(), axisIcon(), box(), centerRectIcon(), chamferIcon(), circleIcon(), coilIcon() (+85 more)

### Community 2 - "Command"
Cohesion: 0.12
Nodes (21): Adding a tool, Command, getInt(), getReal(), CircularPattern, def_, makeBox(), makeCone() (+13 more)

### Community 4 - "MainWindow"
Cohesion: 0.03
Nodes (62): CommandDialog, MainWindow, active_, arrowInput_, arrowInput2_, bodiesBeforeCommand_, combEdges_, combPicking_ (+54 more)

### Community 5 - "run_oracle.py"
Cohesion: 0.08
Nodes (54): add_point(), arc_poly(), body_at(), body_list(), build_sketch(), chain(), circumcentre(), cm() (+46 more)

### Community 6 - "Inputs"
Cohesion: 0.07
Nodes (14): CommandContext, Inputs, CommandSession::CommandSession(), checkBody(), checkPattern(), defaultBody(), Extrude, def_ (+6 more)

### Community 7 - "Document"
Cohesion: 0.05
Nodes (17): Document, effects_, modified_, pendingTools_, registry_, replaying_, txnBodies_, FromOcaf (+9 more)

### Community 8 - "Viewport.cpp"
Cohesion: 0.06
Nodes (5): keys(), qc(), QtFrameBuffer, rgb(), Viewport::Viewport()

### Community 9 - "SketchEditor"
Cohesion: 0.04
Nodes (41): SketchEditor, arcDrag_, arcDragMoved_, arcEndsChain_, arcFrom_, arcRef_, bodyEdges_, boxing_ (+33 more)

### Community 10 - "Dimension"
Cohesion: 0.50
Nodes (4): Dimension, Angle, Length, Unitless

### Community 13 - ".projectAt"
Cohesion: 0.22
Nodes (4): PlaneEdges, arcs, segments, vertices

### Community 14 - "Kind"
Cohesion: 0.08
Nodes (25): ConstructPlane, def_, kind_, EdgeFeature, def_, kind_, FaceFeature, def_ (+17 more)

### Community 15 - "MainWindowTools.cpp"
Cohesion: 0.08
Nodes (7): MainWindow::chooseUnits(), MainWindow::insertFile(), MainWindow::sectionFrame(), MainWindow::sectionPlane(), MainWindow::setSelectionFilter(), MainWindow::showParameters(), MainWindow::updateSectionArrow()

### Community 16 - "CommandDialog"
Cohesion: 0.05
Nodes (31): CommandDialog, bodiesId_, bodiesLabel_, bodyInput_, buttons_, cmd_, conditional_, edgesId_ (+23 more)

### Community 17 - "Io.cpp"
Cohesion: 0.12
Nodes (8): formatForPath(), fromBrep(), importShape(), lower(), meshOf(), scaled(), toBrep(), xmlEscape()

### Community 18 - "Unit"
Cohesion: 0.10
Nodes (30): ExpressionEnv, lengthUnit, lookup, ExpressionError, Quantity, angle, length, value (+22 more)

### Community 19 - "Profile"
Cohesion: 0.18
Nodes (12): Profile, area, face, x, y, curve(), curves(), interiorPoint() (+4 more)

### Community 20 - ".rebuild"
Cohesion: 0.36
Nodes (5): fixedColor(), freeColor(), qc(), rgb(), wire()

### Community 21 - "Unit"
Cohesion: 0.11
Nodes (18): bindAdsk(), MainWindow::lengthUnit(), Unit, Centimeter, Degree, Foot, Inch, Meter (+10 more)

### Community 22 - "MainWindow.cpp"
Cohesion: 0.09
Nodes (4): commandIcon(), qs(), MainWindow::enterSketchMode(), MainWindow::applySection()

### Community 23 - "TEST"
Cohesion: 0.09
Nodes (6): Sketch, constraints, entities, points, Sketch::addCircle(), TEST()

### Community 24 - "Sketch.cpp"
Cohesion: 0.09
Nodes (16): Point, x, y, SketchError, entityTypeName(), isDimension(), Sketch::addSpline(), Sketch::checkIndices() (+8 more)

### Community 25 - "ViewportSketch.cpp"
Cohesion: 0.08
Nodes (6): faceStyle(), lineStyle(), rgb(), Viewport::lookAt(), Viewport::planePoint(), Viewport::toWidget()

### Community 26 - "SketchPalette"
Cohesion: 0.06
Nodes (27): flatButton(), MainWindow::buildSketchTab(), QCheckBox, QLabel, QToolButton, QWidget, SketchEditor, SketchPalette (+19 more)

### Community 28 - "CommandError"
Cohesion: 0.11
Nodes (16): CommandError, getBool(), bodyCentre(), bodyName(), Coil, def_, Joint, def_ (+8 more)

### Community 29 - "AdskModule.cpp"
Cohesion: 0.13
Nodes (13): Application, BRepBodies, Component, Design, Product, raiseIfError(), UserParameter, name (+5 more)

### Community 30 - "Colors"
Cohesion: 0.07
Nodes (28): Colors, base, border, cubeBox, cubeText, errorBackground, grid, gridMajor (+20 more)

### Community 31 - "TopoDS_Shape"
Cohesion: 0.21
Nodes (30): KernelError, asSolid(), boolean(), chamfer(), chamferEx(), coil(), draft(), extrude() (+22 more)

### Community 32 - "SketchOps.cpp"
Cohesion: 0.21
Nodes (19): at(), chainOf(), chamferCorner(), cornerAt(), cross(), dot(), extendLine(), filletCorner() (+11 more)

### Community 33 - "Session.cpp"
Cohesion: 0.06
Nodes (42): CommandSession, inputs_, expressionKey(), checkInputValue(), CommandContext::evaluateExpression(), CommandDef::input(), CommandSession::applyInTransaction(), CommandSession::cancel() (+34 more)

### Community 34 - "ParameterCompleter"
Cohesion: 0.12
Nodes (9): MainWindow::attachArrowCompleters(), ParameterCompleter, completer_, edit_, names_, ParameterCompleter::ParameterCompleter(), public, QCompleter (+1 more)

### Community 37 - "Viewport.h"
Cohesion: 0.06
Nodes (17): MarkingMenu::keyPressEvent(), AnalysisKind, CurvatureMap, Draft, None, Zebra, AnalysisSettings, curvatureScale (+9 more)

### Community 38 - "solve"
Cohesion: 0.18
Nodes (12): addConstraintChecked(), Layout, n, px, py, rad, makeLayout(), pack() (+4 more)

### Community 39 - "MarkingMenu.cpp"
Cohesion: 0.07
Nodes (18): UiCommand, enabled, icon, id, name, panel, run, shortcut (+10 more)

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
Cohesion: 0.11
Nodes (18): Snap, alignX, alignY, bodyArc, bodySegment, entity, fromX, fromY (+10 more)

### Community 45 - "Kind"
Cohesion: 0.09
Nodes (21): HudField, edit, editing, kind, locked, value, Kind, Angle (+13 more)

### Community 47 - "fromInternal"
Cohesion: 0.23
Nodes (11): MainWindow::checkInterference(), MainWindow::driveJoints(), MainWindow::formatLength(), MainWindow::gridSettings(), MainWindow::openAnalysis(), MainWindow::openSection(), MainWindow::showCenterOfMass(), MainWindow::updateMeasure() (+3 more)

### Community 48 - "Document.cpp"
Cohesion: 0.08
Nodes (30): ConstructionPlane, name, spec, Document::axes(), Document::bodies(), Document::body(), Document::bodyName(), Document::components() (+22 more)

### Community 49 - "Session"
Cohesion: 0.10
Nodes (7): PythonHost::PythonHost(), Session, commands_, doc_, listeners_, nextListener_, path_

### Community 50 - "MainWindowSketch.cpp"
Cohesion: 0.10
Nodes (12): MainWindow::cancelSketch(), MainWindow::editSketch(), MainWindow::finishSketch(), MainWindow::onProfileClicked(), MainWindow::originalShape(), MainWindow::sketchPalette(), MainWindow::sketchVisible(), MainWindow::startSketch() (+4 more)

### Community 52 - "InputDef"
Cohesion: 0.04
Nodes (56): CommandDef, feature, icon, id, inputs, name, nameInput, panel (+48 more)

### Community 54 - "ViewportAnalysis.cpp"
Cohesion: 0.08
Nodes (11): ArrowPlacement, base, dir, edgePlacement(), facesPlacement(), MainWindow::patternCentre(), MainWindow::pickedFaces(), packed() (+3 more)

### Community 56 - "Theme.cpp"
Cohesion: 0.19
Nodes (6): setIconTheme(), darkColors(), darkPalette(), darkStyleSheet(), lightColors(), lightStyleSheet()

### Community 57 - "FeatureEffect"
Cohesion: 0.08
Nodes (21): Body, display, name, shape, Component, bodies, name, FeatureEffect (+13 more)

### Community 58 - "Constraint"
Cohesion: 0.11
Nodes (17): Constraint, entities, expression, points, type, value, value2, SolveResult (+9 more)

### Community 59 - "xdrive.py"
Cohesion: 0.32
Nodes (14): button(), canvas(), click(), drag(), flush(), geometry(), key(), keycode() (+6 more)

### Community 62 - "cmath"
Cohesion: 0.21
Nodes (5): Case, name, fail(), Failure, Register

### Community 63 - "ViewportArrow.cpp"
Cohesion: 0.06
Nodes (17): QMouseEvent, ViewInteractor, Viewport::frontEdgeOwner(), rgb(), segmentDistance(), Viewport::arrowAt(), Viewport::arrowMouseMove(), Viewport::arrowMousePress() (+9 more)

### Community 65 - "CommandRegistry"
Cohesion: 0.12
Nodes (4): CommandRegistry, cmds_, CommandRegistry::add(), TEST()

### Community 66 - "PythonHost.cpp"
Cohesion: 0.21
Nodes (8): Result, error, ok, output, captured(), PythonHost::exec(), PythonHost::runScript(), fn

### Community 67 - "Vec3"
Cohesion: 0.20
Nodes (18): SurfacePoint, normal, point, Vec3, edgeMidpoint(), edgesNear(), frame(), makeCone() (+10 more)

### Community 68 - "Theme"
Cohesion: 0.22
Nodes (4): Theme, colors_, public, styled_

### Community 69 - "FileFormat"
Cohesion: 0.17
Nodes (12): FileFormat, Brep, Iges, Obj, Step, Stl, ThreeMF, FormatInfo (+4 more)

### Community 71 - "ParametersDialog.cpp"
Cohesion: 0.09
Nodes (15): number(), ParametersDialog, building_, error_, listener_, ParametersDialog::ParametersDialog(), public, rebuildPending_ (+7 more)

### Community 72 - "MainWindow::MainWindow"
Cohesion: 0.13
Nodes (4): PythonHost, MainWindow::MainWindow(), MainWindow::exitSketchMode(), MainWindow::showPreferences()

### Community 73 - "TopologyCounts"
Cohesion: 0.29
Nodes (7): TopologyCounts, edges, faces, shells, solids, vertices, smoothPatchCount()

### Community 74 - "QString"
Cohesion: 0.11
Nodes (6): ExpressionSpinBox, eval_, expression_, shown_, formatNumber(), dimensionOf()

### Community 75 - "InputType"
Cohesion: 0.12
Nodes (17): InputType, Axis, Bodies, Body, Bool, Choice, Edges, Faces (+9 more)

### Community 76 - ".redrawAll"
Cohesion: 0.14
Nodes (8): NavPreset, Fusion, SolidWorks, Tinkercad, Viewport::setCurvatureComb(), Viewport::clearDragArrow(), Viewport::clearSecondArrow(), Viewport::setInteractor()

### Community 79 - "TEST"
Cohesion: 0.19
Nodes (3): slurp(), TEST(), tmp()

### Community 80 - "SketchDisplay"
Cohesion: 0.08
Nodes (18): DragArrow, base, dir, value, PendingLook, center, frame, size (+10 more)

### Community 81 - "string"
Cohesion: 0.15
Nodes (15): bodyNumber(), Document::component(), Document::componentOfBody(), Document::nextAxisName(), Document::nextBodyName(), Document::nextComponentName(), Document::nextPlaneName(), Document::nextPointName() (+7 more)

### Community 82 - "Measurement"
Cohesion: 0.13
Nodes (14): Kind, Angle, Area, Length, Volume, Measurement, from, hasLine (+6 more)

### Community 83 - "rect"
Cohesion: 0.28
Nodes (3): SelectionBox, crossing, rect()

### Community 84 - "Entity"
Cohesion: 0.22
Nodes (9): Entity, a, b, center, construction, fit, projected, radius (+1 more)

### Community 85 - "Level"
Cohesion: 0.12
Nodes (13): debug(), error(), info(), Level, Debug, Error, Info, Warning (+5 more)

### Community 86 - "README.md"
Cohesion: 0.10
Nodes (16): Build, Conventions, Development, Tests, Known gaps, Reference parts, Fusion feature checklist, Roadmap (+8 more)

### Community 87 - "QDialog"
Cohesion: 0.18
Nodes (5): QDialog, MainWindow::exportDesign(), MainWindow::measurePick(), MainWindow::openMeasure(), toolWindow()

### Community 91 - "Sketch.h"
Cohesion: 0.18
Nodes (7): CommandRegistry::all(), EntityType, Arc, Circle, Line, Spline, isRound()

### Community 93 - "Known differences still to build"
Cohesion: 0.15
Nodes (12): Data and files, Findings from the videos, Fusion study list, Interface, Known differences still to build, Navigation and display, Selection and the canvas, Sketch (+4 more)

### Community 96 - "TsrModule.cpp"
Cohesion: 0.25
Nodes (4): bindTsr(), fromPy(), toPy(), typeName()

### Community 97 - "string"
Cohesion: 0.08
Nodes (41): BodyFrame, diag, dx, dy, dz, x0, y0, z0 (+33 more)

### Community 98 - "FakeDoc"
Cohesion: 0.17
Nodes (6): FakeDoc, aborts, commits, items, open, snapshot

### Community 99 - "DocCommands.cpp"
Cohesion: 0.08
Nodes (27): applyOperation(), axisOf(), CopyFn, differenceOrNull(), InsertGeometry, def_, Loft, def_ (+19 more)

### Community 100 - "Zip.cpp"
Cohesion: 0.17
Nodes (11): Entry, data, name, ZipError, crc32(), get16(), get32(), put16() (+3 more)

### Community 101 - "Feature"
Cohesion: 0.22
Nodes (9): Feature, commandId, error, id, inputs, name, rolledBack, suppressed (+1 more)

### Community 102 - "Axis"
Cohesion: 0.50
Nodes (4): Axis, X, Y, Z

### Community 103 - "DocumentError"
Cohesion: 0.08
Nodes (16): DocumentError, doc_(), Document::addBody(), Document::axisFrame(), Document::bodyShapes(), Document::Document(), Document::effectOf(), Document::evaluate() (+8 more)

### Community 104 - "BooleanOp"
Cohesion: 0.50
Nodes (4): BooleanOp, Cut, Intersect, Join

### Community 105 - "ConstructionAxis"
Cohesion: 0.29
Nodes (5): ConstructionAxis, axis, name, Document::axis(), Document::setAxis()

### Community 106 - "SectionState"
Cohesion: 0.25
Nodes (7): SectionState, active, angle, flip, offset, plane, visible

### Community 107 - "Display"
Cohesion: 0.25
Nodes (7): Display, constraints, construction, dimensions, points, profiles, projected

### Community 108 - "ThreadInfo"
Cohesion: 0.50
Nodes (4): ThreadInfo, diameter, internal, pitch

### Community 109 - ".requireTransaction"
Cohesion: 0.11
Nodes (22): SketchRecord, data, name, offset, plane, Document::abortTransaction(), Document::addUserParameter(), Document::commitTransaction() (+14 more)

### Community 110 - "openWallBand"
Cohesion: 0.10
Nodes (20): BoundingBox, max, min, Section, Circular, Square, Triangular, WallSide (+12 more)

### Community 111 - "exportShapes"
Cohesion: 0.47
Nodes (7): MainWindow::print3d(), NamedShape, compoundOf(), exportShapes(), fmt(), write3mf(), writeObj()

### Community 112 - "ConstructionPoint"
Cohesion: 0.29
Nodes (5): ConstructionPoint, name, point, Document::point(), Document::setPoint()

### Community 113 - "main"
Cohesion: 0.36
Nodes (4): listCommands(), main(), usage(), main()

### Community 114 - "uninstall.sh"
Cohesion: 0.52
Nodes (6): die(), manifest_for(), refresh(), uninstall.sh script, step(), usage()

### Community 115 - "install.sh"
Cohesion: 0.60
Nodes (5): die(), refresh(), install.sh script, step(), usage()

### Community 117 - "Column"
Cohesion: 0.33
Nodes (6): Column, kComment, kExpression, kParameter, kUnit, kValue

### Community 118 - "ChamferType"
Cohesion: 0.67
Nodes (3): ChamferType, DistanceAngle, TwoDistances

### Community 123 - "functional"
Cohesion: 0.29
Nodes (3): MarkingMenu, enabled, public

### Community 124 - "Document::reevaluateParameters"
Cohesion: 0.38
Nodes (3): Document::expressionEnv(), Document::reevaluateParameters(), Document::save()

### Community 125 - "Architecture"
Cohesion: 0.40
Nodes (4): Architecture, How a command works, The document, Units

### Community 127 - "smoke"
Cohesion: 0.40
Nodes (5): smoke(), MassProperties, area, centerOfMass, volume

### Community 128 - "Mesh"
Cohesion: 0.40
Nodes (3): Mesh, nodes, triangles

### Community 132 - "ChainSegment"
Cohesion: 0.67
Nodes (3): ChainSegment, entity, forward

## Knowledge Gaps
- **637 isolated node(s):** `ok`, `output`, `error`, `isReal`, `real` (+632 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 1206 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **34 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `optional` connect `optional` to `Viewport`, `MainWindow`, `Inputs`, `Kernel.cpp`, `Io.cpp`, `Unit`, `Unit`, `ViewportSketch.cpp`, `.hitTest`, `SketchOps.cpp`, `Viewport.h`, `Document.cpp`, `Session`, `InputDef`, `ViewportAnalysis.cpp`, `ViewportArrow.cpp`, `Vec3`, `CommandDialog.cpp`, `QString`, `SketchDisplay`, `string`, `DocCommands.cpp`, `Feature`, `ConstructionAxis`, `.requireTransaction`, `ConstructionPoint`?**
  _High betweenness centrality (0.131) - this node is a cross-community bridge._
- **What connects `ok`, `output`, `error` to the rest of the system?**
  _637 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Viewport` be split into smaller, more focused modules?**
  _Cohesion score 0.01832013662474771 - nodes in this community are weakly interconnected._
- **Why does `Viewport` connect `Viewport` to `Viewport.h`, `ParametersDialog.cpp`, `Viewport.cpp`, `optional`, `.redrawAll`, `.initializeGL`, `fromInternal`, `SketchDisplay`, `rect`, `.toPixels`, `ViewportAnalysis.cpp`, `.selectedSubShapes`, `ViewportArrow.cpp`?**
  _High betweenness centrality (0.128) - this node is a cross-community bridge._
- **Should `Icons.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.06538461538461539 - nodes in this community are weakly interconnected._
- **Why does `MainWindow` connect `MainWindow` to `.openMarkingMenu`, `ParameterCompleter`, `.showDialog`, `MarkingMenu.cpp`, `src/main.cpp`, `MainWindow::MainWindow`, `SectionState`, `optional`, `fromInternal`, `MainWindowTools.cpp`, `Session`, `MainWindowSketch.cpp`, `MainWindow.cpp`, `QDialog`, `SketchPalette`, `smoke`?**
  _High betweenness centrality (0.098) - this node is a cross-community bridge._
- **Should `Command` be split into smaller, more focused modules?**
  _Cohesion score 0.12473118279569892 - nodes in this community are weakly interconnected._