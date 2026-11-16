# Graph Report - tessera  (2026-11-16)

## Corpus Check
- 407 files · ~270,502 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 65 file(s) not represented in the graph (top: .drive 57, (none) 5, .cmake 1)

## Summary
- 3823 nodes · 9838 edges · 135 communities (107 shown, 28 thin omitted)
- Extraction: 85% EXTRACTED · 15% INFERRED · 0% AMBIGUOUS · INFERRED: 1505 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `0b3207de`
- Run `git rev-parse HEAD` and compare to check if the graph is stale.
- Run `graphify update .` after code changes (no API cost).

## Community Hubs (Navigation)
- Viewport
- Icons.cpp
- Session.cpp
- MainWindow
- run_oracle.py
- NewComponent
- Document
- Viewport.cpp
- SketchEditor
- DocumentError
- optional
- Kernel.cpp
- AnalysisSettings
- Kind
- ViewportAnalysis.cpp
- CommandDialog
- Io.cpp
- Parser
- .setSelectionFilter
- SketchEditor.cpp
- Document
- Snap
- PlaneEdges
- Affine
- ViewportSketch.cpp
- SketchPalette
- Sketch
- DocCommands.cpp
- CommandContext
- Colors
- KernelError
- SketchOps.cpp
- MainWindow::buildSketchTab
- ParameterCompleter
- Constraint
- getReal
- MainWindow.cpp
- solve
- .eventFilter
- Value.h
- ConstraintType
- AdskModule.cpp
- Pick
- Unit
- Zip.cpp
- AnalysisSettings
- Sketch.cpp
- Document.cpp
- MainWindowSketch.cpp
- InputDef
- .updatePreview
- .toPixels
- SketchGeometry.cpp
- Document::recompute
- Dimension
- WallSide
- Entity
- xdrive.py
- adsk_core
- UiCommand
- Session
- Theme.cpp
- BodyFrame
- CommandRegistry
- fail
- TEST
- Theme
- Feature
- InputType
- ParametersDialog.cpp
- smoke
- Viewport.h
- MainWindow::applySection
- .mouseMove
- Vec3
- MainWindow::MainWindow
- math
- ExpressionSpinBox
- SketchDisplay
- Command
- Measurement
- SketchCurves.cpp
- Level
- README.md
- test_feature_pattern.py
- gp_Pnt
- QDialog
- FileFormat
- Known differences still to build
- TEST
- ReplayStep
- SketchRecord
- cachedProfiles
- FakeDoc
- ParamSet
- MainWindow::buildUiCommands
- Document::load
- .showDialog
- BoundingBox
- test_rigid_group.py
- SectionState
- Display
- cli_main.cpp
- TopologyCounts
- .redrawAll
- uninstall.sh
- install.sh
- TestFramework.h
- .rebuild
- src/main.cpp
- Known gaps
- test_incremental_replay.py
- Placement
- Column
- .eventFilter
- Joint
- Profile
- Architecture
- LAB_NOTES.md
- Axis
- BooleanOp
- build.sh
- live-test.sh
- ThreadInfo
- PYBIND11_EMBEDDED_MODULE
- SplineHandle
- ChamferType
- ChainSegment

## God Nodes (most connected - your core abstractions)
1. `Viewport` - 257 edges
2. `SketchEditor` - 198 edges
3. `MainWindow` - 184 edges
4. `Inputs` - 158 edges
5. `render()` - 123 edges
6. `Document` - 121 edges
7. `CommandContext` - 114 edges
8. `CommandDialog` - 90 edges
9. `Command` - 67 edges
10. `CommandError` - 66 edges

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

## Communities (135 total, 28 thin omitted)

### Community 0 - "Viewport"
Cohesion: 0.02
Nodes (69): view_, QLineEdit, Viewport, analysis_, analysisObjects_, appliedGridStep_, arrowBoxes_, arrowDragging_ (+61 more)

### Community 1 - "Icons.cpp"
Cohesion: 0.05
Nodes (130): accessibilityIcon(), appearanceIcon(), arc3Icon(), arcIcon(), arcTangentIcon(), arrow(), axisIcon(), box() (+122 more)

