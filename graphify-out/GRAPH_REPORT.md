# Graph Report - tessera  (2026-11-13)

## Corpus Check
- 353 files · ~212,347 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 42 file(s) not represented in the graph (top: .drive 34, (none) 5, .cmake 1)

## Summary
- 3267 nodes · 8265 edges · 139 communities (108 shown, 31 thin omitted)
- Extraction: 84% EXTRACTED · 16% INFERRED · 0% AMBIGUOUS · INFERRED: 1300 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `8ab2d9d4`
- Run `git rev-parse HEAD` and compare to check if the graph is stale.
- Run `graphify update .` after code changes (no API cost).

## Community Hubs (Navigation)
- Viewport
- Icons.cpp
- ConstructAxisPoint
- MainWindow
- run_oracle.py
- CommandContext
- Document
- Viewport.cpp
- SketchEditor
- QString
- optional
- Kernel.cpp
- sketchFor
- Kind
- MainWindowTools.cpp
- CommandDialog
- Io.cpp
- Quantity
- src/main.cpp
- CommandDialog::CommandDialog
- SketchEditor.cpp
- TEST
- Sketch.cpp
- ViewportSketch.cpp
- SketchPalette
- Command
- SketchProfiles
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
- ViewportAnalysis.cpp
- Constraint
- ConstraintType
- TEST
- Pick
- Parser
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
- DocCommands.h
- ViewportArrow.cpp
- string
- CommandRegistry
- cmath
- TopoDS_Shape
- Theme
- FileFormat
- .apply
- src/main.cpp
- CommandSession
- QTimer
- Profile
- InputType
- Feature
- Command.cpp
- math
- Value.h
- SketchDisplay
- PYBIND11_EMBEDDED_MODULE
- Measurement
- Expression.cpp
- Axis
- Level
- README.md
- Document.cpp
- test_feature_pattern.py
- SketchEditor::SketchEditor
- UserParameter
- UiCommand
- Known differences still to build
- ChainSegment
- Document::recompute
- MarkingMenu
- BodyFrame
- FakeDoc
- TEST
- Zip.cpp
- planeOf
- OcafApp.h
- Document::reevaluateParameters
- SketchRecord
- TEST
- SectionState
- Display
- Dimension
- openWallBand
- ConstructionPoint
- ConstructionAxis
- main
- uninstall.sh
- install.sh
- Mesh
- FeatureEffect
- BooleanOp
- MainWindow::enterSketchMode
- ThreadInfo
- cmath
- Placement
- bindAdsk
- SelectionBox
- Column
- Joints
- MainWindow::setSelectionFilter
- ChamferType
- Session::addListener
- Session::notifyChanged
- LAB_NOTES.md
- Placement::apply
- build.sh
- live-test.sh

## God Nodes (most connected - your core abstractions)
1. `Viewport` - 227 edges
2. `SketchEditor` - 174 edges
3. `MainWindow` - 172 edges
4. `Inputs` - 136 edges
5. `Document` - 128 edges
6. `CommandContext` - 102 edges
7. `render()` - 100 edges
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

## Communities (139 total, 31 thin omitted)

### Community 0 - "Viewport"
Cohesion: 0.02
Nodes (57): view_, QLineEdit, Viewport, analysis_, analysisObjects_, appliedGridStep_, arrowBoxes_, arrowDragging_ (+49 more)

### Community 1 - "Icons.cpp"
Cohesion: 0.06
Nodes (106): arc3Icon(), arcIcon(), arrow(), axisIcon(), box(), centerRectIcon(), chamferIcon(), circle2Icon() (+98 more)

### Community 2 - "ConstructAxisPoint"
Cohesion: 0.16
Nodes (6): ConstructAxisPoint, def_, kind_, differenceOrNull(), JointPick, frame

### Community 4 - "MainWindow"
Cohesion: 0.03
Nodes (62): CommandDialog, MainWindow, active_, arrowInput_, arrowInput2_, bodiesBeforeCommand_, combEdges_, combPicking_ (+54 more)

