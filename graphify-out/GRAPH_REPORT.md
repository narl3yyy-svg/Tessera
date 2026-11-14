# Graph Report - tessera  (2026-11-13)

## Corpus Check
- 384 files · ~249,252 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 56 file(s) not represented in the graph (top: .drive 48, (none) 5, .cmake 1)

## Summary
- 3638 nodes · 9293 edges · 126 communities (102 shown, 24 thin omitted)
- Extraction: 85% EXTRACTED · 15% INFERRED · 0% AMBIGUOUS · INFERRED: 1428 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `d1aaf2bb`
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
- Viewport.h
- Kind
- .openMarkingMenu
- CommandDialog
- Io.cpp
- Unit
- MainWindowTools.cpp
- Known gaps
- Document
- MainWindow.cpp
- Architecture
- Sketch.cpp
- ViewportSketch.cpp
- SketchPalette
- Kind
- Inputs
- string
- Colors
- KernelError
- SketchOps.cpp
- ViewportArrow.cpp
- ParameterCompleter
- Constraint
- string
- test_text_box_path.py
- solve
- Snap
- CommandDialog.cpp
- ConstraintType
- AdskModule.cpp
- Pick
- SketchEditor.cpp
- TEST
- Zip.cpp
- AnalysisSettings
- ParamSet
- MainWindowSketch.cpp
- InputDef
- HoleSize
- .toPixels
- ViewportAnalysis.cpp
- Theme.cpp
- Entity
- xdrive.py
- Session
- BodyFrame
- CommandRegistry
- Feature
- BodyFrame
- Theme
- .apply
- ParametersDialog.cpp
- TEST
- curve
- InputType
- Vec3
- QString
- SketchDisplay
- Command
- Measurement
- SketchCurves.cpp
- UiCommand
- Level
- README.md
- string
- test_feature_pattern.py
- rect
- cachedProfiles
- EntityType
- FileFormat
- Known differences still to build
- ReplayStep
- Tool
- FakeDoc
- MainWindowArrow.cpp
- .add
- sstream
- TsrModule.cpp
- WallSide
- Joints
- SectionState
- Display
- main
- smoke
- TopologyCounts
- UserParameter
- BooleanOp
- uninstall.sh
- install.sh
- TestFramework.h
- .redrawAll
- ThreadInfo
- cmath
- test_incremental_replay.py
- Placement
- ChainSegment
- ChamferType
- Placement::apply
- .mouseMove
- DocCommands.cpp
- LAB_NOTES.md
- src/main.cpp
- build.sh
- live-test.sh
- Point
- SplineHandle

## God Nodes (most connected - your core abstractions)
1. `Viewport` - 251 edges
2. `SketchEditor` - 185 edges
3. `MainWindow` - 180 edges
4. `Inputs` - 145 edges
5. `Document` - 118 edges
6. `render()` - 111 edges
7. `CommandContext` - 105 edges
8. `CommandDialog` - 90 edges
9. `Command` - 64 edges
10. `CommandError` - 59 edges

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

## Communities (126 total, 24 thin omitted)

### Community 0 - "Viewport"
Cohesion: 0.02
Nodes (67): view_, QLineEdit, Viewport, analysis_, analysisObjects_, appliedGridStep_, arrowBoxes_, arrowDragging_ (+59 more)

### Community 1 - "Icons.cpp"
Cohesion: 0.06
Nodes (116): arc3Icon(), arcIcon(), arcTangentIcon(), arrow(), axisIcon(), box(), breakIcon(), centerRectIcon() (+108 more)

### Community 2 - "Session.cpp"
Cohesion: 0.06
Nodes (48): CommandSession, inputs_, expressionKey(), checkInputValue(), CommandContext::evaluateExpression(), CommandDef::input(), CommandSession::applyInTransaction(), CommandSession::cancel() (+40 more)

### Community 4 - "MainWindow"
Cohesion: 0.03
Nodes (65): writeLiveGeometry(), CommandDialog, MainWindow, active_, arrowInput_, arrowInput2_, bodiesBeforeCommand_, combEdges_ (+57 more)

### Community 5 - "run_oracle.py"
Cohesion: 0.08
Nodes (54): add_point(), arc_poly(), body_at(), body_list(), build_sketch(), chain(), circumcentre(), cm() (+46 more)

### Community 7 - "Document"
Cohesion: 0.03
Nodes (15): Document, effects_, lastReplayed_, lastReused_, modified_, pendingTools_, registry_, replaying_ (+7 more)