### Community 2 - "Session.cpp"
Cohesion: 0.06
Nodes (50): CommandSession, inputs_, expressionKey(), checkInputValue(), CommandContext::evaluateExpression(), CommandDef::input(), CommandSession::applyInTransaction(), CommandSession::cancel() (+42 more)

### Community 4 - "MainWindow"
Cohesion: 0.03
Nodes (63): CommandDialog, MainWindow, active_, arrowInput_, arrowInput2_, bodiesBeforeCommand_, combEdges_, combPicking_ (+55 more)

### Community 5 - "run_oracle.py"
Cohesion: 0.08
Nodes (54): add_point(), arc_poly(), body_at(), body_list(), build_sketch(), chain(), circumcentre(), cm() (+46 more)

### Community 6 - "NewComponent"
Cohesion: 0.15
Nodes (7): AddUserParameter, def_, isIdentifier(), NewComponent, def_, RigidGroup, def_

### Community 7 - "Document"
Cohesion: 0.03
Nodes (15): Document, effects_, lastReplayed_, lastReused_, modified_, pendingTools_, registry_, replaying_ (+7 more)

### Community 8 - "Viewport.cpp"
Cohesion: 0.05
Nodes (8): glide(), keys(), QKeyEvent, QtFrameBuffer, SelectionBox, crossing, Viewport::frontEdgeOwner(), Viewport::Viewport()

### Community 9 - "SketchEditor"
Cohesion: 0.03
Nodes (56): HudField, edit, editing, kind, locked, value, QLineEdit, SketchEditor (+48 more)

### Community 10 - "DocumentError"
Cohesion: 0.11
Nodes (27): DocumentError, checkViewName(), Document::abortTransaction(), Document::addNamedView(), Document::addUserParameter(), Document::commitTransaction(), Document::historyMarker(), Document::removeNamedView() (+19 more)

### Community 13 - "AnalysisSettings"
Cohesion: 0.11
Nodes (18): AnalysisKind, Accessibility, CurvatureMap, Draft, Isocurve, MinimumRadius, None, Zebra (+10 more)

### Community 14 - "Kind"
Cohesion: 0.06
Nodes (32): ConstructPlane, def_, kind_, EdgeFeature, def_, kind_, FaceFeature, def_ (+24 more)

### Community 15 - "ViewportAnalysis.cpp"
Cohesion: 0.07
Nodes (13): ArrowPlacement, base, dir, edgePlacement(), facesPlacement(), MainWindow::attachArrowCompleters(), MainWindow::patternCentre(), MainWindow::pickedFaces() (+5 more)

### Community 16 - "CommandDialog"
Cohesion: 0.04
Nodes (35): CommandDialog, bodiesId_, bodiesLabel_, bodyInput_, buttons_, cmd_, CommandDialog::CommandDialog(), conditional_ (+27 more)

### Community 17 - "Io.cpp"
Cohesion: 0.09
Nodes (19): Document::load(), NamedShape, compoundOf(), exportShapes(), fmt(), formatForPath(), fromBrep(), importShape() (+11 more)

### Community 18 - "Parser"
Cohesion: 0.10
Nodes (31): ExpressionEnv, lengthUnit, lookup, ExpressionError, Quantity, angle, length, value (+23 more)

### Community 21 - "Document"
Cohesion: 0.21
Nodes (7): ConstructAxisPoint, def_, kind_, JointPick, frame, planeOf(), revolveAxis()

### Community 22 - "Snap"
Cohesion: 0.05
Nodes (35): Hit, index, kind, Kind, Angle, BodyEdge, BodyVertex, Count (+27 more)

### Community 23 - "PlaneEdges"
Cohesion: 0.22
Nodes (5): PlaneEdges, arcs, curves, segments, vertices

### Community 24 - "Affine"
Cohesion: 0.14
Nodes (13): Affine, a, b, d, e, Builder, byPlace_, k_ (+5 more)

### Community 25 - "ViewportSketch.cpp"
Cohesion: 0.09
Nodes (6): faceStyle(), lineStyle(), rgb(), Viewport::lookAt(), Viewport::planePoint(), Viewport::toWidget()

### Community 26 - "SketchPalette"
Cohesion: 0.06
Nodes (26): flatButton(), QCheckBox, QLabel, QToolButton, QWidget, SketchEditor, SketchPalette, body_ (+18 more)

