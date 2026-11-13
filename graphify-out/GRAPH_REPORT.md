# Graph Report - tessera  (2026-11-13)

## Corpus Check
- 365 files · ~223,731 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 50 file(s) not represented in the graph (top: .drive 42, (none) 5, .cmake 1)

## Summary
- 3418 nodes · 8581 edges · 146 communities (115 shown, 31 thin omitted)
- Extraction: 85% EXTRACTED · 15% INFERRED · 0% AMBIGUOUS · INFERRED: 1278 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `6648309e`
- Run `git rev-parse HEAD` and compare to check if the graph is stale.
- Run `graphify update .` after code changes (no API cost).

## Community Hubs (Navigation)
- Viewport
- Icons.cpp
- Session.cpp
- MainWindow
- run_oracle.py
- Inputs
- Document
- Viewport.cpp
- SketchEditor
- .press
- optional
- Kernel.cpp
- DocCommands.cpp
- Kind
- .openMarkingMenu
- CommandDialog
- Io.cpp
- Unit
- MainWindowTools.cpp
- string
- Document
- MainWindow::MainWindow
- TEST
- Sketch.cpp
- ViewportSketch.cpp
- SketchPalette
- Snap
- .apply
- AdskModule.cpp
- Colors
- KernelError
- SketchOps.cpp
- Unit
- ParameterCompleter
- Constraint
- Expression.cpp
- MainWindow.cpp
- solve
- ViewportAnalysis.cpp
- .rebuild
- ConstraintType
- fromInternal
- Pick
- .mouseMove
- Kind
- Zip.cpp
- AnalysisSettings
- Document.cpp
- SketchRecord
- MainWindowSketch.cpp
- InputDef
- DocCommands.h
- .toPixels
- MainWindowArrow.cpp
- Viewport.h
- Theme.cpp
- TEST
- Entity
- xdrive.py
- SketchGeometry.cpp
- Session
- ViewportArrow.cpp
- BodyFrame
- CommandRegistry
- cmath
- TopoDS_Shape
- Theme
- ext
- src/main.cpp
- src/main.cpp
- FileFormat
- InputType
- string
- QString
- math
- SketchDisplay
- DocCommands.cpp
- Measurement
- .redrawAll
- Axis
- Level
- README.md
- DocumentError
- test_feature_pattern.py
- Tool
- .add
- MarkingMenu.cpp
- CommandSession
- Known differences still to build
- Value.h
- Feature
- UserParameter
- WallSide
- FakeDoc
- CommandDialog.cpp
- .buildAppBar
- string
- sstream
- rect
- Command.cpp
- QTimer
- SectionState
- Display
- TestFramework.h
- PlaneEdges
- openWallBand
- ConstructionPoint
- ConstructionAxis
- uninstall.sh
- install.sh
- PYBIND11_EMBEDDED_MODULE
- main
- AnalysisSettings
- Sketch.h
- Column
- QObject
- BooleanOp
- Placement
- ChainSegment
- ThreadInfo
- ChamferType
- Joints
- ParametersDialog.h
- Document::nameFeatureParameters
- CommandDialog::CommandDialog
- LAB_NOTES.md
- .attach
- bindAdsk
- build.sh
- live-test.sh
- NamedView
- QDialog
- Profile
- MarkingMenu
- Joint
- Session::addListener

## God Nodes (most connected - your core abstractions)
1. `Viewport` - 251 edges
2. `SketchEditor` - 177 edges
3. `MainWindow` - 175 edges
4. `Inputs` - 138 edges
5. `Document` - 104 edges
6. `render()` - 102 edges
7. `CommandContext` - 102 edges
8. `CommandDialog` - 90 edges
9. `Command` - 63 edges
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

## Communities (146 total, 31 thin omitted)

### Community 0 - "Viewport"
Cohesion: 0.02
Nodes (67): view_, QLineEdit, Viewport, analysis_, analysisObjects_, appliedGridStep_, arrowBoxes_, arrowDragging_ (+59 more)

