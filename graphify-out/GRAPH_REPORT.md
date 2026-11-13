# Graph Report - tessera  (2026-11-13)

## Corpus Check
- 358 files · ~216,062 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 45 file(s) not represented in the graph (top: .drive 37, (none) 5, .cmake 1)

## Summary
- 3299 nodes · 8255 edges · 134 communities (105 shown, 29 thin omitted)
- Extraction: 85% EXTRACTED · 15% INFERRED · 0% AMBIGUOUS · INFERRED: 1220 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `f72f023e`
- Run `git rev-parse HEAD` and compare to check if the graph is stale.
- Run `graphify update .` after code changes (no API cost).

## Community Hubs (Navigation)
- Viewport
- Icons.cpp
- ViewportAnalysis.cpp
- MainWindow
- run_oracle.py
- Inputs
- Document
- Viewport.cpp
- SketchEditor
- Expression.cpp
- optional
- Kernel.cpp
- Command
- Kind
- MainWindowTools.cpp
- CommandDialog
- Io.cpp
- Parser
- Unit
- Document
- .updatePreview
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
- CommandDialog.cpp
- MainWindow::MainWindow
- solve
- .showDialog
- Constraint
- ConstraintType
- TEST
- Pick
- Snap
- Kind
- .hitTest
- AnalysisSettings
- Document.cpp
- .add
- MainWindowSketch.cpp
- InputDef
- .toPixels
- MainWindowArrow.cpp
- QDialog
- Theme.cpp
- MainWindow.cpp
- Entity
- xdrive.py
- SketchGeometry.cpp
- Session
- ViewportArrow.cpp
- string
- CommandRegistry
- cmath
- TopoDS_Shape
- Theme
- QTimer
- CommandError
- src/main.cpp
- fromInternal
- bindAdsk
- InputType
- string
- CommandDialog::CommandDialog
- math
- AddUserParameter
- SketchDisplay
- CommandDef
- Measurement
- .redrawAll
- Axis
- Level
- README.md
- DocumentError
- test_feature_pattern.py
- SketchEditor::SketchEditor
- UiCommand
- Joint
- Known differences still to build
- Value.h
- FeatureEffect
- Architecture
- openWallBand
- FakeDoc
- smoke
- Zip.cpp
- EdgeSig
- sstream
- Dimension
- ModelParameter
- BooleanOp
- SectionState
- Display
- fail
- PlaneEdges
- openWallBand
- ConstructionPoint
- Handle
- ConstructionAxis
- uninstall.sh
- install.sh
- PYBIND11_EMBEDDED_MODULE
- main
- Feature
- QTabWidget
- .openMarkingMenu
- ChamferType
- cmath
- Placement
- ChainSegment
- rect
- Joints
- LAB_NOTES.md
- build.sh
- live-test.sh

## God Nodes (most connected - your core abstractions)
1. `Viewport` - 229 edges
2. `SketchEditor` - 177 edges
3. `MainWindow` - 172 edges
4. `Inputs` - 136 edges
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
- `Architecture` --references--> `InputDef`  [INFERRED]
  docs/ARCHITECTURE.md → modules/core/include/tsr/core/Command.h
- `Architecture` --references--> `CommandDef`  [INFERRED]
  docs/ARCHITECTURE.md → modules/core/include/tsr/core/Command.h
- `Adding a tool` --references--> `CommandDef`  [INFERRED]
  docs/DEVELOPMENT.md → modules/core/include/tsr/core/Command.h

## Import Cycles
- None detected.

## Communities (134 total, 29 thin omitted)

### Community 0 - "Viewport"
Cohesion: 0.02
Nodes (57): view_, QLineEdit, Viewport, analysis_, analysisObjects_, appliedGridStep_, arrowBoxes_, arrowDragging_ (+49 more)

### Community 1 - "Icons.cpp"
Cohesion: 0.06
Nodes (107): arc3Icon(), arcIcon(), arrow(), axisIcon(), box(), breakIcon(), centerRectIcon(), chamferIcon() (+99 more)

