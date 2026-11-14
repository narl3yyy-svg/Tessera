# Graph Report - tessera  (2026-11-13)

## Corpus Check
- 382 files · ~242,151 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 56 file(s) not represented in the graph (top: .drive 48, (none) 5, .cmake 1)

## Summary
- 3590 nodes · 9121 edges · 142 communities (114 shown, 28 thin omitted)
- Extraction: 85% EXTRACTED · 15% INFERRED · 0% AMBIGUOUS · INFERRED: 1394 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `dce225ff`
- Run `git rev-parse HEAD` and compare to check if the graph is stale.
- Run `graphify update .` after code changes (no API cost).

## Community Hubs (Navigation)
- Viewport
- Icons.cpp
- Session.cpp
- tsr
- MainWindow
- run_oracle.py
- Document
- Viewport.cpp
- SketchEditor
- Document::recompute
- optional
- Kernel.cpp
- AnalysisSettings
- Kind
- .openMarkingMenu
- CommandDialog
- Io.cpp
- Unit
- MainWindowTools.cpp
- Unit
- Document
- MainWindow.cpp
- TEST
- Sketch.cpp
- ViewportSketch.cpp
- SketchPalette
- Snap
- Inputs
- string
- Colors
- KernelError
- SketchOps.cpp
- ViewportArrow.cpp
- ParameterCompleter
- Constraint
- Joint
- .applyPreSelection
- solve
- TsrModule.cpp
- CommandDialog.cpp
- ConstraintType
- AdskModule.cpp
- Pick
- SketchEditor.cpp
- rect
- Zip.cpp
- AnalysisSettings
- .rebuild
- ParamSet
- MainWindowSketch.cpp
- InputDef
- sketchFor
- .toPixels
- MainWindowArrow.cpp
- CommandSession
- Theme.cpp
- QDialog
- Entity
- xdrive.py
- Session
- ViewportArrow.cpp
- BodyFrame
- CommandRegistry
- MainWindow::MainWindow
- BodyFrame
- Theme
- string
- ParametersDialog.cpp
- TEST
- ParametersDialog.h
- Column
- InputType
- Vec3
- QString
- Command.cpp
- SketchDisplay
- CommandDef
- Measurement
- SketchCurves.cpp
- MarkingMenu.cpp
- Level
- README.md
- string
- test_feature_pattern.py
- .add
- EntityType
- FileFormat
- Known differences still to build
- openWallBand
- ReplayStep
- ParameterCompleter.cpp
- Tool
- FakeDoc
- Icons.h
- src/main.cpp
- NavPreset
- sstream
- UserParameter
- Loft
- Joints
- SectionState
- Display
- main
- PlaneEdges
- openWallBand
- Profile
- Session::addListener
- Axis
- uninstall.sh
- install.sh
- TestFramework.h
- BooleanOp
- ThreadInfo
- Value.h
- test_incremental_replay.py
- Placement
- ChainSegment
- curve
- HandleHit
- smoke
- .mouseMove
- Rect
- ChamferType
- DocCommands.cpp
- Placement::apply
- LAB_NOTES.md
- MarkingMenu
- Dimension
- build.sh
- live-test.sh
- fail
- Point
- SplineHandle

## God Nodes (most connected - your core abstractions)
1. `Viewport` - 251 edges
2. `SketchEditor` - 185 edges
3. `MainWindow` - 179 edges
4. `Inputs` - 140 edges
5. `Document` - 118 edges
6. `render()` - 110 edges
7. `CommandContext` - 102 edges
8. `CommandDialog` - 90 edges
9. `Command` - 63 edges
10. `CommandError` - 57 edges

## Surprising Connections (you probably didn't know these)
- `Tests` --references--> `unit()`  [INFERRED]
  docs/DEVELOPMENT.md → modules/sketch/src/SketchOps.cpp
- `Known gaps` --references--> `QTabWidget`  [INFERRED]
  docs/KNOWN_GAPS.md → modules/app/src/MainWindow.h
- `Architecture` --references--> `InputDef`  [INFERRED]
  docs/ARCHITECTURE.md → modules/core/include/tsr/core/Command.h
