# Graph Report - tessera  (2026-11-13)

## Corpus Check
- 361 files · ~217,410 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 46 file(s) not represented in the graph (top: .drive 38, (none) 5, .cmake 1)

## Summary
- 3319 nodes · 8295 edges · 136 communities (107 shown, 29 thin omitted)
- Extraction: 85% EXTRACTED · 15% INFERRED · 0% AMBIGUOUS · INFERRED: 1226 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `40a03393`
- Run `git rev-parse HEAD` and compare to check if the graph is stale.
- Run `graphify update .` after code changes (no API cost).

## Community Hubs (Navigation)
- Viewport
- Icons.cpp
- Expression.cpp
- MainWindow
- run_oracle.py
- Inputs
- Document
- Viewport.cpp
- SketchEditor
- .askValue
- optional
- Kernel.cpp
- vector
- Kind
- src/main.cpp
- CommandDialog
- Io.cpp
- Parser
- Unit
- SketchEditor.cpp
- Document
- CommandDialog.cpp
- TEST
- Sketch.cpp
- ViewportSketch.cpp
- SketchPalette
- Viewport.h
- CommandError
- AdskModule.cpp
- Colors
- KernelError
- SketchOps.cpp
- Session.cpp
- ParameterCompleter
- Constraint
- MainWindow::MainWindow
- solve
- .openMarkingMenu
- Constraint
- ConstraintType
- TEST
- Pick
- Snap
- Kind
- TEST
- AnalysisSettings
- Document.cpp
- .add
- MainWindowSketch.cpp
- InputDef
- .toPixels
- MainWindowArrow.cpp
- QMouseEvent
- Theme.cpp
- MainWindow.cpp
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
- ViewportAnalysis.cpp
- gp_Ax3
- src/main.cpp
- MainWindowTools.cpp
- FileFormat
- cmath
- InputType
- string
- CommandDialog::CommandDialog
- math
- Handle
- SketchDisplay
- DocCommands.cpp
- Measurement
- NavPreset
- Axis
- Level
- README.md
- DocumentError
- test_feature_pattern.py
- SketchEditor::SketchEditor
- exportShapes
- MarkingMenu.cpp
- Document::evaluate
- Known differences still to build
- Value.h
- FeatureEffect
- bindAdsk
- WallSide
- FakeDoc
- smoke
- Icons.h
- string
- sstream
- UserParameter
- Architecture
- BooleanOp
- SectionState
- Display
- fail
- PlaneEdges
- openWallBand
- ConstructionPoint
- Mesh
- ConstructionAxis
- uninstall.sh
- install.sh
- PYBIND11_EMBEDDED_MODULE
- main
- Feature
- Push
- Dimension
- ChamferType
- ThreadInfo
- Placement
- ChainSegment
- Viewport::Viewport
- Joints
- LAB_NOTES.md
- build.sh
- live-test.sh

## God Nodes (most connected - your core abstractions)
1. `Viewport` - 229 edges
2. `SketchEditor` - 177 edges
3. `MainWindow` - 172 edges
4. `Inputs` - 137 edges
5. `render()` - 102 edges
6. `CommandContext` - 102 edges
7. `Document` - 96 edges
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

## Communities (136 total, 29 thin omitted)

### Community 0 - "Viewport"
Cohesion: 0.02
Nodes (57): view_, QLineEdit, Viewport, analysis_, analysisObjects_, appliedGridStep_, arrowBoxes_, arrowDragging_ (+49 more)

### Community 1 - "Icons.cpp"
Cohesion: 0.06
Nodes (107): arc3Icon(), arcIcon(), arrow(), axisIcon(), box(), breakIcon(), centerRectIcon(), chamferIcon() (+99 more)

### Community 2 - "Expression.cpp"
Cohesion: 0.13
Nodes (15): ExpressionEnv, lengthUnit, lookup, ExpressionError, evaluateExpression(), evaluateQuantity(), expressionReferences(), isConstantName() (+7 more)

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
Nodes (12): Document, effects_, modified_, pendingTools_, registry_, replaying_, txnBodies_, FromOcaf (+4 more)