### Community 8 - "Viewport.cpp"
Cohesion: 0.05
Nodes (9): glide(), hiddenColour(), keys(), qc(), QtFrameBuffer, rgb(), sharpEdges(), Viewport::Viewport() (+1 more)

### Community 9 - "SketchEditor"
Cohesion: 0.03
Nodes (55): HandleHit, back, index, spline, PlaneEdges, arcs, curves, segments (+47 more)

### Community 10 - "Document::recompute"
Cohesion: 0.18
Nodes (8): Document::expressionEnv(), Document::recompute(), Document::recordFeature(), Document::removeFeature(), Document::setFeatureInputs(), Document::setFeatureSuppressed(), featureData(), toJson()

### Community 11 - "optional"
Cohesion: 0.08
Nodes (13): optional, Dimension, Angle, Length, Unitless, isEmpty(), Value, CommandRegistry::all() (+5 more)

### Community 13 - "Viewport.h"
Cohesion: 0.06
Nodes (18): MarkingMenu::mouseMoveEvent(), AnalysisKind, CurvatureMap, Draft, None, Zebra, AnalysisSettings, curvatureScale (+10 more)

### Community 14 - "Kind"
Cohesion: 0.07
Nodes (26): ConstructPlane, def_, kind_, EdgeFeature, def_, kind_, Kind, Angle (+18 more)

### Community 15 - ".openMarkingMenu"
Cohesion: 0.06
Nodes (10): PythonHost, commandIcon(), MainWindow::MainWindow(), qs(), MainWindow::beginSketch(), MainWindow::enterSketchMode(), MainWindow::exitSketchMode(), MainWindow::onEdgeClicked() (+2 more)

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
Cohesion: 0.05
Nodes (28): QDialog, MainWindow::applySection(), MainWindow::checkInterference(), MainWindow::chooseUnits(), MainWindow::driveJoints(), MainWindow::exportDesign(), MainWindow::formatLength(), MainWindow::gridSettings() (+20 more)

### Community 20 - "Known gaps"
Cohesion: 0.33
Nodes (5): Include 3D Geometry, Known gaps, Sketch text, Splines and conics, Visual styles

### Community 21 - "Document"
Cohesion: 0.17
Nodes (11): applyOperation(), bodyCentre(), ConstructAxisPoint, def_, kind_, jointOrigin(), JointPick, frame (+3 more)

### Community 23 - "Architecture"
Cohesion: 0.40
Nodes (4): Architecture, How a command works, The document, Units

### Community 24 - "Sketch.cpp"
Cohesion: 0.05
Nodes (33): SketchError, SplineKind, Conic, Control, Fit, entityTypeName(), Sketch::addConic(), Sketch::addEllipticalArc() (+25 more)

### Community 25 - "ViewportSketch.cpp"
Cohesion: 0.09
Nodes (6): faceStyle(), lineStyle(), rgb(), Viewport::lookAt(), Viewport::planePoint(), Viewport::toWidget()

### Community 26 - "SketchPalette"
Cohesion: 0.05
Nodes (25): MainWindow::buildSketchTab(), QCheckBox, QLabel, QWidget, SketchEditor, SketchPalette, body_, constraints_ (+17 more)

### Community 27 - "Kind"
Cohesion: 0.07
Nodes (24): Hit, index, kind, HudField, edit, editing, kind, locked (+16 more)

### Community 28 - "Inputs"
Cohesion: 0.08
Nodes (19): CommandContext, CommandError, Inputs, CommandSession::CommandSession(), getBool(), getInt(), getReal(), bodyName() (+11 more)

### Community 29 - "string"
Cohesion: 0.10
Nodes (24): DocumentError, checkViewName(), Document::abortTransaction(), Document::addBody(), Document::addNamedView(), Document::addUserParameter(), Document::commitTransaction(), Document::openTransaction() (+16 more)

### Community 30 - "Colors"
Cohesion: 0.07
Nodes (28): Colors, base, border, cubeBox, cubeText, errorBackground, grid, gridMajor (+20 more)

### Community 31 - "KernelError"
Cohesion: 0.25
Nodes (29): KernelError, asSolid(), boolean(), chamfer(), chamferEx(), deleteFaces(), draft(), extrude() (+21 more)

### Community 32 - "SketchOps.cpp"
Cohesion: 0.24
Nodes (26): at(), chainOf(), chamferCorner(), circularPattern(), copyEntities(), cross(), dot(), extendLine() (+18 more)

