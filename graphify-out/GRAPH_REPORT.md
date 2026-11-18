# Graph Report - tessera  (2026-11-17)

## Corpus Check
- 419 files · ~278,672 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 70 file(s) not represented in the graph (top: .drive 62, (none) 5, .cmake 1)

## Summary
- 3945 nodes · 10137 edges · 157 communities (126 shown, 31 thin omitted)
- Extraction: 85% EXTRACTED · 15% INFERRED · 0% AMBIGUOUS · INFERRED: 1550 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `51136e5b`
- Run `git rev-parse HEAD` and compare to check if the graph is stale.
- Run `graphify update .` after code changes (no API cost).

## Community Hubs (Navigation)
- Viewport
- Icons.cpp
- Session.cpp
- MainWindow
- run_oracle.py
- DocCommands.cpp
- Document
- Viewport.cpp
- SketchEditor
- DocumentError
- optional
- Kernel.cpp
- AnalysisSettings
- Kind
- QMouseEvent
- CommandDialog
- Io.cpp
- Parser
- sketchFor
- Document
- Snap
- Affine
- ViewportSketch.cpp
- SketchPalette
- Sketch
- Inputs
- Command
- Colors
- KernelError
- SketchOps.cpp
- MainWindowSketch.cpp
- ParameterCompleter
- Pick
- Document::recompute
- MainWindow.cpp
- solve
- QObject
- curve
- ConstraintType
- AdskModule.cpp
- QPointF
- Icons.h
- Zip.cpp
- AnalysisSettings
- Sketch.cpp
- Document.cpp
- MarkingMenu.cpp
- InputDef
- SketchEditor.cpp
- .toPixels
- string
- Command.cpp
- BoundingBox
- ViewportAnalysis.cpp
- xdrive.py
- CommandDialog.cpp
- Session
- Theme.cpp
- BodyFrame
- CommandRegistry
- Expression.cpp
- TEST
- Theme
- Feature
- InputType
- ParametersDialog.cpp
- Axis
- ViewportArrow.cpp
- cachedProfiles
- Constraint
- Vec3
- CommandDialog::CommandDialog
- math
- CommandDialog::CommandDialog
- SketchDisplay
- Kind
- Measurement
- SketchCurves.cpp
- QTimer
- Level
- README.md
- .showDialog
- test_feature_pattern.py
- Sweep
- QDialog
- toDxf
- FileFormat
- Known differences still to build
- Unit
- ReplayStep
- src/main.cpp
- MainWindowArrow.cpp
- FakeDoc
- ModelParameter
- .openMarkingMenu
- Viewport::setDragArrow
- Document::load
- UserParameter
- TEST
- test_rigid_group.py
- Entity
- Display
- main
- TopologyCounts
- Known gaps
- .redrawAll
- SectionState
- uninstall.sh
- install.sh
- TestFramework.h
- Viewport.h
- Placement
- bindAdsk
- MainWindow::MainWindow
- SelectionBox
- test_incremental_replay.py
- Profile
- TEST
- QScrollArea
- BooleanOp
- MassProperties
- ThreadInfo
- Joint
- test_conic_control_spline.py
- PYBIND11_EMBEDDED_MODULE
- CommandSession
- LAB_NOTES.md
- ChamferType
- .add
- build.sh
- live-test.sh
- MetricSize
- Handle
- path
- SplineHandle
- SplineKind
- ChainSegment
- gp_Pnt
- Joints
- EntityType
- fromSvg
- test_extrude_participants.py
- SketchError
- Value.h
- Architecture
- Document::reevaluateParameters
- Mesh
- fail
- Placement::apply

## God Nodes (most connected - your core abstractions)
1. `Viewport` - 286 edges
2. `SketchEditor` - 198 edges
3. `MainWindow` - 184 edges
4. `Inputs` - 161 edges
5. `render()` - 124 edges
6. `Document` - 121 edges
7. `CommandContext` - 116 edges
8. `CommandDialog` - 98 edges
9. `CommandError` - 70 edges
10. `Command` - 68 edges

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

## Communities (157 total, 31 thin omitted)

### Community 0 - "Viewport"
Cohesion: 0.01
Nodes (79): view_, QLineEdit, Viewport, analysis_, analysisObjects_, appliedGridStep_, arrowBoxes_, arrowDragging_ (+71 more)