### Community 1 - "Icons.cpp"
Cohesion: 0.06
Nodes (105): arc3Icon(), arcIcon(), arrow(), axisIcon(), box(), breakIcon(), centerRectIcon(), chamferIcon() (+97 more)

### Community 2 - "Session.cpp"
Cohesion: 0.18
Nodes (23): historyEdit(), plainEdit(), Session::addNamedView(), Session::deleteFeature(), Session::deleteNamedView(), Session::deleteParameter(), Session::newDocument(), Session::open() (+15 more)

### Community 4 - "MainWindow"
Cohesion: 0.03
Nodes (63): CommandDialog, MainWindow, active_, arrowInput_, arrowInput2_, bodiesBeforeCommand_, combEdges_, combPicking_ (+55 more)

### Community 5 - "run_oracle.py"
Cohesion: 0.08
Nodes (54): add_point(), arc_poly(), body_at(), body_list(), build_sketch(), chain(), circumcentre(), cm() (+46 more)

### Community 6 - "Inputs"
Cohesion: 0.09
Nodes (16): CommandContext, CommandError, Inputs, CommandSession::CommandSession(), getBool(), getInt(), getReal(), bodyCentre() (+8 more)

### Community 7 - "Document"
Cohesion: 0.03
Nodes (16): Body, display, name, shape, Document, effects_, modified_, pendingTools_ (+8 more)

### Community 8 - "Viewport.cpp"
Cohesion: 0.05
Nodes (3): glide(), keys(), QtFrameBuffer

### Community 9 - "SketchEditor"
Cohesion: 0.03
Nodes (45): SketchEditor, arcDrag_, arcDragMoved_, arcEndsChain_, arcFrom_, arcRef_, bodyEdges_, boxing_ (+37 more)

### Community 13 - "DocCommands.cpp"
Cohesion: 0.09
Nodes (28): axisOf(), CopyFn, differenceOrNull(), evaluateDimensions(), HoleSize, modeled, pitch, radius (+20 more)

### Community 14 - "Kind"
Cohesion: 0.09
Nodes (22): ConstructPlane, def_, kind_, EdgeFeature, def_, kind_, Kind, Angle (+14 more)

### Community 16 - "CommandDialog"
Cohesion: 0.05
Nodes (31): CommandDialog, bodiesId_, bodiesLabel_, bodyInput_, buttons_, cmd_, conditional_, edgesId_ (+23 more)

### Community 17 - "Io.cpp"
Cohesion: 0.10
Nodes (18): MainWindow::print3d(), NamedShape, compoundOf(), exportShapes(), fmt(), formatForPath(), fromBrep(), importShape() (+10 more)

### Community 18 - "Unit"
Cohesion: 0.18
Nodes (14): Quantity, angle, length, value, describe(), isIdentChar(), isIdentStart(), Parser (+6 more)

### Community 19 - "MainWindowTools.cpp"
Cohesion: 0.07
Nodes (11): MainWindow::chooseUnits(), MainWindow::insertFile(), MainWindow::measurePick(), MainWindow::openAnalysis(), MainWindow::openMeasure(), MainWindow::sectionFrame(), MainWindow::sectionPlane(), MainWindow::setSelectionFilter() (+3 more)

### Community 20 - "string"
Cohesion: 0.10
Nodes (14): AddUserParameter, def_, isIdentifier(), NewComponent, def_, Pipe, def_, Revolve (+6 more)

### Community 21 - "Document"
Cohesion: 0.20
Nodes (9): applyOperation(), ConstructAxisPoint, def_, kind_, jointOrigin(), JointPick, frame, revolveAxis() (+1 more)

### Community 22 - "MainWindow::MainWindow"
Cohesion: 0.14
Nodes (5): PythonHost, retintIcons(), setIcon(), MainWindow::MainWindow(), MainWindow::exitSketchMode()

### Community 23 - "TEST"
Cohesion: 0.08
Nodes (7): Sketch, constraints, entities, points, texts, Sketch::addCircle(), TEST()

