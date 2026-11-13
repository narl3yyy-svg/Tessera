# Graph Report - tessera  (2026-11-13)

## Corpus Check
- 346 files · ~203,357 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 38 file(s) not represented in the graph (top: .drive 30, (none) 5, .cmake 1)

## Summary
- 3198 nodes · 8021 edges · 133 communities (100 shown, 33 thin omitted)
- Extraction: 84% EXTRACTED · 16% INFERRED · 0% AMBIGUOUS · INFERRED: 1252 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `9f7beae7`
- Run `git rev-parse HEAD` and compare to check if the graph is stale.
- Run `graphify update .` after code changes (no API cost).

## Community Hubs (Navigation)
- Viewport
- Icons.cpp
- Command
- tsr
- MainWindow
- run_oracle.py
- DocCommands.cpp
- Document
- Viewport.cpp
- SketchEditor
- QString
- optional
- Kernel.cpp
- .projectAt
- Kind
- MainWindowTools.cpp
- CommandDialog
- Io.cpp
- Unit
- .apply
- .updatePreview
- Viewport.h
- .showDialog
- TEST
- Sketch.cpp
- ViewportSketch.cpp
- SketchPalette
- Constraint
- SketchProfiles
- AdskModule.cpp
- Colors
- KernelError
- SketchOps.cpp
- Session.cpp
- ParameterCompleter
- ConstructAxisPoint
- CommandDialog.cpp
- .openMarkingMenu
- solve
- ViewportAnalysis.cpp
- src/main.cpp
- ConstraintType
- TEST
- Pick
- Snap
- Kind
- Inputs
- AnalysisSettings
- Document.cpp
- Session
- MainWindowSketch.cpp
- InputDef
- .toPixels
- ViewportAnalysis.cpp
- .rebuild
- Theme.cpp
- MainWindow.cpp
- Entity
- xdrive.py
- SketchGeometry.cpp
- Architecture
- ViewportArrow.cpp
- string
- CommandRegistry
- PythonHost.cpp
- TopoDS_Shape
- Theme
- MainWindow::MainWindow
- sketchFor
- ParametersDialog.cpp
- QObject
- QTimer
- CommandDialog::CommandDialog
- InputType
- Feature
- MarkingMenu.cpp
- Value.h
- SketchDisplay
- Unit
- Measurement
- rect
- BooleanOp
- Level
- README.md
- Document.cpp
- test_feature_pattern.py
- UserParameter
- UiCommand
- Known differences still to build
- ThreadInfo
- cmath
- BodyFrame
- FakeDoc
- TEST
- Zip.cpp
- Axis
- Document::load
- planeOf
- SectionState
- Display
- Handle
- string
- openWallBand
- ConstructionPoint
- ConstructionAxis
- main
- uninstall.sh
- install.sh
- TsrModule.cpp
- FeatureEffect
- MainWindow::enterSketchMode
- smoke
- Sketch.h
- ModelParameter
- Column
- BRepBody
- MainWindow::setSelectionFilter
- LAB_NOTES.md
- build.sh
- live-test.sh

## God Nodes (most connected - your core abstractions)
1. `Viewport` - 227 edges
2. `MainWindow` - 172 edges
3. `SketchEditor` - 163 edges
4. `Inputs` - 136 edges
5. `Document` - 128 edges
6. `CommandContext` - 102 edges
7. `render()` - 91 edges
8. `CommandDialog` - 90 edges
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

## Communities (133 total, 33 thin omitted)

### Community 0 - "Viewport"
Cohesion: 0.02
Nodes (56): view_, Viewport, analysis_, analysisObjects_, appliedGridStep_, arrowBoxes_, arrowDragging_, arrowGrab_ (+48 more)

### Community 1 - "Icons.cpp"
Cohesion: 0.07
Nodes (95): arc3Icon(), arcIcon(), arrow(), axisIcon(), box(), centerRectIcon(), chamferIcon(), circle2Icon() (+87 more)

### Community 2 - "Command"
Cohesion: 0.16
Nodes (18): Adding a tool, Command, getReal(), makeBox(), makeCone(), makeCylinder(), makeSphere(), makeTorus() (+10 more)