### Community 33 - "ViewportArrow.cpp"
Cohesion: 0.07
Nodes (18): Viewport::frontEdgeOwner(), rgb(), segmentDistance(), Viewport::arrowAt(), Viewport::arrowMouseMove(), Viewport::arrowMousePress(), Viewport::arrowMouseRelease(), Viewport::arrowParam() (+10 more)

### Community 34 - "ParameterCompleter"
Cohesion: 0.12
Nodes (8): ParameterCompleter, completer_, edit_, names_, ParameterCompleter::ParameterCompleter(), public, QCompleter, QLineEdit

### Community 35 - "Constraint"
Cohesion: 0.08
Nodes (21): Constraint, driven, entities, expression, hasLabel, labelX, labelY, name (+13 more)

### Community 36 - "string"
Cohesion: 0.10
Nodes (14): AddUserParameter, def_, Hole, def_, isIdentifier(), NewComponent, def_, Pipe (+6 more)

### Community 38 - "solve"
Cohesion: 0.17
Nodes (14): set, addConstraintChecked(), Layout, n, px, py, rad, makeLayout() (+6 more)

### Community 39 - "Snap"
Cohesion: 0.11
Nodes (18): Snap, alignX, alignY, bodyArc, bodySegment, entity, fromX, fromY (+10 more)

### Community 41 - "ConstraintType"
Cohesion: 0.08
Nodes (24): ConstraintType, Angle, Coincident, Collinear, Concentric, Diameter, Distance, Equal (+16 more)

### Community 42 - "AdskModule.cpp"
Cohesion: 0.09
Nodes (16): Application, bindAdsk(), BRepBodies, BRepBody, index, Component, Design, Product (+8 more)

### Community 43 - "Pick"
Cohesion: 0.13
Nodes (14): Pick, bodyArc, bodyPoint, bodySegment, hit, midpointOf, onEntity, onXAxis (+6 more)

### Community 46 - "Zip.cpp"
Cohesion: 0.11
Nodes (14): Entry, data, name, ZipError, crc32(), get16(), get32(), put16() (+6 more)

### Community 47 - "AnalysisSettings"
Cohesion: 0.10
Nodes (16): DragArrow, base, dir, radius, ref, ring, value, PendingLook (+8 more)

### Community 49 - "ParamSet"
Cohesion: 0.08
Nodes (28): dimensionOf(), ModelParameter, angle, expression, input, label, name, owner (+20 more)

### Community 50 - "MainWindowSketch.cpp"
Cohesion: 0.06
Nodes (17): QAbstractButton, QAction, MainWindow::cancelSketch(), MainWindow::editSketch(), MainWindow::finishSketch(), MainWindow::onProfileClicked(), MainWindow::originalShape(), MainWindow::sketchPalette() (+9 more)

### Community 51 - "InputDef"
Cohesion: 0.09
Nodes (21): InputDef, choices, defaultValue, id, label, max, min, minExclusive (+13 more)

### Community 52 - "HoleSize"
Cohesion: 0.50
Nodes (4): HoleSize, modeled, pitch, radius

### Community 54 - "ViewportAnalysis.cpp"
Cohesion: 0.11
Nodes (6): packed(), ramp(), shade(), Viewport::buildAnalysis(), Viewport::setCurvatureComb(), f

### Community 56 - "Theme.cpp"
Cohesion: 0.19
Nodes (6): setIconTheme(), darkColors(), darkPalette(), darkStyleSheet(), lightColors(), lightStyleSheet()

### Community 58 - "Entity"
Cohesion: 0.09
Nodes (13): QObject, Entity, a, b, center, construction, fit, handles (+5 more)

### Community 59 - "xdrive.py"
Cohesion: 0.28
Nodes (15): button(), canvas(), click(), drag(), flush(), geometry(), key(), keycode() (+7 more)

### Community 62 - "Session"
Cohesion: 0.08
Nodes (7): PythonHost::PythonHost(), Session, commands_, doc_, listeners_, nextListener_, path_

### Community 64 - "BodyFrame"
Cohesion: 0.10
Nodes (31): completeEdgeReferences(), completeFaceReferences(), decode(), decodeFaces(), dot(), edgeReference(), EdgeSig, full (+23 more)

### Community 65 - "CommandRegistry"
Cohesion: 0.12
Nodes (4): CommandRegistry, cmds_, CommandRegistry::add(), TEST()

### Community 66 - "Feature"
Cohesion: 0.12
Nodes (16): Feature, commandId, error, id, inputs, name, parameterNames, rolledBack (+8 more)