### Community 5 - "run_oracle.py"
Cohesion: 0.08
Nodes (54): add_point(), arc_poly(), body_at(), body_list(), build_sketch(), chain(), circumcentre(), cm() (+46 more)

### Community 6 - "CommandContext"
Cohesion: 0.04
Nodes (49): CommandDef, feature, icon, id, inputs, name, nameInput, panel (+41 more)

### Community 7 - "Document"
Cohesion: 0.04
Nodes (12): Document, effects_, modified_, pendingTools_, registry_, replaying_, txnBodies_, FromOcaf (+4 more)

### Community 8 - "Viewport.cpp"
Cohesion: 0.05
Nodes (11): MarkingMenu::keyPressEvent(), keys(), NavPreset, Fusion, SolidWorks, Tinkercad, qc(), QKeyEvent (+3 more)

### Community 9 - "SketchEditor"
Cohesion: 0.03
Nodes (49): PlaneEdges, arcs, segments, vertices, SketchEditor, arcDrag_, arcDragMoved_, arcEndsChain_ (+41 more)

### Community 10 - "QString"
Cohesion: 0.12
Nodes (5): ExpressionSpinBox, eval_, expression_, shown_, formatNumber()

### Community 13 - "sketchFor"
Cohesion: 0.16
Nodes (13): applyOperation(), CopyFn, Hole, def_, PathPattern, def_, patternFeatures(), placeCopies() (+5 more)

### Community 14 - "Kind"
Cohesion: 0.09
Nodes (22): EdgeFeature, def_, kind_, FaceFeature, def_, kind_, Kind, Angle (+14 more)

### Community 15 - "MainWindowTools.cpp"
Cohesion: 0.07
Nodes (25): QDialog, MainWindow::checkInterference(), MainWindow::chooseUnits(), MainWindow::driveJoints(), MainWindow::exportDesign(), MainWindow::formatLength(), MainWindow::gridSettings(), MainWindow::insertFile() (+17 more)

### Community 16 - "CommandDialog"
Cohesion: 0.05
Nodes (31): CommandDialog, bodiesId_, bodiesLabel_, bodyInput_, buttons_, cmd_, conditional_, edgesId_ (+23 more)

### Community 17 - "Io.cpp"
Cohesion: 0.11
Nodes (15): MainWindow::print3d(), NamedShape, compoundOf(), exportShapes(), fmt(), formatForPath(), fromBrep(), importShape() (+7 more)

### Community 18 - "Quantity"
Cohesion: 0.28
Nodes (9): ExpressionError, Quantity, angle, length, value, describe(), evaluateExpression(), quantityOf() (+1 more)

### Community 19 - "src/main.cpp"
Cohesion: 0.09
Nodes (8): grabWindowWithPanels(), main(), smoke(), writeLiveGeometry(), MassProperties, area, centerOfMass, volume

### Community 22 - "SketchEditor.cpp"
Cohesion: 0.14
Nodes (4): angleInArc(), ccwContains(), circumcircle(), segDistance()

### Community 23 - "TEST"
Cohesion: 0.08
Nodes (7): Sketch, constraints, entities, points, texts, Sketch::addCircle(), TEST()

### Community 24 - "Sketch.cpp"
Cohesion: 0.09
Nodes (17): Point, x, y, SketchError, entityTypeName(), isDimension(), Sketch::addSpline(), Sketch::addText() (+9 more)

### Community 25 - "ViewportSketch.cpp"
Cohesion: 0.05
Nodes (7): QLabel, faceStyle(), lineStyle(), rgb(), Viewport::lookAt(), Viewport::planePoint(), Viewport::toWidget()

### Community 26 - "SketchPalette"
Cohesion: 0.06
Nodes (26): flatButton(), QCheckBox, QLabel, QToolButton, QWidget, SketchEditor, SketchPalette, body_ (+18 more)