### Community 9 - "SketchEditor"
Cohesion: 0.03
Nodes (45): SketchEditor, arcDrag_, arcDragMoved_, arcEndsChain_, arcFrom_, arcRef_, bodyEdges_, boxing_ (+37 more)

### Community 10 - ".askValue"
Cohesion: 0.12
Nodes (5): Text, angle, font, point, text

### Community 12 - "Kernel.cpp"
Cohesion: 0.04
Nodes (5): dot(), faceScore(), isoCoarsePitch(), score(), vec()

### Community 13 - "vector"
Cohesion: 0.13
Nodes (13): Loft, def_, NewComponent, def_, openChains(), parsePoints(), pickedFaces(), profilesOf() (+5 more)

### Community 14 - "Kind"
Cohesion: 0.09
Nodes (22): ConstructPlane, def_, kind_, EdgeFeature, def_, kind_, Kind, Angle (+14 more)

### Community 15 - "src/main.cpp"
Cohesion: 0.08
Nodes (4): grabWindowWithPanels(), MarkingMenu, enabled, public

### Community 16 - "CommandDialog"
Cohesion: 0.05
Nodes (31): CommandDialog, bodiesId_, bodiesLabel_, bodyInput_, buttons_, cmd_, conditional_, edgesId_ (+23 more)

### Community 17 - "Io.cpp"
Cohesion: 0.12
Nodes (8): formatForPath(), fromBrep(), importShape(), lower(), meshOf(), scaled(), toBrep(), xmlEscape()

### Community 18 - "Parser"
Cohesion: 0.18
Nodes (15): Quantity, angle, length, value, describe(), isIdentChar(), isIdentStart(), Parser (+7 more)

### Community 19 - "Unit"
Cohesion: 0.10
Nodes (28): MainWindow::checkInterference(), MainWindow::driveJoints(), MainWindow::formatLength(), MainWindow::gridSettings(), MainWindow::lengthUnit(), MainWindow::openAnalysis(), MainWindow::openSection(), MainWindow::showCenterOfMass() (+20 more)

### Community 20 - "SketchEditor.cpp"
Cohesion: 0.12
Nodes (4): angleInArc(), ccwContains(), circumcircle(), segDistance()

### Community 21 - "Document"
Cohesion: 0.19
Nodes (7): ConstructAxisPoint, def_, kind_, differenceOrNull(), JointPick, frame, revolveAxis()

### Community 23 - "TEST"
Cohesion: 0.07
Nodes (9): Sketch, constraints, entities, points, texts, Sketch::addCircle(), Sketch::addLine(), rect() (+1 more)

### Community 24 - "Sketch.cpp"
Cohesion: 0.09
Nodes (18): Point, x, y, SketchError, entityTypeName(), isDimension(), Sketch::addConstraint(), Sketch::addSpline() (+10 more)

### Community 25 - "ViewportSketch.cpp"
Cohesion: 0.06
Nodes (17): faceStyle(), lineStyle(), rgb(), Viewport::lookAt(), Viewport::planePoint(), Viewport::toWidget(), Entry, data (+9 more)

### Community 26 - "SketchPalette"
Cohesion: 0.06
Nodes (26): flatButton(), QCheckBox, QLabel, QToolButton, QWidget, SketchEditor, SketchPalette, body_ (+18 more)

### Community 27 - "Viewport.h"
Cohesion: 0.10
Nodes (6): QLabel, Profile, area, face, x, y

### Community 28 - "CommandError"
Cohesion: 0.09
Nodes (29): CommandError, getBool(), getReal(), applyOperation(), bodyCentre(), bodyName(), Coil, def_ (+21 more)

### Community 29 - "AdskModule.cpp"
Cohesion: 0.08
Nodes (18): Application, BRepBodies, Component, Design, Product, raiseIfError(), UserParameter, name (+10 more)

### Community 30 - "Colors"
Cohesion: 0.07
Nodes (28): Colors, base, border, cubeBox, cubeText, errorBackground, grid, gridMajor (+20 more)