### Community 2 - "ViewportAnalysis.cpp"
Cohesion: 0.12
Nodes (5): packed(), ramp(), shade(), Viewport::buildAnalysis(), Viewport::setCurvatureComb()

### Community 4 - "MainWindow"
Cohesion: 0.03
Nodes (62): writeLiveGeometry(), CommandDialog, MainWindow, active_, arrowInput_, arrowInput2_, bodiesBeforeCommand_, combEdges_ (+54 more)

### Community 5 - "run_oracle.py"
Cohesion: 0.08
Nodes (54): add_point(), arc_poly(), body_at(), body_list(), build_sketch(), chain(), circumcentre(), cm() (+46 more)

### Community 6 - "Inputs"
Cohesion: 0.08
Nodes (17): CommandContext, Inputs, CommandSession::CommandSession(), checkBody(), checkPattern(), defaultBody(), Hole, def_ (+9 more)

### Community 7 - "Document"
Cohesion: 0.03
Nodes (14): Document, effects_, modified_, pendingTools_, registry_, replaying_, txnBodies_, FromOcaf (+6 more)

### Community 8 - "Viewport.cpp"
Cohesion: 0.06
Nodes (6): MarkingMenu::keyPressEvent(), keys(), qc(), QKeyEvent, rgb(), Viewport::Viewport()

### Community 9 - "SketchEditor"
Cohesion: 0.03
Nodes (45): SketchEditor, arcDrag_, arcDragMoved_, arcEndsChain_, arcFrom_, arcRef_, bodyEdges_, boxing_ (+37 more)

### Community 10 - "Expression.cpp"
Cohesion: 0.13
Nodes (17): ExpressionEnv, lengthUnit, lookup, ExpressionError, evaluateExpression(), evaluateQuantity(), expressionReferences(), isConstantName() (+9 more)

### Community 11 - "optional"
Cohesion: 0.11
Nodes (3): optional, CommandRegistry::all(), Document

### Community 13 - "Command"
Cohesion: 0.10
Nodes (23): Adding a tool, Command, getInt(), getReal(), CircularPattern, def_, makeBox(), makeCone() (+15 more)

### Community 14 - "Kind"
Cohesion: 0.07
Nodes (25): ConstructPlane, def_, kind_, EdgeFeature, def_, kind_, FaceFeature, def_ (+17 more)

### Community 15 - "MainWindowTools.cpp"
Cohesion: 0.04
Nodes (9): QAbstractButton, QAction, grabWindowWithPanels(), MainWindow::insertFile(), MainWindow::sectionFrame(), MainWindow::sectionPlane(), MainWindow::setSelectionFilter(), MainWindow::showParameters() (+1 more)

### Community 16 - "CommandDialog"
Cohesion: 0.05
Nodes (31): CommandDialog, bodiesId_, bodiesLabel_, bodyInput_, buttons_, cmd_, conditional_, edgesId_ (+23 more)

### Community 17 - "Io.cpp"
Cohesion: 0.06
Nodes (30): MainWindow::print3d(), FileFormat, Brep, Iges, Obj, Step, Stl, ThreeMF (+22 more)

### Community 18 - "Parser"
Cohesion: 0.20
Nodes (13): Quantity, angle, length, value, describe(), isIdentChar(), Parser, ang_ (+5 more)

### Community 19 - "Unit"
Cohesion: 0.13
Nodes (16): MainWindow::lengthUnit(), Unit, Centimeter, Degree, Foot, Inch, Meter, Millimeter (+8 more)

### Community 21 - "Document"
Cohesion: 0.23
Nodes (7): ConstructAxisPoint, def_, kind_, jointOrigin(), JointPick, frame, revolveAxis()

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
Nodes (24): QCheckBox, QLabel, QWidget, SketchEditor, SketchPalette, body_, constraints_, construction_ (+16 more)

