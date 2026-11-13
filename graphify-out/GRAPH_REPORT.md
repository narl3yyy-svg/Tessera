# Graph Report - tessera  (2026-11-13)

## Corpus Check
- 356 files · ~214,959 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 44 file(s) not represented in the graph (top: .drive 36, (none) 5, .cmake 1)

## Summary
- 3282 nodes · 8316 edges · 134 communities (104 shown, 30 thin omitted)
- Extraction: 84% EXTRACTED · 16% INFERRED · 0% AMBIGUOUS · INFERRED: 1308 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `a4fb47eb`
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
- dimensionOf
- Viewport.h
- Kernel.cpp
- getReal
- Kind
- MainWindowTools.cpp
- CommandDialog
- Io.cpp
- Parser
- src/main.cpp
- ViewportArrow.cpp
- .updatePreview
- TEST
- Sketch.cpp
- ViewportSketch.cpp
- SketchPalette
- Document.cpp
- .apply
- AdskModule.cpp
- Colors
- KernelError
- SketchOps.cpp
- Session.cpp
- ParameterCompleter
- SketchPalette.cpp
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
- sketchFor
- AnalysisSettings
- Document.cpp
- .add
- MainWindowSketch.cpp
- InputDef
- .toPixels
- optional
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
- FormatInfo
- CommandError
- src/main.cpp
- fromInternal
- Command.cpp
- InputType
- string
- CommandDialog::CommandDialog
- math
- string
- SketchDisplay
- .planeFrame
- Measurement
- .redrawAll
- Kernel.h
- Level
- README.md
- DocumentError
- test_feature_pattern.py
- SketchEditor::SketchEditor
- UserParameter
- UiCommand
- Known differences still to build
- CommandSession
- FeatureEffect
- PendingLook
- BodyFrame
- FakeDoc
- Zip.cpp
- BoundingBox
- sstream
- Viewport::setDragArrow
- ext
- Column
- SectionState
- Display
- Development
- PlaneEdges
- openWallBand
- ConstructionPoint
- ConstructionAxis
- uninstall.sh
- install.sh
- main
- Feature
- QTabWidget
- .openMarkingMenu
- Session::open
- cmath
- Placement
- Rect
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

## Communities (134 total, 30 thin omitted)

### Community 0 - "Viewport"
Cohesion: 0.02
Nodes (57): view_, QLineEdit, Viewport, analysis_, analysisObjects_, appliedGridStep_, arrowBoxes_, arrowDragging_ (+49 more)

### Community 1 - "Icons.cpp"
Cohesion: 0.06
Nodes (107): arc3Icon(), arcIcon(), arrow(), axisIcon(), box(), breakIcon(), centerRectIcon(), chamferIcon() (+99 more)

### Community 2 - "ViewportAnalysis.cpp"
Cohesion: 0.08
Nodes (6): MainWindow::attachArrowCompleters(), packed(), ramp(), shade(), Viewport::buildAnalysis(), Viewport::setCurvatureComb()

### Community 4 - "MainWindow"
Cohesion: 0.03
Nodes (61): CommandDialog, MainWindow, active_, arrowInput_, arrowInput2_, bodiesBeforeCommand_, combEdges_, combPicking_ (+53 more)

### Community 5 - "run_oracle.py"
Cohesion: 0.08
Nodes (54): add_point(), arc_poly(), body_at(), body_list(), build_sketch(), chain(), circumcentre(), cm() (+46 more)

### Community 6 - "Inputs"
Cohesion: 0.04
Nodes (56): Adding a tool, Command, CommandContext, CommandDef, feature, icon, id, inputs (+48 more)

### Community 7 - "Document"
Cohesion: 0.05
Nodes (14): Document, effects_, modified_, pendingTools_, registry_, replaying_, txnBodies_, FromOcaf (+6 more)

### Community 8 - "Viewport.cpp"
Cohesion: 0.07
Nodes (5): keys(), qc(), QtFrameBuffer, rgb(), Viewport::Viewport()

