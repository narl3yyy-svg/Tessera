# Graph Report - tessera  (2026-11-12)

## Corpus Check
- 326 files · ~185,250 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 24 file(s) not represented in the graph (top: .drive 16, (none) 5, .cmake 1)

## Summary
- 3033 nodes · 7526 edges · 139 communities (114 shown, 25 thin omitted)
- Extraction: 85% EXTRACTED · 15% INFERRED · 0% AMBIGUOUS · INFERRED: 1147 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `580908c3`
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
- CommandError
- optional
- Kernel.cpp
- MainWindowTools.cpp
- MainWindowSketch.cpp
- Unit
- CommandDialog
- Io.cpp
- Parser
- SketchGeometry.cpp
- ViewportAnalysis.cpp
- Expression.cpp
- MainWindow.cpp
- TEST
- Sketch.cpp
- Zip.cpp
- SketchPalette
- QMouseEvent
- AdskModule.cpp
- Colors
- TopoDS_Shape
- SketchOps.cpp
- ViewportSketch.cpp
- ParameterCompleter
- BodyFrame
- nameOf
- AnalysisSettings
- solve
- Viewport::arrowMouseMove
- ConstructAxisPoint
- ConstraintType
- TEST
- Pick
- Snap
- Kind
- .redrawAll
- string
- Document.cpp
- CommandDialog::CommandDialog
- .openMarkingMenu
- Session.cpp
- choice
- .toPixels
- MainWindowArrow.cpp
- sketchFor
- QObject
- ParametersDialog.cpp
- Constraint
- xdrive.py
- SketchPalette.cpp
- FeatureEffect
- patternFeatures
- DocumentError
- CommandRegistry
- PythonHost.cpp
- Vec3
- MainWindow::MainWindow
- CommandDialog.cpp
- QString
- ParametersDialog
- ext
- TopologyCounts
- Command.cpp
- InputType
- Kind
- Session
- Theme.cpp
- .solveAndShow
- SketchDisplay
- string
- Measurement
- EdgeSig
- Entity
- Level
- README.md
- .projectAt
- Tool
- InputDef
- string
- Viewport.h
- Known differences still to build
- CommandSession
- .add
- MainWindow::onEdgeClicked
- FileFormat
- FakeDoc
- UiCommand
- MainWindow::buildUiCommands
- Theme
- OcafApp.h
- cli_main.cpp
- writeLiveGeometry
- SectionState
- Display
- Log.h
- Feature
- Primitive
- NewComponent
- planeChoice
- uninstall.sh
- install.sh
- Column
- ConstructionPoint
- Value.h
- Architecture
- Development
- BRepBody
- smoke
- MarkingMenu
- .CircularPattern
- Dimension
- Axis
- BooleanOp
- ThreadInfo
- Push
- OwnedCommand
- ChamferType
- ChainSegment
- LAB_NOTES.md
- Session::addListener
- Session::notifyChanged
- build.sh
- live-test.sh

## God Nodes (most connected - your core abstractions)
1. `Viewport` - 201 edges
2. `MainWindow` - 157 edges
3. `SketchEditor` - 154 edges
4. `Inputs` - 135 edges
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
- `Architecture` --references--> `InputDef`  [INFERRED]
  docs/ARCHITECTURE.md → modules/core/include/tsr/core/Command.h
- `Architecture` --references--> `CommandDef`  [INFERRED]
  docs/ARCHITECTURE.md → modules/core/include/tsr/core/Command.h
- `Architecture` --references--> `CommandRegistry`  [INFERRED]
  docs/ARCHITECTURE.md → modules/core/include/tsr/core/CommandRegistry.h

## Import Cycles
- None detected.

## Communities (139 total, 25 thin omitted)

### Community 0 - "Viewport"
Cohesion: 0.02
Nodes (49): view_, QLineEdit, Viewport, analysis_, analysisObjects_, appliedGridStep_, arrowBoxes_, arrowDragging_ (+41 more)

