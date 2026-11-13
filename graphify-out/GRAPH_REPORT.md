# Graph Report - tessera  (2026-11-13)

## Corpus Check
- 343 files · ~199,932 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 36 file(s) not represented in the graph (top: .drive 28, (none) 5, .cmake 1)

## Summary
- 3171 nodes · 7937 edges · 135 communities (98 shown, 37 thin omitted)
- Extraction: 84% EXTRACTED · 16% INFERRED · 0% AMBIGUOUS · INFERRED: 1236 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `7f6b4f38`
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
- Parser
- CommandError
- .updatePreview
- Viewport::Viewport
- MainWindow.cpp
- TEST
- Sketch.cpp
- ViewportSketch.cpp
- SketchPalette
- SketchEditor.cpp
- NewComponent
- AdskModule.cpp
- Colors
- KernelError
- SketchOps.cpp
- Session.cpp
- ParameterCompleter
- Expression.cpp
- CommandDialog.cpp
- Command.cpp
- solve
- TEST
- src/main.cpp
- ConstraintType
- TEST
- Pick
- Snap
- Kind
- CommandSession
- AnalysisSettings
- Document.cpp
- Session
- MainWindowSketch.cpp
- InputDef
- .toPixels
- ViewportAnalysis.cpp
- .showDialog
- Theme.cpp
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
- openWallBand
- QString
- InputType
- UiCommand
- Value.h
- SketchDisplay
- string
- Measurement
- rect
- Entity
- Level
- README.md
- ext
- CommandDialog::CommandDialog
- fail
- Known differences still to build
- SketchEditor::SketchEditor
- .add
- CommandRegistry::run
- BodyFrame
- FakeDoc
- ConstructionPlane
- Zip.cpp
- AddUserParameter
- Axis
- Document::load
- ParameterCompleter.cpp
- Development
- SectionState
- Display
- BRepBody
- .requireTransaction
- openWallBand
- ConstructionPoint
- ConstructionAxis
- main
- uninstall.sh
- install.sh
- Rect
- Icons.h
- FeatureEffect
- smoke
- BooleanOp
- ThreadInfo
- ChamferType
- Session::addListener
- Dimension
- ChainSegment
- LAB_NOTES.md
- build.sh
- live-test.sh

## God Nodes (most connected - your core abstractions)
1. `Viewport` - 227 edges
2. `MainWindow` - 172 edges
3. `SketchEditor` - 161 edges
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

## Communities (135 total, 37 thin omitted)

### Community 0 - "Viewport"
Cohesion: 0.02
Nodes (57): view_, QLineEdit, Viewport, analysis_, analysisObjects_, appliedGridStep_, arrowBoxes_, arrowDragging_ (+49 more)

### Community 1 - "Icons.cpp"
Cohesion: 0.07
Nodes (90): arcIcon(), arrow(), axisIcon(), box(), centerRectIcon(), chamferIcon(), circleIcon(), coilIcon() (+82 more)

### Community 2 - "DocCommands.cpp"
Cohesion: 0.04
Nodes (66): Adding a tool, Command, CommandDef, feature, icon, id, inputs, name (+58 more)

### Community 4 - "MainWindow"
Cohesion: 0.03
Nodes (63): CommandDialog, MainWindow, active_, arrowInput_, arrowInput2_, bodiesBeforeCommand_, combEdges_, combPicking_ (+55 more)

### Community 5 - "run_oracle.py"
Cohesion: 0.08
Nodes (54): add_point(), arc_poly(), body_at(), body_list(), build_sketch(), chain(), circumcentre(), cm() (+46 more)

### Community 6 - "Inputs"
Cohesion: 0.08
Nodes (12): CommandContext, Inputs, CommandSession::CommandSession(), checkBody(), checkPattern(), defaultBody(), isIdentifier(), RectangularPattern (+4 more)

### Community 7 - "Document"
Cohesion: 0.05
Nodes (16): Document, effects_, modified_, pendingTools_, registry_, replaying_, txnBodies_, FromOcaf (+8 more)

