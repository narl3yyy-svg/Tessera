# Graph Report - tessera  (2026-11-13)

## Corpus Check
- 363 files · ~221,081 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 49 file(s) not represented in the graph (top: .drive 41, (none) 5, .cmake 1)

## Summary
- 3383 nodes · 8473 edges · 134 communities (109 shown, 25 thin omitted)
- Extraction: 85% EXTRACTED · 15% INFERRED · 0% AMBIGUOUS · INFERRED: 1254 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `d58754a3`
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
- SketchEditor.cpp
- optional
- Kernel.cpp
- vector
- Kind
- .openMarkingMenu
- CommandDialog
- Io.cpp
- Unit
- MainWindowTools.cpp
- .showDialog
- Document
- MainWindow::MainWindow
- TEST
- Sketch.cpp
- ViewportSketch.cpp
- SketchPalette
- Snap
- CommandError
- AdskModule.cpp
- Colors
- KernelError
- SketchOps.cpp
- Unit
- ParameterCompleter
- Constraint
- Handle
- MainWindow.cpp
- solve
- ViewportAnalysis.cpp
- gp_Ax3
- ConstraintType
- TEST
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
- MetricSize
- Document::reevaluateParameters
- src/main.cpp
- src/main.cpp
- FileFormat
- InputType
- string
- ExpressionSpinBox
- math
- QTimer
- SketchDisplay
- DocCommands.cpp
- Measurement
- NavPreset
- Axis
- Level
- README.md
- DocumentError
- test_feature_pattern.py
- QObject
- .add
- UiCommand
- ConstructionPlane
- Known differences still to build
- Value.h
- FeatureEffect
- UserParameter
- WallSide
- FakeDoc
- smoke
- string
- sstream
- rect
- Architecture
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
- Feature
- Push
- Column
- Mesh
- BooleanOp
- Placement
- ChainSegment
- ThreadInfo
- ChamferType
- Joints
- LAB_NOTES.md
- build.sh
- live-test.sh

## God Nodes (most connected - your core abstractions)
1. `Viewport` - 251 edges
2. `SketchEditor` - 177 edges
3. `MainWindow` - 175 edges
4. `Inputs` - 137 edges
5. `render()` - 102 edges
6. `CommandContext` - 102 edges
7. `Document` - 100 edges
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

## Communities (134 total, 25 thin omitted)

### Community 0 - "Viewport"
Cohesion: 0.02
Nodes (67): view_, QLineEdit, Viewport, analysis_, analysisObjects_, appliedGridStep_, arrowBoxes_, arrowDragging_ (+59 more)

### Community 1 - "Icons.cpp"
Cohesion: 0.06
Nodes (109): arc3Icon(), arcIcon(), arrow(), axisIcon(), box(), breakIcon(), centerRectIcon(), chamferIcon() (+101 more)

### Community 2 - "Session.cpp"
Cohesion: 0.06
Nodes (42): CommandSession, inputs_, expressionKey(), checkInputValue(), CommandContext::evaluateExpression(), CommandDef::input(), CommandSession::applyInTransaction(), CommandSession::cancel() (+34 more)

### Community 4 - "MainWindow"
Cohesion: 0.03
Nodes (64): writeLiveGeometry(), CommandDialog, MainWindow, active_, arrowInput_, arrowInput2_, bodiesBeforeCommand_, combEdges_ (+56 more)

### Community 5 - "run_oracle.py"
Cohesion: 0.08
Nodes (54): add_point(), arc_poly(), body_at(), body_list(), build_sketch(), chain(), circumcentre(), cm() (+46 more)

### Community 6 - "Inputs"
Cohesion: 0.07
Nodes (19): CommandContext, Inputs, CommandSession::CommandSession(), getInt(), AddUserParameter, def_, checkBody(), checkPattern() (+11 more)

### Community 7 - "Document"
Cohesion: 0.03
Nodes (11): Document, effects_, modified_, pendingTools_, registry_, replaying_, txnBodies_, FromOcaf (+3 more)

### Community 8 - "Viewport.cpp"
Cohesion: 0.05
Nodes (8): hiddenColour(), keys(), qc(), QKeyEvent, rgb(), sharpEdges(), Viewport::Viewport(), wireColour()

### Community 9 - "SketchEditor"
Cohesion: 0.03
Nodes (45): SketchEditor, arcDrag_, arcDragMoved_, arcEndsChain_, arcFrom_, arcRef_, bodyEdges_, boxing_ (+37 more)

### Community 10 - "SketchEditor.cpp"
Cohesion: 0.14
Nodes (4): angleInArc(), ccwContains(), circumcircle(), segDistance()

