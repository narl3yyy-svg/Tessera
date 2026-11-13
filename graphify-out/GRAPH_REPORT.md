# Graph Report - tessera  (2026-11-13)

## Corpus Check
- 360 files · ~216,330 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 46 file(s) not represented in the graph (top: .drive 38, (none) 5, .cmake 1)

## Summary
- 3301 nodes · 8260 edges · 133 communities (106 shown, 27 thin omitted)
- Extraction: 85% EXTRACTED · 15% INFERRED · 0% AMBIGUOUS · INFERRED: 1220 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `575d901c`
- Run `git rev-parse HEAD` and compare to check if the graph is stale.
- Run `graphify update .` after code changes (no API cost).

## Community Hubs (Navigation)
- Viewport
- Icons.cpp
- Command.cpp
- MainWindow
- run_oracle.py
- Inputs
- Document
- Viewport.cpp
- SketchEditor
- Text
- optional
- Kernel.cpp
- Command
- Kind
- src/main.cpp
- CommandDialog
- Io.cpp
- Parser
- Unit
- SketchEditor.cpp
- Document
- .updatePreview
- TEST
- Sketch.cpp
- ViewportSketch.cpp
- SketchPalette
- CommandSession
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
- .showDialog
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
- bindTsr
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
- MainWindowTools.cpp
- Log.h
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
- Column
- UiCommand
- Joint
- Known differences still to build
- Value.h
- FeatureEffect
- Development
- openWallBand
- FakeDoc
- smoke
- Zip.cpp
- EdgeSig
- sstream
- Rect
- ModelParameter
- BooleanOp
- SectionState
- Display
- fail
- PlaneEdges
- openWallBand
- ConstructionPoint
- MainWindow::setSelectionFilter
- ConstructionAxis
- uninstall.sh
- install.sh
- PYBIND11_EMBEDDED_MODULE
- main
- Feature
- Session::addListener
- .openMarkingMenu
- ChamferType
- MarkingMenu
- Placement
- ChainSegment
- rect
- Joints
- Placement::apply
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

## Communities (133 total, 27 thin omitted)

### Community 0 - "Viewport"
Cohesion: 0.02
Nodes (57): view_, QLineEdit, Viewport, analysis_, analysisObjects_, appliedGridStep_, arrowBoxes_, arrowDragging_ (+49 more)

### Community 1 - "Icons.cpp"
Cohesion: 0.06
Nodes (109): arc3Icon(), arcIcon(), arrow(), axisIcon(), box(), breakIcon(), centerRectIcon(), chamferIcon() (+101 more)

### Community 2 - "Command.cpp"
Cohesion: 0.24
Nodes (10): expressionKey(), checkInputValue(), CommandContext::evaluateExpression(), CommandDef::input(), CommandSession::applyInTransaction(), CommandSession::cancel(), CommandSession::execute(), CommandSession::preview() (+2 more)

### Community 4 - "MainWindow"
Cohesion: 0.03
Nodes (64): Known gaps, writeLiveGeometry(), CommandDialog, MainWindow, active_, arrowInput_, arrowInput2_, bodiesBeforeCommand_ (+56 more)

### Community 5 - "run_oracle.py"
Cohesion: 0.08
Nodes (54): add_point(), arc_poly(), body_at(), body_list(), build_sketch(), chain(), circumcentre(), cm() (+46 more)

### Community 6 - "Inputs"
Cohesion: 0.08
Nodes (17): CommandContext, Inputs, CommandSession::CommandSession(), checkBody(), checkPattern(), defaultBody(), Hole, def_ (+9 more)

### Community 7 - "Document"
Cohesion: 0.03
Nodes (11): Document, effects_, modified_, pendingTools_, registry_, replaying_, txnBodies_, FromOcaf (+3 more)

### Community 8 - "Viewport.cpp"
Cohesion: 0.06
Nodes (4): keys(), qc(), QtFrameBuffer, rgb()

### Community 9 - "SketchEditor"
Cohesion: 0.03
Nodes (45): SketchEditor, arcDrag_, arcDragMoved_, arcEndsChain_, arcFrom_, arcRef_, bodyEdges_, boxing_ (+37 more)

