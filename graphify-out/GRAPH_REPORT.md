# Graph Report - tessera  (2026-11-13)

## Corpus Check
- 379 files · ~239,737 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 56 file(s) not represented in the graph (top: .drive 48, (none) 5, .cmake 1)

## Summary
- 3568 nodes · 9033 edges · 140 communities (113 shown, 27 thin omitted)
- Extraction: 85% EXTRACTED · 15% INFERRED · 0% AMBIGUOUS · INFERRED: 1377 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `4ed0d0c4`
- Run `git rev-parse HEAD` and compare to check if the graph is stale.
- Run `graphify update .` after code changes (no API cost).

## Community Hubs (Navigation)
- Viewport
- Icons.cpp
- Session.cpp
- tsr
- MainWindow
- run_oracle.py
- vector
- Document
- Viewport.cpp
- SketchEditor
- Document::recompute
- optional
- Viewport.h
- Kind
- TEST
- CommandDialog
- Io.cpp
- Parser
- MainWindowTools.cpp
- Unit
- Document
- MainWindow.cpp
- TEST
- Sketch.cpp
- ViewportSketch.cpp
- SketchPalette
- .updatePreview
- Inputs
- string
- Colors
- KernelError
- SketchOps.cpp
- Expression.cpp
- ParameterCompleter
- Constraint
- SketchCurves.cpp
- .openMarkingMenu
- solve
- Kind
- QString
- ConstraintType
- AdskModule.cpp
- Pick
- SketchEditor.cpp
- rect
- Zip.cpp
- AnalysisSettings
- TsrModule.cpp
- ParamSet
- MainWindowSketch.cpp
- InputDef
- string
- .toPixels
- MainWindowArrow.cpp
- CommandSession
- Theme.cpp
- Snap
- Entity
- xdrive.py
- Session
- ViewportArrow.cpp
- BodyFrame
- CommandRegistry
- MainWindow::MainWindow
- openWallBand
- Theme
- PYBIND11_EMBEDDED_MODULE
- ParametersDialog.cpp
- smoke
- test_text_box_path.py
- Column
- InputType
- Vec3
- CommandDialog::CommandDialog
- Command.cpp
- SketchDisplay
- CommandDef
- Measurement
- NavPreset
- MarkingMenu.cpp
- Level
- README.md
- Document.cpp
- test_feature_pattern.py
- ParameterCompleter.cpp
- .add
- EntityType
- FileFormat
- Known differences still to build
- Value.h
- ReplayStep
- Curve2d
- cmath
- FakeDoc
- CommandDialog.cpp
- src/main.cpp
- .rebuild
- sstream
- BodyFrame
- Joints
- SectionState
- Display
- fail
- PlaneEdges
- openWallBand
- Profile
- ViewportAnalysis.cpp
- Axis
- uninstall.sh
- install.sh
- TestFramework.h
- main
- BooleanOp
- ThreadInfo
- MarkingMenu
- test_incremental_replay.py
- Placement
- ChainSegment
- curve
- UserParameter
- MainWindow::setSelectionFilter
- Tool
- Rect
- ChamferType
- DocCommands.cpp
- Placement::apply
- LAB_NOTES.md
- build.sh
- live-test.sh
- Point
- SplineHandle
- cachedProfiles

## God Nodes (most connected - your core abstractions)
1. `Viewport` - 251 edges
2. `SketchEditor` - 185 edges
3. `MainWindow` - 175 edges
4. `Inputs` - 139 edges
5. `Document` - 118 edges
6. `render()` - 108 edges
7. `CommandContext` - 102 edges
8. `CommandDialog` - 90 edges
9. `Command` - 63 edges
10. `CommandDef` - 56 edges

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

## Communities (140 total, 27 thin omitted)

### Community 0 - "Viewport"
Cohesion: 0.02
Nodes (67): view_, QLineEdit, Viewport, analysis_, analysisObjects_, appliedGridStep_, arrowBoxes_, arrowDragging_ (+59 more)

### Community 1 - "Icons.cpp"
Cohesion: 0.06
Nodes (111): arc3Icon(), arcIcon(), arcTangentIcon(), arrow(), axisIcon(), box(), breakIcon(), centerRectIcon() (+103 more)

### Community 2 - "Session.cpp"
Cohesion: 0.17
Nodes (24): historyEdit(), plainEdit(), Session::addListener(), Session::addNamedView(), Session::deleteFeature(), Session::deleteNamedView(), Session::deleteParameter(), Session::newDocument() (+16 more)

