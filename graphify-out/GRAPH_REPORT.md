# Graph Report - tessera  (2026-11-12)

## Corpus Check
- 329 files · ~188,251 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 26 file(s) not represented in the graph (top: .drive 18, (none) 5, .cmake 1)

## Summary
- 3056 nodes · 7604 edges · 122 communities (99 shown, 23 thin omitted)
- Extraction: 85% EXTRACTED · 15% INFERRED · 0% AMBIGUOUS · INFERRED: 1149 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `7ce40dbb`
- Run `git rev-parse HEAD` and compare to check if the graph is stale.
- Run `graphify update .` after code changes (no API cost).

## Community Hubs (Navigation)
- Viewport
- Icons.cpp
- DocCommands.cpp
- tsr
- MainWindow
- run_oracle.py
- sketchFor
- Document
- Viewport.cpp
- SketchEditor
- Inputs
- Sketch.h
- Kernel.cpp
- MainWindow::setSelectionFilter
- MainWindowSketch.cpp
- MainWindowTools.cpp
- CommandDialog
- Io.cpp
- Parser
- SketchGeometry.cpp
- .mouseMove
- Expression.cpp
- MainWindow.cpp
- TEST
- Sketch.cpp
- ViewportSketch.cpp
- SketchPalette
- QMouseEvent
- AdskModule.cpp
- Colors
- TopoDS_Shape
- SketchOps.cpp
- Unit
- ParameterCompleter
- string
- ConstructAxisPoint
- Viewport.h
- solve
- ViewportArrow.cpp
- src/main.cpp
- ConstraintType
- TEST
- Pick
- Snap
- Kind
- .redrawAll
- Zip.cpp
- Document.cpp
- CommandDialog::CommandDialog
- MainWindow::enterSketchMode
- Session.cpp
- InputDef
- .toPixels
- MainWindowArrow.cpp
- .apply
- SketchEditor.cpp
- ViewportAnalysis.cpp
- Constraint
- xdrive.py
- TEST
- Document.h
- ParametersDialog
- DocumentError
- CommandRegistry
- PythonHost.cpp
- Vec3
- MainWindow::MainWindow
- FileFormat
- CommandDialog.cpp
- ParametersDialog.cpp
- ext
- Kernel.h
- Command.cpp
- InputType
- Kind
- TsrModule.cpp
- Theme.cpp
- CommandRegistry::run
- SketchDisplay
- string
- Measurement
- BoundingBox
- Entity
- Level
- README.md
- ParameterCompleter.cpp
- .hitTest
- QObject
- EdgeSig
- Profile
- Known differences still to build
- CommandSession
- .add
- CommandDialog::CommandDialog
- gp_Pnt
- FakeDoc
- UiCommand
- TEST
- Theme
- DocumentError
- cli_main.cpp
- Session::notifyChanged
- SectionState
- Display
- string
- uninstall.sh
- install.sh
- Column
- cmath
- smoke
- MarkingMenu
- Dimension
- ChainSegment
- LAB_NOTES.md
- build.sh
- live-test.sh

## God Nodes (most connected - your core abstractions)
1. `Viewport` - 203 edges
2. `MainWindow` - 157 edges
3. `SketchEditor` - 154 edges
4. `Inputs` - 136 edges
5. `Document` - 119 edges
6. `CommandContext` - 102 edges
7. `CommandDialog` - 88 edges
8. `render()` - 86 edges
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

## Communities (122 total, 23 thin omitted)

### Community 0 - "Viewport"
Cohesion: 0.02
Nodes (48): view_, Viewport, analysis_, analysisObjects_, appliedGridStep_, arrowBoxes_, arrowDragging_, arrowGrab_ (+40 more)

### Community 1 - "Icons.cpp"
Cohesion: 0.07
Nodes (90): arcIcon(), arrow(), axisIcon(), box(), centerRectIcon(), chamferIcon(), circleIcon(), coilIcon() (+82 more)

### Community 2 - "DocCommands.cpp"
Cohesion: 0.04
Nodes (54): Adding a tool, Command, CommandDef, feature, icon, id, inputs, name (+46 more)

