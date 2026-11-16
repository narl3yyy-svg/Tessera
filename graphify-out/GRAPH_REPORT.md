# Graph Report - tessera  (2026-11-16)

## Corpus Check
- 401 files · ~266,411 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 63 file(s) not represented in the graph (top: .drive 55, (none) 5, .cmake 1)

## Summary
- 3790 nodes · 9721 edges · 130 communities (108 shown, 22 thin omitted)
- Extraction: 85% EXTRACTED · 15% INFERRED · 0% AMBIGUOUS · INFERRED: 1494 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `777a2583`
- Run `git rev-parse HEAD` and compare to check if the graph is stale.
- Run `graphify update .` after code changes (no API cost).

## Community Hubs (Navigation)
- Viewport
- Icons.cpp
- Session.cpp
- MainWindow
- run_oracle.py
- Expression.cpp
- Document
- Viewport.cpp
- SketchEditor
- sketchFor
- optional
- Kernel.cpp
- AnalysisSettings
- Kind
- src/main.cpp
- CommandDialog
- Parser
- Snap
- Document
- Snap
- MainWindow::lookTargets
- Affine
- ViewportSketch.cpp
- SketchPalette
- Sketch
- Inputs
- NewComponent
- Colors
- KernelError
- SketchOps.cpp
- ViewportArrow.cpp
- ParameterCompleter
- Constraint
- DocCommands.cpp
- MainWindow.cpp
- solve
- .eventFilter
- CommandDialog.cpp
- ConstraintType
- AdskModule.cpp
- Pick
- SketchEditor.cpp
- Unit
- Zip.cpp
- AnalysisSettings
- Sketch.cpp
- Document.cpp
- MainWindowSketch.cpp
- InputDef
- validateOperation
- .toPixels
- SketchGeometry.cpp
- Document::recompute
- MarkingMenu.cpp
- Command.cpp
- Entity
- xdrive.py
- adsk_core
- UiCommand
- Session
- Theme.cpp
- BodyFrame
- CommandRegistry
- path
- map
- Theme
- Feature
- InputType
- ParametersDialog.cpp
- Kernel.h
- ViewportAnalysis.cpp
- QMouseEvent
- .mouseMove
- Vec3
- Expression.h
- math
- QString
- SketchDisplay
- Command
- Measurement
- SketchCurves.cpp
- Level
- README.md
- SolveResult
- test_feature_pattern.py
- BodyFrame
- fromInternal
- cmath
- FileFormat
- Known differences still to build
- TEST
- ReplayStep
- Body
- optional
- FakeDoc
- ParamSet
- formatForPath
- MainWindow::MainWindow
- .initLayout
- NamedView
- BoundingBox
- test_rigid_group.py
- SectionState
- Display
- cli_main.cpp
- Mesh
- TopologyCounts
- TestFramework.h
- toDxf
- uninstall.sh
- install.sh
- TestFramework.h
- .rebuild
- MarkingMenu
- EntityType
- test_incremental_replay.py
- Placement
- Viewport::Viewport
- Joint
- LAB_NOTES.md
- build.sh
- live-test.sh
- SplineHandle

## God Nodes (most connected - your core abstractions)
1. `Viewport` - 257 edges
2. `SketchEditor` - 198 edges
3. `MainWindow` - 184 edges
4. `Inputs` - 152 edges
5. `render()` - 122 edges
6. `Document` - 121 edges
7. `CommandContext` - 111 edges
8. `CommandDialog` - 90 edges
9. `Command` - 66 edges
10. `CommandError` - 62 edges

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

## Communities (130 total, 22 thin omitted)

### Community 0 - "Viewport"
Cohesion: 0.02
Nodes (69): view_, QLineEdit, Viewport, analysis_, analysisObjects_, appliedGridStep_, arrowBoxes_, arrowDragging_ (+61 more)

