# Graph Report - tessera  (2026-11-17)

## Corpus Check
- 429 files · ~282,907 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 74 file(s) not represented in the graph (top: .drive 66, (none) 5, .cmake 1)

## Summary
- 3980 nodes · 10231 edges · 146 communities (120 shown, 26 thin omitted)
- Extraction: 85% EXTRACTED · 15% INFERRED · 0% AMBIGUOUS · INFERRED: 1567 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `aa019d3d`
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
- Unit
- sketchFor
- Entity
- Document
- TEST
- Affine
- ViewportSketch.cpp
- SketchPalette
- Constraint
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
- validateOperation
- curve
- ConstraintType
- AdskModule.cpp
- Pick
- TopologyCounts
- Zip.cpp
- AnalysisSettings
- Sketch
- Document.cpp
- InputDef
- SketchEditor.cpp
- .toPixels
- Snap
- Document::recompute
- .showDialog
- TEST
- TsrModule.cpp
- xdrive.py
- adsk_core
- CommandDialog.cpp
- Session
- Theme.cpp
- BodyFrame
- CommandRegistry
- src/main.cpp
- Unit
- Theme
- Feature
- InputType
- ParametersDialog.cpp
- MainWindowSketch.cpp
- ViewportArrow.cpp
- .add
- .mouseMove
- Vec3
- CommandDialog::CommandDialog
- math
- CommandDialog::CommandDialog
- SketchDisplay
- Kind
- Measurement
- SketchCurves.cpp
- TEST
- Level
- README.md
- cachedProfiles
- test_feature_pattern.py
- QDialog
- path
- FileFormat
- Known differences still to build
- ReplayStep
- main
- src/main.cpp
- FakeDoc
- NamedView
- BoundingBox
- TEST
- Document::load
- toDxf
- Placement
- test_rigid_group.py
- QObject
- Display
- Joints
- Axis
- Known gaps
- .redrawAll
- SectionState
- uninstall.sh
- install.sh
- TestFramework.h
- includeEdges
- Profile
- Mesh
- Entry
- SelectionBox
- test_incremental_replay.py
- BooleanOp
- MassProperties
- QScrollArea
- ThreadInfo
- ChamferType
- Joint
- Column
- bindAdsk
- Document::nameFeatureParameters
- LAB_NOTES.md
- SketchRecord
- UserParameter
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
4. `Inputs` - 161 edges
5. `render()` - 124 edges
6. `Document` - 122 edges
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

## Communities (146 total, 26 thin omitted)

### Community 0 - "Viewport"
Cohesion: 0.01
Nodes (79): view_, QLineEdit, Viewport, analysis_, analysisObjects_, appliedGridStep_, arrowBoxes_, arrowDragging_ (+71 more)

### Community 1 - "Icons.cpp"
Cohesion: 0.05
Nodes (129): accessibilityIcon(), appearanceIcon(), arc3Icon(), arcIcon(), arcTangentIcon(), arrow(), axisIcon(), boundaryFillIcon() (+121 more)

### Community 2 - "Session.cpp"
Cohesion: 0.06
Nodes (51): CommandSession, inputs_, expressionKey(), checkInputValue(), CommandContext::evaluateExpression(), CommandDef::input(), CommandSession::applyInTransaction(), CommandSession::cancel() (+43 more)

### Community 4 - "MainWindow"
Cohesion: 0.03
Nodes (67): CommandDialog, MainWindow, active_, appearanceColour_, appearanceFaces_, appearancePanel_, arrowInput_, arrowInput2_ (+59 more)

### Community 5 - "run_oracle.py"
Cohesion: 0.08
Nodes (54): add_point(), arc_poly(), body_at(), body_list(), build_sketch(), chain(), circumcentre(), cm() (+46 more)

### Community 6 - "DocCommands.cpp"
Cohesion: 0.10
Nodes (17): AddUserParameter, def_, applyToParticipants(), boundaryFillCells(), checkPattern(), isIdentifier(), Loft, def_ (+9 more)

### Community 7 - "Document"
Cohesion: 0.03
Nodes (16): Document, effects_, lastReplayed_, lastReused_, modified_, pendingTools_, registry_, replaying_ (+8 more)

