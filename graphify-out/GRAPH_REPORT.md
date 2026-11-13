# Graph Report - tessera  (2026-11-13)

## Corpus Check
- 339 files · ~196,572 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 33 file(s) not represented in the graph (top: .drive 25, (none) 5, .cmake 1)

## Summary
- 3154 nodes · 7892 edges · 129 communities (101 shown, 28 thin omitted)
- Extraction: 84% EXTRACTED · 16% INFERRED · 0% AMBIGUOUS · INFERRED: 1224 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `134ed332`
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
- Dimension
- cmath
- .projectAt
- Kind
- MainWindowTools.cpp
- CommandDialog
- Io.cpp
- Unit
- Profile
- .updatePreview
- ViewportArrow.cpp
- MainWindow.cpp
- TEST
- Sketch.cpp
- ViewportSketch.cpp
- SketchPalette
- .motion
- AdskModule.cpp
- Colors
- TopoDS_Shape
- SketchOps.cpp
- Session.cpp
- ParameterCompleter
- ViewportAnalysis.cpp
- Viewport.h
- solve
- MarkingMenu.cpp
- src/main.cpp
- ConstraintType
- TEST
- Pick
- Snap
- Kind
- .press
- Command.cpp
- Document.cpp
- Session
- MainWindowSketch.cpp
- CommandDialog.h
- InputDef
- .toPixels
- ViewportAnalysis.cpp
- CommandSession
- Theme.cpp
- FeatureEffect
- Constraint
- xdrive.py
- SketchGeometry.cpp
- fail
- QTimer
- EdgeSig
- CommandRegistry
- PythonHost.cpp
- Vec3
- Theme
- FileFormat
- CommandDialog.cpp
- ParametersDialog.cpp
- string
- UiCommand
- QString
- InputType
- NavPreset
- CommandRegistry::run
- TEST
- SketchDisplay
- string
- Measurement
- rect
- Entity
- Level
- README.md
- Handle
- CommandDialog::CommandDialog
- EntityType
- Known differences still to build
- SketchEditor::SketchEditor
- .add
- TsrModule.cpp
- BodyFrame
- FakeDoc
- CommandError
- Zip.cpp
- Log.h
- Kernel.h
- DocumentError
- Development
- optional
- SectionState
- Display
- ConstructionPlane
- .requireTransaction
- openWallBand
- Rect
- ConstructionPoint
- main
- uninstall.sh
- install.sh
- .bodies
- Session::addListener
- functional
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

## Communities (129 total, 28 thin omitted)

### Community 0 - "Viewport"
Cohesion: 0.02
Nodes (56): view_, Viewport, analysis_, analysisObjects_, appliedGridStep_, arrowBoxes_, arrowDragging_, arrowGrab_ (+48 more)

### Community 1 - "Icons.cpp"
Cohesion: 0.07
Nodes (91): arcIcon(), arrow(), axisIcon(), box(), centerRectIcon(), chamferIcon(), circleIcon(), coilIcon() (+83 more)

### Community 2 - "DocCommands.cpp"
Cohesion: 0.04
Nodes (65): Adding a tool, Command, CommandDef, feature, icon, id, inputs, name (+57 more)

### Community 4 - "MainWindow"
Cohesion: 0.03
Nodes (62): CommandDialog, MainWindow, active_, arrowInput_, arrowInput2_, bodiesBeforeCommand_, combEdges_, combPicking_ (+54 more)

### Community 5 - "run_oracle.py"
Cohesion: 0.08
Nodes (54): add_point(), arc_poly(), body_at(), body_list(), build_sketch(), chain(), circumcentre(), cm() (+46 more)

### Community 6 - "Inputs"
Cohesion: 0.07
Nodes (18): CommandContext, Inputs, CommandSession::CommandSession(), checkBody(), checkPattern(), defaultBody(), Hole, def_ (+10 more)

### Community 7 - "Document"
Cohesion: 0.04
Nodes (14): Document, effects_, modified_, pendingTools_, registry_, replaying_, txnBodies_, FromOcaf (+6 more)