### Community 4 - "MainWindow"
Cohesion: 0.03
Nodes (63): CommandDialog, MainWindow, active_, arrowInput_, arrowInput2_, bodiesBeforeCommand_, combEdges_, combPicking_ (+55 more)

### Community 5 - "run_oracle.py"
Cohesion: 0.08
Nodes (54): add_point(), arc_poly(), body_at(), body_list(), build_sketch(), chain(), circumcentre(), cm() (+46 more)

### Community 6 - "vector"
Cohesion: 0.17
Nodes (11): Loft, def_, NewComponent, def_, parsePoints(), pickedFaces(), profilesOf(), SketchProfiles (+3 more)

### Community 7 - "Document"
Cohesion: 0.03
Nodes (16): Document, effects_, lastReplayed_, lastReused_, modified_, pendingTools_, registry_, replaying_ (+8 more)

### Community 8 - "Viewport.cpp"
Cohesion: 0.05
Nodes (4): glide(), keys(), QtFrameBuffer, Viewport::Viewport()

### Community 9 - "SketchEditor"
Cohesion: 0.03
Nodes (50): HandleHit, back, index, spline, SketchEditor, arcDrag_, arcDragMoved_, arcEndsChain_ (+42 more)

### Community 10 - "Document::recompute"
Cohesion: 0.16
Nodes (9): Document::expressionEnv(), Document::openTransaction(), Document::recompute(), Document::recordFeature(), Document::removeFeature(), Document::setFeatureInputs(), Document::setFeatureSuppressed(), featureData() (+1 more)

### Community 11 - "optional"
Cohesion: 0.11
Nodes (3): optional, CommandRegistry::all(), Document

### Community 13 - "Viewport.h"
Cohesion: 0.06
Nodes (19): MarkingMenu::mouseMoveEvent(), MarkingMenu::mouseReleaseEvent(), AnalysisKind, CurvatureMap, Draft, None, Zebra, AnalysisSettings (+11 more)

### Community 14 - "Kind"
Cohesion: 0.08
Nodes (22): ConstructPlane, def_, kind_, EdgeFeature, def_, kind_, Kind, Angle (+14 more)

### Community 15 - "TEST"
Cohesion: 0.09
Nodes (3): param(), TEST(), tmp()

### Community 16 - "CommandDialog"
Cohesion: 0.05
Nodes (31): CommandDialog, bodiesId_, bodiesLabel_, bodyInput_, buttons_, cmd_, conditional_, edgesId_ (+23 more)

### Community 17 - "Io.cpp"
Cohesion: 0.10
Nodes (18): NamedShape, compoundOf(), exportShapes(), fmt(), formatForPath(), fromBrep(), importShape(), lower() (+10 more)

### Community 18 - "Parser"
Cohesion: 0.18
Nodes (15): Quantity, angle, length, value, describe(), isIdentChar(), isIdentStart(), Parser (+7 more)

### Community 19 - "MainWindowTools.cpp"
Cohesion: 0.06
Nodes (24): QDialog, MainWindow::checkInterference(), MainWindow::chooseUnits(), MainWindow::driveJoints(), MainWindow::exportDesign(), MainWindow::formatLength(), MainWindow::gridSettings(), MainWindow::insertFile() (+16 more)

### Community 20 - "Unit"
Cohesion: 0.10
Nodes (21): MainWindow::lengthUnit(), Dimension, Angle, Length, Unitless, Unit, Centimeter, Degree (+13 more)

### Community 21 - "Document"
Cohesion: 0.17
Nodes (13): bodyCentre(), ConstructAxisPoint, def_, kind_, CopyFn, differenceOrNull(), jointOrigin(), JointPick (+5 more)

### Community 22 - "MainWindow.cpp"
Cohesion: 0.09
Nodes (3): commandIcon(), qs(), MainWindow::applySection()

### Community 23 - "TEST"
Cohesion: 0.07
Nodes (9): Sketch, constraints, entities, points, texts, Sketch::addCircle(), Sketch::addConic(), Sketch::addEllipticalArc() (+1 more)

### Community 24 - "Sketch.cpp"
Cohesion: 0.08
Nodes (19): SketchError, SplineKind, Conic, Control, Fit, entityTypeName(), isDimension(), Sketch::addConstraint() (+11 more)