### Community 8 - "Viewport.cpp"
Cohesion: 0.06
Nodes (3): MarkingMenu::keyPressEvent(), QKeyEvent, QtFrameBuffer

### Community 9 - "SketchEditor"
Cohesion: 0.03
Nodes (42): SketchEditor, arcDrag_, arcDragMoved_, arcEndsChain_, arcFrom_, arcRef_, bodyEdges_, boxing_ (+34 more)

### Community 10 - "Unit"
Cohesion: 0.11
Nodes (23): bindAdsk(), formatNumber(), MainWindow::lengthUnit(), withUnit(), Unit, Centimeter, Degree, Foot (+15 more)

### Community 13 - ".projectAt"
Cohesion: 0.22
Nodes (4): PlaneEdges, arcs, segments, vertices

### Community 14 - "Kind"
Cohesion: 0.08
Nodes (25): ConstructPlane, def_, kind_, EdgeFeature, def_, kind_, FaceFeature, def_ (+17 more)

### Community 15 - "MainWindowTools.cpp"
Cohesion: 0.06
Nodes (25): QDialog, MainWindow::applySection(), MainWindow::checkInterference(), MainWindow::chooseUnits(), MainWindow::driveJoints(), MainWindow::exportDesign(), MainWindow::formatLength(), MainWindow::gridSettings() (+17 more)

### Community 16 - "CommandDialog"
Cohesion: 0.05
Nodes (31): CommandDialog, bodiesId_, bodiesLabel_, bodyInput_, buttons_, cmd_, conditional_, edgesId_ (+23 more)

### Community 17 - "Io.cpp"
Cohesion: 0.10
Nodes (17): NamedShape, compoundOf(), exportShapes(), fmt(), formatForPath(), fromBrep(), importShape(), lower() (+9 more)

### Community 18 - "Parser"
Cohesion: 0.18
Nodes (15): Quantity, angle, length, value, describe(), isIdentChar(), isIdentStart(), Parser (+7 more)

### Community 19 - "CommandError"
Cohesion: 0.11
Nodes (20): CommandError, getBool(), applyOperation(), bodyCentre(), bodyName(), Coil, def_, CopyFn (+12 more)

### Community 20 - ".updatePreview"
Cohesion: 0.11
Nodes (6): ext(), fixedColor(), freeColor(), qc(), rgb(), wire()

### Community 21 - "Viewport::Viewport"
Cohesion: 0.11
Nodes (10): keys(), NavPreset, Fusion, SolidWorks, Tinkercad, qc(), rgb(), SelectionBox (+2 more)

### Community 22 - "MainWindow.cpp"
Cohesion: 0.07
Nodes (8): commandIcon(), qs(), run, MainWindow::beginSketch(), MainWindow::buildSketchTab(), MainWindow::enterSketchMode(), MarkingMenu::mouseReleaseEvent(), MarkingMenu::triggerForTest()

### Community 23 - "TEST"
Cohesion: 0.09
Nodes (6): Sketch, constraints, entities, points, Sketch::addCircle(), TEST()

### Community 24 - "Sketch.cpp"
Cohesion: 0.09
Nodes (17): Point, x, y, SketchError, entityTypeName(), isDimension(), Sketch::addLine(), Sketch::addSpline() (+9 more)

### Community 25 - "ViewportSketch.cpp"
Cohesion: 0.06
Nodes (7): QLabel, faceStyle(), lineStyle(), rgb(), Viewport::lookAt(), Viewport::planePoint(), Viewport::toWidget()

### Community 26 - "SketchPalette"
Cohesion: 0.06
Nodes (25): QCheckBox, QLabel, QToolButton, QWidget, SketchEditor, SketchPalette, body_, constraints_ (+17 more)

### Community 29 - "AdskModule.cpp"
Cohesion: 0.13
Nodes (13): Application, BRepBodies, Component, Design, Product, raiseIfError(), UserParameter, name (+5 more)