### Community 9 - "SketchEditor"
Cohesion: 0.03
Nodes (45): SketchEditor, arcDrag_, arcDragMoved_, arcEndsChain_, arcFrom_, arcRef_, bodyEdges_, boxing_ (+37 more)

### Community 11 - "Viewport.h"
Cohesion: 0.05
Nodes (23): QComboBox, QDialogButtonBox, QFormLayout, QLabel, QLabel, Dimension, Angle, Length (+15 more)

### Community 13 - "getReal"
Cohesion: 0.31
Nodes (10): getInt(), getReal(), makeBox(), makeCone(), makeCylinder(), makeSphere(), makeTorus(), position() (+2 more)

### Community 14 - "Kind"
Cohesion: 0.08
Nodes (22): ConstructPlane, def_, kind_, EdgeFeature, def_, kind_, Kind, Angle (+14 more)

### Community 15 - "MainWindowTools.cpp"
Cohesion: 0.06
Nodes (13): QDialog, MainWindow::chooseUnits(), MainWindow::exportDesign(), MainWindow::insertFile(), MainWindow::measurePick(), MainWindow::openMeasure(), MainWindow::sectionFrame(), MainWindow::sectionPlane() (+5 more)

### Community 16 - "CommandDialog"
Cohesion: 0.05
Nodes (27): CommandDialog, bodiesId_, bodiesLabel_, bodyInput_, buttons_, cmd_, conditional_, edgesId_ (+19 more)

### Community 17 - "Io.cpp"
Cohesion: 0.08
Nodes (25): MainWindow::print3d(), FileFormat, Brep, Iges, Obj, Step, Stl, ThreeMF (+17 more)

### Community 18 - "Parser"
Cohesion: 0.06
Nodes (47): MainWindow::lengthUnit(), ExpressionEnv, lengthUnit, lookup, ExpressionError, Quantity, angle, length (+39 more)

### Community 21 - "ViewportArrow.cpp"
Cohesion: 0.17
Nodes (6): rgb(), segmentDistance(), Viewport::arrowAt(), Viewport::arrowParam(), Viewport::dragArrowHandle(), Viewport::placeArrowBoxes()

### Community 22 - ".updatePreview"
Cohesion: 0.17
Nodes (4): angleInArc(), ccwContains(), circumcircle(), segDistance()

### Community 23 - "TEST"
Cohesion: 0.07
Nodes (8): Sketch, constraints, entities, points, texts, Sketch::addCircle(), Sketch::addLine(), TEST()

### Community 24 - "Sketch.cpp"
Cohesion: 0.10
Nodes (14): SketchError, entityTypeName(), isDimension(), Sketch::addConstraint(), Sketch::addSpline(), Sketch::addText(), Sketch::checkIndices(), Sketch::entityPoints() (+6 more)

### Community 25 - "ViewportSketch.cpp"
Cohesion: 0.08
Nodes (6): faceStyle(), lineStyle(), rgb(), Viewport::lookAt(), Viewport::planePoint(), Viewport::toWidget()

### Community 26 - "SketchPalette"
Cohesion: 0.07
Nodes (22): QLabel, QWidget, SketchEditor, SketchPalette, body_, constraints_, construction_, dimensions_ (+14 more)

### Community 27 - "Document.cpp"
Cohesion: 0.10
Nodes (11): Document::features(), Document::historyMarker(), Document::redo(), Document::removeFeature(), Document::setFeatureInputs(), Document::setFeatureSuppressed(), Document::undo(), featureData() (+3 more)

### Community 28 - ".apply"
Cohesion: 0.16
Nodes (8): Coil, def_, Extrude, def_, Primitive, build_, def_, validateOperation()

### Community 29 - "AdskModule.cpp"
Cohesion: 0.10
Nodes (16): Application, bindAdsk(), BRepBodies, BRepBody, index, Component, Design, Product (+8 more)

### Community 30 - "Colors"
Cohesion: 0.07
Nodes (28): Colors, base, border, cubeBox, cubeText, errorBackground, grid, gridMajor (+20 more)

### Community 31 - "KernelError"
Cohesion: 0.23
Nodes (29): KernelError, asSolid(), boolean(), chamfer(), chamferEx(), draft(), extrude(), extrudeEx() (+21 more)

