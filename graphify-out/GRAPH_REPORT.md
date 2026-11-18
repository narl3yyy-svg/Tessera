# Graph Report - tessera  (2026-11-17)

## Corpus Check
- 438 files · ~286,904 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 77 file(s) not represented in the graph (top: .drive 69, (none) 5, .cmake 1)

## Summary
- 4027 nodes · 10364 edges · 156 communities (127 shown, 29 thin omitted)
- Extraction: 85% EXTRACTED · 15% INFERRED · 0% AMBIGUOUS · INFERRED: 1579 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `57ed7273`
- Run `git rev-parse HEAD` and compare to check if the graph is stale.
- Run `graphify update .` after code changes (no API cost).

## Community Hubs (Navigation)
- Viewport
- QPainter
- Session.cpp
- tsr
- MainWindow
- run_oracle.py
- CommandError
- Document
- Viewport.cpp
- SketchEditor
- DocumentError
- optional
- Kernel.cpp
- AnalysisSettings
- Kind
- Viewport::setDragArrow
- CommandDialog
- Io.cpp
- Parser
- InputDef
- SketchEditor.cpp
- stroke
- TEST
- CommandDialog.cpp
- Affine
- ViewportSketch.cpp
- SketchPalette
- DocCommands.cpp
- sketchFor
- CommandContext
- Colors
- KernelError
- SketchOps.cpp
- .rebuild
- ParameterCompleter
- Constraint
- src/main.cpp
- solve
- Icons.cpp
- curve
- ConstraintType
- AdskModule.cpp
- Pick
- TopologyCounts
- Zip.cpp
- AnalysisSettings
- Sketch
- Document.cpp
- .showDialog
- string
- .press2d
- .toPixels
- Snap
- Document::recompute
- MainWindow.cpp
- TEST
- .openMarkingMenu
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
- .mouseMove
- Vec3
- CommandDialog::CommandDialog
- math
- CommandDialog::CommandDialog
- SketchDisplay
- Kind
- Measurement
- SketchCurves.cpp
- Known gaps
- Level
- checkPattern
- UiCommand
- test_feature_pattern.py
- MainWindow::MainWindow
- MainWindowTools.cpp
- TEST
- FileFormat
- Known differences still to build
- ReplayStep
- main
- MainWindowArrow.cpp
- FakeDoc
- ParamSet
- BoundingBox
- QPointF
- Document::load
- toDxf
- Placement
- test_rigid_group.py
- Entity
- ViewportAnalysis.cpp
- Display
- Axis
- Known gaps
- TEST
- SectionState
- uninstall.sh
- install.sh
- TestFramework.h
- .redrawAll
- QDialog
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
- Inputs
- Icons.h
- .add
- cachedProfiles
- LAB_NOTES.md
- MainWindow::buildUiCommands
- qs
- build.sh
- live-test.sh
- ChainSegment
- .eventFilter
- SplineHandle
- ConstructionPoint
- BodyFrame
- Align
- EntityType
- Architecture
- BRepBody
- HandleHit
- Joints
- ellipseIcon
- Placement::apply

## God Nodes (most connected - your core abstractions)
1. `Viewport` - 286 edges
2. `SketchEditor` - 198 edges
3. `MainWindow` - 189 edges
4. `Inputs` - 170 edges
5. `render()` - 127 edges
6. `CommandContext` - 125 edges
7. `Document` - 122 edges
8. `CommandDialog` - 101 edges
9. `CommandError` - 75 edges
10. `Command` - 71 edges

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

## Communities (156 total, 29 thin omitted)

### Community 0 - "Viewport"
Cohesion: 0.01
Nodes (79): view_, QLineEdit, Viewport, analysis_, analysisObjects_, appliedGridStep_, arrowBoxes_, arrowDragging_ (+71 more)

### Community 1 - "QPainter"
Cohesion: 0.09
Nodes (52): accessibilityIcon(), alignIcon(), arrow(), axisIcon(), coilIcon(), combineIcon(), comIcon(), componentIcon() (+44 more)