### Community 4 - "MainWindow"
Cohesion: 0.03
Nodes (61): CommandDialog, MainWindow, active_, arrowInput_, arrowInput2_, bodiesBeforeCommand_, combEdges_, combPicking_ (+53 more)

### Community 5 - "run_oracle.py"
Cohesion: 0.08
Nodes (54): add_point(), arc_poly(), body_at(), body_list(), build_sketch(), chain(), circumcentre(), cm() (+46 more)

### Community 6 - "DocCommands.cpp"
Cohesion: 0.04
Nodes (49): CommandDef, feature, icon, id, inputs, name, nameInput, panel (+41 more)

### Community 7 - "Document"
Cohesion: 0.04
Nodes (14): Document, effects_, modified_, pendingTools_, registry_, replaying_, txnBodies_, FromOcaf (+6 more)

### Community 8 - "Viewport.cpp"
Cohesion: 0.05
Nodes (12): keys(), NavPreset, Fusion, SolidWorks, Tinkercad, qc(), rgb(), SelectionBox (+4 more)

### Community 9 - "SketchEditor"
Cohesion: 0.04
Nodes (42): SketchEditor, arcDrag_, arcDragMoved_, arcEndsChain_, arcFrom_, arcRef_, bodyEdges_, boxing_ (+34 more)

### Community 10 - "QString"
Cohesion: 0.12
Nodes (5): ExpressionSpinBox, eval_, expression_, shown_, formatNumber()

### Community 13 - ".projectAt"
Cohesion: 0.22
Nodes (4): PlaneEdges, arcs, segments, vertices

### Community 14 - "Kind"
Cohesion: 0.09
Nodes (22): EdgeFeature, def_, kind_, FaceFeature, def_, kind_, Kind, Angle (+14 more)

### Community 15 - "MainWindowTools.cpp"
Cohesion: 0.07
Nodes (24): QDialog, MainWindow::checkInterference(), MainWindow::chooseUnits(), MainWindow::driveJoints(), MainWindow::exportDesign(), MainWindow::formatLength(), MainWindow::gridSettings(), MainWindow::insertFile() (+16 more)

### Community 16 - "CommandDialog"
Cohesion: 0.05
Nodes (31): CommandDialog, bodiesId_, bodiesLabel_, bodyInput_, buttons_, cmd_, conditional_, edgesId_ (+23 more)

### Community 17 - "Io.cpp"
Cohesion: 0.06
Nodes (30): MainWindow::print3d(), FileFormat, Brep, Iges, Obj, Step, Stl, ThreeMF (+22 more)

### Community 18 - "Unit"
Cohesion: 0.10
Nodes (30): ExpressionEnv, lengthUnit, lookup, ExpressionError, Quantity, angle, length, value (+22 more)

### Community 19 - ".apply"
Cohesion: 0.16
Nodes (10): Coil, def_, Extrude, def_, Revolve, def_, validateOperation(), x (+2 more)

### Community 20 - ".updatePreview"
Cohesion: 0.14
Nodes (4): angleInArc(), ccwContains(), circumcircle(), segDistance()

### Community 21 - "Viewport.h"
Cohesion: 0.08
Nodes (7): MarkingMenu::keyPressEvent(), QKeyEvent, QLabel, QLineEdit, QMouseEvent, ViewInteractor, Viewport::setInteractor()

### Community 23 - "TEST"
Cohesion: 0.08
Nodes (7): Sketch, constraints, entities, points, Sketch::addCircle(), Sketch::addLine(), TEST()

### Community 24 - "Sketch.cpp"
Cohesion: 0.09
Nodes (16): Point, x, y, SketchError, entityTypeName(), isDimension(), Sketch::addSpline(), Sketch::checkIndices() (+8 more)

### Community 25 - "ViewportSketch.cpp"
Cohesion: 0.08
Nodes (6): faceStyle(), lineStyle(), rgb(), Viewport::lookAt(), Viewport::planePoint(), Viewport::toWidget()

### Community 26 - "SketchPalette"
Cohesion: 0.06
Nodes (26): QAbstractButton, QAction, QCheckBox, QLabel, QWidget, SketchEditor, SketchPalette, body_ (+18 more)