### Community 8 - "Viewport.cpp"
Cohesion: 0.05
Nodes (5): glide(), keys(), QKeyEvent, QtFrameBuffer, Viewport::Viewport()

### Community 9 - "SketchEditor"
Cohesion: 0.03
Nodes (53): HandleHit, back, index, spline, SketchEditor, arcDrag_, arcDragMoved_, arcEndsChain_ (+45 more)

### Community 10 - "DocumentError"
Cohesion: 0.08
Nodes (39): DocumentError, bodyNumber(), checkViewName(), Document::abortTransaction(), Document::addBody(), Document::addNamedView(), Document::addUserParameter(), Document::axisFrame() (+31 more)

### Community 11 - "optional"
Cohesion: 0.09
Nodes (7): optional, isEmpty(), Value, CommandRegistry::all(), Document, fail(), Failure

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
Cohesion: 0.08
Nodes (11): QMouseEvent, ViewInteractor, Viewport::arrowMouseMove(), Viewport::arrowMousePress(), Viewport::arrowMouseRelease(), Viewport::DragArrow::handle(), Viewport::dragArrowForTest(), Viewport::emitArrow() (+3 more)

### Community 16 - "CommandDialog"
Cohesion: 0.04
Nodes (36): CommandDialog, bodiesId_, bodiesLabel_, bodyInput_, buttons_, cellsId_, cellsList_, cmd_ (+28 more)

### Community 17 - "Io.cpp"
Cohesion: 0.10
Nodes (4): fromBrep(), lower(), toBrep(), xmlEscape()

### Community 18 - "Unit"
Cohesion: 0.12
Nodes (27): ExpressionEnv, lengthUnit, lookup, ExpressionError, Quantity, angle, length, value (+19 more)

### Community 19 - "sketchFor"
Cohesion: 0.13
Nodes (14): applyOperation(), Extrude, def_, Pipe, def_, profilesOf(), Revolve, def_ (+6 more)

### Community 20 - "Entity"
Cohesion: 0.10
Nodes (11): Entity, a, b, center, construction, fit, handles, included (+3 more)

### Community 21 - "Document"
Cohesion: 0.22
Nodes (8): ConstructAxisPoint, def_, kind_, jointOrigin(), JointPick, frame, planeOf(), revolveAxis()

### Community 22 - "TEST"
Cohesion: 0.08
Nodes (17): Sketch, constraints, entities, points, texts, Text, angle, corner (+9 more)

### Community 24 - "Affine"
Cohesion: 0.14
Nodes (13): Affine, a, b, d, e, Builder, byPlace_, k_ (+5 more)

### Community 25 - "ViewportSketch.cpp"
Cohesion: 0.05
Nodes (7): QLabel, faceStyle(), lineStyle(), rgb(), Viewport::lookAt(), Viewport::planePoint(), Viewport::toWidget()

### Community 26 - "SketchPalette"
Cohesion: 0.06
Nodes (26): flatButton(), QCheckBox, QLabel, QToolButton, QWidget, SketchEditor, SketchPalette, body_ (+18 more)

### Community 27 - "Constraint"
Cohesion: 0.09
Nodes (20): Constraint, driven, entities, expression, hasLabel, labelX, labelY, name (+12 more)

### Community 28 - "Inputs"
Cohesion: 0.08
Nodes (25): CommandContext, CommandError, Inputs, CommandSession::CommandSession(), getBool(), getInt(), getReal(), bodyCentre() (+17 more)

### Community 29 - "Command"
Cohesion: 0.03
Nodes (75): Adding a tool, Command, CommandDef, feature, icon, id, inputs, name (+67 more)

### Community 30 - "Colors"
Cohesion: 0.07
Nodes (28): Colors, base, border, cubeBox, cubeText, errorBackground, grid, gridMajor (+20 more)

### Community 31 - "KernelError"
Cohesion: 0.23
Nodes (33): KernelError, asSolid(), boolean(), boundaryCells(), chamfer(), chamferEx(), deleteFaces(), draft() (+25 more)

