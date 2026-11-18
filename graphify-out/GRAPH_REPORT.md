# Graph Report - tessera  (2026-11-17)

## Corpus Check
- 432 files · ~284,487 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 75 file(s) not represented in the graph (top: .drive 67, (none) 5, .cmake 1)

## Summary
- 3999 nodes · 10284 edges · 136 communities (112 shown, 24 thin omitted)
- Extraction: 85% EXTRACTED · 15% INFERRED · 0% AMBIGUOUS · INFERRED: 1570 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `188a9958`
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
- Unit
- sketchFor
- Entity
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
- TEST
- MainWindow.cpp
- solve
- MainWindow::MainWindow
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
- InputDef
- SketchEditor.cpp
- .toPixels
- Snap
- Document::recompute
- qs
- TEST
- ConstructionPoint
- xdrive.py
- adsk_core
- CommandDialog.cpp
- Session
- Theme.cpp
- BodyFrame
- CommandRegistry
- MetricSize
- dimensionOf
- Theme
- Feature
- InputType
- ParametersDialog.cpp
- MainWindowSketch.cpp
- ViewportArrow.cpp
- .add
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
- README.md
- test_feature_pattern.py
- Development
- QDialog
- extrudeToFace
- FileFormat
- Known differences still to build
- ReplayStep
- main
- src/main.cpp
- FakeDoc
- ParamSet
- WallSide
- fail
- Document::load
- toDxf
- Placement
- test_rigid_group.py
- QObject
- Joints
- Axis
- Known gaps
- .redrawAll
- SectionState
- uninstall.sh
- install.sh
- TestFramework.h
- SelectionBox
- test_incremental_replay.py
- BooleanOp
- MassProperties
- QScrollArea
- ThreadInfo
- ChamferType
- Joint
- Column
- LAB_NOTES.md
- build.sh
- live-test.sh
- PYBIND11_EMBEDDED_MODULE
- ChainSegment
- Placement::apply
- SplineHandle
- BodyFrame
- EntityType
- Architecture

## God Nodes (most connected - your core abstractions)
1. `Viewport` - 286 edges
2. `SketchEditor` - 198 edges
3. `MainWindow` - 189 edges
4. `Inputs` - 164 edges
5. `render()` - 125 edges
6. `Document` - 122 edges
7. `CommandContext` - 119 edges
8. `CommandDialog` - 101 edges
9. `CommandError` - 72 edges
10. `Command` - 69 edges

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

## Communities (136 total, 24 thin omitted)

### Community 0 - "Viewport"
Cohesion: 0.01
Nodes (79): view_, QLineEdit, Viewport, analysis_, analysisObjects_, appliedGridStep_, arrowBoxes_, arrowDragging_ (+71 more)

### Community 1 - "Icons.cpp"
Cohesion: 0.05
Nodes (130): accessibilityIcon(), appearanceIcon(), arc3Icon(), arcIcon(), arcTangentIcon(), arrow(), axisIcon(), boundaryFillIcon() (+122 more)

### Community 2 - "Session.cpp"
Cohesion: 0.06
Nodes (51): CommandSession, inputs_, expressionKey(), checkInputValue(), CommandContext::evaluateExpression(), CommandDef::input(), CommandSession::applyInTransaction(), CommandSession::cancel() (+43 more)

### Community 4 - "MainWindow"
Cohesion: 0.02
Nodes (69): CommandDialog, MainWindow, active_, appearanceColour_, appearanceFaces_, appearancePanel_, arrowInput_, arrowInput2_ (+61 more)

### Community 5 - "run_oracle.py"
Cohesion: 0.08
Nodes (54): add_point(), arc_poly(), body_at(), body_list(), build_sketch(), chain(), circumcentre(), cm() (+46 more)

### Community 6 - "CommandError"
Cohesion: 0.13
Nodes (23): CommandError, getBool(), getInt(), getReal(), applyToParticipants(), bodyCentre(), bodyName(), boundaryFillCells() (+15 more)

### Community 7 - "Document"
Cohesion: 0.03
Nodes (15): Document, effects_, lastReplayed_, lastReused_, modified_, pendingTools_, registry_, replaying_ (+7 more)

### Community 8 - "Viewport.cpp"
Cohesion: 0.05
Nodes (5): glide(), keys(), QKeyEvent, QtFrameBuffer, Viewport::Viewport()

### Community 9 - "SketchEditor"
Cohesion: 0.03
Nodes (60): Display, constraints, construction, dimensions, points, profiles, projected, HandleHit (+52 more)