### Community 1 - "Icons.cpp"
Cohesion: 0.05
Nodes (127): accessibilityIcon(), appearanceIcon(), arc3Icon(), arcIcon(), arcTangentIcon(), arrow(), axisIcon(), box() (+119 more)

### Community 2 - "Session.cpp"
Cohesion: 0.08
Nodes (35): CommandSession, inputs_, CommandRegistry::find(), CommandRegistry::run(), historyEdit(), OwnedCommand, owned, OwningCommandSession (+27 more)

### Community 4 - "MainWindow"
Cohesion: 0.03
Nodes (64): CommandDialog, MainWindow, active_, arrowInput_, arrowInput2_, bodiesBeforeCommand_, combEdges_, combPicking_ (+56 more)

### Community 5 - "run_oracle.py"
Cohesion: 0.08
Nodes (54): add_point(), arc_poly(), body_at(), body_list(), build_sketch(), chain(), circumcentre(), cm() (+46 more)

### Community 6 - "Expression.cpp"
Cohesion: 0.17
Nodes (14): ExpressionEnv, lengthUnit, lookup, ExpressionError, evaluateExpression(), evaluateQuantity(), expressionReferences(), isConstantName() (+6 more)

### Community 7 - "Document"
Cohesion: 0.03
Nodes (15): Document, effects_, lastReplayed_, lastReused_, modified_, pendingTools_, registry_, replaying_ (+7 more)

### Community 8 - "Viewport.cpp"
Cohesion: 0.04
Nodes (4): glide(), QKeyEvent, QLabel, QtFrameBuffer

### Community 9 - "SketchEditor"
Cohesion: 0.03
Nodes (58): HandleHit, back, index, spline, PlaneEdges, arcs, curves, segments (+50 more)

### Community 10 - "sketchFor"
Cohesion: 0.17
Nodes (8): Hole, def_, Pipe, def_, Revolve, def_, sectionOf(), sketchFor()

### Community 11 - "optional"
Cohesion: 0.10
Nodes (7): isEmpty(), Value, Profile, area, face, x, y

### Community 13 - "AnalysisSettings"
Cohesion: 0.11
Nodes (18): AnalysisKind, Accessibility, CurvatureMap, Draft, Isocurve, MinimumRadius, None, Zebra (+10 more)

### Community 14 - "Kind"
Cohesion: 0.06
Nodes (32): ConstructPlane, def_, kind_, EdgeFeature, def_, kind_, FaceFeature, def_ (+24 more)

### Community 15 - "src/main.cpp"
Cohesion: 0.06
Nodes (11): grabWindowWithPanels(), writeLiveGeometry(), ArrowPlacement, base, dir, edgePlacement(), facesPlacement(), MainWindow::attachArrowCompleters() (+3 more)

### Community 16 - "CommandDialog"
Cohesion: 0.05
Nodes (33): CommandDialog, bodiesId_, bodiesLabel_, bodyInput_, buttons_, cmd_, conditional_, edgesId_ (+25 more)

### Community 18 - "Parser"
Cohesion: 0.20
Nodes (13): Quantity, angle, length, value, describe(), Parser, ang_, env_ (+5 more)

### Community 19 - "Snap"
Cohesion: 0.09
Nodes (21): HudField, edit, editing, kind, locked, value, Kind, Angle (+13 more)

### Community 21 - "Document"
Cohesion: 0.17
Nodes (12): ConstructAxisPoint, def_, kind_, jointOrigin(), JointPick, frame, parsePoints(), profilesOf() (+4 more)

### Community 22 - "Snap"
Cohesion: 0.11
Nodes (18): Snap, alignX, alignY, bodyArc, bodySegment, entity, fromX, fromY (+10 more)

### Community 24 - "Affine"
Cohesion: 0.13
Nodes (13): Affine, a, b, d, e, Builder, byPlace_, k_ (+5 more)

