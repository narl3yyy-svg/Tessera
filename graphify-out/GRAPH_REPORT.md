# Graph Report - tessera  (2026-11-13)

## Corpus Check
- 349 files · ~207,097 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 40 file(s) not represented in the graph (top: .drive 32, (none) 5, .cmake 1)

## Summary
- 3214 nodes · 8075 edges · 134 communities (105 shown, 29 thin omitted)
- Extraction: 84% EXTRACTED · 16% INFERRED · 0% AMBIGUOUS · INFERRED: 1260 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `1eeb3eed`
- Run `git rev-parse HEAD` and compare to check if the graph is stale.
- Run `graphify update .` after code changes (no API cost).

## Community Hubs (Navigation)
- Viewport
- Icons.cpp
- DocCommands.cpp
- MainWindow
- run_oracle.py
- CommandContext
- Document
- Viewport.cpp
- SketchEditor
- QString
- optional
- Kernel.cpp
- .projectAt
- Kind
- MainWindowTools.cpp
- CommandDialog
- Io.cpp
- Unit
- Session
- SketchEditor.cpp
- .redrawAll
- .updatePreview
- TEST
- Sketch.cpp
- ViewportSketch.cpp
- SketchPalette
- Constraint
- Inputs
- AdskModule.cpp
- Colors
- KernelError
- SketchOps.cpp
- Session.cpp
- ParameterCompleter
- string
- CommandDialog.cpp
- Command.cpp
- solve
- ViewportAnalysis.cpp
- CommandSession
- ConstraintType
- TEST
- Pick
- Snap
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
- src/main.cpp
- ViewportArrow.cpp
- string
- CommandRegistry
- cmath
- TopoDS_Shape
- Theme
- FileFormat
- .motion
- src/main.cpp
- QObject
- Viewport.h
- InputType
- Feature
- Rect
- math
- Value.h
- SketchDisplay
- PYBIND11_EMBEDDED_MODULE
- Measurement
- rect
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
- CommandRegistry::run
- MarkingMenu
- BodyFrame
- FakeDoc
- TEST
- Zip.cpp
- Handle
- OcafApp.h
- Document::reevaluateParameters
- SketchRecord
- ModelParameter
- SectionState
- Display
- Column
- string
- openWallBand
- ConstructionPoint
- ConstructionAxis
- main
- uninstall.sh
- install.sh
- Development
- Mesh
- FeatureEffect
- BooleanOp
- ThreadInfo
- fail
- smoke
- Sketch.h
- ChamferType
- Session::addListener
- LAB_NOTES.md
- build.sh
- live-test.sh

## God Nodes (most connected - your core abstractions)
1. `Viewport` - 227 edges
2. `MainWindow` - 172 edges
3. `SketchEditor` - 166 edges
4. `Inputs` - 136 edges
5. `Document` - 128 edges
6. `CommandContext` - 102 edges
7. `render()` - 95 edges
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

## Communities (134 total, 29 thin omitted)

### Community 0 - "Viewport"
Cohesion: 0.02
Nodes (57): view_, QLineEdit, Viewport, analysis_, analysisObjects_, appliedGridStep_, arrowBoxes_, arrowDragging_ (+49 more)

### Community 1 - "Icons.cpp"
Cohesion: 0.06
Nodes (101): arc3Icon(), arcIcon(), arrow(), axisIcon(), box(), centerRectIcon(), chamferIcon(), circle2Icon() (+93 more)

### Community 2 - "DocCommands.cpp"
Cohesion: 0.10
Nodes (18): ConstructAxisPoint, def_, kind_, evaluateDimensions(), makeBox(), makeCone(), makeCylinder(), makeSphere() (+10 more)

### Community 4 - "MainWindow"
Cohesion: 0.03
Nodes (63): CommandDialog, MainWindow, active_, arrowInput_, arrowInput2_, bodiesBeforeCommand_, combEdges_, combPicking_ (+55 more)