### Community 10 - "Text"
Cohesion: 0.19
Nodes (5): Text, angle, font, point, text

### Community 11 - "optional"
Cohesion: 0.12
Nodes (3): optional, CommandRegistry::all(), Document

### Community 13 - "Command"
Cohesion: 0.10
Nodes (23): Adding a tool, Command, getInt(), getReal(), CircularPattern, def_, makeBox(), makeCone() (+15 more)

### Community 14 - "Kind"
Cohesion: 0.07
Nodes (25): ConstructPlane, def_, kind_, EdgeFeature, def_, kind_, FaceFeature, def_ (+17 more)

### Community 16 - "CommandDialog"
Cohesion: 0.04
Nodes (32): CommandDialog, bodiesId_, bodiesLabel_, bodyInput_, buttons_, cmd_, conditional_, edgesId_ (+24 more)

### Community 17 - "Io.cpp"
Cohesion: 0.07
Nodes (30): MainWindow::print3d(), FileFormat, Brep, Iges, Obj, Step, Stl, ThreeMF (+22 more)

### Community 18 - "Parser"
Cohesion: 0.09
Nodes (30): ExpressionEnv, lengthUnit, lookup, ExpressionError, Quantity, angle, length, value (+22 more)

### Community 19 - "Unit"
Cohesion: 0.11
Nodes (22): MainWindow::lengthUnit(), Dimension, Angle, Length, Unitless, Unit, Centimeter, Degree (+14 more)

### Community 21 - "Document"
Cohesion: 0.23
Nodes (7): ConstructAxisPoint, def_, kind_, jointOrigin(), JointPick, frame, revolveAxis()

### Community 22 - ".updatePreview"
Cohesion: 0.17
Nodes (4): angleInArc(), ccwContains(), circumcircle(), segDistance()

### Community 23 - "TEST"
Cohesion: 0.08
Nodes (7): Sketch, constraints, entities, points, texts, Sketch::addCircle(), TEST()

### Community 24 - "Sketch.cpp"
Cohesion: 0.07
Nodes (23): EntityType, Arc, Circle, Ellipse, Line, Spline, isRound(), Point (+15 more)

### Community 25 - "ViewportSketch.cpp"
Cohesion: 0.08
Nodes (6): faceStyle(), lineStyle(), rgb(), Viewport::lookAt(), Viewport::planePoint(), Viewport::toWidget()

### Community 26 - "SketchPalette"
Cohesion: 0.06
Nodes (26): flatButton(), QCheckBox, QLabel, QToolButton, QWidget, SketchEditor, SketchPalette, body_ (+18 more)

### Community 27 - "CommandSession"
Cohesion: 0.15
Nodes (4): CommandSession, inputs_, CommandRegistry::find(), CommandRegistry::run()

### Community 28 - "CommandError"
Cohesion: 0.11
Nodes (20): CommandError, applyOperation(), Coil, def_, evaluateDimensions(), Extrude, def_, openChains() (+12 more)

### Community 29 - "AdskModule.cpp"
Cohesion: 0.09
Nodes (16): Application, bindAdsk(), BRepBodies, BRepBody, index, Component, Design, Product (+8 more)

### Community 30 - "Colors"
Cohesion: 0.07
Nodes (28): Colors, base, border, cubeBox, cubeText, errorBackground, grid, gridMajor (+20 more)

### Community 31 - "KernelError"
Cohesion: 0.20
Nodes (30): KernelError, ThreadInfo, diameter, internal, pitch, asSolid(), boolean(), chamfer() (+22 more)

### Community 32 - "SketchOps.cpp"
Cohesion: 0.23
Nodes (25): at(), chainOf(), chamferCorner(), circularPattern(), copyEntities(), cross(), dot(), extendLine() (+17 more)

### Community 33 - "Session.cpp"
Cohesion: 0.15
Nodes (22): historyEdit(), OwnedCommand, owned, OwningCommandSession, Session::begin(), Session::deleteFeature(), Session::deleteParameter(), Session::editFeature() (+14 more)