- `How a command works` --references--> `CommandDef`  [INFERRED]
  docs/ARCHITECTURE.md → modules/core/include/tsr/core/Command.h
- `Adding a tool` --references--> `CommandDef`  [INFERRED]
  docs/DEVELOPMENT.md → modules/core/include/tsr/core/Command.h

## Import Cycles
- None detected.

## Communities (142 total, 28 thin omitted)

### Community 0 - "Viewport"
Cohesion: 0.02
Nodes (67): view_, QLineEdit, Viewport, analysis_, analysisObjects_, appliedGridStep_, arrowBoxes_, arrowDragging_ (+59 more)

### Community 1 - "Icons.cpp"
Cohesion: 0.06
Nodes (115): arc3Icon(), arcIcon(), arcTangentIcon(), arrow(), axisIcon(), box(), breakIcon(), centerRectIcon() (+107 more)

### Community 2 - "Session.cpp"
Cohesion: 0.18
Nodes (23): historyEdit(), plainEdit(), Session::addNamedView(), Session::deleteFeature(), Session::deleteNamedView(), Session::deleteParameter(), Session::newDocument(), Session::open() (+15 more)

### Community 3 - "tsr"
Cohesion: 0.05
Nodes (3): PYBIND11_EMBEDDED_MODULE(), letters(), dist_to_line()

### Community 4 - "MainWindow"
Cohesion: 0.03
Nodes (64): writeLiveGeometry(), CommandDialog, MainWindow, active_, arrowInput_, arrowInput2_, bodiesBeforeCommand_, combEdges_ (+56 more)

### Community 5 - "run_oracle.py"
Cohesion: 0.08
Nodes (54): add_point(), arc_poly(), body_at(), body_list(), build_sketch(), chain(), circumcentre(), cm() (+46 more)

### Community 7 - "Document"
Cohesion: 0.03
Nodes (16): Document, effects_, lastReplayed_, lastReused_, modified_, pendingTools_, registry_, replaying_ (+8 more)

### Community 8 - "Viewport.cpp"
Cohesion: 0.05
Nodes (4): glide(), keys(), QKeyEvent, QtFrameBuffer

### Community 9 - "SketchEditor"
Cohesion: 0.03
Nodes (53): HudField, edit, editing, kind, locked, value, QLineEdit, SketchEditor (+45 more)

### Community 10 - "Document::recompute"
Cohesion: 0.16
Nodes (9): Document::expressionEnv(), Document::openTransaction(), Document::recompute(), Document::recordFeature(), Document::removeFeature(), Document::setFeatureInputs(), Document::setFeatureSuppressed(), featureData() (+1 more)

### Community 12 - "Kernel.cpp"
Cohesion: 0.04
Nodes (6): dot(), faceScore(), isoCoarsePitch(), score(), topologyCounts(), vec()

### Community 13 - "AnalysisSettings"
Cohesion: 0.09
Nodes (14): AnalysisKind, CurvatureMap, Draft, None, Zebra, AnalysisSettings, curvatureScale, draftAngle (+6 more)

### Community 14 - "Kind"
Cohesion: 0.07
Nodes (26): ConstructPlane, def_, kind_, EdgeFeature, def_, kind_, Kind, Angle (+18 more)

### Community 15 - ".openMarkingMenu"
Cohesion: 0.10
Nodes (6): MainWindow::buildSketchTab(), MainWindow::enterSketchMode(), MainWindow::exitSketchMode(), MainWindow::applySection(), QTimer, Viewport::selectArrowValue()

### Community 16 - "CommandDialog"
Cohesion: 0.05
Nodes (31): CommandDialog, bodiesId_, bodiesLabel_, bodyInput_, buttons_, cmd_, conditional_, edgesId_ (+23 more)

### Community 17 - "Io.cpp"
Cohesion: 0.10
Nodes (19): MainWindow::print3d(), NamedShape, compoundOf(), exportShapes(), fmt(), formatForPath(), fromBrep(), importShape() (+11 more)

