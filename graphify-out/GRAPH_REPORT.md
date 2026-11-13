# Graph Report - tessera  (2026-11-13)

## Corpus Check
- 347 files · ~205,881 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 39 file(s) not represented in the graph (top: .drive 31, (none) 5, .cmake 1)

## Summary
- 3207 nodes · 8052 edges · 122 communities (96 shown, 26 thin omitted)
- Extraction: 84% EXTRACTED · 16% INFERRED · 0% AMBIGUOUS · INFERRED: 1256 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `6c30dec5`
- Run `git rev-parse HEAD` and compare to check if the graph is stale.
- Run `graphify update .` after code changes (no API cost).

## Community Hubs (Navigation)
- Viewport
- Icons.cpp
- DocCommands.cpp
- MainWindow
- run_oracle.py
- CommandContext
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
- CommandError
- SketchEditor.cpp
- .redrawAll
- .updatePreview
- TEST
- Sketch.cpp
- ViewportSketch.cpp
- SketchPalette
- Constraint
- string
- AdskModule.cpp
- Colors
- KernelError
- SketchOps.cpp
- Session.cpp
- ParameterCompleter
- ConstructAxisPoint
- CommandDialog.cpp
- Command.cpp
- solve
- ViewportAnalysis.cpp
- CommandSession
- ConstraintType
- Session
- Pick
- Snap
- Kind
- Inputs
- AnalysisSettings
- Document.cpp
- .add
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
- cmath
- TopoDS_Shape
- Theme
- FileFormat
- .motion
- src/main.cpp
- QObject
- Profile
- InputType
- Feature
- Rect
- math
- Value.h
- SketchDisplay
- PYBIND11_EMBEDDED_MODULE
- Measurement
- rect
- Kernel.h
- Level
- README.md
- Document.cpp
- test_feature_pattern.py
- isInputVisible
- UserParameter
- UiCommand
- Known differences still to build
- ChainSegment
- MarkingMenu
- BodyFrame
- FakeDoc
- TEST
- Zip.cpp
- DocumentError
- ConstructPlane
- SectionState
- Display
- string
- openWallBand
- ConstructionPoint
- ConstructionAxis
- main
- uninstall.sh
- install.sh
- FeatureEffect
- MainWindow::buildSketchTab
- smoke
- Sketch.h
- LAB_NOTES.md
- build.sh
- live-test.sh

## God Nodes (most connected - your core abstractions)
1. `Viewport` - 227 edges
2. `MainWindow` - 172 edges
3. `SketchEditor` - 166 edges
4. `Inputs` - 136 edges
5. `Document` - 128 edges
6. `CommandContext` - 102 edges
7. `render()` - 94 edges
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

## Communities (122 total, 26 thin omitted)

### Community 0 - "Viewport"
Cohesion: 0.02
Nodes (57): view_, QLineEdit, Viewport, analysis_, analysisObjects_, appliedGridStep_, arrowBoxes_, arrowDragging_ (+49 more)

### Community 1 - "Icons.cpp"
Cohesion: 0.06
Nodes (100): arc3Icon(), arcIcon(), arrow(), axisIcon(), box(), centerRectIcon(), chamferIcon(), circle2Icon() (+92 more)

### Community 2 - "DocCommands.cpp"
Cohesion: 0.14
Nodes (17): axisOf(), differenceOrNull(), evaluateDimensions(), makeBox(), makeCone(), makeCylinder(), makeSphere(), makeTorus() (+9 more)

### Community 4 - "MainWindow"
Cohesion: 0.03
Nodes (63): CommandDialog, MainWindow, active_, arrowInput_, arrowInput2_, bodiesBeforeCommand_, combEdges_, combPicking_ (+55 more)

### Community 5 - "run_oracle.py"
Cohesion: 0.08
Nodes (54): add_point(), arc_poly(), body_at(), body_list(), build_sketch(), chain(), circumcentre(), cm() (+46 more)

### Community 6 - "CommandContext"
Cohesion: 0.03
Nodes (56): Adding a tool, Command, CommandContext, CommandDef, feature, icon, id, inputs (+48 more)

### Community 7 - "Document"
Cohesion: 0.04
Nodes (11): Document, effects_, modified_, pendingTools_, registry_, replaying_, txnBodies_, FromOcaf (+3 more)

### Community 8 - "Viewport.cpp"
Cohesion: 0.05
Nodes (7): MarkingMenu::keyPressEvent(), keys(), qc(), QKeyEvent, QtFrameBuffer, rgb(), Viewport::Viewport()