### Community 34 - "ParameterCompleter"
Cohesion: 0.12
Nodes (8): ParameterCompleter, completer_, edit_, names_, ParameterCompleter::ParameterCompleter(), public, QCompleter, QLineEdit

### Community 35 - "Constraint"
Cohesion: 0.12
Nodes (13): Constraint, driven, entities, expression, hasLabel, labelX, labelY, name (+5 more)

### Community 37 - "MainWindow::MainWindow"
Cohesion: 0.15
Nodes (3): PythonHost, MainWindow::MainWindow(), MainWindow::showPreferences()

### Community 38 - "solve"
Cohesion: 0.18
Nodes (12): addConstraintChecked(), Layout, n, px, py, rad, makeLayout(), pack() (+4 more)

### Community 40 - "Constraint"
Cohesion: 0.13
Nodes (7): ext(), fixedColor(), freeColor(), qc(), rgb(), wire(), Sketch::addLine()

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
Cohesion: 0.19
Nodes (3): slurp(), TEST(), tmp()

### Community 47 - "AnalysisSettings"
Cohesion: 0.07
Nodes (24): AnalysisKind, CurvatureMap, Draft, None, Zebra, AnalysisSettings, curvatureScale, draftAngle (+16 more)

### Community 48 - "Document.cpp"
Cohesion: 0.08
Nodes (30): ConstructionPlane, name, spec, Document::axes(), Document::bodies(), Document::body(), Document::bodyName(), Document::component() (+22 more)

### Community 50 - "MainWindowSketch.cpp"
Cohesion: 0.05
Nodes (20): MainWindow::cancelSketch(), MainWindow::editSketch(), MainWindow::finishSketch(), MainWindow::onProfileClicked(), MainWindow::originalShape(), MainWindow::sketchPalette(), MainWindow::sketchVisible(), MainWindow::startSketch() (+12 more)

### Community 51 - "InputDef"
Cohesion: 0.08
Nodes (24): InputDef, choices, defaultValue, id, label, max, min, minExclusive (+16 more)

### Community 54 - "MainWindowArrow.cpp"
Cohesion: 0.07
Nodes (12): ArrowPlacement, base, dir, edgePlacement(), facesPlacement(), MainWindow::attachArrowCompleters(), MainWindow::patternCentre(), MainWindow::pickedFaces() (+4 more)

### Community 55 - "bindTsr"
Cohesion: 0.29
Nodes (4): bindTsr(), fromPy(), toPy(), typeName()

### Community 56 - "Theme.cpp"
Cohesion: 0.19
Nodes (6): setIconTheme(), darkColors(), darkPalette(), darkStyleSheet(), lightColors(), lightStyleSheet()

### Community 57 - "MainWindow.cpp"
Cohesion: 0.08
Nodes (5): commandIcon(), qs(), MainWindow::beginSketch(), MainWindow::exitSketchMode(), MainWindow::applySection()

### Community 58 - "Entity"
Cohesion: 0.11
Nodes (17): Entity, a, b, center, construction, fit, projected, radius (+9 more)

### Community 59 - "xdrive.py"
Cohesion: 0.32
Nodes (14): button(), canvas(), click(), drag(), flush(), geometry(), key(), keycode() (+6 more)

### Community 61 - "SketchGeometry.cpp"
Cohesion: 0.09
Nodes (16): Profile, area, face, x, y, curve(), curves(), customPlaneSpec() (+8 more)

### Community 62 - "Session"
Cohesion: 0.10
Nodes (6): Session, commands_, doc_, listeners_, nextListener_, path_

### Community 63 - "ViewportArrow.cpp"
Cohesion: 0.05
Nodes (20): MarkingMenu::mouseMoveEvent(), QMouseEvent, ViewInteractor, Viewport::frontEdgeOwner(), rgb(), segmentDistance(), Viewport::arrowAt(), Viewport::arrowMouseMove() (+12 more)

### Community 64 - "string"
Cohesion: 0.10
Nodes (31): BodyFrame, diag, dx, dy, dz, x0, y0, z0 (+23 more)