### Community 1 - "Icons.cpp"
Cohesion: 0.05
Nodes (129): accessibilityIcon(), appearanceIcon(), arc3Icon(), arcIcon(), arcTangentIcon(), arrow(), axisIcon(), boundaryFillIcon() (+121 more)

### Community 2 - "Session.cpp"
Cohesion: 0.12
Nodes (33): historyEdit(), OwnedCommand, owned, OwningCommandSession, plainEdit(), Session::addListener(), Session::addNamedView(), Session::begin() (+25 more)

### Community 4 - "MainWindow"
Cohesion: 0.03
Nodes (64): CommandDialog, MainWindow, active_, arrowInput_, arrowInput2_, bodiesBeforeCommand_, combEdges_, combPicking_ (+56 more)

### Community 5 - "run_oracle.py"
Cohesion: 0.08
Nodes (54): add_point(), arc_poly(), body_at(), body_list(), build_sketch(), chain(), circumcentre(), cm() (+46 more)

### Community 6 - "DocCommands.cpp"
Cohesion: 0.06
Nodes (35): AddUserParameter, def_, axisOf(), boundaryFillCells(), checkPattern(), CircularPattern, def_, CreateSketch (+27 more)

### Community 7 - "Document"
Cohesion: 0.03
Nodes (15): Document, effects_, lastReplayed_, lastReused_, modified_, pendingTools_, registry_, replaying_ (+7 more)

### Community 8 - "Viewport.cpp"
Cohesion: 0.05
Nodes (15): hiddenColour(), keys(), qc(), QKeyEvent, rgb(), sharpEdges(), Style, Shaded (+7 more)

### Community 9 - "SketchEditor"
Cohesion: 0.03
Nodes (53): HandleHit, back, index, spline, SketchEditor, arcDrag_, arcDragMoved_, arcEndsChain_ (+45 more)

### Community 10 - "DocumentError"
Cohesion: 0.09
Nodes (31): DocumentError, PhysicalMaterial, color, density, name, SketchRecord, data, name (+23 more)

### Community 11 - "optional"
Cohesion: 0.15
Nodes (3): optional, CommandRegistry::all(), Document

### Community 12 - "Kernel.cpp"
Cohesion: 0.03
Nodes (4): isoCoarsePitch(), topologyCounts(), touching(), wrapOntoCylinder()

### Community 13 - "AnalysisSettings"
Cohesion: 0.11
Nodes (18): AnalysisKind, Accessibility, CurvatureMap, Draft, Isocurve, MinimumRadius, None, Zebra (+10 more)

### Community 14 - "Kind"
Cohesion: 0.07
Nodes (29): ConstructPlane, def_, kind_, EdgeFeature, def_, kind_, Kind, Angle (+21 more)

### Community 15 - "QMouseEvent"
Cohesion: 0.15
Nodes (7): QMouseEvent, ViewInteractor, Viewport::arrowMouseMove(), Viewport::arrowMousePress(), Viewport::arrowMouseRelease(), Viewport::dragArrowForTest(), Viewport::rebuildArrows()

### Community 16 - "CommandDialog"
Cohesion: 0.04
Nodes (36): CommandDialog, bodiesId_, bodiesLabel_, bodyInput_, buttons_, cellsId_, cellsList_, cmd_ (+28 more)

### Community 17 - "Io.cpp"
Cohesion: 0.11
Nodes (8): formatForPath(), fromBrep(), importShape(), lower(), meshOf(), scaled(), toBrep(), xmlEscape()

### Community 18 - "Parser"
Cohesion: 0.18
Nodes (15): Quantity, angle, length, value, describe(), isIdentChar(), Parser, ang_ (+7 more)

### Community 19 - "sketchFor"
Cohesion: 0.12
Nodes (14): Extrude, def_, Pipe, def_, Revolve, def_, RibWeb, def_ (+6 more)

### Community 21 - "Document"
Cohesion: 0.22
Nodes (8): ConstructAxisPoint, def_, kind_, jointOrigin(), JointPick, frame, planeOf(), revolveAxis()

### Community 22 - "Snap"
Cohesion: 0.11
Nodes (18): Snap, alignX, alignY, bodyArc, bodySegment, entity, fromX, fromY (+10 more)

