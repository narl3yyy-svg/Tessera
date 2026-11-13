# Graph Report - tessera  (2026-11-13)

## Corpus Check
- 345 files · ~201,771 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 37 file(s) not represented in the graph (top: .drive 29, (none) 5, .cmake 1)

## Summary
- 3190 nodes · 7990 edges · 123 communities (98 shown, 25 thin omitted)
- Extraction: 84% EXTRACTED · 16% INFERRED · 0% AMBIGUOUS · INFERRED: 1251 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `9a884445`
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
- .updatePreview
- Viewport.h
- MainWindow.cpp
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
- sketchFor
- solve
- ViewportAnalysis.cpp
- src/main.cpp
- ConstraintType
- TEST
- Pick
- Snap
- Kind
- .motion
- AnalysisSettings
- Document.cpp
- Session
- MainWindowSketch.cpp
- InputDef
- .toPixels
- ViewportAnalysis.cpp
- .rebuild
- Theme.cpp
- MainWindow::buildSketchTab
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
- FileFormat
- body
- ParametersDialog.cpp
- Document::addUserParameter
- QTimer
- ExpressionSpinBox
- InputType
- Feature
- MarkingMenu.cpp
- Value.h
- SketchDisplay
- Dimension
- Measurement
- rect
- BooleanOp
- Level
- README.md
- Document.cpp
- test_feature_pattern.py
- QObject
- UserParameter
- fail
- Known differences still to build
- .finishArcDrag
- ThreadInfo
- MarkingMenu
- BodyFrame
- FakeDoc
- ChamferType
- Zip.cpp
- Axis
- Document::load
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
- smoke
- ChainSegment
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

## Communities (123 total, 25 thin omitted)

### Community 0 - "Viewport"
Cohesion: 0.02
Nodes (57): view_, QLineEdit, Viewport, analysis_, analysisObjects_, appliedGridStep_, arrowBoxes_, arrowDragging_ (+49 more)

### Community 1 - "Icons.cpp"
Cohesion: 0.07
Nodes (91): arcIcon(), arrow(), axisIcon(), box(), centerRectIcon(), chamferIcon(), circleIcon(), coilIcon() (+83 more)

### Community 2 - "DocCommands.cpp"
Cohesion: 0.19
Nodes (11): axisOf(), InsertGeometry, def_, makeBox(), makeCone(), makeCylinder(), makeSphere(), makeTorus() (+3 more)

### Community 4 - "MainWindow"
Cohesion: 0.03
Nodes (62): CommandDialog, MainWindow, active_, arrowInput_, arrowInput2_, bodiesBeforeCommand_, combEdges_, combPicking_ (+54 more)

### Community 5 - "run_oracle.py"
Cohesion: 0.08
Nodes (54): add_point(), arc_poly(), body_at(), body_list(), build_sketch(), chain(), circumcentre(), cm() (+46 more)

### Community 6 - "Inputs"
Cohesion: 0.04
Nodes (57): Adding a tool, Command, CommandContext, CommandDef, feature, icon, id, inputs (+49 more)

### Community 7 - "Document"
Cohesion: 0.04
Nodes (14): Document, effects_, modified_, pendingTools_, registry_, replaying_, txnBodies_, FromOcaf (+6 more)

### Community 8 - "Viewport.cpp"
Cohesion: 0.05
Nodes (12): keys(), NavPreset, Fusion, SolidWorks, Tinkercad, qc(), QtFrameBuffer, rgb() (+4 more)

### Community 9 - "SketchEditor"
Cohesion: 0.04
Nodes (42): SketchEditor, arcDrag_, arcDragMoved_, arcEndsChain_, arcFrom_, arcRef_, bodyEdges_, boxing_ (+34 more)

### Community 11 - "optional"
Cohesion: 0.10
Nodes (8): optional, CommandRegistry::all(), EntityType, Arc, Circle, Line, Spline, isRound()