### Community 27 - "Viewport.h"
Cohesion: 0.11
Nodes (6): QLabel, Profile, area, face, x, y

### Community 28 - "CommandError"
Cohesion: 0.11
Nodes (20): CommandError, applyOperation(), Coil, def_, evaluateDimensions(), Extrude, def_, openChains() (+12 more)

### Community 29 - "AdskModule.cpp"
Cohesion: 0.12
Nodes (13): Application, BRepBodies, Component, Design, Product, raiseIfError(), UserParameter, name (+5 more)

### Community 30 - "Colors"
Cohesion: 0.07
Nodes (28): Colors, base, border, cubeBox, cubeText, errorBackground, grid, gridMajor (+20 more)

### Community 31 - "KernelError"
Cohesion: 0.20
Nodes (30): KernelError, ThreadInfo, diameter, internal, pitch, asSolid(), boolean(), chamfer() (+22 more)

### Community 32 - "SketchOps.cpp"
Cohesion: 0.21
Nodes (26): at(), chainOf(), chamferCorner(), circularPattern(), copyEntities(), cross(), dot(), extendLine() (+18 more)

### Community 33 - "Session.cpp"
Cohesion: 0.06
Nodes (42): CommandSession, inputs_, expressionKey(), checkInputValue(), CommandContext::evaluateExpression(), CommandDef::input(), CommandSession::applyInTransaction(), CommandSession::cancel() (+34 more)

### Community 34 - "ParameterCompleter"
Cohesion: 0.12
Nodes (8): ParameterCompleter, completer_, edit_, names_, ParameterCompleter::ParameterCompleter(), public, QCompleter, QLineEdit

### Community 35 - "Constraint"
Cohesion: 0.14
Nodes (12): Constraint, driven, entities, expression, hasLabel, labelX, labelY, name (+4 more)

### Community 37 - "MainWindow::MainWindow"
Cohesion: 0.14
Nodes (4): PythonHost, MainWindow::MainWindow(), MainWindow::exitSketchMode(), MainWindow::showPreferences()

### Community 38 - "solve"
Cohesion: 0.18
Nodes (12): addConstraintChecked(), Layout, n, px, py, rad, makeLayout(), pack() (+4 more)

### Community 40 - "Constraint"
Cohesion: 0.11
Nodes (12): ext(), fixedColor(), freeColor(), qc(), rgb(), wire(), Text, angle (+4 more)

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
Cohesion: 0.09
Nodes (18): Snap, alignX, alignY, bodyArc, bodySegment, entity, fromX, fromY (+10 more)

### Community 45 - "Kind"
Cohesion: 0.09
Nodes (21): HudField, edit, editing, kind, locked, value, Kind, Angle (+13 more)

### Community 46 - ".hitTest"
Cohesion: 0.19
Nodes (5): angleInArc(), Hit, index, kind, segDistance()

### Community 47 - "AnalysisSettings"
Cohesion: 0.09
Nodes (20): AnalysisKind, CurvatureMap, Draft, None, Zebra, AnalysisSettings, curvatureScale, draftAngle (+12 more)

### Community 48 - "Document.cpp"
Cohesion: 0.09
Nodes (27): ConstructionPlane, name, spec, Document::axes(), Document::bodies(), Document::body(), Document::bodyName(), Document::components() (+19 more)

### Community 50 - "MainWindowSketch.cpp"
Cohesion: 0.10
Nodes (12): MainWindow::cancelSketch(), MainWindow::editSketch(), MainWindow::finishSketch(), MainWindow::onProfileClicked(), MainWindow::originalShape(), MainWindow::sketchPalette(), MainWindow::sketchVisible(), MainWindow::startSketch() (+4 more)

### Community 51 - "InputDef"
Cohesion: 0.08
Nodes (24): InputDef, choices, defaultValue, id, label, max, min, minExclusive (+16 more)