### Community 27 - "Command"
Cohesion: 0.16
Nodes (18): Adding a tool, Command, getReal(), makeBox(), makeCone(), makeCylinder(), makeSphere(), makeTorus() (+10 more)

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
Cohesion: 0.20
Nodes (26): at(), chainOf(), chamferCorner(), circularPattern(), copyEntities(), cornerAt(), cross(), dot() (+18 more)

### Community 33 - "Session.cpp"
Cohesion: 0.19
Nodes (18): historyEdit(), Session::deleteFeature(), Session::deleteParameter(), Session::editFeature(), Session::newDocument(), Session::open(), Session::redo(), Session::renameBody() (+10 more)

### Community 34 - "ParameterCompleter"
Cohesion: 0.12
Nodes (8): ParameterCompleter, completer_, edit_, names_, ParameterCompleter::ParameterCompleter(), public, QCompleter, QLineEdit

### Community 35 - "Unit"
Cohesion: 0.14
Nodes (16): Unit, Centimeter, Degree, Foot, Inch, Meter, Millimeter, None (+8 more)

### Community 37 - "MainWindow::MainWindow"
Cohesion: 0.13
Nodes (4): PythonHost, MainWindow::MainWindow(), MainWindow::exitSketchMode(), MainWindow::showPreferences()

### Community 38 - "solve"
Cohesion: 0.18
Nodes (12): addConstraintChecked(), Layout, n, px, py, rad, makeLayout(), pack() (+4 more)

### Community 39 - "ViewportAnalysis.cpp"
Cohesion: 0.13
Nodes (5): packed(), ramp(), shade(), Viewport::buildAnalysis(), Viewport::setCurvatureComb()

### Community 40 - "Constraint"
Cohesion: 0.06
Nodes (26): Constraint, driven, entities, expression, hasLabel, labelX, labelY, name (+18 more)

### Community 41 - "ConstraintType"
Cohesion: 0.08
Nodes (24): ConstraintType, Angle, Coincident, Collinear, Concentric, Diameter, Distance, Equal (+16 more)

### Community 42 - "TEST"
Cohesion: 0.05
Nodes (10): PythonHost::PythonHost(), Session, commands_, doc_, listeners_, nextListener_, path_, param() (+2 more)

### Community 43 - "Pick"
Cohesion: 0.10
Nodes (17): Hit, index, kind, Pick, bodyArc, bodyPoint, bodySegment, hit (+9 more)

### Community 44 - "Parser"
Cohesion: 0.21
Nodes (9): isIdentChar(), isIdentStart(), Parser, ang_, env_, len_, pos_, refs_ (+1 more)

### Community 45 - "Kind"
Cohesion: 0.05
Nodes (39): HudField, edit, editing, kind, locked, value, Kind, Angle (+31 more)

### Community 46 - "Inputs"
Cohesion: 0.08
Nodes (13): CommandContext, CommandError, Inputs, CommandSession::CommandSession(), getBool(), getInt(), bodyCentre(), bodyName() (+5 more)

### Community 47 - "AnalysisSettings"
Cohesion: 0.08
Nodes (21): AnalysisKind, CurvatureMap, Draft, None, Zebra, AnalysisSettings, curvatureScale, draftAngle (+13 more)

### Community 48 - "Document.cpp"
Cohesion: 0.08
Nodes (35): ConstructionPlane, name, spec, bodyNumber(), Document::abortTransaction(), Document::axes(), Document::bodies(), Document::body() (+27 more)

### Community 50 - "MainWindowSketch.cpp"
Cohesion: 0.07
Nodes (16): MainWindow::cancelSketch(), MainWindow::editSketch(), MainWindow::finishSketch(), MainWindow::onEdgeClicked(), MainWindow::onProfileClicked(), MainWindow::originalShape(), MainWindow::sketchPalette(), MainWindow::sketchVisible() (+8 more)