### Community 13 - ".projectAt"
Cohesion: 0.14
Nodes (5): PlaneEdges, arcs, segments, vertices, edges

### Community 14 - "Kind"
Cohesion: 0.10
Nodes (19): EdgeFeature, def_, kind_, Kind, Angle, AxisCylinder, AxisEdge, AxisTwoPlanes (+11 more)

### Community 15 - "MainWindowTools.cpp"
Cohesion: 0.06
Nodes (26): QDialog, MainWindow::checkInterference(), MainWindow::chooseUnits(), MainWindow::driveJoints(), MainWindow::exportDesign(), MainWindow::formatLength(), MainWindow::gridSettings(), MainWindow::insertFile() (+18 more)

### Community 16 - "CommandDialog"
Cohesion: 0.05
Nodes (31): CommandDialog, bodiesId_, bodiesLabel_, bodyInput_, buttons_, cmd_, conditional_, edgesId_ (+23 more)

### Community 17 - "Io.cpp"
Cohesion: 0.10
Nodes (17): NamedShape, compoundOf(), exportShapes(), fmt(), formatForPath(), fromBrep(), importShape(), lower() (+9 more)

### Community 18 - "Unit"
Cohesion: 0.06
Nodes (46): MainWindow::lengthUnit(), ExpressionEnv, lengthUnit, lookup, ExpressionError, Quantity, angle, length (+38 more)

### Community 19 - "CommandError"
Cohesion: 0.10
Nodes (21): CommandError, getInt(), getReal(), applyOperation(), Coil, def_, evaluateDimensions(), Extrude (+13 more)

### Community 20 - ".updatePreview"
Cohesion: 0.17
Nodes (3): angleInArc(), segDistance(), Sketch::addLine()

### Community 21 - "Viewport.h"
Cohesion: 0.08
Nodes (6): MarkingMenu::keyPressEvent(), MarkingMenu::mouseMoveEvent(), QKeyEvent, QLabel, QMouseEvent, ViewInteractor

### Community 22 - "MainWindow.cpp"
Cohesion: 0.06
Nodes (10): PythonHost, commandIcon(), flatButton(), MainWindow::MainWindow(), qs(), MainWindow::beginSketch(), MainWindow::enterSketchMode(), MainWindow::exitSketchMode() (+2 more)

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
Nodes (25): QCheckBox, QLabel, QToolButton, QWidget, SketchEditor, SketchPalette, body_, constraints_ (+17 more)

### Community 27 - "Constraint"
Cohesion: 0.10
Nodes (13): Constraint, driven, entities, expression, hasLabel, labelX, labelY, name (+5 more)

### Community 28 - "string"
Cohesion: 0.11
Nodes (10): AddUserParameter, def_, isIdentifier(), Loft, def_, NewComponent, def_, Sweep (+2 more)

### Community 29 - "AdskModule.cpp"
Cohesion: 0.07
Nodes (20): Application, bindAdsk(), BRepBodies, BRepBody, index, Component, Design, Product (+12 more)

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
Cohesion: 0.06
Nodes (42): CommandSession, inputs_, expressionKey(), checkInputValue(), CommandContext::evaluateExpression(), CommandDef::input(), CommandSession::applyInTransaction(), CommandSession::cancel() (+34 more)

### Community 34 - "ParameterCompleter"
Cohesion: 0.12
Nodes (9): MainWindow::attachArrowCompleters(), ParameterCompleter, completer_, edit_, names_, ParameterCompleter::ParameterCompleter(), public, QCompleter (+1 more)

### Community 35 - "ConstructAxisPoint"
Cohesion: 0.26
Nodes (5): ConstructAxisPoint, def_, kind_, JointPick, frame

### Community 37 - "sketchFor"
Cohesion: 0.20
Nodes (7): Hole, def_, Pipe, def_, Revolve, def_, sketchFor()

### Community 38 - "solve"
Cohesion: 0.12
Nodes (14): addConstraintChecked(), Layout, n, px, py, rad, makeLayout(), pack() (+6 more)