### Community 27 - "Sketch"
Cohesion: 0.06
Nodes (13): writeLiveGeometry(), Sketch, constraints, entities, points, texts, Sketch::addCircle(), Sketch::addConic() (+5 more)

### Community 28 - "DocCommands.cpp"
Cohesion: 0.08
Nodes (38): CommandError, getBool(), getInt(), applyOperation(), axisOf(), bodyCentre(), bodyName(), Combine (+30 more)

### Community 29 - "CommandContext"
Cohesion: 0.06
Nodes (16): CommandContext, Inputs, CommandSession::CommandSession(), checkBody(), checkPattern(), defaultBody(), Loft, def_ (+8 more)

### Community 30 - "Colors"
Cohesion: 0.07
Nodes (28): Colors, base, border, cubeBox, cubeText, errorBackground, grid, gridMajor (+20 more)

### Community 31 - "KernelError"
Cohesion: 0.21
Nodes (36): KernelError, asSolid(), boolean(), chamfer(), chamferEx(), curveMiddles(), deleteFaces(), draft() (+28 more)

### Community 32 - "SketchOps.cpp"
Cohesion: 0.15
Nodes (30): at(), chainOf(), chamferCorner(), circularPattern(), copyEntities(), cornerAt(), cross(), dot() (+22 more)

### Community 34 - "ParameterCompleter"
Cohesion: 0.12
Nodes (8): ParameterCompleter, completer_, edit_, names_, ParameterCompleter::ParameterCompleter(), public, QCompleter, QLineEdit

### Community 35 - "Constraint"
Cohesion: 0.08
Nodes (20): Constraint, driven, entities, expression, hasLabel, labelX, labelY, name (+12 more)

### Community 36 - "getReal"
Cohesion: 0.16
Nodes (17): getReal(), Coil, def_, CreateSketch, def_, evaluateDimensions(), makeBox(), makeCone() (+9 more)

### Community 37 - "MainWindow.cpp"
Cohesion: 0.11
Nodes (3): commandIcon(), qs(), MainWindow::enterSketchMode()

### Community 38 - "solve"
Cohesion: 0.11
Nodes (14): addConstraintChecked(), Layout, n, px, py, rad, makeLayout(), pack() (+6 more)

### Community 39 - ".eventFilter"
Cohesion: 0.12
Nodes (7): QObject, SketchEditor::SketchEditor(), Tool, op, shape, target, type

### Community 41 - "ConstraintType"
Cohesion: 0.07
Nodes (26): ConstraintType, Angle, Coincident, Collinear, Concentric, Curvature, Diameter, Distance (+18 more)

### Community 42 - "AdskModule.cpp"
Cohesion: 0.07
Nodes (18): Application, BRepBodies, Component, Design, Product, raiseIfError(), UserParameter, name (+10 more)

### Community 43 - "Pick"
Cohesion: 0.12
Nodes (16): Pick, bodyArc, bodyPoint, bodySegment, hit, midpointOf, onEntity, onXAxis (+8 more)

### Community 45 - "Unit"
Cohesion: 0.08
Nodes (19): bindAdsk(), BRepBody, index, MainWindow::lengthUnit(), Unit, Centimeter, Degree, Foot (+11 more)

### Community 46 - "Zip.cpp"
Cohesion: 0.20
Nodes (13): Entry, data, name, ZipError, crc32(), deflateRaw(), get16(), get32() (+5 more)

### Community 47 - "AnalysisSettings"
Cohesion: 0.10
Nodes (16): DragArrow, base, dir, radius, ref, ring, value, PendingLook (+8 more)

### Community 48 - "Sketch.cpp"
Cohesion: 0.06
Nodes (26): EntityType, Arc, Circle, Ellipse, Line, Spline, isRound(), SketchError (+18 more)

### Community 49 - "Document.cpp"
Cohesion: 0.06
Nodes (42): ConstructionPlane, name, spec, bodyNumber(), Document::addBody(), Document::axisFrame(), Document::bodies(), Document::body() (+34 more)

### Community 50 - "MainWindowSketch.cpp"
Cohesion: 0.05
Nodes (25): MainWindow::cancelSketch(), MainWindow::editSketch(), MainWindow::finishSketch(), MainWindow::onProfileClicked(), MainWindow::originalShape(), MainWindow::sketchPalette(), MainWindow::sketchVisible(), MainWindow::startSketch() (+17 more)