### Community 31 - "KernelError"
Cohesion: 0.21
Nodes (31): KernelError, vertices, asSolid(), boolean(), boundingBox(), chamfer(), chamferEx(), draft() (+23 more)

### Community 32 - "SketchOps.cpp"
Cohesion: 0.22
Nodes (25): at(), chainOf(), chamferCorner(), circularPattern(), copyEntities(), cross(), dot(), extendLine() (+17 more)

### Community 33 - "Session.cpp"
Cohesion: 0.06
Nodes (42): CommandSession, inputs_, expressionKey(), checkInputValue(), CommandContext::evaluateExpression(), CommandDef::input(), CommandSession::applyInTransaction(), CommandSession::cancel() (+34 more)

### Community 34 - "ParameterCompleter"
Cohesion: 0.13
Nodes (9): QObject, ParameterCompleter, completer_, edit_, names_, ParameterCompleter::ParameterCompleter(), public, QCompleter (+1 more)

### Community 35 - "Constraint"
Cohesion: 0.12
Nodes (12): Constraint, driven, entities, expression, hasLabel, labelX, labelY, name (+4 more)

### Community 37 - "MainWindow::MainWindow"
Cohesion: 0.11
Nodes (6): MainWindow::MainWindow(), MainWindow::buildSketchTab(), MainWindow::enterSketchMode(), MainWindow::exitSketchMode(), QTimer, Viewport::selectArrowValue()

### Community 38 - "solve"
Cohesion: 0.18
Nodes (12): addConstraintChecked(), Layout, n, px, py, rad, makeLayout(), pack() (+4 more)

### Community 40 - "Constraint"
Cohesion: 0.13
Nodes (6): ext(), fixedColor(), freeColor(), qc(), rgb(), wire()

### Community 41 - "ConstraintType"
Cohesion: 0.08
Nodes (25): ConstraintType, Angle, Coincident, Collinear, Concentric, Diameter, Distance, Equal (+17 more)

### Community 42 - "TEST"
Cohesion: 0.09
Nodes (3): param(), TEST(), tmp()

### Community 43 - "Pick"
Cohesion: 0.10
Nodes (17): Hit, index, kind, Pick, bodyArc, bodyPoint, bodySegment, hit (+9 more)

### Community 44 - "Snap"
Cohesion: 0.11
Nodes (18): Snap, alignX, alignY, bodyArc, bodySegment, entity, fromX, fromY (+10 more)

### Community 45 - "Kind"
Cohesion: 0.09
Nodes (21): HudField, edit, editing, kind, locked, value, Kind, Angle (+13 more)

### Community 46 - "TEST"
Cohesion: 0.24
Nodes (3): slurp(), TEST(), tmp()

### Community 47 - "AnalysisSettings"
Cohesion: 0.09
Nodes (20): AnalysisKind, CurvatureMap, Draft, None, Zebra, AnalysisSettings, curvatureScale, draftAngle (+12 more)

### Community 48 - "Document.cpp"
Cohesion: 0.08
Nodes (31): ConstructionPlane, name, spec, Document::axes(), Document::bodies(), Document::body(), Document::bodyName(), Document::components() (+23 more)

### Community 50 - "MainWindowSketch.cpp"
Cohesion: 0.09
Nodes (13): MainWindow::cancelSketch(), MainWindow::editSketch(), MainWindow::finishSketch(), MainWindow::onEdgeClicked(), MainWindow::onProfileClicked(), MainWindow::originalShape(), MainWindow::sketchPalette(), MainWindow::sketchVisible() (+5 more)

### Community 51 - "InputDef"
Cohesion: 0.08
Nodes (24): InputDef, choices, defaultValue, id, label, max, min, minExclusive (+16 more)

### Community 54 - "MainWindowArrow.cpp"
Cohesion: 0.12
Nodes (8): ArrowPlacement, base, dir, edgePlacement(), facesPlacement(), MainWindow::attachArrowCompleters(), MainWindow::patternCentre(), MainWindow::pickedFaces()