### Community 4 - "MainWindow"
Cohesion: 0.03
Nodes (54): CommandDialog, MainWindow, active_, arrowInput_, arrowInput2_, bodiesBeforeCommand_, combEdges_, combPicking_ (+46 more)

### Community 5 - "run_oracle.py"
Cohesion: 0.08
Nodes (54): add_point(), arc_poly(), body_at(), body_list(), build_sketch(), chain(), circumcentre(), cm() (+46 more)

### Community 6 - "sketchFor"
Cohesion: 0.20
Nodes (8): Hole, def_, Pipe, def_, Revolve, def_, sketchFor(), stringOr()

### Community 7 - "Document"
Cohesion: 0.04
Nodes (21): Document, effects_, modified_, pendingTools_, registry_, replaying_, txnBodies_, FeatureEffect (+13 more)

### Community 8 - "Viewport.cpp"
Cohesion: 0.05
Nodes (5): keys(), qc(), QtFrameBuffer, rgb(), Viewport::Viewport()

### Community 9 - "SketchEditor"
Cohesion: 0.03
Nodes (43): PlaneEdges, arcs, segments, vertices, SketchEditor, arcDrag_, arcDragMoved_, arcEndsChain_ (+35 more)

### Community 10 - "Inputs"
Cohesion: 0.09
Nodes (22): CommandContext, CommandError, Inputs, CommandSession::CommandSession(), getBool(), getInt(), getReal(), applyOperation() (+14 more)

### Community 11 - "Sketch.h"
Cohesion: 0.11
Nodes (8): isEmpty(), Value, EntityType, Arc, Circle, Line, Spline, isRound()

### Community 14 - "MainWindowSketch.cpp"
Cohesion: 0.08
Nodes (13): MainWindow::cancelSketch(), MainWindow::editSketch(), MainWindow::finishSketch(), MainWindow::onEdgeClicked(), MainWindow::onProfileClicked(), MainWindow::originalShape(), MainWindow::sketchPalette(), MainWindow::sketchVisible() (+5 more)

### Community 15 - "MainWindowTools.cpp"
Cohesion: 0.07
Nodes (25): QDialog, MainWindow::checkInterference(), MainWindow::chooseUnits(), MainWindow::driveJoints(), MainWindow::exportDesign(), MainWindow::formatLength(), MainWindow::gridSettings(), MainWindow::insertFile() (+17 more)

### Community 16 - "CommandDialog"
Cohesion: 0.06
Nodes (29): CommandDialog, bodiesId_, bodiesLabel_, bodyInput_, buttons_, cmd_, conditional_, edgesId_ (+21 more)

### Community 17 - "Io.cpp"
Cohesion: 0.10
Nodes (18): MainWindow::print3d(), NamedShape, compoundOf(), exportShapes(), fmt(), formatForPath(), fromBrep(), importShape() (+10 more)

### Community 18 - "Parser"
Cohesion: 0.18
Nodes (14): Quantity, angle, length, value, describe(), isIdentChar(), isIdentStart(), Parser (+6 more)

### Community 19 - "SketchGeometry.cpp"
Cohesion: 0.12
Nodes (9): curve(), curves(), customPlaneSpec(), interiorPoint(), planeFrame(), profileAt(), profiles(), toSketch() (+1 more)

### Community 20 - ".mouseMove"
Cohesion: 0.13
Nodes (7): ext(), fixedColor(), freeColor(), qc(), rgb(), wire(), Sketch::addLine()

### Community 21 - "Expression.cpp"
Cohesion: 0.12
Nodes (18): ExpressionEnv, lengthUnit, lookup, ExpressionError, evaluateExpression(), evaluateQuantity(), expressionReferences(), isConstantName() (+10 more)

### Community 22 - "MainWindow.cpp"
Cohesion: 0.08
Nodes (5): commandIcon(), qs(), run, MainWindow::applySection(), MarkingMenu::mouseReleaseEvent()

### Community 23 - "TEST"
Cohesion: 0.09
Nodes (6): Sketch, constraints, entities, points, Sketch::addCircle(), TEST()

### Community 24 - "Sketch.cpp"
Cohesion: 0.09
Nodes (16): Point, x, y, SketchError, entityTypeName(), isDimension(), Sketch::addSpline(), Sketch::checkIndices() (+8 more)

