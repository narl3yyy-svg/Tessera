# Graph Report - tessera  (2026-11-12)

## Corpus Check
- 335 files · ~193,364 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 30 file(s) not represented in the graph (top: .drive 22, (none) 5, .cmake 1)

## Summary
- 3120 nodes · 7792 edges · 117 communities (99 shown, 18 thin omitted)
- Extraction: 85% EXTRACTED · 15% INFERRED · 0% AMBIGUOUS · INFERRED: 1202 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `f4df8a4b`
- Run `git rev-parse HEAD` and compare to check if the graph is stale.
- Run `graphify update .` after code changes (no API cost).

## Community Hubs (Navigation)
- Viewport
- Icons.cpp
- CommandDef
- MainWindow
- run_oracle.py
- Inputs
- Document
- Viewport.cpp
- SketchEditor
- Dimension
- cmath
- Kernel.cpp
- .projectAt
- Kind
- MainWindowTools.cpp
- CommandDialog
- Io.cpp
- Unit
- SketchGeometry.cpp
- .hitTest
- Command
- MainWindow.cpp
- TEST
- Sketch.cpp
- ViewportSketch.cpp
- SketchPalette
- SketchEditor.cpp
- cmath
- AdskModule.cpp
- Colors
- TopoDS_Shape
- SketchOps.cpp
- CommandSession
- ParameterCompleter
- string
- ConstructAxisPoint
- Viewport.h
- solve
- ViewportAnalysis.cpp
- src/main.cpp
- ConstraintType
- TEST
- Pick
- Snap
- Kind
- .updatePreview
- Zip.cpp
- Document.cpp
- CommandDialog::CommandDialog
- MainWindowSketch.cpp
- Session.cpp
- InputDef
- .toPixels
- MainWindowArrow.cpp
- string
- Command.cpp
- FeatureEffect
- Constraint
- xdrive.py
- DocCommands.cpp
- CommandDialog::CommandDialog
- ViewportArrow.cpp
- Document.cpp
- CommandRegistry
- PythonHost.cpp
- Vec3
- MainWindow::MainWindow
- FileFormat
- CommandDialog.cpp
- ParametersDialog.cpp
- .apply
- TopologyCounts
- NavPreset
- InputType
- ParametersDialog
- Theme.cpp
- optional
- SketchDisplay
- string
- Measurement
- rect
- Entity
- Level
- README.md
- Sketch.h
- BoundingBox
- SketchEditor::SketchEditor
- Value.h
- Rect
- Session::addListener
- Known differences still to build
- .add
- sketchFor
- BodyFrame
- FakeDoc
- TsrModule.cpp
- Zip.h
- Theme
- DocumentError
- cli_main.cpp
- SectionState
- Display
- ParameterCompleter.cpp
- Kernel.h
- Mesh
- uninstall.sh
- install.sh
- Column
- MarkingMenu
- ChainSegment
- LAB_NOTES.md
- build.sh
- live-test.sh

## God Nodes (most connected - your core abstractions)
1. `Viewport` - 213 edges
2. `MainWindow` - 166 edges
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
- `Architecture` --references--> `InputDef`  [INFERRED]
  docs/ARCHITECTURE.md → modules/core/include/tsr/core/Command.h
- `Architecture` --references--> `CommandDef`  [INFERRED]
  docs/ARCHITECTURE.md → modules/core/include/tsr/core/Command.h
- `Adding a tool` --references--> `CommandDef`  [INFERRED]
  docs/DEVELOPMENT.md → modules/core/include/tsr/core/Command.h

## Import Cycles
- None detected.

## Communities (117 total, 18 thin omitted)

### Community 0 - "Viewport"
Cohesion: 0.02
Nodes (52): view_, QLineEdit, Viewport, analysis_, analysisObjects_, appliedGridStep_, arrowBoxes_, arrowDragging_ (+44 more)

### Community 1 - "Icons.cpp"
Cohesion: 0.07
Nodes (91): arcIcon(), arrow(), axisIcon(), box(), centerRectIcon(), chamferIcon(), circleIcon(), coilIcon() (+83 more)