### Community 51 - "InputDef"
Cohesion: 0.08
Nodes (24): InputDef, choices, defaultValue, id, label, max, min, minExclusive (+16 more)

### Community 54 - "ViewportAnalysis.cpp"
Cohesion: 0.10
Nodes (9): ArrowPlacement, base, dir, edgePlacement(), facesPlacement(), MainWindow::attachArrowCompleters(), MainWindow::patternCentre(), MainWindow::pickedFaces() (+1 more)

### Community 55 - ".rebuild"
Cohesion: 0.14
Nodes (7): ext(), fixedColor(), freeColor(), qc(), rgb(), wire(), Sketch::addLine()

### Community 56 - "Theme.cpp"
Cohesion: 0.19
Nodes (6): setIconTheme(), darkColors(), darkPalette(), darkStyleSheet(), lightColors(), lightStyleSheet()

### Community 57 - "MainWindow.cpp"
Cohesion: 0.08
Nodes (4): commandIcon(), qs(), MainWindow::beginSketch(), MainWindow::applySection()

### Community 58 - "Entity"
Cohesion: 0.12
Nodes (16): Entity, a, b, center, construction, fit, projected, radius (+8 more)

### Community 59 - "xdrive.py"
Cohesion: 0.32
Nodes (14): button(), canvas(), click(), drag(), flush(), geometry(), key(), keycode() (+6 more)

### Community 61 - "SketchGeometry.cpp"
Cohesion: 0.12
Nodes (11): curve(), curves(), customPlaneSpec(), entityCurves(), interiorPoint(), planeFrame(), profileAt(), profiles() (+3 more)

### Community 62 - "DocCommands.h"
Cohesion: 0.33
Nodes (4): bindTsr(), fromPy(), toPy(), typeName()

### Community 63 - "ViewportArrow.cpp"
Cohesion: 0.06
Nodes (22): MarkingMenu::mouseMoveEvent(), QMouseEvent, ViewInteractor, Viewport::frontEdgeOwner(), rgb(), segmentDistance(), Viewport::arrowAt(), Viewport::arrowMouseMove() (+14 more)

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

### Community 70 - ".apply"
Cohesion: 0.16
Nodes (10): Coil, def_, Extrude, def_, Revolve, def_, validateOperation(), x (+2 more)

### Community 71 - "src/main.cpp"
Cohesion: 0.09
Nodes (13): number(), ParametersDialog, building_, error_, listener_, ParametersDialog::ParametersDialog(), public, rebuildPending_ (+5 more)

### Community 72 - "CommandSession"
Cohesion: 0.12
Nodes (8): CommandSession, inputs_, CommandRegistry::find(), CommandRegistry::run(), OwnedCommand, owned, OwningCommandSession, Session::begin()

### Community 74 - "Profile"
Cohesion: 0.33
Nodes (5): Profile, area, face, x, y

### Community 75 - "InputType"
Cohesion: 0.12
Nodes (17): InputType, Axis, Bodies, Body, Bool, Choice, Edges, Faces (+9 more)

### Community 76 - "Feature"
Cohesion: 0.14
Nodes (15): Feature, commandId, error, id, inputs, name, rolledBack, suppressed (+7 more)

### Community 77 - "Command.cpp"
Cohesion: 0.22
Nodes (11): expressionKey(), checkInputValue(), CommandContext::evaluateExpression(), CommandDef::input(), CommandSession::applyInTransaction(), CommandSession::cancel(), CommandSession::execute(), CommandSession::preview() (+3 more)

### Community 80 - "SketchDisplay"
Cohesion: 0.13
Nodes (10): ProfileObject, index, sketch, SketchDisplay, construction, curves, frame, name (+2 more)

### Community 82 - "Measurement"
Cohesion: 0.09
Nodes (20): BoundingBox, max, min, Kind, Angle, Area, Length, Volume (+12 more)