### Community 39 - "ViewportAnalysis.cpp"
Cohesion: 0.12
Nodes (5): packed(), ramp(), shade(), Viewport::buildAnalysis(), Viewport::setCurvatureComb()

### Community 41 - "ConstraintType"
Cohesion: 0.08
Nodes (24): ConstraintType, Angle, Coincident, Collinear, Concentric, Diameter, Distance, Equal (+16 more)

### Community 42 - "TEST"
Cohesion: 0.09
Nodes (3): param(), TEST(), tmp()

### Community 43 - "Pick"
Cohesion: 0.12
Nodes (14): Pick, bodyArc, bodyPoint, bodySegment, hit, midpointOf, onEntity, onXAxis (+6 more)

### Community 44 - "Snap"
Cohesion: 0.11
Nodes (18): Snap, alignX, alignY, bodyArc, bodySegment, entity, fromX, fromY (+10 more)

### Community 45 - "Kind"
Cohesion: 0.08
Nodes (24): Hit, index, kind, HudField, edit, editing, kind, locked (+16 more)

### Community 46 - ".motion"
Cohesion: 0.31
Nodes (3): Joint, def_, jointOrigin()

### Community 47 - "AnalysisSettings"
Cohesion: 0.08
Nodes (21): AnalysisKind, CurvatureMap, Draft, None, Zebra, AnalysisSettings, curvatureScale, draftAngle (+13 more)

### Community 48 - "Document.cpp"
Cohesion: 0.13
Nodes (17): ConstructionPlane, name, spec, Document::axes(), Document::bodies(), Document::body(), Document::components(), Document::features() (+9 more)

### Community 49 - "Session"
Cohesion: 0.09
Nodes (10): PythonHost::PythonHost(), main(), smoke(), Session, commands_, doc_, listeners_, nextListener_ (+2 more)

### Community 50 - "MainWindowSketch.cpp"
Cohesion: 0.07
Nodes (14): QAbstractButton, QAction, MainWindow::cancelSketch(), MainWindow::editSketch(), MainWindow::finishSketch(), MainWindow::onProfileClicked(), MainWindow::originalShape(), MainWindow::sketchPalette() (+6 more)

### Community 51 - "InputDef"
Cohesion: 0.08
Nodes (24): InputDef, choices, defaultValue, id, label, max, min, minExclusive (+16 more)

### Community 54 - "ViewportAnalysis.cpp"
Cohesion: 0.10
Nodes (8): ArrowPlacement, base, dir, edgePlacement(), facesPlacement(), MainWindow::patternCentre(), MainWindow::pickedFaces(), MainWindow::updateDragArrow()

### Community 55 - ".rebuild"
Cohesion: 0.15
Nodes (6): ext(), fixedColor(), freeColor(), qc(), rgb(), wire()

### Community 56 - "Theme.cpp"
Cohesion: 0.19
Nodes (6): setIconTheme(), darkColors(), darkPalette(), darkStyleSheet(), lightColors(), lightStyleSheet()

### Community 58 - "Entity"
Cohesion: 0.11
Nodes (17): Entity, a, b, center, construction, fit, projected, radius (+9 more)

### Community 59 - "xdrive.py"
Cohesion: 0.32
Nodes (14): button(), canvas(), click(), drag(), flush(), geometry(), key(), keycode() (+6 more)

### Community 61 - "SketchGeometry.cpp"
Cohesion: 0.09
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
Cohesion: 0.14
Nodes (11): Result, error, ok, output, captured(), PythonHost::exec(), PythonHost::runScript(), Case (+3 more)

### Community 67 - "TopoDS_Shape"
Cohesion: 0.15
Nodes (24): SurfacePoint, normal, point, Vec3, asSolid(), boundingBox(), edgeMidpoint(), edgesNear() (+16 more)

### Community 68 - "Theme"
Cohesion: 0.22
Nodes (4): Theme, colors_, public, styled_