### Community 32 - "SketchOps.cpp"
Cohesion: 0.22
Nodes (25): at(), chainOf(), chamferCorner(), circularPattern(), copyEntities(), cornerAt(), cross(), dot() (+17 more)

### Community 33 - ".rebuild"
Cohesion: 0.10
Nodes (12): hiddenColour(), qc(), rgb(), sharpEdges(), Style, Shaded, ShadedEdges, ShadedHidden (+4 more)

### Community 34 - "ParameterCompleter"
Cohesion: 0.12
Nodes (8): ParameterCompleter, completer_, edit_, names_, ParameterCompleter::ParameterCompleter(), public, QCompleter, QLineEdit

### Community 35 - "TEST"
Cohesion: 0.09
Nodes (3): param(), TEST(), tmp()

### Community 37 - "MainWindow.cpp"
Cohesion: 0.05
Nodes (12): commandIcon(), MainWindow::MainWindow(), qs(), MainWindow::beginSketch(), MainWindow::buildSketchTab(), MainWindow::enterSketchMode(), MainWindow::exitSketchMode(), MainWindow::applySection() (+4 more)

### Community 38 - "solve"
Cohesion: 0.18
Nodes (13): addConstraintChecked(), Layout, n, px, py, rad, makeLayout(), pack() (+5 more)

### Community 39 - "validateOperation"
Cohesion: 0.13
Nodes (10): Coil, def_, Primitive, build_, def_, Sweep, def_, Thicken (+2 more)

### Community 40 - "curve"
Cohesion: 0.19
Nodes (17): conditionedSpline(), curve(), curves(), entityCurves(), G2End, d1, d2, set (+9 more)

### Community 41 - "ConstraintType"
Cohesion: 0.08
Nodes (26): ConstraintType, Angle, Coincident, Collinear, Concentric, Curvature, Diameter, Distance (+18 more)

### Community 42 - "AdskModule.cpp"
Cohesion: 0.12
Nodes (13): Application, BRepBodies, Component, Design, Product, raiseIfError(), UserParameter, name (+5 more)

### Community 43 - "Pick"
Cohesion: 0.08
Nodes (20): Pick, bodyArc, bodyPoint, bodySegment, hit, midpointOf, onEntity, onXAxis (+12 more)

### Community 45 - "TopologyCounts"
Cohesion: 0.18
Nodes (16): Section, Circular, Square, Triangular, TopologyCounts, edges, faces, shells (+8 more)

### Community 46 - "Zip.cpp"
Cohesion: 0.25
Nodes (10): ZipError, crc32(), deflateRaw(), get16(), get32(), inflateRaw(), put16(), put32() (+2 more)

### Community 47 - "AnalysisSettings"
Cohesion: 0.08
Nodes (20): DragArrow, base, dir, radius, ref, ring, value, PendingLook (+12 more)

### Community 48 - "Sketch"
Cohesion: 0.08
Nodes (21): SketchError, SplineKind, Conic, Control, Fit, entityTypeName(), isDimension(), Sketch::addConic() (+13 more)

### Community 49 - "Document.cpp"
Cohesion: 0.08
Nodes (37): ParamSet, env, text, Document::axes(), Document::bodies(), Document::body(), Document::bodyName(), Document::component() (+29 more)

### Community 51 - "InputDef"
Cohesion: 0.09
Nodes (22): InputDef, choices, defaultValue, id, label, max, min, minExclusive (+14 more)

### Community 52 - "SketchEditor.cpp"
Cohesion: 0.12
Nodes (5): angleInArc(), ccwContains(), circumcircle(), lineEntity(), segDistance()

### Community 54 - "Snap"
Cohesion: 0.11
Nodes (18): Snap, alignX, alignY, bodyArc, bodySegment, entity, fromX, fromY (+10 more)

### Community 55 - "Document::recompute"
Cohesion: 0.13
Nodes (10): Document::currentParams(), Document::expressionEnv(), Document::openTransaction(), Document::recompute(), Document::recordFeature(), Document::removeFeature(), Document::setFeatureInputs(), Document::setFeatureSuppressed() (+2 more)