### Community 25 - "ViewportSketch.cpp"
Cohesion: 0.10
Nodes (6): faceStyle(), lineStyle(), rgb(), Viewport::lookAt(), Viewport::planePoint(), Viewport::toWidget()

### Community 26 - "SketchPalette"
Cohesion: 0.06
Nodes (26): flatButton(), QCheckBox, QLabel, QToolButton, QWidget, SketchEditor, SketchPalette, body_ (+18 more)

### Community 28 - "QMouseEvent"
Cohesion: 0.09
Nodes (11): MarkingMenu::keyPressEvent(), MarkingMenu::MarkingMenu(), MarkingMenu::mouseMoveEvent(), MarkingMenu::paintEvent(), MarkingMenu::popupAt(), MarkingMenu::ringIndexAt(), MarkingMenu::run(), MarkingMenu::triggerForTest() (+3 more)

### Community 29 - "AdskModule.cpp"
Cohesion: 0.10
Nodes (15): Application, BRepBodies, BRepBody, index, Component, Design, Product, raiseIfError() (+7 more)

### Community 30 - "Colors"
Cohesion: 0.07
Nodes (28): Colors, base, border, cubeBox, cubeText, errorBackground, grid, gridMajor (+20 more)

### Community 31 - "TopoDS_Shape"
Cohesion: 0.27
Nodes (23): KernelError, vertices, boolean(), chamfer(), chamferEx(), draft(), extrude(), extrudeEx() (+15 more)

### Community 32 - "SketchOps.cpp"
Cohesion: 0.21
Nodes (19): at(), chainOf(), chamferCorner(), cornerAt(), cross(), dot(), extendLine(), filletCorner() (+11 more)

### Community 33 - "Unit"
Cohesion: 0.17
Nodes (14): bindAdsk(), MainWindow::lengthUnit(), Unit, Centimeter, Degree, Foot, Inch, Meter (+6 more)

### Community 34 - "ParameterCompleter"
Cohesion: 0.18
Nodes (8): QObject, ParameterCompleter, completer_, edit_, names_, public, QCompleter, QLineEdit

### Community 35 - "string"
Cohesion: 0.10
Nodes (30): BodyFrame, diag, dx, dy, dz, x0, y0, z0 (+22 more)

### Community 36 - "ConstructAxisPoint"
Cohesion: 0.21
Nodes (5): ConstructAxisPoint, def_, kind_, JointPick, frame

### Community 37 - "Viewport.h"
Cohesion: 0.07
Nodes (15): AnalysisKind, CurvatureMap, Draft, None, Zebra, AnalysisSettings, curvatureScale, draftAngle (+7 more)

### Community 38 - "solve"
Cohesion: 0.18
Nodes (12): addConstraintChecked(), Layout, n, px, py, rad, makeLayout(), pack() (+4 more)

### Community 39 - "ViewportArrow.cpp"
Cohesion: 0.08
Nodes (14): rgb(), segmentDistance(), Viewport::arrowAt(), Viewport::arrowMouseMove(), Viewport::arrowMousePress(), Viewport::arrowMouseRelease(), Viewport::arrowParam(), Viewport::dragArrowForTest() (+6 more)

### Community 41 - "ConstraintType"
Cohesion: 0.09
Nodes (23): ConstraintType, Angle, Coincident, Collinear, Concentric, Diameter, Distance, Equal (+15 more)

### Community 42 - "TEST"
Cohesion: 0.06
Nodes (10): main(), Session, commands_, doc_, listeners_, nextListener_, path_, param() (+2 more)

### Community 43 - "Pick"
Cohesion: 0.17
Nodes (12): Pick, bodyArc, bodyPoint, bodySegment, hit, midpointOf, onEntity, parallelTo (+4 more)

### Community 44 - "Snap"
Cohesion: 0.11
Nodes (18): Snap, alignX, alignY, bodyArc, bodySegment, entity, fromX, fromY (+10 more)

### Community 45 - "Kind"
Cohesion: 0.09
Nodes (21): HudField, edit, editing, kind, locked, value, Kind, Angle (+13 more)

### Community 46 - ".redrawAll"
Cohesion: 0.11
Nodes (7): NavPreset, Fusion, SolidWorks, Tinkercad, Viewport::clearDragArrow(), Viewport::clearSecondArrow(), Viewport::setInteractor()

