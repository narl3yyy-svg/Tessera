# Graph Report - tessera  (2026-11-17)

## Corpus Check
- 435 files · ~285,736 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 76 file(s) not represented in the graph (top: .drive 68, (none) 5, .cmake 1)

## Summary
- 4013 nodes · 10319 edges · 144 communities (119 shown, 25 thin omitted)
- Extraction: 85% EXTRACTED · 15% INFERRED · 0% AMBIGUOUS · INFERRED: 1573 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `e81a00b2`
- Run `git rev-parse HEAD` and compare to check if the graph is stale.
- Run `graphify update .` after code changes (no API cost).

## Community Hubs (Navigation)
- Viewport
- Icons.cpp
- Session.cpp
- MainWindow
- run_oracle.py
- CommandError
- Document
- Viewport.cpp
- SketchEditor
- DocumentError
- optional
- Kernel.cpp
- Viewport.h
- Kind
- Viewport::setDragArrow
- CommandDialog
- Io.cpp
- Parser
- nameOf
- SketchEditor.cpp
- Document
- TEST
- Affine
- ViewportSketch.cpp
- SketchPalette
- DocCommands.cpp
- Inputs
- Command
- Colors
- KernelError
- SketchOps.cpp
- .rebuild
- ParameterCompleter
- Constraint
- src/main.cpp
- solve
- ParametersDialog
- curve
- ConstraintType
- AdskModule.cpp
- Pick
- TopologyCounts
- Zip.cpp
- AnalysisSettings
- Sketch
- Document.cpp
- test_extrude_participants.py
- NewComponent
- .press2d
- .toPixels
- Snap
- Document::recompute
- MainWindow.cpp
- QMouseEvent
- Expression.cpp
- xdrive.py
- adsk_core
- CommandDialog.cpp
- Session
- Theme.cpp
- BodyFrame
- CommandRegistry
- Command.cpp
- Unit
- Theme
- Feature
- InputType
- ParametersDialog.cpp
- MainWindowSketch.cpp
- ViewportArrow.cpp
- CommandSession
- Constraint
- Vec3
- BoundaryCell
- math
- CommandDialog::CommandDialog
- SketchDisplay
- Kind
- Measurement
- SketchCurves.cpp
- TEST
- Level
- .apply
- UiCommand
- test_feature_pattern.py
- CommandRegistry::run
- QDialog
- TEST
- FileFormat
- Known differences still to build
- QTimer
- ReplayStep
- cli_main.cpp
- MainWindowArrow.cpp
- FakeDoc
- ParamSet
- BoundingBox
- fail
- Document::load
- toDxf
- Placement
- test_rigid_group.py
- Entity
- bindTsr
- Display
- Axis
- Known gaps
- .redrawAll
- SectionState
- uninstall.sh
- install.sh
- TestFramework.h
- .primary
- UserParameter
- Profile
- SelectionBox
- test_incremental_replay.py
- BooleanOp
- MassProperties
- QScrollArea
- ThreadInfo
- Value.h
- ChamferType
- Joint
- Column
- MarkingMenu
- LAB_NOTES.md
- HoleSize
- Rect
- build.sh
- live-test.sh
- ChainSegment
- SplineHandle
- BodyFrame
- EntityType

## God Nodes (most connected - your core abstractions)
1. `Viewport` - 286 edges
2. `SketchEditor` - 198 edges
3. `MainWindow` - 189 edges
4. `Inputs` - 167 edges
5. `render()` - 126 edges
6. `CommandContext` - 122 edges
7. `Document` - 122 edges
8. `CommandDialog` - 101 edges
9. `CommandError` - 73 edges
10. `Command` - 70 edges

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

## Communities (144 total, 25 thin omitted)

### Community 0 - "Viewport"
Cohesion: 0.01
Nodes (78): view_, Viewport, analysis_, analysisObjects_, appliedGridStep_, arrowBoxes_, arrowDragging_, arrowGrab_ (+70 more)

### Community 1 - "Icons.cpp"
Cohesion: 0.05
Nodes (131): accessibilityIcon(), alignIcon(), appearanceIcon(), arc3Icon(), arcIcon(), arcTangentIcon(), arrow(), axisIcon() (+123 more)