### Community 24 - "Sketch.cpp"
Cohesion: 0.09
Nodes (17): Point, x, y, SketchError, entityTypeName(), isDimension(), Sketch::addSpline(), Sketch::addText() (+9 more)

### Community 25 - "ViewportSketch.cpp"
Cohesion: 0.08
Nodes (7): faceStyle(), lineStyle(), rgb(), Viewport::lookAt(), Viewport::planePoint(), Viewport::toWidget(), height

### Community 26 - "SketchPalette"
Cohesion: 0.06
Nodes (26): flatButton(), QCheckBox, QLabel, QToolButton, QWidget, SketchEditor, SketchPalette, body_ (+18 more)

### Community 27 - "Snap"
Cohesion: 0.11
Nodes (18): Snap, alignX, alignY, bodyArc, bodySegment, entity, fromX, fromY (+10 more)

### Community 28 - ".apply"
Cohesion: 0.22
Nodes (8): Coil, def_, Extrude, def_, planeOf(), x, y, z

### Community 29 - "AdskModule.cpp"
Cohesion: 0.11
Nodes (14): Application, BRepBodies, Component, Design, Product, raiseIfError(), UserParameter, name (+6 more)

### Community 30 - "Colors"
Cohesion: 0.07
Nodes (28): Colors, base, border, cubeBox, cubeText, errorBackground, grid, gridMajor (+20 more)

### Community 31 - "KernelError"
Cohesion: 0.21
Nodes (31): KernelError, vertices, asSolid(), boolean(), boundingBox(), chamfer(), chamferEx(), draft() (+23 more)

### Community 32 - "SketchOps.cpp"
Cohesion: 0.21
Nodes (26): at(), chainOf(), chamferCorner(), circularPattern(), copyEntities(), cross(), dot(), extendLine() (+18 more)

### Community 33 - "Unit"
Cohesion: 0.11
Nodes (25): formatNumber(), MainWindow::lengthUnit(), number(), withUnit(), Dimension, Angle, Length, Unitless (+17 more)

### Community 34 - "ParameterCompleter"
Cohesion: 0.12
Nodes (8): ParameterCompleter, completer_, edit_, names_, ParameterCompleter::ParameterCompleter(), public, QCompleter, QLineEdit

### Community 35 - "Constraint"
Cohesion: 0.13
Nodes (13): Constraint, driven, entities, expression, hasLabel, labelX, labelY, name (+5 more)

### Community 36 - "Expression.cpp"
Cohesion: 0.14
Nodes (15): ExpressionEnv, lengthUnit, lookup, ExpressionError, evaluateExpression(), evaluateQuantity(), expressionReferences(), isConstantName() (+7 more)

### Community 37 - "MainWindow.cpp"
Cohesion: 0.10
Nodes (3): commandIcon(), qs(), MainWindow::applySection()

### Community 38 - "solve"
Cohesion: 0.18
Nodes (12): addConstraintChecked(), Layout, n, px, py, rad, makeLayout(), pack() (+4 more)

### Community 39 - "ViewportAnalysis.cpp"
Cohesion: 0.11
Nodes (5): packed(), ramp(), shade(), Viewport::buildAnalysis(), Viewport::setCurvatureComb()

### Community 40 - ".rebuild"
Cohesion: 0.12
Nodes (5): hiddenColour(), qc(), rgb(), sharpEdges(), wireColour()

### Community 41 - "ConstraintType"
Cohesion: 0.08
Nodes (24): ConstraintType, Angle, Coincident, Collinear, Concentric, Diameter, Distance, Equal (+16 more)

### Community 42 - "fromInternal"
Cohesion: 0.16
Nodes (14): MainWindow::checkInterference(), MainWindow::driveJoints(), MainWindow::formatLength(), MainWindow::gridSettings(), MainWindow::openSection(), MainWindow::showCenterOfMass(), MainWindow::updateMeasure(), qs() (+6 more)

### Community 43 - "Pick"
Cohesion: 0.13
Nodes (14): Pick, bodyArc, bodyPoint, bodySegment, hit, midpointOf, onEntity, onXAxis (+6 more)