### Community 1 - "Icons.cpp"
Cohesion: 0.07
Nodes (92): arcIcon(), arrow(), axisIcon(), box(), centerRectIcon(), chamferIcon(), circleIcon(), coilIcon() (+84 more)

### Community 2 - "DocCommands.cpp"
Cohesion: 0.04
Nodes (65): Adding a tool, Command, CommandDef, feature, icon, id, inputs, name (+57 more)

### Community 4 - "MainWindow"
Cohesion: 0.03
Nodes (55): Known gaps, CommandDialog, MainWindow, active_, arrowInput_, arrowInput2_, bodiesBeforeCommand_, combEdges_ (+47 more)

### Community 5 - "run_oracle.py"
Cohesion: 0.08
Nodes (54): add_point(), arc_poly(), body_at(), body_list(), build_sketch(), chain(), circumcentre(), cm() (+46 more)

### Community 6 - "Inputs"
Cohesion: 0.09
Nodes (11): CommandContext, Inputs, CommandSession::CommandSession(), checkBody(), checkPattern(), defaultBody(), isIdentifier(), RectangularPattern (+3 more)

### Community 7 - "Document"
Cohesion: 0.04
Nodes (14): Document, effects_, modified_, pendingTools_, registry_, replaying_, txnBodies_, FromOcaf (+6 more)

### Community 8 - "Viewport.cpp"
Cohesion: 0.05
Nodes (5): keys(), qc(), QtFrameBuffer, rgb(), Viewport::Viewport()

### Community 9 - "SketchEditor"
Cohesion: 0.04
Nodes (39): SketchEditor, arcDrag_, arcDragMoved_, arcEndsChain_, arcFrom_, arcRef_, bodyEdges_, chainStart_ (+31 more)

### Community 10 - "CommandError"
Cohesion: 0.12
Nodes (22): CommandError, getBool(), getReal(), applyOperation(), bodyCentre(), bodyName(), Extrude, def_ (+14 more)

### Community 11 - "optional"
Cohesion: 0.11
Nodes (4): optional, CommandRegistry::all(), fail(), Failure

### Community 13 - "MainWindowTools.cpp"
Cohesion: 0.06
Nodes (14): QDialog, MainWindow::chooseUnits(), MainWindow::exportDesign(), MainWindow::insertFile(), MainWindow::measurePick(), MainWindow::openAnalysis(), MainWindow::openMeasure(), MainWindow::sectionFrame() (+6 more)

### Community 14 - "MainWindowSketch.cpp"
Cohesion: 0.06
Nodes (9): grabWindowWithPanels(), MainWindow::cancelSketch(), MainWindow::editSketch(), MainWindow::finishSketch(), MainWindow::sketchPalette(), MainWindow::sketchVisible(), MainWindow::startSketch(), MainWindow::updateProfilePicking() (+1 more)

### Community 15 - "Unit"
Cohesion: 0.10
Nodes (27): bindAdsk(), MainWindow::checkInterference(), MainWindow::driveJoints(), MainWindow::formatLength(), MainWindow::gridSettings(), MainWindow::lengthUnit(), MainWindow::openSection(), MainWindow::updateMeasure() (+19 more)

### Community 16 - "CommandDialog"
Cohesion: 0.05
Nodes (29): CommandDialog, bodiesId_, bodiesLabel_, bodyInput_, buttons_, cmd_, conditional_, edgesId_ (+21 more)

### Community 17 - "Io.cpp"
Cohesion: 0.10
Nodes (18): MainWindow::print3d(), NamedShape, compoundOf(), exportShapes(), fmt(), formatForPath(), fromBrep(), importShape() (+10 more)

### Community 18 - "Parser"
Cohesion: 0.18
Nodes (14): Quantity, angle, length, value, describe(), isIdentChar(), isIdentStart(), Parser (+6 more)

### Community 19 - "SketchGeometry.cpp"
Cohesion: 0.10
Nodes (14): Profile, area, face, x, y, curve(), curves(), customPlaneSpec() (+6 more)