### Community 56 - ".showDialog"
Cohesion: 0.12
Nodes (5): MainWindow::onEdgeClicked(), MainWindow::onProfileClicked(), MainWindow::originalShape(), MainWindow::syncPickedShapes(), MainWindow::toOriginal()

### Community 58 - "TsrModule.cpp"
Cohesion: 0.33
Nodes (3): bindTsr(), fromPy(), toPy()

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
Cohesion: 0.09
Nodes (33): boundingBox(), completeEdgeReferences(), completeFaceReferences(), decode(), decodeFaces(), dot(), edgeReference(), EdgeSig (+25 more)

### Community 65 - "CommandRegistry"
Cohesion: 0.12
Nodes (4): CommandRegistry, cmds_, CommandRegistry::add(), TEST()

### Community 66 - "src/main.cpp"
Cohesion: 0.09
Nodes (7): QAbstractButton, QAction, grabWindowWithPanels(), writeLiveGeometry(), MarkingMenu, enabled, public

### Community 67 - "Unit"
Cohesion: 0.13
Nodes (20): formatNumber(), MainWindow::lengthUnit(), Dimension, Angle, Length, Unitless, Unit, Centimeter (+12 more)

### Community 68 - "Theme"
Cohesion: 0.22
Nodes (4): Theme, colors_, public, styled_

### Community 69 - "Feature"
Cohesion: 0.15
Nodes (11): Feature, commandId, error, id, inputs, name, parameterNames, rolledBack (+3 more)

### Community 70 - "InputType"
Cohesion: 0.11
Nodes (18): typeName(), InputType, Axis, Bodies, Body, Bool, Choice, Edges (+10 more)

### Community 71 - "ParametersDialog.cpp"
Cohesion: 0.08
Nodes (16): number(), ParametersDialog, building_, error_, filter_, listener_, ParametersDialog::ParametersDialog(), public (+8 more)

### Community 72 - "MainWindowSketch.cpp"
Cohesion: 0.04
Nodes (34): UiCommand, enabled, icon, id, name, panel, run, shortcut (+26 more)

### Community 73 - "ViewportArrow.cpp"
Cohesion: 0.06
Nodes (26): Viewport::frontEdgeOwner(), rgb(), segmentDistance(), Viewport::arrowAt(), Viewport::arrowParam(), Viewport::dragArrowHandle(), Viewport::placeArrowBoxes(), Viewport::rebuildArrow() (+18 more)

### Community 75 - ".mouseMove"
Cohesion: 0.19
Nodes (6): ext(), fixedColor(), freeColor(), qc(), rgb(), wire()

### Community 76 - "Vec3"
Cohesion: 0.16
Nodes (23): SurfacePoint, normal, point, Vec3, containsPoint(), edgeMidpoint(), edgesNear(), extrudeToFace() (+15 more)

### Community 77 - "CommandDialog::CommandDialog"
Cohesion: 0.13
Nodes (5): CommandDialog::CommandDialog(), BoundaryCell, ref, shape, volume

### Community 78 - "math"
Cohesion: 0.05
Nodes (4): dist(), up_to_underside(), check_regular(), dist_to_line()

### Community 79 - "CommandDialog::CommandDialog"
Cohesion: 0.17
Nodes (4): ExpressionSpinBox, eval_, expression_, shown_

### Community 80 - "SketchDisplay"
Cohesion: 0.12
Nodes (11): ProfileObject, index, sketch, SketchDisplay, construction, curves, fixedCurves, frame (+3 more)

### Community 81 - "Kind"
Cohesion: 0.07
Nodes (24): Hit, index, kind, HudField, edit, editing, kind, locked (+16 more)

### Community 82 - "Measurement"
Cohesion: 0.12
Nodes (15): Kind, Angle, Area, Length, Volume, Measurement, from, hasLine (+7 more)

### Community 83 - "SketchCurves.cpp"
Cohesion: 0.14
Nodes (17): crossings(), crossingsOf(), Curve2d, curve2d(), periodic, t0, t1, endIsFree() (+9 more)

### Community 84 - "TEST"
Cohesion: 0.20
Nodes (3): slurp(), TEST(), tmp()

