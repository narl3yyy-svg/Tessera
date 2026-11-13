# Graph Report - tessera  (2026-11-13)

## Corpus Check
- 355 files · ~214,674 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 43 file(s) not represented in the graph (top: .drive 35, (none) 5, .cmake 1)

## Summary
- 3281 nodes · 8313 edges · 133 communities (104 shown, 29 thin omitted)
- Extraction: 84% EXTRACTED · 16% INFERRED · 0% AMBIGUOUS · INFERRED: 1308 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `4230b2dc`
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
- QString
- optional
- Kernel.cpp
- DocCommands.cpp
- Kind
- MainWindowTools.cpp
- CommandDialog
- Io.cpp
- Parser
- src/main.cpp
- .solveAndShow
- ViewportArrow.cpp
- .updatePreview
- TEST
- Sketch.cpp
- ViewportSketch.cpp
- SketchPalette
- ConstructAxisPoint
- sketchFor
- AdskModule.cpp
- Colors
- KernelError
- SketchOps.cpp
- Session.cpp
- ParameterCompleter
- Unit
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
- CommandContext
- Viewport.h
- Document.cpp
- .add
- MainWindowSketch.cpp
- InputDef
- .toPixels
- ViewportAnalysis.cpp
- Text
- Theme.cpp
- MainWindow.cpp
- Entity
- xdrive.py
- SketchGeometry.cpp
- Session
- QMouseEvent
- string
- CommandRegistry
- cmath
- TopoDS_Shape
- Theme
- FileFormat
- CommandError
- src/main.cpp
- QTimer
- Profile
- InputType
- string
- CommandDialog::CommandDialog
- math
- Value.h
- SketchDisplay
- PYBIND11_EMBEDDED_MODULE
- Measurement
- Expression.cpp
- Kernel.h
- Level
- README.md
- DocumentError
- test_feature_pattern.py
- SketchEditor::SketchEditor
- UserParameter
- UiCommand
- Known differences still to build
- ChainSegment
- FeatureEffect
- MarkingMenu
- BodyFrame
- FakeDoc
- TEST
- Zip.cpp
- TsrModule.cpp
- OcafApp.h
- Document::reevaluateParameters
- SketchRecord
- Sketch.h
- SectionState
- Display
- Dimension
- PlaneEdges
- openWallBand
- ConstructionPoint
- ModelParameter
- ConstructionAxis
- uninstall.sh
- install.sh
- main
- Feature
- Architecture
- MainWindow::enterSketchMode
- smoke
- TestFramework.h
- Placement
- Mesh
- rect
- Joints
- LAB_NOTES.md
- build.sh
- live-test.sh

## God Nodes (most connected - your core abstractions)
1. `Viewport` - 228 edges
2. `SketchEditor` - 177 edges
3. `MainWindow` - 172 edges
4. `Inputs` - 136 edges
5. `Document` - 128 edges
6. `render()` - 102 edges
7. `CommandContext` - 102 edges
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
- `Architecture` --references--> `CommandRegistry`  [INFERRED]
  docs/ARCHITECTURE.md → modules/core/include/tsr/core/CommandRegistry.h

## Import Cycles
- None detected.

## Communities (133 total, 29 thin omitted)

### Community 0 - "Viewport"
Cohesion: 0.02
Nodes (56): view_, Viewport, analysis_, analysisObjects_, appliedGridStep_, arrowBoxes_, arrowDragging_, arrowGrab_ (+48 more)

### Community 1 - "Icons.cpp"
Cohesion: 0.06
Nodes (107): arc3Icon(), arcIcon(), arrow(), axisIcon(), box(), breakIcon(), centerRectIcon(), chamferIcon() (+99 more)

### Community 2 - "ViewportAnalysis.cpp"
Cohesion: 0.13
Nodes (5): packed(), ramp(), shade(), Viewport::buildAnalysis(), Viewport::setCurvatureComb()

### Community 4 - "MainWindow"
Cohesion: 0.03
Nodes (63): Known gaps, CommandDialog, MainWindow, active_, arrowInput_, arrowInput2_, bodiesBeforeCommand_, combEdges_ (+55 more)

### Community 5 - "run_oracle.py"
Cohesion: 0.08
Nodes (54): add_point(), arc_poly(), body_at(), body_list(), build_sketch(), chain(), circumcentre(), cm() (+46 more)

### Community 6 - "Inputs"
Cohesion: 0.07
Nodes (17): CommandContext, Inputs, CommandSession::CommandSession(), getInt(), checkBody(), checkPattern(), CircularPattern, def_ (+9 more)