### Community 25 - "ViewportSketch.cpp"
Cohesion: 0.07
Nodes (7): faceStyle(), lineStyle(), rgb(), Viewport::lookAt(), Viewport::planePoint(), Viewport::toWidget(), height

### Community 26 - "SketchPalette"
Cohesion: 0.03
Nodes (40): QAbstractButton, QAction, MainWindow::buildSketchTab(), MainWindow::applySection(), MainWindow::chooseUnits(), MainWindow::editAppearance(), MainWindow::editMaterial(), MainWindow::insertFile() (+32 more)

### Community 27 - "Sketch"
Cohesion: 0.07
Nodes (10): Sketch, constraints, entities, points, texts, Sketch::addCircle(), Sketch::addConic(), Sketch::addEllipticalArc() (+2 more)

### Community 28 - "Inputs"
Cohesion: 0.11
Nodes (26): CommandError, Inputs, getBool(), getInt(), getReal(), applyOperation(), bodyCentre(), bodyName() (+18 more)

### Community 29 - "NewComponent"
Cohesion: 0.14
Nodes (7): AddUserParameter, def_, isIdentifier(), NewComponent, def_, RigidGroup, def_

### Community 30 - "Colors"
Cohesion: 0.07
Nodes (28): Colors, base, border, cubeBox, cubeText, errorBackground, grid, gridMajor (+20 more)

### Community 31 - "KernelError"
Cohesion: 0.20
Nodes (32): KernelError, asSolid(), boolean(), chamfer(), chamferEx(), deleteFaces(), draft(), extrude() (+24 more)

### Community 32 - "SketchOps.cpp"
Cohesion: 0.17
Nodes (28): at(), chainOf(), chamferCorner(), circularPattern(), copyEntities(), cornerAt(), cross(), dot() (+20 more)

### Community 33 - "ViewportArrow.cpp"
Cohesion: 0.06
Nodes (19): Viewport::frontEdgeOwner(), rgb(), segmentDistance(), Viewport::arrowAt(), Viewport::arrowMouseMove(), Viewport::arrowMousePress(), Viewport::arrowMouseRelease(), Viewport::arrowParam() (+11 more)

### Community 34 - "ParameterCompleter"
Cohesion: 0.11
Nodes (9): QObject, ParameterCompleter, completer_, edit_, names_, ParameterCompleter::ParameterCompleter(), public, QCompleter (+1 more)

### Community 35 - "Constraint"
Cohesion: 0.09
Nodes (13): Constraint, driven, entities, expression, hasLabel, labelX, labelY, name (+5 more)

### Community 36 - "DocCommands.cpp"
Cohesion: 0.12
Nodes (17): axisOf(), evaluateDimensions(), HoleSize, modeled, pitch, radius, Loft, def_ (+9 more)

### Community 37 - "MainWindow.cpp"
Cohesion: 0.09
Nodes (4): commandIcon(), flatButton(), qs(), run

### Community 38 - "solve"
Cohesion: 0.12
Nodes (14): addConstraintChecked(), Layout, n, px, py, rad, makeLayout(), pack() (+6 more)

### Community 41 - "ConstraintType"
Cohesion: 0.08
Nodes (26): ConstraintType, Angle, Coincident, Collinear, Concentric, Curvature, Diameter, Distance (+18 more)

### Community 42 - "AdskModule.cpp"
Cohesion: 0.09
Nodes (16): Application, bindAdsk(), BRepBodies, BRepBody, index, Component, Design, Product (+8 more)

### Community 43 - "Pick"
Cohesion: 0.07
Nodes (20): Hit, index, kind, Pick, bodyArc, bodyPoint, bodySegment, hit (+12 more)

### Community 44 - "SketchEditor.cpp"
Cohesion: 0.12
Nodes (5): angleInArc(), ccwContains(), circumcircle(), lineEntity(), segDistance()

### Community 45 - "Unit"
Cohesion: 0.20
Nodes (13): MainWindow::lengthUnit(), Unit, Centimeter, Degree, Foot, Inch, Meter, Millimeter (+5 more)