### Community 24 - "Affine"
Cohesion: 0.16
Nodes (9): Affine, a, b, d, e, Builder, byPlace_, k_ (+1 more)

### Community 25 - "ViewportSketch.cpp"
Cohesion: 0.09
Nodes (6): faceStyle(), lineStyle(), rgb(), Viewport::lookAt(), Viewport::planePoint(), Viewport::toWidget()

### Community 26 - "SketchPalette"
Cohesion: 0.05
Nodes (27): flatButton(), MainWindow::buildSketchTab(), QCheckBox, QLabel, QToolButton, QWidget, SketchEditor, SketchPalette (+19 more)

### Community 27 - "Sketch"
Cohesion: 0.06
Nodes (25): Sketch, constraints, entities, points, texts, SolveResult, dof, entityFixed (+17 more)

### Community 28 - "Inputs"
Cohesion: 0.07
Nodes (26): CommandContext, CommandError, Inputs, CommandSession::CommandSession(), getBool(), getInt(), applyOperation(), applyToParticipants() (+18 more)

### Community 29 - "Command"
Cohesion: 0.04
Nodes (56): Adding a tool, Command, CommandDef, feature, icon, id, inputs, name (+48 more)

### Community 30 - "Colors"
Cohesion: 0.07
Nodes (28): Colors, base, border, cubeBox, cubeText, errorBackground, grid, gridMajor (+20 more)

### Community 31 - "KernelError"
Cohesion: 0.22
Nodes (34): KernelError, asSolid(), boolean(), boundaryCells(), chamfer(), chamferEx(), deleteFaces(), draft() (+26 more)

### Community 32 - "SketchOps.cpp"
Cohesion: 0.25
Nodes (24): at(), chainOf(), chamferCorner(), circularPattern(), copyEntities(), cross(), dot(), extendLine() (+16 more)

### Community 33 - "MainWindowSketch.cpp"
Cohesion: 0.08
Nodes (15): MainWindow::cancelSketch(), MainWindow::editSketch(), MainWindow::finishSketch(), MainWindow::onProfileClicked(), MainWindow::originalShape(), MainWindow::sketchPalette(), MainWindow::sketchVisible(), MainWindow::startSketch() (+7 more)

### Community 34 - "ParameterCompleter"
Cohesion: 0.13
Nodes (9): QObject, ParameterCompleter, completer_, edit_, names_, ParameterCompleter::ParameterCompleter(), public, QCompleter (+1 more)

### Community 35 - "Pick"
Cohesion: 0.12
Nodes (15): Pick, bodyArc, bodyPoint, bodySegment, hit, midpointOf, onEntity, onXAxis (+7 more)

### Community 36 - "Document::recompute"
Cohesion: 0.17
Nodes (8): Document::expressionEnv(), Document::recompute(), Document::recordFeature(), Document::removeFeature(), Document::setFeatureInputs(), Document::setFeatureSuppressed(), featureData(), toJson()

### Community 37 - "MainWindow.cpp"
Cohesion: 0.09
Nodes (3): commandIcon(), qs(), MainWindow::applySection()

### Community 38 - "solve"
Cohesion: 0.18
Nodes (12): addConstraintChecked(), Layout, n, px, py, rad, makeLayout(), pack() (+4 more)

### Community 39 - "QObject"
Cohesion: 0.16
Nodes (6): SketchEditor::SketchEditor(), edges, Tool, op, shape, target

### Community 40 - "curve"
Cohesion: 0.16
Nodes (19): conditionedSpline(), curve(), curves(), entityCurves(), G2End, d1, d2, set (+11 more)

### Community 41 - "ConstraintType"
Cohesion: 0.09
Nodes (23): ConstraintType, Angle, Coincident, Collinear, Concentric, Curvature, Diameter, Distance (+15 more)

### Community 42 - "AdskModule.cpp"
Cohesion: 0.08
Nodes (17): Application, BRepBodies, Component, Design, Product, raiseIfError(), UserParameter, name (+9 more)

### Community 43 - "QPointF"
Cohesion: 0.12
Nodes (5): PlaneEdges, arcs, curves, segments, vertices

### Community 46 - "Zip.cpp"
Cohesion: 0.27
Nodes (10): ZipError, crc32(), deflateRaw(), get16(), get32(), inflateRaw(), put16(), put32() (+2 more)

