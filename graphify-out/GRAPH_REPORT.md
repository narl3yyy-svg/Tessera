# Graph Report - tessera  (2026-11-12)

## Corpus Check
- 329 files · ~187,393 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 26 file(s) not represented in the graph (top: .drive 18, (none) 5, .cmake 1)

## Summary
- 3052 nodes · 7586 edges · 135 communities (110 shown, 25 thin omitted)
- Extraction: 85% EXTRACTED · 15% INFERRED · 0% AMBIGUOUS · INFERRED: 1149 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `a55a84a3`
- Run `git rev-parse HEAD` and compare to check if the graph is stale.
- Run `graphify update .` after code changes (no API cost).

## Community Hubs (Navigation)
- Viewport
- Icons.cpp
- Inputs
- tsr
- MainWindow
- run_oracle.py
- string
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
- .mouseMove
- Expression.cpp
- MainWindow.cpp
- TEST
- Sketch.cpp
- Zip.cpp
- SketchPalette
- SketchEditor.cpp
- QMouseEvent
- AdskModule.cpp
- Colors
- TopoDS_Shape
- SketchOps.cpp
- Unit
- ParameterCompleter
- BodyFrame
- nameOf
- AnalysisSettings
- solve
- ViewportArrow.cpp
- src/main.cpp
- ConstraintType
- TEST
- Pick
- Snap
- Kind
- .redrawAll
- Document::reevaluateParameters
- Document.cpp
- CommandDialog::CommandDialog
- MainWindow::buildSketchTab
- Session.cpp
- choice
- .toPixels
- MainWindowArrow.cpp
- .planeFrame
- QDialog
- Constraint
- xdrive.py
- ConstructPlane
- FeatureEffect
- DocCommands.cpp
- Document::effectOf
- CommandRegistry
- PythonHost.cpp
- Vec3
- MainWindow::MainWindow
- .primary
- CommandDialog.cpp
- ParametersDialog.cpp
- SketchRecord
- TopologyCounts
- Command.cpp
- InputType
- Kind
- Session
- Theme.cpp
- ConstructionPlane
- SketchDisplay
- string
- Measurement
- BoundingBox
- Entity
- Level
- README.md
- .projectAt
- QObject
- InputDef
- string
- Viewport.h
- Known differences still to build
- CommandSession
- .add
- MainWindow::onEdgeClicked
- FakeDoc
- UiCommand
- MainWindow::buildUiCommands
- Theme
- DocumentError
- cli_main.cpp
- writeLiveGeometry
- SectionState
- Display
- Feature
- WallSide
- NewComponent
- planeChoice
- uninstall.sh
- install.sh
- Column
- ConstructionPoint
- cmath
- Architecture
- Development
- BRepBody
- smoke
- MarkingMenu
- .CircularPattern
- Dimension
- BooleanOp
- ThreadInfo
- ChamferType
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

## Communities (135 total, 25 thin omitted)

### Community 0 - "Viewport"
Cohesion: 0.02
Nodes (49): view_, QLineEdit, Viewport, analysis_, analysisObjects_, appliedGridStep_, arrowBoxes_, arrowDragging_ (+41 more)

### Community 1 - "Icons.cpp"
Cohesion: 0.07
Nodes (92): arcIcon(), arrow(), axisIcon(), box(), centerRectIcon(), chamferIcon(), circleIcon(), coilIcon() (+84 more)

### Community 2 - "Inputs"
Cohesion: 0.04
Nodes (55): Adding a tool, Command, CommandContext, CommandDef, feature, icon, id, inputs (+47 more)

### Community 4 - "MainWindow"
Cohesion: 0.03
Nodes (55): writeLiveGeometry(), CommandDialog, MainWindow, active_, arrowInput_, arrowInput2_, bodiesBeforeCommand_, combEdges_ (+47 more)

### Community 5 - "run_oracle.py"
Cohesion: 0.08
Nodes (54): add_point(), arc_poly(), body_at(), body_list(), build_sketch(), chain(), circumcentre(), cm() (+46 more)

### Community 6 - "string"
Cohesion: 0.11
Nodes (14): Coil, def_, EdgeFeature, def_, kind_, Extrude, def_, Pipe (+6 more)

### Community 7 - "Document"
Cohesion: 0.05
Nodes (16): Document, effects_, modified_, pendingTools_, registry_, replaying_, txnBodies_, FromOcaf (+8 more)