### Community 10 - "DocumentError"
Cohesion: 0.10
Nodes (26): DocumentError, checkViewName(), Document::abortTransaction(), Document::addNamedView(), Document::addUserParameter(), Document::commitTransaction(), Document::openTransaction(), Document::removeBody() (+18 more)

### Community 11 - "optional"
Cohesion: 0.08
Nodes (11): optional, isEmpty(), Value, CommandRegistry::all(), Document, UserParameter, comment, expression (+3 more)

### Community 12 - "Kernel.cpp"
Cohesion: 0.03
Nodes (4): isoCoarsePitch(), topologyCounts(), touching(), wrapOntoCylinder()

### Community 13 - "Viewport.h"
Cohesion: 0.05
Nodes (24): AnalysisKind, Accessibility, CurvatureMap, Draft, Isocurve, MinimumRadius, None, Zebra (+16 more)

### Community 14 - "Kind"
Cohesion: 0.06
Nodes (32): ConstructPlane, def_, kind_, EdgeFeature, def_, kind_, FaceFeature, def_ (+24 more)

### Community 15 - "Viewport::setDragArrow"
Cohesion: 0.18
Nodes (4): Viewport::DragArrow::handle(), Viewport::emitArrow(), Viewport::setDragArrow(), Viewport::setDragRing()

### Community 16 - "CommandDialog"
Cohesion: 0.04
Nodes (39): CommandDialog, bodiesId_, bodiesLabel_, bodyInput_, buttons_, cellsId_, cellsList_, cmd_ (+31 more)

### Community 17 - "Io.cpp"
Cohesion: 0.10
Nodes (19): MainWindow::print3d(), NamedShape, compoundOf(), exportShapes(), fmt(), formatForPath(), fromBrep(), importShape() (+11 more)

### Community 18 - "Unit"
Cohesion: 0.07
Nodes (45): MainWindow::lengthUnit(), ExpressionEnv, lengthUnit, lookup, ExpressionError, Quantity, angle, length (+37 more)

### Community 19 - "sketchFor"
Cohesion: 0.10
Nodes (18): applyOperation(), Coil, def_, Emboss, def_, Extrude, def_, pickedFaces() (+10 more)

### Community 20 - "Entity"
Cohesion: 0.09
Nodes (11): Entity, a, b, center, construction, fit, handles, included (+3 more)

### Community 21 - "Document"
Cohesion: 0.21
Nodes (8): ConstructAxisPoint, def_, kind_, jointOrigin(), JointPick, frame, planeOf(), revolveAxis()

### Community 22 - "TEST"
Cohesion: 0.06
Nodes (25): Sketch, constraints, entities, points, texts, SolveResult, dof, entityFixed (+17 more)

### Community 24 - "Affine"
Cohesion: 0.13
Nodes (13): Affine, a, b, d, e, Builder, byPlace_, k_ (+5 more)

### Community 25 - "ViewportSketch.cpp"
Cohesion: 0.08
Nodes (6): faceStyle(), lineStyle(), rgb(), Viewport::lookAt(), Viewport::planePoint(), Viewport::toWidget()

### Community 26 - "SketchPalette"
Cohesion: 0.06
Nodes (25): QCheckBox, QLabel, QToolButton, QWidget, SketchEditor, SketchPalette, body_, constraints_ (+17 more)

### Community 27 - "DocCommands.cpp"
Cohesion: 0.14
Nodes (19): axisOf(), evaluateDimensions(), HoleSize, modeled, pitch, radius, makeBox(), makeCone() (+11 more)

### Community 28 - "Inputs"
Cohesion: 0.06
Nodes (19): CommandContext, Inputs, CommandSession::CommandSession(), checkBody(), checkPattern(), defaultBody(), Hole, def_ (+11 more)

### Community 29 - "Command"
Cohesion: 0.04
Nodes (61): Adding a tool, Command, CommandDef, feature, icon, id, inputs, name (+53 more)

### Community 30 - "Colors"
Cohesion: 0.07
Nodes (28): Colors, base, border, cubeBox, cubeText, errorBackground, grid, gridMajor (+20 more)

### Community 31 - "KernelError"
Cohesion: 0.19
Nodes (42): BoundingBox, max, min, KernelError, asSolid(), boolean(), boundaryCells(), chamfer() (+34 more)

### Community 32 - "SketchOps.cpp"
Cohesion: 0.25
Nodes (24): at(), chainOf(), chamferCorner(), circularPattern(), copyEntities(), cross(), dot(), extendLine() (+16 more)