### Community 46 - "Zip.cpp"
Cohesion: 0.19
Nodes (13): Entry, data, name, ZipError, crc32(), deflateRaw(), get16(), get32() (+5 more)

### Community 47 - "AnalysisSettings"
Cohesion: 0.10
Nodes (16): DragArrow, base, dir, radius, ref, ring, value, PendingLook (+8 more)

### Community 48 - "Sketch.cpp"
Cohesion: 0.09
Nodes (15): SplineKind, Conic, Control, Fit, entityTypeName(), isDimension(), Sketch::addSpline(), Sketch::addText() (+7 more)

### Community 49 - "Document.cpp"
Cohesion: 0.06
Nodes (67): DocumentError, SketchRecord, data, name, offset, plane, bodyNumber(), checkViewName() (+59 more)

### Community 50 - "MainWindowSketch.cpp"
Cohesion: 0.05
Nodes (20): bindTsr(), fromPy(), toPy(), typeName(), MainWindow::cancelSketch(), MainWindow::editSketch(), MainWindow::finishSketch(), MainWindow::onEdgeClicked() (+12 more)

### Community 51 - "InputDef"
Cohesion: 0.09
Nodes (21): InputDef, choices, defaultValue, id, label, max, min, minExclusive (+13 more)

### Community 52 - "validateOperation"
Cohesion: 0.17
Nodes (8): Primitive, build_, def_, Sweep, def_, Thicken, def_, validateOperation()

### Community 54 - "SketchGeometry.cpp"
Cohesion: 0.07
Nodes (19): conditionedSpline(), curve(), curves(), entityCurves(), G2End, d1, d2, set (+11 more)

### Community 55 - "Document::recompute"
Cohesion: 0.18
Nodes (8): Document::expressionEnv(), Document::recompute(), Document::recordFeature(), Document::removeFeature(), Document::setFeatureInputs(), Document::setFeatureSuppressed(), featureData(), toJson()

### Community 56 - "MarkingMenu.cpp"
Cohesion: 0.08
Nodes (16): MarkingMenu::keyPressEvent(), MarkingMenu::MarkingMenu(), MarkingMenu::mouseMoveEvent(), MarkingMenu::mouseReleaseEvent(), MarkingMenu::paintEvent(), MarkingMenu::popupAt(), MarkingMenu::ringIndexAt(), MarkingMenu::run() (+8 more)

### Community 57 - "Command.cpp"
Cohesion: 0.15
Nodes (17): expressionKey(), Dimension, Angle, Length, Unitless, checkInputValue(), CommandContext::evaluateExpression(), CommandDef::input() (+9 more)

### Community 58 - "Entity"
Cohesion: 0.09
Nodes (20): Entity, a, b, center, construction, fit, handles, included (+12 more)

### Community 59 - "xdrive.py"
Cohesion: 0.28
Nodes (15): button(), canvas(), click(), drag(), flush(), geometry(), key(), keycode() (+7 more)

### Community 61 - "UiCommand"
Cohesion: 0.18
Nodes (9): UiCommand, enabled, icon, id, name, panel, shortcut, tab (+1 more)

### Community 62 - "Session"
Cohesion: 0.05
Nodes (10): main(), smoke(), key, Session, commands_, doc_, listeners_, nextListener_ (+2 more)

### Community 63 - "Theme.cpp"
Cohesion: 0.19
Nodes (6): setIconTheme(), darkColors(), darkPalette(), darkStyleSheet(), lightColors(), lightStyleSheet()

### Community 64 - "BodyFrame"
Cohesion: 0.10
Nodes (31): completeEdgeReferences(), completeFaceReferences(), decode(), decodeFaces(), dot(), edgeReference(), EdgeSig, full (+23 more)