### Community 2 - "CommandDef"
Cohesion: 0.06
Nodes (30): CommandDef, feature, icon, id, inputs, name, nameInput, panel (+22 more)

### Community 4 - "MainWindow"
Cohesion: 0.03
Nodes (60): Known gaps, CommandDialog, MainWindow, active_, arrowInput_, arrowInput2_, bodiesBeforeCommand_, combEdges_ (+52 more)

### Community 5 - "run_oracle.py"
Cohesion: 0.08
Nodes (54): add_point(), arc_poly(), body_at(), body_list(), build_sketch(), chain(), circumcentre(), cm() (+46 more)

### Community 6 - "Inputs"
Cohesion: 0.09
Nodes (19): CommandContext, CommandError, Inputs, CommandSession::CommandSession(), getBool(), getInt(), applyOperation(), bodyName() (+11 more)

### Community 7 - "Document"
Cohesion: 0.04
Nodes (11): Document, effects_, modified_, pendingTools_, registry_, replaying_, txnBodies_, FromOcaf (+3 more)

### Community 8 - "Viewport.cpp"
Cohesion: 0.05
Nodes (6): keys(), qc(), QtFrameBuffer, rgb(), Viewport::Viewport(), Viewport::setInteractor()

### Community 9 - "SketchEditor"
Cohesion: 0.03
Nodes (41): SketchEditor, arcDrag_, arcDragMoved_, arcEndsChain_, arcFrom_, arcRef_, bodyEdges_, boxing_ (+33 more)

### Community 10 - "Dimension"
Cohesion: 0.50
Nodes (4): Dimension, Angle, Length, Unitless

### Community 11 - "cmath"
Cohesion: 0.15
Nodes (3): CommandRegistry::all(), fail(), Failure

### Community 13 - ".projectAt"
Cohesion: 0.14
Nodes (5): PlaneEdges, arcs, segments, vertices, edges

### Community 14 - "Kind"
Cohesion: 0.09
Nodes (22): ConstructPlane, def_, kind_, EdgeFeature, def_, kind_, Kind, Angle (+14 more)

### Community 15 - "MainWindowTools.cpp"
Cohesion: 0.05
Nodes (25): QDialog, MainWindow::checkInterference(), MainWindow::chooseUnits(), MainWindow::driveJoints(), MainWindow::exportDesign(), MainWindow::formatLength(), MainWindow::gridSettings(), MainWindow::insertFile() (+17 more)

### Community 16 - "CommandDialog"
Cohesion: 0.05
Nodes (31): CommandDialog, bodiesId_, bodiesLabel_, bodyInput_, buttons_, cmd_, conditional_, edgesId_ (+23 more)

### Community 17 - "Io.cpp"
Cohesion: 0.11
Nodes (15): MainWindow::print3d(), NamedShape, compoundOf(), exportShapes(), fmt(), formatForPath(), fromBrep(), importShape() (+7 more)

### Community 18 - "Unit"
Cohesion: 0.07
Nodes (46): MainWindow::lengthUnit(), ExpressionEnv, lengthUnit, lookup, ExpressionError, Quantity, angle, length (+38 more)

### Community 19 - "SketchGeometry.cpp"
Cohesion: 0.13
Nodes (9): curve(), curves(), customPlaneSpec(), interiorPoint(), planeFrame(), profileAt(), profiles(), toSketch() (+1 more)

### Community 20 - ".hitTest"
Cohesion: 0.13
Nodes (5): Hit, index, kind, x, y

### Community 21 - "Command"
Cohesion: 0.12
Nodes (20): Adding a tool, Command, getReal(), DocumentUnits, def_, InsertGeometry, def_, makeBox() (+12 more)

### Community 22 - "MainWindow.cpp"
Cohesion: 0.07
Nodes (5): commandIcon(), qs(), MainWindow::beginSketch(), MainWindow::enterSketchMode(), MainWindow::applySection()

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
Nodes (27): flatButton(), MainWindow::buildSketchTab(), QCheckBox, QLabel, QToolButton, QWidget, SketchEditor, SketchPalette (+19 more)