### Community 13 - "vector"
Cohesion: 0.13
Nodes (13): Loft, def_, NewComponent, def_, openChains(), parsePoints(), pickedFaces(), profilesOf() (+5 more)

### Community 14 - "Kind"
Cohesion: 0.09
Nodes (22): ConstructPlane, def_, kind_, EdgeFeature, def_, kind_, Kind, Angle (+14 more)

### Community 15 - ".openMarkingMenu"
Cohesion: 0.10
Nodes (4): MainWindow::beginSketch(), MainWindow::buildSketchTab(), MainWindow::enterSketchMode(), MainWindow::buildUiCommands()

### Community 16 - "CommandDialog"
Cohesion: 0.05
Nodes (34): CommandDialog, bodiesId_, bodiesLabel_, bodyInput_, buttons_, cmd_, CommandDialog::CommandDialog(), conditional_ (+26 more)

### Community 17 - "Io.cpp"
Cohesion: 0.11
Nodes (15): MainWindow::print3d(), NamedShape, compoundOf(), exportShapes(), fmt(), formatForPath(), fromBrep(), importShape() (+7 more)

### Community 18 - "Unit"
Cohesion: 0.09
Nodes (30): ExpressionEnv, lengthUnit, lookup, ExpressionError, Quantity, angle, length, value (+22 more)

### Community 19 - "MainWindowTools.cpp"
Cohesion: 0.06
Nodes (24): QDialog, MainWindow::checkInterference(), MainWindow::chooseUnits(), MainWindow::driveJoints(), MainWindow::exportDesign(), MainWindow::formatLength(), MainWindow::gridSettings(), MainWindow::insertFile() (+16 more)

### Community 21 - "Document"
Cohesion: 0.19
Nodes (7): ConstructAxisPoint, def_, kind_, differenceOrNull(), JointPick, frame, revolveAxis()

### Community 22 - "MainWindow::MainWindow"
Cohesion: 0.13
Nodes (4): PythonHost, MainWindow::MainWindow(), MainWindow::exitSketchMode(), MainWindow::showPreferences()

### Community 23 - "TEST"
Cohesion: 0.07
Nodes (9): Point, x, y, Sketch, constraints, entities, points, texts (+1 more)

### Community 24 - "Sketch.cpp"
Cohesion: 0.09
Nodes (16): SketchError, entityTypeName(), isDimension(), Sketch::addCircle(), Sketch::addConstraint(), Sketch::addSpline(), Sketch::addText(), Sketch::checkIndices() (+8 more)

### Community 25 - "ViewportSketch.cpp"
Cohesion: 0.08
Nodes (6): faceStyle(), lineStyle(), rgb(), Viewport::lookAt(), Viewport::planePoint(), Viewport::toWidget()

### Community 26 - "SketchPalette"
Cohesion: 0.06
Nodes (26): flatButton(), QCheckBox, QLabel, QToolButton, QWidget, SketchEditor, SketchPalette, body_ (+18 more)

### Community 27 - "Snap"
Cohesion: 0.11
Nodes (18): Snap, alignX, alignY, bodyArc, bodySegment, entity, fromX, fromY (+10 more)

### Community 28 - "CommandError"
Cohesion: 0.09
Nodes (29): CommandError, getBool(), getReal(), applyOperation(), bodyCentre(), bodyName(), Coil, def_ (+21 more)

### Community 29 - "AdskModule.cpp"
Cohesion: 0.10
Nodes (16): Application, bindAdsk(), BRepBodies, BRepBody, index, Component, Design, Product (+8 more)

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
Cohesion: 0.10
Nodes (21): MainWindow::lengthUnit(), Dimension, Angle, Length, Unitless, Unit, Centimeter, Degree (+13 more)

### Community 34 - "ParameterCompleter"
Cohesion: 0.12
Nodes (8): ParameterCompleter, completer_, edit_, names_, ParameterCompleter::ParameterCompleter(), public, QCompleter, QLineEdit

### Community 35 - "Constraint"
Cohesion: 0.14
Nodes (12): Constraint, driven, entities, expression, hasLabel, labelX, labelY, name (+4 more)

### Community 37 - "MainWindow.cpp"
Cohesion: 0.13
Nodes (3): commandIcon(), qs(), MainWindow::applySection()

### Community 38 - "solve"
Cohesion: 0.18
Nodes (12): addConstraintChecked(), Layout, n, px, py, rad, makeLayout(), pack() (+4 more)