### Community 8 - "Viewport.cpp"
Cohesion: 0.06
Nodes (8): keys(), qc(), rgb(), Viewport::frontEdgeOwner(), Viewport::Viewport(), Viewport::clearDragArrow(), Viewport::clearSecondArrow(), Viewport::setInteractor()

### Community 9 - "SketchEditor"
Cohesion: 0.03
Nodes (41): SketchEditor, arcDrag_, arcDragMoved_, arcEndsChain_, arcFrom_, arcRef_, bodyEdges_, boxing_ (+33 more)

### Community 10 - "Dimension"
Cohesion: 0.50
Nodes (4): Dimension, Angle, Length, Unitless

### Community 13 - ".projectAt"
Cohesion: 0.29
Nodes (4): PlaneEdges, arcs, segments, vertices

### Community 14 - "Kind"
Cohesion: 0.08
Nodes (22): ConstructPlane, def_, kind_, EdgeFeature, def_, kind_, Kind, Angle (+14 more)

### Community 15 - "MainWindowTools.cpp"
Cohesion: 0.05
Nodes (28): QDialog, MainWindow::applySection(), MainWindow::checkInterference(), MainWindow::chooseUnits(), MainWindow::driveJoints(), MainWindow::exportDesign(), MainWindow::formatLength(), MainWindow::gridSettings() (+20 more)

### Community 16 - "CommandDialog"
Cohesion: 0.05
Nodes (27): CommandDialog, bodiesId_, bodiesLabel_, bodyInput_, buttons_, cmd_, conditional_, edgesId_ (+19 more)

### Community 17 - "Io.cpp"
Cohesion: 0.10
Nodes (17): NamedShape, compoundOf(), exportShapes(), fmt(), formatForPath(), fromBrep(), importShape(), lower() (+9 more)

### Community 18 - "Unit"
Cohesion: 0.07
Nodes (47): MainWindow::lengthUnit(), ExpressionEnv, lengthUnit, lookup, ExpressionError, Quantity, angle, length (+39 more)

### Community 19 - "Profile"
Cohesion: 0.33
Nodes (5): Profile, area, face, x, y

### Community 20 - ".updatePreview"
Cohesion: 0.15
Nodes (7): ext(), fixedColor(), freeColor(), qc(), rgb(), wire(), Sketch::addLine()

### Community 21 - "ViewportArrow.cpp"
Cohesion: 0.14
Nodes (6): rgb(), segmentDistance(), Viewport::arrowAt(), Viewport::arrowParam(), Viewport::dragArrowHandle(), Viewport::placeArrowBoxes()

### Community 22 - "MainWindow.cpp"
Cohesion: 0.05
Nodes (8): commandIcon(), MainWindow::MainWindow(), qs(), run, MainWindow::beginSketch(), MainWindow::enterSketchMode(), MainWindow::exitSketchMode(), MarkingMenu::triggerForTest()

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
Nodes (27): flatButton(), MainWindow::buildSketchTab(), QCheckBox, QLabel, QToolButton, QWidget, SketchEditor, SketchPalette (+19 more)

### Community 28 - ".motion"
Cohesion: 0.19
Nodes (5): Coil, def_, Joint, def_, jointOrigin()

### Community 29 - "AdskModule.cpp"
Cohesion: 0.10
Nodes (16): Application, bindAdsk(), BRepBodies, BRepBody, index, Component, Design, Product (+8 more)

### Community 30 - "Colors"
Cohesion: 0.07
Nodes (28): Colors, base, border, cubeBox, cubeText, errorBackground, grid, gridMajor (+20 more)

### Community 31 - "TopoDS_Shape"
Cohesion: 0.15
Nodes (33): KernelError, edges, faces, vertices, asSolid(), chamfer(), chamferEx(), decode() (+25 more)

### Community 32 - "SketchOps.cpp"
Cohesion: 0.21
Nodes (19): at(), chainOf(), chamferCorner(), cornerAt(), cross(), dot(), extendLine(), filletCorner() (+11 more)