### Community 65 - "CommandRegistry"
Cohesion: 0.08
Nodes (9): Architecture, How a command works, The document, Units, CommandRegistry, cmds_, CommandRegistry::add(), CommandRegistry::all() (+1 more)

### Community 66 - "path"
Cohesion: 0.38
Nodes (10): MainWindow::print3d(), NamedShape, compoundOf(), exportShapes(), fmt(), meshOf(), scaled(), write3mf() (+2 more)

### Community 67 - "map"
Cohesion: 0.27
Nodes (3): env(), mm(), TEST()

### Community 68 - "Theme"
Cohesion: 0.22
Nodes (4): Theme, colors_, public, styled_

### Community 69 - "Feature"
Cohesion: 0.09
Nodes (20): Feature, commandId, error, id, inputs, name, parameterNames, rolledBack (+12 more)

### Community 70 - "InputType"
Cohesion: 0.12
Nodes (17): InputType, Axis, Bodies, Body, Bool, Choice, Edges, Faces (+9 more)

### Community 71 - "ParametersDialog.cpp"
Cohesion: 0.07
Nodes (24): Column, kComment, kExpression, kName, kParameter, kStar, kUnit, kValue (+16 more)

### Community 72 - "Kernel.h"
Cohesion: 0.10
Nodes (19): Axis, X, Y, Z, BooleanOp, Cut, Intersect, Join (+11 more)

### Community 73 - "ViewportAnalysis.cpp"
Cohesion: 0.11
Nodes (6): packed(), ramp(), shade(), Viewport::buildAnalysis(), Viewport::setCurvatureComb(), f

### Community 74 - "QMouseEvent"
Cohesion: 0.27
Nodes (3): QMouseEvent, ViewInteractor, Viewport::setInteractor()

### Community 75 - ".mouseMove"
Cohesion: 0.13
Nodes (7): ext(), fixedColor(), freeColor(), qc(), rgb(), wire(), Sketch::addLine()

### Community 76 - "Vec3"
Cohesion: 0.18
Nodes (20): SurfacePoint, normal, point, Vec3, boundingBox(), edgeMidpoint(), edgesNear(), frame() (+12 more)

### Community 78 - "math"
Cohesion: 0.07
Nodes (3): dist(), check_regular(), dist_to_line()

### Community 79 - "QString"
Cohesion: 0.12
Nodes (5): ExpressionSpinBox, eval_, expression_, shown_, formatNumber()

### Community 80 - "SketchDisplay"
Cohesion: 0.12
Nodes (11): ProfileObject, index, sketch, SketchDisplay, construction, curves, fixedCurves, frame (+3 more)

### Community 81 - "Command"
Cohesion: 0.03
Nodes (59): Adding a tool, Command, CommandContext, CommandDef, feature, icon, id, inputs (+51 more)

### Community 82 - "Measurement"
Cohesion: 0.13
Nodes (14): Kind, Angle, Area, Length, Volume, Measurement, from, hasLine (+6 more)

### Community 83 - "SketchCurves.cpp"
Cohesion: 0.13
Nodes (19): crossings(), crossingsOf(), Curve2d, curve2d(), periodic, t0, t1, endIsFree() (+11 more)

### Community 85 - "Level"
Cohesion: 0.16
Nodes (13): debug(), error(), info(), Level, Debug, Error, Info, Warning (+5 more)

### Community 86 - "README.md"
Cohesion: 0.07
Nodes (23): Build, Conventions, Development, Tests, 3D Sketch, Curvature (G2), Include 3D Geometry, Known gaps (+15 more)

### Community 87 - "SolveResult"
Cohesion: 0.20
Nodes (8): SolveResult, dof, entityFixed, iterations, message, ok, pointFixed, residual

### Community 89 - "BodyFrame"
Cohesion: 0.14
Nodes (15): BodyFrame, diag, dx, dy, dz, x0, y0, z0 (+7 more)