### Community 9 - "SketchEditor"
Cohesion: 0.03
Nodes (44): SketchEditor, arcDrag_, arcDragMoved_, arcEndsChain_, arcFrom_, arcRef_, bodyEdges_, boxing_ (+36 more)

### Community 10 - "QString"
Cohesion: 0.11
Nodes (6): ExpressionSpinBox, eval_, expression_, shown_, formatNumber(), inputExpression()

### Community 13 - ".projectAt"
Cohesion: 0.14
Nodes (5): PlaneEdges, arcs, segments, vertices, edges

### Community 14 - "Kind"
Cohesion: 0.09
Nodes (19): EdgeFeature, def_, kind_, Kind, Angle, AxisCylinder, AxisEdge, AxisTwoPlanes (+11 more)

### Community 15 - "MainWindowTools.cpp"
Cohesion: 0.05
Nodes (26): QDialog, MainWindow::applySection(), MainWindow::checkInterference(), MainWindow::chooseUnits(), MainWindow::driveJoints(), MainWindow::exportDesign(), MainWindow::formatLength(), MainWindow::gridSettings() (+18 more)

### Community 16 - "CommandDialog"
Cohesion: 0.05
Nodes (31): CommandDialog, bodiesId_, bodiesLabel_, bodyInput_, buttons_, cmd_, conditional_, edgesId_ (+23 more)

### Community 17 - "Io.cpp"
Cohesion: 0.09
Nodes (18): MainWindow::print3d(), NamedShape, compoundOf(), exportShapes(), fmt(), formatForPath(), fromBrep(), importShape() (+10 more)

### Community 18 - "Unit"
Cohesion: 0.06
Nodes (50): MainWindow::lengthUnit(), ExpressionEnv, lengthUnit, lookup, ExpressionError, Quantity, angle, length (+42 more)

### Community 19 - "CommandError"
Cohesion: 0.17
Nodes (12): CommandError, applyOperation(), Extrude, def_, pickedFaces(), planeOf(), profilesOf(), sectionOf() (+4 more)

### Community 21 - ".redrawAll"
Cohesion: 0.11
Nodes (7): NavPreset, Fusion, SolidWorks, Tinkercad, Viewport::clearDragArrow(), Viewport::clearSecondArrow(), Viewport::setInteractor()

### Community 23 - "TEST"
Cohesion: 0.08
Nodes (8): Point, x, y, Sketch, constraints, entities, points, TEST()

### Community 24 - "Sketch.cpp"
Cohesion: 0.09
Nodes (14): SketchError, entityTypeName(), isDimension(), Sketch::addCircle(), Sketch::addSpline(), Sketch::checkIndices(), Sketch::entityPoints(), Sketch::fromJson() (+6 more)

### Community 25 - "ViewportSketch.cpp"
Cohesion: 0.08
Nodes (6): faceStyle(), lineStyle(), rgb(), Viewport::lookAt(), Viewport::planePoint(), Viewport::toWidget()

### Community 26 - "SketchPalette"
Cohesion: 0.07
Nodes (22): QLabel, QWidget, SketchEditor, SketchPalette, body_, constraints_, construction_, dimensions_ (+14 more)

### Community 27 - "Constraint"
Cohesion: 0.09
Nodes (21): Constraint, driven, entities, expression, hasLabel, labelX, labelY, name (+13 more)

### Community 28 - "string"
Cohesion: 0.10
Nodes (12): AddUserParameter, def_, Coil, def_, CreateSketch, def_, isIdentifier(), Loft (+4 more)

### Community 29 - "AdskModule.cpp"
Cohesion: 0.10
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
Cohesion: 0.14
Nodes (23): historyEdit(), OwnedCommand, owned, OwningCommandSession, Session::addListener(), Session::begin(), Session::deleteFeature(), Session::deleteParameter() (+15 more)

### Community 34 - "ParameterCompleter"
Cohesion: 0.12
Nodes (9): MainWindow::attachArrowCompleters(), ParameterCompleter, completer_, edit_, names_, ParameterCompleter::ParameterCompleter(), public, QCompleter (+1 more)

### Community 35 - "ConstructAxisPoint"
Cohesion: 0.12
Nodes (7): ConstructAxisPoint, def_, kind_, JointPick, frame, NewComponent, def_

### Community 37 - "Command.cpp"
Cohesion: 0.24
Nodes (9): checkInputValue(), CommandContext::evaluateExpression(), CommandDef::input(), CommandSession::applyInTransaction(), CommandSession::cancel(), CommandSession::execute(), CommandSession::preview(), CommandSession::setInput() (+1 more)