### Community 33 - "Session.cpp"
Cohesion: 0.19
Nodes (18): historyEdit(), Session::deleteFeature(), Session::deleteParameter(), Session::editFeature(), Session::newDocument(), Session::open(), Session::redo(), Session::renameBody() (+10 more)

### Community 34 - "ParameterCompleter"
Cohesion: 0.12
Nodes (9): MainWindow::attachArrowCompleters(), ParameterCompleter, completer_, edit_, names_, ParameterCompleter::ParameterCompleter(), public, QCompleter (+1 more)

### Community 35 - "ViewportAnalysis.cpp"
Cohesion: 0.13
Nodes (5): packed(), ramp(), shade(), Viewport::buildAnalysis(), Viewport::setCurvatureComb()

### Community 37 - "Viewport.h"
Cohesion: 0.07
Nodes (15): AnalysisKind, CurvatureMap, Draft, None, Zebra, AnalysisSettings, curvatureScale, draftAngle (+7 more)

### Community 38 - "solve"
Cohesion: 0.18
Nodes (12): addConstraintChecked(), Layout, n, px, py, rad, makeLayout(), pack() (+4 more)

### Community 39 - "MarkingMenu.cpp"
Cohesion: 0.09
Nodes (11): MarkingMenu::keyPressEvent(), MarkingMenu::MarkingMenu(), MarkingMenu::mouseMoveEvent(), MarkingMenu::mouseReleaseEvent(), MarkingMenu::paintEvent(), MarkingMenu::popupAt(), MarkingMenu::ringIndexAt(), MarkingMenu::run() (+3 more)

### Community 41 - "ConstraintType"
Cohesion: 0.09
Nodes (23): ConstraintType, Angle, Coincident, Collinear, Concentric, Diameter, Distance, Equal (+15 more)

### Community 42 - "TEST"
Cohesion: 0.09
Nodes (3): param(), TEST(), tmp()

### Community 43 - "Pick"
Cohesion: 0.12
Nodes (15): Hit, index, kind, Pick, bodyArc, bodyPoint, bodySegment, hit (+7 more)

### Community 44 - "Snap"
Cohesion: 0.10
Nodes (18): Snap, alignX, alignY, bodyArc, bodySegment, entity, fromX, fromY (+10 more)

### Community 45 - "Kind"
Cohesion: 0.09
Nodes (21): HudField, edit, editing, kind, locked, value, Kind, Angle (+13 more)

### Community 47 - "Command.cpp"
Cohesion: 0.22
Nodes (11): expressionKey(), checkInputValue(), CommandContext::evaluateExpression(), CommandDef::input(), CommandSession::applyInTransaction(), CommandSession::cancel(), CommandSession::execute(), CommandSession::preview() (+3 more)

### Community 48 - "Document.cpp"
Cohesion: 0.11
Nodes (20): Document::axes(), Document::bodies(), Document::components(), Document::features(), Document::historyMarker(), Document::planes(), Document::points(), Document::redo() (+12 more)

### Community 49 - "Session"
Cohesion: 0.10
Nodes (6): Session, commands_, doc_, listeners_, nextListener_, path_

### Community 50 - "MainWindowSketch.cpp"
Cohesion: 0.07
Nodes (15): QAbstractButton, QAction, MainWindow::cancelSketch(), MainWindow::editSketch(), MainWindow::finishSketch(), MainWindow::onEdgeClicked(), MainWindow::onProfileClicked(), MainWindow::originalShape() (+7 more)

### Community 51 - "CommandDialog.h"
Cohesion: 0.23
Nodes (4): QComboBox, QDialogButtonBox, QFormLayout, QLabel

### Community 52 - "InputDef"
Cohesion: 0.08
Nodes (24): InputDef, choices, defaultValue, id, label, max, min, minExclusive (+16 more)