### Community 5 - "run_oracle.py"
Cohesion: 0.08
Nodes (54): add_point(), arc_poly(), body_at(), body_list(), build_sketch(), chain(), circumcentre(), cm() (+46 more)

### Community 6 - "CommandContext"
Cohesion: 0.03
Nodes (55): Adding a tool, Command, CommandContext, CommandDef, feature, icon, id, inputs (+47 more)

### Community 7 - "Document"
Cohesion: 0.03
Nodes (11): Document, effects_, modified_, pendingTools_, registry_, replaying_, txnBodies_, FromOcaf (+3 more)

### Community 8 - "Viewport.cpp"
Cohesion: 0.07
Nodes (4): keys(), qc(), rgb(), Viewport::Viewport()

### Community 9 - "SketchEditor"
Cohesion: 0.03
Nodes (44): SketchEditor, arcDrag_, arcDragMoved_, arcEndsChain_, arcFrom_, arcRef_, bodyEdges_, boxing_ (+36 more)

### Community 10 - "QString"
Cohesion: 0.11
Nodes (5): ExpressionSpinBox, eval_, expression_, shown_, formatNumber()

### Community 13 - ".projectAt"
Cohesion: 0.14
Nodes (5): PlaneEdges, arcs, segments, vertices, edges

### Community 14 - "Kind"
Cohesion: 0.10
Nodes (19): EdgeFeature, def_, kind_, Kind, Angle, AxisCylinder, AxisEdge, AxisTwoPlanes (+11 more)

### Community 15 - "MainWindowTools.cpp"
Cohesion: 0.08
Nodes (20): QDialog, MainWindow::checkInterference(), MainWindow::chooseUnits(), MainWindow::driveJoints(), MainWindow::exportDesign(), MainWindow::formatLength(), MainWindow::gridSettings(), MainWindow::insertFile() (+12 more)

### Community 16 - "CommandDialog"
Cohesion: 0.05
Nodes (31): CommandDialog, bodiesId_, bodiesLabel_, bodyInput_, buttons_, cmd_, conditional_, edgesId_ (+23 more)

### Community 17 - "Io.cpp"
Cohesion: 0.11
Nodes (15): MainWindow::print3d(), NamedShape, compoundOf(), exportShapes(), fmt(), formatForPath(), fromBrep(), importShape() (+7 more)

### Community 18 - "Unit"
Cohesion: 0.07
Nodes (50): MainWindow::lengthUnit(), ExpressionEnv, lengthUnit, lookup, ExpressionError, Quantity, angle, length (+42 more)

### Community 19 - "Session"
Cohesion: 0.10
Nodes (7): PythonHost::PythonHost(), Session, commands_, doc_, listeners_, nextListener_, path_

### Community 21 - ".redrawAll"
Cohesion: 0.13
Nodes (9): NavPreset, Fusion, SolidWorks, Tinkercad, rgb(), Viewport::clearDragArrow(), Viewport::clearSecondArrow(), Viewport::rebuildArrow() (+1 more)

### Community 23 - "TEST"
Cohesion: 0.08
Nodes (7): Sketch, constraints, entities, points, Sketch::addCircle(), Sketch::addLine(), TEST()

### Community 24 - "Sketch.cpp"
Cohesion: 0.09
Nodes (17): Point, x, y, SketchError, entityTypeName(), isDimension(), Sketch::addConstraint(), Sketch::addSpline() (+9 more)

### Community 25 - "ViewportSketch.cpp"
Cohesion: 0.08
Nodes (6): faceStyle(), lineStyle(), rgb(), Viewport::lookAt(), Viewport::planePoint(), Viewport::toWidget()

### Community 26 - "SketchPalette"
Cohesion: 0.05
Nodes (26): flatButton(), MainWindow::buildSketchTab(), QLabel, QToolButton, QWidget, SketchEditor, SketchPalette, body_ (+18 more)

### Community 27 - "Constraint"
Cohesion: 0.10
Nodes (20): Constraint, driven, entities, expression, hasLabel, labelX, labelY, name (+12 more)

