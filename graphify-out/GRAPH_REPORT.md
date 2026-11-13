# Graph Report - tessera  (2026-11-13)

## Corpus Check
- 342 files · ~197,556 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 35 file(s) not represented in the graph (top: .drive 27, (none) 5, .cmake 1)

## Summary
- 3161 nodes · 7902 edges · 136 communities (105 shown, 31 thin omitted)
- Extraction: 85% EXTRACTED · 15% INFERRED · 0% AMBIGUOUS · INFERRED: 1224 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `ed64b8d2`
- Run `git rev-parse HEAD` and compare to check if the graph is stale.
- Run `graphify update .` after code changes (no API cost).

## Community Hubs (Navigation)
- Viewport
- Icons.cpp
- CommandDef
- tsr
- MainWindow
- run_oracle.py
- Inputs
- Document
- Viewport.cpp
- SketchEditor
- fromInternal
- optional
- Kernel.cpp
- .projectAt
- Kind
- MainWindowTools.cpp
- CommandDialog
- Io.cpp
- Unit
- DocCommands.cpp
- .press
- ConstructAxisPoint
- TEST
- Sketch.cpp
- ViewportSketch.cpp
- SketchPalette
- SketchEditor.cpp
- string
- AdskModule.cpp
- Colors
- KernelError
- SketchOps.cpp
- Session.cpp
- ParameterCompleter
- ViewportAnalysis.cpp
- CommandDialog.cpp
- Viewport.h
- solve
- MarkingMenu.cpp
- src/main.cpp
- ConstraintType
- TEST
- Pick
- Snap
- Kind
- Command
- AnalysisSettings
- Document.cpp
- Session
- MainWindowSketch.cpp
- InputDef
- .toPixels
- ViewportAnalysis.cpp
- .showDialog
- Theme.cpp
- UserParameter
- Constraint
- xdrive.py
- SketchGeometry.cpp
- MainWindow::MainWindow
- ViewportArrow.cpp
- string
- CommandRegistry
- DocCommands.h
- TopoDS_Shape
- Theme
- FileFormat
- .planeFrame
- ParametersDialog.cpp
- planeOf
- QTimer
- QString
- InputType
- SketchGeometry.cpp
- UiCommand
- Zip.h
- SketchDisplay
- string
- Measurement
- rect
- Entity
- Level
- README.md
- Document::recompute
- .openMarkingMenu
- cmath
- Known differences still to build
- .finishArcDrag
- .add
- Sketch.h
- BodyFrame
- FakeDoc
- .apply
- Zip.cpp
- .rebuild
- Kernel.h
- Document::load
- ParameterCompleter.cpp
- SketchRecord
- SectionState
- Display
- Handle
- .requireTransaction
- openWallBand
- ConstructionPoint
- ConstructionAxis
- main
- uninstall.sh
- install.sh
- Architecture
- Icons.h
- Feature
- smoke
- qs
- MarkingMenu
- Column
- Primitive
- Dimension
- Mesh
- ChainSegment
- LAB_NOTES.md
- build.sh
- live-test.sh

## God Nodes (most connected - your core abstractions)
1. `Viewport` - 227 edges
2. `MainWindow` - 172 edges
3. `SketchEditor` - 157 edges
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

## Communities (136 total, 31 thin omitted)

### Community 0 - "Viewport"
Cohesion: 0.02
Nodes (56): view_, Viewport, analysis_, analysisObjects_, appliedGridStep_, arrowBoxes_, arrowDragging_, arrowGrab_ (+48 more)

### Community 1 - "Icons.cpp"
Cohesion: 0.07
Nodes (91): arcIcon(), arrow(), axisIcon(), box(), centerRectIcon(), chamferIcon(), circleIcon(), coilIcon() (+83 more)

### Community 2 - "CommandDef"
Cohesion: 0.06
Nodes (24): CommandDef, feature, icon, id, inputs, name, nameInput, panel (+16 more)