### Community 54 - "MainWindowArrow.cpp"
Cohesion: 0.12
Nodes (8): ArrowPlacement, base, dir, edgePlacement(), facesPlacement(), MainWindow::attachArrowCompleters(), MainWindow::patternCentre(), MainWindow::pickedFaces()

### Community 55 - "QDialog"
Cohesion: 0.18
Nodes (5): QDialog, MainWindow::exportDesign(), MainWindow::measurePick(), MainWindow::openMeasure(), toolWindow()

### Community 56 - "Theme.cpp"
Cohesion: 0.19
Nodes (6): setIconTheme(), darkColors(), darkPalette(), darkStyleSheet(), lightColors(), lightStyleSheet()

### Community 57 - "MainWindow.cpp"
Cohesion: 0.10
Nodes (5): commandIcon(), flatButton(), qs(), MainWindow::applySection(), QToolButton

### Community 58 - "Entity"
Cohesion: 0.08
Nodes (24): Entity, a, b, center, construction, fit, projected, radius (+16 more)

### Community 59 - "xdrive.py"
Cohesion: 0.32
Nodes (14): button(), canvas(), click(), drag(), flush(), geometry(), key(), keycode() (+6 more)

### Community 61 - "SketchGeometry.cpp"
Cohesion: 0.12
Nodes (11): curve(), curves(), customPlaneSpec(), entityCurves(), interiorPoint(), planeFrame(), profileAt(), profiles() (+3 more)

### Community 62 - "Session"
Cohesion: 0.09
Nodes (7): PythonHost::PythonHost(), Session, commands_, doc_, listeners_, nextListener_, path_

### Community 63 - "ViewportArrow.cpp"
Cohesion: 0.05
Nodes (21): MarkingMenu::mouseMoveEvent(), QMouseEvent, ViewInteractor, Viewport::frontEdgeOwner(), rgb(), segmentDistance(), Viewport::arrowAt(), Viewport::arrowMouseMove() (+13 more)

### Community 64 - "string"
Cohesion: 0.10
Nodes (31): BodyFrame, diag, dx, dy, dz, x0, y0, z0 (+23 more)

### Community 65 - "CommandRegistry"
Cohesion: 0.12
Nodes (4): CommandRegistry, cmds_, CommandRegistry::add(), TEST()

### Community 66 - "cmath"
Cohesion: 0.15
Nodes (11): Result, error, ok, output, captured(), PythonHost::exec(), PythonHost::runScript(), Case (+3 more)

### Community 67 - "TopoDS_Shape"
Cohesion: 0.19
Nodes (19): SurfacePoint, normal, point, Vec3, edgeMidpoint(), edgesNear(), frame(), makeBox() (+11 more)

### Community 68 - "Theme"
Cohesion: 0.22
Nodes (4): Theme, colors_, public, styled_

### Community 69 - "QTimer"
Cohesion: 0.18
Nodes (4): MainWindow::buildSketchTab(), MainWindow::enterSketchMode(), QTimer, Viewport::selectArrowValue()

### Community 70 - "CommandError"
Cohesion: 0.08
Nodes (28): getBool(), axisOf(), bodyCentre(), bodyName(), Combine, def_, CopyFn, differenceOrNull() (+20 more)

### Community 71 - "src/main.cpp"
Cohesion: 0.09
Nodes (20): Column, kComment, kExpression, kParameter, kUnit, kValue, number(), ParametersDialog (+12 more)

### Community 72 - "fromInternal"
Cohesion: 0.17
Nodes (13): MainWindow::checkInterference(), MainWindow::chooseUnits(), MainWindow::driveJoints(), MainWindow::formatLength(), MainWindow::gridSettings(), MainWindow::openAnalysis(), MainWindow::openSection(), MainWindow::showCenterOfMass() (+5 more)

### Community 74 - "bindAdsk"
Cohesion: 0.29
Nodes (3): bindAdsk(), BRepBody, index