### Community 32 - "SketchOps.cpp"
Cohesion: 0.22
Nodes (25): at(), chainOf(), chamferCorner(), circularPattern(), copyEntities(), cross(), dot(), extendLine() (+17 more)

### Community 33 - "Session.cpp"
Cohesion: 0.16
Nodes (21): historyEdit(), OwnedCommand, owned, OwningCommandSession, Session::addListener(), Session::begin(), Session::deleteFeature(), Session::deleteParameter() (+13 more)

### Community 34 - "ParameterCompleter"
Cohesion: 0.12
Nodes (8): ParameterCompleter, completer_, edit_, names_, ParameterCompleter::ParameterCompleter(), public, QCompleter, QLineEdit

### Community 35 - "SketchPalette.cpp"
Cohesion: 0.13
Nodes (6): QAbstractButton, QAction, flatButton(), QCheckBox, QToolButton, SketchPalette::SketchPalette()

### Community 37 - "MainWindow::MainWindow"
Cohesion: 0.12
Nodes (6): MainWindow::MainWindow(), MainWindow::enterSketchMode(), MainWindow::exitSketchMode(), MainWindow::showPreferences(), QTimer, Viewport::selectArrowValue()

### Community 38 - "solve"
Cohesion: 0.18
Nodes (12): addConstraintChecked(), Layout, n, px, py, rad, makeLayout(), pack() (+4 more)

### Community 40 - "Constraint"
Cohesion: 0.07
Nodes (23): ext(), fixedColor(), freeColor(), qc(), rgb(), wire(), Constraint, driven (+15 more)

### Community 41 - "ConstraintType"
Cohesion: 0.08
Nodes (25): ConstraintType, Angle, Coincident, Collinear, Concentric, Diameter, Distance, Equal (+17 more)

### Community 43 - "Pick"
Cohesion: 0.13
Nodes (14): Pick, bodyArc, bodyPoint, bodySegment, hit, midpointOf, onEntity, onXAxis (+6 more)

### Community 44 - "Snap"
Cohesion: 0.10
Nodes (18): Snap, alignX, alignY, bodyArc, bodySegment, entity, fromX, fromY (+10 more)

### Community 45 - "Kind"
Cohesion: 0.09
Nodes (21): HudField, edit, editing, kind, locked, value, Kind, Angle (+13 more)

### Community 46 - "sketchFor"
Cohesion: 0.16
Nodes (9): Hole, def_, Pipe, def_, Revolve, def_, sectionOf(), sketchFor() (+1 more)

### Community 47 - "AnalysisSettings"
Cohesion: 0.15
Nodes (13): AnalysisKind, CurvatureMap, Draft, None, Zebra, AnalysisSettings, curvatureScale, draftAngle (+5 more)

### Community 48 - "Document.cpp"
Cohesion: 0.12
Nodes (22): ConstructionPlane, name, spec, Document::axes(), Document::bodies(), Document::body(), Document::bodyName(), Document::components() (+14 more)

### Community 50 - "MainWindowSketch.cpp"
Cohesion: 0.05
Nodes (20): MainWindow::cancelSketch(), MainWindow::editSketch(), MainWindow::finishSketch(), MainWindow::onProfileClicked(), MainWindow::originalShape(), MainWindow::sketchPalette(), MainWindow::sketchVisible(), MainWindow::startSketch() (+12 more)

### Community 51 - "InputDef"
Cohesion: 0.09
Nodes (21): InputDef, choices, defaultValue, id, label, max, min, minExclusive (+13 more)

### Community 54 - "optional"
Cohesion: 0.21
Nodes (8): ArrowPlacement, base, dir, edgePlacement(), facesPlacement(), MainWindow::patternCentre(), MainWindow::pickedFaces(), optional

### Community 56 - "Theme.cpp"
Cohesion: 0.19
Nodes (6): setIconTheme(), darkColors(), darkPalette(), darkStyleSheet(), lightColors(), lightStyleSheet()

