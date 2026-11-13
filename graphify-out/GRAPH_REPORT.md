# Graph Report - tessera  (2026-11-13)

## Corpus Check
- 344 files · ~200,281 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 37 file(s) not represented in the graph (top: .drive 29, (none) 5, .cmake 1)

## Summary
- 3173 nodes · 7946 edges · 130 communities (98 shown, 32 thin omitted)
- Extraction: 84% EXTRACTED · 16% INFERRED · 0% AMBIGUOUS · INFERRED: 1241 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `09f8b702`
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
- dimensionOf
- optional
- Kernel.cpp
- .projectAt
- Kind
- QDialog
- CommandDialog
- Io.cpp
- Unit
- CommandError
- .updatePreview
- Viewport.h
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
- Document.cpp
- CommandDialog.cpp
- Command.cpp
- solve
- ViewportAnalysis.cpp
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
- .rebuild
- Theme.cpp
- TEST
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
- DocCommands.cpp
- ParametersDialog.cpp
- Handle
- ExpressionSpinBox
- InputType
- Feature
- MarkingMenu.cpp
- Value.h
- SketchDisplay
- string
- Measurement
- rect
- Entity
- Level
- README.md
- ext
- UserParameter
- cmath
- Known differences still to build
- SketchEditor::SketchEditor
- .add
- MarkingMenu
- BodyFrame
- FakeDoc
- Mesh
- Zip.cpp
- AddUserParameter
- Kernel.h
- Document::load
- ParameterCompleter.cpp
- Development
- SectionState
- Display
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
- Session::addListener
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

## Communities (130 total, 32 thin omitted)

### Community 0 - "Viewport"
Cohesion: 0.02
Nodes (57): view_, QLineEdit, Viewport, analysis_, analysisObjects_, appliedGridStep_, arrowBoxes_, arrowDragging_ (+49 more)

### Community 1 - "Icons.cpp"
Cohesion: 0.07
Nodes (91): arcIcon(), arrow(), axisIcon(), box(), centerRectIcon(), chamferIcon(), circleIcon(), coilIcon() (+83 more)

### Community 2 - "Command"
Cohesion: 0.12
Nodes (21): Adding a tool, Command, getInt(), getReal(), CircularPattern, def_, makeBox(), makeCone() (+13 more)

### Community 4 - "MainWindow"
Cohesion: 0.03
Nodes (63): CommandDialog, MainWindow, active_, arrowInput_, arrowInput2_, bodiesBeforeCommand_, combEdges_, combPicking_ (+55 more)

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
Cohesion: 0.05
Nodes (13): MarkingMenu::keyPressEvent(), keys(), NavPreset, Fusion, SolidWorks, Tinkercad, qc(), QKeyEvent (+5 more)

### Community 9 - "SketchEditor"
Cohesion: 0.03
Nodes (42): SketchEditor, arcDrag_, arcDragMoved_, arcEndsChain_, arcFrom_, arcRef_, bodyEdges_, boxing_ (+34 more)

### Community 10 - "dimensionOf"
Cohesion: 0.18
Nodes (7): formatNumber(), Dimension, Angle, Length, Unitless, inputExpression(), dimensionOf()

### Community 13 - ".projectAt"
Cohesion: 0.14
Nodes (5): PlaneEdges, arcs, segments, vertices, edges

### Community 14 - "Kind"
Cohesion: 0.08
Nodes (25): ConstructPlane, def_, kind_, EdgeFeature, def_, kind_, FaceFeature, def_ (+17 more)

### Community 15 - "QDialog"
Cohesion: 0.10
Nodes (18): QDialog, MainWindow::checkInterference(), MainWindow::driveJoints(), MainWindow::exportDesign(), MainWindow::formatLength(), MainWindow::gridSettings(), MainWindow::insertFile(), MainWindow::openAnalysis() (+10 more)

### Community 16 - "CommandDialog"
Cohesion: 0.05
Nodes (31): CommandDialog, bodiesId_, bodiesLabel_, bodyInput_, buttons_, cmd_, conditional_, edgesId_ (+23 more)

### Community 17 - "Io.cpp"
Cohesion: 0.12
Nodes (15): MainWindow::print3d(), NamedShape, compoundOf(), exportShapes(), fmt(), formatForPath(), fromBrep(), importShape() (+7 more)

### Community 18 - "Unit"
Cohesion: 0.07
Nodes (46): MainWindow::lengthUnit(), ExpressionEnv, lengthUnit, lookup, ExpressionError, Quantity, angle, length (+38 more)

