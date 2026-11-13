# Graph Report - tessera  (2026-11-13)

## Corpus Check
- 355 files · ~214,491 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 43 file(s) not represented in the graph (top: .drive 35, (none) 5, .cmake 1)

## Summary
- 3280 nodes · 8309 edges · 134 communities (106 shown, 28 thin omitted)
- Extraction: 84% EXTRACTED · 16% INFERRED · 0% AMBIGUOUS · INFERRED: 1308 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `cf928066`
- Run `git rev-parse HEAD` and compare to check if the graph is stale.
- Run `graphify update .` after code changes (no API cost).

## Community Hubs (Navigation)
- Viewport
- Icons.cpp
- ViewportAnalysis.cpp
- MainWindow
- run_oracle.py
- string
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
- ViewportArrow.cpp
- .updatePreview
- TEST
- Sketch.cpp
- ViewportSketch.cpp
- SketchPalette
- Command.cpp
- sketchFor
- AdskModule.cpp
- Colors
- KernelError
- SketchOps.cpp
- Session.cpp
- ParameterCompleter
- fromInternal
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
- .rebuild
- Theme.cpp
- Entity
- xdrive.py
- SketchGeometry.cpp
- .redrawAll
- QMouseEvent
- string
- CommandRegistry
- cmath
- TopoDS_Shape
- Theme
- FileFormat
- CommandError
- src/main.cpp
- .hitTest
- QTimer
- Profile
- InputType
- string
- CommandSession
- math
- Value.h
- SketchDisplay
- PYBIND11_EMBEDDED_MODULE
- Measurement
- .motion
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
- Viewport::setDragArrow
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
- Session::open
- Feature
- Rect
- .openMarkingMenu
- fail
- Placement
- rect
- Column
- Joints
- Handle
- openWallBand
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

## Communities (134 total, 28 thin omitted)

### Community 0 - "Viewport"
Cohesion: 0.02
Nodes (56): view_, Viewport, analysis_, analysisObjects_, appliedGridStep_, arrowBoxes_, arrowDragging_, arrowGrab_ (+48 more)

### Community 1 - "Icons.cpp"
Cohesion: 0.06
Nodes (109): arc3Icon(), arcIcon(), arrow(), axisIcon(), box(), breakIcon(), centerRectIcon(), chamferIcon() (+101 more)

### Community 2 - "ViewportAnalysis.cpp"
Cohesion: 0.13
Nodes (5): packed(), ramp(), shade(), Viewport::buildAnalysis(), Viewport::setCurvatureComb()

### Community 4 - "MainWindow"
Cohesion: 0.03
Nodes (63): Known gaps, CommandDialog, MainWindow, active_, arrowInput_, arrowInput2_, bodiesBeforeCommand_, combEdges_ (+55 more)

### Community 5 - "run_oracle.py"
Cohesion: 0.08
Nodes (54): add_point(), arc_poly(), body_at(), body_list(), build_sketch(), chain(), circumcentre(), cm() (+46 more)

### Community 6 - "string"
Cohesion: 0.12
Nodes (10): AddUserParameter, def_, Combine, def_, isIdentifier(), jointOrigin(), JointPick, frame (+2 more)

### Community 7 - "Document"
Cohesion: 0.03
Nodes (11): Document, effects_, modified_, pendingTools_, registry_, replaying_, txnBodies_, FromOcaf (+3 more)

### Community 8 - "Viewport.cpp"
Cohesion: 0.06
Nodes (7): MarkingMenu::keyPressEvent(), keys(), qc(), QKeyEvent, rgb(), Viewport::frontEdgeOwner(), Viewport::Viewport()

### Community 9 - "SketchEditor"
Cohesion: 0.03
Nodes (45): SketchEditor, arcDrag_, arcDragMoved_, arcEndsChain_, arcFrom_, arcRef_, bodyEdges_, boxing_ (+37 more)

### Community 10 - "QString"
Cohesion: 0.11
Nodes (6): ExpressionSpinBox, eval_, expression_, shown_, formatNumber(), dimensionOf()

### Community 12 - "Kernel.cpp"
Cohesion: 0.04
Nodes (4): dot(), faceScore(), score(), vec()

### Community 13 - "DocCommands.cpp"
Cohesion: 0.10
Nodes (18): ConstructAxisPoint, def_, kind_, evaluateDimensions(), makeBox(), makeCone(), makeCylinder(), makeSphere() (+10 more)