### Community 2 - "Session.cpp"
Cohesion: 0.13
Nodes (32): historyEdit(), OwnedCommand, owned, OwningCommandSession, plainEdit(), Session::addListener(), Session::addNamedView(), Session::begin() (+24 more)

### Community 4 - "MainWindow"
Cohesion: 0.03
Nodes (66): CommandDialog, MainWindow, active_, appearanceColour_, appearanceFaces_, appearancePanel_, arrowInput_, arrowInput2_ (+58 more)

### Community 5 - "run_oracle.py"
Cohesion: 0.08
Nodes (54): add_point(), arc_poly(), body_at(), body_list(), build_sketch(), chain(), circumcentre(), cm() (+46 more)

### Community 6 - "CommandError"
Cohesion: 0.10
Nodes (37): CommandError, getBool(), getInt(), getReal(), Align::apply(), applyOperation(), applyToParticipants(), bodyCentre() (+29 more)

### Community 7 - "Document"
Cohesion: 0.03
Nodes (15): Document, effects_, lastReplayed_, lastReused_, modified_, pendingTools_, registry_, replaying_ (+7 more)

### Community 8 - "Viewport.cpp"
Cohesion: 0.05
Nodes (8): glide(), keys(), NavPreset, Fusion, SolidWorks, Tinkercad, QKeyEvent, QtFrameBuffer

### Community 9 - "SketchEditor"
Cohesion: 0.03
Nodes (53): SketchEditor, arcDrag_, arcDragMoved_, arcEndsChain_, arcFrom_, arcRef_, bodyEdges_, boxing_ (+45 more)

### Community 10 - "DocumentError"
Cohesion: 0.10
Nodes (26): DocumentError, checkViewName(), Document::abortTransaction(), Document::addNamedView(), Document::addUserParameter(), Document::commitTransaction(), Document::openTransaction(), Document::removeBody() (+18 more)

### Community 11 - "optional"
Cohesion: 0.10
Nodes (3): optional, CommandRegistry::all(), Document

### Community 12 - "Kernel.cpp"
Cohesion: 0.03
Nodes (4): isoCoarsePitch(), topologyCounts(), touching(), wrapOntoCylinder()

### Community 13 - "AnalysisSettings"
Cohesion: 0.11
Nodes (18): AnalysisKind, Accessibility, CurvatureMap, Draft, Isocurve, MinimumRadius, None, Zebra (+10 more)

### Community 14 - "Kind"
Cohesion: 0.07
Nodes (29): ConstructAxisPoint, def_, kind_, EdgeFeature, def_, kind_, Kind, Angle (+21 more)

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
Cohesion: 0.12
Nodes (27): ExpressionEnv, lengthUnit, lookup, ExpressionError, Quantity, angle, length, value (+19 more)

### Community 19 - "InputDef"
Cohesion: 0.09
Nodes (22): InputDef, choices, defaultValue, id, label, max, min, minExclusive (+14 more)

### Community 21 - "stroke"
Cohesion: 0.07
Nodes (41): arc3Icon(), arcIcon(), arcTangentIcon(), breakIcon(), centerRectIcon(), circle2Icon(), circle3Icon(), circleIcon() (+33 more)

### Community 22 - "TEST"
Cohesion: 0.08
Nodes (17): Sketch, constraints, entities, points, texts, Text, angle, corner (+9 more)

### Community 24 - "Affine"
Cohesion: 0.14
Nodes (13): Affine, a, b, d, e, Builder, byPlace_, k_ (+5 more)

### Community 25 - "ViewportSketch.cpp"
Cohesion: 0.06
Nodes (7): QLabel, faceStyle(), lineStyle(), rgb(), Viewport::lookAt(), Viewport::planePoint(), Viewport::toWidget()

### Community 26 - "SketchPalette"
Cohesion: 0.07
Nodes (23): QLabel, QToolButton, QWidget, SketchEditor, SketchPalette, body_, constraints_, construction_ (+15 more)