### Community 27 - "Constraint"
Cohesion: 0.11
Nodes (15): Constraint, driven, entities, expression, hasLabel, labelX, labelY, name (+7 more)

### Community 28 - "SketchProfiles"
Cohesion: 0.17
Nodes (10): Loft, def_, parsePoints(), pickedFaces(), profilesOf(), SketchProfiles, frame, profiles (+2 more)

### Community 29 - "AdskModule.cpp"
Cohesion: 0.12
Nodes (13): Application, BRepBodies, Component, Design, Product, raiseIfError(), UserParameter, name (+5 more)

### Community 30 - "Colors"
Cohesion: 0.07
Nodes (28): Colors, base, border, cubeBox, cubeText, errorBackground, grid, gridMajor (+20 more)

### Community 31 - "KernelError"
Cohesion: 0.24
Nodes (25): KernelError, WallSide, Center, Side1, Side2, boolean(), chamfer(), chamferEx() (+17 more)

### Community 32 - "SketchOps.cpp"
Cohesion: 0.18
Nodes (22): ChainSegment, entity, forward, at(), chainOf(), chamferCorner(), cornerAt(), cross() (+14 more)

### Community 33 - "Session.cpp"
Cohesion: 0.06
Nodes (42): CommandSession, inputs_, expressionKey(), checkInputValue(), CommandContext::evaluateExpression(), CommandDef::input(), CommandSession::applyInTransaction(), CommandSession::cancel() (+34 more)

### Community 34 - "ParameterCompleter"
Cohesion: 0.12
Nodes (9): MainWindow::attachArrowCompleters(), ParameterCompleter, completer_, edit_, names_, ParameterCompleter::ParameterCompleter(), public, QCompleter (+1 more)

### Community 35 - "ConstructAxisPoint"
Cohesion: 0.16
Nodes (6): ConstructAxisPoint, def_, kind_, differenceOrNull(), JointPick, frame

### Community 38 - "solve"
Cohesion: 0.18
Nodes (12): addConstraintChecked(), Layout, n, px, py, rad, makeLayout(), pack() (+4 more)

### Community 39 - "ViewportAnalysis.cpp"
Cohesion: 0.10
Nodes (5): packed(), ramp(), shade(), Viewport::buildAnalysis(), Viewport::setCurvatureComb()

### Community 41 - "ConstraintType"
Cohesion: 0.08
Nodes (24): ConstraintType, Angle, Coincident, Collinear, Concentric, Diameter, Distance, Equal (+16 more)

### Community 42 - "TEST"
Cohesion: 0.09
Nodes (3): param(), TEST(), tmp()

### Community 43 - "Pick"
Cohesion: 0.13
Nodes (14): Pick, bodyArc, bodyPoint, bodySegment, hit, midpointOf, onEntity, onXAxis (+6 more)

### Community 44 - "Snap"
Cohesion: 0.11
Nodes (18): Snap, alignX, alignY, bodyArc, bodySegment, entity, fromX, fromY (+10 more)

### Community 45 - "Kind"
Cohesion: 0.09
Nodes (21): HudField, edit, editing, kind, locked, value, Kind, Angle (+13 more)

### Community 46 - "Inputs"
Cohesion: 0.08
Nodes (13): CommandContext, CommandError, Inputs, CommandSession::CommandSession(), getBool(), getInt(), bodyCentre(), bodyName() (+5 more)

### Community 47 - "AnalysisSettings"
Cohesion: 0.08
Nodes (21): AnalysisKind, CurvatureMap, Draft, None, Zebra, AnalysisSettings, curvatureScale, draftAngle (+13 more)

### Community 48 - "Document.cpp"
Cohesion: 0.09
Nodes (28): ConstructionPlane, name, spec, Document::axes(), Document::bodies(), Document::body(), Document::bodyName(), Document::components() (+20 more)

### Community 49 - "Session"
Cohesion: 0.10
Nodes (7): PythonHost::PythonHost(), Session, commands_, doc_, listeners_, nextListener_, path_

