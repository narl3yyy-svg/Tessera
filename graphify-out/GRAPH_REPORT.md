# Graph Report - tessera  (2026-11-13)

## Corpus Check
- 380 files · ~240,411 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 56 file(s) not represented in the graph (top: .drive 48, (none) 5, .cmake 1)

## Summary
- 3574 nodes · 9059 edges · 136 communities (108 shown, 28 thin omitted)
- Extraction: 85% EXTRACTED · 15% INFERRED · 0% AMBIGUOUS · INFERRED: 1381 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `6bee725f`
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
- AnalysisSettings
- Kind
- .openMarkingMenu
- CommandDialog
- Io.cpp
- Unit
- MainWindowTools.cpp
- fromInternal
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
- QMouseEvent
- ParameterCompleter
- Constraint
- SketchCurves.cpp
- .applyPreSelection
- solve
- Kind
- CommandDialog::CommandDialog
- ConstraintType
- AdskModule.cpp
- Pick
- SketchEditor.cpp
- rect
- Zip.cpp
- AnalysisSettings
- ParametersDialog
- ParamSet
- MainWindowSketch.cpp
- InputDef
- CommandError
- .toPixels
- MainWindowArrow.cpp
- CommandSession
- Theme.cpp
- Feature
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
- QDialog
- test_text_box_path.py
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
- Document.cpp
- test_feature_pattern.py
- .initializeGL
- .add
- EntityType
- FileFormat
- Known differences still to build
- Value.h
- ReplayStep
- Joint
- Icons.h
- FakeDoc
- CommandDialog.cpp
- src/main.cpp
- .redrawAll
- sstream
- cmath
- BodyFrame
- Joints
- SectionState
- Display
- Dimension
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
- test_incremental_replay.py
- Placement
- ChainSegment
- curve
- UserParameter
- .press
- Rect
- ChamferType
- DocCommands.cpp
- Placement::apply
- LAB_NOTES.md
- build.sh
- live-test.sh
- Point
- SplineHandle

## God Nodes (most connected - your core abstractions)
1. `Viewport` - 251 edges
2. `SketchEditor` - 185 edges
3. `MainWindow` - 175 edges
4. `Inputs` - 140 edges
5. `Document` - 118 edges
6. `render()` - 108 edges
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
- `Architecture` --references--> `CommandRegistry`  [INFERRED]
  docs/ARCHITECTURE.md → modules/core/include/tsr/core/CommandRegistry.h

## Import Cycles
- None detected.

## Communities (136 total, 28 thin omitted)

### Community 0 - "Viewport"
Cohesion: 0.02
Nodes (68): view_, QLabel, QLineEdit, Viewport, analysis_, analysisObjects_, appliedGridStep_, arrowBoxes_ (+60 more)

### Community 1 - "Icons.cpp"
Cohesion: 0.06
Nodes (111): arc3Icon(), arcIcon(), arcTangentIcon(), arrow(), axisIcon(), box(), breakIcon(), centerRectIcon() (+103 more)

### Community 2 - "Session.cpp"
Cohesion: 0.18
Nodes (23): historyEdit(), plainEdit(), Session::addNamedView(), Session::deleteFeature(), Session::deleteNamedView(), Session::deleteParameter(), Session::newDocument(), Session::open() (+15 more)

### Community 4 - "MainWindow"
Cohesion: 0.03
Nodes (64): writeLiveGeometry(), CommandDialog, MainWindow, active_, arrowInput_, arrowInput2_, bodiesBeforeCommand_, combEdges_ (+56 more)

### Community 5 - "run_oracle.py"
Cohesion: 0.08
Nodes (54): add_point(), arc_poly(), body_at(), body_list(), build_sketch(), chain(), circumcentre(), cm() (+46 more)

### Community 7 - "Document"
Cohesion: 0.03
Nodes (15): Document, effects_, lastReplayed_, lastReused_, modified_, pendingTools_, registry_, replaying_ (+7 more)

### Community 8 - "Viewport.cpp"
Cohesion: 0.04
Nodes (11): glide(), hiddenColour(), keys(), qc(), QKeyEvent, QtFrameBuffer, rgb(), sharpEdges() (+3 more)

### Community 9 - "SketchEditor"
Cohesion: 0.03
Nodes (54): HandleHit, back, index, spline, SketchEditor, arcDrag_, arcDragMoved_, arcEndsChain_ (+46 more)

### Community 10 - "Document::recompute"
Cohesion: 0.18
Nodes (8): Document::expressionEnv(), Document::recompute(), Document::recordFeature(), Document::removeFeature(), Document::setFeatureInputs(), Document::setFeatureSuppressed(), featureData(), toJson()