### Community 85 - "Level"
Cohesion: 0.16
Nodes (13): debug(), error(), info(), Level, Debug, Error, Info, Warning (+5 more)

### Community 86 - "README.md"
Cohesion: 0.10
Nodes (15): Build, Conventions, Development, Tests, Reference parts, Fusion feature checklist, Roadmap, Contents (+7 more)

### Community 90 - "QDialog"
Cohesion: 0.05
Nodes (31): QDialog, MainWindow::checkInterference(), MainWindow::chooseUnits(), MainWindow::driveJoints(), MainWindow::editMaterial(), MainWindow::exportDesign(), MainWindow::formatLength(), MainWindow::gridSettings() (+23 more)

### Community 91 - "path"
Cohesion: 0.32
Nodes (12): MainWindow::print3d(), NamedShape, compoundOf(), exportShapes(), fmt(), formatForPath(), importShape(), meshOf() (+4 more)

### Community 92 - "FileFormat"
Cohesion: 0.17
Nodes (12): FileFormat, Brep, Iges, Obj, Step, Stl, ThreeMF, FormatInfo (+4 more)

### Community 93 - "Known differences still to build"
Cohesion: 0.15
Nodes (12): Data and files, Findings from the videos, Fusion study list, Interface, Known differences still to build, Navigation and display, Selection and the canvas, Sketch (+4 more)

### Community 95 - "ReplayStep"
Cohesion: 0.04
Nodes (58): Body, color, display, faceColors, material, name, shape, Component (+50 more)

### Community 96 - "main"
Cohesion: 0.27
Nodes (6): listCommands(), main(), usage(), main(), smoke(), key

### Community 97 - "src/main.cpp"
Cohesion: 0.06
Nodes (14): ArrowPlacement, base, dir, edgePlacement(), facesPlacement(), MainWindow::attachArrowCompleters(), MainWindow::patternCentre(), MainWindow::pickedFaces() (+6 more)

### Community 98 - "FakeDoc"
Cohesion: 0.17
Nodes (6): FakeDoc, aborts, commits, items, open, snapshot

### Community 99 - "NamedView"
Cohesion: 0.29
Nodes (7): NamedView, eye, name, size, target, up, fromJson()

### Community 100 - "BoundingBox"
Cohesion: 0.17
Nodes (16): BoundingBox, max, min, WallSide, Center, Side1, Side2, extendedWire() (+8 more)

### Community 101 - "TEST"
Cohesion: 0.27
Nodes (3): env(), mm(), TEST()

### Community 102 - "Document::load"
Cohesion: 0.17
Nodes (5): doc_(), Document::Document(), Document::ocafBytes(), ocafApplication(), Document::load()

### Community 103 - "toDxf"
Cohesion: 0.43
Nodes (7): Point, x, y, z, customPlaneSpec(), planeFrame(), toDxf()

### Community 104 - "Placement"
Cohesion: 0.25
Nodes (7): Placement, angle, cx, cy, dx, dy, scale

### Community 106 - "QObject"
Cohesion: 0.13
Nodes (4): QObject, SketchEditor::SketchEditor(), edges, type

### Community 107 - "Display"
Cohesion: 0.25
Nodes (7): Display, constraints, construction, dimensions, points, profiles, projected

### Community 110 - "Axis"
Cohesion: 0.50
Nodes (4): Axis, X, Y, Z

### Community 111 - "Known gaps"
Cohesion: 0.12
Nodes (16): 3D Sketch, Appearance, Boundary Fill, Curvature (G2), Draft, Emboss, Face patterns, Fillet (+8 more)

### Community 112 - ".redrawAll"
Cohesion: 0.09
Nodes (9): NavPreset, Fusion, SolidWorks, Tinkercad, Viewport::setCurvatureComb(), Viewport::clearDragArrow(), Viewport::clearSecondArrow(), Viewport::setInteractor() (+1 more)

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
Nodes (12): PythonHost, Result, error, ok, output, captured(), PythonHost::exec(), PythonHost::runScript() (+4 more)