### Community 7 - "Document"
Cohesion: 0.03
Nodes (13): Document, effects_, modified_, pendingTools_, registry_, replaying_, txnBodies_, FromOcaf (+5 more)

### Community 8 - "Viewport.cpp"
Cohesion: 0.05
Nodes (11): keys(), NavPreset, Fusion, SolidWorks, Tinkercad, qc(), QtFrameBuffer, rgb() (+3 more)

### Community 9 - "SketchEditor"
Cohesion: 0.03
Nodes (45): SketchEditor, arcDrag_, arcDragMoved_, arcEndsChain_, arcFrom_, arcRef_, bodyEdges_, boxing_ (+37 more)

### Community 13 - "DocCommands.cpp"
Cohesion: 0.11
Nodes (20): axisOf(), evaluateDimensions(), makeBox(), makeCone(), makeCylinder(), makeSphere(), makeTorus(), NewComponent (+12 more)

### Community 14 - "Kind"
Cohesion: 0.09
Nodes (22): ConstructPlane, def_, kind_, EdgeFeature, def_, kind_, Kind, Angle (+14 more)

### Community 15 - "MainWindowTools.cpp"
Cohesion: 0.07
Nodes (26): QDialog, MainWindow::checkInterference(), MainWindow::chooseUnits(), MainWindow::driveJoints(), MainWindow::exportDesign(), MainWindow::formatLength(), MainWindow::gridSettings(), MainWindow::insertFile() (+18 more)

### Community 16 - "CommandDialog"
Cohesion: 0.05
Nodes (31): CommandDialog, bodiesId_, bodiesLabel_, bodyInput_, buttons_, cmd_, conditional_, edgesId_ (+23 more)

### Community 17 - "Io.cpp"
Cohesion: 0.12
Nodes (14): NamedShape, compoundOf(), exportShapes(), fmt(), formatForPath(), fromBrep(), importShape(), lower() (+6 more)

### Community 18 - "Parser"
Cohesion: 0.13
Nodes (22): ExpressionEnv, lengthUnit, lookup, ExpressionError, Quantity, angle, length, value (+14 more)

### Community 19 - "src/main.cpp"
Cohesion: 0.10
Nodes (4): QAbstractButton, QAction, grabWindowWithPanels(), writeLiveGeometry()

### Community 21 - "ViewportArrow.cpp"
Cohesion: 0.07
Nodes (15): Viewport::frontEdgeOwner(), rgb(), segmentDistance(), Viewport::arrowAt(), Viewport::arrowMouseMove(), Viewport::arrowMousePress(), Viewport::arrowMouseRelease(), Viewport::arrowParam() (+7 more)

### Community 22 - ".updatePreview"
Cohesion: 0.19
Nodes (4): angleInArc(), ccwContains(), circumcircle(), segDistance()

### Community 23 - "TEST"
Cohesion: 0.07
Nodes (9): Sketch, constraints, entities, points, texts, Sketch::addCircle(), Sketch::addLine(), rect() (+1 more)

### Community 24 - "Sketch.cpp"
Cohesion: 0.09
Nodes (17): Point, x, y, SketchError, entityTypeName(), isDimension(), Sketch::addSpline(), Sketch::addText() (+9 more)

### Community 25 - "ViewportSketch.cpp"
Cohesion: 0.08
Nodes (7): faceStyle(), lineStyle(), rgb(), Viewport::lookAt(), Viewport::planePoint(), Viewport::toWidget(), height

### Community 26 - "SketchPalette"
Cohesion: 0.06
Nodes (26): flatButton(), QCheckBox, QLabel, QToolButton, QWidget, SketchEditor, SketchPalette, body_ (+18 more)

### Community 27 - "ConstructAxisPoint"
Cohesion: 0.21
Nodes (5): ConstructAxisPoint, def_, kind_, JointPick, frame

### Community 28 - "sketchFor"
Cohesion: 0.12
Nodes (10): Coil, def_, Extrude, def_, Loft, def_, sketchFor(), Sweep (+2 more)

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
Cohesion: 0.19
Nodes (26): at(), chainOf(), chamferCorner(), circularPattern(), copyEntities(), cornerAt(), cross(), dot() (+18 more)

### Community 33 - "Session.cpp"
Cohesion: 0.06
Nodes (42): CommandSession, inputs_, expressionKey(), checkInputValue(), CommandContext::evaluateExpression(), CommandDef::input(), CommandSession::applyInTransaction(), CommandSession::cancel() (+34 more)