### Community 57 - "MainWindow.cpp"
Cohesion: 0.13
Nodes (3): commandIcon(), qs(), MainWindow::applySection()

### Community 58 - "Entity"
Cohesion: 0.09
Nodes (21): Entity, a, b, center, construction, fit, projected, radius (+13 more)

### Community 59 - "xdrive.py"
Cohesion: 0.32
Nodes (14): button(), canvas(), click(), drag(), flush(), geometry(), key(), keycode() (+6 more)

### Community 61 - "SketchGeometry.cpp"
Cohesion: 0.10
Nodes (16): Profile, area, face, x, y, curve(), curves(), customPlaneSpec() (+8 more)

### Community 62 - "Session"
Cohesion: 0.09
Nodes (9): main(), smoke(), Session, commands_, doc_, listeners_, nextListener_, path_ (+1 more)

### Community 63 - "QMouseEvent"
Cohesion: 0.10
Nodes (11): MarkingMenu::keyPressEvent(), QKeyEvent, QMouseEvent, ViewInteractor, Viewport::frontEdgeOwner(), Viewport::arrowMouseMove(), Viewport::arrowMousePress(), Viewport::arrowMouseRelease() (+3 more)

### Community 64 - "string"
Cohesion: 0.10
Nodes (28): boundingBox(), completeEdgeReferences(), completeFaceReferences(), decode(), decodeFaces(), edgeReference(), EdgeSig, full (+20 more)

### Community 65 - "CommandRegistry"
Cohesion: 0.12
Nodes (4): CommandRegistry, cmds_, CommandRegistry::add(), TEST()

### Community 66 - "cmath"
Cohesion: 0.11
Nodes (11): PythonHost, Result, error, ok, output, captured(), PYBIND11_EMBEDDED_MODULE(), PythonHost::exec() (+3 more)

### Community 67 - "TopoDS_Shape"
Cohesion: 0.20
Nodes (18): SurfacePoint, normal, point, Vec3, edgeMidpoint(), edgesNear(), frame(), makeCone() (+10 more)

### Community 68 - "Theme"
Cohesion: 0.22
Nodes (4): Theme, colors_, public, styled_

### Community 69 - "FormatInfo"
Cohesion: 0.40
Nodes (5): FormatInfo, canImport, extensions, format, name

### Community 70 - "CommandError"
Cohesion: 0.09
Nodes (29): CommandError, getBool(), applyOperation(), axisOf(), bodyCentre(), bodyName(), Combine, def_ (+21 more)

### Community 71 - "src/main.cpp"
Cohesion: 0.11
Nodes (13): number(), ParametersDialog, building_, error_, listener_, ParametersDialog::ParametersDialog(), public, rebuildPending_ (+5 more)

### Community 72 - "fromInternal"
Cohesion: 0.21
Nodes (12): MainWindow::checkInterference(), MainWindow::driveJoints(), MainWindow::formatLength(), MainWindow::gridSettings(), MainWindow::openAnalysis(), MainWindow::openSection(), MainWindow::updateMeasure(), qs() (+4 more)

### Community 74 - "Command.cpp"
Cohesion: 0.22
Nodes (11): expressionKey(), checkInputValue(), CommandContext::evaluateExpression(), CommandDef::input(), CommandSession::applyInTransaction(), CommandSession::cancel(), CommandSession::execute(), CommandSession::preview() (+3 more)

### Community 75 - "InputType"
Cohesion: 0.09
Nodes (21): bindTsr(), fromPy(), toPy(), typeName(), InputType, Axis, Bodies, Body (+13 more)

### Community 76 - "string"
Cohesion: 0.15
Nodes (15): bodyNumber(), Document::component(), Document::componentOfBody(), Document::nextAxisName(), Document::nextBodyName(), Document::nextComponentName(), Document::nextDimensionName(), Document::nextPlaneName() (+7 more)

### Community 77 - "CommandDialog::CommandDialog"
Cohesion: 0.13
Nodes (5): CommandDialog::CommandDialog(), ExpressionSpinBox, eval_, expression_, shown_