### Community 47 - "Zip.cpp"
Cohesion: 0.21
Nodes (11): Entry, data, name, ZipError, crc32(), get16(), get32(), put16() (+3 more)

### Community 48 - "Document.cpp"
Cohesion: 0.11
Nodes (22): ConstructionPlane, name, spec, Document::axes(), Document::bodies(), Document::body(), Document::components(), Document::features() (+14 more)

### Community 49 - "CommandDialog::CommandDialog"
Cohesion: 0.12
Nodes (5): ExpressionSpinBox, eval_, expression_, shown_, formatNumber()

### Community 51 - "Session.cpp"
Cohesion: 0.18
Nodes (15): historyEdit(), Session::addListener(), Session::begin(), Session::deleteFeature(), Session::deleteParameter(), Session::editFeature(), Session::newDocument(), Session::open() (+7 more)

### Community 52 - "InputDef"
Cohesion: 0.08
Nodes (24): InputDef, choices, defaultValue, id, label, max, min, minExclusive (+16 more)

### Community 54 - "MainWindowArrow.cpp"
Cohesion: 0.10
Nodes (8): ArrowPlacement, base, dir, edgePlacement(), facesPlacement(), MainWindow::patternCentre(), MainWindow::pickedFaces(), MainWindow::updateDragArrow()

### Community 55 - ".apply"
Cohesion: 0.09
Nodes (17): Coil, def_, evaluateDimensions(), Extrude, def_, Loft, def_, openChains() (+9 more)

### Community 57 - "ViewportAnalysis.cpp"
Cohesion: 0.13
Nodes (5): packed(), ramp(), shade(), Viewport::buildAnalysis(), Viewport::setCurvatureComb()

### Community 58 - "Constraint"
Cohesion: 0.11
Nodes (17): Constraint, entities, expression, points, type, value, value2, SolveResult (+9 more)

### Community 59 - "xdrive.py"
Cohesion: 0.32
Nodes (14): button(), canvas(), click(), drag(), flush(), geometry(), key(), keycode() (+6 more)

### Community 61 - "TEST"
Cohesion: 0.19
Nodes (3): slurp(), TEST(), tmp()

### Community 62 - "Document.h"
Cohesion: 0.07
Nodes (27): Body, name, shape, Component, bodies, name, ConstructionAxis, axis (+19 more)

### Community 63 - "ParametersDialog"
Cohesion: 0.19
Nodes (10): ParametersDialog, building_, error_, listener_, public, rebuildPending_, tree_, QLabel (+2 more)

### Community 64 - "DocumentError"
Cohesion: 0.11
Nodes (17): DocumentError, Document::abortTransaction(), Document::addBody(), Document::addUserParameter(), Document::axisFrame(), Document::bodyShapes(), Document::commitTransaction(), Document::effectOf() (+9 more)

### Community 65 - "CommandRegistry"
Cohesion: 0.14
Nodes (3): CommandRegistry, cmds_, TEST()

### Community 66 - "PythonHost.cpp"
Cohesion: 0.21
Nodes (9): Result, error, ok, output, captured(), PythonHost::exec(), PythonHost::PythonHost(), PythonHost::runScript() (+1 more)

### Community 67 - "Vec3"
Cohesion: 0.18
Nodes (21): SurfacePoint, normal, point, Vec3, asSolid(), boundingBox(), edgeMidpoint(), edgesNear() (+13 more)

### Community 68 - "MainWindow::MainWindow"
Cohesion: 0.12
Nodes (5): PythonHost, MainWindow::MainWindow(), MainWindow::beginSketch(), MainWindow::exitSketchMode(), MainWindow::showPreferences()

### Community 69 - "FileFormat"
Cohesion: 0.17
Nodes (12): FileFormat, Brep, Iges, Obj, Step, Stl, ThreeMF, FormatInfo (+4 more)

### Community 71 - "ParametersDialog.cpp"
Cohesion: 0.14
Nodes (4): number(), ParametersDialog::ParametersDialog(), qs(), withUnit()

### Community 72 - "ext"
Cohesion: 0.16
Nodes (13): SketchRecord, data, name, offset, plane, Document::openTransaction(), Document::recompute(), Document::recordFeature() (+5 more)