### Community 47 - "AnalysisSettings"
Cohesion: 0.08
Nodes (20): DragArrow, base, dir, radius, ref, ring, value, PendingLook (+12 more)

### Community 48 - "Sketch.cpp"
Cohesion: 0.10
Nodes (13): entityTypeName(), isDimension(), Sketch::addConstraint(), Sketch::addEllipticalArc(), Sketch::addText(), Sketch::removeEntities(), Sketch::removeImpl(), Sketch::removeItems() (+5 more)

### Community 49 - "Document.cpp"
Cohesion: 0.07
Nodes (33): ConstructionPlane, name, spec, Document::bodies(), Document::body(), Document::bodyName(), Document::component(), Document::componentOfBody() (+25 more)

### Community 50 - "MarkingMenu.cpp"
Cohesion: 0.13
Nodes (12): UiCommand, enabled, icon, id, name, panel, run, shortcut (+4 more)

### Community 51 - "InputDef"
Cohesion: 0.09
Nodes (22): InputDef, choices, defaultValue, id, label, max, min, minExclusive (+14 more)

### Community 52 - "SketchEditor.cpp"
Cohesion: 0.11
Nodes (8): angleInArc(), ccwContains(), circumcircle(), Hit, index, kind, lineEntity(), segDistance()

### Community 53 - ".toPixels"
Cohesion: 0.08
Nodes (3): glide(), toVKeys(), Viewport::environmentNames()

### Community 55 - "string"
Cohesion: 0.13
Nodes (18): bodyNumber(), Document::axisFrame(), Document::nextAxisName(), Document::nextBodyName(), Document::nextComponentName(), Document::nextDimensionName(), Document::nextPlaneName(), Document::nextPointName() (+10 more)

### Community 56 - "Command.cpp"
Cohesion: 0.15
Nodes (17): expressionKey(), Dimension, Angle, Length, Unitless, checkInputValue(), CommandContext::evaluateExpression(), CommandDef::input() (+9 more)

### Community 57 - "BoundingBox"
Cohesion: 0.18
Nodes (16): BoundingBox, max, min, WallSide, Center, Side1, Side2, curveMiddles() (+8 more)

### Community 58 - "ViewportAnalysis.cpp"
Cohesion: 0.10
Nodes (6): packed(), ramp(), shade(), Viewport::buildAnalysis(), Viewport::setCurvatureComb(), f

### Community 59 - "xdrive.py"
Cohesion: 0.28
Nodes (15): button(), canvas(), click(), drag(), flush(), geometry(), key(), keycode() (+7 more)

### Community 62 - "Session"
Cohesion: 0.07
Nodes (7): PythonHost::PythonHost(), Session, commands_, doc_, listeners_, nextListener_, path_

### Community 63 - "Theme.cpp"
Cohesion: 0.19
Nodes (6): setIconTheme(), darkColors(), darkPalette(), darkStyleSheet(), lightColors(), lightStyleSheet()

### Community 64 - "BodyFrame"
Cohesion: 0.07
Nodes (41): BodyFrame, diag, dx, dy, dz, x0, y0, z0 (+33 more)

### Community 65 - "CommandRegistry"
Cohesion: 0.12
Nodes (4): CommandRegistry, cmds_, CommandRegistry::add(), TEST()

### Community 66 - "Expression.cpp"
Cohesion: 0.13
Nodes (15): ExpressionEnv, lengthUnit, lookup, ExpressionError, evaluateExpression(), evaluateQuantity(), expressionReferences(), isConstantName() (+7 more)

### Community 67 - "TEST"
Cohesion: 0.09
Nodes (3): param(), TEST(), tmp()

### Community 68 - "Theme"
Cohesion: 0.22
Nodes (4): Theme, colors_, public, styled_

### Community 69 - "Feature"
Cohesion: 0.08
Nodes (20): Feature, commandId, error, id, inputs, name, parameterNames, rolledBack (+12 more)

### Community 70 - "InputType"
Cohesion: 0.12
Nodes (17): InputType, Axis, Bodies, Body, Bool, Choice, Edges, Faces (+9 more)

### Community 71 - "ParametersDialog.cpp"
Cohesion: 0.06
Nodes (24): Column, kComment, kExpression, kName, kParameter, kStar, kUnit, kValue (+16 more)