### Community 51 - "InputDef"
Cohesion: 0.09
Nodes (22): InputDef, choices, defaultValue, id, label, max, min, minExclusive (+14 more)

### Community 54 - "SketchGeometry.cpp"
Cohesion: 0.07
Nodes (25): Point, x, y, z, conditionedSpline(), curve(), curves(), customPlaneSpec() (+17 more)

### Community 55 - "Document::recompute"
Cohesion: 0.14
Nodes (10): Document::expressionEnv(), Document::feature(), Document::nextPlaneName(), Document::nextSketchName(), Document::openTransaction(), Document::recompute(), Document::recordFeature(), Document::removeFeature() (+2 more)

### Community 56 - "Dimension"
Cohesion: 0.50
Nodes (4): Dimension, Angle, Length, Unitless

### Community 57 - "WallSide"
Cohesion: 0.50
Nodes (4): WallSide, Center, Side1, Side2

### Community 58 - "Entity"
Cohesion: 0.09
Nodes (20): Entity, a, b, center, construction, fit, handles, included (+12 more)

### Community 59 - "xdrive.py"
Cohesion: 0.28
Nodes (15): button(), canvas(), click(), drag(), flush(), geometry(), key(), keycode() (+7 more)

### Community 61 - "UiCommand"
Cohesion: 0.13
Nodes (12): UiCommand, enabled, icon, id, name, panel, run, shortcut (+4 more)

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

### Community 67 - "TEST"
Cohesion: 0.09
Nodes (3): param(), TEST(), tmp()

### Community 68 - "Theme"
Cohesion: 0.22
Nodes (4): Theme, colors_, public, styled_

### Community 69 - "Feature"
Cohesion: 0.09
Nodes (16): Feature, commandId, error, id, inputs, name, parameterNames, rolledBack (+8 more)

### Community 70 - "InputType"
Cohesion: 0.12
Nodes (17): InputType, Axis, Bodies, Body, Bool, Choice, Edges, Faces (+9 more)

### Community 71 - "ParametersDialog.cpp"
Cohesion: 0.07
Nodes (17): QDialog, number(), ParametersDialog, building_, error_, filter_, listener_, ParametersDialog::ParametersDialog() (+9 more)

### Community 72 - "smoke"
Cohesion: 0.33
Nodes (6): smoke(), key, MassProperties, area, centerOfMass, volume

### Community 73 - "Viewport.h"
Cohesion: 0.04
Nodes (20): QLabel, QMouseEvent, ViewInteractor, rgb(), segmentDistance(), Viewport::arrowAt(), Viewport::arrowMouseMove(), Viewport::arrowMousePress() (+12 more)

### Community 75 - ".mouseMove"
Cohesion: 0.11
Nodes (11): ext(), fixedColor(), freeColor(), HandleHit, back, index, spline, lineEntity() (+3 more)

### Community 76 - "Vec3"
Cohesion: 0.17
Nodes (19): SurfacePoint, normal, point, Vec3, boundingBox(), edgeMidpoint(), edgesNear(), frame() (+11 more)

### Community 77 - "MainWindow::MainWindow"
Cohesion: 0.12
Nodes (5): PythonHost, MainWindow::MainWindow(), MainWindow::beginSketch(), MainWindow::exitSketchMode(), MainWindow::showPreferences()

### Community 78 - "math"
Cohesion: 0.07
Nodes (3): dist(), check_regular(), dist_to_line()

### Community 79 - "ExpressionSpinBox"
Cohesion: 0.16
Nodes (4): ExpressionSpinBox, eval_, expression_, shown_

### Community 80 - "SketchDisplay"
Cohesion: 0.12
Nodes (11): ProfileObject, index, sketch, SketchDisplay, construction, curves, fixedCurves, frame (+3 more)

### Community 81 - "Command"
Cohesion: 0.04
Nodes (57): Adding a tool, Command, CommandDef, feature, icon, id, inputs, name (+49 more)

### Community 82 - "Measurement"
Cohesion: 0.13
Nodes (14): Kind, Angle, Area, Length, Volume, Measurement, from, hasLine (+6 more)