### Community 2 - "Session.cpp"
Cohesion: 0.16
Nodes (27): historyEdit(), plainEdit(), Session::addListener(), Session::addNamedView(), Session::computeAll(), Session::deleteFeature(), Session::deleteNamedView(), Session::deleteParameter() (+19 more)

### Community 4 - "MainWindow"
Cohesion: 0.03
Nodes (67): CommandDialog, MainWindow, active_, appearanceColour_, appearanceFaces_, appearancePanel_, arrowInput_, arrowInput2_ (+59 more)

### Community 5 - "run_oracle.py"
Cohesion: 0.08
Nodes (54): add_point(), arc_poly(), body_at(), body_list(), build_sketch(), chain(), circumcentre(), cm() (+46 more)

### Community 6 - "CommandError"
Cohesion: 0.12
Nodes (16): CommandError, getBool(), getReal(), Align::apply(), applyOperation(), bodyCentre(), bodyName(), defaultBody() (+8 more)

### Community 7 - "Document"
Cohesion: 0.03
Nodes (15): Document, effects_, lastReplayed_, lastReused_, modified_, pendingTools_, registry_, replaying_ (+7 more)

### Community 8 - "Viewport.cpp"
Cohesion: 0.05
Nodes (4): glide(), QKeyEvent, QtFrameBuffer, Viewport::frontEdgeOwner()

### Community 9 - "SketchEditor"
Cohesion: 0.03
Nodes (62): HandleHit, back, index, spline, PlaneEdges, arcs, curves, segments (+54 more)

### Community 10 - "DocumentError"
Cohesion: 0.08
Nodes (38): DocumentError, checkViewName(), Document::abortTransaction(), Document::addBody(), Document::addNamedView(), Document::addUserParameter(), Document::axisFrame(), Document::commitTransaction() (+30 more)

### Community 12 - "Kernel.cpp"
Cohesion: 0.03
Nodes (7): dot(), faceScore(), isoCoarsePitch(), score(), topologyCounts(), touching(), vec()

### Community 13 - "Viewport.h"
Cohesion: 0.06
Nodes (20): AnalysisKind, Accessibility, CurvatureMap, Draft, Isocurve, MinimumRadius, None, Zebra (+12 more)

### Community 14 - "Kind"
Cohesion: 0.07
Nodes (29): EdgeFeature, def_, kind_, FaceFeature, def_, kind_, Kind, Angle (+21 more)

### Community 15 - "Viewport::setDragArrow"
Cohesion: 0.18
Nodes (4): Viewport::DragArrow::handle(), Viewport::emitArrow(), Viewport::setDragArrow(), Viewport::setDragRing()

### Community 16 - "CommandDialog"
Cohesion: 0.04
Nodes (39): CommandDialog, bodiesId_, bodiesLabel_, bodyInput_, buttons_, cellsId_, cellsList_, cmd_ (+31 more)

### Community 17 - "Io.cpp"
Cohesion: 0.09
Nodes (19): MainWindow::print3d(), NamedShape, compoundOf(), exportShapes(), fmt(), formatForPath(), fromBrep(), importShape() (+11 more)

### Community 18 - "Parser"
Cohesion: 0.23
Nodes (12): Quantity, angle, length, value, describe(), Parser, ang_, env_ (+4 more)

### Community 19 - "nameOf"
Cohesion: 0.12
Nodes (21): ConstructionPlane, name, spec, SketchRecord, data, name, offset, plane (+13 more)

### Community 21 - "Document"
Cohesion: 0.15
Nodes (10): ConstructAxisPoint, def_, kind_, ConstructPlane, def_, kind_, JointPick, frame (+2 more)

### Community 22 - "TEST"
Cohesion: 0.07
Nodes (10): Sketch, constraints, entities, points, texts, Sketch::addCircle(), Sketch::addConic(), Sketch::addEllipticalArc() (+2 more)

### Community 24 - "Affine"
Cohesion: 0.14
Nodes (13): Affine, a, b, d, e, Builder, byPlace_, k_ (+5 more)