### Community 54 - "ViewportAnalysis.cpp"
Cohesion: 0.10
Nodes (8): ArrowPlacement, base, dir, edgePlacement(), facesPlacement(), MainWindow::patternCentre(), MainWindow::pickedFaces(), MainWindow::updateDragArrow()

### Community 55 - "CommandSession"
Cohesion: 0.17
Nodes (6): CommandSession, inputs_, OwnedCommand, owned, OwningCommandSession, Session::begin()

### Community 56 - "Theme.cpp"
Cohesion: 0.19
Nodes (6): setIconTheme(), darkColors(), darkPalette(), darkStyleSheet(), lightColors(), lightStyleSheet()

### Community 57 - "FeatureEffect"
Cohesion: 0.06
Nodes (27): Body, display, name, shape, Component, bodies, name, Feature (+19 more)

### Community 58 - "Constraint"
Cohesion: 0.11
Nodes (17): Constraint, entities, expression, points, type, value, value2, SolveResult (+9 more)

### Community 59 - "xdrive.py"
Cohesion: 0.32
Nodes (14): button(), canvas(), click(), drag(), flush(), geometry(), key(), keycode() (+6 more)

### Community 61 - "SketchGeometry.cpp"
Cohesion: 0.13
Nodes (9): curve(), curves(), customPlaneSpec(), interiorPoint(), planeFrame(), profileAt(), profiles(), toSketch() (+1 more)

### Community 63 - "QTimer"
Cohesion: 0.08
Nodes (9): QTimer, Viewport::arrowMouseMove(), Viewport::arrowMousePress(), Viewport::arrowMouseRelease(), Viewport::dragArrowForTest(), Viewport::emitArrow(), Viewport::rebuildArrow(), Viewport::rebuildArrows() (+1 more)

### Community 64 - "EdgeSig"
Cohesion: 0.18
Nodes (11): dot(), EdgeSig, full, normals, point, rel, tangent, type (+3 more)

### Community 65 - "CommandRegistry"
Cohesion: 0.14
Nodes (3): CommandRegistry, cmds_, TEST()

### Community 66 - "PythonHost.cpp"
Cohesion: 0.11
Nodes (13): PythonHost, Result, error, ok, output, captured(), PythonHost::exec(), PythonHost::PythonHost() (+5 more)

### Community 67 - "Vec3"
Cohesion: 0.22
Nodes (21): TopologyCounts, shells, solids, Vec3, boolean(), extrude(), extrudeEx(), extrudeToPlane() (+13 more)

### Community 68 - "Theme"
Cohesion: 0.22
Nodes (4): Theme, colors_, public, styled_

### Community 69 - "FileFormat"
Cohesion: 0.17
Nodes (12): FileFormat, Brep, Iges, Obj, Step, Stl, ThreeMF, FormatInfo (+4 more)

### Community 71 - "ParametersDialog.cpp"
Cohesion: 0.09
Nodes (20): Column, kComment, kExpression, kParameter, kUnit, kValue, number(), ParametersDialog (+12 more)

### Community 72 - "string"
Cohesion: 0.29
Nodes (10): boundingBox(), completeEdgeReferences(), completeFaceReferences(), edgeReference(), encode(), encodeFace(), faceReference(), fmt() (+2 more)

### Community 73 - "UiCommand"
Cohesion: 0.18
Nodes (9): UiCommand, enabled, icon, id, name, panel, shortcut, tab (+1 more)

### Community 74 - "QString"
Cohesion: 0.12
Nodes (5): ExpressionSpinBox, eval_, expression_, shown_, formatNumber()

### Community 75 - "InputType"
Cohesion: 0.12
Nodes (17): InputType, Axis, Bodies, Body, Bool, Choice, Edges, Faces (+9 more)

### Community 76 - "NavPreset"
Cohesion: 0.40
Nodes (4): NavPreset, Fusion, SolidWorks, Tinkercad

### Community 77 - "CommandRegistry::run"
Cohesion: 0.22
Nodes (4): CommandRegistry::add(), CommandRegistry::all(), CommandRegistry::find(), CommandRegistry::run()