### Community 55 - "QMouseEvent"
Cohesion: 0.14
Nodes (8): MarkingMenu::mouseMoveEvent(), QMouseEvent, ViewInteractor, Viewport::arrowMouseMove(), Viewport::arrowMousePress(), Viewport::arrowMouseRelease(), Viewport::dragArrowForTest(), Viewport::rebuildArrows()

### Community 56 - "Theme.cpp"
Cohesion: 0.19
Nodes (6): setIconTheme(), darkColors(), darkPalette(), darkStyleSheet(), lightColors(), lightStyleSheet()

### Community 58 - "Entity"
Cohesion: 0.11
Nodes (17): Entity, a, b, center, construction, fit, projected, radius (+9 more)

### Community 59 - "xdrive.py"
Cohesion: 0.32
Nodes (14): button(), canvas(), click(), drag(), flush(), geometry(), key(), keycode() (+6 more)

### Community 62 - "Session"
Cohesion: 0.09
Nodes (7): PythonHost::PythonHost(), Session, commands_, doc_, listeners_, nextListener_, path_

### Community 63 - "ViewportArrow.cpp"
Cohesion: 0.06
Nodes (17): Viewport::frontEdgeOwner(), Viewport::setCurvatureComb(), rgb(), segmentDistance(), Viewport::arrowAt(), Viewport::arrowParam(), Viewport::clearDragArrow(), Viewport::clearSecondArrow() (+9 more)

### Community 64 - "BodyFrame"
Cohesion: 0.09
Nodes (24): BoundingBox, max, min, BodyFrame, diag, dx, dy, dz (+16 more)

### Community 65 - "CommandRegistry"
Cohesion: 0.12
Nodes (4): CommandRegistry, cmds_, CommandRegistry::add(), TEST()

### Community 66 - "cmath"
Cohesion: 0.12
Nodes (12): PythonHost, Result, error, ok, output, captured(), PythonHost::exec(), PythonHost::runScript() (+4 more)

### Community 67 - "TopoDS_Shape"
Cohesion: 0.19
Nodes (17): SurfacePoint, normal, point, Vec3, edgeMidpoint(), edgesNear(), frame(), makeBox() (+9 more)

### Community 68 - "Theme"
Cohesion: 0.22
Nodes (4): Theme, colors_, public, styled_

### Community 69 - "ViewportAnalysis.cpp"
Cohesion: 0.15
Nodes (4): packed(), ramp(), shade(), Viewport::buildAnalysis()

### Community 70 - "gp_Ax3"
Cohesion: 0.31
Nodes (9): curve(), curves(), entityCurves(), interiorPoint(), profileAt(), profiles(), textShape(), toSketch() (+1 more)

### Community 71 - "src/main.cpp"
Cohesion: 0.08
Nodes (20): Column, kComment, kExpression, kParameter, kUnit, kValue, number(), ParametersDialog (+12 more)

### Community 72 - "MainWindowTools.cpp"
Cohesion: 0.06
Nodes (14): QDialog, MainWindow::applySection(), MainWindow::chooseUnits(), MainWindow::exportDesign(), MainWindow::insertFile(), MainWindow::measurePick(), MainWindow::openMeasure(), MainWindow::sectionFrame() (+6 more)

### Community 73 - "FileFormat"
Cohesion: 0.17
Nodes (12): FileFormat, Brep, Iges, Obj, Step, Stl, ThreeMF, FormatInfo (+4 more)

### Community 74 - "cmath"
Cohesion: 0.20
Nodes (7): EntityType, Arc, Circle, Ellipse, Line, Spline, isRound()

### Community 75 - "InputType"
Cohesion: 0.12
Nodes (17): InputType, Axis, Bodies, Body, Bool, Choice, Edges, Faces (+9 more)

### Community 76 - "string"
Cohesion: 0.13
Nodes (16): bodyNumber(), Document::component(), Document::componentOfBody(), Document::nextAxisName(), Document::nextBodyName(), Document::nextComponentName(), Document::nextDimensionName(), Document::nextPlaneName() (+8 more)