### Community 27 - "DocCommands.cpp"
Cohesion: 0.14
Nodes (15): axisOf(), HoleSize, modeled, pitch, radius, JointPick, frame, makeBox() (+7 more)

### Community 28 - "sketchFor"
Cohesion: 0.11
Nodes (12): Emboss, def_, Extrude, def_, Hole, def_, Pipe, def_ (+4 more)

### Community 29 - "CommandContext"
Cohesion: 0.03
Nodes (57): Adding a tool, Command, CommandContext, CommandDef, feature, icon, id, inputs (+49 more)

### Community 30 - "Colors"
Cohesion: 0.07
Nodes (28): Colors, base, border, cubeBox, cubeText, errorBackground, grid, gridMajor (+20 more)

### Community 31 - "KernelError"
Cohesion: 0.23
Nodes (35): KernelError, asSolid(), boolean(), boundaryCells(), chamfer(), chamferEx(), deleteFaces(), draft() (+27 more)

### Community 32 - "SketchOps.cpp"
Cohesion: 0.21
Nodes (26): at(), chainOf(), chamferCorner(), circularPattern(), copyEntities(), cornerAt(), cross(), dot() (+18 more)

### Community 33 - ".rebuild"
Cohesion: 0.10
Nodes (12): hiddenColour(), qc(), rgb(), sharpEdges(), Style, Shaded, ShadedEdges, ShadedHidden (+4 more)

### Community 34 - "ParameterCompleter"
Cohesion: 0.12
Nodes (8): ParameterCompleter, completer_, edit_, names_, ParameterCompleter::ParameterCompleter(), public, QCompleter, QLineEdit

### Community 35 - "Constraint"
Cohesion: 0.08
Nodes (20): Constraint, driven, entities, expression, hasLabel, labelX, labelY, name (+12 more)

### Community 37 - "src/main.cpp"
Cohesion: 0.08
Nodes (5): grabWindowWithPanels(), writeLiveGeometry(), MarkingMenu, enabled, public

### Community 38 - "solve"
Cohesion: 0.18
Nodes (12): addConstraintChecked(), Layout, n, px, py, rad, makeLayout(), pack() (+4 more)

### Community 39 - "Icons.cpp"
Cohesion: 0.09
Nodes (29): appearanceIcon(), boundaryFillIcon(), box(), chamferIcon(), cylinder(), draftIcon(), embossIcon(), extrudeIcon() (+21 more)

### Community 40 - "curve"
Cohesion: 0.16
Nodes (19): conditionedSpline(), curve(), curves(), entityCurves(), G2End, d1, d2, set (+11 more)

### Community 41 - "ConstraintType"
Cohesion: 0.08
Nodes (25): ConstraintType, Angle, Coincident, Collinear, Concentric, Curvature, Diameter, Distance (+17 more)

### Community 42 - "AdskModule.cpp"
Cohesion: 0.12
Nodes (13): Application, BRepBodies, Component, Design, Product, raiseIfError(), UserParameter, name (+5 more)

### Community 43 - "Pick"
Cohesion: 0.09
Nodes (18): QObject, Pick, bodyArc, bodyPoint, bodySegment, hit, midpointOf, onEntity (+10 more)

### Community 45 - "TopologyCounts"
Cohesion: 0.15
Nodes (18): Section, Circular, Square, Triangular, TopologyCounts, edges, faces, shells (+10 more)

### Community 46 - "Zip.cpp"
Cohesion: 0.11
Nodes (16): Entry, data, name, ZipError, crc32(), deflateRaw(), get16(), get32() (+8 more)

### Community 47 - "AnalysisSettings"
Cohesion: 0.08
Nodes (20): DragArrow, base, dir, radius, ref, ring, value, PendingLook (+12 more)

### Community 48 - "Sketch"
Cohesion: 0.08
Nodes (20): SketchError, SplineKind, Conic, Control, Fit, isDimension(), Sketch::addConic(), Sketch::addConstraint() (+12 more)