### Community 25 - "ViewportSketch.cpp"
Cohesion: 0.08
Nodes (6): faceStyle(), lineStyle(), rgb(), Viewport::lookAt(), Viewport::planePoint(), Viewport::toWidget()

### Community 26 - "SketchPalette"
Cohesion: 0.05
Nodes (30): retintIcons(), setIcon(), flatButton(), MainWindow::buildSketchTab(), QCheckBox, QLabel, QToolButton, QWidget (+22 more)

### Community 27 - ".updatePreview"
Cohesion: 0.14
Nodes (8): ext(), fixedColor(), freeColor(), lineEntity(), qc(), rgb(), wire(), Sketch::addLine()

### Community 28 - "Inputs"
Cohesion: 0.08
Nodes (20): CommandContext, CommandError, Inputs, CommandSession::CommandSession(), getBool(), getInt(), getReal(), applyOperation() (+12 more)

### Community 29 - "string"
Cohesion: 0.07
Nodes (45): DocumentError, SketchRecord, data, name, offset, plane, checkViewName(), Document::abortTransaction() (+37 more)

### Community 30 - "Colors"
Cohesion: 0.07
Nodes (28): Colors, base, border, cubeBox, cubeText, errorBackground, grid, gridMajor (+20 more)

### Community 31 - "KernelError"
Cohesion: 0.18
Nodes (33): KernelError, vertices, asSolid(), boolean(), boundingBox(), chamfer(), chamferEx(), draft() (+25 more)

### Community 32 - "SketchOps.cpp"
Cohesion: 0.22
Nodes (27): at(), chainOf(), chamferCorner(), circularPattern(), copyEntities(), cornerAt(), cross(), dot() (+19 more)

### Community 33 - "Expression.cpp"
Cohesion: 0.13
Nodes (15): ExpressionEnv, lengthUnit, lookup, ExpressionError, evaluateExpression(), evaluateQuantity(), expressionReferences(), isConstantName() (+7 more)

### Community 34 - "ParameterCompleter"
Cohesion: 0.18
Nodes (8): QObject, ParameterCompleter, completer_, edit_, names_, public, QCompleter, QLineEdit

### Community 35 - "Constraint"
Cohesion: 0.07
Nodes (20): Constraint, driven, entities, expression, hasLabel, labelX, labelY, name (+12 more)

### Community 36 - "SketchCurves.cpp"
Cohesion: 0.13
Nodes (14): crossings(), crossingsOf(), curve2d(), endIsFree(), extendCurve(), finishExtend(), flattened(), includeEdges() (+6 more)

### Community 38 - "solve"
Cohesion: 0.18
Nodes (13): set, addConstraintChecked(), Layout, n, px, py, rad, makeLayout() (+5 more)

### Community 39 - "Kind"
Cohesion: 0.09
Nodes (21): HudField, edit, editing, kind, locked, value, Kind, Angle (+13 more)

### Community 40 - "QString"
Cohesion: 0.13
Nodes (5): ExpressionSpinBox, eval_, expression_, shown_, formatNumber()

### Community 41 - "ConstraintType"
Cohesion: 0.08
Nodes (24): ConstraintType, Angle, Coincident, Collinear, Concentric, Diameter, Distance, Equal (+16 more)

### Community 42 - "AdskModule.cpp"
Cohesion: 0.09
Nodes (16): Application, bindAdsk(), BRepBodies, BRepBody, index, Component, Design, Product (+8 more)

### Community 43 - "Pick"
Cohesion: 0.10
Nodes (17): Hit, index, kind, Pick, bodyArc, bodyPoint, bodySegment, hit (+9 more)

### Community 44 - "SketchEditor.cpp"
Cohesion: 0.11
Nodes (4): angleInArc(), ccwContains(), circumcircle(), segDistance()

### Community 45 - "rect"
Cohesion: 0.14
Nodes (4): SelectionBox, crossing, height, rect()

### Community 46 - "Zip.cpp"
Cohesion: 0.11
Nodes (14): Entry, data, name, ZipError, crc32(), get16(), get32(), put16() (+6 more)

### Community 47 - "AnalysisSettings"
Cohesion: 0.10
Nodes (16): DragArrow, base, dir, radius, ref, ring, value, PendingLook (+8 more)

### Community 48 - "TsrModule.cpp"
Cohesion: 0.25
Nodes (4): bindTsr(), fromPy(), toPy(), typeName()