### Community 8 - "Viewport.cpp"
Cohesion: 0.05
Nodes (5): keys(), qc(), QtFrameBuffer, rgb(), Viewport::Viewport()

### Community 9 - "SketchEditor"
Cohesion: 0.04
Nodes (39): SketchEditor, arcDrag_, arcDragMoved_, arcEndsChain_, arcFrom_, arcRef_, bodyEdges_, chainStart_ (+31 more)

### Community 10 - "CommandError"
Cohesion: 0.16
Nodes (17): CommandError, getBool(), getInt(), getReal(), applyOperation(), bodyName(), CopyFn, body (+9 more)

### Community 11 - "optional"
Cohesion: 0.14
Nodes (6): optional, CommandRegistry::all(), Axis, X, Y, Z

### Community 12 - "Kernel.cpp"
Cohesion: 0.04
Nodes (6): dot(), faceScore(), isoCoarsePitch(), score(), topologyCounts(), vec()

### Community 13 - "MainWindowTools.cpp"
Cohesion: 0.08
Nodes (7): MainWindow::insertFile(), MainWindow::print3d(), MainWindow::sectionFrame(), MainWindow::sectionPlane(), MainWindow::setSelectionFilter(), MainWindow::showParameters(), MainWindow::updateSectionArrow()

### Community 14 - "MainWindowSketch.cpp"
Cohesion: 0.12
Nodes (8): MainWindow::cancelSketch(), MainWindow::editSketch(), MainWindow::finishSketch(), MainWindow::sketchPalette(), MainWindow::sketchVisible(), MainWindow::startSketch(), MainWindow::updateProfilePicking(), qs()

### Community 15 - "Unit"
Cohesion: 0.13
Nodes (14): MainWindow::checkInterference(), MainWindow::chooseUnits(), MainWindow::driveJoints(), MainWindow::formatLength(), MainWindow::gridSettings(), MainWindow::openAnalysis(), MainWindow::openSection(), MainWindow::showCenterOfMass() (+6 more)

### Community 16 - "CommandDialog"
Cohesion: 0.05
Nodes (30): CommandDialog, bodiesId_, bodiesLabel_, bodyInput_, buttons_, cmd_, conditional_, edgesId_ (+22 more)

### Community 17 - "Io.cpp"
Cohesion: 0.07
Nodes (29): FileFormat, Brep, Iges, Obj, Step, Stl, ThreeMF, FormatInfo (+21 more)

### Community 18 - "Parser"
Cohesion: 0.21
Nodes (13): Quantity, angle, length, value, describe(), Parser, ang_, env_ (+5 more)

### Community 19 - "SketchGeometry.cpp"
Cohesion: 0.12
Nodes (9): curve(), curves(), customPlaneSpec(), interiorPoint(), planeFrame(), profileAt(), profiles(), toSketch() (+1 more)

### Community 20 - ".mouseMove"
Cohesion: 0.16
Nodes (7): ext(), fixedColor(), freeColor(), qc(), rgb(), wire(), Sketch::addLine()

### Community 21 - "Expression.cpp"
Cohesion: 0.14
Nodes (15): ExpressionEnv, lengthUnit, lookup, ExpressionError, evaluateExpression(), evaluateQuantity(), expressionReferences(), isConstantName() (+7 more)

### Community 22 - "MainWindow.cpp"
Cohesion: 0.10
Nodes (5): commandIcon(), flatButton(), qs(), MainWindow::enterSketchMode(), MainWindow::applySection()

### Community 23 - "TEST"
Cohesion: 0.09
Nodes (5): Sketch, constraints, entities, points, TEST()

### Community 24 - "Sketch.cpp"
Cohesion: 0.08
Nodes (17): Point, x, y, SketchError, entityTypeName(), isDimension(), Sketch::addCircle(), Sketch::addSpline() (+9 more)

### Community 25 - "Zip.cpp"
Cohesion: 0.05
Nodes (20): faceStyle(), lineStyle(), rgb(), Viewport::lookAt(), Viewport::planePoint(), Viewport::toWidget(), Entry, data (+12 more)

### Community 26 - "SketchPalette"
Cohesion: 0.06
Nodes (25): QCheckBox, QLabel, QToolButton, QWidget, SketchEditor, SketchPalette, body_, constraints_ (+17 more)