### Community 67 - "BodyFrame"
Cohesion: 0.15
Nodes (14): BodyFrame, diag, dx, dy, dz, x0, y0, z0 (+6 more)

### Community 68 - "Theme"
Cohesion: 0.22
Nodes (4): Theme, colors_, public, styled_

### Community 69 - ".apply"
Cohesion: 0.16
Nodes (6): Extrude, def_, Joint, def_, Sweep, def_

### Community 71 - "ParametersDialog.cpp"
Cohesion: 0.06
Nodes (24): Column, kComment, kExpression, kName, kParameter, kStar, kUnit, kValue (+16 more)

### Community 72 - "TEST"
Cohesion: 0.09
Nodes (3): param(), TEST(), tmp()

### Community 73 - "curve"
Cohesion: 0.31
Nodes (10): curve(), curves(), entityCurves(), interiorPoint(), profileAt(), profiles(), splineHandles(), textShape() (+2 more)

### Community 75 - "InputType"
Cohesion: 0.12
Nodes (17): InputType, Axis, Bodies, Body, Bool, Choice, Edges, Faces (+9 more)

### Community 76 - "Vec3"
Cohesion: 0.17
Nodes (19): SurfacePoint, normal, point, Vec3, boundingBox(), edgeMidpoint(), edgesNear(), frame() (+11 more)

### Community 77 - "QString"
Cohesion: 0.12
Nodes (5): ExpressionSpinBox, eval_, expression_, shown_, formatNumber()

### Community 80 - "SketchDisplay"
Cohesion: 0.09
Nodes (16): ProfileObject, index, sketch, SketchDisplay, construction, curves, fixedCurves, frame (+8 more)

### Community 81 - "Command"
Cohesion: 0.03
Nodes (58): Adding a tool, Command, CommandDef, feature, icon, id, inputs, name (+50 more)

### Community 82 - "Measurement"
Cohesion: 0.09
Nodes (20): BoundingBox, max, min, Kind, Angle, Area, Length, Volume (+12 more)

### Community 83 - "SketchCurves.cpp"
Cohesion: 0.13
Nodes (18): crossings(), crossingsOf(), Curve2d, curve2d(), periodic, t0, t1, endIsFree() (+10 more)

### Community 84 - "UiCommand"
Cohesion: 0.07
Nodes (22): UiCommand, enabled, icon, id, name, panel, run, shortcut (+14 more)

### Community 85 - "Level"
Cohesion: 0.12
Nodes (13): debug(), error(), info(), Level, Debug, Error, Info, Warning (+5 more)

### Community 86 - "README.md"
Cohesion: 0.11
Nodes (15): Build, Conventions, Development, Tests, Reference parts, Fusion feature checklist, Roadmap, Contents (+7 more)

### Community 87 - "string"
Cohesion: 0.06
Nodes (45): ConstructionPlane, name, spec, SketchRecord, data, name, offset, plane (+37 more)

### Community 89 - "rect"
Cohesion: 0.28
Nodes (3): SelectionBox, crossing, rect()

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

### Community 97 - "Tool"
Cohesion: 0.16
Nodes (6): SketchEditor::SketchEditor(), edges, Tool, op, shape, target

### Community 98 - "FakeDoc"
Cohesion: 0.17
Nodes (6): FakeDoc, aborts, commits, items, open, snapshot

### Community 100 - "MainWindowArrow.cpp"
Cohesion: 0.13
Nodes (8): ArrowPlacement, base, dir, edgePlacement(), facesPlacement(), MainWindow::attachArrowCompleters(), MainWindow::patternCentre(), MainWindow::pickedFaces()

### Community 102 - "sstream"
Cohesion: 0.17
Nodes (5): doc_(), Document::Document(), Document::ocafBytes(), ocafApplication(), Document::load()

### Community 103 - "TsrModule.cpp"
Cohesion: 0.25
Nodes (4): bindTsr(), fromPy(), toPy(), typeName()

### Community 104 - "WallSide"
Cohesion: 0.50
Nodes (4): WallSide, Center, Side1, Side2

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

### Community 109 - "smoke"
Cohesion: 0.33
Nodes (6): smoke(), key, MassProperties, area, centerOfMass, volume

### Community 110 - "TopologyCounts"
Cohesion: 0.16
Nodes (18): Section, Circular, Square, Triangular, TopologyCounts, edges, faces, shells (+10 more)

### Community 111 - "UserParameter"
Cohesion: 0.33
Nodes (6): UserParameter, comment, expression, name, unit, value

### Community 113 - "BooleanOp"
Cohesion: 0.50
Nodes (4): BooleanOp, Cut, Intersect, Join