### Community 25 - "ViewportSketch.cpp"
Cohesion: 0.07
Nodes (6): faceStyle(), lineStyle(), rgb(), Viewport::lookAt(), Viewport::planePoint(), Viewport::toWidget()

### Community 26 - "SketchPalette"
Cohesion: 0.06
Nodes (25): QCheckBox, QLabel, QToolButton, QWidget, SketchEditor, SketchPalette, body_, constraints_ (+17 more)

### Community 27 - "DocCommands.cpp"
Cohesion: 0.11
Nodes (32): applyToParticipants(), axisOf(), boundaryFillCells(), CopyFn, differenceOrNull(), evaluateDimensions(), facesTool(), Loft (+24 more)

### Community 28 - "Inputs"
Cohesion: 0.07
Nodes (18): CommandContext, Inputs, CommandSession::CommandSession(), checkBody(), checkPattern(), Hole, def_, holeSize() (+10 more)

### Community 29 - "Command"
Cohesion: 0.03
Nodes (83): Adding a tool, Command, CommandDef, feature, icon, id, inputs, name (+75 more)

### Community 30 - "Colors"
Cohesion: 0.07
Nodes (28): Colors, base, border, cubeBox, cubeText, errorBackground, grid, gridMajor (+20 more)

### Community 31 - "KernelError"
Cohesion: 0.21
Nodes (38): KernelError, asSolid(), boolean(), boundaryCells(), chamfer(), chamferEx(), deleteFaces(), draft() (+30 more)

### Community 32 - "SketchOps.cpp"
Cohesion: 0.17
Nodes (28): at(), chainOf(), chamferCorner(), circularPattern(), copyEntities(), cornerAt(), cross(), dot() (+20 more)

### Community 33 - ".rebuild"
Cohesion: 0.10
Nodes (12): hiddenColour(), qc(), rgb(), sharpEdges(), Style, Shaded, ShadedEdges, ShadedHidden (+4 more)

### Community 34 - "ParameterCompleter"
Cohesion: 0.12
Nodes (8): ParameterCompleter, completer_, edit_, names_, ParameterCompleter::ParameterCompleter(), public, QCompleter, QLineEdit

### Community 35 - "Constraint"
Cohesion: 0.09
Nodes (20): Constraint, driven, entities, expression, hasLabel, labelX, labelY, name (+12 more)

### Community 37 - "src/main.cpp"
Cohesion: 0.09
Nodes (4): QAbstractButton, QAction, grabWindowWithPanels(), writeLiveGeometry()

### Community 38 - "solve"
Cohesion: 0.11
Nodes (14): addConstraintChecked(), Layout, n, px, py, rad, makeLayout(), pack() (+6 more)

### Community 39 - "ParametersDialog"
Cohesion: 0.12
Nodes (12): ParametersDialog, building_, error_, filter_, listener_, public, rebuildPending_, tree_ (+4 more)

### Community 40 - "curve"
Cohesion: 0.16
Nodes (19): conditionedSpline(), curve(), curves(), entityCurves(), G2End, d1, d2, set (+11 more)

### Community 41 - "ConstraintType"
Cohesion: 0.07
Nodes (27): ConstraintType, Angle, Coincident, Collinear, Concentric, Curvature, Diameter, Distance (+19 more)

### Community 42 - "AdskModule.cpp"
Cohesion: 0.09
Nodes (16): Application, bindAdsk(), BRepBodies, BRepBody, index, Component, Design, Product (+8 more)

### Community 43 - "Pick"
Cohesion: 0.10
Nodes (16): QObject, Pick, bodyArc, bodyPoint, bodySegment, hit, midpointOf, onEntity (+8 more)

### Community 45 - "TopologyCounts"
Cohesion: 0.16
Nodes (17): Section, Circular, Square, Triangular, TopologyCounts, edges, faces, shells (+9 more)

### Community 46 - "Zip.cpp"
Cohesion: 0.19
Nodes (13): Entry, data, name, ZipError, crc32(), deflateRaw(), get16(), get32() (+5 more)