### Community 83 - "SketchCurves.cpp"
Cohesion: 0.12
Nodes (19): crossings(), crossingsOf(), Curve2d, curve2d(), periodic, t0, t1, endIsFree() (+11 more)

### Community 85 - "Level"
Cohesion: 0.16
Nodes (13): debug(), error(), info(), Level, Debug, Error, Info, Warning (+5 more)

### Community 86 - "README.md"
Cohesion: 0.11
Nodes (15): Build, Conventions, Development, Tests, Reference parts, Fusion feature checklist, Roadmap, Contents (+7 more)

### Community 89 - "gp_Pnt"
Cohesion: 0.32
Nodes (5): faceNormalAt(), nearestFace(), offsetLoop(), offsetRegion(), pointOnFace()

### Community 90 - "QDialog"
Cohesion: 0.06
Nodes (26): MainWindow::checkInterference(), MainWindow::chooseUnits(), MainWindow::driveJoints(), MainWindow::editAppearance(), MainWindow::editMaterial(), MainWindow::exportDesign(), MainWindow::formatLength(), MainWindow::gridSettings() (+18 more)

### Community 92 - "FileFormat"
Cohesion: 0.17
Nodes (12): FileFormat, Brep, Iges, Obj, Step, Stl, ThreeMF, FormatInfo (+4 more)

### Community 93 - "Known differences still to build"
Cohesion: 0.15
Nodes (12): Data and files, Findings from the videos, Fusion study list, Interface, Known differences still to build, Navigation and display, Selection and the canvas, Sketch (+4 more)

### Community 94 - "TEST"
Cohesion: 0.18
Nodes (3): slurp(), TEST(), tmp()

### Community 95 - "ReplayStep"
Cohesion: 0.04
Nodes (45): Body, color, display, material, name, shape, Component, bodies (+37 more)

### Community 96 - "SketchRecord"
Cohesion: 0.20
Nodes (9): SketchRecord, data, name, offset, plane, Document::setSketch(), Document::sketch(), Document::sketches() (+1 more)

### Community 97 - "cachedProfiles"
Cohesion: 0.22
Nodes (3): MainWindow::updateDragArrow(), cachedProfiles(), keyOf()

### Community 98 - "FakeDoc"
Cohesion: 0.17
Nodes (6): FakeDoc, aborts, commits, items, open, snapshot

### Community 99 - "ParamSet"
Cohesion: 0.09
Nodes (28): ModelParameter, angle, expression, input, label, name, owner, unit (+20 more)

### Community 102 - "Document::load"
Cohesion: 0.22
Nodes (4): doc_(), Document::Document(), Document::ocafBytes(), ocafApplication()

### Community 104 - "BoundingBox"
Cohesion: 0.24
Nodes (9): BoundingBox, max, min, extendedWire(), massProperties(), measure(), offsetOpenWire(), polygonToCircleLoft() (+1 more)

### Community 106 - "SectionState"
Cohesion: 0.25
Nodes (7): SectionState, active, angle, flip, offset, plane, visible

### Community 107 - "Display"
Cohesion: 0.25
Nodes (7): Display, constraints, construction, dimensions, points, profiles, projected

### Community 108 - "cli_main.cpp"
Cohesion: 0.36
Nodes (4): listCommands(), main(), usage(), main()

### Community 110 - "TopologyCounts"
Cohesion: 0.17
Nodes (17): Section, Circular, Square, Triangular, TopologyCounts, edges, faces, shells (+9 more)

### Community 112 - ".redrawAll"
Cohesion: 0.14
Nodes (8): NavPreset, Fusion, SolidWorks, Tinkercad, Viewport::setCurvatureComb(), Viewport::clearDragArrow(), Viewport::clearSecondArrow(), Viewport::setInteractor()

### Community 114 - "uninstall.sh"
Cohesion: 0.52
Nodes (6): die(), manifest_for(), refresh(), uninstall.sh script, step(), usage()

### Community 115 - "install.sh"
Cohesion: 0.60
Nodes (5): die(), refresh(), install.sh script, step(), usage()

### Community 116 - "TestFramework.h"
Cohesion: 0.15
Nodes (11): Result, error, ok, output, captured(), PythonHost::exec(), PythonHost::runScript(), Case (+3 more)

### Community 117 - ".rebuild"
Cohesion: 0.13
Nodes (11): hiddenColour(), qc(), rgb(), Style, Shaded, ShadedEdges, ShadedHidden, Wireframe (+3 more)