### Community 34 - "ParameterCompleter"
Cohesion: 0.12
Nodes (8): ParameterCompleter, completer_, edit_, names_, ParameterCompleter::ParameterCompleter(), public, QCompleter, QLineEdit

### Community 35 - "Unit"
Cohesion: 0.11
Nodes (17): bindAdsk(), MainWindow::lengthUnit(), Unit, Centimeter, Degree, Foot, Inch, Meter (+9 more)

### Community 38 - "solve"
Cohesion: 0.17
Nodes (13): addConstraintChecked(), Layout, n, px, py, rad, makeLayout(), pack() (+5 more)

### Community 40 - "Constraint"
Cohesion: 0.10
Nodes (13): Constraint, driven, entities, expression, hasLabel, labelX, labelY, name (+5 more)

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
Cohesion: 0.08
Nodes (24): ext(), fixedColor(), freeColor(), qc(), rgb(), Snap, alignX, alignY (+16 more)

### Community 45 - "Kind"
Cohesion: 0.09
Nodes (21): HudField, edit, editing, kind, locked, value, Kind, Angle (+13 more)

### Community 46 - "CommandContext"
Cohesion: 0.05
Nodes (50): Adding a tool, Command, CommandDef, feature, icon, id, inputs, name (+42 more)

### Community 47 - "Viewport.h"
Cohesion: 0.07
Nodes (15): AnalysisKind, CurvatureMap, Draft, None, Zebra, AnalysisSettings, curvatureScale, draftAngle (+7 more)

### Community 48 - "Document.cpp"
Cohesion: 0.09
Nodes (28): ConstructionPlane, name, spec, Document::axes(), Document::bodies(), Document::body(), Document::bodyName(), Document::components() (+20 more)

### Community 50 - "MainWindowSketch.cpp"
Cohesion: 0.09
Nodes (12): MainWindow::cancelSketch(), MainWindow::editSketch(), MainWindow::finishSketch(), MainWindow::onProfileClicked(), MainWindow::originalShape(), MainWindow::sketchPalette(), MainWindow::sketchVisible(), MainWindow::startSketch() (+4 more)

### Community 51 - "InputDef"
Cohesion: 0.08
Nodes (24): InputDef, choices, defaultValue, id, label, max, min, minExclusive (+16 more)

### Community 54 - "ViewportAnalysis.cpp"
Cohesion: 0.10
Nodes (9): ArrowPlacement, base, dir, edgePlacement(), facesPlacement(), MainWindow::attachArrowCompleters(), MainWindow::patternCentre(), MainWindow::pickedFaces() (+1 more)

### Community 55 - "Text"
Cohesion: 0.17
Nodes (5): Text, angle, font, point, text

### Community 56 - "Theme.cpp"
Cohesion: 0.19
Nodes (6): setIconTheme(), darkColors(), darkPalette(), darkStyleSheet(), lightColors(), lightStyleSheet()

### Community 57 - "MainWindow.cpp"
Cohesion: 0.08
Nodes (4): commandIcon(), qs(), MainWindow::exitSketchMode(), MainWindow::applySection()

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
Cohesion: 0.10
Nodes (7): PythonHost::PythonHost(), Session, commands_, doc_, listeners_, nextListener_, path_

### Community 63 - "QMouseEvent"
Cohesion: 0.21
Nodes (4): MarkingMenu::mouseMoveEvent(), QMouseEvent, ViewInteractor, Viewport::setInteractor()

### Community 64 - "string"
Cohesion: 0.10
Nodes (30): completeEdgeReferences(), completeFaceReferences(), decode(), decodeFaces(), dot(), edgeReference(), EdgeSig, full (+22 more)

### Community 65 - "CommandRegistry"
Cohesion: 0.12
Nodes (4): CommandRegistry, cmds_, CommandRegistry::add(), TEST()

### Community 66 - "cmath"
Cohesion: 0.21
Nodes (8): Result, error, ok, output, captured(), PythonHost::exec(), PythonHost::runScript(), fn

### Community 67 - "TopoDS_Shape"
Cohesion: 0.15
Nodes (24): SurfacePoint, normal, point, Vec3, asSolid(), boundingBox(), edgeMidpoint(), edgesNear() (+16 more)

### Community 68 - "Theme"
Cohesion: 0.22
Nodes (4): Theme, colors_, public, styled_