### Community 18 - "Unit"
Cohesion: 0.07
Nodes (45): MainWindow::lengthUnit(), ExpressionEnv, lengthUnit, lookup, ExpressionError, Quantity, angle, length (+37 more)

### Community 19 - "MainWindowTools.cpp"
Cohesion: 0.08
Nodes (7): MainWindow::chooseUnits(), MainWindow::insertFile(), MainWindow::sectionFrame(), MainWindow::sectionPlane(), MainWindow::setSelectionFilter(), MainWindow::showParameters(), MainWindow::updateSectionArrow()

### Community 20 - "Unit"
Cohesion: 0.15
Nodes (13): MainWindow::checkInterference(), MainWindow::driveJoints(), MainWindow::formatLength(), MainWindow::gridSettings(), MainWindow::openAnalysis(), MainWindow::openSection(), MainWindow::showCenterOfMass(), MainWindow::updateMeasure() (+5 more)

### Community 21 - "Document"
Cohesion: 0.15
Nodes (14): ConstructAxisPoint, def_, kind_, jointOrigin(), JointPick, frame, parsePoints(), pickedFaces() (+6 more)

### Community 23 - "TEST"
Cohesion: 0.07
Nodes (9): Sketch, constraints, entities, points, texts, Sketch::addCircle(), Sketch::addConic(), Sketch::addEllipticalArc() (+1 more)

### Community 24 - "Sketch.cpp"
Cohesion: 0.08
Nodes (19): SketchError, SplineKind, Conic, Control, Fit, entityTypeName(), isDimension(), Sketch::addConstraint() (+11 more)

### Community 25 - "ViewportSketch.cpp"
Cohesion: 0.09
Nodes (6): faceStyle(), lineStyle(), rgb(), Viewport::lookAt(), Viewport::planePoint(), Viewport::toWidget()

### Community 26 - "SketchPalette"
Cohesion: 0.06
Nodes (26): flatButton(), QCheckBox, QLabel, QToolButton, QWidget, SketchEditor, SketchPalette, body_ (+18 more)

### Community 27 - "Snap"
Cohesion: 0.05
Nodes (35): Hit, index, kind, Kind, Angle, BodyEdge, BodyVertex, Count (+27 more)

### Community 28 - "Inputs"
Cohesion: 0.09
Nodes (22): CommandContext, CommandError, Inputs, CommandSession::CommandSession(), getBool(), getInt(), getReal(), applyOperation() (+14 more)

### Community 29 - "string"
Cohesion: 0.07
Nodes (45): DocumentError, SketchRecord, data, name, offset, plane, checkViewName(), Document::abortTransaction() (+37 more)

### Community 30 - "Colors"
Cohesion: 0.07
Nodes (28): Colors, base, border, cubeBox, cubeText, errorBackground, grid, gridMajor (+20 more)

### Community 31 - "KernelError"
Cohesion: 0.23
Nodes (30): KernelError, asSolid(), boolean(), chamfer(), chamferEx(), deleteFaces(), draft(), extrude() (+22 more)

### Community 32 - "SketchOps.cpp"
Cohesion: 0.25
Nodes (27): at(), chainOf(), chamferCorner(), circularPattern(), copyEntities(), cross(), dot(), extendLine() (+19 more)

### Community 33 - "ViewportArrow.cpp"
Cohesion: 0.05
Nodes (24): MarkingMenu::mouseMoveEvent(), QMouseEvent, ViewInteractor, Viewport::frontEdgeOwner(), rgb(), segmentDistance(), Viewport::arrowAt(), Viewport::arrowMouseMove() (+16 more)

### Community 34 - "ParameterCompleter"
Cohesion: 0.19
Nodes (8): QObject, ParameterCompleter, completer_, edit_, names_, public, QCompleter, QLineEdit

### Community 35 - "Constraint"
Cohesion: 0.08
Nodes (20): Constraint, driven, entities, expression, hasLabel, labelX, labelY, name (+12 more)

### Community 36 - "Joint"
Cohesion: 0.17
Nodes (6): Coil, def_, Joint, def_, Sweep, def_