### Community 69 - "FileFormat"
Cohesion: 0.17
Nodes (12): FileFormat, Brep, Iges, Obj, Step, Stl, ThreeMF, FormatInfo (+4 more)

### Community 70 - "body"
Cohesion: 0.15
Nodes (14): getBool(), bodyCentre(), bodyName(), Combine, def_, CopyFn, differenceOrNull(), body (+6 more)

### Community 71 - "ParametersDialog.cpp"
Cohesion: 0.09
Nodes (20): Column, kComment, kExpression, kParameter, kUnit, kValue, number(), ParametersDialog (+12 more)

### Community 72 - "Document::addUserParameter"
Cohesion: 0.40
Nodes (3): Document::addUserParameter(), Document::userParameter(), Document::userParameters()

### Community 74 - "ExpressionSpinBox"
Cohesion: 0.13
Nodes (5): CommandDialog::CommandDialog(), ExpressionSpinBox, eval_, expression_, shown_

### Community 75 - "InputType"
Cohesion: 0.12
Nodes (17): InputType, Axis, Bodies, Body, Bool, Choice, Edges, Faces (+9 more)

### Community 76 - "Feature"
Cohesion: 0.14
Nodes (15): Feature, commandId, error, id, inputs, name, rolledBack, suppressed (+7 more)

### Community 77 - "MarkingMenu.cpp"
Cohesion: 0.08
Nodes (17): UiCommand, enabled, icon, id, name, panel, run, shortcut (+9 more)

### Community 80 - "SketchDisplay"
Cohesion: 0.13
Nodes (10): ProfileObject, index, sketch, SketchDisplay, construction, curves, frame, name (+2 more)

### Community 81 - "Dimension"
Cohesion: 0.50
Nodes (4): Dimension, Angle, Length, Unitless

### Community 82 - "Measurement"
Cohesion: 0.09
Nodes (20): BoundingBox, max, min, Kind, Angle, Area, Length, Volume (+12 more)

### Community 83 - "rect"
Cohesion: 0.28
Nodes (3): SelectionBox, crossing, rect()

### Community 84 - "BooleanOp"
Cohesion: 0.50
Nodes (4): BooleanOp, Cut, Intersect, Join

### Community 85 - "Level"
Cohesion: 0.16
Nodes (13): debug(), error(), info(), Level, Debug, Error, Info, Warning (+5 more)

### Community 86 - "README.md"
Cohesion: 0.10
Nodes (16): Build, Conventions, Development, Tests, Known gaps, Reference parts, Fusion feature checklist, Roadmap (+8 more)

### Community 87 - "Document.cpp"
Cohesion: 0.09
Nodes (26): SketchRecord, data, name, offset, plane, Document::abortTransaction(), Document::commitTransaction(), Document::historyMarker() (+18 more)

### Community 90 - "UserParameter"
Cohesion: 0.33
Nodes (6): UserParameter, comment, expression, name, unit, value

### Community 93 - "Known differences still to build"
Cohesion: 0.15
Nodes (12): Data and files, Findings from the videos, Fusion study list, Interface, Known differences still to build, Navigation and display, Selection and the canvas, Sketch (+4 more)

### Community 95 - "ThreadInfo"
Cohesion: 0.50
Nodes (4): ThreadInfo, diameter, internal, pitch

### Community 96 - "MarkingMenu"
Cohesion: 0.40
Nodes (3): MarkingMenu, enabled, public

### Community 97 - "BodyFrame"
Cohesion: 0.15
Nodes (14): BodyFrame, diag, dx, dy, dz, x0, y0, z0 (+6 more)

### Community 98 - "FakeDoc"
Cohesion: 0.17
Nodes (6): FakeDoc, aborts, commits, items, open, snapshot

### Community 99 - "ChamferType"
Cohesion: 0.67
Nodes (3): ChamferType, DistanceAngle, TwoDistances