### Community 75 - "InputType"
Cohesion: 0.08
Nodes (21): bindTsr(), fromPy(), toPy(), typeName(), InputType, Axis, Bodies, Body (+13 more)

### Community 76 - "string"
Cohesion: 0.12
Nodes (18): bodyNumber(), Document::bodyShapes(), Document::component(), Document::componentOfBody(), Document::effectOf(), Document::evaluate(), Document::nextAxisName(), Document::nextBodyName() (+10 more)

### Community 77 - "CommandDialog::CommandDialog"
Cohesion: 0.14
Nodes (6): ExpressionSpinBox, eval_, expression_, shown_, formatNumber(), dimensionOf()

### Community 80 - "SketchDisplay"
Cohesion: 0.09
Nodes (15): PendingLook, center, frame, size, ProfileObject, index, sketch, SketchDisplay (+7 more)

### Community 81 - "CommandDef"
Cohesion: 0.06
Nodes (24): CommandDef, feature, icon, id, inputs, name, nameInput, panel (+16 more)

### Community 82 - "Measurement"
Cohesion: 0.13
Nodes (14): Kind, Angle, Area, Length, Volume, Measurement, from, hasLine (+6 more)

### Community 83 - ".redrawAll"
Cohesion: 0.09
Nodes (7): NavPreset, Fusion, SolidWorks, Tinkercad, Viewport::clearDragArrow(), Viewport::clearSecondArrow(), Viewport::setInteractor()

### Community 84 - "Axis"
Cohesion: 0.50
Nodes (4): Axis, X, Y, Z

### Community 85 - "Level"
Cohesion: 0.12
Nodes (13): debug(), error(), info(), Level, Debug, Error, Info, Warning (+5 more)

### Community 86 - "README.md"
Cohesion: 0.11
Nodes (15): Build, Conventions, Development, Tests, Reference parts, Fusion feature checklist, Roadmap, Contents (+7 more)

### Community 87 - "DocumentError"
Cohesion: 0.08
Nodes (30): DocumentError, SketchRecord, data, name, offset, plane, Document::abortTransaction(), Document::addBody() (+22 more)

### Community 89 - "SketchEditor::SketchEditor"
Cohesion: 0.10
Nodes (7): QObject, SketchEditor::SketchEditor(), edges, Tool, op, shape, target

### Community 91 - "UiCommand"
Cohesion: 0.12
Nodes (12): UiCommand, enabled, icon, id, name, panel, run, shortcut (+4 more)

### Community 93 - "Known differences still to build"
Cohesion: 0.15
Nodes (12): Data and files, Findings from the videos, Fusion study list, Interface, Known differences still to build, Navigation and display, Selection and the canvas, Sketch (+4 more)

### Community 95 - "FeatureEffect"
Cohesion: 0.09
Nodes (18): Body, display, name, shape, Component, bodies, name, FeatureEffect (+10 more)

### Community 96 - "Architecture"
Cohesion: 0.40
Nodes (4): Architecture, How a command works, The document, Units

### Community 97 - "openWallBand"
Cohesion: 0.14
Nodes (13): BoundingBox, max, min, WallSide, Center, Side1, Side2, faceNormalAt() (+5 more)

### Community 98 - "FakeDoc"
Cohesion: 0.17
Nodes (6): FakeDoc, aborts, commits, items, open, snapshot

### Community 99 - "smoke"
Cohesion: 0.40
Nodes (5): smoke(), MassProperties, area, centerOfMass, volume

### Community 100 - "Zip.cpp"
Cohesion: 0.11
Nodes (14): Entry, data, name, ZipError, crc32(), get16(), get32(), put16() (+6 more)

### Community 101 - "EdgeSig"
Cohesion: 0.18
Nodes (11): dot(), EdgeSig, full, normals, point, rel, tangent, type (+3 more)