### Community 38 - "solve"
Cohesion: 0.18
Nodes (12): addConstraintChecked(), Layout, n, px, py, rad, makeLayout(), pack() (+4 more)

### Community 39 - "ViewportAnalysis.cpp"
Cohesion: 0.09
Nodes (6): QLabel, packed(), ramp(), shade(), Viewport::buildAnalysis(), Viewport::setCurvatureComb()

### Community 40 - "CommandSession"
Cohesion: 0.17
Nodes (4): CommandSession, inputs_, CommandRegistry::find(), CommandRegistry::run()

### Community 41 - "ConstraintType"
Cohesion: 0.08
Nodes (24): ConstraintType, Angle, Coincident, Collinear, Concentric, Diameter, Distance, Equal (+16 more)

### Community 42 - "Session"
Cohesion: 0.05
Nodes (11): PythonHost::PythonHost(), main(), Session, commands_, doc_, listeners_, nextListener_, path_ (+3 more)

### Community 43 - "Pick"
Cohesion: 0.11
Nodes (17): Hit, index, kind, Pick, bodyArc, bodyPoint, bodySegment, hit (+9 more)

### Community 44 - "Snap"
Cohesion: 0.10
Nodes (18): Snap, alignX, alignY, bodyArc, bodySegment, entity, fromX, fromY (+10 more)

### Community 45 - "Kind"
Cohesion: 0.09
Nodes (21): HudField, edit, editing, kind, locked, value, Kind, Angle (+13 more)

### Community 46 - "Inputs"
Cohesion: 0.12
Nodes (19): Inputs, getBool(), getInt(), getReal(), bodyCentre(), bodyName(), checkPattern(), CopyFn (+11 more)

### Community 47 - "AnalysisSettings"
Cohesion: 0.15
Nodes (13): AnalysisKind, CurvatureMap, Draft, None, Zebra, AnalysisSettings, curvatureScale, draftAngle (+5 more)

### Community 48 - "Document.cpp"
Cohesion: 0.09
Nodes (28): ConstructionPlane, name, spec, Document::addUserParameter(), Document::axes(), Document::bodies(), Document::body(), Document::bodyName() (+20 more)

### Community 50 - "MainWindowSketch.cpp"
Cohesion: 0.05
Nodes (19): MainWindow::cancelSketch(), MainWindow::editSketch(), MainWindow::finishSketch(), MainWindow::onEdgeClicked(), MainWindow::onProfileClicked(), MainWindow::originalShape(), MainWindow::sketchPalette(), MainWindow::sketchVisible() (+11 more)

### Community 51 - "InputDef"
Cohesion: 0.08
Nodes (24): InputDef, choices, defaultValue, id, label, max, min, minExclusive (+16 more)

### Community 54 - "ViewportAnalysis.cpp"
Cohesion: 0.12
Nodes (7): ArrowPlacement, base, dir, edgePlacement(), facesPlacement(), MainWindow::patternCentre(), MainWindow::pickedFaces()

### Community 55 - ".rebuild"
Cohesion: 0.13
Nodes (7): ext(), fixedColor(), freeColor(), qc(), rgb(), wire(), Sketch::addLine()

### Community 56 - "Theme.cpp"
Cohesion: 0.19
Nodes (6): setIconTheme(), darkColors(), darkPalette(), darkStyleSheet(), lightColors(), lightStyleSheet()

### Community 57 - "MainWindow.cpp"
Cohesion: 0.06
Nodes (9): commandIcon(), flatButton(), MainWindow::MainWindow(), qs(), MainWindow::beginSketch(), MainWindow::enterSketchMode(), MainWindow::exitSketchMode(), QToolButton (+1 more)

### Community 58 - "Entity"
Cohesion: 0.22
Nodes (9): Entity, a, b, center, construction, fit, projected, radius (+1 more)

### Community 59 - "xdrive.py"
Cohesion: 0.32
Nodes (14): button(), canvas(), click(), drag(), flush(), geometry(), key(), keycode() (+6 more)

### Community 61 - "SketchGeometry.cpp"
Cohesion: 0.11
Nodes (9): curve(), curves(), customPlaneSpec(), interiorPoint(), planeFrame(), profileAt(), profiles(), toSketch() (+1 more)

### Community 62 - "Architecture"
Cohesion: 0.40
Nodes (4): Architecture, How a command works, The document, Units