### Community 49 - "Document.cpp"
Cohesion: 0.06
Nodes (46): ConstructionPlane, name, spec, SketchRecord, data, name, offset, plane (+38 more)

### Community 50 - ".showDialog"
Cohesion: 0.13
Nodes (5): MainWindow::onEdgeClicked(), MainWindow::onProfileClicked(), MainWindow::originalShape(), MainWindow::syncPickedShapes(), MainWindow::toOriginal()

### Community 51 - "string"
Cohesion: 0.12
Nodes (9): AddUserParameter, def_, Combine, def_, isIdentifier(), NewComponent, def_, RigidGroup (+1 more)

### Community 52 - ".press2d"
Cohesion: 0.17
Nodes (3): ccwContains(), circumcircle(), segDistance()

### Community 53 - ".toPixels"
Cohesion: 0.08
Nodes (3): toVKeys(), Viewport::environmentNames(), Viewport::Viewport()

### Community 54 - "Snap"
Cohesion: 0.10
Nodes (18): Snap, alignX, alignY, bodyArc, bodySegment, entity, fromX, fromY (+10 more)

### Community 55 - "Document::recompute"
Cohesion: 0.18
Nodes (8): Document::expressionEnv(), Document::recompute(), Document::recordFeature(), Document::removeFeature(), Document::setFeatureInputs(), Document::setFeatureSuppressed(), featureData(), toJson()

### Community 56 - "MainWindow.cpp"
Cohesion: 0.10
Nodes (4): commandIcon(), flatButton(), qs(), MainWindow::applySection()

### Community 57 - "TEST"
Cohesion: 0.09
Nodes (3): param(), TEST(), tmp()

### Community 58 - ".openMarkingMenu"
Cohesion: 0.12
Nodes (5): MainWindow::beginSketch(), MainWindow::buildSketchTab(), MainWindow::enterSketchMode(), QTimer, Viewport::selectArrowValue()

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
Cohesion: 0.08
Nodes (34): boundingBox(), completeEdgeReferences(), completeFaceReferences(), decode(), decodeFaces(), dot(), edgeReference(), EdgeSig (+26 more)

### Community 65 - "CommandRegistry"
Cohesion: 0.12
Nodes (4): CommandRegistry, cmds_, CommandRegistry::add(), TEST()

### Community 66 - "Command.cpp"
Cohesion: 0.15
Nodes (16): expressionKey(), Dimension, Angle, Length, Unitless, checkInputValue(), CommandContext::evaluateExpression(), CommandDef::input() (+8 more)

### Community 67 - "Unit"
Cohesion: 0.10
Nodes (30): bindAdsk(), MainWindow::checkInterference(), MainWindow::driveJoints(), MainWindow::formatLength(), MainWindow::gridSettings(), MainWindow::lengthUnit(), MainWindow::openAnalysis(), MainWindow::openSection() (+22 more)

### Community 68 - "Theme"
Cohesion: 0.22
Nodes (4): Theme, colors_, public, styled_

### Community 69 - "Feature"
Cohesion: 0.10
Nodes (18): Feature, commandId, error, id, inputs, name, parameterNames, rolledBack (+10 more)

### Community 70 - "InputType"
Cohesion: 0.12
Nodes (17): InputType, Axis, Bodies, Body, Bool, Choice, Edges, Faces (+9 more)

### Community 71 - "ParametersDialog.cpp"
Cohesion: 0.06
Nodes (24): Column, kComment, kExpression, kName, kParameter, kStar, kUnit, kValue (+16 more)

### Community 72 - "MainWindowSketch.cpp"
Cohesion: 0.05
Nodes (19): bindTsr(), fromPy(), toPy(), typeName(), MainWindow::sketchPalette(), MarkingMenu::keyPressEvent(), MarkingMenu::MarkingMenu(), MarkingMenu::mouseMoveEvent() (+11 more)