### Community 33 - ".rebuild"
Cohesion: 0.10
Nodes (12): hiddenColour(), qc(), rgb(), sharpEdges(), Style, Shaded, ShadedEdges, ShadedHidden (+4 more)

### Community 34 - "ParameterCompleter"
Cohesion: 0.13
Nodes (8): ParameterCompleter, completer_, edit_, names_, ParameterCompleter::ParameterCompleter(), public, QCompleter, QLineEdit

### Community 35 - "TEST"
Cohesion: 0.09
Nodes (3): param(), TEST(), tmp()

### Community 37 - "MainWindow.cpp"
Cohesion: 0.05
Nodes (6): grabWindowWithPanels(), writeLiveGeometry(), flatButton(), MarkingMenu, enabled, public

### Community 38 - "solve"
Cohesion: 0.18
Nodes (12): addConstraintChecked(), Layout, n, px, py, rad, makeLayout(), pack() (+4 more)

### Community 39 - "MainWindow::MainWindow"
Cohesion: 0.10
Nodes (7): PythonHost, MainWindow::MainWindow(), MainWindow::enterSketchMode(), MainWindow::editAppearance(), MainWindow::showPreferences(), QTimer, Viewport::selectArrowValue()

### Community 40 - "curve"
Cohesion: 0.16
Nodes (19): conditionedSpline(), curve(), curves(), entityCurves(), G2End, d1, d2, set (+11 more)

### Community 41 - "ConstraintType"
Cohesion: 0.09
Nodes (23): ConstraintType, Angle, Coincident, Collinear, Concentric, Curvature, Diameter, Distance (+15 more)

### Community 42 - "AdskModule.cpp"
Cohesion: 0.09
Nodes (16): Application, bindAdsk(), BRepBodies, BRepBody, index, Component, Design, Product (+8 more)

### Community 43 - "Pick"
Cohesion: 0.07
Nodes (21): Pick, bodyArc, bodyPoint, bodySegment, hit, midpointOf, onEntity, onXAxis (+13 more)

### Community 45 - "TopologyCounts"
Cohesion: 0.14
Nodes (20): Section, Circular, Square, Triangular, TopologyCounts, edges, faces, shells (+12 more)

### Community 46 - "Zip.cpp"
Cohesion: 0.17
Nodes (13): Entry, data, name, ZipError, crc32(), deflateRaw(), get16(), get32() (+5 more)

### Community 47 - "AnalysisSettings"
Cohesion: 0.08
Nodes (20): DragArrow, base, dir, radius, ref, ring, value, PendingLook (+12 more)

### Community 48 - "Sketch"
Cohesion: 0.07
Nodes (25): SketchError, SplineKind, Conic, Control, Fit, entityTypeName(), isDimension(), Sketch::addConic() (+17 more)

### Community 49 - "Document.cpp"
Cohesion: 0.06
Nodes (46): ConstructionPlane, name, spec, SketchRecord, data, name, offset, plane (+38 more)

### Community 51 - "InputDef"
Cohesion: 0.08
Nodes (22): InputDef, choices, defaultValue, id, label, max, min, minExclusive (+14 more)

### Community 52 - "SketchEditor.cpp"
Cohesion: 0.10
Nodes (5): angleInArc(), ccwContains(), circumcircle(), lineEntity(), segDistance()

### Community 54 - "Snap"
Cohesion: 0.11
Nodes (18): Snap, alignX, alignY, bodyArc, bodySegment, entity, fromX, fromY (+10 more)

### Community 55 - "Document::recompute"
Cohesion: 0.18
Nodes (8): Document::expressionEnv(), Document::recompute(), Document::recordFeature(), Document::removeFeature(), Document::setFeatureInputs(), Document::setFeatureSuppressed(), featureData(), toJson()

### Community 56 - "qs"
Cohesion: 0.08
Nodes (8): commandIcon(), qs(), MainWindow::beginSketch(), MainWindow::exitSketchMode(), MainWindow::onEdgeClicked(), MainWindow::applySection(), cachedProfiles(), keyOf()

### Community 58 - "ConstructionPoint"
Cohesion: 0.33
Nodes (5): ConstructionPoint, name, point, Document::point(), Document::setPoint()

### Community 59 - "xdrive.py"
Cohesion: 0.28
Nodes (15): button(), canvas(), click(), drag(), flush(), geometry(), key(), keycode() (+7 more)

### Community 62 - "Session"
Cohesion: 0.07
Nodes (7): PythonHost::PythonHost(), Session, commands_, doc_, listeners_, nextListener_, path_