### Community 79 - "string"
Cohesion: 0.18
Nodes (5): AddUserParameter, def_, isIdentifier(), NewComponent, def_

### Community 80 - "SketchDisplay"
Cohesion: 0.12
Nodes (11): ProfileObject, index, sketch, SketchDisplay, construction, curves, fixedCurves, frame (+3 more)

### Community 81 - ".planeFrame"
Cohesion: 0.21
Nodes (6): Loft, def_, profilesOf(), profiles, Sweep, def_

### Community 82 - "Measurement"
Cohesion: 0.13
Nodes (14): Kind, Angle, Area, Length, Volume, Measurement, from, hasLine (+6 more)

### Community 83 - ".redrawAll"
Cohesion: 0.13
Nodes (7): NavPreset, Fusion, SolidWorks, Tinkercad, Viewport::clearDragArrow(), Viewport::clearSecondArrow(), Viewport::setInteractor()

### Community 84 - "Kernel.h"
Cohesion: 0.09
Nodes (22): Axis, X, Y, Z, BooleanOp, Cut, Intersect, Join (+14 more)

### Community 85 - "Level"
Cohesion: 0.16
Nodes (13): debug(), error(), info(), Level, Debug, Error, Info, Warning (+5 more)

### Community 86 - "README.md"
Cohesion: 0.11
Nodes (15): Architecture, How a command works, The document, Units, Reference parts, Fusion feature checklist, Roadmap, Contents (+7 more)

### Community 87 - "DocumentError"
Cohesion: 0.11
Nodes (16): DocumentError, Document::abortTransaction(), Document::addBody(), Document::addUserParameter(), Document::axisFrame(), Document::bodyShapes(), Document::commitTransaction(), Document::effectOf() (+8 more)

### Community 89 - "SketchEditor::SketchEditor"
Cohesion: 0.11
Nodes (10): QObject, Hit, index, kind, SketchEditor::SketchEditor(), edges, Tool, op (+2 more)

### Community 90 - "UserParameter"
Cohesion: 0.33
Nodes (6): UserParameter, comment, expression, name, unit, value

### Community 91 - "UiCommand"
Cohesion: 0.14
Nodes (11): UiCommand, enabled, icon, id, name, panel, run, shortcut (+3 more)

### Community 93 - "Known differences still to build"
Cohesion: 0.15
Nodes (12): Data and files, Findings from the videos, Fusion study list, Interface, Known differences still to build, Navigation and display, Selection and the canvas, Sketch (+4 more)

### Community 94 - "CommandSession"
Cohesion: 0.17
Nodes (4): CommandSession, inputs_, CommandRegistry::find(), CommandRegistry::run()

### Community 95 - "FeatureEffect"
Cohesion: 0.08
Nodes (19): Body, display, name, shape, Component, bodies, name, FeatureEffect (+11 more)

### Community 96 - "PendingLook"
Cohesion: 0.18
Nodes (8): DragArrow, base, dir, value, PendingLook, center, frame, size

### Community 97 - "BodyFrame"
Cohesion: 0.15
Nodes (14): BodyFrame, diag, dx, dy, dz, x0, y0, z0 (+6 more)

### Community 98 - "FakeDoc"
Cohesion: 0.17
Nodes (6): FakeDoc, aborts, commits, items, open, snapshot

### Community 100 - "Zip.cpp"
Cohesion: 0.11
Nodes (14): Entry, data, name, ZipError, crc32(), get16(), get32(), put16() (+6 more)

### Community 101 - "BoundingBox"
Cohesion: 0.29
Nodes (7): BoundingBox, max, min, dot(), faceScore(), score(), vec()

### Community 102 - "sstream"
Cohesion: 0.11
Nodes (8): doc_(), Document::Document(), Document::ocafBytes(), Document::parameterUsers(), Document::reevaluateParameters(), ocafApplication(), Document::load(), Document::save()

### Community 104 - "ext"
Cohesion: 0.14
Nodes (13): SketchRecord, data, name, offset, plane, Document::openTransaction(), Document::recompute(), Document::recordFeature() (+5 more)