### Community 47 - "AnalysisSettings"
Cohesion: 0.08
Nodes (20): DragArrow, base, dir, radius, ref, ring, value, PendingLook (+12 more)

### Community 48 - "Sketch"
Cohesion: 0.08
Nodes (19): SketchError, SplineKind, Conic, Control, Fit, entityTypeName(), isDimension(), Sketch::addConstraint() (+11 more)

### Community 49 - "Document.cpp"
Cohesion: 0.08
Nodes (22): bodyNumber(), Document::bodies(), Document::body(), Document::bodyName(), Document::bodyShapes(), Document::component(), Document::components(), Document::effectOf() (+14 more)

### Community 51 - "NewComponent"
Cohesion: 0.24
Nodes (4): NewComponent, def_, RigidGroup, def_

### Community 52 - ".press2d"
Cohesion: 0.13
Nodes (5): ccwContains(), circumcircle(), x, y, segDistance()

### Community 54 - "Snap"
Cohesion: 0.11
Nodes (18): Snap, alignX, alignY, bodyArc, bodySegment, entity, fromX, fromY (+10 more)

### Community 55 - "Document::recompute"
Cohesion: 0.17
Nodes (8): Document::expressionEnv(), Document::recompute(), Document::recordFeature(), Document::removeFeature(), Document::setFeatureInputs(), Document::setFeatureSuppressed(), featureData(), toJson()

### Community 56 - "MainWindow.cpp"
Cohesion: 0.04
Nodes (13): PythonHost, commandIcon(), flatButton(), MainWindow::MainWindow(), qs(), run, MainWindow::beginSketch(), MainWindow::buildSketchTab() (+5 more)

### Community 57 - "QMouseEvent"
Cohesion: 0.15
Nodes (7): QMouseEvent, ViewInteractor, Viewport::arrowMouseMove(), Viewport::arrowMousePress(), Viewport::arrowMouseRelease(), Viewport::dragArrowForTest(), Viewport::rebuildArrows()

### Community 58 - "Expression.cpp"
Cohesion: 0.22
Nodes (12): ExpressionEnv, lengthUnit, lookup, ExpressionError, evaluateExpression(), evaluateQuantity(), expressionReferences(), isConstantName() (+4 more)

### Community 59 - "xdrive.py"
Cohesion: 0.28
Nodes (15): button(), canvas(), click(), drag(), flush(), geometry(), key(), keycode() (+7 more)

### Community 62 - "Session"
Cohesion: 0.04
Nodes (12): main(), smoke(), key, Session, commands_, doc_, listeners_, nextListener_ (+4 more)

### Community 63 - "Theme.cpp"
Cohesion: 0.21
Nodes (6): setIconTheme(), darkColors(), darkPalette(), darkStyleSheet(), lightColors(), lightStyleSheet()

### Community 64 - "BodyFrame"
Cohesion: 0.13
Nodes (23): boundingBox(), completeEdgeReferences(), completeFaceReferences(), decode(), decodeFaces(), edgeReference(), EdgeSig, full (+15 more)

### Community 65 - "CommandRegistry"
Cohesion: 0.11
Nodes (7): Architecture, How a command works, The document, Units, CommandRegistry, cmds_, TEST()

### Community 66 - "Command.cpp"
Cohesion: 0.22
Nodes (11): expressionKey(), checkInputValue(), CommandContext::evaluateExpression(), CommandDef::input(), CommandSession::applyInTransaction(), CommandSession::cancel(), CommandSession::execute(), CommandSession::preview() (+3 more)

### Community 67 - "Unit"
Cohesion: 0.13
Nodes (21): MainWindow::lengthUnit(), Dimension, Angle, Length, Unitless, Unit, Centimeter, Degree (+13 more)

### Community 68 - "Theme"
Cohesion: 0.22
Nodes (4): Theme, colors_, public, styled_

### Community 69 - "Feature"
Cohesion: 0.10
Nodes (19): optional, ConstructionPoint, name, point, Feature, commandId, error, id (+11 more)

### Community 70 - "InputType"
Cohesion: 0.12
Nodes (17): InputType, Axis, Bodies, Body, Bool, Choice, Edges, Faces (+9 more)