### Community 63 - "ViewportArrow.cpp"
Cohesion: 0.07
Nodes (17): QMouseEvent, ViewInteractor, Viewport::frontEdgeOwner(), rgb(), segmentDistance(), Viewport::arrowAt(), Viewport::arrowMouseMove(), Viewport::arrowMousePress() (+9 more)

### Community 64 - "string"
Cohesion: 0.10
Nodes (30): completeEdgeReferences(), completeFaceReferences(), decode(), decodeFaces(), dot(), edgeReference(), EdgeSig, full (+22 more)

### Community 65 - "CommandRegistry"
Cohesion: 0.12
Nodes (4): CommandRegistry, cmds_, CommandRegistry::add(), TEST()

### Community 66 - "cmath"
Cohesion: 0.09
Nodes (13): Result, error, ok, output, captured(), PythonHost::exec(), PythonHost::runScript(), Case (+5 more)

### Community 67 - "TopoDS_Shape"
Cohesion: 0.15
Nodes (24): SurfacePoint, normal, point, Vec3, asSolid(), boundingBox(), edgeMidpoint(), edgesNear() (+16 more)

### Community 68 - "Theme"
Cohesion: 0.20
Nodes (5): MainWindow::showPreferences(), Theme, colors_, public, styled_

### Community 69 - "FileFormat"
Cohesion: 0.17
Nodes (12): FileFormat, Brep, Iges, Obj, Step, Stl, ThreeMF, FormatInfo (+4 more)

### Community 70 - ".motion"
Cohesion: 0.36
Nodes (3): Joint, def_, jointOrigin()

### Community 71 - "src/main.cpp"
Cohesion: 0.05
Nodes (22): grabWindowWithPanels(), writeLiveGeometry(), Column, kComment, kExpression, kParameter, kUnit, kValue (+14 more)

### Community 74 - "Profile"
Cohesion: 0.33
Nodes (5): Profile, area, face, x, y

### Community 75 - "InputType"
Cohesion: 0.08
Nodes (21): bindTsr(), fromPy(), toPy(), typeName(), InputType, Axis, Bodies, Body (+13 more)

### Community 76 - "Feature"
Cohesion: 0.22
Nodes (9): Feature, commandId, error, id, inputs, name, rolledBack, suppressed (+1 more)

### Community 77 - "Rect"
Cohesion: 0.50
Nodes (4): Session::notifyChanged(), Rect, l, p

### Community 80 - "SketchDisplay"
Cohesion: 0.08
Nodes (18): DragArrow, base, dir, value, PendingLook, center, frame, size (+10 more)

### Community 82 - "Measurement"
Cohesion: 0.09
Nodes (20): BoundingBox, max, min, Kind, Angle, Area, Length, Volume (+12 more)

### Community 83 - "rect"
Cohesion: 0.28
Nodes (3): SelectionBox, crossing, rect()

### Community 84 - "Kernel.h"
Cohesion: 0.10
Nodes (15): Axis, X, Y, Z, BooleanOp, Cut, Intersect, Join (+7 more)

### Community 85 - "Level"
Cohesion: 0.12
Nodes (13): debug(), error(), info(), Level, Debug, Error, Info, Warning (+5 more)

### Community 86 - "README.md"
Cohesion: 0.10
Nodes (16): Build, Conventions, Development, Tests, Known gaps, Reference parts, Fusion feature checklist, Roadmap (+8 more)

### Community 87 - "Document.cpp"
Cohesion: 0.10
Nodes (24): SketchRecord, data, name, offset, plane, Document::abortTransaction(), Document::commitTransaction(), Document::openTransaction() (+16 more)

### Community 90 - "UserParameter"
Cohesion: 0.33
Nodes (6): UserParameter, comment, expression, name, unit, value

### Community 91 - "UiCommand"
Cohesion: 0.08
Nodes (15): PythonHost, UiCommand, enabled, icon, id, name, panel, run (+7 more)

### Community 93 - "Known differences still to build"
Cohesion: 0.15
Nodes (12): Data and files, Findings from the videos, Fusion study list, Interface, Known differences still to build, Navigation and display, Selection and the canvas, Sketch (+4 more)

### Community 94 - "ChainSegment"
Cohesion: 0.67
Nodes (3): ChainSegment, entity, forward

### Community 96 - "MarkingMenu"
Cohesion: 0.40
Nodes (3): MarkingMenu, enabled, public

### Community 97 - "BodyFrame"
Cohesion: 0.15
Nodes (14): BodyFrame, diag, dx, dy, dz, x0, y0, z0 (+6 more)