### Community 28 - "cmath"
Cohesion: 0.07
Nodes (18): UiCommand, enabled, icon, id, name, panel, run, shortcut (+10 more)

### Community 29 - "AdskModule.cpp"
Cohesion: 0.10
Nodes (16): Application, bindAdsk(), BRepBodies, BRepBody, index, Component, Design, Product (+8 more)

### Community 30 - "Colors"
Cohesion: 0.07
Nodes (28): Colors, base, border, cubeBox, cubeText, errorBackground, grid, gridMajor (+20 more)

### Community 31 - "TopoDS_Shape"
Cohesion: 0.24
Nodes (28): KernelError, asSolid(), boolean(), chamfer(), chamferEx(), draft(), extrude(), extrudeEx() (+20 more)

### Community 32 - "SketchOps.cpp"
Cohesion: 0.21
Nodes (19): at(), chainOf(), chamferCorner(), cornerAt(), cross(), dot(), extendLine(), filletCorner() (+11 more)

### Community 33 - "CommandSession"
Cohesion: 0.12
Nodes (8): CommandSession, inputs_, CommandRegistry::find(), CommandRegistry::run(), OwnedCommand, owned, OwningCommandSession, Session::begin()

### Community 34 - "ParameterCompleter"
Cohesion: 0.18
Nodes (8): QObject, ParameterCompleter, completer_, edit_, names_, public, QCompleter, QLineEdit

### Community 35 - "string"
Cohesion: 0.10
Nodes (28): boundingBox(), completeEdgeReferences(), completeFaceReferences(), decode(), decodeFaces(), edgeReference(), EdgeSig, full (+20 more)

### Community 36 - "ConstructAxisPoint"
Cohesion: 0.25
Nodes (3): ConstructAxisPoint, def_, kind_

### Community 37 - "Viewport.h"
Cohesion: 0.06
Nodes (16): MarkingMenu::keyPressEvent(), AnalysisKind, CurvatureMap, Draft, None, Zebra, AnalysisSettings, curvatureScale (+8 more)

### Community 38 - "solve"
Cohesion: 0.18
Nodes (12): addConstraintChecked(), Layout, n, px, py, rad, makeLayout(), pack() (+4 more)

### Community 39 - "ViewportAnalysis.cpp"
Cohesion: 0.13
Nodes (5): packed(), ramp(), shade(), Viewport::buildAnalysis(), Viewport::setCurvatureComb()

### Community 41 - "ConstraintType"
Cohesion: 0.09
Nodes (23): ConstraintType, Angle, Coincident, Collinear, Concentric, Diameter, Distance, Equal (+15 more)

### Community 42 - "TEST"
Cohesion: 0.06
Nodes (9): Session, commands_, doc_, listeners_, nextListener_, path_, param(), TEST() (+1 more)

### Community 43 - "Pick"
Cohesion: 0.14
Nodes (15): fixedColor(), freeColor(), Pick, bodyArc, bodyPoint, bodySegment, hit, midpointOf (+7 more)

### Community 44 - "Snap"
Cohesion: 0.11
Nodes (18): Snap, alignX, alignY, bodyArc, bodySegment, entity, fromX, fromY (+10 more)

### Community 45 - "Kind"
Cohesion: 0.09
Nodes (21): HudField, edit, editing, kind, locked, value, Kind, Angle (+13 more)

### Community 47 - "Zip.cpp"
Cohesion: 0.20
Nodes (11): Entry, data, name, ZipError, crc32(), get16(), get32(), put16() (+3 more)

### Community 48 - "Document.cpp"
Cohesion: 0.09
Nodes (30): ConstructionPlane, name, spec, SketchRecord, data, name, offset, plane (+22 more)