### Community 20 - "ViewportAnalysis.cpp"
Cohesion: 0.09
Nodes (9): packed(), ramp(), shade(), Viewport::buildAnalysis(), segmentDistance(), Viewport::arrowAt(), Viewport::arrowParam(), Viewport::dragArrowHandle() (+1 more)

### Community 21 - "Expression.cpp"
Cohesion: 0.12
Nodes (16): ExpressionEnv, lengthUnit, lookup, ExpressionError, evaluateExpression(), evaluateQuantity(), expressionReferences(), isConstantName() (+8 more)

### Community 22 - "MainWindow.cpp"
Cohesion: 0.12
Nodes (3): commandIcon(), qs(), MainWindow::applySection()

### Community 23 - "TEST"
Cohesion: 0.08
Nodes (7): Sketch, constraints, entities, points, Sketch::addCircle(), Sketch::addLine(), TEST()

### Community 24 - "Sketch.cpp"
Cohesion: 0.09
Nodes (16): Point, x, y, SketchError, entityTypeName(), isDimension(), Sketch::addSpline(), Sketch::checkIndices() (+8 more)

### Community 25 - "Zip.cpp"
Cohesion: 0.11
Nodes (14): Entry, data, name, ZipError, crc32(), get16(), get32(), put16() (+6 more)

### Community 26 - "SketchPalette"
Cohesion: 0.07
Nodes (22): QLabel, QWidget, SketchEditor, SketchPalette, body_, constraints_, construction_, dimensions_ (+14 more)

### Community 28 - "QMouseEvent"
Cohesion: 0.09
Nodes (11): MarkingMenu::keyPressEvent(), MarkingMenu::MarkingMenu(), MarkingMenu::mouseMoveEvent(), MarkingMenu::paintEvent(), MarkingMenu::popupAt(), MarkingMenu::ringIndexAt(), MarkingMenu::run(), MarkingMenu::triggerForTest() (+3 more)

### Community 29 - "AdskModule.cpp"
Cohesion: 0.09
Nodes (17): Application, BRepBodies, Component, Design, Product, raiseIfError(), UserParameter, name (+9 more)

### Community 30 - "Colors"
Cohesion: 0.07
Nodes (28): Colors, base, border, cubeBox, cubeText, errorBackground, grid, gridMajor (+20 more)

### Community 31 - "TopoDS_Shape"
Cohesion: 0.26
Nodes (25): KernelError, asSolid(), boolean(), chamfer(), chamferEx(), draft(), extrude(), extrudeEx() (+17 more)

### Community 32 - "SketchOps.cpp"
Cohesion: 0.21
Nodes (19): at(), chainOf(), chamferCorner(), cornerAt(), cross(), dot(), extendLine(), filletCorner() (+11 more)

### Community 33 - "ViewportSketch.cpp"
Cohesion: 0.09
Nodes (6): faceStyle(), lineStyle(), rgb(), Viewport::lookAt(), Viewport::planePoint(), Viewport::toWidget()

### Community 34 - "ParameterCompleter"
Cohesion: 0.12
Nodes (9): MainWindow::attachArrowCompleters(), ParameterCompleter, completer_, edit_, names_, ParameterCompleter::ParameterCompleter(), public, QCompleter (+1 more)

### Community 35 - "BodyFrame"
Cohesion: 0.10
Nodes (20): BodyFrame, diag, dx, dy, dz, x0, y0, z0 (+12 more)

### Community 36 - "nameOf"
Cohesion: 0.15
Nodes (20): ConstructionPlane, name, spec, Document::axes(), Document::components(), Document::features(), Document::lengthUnit(), Document::plane() (+12 more)

### Community 37 - "AnalysisSettings"
Cohesion: 0.08
Nodes (21): AnalysisKind, CurvatureMap, Draft, None, Zebra, AnalysisSettings, curvatureScale, draftAngle (+13 more)

### Community 38 - "solve"
Cohesion: 0.18
Nodes (12): addConstraintChecked(), Layout, n, px, py, rad, makeLayout(), pack() (+4 more)