### Community 77 - "CommandDialog::CommandDialog"
Cohesion: 0.11
Nodes (6): ExpressionSpinBox, eval_, expression_, shown_, formatNumber(), dimensionOf()

### Community 80 - "SketchDisplay"
Cohesion: 0.09
Nodes (15): PendingLook, center, frame, size, ProfileObject, index, sketch, SketchDisplay (+7 more)

### Community 81 - "DocCommands.cpp"
Cohesion: 0.04
Nodes (61): Adding a tool, Command, CommandDef, feature, icon, id, inputs, name (+53 more)

### Community 82 - "Measurement"
Cohesion: 0.11
Nodes (17): Kind, Angle, Area, Length, Volume, Measurement, from, hasLine (+9 more)

### Community 83 - "NavPreset"
Cohesion: 0.20
Nodes (5): keys(), NavPreset, Fusion, SolidWorks, Tinkercad

### Community 84 - "Axis"
Cohesion: 0.50
Nodes (4): Axis, X, Y, Z

### Community 85 - "Level"
Cohesion: 0.16
Nodes (13): debug(), error(), info(), Level, Debug, Error, Info, Warning (+5 more)

### Community 86 - "README.md"
Cohesion: 0.10
Nodes (16): Build, Conventions, Development, Tests, Known gaps, Reference parts, Fusion feature checklist, Roadmap (+8 more)

### Community 87 - "DocumentError"
Cohesion: 0.11
Nodes (21): SketchRecord, data, name, offset, plane, Document::abortTransaction(), Document::addUserParameter(), Document::commitTransaction() (+13 more)

### Community 89 - "SketchEditor::SketchEditor"
Cohesion: 0.18
Nodes (5): SketchEditor::SketchEditor(), Tool, op, shape, target

### Community 90 - "exportShapes"
Cohesion: 0.47
Nodes (7): MainWindow::print3d(), NamedShape, compoundOf(), exportShapes(), fmt(), write3mf(), writeObj()

### Community 91 - "MarkingMenu.cpp"
Cohesion: 0.06
Nodes (25): UiCommand, enabled, icon, id, name, panel, run, shortcut (+17 more)

### Community 92 - "Document::evaluate"
Cohesion: 0.29
Nodes (5): Document::addBody(), Document::bodyShapes(), Document::effectOf(), Document::evaluate(), Document::replaceBody()

### Community 93 - "Known differences still to build"
Cohesion: 0.15
Nodes (12): Data and files, Findings from the videos, Fusion study list, Interface, Known differences still to build, Navigation and display, Selection and the canvas, Sketch (+4 more)

### Community 95 - "FeatureEffect"
Cohesion: 0.09
Nodes (17): Body, display, name, shape, Component, bodies, name, FeatureEffect (+9 more)

### Community 96 - "bindAdsk"
Cohesion: 0.29
Nodes (3): bindAdsk(), BRepBody, index

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
Cohesion: 0.17
Nodes (19): completeEdgeReferences(), completeFaceReferences(), decode(), decodeFaces(), edgeReference(), EdgeSig, full, normals (+11 more)

### Community 102 - "sstream"
Cohesion: 0.09
Nodes (12): DocumentError, doc_(), Document::axisFrame(), Document::Document(), Document::ocafBytes(), Document::planeFrame(), Document::removeBody(), Document::removeUserParameter() (+4 more)

### Community 103 - "UserParameter"
Cohesion: 0.33
Nodes (6): UserParameter, comment, expression, name, unit, value

### Community 104 - "Architecture"
Cohesion: 0.40
Nodes (4): Architecture, How a command works, The document, Units

### Community 105 - "BooleanOp"
Cohesion: 0.50
Nodes (4): BooleanOp, Cut, Intersect, Join

### Community 106 - "SectionState"
Cohesion: 0.25
Nodes (7): SectionState, active, angle, flip, offset, plane, visible