### Community 50 - "MainWindowSketch.cpp"
Cohesion: 0.08
Nodes (13): MainWindow::cancelSketch(), MainWindow::editSketch(), MainWindow::finishSketch(), MainWindow::onEdgeClicked(), MainWindow::onProfileClicked(), MainWindow::originalShape(), MainWindow::sketchPalette(), MainWindow::sketchVisible() (+5 more)

### Community 51 - "Session.cpp"
Cohesion: 0.19
Nodes (18): historyEdit(), Session::deleteFeature(), Session::deleteParameter(), Session::editFeature(), Session::newDocument(), Session::open(), Session::redo(), Session::renameBody() (+10 more)

### Community 52 - "InputDef"
Cohesion: 0.08
Nodes (24): InputDef, choices, defaultValue, id, label, max, min, minExclusive (+16 more)

### Community 54 - "MainWindowArrow.cpp"
Cohesion: 0.11
Nodes (8): ArrowPlacement, base, dir, edgePlacement(), facesPlacement(), MainWindow::patternCentre(), MainWindow::pickedFaces(), MainWindow::updateDragArrow()

### Community 55 - "string"
Cohesion: 0.08
Nodes (20): AddUserParameter, def_, checkPattern(), CircularPattern, def_, isIdentifier(), Joint, def_ (+12 more)

### Community 56 - "Command.cpp"
Cohesion: 0.22
Nodes (10): expressionKey(), checkInputValue(), CommandContext::evaluateExpression(), CommandDef::input(), CommandSession::applyInTransaction(), CommandSession::cancel(), CommandSession::execute(), CommandSession::preview() (+2 more)

### Community 57 - "FeatureEffect"
Cohesion: 0.08
Nodes (19): Body, display, name, shape, Component, bodies, name, FeatureEffect (+11 more)

### Community 58 - "Constraint"
Cohesion: 0.11
Nodes (17): Constraint, entities, expression, points, type, value, value2, SolveResult (+9 more)

### Community 59 - "xdrive.py"
Cohesion: 0.32
Nodes (14): button(), canvas(), click(), drag(), flush(), geometry(), key(), keycode() (+6 more)

### Community 61 - "DocCommands.cpp"
Cohesion: 0.08
Nodes (20): axisOf(), bodyCentre(), Combine, def_, CreateSketch, def_, differenceOrNull(), evaluateDimensions() (+12 more)

### Community 62 - "CommandDialog::CommandDialog"
Cohesion: 0.13
Nodes (5): CommandDialog::CommandDialog(), ExpressionSpinBox, eval_, expression_, shown_

### Community 63 - "ViewportArrow.cpp"
Cohesion: 0.06
Nodes (18): QMouseEvent, ViewInteractor, rgb(), segmentDistance(), Viewport::arrowAt(), Viewport::arrowMouseMove(), Viewport::arrowMousePress(), Viewport::arrowMouseRelease() (+10 more)

### Community 64 - "Document.cpp"
Cohesion: 0.09
Nodes (31): DocumentError, Document::abortTransaction(), Document::addBody(), Document::addUserParameter(), Document::axisFrame(), Document::commitTransaction(), Document::openTransaction(), Document::recompute() (+23 more)

### Community 65 - "CommandRegistry"
Cohesion: 0.12
Nodes (4): CommandRegistry, cmds_, CommandRegistry::add(), TEST()

### Community 66 - "PythonHost.cpp"
Cohesion: 0.11
Nodes (13): Result, error, ok, output, captured(), PYBIND11_EMBEDDED_MODULE(), PythonHost::exec(), PythonHost::PythonHost() (+5 more)

### Community 67 - "Vec3"
Cohesion: 0.20
Nodes (18): SurfacePoint, normal, point, Vec3, edgeMidpoint(), edgesNear(), frame(), makeCone() (+10 more)

### Community 68 - "MainWindow::MainWindow"
Cohesion: 0.12
Nodes (4): PythonHost, MainWindow::MainWindow(), MainWindow::exitSketchMode(), MainWindow::showPreferences()

### Community 69 - "FileFormat"
Cohesion: 0.17
Nodes (12): FileFormat, Brep, Iges, Obj, Step, Stl, ThreeMF, FormatInfo (+4 more)