### Community 39 - "Viewport::arrowMouseMove"
Cohesion: 0.10
Nodes (9): rgb(), Viewport::arrowMouseMove(), Viewport::arrowMousePress(), Viewport::arrowMouseRelease(), Viewport::dragArrowForTest(), Viewport::emitArrow(), Viewport::rebuildArrow(), Viewport::rebuildArrows() (+1 more)

### Community 40 - "ConstructAxisPoint"
Cohesion: 0.19
Nodes (5): ConstructAxisPoint, def_, kind_, JointPick, frame

### Community 41 - "ConstraintType"
Cohesion: 0.09
Nodes (23): ConstraintType, Angle, Coincident, Collinear, Concentric, Diameter, Distance, Equal (+15 more)

### Community 42 - "TEST"
Cohesion: 0.09
Nodes (3): param(), TEST(), tmp()

### Community 43 - "Pick"
Cohesion: 0.13
Nodes (17): fixedColor(), freeColor(), Pick, bodyArc, bodyPoint, bodySegment, hit, midpointOf (+9 more)

### Community 44 - "Snap"
Cohesion: 0.10
Nodes (19): ext(), Snap, alignX, alignY, bodyArc, bodySegment, entity, fromX (+11 more)

### Community 45 - "Kind"
Cohesion: 0.09
Nodes (21): HudField, edit, editing, kind, locked, value, Kind, Angle (+13 more)

### Community 46 - ".redrawAll"
Cohesion: 0.10
Nodes (8): NavPreset, Fusion, SolidWorks, Tinkercad, Viewport::setCurvatureComb(), Viewport::clearDragArrow(), Viewport::clearSecondArrow(), Viewport::setInteractor()

### Community 47 - "string"
Cohesion: 0.10
Nodes (15): ConstructionAxis, axis, name, UserParameter, comment, expression, name, unit (+7 more)

### Community 48 - "Document.cpp"
Cohesion: 0.10
Nodes (7): Document::addUserParameter(), Document::bodies(), Document::body(), Document::redo(), Document::undo(), Document::userParameter(), Document::userParameters()

### Community 49 - "CommandDialog::CommandDialog"
Cohesion: 0.12
Nodes (5): CommandDialog::CommandDialog(), ExpressionSpinBox, eval_, expression_, shown_

### Community 50 - ".openMarkingMenu"
Cohesion: 0.13
Nodes (4): run, MainWindow::buildSketchTab(), MainWindow::enterSketchMode(), MarkingMenu::mouseReleaseEvent()

### Community 51 - "Session.cpp"
Cohesion: 0.20
Nodes (14): historyEdit(), Session::begin(), Session::deleteFeature(), Session::deleteParameter(), Session::editFeature(), Session::newDocument(), Session::open(), Session::redo() (+6 more)

### Community 52 - "choice"
Cohesion: 0.20
Nodes (4): addOperationInputs(), bodyInput(), choice(), commonDef()

### Community 54 - "MainWindowArrow.cpp"
Cohesion: 0.13
Nodes (7): ArrowPlacement, base, dir, edgePlacement(), facesPlacement(), MainWindow::patternCentre(), MainWindow::pickedFaces()

### Community 55 - "sketchFor"
Cohesion: 0.12
Nodes (8): getInt(), Loft, def_, PathPattern, def_, Pipe, def_, sketchFor()

### Community 56 - "QObject"
Cohesion: 0.13
Nodes (3): QObject, SketchEditor::SketchEditor(), edges

### Community 57 - "ParametersDialog.cpp"
Cohesion: 0.15
Nodes (3): number(), ParametersDialog::ParametersDialog(), withUnit()

### Community 58 - "Constraint"
Cohesion: 0.11
Nodes (17): Constraint, entities, expression, points, type, value, value2, SolveResult (+9 more)

### Community 59 - "xdrive.py"
Cohesion: 0.32
Nodes (14): button(), canvas(), click(), drag(), flush(), geometry(), key(), keycode() (+6 more)

### Community 61 - "SketchPalette.cpp"
Cohesion: 0.16
Nodes (4): flatButton(), QCheckBox, QToolButton, SketchPalette::SketchPalette()