### Community 50 - "MainWindowSketch.cpp"
Cohesion: 0.09
Nodes (11): MainWindow::cancelSketch(), MainWindow::editSketch(), MainWindow::finishSketch(), MainWindow::onProfileClicked(), MainWindow::originalShape(), MainWindow::sketchPalette(), MainWindow::sketchVisible(), MainWindow::startSketch() (+3 more)

### Community 51 - "InputDef"
Cohesion: 0.08
Nodes (24): InputDef, choices, defaultValue, id, label, max, min, minExclusive (+16 more)

### Community 54 - "ViewportAnalysis.cpp"
Cohesion: 0.11
Nodes (8): ArrowPlacement, base, dir, edgePlacement(), facesPlacement(), MainWindow::patternCentre(), MainWindow::pickedFaces(), MainWindow::updateDragArrow()

### Community 55 - ".rebuild"
Cohesion: 0.16
Nodes (6): ext(), fixedColor(), freeColor(), qc(), rgb(), wire()

### Community 56 - "Theme.cpp"
Cohesion: 0.19
Nodes (6): setIconTheme(), darkColors(), darkPalette(), darkStyleSheet(), lightColors(), lightStyleSheet()

### Community 57 - "MainWindow.cpp"
Cohesion: 0.11
Nodes (5): commandIcon(), flatButton(), qs(), MainWindow::applySection(), QToolButton

### Community 58 - "Entity"
Cohesion: 0.11
Nodes (17): Entity, a, b, center, construction, fit, projected, radius (+9 more)

### Community 59 - "xdrive.py"
Cohesion: 0.32
Nodes (14): button(), canvas(), click(), drag(), flush(), geometry(), key(), keycode() (+6 more)

### Community 61 - "SketchGeometry.cpp"
Cohesion: 0.10
Nodes (14): Profile, area, face, x, y, curve(), curves(), customPlaneSpec() (+6 more)

### Community 62 - "Architecture"
Cohesion: 0.40
Nodes (4): Architecture, How a command works, The document, Units

### Community 63 - "ViewportArrow.cpp"
Cohesion: 0.09
Nodes (15): Viewport::frontEdgeOwner(), rgb(), segmentDistance(), Viewport::arrowAt(), Viewport::arrowMouseMove(), Viewport::arrowMousePress(), Viewport::arrowMouseRelease(), Viewport::arrowParam() (+7 more)

### Community 64 - "string"
Cohesion: 0.10
Nodes (30): completeEdgeReferences(), completeFaceReferences(), decode(), decodeFaces(), dot(), edgeReference(), EdgeSig, full (+22 more)

### Community 65 - "CommandRegistry"
Cohesion: 0.12
Nodes (4): CommandRegistry, cmds_, CommandRegistry::add(), TEST()

### Community 66 - "PythonHost.cpp"
Cohesion: 0.19
Nodes (8): Result, error, ok, output, captured(), PythonHost::exec(), PythonHost::runScript(), fn

### Community 67 - "TopoDS_Shape"
Cohesion: 0.15
Nodes (24): SurfacePoint, normal, point, Vec3, asSolid(), boundingBox(), edgeMidpoint(), edgesNear() (+16 more)

### Community 68 - "Theme"
Cohesion: 0.22
Nodes (4): Theme, colors_, public, styled_

### Community 69 - "MainWindow::MainWindow"
Cohesion: 0.15
Nodes (4): PythonHost, MainWindow::MainWindow(), MainWindow::exitSketchMode(), MainWindow::showPreferences()

### Community 70 - "sketchFor"
Cohesion: 0.16
Nodes (13): applyOperation(), CopyFn, Hole, def_, PathPattern, def_, patternFeatures(), placeCopies() (+5 more)

### Community 71 - "ParametersDialog.cpp"
Cohesion: 0.12
Nodes (13): number(), ParametersDialog, building_, error_, listener_, public, rebuildPending_, tree_ (+5 more)

### Community 72 - "QObject"
Cohesion: 0.13
Nodes (6): QObject, Hit, index, kind, SketchEditor::SketchEditor(), edges

### Community 75 - "InputType"
Cohesion: 0.12
Nodes (17): InputType, Axis, Bodies, Body, Bool, Choice, Edges, Faces (+9 more)

### Community 76 - "Feature"
Cohesion: 0.22
Nodes (9): Feature, commandId, error, id, inputs, name, rolledBack, suppressed (+1 more)