### Community 4 - "MainWindow"
Cohesion: 0.03
Nodes (63): writeLiveGeometry(), CommandDialog, MainWindow, active_, arrowInput_, arrowInput2_, bodiesBeforeCommand_, combEdges_ (+55 more)

### Community 5 - "run_oracle.py"
Cohesion: 0.08
Nodes (54): add_point(), arc_poly(), body_at(), body_list(), build_sketch(), chain(), circumcentre(), cm() (+46 more)

### Community 6 - "Inputs"
Cohesion: 0.08
Nodes (18): CommandContext, CommandError, Inputs, CommandSession::CommandSession(), getBool(), bodyCentre(), bodyName(), defaultBody() (+10 more)

### Community 7 - "Document"
Cohesion: 0.03
Nodes (26): Body, display, name, shape, Component, bodies, name, Document (+18 more)

### Community 8 - "Viewport.cpp"
Cohesion: 0.05
Nodes (10): keys(), NavPreset, Fusion, SolidWorks, Tinkercad, qc(), rgb(), Viewport::Viewport() (+2 more)

### Community 9 - "SketchEditor"
Cohesion: 0.03
Nodes (41): SketchEditor, arcDrag_, arcDragMoved_, arcEndsChain_, arcFrom_, arcRef_, bodyEdges_, boxing_ (+33 more)

### Community 10 - "fromInternal"
Cohesion: 0.14
Nodes (13): MainWindow::checkInterference(), MainWindow::chooseUnits(), MainWindow::driveJoints(), MainWindow::formatLength(), MainWindow::gridSettings(), MainWindow::openAnalysis(), MainWindow::openSection(), MainWindow::updateMeasure() (+5 more)

### Community 13 - ".projectAt"
Cohesion: 0.29
Nodes (4): PlaneEdges, arcs, segments, vertices

### Community 14 - "Kind"
Cohesion: 0.07
Nodes (25): ConstructPlane, def_, kind_, EdgeFeature, def_, kind_, FaceFeature, def_ (+17 more)

### Community 15 - "MainWindowTools.cpp"
Cohesion: 0.06
Nodes (13): QDialog, MainWindow::exportDesign(), MainWindow::insertFile(), MainWindow::measurePick(), MainWindow::openMeasure(), MainWindow::print3d(), MainWindow::sectionFrame(), MainWindow::sectionPlane() (+5 more)

### Community 16 - "CommandDialog"
Cohesion: 0.05
Nodes (31): CommandDialog, bodiesId_, bodiesLabel_, bodyInput_, buttons_, cmd_, conditional_, edgesId_ (+23 more)

### Community 17 - "Io.cpp"
Cohesion: 0.12
Nodes (14): NamedShape, compoundOf(), exportShapes(), fmt(), formatForPath(), fromBrep(), importShape(), lower() (+6 more)

### Community 18 - "Unit"
Cohesion: 0.07
Nodes (46): MainWindow::lengthUnit(), ExpressionEnv, lengthUnit, lookup, ExpressionError, Quantity, angle, length (+38 more)

### Community 19 - "DocCommands.cpp"
Cohesion: 0.09
Nodes (19): axisOf(), CopyFn, differenceOrNull(), evaluateDimensions(), InsertGeometry, def_, openChains(), parsePoints() (+11 more)

### Community 21 - "ConstructAxisPoint"
Cohesion: 0.18
Nodes (5): ConstructAxisPoint, def_, kind_, JointPick, frame

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
Nodes (26): flatButton(), QCheckBox, QLabel, QToolButton, QWidget, SketchEditor, SketchPalette, body_ (+18 more)

### Community 27 - "SketchEditor.cpp"
Cohesion: 0.13
Nodes (3): angleInArc(), segDistance(), edges

