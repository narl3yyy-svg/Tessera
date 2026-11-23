# Graph Report - tessera  (2026-11-22)

## Corpus Check
- 446 files · ~290,925 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 80 file(s) not represented in the graph (top: .drive 72, (none) 5, .cmake 1)

## Summary
- 4071 nodes · 10494 edges · 146 communities (112 shown, 34 thin omitted)
- Extraction: 85% EXTRACTED · 15% INFERRED · 0% AMBIGUOUS · INFERRED: 1592 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `598b201b`
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
- Document.cpp
- optional
- Kernel.cpp
- AnalysisSettings
- Kind
- QMouseEvent
- CommandDialog
- Io.cpp
- Parser
- InputDef
- SketchEditor.cpp
- PhysicalMaterial
- TEST
- Affine
- ViewportSketch.cpp
- SketchPalette
- CommandError
- .apply
- CommandContext
- Colors
- KernelError
- SketchOps.cpp
- .openMarkingMenu
- ParameterCompleter
- Constraint
- SketchGeometry.cpp
- src/main.cpp
- string
- Column
- BoundaryCell
- ConstraintType
- AdskModule.cpp
- Entity
- TopologyCounts
- Zip.cpp
- AnalysisSettings
- Sketch
- ParamSet
- .showDialog
- string
- .updatePreview
- .toPixels
- Snap
- Document::recompute
- MainWindow.cpp
- TEST
- .mouseMove
- xdrive.py
- adsk_core
- CommandDialog.cpp
- Session
- Theme.cpp
- BodyFrame
- CommandRegistry
- SketchPalette.cpp
- Unit
- Theme
- Feature
- InputType
- ParametersDialog.cpp
- MainWindowSketch.cpp
- ViewportArrow.cpp
- qs
- MetricSize
- Vec3
- CommandDialog::CommandDialog
- math
- CommandDialog::CommandDialog
- SketchDisplay
- Kind
- Measurement
- SketchCurves.cpp
- fail
- Level
- Inputs
- UiCommand
- test_feature_pattern.py
- MainWindow::MainWindow
- MainWindowTools.cpp
- Expression.cpp
- FileFormat
- Known differences still to build
- ReplayStep
- cachedProfiles
- MainWindowArrow.cpp
- FakeDoc
- ModelParameter
- BoundingBox
- QPointF
- Document::load
- SketchRecord
- test_rigid_group.py
- main
- toDxf
- Display
- Axis
- Known gaps
- .eventFilter
- SectionState
- uninstall.sh
- install.sh
- TestFramework.h
- .redrawAll
- EntityType
- UserParameter
- Viewport.h
- test_extrude_participants.py
- test_incremental_replay.py
- BooleanOp
- MassProperties
- QScrollArea
- ThreadInfo
- Value.h
- ChamferType
- Joint
- Icons.h
- Profile
- Architecture
- LAB_NOTES.md
- Loft
- .frame
- build.sh
- live-test.sh
- PYBIND11_EMBEDDED_MODULE
- Tool
- SplineHandle
- BodyFrame
- BRepBody

## God Nodes (most connected - your core abstractions)
1. `Viewport` - 290 edges
2. `SketchEditor` - 198 edges
3. `MainWindow` - 189 edges
4. `Inputs` - 175 edges
5. `render()` - 128 edges
6. `CommandContext` - 128 edges
7. `Document` - 124 edges
8. `CommandDialog` - 106 edges
9. `CommandError` - 77 edges
10. `Command` - 72 edges

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

## Communities (146 total, 34 thin omitted)

### Community 0 - "Viewport"
Cohesion: 0.01
Nodes (81): view_, QLineEdit, Viewport, analysis_, analysisObjects_, appliedGridStep_, arrowBoxes_, arrowDragging_ (+73 more)

### Community 1 - "Icons.cpp"
Cohesion: 0.05
Nodes (133): accessibilityIcon(), alignIcon(), appearanceIcon(), arc3Icon(), arcIcon(), arcTangentIcon(), arrow(), axisIcon() (+125 more)