### Community 44 - ".mouseMove"
Cohesion: 0.10
Nodes (14): ccwContains(), circumcircle(), ext(), fixedColor(), freeColor(), qc(), rgb(), wire() (+6 more)

### Community 45 - "Kind"
Cohesion: 0.09
Nodes (21): HudField, edit, editing, kind, locked, value, Kind, Angle (+13 more)

### Community 46 - "Zip.cpp"
Cohesion: 0.28
Nodes (8): ZipError, crc32(), get16(), get32(), put16(), put32(), read(), write()

### Community 47 - "AnalysisSettings"
Cohesion: 0.10
Nodes (16): DragArrow, base, dir, radius, ref, ring, value, PendingLook (+8 more)

### Community 48 - "Document.cpp"
Cohesion: 0.08
Nodes (31): ConstructionPlane, name, spec, Document::axes(), Document::bodies(), Document::body(), Document::bodyName(), Document::component() (+23 more)

### Community 49 - "SketchRecord"
Cohesion: 0.17
Nodes (11): ModelParameter, angle, expression, input, label, name, owner, unit (+3 more)

### Community 50 - "MainWindowSketch.cpp"
Cohesion: 0.08
Nodes (13): MainWindow::cancelSketch(), MainWindow::editSketch(), MainWindow::finishSketch(), MainWindow::onEdgeClicked(), MainWindow::onProfileClicked(), MainWindow::originalShape(), MainWindow::sketchPalette(), MainWindow::sketchVisible() (+5 more)

### Community 51 - "InputDef"
Cohesion: 0.09
Nodes (21): InputDef, choices, defaultValue, id, label, max, min, minExclusive (+13 more)

### Community 52 - "DocCommands.h"
Cohesion: 0.25
Nodes (4): bindTsr(), fromPy(), toPy(), typeName()

### Community 54 - "MainWindowArrow.cpp"
Cohesion: 0.12
Nodes (8): ArrowPlacement, base, dir, edgePlacement(), facesPlacement(), MainWindow::attachArrowCompleters(), MainWindow::patternCentre(), MainWindow::pickedFaces()

### Community 55 - "Viewport.h"
Cohesion: 0.07
Nodes (9): QKeyEvent, QLabel, QMouseEvent, ViewInteractor, Viewport::arrowMouseMove(), Viewport::arrowMousePress(), Viewport::arrowMouseRelease(), Viewport::dragArrowForTest() (+1 more)

### Community 56 - "Theme.cpp"
Cohesion: 0.19
Nodes (6): setIconTheme(), darkColors(), darkPalette(), darkStyleSheet(), lightColors(), lightStyleSheet()

### Community 57 - "TEST"
Cohesion: 0.13
Nodes (6): Entry, data, name, slurp(), TEST(), tmp()

### Community 58 - "Entity"
Cohesion: 0.11
Nodes (17): Entity, a, b, center, construction, fit, projected, radius (+9 more)

### Community 59 - "xdrive.py"
Cohesion: 0.32
Nodes (14): button(), canvas(), click(), drag(), flush(), geometry(), key(), keycode() (+6 more)

### Community 61 - "SketchGeometry.cpp"
Cohesion: 0.12
Nodes (11): curve(), curves(), customPlaneSpec(), entityCurves(), interiorPoint(), planeFrame(), profileAt(), profiles() (+3 more)

### Community 62 - "Session"
Cohesion: 0.05
Nodes (10): PythonHost::PythonHost(), Session, commands_, doc_, listeners_, nextListener_, path_, param() (+2 more)

### Community 63 - "ViewportArrow.cpp"
Cohesion: 0.08
Nodes (13): Viewport::frontEdgeOwner(), rgb(), segmentDistance(), Viewport::arrowAt(), Viewport::arrowParam(), Viewport::DragArrow::handle(), Viewport::dragArrowHandle(), Viewport::emitArrow() (+5 more)

### Community 64 - "BodyFrame"
Cohesion: 0.15
Nodes (14): BodyFrame, diag, dx, dy, dz, x0, y0, z0 (+6 more)