### Community 62 - "FeatureEffect"
Cohesion: 0.11
Nodes (13): Body, name, shape, Component, bodies, name, FeatureEffect, bodies (+5 more)

### Community 63 - "patternFeatures"
Cohesion: 0.20
Nodes (9): Combine, def_, CopyFn, differenceOrNull(), patternFeatures(), placeCopies(), runPattern(), splitNames() (+1 more)

### Community 64 - "DocumentError"
Cohesion: 0.16
Nodes (15): DocumentError, Document::abortTransaction(), Document::addBody(), Document::bodyShapes(), Document::commitTransaction(), Document::effectOf(), Document::removeBody(), Document::removeFeature() (+7 more)

### Community 65 - "CommandRegistry"
Cohesion: 0.12
Nodes (4): CommandRegistry, cmds_, CommandRegistry::add(), TEST()

### Community 66 - "PythonHost.cpp"
Cohesion: 0.14
Nodes (11): Result, error, ok, output, captured(), PythonHost::exec(), PythonHost::runScript(), Case (+3 more)

### Community 67 - "Vec3"
Cohesion: 0.23
Nodes (16): Vec3, boundingBox(), edgeMidpoint(), edgesNear(), frame(), makeBox(), makeCone(), makeCylinder() (+8 more)

### Community 68 - "MainWindow::MainWindow"
Cohesion: 0.12
Nodes (5): PythonHost, MainWindow::MainWindow(), MainWindow::beginSketch(), MainWindow::exitSketchMode(), MainWindow::showPreferences()

### Community 70 - "QString"
Cohesion: 0.16
Nodes (3): formatNumber(), inputExpression(), dimensionOf()

### Community 71 - "ParametersDialog"
Cohesion: 0.15
Nodes (11): ParametersDialog, building_, error_, listener_, public, rebuildPending_, tree_, QLabel (+3 more)

### Community 72 - "ext"
Cohesion: 0.16
Nodes (14): SketchRecord, data, name, offset, plane, Document::openTransaction(), Document::recompute(), Document::recordFeature() (+6 more)

### Community 73 - "TopologyCounts"
Cohesion: 0.18
Nodes (16): Section, Circular, Square, Triangular, TopologyCounts, edges, faces, shells (+8 more)

### Community 74 - "Command.cpp"
Cohesion: 0.22
Nodes (10): expressionKey(), checkInputValue(), CommandContext::evaluateExpression(), CommandDef::input(), CommandSession::applyInTransaction(), CommandSession::cancel(), CommandSession::execute(), CommandSession::preview() (+2 more)

### Community 75 - "InputType"
Cohesion: 0.12
Nodes (17): InputType, Axis, Bodies, Body, Bool, Choice, Edges, Faces (+9 more)

### Community 76 - "Kind"
Cohesion: 0.12
Nodes (16): Kind, Angle, AxisCylinder, AxisEdge, AxisTwoPlanes, AxisTwoPoints, Chamfer, Draft (+8 more)

### Community 77 - "Session"
Cohesion: 0.12
Nodes (7): PythonHost::PythonHost(), Session, commands_, doc_, listeners_, nextListener_, path_

### Community 78 - "Theme.cpp"
Cohesion: 0.19
Nodes (6): setIconTheme(), darkColors(), darkPalette(), darkStyleSheet(), lightColors(), lightStyleSheet()

### Community 80 - "SketchDisplay"
Cohesion: 0.13
Nodes (10): ProfileObject, index, sketch, SketchDisplay, construction, curves, frame, name (+2 more)

### Community 81 - "string"
Cohesion: 0.21
Nodes (12): bodyNumber(), Document::axisFrame(), Document::component(), Document::componentOfBody(), Document::nextAxisName(), Document::nextBodyName(), Document::nextComponentName(), Document::nextPlaneName() (+4 more)

### Community 82 - "Measurement"
Cohesion: 0.13
Nodes (14): Kind, Angle, Area, Length, Volume, Measurement, from, hasLine (+6 more)