### Community 30 - "Colors"
Cohesion: 0.07
Nodes (28): Colors, base, border, cubeBox, cubeText, errorBackground, grid, gridMajor (+20 more)

### Community 31 - "KernelError"
Cohesion: 0.27
Nodes (25): KernelError, asSolid(), boolean(), chamfer(), chamferEx(), draft(), extrude(), extrudeEx() (+17 more)

### Community 32 - "SketchOps.cpp"
Cohesion: 0.21
Nodes (19): at(), chainOf(), chamferCorner(), cornerAt(), cross(), dot(), extendLine(), filletCorner() (+11 more)

### Community 33 - "Session.cpp"
Cohesion: 0.20
Nodes (17): historyEdit(), Session::deleteFeature(), Session::deleteParameter(), Session::newDocument(), Session::open(), Session::redo(), Session::renameBody(), Session::renameFeature() (+9 more)

### Community 34 - "ParameterCompleter"
Cohesion: 0.18
Nodes (8): QObject, ParameterCompleter, completer_, edit_, names_, public, QCompleter, QLineEdit

### Community 35 - "Expression.cpp"
Cohesion: 0.19
Nodes (11): ExpressionEnv, lengthUnit, lookup, ExpressionError, evaluateExpression(), evaluateQuantity(), expressionReferences(), isConstantName() (+3 more)

### Community 37 - "Command.cpp"
Cohesion: 0.24
Nodes (11): expressionKey(), checkInputValue(), CommandContext::evaluateExpression(), CommandDef::input(), CommandSession::applyInTransaction(), CommandSession::cancel(), CommandSession::execute(), CommandSession::preview() (+3 more)

### Community 38 - "solve"
Cohesion: 0.18
Nodes (12): addConstraintChecked(), Layout, n, px, py, rad, makeLayout(), pack() (+4 more)

### Community 39 - "TEST"
Cohesion: 0.16
Nodes (7): quantityOf(), Document::expressionEnv(), Document::reevaluateParameters(), Document::save(), env(), mm(), TEST()

### Community 40 - "src/main.cpp"
Cohesion: 0.09
Nodes (4): grabWindowWithPanels(), MarkingMenu, enabled, public

### Community 41 - "ConstraintType"
Cohesion: 0.08
Nodes (24): ConstraintType, Angle, Coincident, Collinear, Concentric, Diameter, Distance, Equal (+16 more)

### Community 42 - "TEST"
Cohesion: 0.09
Nodes (3): param(), TEST(), tmp()

### Community 43 - "Pick"
Cohesion: 0.11
Nodes (17): Hit, index, kind, Pick, bodyArc, bodyPoint, bodySegment, hit (+9 more)

### Community 44 - "Snap"
Cohesion: 0.11
Nodes (18): Snap, alignX, alignY, bodyArc, bodySegment, entity, fromX, fromY (+10 more)

### Community 45 - "Kind"
Cohesion: 0.09
Nodes (21): HudField, edit, editing, kind, locked, value, Kind, Angle (+13 more)

### Community 46 - "CommandSession"
Cohesion: 0.15
Nodes (7): CommandSession, inputs_, OwnedCommand, owned, OwningCommandSession, Session::begin(), Session::editFeature()

### Community 47 - "AnalysisSettings"
Cohesion: 0.08
Nodes (21): AnalysisKind, CurvatureMap, Draft, None, Zebra, AnalysisSettings, curvatureScale, draftAngle (+13 more)

### Community 48 - "Document.cpp"
Cohesion: 0.10
Nodes (23): Document::axes(), Document::bodies(), Document::body(), Document::bodyName(), Document::components(), Document::features(), Document::historyMarker(), Document::lengthUnit() (+15 more)

### Community 49 - "Session"
Cohesion: 0.10
Nodes (7): PythonHost::PythonHost(), Session, commands_, doc_, listeners_, nextListener_, path_