### Community 90 - "fromInternal"
Cohesion: 0.22
Nodes (14): MainWindow::checkInterference(), MainWindow::driveJoints(), MainWindow::formatLength(), MainWindow::gridSettings(), MainWindow::openAnalysis(), MainWindow::openSection(), MainWindow::showCenterOfMass(), MainWindow::updateMeasure() (+6 more)

### Community 91 - "cmath"
Cohesion: 0.18
Nodes (6): Session::notifyChanged(), C(), Rect, rect(), l, p

### Community 92 - "FileFormat"
Cohesion: 0.17
Nodes (12): FileFormat, Brep, Iges, Obj, Step, Stl, ThreeMF, FormatInfo (+4 more)

### Community 93 - "Known differences still to build"
Cohesion: 0.15
Nodes (12): Data and files, Findings from the videos, Fusion study list, Interface, Known differences still to build, Navigation and display, Selection and the canvas, Sketch (+4 more)

### Community 94 - "TEST"
Cohesion: 0.13
Nodes (5): param(), tmp(), slurp(), TEST(), tmp()

### Community 95 - "ReplayStep"
Cohesion: 0.04
Nodes (46): Component, bodies, name, rigid, ConstructionAxis, axis, name, ConstructionPlane (+38 more)

### Community 96 - "Body"
Cohesion: 0.22
Nodes (8): Body, color, display, material, name, shape, Document::component(), Document::components()

### Community 98 - "FakeDoc"
Cohesion: 0.17
Nodes (6): FakeDoc, aborts, commits, items, open, snapshot

### Community 99 - "ParamSet"
Cohesion: 0.08
Nodes (29): ModelParameter, angle, expression, input, label, name, owner, unit (+21 more)

### Community 100 - "formatForPath"
Cohesion: 0.32
Nodes (6): formatForPath(), fromBrep(), importShape(), lower(), toBrep(), xmlEscape()

### Community 101 - "MainWindow::MainWindow"
Cohesion: 0.07
Nodes (8): PythonHost, MainWindow::MainWindow(), MainWindow::beginSketch(), MainWindow::enterSketchMode(), MainWindow::exitSketchMode(), MainWindow::showPreferences(), QTimer, Viewport::selectArrowValue()

### Community 103 - "NamedView"
Cohesion: 0.33
Nodes (6): NamedView, eye, name, size, target, up

### Community 104 - "BoundingBox"
Cohesion: 0.23
Nodes (14): BoundingBox, max, min, WallSide, Center, Side1, Side2, extendedWire() (+6 more)

### Community 106 - "SectionState"
Cohesion: 0.25
Nodes (7): SectionState, active, angle, flip, offset, plane, visible

### Community 107 - "Display"
Cohesion: 0.25
Nodes (7): Display, constraints, construction, dimensions, points, profiles, projected

### Community 108 - "cli_main.cpp"
Cohesion: 0.28
Nodes (3): listCommands(), main(), usage()

### Community 109 - "Mesh"
Cohesion: 0.40
Nodes (3): Mesh, nodes, triangles

### Community 110 - "TopologyCounts"
Cohesion: 0.18
Nodes (16): Section, Circular, Square, Triangular, TopologyCounts, edges, faces, shells (+8 more)

### Community 111 - "TestFramework.h"
Cohesion: 0.14
Nodes (6): Case, fn, name, fail(), Failure, Register

### Community 113 - "toDxf"
Cohesion: 0.23
Nodes (10): Point, x, y, z, SketchError, Sketch::checkIndices(), Sketch::fromJson(), customPlaneSpec() (+2 more)

### Community 114 - "uninstall.sh"
Cohesion: 0.52
Nodes (6): die(), manifest_for(), refresh(), uninstall.sh script, step(), usage()

### Community 115 - "install.sh"
Cohesion: 0.60
Nodes (5): die(), refresh(), install.sh script, step(), usage()