### Community 28 - "QMouseEvent"
Cohesion: 0.12
Nodes (8): MarkingMenu::keyPressEvent(), MarkingMenu::MarkingMenu(), MarkingMenu::mouseMoveEvent(), MarkingMenu::paintEvent(), MarkingMenu::popupAt(), MarkingMenu::ringIndexAt(), MarkingMenu::run(), QKeyEvent

### Community 29 - "AdskModule.cpp"
Cohesion: 0.13
Nodes (13): Application, BRepBodies, Component, Design, Product, raiseIfError(), UserParameter, name (+5 more)

### Community 30 - "Colors"
Cohesion: 0.07
Nodes (28): Colors, base, border, cubeBox, cubeText, errorBackground, grid, gridMajor (+20 more)

### Community 31 - "TopoDS_Shape"
Cohesion: 0.30
Nodes (23): KernelError, asSolid(), boolean(), chamfer(), chamferEx(), draft(), extrude(), extrudeEx() (+15 more)

### Community 32 - "SketchOps.cpp"
Cohesion: 0.21
Nodes (19): at(), chainOf(), chamferCorner(), cornerAt(), cross(), dot(), extendLine(), filletCorner() (+11 more)

### Community 33 - "Unit"
Cohesion: 0.17
Nodes (16): MainWindow::lengthUnit(), Unit, Centimeter, Degree, Foot, Inch, Meter, Millimeter (+8 more)

### Community 34 - "ParameterCompleter"
Cohesion: 0.12
Nodes (9): MainWindow::attachArrowCompleters(), ParameterCompleter, completer_, edit_, names_, ParameterCompleter::ParameterCompleter(), public, QCompleter (+1 more)

### Community 35 - "BodyFrame"
Cohesion: 0.11
Nodes (21): BodyFrame, diag, dx, dy, dz, x0, y0, z0 (+13 more)

### Community 36 - "nameOf"
Cohesion: 0.17
Nodes (11): ConstructionAxis, axis, name, Document::axes(), Document::axis(), Document::removeBody(), Document::replaceBody(), findBodyLabel() (+3 more)

### Community 37 - "AnalysisSettings"
Cohesion: 0.08
Nodes (21): AnalysisKind, CurvatureMap, Draft, None, Zebra, AnalysisSettings, curvatureScale, draftAngle (+13 more)

### Community 38 - "solve"
Cohesion: 0.17
Nodes (13): addConstraintChecked(), Layout, n, px, py, rad, makeLayout(), pack() (+5 more)

### Community 39 - "ViewportArrow.cpp"
Cohesion: 0.07
Nodes (15): QMouseEvent, ViewInteractor, rgb(), segmentDistance(), Viewport::arrowAt(), Viewport::arrowMouseMove(), Viewport::arrowMousePress(), Viewport::arrowMouseRelease() (+7 more)

### Community 41 - "ConstraintType"
Cohesion: 0.09
Nodes (23): ConstraintType, Angle, Coincident, Collinear, Concentric, Diameter, Distance, Equal (+15 more)

### Community 42 - "TEST"
Cohesion: 0.09
Nodes (3): param(), TEST(), tmp()

### Community 43 - "Pick"
Cohesion: 0.13
Nodes (15): Hit, index, kind, Pick, bodyArc, bodyPoint, bodySegment, hit (+7 more)

### Community 44 - "Snap"
Cohesion: 0.11
Nodes (18): Snap, alignX, alignY, bodyArc, bodySegment, entity, fromX, fromY (+10 more)

### Community 45 - "Kind"
Cohesion: 0.09
Nodes (21): HudField, edit, editing, kind, locked, value, Kind, Angle (+13 more)

### Community 46 - ".redrawAll"
Cohesion: 0.10
Nodes (8): NavPreset, Fusion, SolidWorks, Tinkercad, Viewport::setCurvatureComb(), Viewport::clearDragArrow(), Viewport::clearSecondArrow(), Viewport::setInteractor()

### Community 47 - "Document::reevaluateParameters"
Cohesion: 0.24
Nodes (5): Document::expressionEnv(), Document::reevaluateParameters(), Document::userParameter(), Document::userParameters(), Document::save()

### Community 48 - "Document.cpp"
Cohesion: 0.09
Nodes (23): Document::abortTransaction(), Document::addBody(), Document::addUserParameter(), Document::commitTransaction(), Document::openTransaction(), Document::recompute(), Document::recordFeature(), Document::redo() (+15 more)