### Community 83 - "Expression.cpp"
Cohesion: 0.24
Nodes (9): ExpressionEnv, lengthUnit, lookup, evaluateQuantity(), expressionReferences(), isConstantName(), isFunctionName(), isPlainQuantity() (+1 more)

### Community 84 - "Axis"
Cohesion: 0.50
Nodes (4): Axis, X, Y, Z

### Community 85 - "Level"
Cohesion: 0.16
Nodes (13): debug(), error(), info(), Level, Debug, Error, Info, Warning (+5 more)

### Community 86 - "README.md"
Cohesion: 0.08
Nodes (20): Architecture, How a command works, The document, Units, Build, Conventions, Development, Tests (+12 more)

### Community 87 - "Document.cpp"
Cohesion: 0.15
Nodes (22): DocumentError, Document::addBody(), Document::addUserParameter(), Document::axisFrame(), Document::bodyShapes(), Document::effectOf(), Document::evaluate(), Document::ocafBytes() (+14 more)

### Community 89 - "SketchEditor::SketchEditor"
Cohesion: 0.11
Nodes (7): QObject, SketchEditor::SketchEditor(), edges, Tool, op, shape, target

### Community 90 - "UserParameter"
Cohesion: 0.33
Nodes (6): UserParameter, comment, expression, name, unit, value

### Community 91 - "UiCommand"
Cohesion: 0.10
Nodes (14): UiCommand, enabled, icon, id, name, panel, run, shortcut (+6 more)

### Community 93 - "Known differences still to build"
Cohesion: 0.15
Nodes (12): Data and files, Findings from the videos, Fusion study list, Interface, Known differences still to build, Navigation and display, Selection and the canvas, Sketch (+4 more)

### Community 94 - "ChainSegment"
Cohesion: 0.67
Nodes (3): ChainSegment, entity, forward

### Community 95 - "Document::recompute"
Cohesion: 0.23
Nodes (7): Document::recompute(), Document::recordFeature(), Document::removeFeature(), Document::setFeatureInputs(), Document::setFeatureSuppressed(), featureData(), toJson()

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
Cohesion: 0.12
Nodes (6): Entry, data, name, slurp(), TEST(), tmp()

### Community 100 - "Zip.cpp"
Cohesion: 0.28
Nodes (8): ZipError, crc32(), get16(), get32(), put16(), put32(), read(), write()

### Community 101 - "planeOf"
Cohesion: 0.21
Nodes (6): ConstructPlane, def_, kind_, evaluateDimensions(), openChains(), planeOf()

### Community 102 - "OcafApp.h"
Cohesion: 0.18
Nodes (4): doc_(), Document::Document(), ocafApplication(), Document::load()

### Community 103 - "Document::reevaluateParameters"
Cohesion: 0.28
Nodes (4): Document::expressionEnv(), Document::parameterUsers(), Document::reevaluateParameters(), Document::save()

### Community 104 - "SketchRecord"
Cohesion: 0.25
Nodes (7): SketchRecord, data, name, offset, plane, Document::sketch(), utf8()

### Community 105 - "TEST"
Cohesion: 0.24
Nodes (3): env(), mm(), TEST()

### Community 106 - "SectionState"
Cohesion: 0.25
Nodes (7): SectionState, active, angle, flip, offset, plane, visible

### Community 107 - "Display"
Cohesion: 0.25
Nodes (7): Display, constraints, construction, dimensions, points, profiles, projected

### Community 108 - "Dimension"
Cohesion: 0.50
Nodes (4): Dimension, Angle, Length, Unitless

### Community 110 - "openWallBand"
Cohesion: 0.15
Nodes (19): Section, Circular, Square, Triangular, TopologyCounts, edges, faces, shells (+11 more)

### Community 111 - "ConstructionPoint"
Cohesion: 0.33
Nodes (4): ConstructionPoint, name, point, Document::point()

### Community 112 - "ConstructionAxis"
Cohesion: 0.29
Nodes (5): ConstructionAxis, axis, name, Document::axis(), Document::setAxis()

