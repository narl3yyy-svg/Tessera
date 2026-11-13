# Graph Report - tessera  (2026-11-13)

## Corpus Check
- 341 files · ~197,257 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 34 file(s) not represented in the graph (top: .drive 26, (none) 5, .cmake 1)

## Summary
- 3158 nodes · 7898 edges · 136 communities (101 shown, 35 thin omitted)
- Extraction: 85% EXTRACTED · 15% INFERRED · 0% AMBIGUOUS · INFERRED: 1224 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `2aed0a37`
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
- Unit
- optional
- Kernel.cpp
- .projectAt
- Kind
- MainWindowTools.cpp
- CommandDialog
- Io.cpp
- Unit
- DocCommands.cpp
- .press
- ConstructAxisPoint
- MainWindow.cpp
- TEST
- Sketch.cpp
- ViewportSketch.cpp
- SketchPalette
- SketchEditor.cpp
- .apply
- AdskModule.cpp
- Colors
- KernelError
- SketchOps.cpp
- Session.cpp
- ParameterCompleter
- ViewportAnalysis.cpp
- CommandDialog.cpp
- Viewport.h
- solve
- MarkingMenu.cpp
- src/main.cpp
- ConstraintType
- DocCommands.h
- Pick
- Snap
- Kind
- Command.cpp
- Document.cpp
- Session
- MainWindowSketch.cpp
- InputDef
- commonDef
- .toPixels
- ViewportAnalysis.cpp
- CommandSession
- Theme.cpp
- FeatureEffect
- Constraint
- xdrive.py
- SketchGeometry.cpp
- MainWindow::MainWindow
- ViewportArrow.cpp
- string
- CommandRegistry
- PythonHost.cpp
- TopoDS_Shape
- Theme
- FileFormat
- .planeFrame
- ParametersDialog.cpp
- planeOf
- QTimer
- ExpressionSpinBox
- InputType
- .redrawAll
- QMouseEvent
- TEST
- SketchDisplay
- string
- Measurement
- rect
- Entity
- Level
- README.md
- QObject
- MainWindow::buildUiCommands
- cmath
- Known differences still to build
- SketchEditor::SketchEditor
- .add
- TsrModule.cpp
- BodyFrame
- FakeDoc
- CommandError
- Zip.cpp
- .rebuild
- Kernel.h
- Document::load
- quantityOf
- nameOf
- SectionState
- Display
- ConstructionPlane
- .requireTransaction
- openWallBand
- Rect
- ConstructionAxis
- main
- uninstall.sh
- install.sh
- NewComponent
- Session::addListener
- Feature
- choice
- MainWindow::enterSketchMode
- Column
- Value.h
- .CircularPattern
- Mesh
- ChainSegment
- LAB_NOTES.md
- build.sh
- live-test.sh

## God Nodes (most connected - your core abstractions)
1. `Viewport` - 227 edges
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

## Communities (136 total, 35 thin omitted)

### Community 0 - "Viewport"
Cohesion: 0.02
Nodes (56): view_, Viewport, analysis_, analysisObjects_, appliedGridStep_, arrowBoxes_, arrowDragging_, arrowGrab_ (+48 more)

### Community 1 - "Icons.cpp"
Cohesion: 0.07
Nodes (91): arcIcon(), arrow(), axisIcon(), box(), centerRectIcon(), chamferIcon(), circleIcon(), coilIcon() (+83 more)

### Community 2 - "DocCommands.cpp"
Cohesion: 0.04
Nodes (54): Adding a tool, Command, CommandDef, feature, icon, id, inputs, name (+46 more)

### Community 4 - "MainWindow"
Cohesion: 0.03
Nodes (61): CommandDialog, MainWindow, active_, arrowInput_, arrowInput2_, bodiesBeforeCommand_, combEdges_, combPicking_ (+53 more)

### Community 5 - "run_oracle.py"
Cohesion: 0.08
Nodes (54): add_point(), arc_poly(), body_at(), body_list(), build_sketch(), chain(), circumcentre(), cm() (+46 more)