### Community 19 - "CommandError"
Cohesion: 0.11
Nodes (16): CommandError, getBool(), bodyCentre(), bodyName(), Coil, def_, Joint, def_ (+8 more)

### Community 21 - "Viewport.h"
Cohesion: 0.11
Nodes (6): QLabel, Profile, area, face, x, y

### Community 22 - "MainWindow.cpp"
Cohesion: 0.06
Nodes (3): commandIcon(), qs(), MainWindow::beginSketch()

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
Cohesion: 0.04
Nodes (34): flatButton(), MainWindow::applySection(), MainWindow::chooseUnits(), MainWindow::measurePick(), MainWindow::sectionFrame(), MainWindow::sectionPlane(), MainWindow::setSelectionFilter(), MainWindow::showParameters() (+26 more)

### Community 29 - "AdskModule.cpp"
Cohesion: 0.09
Nodes (16): Application, bindAdsk(), BRepBodies, BRepBody, index, Component, Design, Product (+8 more)

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
Cohesion: 0.18
Nodes (8): QObject, ParameterCompleter, completer_, edit_, names_, public, QCompleter, QLineEdit

### Community 35 - "Document.cpp"
Cohesion: 0.11
Nodes (8): bodyNumber(), Document::features(), Document::historyMarker(), Document::nextBodyName(), Document::redo(), Document::undo(), fromJson(), timelineData()

### Community 37 - "Command.cpp"
Cohesion: 0.24
Nodes (10): expressionKey(), checkInputValue(), CommandContext::evaluateExpression(), CommandDef::input(), CommandSession::applyInTransaction(), CommandSession::cancel(), CommandSession::execute(), CommandSession::preview() (+2 more)

### Community 38 - "solve"
Cohesion: 0.17
Nodes (13): addConstraintChecked(), Layout, n, px, py, rad, makeLayout(), pack() (+5 more)

### Community 39 - "ViewportAnalysis.cpp"
Cohesion: 0.13
Nodes (5): packed(), ramp(), shade(), Viewport::buildAnalysis(), Viewport::setCurvatureComb()

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
Cohesion: 0.12
Nodes (8): CommandSession, inputs_, CommandRegistry::find(), CommandRegistry::run(), OwnedCommand, owned, OwningCommandSession, Session::begin()

### Community 47 - "AnalysisSettings"
Cohesion: 0.15
Nodes (13): AnalysisKind, CurvatureMap, Draft, None, Zebra, AnalysisSettings, curvatureScale, draftAngle (+5 more)

### Community 48 - "Document.cpp"
Cohesion: 0.13
Nodes (21): ConstructionPlane, name, spec, Document::axes(), Document::bodies(), Document::body(), Document::bodyName(), Document::components() (+13 more)

### Community 49 - "Session"
Cohesion: 0.10
Nodes (7): PythonHost::PythonHost(), Session, commands_, doc_, listeners_, nextListener_, path_

### Community 50 - "MainWindowSketch.cpp"
Cohesion: 0.07
Nodes (15): MainWindow::buildSketchTab(), MainWindow::cancelSketch(), MainWindow::editSketch(), MainWindow::enterSketchMode(), MainWindow::finishSketch(), MainWindow::onEdgeClicked(), MainWindow::onProfileClicked(), MainWindow::originalShape() (+7 more)

### Community 51 - "InputDef"
Cohesion: 0.04
Nodes (56): CommandDef, feature, icon, id, inputs, name, nameInput, panel (+48 more)

### Community 54 - "ViewportAnalysis.cpp"
Cohesion: 0.12
Nodes (7): ArrowPlacement, base, dir, edgePlacement(), facesPlacement(), MainWindow::patternCentre(), MainWindow::pickedFaces()

### Community 55 - ".rebuild"
Cohesion: 0.19
Nodes (5): fixedColor(), freeColor(), qc(), rgb(), wire()

### Community 56 - "Theme.cpp"
Cohesion: 0.19
Nodes (6): setIconTheme(), darkColors(), darkPalette(), darkStyleSheet(), lightColors(), lightStyleSheet()

### Community 57 - "TEST"
Cohesion: 0.19
Nodes (3): slurp(), TEST(), tmp()

### Community 58 - "Constraint"
Cohesion: 0.10
Nodes (20): Constraint, driven, entities, expression, hasLabel, labelX, labelY, points (+12 more)