### Community 118 - "src/main.cpp"
Cohesion: 0.08
Nodes (4): grabWindowWithPanels(), MarkingMenu, enabled, public

### Community 120 - "Known gaps"
Cohesion: 0.18
Nodes (10): 3D Sketch, Curvature (G2), Emboss, Face patterns, Include 3D Geometry, Known gaps, Project to Surface, Sketch text (+2 more)

### Community 123 - "Placement"
Cohesion: 0.25
Nodes (7): Placement, angle, cx, cy, dx, dy, scale

### Community 126 - "Column"
Cohesion: 0.25
Nodes (8): Column, kComment, kExpression, kName, kParameter, kStar, kUnit, kValue

### Community 129 - "Joint"
Cohesion: 0.36
Nodes (3): Joint, asBuilt_, def_

### Community 130 - "Profile"
Cohesion: 0.33
Nodes (5): Profile, area, face, x, y

### Community 131 - "Architecture"
Cohesion: 0.40
Nodes (4): Architecture, How a command works, The document, Units

### Community 134 - "Axis"
Cohesion: 0.50
Nodes (4): Axis, X, Y, Z

### Community 135 - "BooleanOp"
Cohesion: 0.50
Nodes (4): BooleanOp, Cut, Intersect, Join

### Community 139 - "ThreadInfo"
Cohesion: 0.50
Nodes (4): ThreadInfo, diameter, internal, pitch

### Community 142 - "SplineHandle"
Cohesion: 0.25
Nodes (8): SplineHandle, arm, index, set, tx, ty, x, y

### Community 143 - "ChamferType"
Cohesion: 0.67
Nodes (3): ChamferType, DistanceAngle, TwoDistances

### Community 144 - "ChainSegment"
Cohesion: 0.67
Nodes (3): ChainSegment, entity, forward

## Knowledge Gaps
- **783 isolated node(s):** `ok`, `output`, `error`, `isReal`, `real` (+778 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 1484 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **28 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `optional` connect `optional` to `Viewport`, `MainWindow`, `SketchEditor`, `Kernel.cpp`, `ViewportAnalysis.cpp`, `CommandDialog`, `Io.cpp`, `Parser`, `SketchEditor.cpp`, `ViewportSketch.cpp`, `DocCommands.cpp`, `CommandContext`, `SketchOps.cpp`, `Constraint`, `Unit`, `AnalysisSettings`, `Document.cpp`, `InputDef`, `SketchGeometry.cpp`, `Document::recompute`, `Session`, `Feature`, `Viewport.h`, `Vec3`, `ExpressionSpinBox`, `SketchCurves.cpp`, `ReplayStep`, `SketchRecord`, `ParamSet`?**
  _High betweenness centrality (0.157) - this node is a cross-community bridge._
- **What connects `ok`, `output`, `error` to the rest of the system?**
  _783 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Viewport` be split into smaller, more focused modules?**
  _Cohesion score 0.0159809183064997 - nodes in this community are weakly interconnected._
- **Why does `Viewport` connect `Viewport` to `.eventFilter`, `MainWindow`, `Viewport.cpp`, `Viewport.h`, `AdskModule.cpp`, `optional`, `AnalysisSettings`, `AnalysisSettings`, `SketchDisplay`, `.redrawAll`, `.initializeGL`, `.setSelectionFilter`, `ViewportAnalysis.cpp`, `.rebuild`, `.toPixels`, `SketchCurves.cpp`, `QDialog`, `Sketch`?**
  _High betweenness centrality (0.126) - this node is a cross-community bridge._
- **Should `Icons.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.05032995173840244 - nodes in this community are weakly interconnected._
- **Why does `SketchEditor` connect `SketchEditor` to `Viewport`, `Constraint`, `.eventFilter`, `Viewport.h`, `AdskModule.cpp`, `Display`, `optional`, `.mouseMove`, `Pick`, `Unit`, `SketchEditor.cpp`, `.updatePreview`, `Snap`, `PlaneEdges`, `Entity`, `Session`?**
  _High betweenness centrality (0.118) - this node is a cross-community bridge._
- **Should `Session.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.05627545353572751 - nodes in this community are weakly interconnected._