### Community 72 - "Axis"
Cohesion: 0.50
Nodes (4): Axis, X, Y, Z

### Community 73 - "ViewportArrow.cpp"
Cohesion: 0.07
Nodes (23): Viewport::frontEdgeOwner(), rgb(), segmentDistance(), Viewport::arrowAt(), Viewport::arrowParam(), Viewport::dragArrowHandle(), Viewport::placeArrowBoxes(), Viewport::rebuildArrow() (+15 more)

### Community 74 - "cachedProfiles"
Cohesion: 0.18
Nodes (3): MainWindow::updateDragArrow(), cachedProfiles(), keyOf()

### Community 75 - "Constraint"
Cohesion: 0.09
Nodes (18): ext(), fixedColor(), freeColor(), qc(), rgb(), wire(), Constraint, driven (+10 more)

### Community 76 - "Vec3"
Cohesion: 0.17
Nodes (22): SurfacePoint, normal, point, Vec3, containsPoint(), edgeMidpoint(), edgesNear(), extrudeToFace() (+14 more)

### Community 77 - "CommandDialog::CommandDialog"
Cohesion: 0.14
Nodes (5): CommandDialog::CommandDialog(), BoundaryCell, ref, shape, volume

### Community 78 - "math"
Cohesion: 0.06
Nodes (3): dist(), check_regular(), dist_to_line()

### Community 79 - "CommandDialog::CommandDialog"
Cohesion: 0.16
Nodes (5): ExpressionSpinBox, eval_, expression_, shown_, formatNumber()

### Community 80 - "SketchDisplay"
Cohesion: 0.12
Nodes (11): ProfileObject, index, sketch, SketchDisplay, construction, curves, fixedCurves, frame (+3 more)

### Community 81 - "Kind"
Cohesion: 0.09
Nodes (21): HudField, edit, editing, kind, locked, value, Kind, Angle (+13 more)

### Community 82 - "Measurement"
Cohesion: 0.13
Nodes (14): Kind, Angle, Area, Length, Volume, Measurement, from, hasLine (+6 more)

### Community 83 - "SketchCurves.cpp"
Cohesion: 0.13
Nodes (19): crossings(), crossingsOf(), Curve2d, curve2d(), periodic, t0, t1, endIsFree() (+11 more)

### Community 84 - "QTimer"
Cohesion: 0.12
Nodes (5): QTimer, Viewport::selectArrowValue(), Viewport::setTriad(), Viewport::setTriadActive(), Viewport::triadMouseRelease()

### Community 85 - "Level"
Cohesion: 0.12
Nodes (13): debug(), error(), info(), Level, Debug, Error, Info, Warning (+5 more)

### Community 86 - "README.md"
Cohesion: 0.10
Nodes (15): Build, Conventions, Development, Tests, Reference parts, Fusion feature checklist, Roadmap, Contents (+7 more)

### Community 89 - "Sweep"
Cohesion: 0.13
Nodes (10): Coil, def_, Primitive, build_, def_, Sweep, def_, Thicken (+2 more)

### Community 90 - "QDialog"
Cohesion: 0.06
Nodes (29): QDialog, MainWindow::checkInterference(), MainWindow::chooseUnits(), MainWindow::driveJoints(), MainWindow::editAppearance(), MainWindow::editMaterial(), MainWindow::exportDesign(), MainWindow::formatLength() (+21 more)

### Community 91 - "toDxf"
Cohesion: 0.43
Nodes (7): Point, x, y, z, customPlaneSpec(), planeFrame(), toDxf()

### Community 92 - "FileFormat"
Cohesion: 0.17
Nodes (12): FileFormat, Brep, Iges, Obj, Step, Stl, ThreeMF, FormatInfo (+4 more)

### Community 93 - "Known differences still to build"
Cohesion: 0.15
Nodes (12): Data and files, Findings from the videos, Fusion study list, Interface, Known differences still to build, Navigation and display, Selection and the canvas, Sketch (+4 more)

### Community 94 - "Unit"
Cohesion: 0.13
Nodes (14): MainWindow::lengthUnit(), Unit, Centimeter, Degree, Foot, Inch, Meter, Millimeter (+6 more)

### Community 95 - "ReplayStep"
Cohesion: 0.05
Nodes (35): Body, color, display, material, name, shape, Component, bodies (+27 more)