### Community 65 - "CommandRegistry"
Cohesion: 0.12
Nodes (4): CommandRegistry, cmds_, CommandRegistry::add(), TEST()

### Community 66 - "cmath"
Cohesion: 0.21
Nodes (8): Result, error, ok, output, captured(), PythonHost::exec(), PythonHost::runScript(), fn

### Community 67 - "TopoDS_Shape"
Cohesion: 0.19
Nodes (17): SurfacePoint, normal, point, Vec3, edgeMidpoint(), edgesNear(), frame(), makeBox() (+9 more)

### Community 68 - "Theme"
Cohesion: 0.20
Nodes (5): MainWindow::showPreferences(), Theme, colors_, public, styled_

### Community 69 - "ext"
Cohesion: 0.14
Nodes (14): SketchRecord, data, name, offset, plane, Document::openTransaction(), Document::recompute(), Document::recordFeature() (+6 more)

### Community 71 - "src/main.cpp"
Cohesion: 0.09
Nodes (11): ParametersDialog, building_, error_, filter_, listener_, ParametersDialog::ParametersDialog(), public, rebuildPending_ (+3 more)

### Community 72 - "src/main.cpp"
Cohesion: 0.08
Nodes (10): QAbstractButton, QAction, grabWindowWithPanels(), main(), smoke(), writeLiveGeometry(), MassProperties, area (+2 more)

### Community 73 - "FileFormat"
Cohesion: 0.17
Nodes (12): FileFormat, Brep, Iges, Obj, Step, Stl, ThreeMF, FormatInfo (+4 more)

### Community 75 - "InputType"
Cohesion: 0.12
Nodes (17): InputType, Axis, Bodies, Body, Bool, Choice, Edges, Faces (+9 more)

### Community 76 - "string"
Cohesion: 0.15
Nodes (16): bodyNumber(), Document::nextAxisName(), Document::nextBodyName(), Document::nextComponentName(), Document::nextDimensionName(), Document::nextPlaneName(), Document::nextPointName(), Document::nextSketchName() (+8 more)

### Community 77 - "QString"
Cohesion: 0.12
Nodes (4): ExpressionSpinBox, eval_, expression_, shown_

### Community 80 - "SketchDisplay"
Cohesion: 0.12
Nodes (11): ProfileObject, index, sketch, SketchDisplay, construction, curves, fixedCurves, frame (+3 more)

### Community 81 - "DocCommands.cpp"
Cohesion: 0.04
Nodes (58): Adding a tool, Command, CommandDef, feature, icon, id, inputs, name (+50 more)

### Community 82 - "Measurement"
Cohesion: 0.09
Nodes (20): BoundingBox, max, min, Kind, Angle, Area, Length, Volume (+12 more)

### Community 83 - ".redrawAll"
Cohesion: 0.11
Nodes (7): NavPreset, Fusion, SolidWorks, Tinkercad, Viewport::clearDragArrow(), Viewport::clearSecondArrow(), Viewport::setInteractor()

### Community 84 - "Axis"
Cohesion: 0.50
Nodes (4): Axis, X, Y, Z

### Community 85 - "Level"
Cohesion: 0.16
Nodes (13): debug(), error(), info(), Level, Debug, Error, Info, Warning (+5 more)

### Community 86 - "README.md"
Cohesion: 0.07
Nodes (21): Architecture, How a command works, The document, Units, Build, Conventions, Development, Tests (+13 more)

### Community 87 - "DocumentError"
Cohesion: 0.12
Nodes (18): DocumentError, checkViewName(), Document::abortTransaction(), Document::addBody(), Document::addNamedView(), Document::addUserParameter(), Document::axisFrame(), Document::bodyShapes() (+10 more)

### Community 89 - "Tool"
Cohesion: 0.16
Nodes (6): SketchEditor::SketchEditor(), edges, Tool, op, shape, target

### Community 91 - "MarkingMenu.cpp"
Cohesion: 0.06
Nodes (26): UiCommand, enabled, icon, id, name, panel, run, shortcut (+18 more)