### Community 65 - "CommandRegistry"
Cohesion: 0.12
Nodes (4): CommandRegistry, cmds_, CommandRegistry::add(), TEST()

### Community 66 - "cmath"
Cohesion: 0.14
Nodes (12): Result, error, ok, output, captured(), PythonHost::exec(), PythonHost::PythonHost(), PythonHost::runScript() (+4 more)

### Community 67 - "TopoDS_Shape"
Cohesion: 0.19
Nodes (19): SurfacePoint, normal, point, Vec3, edgeMidpoint(), edgesNear(), frame(), makeBox() (+11 more)

### Community 68 - "Theme"
Cohesion: 0.22
Nodes (4): Theme, colors_, public, styled_

### Community 69 - "QTimer"
Cohesion: 0.14
Nodes (4): MainWindow::buildSketchTab(), MainWindow::enterSketchMode(), QTimer, Viewport::selectArrowValue()

### Community 70 - "CommandError"
Cohesion: 0.08
Nodes (28): getBool(), axisOf(), bodyCentre(), bodyName(), Combine, def_, CopyFn, differenceOrNull() (+20 more)

### Community 71 - "src/main.cpp"
Cohesion: 0.11
Nodes (14): number(), ParametersDialog, building_, error_, listener_, ParametersDialog::ParametersDialog(), public, rebuildPending_ (+6 more)

### Community 72 - "MainWindowTools.cpp"
Cohesion: 0.08
Nodes (22): QDialog, MainWindow::checkInterference(), MainWindow::chooseUnits(), MainWindow::driveJoints(), MainWindow::exportDesign(), MainWindow::formatLength(), MainWindow::gridSettings(), MainWindow::insertFile() (+14 more)

### Community 74 - "Log.h"
Cohesion: 0.36
Nodes (6): debug(), error(), info(), Sink, warning(), setSink()

### Community 75 - "InputType"
Cohesion: 0.12
Nodes (17): InputType, Axis, Bodies, Body, Bool, Choice, Edges, Faces (+9 more)

### Community 76 - "string"
Cohesion: 0.09
Nodes (25): DocumentError, bodyNumber(), Document::addBody(), Document::axisFrame(), Document::bodyShapes(), Document::effectOf(), Document::evaluate(), Document::nextAxisName() (+17 more)

### Community 77 - "CommandDialog::CommandDialog"
Cohesion: 0.10
Nodes (7): CommandDialog::CommandDialog(), ExpressionSpinBox, eval_, expression_, shown_, formatNumber(), inputExpression()

### Community 80 - "SketchDisplay"
Cohesion: 0.12
Nodes (11): ProfileObject, index, sketch, SketchDisplay, construction, curves, fixedCurves, frame (+3 more)

### Community 81 - "CommandDef"
Cohesion: 0.06
Nodes (24): CommandDef, feature, icon, id, inputs, name, nameInput, panel (+16 more)

### Community 82 - "Measurement"
Cohesion: 0.13
Nodes (14): Kind, Angle, Area, Length, Volume, Measurement, from, hasLine (+6 more)

### Community 83 - ".redrawAll"
Cohesion: 0.14
Nodes (8): NavPreset, Fusion, SolidWorks, Tinkercad, Viewport::setCurvatureComb(), Viewport::clearDragArrow(), Viewport::clearSecondArrow(), Viewport::setInteractor()

### Community 84 - "Axis"
Cohesion: 0.50
Nodes (4): Axis, X, Y, Z

### Community 85 - "Level"
Cohesion: 0.16
Nodes (7): Level, Debug, Error, Info, Warning, name(), write()

### Community 86 - "README.md"
Cohesion: 0.11
Nodes (15): Architecture, How a command works, The document, Units, Reference parts, Fusion feature checklist, Roadmap, Contents (+7 more)

### Community 87 - "DocumentError"
Cohesion: 0.11
Nodes (21): SketchRecord, data, name, offset, plane, Document::abortTransaction(), Document::addUserParameter(), Document::commitTransaction() (+13 more)