### Community 105 - "Column"
Cohesion: 0.33
Nodes (6): Column, kComment, kExpression, kParameter, kUnit, kValue

### Community 106 - "SectionState"
Cohesion: 0.25
Nodes (7): SectionState, active, angle, flip, offset, plane, visible

### Community 107 - "Display"
Cohesion: 0.25
Nodes (7): Display, constraints, construction, dimensions, points, profiles, projected

### Community 108 - "Development"
Cohesion: 0.40
Nodes (4): Build, Conventions, Development, Tests

### Community 109 - "PlaneEdges"
Cohesion: 0.20
Nodes (5): PlaneEdges, arcs, curves, segments, vertices

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
Cohesion: 0.24
Nodes (3): listCommands(), main(), usage()

### Community 118 - "Feature"
Cohesion: 0.22
Nodes (9): Feature, commandId, error, id, inputs, name, rolledBack, suppressed (+1 more)

### Community 120 - ".openMarkingMenu"
Cohesion: 0.10
Nodes (3): MainWindow::beginSketch(), MainWindow::buildSketchTab(), MainWindow::buildUiCommands()

### Community 122 - "cmath"
Cohesion: 0.12
Nodes (8): MarkingMenu, enabled, public, Case, name, fail(), Failure, Register

### Community 123 - "Placement"
Cohesion: 0.25
Nodes (7): Placement, angle, cx, cy, dx, dy, scale

### Community 124 - "Rect"
Cohesion: 0.50
Nodes (4): Session::notifyChanged(), Rect, l, p

### Community 125 - "rect"
Cohesion: 0.28
Nodes (3): SelectionBox, crossing, rect()

### Community 127 - "Joints"
Cohesion: 0.36
Nodes (3): cornerAt(), Joints, parent_

## Knowledge Gaps
- **666 isolated node(s):** `ok`, `output`, `error`, `isReal`, `real` (+661 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 1256 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **30 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `optional` connect `optional` to `Viewport`, `MainWindow`, `dimensionOf`, `Viewport.h`, `Kernel.cpp`, `Io.cpp`, `Parser`, `SketchEditor.cpp`, `ViewportArrow.cpp`, `ViewportSketch.cpp`, `CommandDialog.cpp`, `Constraint`, `sketchFor`, `Document.cpp`, `InputDef`, `Session`, `TopoDS_Shape`, `CommandError`, `string`, `CommandDialog::CommandDialog`, `Kernel.h`, `PendingLook`, `ext`, `ConstructionPoint`, `ConstructionAxis`, `Feature`, `Joints`?**
  _High betweenness centrality (0.112) - this node is a cross-community bridge._
- **What connects `ok`, `output`, `error` to the rest of the system?**
  _666 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Viewport` be split into smaller, more focused modules?**
  _Cohesion score 0.017978190391983496 - nodes in this community are weakly interconnected._
- **Why does `Viewport` connect `Viewport` to `ViewportAnalysis.cpp`, `MainWindow`, `Viewport.cpp`, `Viewport.h`, `src/main.cpp`, `ViewportArrow.cpp`, `MainWindow::MainWindow`, `AnalysisSettings`, `.toPixels`, `optional`, `QMouseEvent`, `fromInternal`, `QTimer`, `SketchDisplay`, `.redrawAll`, `.selectedSubShapes`, `PendingLook`, `Viewport::setDragArrow`, `.leaveEvent`, `rect`?**
  _High betweenness centrality (0.099) - this node is a cross-community bridge._
- **Should `Icons.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.06081754735792622 - nodes in this community are weakly interconnected._
- **Why does `SketchEditor` connect `SketchEditor` to `Viewport`, `Constraint`, `Display`, `Viewport.h`, `PlaneEdges`, `Kind`, `Pick`, `Snap`, `Parser`, `SketchEditor.cpp`, `.updatePreview`, `Text`, `SketchEditor::SketchEditor`, `Entity`, `Session`, `QMouseEvent`?**
  _High betweenness centrality (0.092) - this node is a cross-community bridge._
- **Should `ViewportAnalysis.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.07862903225806452 - nodes in this community are weakly interconnected._