### Community 92 - "CommandSession"
Cohesion: 0.12
Nodes (9): CommandSession, inputs_, CommandRegistry::find(), CommandRegistry::run(), OwnedCommand, owned, OwningCommandSession, Session::begin() (+1 more)

### Community 93 - "Known differences still to build"
Cohesion: 0.15
Nodes (12): Data and files, Findings from the videos, Fusion study list, Interface, Known differences still to build, Navigation and display, Selection and the canvas, Sketch (+4 more)

### Community 95 - "Feature"
Cohesion: 0.09
Nodes (18): Component, bodies, name, Feature, commandId, error, id, inputs (+10 more)

### Community 96 - "UserParameter"
Cohesion: 0.33
Nodes (6): UserParameter, comment, expression, name, unit, value

### Community 97 - "WallSide"
Cohesion: 0.50
Nodes (4): WallSide, Center, Side1, Side2

### Community 98 - "FakeDoc"
Cohesion: 0.17
Nodes (6): FakeDoc, aborts, commits, items, open, snapshot

### Community 101 - "string"
Cohesion: 0.10
Nodes (30): completeEdgeReferences(), completeFaceReferences(), decode(), decodeFaces(), dot(), edgeReference(), EdgeSig, full (+22 more)

### Community 102 - "sstream"
Cohesion: 0.15
Nodes (5): doc_(), Document::Document(), Document::ocafBytes(), ocafApplication(), Document::load()

### Community 103 - "rect"
Cohesion: 0.18
Nodes (7): SelectionBox, crossing, Session::notifyChanged(), Rect, rect(), l, p

### Community 104 - "Command.cpp"
Cohesion: 0.22
Nodes (11): expressionKey(), checkInputValue(), CommandContext::evaluateExpression(), CommandDef::input(), CommandSession::applyInTransaction(), CommandSession::cancel(), CommandSession::execute(), CommandSession::preview() (+3 more)

### Community 106 - "SectionState"
Cohesion: 0.25
Nodes (7): SectionState, active, angle, flip, offset, plane, visible

### Community 107 - "Display"
Cohesion: 0.25
Nodes (7): Display, constraints, construction, dimensions, points, profiles, projected

### Community 108 - "TestFramework.h"
Cohesion: 0.15
Nodes (5): Case, name, fail(), Failure, Register

### Community 109 - "PlaneEdges"
Cohesion: 0.20
Nodes (5): PlaneEdges, arcs, curves, segments, vertices

### Community 110 - "openWallBand"
Cohesion: 0.17
Nodes (17): Section, Circular, Square, Triangular, TopologyCounts, edges, faces, shells (+9 more)

### Community 111 - "ConstructionPoint"
Cohesion: 0.29
Nodes (5): ConstructionPoint, name, point, Document::point(), Document::setPoint()

### Community 113 - "ConstructionAxis"
Cohesion: 0.29
Nodes (5): ConstructionAxis, axis, name, Document::axis(), Document::setAxis()

### Community 114 - "uninstall.sh"
Cohesion: 0.52
Nodes (6): die(), manifest_for(), refresh(), uninstall.sh script, step(), usage()

### Community 115 - "install.sh"
Cohesion: 0.60
Nodes (5): die(), refresh(), install.sh script, step(), usage()

### Community 117 - "main"
Cohesion: 0.28
Nodes (3): listCommands(), main(), usage()

### Community 118 - "AnalysisSettings"
Cohesion: 0.15
Nodes (13): AnalysisKind, CurvatureMap, Draft, None, Zebra, AnalysisSettings, curvatureScale, draftAngle (+5 more)

### Community 119 - "Sketch.h"
Cohesion: 0.17
Nodes (8): CommandRegistry::all(), EntityType, Arc, Circle, Ellipse, Line, Spline, isRound()

### Community 120 - "Column"
Cohesion: 0.25
Nodes (8): Column, kComment, kExpression, kName, kParameter, kStar, kUnit, kValue

### Community 122 - "BooleanOp"
Cohesion: 0.50
Nodes (4): BooleanOp, Cut, Intersect, Join