### Community 113 - "main"
Cohesion: 0.28
Nodes (3): listCommands(), main(), usage()

### Community 114 - "uninstall.sh"
Cohesion: 0.52
Nodes (6): die(), manifest_for(), refresh(), uninstall.sh script, step(), usage()

### Community 115 - "install.sh"
Cohesion: 0.60
Nodes (5): die(), refresh(), install.sh script, step(), usage()

### Community 117 - "Mesh"
Cohesion: 0.40
Nodes (3): Mesh, nodes, triangles

### Community 118 - "FeatureEffect"
Cohesion: 0.09
Nodes (18): Body, display, name, shape, Component, bodies, name, FeatureEffect (+10 more)

### Community 119 - "BooleanOp"
Cohesion: 0.50
Nodes (4): BooleanOp, Cut, Intersect, Join

### Community 121 - "ThreadInfo"
Cohesion: 0.50
Nodes (4): ThreadInfo, diameter, internal, pitch

### Community 122 - "cmath"
Cohesion: 0.14
Nodes (8): Rect, rect(), p, Case, name, fail(), Failure, Register

### Community 123 - "Placement"
Cohesion: 0.25
Nodes (7): Placement, angle, cx, cy, dx, dy, scale

### Community 124 - "bindAdsk"
Cohesion: 0.29
Nodes (3): bindAdsk(), BRepBody, index

### Community 126 - "Column"
Cohesion: 0.33
Nodes (6): Column, kComment, kExpression, kParameter, kUnit, kValue

### Community 130 - "ChamferType"
Cohesion: 0.67
Nodes (3): ChamferType, DistanceAngle, TwoDistances

## Knowledge Gaps
- **664 isolated node(s):** `ok`, `output`, `error`, `isReal`, `real` (+659 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 1251 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **31 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `Viewport` connect `Viewport` to `MainWindow`, `ViewportAnalysis.cpp`, `Viewport.cpp`, `QTimer`, `optional`, `AnalysisSettings`, `SketchDisplay`, `MainWindowTools.cpp`, `.toPixels`, `ViewportSketch.cpp`, `.selectedSubShapes`, `SelectionBox`, `ViewportArrow.cpp`?**
  _High betweenness centrality (0.107) - this node is a cross-community bridge._
- **What connects `ok`, `output`, `error` to the rest of the system?**
  _664 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Viewport` be split into smaller, more focused modules?**
  _Cohesion score 0.01761278959490584 - nodes in this community are weakly interconnected._
- **Why does `optional` connect `optional` to `Viewport`, `MainWindow`, `CommandContext`, `Document`, `QString`, `Kernel.cpp`, `sketchFor`, `Io.cpp`, `.solveAndShow`, `SketchEditor.cpp`, `ViewportSketch.cpp`, `SketchOps.cpp`, `Unit`, `CommandDialog.cpp`, `Constraint`, `TEST`, `Parser`, `AnalysisSettings`, `Document.cpp`, `InputDef`, `ViewportAnalysis.cpp`, `.rebuild`, `ViewportArrow.cpp`, `TopoDS_Shape`, `Feature`, `Expression.cpp`, `SketchRecord`, `ConstructionPoint`, `ConstructionAxis`?**
  _High betweenness centrality (0.104) - this node is a cross-community bridge._
- **Should `Icons.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.060698247138925104 - nodes in this community are weakly interconnected._
- **Why does `SketchEditor` connect `SketchEditor` to `Viewport`, `Unit`, `Constraint`, `TEST`, `Display`, `optional`, `Kind`, `Pick`, `.solveAndShow`, `SketchEditor.cpp`, `.rebuild`, `SketchEditor::SketchEditor`, `ViewportArrow.cpp`?**
  _High betweenness centrality (0.097) - this node is a cross-community bridge._
- **Should `tsr` be split into smaller, more focused modules?**
  _Cohesion score 0.07439024390243902 - nodes in this community are weakly interconnected._