### Community 28 - "string"
Cohesion: 0.09
Nodes (19): checkBody(), checkPattern(), Extrude, def_, Hole, def_, isIdentifier(), MoveCopy (+11 more)

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
Cohesion: 0.06
Nodes (42): CommandSession, inputs_, expressionKey(), checkInputValue(), CommandContext::evaluateExpression(), CommandDef::input(), CommandSession::applyInTransaction(), CommandSession::cancel() (+34 more)

### Community 34 - "ParameterCompleter"
Cohesion: 0.18
Nodes (8): QObject, ParameterCompleter, completer_, edit_, names_, public, QCompleter, QLineEdit

### Community 35 - "ViewportAnalysis.cpp"
Cohesion: 0.12
Nodes (5): packed(), ramp(), shade(), Viewport::buildAnalysis(), Viewport::setCurvatureComb()

### Community 37 - "Viewport.h"
Cohesion: 0.08
Nodes (7): MarkingMenu::keyPressEvent(), QKeyEvent, QLabel, QLineEdit, QMouseEvent, ViewInteractor, Viewport::setInteractor()

### Community 38 - "solve"
Cohesion: 0.18
Nodes (12): addConstraintChecked(), Layout, n, px, py, rad, makeLayout(), pack() (+4 more)

### Community 39 - "MarkingMenu.cpp"
Cohesion: 0.14
Nodes (6): MarkingMenu::MarkingMenu(), MarkingMenu::mouseMoveEvent(), MarkingMenu::paintEvent(), MarkingMenu::popupAt(), MarkingMenu::ringIndexAt(), MarkingMenu::run()

### Community 41 - "ConstraintType"
Cohesion: 0.09
Nodes (23): ConstraintType, Angle, Coincident, Collinear, Concentric, Diameter, Distance, Equal (+15 more)

### Community 42 - "TEST"
Cohesion: 0.09
Nodes (3): param(), TEST(), tmp()

### Community 43 - "Pick"
Cohesion: 0.09
Nodes (17): Hit, index, kind, Pick, bodyArc, bodyPoint, bodySegment, hit (+9 more)

### Community 44 - "Snap"
Cohesion: 0.11
Nodes (18): Snap, alignX, alignY, bodyArc, bodySegment, entity, fromX, fromY (+10 more)

### Community 45 - "Kind"
Cohesion: 0.09
Nodes (21): HudField, edit, editing, kind, locked, value, Kind, Angle (+13 more)

### Community 46 - "Command"
Cohesion: 0.16
Nodes (18): Adding a tool, Command, getReal(), makeBox(), makeCone(), makeCylinder(), makeSphere(), makeTorus() (+10 more)

### Community 47 - "AnalysisSettings"
Cohesion: 0.08
Nodes (21): AnalysisKind, CurvatureMap, Draft, None, Zebra, AnalysisSettings, curvatureScale, draftAngle (+13 more)

### Community 48 - "Document.cpp"
Cohesion: 0.09
Nodes (24): ConstructionPlane, name, spec, Document::axes(), Document::bodies(), Document::body(), Document::components(), Document::features() (+16 more)

### Community 49 - "Session"
Cohesion: 0.10
Nodes (7): PythonHost::PythonHost(), Session, commands_, doc_, listeners_, nextListener_, path_

### Community 50 - "MainWindowSketch.cpp"
Cohesion: 0.09
Nodes (12): MainWindow::cancelSketch(), MainWindow::editSketch(), MainWindow::finishSketch(), MainWindow::onProfileClicked(), MainWindow::originalShape(), MainWindow::sketchPalette(), MainWindow::sketchVisible(), MainWindow::startSketch() (+4 more)

### Community 51 - "InputDef"
Cohesion: 0.09
Nodes (21): InputDef, choices, defaultValue, id, label, max, min, minExclusive (+13 more)

### Community 54 - "ViewportAnalysis.cpp"
Cohesion: 0.12
Nodes (7): ArrowPlacement, base, dir, edgePlacement(), facesPlacement(), MainWindow::patternCentre(), MainWindow::pickedFaces()