### Community 73 - "ViewportArrow.cpp"
Cohesion: 0.05
Nodes (33): QMouseEvent, ViewInteractor, Viewport::frontEdgeOwner(), rgb(), segmentDistance(), Viewport::arrowAt(), Viewport::arrowMouseMove(), Viewport::arrowMousePress() (+25 more)

### Community 74 - "CommandSession"
Cohesion: 0.17
Nodes (4): CommandSession, inputs_, CommandRegistry::find(), CommandRegistry::run()

### Community 75 - ".mouseMove"
Cohesion: 0.15
Nodes (7): ext(), fixedColor(), freeColor(), lineEntity(), qc(), rgb(), wire()

### Community 76 - "Vec3"
Cohesion: 0.17
Nodes (22): SurfacePoint, normal, point, Vec3, containsPoint(), edgeMidpoint(), edgesNear(), extrudeToFace() (+14 more)

### Community 77 - "CommandDialog::CommandDialog"
Cohesion: 0.14
Nodes (5): CommandDialog::CommandDialog(), BoundaryCell, ref, shape, volume

### Community 78 - "math"
Cohesion: 0.04
Nodes (4): dist(), up_to_underside(), check_regular(), dist_to_line()

### Community 79 - "CommandDialog::CommandDialog"
Cohesion: 0.19
Nodes (4): ExpressionSpinBox, eval_, expression_, shown_

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

### Community 84 - "Known gaps"
Cohesion: 0.11
Nodes (19): 3D Sketch, Align, Appearance, Boundary Fill, Curvature (G2), Draft, Emboss, Face patterns (+11 more)

### Community 85 - "Level"
Cohesion: 0.16
Nodes (13): debug(), error(), info(), Level, Debug, Error, Info, Warning (+5 more)

### Community 86 - "checkPattern"
Cohesion: 0.13
Nodes (10): checkPattern(), CircularPattern, def_, Mirror, def_, PathPattern, def_, preparePattern() (+2 more)

### Community 87 - "UiCommand"
Cohesion: 0.13
Nodes (12): UiCommand, enabled, icon, id, name, panel, run, shortcut (+4 more)

### Community 89 - "MainWindow::MainWindow"
Cohesion: 0.12
Nodes (4): PythonHost, MainWindow::MainWindow(), MainWindow::exitSketchMode(), MainWindow::showPreferences()

### Community 90 - "MainWindowTools.cpp"
Cohesion: 0.06
Nodes (12): MainWindow::chooseUnits(), MainWindow::editMaterial(), MainWindow::insertFile(), MainWindow::lookTargets(), MainWindow::sectionFrame(), MainWindow::sectionPlane(), MainWindow::setSelectionFilter(), MainWindow::showCenterOfMass() (+4 more)

### Community 91 - "TEST"
Cohesion: 0.27
Nodes (3): env(), mm(), TEST()

### Community 92 - "FileFormat"
Cohesion: 0.17
Nodes (12): FileFormat, Brep, Iges, Obj, Step, Stl, ThreeMF, FormatInfo (+4 more)

### Community 93 - "Known differences still to build"
Cohesion: 0.15
Nodes (12): Data and files, Findings from the videos, Fusion study list, Interface, Known differences still to build, Navigation and display, Selection and the canvas, Sketch (+4 more)

### Community 95 - "ReplayStep"
Cohesion: 0.06
Nodes (36): Body, color, display, faceColors, material, name, shape, Component (+28 more)

### Community 96 - "main"
Cohesion: 0.27
Nodes (6): listCommands(), main(), usage(), main(), smoke(), key

### Community 97 - "MainWindowArrow.cpp"
Cohesion: 0.13
Nodes (8): ArrowPlacement, base, dir, edgePlacement(), facesPlacement(), MainWindow::attachArrowCompleters(), MainWindow::patternCentre(), MainWindow::pickedFaces()

### Community 98 - "FakeDoc"
Cohesion: 0.17
Nodes (6): FakeDoc, aborts, commits, items, open, snapshot