### Community 2 - "Session.cpp"
Cohesion: 0.06
Nodes (51): CommandSession, inputs_, expressionKey(), checkInputValue(), CommandContext::evaluateExpression(), CommandDef::input(), CommandSession::applyInTransaction(), CommandSession::cancel() (+43 more)

### Community 4 - "MainWindow"
Cohesion: 0.03
Nodes (66): CommandDialog, MainWindow, active_, appearanceColour_, appearanceFaces_, appearancePanel_, arrowInput_, arrowInput2_ (+58 more)

### Community 5 - "run_oracle.py"
Cohesion: 0.08
Nodes (54): add_point(), arc_poly(), body_at(), body_list(), build_sketch(), chain(), circumcentre(), cm() (+46 more)

### Community 6 - "DocCommands.cpp"
Cohesion: 0.07
Nodes (45): getBool(), getReal(), Align::apply(), axisOf(), bodyCentre(), bodyName(), boundaryFillCells(), Combine (+37 more)

### Community 7 - "Document"
Cohesion: 0.03
Nodes (15): Document, effects_, lastReplayed_, lastReused_, modified_, pendingTools_, registry_, replaying_ (+7 more)

### Community 8 - "Viewport.cpp"
Cohesion: 0.04
Nodes (19): glide(), hiddenColour(), keys(), qc(), QKeyEvent, QtFrameBuffer, rgb(), SelectionBox (+11 more)

### Community 9 - "SketchEditor"
Cohesion: 0.03
Nodes (53): HandleHit, back, index, spline, SketchEditor, arcDrag_, arcDragMoved_, arcEndsChain_ (+45 more)

### Community 10 - "Document.cpp"
Cohesion: 0.07
Nodes (37): DocumentError, checkViewName(), Document::abortTransaction(), Document::addBody(), Document::addNamedView(), Document::addUserParameter(), Document::commitTransaction(), Document::historyMarker() (+29 more)

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
Cohesion: 0.06
Nodes (29): ConstructPlane, def_, kind_, EdgeFeature, def_, kind_, Kind, Angle (+21 more)

### Community 15 - "QMouseEvent"
Cohesion: 0.13
Nodes (8): MarkingMenu::mouseMoveEvent(), QMouseEvent, ViewInteractor, Viewport::setTriad(), Viewport::setTriadActive(), Viewport::triadMouseMove(), Viewport::triadMousePress(), Viewport::triadMouseRelease()

### Community 16 - "CommandDialog"
Cohesion: 0.04
Nodes (41): CommandDialog, axisInputs_, axisPicks_, bodiesId_, bodiesLabel_, bodyInput_, buttons_, cellsId_ (+33 more)

### Community 17 - "Io.cpp"
Cohesion: 0.10
Nodes (19): NamedShape, compoundOf(), exportShapes(), fmt(), formatForPath(), fromBrep(), importShape(), lower() (+11 more)

### Community 18 - "Parser"
Cohesion: 0.18
Nodes (15): Quantity, angle, length, value, describe(), isIdentChar(), isIdentStart(), Parser (+7 more)

### Community 19 - "InputDef"
Cohesion: 0.08
Nodes (22): InputDef, choices, defaultValue, id, label, max, min, minExclusive (+14 more)

### Community 21 - "PhysicalMaterial"
Cohesion: 0.22
Nodes (13): PhysicalMaterial, color, density, name, checkMaterial(), Document::designMaterials(), Document::material(), Document::setBodyMaterial() (+5 more)

### Community 22 - "TEST"
Cohesion: 0.06
Nodes (12): Sketch, constraints, entities, points, texts, Sketch::addCircle(), Sketch::addConic(), Sketch::addEllipticalArc() (+4 more)

### Community 24 - "Affine"
Cohesion: 0.14
Nodes (13): SketchError, Affine, a, d, e, Builder, byPlace_, k_ (+5 more)

### Community 25 - "ViewportSketch.cpp"
Cohesion: 0.08
Nodes (6): faceStyle(), lineStyle(), rgb(), Viewport::lookAt(), Viewport::planePoint(), Viewport::toWidget()