### Community 49 - "CommandDialog::CommandDialog"
Cohesion: 0.14
Nodes (4): ExpressionSpinBox, eval_, expression_, shown_

### Community 51 - "Session.cpp"
Cohesion: 0.15
Nodes (18): historyEdit(), OwnedCommand, owned, OwningCommandSession, Session::addListener(), Session::begin(), Session::deleteFeature(), Session::deleteParameter() (+10 more)

### Community 52 - "choice"
Cohesion: 0.20
Nodes (4): addOperationInputs(), bodyInput(), choice(), commonDef()

### Community 54 - "MainWindowArrow.cpp"
Cohesion: 0.08
Nodes (11): ArrowPlacement, base, dir, edgePlacement(), facesPlacement(), MainWindow::patternCentre(), MainWindow::pickedFaces(), packed() (+3 more)

### Community 55 - ".planeFrame"
Cohesion: 0.21
Nodes (6): Loft, def_, profilesOf(), profiles, Sweep, def_

### Community 57 - "QDialog"
Cohesion: 0.18
Nodes (5): QDialog, MainWindow::exportDesign(), MainWindow::measurePick(), MainWindow::openMeasure(), toolWindow()

### Community 58 - "Constraint"
Cohesion: 0.11
Nodes (17): Constraint, entities, expression, points, type, value, value2, SolveResult (+9 more)

### Community 59 - "xdrive.py"
Cohesion: 0.32
Nodes (14): button(), canvas(), click(), drag(), flush(), geometry(), key(), keycode() (+6 more)

### Community 61 - "ConstructPlane"
Cohesion: 0.24
Nodes (3): ConstructPlane, def_, kind_

### Community 62 - "FeatureEffect"
Cohesion: 0.08
Nodes (20): Body, name, shape, Component, bodies, name, FeatureEffect, bodies (+12 more)

### Community 63 - "DocCommands.cpp"
Cohesion: 0.10
Nodes (25): axisOf(), bodyCentre(), checkPattern(), Combine, def_, differenceOrNull(), InsertGeometry, def_ (+17 more)

### Community 65 - "CommandRegistry"
Cohesion: 0.12
Nodes (4): CommandRegistry, cmds_, CommandRegistry::add(), TEST()

### Community 66 - "PythonHost.cpp"
Cohesion: 0.12
Nodes (12): Result, error, ok, output, captured(), PythonHost::exec(), PythonHost::runScript(), bindTsr() (+4 more)

### Community 67 - "Vec3"
Cohesion: 0.20
Nodes (18): SurfacePoint, normal, point, Vec3, edgeMidpoint(), edgesNear(), frame(), makeCone() (+10 more)

### Community 68 - "MainWindow::MainWindow"
Cohesion: 0.12
Nodes (5): PythonHost, MainWindow::MainWindow(), MainWindow::beginSketch(), MainWindow::exitSketchMode(), MainWindow::showPreferences()

### Community 71 - "ParametersDialog.cpp"
Cohesion: 0.10
Nodes (14): number(), ParametersDialog, building_, error_, listener_, ParametersDialog::ParametersDialog(), public, rebuildPending_ (+6 more)

### Community 72 - "SketchRecord"
Cohesion: 0.20
Nodes (10): SketchRecord, data, name, offset, plane, Document::lengthUnit(), Document::sketch(), Document::sketches() (+2 more)

### Community 73 - "TopologyCounts"
Cohesion: 0.18
Nodes (16): Section, Circular, Square, Triangular, TopologyCounts, edges, faces, shells (+8 more)

### Community 74 - "Command.cpp"
Cohesion: 0.22
Nodes (11): expressionKey(), checkInputValue(), CommandContext::evaluateExpression(), CommandDef::input(), CommandSession::applyInTransaction(), CommandSession::cancel(), CommandSession::execute(), CommandSession::preview() (+3 more)

### Community 75 - "InputType"
Cohesion: 0.12
Nodes (17): InputType, Axis, Bodies, Body, Bool, Choice, Edges, Faces (+9 more)

### Community 76 - "Kind"
Cohesion: 0.12
Nodes (16): Kind, Angle, AxisCylinder, AxisEdge, AxisTwoPlanes, AxisTwoPoints, Chamfer, Draft (+8 more)

### Community 77 - "Session"
Cohesion: 0.12
Nodes (8): PythonHost::PythonHost(), main(), Session, commands_, doc_, listeners_, nextListener_, path_