### Community 102 - "sstream"
Cohesion: 0.15
Nodes (5): doc_(), Document::Document(), Document::ocafBytes(), ocafApplication(), Document::load()

### Community 103 - "Dimension"
Cohesion: 0.50
Nodes (4): Dimension, Angle, Length, Unitless

### Community 104 - "ModelParameter"
Cohesion: 0.22
Nodes (8): ModelParameter, angle, expression, name, owner, value, Document::modelParameters(), Document::sketch()

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
Cohesion: 0.25
Nodes (5): PlaneEdges, arcs, curves, segments, vertices

### Community 110 - "openWallBand"
Cohesion: 0.16
Nodes (18): Section, Circular, Square, Triangular, TopologyCounts, edges, faces, shells (+10 more)

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

### Community 121 - "ChamferType"
Cohesion: 0.67
Nodes (3): ChamferType, DistanceAngle, TwoDistances

### Community 122 - "cmath"
Cohesion: 0.10
Nodes (8): MarkingMenu, enabled, MarkingMenu::MarkingMenu(), MarkingMenu::paintEvent(), MarkingMenu::popupAt(), public, MarkingMenu::ringIndexAt(), MarkingMenu::run()

### Community 123 - "Placement"
Cohesion: 0.25
Nodes (7): Placement, angle, cx, cy, dx, dy, scale

### Community 124 - "ChainSegment"
Cohesion: 0.67
Nodes (3): ChainSegment, entity, forward

### Community 125 - "rect"
Cohesion: 0.28
Nodes (3): SelectionBox, crossing, rect()

### Community 127 - "Joints"
Cohesion: 0.36
Nodes (3): cornerAt(), Joints, parent_

## Knowledge Gaps
- **669 isolated node(s):** `ok`, `output`, `error`, `isReal`, `real` (+664 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 1282 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **29 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `Viewport` connect `Viewport` to `ViewportAnalysis.cpp`, `MainWindow`, `QTimer`, `Viewport.cpp`, `QTimer`, `fromInternal`, `optional`, `AnalysisSettings`, `SketchDisplay`, `Handle`, `.redrawAll`, `.toPixels`, `Viewport.h`, `rect`, `ViewportArrow.cpp`?**
  _High betweenness centrality (0.100) - this node is a cross-community bridge._
- **What connects `ok`, `output`, `error` to the rest of the system?**
  _669 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Viewport` be split into smaller, more focused modules?**
  _Cohesion score 0.017978190391983496 - nodes in this community are weakly interconnected._
- **Why does `optional` connect `optional` to `Viewport`, `MainWindow`, `Inputs`, `Expression.cpp`, `Kernel.cpp`, `Io.cpp`, `Parser`, `Unit`, `SketchEditor.cpp`, `ViewportSketch.cpp`, `Viewport.h`, `Constraint`, `CommandDialog.cpp`, `Snap`, `Document.cpp`, `InputDef`, `MainWindowArrow.cpp`, `Session`, `ViewportArrow.cpp`, `TopoDS_Shape`, `CommandError`, `string`, `CommandDialog::CommandDialog`, `SketchDisplay`, `ModelParameter`, `ConstructionPoint`, `ConstructionAxis`, `Feature`, `Joints`?**
  _High betweenness centrality (0.099) - this node is a cross-community bridge._
- **Should `Icons.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.06081754735792622 - nodes in this community are weakly interconnected._
- **Why does `SketchEditor` connect `SketchEditor` to `Viewport`, `Constraint`, `Constraint`, `Display`, `optional`, `PlaneEdges`, `Kind`, `.hitTest`, `Pick`, `Snap`, `Unit`, `SketchEditor.cpp`, `.updatePreview`, `SketchEditor::SketchEditor`, `Entity`, `Viewport.h`, `Session`, `ViewportArrow.cpp`?**
  _High betweenness centrality (0.095) - this node is a cross-community bridge._
- **Should `ViewportAnalysis.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.11904761904761904 - nodes in this community are weakly interconnected._