### Community 56 - "Theme.cpp"
Cohesion: 0.19
Nodes (6): setIconTheme(), darkColors(), darkPalette(), darkStyleSheet(), lightColors(), lightStyleSheet()

### Community 57 - "UserParameter"
Cohesion: 0.33
Nodes (6): UserParameter, comment, expression, name, unit, value

### Community 58 - "Constraint"
Cohesion: 0.11
Nodes (17): Constraint, entities, expression, points, type, value, value2, SolveResult (+9 more)

### Community 59 - "xdrive.py"
Cohesion: 0.32
Nodes (14): button(), canvas(), click(), drag(), flush(), geometry(), key(), keycode() (+6 more)

### Community 61 - "SketchGeometry.cpp"
Cohesion: 0.18
Nodes (12): Profile, area, face, x, y, curve(), curves(), interiorPoint() (+4 more)

### Community 62 - "MainWindow::MainWindow"
Cohesion: 0.14
Nodes (3): PythonHost, MainWindow::MainWindow(), MainWindow::showPreferences()

### Community 63 - "ViewportArrow.cpp"
Cohesion: 0.08
Nodes (15): Viewport::frontEdgeOwner(), rgb(), segmentDistance(), Viewport::arrowAt(), Viewport::arrowMouseMove(), Viewport::arrowMousePress(), Viewport::arrowMouseRelease(), Viewport::arrowParam() (+7 more)

### Community 64 - "string"
Cohesion: 0.10
Nodes (30): completeEdgeReferences(), completeFaceReferences(), decode(), decodeFaces(), dot(), edgeReference(), EdgeSig, full (+22 more)

### Community 65 - "CommandRegistry"
Cohesion: 0.12
Nodes (4): CommandRegistry, cmds_, CommandRegistry::add(), TEST()

### Community 66 - "DocCommands.h"
Cohesion: 0.10
Nodes (12): Result, error, ok, output, captured(), PythonHost::exec(), PythonHost::runScript(), bindTsr() (+4 more)

### Community 67 - "TopoDS_Shape"
Cohesion: 0.15
Nodes (24): SurfacePoint, normal, point, Vec3, asSolid(), boundingBox(), edgeMidpoint(), edgesNear() (+16 more)

### Community 68 - "Theme"
Cohesion: 0.22
Nodes (4): Theme, colors_, public, styled_

### Community 69 - "FileFormat"
Cohesion: 0.17
Nodes (12): FileFormat, Brep, Iges, Obj, Step, Stl, ThreeMF, FormatInfo (+4 more)

### Community 70 - ".planeFrame"
Cohesion: 0.21
Nodes (6): Loft, def_, profilesOf(), profiles, Sweep, def_

### Community 71 - "ParametersDialog.cpp"
Cohesion: 0.09
Nodes (14): number(), ParametersDialog, building_, error_, listener_, ParametersDialog::ParametersDialog(), public, rebuildPending_ (+6 more)

### Community 72 - "planeOf"
Cohesion: 0.23
Nodes (9): applyOperation(), Coil, def_, planeOf(), SplitBody, def_, x, y (+1 more)

### Community 74 - "QString"
Cohesion: 0.11
Nodes (6): ExpressionSpinBox, eval_, expression_, shown_, formatNumber(), dimensionOf()

### Community 75 - "InputType"
Cohesion: 0.12
Nodes (17): InputType, Axis, Bodies, Body, Bool, Choice, Edges, Faces (+9 more)

### Community 77 - "UiCommand"
Cohesion: 0.13
Nodes (12): UiCommand, enabled, icon, id, name, panel, run, shortcut (+4 more)

### Community 79 - "Zip.h"
Cohesion: 0.13
Nodes (5): isEmpty(), Value, slurp(), TEST(), tmp()

### Community 80 - "SketchDisplay"
Cohesion: 0.13
Nodes (10): ProfileObject, index, sketch, SketchDisplay, construction, curves, frame, name (+2 more)