### Community 107 - "Display"
Cohesion: 0.25
Nodes (7): Display, constraints, construction, dimensions, points, profiles, projected

### Community 109 - "PlaneEdges"
Cohesion: 0.13
Nodes (6): PlaneEdges, arcs, curves, segments, vertices, edges

### Community 110 - "openWallBand"
Cohesion: 0.17
Nodes (17): Section, Circular, Square, Triangular, TopologyCounts, edges, faces, shells (+9 more)

### Community 111 - "ConstructionPoint"
Cohesion: 0.29
Nodes (5): ConstructionPoint, name, point, Document::point(), Document::setPoint()

### Community 112 - "Mesh"
Cohesion: 0.40
Nodes (3): Mesh, nodes, triangles

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

### Community 120 - "Dimension"
Cohesion: 0.50
Nodes (4): Dimension, Angle, Length, Unitless

### Community 121 - "ChamferType"
Cohesion: 0.67
Nodes (3): ChamferType, DistanceAngle, TwoDistances

### Community 122 - "ThreadInfo"
Cohesion: 0.50
Nodes (4): ThreadInfo, diameter, internal, pitch

### Community 123 - "Placement"
Cohesion: 0.25
Nodes (7): Placement, angle, cx, cy, dx, dy, scale

### Community 124 - "ChainSegment"
Cohesion: 0.67
Nodes (3): ChainSegment, entity, forward

### Community 125 - "Viewport::Viewport"
Cohesion: 0.16
Nodes (5): qc(), rgb(), SelectionBox, crossing, Viewport::Viewport()

### Community 127 - "Joints"
Cohesion: 0.36
Nodes (3): cornerAt(), Joints, parent_

## Knowledge Gaps
- **677 isolated node(s):** `ok`, `output`, `error`, `isReal`, `real` (+672 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 1295 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **29 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `Viewport` connect `Viewport` to `MainWindow`, `MainWindow::MainWindow`, `ViewportAnalysis.cpp`, `Viewport.cpp`, `optional`, `AnalysisSettings`, `SketchDisplay`, `Handle`, `NavPreset`, `.setSelectionFilter`, `.toPixels`, `Viewport::Viewport`, `QMouseEvent`, `TEST`, `Unit`, `Viewport.h`, `AdskModule.cpp`, `ViewportArrow.cpp`?**
  _High betweenness centrality (0.099) - this node is a cross-community bridge._
- **What connects `ok`, `output`, `error` to the rest of the system?**
  _677 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Viewport` be split into smaller, more focused modules?**
  _Cohesion score 0.017978190391983496 - nodes in this community are weakly interconnected._
- **Why does `optional` connect `optional` to `Viewport`, `Expression.cpp`, `MainWindow`, `Inputs`, `.askValue`, `Kernel.cpp`, `Io.cpp`, `Parser`, `Unit`, `SketchEditor.cpp`, `CommandDialog.cpp`, `ViewportSketch.cpp`, `Viewport.h`, `Constraint`, `Document.cpp`, `InputDef`, `MainWindowArrow.cpp`, `Session`, `ViewportArrow.cpp`, `TopoDS_Shape`, `string`, `CommandDialog::CommandDialog`, `SketchDisplay`, `DocCommands.cpp`, `ConstructionPoint`, `ConstructionAxis`, `Feature`, `Joints`?**
  _High betweenness centrality (0.096) - this node is a cross-community bridge._
- **Should `Icons.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.06081754735792622 - nodes in this community are weakly interconnected._
- **Why does `SketchEditor` connect `SketchEditor` to `Viewport`, `ParameterCompleter`, `Constraint`, `Constraint`, `.askValue`, `Display`, `Pick`, `Kind`, `PlaneEdges`, `Snap`, `Unit`, `SketchEditor.cpp`, `QMouseEvent`, `SketchEditor::SketchEditor`, `Entity`, `Viewport.h`, `Session`?**
  _High betweenness centrality (0.092) - this node is a cross-community bridge._
- **Should `Expression.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.12807881773399016 - nodes in this community are weakly interconnected._