### Community 114 - "uninstall.sh"
Cohesion: 0.52
Nodes (6): die(), manifest_for(), refresh(), uninstall.sh script, step(), usage()

### Community 115 - "install.sh"
Cohesion: 0.60
Nodes (5): die(), refresh(), install.sh script, step(), usage()

### Community 116 - "TestFramework.h"
Cohesion: 0.29
Nodes (7): Result, error, ok, output, captured(), PythonHost::exec(), PythonHost::runScript()

### Community 117 - ".redrawAll"
Cohesion: 0.11
Nodes (7): NavPreset, Fusion, SolidWorks, Tinkercad, Viewport::clearDragArrow(), Viewport::clearSecondArrow(), Viewport::setInteractor()

### Community 118 - "ThreadInfo"
Cohesion: 0.50
Nodes (4): ThreadInfo, diameter, internal, pitch

### Community 120 - "cmath"
Cohesion: 0.13
Nodes (6): Case, fn, name, fail(), Failure, Register

### Community 123 - "Placement"
Cohesion: 0.25
Nodes (7): Placement, angle, cx, cy, dx, dy, scale

### Community 124 - "ChainSegment"
Cohesion: 0.67
Nodes (3): ChainSegment, entity, forward

### Community 125 - "ChamferType"
Cohesion: 0.67
Nodes (3): ChamferType, DistanceAngle, TwoDistances

### Community 128 - ".mouseMove"
Cohesion: 0.06
Nodes (26): ccwContains(), circumcircle(), ext(), fixedColor(), freeColor(), lineEntity(), qc(), rgb() (+18 more)

### Community 131 - "DocCommands.cpp"
Cohesion: 0.11
Nodes (25): axisOf(), checkPattern(), CopyFn, differenceOrNull(), evaluateDimensions(), Loft, def_, makeBox() (+17 more)

### Community 134 - "src/main.cpp"
Cohesion: 0.09
Nodes (4): grabWindowWithPanels(), MarkingMenu, enabled, public

### Community 141 - "Point"
Cohesion: 0.52
Nodes (6): Point, x, y, z, customPlaneSpec(), toDxf()

### Community 142 - "SplineHandle"
Cohesion: 0.29
Nodes (7): SplineHandle, arm, index, tx, ty, x, y

## Knowledge Gaps
- **749 isolated node(s):** `ok`, `output`, `error`, `isReal`, `real` (+744 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 1414 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **24 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `optional` connect `optional` to `Viewport`, `DocCommands.cpp`, `MainWindow`, `Kernel.cpp`, `Viewport.h`, `Io.cpp`, `Unit`, `ViewportSketch.cpp`, `ViewportArrow.cpp`, `Constraint`, `string`, `CommandDialog.cpp`, `SketchEditor.cpp`, `AnalysisSettings`, `ParamSet`, `InputDef`, `Entity`, `Session`, `Feature`, `Vec3`, `QString`, `SketchCurves.cpp`, `string`, `FileFormat`, `ReplayStep`, `MainWindowArrow.cpp`, `Joints`?**
  _High betweenness centrality (0.100) - this node is a cross-community bridge._
- **What connects `ok`, `output`, `error` to the rest of the system?**
  _749 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Viewport` be split into smaller, more focused modules?**
  _Cohesion score 0.01633870005963029 - nodes in this community are weakly interconnected._
- **Why does `Viewport` connect `Viewport` to `ViewportArrow.cpp`, `Viewport.cpp`, `optional`, `.initializeGL`, `Viewport.h`, `AnalysisSettings`, `SketchDisplay`, `.openMarkingMenu`, `SketchCurves.cpp`, `MainWindowTools.cpp`, `.redrawAll`, `.toPixels`, `ViewportAnalysis.cpp`, `rect`?**
  _High betweenness centrality (0.085) - this node is a cross-community bridge._
- **Should `Icons.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.05708661417322835 - nodes in this community are weakly interconnected._
- **Why does `MainWindow` connect `MainWindow` to `ParameterCompleter`, `cachedProfiles`, `ParametersDialog.cpp`, `SectionState`, `optional`, `smoke`, `.openMarkingMenu`, `MainWindowSketch.cpp`, `MainWindowTools.cpp`, `UiCommand`, `MainWindow.cpp`, `SketchPalette`, `Session`?**
  _High betweenness centrality (0.084) - this node is a cross-community bridge._
- **Should `Session.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.05672926447574335 - nodes in this community are weakly interconnected._