### Community 77 - "MarkingMenu.cpp"
Cohesion: 0.12
Nodes (7): MarkingMenu::MarkingMenu(), MarkingMenu::mouseMoveEvent(), MarkingMenu::paintEvent(), MarkingMenu::popupAt(), MarkingMenu::ringIndexAt(), MarkingMenu::run(), MarkingMenu::triggerForTest()

### Community 80 - "SketchDisplay"
Cohesion: 0.13
Nodes (10): ProfileObject, index, sketch, SketchDisplay, construction, curves, frame, name (+2 more)

### Community 81 - "Unit"
Cohesion: 0.09
Nodes (21): bindAdsk(), MainWindow::lengthUnit(), Dimension, Angle, Length, Unitless, Unit, Centimeter (+13 more)

### Community 82 - "Measurement"
Cohesion: 0.09
Nodes (20): BoundingBox, max, min, Kind, Angle, Area, Length, Volume (+12 more)

### Community 84 - "BooleanOp"
Cohesion: 0.24
Nodes (7): BooleanOp, Cut, Intersect, Join, ChamferType, DistanceAngle, TwoDistances

### Community 85 - "Level"
Cohesion: 0.12
Nodes (13): debug(), error(), info(), Level, Debug, Error, Info, Warning (+5 more)

### Community 86 - "README.md"
Cohesion: 0.10
Nodes (16): Build, Conventions, Development, Tests, Known gaps, Reference parts, Fusion feature checklist, Roadmap (+8 more)

### Community 87 - "Document.cpp"
Cohesion: 0.08
Nodes (32): DocumentError, SketchRecord, data, name, offset, plane, Document::abortTransaction(), Document::addUserParameter() (+24 more)

### Community 90 - "UserParameter"
Cohesion: 0.33
Nodes (6): UserParameter, comment, expression, name, unit, value

### Community 91 - "UiCommand"
Cohesion: 0.14
Nodes (11): UiCommand, enabled, icon, id, name, panel, run, shortcut (+3 more)

### Community 93 - "Known differences still to build"
Cohesion: 0.15
Nodes (12): Data and files, Findings from the videos, Fusion study list, Interface, Known differences still to build, Navigation and display, Selection and the canvas, Sketch (+4 more)

### Community 95 - "ThreadInfo"
Cohesion: 0.50
Nodes (4): ThreadInfo, diameter, internal, pitch

### Community 96 - "cmath"
Cohesion: 0.11
Nodes (8): MarkingMenu, enabled, public, Case, name, fail(), Failure, Register

### Community 97 - "BodyFrame"
Cohesion: 0.15
Nodes (14): BodyFrame, diag, dx, dy, dz, x0, y0, z0 (+6 more)

### Community 98 - "FakeDoc"
Cohesion: 0.17
Nodes (6): FakeDoc, aborts, commits, items, open, snapshot

### Community 99 - "TEST"
Cohesion: 0.19
Nodes (3): slurp(), TEST(), tmp()

### Community 100 - "Zip.cpp"
Cohesion: 0.19
Nodes (11): Entry, data, name, ZipError, crc32(), get16(), get32(), put16() (+3 more)

### Community 102 - "Axis"
Cohesion: 0.50
Nodes (4): Axis, X, Y, Z

### Community 103 - "Document::load"
Cohesion: 0.17
Nodes (5): doc_(), Document::Document(), Document::ocafBytes(), ocafApplication(), Document::load()

### Community 104 - "planeOf"
Cohesion: 0.21
Nodes (6): ConstructPlane, def_, kind_, evaluateDimensions(), openChains(), planeOf()

### Community 106 - "SectionState"
Cohesion: 0.25
Nodes (7): SectionState, active, angle, flip, offset, plane, visible

### Community 107 - "Display"
Cohesion: 0.25
Nodes (7): Display, constraints, construction, dimensions, points, profiles, projected

### Community 109 - "string"
Cohesion: 0.15
Nodes (16): bodyNumber(), Document::addBody(), Document::bodyShapes(), Document::component(), Document::componentOfBody(), Document::effectOf(), Document::evaluate(), Document::nextAxisName() (+8 more)