### Community 28 - "Inputs"
Cohesion: 0.11
Nodes (17): Inputs, axisOf(), Hole, def_, Loft, def_, Pipe, def_ (+9 more)

### Community 29 - "AdskModule.cpp"
Cohesion: 0.07
Nodes (20): Application, bindAdsk(), BRepBodies, BRepBody, index, Component, Design, Product (+12 more)

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
Cohesion: 0.19
Nodes (18): historyEdit(), Session::deleteFeature(), Session::deleteParameter(), Session::editFeature(), Session::newDocument(), Session::open(), Session::redo(), Session::renameBody() (+10 more)

### Community 34 - "ParameterCompleter"
Cohesion: 0.12
Nodes (9): MainWindow::attachArrowCompleters(), ParameterCompleter, completer_, edit_, names_, ParameterCompleter::ParameterCompleter(), public, QCompleter (+1 more)

### Community 35 - "string"
Cohesion: 0.12
Nodes (10): AddUserParameter, def_, Combine, def_, isIdentifier(), jointOrigin(), JointPick, frame (+2 more)

### Community 37 - "Command.cpp"
Cohesion: 0.22
Nodes (11): expressionKey(), checkInputValue(), CommandContext::evaluateExpression(), CommandDef::input(), CommandSession::applyInTransaction(), CommandSession::cancel(), CommandSession::execute(), CommandSession::preview() (+3 more)

### Community 38 - "solve"
Cohesion: 0.18
Nodes (12): addConstraintChecked(), Layout, n, px, py, rad, makeLayout(), pack() (+4 more)

### Community 39 - "ViewportAnalysis.cpp"
Cohesion: 0.13
Nodes (5): packed(), ramp(), shade(), Viewport::buildAnalysis(), Viewport::setCurvatureComb()

### Community 40 - "CommandSession"
Cohesion: 0.17
Nodes (6): CommandSession, inputs_, OwnedCommand, owned, OwningCommandSession, Session::begin()

### Community 41 - "ConstraintType"
Cohesion: 0.08
Nodes (24): ConstraintType, Angle, Coincident, Collinear, Concentric, Diameter, Distance, Equal (+16 more)

### Community 42 - "TEST"
Cohesion: 0.09
Nodes (3): param(), TEST(), tmp()

### Community 43 - "Pick"
Cohesion: 0.12
Nodes (14): Pick, bodyArc, bodyPoint, bodySegment, hit, midpointOf, onEntity, onXAxis (+6 more)

### Community 44 - "Snap"
Cohesion: 0.11
Nodes (18): Snap, alignX, alignY, bodyArc, bodySegment, entity, fromX, fromY (+10 more)

### Community 45 - "Kind"
Cohesion: 0.09
Nodes (21): HudField, edit, editing, kind, locked, value, Kind, Angle (+13 more)

### Community 46 - "Inputs"
Cohesion: 0.12
Nodes (21): CommandError, getBool(), getInt(), getReal(), applyOperation(), bodyCentre(), bodyName(), CopyFn (+13 more)

### Community 47 - "AnalysisSettings"
Cohesion: 0.08
Nodes (21): AnalysisKind, CurvatureMap, Draft, None, Zebra, AnalysisSettings, curvatureScale, draftAngle (+13 more)

### Community 48 - "Document.cpp"
Cohesion: 0.09
Nodes (28): ConstructionPlane, name, spec, Document::axes(), Document::bodies(), Document::body(), Document::bodyName(), Document::components() (+20 more)

### Community 50 - "MainWindowSketch.cpp"
Cohesion: 0.05
Nodes (19): MainWindow::cancelSketch(), MainWindow::editSketch(), MainWindow::finishSketch(), MainWindow::onProfileClicked(), MainWindow::originalShape(), MainWindow::sketchPalette(), MainWindow::sketchVisible(), MainWindow::startSketch() (+11 more)

### Community 51 - "InputDef"
Cohesion: 0.08
Nodes (24): InputDef, choices, defaultValue, id, label, max, min, minExclusive (+16 more)