### Community 83 - "EdgeSig"
Cohesion: 0.14
Nodes (14): BoundingBox, max, min, dot(), EdgeSig, full, normals, point (+6 more)

### Community 84 - "Entity"
Cohesion: 0.13
Nodes (15): Entity, a, b, center, construction, fit, projected, radius (+7 more)

### Community 85 - "Level"
Cohesion: 0.16
Nodes (7): Level, Debug, Error, Info, Warning, name(), write()

### Community 86 - "README.md"
Cohesion: 0.14
Nodes (11): Reference parts, Fusion feature checklist, Roadmap, Contents, Development, Features, Install, License (+3 more)

### Community 87 - ".projectAt"
Cohesion: 0.16
Nodes (4): PlaneEdges, arcs, segments, vertices

### Community 89 - "Tool"
Cohesion: 0.15
Nodes (7): Hit, index, kind, Tool, op, shape, target

### Community 90 - "InputDef"
Cohesion: 0.14
Nodes (12): InputDef, choices, defaultValue, id, label, max, min, minExclusive (+4 more)

### Community 91 - "string"
Cohesion: 0.31
Nodes (12): completeEdgeReferences(), completeFaceReferences(), decode(), decodeFaces(), edgeReference(), encode(), encodeFace(), faceReference() (+4 more)

### Community 93 - "Known differences still to build"
Cohesion: 0.15
Nodes (12): Data and files, Findings from the videos, Fusion study list, Interface, Known differences still to build, Navigation and display, Selection and the canvas, Sketch (+4 more)

### Community 94 - "CommandSession"
Cohesion: 0.17
Nodes (4): CommandSession, inputs_, CommandRegistry::find(), CommandRegistry::run()

### Community 96 - "MainWindow::onEdgeClicked"
Cohesion: 0.21
Nodes (5): MainWindow::onEdgeClicked(), MainWindow::onProfileClicked(), MainWindow::originalShape(), MainWindow::syncPickedShapes(), MainWindow::toOriginal()

### Community 97 - "FileFormat"
Cohesion: 0.17
Nodes (12): FileFormat, Brep, Iges, Obj, Step, Stl, ThreeMF, FormatInfo (+4 more)

### Community 98 - "FakeDoc"
Cohesion: 0.17
Nodes (6): FakeDoc, aborts, commits, items, open, snapshot

### Community 99 - "UiCommand"
Cohesion: 0.18
Nodes (9): UiCommand, enabled, icon, id, name, panel, shortcut, tab (+1 more)

### Community 102 - "Theme"
Cohesion: 0.22
Nodes (4): Theme, colors_, public, styled_

### Community 103 - "OcafApp.h"
Cohesion: 0.22
Nodes (4): doc_(), Document::Document(), Document::ocafBytes(), ocafApplication()

### Community 104 - "cli_main.cpp"
Cohesion: 0.36
Nodes (4): listCommands(), main(), usage(), main()

### Community 105 - "writeLiveGeometry"
Cohesion: 0.25
Nodes (4): writeLiveGeometry(), Rect, rect(), p

### Community 106 - "SectionState"
Cohesion: 0.25
Nodes (7): SectionState, active, angle, flip, offset, plane, visible

### Community 107 - "Display"
Cohesion: 0.25
Nodes (7): Display, constraints, construction, dimensions, points, profiles, projected

### Community 108 - "Log.h"
Cohesion: 0.36
Nodes (6): debug(), error(), info(), Sink, warning(), setSink()

### Community 109 - "Feature"
Cohesion: 0.25
Nodes (8): Feature, commandId, error, id, inputs, name, suppressed, Document::feature()

### Community 111 - "Primitive"
Cohesion: 0.38
Nodes (4): offset(), Primitive, build_, def_

### Community 114 - "uninstall.sh"
Cohesion: 0.52
Nodes (6): die(), manifest_for(), refresh(), uninstall.sh script, step(), usage()

### Community 115 - "install.sh"
Cohesion: 0.60
Nodes (5): die(), refresh(), install.sh script, step(), usage()