### Community 14 - "Kind"
Cohesion: 0.10
Nodes (19): EdgeFeature, def_, kind_, Kind, Angle, AxisCylinder, AxisEdge, AxisTwoPlanes (+11 more)

### Community 15 - "MainWindowTools.cpp"
Cohesion: 0.06
Nodes (12): QDialog, MainWindow::exportDesign(), MainWindow::insertFile(), MainWindow::measurePick(), MainWindow::openMeasure(), MainWindow::sectionFrame(), MainWindow::sectionPlane(), MainWindow::setSelectionFilter() (+4 more)

### Community 16 - "CommandDialog"
Cohesion: 0.05
Nodes (31): CommandDialog, bodiesId_, bodiesLabel_, bodyInput_, buttons_, cmd_, conditional_, edgesId_ (+23 more)

### Community 17 - "Io.cpp"
Cohesion: 0.10
Nodes (18): MainWindow::print3d(), NamedShape, compoundOf(), exportShapes(), fmt(), formatForPath(), fromBrep(), importShape() (+10 more)

### Community 18 - "Parser"
Cohesion: 0.07
Nodes (45): MainWindow::lengthUnit(), ExpressionEnv, lengthUnit, lookup, ExpressionError, Quantity, angle, length (+37 more)

### Community 19 - "src/main.cpp"
Cohesion: 0.08
Nodes (8): listCommands(), main(), usage(), grabWindowWithPanels(), main(), smoke(), writeLiveGeometry(), volume

### Community 21 - "ViewportArrow.cpp"
Cohesion: 0.13
Nodes (7): rgb(), segmentDistance(), Viewport::arrowAt(), Viewport::arrowParam(), Viewport::dragArrowHandle(), Viewport::placeArrowBoxes(), height

### Community 23 - "TEST"
Cohesion: 0.08
Nodes (6): Sketch, constraints, entities, points, texts, TEST()

### Community 24 - "Sketch.cpp"
Cohesion: 0.09
Nodes (15): SketchError, entityTypeName(), isDimension(), Sketch::addCircle(), Sketch::addConstraint(), Sketch::addSpline(), Sketch::addText(), Sketch::checkIndices() (+7 more)

### Community 25 - "ViewportSketch.cpp"
Cohesion: 0.08
Nodes (6): faceStyle(), lineStyle(), rgb(), Viewport::lookAt(), Viewport::planePoint(), Viewport::toWidget()

### Community 26 - "SketchPalette"
Cohesion: 0.06
Nodes (26): flatButton(), QCheckBox, QLabel, QToolButton, QWidget, SketchEditor, SketchPalette, body_ (+18 more)

### Community 27 - "Command.cpp"
Cohesion: 0.22
Nodes (11): expressionKey(), checkInputValue(), CommandContext::evaluateExpression(), CommandDef::input(), CommandSession::applyInTransaction(), CommandSession::cancel(), CommandSession::execute(), CommandSession::preview() (+3 more)

### Community 28 - "sketchFor"
Cohesion: 0.11
Nodes (17): Inputs, axisOf(), Hole, def_, Loft, def_, Pipe, def_ (+9 more)

### Community 29 - "AdskModule.cpp"
Cohesion: 0.07
Nodes (20): Application, bindAdsk(), BRepBodies, BRepBody, index, Component, Design, Product (+12 more)

### Community 30 - "Colors"
Cohesion: 0.07
Nodes (28): Colors, base, border, cubeBox, cubeText, errorBackground, grid, gridMajor (+20 more)

### Community 31 - "KernelError"
Cohesion: 0.15
Nodes (27): faces, asSolid(), boolean(), boundingBox(), chamfer(), chamferEx(), edgeMidpoint(), extrudeEx() (+19 more)

### Community 32 - "SketchOps.cpp"
Cohesion: 0.19
Nodes (26): at(), chainOf(), chamferCorner(), circularPattern(), copyEntities(), cornerAt(), cross(), dot() (+18 more)

### Community 33 - "Session.cpp"
Cohesion: 0.16
Nodes (21): historyEdit(), OwnedCommand, owned, OwningCommandSession, Session::addListener(), Session::begin(), Session::deleteFeature(), Session::deleteParameter() (+13 more)

### Community 34 - "ParameterCompleter"
Cohesion: 0.12
Nodes (8): ParameterCompleter, completer_, edit_, names_, ParameterCompleter::ParameterCompleter(), public, QCompleter, QLineEdit