### Community 96 - "src/main.cpp"
Cohesion: 0.09
Nodes (5): grabWindowWithPanels(), writeLiveGeometry(), MarkingMenu, enabled, public

### Community 97 - "MainWindowArrow.cpp"
Cohesion: 0.09
Nodes (11): ArrowPlacement, base, dir, edgePlacement(), facesPlacement(), MainWindow::attachArrowCompleters(), MainWindow::patternCentre(), MainWindow::pickedFaces() (+3 more)

### Community 98 - "FakeDoc"
Cohesion: 0.17
Nodes (6): FakeDoc, aborts, commits, items, open, snapshot

### Community 99 - "ModelParameter"
Cohesion: 0.11
Nodes (23): ModelParameter, angle, expression, input, label, name, owner, unit (+15 more)

### Community 101 - "Viewport::setDragArrow"
Cohesion: 0.18
Nodes (4): Viewport::DragArrow::handle(), Viewport::emitArrow(), Viewport::setDragArrow(), Viewport::setDragRing()

### Community 102 - "Document::load"
Cohesion: 0.17
Nodes (5): doc_(), Document::Document(), Document::ocafBytes(), ocafApplication(), Document::load()

### Community 103 - "UserParameter"
Cohesion: 0.33
Nodes (6): UserParameter, comment, expression, name, unit, value

### Community 106 - "Entity"
Cohesion: 0.11
Nodes (12): Entity, a, b, center, construction, fit, handles, included (+4 more)

### Community 107 - "Display"
Cohesion: 0.25
Nodes (7): Display, constraints, construction, dimensions, points, profiles, projected

### Community 108 - "main"
Cohesion: 0.27
Nodes (6): listCommands(), main(), usage(), main(), smoke(), key

### Community 110 - "TopologyCounts"
Cohesion: 0.18
Nodes (16): Section, Circular, Square, Triangular, TopologyCounts, edges, faces, shells (+8 more)

### Community 111 - "Known gaps"
Cohesion: 0.17
Nodes (12): 3D Sketch, Boundary Fill, Curvature (G2), Emboss, Face patterns, Include 3D Geometry, Known gaps, Move/Copy (+4 more)

### Community 112 - ".redrawAll"
Cohesion: 0.10
Nodes (8): NavPreset, Fusion, SolidWorks, Tinkercad, Viewport::clearDragArrow(), Viewport::clearSecondArrow(), Viewport::setInteractor(), Viewport::clearTriad()

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
Cohesion: 0.15
Nodes (11): Result, error, ok, output, captured(), PythonHost::exec(), PythonHost::runScript(), Case (+3 more)

### Community 118 - "Placement"
Cohesion: 0.25
Nodes (7): Placement, angle, cx, cy, dx, dy, scale

### Community 119 - "bindAdsk"
Cohesion: 0.29
Nodes (3): bindAdsk(), BRepBody, index

### Community 120 - "MainWindow::MainWindow"
Cohesion: 0.13
Nodes (4): PythonHost, MainWindow::MainWindow(), MainWindow::exitSketchMode(), MainWindow::showPreferences()

### Community 123 - "Profile"
Cohesion: 0.33
Nodes (5): Profile, area, face, x, y

### Community 124 - "TEST"
Cohesion: 0.14
Nodes (6): Entry, data, name, slurp(), TEST(), tmp()

### Community 126 - "BooleanOp"
Cohesion: 0.50
Nodes (4): BooleanOp, Cut, Intersect, Join

### Community 127 - "MassProperties"
Cohesion: 0.50
Nodes (4): MassProperties, area, centerOfMass, volume

### Community 128 - "ThreadInfo"
Cohesion: 0.50
Nodes (4): ThreadInfo, diameter, internal, pitch

### Community 129 - "Joint"
Cohesion: 0.42
Nodes (3): Joint, asBuilt_, def_

### Community 132 - "CommandSession"
Cohesion: 0.15
Nodes (4): CommandSession, inputs_, CommandRegistry::find(), CommandRegistry::run()

### Community 134 - "ChamferType"
Cohesion: 0.67
Nodes (3): ChamferType, DistanceAngle, TwoDistances

### Community 139 - "MetricSize"
Cohesion: 0.15
Nodes (10): MarkingMenu::keyPressEvent(), MarkingMenu::MarkingMenu(), MarkingMenu::run(), MetricSize, close, d, loose, name (+2 more)