### Community 6 - "Inputs"
Cohesion: 0.08
Nodes (12): CommandContext, Inputs, CommandSession::CommandSession(), checkBody(), checkPattern(), defaultBody(), Hole, def_ (+4 more)

### Community 7 - "Document"
Cohesion: 0.04
Nodes (13): Document, effects_, modified_, pendingTools_, registry_, replaying_, txnBodies_, FromOcaf (+5 more)

### Community 8 - "Viewport.cpp"
Cohesion: 0.06
Nodes (5): keys(), qc(), QtFrameBuffer, rgb(), Viewport::Viewport()

### Community 9 - "SketchEditor"
Cohesion: 0.04
Nodes (41): SketchEditor, arcDrag_, arcDragMoved_, arcEndsChain_, arcFrom_, arcRef_, bodyEdges_, boxing_ (+33 more)

### Community 10 - "Unit"
Cohesion: 0.08
Nodes (35): bindAdsk(), MainWindow::checkInterference(), MainWindow::driveJoints(), MainWindow::formatLength(), MainWindow::gridSettings(), MainWindow::lengthUnit(), MainWindow::openAnalysis(), MainWindow::openSection() (+27 more)

### Community 13 - ".projectAt"
Cohesion: 0.22
Nodes (4): PlaneEdges, arcs, segments, vertices

### Community 14 - "Kind"
Cohesion: 0.12
Nodes (16): Kind, Angle, AxisCylinder, AxisEdge, AxisTwoPlanes, AxisTwoPoints, Chamfer, Draft (+8 more)

### Community 15 - "MainWindowTools.cpp"
Cohesion: 0.06
Nodes (15): QAbstractButton, QAction, QDialog, MainWindow::chooseUnits(), MainWindow::exportDesign(), MainWindow::insertFile(), MainWindow::measurePick(), MainWindow::openMeasure() (+7 more)

### Community 16 - "CommandDialog"
Cohesion: 0.04
Nodes (31): CommandDialog, bodiesId_, bodiesLabel_, bodyInput_, buttons_, cmd_, conditional_, edgesId_ (+23 more)

### Community 17 - "Io.cpp"
Cohesion: 0.11
Nodes (15): MainWindow::print3d(), NamedShape, compoundOf(), exportShapes(), fmt(), formatForPath(), fromBrep(), importShape() (+7 more)

### Community 18 - "Unit"
Cohesion: 0.09
Nodes (29): ExpressionEnv, lengthUnit, lookup, ExpressionError, Quantity, angle, length, value (+21 more)

### Community 19 - "DocCommands.cpp"
Cohesion: 0.14
Nodes (20): getReal(), axisOf(), CopyFn, makeBox(), makeCone(), makeCylinder(), makeSphere(), makeTorus() (+12 more)

### Community 21 - "ConstructAxisPoint"
Cohesion: 0.22
Nodes (5): ConstructAxisPoint, def_, kind_, JointPick, frame

### Community 22 - "MainWindow.cpp"
Cohesion: 0.08
Nodes (5): commandIcon(), qs(), MainWindow::beginSketch(), MainWindow::exitSketchMode(), MainWindow::applySection()

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
Cohesion: 0.07
Nodes (25): QCheckBox, QLabel, QToolButton, QWidget, SketchEditor, SketchPalette, body_, constraints_ (+17 more)

### Community 28 - ".apply"
Cohesion: 0.18
Nodes (4): Extrude, def_, Joint, def_

### Community 29 - "AdskModule.cpp"
Cohesion: 0.10
Nodes (15): Application, BRepBodies, BRepBody, index, Component, Design, Product, raiseIfError() (+7 more)

### Community 30 - "Colors"
Cohesion: 0.07
Nodes (28): Colors, base, border, cubeBox, cubeText, errorBackground, grid, gridMajor (+20 more)

### Community 31 - "KernelError"
Cohesion: 0.24
Nodes (25): KernelError, WallSide, Center, Side1, Side2, boolean(), chamfer(), chamferEx() (+17 more)

### Community 32 - "SketchOps.cpp"
Cohesion: 0.21
Nodes (19): at(), chainOf(), chamferCorner(), cornerAt(), cross(), dot(), extendLine(), filletCorner() (+11 more)