### Community 35 - "fromInternal"
Cohesion: 0.14
Nodes (13): MainWindow::checkInterference(), MainWindow::chooseUnits(), MainWindow::driveJoints(), MainWindow::formatLength(), MainWindow::gridSettings(), MainWindow::openAnalysis(), MainWindow::openSection(), MainWindow::updateMeasure() (+5 more)

### Community 37 - "MainWindow::MainWindow"
Cohesion: 0.15
Nodes (3): PythonHost, MainWindow::MainWindow(), MainWindow::showPreferences()

### Community 38 - "solve"
Cohesion: 0.18
Nodes (12): addConstraintChecked(), Layout, n, px, py, rad, makeLayout(), pack() (+4 more)

### Community 39 - ".showDialog"
Cohesion: 0.12
Nodes (4): commandIcon(), qs(), MainWindow::exitSketchMode(), MainWindow::applySection()

### Community 40 - "Constraint"
Cohesion: 0.14
Nodes (12): Constraint, driven, entities, expression, hasLabel, labelX, labelY, name (+4 more)

### Community 41 - "ConstraintType"
Cohesion: 0.08
Nodes (25): ConstraintType, Angle, Coincident, Collinear, Concentric, Diameter, Distance, Equal (+17 more)

### Community 42 - "TEST"
Cohesion: 0.05
Nodes (9): Session, commands_, doc_, listeners_, nextListener_, path_, param(), TEST() (+1 more)

### Community 43 - "Pick"
Cohesion: 0.13
Nodes (14): Pick, bodyArc, bodyPoint, bodySegment, hit, midpointOf, onEntity, onXAxis (+6 more)

### Community 44 - "Snap"
Cohesion: 0.09
Nodes (18): Snap, alignX, alignY, bodyArc, bodySegment, entity, fromX, fromY (+10 more)

### Community 45 - "Kind"
Cohesion: 0.09
Nodes (21): HudField, edit, editing, kind, locked, value, Kind, Angle (+13 more)

### Community 46 - "CommandContext"
Cohesion: 0.03
Nodes (55): Adding a tool, Command, CommandContext, CommandDef, feature, icon, id, inputs (+47 more)

### Community 47 - "Viewport.h"
Cohesion: 0.07
Nodes (15): AnalysisKind, CurvatureMap, Draft, None, Zebra, AnalysisSettings, curvatureScale, draftAngle (+7 more)

### Community 48 - "Document.cpp"
Cohesion: 0.09
Nodes (28): ConstructionPlane, name, spec, Document::axes(), Document::bodies(), Document::body(), Document::bodyName(), Document::components() (+20 more)

### Community 50 - "MainWindowSketch.cpp"
Cohesion: 0.09
Nodes (13): MainWindow::cancelSketch(), MainWindow::editSketch(), MainWindow::finishSketch(), MainWindow::onEdgeClicked(), MainWindow::onProfileClicked(), MainWindow::originalShape(), MainWindow::sketchPalette(), MainWindow::sketchVisible() (+5 more)

### Community 51 - "InputDef"
Cohesion: 0.08
Nodes (24): InputDef, choices, defaultValue, id, label, max, min, minExclusive (+16 more)

### Community 54 - "ViewportAnalysis.cpp"
Cohesion: 0.11
Nodes (8): ArrowPlacement, base, dir, edgePlacement(), facesPlacement(), MainWindow::attachArrowCompleters(), MainWindow::patternCentre(), MainWindow::pickedFaces()

### Community 55 - ".rebuild"
Cohesion: 0.11
Nodes (12): ext(), fixedColor(), freeColor(), qc(), rgb(), wire(), Text, angle (+4 more)

### Community 56 - "Theme.cpp"
Cohesion: 0.19
Nodes (6): setIconTheme(), darkColors(), darkPalette(), darkStyleSheet(), lightColors(), lightStyleSheet()

### Community 58 - "Entity"
Cohesion: 0.09
Nodes (21): Entity, a, b, center, construction, fit, projected, radius (+13 more)

### Community 59 - "xdrive.py"
Cohesion: 0.32
Nodes (14): button(), canvas(), click(), drag(), flush(), geometry(), key(), keycode() (+6 more)

### Community 61 - "SketchGeometry.cpp"
Cohesion: 0.12
Nodes (11): curve(), curves(), customPlaneSpec(), entityCurves(), interiorPoint(), planeFrame(), profileAt(), profiles() (+3 more)

### Community 62 - ".redrawAll"
Cohesion: 0.15
Nodes (8): NavPreset, Fusion, SolidWorks, Tinkercad, Viewport::clearDragArrow(), Viewport::clearSecondArrow(), Viewport::rebuildArrow(), Viewport::setInteractor()