### Community 99 - "ParamSet"
Cohesion: 0.07
Nodes (34): ModelParameter, angle, expression, input, label, name, owner, unit (+26 more)

### Community 100 - "BoundingBox"
Cohesion: 0.23
Nodes (14): BoundingBox, max, min, WallSide, Center, Side1, Side2, extendedWire() (+6 more)

### Community 101 - "QPointF"
Cohesion: 0.16
Nodes (5): PlaneEdges, arcs, curves, segments, vertices

### Community 102 - "Document::load"
Cohesion: 0.17
Nodes (5): doc_(), Document::Document(), Document::ocafBytes(), ocafApplication(), Document::load()

### Community 103 - "toDxf"
Cohesion: 0.43
Nodes (7): Point, x, y, z, customPlaneSpec(), planeFrame(), toDxf()

### Community 104 - "Placement"
Cohesion: 0.25
Nodes (7): Placement, angle, cx, cy, dx, dy, scale

### Community 106 - "Entity"
Cohesion: 0.18
Nodes (11): Entity, a, b, center, construction, fit, handles, included (+3 more)

### Community 107 - "ViewportAnalysis.cpp"
Cohesion: 0.15
Nodes (5): packed(), ramp(), shade(), Viewport::buildAnalysis(), f

### Community 108 - "Display"
Cohesion: 0.25
Nodes (7): Display, constraints, construction, dimensions, points, profiles, projected

### Community 110 - "Axis"
Cohesion: 0.50
Nodes (4): Axis, X, Y, Z

### Community 111 - "Known gaps"
Cohesion: 0.10
Nodes (15): Build, Conventions, Development, Tests, Reference parts, Fusion feature checklist, Roadmap, Contents (+7 more)

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

### Community 117 - ".redrawAll"
Cohesion: 0.12
Nodes (5): Viewport::setCurvatureComb(), Viewport::clearDragArrow(), Viewport::clearSecondArrow(), Viewport::setInteractor(), Viewport::clearTriad()

### Community 118 - "QDialog"
Cohesion: 0.14
Nodes (6): QDialog, MainWindow::editAppearance(), MainWindow::exportDesign(), MainWindow::measurePick(), MainWindow::openMeasure(), toolWindow()

### Community 119 - "UserParameter"
Cohesion: 0.33
Nodes (6): UserParameter, comment, expression, name, unit, value

### Community 120 - "Profile"
Cohesion: 0.33
Nodes (5): Profile, area, face, x, y

### Community 121 - "SelectionBox"
Cohesion: 0.18
Nodes (7): SelectionBox, crossing, Session::notifyChanged(), Rect, rect(), l, p

### Community 123 - "BooleanOp"
Cohesion: 0.50
Nodes (4): BooleanOp, Cut, Intersect, Join

### Community 124 - "MassProperties"
Cohesion: 0.50
Nodes (4): MassProperties, area, centerOfMass, volume

### Community 126 - "ThreadInfo"
Cohesion: 0.50
Nodes (4): ThreadInfo, diameter, internal, pitch

### Community 127 - "Value.h"
Cohesion: 0.22
Nodes (4): isEmpty(), Value, fail(), Failure

### Community 128 - "ChamferType"
Cohesion: 0.67
Nodes (3): ChamferType, DistanceAngle, TwoDistances

### Community 129 - "Inputs"
Cohesion: 0.09
Nodes (17): Inputs, Coil, def_, ConstructPlane, def_, kind_, Joint, asBuilt_ (+9 more)

### Community 130 - "Icons.h"
Cohesion: 0.19
Nodes (9): constraintIcon(), fallback(), filterIcon(), icon(), QAbstractButton, QAction, retintIcons(), setIcon() (+1 more)

### Community 132 - "cachedProfiles"
Cohesion: 0.20
Nodes (3): MainWindow::updateDragArrow(), cachedProfiles(), keyOf()