### Community 33 - "Session.cpp"
Cohesion: 0.19
Nodes (18): historyEdit(), Session::deleteFeature(), Session::deleteParameter(), Session::editFeature(), Session::newDocument(), Session::open(), Session::redo(), Session::renameBody() (+10 more)

### Community 34 - "ParameterCompleter"
Cohesion: 0.12
Nodes (9): MainWindow::attachArrowCompleters(), ParameterCompleter, completer_, edit_, names_, ParameterCompleter::ParameterCompleter(), public, QCompleter (+1 more)

### Community 35 - "ViewportAnalysis.cpp"
Cohesion: 0.12
Nodes (5): packed(), ramp(), shade(), Viewport::buildAnalysis(), Viewport::setCurvatureComb()

### Community 37 - "Viewport.h"
Cohesion: 0.07
Nodes (15): AnalysisKind, CurvatureMap, Draft, None, Zebra, AnalysisSettings, curvatureScale, draftAngle (+7 more)

### Community 38 - "solve"
Cohesion: 0.18
Nodes (12): addConstraintChecked(), Layout, n, px, py, rad, makeLayout(), pack() (+4 more)

### Community 39 - "MarkingMenu.cpp"
Cohesion: 0.07
Nodes (19): UiCommand, enabled, icon, id, name, panel, run, shortcut (+11 more)

### Community 40 - "src/main.cpp"
Cohesion: 0.08
Nodes (8): grabWindowWithPanels(), main(), smoke(), writeLiveGeometry(), MarkingMenu, enabled, public, volume

### Community 41 - "ConstraintType"
Cohesion: 0.09
Nodes (23): ConstraintType, Angle, Coincident, Collinear, Concentric, Diameter, Distance, Equal (+15 more)

### Community 43 - "Pick"
Cohesion: 0.12
Nodes (15): Hit, index, kind, Pick, bodyArc, bodyPoint, bodySegment, hit (+7 more)

### Community 44 - "Snap"
Cohesion: 0.11
Nodes (18): Snap, alignX, alignY, bodyArc, bodySegment, entity, fromX, fromY (+10 more)

### Community 45 - "Kind"
Cohesion: 0.09
Nodes (21): HudField, edit, editing, kind, locked, value, Kind, Angle (+13 more)

### Community 47 - "Command.cpp"
Cohesion: 0.23
Nodes (10): expressionKey(), checkInputValue(), CommandDef::input(), CommandSession::applyInTransaction(), CommandSession::cancel(), CommandSession::execute(), CommandSession::preview(), CommandSession::setInput() (+2 more)

### Community 48 - "Document.cpp"
Cohesion: 0.09
Nodes (9): bodyNumber(), Document::axisFrame(), Document::body(), Document::component(), Document::componentOfBody(), Document::nextBodyName(), Document::redo(), Document::setComponent() (+1 more)

### Community 49 - "Session"
Cohesion: 0.06
Nodes (7): Session, commands_, doc_, listeners_, nextListener_, path_, TEST()

### Community 50 - "MainWindowSketch.cpp"
Cohesion: 0.09
Nodes (13): MainWindow::cancelSketch(), MainWindow::editSketch(), MainWindow::finishSketch(), MainWindow::onEdgeClicked(), MainWindow::onProfileClicked(), MainWindow::originalShape(), MainWindow::sketchPalette(), MainWindow::sketchVisible() (+5 more)

### Community 51 - "InputDef"
Cohesion: 0.12
Nodes (13): InputDef, choices, defaultValue, id, label, max, min, minExclusive (+5 more)

### Community 52 - "commonDef"
Cohesion: 0.22
Nodes (4): bodyInput(), commonDef(), planeChoice(), planeOffset()

### Community 54 - "ViewportAnalysis.cpp"
Cohesion: 0.10
Nodes (8): ArrowPlacement, base, dir, edgePlacement(), facesPlacement(), MainWindow::patternCentre(), MainWindow::pickedFaces(), MainWindow::updateDragArrow()