### Community 63 - "QMouseEvent"
Cohesion: 0.14
Nodes (8): MarkingMenu::mouseMoveEvent(), QMouseEvent, ViewInteractor, Viewport::arrowMouseMove(), Viewport::arrowMousePress(), Viewport::arrowMouseRelease(), Viewport::dragArrowForTest(), Viewport::rebuildArrows()

### Community 64 - "string"
Cohesion: 0.14
Nodes (24): KernelError, edges, vertices, completeEdgeReferences(), completeFaceReferences(), decode(), decodeFaces(), edgeReference() (+16 more)

### Community 65 - "CommandRegistry"
Cohesion: 0.12
Nodes (4): CommandRegistry, cmds_, CommandRegistry::add(), TEST()

### Community 66 - "cmath"
Cohesion: 0.14
Nodes (12): Result, error, ok, output, captured(), PythonHost::exec(), PythonHost::PythonHost(), PythonHost::runScript() (+4 more)

### Community 67 - "TopoDS_Shape"
Cohesion: 0.22
Nodes (21): SurfacePoint, normal, point, Vec3, draft(), edgesNear(), extrude(), frame() (+13 more)

### Community 68 - "Theme"
Cohesion: 0.22
Nodes (4): Theme, colors_, public, styled_

### Community 69 - "FileFormat"
Cohesion: 0.17
Nodes (12): FileFormat, Brep, Iges, Obj, Step, Stl, ThreeMF, FormatInfo (+4 more)

### Community 70 - "CommandError"
Cohesion: 0.12
Nodes (21): CommandError, getBool(), getInt(), getReal(), applyOperation(), bodyCentre(), bodyName(), CopyFn (+13 more)

### Community 71 - "src/main.cpp"
Cohesion: 0.10
Nodes (14): number(), ParametersDialog, building_, error_, listener_, ParametersDialog::ParametersDialog(), public, rebuildPending_ (+6 more)

### Community 72 - ".hitTest"
Cohesion: 0.19
Nodes (5): angleInArc(), Hit, index, kind, segDistance()

### Community 74 - "Profile"
Cohesion: 0.33
Nodes (5): Profile, area, face, x, y

### Community 75 - "InputType"
Cohesion: 0.12
Nodes (17): InputType, Axis, Bodies, Body, Bool, Choice, Edges, Faces (+9 more)

### Community 76 - "string"
Cohesion: 0.20
Nodes (13): bodyNumber(), Document::axisFrame(), Document::component(), Document::componentOfBody(), Document::nextAxisName(), Document::nextBodyName(), Document::nextComponentName(), Document::nextDimensionName() (+5 more)

### Community 77 - "CommandSession"
Cohesion: 0.17
Nodes (4): CommandSession, inputs_, CommandRegistry::find(), CommandRegistry::run()

### Community 80 - "SketchDisplay"
Cohesion: 0.08
Nodes (18): DragArrow, base, dir, value, PendingLook, center, frame, size (+10 more)

### Community 82 - "Measurement"
Cohesion: 0.13
Nodes (14): Kind, Angle, Area, Length, Volume, Measurement, from, hasLine (+6 more)

### Community 83 - ".motion"
Cohesion: 0.21
Nodes (4): Coil, def_, Joint, def_

### Community 84 - "Kernel.h"
Cohesion: 0.11
Nodes (18): Axis, X, Y, Z, BooleanOp, Cut, Intersect, Join (+10 more)

### Community 85 - "Level"
Cohesion: 0.16
Nodes (13): debug(), error(), info(), Level, Debug, Error, Info, Warning (+5 more)

### Community 86 - "README.md"
Cohesion: 0.08
Nodes (19): Architecture, How a command works, The document, Units, Build, Conventions, Development, Tests (+11 more)

### Community 87 - "DocumentError"
Cohesion: 0.12
Nodes (25): DocumentError, Document::abortTransaction(), Document::addBody(), Document::addUserParameter(), Document::commitTransaction(), Document::openTransaction(), Document::recompute(), Document::recordFeature() (+17 more)

### Community 89 - "SketchEditor::SketchEditor"
Cohesion: 0.10
Nodes (7): QObject, SketchEditor::SketchEditor(), edges, Tool, op, shape, target

### Community 90 - "UserParameter"
Cohesion: 0.33
Nodes (6): UserParameter, comment, expression, name, unit, value