### Community 123 - "Placement"
Cohesion: 0.25
Nodes (7): Placement, angle, cx, cy, dx, dy, scale

### Community 124 - "ChainSegment"
Cohesion: 0.67
Nodes (3): ChainSegment, entity, forward

### Community 125 - "ThreadInfo"
Cohesion: 0.50
Nodes (4): ThreadInfo, diameter, internal, pitch

### Community 126 - "ChamferType"
Cohesion: 0.67
Nodes (3): ChamferType, DistanceAngle, TwoDistances

### Community 127 - "Joints"
Cohesion: 0.36
Nodes (3): cornerAt(), Joints, parent_

### Community 129 - "ParametersDialog.h"
Cohesion: 0.25
Nodes (3): QLabel, QLineEdit, QTreeWidgetItem

### Community 130 - "Document::nameFeatureParameters"
Cohesion: 0.25
Nodes (6): Document::nameFeatureParameters(), Document::removeFeature(), Document::setFeatureSuppressed(), featureData(), joinNames(), parseNames()

### Community 134 - ".attach"
Cohesion: 0.25
Nodes (3): Hit, index, kind

### Community 135 - "bindAdsk"
Cohesion: 0.29
Nodes (3): bindAdsk(), BRepBody, index

### Community 139 - "NamedView"
Cohesion: 0.29
Nodes (7): NamedView, eye, name, size, target, up, Document::namedViews()

### Community 141 - "Profile"
Cohesion: 0.33
Nodes (5): Profile, area, face, x, y

### Community 142 - "MarkingMenu"
Cohesion: 0.40
Nodes (3): MarkingMenu, enabled, public

## Knowledge Gaps
- **704 isolated node(s):** `ok`, `output`, `error`, `isReal`, `real` (+699 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 1337 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **31 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `Viewport` connect `Viewport` to `MainWindow`, `ViewportAnalysis.cpp`, `.rebuild`, `QTimer`, `Viewport.cpp`, `rect`, `optional`, `AnalysisSettings`, `SketchDisplay`, `QTimer`, `.redrawAll`, `MainWindowTools.cpp`, `.toPixels`, `AnalysisSettings`, `Viewport.h`, `AdskModule.cpp`, `ViewportArrow.cpp`?**
  _High betweenness centrality (0.112) - this node is a cross-community bridge._
- **What connects `ok`, `output`, `error` to the rest of the system?**
  _704 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Viewport` be split into smaller, more focused modules?**
  _Cohesion score 0.01650793650793651 - nodes in this community are weakly interconnected._
- **Why does `optional` connect `optional` to `Viewport`, `MainWindow`, `.attach`, `Kernel.cpp`, `DocCommands.cpp`, `Io.cpp`, `Unit`, `string`, `ViewportSketch.cpp`, `Unit`, `Constraint`, `Expression.cpp`, `AnalysisSettings`, `Document.cpp`, `SketchRecord`, `InputDef`, `MainWindowArrow.cpp`, `Viewport.h`, `Session`, `ViewportArrow.cpp`, `TopoDS_Shape`, `SketchEditor.cpp`, `QString`, `Feature`, `CommandDialog.cpp`, `ConstructionPoint`, `ConstructionAxis`, `Joints`?**
  _High betweenness centrality (0.109) - this node is a cross-community bridge._
- **Should `Icons.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.06361556064073226 - nodes in this community are weakly interconnected._
- **Why does `SketchEditor` connect `SketchEditor` to `Tool`, `Viewport`, `Unit`, `Constraint`, `.attach`, `SketchEditor.cpp`, `Display`, `optional`, `PlaneEdges`, `Kind`, `Pick`, `.mouseMove`, `.press`, `Viewport.h`, `QObject`, `Entity`, `Snap`, `Session`?**
  _High betweenness centrality (0.098) - this node is a cross-community bridge._
- **Should `tsr` be split into smaller, more focused modules?**
  _Cohesion score 0.0647342995169082 - nodes in this community are weakly interconnected._