### Community 54 - "ViewportAnalysis.cpp"
Cohesion: 0.12
Nodes (7): ArrowPlacement, base, dir, edgePlacement(), facesPlacement(), MainWindow::patternCentre(), MainWindow::pickedFaces()

### Community 55 - ".rebuild"
Cohesion: 0.12
Nodes (6): ext(), fixedColor(), freeColor(), qc(), rgb(), wire()

### Community 56 - "Theme.cpp"
Cohesion: 0.19
Nodes (6): setIconTheme(), darkColors(), darkPalette(), darkStyleSheet(), lightColors(), lightStyleSheet()

### Community 57 - "MainWindow.cpp"
Cohesion: 0.04
Nodes (11): PythonHost, commandIcon(), MainWindow::MainWindow(), qs(), MainWindow::beginSketch(), MainWindow::enterSketchMode(), MainWindow::exitSketchMode(), MainWindow::onEdgeClicked() (+3 more)

### Community 58 - "Entity"
Cohesion: 0.22
Nodes (9): Entity, a, b, center, construction, fit, projected, radius (+1 more)

### Community 59 - "xdrive.py"
Cohesion: 0.32
Nodes (14): button(), canvas(), click(), drag(), flush(), geometry(), key(), keycode() (+6 more)

### Community 61 - "SketchGeometry.cpp"
Cohesion: 0.12
Nodes (9): curve(), curves(), customPlaneSpec(), interiorPoint(), planeFrame(), profileAt(), profiles(), toSketch() (+1 more)

### Community 63 - "ViewportArrow.cpp"
Cohesion: 0.07
Nodes (16): MarkingMenu::mouseMoveEvent(), QMouseEvent, ViewInteractor, Viewport::frontEdgeOwner(), segmentDistance(), Viewport::arrowAt(), Viewport::arrowMouseMove(), Viewport::arrowMousePress() (+8 more)

### Community 64 - "string"
Cohesion: 0.10
Nodes (30): completeEdgeReferences(), completeFaceReferences(), decode(), decodeFaces(), dot(), edgeReference(), EdgeSig, full (+22 more)

### Community 65 - "CommandRegistry"
Cohesion: 0.14
Nodes (3): CommandRegistry, cmds_, TEST()

### Community 66 - "cmath"
Cohesion: 0.15
Nodes (11): Result, error, ok, output, captured(), PythonHost::exec(), PythonHost::runScript(), Case (+3 more)

### Community 67 - "TopoDS_Shape"
Cohesion: 0.15
Nodes (24): SurfacePoint, normal, point, Vec3, asSolid(), boundingBox(), edgeMidpoint(), edgesNear() (+16 more)

### Community 68 - "Theme"
Cohesion: 0.22
Nodes (4): Theme, colors_, public, styled_

### Community 69 - "FileFormat"
Cohesion: 0.17
Nodes (12): FileFormat, Brep, Iges, Obj, Step, Stl, ThreeMF, FormatInfo (+4 more)

### Community 70 - ".motion"
Cohesion: 0.21
Nodes (4): Coil, def_, Joint, def_

### Community 71 - "src/main.cpp"
Cohesion: 0.05
Nodes (20): MainWindow::sectionFrame(), MainWindow::sectionPlane(), MainWindow::setSelectionFilter(), MainWindow::showParameters(), MainWindow::updateSectionArrow(), number(), ParametersDialog, building_ (+12 more)

### Community 74 - "Viewport.h"
Cohesion: 0.09
Nodes (6): QLabel, Profile, area, face, x, y

### Community 75 - "InputType"
Cohesion: 0.12
Nodes (17): InputType, Axis, Bodies, Body, Bool, Choice, Edges, Faces (+9 more)

### Community 76 - "Feature"
Cohesion: 0.22
Nodes (9): Feature, commandId, error, id, inputs, name, rolledBack, suppressed (+1 more)

### Community 77 - "Rect"
Cohesion: 0.50
Nodes (4): Session::notifyChanged(), Rect, l, p