### Community 11 - "optional"
Cohesion: 0.11
Nodes (3): optional, CommandRegistry::all(), Document

### Community 13 - "AnalysisSettings"
Cohesion: 0.15
Nodes (13): AnalysisKind, CurvatureMap, Draft, None, Zebra, AnalysisSettings, curvatureScale, draftAngle (+5 more)

### Community 14 - "Kind"
Cohesion: 0.07
Nodes (27): ConstructPlane, def_, kind_, EdgeFeature, def_, kind_, FaceFeature, def_ (+19 more)

### Community 15 - ".openMarkingMenu"
Cohesion: 0.10
Nodes (4): MainWindow::buildSketchTab(), MainWindow::enterSketchMode(), MainWindow::buildUiCommands(), QTimer

### Community 16 - "CommandDialog"
Cohesion: 0.05
Nodes (31): CommandDialog, bodiesId_, bodiesLabel_, bodyInput_, buttons_, cmd_, conditional_, edgesId_ (+23 more)

### Community 17 - "Io.cpp"
Cohesion: 0.10
Nodes (18): NamedShape, compoundOf(), exportShapes(), fmt(), formatForPath(), fromBrep(), importShape(), lower() (+10 more)

### Community 18 - "Unit"
Cohesion: 0.07
Nodes (45): MainWindow::lengthUnit(), ExpressionEnv, lengthUnit, lookup, ExpressionError, Quantity, angle, length (+37 more)

### Community 19 - "MainWindowTools.cpp"
Cohesion: 0.08
Nodes (9): MainWindow::chooseUnits(), MainWindow::insertFile(), MainWindow::print3d(), MainWindow::sectionFrame(), MainWindow::sectionPlane(), MainWindow::setSelectionFilter(), MainWindow::showCenterOfMass(), MainWindow::showParameters() (+1 more)

### Community 20 - "fromInternal"
Cohesion: 0.19
Nodes (11): MainWindow::checkInterference(), MainWindow::driveJoints(), MainWindow::formatLength(), MainWindow::gridSettings(), MainWindow::openSection(), MainWindow::updateMeasure(), qs(), formatQuantity() (+3 more)

### Community 21 - "Document"
Cohesion: 0.22
Nodes (7): ConstructAxisPoint, def_, kind_, jointOrigin(), JointPick, frame, revolveAxis()

### Community 22 - "MainWindow.cpp"
Cohesion: 0.10
Nodes (3): commandIcon(), qs(), MainWindow::applySection()

### Community 23 - "TEST"
Cohesion: 0.07
Nodes (9): Sketch, constraints, entities, points, texts, Sketch::addCircle(), Sketch::addConic(), Sketch::addEllipticalArc() (+1 more)

### Community 24 - "Sketch.cpp"
Cohesion: 0.09
Nodes (18): SketchError, SplineKind, Conic, Control, Fit, entityTypeName(), isDimension(), Sketch::addSpline() (+10 more)

### Community 25 - "ViewportSketch.cpp"
Cohesion: 0.08
Nodes (6): faceStyle(), lineStyle(), rgb(), Viewport::lookAt(), Viewport::planePoint(), Viewport::toWidget()

### Community 26 - "SketchPalette"
Cohesion: 0.07
Nodes (25): QCheckBox, QLabel, QToolButton, QWidget, SketchEditor, SketchPalette, body_, constraints_ (+17 more)

### Community 27 - ".updatePreview"
Cohesion: 0.08
Nodes (26): ext(), fixedColor(), freeColor(), lineEntity(), qc(), rgb(), Snap, alignX (+18 more)

### Community 28 - "Inputs"
Cohesion: 0.06
Nodes (20): CommandContext, Inputs, CommandSession::CommandSession(), AddUserParameter, def_, checkBody(), checkPattern(), defaultBody() (+12 more)

### Community 29 - "string"
Cohesion: 0.10
Nodes (24): DocumentError, checkViewName(), Document::abortTransaction(), Document::addBody(), Document::addNamedView(), Document::addUserParameter(), Document::commitTransaction(), Document::openTransaction() (+16 more)

### Community 30 - "Colors"
Cohesion: 0.07
Nodes (28): Colors, base, border, cubeBox, cubeText, errorBackground, grid, gridMajor (+20 more)

### Community 31 - "KernelError"
Cohesion: 0.18
Nodes (33): KernelError, vertices, asSolid(), boolean(), boundingBox(), chamfer(), chamferEx(), draft() (+25 more)