### Community 71 - "ParametersDialog.cpp"
Cohesion: 0.14
Nodes (4): number(), ParametersDialog::ParametersDialog(), qs(), withUnit()

### Community 72 - ".apply"
Cohesion: 0.24
Nodes (5): Coil, def_, Extrude, def_, validateOperation()

### Community 73 - "TopologyCounts"
Cohesion: 0.17
Nodes (17): Section, Circular, Square, Triangular, TopologyCounts, edges, faces, shells (+9 more)

### Community 74 - "NavPreset"
Cohesion: 0.33
Nodes (4): NavPreset, Fusion, SolidWorks, Tinkercad

### Community 75 - "InputType"
Cohesion: 0.12
Nodes (17): InputType, Axis, Bodies, Body, Bool, Choice, Edges, Faces (+9 more)

### Community 76 - "ParametersDialog"
Cohesion: 0.19
Nodes (10): ParametersDialog, building_, error_, listener_, public, rebuildPending_, tree_, QLabel (+2 more)

### Community 78 - "Theme.cpp"
Cohesion: 0.19
Nodes (6): setIconTheme(), darkColors(), darkPalette(), darkStyleSheet(), lightColors(), lightStyleSheet()

### Community 79 - "optional"
Cohesion: 0.07
Nodes (22): optional, ConstructionAxis, axis, name, ConstructionPoint, name, point, Feature (+14 more)

### Community 80 - "SketchDisplay"
Cohesion: 0.08
Nodes (18): DragArrow, base, dir, value, PendingLook, center, frame, size (+10 more)

### Community 81 - "string"
Cohesion: 0.22
Nodes (11): bodyNumber(), Document::bodyShapes(), Document::effectOf(), Document::nextAxisName(), Document::nextBodyName(), Document::nextComponentName(), Document::nextPlaneName(), Document::nextPointName() (+3 more)

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
Cohesion: 0.12
Nodes (13): debug(), error(), info(), Level, Debug, Error, Info, Warning (+5 more)

### Community 86 - "README.md"
Cohesion: 0.08
Nodes (19): Architecture, How a command works, The document, Units, Build, Conventions, Development, Tests (+11 more)

### Community 87 - "Sketch.h"
Cohesion: 0.12
Nodes (11): EntityType, Arc, Circle, Line, Spline, isRound(), Profile, area (+3 more)

### Community 88 - "BoundingBox"
Cohesion: 0.29
Nodes (7): BoundingBox, max, min, dot(), faceScore(), score(), vec()

### Community 89 - "SketchEditor::SketchEditor"
Cohesion: 0.15
Nodes (5): SketchEditor::SketchEditor(), Tool, op, shape, target

### Community 91 - "Rect"
Cohesion: 0.50
Nodes (4): Session::notifyChanged(), Rect, l, p

### Community 93 - "Known differences still to build"
Cohesion: 0.15
Nodes (12): Data and files, Findings from the videos, Fusion study list, Interface, Known differences still to build, Navigation and display, Selection and the canvas, Sketch (+4 more)

### Community 96 - "sketchFor"
Cohesion: 0.18
Nodes (8): Hole, def_, Pipe, def_, Revolve, def_, sketchFor(), stringOr()

### Community 97 - "BodyFrame"
Cohesion: 0.15
Nodes (14): BodyFrame, diag, dx, dy, dz, x0, y0, z0 (+6 more)

### Community 98 - "FakeDoc"
Cohesion: 0.17
Nodes (6): FakeDoc, aborts, commits, items, open, snapshot

### Community 100 - "TsrModule.cpp"
Cohesion: 0.20
Nodes (4): bindTsr(), fromPy(), toPy(), typeName()

### Community 101 - "Zip.h"
Cohesion: 0.19
Nodes (3): slurp(), TEST(), tmp()

### Community 102 - "Theme"
Cohesion: 0.14
Nodes (6): QAbstractButton, QAction, Theme, colors_, public, styled_