### Community 39 - "ViewportAnalysis.cpp"
Cohesion: 0.12
Nodes (5): packed(), ramp(), shade(), Viewport::buildAnalysis(), Viewport::setCurvatureComb()

### Community 40 - "gp_Ax3"
Cohesion: 0.31
Nodes (9): curve(), curves(), entityCurves(), interiorPoint(), profileAt(), profiles(), textShape(), toSketch() (+1 more)

### Community 41 - "ConstraintType"
Cohesion: 0.08
Nodes (24): ConstraintType, Angle, Coincident, Collinear, Concentric, Diameter, Distance, Equal (+16 more)

### Community 42 - "TEST"
Cohesion: 0.09
Nodes (3): param(), TEST(), tmp()

### Community 43 - "Pick"
Cohesion: 0.10
Nodes (17): Hit, index, kind, Pick, bodyArc, bodyPoint, bodySegment, hit (+9 more)

### Community 44 - ".mouseMove"
Cohesion: 0.11
Nodes (12): ext(), fixedColor(), freeColor(), qc(), rgb(), wire(), Text, angle (+4 more)

### Community 45 - "Kind"
Cohesion: 0.09
Nodes (21): HudField, edit, editing, kind, locked, value, Kind, Angle (+13 more)

### Community 46 - "Zip.cpp"
Cohesion: 0.21
Nodes (11): Entry, data, name, ZipError, crc32(), get16(), get32(), put16() (+3 more)

### Community 47 - "AnalysisSettings"
Cohesion: 0.06
Nodes (29): AnalysisKind, CurvatureMap, Draft, None, Zebra, AnalysisSettings, curvatureScale, draftAngle (+21 more)

### Community 48 - "Document.cpp"
Cohesion: 0.12
Nodes (23): Document::axes(), Document::bodies(), Document::body(), Document::bodyName(), Document::components(), Document::features(), Document::historyMarker(), Document::lengthUnit() (+15 more)

### Community 49 - "SketchRecord"
Cohesion: 0.13
Nodes (14): ModelParameter, angle, expression, name, owner, value, SketchRecord, data (+6 more)

### Community 50 - "MainWindowSketch.cpp"
Cohesion: 0.07
Nodes (14): MainWindow::cancelSketch(), MainWindow::editSketch(), MainWindow::finishSketch(), MainWindow::onProfileClicked(), MainWindow::originalShape(), MainWindow::sketchPalette(), MainWindow::sketchVisible(), MainWindow::startSketch() (+6 more)

### Community 51 - "InputDef"
Cohesion: 0.08
Nodes (24): InputDef, choices, defaultValue, id, label, max, min, minExclusive (+16 more)

### Community 52 - "DocCommands.h"
Cohesion: 0.23
Nodes (5): bindTsr(), fromPy(), toPy(), typeName(), Document

### Community 54 - "MainWindowArrow.cpp"
Cohesion: 0.12
Nodes (8): ArrowPlacement, base, dir, edgePlacement(), facesPlacement(), MainWindow::attachArrowCompleters(), MainWindow::patternCentre(), MainWindow::pickedFaces()

### Community 55 - "Viewport.h"
Cohesion: 0.11
Nodes (6): QLabel, Profile, area, face, x, y

### Community 56 - "Theme.cpp"
Cohesion: 0.19
Nodes (6): setIconTheme(), darkColors(), darkPalette(), darkStyleSheet(), lightColors(), lightStyleSheet()

### Community 57 - "TEST"
Cohesion: 0.19
Nodes (3): slurp(), TEST(), tmp()

### Community 58 - "Entity"
Cohesion: 0.08
Nodes (24): Entity, a, b, center, construction, fit, projected, radius (+16 more)

### Community 59 - "xdrive.py"
Cohesion: 0.32
Nodes (14): button(), canvas(), click(), drag(), flush(), geometry(), key(), keycode() (+6 more)

### Community 62 - "Session"
Cohesion: 0.08
Nodes (7): PythonHost::PythonHost(), Session, commands_, doc_, listeners_, nextListener_, path_

### Community 63 - "ViewportArrow.cpp"
Cohesion: 0.05
Nodes (24): MarkingMenu::mouseMoveEvent(), QMouseEvent, ViewInteractor, Viewport::frontEdgeOwner(), rgb(), segmentDistance(), Viewport::arrowAt(), Viewport::arrowMouseMove() (+16 more)

### Community 64 - "BodyFrame"
Cohesion: 0.15
Nodes (14): BodyFrame, diag, dx, dy, dz, x0, y0, z0 (+6 more)

### Community 65 - "CommandRegistry"
Cohesion: 0.12
Nodes (4): CommandRegistry, cmds_, CommandRegistry::add(), TEST()