### Community 55 - "CommandSession"
Cohesion: 0.12
Nodes (8): CommandSession, inputs_, CommandRegistry::find(), CommandRegistry::run(), OwnedCommand, owned, OwningCommandSession, Session::begin()

### Community 56 - "Theme.cpp"
Cohesion: 0.19
Nodes (6): setIconTheme(), darkColors(), darkPalette(), darkStyleSheet(), lightColors(), lightStyleSheet()

### Community 57 - "FeatureEffect"
Cohesion: 0.07
Nodes (22): Body, display, name, shape, Component, bodies, name, FeatureEffect (+14 more)

### Community 58 - "Constraint"
Cohesion: 0.11
Nodes (17): Constraint, entities, expression, points, type, value, value2, SolveResult (+9 more)

### Community 59 - "xdrive.py"
Cohesion: 0.32
Nodes (14): button(), canvas(), click(), drag(), flush(), geometry(), key(), keycode() (+6 more)

### Community 61 - "SketchGeometry.cpp"
Cohesion: 0.09
Nodes (14): Profile, area, face, x, y, curve(), curves(), customPlaneSpec() (+6 more)

### Community 62 - "MainWindow::MainWindow"
Cohesion: 0.14
Nodes (4): PythonHost, flatButton(), MainWindow::MainWindow(), MainWindow::showPreferences()

### Community 63 - "ViewportArrow.cpp"
Cohesion: 0.08
Nodes (15): Viewport::frontEdgeOwner(), rgb(), segmentDistance(), Viewport::arrowAt(), Viewport::arrowMouseMove(), Viewport::arrowMousePress(), Viewport::arrowMouseRelease(), Viewport::arrowParam() (+7 more)

### Community 64 - "string"
Cohesion: 0.10
Nodes (30): completeEdgeReferences(), completeFaceReferences(), decode(), decodeFaces(), dot(), edgeReference(), EdgeSig, full (+22 more)

### Community 65 - "CommandRegistry"
Cohesion: 0.12
Nodes (4): CommandRegistry, cmds_, CommandRegistry::add(), TEST()

### Community 66 - "PythonHost.cpp"
Cohesion: 0.17
Nodes (9): Result, error, ok, output, captured(), PythonHost::exec(), PythonHost::PythonHost(), PythonHost::runScript() (+1 more)

### Community 67 - "TopoDS_Shape"
Cohesion: 0.15
Nodes (24): SurfacePoint, normal, point, Vec3, asSolid(), boundingBox(), edgeMidpoint(), edgesNear() (+16 more)

### Community 68 - "Theme"
Cohesion: 0.22
Nodes (4): Theme, colors_, public, styled_

### Community 69 - "FileFormat"
Cohesion: 0.17
Nodes (12): FileFormat, Brep, Iges, Obj, Step, Stl, ThreeMF, FormatInfo (+4 more)

### Community 70 - ".planeFrame"
Cohesion: 0.21
Nodes (6): Loft, def_, profilesOf(), profiles, Sweep, def_

### Community 71 - "ParametersDialog.cpp"
Cohesion: 0.08
Nodes (15): number(), ParametersDialog, building_, error_, listener_, ParametersDialog::ParametersDialog(), public, rebuildPending_ (+7 more)

### Community 72 - "planeOf"
Cohesion: 0.33
Nodes (6): Coil, def_, planeOf(), x, y, z

### Community 74 - "ExpressionSpinBox"
Cohesion: 0.16
Nodes (4): ExpressionSpinBox, eval_, expression_, shown_

### Community 75 - "InputType"
Cohesion: 0.12
Nodes (17): InputType, Axis, Bodies, Body, Bool, Choice, Edges, Faces (+9 more)

### Community 76 - ".redrawAll"
Cohesion: 0.18
Nodes (7): NavPreset, Fusion, SolidWorks, Tinkercad, Viewport::clearDragArrow(), Viewport::clearSecondArrow(), Viewport::setInteractor()

### Community 77 - "QMouseEvent"
Cohesion: 0.24
Nodes (3): MarkingMenu::mouseMoveEvent(), QMouseEvent, ViewInteractor