### Community 63 - "Theme.cpp"
Cohesion: 0.23
Nodes (6): setIconTheme(), darkColors(), darkPalette(), darkStyleSheet(), lightColors(), lightStyleSheet()

### Community 64 - "BodyFrame"
Cohesion: 0.08
Nodes (34): boundingBox(), completeEdgeReferences(), completeFaceReferences(), decode(), decodeFaces(), dot(), edgeReference(), EdgeSig (+26 more)

### Community 65 - "CommandRegistry"
Cohesion: 0.12
Nodes (4): CommandRegistry, cmds_, CommandRegistry::add(), TEST()

### Community 66 - "MetricSize"
Cohesion: 0.33
Nodes (6): MetricSize, d, loose, name, normal, pitch

### Community 67 - "dimensionOf"
Cohesion: 0.40
Nodes (5): Dimension, Angle, Length, Unitless, dimensionOf()

### Community 68 - "Theme"
Cohesion: 0.22
Nodes (4): Theme, colors_, public, styled_

### Community 69 - "Feature"
Cohesion: 0.10
Nodes (18): Feature, commandId, error, id, inputs, name, parameterNames, rolledBack (+10 more)

### Community 70 - "InputType"
Cohesion: 0.08
Nodes (21): bindTsr(), fromPy(), toPy(), typeName(), InputType, Axis, Bodies, Body (+13 more)

### Community 71 - "ParametersDialog.cpp"
Cohesion: 0.07
Nodes (18): MainWindow::openMeasure(), number(), ParametersDialog, building_, error_, filter_, listener_, ParametersDialog::ParametersDialog() (+10 more)

### Community 72 - "MainWindowSketch.cpp"
Cohesion: 0.04
Nodes (31): UiCommand, enabled, icon, id, name, panel, run, shortcut (+23 more)

### Community 73 - "ViewportArrow.cpp"
Cohesion: 0.05
Nodes (34): MarkingMenu::mouseMoveEvent(), QMouseEvent, ViewInteractor, Viewport::frontEdgeOwner(), rgb(), segmentDistance(), Viewport::arrowAt(), Viewport::arrowMouseMove() (+26 more)

### Community 75 - "Constraint"
Cohesion: 0.08
Nodes (18): ext(), fixedColor(), freeColor(), qc(), rgb(), wire(), Constraint, driven (+10 more)

### Community 76 - "Vec3"
Cohesion: 0.18
Nodes (19): SurfacePoint, normal, point, Vec3, containsPoint(), edgeMidpoint(), edgesNear(), frame() (+11 more)

### Community 77 - "BoundaryCell"
Cohesion: 0.29
Nodes (4): BoundaryCell, ref, shape, volume

### Community 78 - "math"
Cohesion: 0.05
Nodes (3): dist(), check_regular(), dist_to_line()

### Community 79 - "CommandDialog::CommandDialog"
Cohesion: 0.11
Nodes (5): ExpressionSpinBox, eval_, expression_, shown_, formatNumber()

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
Cohesion: 0.20
Nodes (3): slurp(), TEST(), tmp()

### Community 85 - "Level"
Cohesion: 0.16
Nodes (13): debug(), error(), info(), Level, Debug, Error, Info, Warning (+5 more)

### Community 86 - "README.md"
Cohesion: 0.13
Nodes (11): Reference parts, Fusion feature checklist, Roadmap, Contents, Development, Features, Install, License (+3 more)

### Community 89 - "Development"
Cohesion: 0.40
Nodes (4): Build, Conventions, Development, Tests

### Community 90 - "QDialog"
Cohesion: 0.05
Nodes (29): QAbstractButton, QAction, QDialog, MainWindow::checkInterference(), MainWindow::chooseUnits(), MainWindow::driveJoints(), MainWindow::editMaterial(), MainWindow::exportDesign() (+21 more)

### Community 91 - "extrudeToFace"
Cohesion: 0.70
Nodes (5): extendedFace(), extrudeToFace(), interiorPoint(), massProperties(), replaceFaces()

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

### Community 97 - "src/main.cpp"
Cohesion: 0.07
Nodes (14): ArrowPlacement, base, dir, edgePlacement(), facesPlacement(), MainWindow::attachArrowCompleters(), MainWindow::patternCentre(), MainWindow::pickedFaces() (+6 more)

### Community 98 - "FakeDoc"
Cohesion: 0.17
Nodes (6): FakeDoc, aborts, commits, items, open, snapshot

### Community 99 - "ParamSet"
Cohesion: 0.07
Nodes (34): ModelParameter, angle, expression, input, label, name, owner, unit (+26 more)