### Community 141 - "path"
Cohesion: 0.47
Nodes (8): MainWindow::print3d(), NamedShape, compoundOf(), exportShapes(), fmt(), write3mf(), writeObj(), path

### Community 142 - "SplineHandle"
Cohesion: 0.25
Nodes (8): SplineHandle, arm, index, set, tx, ty, x, y

### Community 143 - "SplineKind"
Cohesion: 0.22
Nodes (7): SplineKind, Conic, Control, Fit, Sketch::addSpline(), Sketch::entityPoints(), Sketch::removePoints()

### Community 144 - "ChainSegment"
Cohesion: 0.67
Nodes (3): ChainSegment, entity, forward

### Community 145 - "gp_Pnt"
Cohesion: 0.32
Nodes (5): faceNormalAt(), nearestFace(), offsetLoop(), offsetRegion(), pointOnFace()

### Community 146 - "Joints"
Cohesion: 0.36
Nodes (3): cornerAt(), Joints, parent_

### Community 147 - "EntityType"
Cohesion: 0.29
Nodes (7): EntityType, Arc, Circle, Ellipse, Line, Spline, isRound()

### Community 148 - "fromSvg"
Cohesion: 0.57
Nodes (4): fromSvg(), lengthMm(), numbers(), parseTransform()

### Community 150 - "SketchError"
Cohesion: 0.33
Nodes (4): SketchError, Sketch::addConic(), Sketch::checkIndices(), Sketch::fromJson()

### Community 152 - "Architecture"
Cohesion: 0.40
Nodes (4): Architecture, How a command works, The document, Units

### Community 154 - "Mesh"
Cohesion: 0.40
Nodes (3): Mesh, nodes, triangles

## Knowledge Gaps
- **804 isolated node(s):** `ok`, `output`, `error`, `isReal`, `real` (+799 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 1538 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **31 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `optional` connect `optional` to `Viewport`, `MainWindow`, `DocCommands.cpp`, `SketchEditor`, `DocumentError`, `Kernel.cpp`, `Io.cpp`, `Parser`, `sketchFor`, `Entity`, `Joints`, `ViewportSketch.cpp`, `QPointF`, `AnalysisSettings`, `Document.cpp`, `InputDef`, `SketchEditor.cpp`, `SketchGeometry.cpp`, `string`, `CommandDialog.cpp`, `Session`, `Expression.cpp`, `Feature`, `ViewportArrow.cpp`, `Constraint`, `Vec3`, `CommandDialog::CommandDialog`, `SketchCurves.cpp`, `Unit`, `ReplayStep`, `MainWindowArrow.cpp`, `Viewport.h`?**
  _High betweenness centrality (0.140) - this node is a cross-community bridge._
- **What connects `ok`, `output`, `error` to the rest of the system?**
  _804 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Viewport` be split into smaller, more focused modules?**
  _Cohesion score 0.014071381977448514 - nodes in this community are weakly interconnected._
- **Why does `Viewport` connect `Viewport` to `MainWindow`, `Viewport::setDragArrow`, `QDialog`, `Viewport.cpp`, `ViewportArrow.cpp`, `optional`, `Handle`, `AnalysisSettings`, `AnalysisSettings`, `SketchDisplay`, `.redrawAll`, `QMouseEvent`, `SketchCurves.cpp`, `QTimer`, `Viewport.h`, `.toPixels`, `SelectionBox`, `ViewportAnalysis.cpp`?**
  _High betweenness centrality (0.138) - this node is a cross-community bridge._
- **Should `Icons.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.052312435765673175 - nodes in this community are weakly interconnected._
- **Why does `SketchEditor` connect `SketchEditor` to `Viewport`, `optional`, `QMouseEvent`, `Entity`, `Snap`, `Sketch`, `ParameterCompleter`, `Pick`, `QObject`, `QPointF`, `SketchEditor.cpp`, `Session`, `Constraint`, `Kind`, `Unit`, `MainWindowArrow.cpp`, `Entity`, `Display`, `Viewport.h`?**
  _High betweenness centrality (0.104) - this node is a cross-community bridge._
- **Should `Session.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.11951219512195121 - nodes in this community are weakly interconnected._