### Community 79 - "TEST"
Cohesion: 0.19
Nodes (3): slurp(), TEST(), tmp()

### Community 80 - "SketchDisplay"
Cohesion: 0.08
Nodes (18): DragArrow, base, dir, value, PendingLook, center, frame, size (+10 more)

### Community 81 - "string"
Cohesion: 0.16
Nodes (18): bodyNumber(), Document::addBody(), Document::bodyName(), Document::bodyShapes(), Document::effectOf(), Document::lengthUnit(), Document::nextAxisName(), Document::nextBodyName() (+10 more)

### Community 82 - "Measurement"
Cohesion: 0.13
Nodes (14): Kind, Angle, Area, Length, Volume, Measurement, from, hasLine (+6 more)

### Community 83 - "rect"
Cohesion: 0.28
Nodes (3): SelectionBox, crossing, rect()

### Community 84 - "Entity"
Cohesion: 0.22
Nodes (9): Entity, a, b, center, construction, fit, projected, radius (+1 more)

### Community 85 - "Level"
Cohesion: 0.16
Nodes (7): Level, Debug, Error, Info, Warning, name(), write()

### Community 86 - "README.md"
Cohesion: 0.10
Nodes (16): Architecture, How a command works, The document, Units, Known gaps, Reference parts, Fusion feature checklist, Roadmap (+8 more)

### Community 91 - "EntityType"
Cohesion: 0.33
Nodes (6): EntityType, Arc, Circle, Line, Spline, isRound()

### Community 93 - "Known differences still to build"
Cohesion: 0.15
Nodes (12): Data and files, Findings from the videos, Fusion study list, Interface, Known differences still to build, Navigation and display, Selection and the canvas, Sketch (+4 more)

### Community 94 - "SketchEditor::SketchEditor"
Cohesion: 0.14
Nodes (7): QObject, SketchEditor::SketchEditor(), edges, Tool, op, shape, target

### Community 96 - "TsrModule.cpp"
Cohesion: 0.20
Nodes (4): bindTsr(), fromPy(), toPy(), typeName()

### Community 97 - "BodyFrame"
Cohesion: 0.09
Nodes (22): BodyFrame, diag, dx, dy, dz, x0, y0, z0 (+14 more)

### Community 98 - "FakeDoc"
Cohesion: 0.17
Nodes (6): FakeDoc, aborts, commits, items, open, snapshot

### Community 99 - "CommandError"
Cohesion: 0.11
Nodes (27): CommandError, getBool(), getInt(), getReal(), applyOperation(), bodyCentre(), bodyName(), CopyFn (+19 more)

### Community 100 - "Zip.cpp"
Cohesion: 0.21
Nodes (11): Entry, data, name, ZipError, crc32(), get16(), get32(), put16() (+3 more)

### Community 101 - "Log.h"
Cohesion: 0.36
Nodes (6): debug(), error(), info(), Sink, warning(), setSink()

### Community 102 - "Kernel.h"
Cohesion: 0.09
Nodes (21): Axis, X, Y, Z, BooleanOp, Cut, Intersect, Join (+13 more)

### Community 103 - "DocumentError"
Cohesion: 0.08
Nodes (17): DocumentError, doc_(), Document::addUserParameter(), Document::axisFrame(), Document::Document(), Document::ocafBytes(), Document::planeFrame(), Document::reevaluateParameters() (+9 more)

### Community 104 - "Development"
Cohesion: 0.40
Nodes (4): Build, Conventions, Development, Tests

### Community 105 - "optional"
Cohesion: 0.17
Nodes (10): optional, ConstructionAxis, axis, name, Document::axis(), Document::body(), Document::component(), Document::componentOfBody() (+2 more)

### Community 106 - "SectionState"
Cohesion: 0.25
Nodes (7): SectionState, active, angle, flip, offset, plane, visible

### Community 107 - "Display"
Cohesion: 0.25
Nodes (7): Display, constraints, construction, dimensions, points, profiles, projected