### Community 71 - "ParametersDialog.cpp"
Cohesion: 0.18
Nodes (4): number(), ParametersDialog::ParametersDialog(), qs(), withUnit()

### Community 72 - "MainWindowSketch.cpp"
Cohesion: 0.04
Nodes (29): MainWindow::cancelSketch(), MainWindow::editSketch(), MainWindow::finishSketch(), MainWindow::onProfileClicked(), MainWindow::originalShape(), MainWindow::sketchPalette(), MainWindow::sketchVisible(), MainWindow::startSketch() (+21 more)

### Community 73 - "ViewportArrow.cpp"
Cohesion: 0.05
Nodes (29): packed(), ramp(), shade(), Viewport::buildAnalysis(), Viewport::setCurvatureComb(), rgb(), segmentDistance(), Viewport::arrowAt() (+21 more)

### Community 74 - "CommandSession"
Cohesion: 0.16
Nodes (7): CommandSession, inputs_, OwnedCommand, owned, OwningCommandSession, Session::begin(), Session::editFeature()

### Community 75 - "Constraint"
Cohesion: 0.09
Nodes (8): ext(), fixedColor(), freeColor(), lineEntity(), qc(), rgb(), wire(), Sketch::addLine()

### Community 76 - "Vec3"
Cohesion: 0.20
Nodes (20): SurfacePoint, normal, point, Vec3, containsPoint(), edgeMidpoint(), edgesNear(), frame() (+12 more)

### Community 77 - "BoundaryCell"
Cohesion: 0.29
Nodes (4): BoundaryCell, ref, shape, volume

### Community 78 - "math"
Cohesion: 0.05
Nodes (3): dist(), check_regular(), dist_to_line()

### Community 79 - "CommandDialog::CommandDialog"
Cohesion: 0.11
Nodes (6): CommandDialog::CommandDialog(), ExpressionSpinBox, eval_, expression_, shown_, formatNumber()

### Community 80 - "SketchDisplay"
Cohesion: 0.12
Nodes (11): ProfileObject, index, sketch, SketchDisplay, construction, curves, fixedCurves, frame (+3 more)

### Community 81 - "Kind"
Cohesion: 0.08
Nodes (24): Hit, index, kind, HudField, edit, editing, kind, locked (+16 more)

### Community 82 - "Measurement"
Cohesion: 0.12
Nodes (15): Kind, Angle, Area, Length, Volume, Measurement, from, hasLine (+7 more)

### Community 83 - "SketchCurves.cpp"
Cohesion: 0.13
Nodes (19): crossings(), crossingsOf(), Curve2d, curve2d(), periodic, t0, t1, endIsFree() (+11 more)

### Community 84 - "TEST"
Cohesion: 0.18
Nodes (3): slurp(), TEST(), tmp()

### Community 85 - "Level"
Cohesion: 0.16
Nodes (13): debug(), error(), info(), Level, Debug, Error, Info, Warning (+5 more)

### Community 86 - ".apply"
Cohesion: 0.18
Nodes (7): getInt(), CircularPattern, def_, PathPattern, def_, RectangularPattern, def_

### Community 87 - "UiCommand"
Cohesion: 0.18
Nodes (9): UiCommand, enabled, icon, id, name, panel, shortcut, tab (+1 more)

### Community 89 - "CommandRegistry::run"
Cohesion: 0.22
Nodes (4): CommandRegistry::add(), CommandRegistry::all(), CommandRegistry::find(), CommandRegistry::run()

### Community 90 - "QDialog"
Cohesion: 0.05
Nodes (31): QDialog, MainWindow::applySection(), MainWindow::checkInterference(), MainWindow::chooseUnits(), MainWindow::driveJoints(), MainWindow::editAppearance(), MainWindow::editMaterial(), MainWindow::exportDesign() (+23 more)

### Community 91 - "TEST"
Cohesion: 0.27
Nodes (3): env(), mm(), TEST()

### Community 92 - "FileFormat"
Cohesion: 0.17
Nodes (12): FileFormat, Brep, Iges, Obj, Step, Stl, ThreeMF, FormatInfo (+4 more)