### Community 26 - "SketchPalette"
Cohesion: 0.07
Nodes (23): QLabel, QToolButton, QWidget, SketchEditor, SketchPalette, body_, constraints_, construction_ (+15 more)

### Community 27 - "CommandError"
Cohesion: 0.10
Nodes (22): CommandError, applyOperation(), applyToParticipants(), ConstructAxisPoint, def_, kind_, evaluateDimensions(), Extrude (+14 more)

### Community 28 - ".apply"
Cohesion: 0.29
Nodes (5): Coil, def_, Pipe, def_, sectionOf()

### Community 29 - "CommandContext"
Cohesion: 0.04
Nodes (54): Adding a tool, Command, CommandDef, feature, icon, id, inputs, name (+46 more)

### Community 30 - "Colors"
Cohesion: 0.07
Nodes (28): Colors, base, border, cubeBox, cubeText, errorBackground, grid, gridMajor (+20 more)

### Community 31 - "KernelError"
Cohesion: 0.23
Nodes (35): KernelError, asSolid(), boolean(), boundaryCells(), chamfer(), chamferEx(), deleteFaces(), draft() (+27 more)

### Community 32 - "SketchOps.cpp"
Cohesion: 0.06
Nodes (54): ChainSegment, entity, forward, Placement, angle, cx, cy, dx (+46 more)

### Community 33 - ".openMarkingMenu"
Cohesion: 0.08
Nodes (6): MainWindow::beginSketch(), MainWindow::buildSketchTab(), MainWindow::enterSketchMode(), MainWindow::buildUiCommands(), QTimer, Viewport::selectArrowValue()

### Community 34 - "ParameterCompleter"
Cohesion: 0.13
Nodes (8): ParameterCompleter, completer_, edit_, names_, ParameterCompleter::ParameterCompleter(), public, QCompleter, QLineEdit

### Community 35 - "Constraint"
Cohesion: 0.08
Nodes (20): Constraint, driven, entities, expression, hasLabel, labelX, labelY, name (+12 more)

### Community 36 - "SketchGeometry.cpp"
Cohesion: 0.07
Nodes (19): conditionedSpline(), curve(), curves(), entityCurves(), G2End, d1, d2, set (+11 more)

### Community 37 - "src/main.cpp"
Cohesion: 0.07
Nodes (5): grabWindowWithPanels(), writeLiveGeometry(), MarkingMenu, enabled, public

### Community 38 - "string"
Cohesion: 0.11
Nodes (19): bodyNumber(), Document::axisFrame(), Document::bodyShapes(), Document::componentOfBody(), Document::effectOf(), Document::evaluate(), Document::feature(), Document::featureValueParameters() (+11 more)

### Community 39 - "Column"
Cohesion: 0.25
Nodes (8): Column, kComment, kExpression, kName, kParameter, kStar, kUnit, kValue

### Community 40 - "BoundaryCell"
Cohesion: 0.29
Nodes (4): BoundaryCell, ref, shape, volume

### Community 41 - "ConstraintType"
Cohesion: 0.07
Nodes (26): ConstraintType, Angle, Coincident, Collinear, Concentric, Curvature, Diameter, Distance (+18 more)

### Community 42 - "AdskModule.cpp"
Cohesion: 0.12
Nodes (13): Application, BRepBodies, Component, Design, Product, raiseIfError(), UserParameter, name (+5 more)

### Community 43 - "Entity"
Cohesion: 0.08
Nodes (20): Entity, a, b, center, construction, fit, handles, included (+12 more)

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
Nodes (18): SplineKind, Conic, Control, Fit, entityTypeName(), isDimension(), Sketch::addConstraint(), Sketch::addSpline() (+10 more)

### Community 49 - "ParamSet"
Cohesion: 0.08
Nodes (39): ConstructionPlane, name, spec, NamedView, eye, name, size, target (+31 more)