### Community 103 - "DocumentError"
Cohesion: 0.11
Nodes (8): doc_(), Document::Document(), Document::expressionEnv(), Document::ocafBytes(), Document::reevaluateParameters(), ocafApplication(), Document::load(), Document::save()

### Community 104 - "cli_main.cpp"
Cohesion: 0.27
Nodes (6): listCommands(), main(), usage(), main(), smoke(), volume

### Community 106 - "SectionState"
Cohesion: 0.25
Nodes (7): SectionState, active, angle, flip, offset, plane, visible

### Community 107 - "Display"
Cohesion: 0.25
Nodes (7): Display, constraints, construction, dimensions, points, profiles, projected

### Community 110 - "Kernel.h"
Cohesion: 0.09
Nodes (22): Axis, X, Y, Z, BooleanOp, Cut, Intersect, Join (+14 more)

### Community 113 - "Mesh"
Cohesion: 0.40
Nodes (3): Mesh, nodes, triangles

### Community 114 - "uninstall.sh"
Cohesion: 0.52
Nodes (6): die(), manifest_for(), refresh(), uninstall.sh script, step(), usage()

### Community 115 - "install.sh"
Cohesion: 0.60
Nodes (5): die(), refresh(), install.sh script, step(), usage()

### Community 117 - "Column"
Cohesion: 0.33
Nodes (6): Column, kComment, kExpression, kParameter, kUnit, kValue

### Community 123 - "MarkingMenu"
Cohesion: 0.40
Nodes (3): MarkingMenu, enabled, public

### Community 132 - "ChainSegment"
Cohesion: 0.67
Nodes (3): ChainSegment, entity, forward

## Knowledge Gaps
- **630 isolated node(s):** `ok`, `output`, `error`, `isReal`, `real` (+625 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 1192 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **18 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `optional` connect `optional` to `Viewport`, `MainWindow`, `cmath`, `Kernel.cpp`, `CommandDialog`, `Io.cpp`, `Unit`, `.hitTest`, `ViewportSketch.cpp`, `SketchEditor.cpp`, `SketchOps.cpp`, `Viewport.h`, `TEST`, `.updatePreview`, `Document.cpp`, `CommandDialog::CommandDialog`, `InputDef`, `MainWindowArrow.cpp`, `DocCommands.cpp`, `CommandDialog::CommandDialog`, `ViewportArrow.cpp`, `Vec3`, `CommandDialog.cpp`, `SketchDisplay`, `Sketch.h`, `sketchFor`, `TsrModule.cpp`, `Kernel.h`?**
  _High betweenness centrality (0.135) - this node is a cross-community bridge._
- **What connects `ok`, `output`, `error` to the rest of the system?**
  _630 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Viewport` be split into smaller, more focused modules?**
  _Cohesion score 0.018459191456903126 - nodes in this community are weakly interconnected._
- **Why does `Session` connect `TEST` to `CommandRegistry`, `PythonHost.cpp`, `MainWindow`, `MainWindow::MainWindow`, `ParametersDialog.cpp`, `cli_main.cpp`, `SketchEditor`, `Document`, `ParametersDialog`, `optional`, `CommandDialog`, `Session.cpp`, `README.md`, `MainWindow.cpp`, `SketchEditor::SketchEditor`, `CommandDialog::CommandDialog`?**
  _High betweenness centrality (0.128) - this node is a cross-community bridge._
- **Should `Icons.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.06853038245000971 - nodes in this community are weakly interconnected._
- **Why does `Viewport` connect `Viewport` to `MainWindow`, `Viewport.h`, `ViewportAnalysis.cpp`, `Viewport.cpp`, `NavPreset`, `.initializeGL`, `MainWindowTools.cpp`, `SketchDisplay`, `optional`, `rect`, `.toPixels`, `ViewportArrow.cpp`?**
  _High betweenness centrality (0.123) - this node is a cross-community bridge._
- **Should `CommandDef` be split into smaller, more focused modules?**
  _Cohesion score 0.05731707317073171 - nodes in this community are weakly interconnected._