### Community 100 - "WallSide"
Cohesion: 0.50
Nodes (4): WallSide, Center, Side1, Side2

### Community 102 - "Document::load"
Cohesion: 0.17
Nodes (5): doc_(), Document::Document(), Document::ocafBytes(), ocafApplication(), Document::load()

### Community 103 - "toDxf"
Cohesion: 0.52
Nodes (6): Point, x, y, z, customPlaneSpec(), toDxf()

### Community 104 - "Placement"
Cohesion: 0.25
Nodes (7): Placement, angle, cx, cy, dx, dy, scale

### Community 106 - "QObject"
Cohesion: 0.12
Nodes (7): QObject, SketchEditor::SketchEditor(), Tool, op, shape, target, type

### Community 108 - "Joints"
Cohesion: 0.36
Nodes (3): cornerAt(), Joints, parent_

### Community 110 - "Axis"
Cohesion: 0.50
Nodes (4): Axis, X, Y, Z

### Community 111 - "Known gaps"
Cohesion: 0.12
Nodes (17): 3D Sketch, Appearance, Boundary Fill, Curvature (G2), Draft, Emboss, Face patterns, Fillet (+9 more)

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
Cohesion: 0.16
Nodes (11): Result, error, ok, output, captured(), PythonHost::exec(), PythonHost::runScript(), Case (+3 more)

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
Cohesion: 0.42
Nodes (3): Joint, asBuilt_, def_

### Community 130 - "Column"
Cohesion: 0.25
Nodes (8): Column, kComment, kExpression, kName, kParameter, kStar, kUnit, kValue

### Community 140 - "ChainSegment"
Cohesion: 0.67
Nodes (3): ChainSegment, entity, forward

### Community 142 - "SplineHandle"
Cohesion: 0.25
Nodes (8): SplineHandle, arm, index, set, tx, ty, x, y

### Community 145 - "BodyFrame"
Cohesion: 0.15
Nodes (14): BodyFrame, diag, dx, dy, dz, x0, y0, z0 (+6 more)

### Community 147 - "EntityType"
Cohesion: 0.29
Nodes (7): EntityType, Arc, Circle, Ellipse, Line, Spline, isRound()

### Community 152 - "Architecture"
Cohesion: 0.40
Nodes (4): Architecture, How a command works, The document, Units

## Knowledge Gaps
- **811 isolated node(s):** `ok`, `output`, `error`, `isReal`, `real` (+806 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 1561 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **24 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `optional` connect `optional` to `Viewport`, `MainWindow`, `SketchEditor`, `Kernel.cpp`, `Viewport.h`, `Io.cpp`, `Unit`, `sketchFor`, `Entity`, `ViewportSketch.cpp`, `DocCommands.cpp`, `SketchGeometry.cpp`, `AnalysisSettings`, `Document.cpp`, `InputDef`, `SketchEditor.cpp`, `ConstructionPoint`, `CommandDialog.cpp`, `Session`, `Feature`, `ViewportArrow.cpp`, `Constraint`, `Vec3`, `CommandDialog::CommandDialog`, `SketchCurves.cpp`, `ReplayStep`, `src/main.cpp`, `ParamSet`, `Joints`?**
  _High betweenness centrality (0.130) - this node is a cross-community bridge._
- **What connects `ok`, `output`, `error` to the rest of the system?**
  _811 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Viewport` be split into smaller, more focused modules?**
  _Cohesion score 0.014071381977448514 - nodes in this community are weakly interconnected._
- **Why does `Viewport` connect `Viewport` to `.rebuild`, `src/main.cpp`, `MainWindow`, `MainWindow::MainWindow`, `Viewport.cpp`, `ViewportArrow.cpp`, `optional`, `Viewport.h`, `AnalysisSettings`, `SketchDisplay`, `.redrawAll`, `Viewport::setDragArrow`, `SketchCurves.cpp`, `.toPixels`, `SelectionBox`, `QDialog`, `.initializeGL`?**
  _High betweenness centrality (0.126) - this node is a cross-community bridge._
- **Should `Icons.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.05251798561151079 - nodes in this community are weakly interconnected._
- **Why does `SketchEditor` connect `SketchEditor` to `Viewport`, `ViewportArrow.cpp`, `QObject`, `Pick`, `optional`, `Viewport.h`, `Constraint`, `Kind`, `Unit`, `Entity`, `SketchEditor.cpp`, `Snap`, `TEST`, `Session`?**
  _High betweenness centrality (0.096) - this node is a cross-community bridge._
- **Should `Session.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.055855855855855854 - nodes in this community are weakly interconnected._