### Community 66 - "cmath"
Cohesion: 0.17
Nodes (8): Result, error, ok, output, captured(), PythonHost::exec(), PythonHost::runScript(), fn

### Community 67 - "TopoDS_Shape"
Cohesion: 0.19
Nodes (17): SurfacePoint, normal, point, Vec3, edgeMidpoint(), edgesNear(), frame(), makeBox() (+9 more)

### Community 68 - "Theme"
Cohesion: 0.22
Nodes (4): Theme, colors_, public, styled_

### Community 69 - "MetricSize"
Cohesion: 0.15
Nodes (10): MarkingMenu::keyPressEvent(), MarkingMenu::MarkingMenu(), MarkingMenu::run(), MetricSize, close, d, loose, name (+2 more)

### Community 70 - "Document::reevaluateParameters"
Cohesion: 0.28
Nodes (4): Document::expressionEnv(), Document::reevaluateParameters(), Document::userParameter(), Document::save()

### Community 71 - "src/main.cpp"
Cohesion: 0.09
Nodes (14): number(), ParametersDialog, building_, error_, listener_, ParametersDialog::ParametersDialog(), public, rebuildPending_ (+6 more)

### Community 72 - "src/main.cpp"
Cohesion: 0.09
Nodes (4): grabWindowWithPanels(), MarkingMenu, enabled, public

### Community 73 - "FileFormat"
Cohesion: 0.17
Nodes (12): FileFormat, Brep, Iges, Obj, Step, Stl, ThreeMF, FormatInfo (+4 more)

### Community 75 - "InputType"
Cohesion: 0.12
Nodes (17): InputType, Axis, Bodies, Body, Bool, Choice, Edges, Faces (+9 more)

### Community 76 - "string"
Cohesion: 0.13
Nodes (16): bodyNumber(), Document::axisFrame(), Document::component(), Document::componentOfBody(), Document::nextAxisName(), Document::nextBodyName(), Document::nextComponentName(), Document::nextDimensionName() (+8 more)

### Community 77 - "ExpressionSpinBox"
Cohesion: 0.16
Nodes (4): ExpressionSpinBox, eval_, expression_, shown_

### Community 80 - "SketchDisplay"
Cohesion: 0.12
Nodes (11): ProfileObject, index, sketch, SketchDisplay, construction, curves, fixedCurves, frame (+3 more)

### Community 81 - "DocCommands.cpp"
Cohesion: 0.04
Nodes (61): Adding a tool, Command, CommandDef, feature, icon, id, inputs, name (+53 more)

### Community 82 - "Measurement"
Cohesion: 0.09
Nodes (20): BoundingBox, max, min, Kind, Angle, Area, Length, Volume (+12 more)

### Community 83 - "NavPreset"
Cohesion: 0.33
Nodes (4): NavPreset, Fusion, SolidWorks, Tinkercad

### Community 84 - "Axis"
Cohesion: 0.50
Nodes (4): Axis, X, Y, Z

### Community 85 - "Level"
Cohesion: 0.16
Nodes (13): debug(), error(), info(), Level, Debug, Error, Info, Warning (+5 more)

### Community 86 - "README.md"
Cohesion: 0.09
Nodes (17): Build, Conventions, Development, Tests, Known gaps, Visual styles, Reference parts, Fusion feature checklist (+9 more)

### Community 87 - "DocumentError"
Cohesion: 0.10
Nodes (26): DocumentError, checkViewName(), Document::abortTransaction(), Document::addBody(), Document::addNamedView(), Document::addUserParameter(), Document::commitTransaction(), Document::openTransaction() (+18 more)

### Community 89 - "QObject"
Cohesion: 0.11
Nodes (6): QObject, SketchEditor::SketchEditor(), Tool, op, shape, target

### Community 91 - "UiCommand"
Cohesion: 0.13
Nodes (12): UiCommand, enabled, icon, id, name, panel, run, shortcut (+4 more)

### Community 92 - "ConstructionPlane"
Cohesion: 0.33
Nodes (5): ConstructionPlane, name, spec, Document::plane(), Document::setPlane()

### Community 93 - "Known differences still to build"
Cohesion: 0.15
Nodes (12): Data and files, Findings from the videos, Fusion study list, Interface, Known differences still to build, Navigation and display, Selection and the canvas, Sketch (+4 more)

### Community 95 - "FeatureEffect"
Cohesion: 0.07
Nodes (22): Body, display, name, shape, Component, bodies, name, FeatureEffect (+14 more)