### Community 50 - "MainWindowSketch.cpp"
Cohesion: 0.06
Nodes (17): MainWindow::cancelSketch(), MainWindow::editSketch(), MainWindow::finishSketch(), MainWindow::onProfileClicked(), MainWindow::originalShape(), MainWindow::sketchPalette(), MainWindow::sketchVisible(), MainWindow::startSketch() (+9 more)

### Community 51 - "InputDef"
Cohesion: 0.08
Nodes (24): InputDef, choices, defaultValue, id, label, max, min, minExclusive (+16 more)

### Community 54 - "ViewportAnalysis.cpp"
Cohesion: 0.07
Nodes (11): ArrowPlacement, base, dir, edgePlacement(), facesPlacement(), MainWindow::patternCentre(), MainWindow::pickedFaces(), packed() (+3 more)

### Community 56 - "Theme.cpp"
Cohesion: 0.19
Nodes (6): setIconTheme(), darkColors(), darkPalette(), darkStyleSheet(), lightColors(), lightStyleSheet()

### Community 58 - "Constraint"
Cohesion: 0.10
Nodes (19): Constraint, entities, expression, hasLabel, labelX, labelY, points, type (+11 more)

### Community 59 - "xdrive.py"
Cohesion: 0.32
Nodes (14): button(), canvas(), click(), drag(), flush(), geometry(), key(), keycode() (+6 more)

### Community 61 - "SketchGeometry.cpp"
Cohesion: 0.10
Nodes (14): Profile, area, face, x, y, curve(), curves(), customPlaneSpec() (+6 more)

### Community 62 - "MainWindow::MainWindow"
Cohesion: 0.12
Nodes (5): PythonHost, setIcon(), flatButton(), MainWindow::MainWindow(), MainWindow::exitSketchMode()

### Community 63 - "ViewportArrow.cpp"
Cohesion: 0.05
Nodes (22): MarkingMenu::mouseMoveEvent(), QMouseEvent, ViewInteractor, Viewport::frontEdgeOwner(), Viewport::setCurvatureComb(), rgb(), segmentDistance(), Viewport::arrowAt() (+14 more)

### Community 64 - "string"
Cohesion: 0.09
Nodes (31): completeEdgeReferences(), completeFaceReferences(), decode(), decodeFaces(), dot(), edgeReference(), EdgeSig, full (+23 more)

### Community 65 - "CommandRegistry"
Cohesion: 0.14
Nodes (3): CommandRegistry, cmds_, TEST()

### Community 66 - "PythonHost.cpp"
Cohesion: 0.12
Nodes (11): Result, error, ok, output, captured(), PythonHost::exec(), PythonHost::runScript(), Case (+3 more)

### Community 67 - "TopoDS_Shape"
Cohesion: 0.19
Nodes (20): SurfacePoint, normal, point, Vec3, boundingBox(), edgeMidpoint(), edgesNear(), frame() (+12 more)

### Community 68 - "Theme"
Cohesion: 0.22
Nodes (4): Theme, colors_, public, styled_

### Community 69 - "FileFormat"
Cohesion: 0.17
Nodes (12): FileFormat, Brep, Iges, Obj, Step, Stl, ThreeMF, FormatInfo (+4 more)

### Community 70 - ".planeFrame"
Cohesion: 0.13
Nodes (13): getInt(), Loft, def_, openChains(), parsePoints(), pickedFaces(), profilesOf(), SketchProfiles (+5 more)

### Community 71 - "ParametersDialog.cpp"
Cohesion: 0.07
Nodes (20): Column, kComment, kExpression, kParameter, kUnit, kValue, number(), ParametersDialog (+12 more)

### Community 72 - "openWallBand"
Cohesion: 0.20
Nodes (11): BoundingBox, max, min, WallSide, Center, Side1, Side2, massProperties() (+3 more)

### Community 74 - "QString"
Cohesion: 0.12
Nodes (4): ExpressionSpinBox, eval_, expression_, shown_

### Community 75 - "InputType"
Cohesion: 0.08
Nodes (21): bindTsr(), fromPy(), toPy(), typeName(), InputType, Axis, Bodies, Body (+13 more)