### Community 78 - "Theme.cpp"
Cohesion: 0.19
Nodes (6): setIconTheme(), darkColors(), darkPalette(), darkStyleSheet(), lightColors(), lightStyleSheet()

### Community 79 - "ConstructionPlane"
Cohesion: 0.33
Nodes (5): ConstructionPlane, name, spec, Document::plane(), Document::planes()

### Community 80 - "SketchDisplay"
Cohesion: 0.13
Nodes (10): ProfileObject, index, sketch, SketchDisplay, construction, curves, frame, name (+2 more)

### Community 81 - "string"
Cohesion: 0.16
Nodes (14): bodyNumber(), Document::bodies(), Document::body(), Document::component(), Document::componentOfBody(), Document::components(), Document::nextAxisName(), Document::nextBodyName() (+6 more)

### Community 82 - "Measurement"
Cohesion: 0.13
Nodes (14): Kind, Angle, Area, Length, Volume, Measurement, from, hasLine (+6 more)

### Community 83 - "BoundingBox"
Cohesion: 0.22
Nodes (7): BoundingBox, max, min, massProperties(), measure(), polygonToCircleLoft(), sweepWire()

### Community 84 - "Entity"
Cohesion: 0.13
Nodes (15): Entity, a, b, center, construction, fit, projected, radius (+7 more)

### Community 85 - "Level"
Cohesion: 0.16
Nodes (13): debug(), error(), info(), Level, Debug, Error, Info, Warning (+5 more)

### Community 86 - "README.md"
Cohesion: 0.12
Nodes (12): Known gaps, Reference parts, Fusion feature checklist, Roadmap, Contents, Development, Features, Install (+4 more)

### Community 87 - ".projectAt"
Cohesion: 0.14
Nodes (5): PlaneEdges, arcs, segments, vertices, edges

### Community 90 - "InputDef"
Cohesion: 0.14
Nodes (12): InputDef, choices, defaultValue, id, label, max, min, minExclusive (+4 more)

### Community 91 - "string"
Cohesion: 0.15
Nodes (21): boundingBox(), completeEdgeReferences(), completeFaceReferences(), decode(), decodeFaces(), edgeReference(), EdgeSig, full (+13 more)

### Community 92 - "Viewport.h"
Cohesion: 0.11
Nodes (6): QLabel, Profile, area, face, x, y

### Community 93 - "Known differences still to build"
Cohesion: 0.15
Nodes (12): Data and files, Findings from the videos, Fusion study list, Interface, Known differences still to build, Navigation and display, Selection and the canvas, Sketch (+4 more)

### Community 94 - "CommandSession"
Cohesion: 0.17
Nodes (4): CommandSession, inputs_, CommandRegistry::find(), CommandRegistry::run()

### Community 96 - "MainWindow::onEdgeClicked"
Cohesion: 0.21
Nodes (5): MainWindow::onEdgeClicked(), MainWindow::onProfileClicked(), MainWindow::originalShape(), MainWindow::syncPickedShapes(), MainWindow::toOriginal()

### Community 98 - "FakeDoc"
Cohesion: 0.17
Nodes (6): FakeDoc, aborts, commits, items, open, snapshot

### Community 99 - "UiCommand"
Cohesion: 0.13
Nodes (12): UiCommand, enabled, icon, id, name, panel, run, shortcut (+4 more)

### Community 102 - "Theme"
Cohesion: 0.22
Nodes (4): Theme, colors_, public, styled_

### Community 103 - "DocumentError"
Cohesion: 0.09
Nodes (11): DocumentError, doc_(), Document::axisFrame(), Document::Document(), Document::evaluate(), Document::ocafBytes(), Document::planeFrame(), Document::removeUserParameter() (+3 more)

### Community 104 - "cli_main.cpp"
Cohesion: 0.28
Nodes (3): listCommands(), main(), usage()

### Community 105 - "writeLiveGeometry"
Cohesion: 0.25
Nodes (5): Session::notifyChanged(), Rect, rect(), l, p

### Community 106 - "SectionState"
Cohesion: 0.25
Nodes (7): SectionState, active, angle, flip, offset, plane, visible

### Community 107 - "Display"
Cohesion: 0.25
Nodes (7): Display, constraints, construction, dimensions, points, profiles, projected

### Community 109 - "Feature"
Cohesion: 0.20
Nodes (10): Feature, commandId, error, id, inputs, name, suppressed, Document::feature() (+2 more)