### Community 117 - "includeEdges"
Cohesion: 0.24
Nodes (4): includeEdges(), projectToSurface(), interiorPoint(), toSketch()

### Community 118 - "Profile"
Cohesion: 0.33
Nodes (5): Profile, area, face, x, y

### Community 119 - "Mesh"
Cohesion: 0.40
Nodes (3): Mesh, nodes, triangles

### Community 120 - "Entry"
Cohesion: 0.50
Nodes (3): Entry, data, name

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

### Community 131 - "bindAdsk"
Cohesion: 0.29
Nodes (3): bindAdsk(), BRepBody, index

### Community 132 - "Document::nameFeatureParameters"
Cohesion: 0.33
Nodes (5): Document::bodyShapes(), Document::effectOf(), Document::nameFeatureParameters(), joinNames(), parseNames()

### Community 134 - "SketchRecord"
Cohesion: 0.29
Nodes (7): SketchRecord, data, name, offset, plane, Document::setSketch(), Document::sketch()

### Community 135 - "UserParameter"
Cohesion: 0.33
Nodes (6): UserParameter, comment, expression, name, unit, value

### Community 140 - "ChainSegment"
Cohesion: 0.67
Nodes (3): ChainSegment, entity, forward

### Community 142 - "SplineHandle"
Cohesion: 0.25
Nodes (8): SplineHandle, arm, index, set, tx, ty, x, y

### Community 145 - "BodyFrame"
Cohesion: 0.14
Nodes (15): BodyFrame, diag, dx, dy, dz, x0, y0, z0 (+7 more)

### Community 147 - "EntityType"
Cohesion: 0.29
Nodes (7): EntityType, Arc, Circle, Ellipse, Line, Spline, isRound()

### Community 152 - "Architecture"
Cohesion: 0.40
Nodes (4): Architecture, How a command works, The document, Units

## Knowledge Gaps
- **808 isolated node(s):** `ok`, `output`, `error`, `isReal`, `real` (+803 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 1554 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **26 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `Viewport` connect `Viewport` to `.rebuild`, `src/main.cpp`, `SelectionBox`, `MainWindow.cpp`, `Viewport.cpp`, `ViewportArrow.cpp`, `optional`, `AnalysisSettings`, `AnalysisSettings`, `SketchDisplay`, `.redrawAll`, `QMouseEvent`, `SketchCurves.cpp`, `.toPixels`, `ViewportSketch.cpp`, `QDialog`, `.initializeGL`?**
  _High betweenness centrality (0.133) - this node is a cross-community bridge._
- **What connects `ok`, `output`, `error` to the rest of the system?**
  _808 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Viewport` be split into smaller, more focused modules?**
  _Cohesion score 0.014071381977448514 - nodes in this community are weakly interconnected._
- **Why does `optional` connect `optional` to `Viewport`, `MainWindow`, `SketchRecord`, `SketchEditor`, `DocumentError`, `Kernel.cpp`, `Unit`, `sketchFor`, `Entity`, `ViewportSketch.cpp`, `Command`, `SketchOps.cpp`, `SketchGeometry.cpp`, `AnalysisSettings`, `Document.cpp`, `.solveAndShow`, `InputDef`, `SketchEditor.cpp`, `CommandDialog.cpp`, `Session`, `Unit`, `Feature`, `ViewportArrow.cpp`, `.mouseMove`, `Vec3`, `CommandDialog::CommandDialog`, `SketchCurves.cpp`, `path`, `ReplayStep`, `src/main.cpp`?**
  _High betweenness centrality (0.124) - this node is a cross-community bridge._
- **Should `Icons.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.052312435765673175 - nodes in this community are weakly interconnected._
- **Why does `SketchEditor` connect `SketchEditor` to `Viewport`, `Unit`, `QObject`, `Display`, `Pick`, `optional`, `.mouseMove`, `QMouseEvent`, `Kind`, `.solveAndShow`, `Entity`, `SketchEditor.cpp`, `Snap`, `Constraint`, `Session`, `ReplayStep`?**
  _High betweenness centrality (0.091) - this node is a cross-community bridge._
- **Should `Session.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.055855855855855854 - nodes in this community are weakly interconnected._