### Community 96 - "UserParameter"
Cohesion: 0.33
Nodes (6): UserParameter, comment, expression, name, unit, value

### Community 97 - "WallSide"
Cohesion: 0.50
Nodes (4): WallSide, Center, Side1, Side2

### Community 98 - "FakeDoc"
Cohesion: 0.17
Nodes (6): FakeDoc, aborts, commits, items, open, snapshot

### Community 99 - "smoke"
Cohesion: 0.40
Nodes (5): smoke(), MassProperties, area, centerOfMass, volume

### Community 101 - "string"
Cohesion: 0.10
Nodes (30): completeEdgeReferences(), completeFaceReferences(), decode(), decodeFaces(), dot(), edgeReference(), EdgeSig, full (+22 more)

### Community 102 - "sstream"
Cohesion: 0.15
Nodes (5): doc_(), Document::Document(), Document::ocafBytes(), ocafApplication(), Document::load()

### Community 103 - "rect"
Cohesion: 0.18
Nodes (7): SelectionBox, crossing, Session::notifyChanged(), Rect, rect(), l, p

### Community 104 - "Architecture"
Cohesion: 0.40
Nodes (4): Architecture, How a command works, The document, Units

### Community 106 - "SectionState"
Cohesion: 0.25
Nodes (7): SectionState, active, angle, flip, offset, plane, visible

### Community 107 - "Display"
Cohesion: 0.25
Nodes (7): Display, constraints, construction, dimensions, points, profiles, projected

### Community 108 - "TestFramework.h"
Cohesion: 0.14
Nodes (5): Case, name, fail(), Failure, Register

### Community 109 - "PlaneEdges"
Cohesion: 0.11
Nodes (6): PlaneEdges, arcs, curves, segments, vertices, edges

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
Cohesion: 0.36
Nodes (4): listCommands(), main(), usage(), main()

### Community 118 - "Feature"
Cohesion: 0.22
Nodes (9): Feature, commandId, error, id, inputs, name, rolledBack, suppressed (+1 more)

### Community 120 - "Column"
Cohesion: 0.33
Nodes (6): Column, kComment, kExpression, kParameter, kUnit, kValue

### Community 121 - "Mesh"
Cohesion: 0.40
Nodes (3): Mesh, nodes, triangles

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

## Knowledge Gaps
- **697 isolated node(s):** `ok`, `output`, `error`, `isReal`, `real` (+692 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 1323 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **25 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `optional` connect `optional` to `Viewport`, `MainWindow`, `Inputs`, `SketchEditor.cpp`, `Kernel.cpp`, `CommandDialog`, `Io.cpp`, `Unit`, `ViewportSketch.cpp`, `Unit`, `Constraint`, `AnalysisSettings`, `Document.cpp`, `SketchRecord`, `InputDef`, `MainWindowArrow.cpp`, `Viewport.h`, `Session`, `ViewportArrow.cpp`, `TopoDS_Shape`, `Document::reevaluateParameters`, `.solveAndShow`, `string`, `ExpressionSpinBox`, `DocCommands.cpp`, `ConstructionPlane`, `ConstructionPoint`, `ConstructionAxis`, `Feature`, `Joints`?**
  _High betweenness centrality (0.114) - this node is a cross-community bridge._
- **What connects `ok`, `output`, `error` to the rest of the system?**
  _697 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Viewport` be split into smaller, more focused modules?**
  _Cohesion score 0.01650793650793651 - nodes in this community are weakly interconnected._
- **Why does `Viewport` connect `Viewport` to `Handle`, `ViewportAnalysis.cpp`, `Viewport.cpp`, `src/main.cpp`, `rect`, `optional`, `AnalysisSettings`, `SketchDisplay`, `QTimer`, `NavPreset`, `DocCommands.h`, `.toPixels`, `MainWindowTools.cpp`, `Viewport.h`, `ViewportArrow.cpp`?**
  _High betweenness centrality (0.110) - this node is a cross-community bridge._
- **Should `Icons.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.05839317165695705 - nodes in this community are weakly interconnected._
- **Why does `SketchEditor` connect `SketchEditor` to `Viewport`, `Unit`, `Constraint`, `.solveAndShow`, `Display`, `optional`, `PlaneEdges`, `Kind`, `Pick`, `.mouseMove`, `SketchEditor.cpp`, `Viewport.h`, `QObject`, `Entity`, `Snap`, `Session`, `ViewportArrow.cpp`?**
  _High betweenness centrality (0.091) - this node is a cross-community bridge._
- **Should `Session.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.06105834464043419 - nodes in this community are weakly interconnected._