### Community 135 - "qs"
Cohesion: 0.22
Nodes (7): MainWindow::cancelSketch(), MainWindow::editSketch(), MainWindow::finishSketch(), MainWindow::sketchVisible(), MainWindow::startSketch(), MainWindow::updateProfilePicking(), qs()

### Community 140 - "ChainSegment"
Cohesion: 0.67
Nodes (3): ChainSegment, entity, forward

### Community 142 - "SplineHandle"
Cohesion: 0.25
Nodes (8): SplineHandle, arm, index, set, tx, ty, x, y

### Community 144 - "ConstructionPoint"
Cohesion: 0.33
Nodes (5): ConstructionPoint, name, point, Document::point(), Document::setPoint()

### Community 145 - "BodyFrame"
Cohesion: 0.13
Nodes (16): BodyFrame, diag, dx, dy, dz, x0, y0, z0 (+8 more)

### Community 147 - "EntityType"
Cohesion: 0.25
Nodes (8): EntityType, Arc, Circle, Ellipse, Line, Spline, isRound(), entityTypeName()

### Community 148 - "Architecture"
Cohesion: 0.40
Nodes (4): Architecture, How a command works, The document, Units

### Community 150 - "HandleHit"
Cohesion: 0.40
Nodes (4): HandleHit, back, index, spline

### Community 154 - "ellipseIcon"
Cohesion: 0.67
Nodes (3): ellipseIcon(), patternIcon(), save()

## Knowledge Gaps
- **813 isolated node(s):** `ok`, `output`, `error`, `isReal`, `real` (+808 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 1573 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **29 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `optional` connect `optional` to `Viewport`, `MainWindow`, `SketchEditor`, `Kernel.cpp`, `.eventFilter`, `ConstructionPoint`, `Io.cpp`, `Parser`, `InputDef`, `SketchEditor.cpp`, `CommandDialog.cpp`, `ViewportSketch.cpp`, `DocCommands.cpp`, `sketchFor`, `SketchOps.cpp`, `Constraint`, `SketchGeometry.cpp`, `AnalysisSettings`, `Document.cpp`, `CommandDialog.cpp`, `Session`, `Unit`, `Feature`, `ViewportArrow.cpp`, `Vec3`, `CommandDialog::CommandDialog`, `SketchCurves.cpp`, `ReplayStep`, `MainWindowArrow.cpp`, `ParamSet`?**
  _High betweenness centrality (0.128) - this node is a cross-community bridge._
- **What connects `ok`, `output`, `error` to the rest of the system?**
  _813 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Viewport` be split into smaller, more focused modules?**
  _Cohesion score 0.014071381977448514 - nodes in this community are weakly interconnected._
- **Why does `Viewport` connect `Viewport` to `.rebuild`, `SelectionBox`, `Unit`, `MainWindow`, `Viewport.cpp`, `ViewportArrow.cpp`, `optional`, `ViewportAnalysis.cpp`, `AnalysisSettings`, `AnalysisSettings`, `SketchDisplay`, `Viewport::setDragArrow`, `SketchCurves.cpp`, `.toPixels`, `.redrawAll`, `ViewportSketch.cpp`, `.openMarkingMenu`, `QTimer`?**
  _High betweenness centrality (0.119) - this node is a cross-community bridge._
- **Should `QPainter` be split into smaller, more focused modules?**
  _Cohesion score 0.08635703918722787 - nodes in this community are weakly interconnected._
- **Why does `MainWindow` connect `MainWindow` to `cachedProfiles`, `MainWindow::buildUiCommands`, `qs`, `optional`, `.eventFilter`, `SketchPalette`, `ParameterCompleter`, `src/main.cpp`, `.showDialog`, `MainWindow.cpp`, `.openMarkingMenu`, `Session`, `Unit`, `ParametersDialog.cpp`, `UiCommand`, `MainWindow::MainWindow`, `MainWindowTools.cpp`, `main`, `SectionState`, `QDialog`?**
  _High betweenness centrality (0.093) - this node is a cross-community bridge._
- **Should `Session.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.12692307692307692 - nodes in this community are weakly interconnected._