### Community 98 - "FakeDoc"
Cohesion: 0.17
Nodes (6): FakeDoc, aborts, commits, items, open, snapshot

### Community 99 - "TEST"
Cohesion: 0.21
Nodes (3): slurp(), TEST(), tmp()

### Community 100 - "Zip.cpp"
Cohesion: 0.19
Nodes (11): Entry, data, name, ZipError, crc32(), get16(), get32(), put16() (+3 more)

### Community 103 - "DocumentError"
Cohesion: 0.08
Nodes (13): DocumentError, doc_(), Document::axisFrame(), Document::Document(), Document::expressionEnv(), Document::ocafBytes(), Document::planeFrame(), Document::reevaluateParameters() (+5 more)

### Community 104 - "ConstructPlane"
Cohesion: 0.38
Nodes (3): ConstructPlane, def_, kind_

### Community 106 - "SectionState"
Cohesion: 0.25
Nodes (7): SectionState, active, angle, flip, offset, plane, visible

### Community 107 - "Display"
Cohesion: 0.25
Nodes (7): Display, constraints, construction, dimensions, points, profiles, projected

### Community 109 - "string"
Cohesion: 0.13
Nodes (20): bodyNumber(), Document::addBody(), Document::bodyShapes(), Document::component(), Document::componentOfBody(), Document::effectOf(), Document::evaluate(), Document::nextAxisName() (+12 more)

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
Cohesion: 0.60
Nodes (3): listCommands(), main(), usage()

### Community 114 - "uninstall.sh"
Cohesion: 0.52
Nodes (6): die(), manifest_for(), refresh(), uninstall.sh script, step(), usage()

### Community 115 - "install.sh"
Cohesion: 0.60
Nodes (5): die(), refresh(), install.sh script, step(), usage()

### Community 118 - "FeatureEffect"
Cohesion: 0.08
Nodes (21): Body, display, name, shape, Component, bodies, name, FeatureEffect (+13 more)

### Community 123 - "smoke"
Cohesion: 0.40
Nodes (5): smoke(), MassProperties, area, centerOfMass, volume

### Community 124 - "Sketch.h"
Cohesion: 0.18
Nodes (7): CommandRegistry::all(), EntityType, Arc, Circle, Line, Spline, isRound()

## Knowledge Gaps
- **653 isolated node(s):** `ok`, `output`, `error`, `isReal`, `real` (+648 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 1230 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **26 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `optional` connect `optional` to `Viewport`, `DocCommands.cpp`, `MainWindow`, `QString`, `Kernel.cpp`, `Io.cpp`, `Unit`, `CommandError`, `SketchEditor.cpp`, `ViewportSketch.cpp`, `SketchOps.cpp`, `CommandDialog.cpp`, `ViewportAnalysis.cpp`, `Session`, `Document.cpp`, `InputDef`, `ViewportAnalysis.cpp`, `.rebuild`, `ViewportArrow.cpp`, `TopoDS_Shape`, `Feature`, `SketchDisplay`, `Kernel.h`, `Document.cpp`, `string`, `ConstructionPoint`, `ConstructionAxis`?**
  _High betweenness centrality (0.108) - this node is a cross-community bridge._
- **What connects `ok`, `output`, `error` to the rest of the system?**
  _653 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Viewport` be split into smaller, more focused modules?**
  _Cohesion score 0.017978190391983496 - nodes in this community are weakly interconnected._
- **Why does `SketchEditor` connect `SketchEditor` to `Viewport`, `QObject`, `Session`, `Display`, `optional`, `.projectAt`, `Kind`, `Pick`, `Snap`, `Unit`, `SketchEditor.cpp`, `.updatePreview`, `.rebuild`, `FeatureEffect`, `Constraint`, `ViewportArrow.cpp`?**
  _High betweenness centrality (0.102) - this node is a cross-community bridge._
- **Should `Icons.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.0629021879021879 - nodes in this community are weakly interconnected._
- **Why does `Viewport` connect `Viewport` to `MainWindow`, `ViewportAnalysis.cpp`, `Viewport.cpp`, `QTimer`, `optional`, `AnalysisSettings`, `SketchDisplay`, `MainWindowTools.cpp`, `rect`, `.redrawAll`, `.toPixels`, `MainWindow.cpp`, `.selectedSubShapes`, `ViewportArrow.cpp`?**
  _High betweenness centrality (0.097) - this node is a cross-community bridge._
- **Should `DocCommands.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.1354679802955665 - nodes in this community are weakly interconnected._