### Community 100 - "Zip.cpp"
Cohesion: 0.11
Nodes (14): Entry, data, name, ZipError, crc32(), get16(), get32(), put16() (+6 more)

### Community 102 - "Axis"
Cohesion: 0.50
Nodes (4): Axis, X, Y, Z

### Community 103 - "Document::load"
Cohesion: 0.17
Nodes (5): doc_(), Document::Document(), Document::ocafBytes(), ocafApplication(), Document::load()

### Community 106 - "SectionState"
Cohesion: 0.25
Nodes (7): SectionState, active, angle, flip, offset, plane, visible

### Community 107 - "Display"
Cohesion: 0.25
Nodes (7): Display, constraints, construction, dimensions, points, profiles, projected

### Community 109 - "string"
Cohesion: 0.09
Nodes (25): DocumentError, bodyNumber(), Document::addBody(), Document::axisFrame(), Document::bodyName(), Document::bodyShapes(), Document::component(), Document::componentOfBody() (+17 more)

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
Cohesion: 0.24
Nodes (3): listCommands(), main(), usage()

### Community 114 - "uninstall.sh"
Cohesion: 0.52
Nodes (6): die(), manifest_for(), refresh(), uninstall.sh script, step(), usage()

### Community 115 - "install.sh"
Cohesion: 0.60
Nodes (5): die(), refresh(), install.sh script, step(), usage()

### Community 118 - "FeatureEffect"
Cohesion: 0.08
Nodes (22): Body, display, name, shape, Component, bodies, name, FeatureEffect (+14 more)

### Community 123 - "smoke"
Cohesion: 0.67
Nodes (3): MassProperties, area, centerOfMass

### Community 132 - "ChainSegment"
Cohesion: 0.67
Nodes (3): ChainSegment, entity, forward

## Knowledge Gaps
- **651 isolated node(s):** `ok`, `output`, `error`, `isReal`, `real` (+646 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 1227 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **25 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `optional` connect `optional` to `Viewport`, `DocCommands.cpp`, `MainWindow`, `QString`, `Kernel.cpp`, `Io.cpp`, `Unit`, `Viewport.h`, `ViewportSketch.cpp`, `SketchOps.cpp`, `CommandDialog.cpp`, `sketchFor`, `AnalysisSettings`, `Document.cpp`, `Session`, `InputDef`, `ViewportAnalysis.cpp`, `.rebuild`, `ViewportArrow.cpp`, `TopoDS_Shape`, `Document::addUserParameter`, `ExpressionSpinBox`, `Feature`, `string`, `ConstructionPoint`, `ConstructionAxis`?**
  _High betweenness centrality (0.115) - this node is a cross-community bridge._
- **What connects `ok`, `output`, `error` to the rest of the system?**
  _651 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Viewport` be split into smaller, more focused modules?**
  _Cohesion score 0.017978190391983496 - nodes in this community are weakly interconnected._
- **Why does `Viewport` connect `Viewport` to `ViewportAnalysis.cpp`, `Viewport.cpp`, `QTimer`, `optional`, `AnalysisSettings`, `SketchDisplay`, `MainWindowTools.cpp`, `rect`, `Viewport.h`, `.toPixels`, `.selectedSubShapes`, `ViewportArrow.cpp`?**
  _High betweenness centrality (0.110) - this node is a cross-community bridge._
- **Should `Icons.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.06853038245000971 - nodes in this community are weakly interconnected._
- **Why does `SketchEditor` connect `SketchEditor` to `Viewport`, `Display`, `optional`, `.projectAt`, `Kind`, `Pick`, `Snap`, `Session`, `Unit`, `.updatePreview`, `Viewport.h`, `FeatureEffect`, `.rebuild`, `QObject`, `Entity`, `Constraint`, `.finishArcDrag`?**
  _High betweenness centrality (0.102) - this node is a cross-community bridge._
- **Should `tsr` be split into smaller, more focused modules?**
  _Cohesion score 0.07084785133565621 - nodes in this community are weakly interconnected._