### Community 111 - "WallSide"
Cohesion: 0.50
Nodes (4): WallSide, Center, Side1, Side2

### Community 112 - "NewComponent"
Cohesion: 0.13
Nodes (7): AddUserParameter, def_, CreateSketch, def_, isIdentifier(), NewComponent, def_

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
Cohesion: 0.29
Nodes (5): ConstructionPoint, name, point, Document::point(), Document::points()

### Community 118 - "cmath"
Cohesion: 0.10
Nodes (7): isEmpty(), Value, Case, name, fail(), Failure, Register

### Community 119 - "Architecture"
Cohesion: 0.40
Nodes (4): Architecture, How a command works, The document, Units

### Community 120 - "Development"
Cohesion: 0.40
Nodes (4): Build, Conventions, Development, Tests

### Community 121 - "BRepBody"
Cohesion: 0.29
Nodes (3): bindAdsk(), BRepBody, index

### Community 122 - "smoke"
Cohesion: 0.40
Nodes (5): smoke(), MassProperties, area, centerOfMass, volume

### Community 123 - "MarkingMenu"
Cohesion: 0.40
Nodes (3): MarkingMenu, enabled, public

### Community 125 - "Dimension"
Cohesion: 0.50
Nodes (4): Dimension, Angle, Length, Unitless

### Community 127 - "BooleanOp"
Cohesion: 0.50
Nodes (4): BooleanOp, Cut, Intersect, Join

### Community 128 - "ThreadInfo"
Cohesion: 0.50
Nodes (4): ThreadInfo, diameter, internal, pitch

### Community 131 - "ChamferType"
Cohesion: 0.67
Nodes (3): ChamferType, DistanceAngle, TwoDistances

### Community 132 - "ChainSegment"
Cohesion: 0.67
Nodes (3): ChainSegment, entity, forward

## Knowledge Gaps
- **618 isolated node(s):** `ok`, `output`, `error`, `isReal`, `real` (+613 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 1176 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **25 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `Viewport` connect `Viewport` to `AnalysisSettings`, `ViewportArrow.cpp`, `Viewport.cpp`, `writeLiveGeometry`, `optional`, `.setBodyOverrides`, `QMouseEvent`, `.redrawAll`, `.initializeGL`, `SketchDisplay`, `Unit`, `.toPixels`, `MainWindowArrow.cpp`, `Viewport.h`, `.leaveEvent`?**
  _High betweenness centrality (0.124) - this node is a cross-community bridge._
- **What connects `ok`, `output`, `error` to the rest of the system?**
  _618 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Viewport` be split into smaller, more focused modules?**
  _Cohesion score 0.019367991845056064 - nodes in this community are weakly interconnected._
- **Why does `optional` connect `optional` to `Viewport`, `MainWindow`, `string`, `Kernel.cpp`, `Io.cpp`, `Expression.cpp`, `Zip.cpp`, `SketchEditor.cpp`, `SketchOps.cpp`, `Unit`, `nameOf`, `AnalysisSettings`, `ViewportArrow.cpp`, `Document::reevaluateParameters`, `CommandDialog::CommandDialog`, `.toPixels`, `MainWindowArrow.cpp`, `DocCommands.cpp`, `Vec3`, `.primary`, `CommandDialog.cpp`, `SketchRecord`, `Session`, `ConstructionPlane`, `string`, `.press`, `InputDef`, `Viewport.h`, `Feature`, `ConstructionPoint`?**
  _High betweenness centrality (0.115) - this node is a cross-community bridge._
- **Should `Icons.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.0660941000746826 - nodes in this community are weakly interconnected._
- **Why does `MainWindow` connect `MainWindow` to `MainWindow::onEdgeClicked`, `.eventFilter`, `SketchPalette`, `MainWindow::MainWindow`, `UiCommand`, `.buildAppBar`, `MainWindow::buildUiCommands`, `SectionState`, `optional`, `MainWindowTools.cpp`, `MainWindowSketch.cpp`, `Unit`, `Session`, `MainWindow::buildSketchTab`, `MainWindow.cpp`, `QDialog`, `smoke`, `Viewport.h`?**
  _High betweenness centrality (0.089) - this node is a cross-community bridge._
- **Should `Inputs` be split into smaller, more focused modules?**
  _Cohesion score 0.03882063882063882 - nodes in this community are weakly interconnected._