### Community 108 - "ConstructionPlane"
Cohesion: 0.40
Nodes (5): ConstructionPlane, name, spec, Document::plane(), Document::setPlane()

### Community 109 - ".requireTransaction"
Cohesion: 0.13
Nodes (21): SketchRecord, data, name, offset, plane, Document::abortTransaction(), Document::commitTransaction(), Document::openTransaction() (+13 more)

### Community 110 - "openWallBand"
Cohesion: 0.15
Nodes (18): BoundingBox, max, min, Section, Circular, Square, Triangular, WallSide (+10 more)

### Community 111 - "Rect"
Cohesion: 0.50
Nodes (4): Session::notifyChanged(), Rect, l, p

### Community 112 - "ConstructionPoint"
Cohesion: 0.33
Nodes (5): ConstructionPoint, name, point, Document::point(), Document::setPoint()

### Community 113 - "main"
Cohesion: 0.27
Nodes (6): listCommands(), main(), usage(), main(), smoke(), volume

### Community 114 - "uninstall.sh"
Cohesion: 0.52
Nodes (6): die(), manifest_for(), refresh(), uninstall.sh script, step(), usage()

### Community 115 - "install.sh"
Cohesion: 0.60
Nodes (5): die(), refresh(), install.sh script, step(), usage()

### Community 116 - ".bodies"
Cohesion: 0.18
Nodes (4): Extrude, def_, NewComponent, def_

### Community 123 - "functional"
Cohesion: 0.40
Nodes (3): MarkingMenu, enabled, public

### Community 132 - "ChainSegment"
Cohesion: 0.67
Nodes (3): ChainSegment, entity, forward

## Knowledge Gaps
- **638 isolated node(s):** `ok`, `output`, `error`, `isReal`, `real` (+633 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 1207 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **28 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `optional` connect `optional` to `Viewport`, `DocCommands.cpp`, `MainWindow`, `Inputs`, `cmath`, `Kernel.cpp`, `Io.cpp`, `Unit`, `ViewportArrow.cpp`, `ViewportSketch.cpp`, `SketchEditor.cpp`, `SketchOps.cpp`, `Viewport.h`, `.press`, `Session`, `CommandDialog.h`, `InputDef`, `ViewportAnalysis.cpp`, `FeatureEffect`, `Vec3`, `CommandDialog.cpp`, `QString`, `SketchDisplay`, `TsrModule.cpp`, `Kernel.h`, `DocumentError`, `ConstructionPlane`, `ConstructionPoint`?**
  _High betweenness centrality (0.130) - this node is a cross-community bridge._
- **What connects `ok`, `output`, `error` to the rest of the system?**
  _638 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Viewport` be split into smaller, more focused modules?**
  _Cohesion score 0.01815408085430969 - nodes in this community are weakly interconnected._
- **Why does `Viewport` connect `Viewport` to `ViewportAnalysis.cpp`, `Viewport.h`, `MarkingMenu.cpp`, `Viewport.cpp`, `optional`, `NavPreset`, `MainWindowTools.cpp`, `SketchDisplay`, `rect`, `.toPixels`, `ViewportArrow.cpp`, `Handle`, `.selectedSubShapes`, `QTimer`?**
  _High betweenness centrality (0.127) - this node is a cross-community bridge._
- **Should `Icons.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.06853038245000971 - nodes in this community are weakly interconnected._
- **Why does `MainWindow` connect `MainWindow` to `TsrModule.cpp`, `PythonHost.cpp`, `ParameterCompleter`, `src/main.cpp`, `UiCommand`, `SectionState`, `MainWindowTools.cpp`, `main`, `MainWindowSketch.cpp`, `Session`, `MainWindow.cpp`, `ViewportAnalysis.cpp`, `SketchPalette`?**
  _High betweenness centrality (0.098) - this node is a cross-community bridge._
- **Should `DocCommands.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.041176470588235294 - nodes in this community are weakly interconnected._