### Community 73 - "Kernel.h"
Cohesion: 0.07
Nodes (34): Axis, X, Y, Z, BooleanOp, Cut, Intersect, Join (+26 more)

### Community 74 - "Command.cpp"
Cohesion: 0.22
Nodes (11): expressionKey(), checkInputValue(), CommandContext::evaluateExpression(), CommandDef::input(), CommandSession::applyInTransaction(), CommandSession::cancel(), CommandSession::execute(), CommandSession::preview() (+3 more)

### Community 75 - "InputType"
Cohesion: 0.12
Nodes (17): InputType, Axis, Bodies, Body, Bool, Choice, Edges, Faces (+9 more)

### Community 76 - "Kind"
Cohesion: 0.09
Nodes (22): ConstructPlane, def_, kind_, EdgeFeature, def_, kind_, Kind, Angle (+14 more)

### Community 77 - "TsrModule.cpp"
Cohesion: 0.25
Nodes (4): bindTsr(), fromPy(), toPy(), typeName()

### Community 78 - "Theme.cpp"
Cohesion: 0.19
Nodes (6): setIconTheme(), darkColors(), darkPalette(), darkStyleSheet(), lightColors(), lightStyleSheet()

### Community 79 - "CommandRegistry::run"
Cohesion: 0.22
Nodes (4): CommandRegistry::add(), CommandRegistry::all(), CommandRegistry::find(), CommandRegistry::run()

### Community 80 - "SketchDisplay"
Cohesion: 0.08
Nodes (18): DragArrow, base, dir, value, PendingLook, center, frame, size (+10 more)

### Community 81 - "string"
Cohesion: 0.14
Nodes (17): optional, bodyNumber(), Document::axis(), Document::component(), Document::componentOfBody(), Document::feature(), Document::nextAxisName(), Document::nextBodyName() (+9 more)

### Community 82 - "Measurement"
Cohesion: 0.13
Nodes (14): Kind, Angle, Area, Length, Volume, Measurement, from, hasLine (+6 more)

### Community 83 - "BoundingBox"
Cohesion: 0.25
Nodes (8): BoundingBox, max, min, massProperties(), measure(), offsetOpenWire(), polygonToCircleLoft(), sweepWire()

### Community 84 - "Entity"
Cohesion: 0.22
Nodes (9): Entity, a, b, center, construction, fit, projected, radius (+1 more)

### Community 85 - "Level"
Cohesion: 0.16
Nodes (13): debug(), error(), info(), Level, Debug, Error, Info, Warning (+5 more)

### Community 86 - "README.md"
Cohesion: 0.08
Nodes (20): Architecture, How a command works, The document, Units, Build, Conventions, Development, Tests (+12 more)

### Community 88 - ".hitTest"
Cohesion: 0.17
Nodes (4): Hit, index, kind, segDistance()

### Community 91 - "EdgeSig"
Cohesion: 0.18
Nodes (11): dot(), EdgeSig, full, normals, point, rel, tangent, type (+3 more)

### Community 92 - "Profile"
Cohesion: 0.33
Nodes (5): Profile, area, face, x, y

### Community 93 - "Known differences still to build"
Cohesion: 0.15
Nodes (12): Data and files, Findings from the videos, Fusion study list, Interface, Known differences still to build, Navigation and display, Selection and the canvas, Sketch (+4 more)

### Community 94 - "CommandSession"
Cohesion: 0.18
Nodes (5): CommandSession, inputs_, OwnedCommand, owned, OwningCommandSession

### Community 97 - "gp_Pnt"
Cohesion: 0.32
Nodes (5): faceNormalAt(), nearestFace(), offsetLoop(), offsetRegion(), pointOnFace()

### Community 98 - "FakeDoc"
Cohesion: 0.17
Nodes (6): FakeDoc, aborts, commits, items, open, snapshot

### Community 99 - "UiCommand"
Cohesion: 0.18
Nodes (9): UiCommand, enabled, icon, id, name, panel, shortcut, tab (+1 more)

### Community 102 - "Theme"
Cohesion: 0.14
Nodes (6): QAbstractButton, QAction, Theme, colors_, public, styled_