### Community 116 - "TestFramework.h"
Cohesion: 0.19
Nodes (9): Result, error, ok, output, captured(), PYBIND11_EMBEDDED_MODULE(), PythonHost::exec(), PythonHost::PythonHost() (+1 more)

### Community 117 - ".rebuild"
Cohesion: 0.10
Nodes (12): hiddenColour(), qc(), rgb(), sharpEdges(), Style, Shaded, ShadedEdges, ShadedHidden (+4 more)

### Community 118 - "MarkingMenu"
Cohesion: 0.25
Nodes (3): MarkingMenu, enabled, public

### Community 121 - "EntityType"
Cohesion: 0.29
Nodes (7): EntityType, Arc, Circle, Ellipse, Line, Spline, isRound()

### Community 123 - "Placement"
Cohesion: 0.16
Nodes (10): ChainSegment, entity, forward, Placement, angle, cx, cy, dx (+2 more)

### Community 127 - "Viewport::Viewport"
Cohesion: 0.14
Nodes (8): keys(), NavPreset, Fusion, SolidWorks, Tinkercad, SelectionBox, crossing, Viewport::Viewport()

### Community 129 - "Joint"
Cohesion: 0.42
Nodes (3): Joint, asBuilt_, def_

### Community 142 - "SplineHandle"
Cohesion: 0.25
Nodes (8): SplineHandle, arm, index, set, tx, ty, x, y

## Knowledge Gaps
- **782 isolated node(s):** `ok`, `output`, `error`, `isReal`, `real` (+777 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 1471 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **22 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `optional` connect `optional` to `Viewport`, `MainWindow`, `Expression.cpp`, `Viewport.cpp`, `SketchEditor`, `sketchFor`, `optional`, `Kernel.cpp`, `src/main.cpp`, `CommandDialog`, `Parser`, `ViewportSketch.cpp`, `SketchOps.cpp`, `ViewportArrow.cpp`, `DocCommands.cpp`, `CommandDialog.cpp`, `SketchEditor.cpp`, `Unit`, `AnalysisSettings`, `Document.cpp`, `InputDef`, `SketchGeometry.cpp`, `Session`, `Feature`, `Kernel.h`, `.mouseMove`, `Vec3`, `Expression.h`, `QString`, `SketchCurves.cpp`, `ReplayStep`, `Body`, `ParamSet`, `formatForPath`?**
  _High betweenness centrality (0.153) - this node is a cross-community bridge._
- **What connects `ok`, `output`, `error` to the rest of the system?**
  _782 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Viewport` be split into smaller, more focused modules?**
  _Cohesion score 0.0159809183064997 - nodes in this community are weakly interconnected._
- **Why does `Viewport` connect `Viewport` to `MainWindow`, `Viewport.cpp`, `AnalysisSettings`, `ViewportSketch.cpp`, `ViewportArrow.cpp`, `AnalysisSettings`, `MainWindowSketch.cpp`, `.toPixels`, `ViewportAnalysis.cpp`, `QMouseEvent`, `SketchDisplay`, `SketchCurves.cpp`, `fromInternal`, `cmath`, `optional`, `MainWindow::MainWindow`, `.setSelectionFilter`, `.rebuild`, `Viewport::Viewport`?**
  _High betweenness centrality (0.124) - this node is a cross-community bridge._
- **Should `Icons.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.05254926493587739 - nodes in this community are weakly interconnected._
- **Why does `SketchEditor` connect `SketchEditor` to `Viewport`, `optional`, `Snap`, `.solveAndShow`, `Snap`, `ParameterCompleter`, `Constraint`, `.eventFilter`, `Pick`, `SketchEditor.cpp`, `Unit`, `Entity`, `Session`, `QMouseEvent`, `.mouseMove`, `SolveResult`, `ReplayStep`, `optional`, `Display`?**
  _High betweenness centrality (0.114) - this node is a cross-community bridge._
- **Should `Session.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.08200290275761973 - nodes in this community are weakly interconnected._