### Community 50 - ".showDialog"
Cohesion: 0.11
Nodes (5): MainWindow::onEdgeClicked(), MainWindow::onProfileClicked(), MainWindow::originalShape(), MainWindow::syncPickedShapes(), MainWindow::toOriginal()

### Community 51 - "string"
Cohesion: 0.15
Nodes (7): AddUserParameter, def_, isIdentifier(), NewComponent, def_, RigidGroup, def_

### Community 54 - "Snap"
Cohesion: 0.06
Nodes (33): Pick, bodyArc, bodyPoint, bodySegment, hit, midpointOf, onEntity, onXAxis (+25 more)

### Community 55 - "Document::recompute"
Cohesion: 0.22
Nodes (6): Document::expressionEnv(), Document::openTransaction(), Document::recompute(), Document::recordFeature(), Document::setFeatureInputs(), toJson()

### Community 58 - ".mouseMove"
Cohesion: 0.14
Nodes (7): ext(), fixedColor(), freeColor(), lineEntity(), qc(), rgb(), wire()

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

### Community 67 - "Unit"
Cohesion: 0.11
Nodes (28): bindAdsk(), MainWindow::checkInterference(), MainWindow::driveJoints(), MainWindow::formatLength(), MainWindow::gridSettings(), MainWindow::lengthUnit(), MainWindow::openAnalysis(), MainWindow::openSection() (+20 more)

### Community 68 - "Theme"
Cohesion: 0.22
Nodes (4): Theme, colors_, public, styled_

### Community 69 - "Feature"
Cohesion: 0.17
Nodes (10): Feature, commandId, error, id, inputs, name, parameterNames, rolledBack (+2 more)

### Community 70 - "InputType"
Cohesion: 0.08
Nodes (21): bindTsr(), fromPy(), toPy(), typeName(), InputType, Axis, Bodies, Body (+13 more)

### Community 71 - "ParametersDialog.cpp"
Cohesion: 0.07
Nodes (16): number(), ParametersDialog, building_, error_, filter_, listener_, ParametersDialog::ParametersDialog(), public (+8 more)

### Community 72 - "MainWindowSketch.cpp"
Cohesion: 0.07
Nodes (11): MainWindow::cancelSketch(), MainWindow::editSketch(), MainWindow::finishSketch(), MainWindow::sketchPalette(), MainWindow::sketchVisible(), MainWindow::startSketch(), MainWindow::updateProfilePicking(), qs() (+3 more)

### Community 73 - "ViewportArrow.cpp"
Cohesion: 0.05
Nodes (30): Viewport::frontEdgeOwner(), rgb(), segmentDistance(), Viewport::arrowAt(), Viewport::arrowMouseMove(), Viewport::arrowMousePress(), Viewport::arrowMouseRelease(), Viewport::arrowParam() (+22 more)

### Community 74 - "qs"
Cohesion: 0.25
Nodes (3): commandIcon(), qs(), MainWindow::applySection()

### Community 75 - "MetricSize"
Cohesion: 0.15
Nodes (10): MarkingMenu::keyPressEvent(), MarkingMenu::MarkingMenu(), MarkingMenu::run(), MetricSize, close, d, loose, name (+2 more)

### Community 76 - "Vec3"
Cohesion: 0.17
Nodes (22): SurfacePoint, normal, point, Vec3, containsPoint(), edgeMidpoint(), edgesNear(), extrudeToFace() (+14 more)

### Community 77 - "CommandDialog::CommandDialog"
Cohesion: 0.13
Nodes (7): CommandDialog::CommandDialog(), formatNumber(), Dimension, Angle, Length, Unitless, dimensionOf()

### Community 78 - "math"
Cohesion: 0.04
Nodes (3): dist(), check_regular(), dist_to_line()

### Community 79 - "CommandDialog::CommandDialog"
Cohesion: 0.16
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

### Community 85 - "Level"
Cohesion: 0.16
Nodes (13): debug(), error(), info(), Level, Debug, Error, Info, Warning (+5 more)