### Community 49 - "ParamSet"
Cohesion: 0.07
Nodes (34): ModelParameter, angle, expression, input, label, name, owner, unit (+26 more)

### Community 50 - "MainWindowSketch.cpp"
Cohesion: 0.09
Nodes (12): MainWindow::cancelSketch(), MainWindow::editSketch(), MainWindow::finishSketch(), MainWindow::onProfileClicked(), MainWindow::originalShape(), MainWindow::sketchPalette(), MainWindow::sketchVisible(), MainWindow::startSketch() (+4 more)

### Community 51 - "InputDef"
Cohesion: 0.08
Nodes (24): InputDef, choices, defaultValue, id, label, max, min, minExclusive (+16 more)

### Community 52 - "string"
Cohesion: 0.09
Nodes (15): AddUserParameter, def_, Extrude, def_, isIdentifier(), Joint, def_, Pipe (+7 more)

### Community 54 - "MainWindowArrow.cpp"
Cohesion: 0.12
Nodes (8): ArrowPlacement, base, dir, edgePlacement(), facesPlacement(), MainWindow::attachArrowCompleters(), MainWindow::patternCentre(), MainWindow::pickedFaces()

### Community 55 - "CommandSession"
Cohesion: 0.12
Nodes (9): CommandSession, inputs_, CommandRegistry::find(), CommandRegistry::run(), OwnedCommand, owned, OwningCommandSession, Session::begin() (+1 more)

### Community 56 - "Theme.cpp"
Cohesion: 0.19
Nodes (6): setIconTheme(), darkColors(), darkPalette(), darkStyleSheet(), lightColors(), lightStyleSheet()

### Community 57 - "Snap"
Cohesion: 0.11
Nodes (18): Snap, alignX, alignY, bodyArc, bodySegment, entity, fromX, fromY (+10 more)

### Community 58 - "Entity"
Cohesion: 0.07
Nodes (21): Entity, a, b, center, construction, fit, handles, included (+13 more)

### Community 59 - "xdrive.py"
Cohesion: 0.28
Nodes (15): button(), canvas(), click(), drag(), flush(), geometry(), key(), keycode() (+7 more)

### Community 62 - "Session"
Cohesion: 0.08
Nodes (7): PythonHost::PythonHost(), Session, commands_, doc_, listeners_, nextListener_, path_

### Community 63 - "ViewportArrow.cpp"
Cohesion: 0.06
Nodes (21): Viewport::frontEdgeOwner(), rgb(), segmentDistance(), Viewport::arrowAt(), Viewport::arrowMouseMove(), Viewport::arrowMousePress(), Viewport::arrowMouseRelease(), Viewport::arrowParam() (+13 more)

### Community 64 - "BodyFrame"
Cohesion: 0.10
Nodes (32): completeEdgeReferences(), completeFaceReferences(), decode(), decodeFaces(), dot(), edgeReference(), EdgeSig, full (+24 more)

### Community 65 - "CommandRegistry"
Cohesion: 0.10
Nodes (7): CommandRegistry, cmds_, CommandRegistry::add(), EditFeature, def_, featureId_, TEST()

### Community 66 - "MainWindow::MainWindow"
Cohesion: 0.10
Nodes (5): PythonHost, MainWindow::MainWindow(), MainWindow::beginSketch(), MainWindow::enterSketchMode(), MainWindow::exitSketchMode()

### Community 67 - "openWallBand"
Cohesion: 0.25
Nodes (9): BoundingBox, max, min, WallSide, Center, Side1, Side2, offsetOpenWire() (+1 more)

### Community 68 - "Theme"
Cohesion: 0.17
Nodes (5): MainWindow::showPreferences(), Theme, colors_, public, styled_

### Community 71 - "ParametersDialog.cpp"
Cohesion: 0.08
Nodes (16): number(), ParametersDialog, building_, error_, filter_, listener_, ParametersDialog::ParametersDialog(), public (+8 more)

### Community 72 - "smoke"
Cohesion: 0.33
Nodes (6): smoke(), key, MassProperties, area, centerOfMass, volume

### Community 74 - "Column"
Cohesion: 0.25
Nodes (8): Column, kComment, kExpression, kName, kParameter, kStar, kUnit, kValue

### Community 75 - "InputType"
Cohesion: 0.12
Nodes (17): InputType, Axis, Bodies, Body, Bool, Choice, Edges, Faces (+9 more)