### Community 93 - "Known differences still to build"
Cohesion: 0.15
Nodes (12): Data and files, Findings from the videos, Fusion study list, Interface, Known differences still to build, Navigation and display, Selection and the canvas, Sketch (+4 more)

### Community 94 - "QTimer"
Cohesion: 0.15
Nodes (3): QTimer, Viewport::rebuildArrow(), Viewport::selectArrowValue()

### Community 95 - "ReplayStep"
Cohesion: 0.06
Nodes (35): Body, color, display, faceColors, material, name, shape, Component (+27 more)

### Community 96 - "cli_main.cpp"
Cohesion: 0.28
Nodes (3): listCommands(), main(), usage()

### Community 97 - "MainWindowArrow.cpp"
Cohesion: 0.11
Nodes (9): ArrowPlacement, base, dir, edgePlacement(), facesPlacement(), MainWindow::attachArrowCompleters(), MainWindow::patternCentre(), MainWindow::pickedFaces() (+1 more)

### Community 98 - "FakeDoc"
Cohesion: 0.17
Nodes (6): FakeDoc, aborts, commits, items, open, snapshot

### Community 99 - "ParamSet"
Cohesion: 0.08
Nodes (30): ModelParameter, angle, expression, input, label, name, owner, unit (+22 more)

### Community 100 - "BoundingBox"
Cohesion: 0.23
Nodes (14): BoundingBox, max, min, WallSide, Center, Side1, Side2, extendedWire() (+6 more)

### Community 102 - "Document::load"
Cohesion: 0.12
Nodes (6): doc_(), Document::Document(), Document::ocafBytes(), ocafApplication(), Document::load(), Document::save()

### Community 103 - "toDxf"
Cohesion: 0.43
Nodes (7): Point, x, y, z, customPlaneSpec(), planeFrame(), toDxf()

### Community 104 - "Placement"
Cohesion: 0.25
Nodes (7): Placement, angle, cx, cy, dx, dy, scale

### Community 106 - "Entity"
Cohesion: 0.08
Nodes (21): Entity, a, b, center, construction, fit, handles, included (+13 more)

### Community 107 - "bindTsr"
Cohesion: 0.29
Nodes (4): bindTsr(), fromPy(), toPy(), typeName()

### Community 108 - "Display"
Cohesion: 0.25
Nodes (7): Display, constraints, construction, dimensions, points, profiles, projected

### Community 110 - "Axis"
Cohesion: 0.50
Nodes (4): Axis, X, Y, Z

### Community 111 - "Known gaps"
Cohesion: 0.05
Nodes (33): Build, Conventions, Development, Tests, 3D Sketch, Align, Appearance, Boundary Fill (+25 more)

### Community 112 - ".redrawAll"
Cohesion: 0.11
Nodes (10): keys(), NavPreset, Fusion, SolidWorks, Tinkercad, Viewport::Viewport(), Viewport::clearDragArrow(), Viewport::clearSecondArrow() (+2 more)

### Community 113 - "SectionState"
Cohesion: 0.25
Nodes (7): SectionState, active, angle, flip, offset, plane, visible

### Community 114 - "uninstall.sh"
Cohesion: 0.52
Nodes (6): die(), manifest_for(), refresh(), uninstall.sh script, step(), usage()

### Community 115 - "install.sh"
Cohesion: 0.60
Nodes (5): die(), refresh(), install.sh script, step(), usage()

### Community 116 - "TestFramework.h"
Cohesion: 0.12
Nodes (13): Result, error, ok, output, captured(), PYBIND11_EMBEDDED_MODULE(), PythonHost::exec(), PythonHost::PythonHost() (+5 more)

### Community 119 - "UserParameter"
Cohesion: 0.33
Nodes (6): UserParameter, comment, expression, name, unit, value

### Community 120 - "Profile"
Cohesion: 0.33
Nodes (5): Profile, area, face, x, y

### Community 121 - "SelectionBox"
Cohesion: 0.28
Nodes (3): SelectionBox, crossing, rect()

### Community 123 - "BooleanOp"
Cohesion: 0.50
Nodes (4): BooleanOp, Cut, Intersect, Join