### Community 86 - "Inputs"
Cohesion: 0.06
Nodes (21): CommandContext, Inputs, CommandSession::CommandSession(), getInt(), checkBody(), checkPattern(), CircularPattern, def_ (+13 more)

### Community 87 - "UiCommand"
Cohesion: 0.13
Nodes (12): UiCommand, enabled, icon, id, name, panel, run, shortcut (+4 more)

### Community 89 - "MainWindow::MainWindow"
Cohesion: 0.13
Nodes (4): PythonHost, MainWindow::MainWindow(), MainWindow::exitSketchMode(), MainWindow::showPreferences()

### Community 90 - "MainWindowTools.cpp"
Cohesion: 0.05
Nodes (21): QObject, QDialog, editMaterialDialog(), MainWindow::chooseUnits(), MainWindow::editAppearance(), MainWindow::editMaterial(), MainWindow::exportDesign(), MainWindow::insertFile() (+13 more)

### Community 91 - "Expression.cpp"
Cohesion: 0.13
Nodes (15): ExpressionEnv, lengthUnit, lookup, ExpressionError, evaluateExpression(), evaluateQuantity(), expressionReferences(), isConstantName() (+7 more)

### Community 92 - "FileFormat"
Cohesion: 0.17
Nodes (12): FileFormat, Brep, Iges, Obj, Step, Stl, ThreeMF, FormatInfo (+4 more)

### Community 93 - "Known differences still to build"
Cohesion: 0.15
Nodes (12): Data and files, Findings from the videos, Fusion study list, Interface, Known differences still to build, Navigation and display, Selection and the canvas, Sketch (+4 more)

### Community 95 - "ReplayStep"
Cohesion: 0.05
Nodes (37): MainWindow::paintBody(), Body, color, display, faceColors, material, name, shape (+29 more)

### Community 96 - "cachedProfiles"
Cohesion: 0.20
Nodes (3): MainWindow::updateDragArrow(), cachedProfiles(), keyOf()

### Community 97 - "MainWindowArrow.cpp"
Cohesion: 0.08
Nodes (13): ArrowPlacement, base, dir, edgePlacement(), facesPlacement(), MainWindow::attachArrowCompleters(), MainWindow::patternCentre(), MainWindow::pickedFaces() (+5 more)

### Community 98 - "FakeDoc"
Cohesion: 0.17
Nodes (6): FakeDoc, aborts, commits, items, open, snapshot

### Community 99 - "ModelParameter"
Cohesion: 0.13
Nodes (13): ModelParameter, angle, expression, input, label, name, owner, unit (+5 more)

### Community 100 - "BoundingBox"
Cohesion: 0.23
Nodes (14): BoundingBox, max, min, WallSide, Center, Side1, Side2, extendedWire() (+6 more)

### Community 101 - "QPointF"
Cohesion: 0.12
Nodes (5): PlaneEdges, arcs, curves, segments, vertices

### Community 102 - "Document::load"
Cohesion: 0.17
Nodes (5): doc_(), Document::Document(), Document::ocafBytes(), ocafApplication(), Document::load()

### Community 104 - "SketchRecord"
Cohesion: 0.17
Nodes (9): SketchRecord, data, name, offset, plane, Document::replayContext(), Document::setSketch(), Document::sketch() (+1 more)

### Community 106 - "main"
Cohesion: 0.31
Nodes (5): listCommands(), main(), usage(), main(), smoke()

### Community 107 - "toDxf"
Cohesion: 0.43
Nodes (7): Point, x, y, z, customPlaneSpec(), planeFrame(), toDxf()

### Community 108 - "Display"
Cohesion: 0.25
Nodes (7): Display, constraints, construction, dimensions, points, profiles, projected

### Community 110 - "Axis"
Cohesion: 0.50
Nodes (4): Axis, X, Y, Z

### Community 111 - "Known gaps"
Cohesion: 0.05
Nodes (36): Build, Conventions, Development, Tests, 3D Sketch, Align, Appearance, Boundary Fill (+28 more)

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
Cohesion: 0.16
Nodes (11): Result, error, ok, output, captured(), PythonHost::exec(), PythonHost::runScript(), Case (+3 more)