### Community 76 - "Vec3"
Cohesion: 0.22
Nodes (17): SurfacePoint, normal, point, Vec3, edgesNear(), frame(), makeBox(), makeCone() (+9 more)

### Community 79 - "Command.cpp"
Cohesion: 0.22
Nodes (11): expressionKey(), checkInputValue(), CommandContext::evaluateExpression(), CommandDef::input(), CommandSession::applyInTransaction(), CommandSession::cancel(), CommandSession::execute(), CommandSession::preview() (+3 more)

### Community 80 - "SketchDisplay"
Cohesion: 0.12
Nodes (11): ProfileObject, index, sketch, SketchDisplay, construction, curves, fixedCurves, frame (+3 more)

### Community 81 - "CommandDef"
Cohesion: 0.05
Nodes (34): Architecture, How a command works, The document, Units, CommandDef, feature, icon, id (+26 more)

### Community 82 - "Measurement"
Cohesion: 0.13
Nodes (14): Kind, Angle, Area, Length, Volume, Measurement, from, hasLine (+6 more)

### Community 83 - "NavPreset"
Cohesion: 0.33
Nodes (4): NavPreset, Fusion, SolidWorks, Tinkercad

### Community 84 - "MarkingMenu.cpp"
Cohesion: 0.09
Nodes (15): run, MarkingMenu::keyPressEvent(), MarkingMenu::MarkingMenu(), MarkingMenu::paintEvent(), MarkingMenu::popupAt(), MarkingMenu::ringIndexAt(), MarkingMenu::run(), MarkingMenu::triggerForTest() (+7 more)

### Community 85 - "Level"
Cohesion: 0.16
Nodes (13): debug(), error(), info(), Level, Debug, Error, Info, Warning (+5 more)

### Community 86 - "README.md"
Cohesion: 0.08
Nodes (20): Build, Conventions, Development, Tests, Include 3D Geometry, Known gaps, Sketch text, Splines and conics (+12 more)

### Community 87 - "Document.cpp"
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

### Community 95 - "ReplayStep"
Cohesion: 0.05
Nodes (40): Body, display, name, shape, Component, bodies, name, ConstructionAxis (+32 more)

### Community 96 - "Curve2d"
Cohesion: 0.40
Nodes (4): Curve2d, periodic, t0, t1

### Community 97 - "cmath"
Cohesion: 0.18
Nodes (9): UiCommand, enabled, icon, id, name, panel, shortcut, tab (+1 more)

### Community 98 - "FakeDoc"
Cohesion: 0.17
Nodes (6): FakeDoc, aborts, commits, items, open, snapshot

### Community 100 - "src/main.cpp"
Cohesion: 0.10
Nodes (4): QAbstractButton, QAction, grabWindowWithPanels(), writeLiveGeometry()

### Community 101 - ".rebuild"
Cohesion: 0.09
Nodes (5): hiddenColour(), qc(), rgb(), sharpEdges(), wireColour()

### Community 102 - "sstream"
Cohesion: 0.17
Nodes (5): doc_(), Document::Document(), Document::ocafBytes(), ocafApplication(), Document::load()

### Community 104 - "BodyFrame"
Cohesion: 0.14
Nodes (13): BodyFrame, diag, dx, dy, dz, x0, y0, z0 (+5 more)

### Community 106 - "SectionState"
Cohesion: 0.25
Nodes (7): SectionState, active, angle, flip, offset, plane, visible

### Community 107 - "Display"
Cohesion: 0.25
Nodes (7): Display, constraints, construction, dimensions, points, profiles, projected

### Community 109 - "PlaneEdges"
Cohesion: 0.13
Nodes (6): PlaneEdges, arcs, curves, segments, vertices, edges

### Community 110 - "openWallBand"
Cohesion: 0.18
Nodes (16): Section, Circular, Square, Triangular, TopologyCounts, edges, faces, shells (+8 more)

### Community 111 - "Profile"
Cohesion: 0.33
Nodes (5): Profile, area, face, x, y

### Community 112 - "ViewportAnalysis.cpp"
Cohesion: 0.13
Nodes (5): packed(), ramp(), shade(), Viewport::buildAnalysis(), Viewport::setCurvatureComb()

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
Cohesion: 0.15
Nodes (11): Result, error, ok, output, captured(), PythonHost::exec(), PythonHost::runScript(), Case (+3 more)