### Community 77 - "UiCommand"
Cohesion: 0.18
Nodes (9): UiCommand, enabled, icon, id, name, panel, shortcut, tab (+1 more)

### Community 80 - "SketchDisplay"
Cohesion: 0.13
Nodes (10): ProfileObject, index, sketch, SketchDisplay, construction, curves, frame, name (+2 more)

### Community 81 - "string"
Cohesion: 0.15
Nodes (15): bodyNumber(), Document::axisFrame(), Document::component(), Document::componentOfBody(), Document::nextAxisName(), Document::nextBodyName(), Document::nextComponentName(), Document::nextPlaneName() (+7 more)

### Community 82 - "Measurement"
Cohesion: 0.13
Nodes (14): Kind, Angle, Area, Length, Volume, Measurement, from, hasLine (+6 more)

### Community 84 - "Entity"
Cohesion: 0.13
Nodes (15): Entity, a, b, center, construction, fit, projected, radius (+7 more)

### Community 85 - "Level"
Cohesion: 0.16
Nodes (13): debug(), error(), info(), Level, Debug, Error, Info, Warning (+5 more)

### Community 86 - "README.md"
Cohesion: 0.10
Nodes (16): Architecture, How a command works, The document, Units, Known gaps, Reference parts, Fusion feature checklist, Roadmap (+8 more)

### Community 87 - "ext"
Cohesion: 0.14
Nodes (15): SketchRecord, data, name, offset, plane, Document::openTransaction(), Document::recompute(), Document::recordFeature() (+7 more)

### Community 93 - "Known differences still to build"
Cohesion: 0.15
Nodes (12): Data and files, Findings from the videos, Fusion study list, Interface, Known differences still to build, Navigation and display, Selection and the canvas, Sketch (+4 more)

### Community 96 - "CommandRegistry::run"
Cohesion: 0.22
Nodes (4): CommandRegistry::add(), CommandRegistry::all(), CommandRegistry::find(), CommandRegistry::run()

### Community 97 - "BodyFrame"
Cohesion: 0.15
Nodes (14): BodyFrame, diag, dx, dy, dz, x0, y0, z0 (+6 more)

### Community 98 - "FakeDoc"
Cohesion: 0.17
Nodes (6): FakeDoc, aborts, commits, items, open, snapshot

### Community 99 - "ConstructionPlane"
Cohesion: 0.29
Nodes (6): ConstructionPlane, name, spec, Document::plane(), Document::planes(), Document::setPlane()

### Community 100 - "Zip.cpp"
Cohesion: 0.11
Nodes (14): Entry, data, name, ZipError, crc32(), get16(), get32(), put16() (+6 more)

### Community 102 - "Axis"
Cohesion: 0.50
Nodes (4): Axis, X, Y, Z

### Community 103 - "Document::load"
Cohesion: 0.17
Nodes (5): doc_(), Document::Document(), Document::ocafBytes(), ocafApplication(), Document::load()

### Community 105 - "Development"
Cohesion: 0.40
Nodes (4): Build, Conventions, Development, Tests

### Community 106 - "SectionState"
Cohesion: 0.25
Nodes (7): SectionState, active, angle, flip, offset, plane, visible

### Community 107 - "Display"
Cohesion: 0.25
Nodes (7): Display, constraints, construction, dimensions, points, profiles, projected

### Community 109 - ".requireTransaction"
Cohesion: 0.12
Nodes (17): DocumentError, Document::abortTransaction(), Document::addBody(), Document::addUserParameter(), Document::bodyShapes(), Document::commitTransaction(), Document::effectOf(), Document::removeBody() (+9 more)

### Community 110 - "openWallBand"
Cohesion: 0.18
Nodes (16): Section, Circular, Square, Triangular, TopologyCounts, edges, faces, shells (+8 more)

### Community 111 - "ConstructionPoint"
Cohesion: 0.29
Nodes (5): ConstructionPoint, name, point, Document::point(), Document::setPoint()