### Community 32 - "SketchOps.cpp"
Cohesion: 0.24
Nodes (26): at(), chainOf(), chamferCorner(), circularPattern(), copyEntities(), cross(), dot(), extendLine() (+18 more)

### Community 33 - "QMouseEvent"
Cohesion: 0.13
Nodes (9): MarkingMenu::mouseMoveEvent(), MarkingMenu::mouseReleaseEvent(), QMouseEvent, ViewInteractor, Viewport::arrowMouseMove(), Viewport::arrowMousePress(), Viewport::arrowMouseRelease(), Viewport::dragArrowForTest() (+1 more)

### Community 34 - "ParameterCompleter"
Cohesion: 0.14
Nodes (9): QObject, ParameterCompleter, completer_, edit_, names_, ParameterCompleter::ParameterCompleter(), public, QCompleter (+1 more)

### Community 35 - "Constraint"
Cohesion: 0.06
Nodes (30): Constraint, driven, entities, expression, hasLabel, labelX, labelY, name (+22 more)

### Community 36 - "SketchCurves.cpp"
Cohesion: 0.17
Nodes (17): crossings(), crossingsOf(), Curve2d, curve2d(), periodic, t0, t1, endIsFree() (+9 more)

### Community 37 - ".applyPreSelection"
Cohesion: 0.15
Nodes (4): MainWindow::onEdgeClicked(), MainWindow::originalShape(), MainWindow::syncPickedShapes(), MainWindow::toOriginal()

### Community 38 - "solve"
Cohesion: 0.18
Nodes (13): set, addConstraintChecked(), Layout, n, px, py, rad, makeLayout() (+5 more)

### Community 39 - "Kind"
Cohesion: 0.09
Nodes (21): HudField, edit, editing, kind, locked, value, Kind, Angle (+13 more)

### Community 40 - "CommandDialog::CommandDialog"
Cohesion: 0.14
Nodes (5): CommandDialog::CommandDialog(), ExpressionSpinBox, eval_, expression_, shown_

### Community 41 - "ConstraintType"
Cohesion: 0.08
Nodes (24): ConstraintType, Angle, Coincident, Collinear, Concentric, Diameter, Distance, Equal (+16 more)

### Community 42 - "AdskModule.cpp"
Cohesion: 0.10
Nodes (16): Application, bindAdsk(), BRepBodies, BRepBody, index, Component, Design, Product (+8 more)

### Community 43 - "Pick"
Cohesion: 0.11
Nodes (17): Hit, index, kind, Pick, bodyArc, bodyPoint, bodySegment, hit (+9 more)

### Community 45 - "rect"
Cohesion: 0.28
Nodes (3): SelectionBox, crossing, rect()

### Community 46 - "Zip.cpp"
Cohesion: 0.10
Nodes (14): Entry, data, name, ZipError, crc32(), get16(), get32(), put16() (+6 more)

### Community 47 - "AnalysisSettings"
Cohesion: 0.10
Nodes (16): DragArrow, base, dir, radius, ref, ring, value, PendingLook (+8 more)

### Community 48 - "ParametersDialog"
Cohesion: 0.13
Nodes (12): ParametersDialog, building_, error_, filter_, listener_, public, rebuildPending_, tree_ (+4 more)

### Community 49 - "ParamSet"
Cohesion: 0.08
Nodes (28): dimensionOf(), ModelParameter, angle, expression, input, label, name, owner (+20 more)

### Community 50 - "MainWindowSketch.cpp"
Cohesion: 0.06
Nodes (14): MainWindow::cancelSketch(), MainWindow::editSketch(), MainWindow::finishSketch(), MainWindow::onProfileClicked(), MainWindow::sketchPalette(), MainWindow::sketchVisible(), MainWindow::startSketch(), MainWindow::updateProfilePicking() (+6 more)

### Community 51 - "InputDef"
Cohesion: 0.08
Nodes (24): InputDef, choices, defaultValue, id, label, max, min, minExclusive (+16 more)

### Community 52 - "CommandError"
Cohesion: 0.12
Nodes (22): CommandError, getBool(), getInt(), getReal(), applyOperation(), bodyCentre(), bodyName(), CopyFn (+14 more)

### Community 54 - "MainWindowArrow.cpp"
Cohesion: 0.12
Nodes (8): ArrowPlacement, base, dir, edgePlacement(), facesPlacement(), MainWindow::attachArrowCompleters(), MainWindow::patternCentre(), MainWindow::pickedFaces()

### Community 55 - "CommandSession"
Cohesion: 0.12
Nodes (9): CommandSession, inputs_, CommandRegistry::find(), CommandRegistry::run(), OwnedCommand, owned, OwningCommandSession, Session::begin() (+1 more)