### Community 117 - "main"
Cohesion: 0.36
Nodes (4): listCommands(), main(), usage(), main()

### Community 118 - "BooleanOp"
Cohesion: 0.50
Nodes (4): BooleanOp, Cut, Intersect, Join

### Community 119 - "ThreadInfo"
Cohesion: 0.50
Nodes (4): ThreadInfo, diameter, internal, pitch

### Community 121 - "MarkingMenu"
Cohesion: 0.40
Nodes (3): MarkingMenu, enabled, public

### Community 123 - "Placement"
Cohesion: 0.25
Nodes (7): Placement, angle, cx, cy, dx, dy, scale

### Community 124 - "ChainSegment"
Cohesion: 0.67
Nodes (3): ChainSegment, entity, forward

### Community 125 - "curve"
Cohesion: 0.31
Nodes (10): curve(), curves(), entityCurves(), interiorPoint(), profileAt(), profiles(), splineHandles(), textShape() (+2 more)

### Community 126 - "UserParameter"
Cohesion: 0.33
Nodes (6): UserParameter, comment, expression, name, unit, value

### Community 128 - "Tool"
Cohesion: 0.19
Nodes (5): SketchEditor::SketchEditor(), Tool, op, shape, target

### Community 129 - "Rect"
Cohesion: 0.50
Nodes (4): Session::notifyChanged(), Rect, l, p

### Community 130 - "ChamferType"
Cohesion: 0.67
Nodes (3): ChamferType, DistanceAngle, TwoDistances

### Community 131 - "DocCommands.cpp"
Cohesion: 0.06
Nodes (39): Adding a tool, Command, axisOf(), checkPattern(), CircularPattern, def_, Coil, def_ (+31 more)

### Community 141 - "Point"
Cohesion: 0.38
Nodes (6): Point, x, y, z, customPlaneSpec(), planeFrame()

### Community 142 - "SplineHandle"
Cohesion: 0.29
Nodes (7): SplineHandle, arm, index, tx, ty, x, y

### Community 144 - "cachedProfiles"
Cohesion: 0.22
Nodes (3): MainWindow::updateDragArrow(), cachedProfiles(), keyOf()

## Knowledge Gaps
- **737 isolated node(s):** `ok`, `output`, `error`, `isReal`, `real` (+732 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 1396 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **27 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `Viewport` connect `Viewport` to `MainWindow`, `.rebuild`, `SketchCurves.cpp`, `Viewport.cpp`, `optional`, `Viewport.h`, `rect`, `AnalysisSettings`, `SketchDisplay`, `ViewportAnalysis.cpp`, `NavPreset`, `MainWindowTools.cpp`, `.toPixels`, `SketchPalette`, `ViewportArrow.cpp`?**
  _High betweenness centrality (0.104) - this node is a cross-community bridge._
- **What connects `ok`, `output`, `error` to the rest of the system?**
  _737 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Viewport` be split into smaller, more focused modules?**
  _Cohesion score 0.01664516129032258 - nodes in this community are weakly interconnected._
- **Why does `SketchEditor` connect `SketchEditor` to `Tool`, `Viewport`, `ParameterCompleter`, `Constraint`, `Kind`, `Display`, `optional`, `PlaneEdges`, `Pick`, `SketchEditor.cpp`, `Viewport.h`, `Unit`, `Snap`, `Entity`, `.updatePreview`, `Session`?**
  _High betweenness centrality (0.103) - this node is a cross-community bridge._
- **Should `Icons.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.06101928374655648 - nodes in this community are weakly interconnected._
- **Why does `optional` connect `optional` to `Viewport`, `DocCommands.cpp`, `MainWindow`, `Kernel.cpp`, `Viewport.h`, `Io.cpp`, `Parser`, `Unit`, `ViewportSketch.cpp`, `.updatePreview`, `string`, `SketchOps.cpp`, `Expression.cpp`, `SketchCurves.cpp`, `QString`, `SketchEditor.cpp`, `AnalysisSettings`, `ParamSet`, `InputDef`, `string`, `MainWindowArrow.cpp`, `Entity`, `Session`, `ViewportArrow.cpp`, `Vec3`, `Document.cpp`, `ReplayStep`, `CommandDialog.cpp`?**
  _High betweenness centrality (0.096) - this node is a cross-community bridge._
- **Should `tsr` be split into smaller, more focused modules?**
  _Cohesion score 0.05519480519480519 - nodes in this community are weakly interconnected._