### Community 112 - "ConstructionAxis"
Cohesion: 0.29
Nodes (5): ConstructionAxis, axis, name, Document::axis(), Document::setAxis()

### Community 113 - "main"
Cohesion: 0.21
Nodes (4): listCommands(), main(), usage(), main()

### Community 114 - "uninstall.sh"
Cohesion: 0.52
Nodes (6): die(), manifest_for(), refresh(), uninstall.sh script, step(), usage()

### Community 115 - "install.sh"
Cohesion: 0.60
Nodes (5): die(), refresh(), install.sh script, step(), usage()

### Community 116 - "Rect"
Cohesion: 0.50
Nodes (4): Session::notifyChanged(), Rect, l, p

### Community 118 - "FeatureEffect"
Cohesion: 0.05
Nodes (31): Body, display, name, shape, Component, bodies, name, Feature (+23 more)

### Community 123 - "smoke"
Cohesion: 0.40
Nodes (5): smoke(), MassProperties, area, centerOfMass, volume

### Community 124 - "BooleanOp"
Cohesion: 0.50
Nodes (4): BooleanOp, Cut, Intersect, Join

### Community 125 - "ThreadInfo"
Cohesion: 0.50
Nodes (4): ThreadInfo, diameter, internal, pitch

### Community 126 - "ChamferType"
Cohesion: 0.67
Nodes (3): ChamferType, DistanceAngle, TwoDistances

### Community 128 - "Dimension"
Cohesion: 0.50
Nodes (4): Dimension, Angle, Length, Unitless

### Community 132 - "ChainSegment"
Cohesion: 0.67
Nodes (3): ChainSegment, entity, forward

## Knowledge Gaps
- **644 isolated node(s):** `ok`, `output`, `error`, `isReal`, `real` (+639 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 1218 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **37 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `optional` connect `optional` to `Viewport`, `DocCommands.cpp`, `MainWindow`, `Inputs`, `Unit`, `Kernel.cpp`, `Io.cpp`, `Parser`, `.updatePreview`, `ViewportSketch.cpp`, `SketchEditor.cpp`, `SketchOps.cpp`, `Expression.cpp`, `CommandDialog.cpp`, `AnalysisSettings`, `Document.cpp`, `Session`, `InputDef`, `ViewportAnalysis.cpp`, `ViewportArrow.cpp`, `TopoDS_Shape`, `QString`, `string`, `ext`, `ConstructionPlane`, `ConstructionPoint`, `ConstructionAxis`, `FeatureEffect`?**
  _High betweenness centrality (0.115) - this node is a cross-community bridge._
- **What connects `ok`, `output`, `error` to the rest of the system?**
  _644 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Viewport` be split into smaller, more focused modules?**
  _Cohesion score 0.017978190391983496 - nodes in this community are weakly interconnected._
- **Why does `SketchEditor` connect `SketchEditor` to `Viewport`, `ParameterCompleter`, `Unit`, `Display`, `optional`, `Kind`, `.projectAt`, `Pick`, `Snap`, `Session`, `.updatePreview`, `FeatureEffect`, `QObject`, `Constraint`, `SketchEditor.cpp`, `SketchEditor::SketchEditor`, `ViewportArrow.cpp`?**
  _High betweenness centrality (0.102) - this node is a cross-community bridge._
- **Should `Icons.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.07111935683364255 - nodes in this community are weakly interconnected._
- **Why does `Viewport` connect `Viewport` to `MainWindow`, `ParametersDialog.cpp`, `Viewport.cpp`, `QTimer`, `optional`, `.rebuild`, `AnalysisSettings`, `SketchDisplay`, `MainWindowTools.cpp`, `rect`, `Viewport::Viewport`, `.toPixels`, `ViewportAnalysis.cpp`, `ViewportSketch.cpp`, `.selectedSubShapes`, `ViewportArrow.cpp`?**
  _High betweenness centrality (0.099) - this node is a cross-community bridge._
- **Should `DocCommands.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.04341736694677871 - nodes in this community are weakly interconnected._