### Community 38 - "solve"
Cohesion: 0.13
Nodes (14): set, Sketch::removeImpl(), addConstraintChecked(), Layout, n, px, py, rad (+6 more)

### Community 39 - "TsrModule.cpp"
Cohesion: 0.19
Nodes (5): bindTsr(), fromPy(), toPy(), typeName(), Document

### Community 41 - "ConstraintType"
Cohesion: 0.08
Nodes (24): ConstraintType, Angle, Coincident, Collinear, Concentric, Diameter, Distance, Equal (+16 more)

### Community 42 - "AdskModule.cpp"
Cohesion: 0.10
Nodes (16): Application, bindAdsk(), BRepBodies, BRepBody, index, Component, Design, Product (+8 more)

### Community 43 - "Pick"
Cohesion: 0.13
Nodes (14): Pick, bodyArc, bodyPoint, bodySegment, hit, midpointOf, onEntity, onXAxis (+6 more)

### Community 44 - "SketchEditor.cpp"
Cohesion: 0.11
Nodes (5): angleInArc(), ccwContains(), circumcircle(), lineEntity(), segDistance()

### Community 45 - "rect"
Cohesion: 0.28
Nodes (3): SelectionBox, crossing, rect()

### Community 46 - "Zip.cpp"
Cohesion: 0.11
Nodes (14): Entry, data, name, ZipError, crc32(), get16(), get32(), put16() (+6 more)

### Community 47 - "AnalysisSettings"
Cohesion: 0.10
Nodes (16): DragArrow, base, dir, radius, ref, ring, value, PendingLook (+8 more)

### Community 48 - ".rebuild"
Cohesion: 0.12
Nodes (5): hiddenColour(), qc(), rgb(), sharpEdges(), wireColour()

### Community 49 - "ParamSet"
Cohesion: 0.07
Nodes (34): ModelParameter, angle, expression, input, label, name, owner, unit (+26 more)

### Community 50 - "MainWindowSketch.cpp"
Cohesion: 0.05
Nodes (18): MainWindow::updateDragArrow(), MainWindow::cancelSketch(), MainWindow::editSketch(), MainWindow::finishSketch(), MainWindow::onProfileClicked(), MainWindow::originalShape(), MainWindow::sketchPalette(), MainWindow::sketchVisible() (+10 more)

### Community 51 - "InputDef"
Cohesion: 0.08
Nodes (24): InputDef, choices, defaultValue, id, label, max, min, minExclusive (+16 more)

### Community 52 - "sketchFor"
Cohesion: 0.13
Nodes (10): Extrude, def_, Hole, def_, Pipe, def_, Revolve, def_ (+2 more)

### Community 54 - "MainWindowArrow.cpp"
Cohesion: 0.13
Nodes (8): ArrowPlacement, base, dir, edgePlacement(), facesPlacement(), MainWindow::attachArrowCompleters(), MainWindow::patternCentre(), MainWindow::pickedFaces()

### Community 55 - "CommandSession"
Cohesion: 0.12
Nodes (9): CommandSession, inputs_, CommandRegistry::find(), CommandRegistry::run(), OwnedCommand, owned, OwningCommandSession, Session::begin() (+1 more)

### Community 56 - "Theme.cpp"
Cohesion: 0.19
Nodes (6): setIconTheme(), darkColors(), darkPalette(), darkStyleSheet(), lightColors(), lightStyleSheet()

### Community 57 - "QDialog"
Cohesion: 0.18
Nodes (5): QDialog, MainWindow::exportDesign(), MainWindow::measurePick(), MainWindow::openMeasure(), toolWindow()

### Community 58 - "Entity"
Cohesion: 0.08
Nodes (21): Entity, a, b, center, construction, fit, handles, included (+13 more)

### Community 59 - "xdrive.py"
Cohesion: 0.28
Nodes (15): button(), canvas(), click(), drag(), flush(), geometry(), key(), keycode() (+7 more)

### Community 62 - "Session"
Cohesion: 0.08
Nodes (7): PythonHost::PythonHost(), Session, commands_, doc_, listeners_, nextListener_, path_