### Community 80 - "SketchDisplay"
Cohesion: 0.13
Nodes (10): ProfileObject, index, sketch, SketchDisplay, construction, curves, frame, name (+2 more)

### Community 82 - "Measurement"
Cohesion: 0.09
Nodes (20): BoundingBox, max, min, Kind, Angle, Area, Length, Volume (+12 more)

### Community 83 - "rect"
Cohesion: 0.28
Nodes (3): SelectionBox, crossing, rect()

### Community 84 - "Axis"
Cohesion: 0.50
Nodes (4): Axis, X, Y, Z

### Community 85 - "Level"
Cohesion: 0.16
Nodes (13): debug(), error(), info(), Level, Debug, Error, Info, Warning (+5 more)

### Community 86 - "README.md"
Cohesion: 0.10
Nodes (16): Architecture, How a command works, The document, Units, Known gaps, Reference parts, Fusion feature checklist, Roadmap (+8 more)

### Community 87 - "Document.cpp"
Cohesion: 0.12
Nodes (25): DocumentError, Document::abortTransaction(), Document::addBody(), Document::addUserParameter(), Document::commitTransaction(), Document::openTransaction(), Document::recompute(), Document::recordFeature() (+17 more)

### Community 89 - "SketchEditor::SketchEditor"
Cohesion: 0.14
Nodes (8): Hit, index, kind, SketchEditor::SketchEditor(), Tool, op, shape, target

### Community 90 - "UserParameter"
Cohesion: 0.33
Nodes (6): UserParameter, comment, expression, name, unit, value

### Community 91 - "UiCommand"
Cohesion: 0.13
Nodes (12): UiCommand, enabled, icon, id, name, panel, run, shortcut (+4 more)

### Community 93 - "Known differences still to build"
Cohesion: 0.15
Nodes (12): Data and files, Findings from the videos, Fusion study list, Interface, Known differences still to build, Navigation and display, Selection and the canvas, Sketch (+4 more)

### Community 94 - "ChainSegment"
Cohesion: 0.67
Nodes (3): ChainSegment, entity, forward

### Community 95 - "CommandRegistry::run"
Cohesion: 0.22
Nodes (4): CommandRegistry::add(), CommandRegistry::all(), CommandRegistry::find(), CommandRegistry::run()

### Community 96 - "MarkingMenu"
Cohesion: 0.33
Nodes (3): MarkingMenu, enabled, public

### Community 97 - "BodyFrame"
Cohesion: 0.15
Nodes (14): BodyFrame, diag, dx, dy, dz, x0, y0, z0 (+6 more)

### Community 98 - "FakeDoc"
Cohesion: 0.17
Nodes (6): FakeDoc, aborts, commits, items, open, snapshot

### Community 99 - "TEST"
Cohesion: 0.22
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

### Community 105 - "ModelParameter"
Cohesion: 0.29
Nodes (7): ModelParameter, angle, expression, name, owner, value, Document::modelParameters()

### Community 106 - "SectionState"
Cohesion: 0.25
Nodes (7): SectionState, active, angle, flip, offset, plane, visible

### Community 107 - "Display"
Cohesion: 0.25
Nodes (7): Display, constraints, construction, dimensions, points, profiles, projected

### Community 108 - "Column"
Cohesion: 0.33
Nodes (6): Column, kComment, kExpression, kParameter, kUnit, kValue

### Community 109 - "string"
Cohesion: 0.20
Nodes (13): bodyNumber(), Document::axisFrame(), Document::component(), Document::componentOfBody(), Document::nextAxisName(), Document::nextBodyName(), Document::nextComponentName(), Document::nextDimensionName() (+5 more)

### Community 110 - "openWallBand"
Cohesion: 0.15
Nodes (19): Section, Circular, Square, Triangular, TopologyCounts, edges, faces, shells (+11 more)

### Community 111 - "ConstructionPoint"
Cohesion: 0.33
Nodes (5): ConstructionPoint, name, point, Document::point(), Document::setPoint()