### Community 124 - "MassProperties"
Cohesion: 0.50
Nodes (4): MassProperties, area, centerOfMass, volume

### Community 126 - "ThreadInfo"
Cohesion: 0.50
Nodes (4): ThreadInfo, diameter, internal, pitch

### Community 128 - "ChamferType"
Cohesion: 0.67
Nodes (3): ChamferType, DistanceAngle, TwoDistances

### Community 129 - "Joint"
Cohesion: 0.22
Nodes (5): Joint, asBuilt_, def_, Sweep, def_

### Community 130 - "Column"
Cohesion: 0.25
Nodes (8): Column, kComment, kExpression, kName, kParameter, kStar, kUnit, kValue

### Community 131 - "MarkingMenu"
Cohesion: 0.40
Nodes (3): MarkingMenu, enabled, public

### Community 134 - "HoleSize"
Cohesion: 0.50
Nodes (4): HoleSize, modeled, pitch, radius

### Community 135 - "Rect"
Cohesion: 0.50
Nodes (4): Session::notifyChanged(), Rect, l, p

### Community 140 - "ChainSegment"
Cohesion: 0.67
Nodes (3): ChainSegment, entity, forward

### Community 142 - "SplineHandle"
Cohesion: 0.25
Nodes (8): SplineHandle, arm, index, set, tx, ty, x, y

### Community 145 - "BodyFrame"
Cohesion: 0.09
Nodes (23): BodyFrame, diag, dx, dy, dz, x0, y0, z0 (+15 more)

### Community 147 - "EntityType"
Cohesion: 0.33
Nodes (6): EntityType, Arc, Circle, Ellipse, Line, Spline

## Knowledge Gaps
- **812 isolated node(s):** `ok`, `output`, `error`, `isReal`, `real` (+807 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 1568 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **25 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `Viewport` connect `Viewport` to `.rebuild`, `SelectionBox`, `Feature`, `Viewport.cpp`, `ViewportArrow.cpp`, `Viewport.h`, `AnalysisSettings`, `SketchDisplay`, `.redrawAll`, `Viewport::setDragArrow`, `SketchCurves.cpp`, `.toPixels`, `.setSelectionFilter`, `QMouseEvent`, `QDialog`, `QTimer`?**
  _High betweenness centrality (0.126) - this node is a cross-community bridge._
- **What connects `ok`, `output`, `error` to the rest of the system?**
  _812 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Viewport` be split into smaller, more focused modules?**
  _Cohesion score 0.014176245210727969 - nodes in this community are weakly interconnected._
- **Why does `optional` connect `Feature` to `Viewport`, `MainWindow`, `SketchEditor`, `DocumentError`, `optional`, `Kernel.cpp`, `Viewport.h`, `CommandDialog`, `Io.cpp`, `nameOf`, `SketchEditor.cpp`, `ViewportSketch.cpp`, `DocCommands.cpp`, `Inputs`, `Command`, `SketchOps.cpp`, `SketchGeometry.cpp`, `AnalysisSettings`, `Document.cpp`, `Expression.cpp`, `CommandDialog.cpp`, `Session`, `Unit`, `ViewportArrow.cpp`, `Constraint`, `Vec3`, `CommandDialog::CommandDialog`, `SketchCurves.cpp`, `ReplayStep`, `MainWindowArrow.cpp`, `.primary`?**
  _High betweenness centrality (0.121) - this node is a cross-community bridge._
- **Should `Icons.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.051643192488262914 - nodes in this community are weakly interconnected._
- **Why does `SketchEditor` connect `SketchEditor` to `Viewport`, `Constraint`, `MainWindow`, `Feature`, `Unit`, `Entity`, `Pick`, `optional`, `Display`, `Constraint`, `Kind`, `SketchEditor.cpp`, `.press2d`, `Snap`, `QMouseEvent`, `Session`?**
  _High betweenness centrality (0.088) - this node is a cross-community bridge._
- **Should `tsr` be split into smaller, more focused modules?**
  _Cohesion score 0.035283993115318414 - nodes in this community are weakly interconnected._