### Community 89 - "SketchEditor::SketchEditor"
Cohesion: 0.16
Nodes (6): QObject, SketchEditor::SketchEditor(), Tool, op, shape, target

### Community 90 - "Column"
Cohesion: 0.33
Nodes (6): Column, kComment, kExpression, kParameter, kUnit, kValue

### Community 91 - "UiCommand"
Cohesion: 0.13
Nodes (12): UiCommand, enabled, icon, id, name, panel, run, shortcut (+4 more)

### Community 93 - "Known differences still to build"
Cohesion: 0.15
Nodes (12): Data and files, Findings from the videos, Fusion study list, Interface, Known differences still to build, Navigation and display, Selection and the canvas, Sketch (+4 more)

### Community 95 - "FeatureEffect"
Cohesion: 0.09
Nodes (17): Body, display, name, shape, Component, bodies, name, FeatureEffect (+9 more)

### Community 96 - "Development"
Cohesion: 0.40
Nodes (4): Build, Conventions, Development, Tests

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
Cohesion: 0.21
Nodes (11): Entry, data, name, ZipError, crc32(), get16(), get32(), put16() (+3 more)

### Community 101 - "EdgeSig"
Cohesion: 0.18
Nodes (11): dot(), EdgeSig, full, normals, point, rel, tangent, type (+3 more)

### Community 102 - "sstream"
Cohesion: 0.10
Nodes (8): doc_(), Document::Document(), Document::expressionEnv(), Document::ocafBytes(), Document::reevaluateParameters(), ocafApplication(), Document::load(), Document::save()

### Community 103 - "Rect"
Cohesion: 0.50
Nodes (4): Session::notifyChanged(), Rect, l, p

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

### Community 122 - "MarkingMenu"
Cohesion: 0.40
Nodes (3): MarkingMenu, enabled, public

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
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 1283 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **27 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `Viewport` connect `Viewport` to `MainWindow`, `QTimer`, `Viewport.cpp`, `QTimer`, `MainWindowTools.cpp`, `optional`, `AnalysisSettings`, `SketchDisplay`, `src/main.cpp`, `MainWindowSketch.cpp`, `.redrawAll`, `.setSelectionFilter`, `.toPixels`, `MainWindowArrow.cpp`, `rect`, `ViewportArrow.cpp`?**
  _High betweenness centrality (0.099) - this node is a cross-community bridge._
- **What connects `ok`, `output`, `error` to the rest of the system?**
  _669 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Viewport` be split into smaller, more focused modules?**
  _Cohesion score 0.017978190391983496 - nodes in this community are weakly interconnected._
- **Why does `optional` connect `optional` to `Viewport`, `MainWindow`, `Inputs`, `Kernel.cpp`, `src/main.cpp`, `Io.cpp`, `Parser`, `Unit`, `SketchEditor.cpp`, `ViewportSketch.cpp`, `Constraint`, `CommandDialog.cpp`, `Constraint`, `AnalysisSettings`, `Document.cpp`, `InputDef`, `MainWindowArrow.cpp`, `Session`, `ViewportArrow.cpp`, `TopoDS_Shape`, `CommandError`, `CommandDialog::CommandDialog`, `ModelParameter`, `ConstructionPoint`, `ConstructionAxis`, `Feature`, `Joints`?**
  _High betweenness centrality (0.097) - this node is a cross-community bridge._
- **Should `Icons.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.05839317165695705 - nodes in this community are weakly interconnected._
- **Why does `SketchEditor` connect `SketchEditor` to `Viewport`, `Constraint`, `Constraint`, `Text`, `Display`, `optional`, `PlaneEdges`, `Kind`, `Pick`, `Snap`, `Unit`, `SketchEditor.cpp`, `.updatePreview`, `SketchEditor::SketchEditor`, `Entity`, `Session`, `ViewportArrow.cpp`?**
  _High betweenness centrality (0.093) - this node is a cross-community bridge._
- **Should `tsr` be split into smaller, more focused modules?**
  _Cohesion score 0.06871035940803383 - nodes in this community are weakly interconnected._