### Community 116 - "Column"
Cohesion: 0.33
Nodes (6): Column, kComment, kExpression, kParameter, kUnit, kValue

### Community 117 - "ConstructionPoint"
Cohesion: 0.33
Nodes (5): ConstructionPoint, name, point, Document::point(), Document::setPoint()

### Community 119 - "Architecture"
Cohesion: 0.40
Nodes (4): Architecture, How a command works, The document, Units

### Community 120 - "Development"
Cohesion: 0.40
Nodes (4): Build, Conventions, Development, Tests

### Community 122 - "smoke"
Cohesion: 0.40
Nodes (5): smoke(), MassProperties, area, centerOfMass, volume

### Community 123 - "MarkingMenu"
Cohesion: 0.40
Nodes (3): MarkingMenu, enabled, public

### Community 125 - "Dimension"
Cohesion: 0.50
Nodes (4): Dimension, Angle, Length, Unitless

### Community 126 - "Axis"
Cohesion: 0.50
Nodes (4): Axis, X, Y, Z

### Community 127 - "BooleanOp"
Cohesion: 0.50
Nodes (4): BooleanOp, Cut, Intersect, Join

### Community 128 - "ThreadInfo"
Cohesion: 0.50
Nodes (4): ThreadInfo, diameter, internal, pitch

### Community 130 - "OwnedCommand"
Cohesion: 0.67
Nodes (3): OwnedCommand, owned, OwningCommandSession

### Community 131 - "ChamferType"
Cohesion: 0.67
Nodes (3): ChamferType, DistanceAngle, TwoDistances

### Community 132 - "ChainSegment"
Cohesion: 0.67
Nodes (3): ChainSegment, entity, forward

## Knowledge Gaps
- **613 isolated node(s):** `ok`, `output`, `error`, `isReal`, `real` (+608 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 1169 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **25 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `Viewport` connect `Viewport` to `MainWindow`, `AnalysisSettings`, `Viewport::arrowMouseMove`, `Viewport.cpp`, `writeLiveGeometry`, `optional`, `QMouseEvent`, `.redrawAll`, `.initializeGL`, `SketchDisplay`, `MainWindowTools.cpp`, `ViewportAnalysis.cpp`, `.toPixels`, `Viewport.h`?**
  _High betweenness centrality (0.122) - this node is a cross-community bridge._
- **What connects `ok`, `output`, `error` to the rest of the system?**
  _613 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Viewport` be split into smaller, more focused modules?**
  _Cohesion score 0.019573267501322517 - nodes in this community are weakly interconnected._
- **Why does `optional` connect `optional` to `Viewport`, `DocCommands.cpp`, `MainWindow`, `Unit`, `Io.cpp`, `Parser`, `ViewportAnalysis.cpp`, `Expression.cpp`, `SketchEditor.cpp`, `SketchOps.cpp`, `ViewportSketch.cpp`, `nameOf`, `AnalysisSettings`, `string`, `Document.cpp`, `CommandDialog::CommandDialog`, `MainWindowArrow.cpp`, `sketchFor`, `CommandDialog.cpp`, `QString`, `ext`, `Session`, `string`, `InputDef`, `Viewport.h`, `Feature`, `ConstructionPoint`?**
  _High betweenness centrality (0.091) - this node is a cross-community bridge._
- **Should `Icons.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.0660941000746826 - nodes in this community are weakly interconnected._
- **Why does `MainWindow` connect `MainWindow` to `MainWindow::onEdgeClicked`, `UiCommand`, `MainWindow::MainWindow`, `.buildAppBar`, `smoke`, `MainWindow::buildUiCommands`, `writeLiveGeometry`, `SectionState`, `optional`, `MainWindowTools.cpp`, `MainWindowSketch.cpp`, `Unit`, `Session`, `.openMarkingMenu`, `MainWindow.cpp`, `SketchPalette`?**
  _High betweenness centrality (0.090) - this node is a cross-community bridge._
- **Should `DocCommands.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.04159495123350545 - nodes in this community are weakly interconnected._