### Community 79 - "TEST"
Cohesion: 0.22
Nodes (3): slurp(), TEST(), tmp()

### Community 80 - "SketchDisplay"
Cohesion: 0.08
Nodes (18): DragArrow, base, dir, value, PendingLook, center, frame, size (+10 more)

### Community 81 - "string"
Cohesion: 0.17
Nodes (16): Document::addBody(), Document::bodyName(), Document::bodyShapes(), Document::effectOf(), Document::lengthUnit(), Document::nextAxisName(), Document::nextComponentName(), Document::nextPlaneName() (+8 more)

### Community 82 - "Measurement"
Cohesion: 0.09
Nodes (20): BoundingBox, max, min, Kind, Angle, Area, Length, Volume (+12 more)

### Community 83 - "rect"
Cohesion: 0.28
Nodes (3): SelectionBox, crossing, rect()

### Community 84 - "Entity"
Cohesion: 0.22
Nodes (9): Entity, a, b, center, construction, fit, projected, radius (+1 more)

### Community 85 - "Level"
Cohesion: 0.16
Nodes (13): debug(), error(), info(), Level, Debug, Error, Info, Warning (+5 more)

### Community 86 - "README.md"
Cohesion: 0.08
Nodes (20): Architecture, How a command works, The document, Units, Build, Conventions, Development, Tests (+12 more)

### Community 91 - "cmath"
Cohesion: 0.10
Nodes (12): CommandRegistry::all(), EntityType, Arc, Circle, Line, Spline, isRound(), Case (+4 more)

### Community 93 - "Known differences still to build"
Cohesion: 0.15
Nodes (12): Data and files, Findings from the videos, Fusion study list, Interface, Known differences still to build, Navigation and display, Selection and the canvas, Sketch (+4 more)

### Community 96 - "TsrModule.cpp"
Cohesion: 0.25
Nodes (4): bindTsr(), fromPy(), toPy(), typeName()

### Community 97 - "BodyFrame"
Cohesion: 0.15
Nodes (14): BodyFrame, diag, dx, dy, dz, x0, y0, z0 (+6 more)

### Community 98 - "FakeDoc"
Cohesion: 0.17
Nodes (6): FakeDoc, aborts, commits, items, open, snapshot

### Community 99 - "CommandError"
Cohesion: 0.10
Nodes (21): CommandError, getBool(), getInt(), applyOperation(), bodyCentre(), bodyName(), differenceOrNull(), jointOrigin() (+13 more)

### Community 100 - "Zip.cpp"
Cohesion: 0.19
Nodes (11): Entry, data, name, ZipError, crc32(), get16(), get32(), put16() (+3 more)

### Community 101 - ".rebuild"
Cohesion: 0.36
Nodes (5): fixedColor(), freeColor(), qc(), rgb(), wire()

### Community 102 - "Kernel.h"
Cohesion: 0.11
Nodes (18): Axis, X, Y, Z, BooleanOp, Cut, Intersect, Join (+10 more)

### Community 103 - "Document::load"
Cohesion: 0.17
Nodes (5): doc_(), Document::Document(), Document::ocafBytes(), ocafApplication(), Document::load()

### Community 104 - "quantityOf"
Cohesion: 0.31
Nodes (5): quantityOf(), Document::expressionEnv(), Document::reevaluateParameters(), Document::userParameter(), Document::save()

### Community 105 - "nameOf"
Cohesion: 0.16
Nodes (22): SketchRecord, data, name, offset, plane, Document::axes(), Document::bodies(), Document::components() (+14 more)

### Community 106 - "SectionState"
Cohesion: 0.25
Nodes (7): SectionState, active, angle, flip, offset, plane, visible

### Community 107 - "Display"
Cohesion: 0.25
Nodes (7): Display, constraints, construction, dimensions, points, profiles, projected

### Community 108 - "ConstructionPlane"
Cohesion: 0.40
Nodes (5): ConstructionPlane, name, spec, Document::plane(), Document::setPlane()