### Community 56 - "Theme.cpp"
Cohesion: 0.19
Nodes (6): setIconTheme(), darkColors(), darkPalette(), darkStyleSheet(), lightColors(), lightStyleSheet()

### Community 57 - "Feature"
Cohesion: 0.12
Nodes (16): Feature, commandId, error, id, inputs, name, parameterNames, rolledBack (+8 more)

### Community 58 - "Entity"
Cohesion: 0.10
Nodes (12): Entity, a, b, center, construction, fit, handles, included (+4 more)

### Community 59 - "xdrive.py"
Cohesion: 0.28
Nodes (15): button(), canvas(), click(), drag(), flush(), geometry(), key(), keycode() (+7 more)

### Community 62 - "Session"
Cohesion: 0.04
Nodes (19): listCommands(), main(), usage(), main(), smoke(), key, Session, commands_ (+11 more)

### Community 63 - "ViewportArrow.cpp"
Cohesion: 0.06
Nodes (15): packed(), ramp(), shade(), Viewport::buildAnalysis(), segmentDistance(), Viewport::arrowAt(), Viewport::arrowParam(), Viewport::DragArrow::handle() (+7 more)

### Community 64 - "BodyFrame"
Cohesion: 0.10
Nodes (32): completeEdgeReferences(), completeFaceReferences(), decode(), decodeFaces(), dot(), edgeReference(), EdgeSig, full (+24 more)

### Community 65 - "CommandRegistry"
Cohesion: 0.12
Nodes (4): CommandRegistry, cmds_, CommandRegistry::add(), TEST()

### Community 66 - "MainWindow::MainWindow"
Cohesion: 0.11
Nodes (7): PythonHost, retintIcons(), setIcon(), flatButton(), MainWindow::MainWindow(), MainWindow::beginSketch(), MainWindow::exitSketchMode()

### Community 67 - "openWallBand"
Cohesion: 0.25
Nodes (9): BoundingBox, max, min, WallSide, Center, Side1, Side2, offsetOpenWire() (+1 more)

### Community 68 - "Theme"
Cohesion: 0.20
Nodes (5): MainWindow::showPreferences(), Theme, colors_, public, styled_

### Community 71 - "ParametersDialog.cpp"
Cohesion: 0.12
Nodes (4): number(), ParametersDialog::ParametersDialog(), qs(), withUnit()

### Community 72 - "QDialog"
Cohesion: 0.14
Nodes (6): QDialog, MainWindow::exportDesign(), MainWindow::measurePick(), MainWindow::openAnalysis(), MainWindow::openMeasure(), toolWindow()

### Community 74 - "Column"
Cohesion: 0.25
Nodes (8): Column, kComment, kExpression, kName, kParameter, kStar, kUnit, kValue

### Community 75 - "InputType"
Cohesion: 0.08
Nodes (21): bindTsr(), fromPy(), toPy(), typeName(), InputType, Axis, Bodies, Body (+13 more)

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
Cohesion: 0.04
Nodes (51): Architecture, How a command works, The document, Units, Adding a tool, Command, CommandDef, feature (+43 more)

### Community 82 - "Measurement"
Cohesion: 0.13
Nodes (14): Kind, Angle, Area, Length, Volume, Measurement, from, hasLine (+6 more)

### Community 84 - "MarkingMenu.cpp"
Cohesion: 0.07
Nodes (21): UiCommand, enabled, icon, id, name, panel, run, shortcut (+13 more)

### Community 85 - "Level"
Cohesion: 0.16
Nodes (13): debug(), error(), info(), Level, Debug, Error, Info, Warning (+5 more)

### Community 86 - "README.md"
Cohesion: 0.08
Nodes (20): Build, Conventions, Development, Tests, Include 3D Geometry, Known gaps, Sketch text, Splines and conics (+12 more)

### Community 87 - "Document.cpp"
Cohesion: 0.06
Nodes (45): ConstructionPlane, name, spec, SketchRecord, data, name, offset, plane (+37 more)

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

### Community 96 - "Joint"
Cohesion: 0.27
Nodes (4): Coil, def_, Joint, def_

### Community 98 - "FakeDoc"
Cohesion: 0.17
Nodes (6): FakeDoc, aborts, commits, items, open, snapshot

### Community 100 - "src/main.cpp"
Cohesion: 0.08
Nodes (4): grabWindowWithPanels(), MarkingMenu, enabled, public