### Community 59 - "xdrive.py"
Cohesion: 0.32
Nodes (14): button(), canvas(), click(), drag(), flush(), geometry(), key(), keycode() (+6 more)

### Community 61 - "SketchGeometry.cpp"
Cohesion: 0.12
Nodes (9): curve(), curves(), customPlaneSpec(), interiorPoint(), planeFrame(), profileAt(), profiles(), toSketch() (+1 more)

### Community 62 - "MainWindow::MainWindow"
Cohesion: 0.13
Nodes (4): PythonHost, MainWindow::MainWindow(), MainWindow::exitSketchMode(), MainWindow::showPreferences()

### Community 63 - "ViewportArrow.cpp"
Cohesion: 0.06
Nodes (18): MarkingMenu::mouseMoveEvent(), QMouseEvent, ViewInteractor, Viewport::frontEdgeOwner(), rgb(), segmentDistance(), Viewport::arrowAt(), Viewport::arrowMouseMove() (+10 more)

### Community 64 - "string"
Cohesion: 0.10
Nodes (30): completeEdgeReferences(), completeFaceReferences(), decode(), decodeFaces(), dot(), edgeReference(), EdgeSig, full (+22 more)

### Community 65 - "CommandRegistry"
Cohesion: 0.12
Nodes (4): CommandRegistry, cmds_, CommandRegistry::add(), TEST()

### Community 66 - "PythonHost.cpp"
Cohesion: 0.15
Nodes (8): Result, error, ok, output, captured(), PythonHost::exec(), PythonHost::runScript(), CommandRegistry::all()

### Community 67 - "TopoDS_Shape"
Cohesion: 0.15
Nodes (24): SurfacePoint, normal, point, Vec3, asSolid(), boundingBox(), edgeMidpoint(), edgesNear() (+16 more)

### Community 68 - "Theme"
Cohesion: 0.22
Nodes (4): Theme, colors_, public, styled_

### Community 69 - "FileFormat"
Cohesion: 0.17
Nodes (12): FileFormat, Brep, Iges, Obj, Step, Stl, ThreeMF, FormatInfo (+4 more)

### Community 70 - "DocCommands.cpp"
Cohesion: 0.08
Nodes (27): applyOperation(), axisOf(), CopyFn, differenceOrNull(), InsertGeometry, def_, Loft, def_ (+19 more)

### Community 71 - "ParametersDialog.cpp"
Cohesion: 0.08
Nodes (21): Column, kComment, kExpression, kParameter, kUnit, kValue, number(), ParametersDialog (+13 more)

### Community 74 - "ExpressionSpinBox"
Cohesion: 0.19
Nodes (4): ExpressionSpinBox, eval_, expression_, shown_

### Community 75 - "InputType"
Cohesion: 0.12
Nodes (17): InputType, Axis, Bodies, Body, Bool, Choice, Edges, Faces (+9 more)

### Community 76 - "Feature"
Cohesion: 0.22
Nodes (9): Feature, commandId, error, id, inputs, name, rolledBack, suppressed (+1 more)

### Community 77 - "MarkingMenu.cpp"
Cohesion: 0.08
Nodes (17): UiCommand, enabled, icon, id, name, panel, run, shortcut (+9 more)

### Community 80 - "SketchDisplay"
Cohesion: 0.08
Nodes (18): DragArrow, base, dir, value, PendingLook, center, frame, size (+10 more)

### Community 81 - "string"
Cohesion: 0.17
Nodes (13): Document::component(), Document::componentOfBody(), Document::nextAxisName(), Document::nextComponentName(), Document::nextPlaneName(), Document::nextPointName(), Document::nextSketchName(), Document::parameterUsers() (+5 more)

### Community 82 - "Measurement"
Cohesion: 0.09
Nodes (20): BoundingBox, max, min, Kind, Angle, Area, Length, Volume (+12 more)

### Community 83 - "rect"
Cohesion: 0.28
Nodes (3): SelectionBox, crossing, rect()

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
Cohesion: 0.12
Nodes (18): SketchRecord, data, name, offset, plane, Document::openTransaction(), Document::recompute(), Document::recordFeature() (+10 more)

### Community 90 - "UserParameter"
Cohesion: 0.33
Nodes (6): UserParameter, comment, expression, name, unit, value

### Community 91 - "cmath"
Cohesion: 0.14
Nodes (6): Case, fn, name, fail(), Failure, Register