### Community 63 - "ViewportArrow.cpp"
Cohesion: 0.13
Nodes (5): packed(), ramp(), shade(), Viewport::buildAnalysis(), Viewport::setCurvatureComb()

### Community 64 - "BodyFrame"
Cohesion: 0.11
Nodes (29): boundingBox(), completeEdgeReferences(), completeFaceReferences(), decode(), decodeFaces(), edgeReference(), EdgeSig, full (+21 more)

### Community 65 - "CommandRegistry"
Cohesion: 0.12
Nodes (4): CommandRegistry, cmds_, CommandRegistry::add(), TEST()

### Community 66 - "MainWindow::MainWindow"
Cohesion: 0.14
Nodes (3): PythonHost, MainWindow::MainWindow(), MainWindow::beginSketch()

### Community 67 - "BodyFrame"
Cohesion: 0.14
Nodes (13): BodyFrame, diag, dx, dy, dz, x0, y0, z0 (+5 more)

### Community 68 - "Theme"
Cohesion: 0.20
Nodes (5): MainWindow::showPreferences(), Theme, colors_, public, styled_

### Community 69 - "string"
Cohesion: 0.08
Nodes (20): AddUserParameter, def_, checkBody(), FaceFeature, def_, kind_, isIdentifier(), MoveCopy (+12 more)

### Community 71 - "ParametersDialog.cpp"
Cohesion: 0.10
Nodes (12): number(), ParametersDialog, building_, error_, filter_, listener_, ParametersDialog::ParametersDialog(), public (+4 more)

### Community 72 - "TEST"
Cohesion: 0.09
Nodes (3): param(), TEST(), tmp()

### Community 73 - "ParametersDialog.h"
Cohesion: 0.20
Nodes (4): QLabel, QLineEdit, QTreeWidget, QTreeWidgetItem

### Community 74 - "Column"
Cohesion: 0.25
Nodes (8): Column, kComment, kExpression, kName, kParameter, kStar, kUnit, kValue

### Community 75 - "InputType"
Cohesion: 0.12
Nodes (17): InputType, Axis, Bodies, Body, Bool, Choice, Edges, Faces (+9 more)

### Community 76 - "Vec3"
Cohesion: 0.19
Nodes (19): SurfacePoint, normal, point, Vec3, edgeMidpoint(), edgesNear(), frame(), makeBox() (+11 more)

### Community 77 - "QString"
Cohesion: 0.11
Nodes (6): ExpressionSpinBox, eval_, expression_, shown_, formatNumber(), dimensionOf()

### Community 79 - "Command.cpp"
Cohesion: 0.22
Nodes (11): expressionKey(), checkInputValue(), CommandContext::evaluateExpression(), CommandDef::input(), CommandSession::applyInTransaction(), CommandSession::cancel(), CommandSession::execute(), CommandSession::preview() (+3 more)

### Community 80 - "SketchDisplay"
Cohesion: 0.12
Nodes (11): ProfileObject, index, sketch, SketchDisplay, construction, curves, fixedCurves, frame (+3 more)

### Community 81 - "CommandDef"
Cohesion: 0.05
Nodes (32): Architecture, How a command works, The document, Units, CommandDef, feature, icon, id (+24 more)

### Community 82 - "Measurement"
Cohesion: 0.13
Nodes (14): Kind, Angle, Area, Length, Volume, Measurement, from, hasLine (+6 more)

### Community 83 - "SketchCurves.cpp"
Cohesion: 0.11
Nodes (18): crossings(), crossingsOf(), Curve2d, curve2d(), periodic, t0, t1, endIsFree() (+10 more)

### Community 84 - "MarkingMenu.cpp"
Cohesion: 0.07
Nodes (22): UiCommand, enabled, icon, id, name, panel, run, shortcut (+14 more)

### Community 85 - "Level"
Cohesion: 0.16
Nodes (13): debug(), error(), info(), Level, Debug, Error, Info, Warning (+5 more)

### Community 86 - "README.md"
Cohesion: 0.08
Nodes (20): Build, Conventions, Development, Tests, Include 3D Geometry, Known gaps, Sketch text, Splines and conics (+12 more)