### Community 110 - "openWallBand"
Cohesion: 0.15
Nodes (19): Section, Circular, Square, Triangular, TopologyCounts, edges, faces, shells (+11 more)

### Community 111 - "ConstructionPoint"
Cohesion: 0.29
Nodes (5): ConstructionPoint, name, point, Document::point(), Document::setPoint()

### Community 112 - "ConstructionAxis"
Cohesion: 0.29
Nodes (5): ConstructionAxis, axis, name, Document::axis(), Document::setAxis()

### Community 113 - "main"
Cohesion: 0.36
Nodes (4): listCommands(), main(), usage(), main()

### Community 114 - "uninstall.sh"
Cohesion: 0.52
Nodes (6): die(), manifest_for(), refresh(), uninstall.sh script, step(), usage()

### Community 115 - "install.sh"
Cohesion: 0.60
Nodes (5): die(), refresh(), install.sh script, step(), usage()

### Community 116 - "TsrModule.cpp"
Cohesion: 0.33
Nodes (4): bindTsr(), fromPy(), toPy(), typeName()

### Community 118 - "FeatureEffect"
Cohesion: 0.10
Nodes (16): Body, display, name, shape, Component, bodies, name, FeatureEffect (+8 more)

### Community 123 - "smoke"
Cohesion: 0.40
Nodes (5): smoke(), MassProperties, area, centerOfMass, volume

### Community 124 - "Sketch.h"
Cohesion: 0.29
Nodes (6): EntityType, Arc, Circle, Line, Spline, isRound()

### Community 125 - "ModelParameter"
Cohesion: 0.29
Nodes (7): ModelParameter, angle, expression, name, owner, value, Document::modelParameters()

### Community 126 - "Column"
Cohesion: 0.33
Nodes (6): Column, kComment, kExpression, kParameter, kUnit, kValue

## Knowledge Gaps
- **651 isolated node(s):** `ok`, `output`, `error`, `isReal`, `real` (+646 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 1228 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **33 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `optional` connect `optional` to `Viewport`, `MainWindow`, `DocCommands.cpp`, `QString`, `Kernel.cpp`, `Io.cpp`, `Unit`, `.updatePreview`, `Viewport.h`, `ViewportSketch.cpp`, `SketchOps.cpp`, `CommandDialog.cpp`, `AnalysisSettings`, `Document.cpp`, `Session`, `InputDef`, `ViewportAnalysis.cpp`, `ViewportArrow.cpp`, `TopoDS_Shape`, `sketchFor`, `Feature`, `Unit`, `Document.cpp`, `string`, `ConstructionPoint`, `ConstructionAxis`?**
  _High betweenness centrality (0.132) - this node is a cross-community bridge._
- **What connects `ok`, `output`, `error` to the rest of the system?**
  _651 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Viewport` be split into smaller, more focused modules?**
  _Cohesion score 0.01815408085430969 - nodes in this community are weakly interconnected._
- **Why does `SketchEditor` connect `SketchEditor` to `Viewport`, `QObject`, `Display`, `optional`, `.projectAt`, `Kind`, `Pick`, `Snap`, `Unit`, `Session`, `.updatePreview`, `.askValue`, `FeatureEffect`, `.rebuild`, `Viewport.h`, `QObject`, `Entity`, `.solveAndShow`?**
  _High betweenness centrality (0.109) - this node is a cross-community bridge._
- **Should `Icons.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.06702605570530099 - nodes in this community are weakly interconnected._
- **Why does `MainWindow` connect `MainWindow` to `MainWindow::enterSketchMode`, `ParameterCompleter`, `MainWindow::MainWindow`, `.openMarkingMenu`, `.buildAppBar`, `SectionState`, `optional`, `UiCommand`, `MainWindowTools.cpp`, `Session`, `MainWindowSketch.cpp`, `rect`, `.showDialog`, `ViewportAnalysis.cpp`, `MainWindow.cpp`, `SketchPalette`, `smoke`?**
  _High betweenness centrality (0.099) - this node is a cross-community bridge._
- **Should `tsr` be split into smaller, more focused modules?**
  _Cohesion score 0.06765327695560254 - nodes in this community are weakly interconnected._