### Community 103 - "DocumentError"
Cohesion: 0.11
Nodes (8): doc_(), Document::Document(), Document::ocafBytes(), Document::reevaluateParameters(), Document::userParameter(), ocafApplication(), Document::load(), Document::save()

### Community 104 - "cli_main.cpp"
Cohesion: 0.28
Nodes (3): listCommands(), main(), usage()

### Community 106 - "SectionState"
Cohesion: 0.25
Nodes (7): SectionState, active, angle, flip, offset, plane, visible

### Community 107 - "Display"
Cohesion: 0.25
Nodes (7): Display, constraints, construction, dimensions, points, profiles, projected

### Community 112 - "string"
Cohesion: 0.07
Nodes (19): AddUserParameter, def_, checkPattern(), CircularPattern, def_, isIdentifier(), Joint, def_ (+11 more)

### Community 114 - "uninstall.sh"
Cohesion: 0.52
Nodes (6): die(), manifest_for(), refresh(), uninstall.sh script, step(), usage()

### Community 115 - "install.sh"
Cohesion: 0.60
Nodes (5): die(), refresh(), install.sh script, step(), usage()

### Community 116 - "Column"
Cohesion: 0.33
Nodes (6): Column, kComment, kExpression, kParameter, kUnit, kValue

### Community 118 - "cmath"
Cohesion: 0.16
Nodes (8): Rect, rect(), p, Case, name, fail(), Failure, Register

### Community 122 - "smoke"
Cohesion: 0.40
Nodes (5): smoke(), MassProperties, area, centerOfMass, volume

### Community 123 - "MarkingMenu"
Cohesion: 0.25
Nodes (3): MarkingMenu, enabled, public

### Community 125 - "Dimension"
Cohesion: 0.50
Nodes (4): Dimension, Angle, Length, Unitless

### Community 132 - "ChainSegment"
Cohesion: 0.67
Nodes (3): ChainSegment, entity, forward

## Knowledge Gaps
- **618 isolated node(s):** `ok`, `output`, `error`, `isReal`, `real` (+613 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 1175 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **23 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `Viewport` connect `Viewport` to `Viewport.h`, `ViewportArrow.cpp`, `Viewport.cpp`, `.setBodyOverrides`, `.redrawAll`, `.initializeGL`, `SketchDisplay`, `MainWindowTools.cpp`, `string`, `.toPixels`, `ViewportAnalysis.cpp`, `QMouseEvent`?**
  _High betweenness centrality (0.125) - this node is a cross-community bridge._
- **What connects `ok`, `output`, `error` to the rest of the system?**
  _618 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Viewport` be split into smaller, more focused modules?**
  _Cohesion score 0.019182652210175146 - nodes in this community are weakly interconnected._
- **Why does `optional` connect `string` to `Viewport`, `DocCommands.cpp`, `MainWindow`, `sketchFor`, `Sketch.h`, `Kernel.cpp`, `CommandDialog`, `Io.cpp`, `Parser`, `Expression.cpp`, `ViewportSketch.cpp`, `SketchOps.cpp`, `Unit`, `Viewport.h`, `ViewportArrow.cpp`, `TEST`, `Document.cpp`, `CommandDialog::CommandDialog`, `InputDef`, `MainWindowArrow.cpp`, `SketchEditor.cpp`, `Document.h`, `Vec3`, `CommandDialog.cpp`, `Kernel.h`, `SketchDisplay`, `.hitTest`, `Session.h`, `DocumentError`?**
  _High betweenness centrality (0.114) - this node is a cross-community bridge._
- **Should `Icons.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.06930693069306931 - nodes in this community are weakly interconnected._
- **Why does `MainWindow` connect `MainWindow` to `UiCommand`, `MainWindow::MainWindow`, `smoke`, `src/main.cpp`, `SectionState`, `Sketch.h`, `TEST`, `MainWindowSketch.cpp`, `MainWindowTools.cpp`, `MainWindow::enterSketchMode`, `MainWindowArrow.cpp`, `MainWindow.cpp`, `SketchPalette`?**
  _High betweenness centrality (0.091) - this node is a cross-community bridge._
- **Should `DocCommands.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.043209876543209874 - nodes in this community are weakly interconnected._