### Community 93 - "Known differences still to build"
Cohesion: 0.15
Nodes (12): Data and files, Findings from the videos, Fusion study list, Interface, Known differences still to build, Navigation and display, Selection and the canvas, Sketch (+4 more)

### Community 94 - "SketchEditor::SketchEditor"
Cohesion: 0.20
Nodes (5): SketchEditor::SketchEditor(), Tool, op, shape, target

### Community 96 - "MarkingMenu"
Cohesion: 0.40
Nodes (3): MarkingMenu, enabled, public

### Community 97 - "BodyFrame"
Cohesion: 0.15
Nodes (14): BodyFrame, diag, dx, dy, dz, x0, y0, z0 (+6 more)

### Community 98 - "FakeDoc"
Cohesion: 0.17
Nodes (6): FakeDoc, aborts, commits, items, open, snapshot

### Community 99 - "Mesh"
Cohesion: 0.40
Nodes (3): Mesh, nodes, triangles

### Community 100 - "Zip.cpp"
Cohesion: 0.20
Nodes (11): Entry, data, name, ZipError, crc32(), get16(), get32(), put16() (+3 more)

### Community 102 - "Kernel.h"
Cohesion: 0.09
Nodes (19): bindTsr(), fromPy(), toPy(), typeName(), Axis, X, Y, Z (+11 more)

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
Nodes (15): DocumentError, Document::abortTransaction(), Document::addBody(), Document::addUserParameter(), Document::axisFrame(), Document::bodyShapes(), Document::commitTransaction(), Document::effectOf() (+7 more)

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
Cohesion: 0.08
Nodes (16): Body, display, name, shape, Component, bodies, name, FeatureEffect (+8 more)

### Community 123 - "smoke"
Cohesion: 0.40
Nodes (5): smoke(), MassProperties, area, centerOfMass, volume

### Community 132 - "ChainSegment"
Cohesion: 0.67
Nodes (3): ChainSegment, entity, forward

## Knowledge Gaps
- **645 isolated node(s):** `ok`, `output`, `error`, `isReal`, `real` (+640 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 1219 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **32 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `optional` connect `optional` to `Viewport`, `MainWindow`, `Inputs`, `dimensionOf`, `Kernel.cpp`, `Io.cpp`, `Unit`, `Viewport.h`, `ViewportSketch.cpp`, `SketchEditor.cpp`, `SketchOps.cpp`, `CommandDialog.cpp`, `Document.cpp`, `Session`, `InputDef`, `.updateProfilesLabel`, `ViewportAnalysis.cpp`, `.rebuild`, `ViewportArrow.cpp`, `TopoDS_Shape`, `DocCommands.cpp`, `ExpressionSpinBox`, `Feature`, `SketchDisplay`, `string`, `ext`, `Kernel.h`, `ConstructionPoint`, `ConstructionAxis`, `FeatureEffect`?**
  _High betweenness centrality (0.119) - this node is a cross-community bridge._
- **What connects `ok`, `output`, `error` to the rest of the system?**
  _645 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Viewport` be split into smaller, more focused modules?**
  _Cohesion score 0.017978190391983496 - nodes in this community are weakly interconnected._
- **Why does `SketchEditor` connect `SketchEditor` to `Viewport`, `ParameterCompleter`, `Display`, `optional`, `.projectAt`, `Kind`, `Pick`, `Snap`, `Session`, `Unit`, `.updatePreview`, `Viewport.h`, `.rebuild`, `QObject`, `Constraint`, `SketchEditor.cpp`, `SketchEditor::SketchEditor`, `ViewportArrow.cpp`?**
  _High betweenness centrality (0.103) - this node is a cross-community bridge._
- **Should `Icons.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.06853038245000971 - nodes in this community are weakly interconnected._
- **Why does `Viewport` connect `Viewport` to `MainWindow`, `ParametersDialog.cpp`, `Viewport.cpp`, `QTimer`, `ViewportAnalysis.cpp`, `Handle`, `optional`, `AnalysisSettings`, `SketchDisplay`, `QDialog`, `rect`, `Viewport.h`, `.toPixels`, `.selectedSubShapes`, `ViewportArrow.cpp`?**
  _High betweenness centrality (0.099) - this node is a cross-community bridge._
- **Should `Command` be split into smaller, more focused modules?**
  _Cohesion score 0.12473118279569892 - nodes in this community are weakly interconnected._