### Community 87 - "string"
Cohesion: 0.07
Nodes (31): ConstructionPlane, name, spec, bodyNumber(), Document::axes(), Document::bodies(), Document::body(), Document::bodyName() (+23 more)

### Community 91 - "EntityType"
Cohesion: 0.29
Nodes (7): EntityType, Arc, Circle, Ellipse, Line, Spline, isRound()

### Community 92 - "FileFormat"
Cohesion: 0.17
Nodes (12): FileFormat, Brep, Iges, Obj, Step, Stl, ThreeMF, FormatInfo (+4 more)

### Community 93 - "Known differences still to build"
Cohesion: 0.15
Nodes (12): Data and files, Findings from the videos, Fusion study list, Interface, Known differences still to build, Navigation and display, Selection and the canvas, Sketch (+4 more)

### Community 94 - "openWallBand"
Cohesion: 0.25
Nodes (9): BoundingBox, max, min, WallSide, Center, Side1, Side2, offsetOpenWire() (+1 more)

### Community 95 - "ReplayStep"
Cohesion: 0.05
Nodes (40): Body, display, name, shape, Component, bodies, name, ConstructionAxis (+32 more)

### Community 97 - "Tool"
Cohesion: 0.16
Nodes (6): SketchEditor::SketchEditor(), edges, Tool, op, shape, target

### Community 98 - "FakeDoc"
Cohesion: 0.17
Nodes (6): FakeDoc, aborts, commits, items, open, snapshot

### Community 101 - "NavPreset"
Cohesion: 0.33
Nodes (4): NavPreset, Fusion, SolidWorks, Tinkercad

### Community 102 - "sstream"
Cohesion: 0.17
Nodes (5): doc_(), Document::Document(), Document::ocafBytes(), ocafApplication(), Document::load()

### Community 103 - "UserParameter"
Cohesion: 0.33
Nodes (6): UserParameter, comment, expression, name, unit, value

### Community 105 - "Joints"
Cohesion: 0.36
Nodes (3): cornerAt(), Joints, parent_

### Community 106 - "SectionState"
Cohesion: 0.25
Nodes (7): SectionState, active, angle, flip, offset, plane, visible

### Community 107 - "Display"
Cohesion: 0.25
Nodes (7): Display, constraints, construction, dimensions, points, profiles, projected

### Community 108 - "main"
Cohesion: 0.36
Nodes (4): listCommands(), main(), usage(), main()

### Community 109 - "PlaneEdges"
Cohesion: 0.13
Nodes (5): PlaneEdges, arcs, curves, segments, vertices

### Community 110 - "openWallBand"
Cohesion: 0.18
Nodes (16): Section, Circular, Square, Triangular, TopologyCounts, edges, faces, shells (+8 more)

### Community 111 - "Profile"
Cohesion: 0.33
Nodes (5): Profile, area, face, x, y

### Community 113 - "Axis"
Cohesion: 0.50
Nodes (4): Axis, X, Y, Z

### Community 114 - "uninstall.sh"
Cohesion: 0.52
Nodes (6): die(), manifest_for(), refresh(), uninstall.sh script, step(), usage()

### Community 115 - "install.sh"
Cohesion: 0.60
Nodes (5): die(), refresh(), install.sh script, step(), usage()

### Community 116 - "TestFramework.h"
Cohesion: 0.14
Nodes (11): Result, error, ok, output, captured(), PythonHost::exec(), PythonHost::runScript(), Case (+3 more)

### Community 118 - "BooleanOp"
Cohesion: 0.50
Nodes (4): BooleanOp, Cut, Intersect, Join

### Community 119 - "ThreadInfo"
Cohesion: 0.50
Nodes (4): ThreadInfo, diameter, internal, pitch

### Community 123 - "Placement"
Cohesion: 0.25
Nodes (7): Placement, angle, cx, cy, dx, dy, scale

### Community 124 - "ChainSegment"
Cohesion: 0.67
Nodes (3): ChainSegment, entity, forward