### Community 69 - "FileFormat"
Cohesion: 0.17
Nodes (12): FileFormat, Brep, Iges, Obj, Step, Stl, ThreeMF, FormatInfo (+4 more)

### Community 70 - "CommandError"
Cohesion: 0.15
Nodes (18): CommandError, getBool(), getReal(), applyOperation(), bodyCentre(), bodyName(), CopyFn, differenceOrNull() (+10 more)

### Community 71 - "src/main.cpp"
Cohesion: 0.08
Nodes (20): Column, kComment, kExpression, kParameter, kUnit, kValue, number(), ParametersDialog (+12 more)

### Community 74 - "Profile"
Cohesion: 0.33
Nodes (5): Profile, area, face, x, y

### Community 75 - "InputType"
Cohesion: 0.12
Nodes (17): InputType, Axis, Bodies, Body, Bool, Choice, Edges, Faces (+9 more)

### Community 76 - "string"
Cohesion: 0.20
Nodes (13): bodyNumber(), Document::axisFrame(), Document::component(), Document::componentOfBody(), Document::nextAxisName(), Document::nextBodyName(), Document::nextComponentName(), Document::nextDimensionName() (+5 more)

### Community 77 - "CommandDialog::CommandDialog"
Cohesion: 0.13
Nodes (5): CommandDialog::CommandDialog(), ExpressionSpinBox, eval_, expression_, shown_

### Community 80 - "SketchDisplay"
Cohesion: 0.07
Nodes (19): DragArrow, base, dir, value, PendingLook, center, frame, size (+11 more)

### Community 82 - "Measurement"
Cohesion: 0.09
Nodes (20): BoundingBox, max, min, Kind, Angle, Area, Length, Volume (+12 more)

### Community 83 - "Expression.cpp"
Cohesion: 0.19
Nodes (8): isConstantName(), isFunctionName(), isIdentStart(), isPlainQuantity(), isValidParameterName(), env(), mm(), TEST()

### Community 84 - "Kernel.h"
Cohesion: 0.12
Nodes (15): Axis, X, Y, Z, BooleanOp, Cut, Intersect, Join (+7 more)

### Community 85 - "Level"
Cohesion: 0.12
Nodes (13): debug(), error(), info(), Level, Debug, Error, Info, Warning (+5 more)

### Community 86 - "README.md"
Cohesion: 0.11
Nodes (15): Build, Conventions, Development, Tests, Reference parts, Fusion feature checklist, Roadmap, Contents (+7 more)

### Community 87 - "DocumentError"
Cohesion: 0.12
Nodes (25): DocumentError, Document::abortTransaction(), Document::addBody(), Document::addUserParameter(), Document::commitTransaction(), Document::openTransaction(), Document::recompute(), Document::recordFeature() (+17 more)

### Community 89 - "SketchEditor::SketchEditor"
Cohesion: 0.16
Nodes (6): QObject, SketchEditor::SketchEditor(), Tool, op, shape, target

### Community 90 - "UserParameter"
Cohesion: 0.33
Nodes (6): UserParameter, comment, expression, name, unit, value

### Community 91 - "UiCommand"
Cohesion: 0.07
Nodes (19): UiCommand, enabled, icon, id, name, panel, run, shortcut (+11 more)

### Community 93 - "Known differences still to build"
Cohesion: 0.15
Nodes (12): Data and files, Findings from the videos, Fusion study list, Interface, Known differences still to build, Navigation and display, Selection and the canvas, Sketch (+4 more)

### Community 94 - "ChainSegment"
Cohesion: 0.67
Nodes (3): ChainSegment, entity, forward

### Community 95 - "FeatureEffect"
Cohesion: 0.09
Nodes (16): Body, display, name, shape, Component, bodies, name, FeatureEffect (+8 more)

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
Cohesion: 0.19
Nodes (3): slurp(), TEST(), tmp()

### Community 100 - "Zip.cpp"
Cohesion: 0.19
Nodes (11): Entry, data, name, ZipError, crc32(), get16(), get32(), put16() (+3 more)

### Community 101 - "TsrModule.cpp"
Cohesion: 0.25
Nodes (4): bindTsr(), fromPy(), toPy(), typeName()

### Community 102 - "OcafApp.h"
Cohesion: 0.22
Nodes (4): doc_(), Document::Document(), Document::ocafBytes(), ocafApplication()

### Community 103 - "Document::reevaluateParameters"
Cohesion: 0.24
Nodes (5): Document::expressionEnv(), Document::reevaluateParameters(), Document::userParameter(), Document::load(), Document::save()