### Community 112 - "ConstructionAxis"
Cohesion: 0.33
Nodes (5): ConstructionAxis, axis, name, Document::axis(), Document::setAxis()

### Community 113 - "main"
Cohesion: 0.21
Nodes (4): listCommands(), main(), usage(), main()

### Community 114 - "uninstall.sh"
Cohesion: 0.52
Nodes (6): die(), manifest_for(), refresh(), uninstall.sh script, step(), usage()

### Community 115 - "install.sh"
Cohesion: 0.60
Nodes (5): die(), refresh(), install.sh script, step(), usage()

### Community 116 - "Development"
Cohesion: 0.40
Nodes (4): Build, Conventions, Development, Tests

### Community 117 - "Mesh"
Cohesion: 0.40
Nodes (3): Mesh, nodes, triangles

### Community 118 - "FeatureEffect"
Cohesion: 0.09
Nodes (16): Body, display, name, shape, Component, bodies, name, FeatureEffect (+8 more)

### Community 119 - "BooleanOp"
Cohesion: 0.50
Nodes (4): BooleanOp, Cut, Intersect, Join

### Community 121 - "ThreadInfo"
Cohesion: 0.50
Nodes (4): ThreadInfo, diameter, internal, pitch

### Community 123 - "smoke"
Cohesion: 0.40
Nodes (5): smoke(), MassProperties, area, centerOfMass, volume

### Community 124 - "Sketch.h"
Cohesion: 0.20
Nodes (7): EntityType, Arc, Circle, Ellipse, Line, Spline, isRound()

### Community 125 - "ChamferType"
Cohesion: 0.67
Nodes (3): ChamferType, DistanceAngle, TwoDistances

## Knowledge Gaps
- **654 isolated node(s):** `ok`, `output`, `error`, `isReal`, `real` (+649 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 1233 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **29 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `optional` connect `optional` to `Viewport`, `DocCommands.cpp`, `MainWindow`, `QString`, `Kernel.cpp`, `Io.cpp`, `Unit`, `Session`, `SketchEditor.cpp`, `ViewportSketch.cpp`, `Inputs`, `SketchOps.cpp`, `CommandDialog.cpp`, `AnalysisSettings`, `Document.cpp`, `InputDef`, `ViewportAnalysis.cpp`, `.rebuild`, `ViewportArrow.cpp`, `TopoDS_Shape`, `Viewport.h`, `Feature`, `Document::reevaluateParameters`, `SketchRecord`, `string`, `ConstructionPoint`, `ConstructionAxis`?**
  _High betweenness centrality (0.127) - this node is a cross-community bridge._
- **What connects `ok`, `output`, `error` to the rest of the system?**
  _654 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Viewport` be split into smaller, more focused modules?**
  _Cohesion score 0.017978190391983496 - nodes in this community are weakly interconnected._
- **Why does `Viewport` connect `Viewport` to `MainWindow`, `Handle`, `ViewportAnalysis.cpp`, `Viewport.cpp`, `QTimer`, `Viewport.h`, `optional`, `AnalysisSettings`, `SketchDisplay`, `MainWindowTools.cpp`, `MainWindowSketch.cpp`, `rect`, `.redrawAll`, `.toPixels`, `MainWindow.cpp`, `.selectedSubShapes`, `ViewportArrow.cpp`?**
  _High betweenness centrality (0.106) - this node is a cross-community bridge._
- **Should `Icons.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.0627370417193426 - nodes in this community are weakly interconnected._
- **Why does `SketchEditor` connect `SketchEditor` to `Viewport`, `QObject`, `Viewport.h`, `Display`, `Pick`, `Kind`, `.projectAt`, `Snap`, `Unit`, `Session`, `SketchEditor.cpp`, `.updatePreview`, `.rebuild`, `SketchEditor::SketchEditor`, `Constraint`, `ViewportArrow.cpp`?**
  _High betweenness centrality (0.094) - this node is a cross-community bridge._
- **Should `DocCommands.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.10283687943262411 - nodes in this community are weakly interconnected._