### Community 81 - "string"
Cohesion: 0.14
Nodes (16): bodyNumber(), Document::axisFrame(), Document::bodyName(), Document::component(), Document::componentOfBody(), Document::lengthUnit(), Document::nextAxisName(), Document::nextBodyName() (+8 more)

### Community 82 - "Measurement"
Cohesion: 0.09
Nodes (20): BoundingBox, max, min, Kind, Angle, Area, Length, Volume (+12 more)

### Community 83 - "rect"
Cohesion: 0.28
Nodes (3): SelectionBox, crossing, rect()

### Community 84 - "Entity"
Cohesion: 0.22
Nodes (9): Entity, a, b, center, construction, fit, projected, radius (+1 more)

### Community 85 - "Level"
Cohesion: 0.16
Nodes (13): debug(), error(), info(), Level, Debug, Error, Info, Warning (+5 more)

### Community 86 - "README.md"
Cohesion: 0.10
Nodes (16): Build, Conventions, Development, Tests, Known gaps, Reference parts, Fusion feature checklist, Roadmap (+8 more)

### Community 87 - "Document::recompute"
Cohesion: 0.21
Nodes (8): Document::openTransaction(), Document::recompute(), Document::recordFeature(), Document::removeFeature(), Document::setFeatureInputs(), Document::setFeatureSuppressed(), featureData(), toJson()

### Community 90 - ".openMarkingMenu"
Cohesion: 0.09
Nodes (4): MainWindow::beginSketch(), MainWindow::buildSketchTab(), MainWindow::enterSketchMode(), MainWindow::buildUiCommands()

### Community 91 - "cmath"
Cohesion: 0.14
Nodes (5): Case, name, fail(), Failure, Register

### Community 93 - "Known differences still to build"
Cohesion: 0.15
Nodes (12): Data and files, Findings from the videos, Fusion study list, Interface, Known differences still to build, Navigation and display, Selection and the canvas, Sketch (+4 more)

### Community 96 - "Sketch.h"
Cohesion: 0.18
Nodes (7): CommandRegistry::all(), EntityType, Arc, Circle, Line, Spline, isRound()

### Community 97 - "BodyFrame"
Cohesion: 0.15
Nodes (14): BodyFrame, diag, dx, dy, dz, x0, y0, z0 (+6 more)

### Community 98 - "FakeDoc"
Cohesion: 0.17
Nodes (6): FakeDoc, aborts, commits, items, open, snapshot

### Community 99 - ".apply"
Cohesion: 0.20
Nodes (5): getInt(), CircularPattern, def_, RectangularPattern, def_

### Community 100 - "Zip.cpp"
Cohesion: 0.19
Nodes (11): Entry, data, name, ZipError, crc32(), get16(), get32(), put16() (+3 more)

### Community 101 - ".rebuild"
Cohesion: 0.27
Nodes (5): fixedColor(), freeColor(), qc(), rgb(), wire()

### Community 102 - "Kernel.h"
Cohesion: 0.12
Nodes (15): Axis, X, Y, Z, BooleanOp, Cut, Intersect, Join (+7 more)

### Community 103 - "Document::load"
Cohesion: 0.11
Nodes (8): doc_(), Document::Document(), Document::ocafBytes(), Document::parameterUsers(), Document::reevaluateParameters(), ocafApplication(), Document::load(), Document::save()

### Community 105 - "SketchRecord"
Cohesion: 0.25
Nodes (8): SketchRecord, data, name, offset, plane, Document::setSketch(), Document::sketch(), Document::sketches()

### Community 106 - "SectionState"
Cohesion: 0.25
Nodes (7): SectionState, active, angle, flip, offset, plane, visible

### Community 107 - "Display"
Cohesion: 0.25
Nodes (7): Display, constraints, construction, dimensions, points, profiles, projected