### Community 101 - ".redrawAll"
Cohesion: 0.09
Nodes (8): NavPreset, Fusion, SolidWorks, Tinkercad, Viewport::setCurvatureComb(), Viewport::clearDragArrow(), Viewport::clearSecondArrow(), Viewport::setInteractor()

### Community 102 - "sstream"
Cohesion: 0.17
Nodes (5): doc_(), Document::Document(), Document::ocafBytes(), ocafApplication(), Document::load()

### Community 103 - "cmath"
Cohesion: 0.11
Nodes (6): Case, fn, name, fail(), Failure, Register

### Community 104 - "BodyFrame"
Cohesion: 0.14
Nodes (13): BodyFrame, diag, dx, dy, dz, x0, y0, z0 (+5 more)

### Community 105 - "Joints"
Cohesion: 0.36
Nodes (3): cornerAt(), Joints, parent_

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
Cohesion: 0.10
Nodes (7): PlaneEdges, arcs, curves, segments, vertices, SketchEditor::SketchEditor(), edges

### Community 110 - "openWallBand"
Cohesion: 0.18
Nodes (16): Section, Circular, Square, Triangular, TopologyCounts, edges, faces, shells (+8 more)

### Community 111 - "Profile"
Cohesion: 0.40
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
Cohesion: 0.21
Nodes (8): Result, error, ok, output, captured(), PythonHost::exec(), PythonHost::PythonHost(), PythonHost::runScript()

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

### Community 126 - "UserParameter"
Cohesion: 0.33
Nodes (6): UserParameter, comment, expression, name, unit, value

### Community 129 - "Rect"
Cohesion: 0.50
Nodes (4): Session::notifyChanged(), Rect, l, p

### Community 130 - "ChamferType"
Cohesion: 0.67
Nodes (3): ChamferType, DistanceAngle, TwoDistances

### Community 131 - "DocCommands.cpp"
Cohesion: 0.08
Nodes (28): axisOf(), CreateSketch, def_, evaluateDimensions(), HoleSize, modeled, pitch, radius (+20 more)

### Community 141 - "Point"
Cohesion: 0.38
Nodes (6): Point, x, y, z, customPlaneSpec(), planeFrame()

### Community 142 - "SplineHandle"
Cohesion: 0.29
Nodes (7): SplineHandle, arm, index, tx, ty, x, y

## Knowledge Gaps
- **739 isolated node(s):** `ok`, `output`, `error`, `isReal`, `real` (+734 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 1399 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **28 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `Viewport` connect `Viewport` to `QMouseEvent`, `MainWindow`, `.redrawAll`, `src/main.cpp`, `SketchCurves.cpp`, `Viewport.cpp`, `QDialog`, `optional`, `AnalysisSettings`, `rect`, `AnalysisSettings`, `SketchDisplay`, `.openMarkingMenu`, `.toPixels`, `.initializeGL`, `ViewportArrow.cpp`?**
  _High betweenness centrality (0.104) - this node is a cross-community bridge._
- **What connects `ok`, `output`, `error` to the rest of the system?**
  _739 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Viewport` be split into smaller, more focused modules?**
  _Cohesion score 0.015809839690436707 - nodes in this community are weakly interconnected._
- **Why does `SketchEditor` connect `SketchEditor` to `.press`, `Viewport`, `ParameterCompleter`, `QMouseEvent`, `Constraint`, `.solveAndShow`, `Kind`, `Display`, `optional`, `PlaneEdges`, `Pick`, `SketchEditor.cpp`, `Unit`, `Entity`, `.updatePreview`, `Session`?**
  _High betweenness centrality (0.102) - this node is a cross-community bridge._
- **Should `Icons.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.06101928374655648 - nodes in this community are weakly interconnected._
- **Why does `optional` connect `optional` to `.press`, `Viewport`, `DocCommands.cpp`, `MainWindow`, `Kernel.cpp`, `Io.cpp`, `Unit`, `ViewportSketch.cpp`, `Inputs`, `SketchCurves.cpp`, `CommandDialog::CommandDialog`, `SketchEditor.cpp`, `AnalysisSettings`, `ParamSet`, `InputDef`, `MainWindowArrow.cpp`, `Feature`, `Entity`, `Session`, `ViewportArrow.cpp`, `Vec3`, `QString`, `SketchCurves.cpp`, `Document.cpp`, `ReplayStep`, `CommandDialog.cpp`, `Joints`?**
  _High betweenness centrality (0.098) - this node is a cross-community bridge._
- **Should `tsr` be split into smaller, more focused modules?**
  _Cohesion score 0.05323653962492438 - nodes in this community are weakly interconnected._