### Community 104 - "SketchRecord"
Cohesion: 0.22
Nodes (8): SketchRecord, data, name, offset, plane, Document::setSketch(), Document::sketch(), utf8()

### Community 105 - "Sketch.h"
Cohesion: 0.29
Nodes (7): EntityType, Arc, Circle, Ellipse, Line, Spline, isRound()

### Community 106 - "SectionState"
Cohesion: 0.25
Nodes (7): SectionState, active, angle, flip, offset, plane, visible

### Community 107 - "Display"
Cohesion: 0.25
Nodes (7): Display, constraints, construction, dimensions, points, profiles, projected

### Community 108 - "Dimension"
Cohesion: 0.50
Nodes (4): Dimension, Angle, Length, Unitless

### Community 109 - "PlaneEdges"
Cohesion: 0.12
Nodes (5): PlaneEdges, arcs, curves, segments, vertices

### Community 110 - "openWallBand"
Cohesion: 0.15
Nodes (19): Section, Circular, Square, Triangular, TopologyCounts, edges, faces, shells (+11 more)

### Community 111 - "ConstructionPoint"
Cohesion: 0.33
Nodes (5): ConstructionPoint, name, point, Document::point(), Document::setPoint()

### Community 112 - "ModelParameter"
Cohesion: 0.29
Nodes (7): ModelParameter, angle, expression, name, owner, value, Document::modelParameters()

### Community 113 - "ConstructionAxis"
Cohesion: 0.33
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

### Community 119 - "Architecture"
Cohesion: 0.40
Nodes (4): Architecture, How a command works, The document, Units

### Community 121 - "smoke"
Cohesion: 0.40
Nodes (5): smoke(), MassProperties, area, centerOfMass, volume

### Community 122 - "TestFramework.h"
Cohesion: 0.14
Nodes (6): CommandRegistry::all(), Case, name, fail(), Failure, Register

### Community 123 - "Placement"
Cohesion: 0.25
Nodes (7): Placement, angle, cx, cy, dx, dy, scale

### Community 124 - "Mesh"
Cohesion: 0.40
Nodes (3): Mesh, nodes, triangles

## Knowledge Gaps
- **666 isolated node(s):** `ok`, `output`, `error`, `isReal`, `real` (+661 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 1256 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **29 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `optional` connect `optional` to `Viewport`, `MainWindow`, `QString`, `Kernel.cpp`, `DocCommands.cpp`, `Io.cpp`, `Parser`, `.solveAndShow`, `ViewportArrow.cpp`, `ViewportSketch.cpp`, `sketchFor`, `SketchOps.cpp`, `Unit`, `CommandDialog.cpp`, `Viewport.h`, `Document.cpp`, `InputDef`, `ViewportAnalysis.cpp`, `Session`, `TopoDS_Shape`, `SketchEditor.cpp`, `string`, `CommandDialog::CommandDialog`, `SketchDisplay`, `Kernel.h`, `Document::reevaluateParameters`, `SketchRecord`, `PlaneEdges`, `ConstructionPoint`, `ConstructionAxis`, `Feature`?**
  _High betweenness centrality (0.114) - this node is a cross-community bridge._
- **What connects `ok`, `output`, `error` to the rest of the system?**
  _666 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Viewport` be split into smaller, more focused modules?**
  _Cohesion score 0.01815408085430969 - nodes in this community are weakly interconnected._
- **Why does `Viewport` connect `Viewport` to `ViewportAnalysis.cpp`, `Viewport.cpp`, `QTimer`, `optional`, `Viewport.h`, `SketchDisplay`, `MainWindowTools.cpp`, `.toPixels`, `ViewportArrow.cpp`, `UiCommand`, `.selectedSubShapes`, `rect`, `QMouseEvent`?**
  _High betweenness centrality (0.100) - this node is a cross-community bridge._
- **Should `Icons.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.06081754735792622 - nodes in this community are weakly interconnected._
- **Why does `SketchEditor` connect `SketchEditor` to `Viewport`, `Unit`, `Constraint`, `SketchEditor.cpp`, `Display`, `optional`, `PlaneEdges`, `Kind`, `Pick`, `Snap`, `.solveAndShow`, `.updatePreview`, `Text`, `SketchEditor::SketchEditor`, `Entity`, `Session`, `QMouseEvent`?**
  _High betweenness centrality (0.093) - this node is a cross-community bridge._
- **Should `ViewportAnalysis.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.12631578947368421 - nodes in this community are weakly interconnected._