### Community 117 - ".redrawAll"
Cohesion: 0.09
Nodes (9): NavPreset, Fusion, SolidWorks, Tinkercad, Viewport::setCurvatureComb(), Viewport::clearDragArrow(), Viewport::clearSecondArrow(), Viewport::setInteractor() (+1 more)

### Community 118 - "EntityType"
Cohesion: 0.29
Nodes (7): EntityType, Arc, Circle, Ellipse, Line, Spline, isRound()

### Community 119 - "UserParameter"
Cohesion: 0.33
Nodes (6): UserParameter, comment, expression, name, unit, value

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
Cohesion: 0.36
Nodes (3): Joint, asBuilt_, def_

### Community 131 - "Profile"
Cohesion: 0.33
Nodes (5): Profile, area, face, x, y

### Community 132 - "Architecture"
Cohesion: 0.40
Nodes (4): Architecture, How a command works, The document, Units

### Community 141 - "Tool"
Cohesion: 0.16
Nodes (6): SketchEditor::SketchEditor(), edges, Tool, op, shape, target

### Community 142 - "SplineHandle"
Cohesion: 0.25
Nodes (8): SplineHandle, arm, index, set, tx, ty, x, y

### Community 145 - "BodyFrame"
Cohesion: 0.13
Nodes (16): BodyFrame, diag, dx, dy, dz, x0, y0, z0 (+8 more)

## Knowledge Gaps
- **818 isolated node(s):** `ok`, `output`, `error`, `isReal`, `real` (+813 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 1590 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **34 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `optional` connect `optional` to `Viewport`, `MainWindow`, `DocCommands.cpp`, `SketchEditor`, `Kernel.cpp`, `Io.cpp`, `Parser`, `InputDef`, `SketchEditor.cpp`, `PhysicalMaterial`, `ViewportSketch.cpp`, `SketchOps.cpp`, `Constraint`, `SketchGeometry.cpp`, `string`, `Entity`, `AnalysisSettings`, `ParamSet`, `Snap`, `CommandDialog.cpp`, `Session`, `Unit`, `Feature`, `ViewportArrow.cpp`, `Vec3`, `CommandDialog::CommandDialog`, `CommandDialog::CommandDialog`, `SketchCurves.cpp`, `Inputs`, `MainWindowTools.cpp`, `Expression.cpp`, `ReplayStep`, `MainWindowArrow.cpp`, `QPointF`, `SketchRecord`, `Viewport.h`?**
  _High betweenness centrality (0.150) - this node is a cross-community bridge._
- **What connects `ok`, `output`, `error` to the rest of the system?**
  _818 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Viewport` be split into smaller, more focused modules?**
  _Cohesion score 0.01348221670802316 - nodes in this community are weakly interconnected._
- **Why does `Viewport` connect `Viewport` to `.openMarkingMenu`, `MainWindowArrow.cpp`, `Unit`, `MainWindow`, `Viewport.cpp`, `ViewportArrow.cpp`, `optional`, `AnalysisSettings`, `AnalysisSettings`, `SketchDisplay`, `QMouseEvent`, `SketchCurves.cpp`, `.redrawAll`, `.toPixels`, `TEST`, `Viewport.h`, `QTimer`?**
  _High betweenness centrality (0.146) - this node is a cross-community bridge._
- **Should `Icons.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.0507964257964258 - nodes in this community are weakly interconnected._
- **Why does `SketchEditor` connect `SketchEditor` to `Viewport`, `Constraint`, `.mouseMove`, `QPointF`, `Unit`, `optional`, `Display`, `Entity`, `Tool`, `QMouseEvent`, `.eventFilter`, `Kind`, `SketchEditor.cpp`, `.updatePreview`, `Snap`, `MainWindowTools.cpp`, `Session`?**
  _High betweenness centrality (0.124) - this node is a cross-community bridge._
- **Should `Session.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.055855855855855854 - nodes in this community are weakly interconnected._