### Community 109 - ".requireTransaction"
Cohesion: 0.12
Nodes (18): DocumentError, Document::abortTransaction(), Document::addBody(), Document::addUserParameter(), Document::bodyShapes(), Document::commitTransaction(), Document::effectOf(), Document::removeBody() (+10 more)

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

### Community 116 - "Architecture"
Cohesion: 0.40
Nodes (4): Architecture, How a command works, The document, Units

### Community 118 - "Feature"
Cohesion: 0.22
Nodes (9): Feature, commandId, error, id, inputs, name, rolledBack, suppressed (+1 more)

### Community 123 - "smoke"
Cohesion: 0.40
Nodes (5): smoke(), MassProperties, area, centerOfMass, volume

### Community 124 - "qs"
Cohesion: 0.26
Nodes (4): commandIcon(), qs(), MainWindow::exitSketchMode(), MainWindow::applySection()

### Community 125 - "MarkingMenu"
Cohesion: 0.40
Nodes (3): MarkingMenu, enabled, public

### Community 126 - "Column"
Cohesion: 0.33
Nodes (6): Column, kComment, kExpression, kParameter, kUnit, kValue

### Community 127 - "Primitive"
Cohesion: 0.50
Nodes (3): Primitive, build_, def_

### Community 128 - "Dimension"
Cohesion: 0.50
Nodes (4): Dimension, Angle, Length, Unitless

### Community 129 - "Mesh"
Cohesion: 0.40
Nodes (3): Mesh, nodes, triangles

### Community 132 - "ChainSegment"
Cohesion: 0.67
Nodes (3): ChainSegment, entity, forward

## Knowledge Gaps
- **640 isolated node(s):** `ok`, `output`, `error`, `isReal`, `real` (+635 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 1212 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **31 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `Viewport` connect `Viewport` to `ViewportAnalysis.cpp`, `MainWindow`, `Viewport.h`, `Viewport.cpp`, `QTimer`, `fromInternal`, `optional`, `Handle`, `AnalysisSettings`, `SketchDisplay`, `rect`, `.toPixels`, `.selectedSubShapes`, `ViewportArrow.cpp`?**
  _High betweenness centrality (0.120) - this node is a cross-community bridge._
- **What connects `ok`, `output`, `error` to the rest of the system?**
  _640 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Viewport` be split into smaller, more focused modules?**
  _Cohesion score 0.01815408085430969 - nodes in this community are weakly interconnected._
- **Why does `optional` connect `optional` to `Viewport`, `MainWindow`, `Kernel.cpp`, `Io.cpp`, `Unit`, `DocCommands.cpp`, `.press`, `ViewportSketch.cpp`, `SketchEditor.cpp`, `string`, `SketchOps.cpp`, `CommandDialog.cpp`, `Viewport.h`, `AnalysisSettings`, `Document.cpp`, `Session`, `InputDef`, `ViewportAnalysis.cpp`, `ViewportArrow.cpp`, `TopoDS_Shape`, `QString`, `string`, `.rebuild`, `Kernel.h`, `SketchRecord`, `ConstructionPoint`, `ConstructionAxis`, `Feature`?**
  _High betweenness centrality (0.119) - this node is a cross-community bridge._
- **Should `Icons.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.06853038245000971 - nodes in this community are weakly interconnected._
- **Why does `MainWindow` connect `MainWindow` to `ParameterCompleter`, `.openMarkingMenu`, `SectionState`, `optional`, `fromInternal`, `UiCommand`, `MainWindowTools.cpp`, `Session`, `MainWindowSketch.cpp`, `MainWindow.cpp`, `.showDialog`, `SketchPalette`, `smoke`, `qs`, `MainWindow::MainWindow`?**
  _High betweenness centrality (0.097) - this node is a cross-community bridge._
- **Should `CommandDef` be split into smaller, more focused modules?**
  _Cohesion score 0.06439393939393939 - nodes in this community are weakly interconnected._