### Community 91 - "UiCommand"
Cohesion: 0.07
Nodes (17): UiCommand, enabled, icon, id, name, panel, run, shortcut (+9 more)

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
Cohesion: 0.11
Nodes (21): BodyFrame, diag, dx, dy, dz, x0, y0, z0 (+13 more)

### Community 98 - "FakeDoc"
Cohesion: 0.17
Nodes (6): FakeDoc, aborts, commits, items, open, snapshot

### Community 99 - "TEST"
Cohesion: 0.21
Nodes (3): slurp(), TEST(), tmp()

### Community 100 - "Zip.cpp"
Cohesion: 0.19
Nodes (11): Entry, data, name, ZipError, crc32(), get16(), get32(), put16() (+3 more)

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
Cohesion: 0.25
Nodes (5): PlaneEdges, arcs, curves, segments, vertices

### Community 110 - "openWallBand"
Cohesion: 0.25
Nodes (12): Section, Circular, Square, Triangular, TopologyCounts, shells, solids, anyPerpendicular() (+4 more)

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

### Community 118 - "Feature"
Cohesion: 0.22
Nodes (9): Feature, commandId, error, id, inputs, name, rolledBack, suppressed (+1 more)

### Community 119 - "Rect"
Cohesion: 0.50
Nodes (4): Session::notifyChanged(), Rect, l, p

### Community 120 - ".openMarkingMenu"
Cohesion: 0.11
Nodes (4): MainWindow::beginSketch(), MainWindow::buildSketchTab(), MainWindow::enterSketchMode(), MainWindow::buildUiCommands()

### Community 123 - "Placement"
Cohesion: 0.25
Nodes (7): Placement, angle, cx, cy, dx, dy, scale

### Community 125 - "rect"
Cohesion: 0.28
Nodes (3): SelectionBox, crossing, rect()

### Community 126 - "Column"
Cohesion: 0.33
Nodes (6): Column, kComment, kExpression, kParameter, kUnit, kValue

### Community 132 - "openWallBand"
Cohesion: 0.22
Nodes (10): BoundingBox, max, min, WallSide, Center, Side1, Side2, offsetOpenWire() (+2 more)

## Knowledge Gaps
- **665 isolated node(s):** `ok`, `output`, `error`, `isReal`, `real` (+660 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 1255 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **28 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `Viewport` connect `Viewport` to `ViewportAnalysis.cpp`, `Handle`, `fromInternal`, `Viewport::setDragArrow`, `Viewport.cpp`, `QTimer`, `optional`, `Viewport.h`, `SketchDisplay`, `.toPixels`, `ViewportArrow.cpp`, `.selectedSubShapes`, `rect`, `.redrawAll`, `QMouseEvent`?**
  _High betweenness centrality (0.110) - this node is a cross-community bridge._
- **What connects `ok`, `output`, `error` to the rest of the system?**
  _665 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Viewport` be split into smaller, more focused modules?**
  _Cohesion score 0.01815408085430969 - nodes in this community are weakly interconnected._
- **Why does `optional` connect `optional` to `Viewport`, `MainWindow`, `QString`, `Kernel.cpp`, `DocCommands.cpp`, `Io.cpp`, `Parser`, `SketchEditor.cpp`, `ViewportArrow.cpp`, `ViewportSketch.cpp`, `sketchFor`, `SketchOps.cpp`, `CommandDialog.cpp`, `Constraint`, `TEST`, `Snap`, `Viewport.h`, `Document.cpp`, `InputDef`, `ViewportAnalysis.cpp`, `TopoDS_Shape`, `string`, `SketchDisplay`, `Kernel.h`, `Document::reevaluateParameters`, `SketchRecord`, `ConstructionPoint`, `ConstructionAxis`, `Feature`?**
  _High betweenness centrality (0.104) - this node is a cross-community bridge._
- **Should `Icons.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.05839317165695705 - nodes in this community are weakly interconnected._
- **Why does `SketchEditor` connect `SketchEditor` to `Viewport`, `.hitTest`, `Constraint`, `TEST`, `Display`, `optional`, `PlaneEdges`, `Kind`, `Pick`, `Snap`, `Parser`, `SketchEditor.cpp`, `.updatePreview`, `.rebuild`, `SketchEditor::SketchEditor`, `Entity`, `QMouseEvent`?**
  _High betweenness centrality (0.092) - this node is a cross-community bridge._
- **Should `ViewportAnalysis.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.12631578947368421 - nodes in this community are weakly interconnected._