### Community 125 - "curve"
Cohesion: 0.31
Nodes (10): curve(), curves(), entityCurves(), interiorPoint(), profileAt(), profiles(), splineHandles(), textShape() (+2 more)

### Community 126 - "HandleHit"
Cohesion: 0.40
Nodes (4): HandleHit, back, index, spline

### Community 127 - "smoke"
Cohesion: 0.33
Nodes (6): smoke(), key, MassProperties, area, centerOfMass, volume

### Community 128 - ".mouseMove"
Cohesion: 0.15
Nodes (7): ext(), fixedColor(), freeColor(), qc(), rgb(), wire(), Sketch::addLine()

### Community 129 - "Rect"
Cohesion: 0.50
Nodes (4): Session::notifyChanged(), Rect, l, p

### Community 130 - "ChamferType"
Cohesion: 0.67
Nodes (3): ChamferType, DistanceAngle, TwoDistances

### Community 131 - "DocCommands.cpp"
Cohesion: 0.07
Nodes (29): Adding a tool, Command, axisOf(), bodyCentre(), Combine, def_, differenceOrNull(), DocumentUnits (+21 more)

### Community 134 - "MarkingMenu"
Cohesion: 0.40
Nodes (3): MarkingMenu, enabled, public

### Community 135 - "Dimension"
Cohesion: 0.50
Nodes (4): Dimension, Angle, Length, Unitless

### Community 141 - "Point"
Cohesion: 0.52
Nodes (6): Point, x, y, z, customPlaneSpec(), toDxf()

### Community 142 - "SplineHandle"
Cohesion: 0.29
Nodes (7): SplineHandle, arm, index, tx, ty, x, y

## Knowledge Gaps
- **741 isolated node(s):** `ok`, `output`, `error`, `isReal`, `real` (+736 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 1402 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **28 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `optional` connect `optional` to `Viewport`, `DocCommands.cpp`, `MainWindow`, `Kernel.cpp`, `AnalysisSettings`, `Io.cpp`, `Unit`, `ViewportSketch.cpp`, `string`, `ViewportArrow.cpp`, `Constraint`, `CommandDialog.cpp`, `SketchEditor.cpp`, `AnalysisSettings`, `ParamSet`, `InputDef`, `sketchFor`, `MainWindowArrow.cpp`, `Session`, `Vec3`, `QString`, `SketchCurves.cpp`, `string`, `ReplayStep`, `Joints`, `PlaneEdges`?**
  _High betweenness centrality (0.105) - this node is a cross-community bridge._
- **What connects `ok`, `output`, `error` to the rest of the system?**
  _741 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Viewport` be split into smaller, more focused modules?**
  _Cohesion score 0.01664516129032258 - nodes in this community are weakly interconnected._
- **Why does `Viewport` connect `Viewport` to `MainWindow`, `Viewport.cpp`, `optional`, `AnalysisSettings`, `.openMarkingMenu`, `Unit`, `ViewportArrow.cpp`, `TsrModule.cpp`, `rect`, `AnalysisSettings`, `.rebuild`, `.toPixels`, `ViewportArrow.cpp`, `SketchDisplay`, `SketchCurves.cpp`, `.initializeGL`, `src/main.cpp`, `NavPreset`, `.setSelectionFilter`?**
  _High betweenness centrality (0.101) - this node is a cross-community bridge._
- **Should `Icons.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.05761779777527809 - nodes in this community are weakly interconnected._
- **Why does `MainWindow` connect `MainWindow` to `MainWindow::MainWindow`, `Icons.h`, `.applyPreSelection`, `ParametersDialog.h`, `SectionState`, `optional`, `.openMarkingMenu`, `MainWindowSketch.cpp`, `MainWindowTools.cpp`, `MarkingMenu.cpp`, `Unit`, `MainWindow.cpp`, `QDialog`, `SketchPalette`, `Session`, `smoke`?**
  _High betweenness centrality (0.084) - this node is a cross-community bridge._
- **Should `tsr` be split into smaller, more focused modules?**
  _Cohesion score 0.04522144522144522 - nodes in this community are weakly interconnected._