### Community 109 - ".requireTransaction"
Cohesion: 0.13
Nodes (22): DocumentError, Document::abortTransaction(), Document::addUserParameter(), Document::commitTransaction(), Document::openTransaction(), Document::recompute(), Document::recordFeature(), Document::removeFeature() (+14 more)

### Community 110 - "openWallBand"
Cohesion: 0.15
Nodes (19): Section, Circular, Square, Triangular, TopologyCounts, edges, faces, shells (+11 more)

### Community 111 - "Rect"
Cohesion: 0.50
Nodes (4): Session::notifyChanged(), Rect, l, p

### Community 112 - "ConstructionAxis"
Cohesion: 0.14
Nodes (11): ConstructionAxis, axis, name, ConstructionPoint, name, point, Document::axis(), Document::point() (+3 more)

### Community 113 - "main"
Cohesion: 0.24
Nodes (3): listCommands(), main(), usage()

### Community 114 - "uninstall.sh"
Cohesion: 0.52
Nodes (6): die(), manifest_for(), refresh(), uninstall.sh script, step(), usage()

### Community 115 - "install.sh"
Cohesion: 0.60
Nodes (5): die(), refresh(), install.sh script, step(), usage()

### Community 118 - "Feature"
Cohesion: 0.22
Nodes (9): Feature, commandId, error, id, inputs, name, rolledBack, suppressed (+1 more)

### Community 126 - "Column"
Cohesion: 0.33
Nodes (6): Column, kComment, kExpression, kParameter, kUnit, kValue

### Community 129 - "Mesh"
Cohesion: 0.40
Nodes (3): Mesh, nodes, triangles

### Community 132 - "ChainSegment"
Cohesion: 0.67
Nodes (3): ChainSegment, entity, forward

## Knowledge Gaps
- **638 isolated node(s):** `ok`, `output`, `error`, `isReal`, `real` (+633 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 1210 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **35 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `optional` connect `optional` to `Viewport`, `MainWindow`, `Inputs`, `Unit`, `Kernel.cpp`, `Io.cpp`, `Unit`, `DocCommands.cpp`, `ViewportSketch.cpp`, `SketchEditor.cpp`, `SketchOps.cpp`, `CommandDialog.cpp`, `Viewport.h`, `Document.cpp`, `Session`, `InputDef`, `ViewportAnalysis.cpp`, `ViewportArrow.cpp`, `TopoDS_Shape`, `ExpressionSpinBox`, `SketchDisplay`, `Kernel.h`, `quantityOf`, `nameOf`, `ConstructionPlane`, `ConstructionAxis`, `Feature`?**
  _High betweenness centrality (0.132) - this node is a cross-community bridge._
- **What connects `ok`, `output`, `error` to the rest of the system?**
  _638 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Viewport` be split into smaller, more focused modules?**
  _Cohesion score 0.01815408085430969 - nodes in this community are weakly interconnected._
- **Why does `Viewport` connect `Viewport` to `ViewportAnalysis.cpp`, `MainWindow`, `Viewport.h`, `MarkingMenu.cpp`, `Viewport.cpp`, `QTimer`, `Unit`, `optional`, `.redrawAll`, `QMouseEvent`, `SketchDisplay`, `rect`, `.toPixels`, `.selectedSubShapes`, `ViewportArrow.cpp`?**
  _High betweenness centrality (0.128) - this node is a cross-community bridge._
- **Should `Icons.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.06853038245000971 - nodes in this community are weakly interconnected._
- **Why does `MainWindow` connect `MainWindow` to `ParameterCompleter`, `MainWindow::buildUiCommands`, `MarkingMenu.cpp`, `src/main.cpp`, `SectionState`, `optional`, `Unit`, `MainWindowTools.cpp`, `Session`, `MainWindowSketch.cpp`, `MainWindow.cpp`, `ViewportAnalysis.cpp`, `.buildAppBar`, `SketchPalette`, `.eventFilter`, `MainWindow::enterSketchMode`, `MainWindow::MainWindow`?**
  _High betweenness centrality (0.098) - this node is a cross-community bridge._
- **Should `DocCommands.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.03934871099050204 - nodes in this community are weakly interconnected._