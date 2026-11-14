# Graph Report - tessera  (2026-11-13)

## Corpus Check
- 385 files · ~252,073 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 56 file(s) not represented in the graph (top: .drive 48, (none) 5, .cmake 1)

## Summary
- 3674 nodes · 9411 edges · 142 communities (117 shown, 25 thin omitted)
- Extraction: 85% EXTRACTED · 15% INFERRED · 0% AMBIGUOUS · INFERRED: 1444 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `5ae37631`
- Run `git rev-parse HEAD` and compare to check if the graph is stale.
- Run `graphify update .` after code changes (no API cost).

## Community Hubs (Navigation)
- Viewport
- Icons.cpp
- Session.cpp
- tsr
- MainWindow
- run_oracle.py
- Feature
- Document
- Viewport.cpp
- SketchEditor
- Expression.cpp
- optional
- Kernel.cpp
- AnalysisSettings
- Kind
- .openMarkingMenu
- CommandDialog
- Io.cpp
- Parser
- MainWindowTools.cpp
- Known gaps
- Document
- MainWindow.cpp
- Architecture
- Affine
- ViewportSketch.cpp
- SketchPalette
- CommandRegistry::run
- Inputs
- string
- Colors
- KernelError
- SketchOps.cpp
- ViewportArrow.cpp
- ParameterCompleter
- Constraint
- CommandError
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
- Sketch.cpp
- ParamSet
- MainWindowSketch.cpp
- InputDef
- .apply
- .toPixels
- ViewportAnalysis.cpp
- Document::recompute
- Command.cpp
- Profile
- Entity
- xdrive.py
- Session
- Theme.cpp
- BodyFrame
- CommandRegistry
- Tool
- BodyFrame
- Theme
- Joint
- ParametersDialog.cpp
- TEST
- curve
- Kind
- InputType
- Vec3
- CommandDialog::CommandDialog
- CommandDialog::CommandDialog
- SketchDisplay
- Command
- Measurement
- SketchCurves.cpp
- UiCommand
- Level
- README.md
- string
- test_feature_pattern.py
- path
- EntityType
- FileFormat
- Known differences still to build
- TEST
- ReplayStep
- bindAdsk
- .features
- FakeDoc
- includeEdges
- MainWindowArrow.cpp
- .add
- sstream
- MarkingMenu
- BoundingBox
- Joints
- SectionState
- Display
- main
- smoke
- TopologyCounts
- Document::reevaluateParameters
- MetricSize
- Mesh
- uninstall.sh
- install.sh
- TestFramework.h
- .rebuild
- Column
- Axis
- BooleanOp
- test_incremental_replay.py
- Placement
- ChainSegment
- AddUserParameter
- ThreadInfo
- MainWindow::setSelectionFilter
- .updatePreview
- ChamferType
- Placement::apply
- DocCommands.cpp
- Unit
- LAB_NOTES.md
- src/main.cpp
- build.sh
- live-test.sh
- PYBIND11_EMBEDDED_MODULE
- Point
- SplineHandle

## God Nodes (most connected - your core abstractions)
1. `Viewport` - 255 edges
2. `SketchEditor` - 185 edges
3. `MainWindow` - 180 edges
4. `Inputs` - 148 edges
5. `Document` - 118 edges
6. `render()` - 116 edges
7. `CommandContext` - 108 edges
8. `CommandDialog` - 90 edges
9. `Command` - 65 edges
10. `CommandError` - 60 edges

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

## Communities (142 total, 25 thin omitted)

### Community 0 - "Viewport"
Cohesion: 0.02
Nodes (68): view_, QLineEdit, Viewport, analysis_, analysisObjects_, appliedGridStep_, arrowBoxes_, arrowDragging_ (+60 more)

### Community 1 - "Icons.cpp"
Cohesion: 0.06
Nodes (119): accessibilityIcon(), arc3Icon(), arcIcon(), arcTangentIcon(), arrow(), axisIcon(), box(), breakIcon() (+111 more)

### Community 2 - "Session.cpp"
Cohesion: 0.13
Nodes (30): historyEdit(), OwnedCommand, owned, OwningCommandSession, plainEdit(), Session::addListener(), Session::addNamedView(), Session::begin() (+22 more)

### Community 4 - "MainWindow"
Cohesion: 0.02
Nodes (64): CommandDialog, MainWindow, active_, arrowInput_, arrowInput2_, bodiesBeforeCommand_, combEdges_, combPicking_ (+56 more)

### Community 5 - "run_oracle.py"
Cohesion: 0.08
Nodes (54): add_point(), arc_poly(), body_at(), body_list(), build_sketch(), chain(), circumcentre(), cm() (+46 more)

### Community 6 - "Feature"
Cohesion: 0.09
Nodes (17): Feature, commandId, error, id, inputs, name, parameterNames, rolledBack (+9 more)

### Community 7 - "Document"
Cohesion: 0.03
Nodes (15): Document, effects_, lastReplayed_, lastReused_, modified_, pendingTools_, registry_, replaying_ (+7 more)

### Community 8 - "Viewport.cpp"
Cohesion: 0.04
Nodes (11): glide(), keys(), NavPreset, Fusion, SolidWorks, Tinkercad, QKeyEvent, QtFrameBuffer (+3 more)

### Community 9 - "SketchEditor"
Cohesion: 0.03
Nodes (51): PlaneEdges, arcs, curves, segments, vertices, SketchEditor, arcDrag_, arcDragMoved_ (+43 more)

### Community 10 - "Expression.cpp"
Cohesion: 0.13
Nodes (17): ExpressionEnv, lengthUnit, lookup, ExpressionError, evaluateExpression(), evaluateQuantity(), expressionReferences(), isConstantName() (+9 more)

### Community 11 - "optional"
Cohesion: 0.09
Nodes (5): isEmpty(), Value, Document, fail(), Failure

### Community 13 - "AnalysisSettings"
Cohesion: 0.11
Nodes (18): AnalysisKind, Accessibility, CurvatureMap, Draft, Isocurve, MinimumRadius, None, Zebra (+10 more)

### Community 14 - "Kind"
Cohesion: 0.07
Nodes (26): ConstructPlane, def_, kind_, EdgeFeature, def_, kind_, Kind, Angle (+18 more)

### Community 15 - ".openMarkingMenu"
Cohesion: 0.15
Nodes (5): MainWindow::beginSketch(), MainWindow::buildSketchTab(), MainWindow::enterSketchMode(), QTimer, Viewport::selectArrowValue()

### Community 16 - "CommandDialog"
Cohesion: 0.05
Nodes (31): CommandDialog, bodiesId_, bodiesLabel_, bodyInput_, buttons_, cmd_, conditional_, edgesId_ (+23 more)

### Community 17 - "Io.cpp"
Cohesion: 0.10
Nodes (4): fromBrep(), lower(), toBrep(), xmlEscape()

### Community 18 - "Parser"
Cohesion: 0.19
Nodes (13): Quantity, angle, length, value, describe(), isIdentChar(), Parser, ang_ (+5 more)

### Community 19 - "MainWindowTools.cpp"
Cohesion: 0.07
Nodes (27): QDialog, MainWindow::checkInterference(), MainWindow::chooseUnits(), MainWindow::driveJoints(), MainWindow::exportDesign(), MainWindow::formatLength(), MainWindow::gridSettings(), MainWindow::insertFile() (+19 more)

### Community 20 - "Known gaps"
Cohesion: 0.33
Nodes (5): Include 3D Geometry, Known gaps, Sketch text, Splines and conics, Visual styles

### Community 21 - "Document"
Cohesion: 0.22
Nodes (7): ConstructAxisPoint, def_, kind_, jointOrigin(), JointPick, frame, revolveAxis()

### Community 22 - "MainWindow.cpp"
Cohesion: 0.07
Nodes (8): retintIcons(), setIcon(), commandIcon(), flatButton(), MainWindow::MainWindow(), qs(), MainWindow::exitSketchMode(), QToolButton

### Community 23 - "Architecture"
Cohesion: 0.40
Nodes (4): Architecture, How a command works, The document, Units

### Community 24 - "Affine"
Cohesion: 0.13
Nodes (14): Affine, a, b, c, d, e, Builder, byPlace_ (+6 more)

### Community 25 - "ViewportSketch.cpp"
Cohesion: 0.05
Nodes (7): QLabel, faceStyle(), lineStyle(), rgb(), Viewport::lookAt(), Viewport::planePoint(), Viewport::toWidget()

### Community 26 - "SketchPalette"
Cohesion: 0.06
Nodes (24): QCheckBox, QLabel, QWidget, SketchEditor, SketchPalette, body_, constraints_, construction_ (+16 more)

### Community 27 - "CommandRegistry::run"
Cohesion: 0.22
Nodes (4): CommandRegistry::add(), CommandRegistry::all(), CommandRegistry::find(), CommandRegistry::run()

### Community 28 - "Inputs"
Cohesion: 0.07
Nodes (18): CommandContext, Inputs, CommandSession::CommandSession(), checkBody(), checkPattern(), defaultBody(), isIdentifier(), Loft (+10 more)

### Community 29 - "string"
Cohesion: 0.12
Nodes (34): DocumentError, checkViewName(), Document::addBody(), Document::addNamedView(), Document::addUserParameter(), Document::axisFrame(), Document::ocafBytes(), Document::openTransaction() (+26 more)

### Community 30 - "Colors"
Cohesion: 0.07
Nodes (28): Colors, base, border, cubeBox, cubeText, errorBackground, grid, gridMajor (+20 more)

### Community 31 - "KernelError"
Cohesion: 0.24
Nodes (30): KernelError, asSolid(), boolean(), chamfer(), chamferEx(), deleteFaces(), draft(), extrude() (+22 more)

### Community 32 - "SketchOps.cpp"
Cohesion: 0.24
Nodes (26): at(), chainOf(), chamferCorner(), circularPattern(), copyEntities(), cross(), dot(), extendLine() (+18 more)

### Community 33 - "ViewportArrow.cpp"
Cohesion: 0.05
Nodes (24): MarkingMenu::mouseMoveEvent(), QMouseEvent, ViewInteractor, Viewport::frontEdgeOwner(), rgb(), segmentDistance(), Viewport::arrowAt(), Viewport::arrowMouseMove() (+16 more)

### Community 34 - "ParameterCompleter"
Cohesion: 0.13
Nodes (8): ParameterCompleter, completer_, edit_, names_, ParameterCompleter::ParameterCompleter(), public, QCompleter, QLineEdit

### Community 35 - "Constraint"
Cohesion: 0.08
Nodes (20): Constraint, driven, entities, expression, hasLabel, labelX, labelY, name (+12 more)

### Community 36 - "CommandError"
Cohesion: 0.09
Nodes (32): CommandError, getBool(), getReal(), applyOperation(), bodyCentre(), bodyName(), CopyFn, differenceOrNull() (+24 more)

### Community 38 - "solve"
Cohesion: 0.18
Nodes (13): set, addConstraintChecked(), Layout, n, px, py, rad, makeLayout() (+5 more)

### Community 39 - "Snap"
Cohesion: 0.07
Nodes (22): HandleHit, back, index, spline, Snap, alignX, alignY, bodyArc (+14 more)

### Community 41 - "ConstraintType"
Cohesion: 0.09
Nodes (23): ConstraintType, Angle, Coincident, Collinear, Concentric, Diameter, Distance, Equal (+15 more)

### Community 42 - "AdskModule.cpp"
Cohesion: 0.12
Nodes (13): Application, BRepBodies, Component, Design, Product, raiseIfError(), UserParameter, name (+5 more)

### Community 43 - "Pick"
Cohesion: 0.09
Nodes (17): Hit, index, kind, Pick, bodyArc, bodyPoint, bodySegment, hit (+9 more)

### Community 44 - "SketchEditor.cpp"
Cohesion: 0.11
Nodes (3): angleInArc(), circumcircle(), segDistance()

### Community 46 - "Zip.cpp"
Cohesion: 0.25
Nodes (8): ZipError, crc32(), get16(), get32(), put16(), put32(), read(), write()

### Community 47 - "AnalysisSettings"
Cohesion: 0.10
Nodes (16): DragArrow, base, dir, radius, ref, ring, value, PendingLook (+8 more)

### Community 48 - "Sketch.cpp"
Cohesion: 0.08
Nodes (20): SketchError, SplineKind, Conic, Control, Fit, entityTypeName(), isDimension(), Sketch::addConstraint() (+12 more)

### Community 49 - "ParamSet"
Cohesion: 0.08
Nodes (31): ModelParameter, angle, expression, input, label, name, owner, unit (+23 more)

### Community 50 - "MainWindowSketch.cpp"
Cohesion: 0.07
Nodes (15): MainWindow::cancelSketch(), MainWindow::editSketch(), MainWindow::finishSketch(), MainWindow::onEdgeClicked(), MainWindow::onProfileClicked(), MainWindow::originalShape(), MainWindow::sketchPalette(), MainWindow::sketchVisible() (+7 more)

### Community 51 - "InputDef"
Cohesion: 0.09
Nodes (21): InputDef, choices, defaultValue, id, label, max, min, minExclusive (+13 more)

### Community 52 - ".apply"
Cohesion: 0.13
Nodes (13): getInt(), Hole, def_, HoleSize, holeSize(), modeled, pitch, radius (+5 more)

### Community 54 - "ViewportAnalysis.cpp"
Cohesion: 0.10
Nodes (6): packed(), ramp(), shade(), Viewport::buildAnalysis(), Viewport::setCurvatureComb(), f

### Community 55 - "Document::recompute"
Cohesion: 0.17
Nodes (8): Document::expressionEnv(), Document::recompute(), Document::recordFeature(), Document::removeFeature(), Document::setFeatureInputs(), Document::setFeatureSuppressed(), featureData(), toJson()

### Community 56 - "Command.cpp"
Cohesion: 0.14
Nodes (12): CommandSession, inputs_, checkInputValue(), CommandContext::evaluateExpression(), CommandDef::input(), CommandSession::applyInTransaction(), CommandSession::cancel(), CommandSession::execute() (+4 more)

### Community 57 - "Profile"
Cohesion: 0.33
Nodes (5): Profile, area, face, x, y

### Community 58 - "Entity"
Cohesion: 0.07
Nodes (22): MainWindow::attachArrowCompleters(), Entity, a, b, center, construction, fit, handles (+14 more)

### Community 59 - "xdrive.py"
Cohesion: 0.28
Nodes (15): button(), canvas(), click(), drag(), flush(), geometry(), key(), keycode() (+7 more)

### Community 62 - "Session"
Cohesion: 0.08
Nodes (7): PythonHost::PythonHost(), Session, commands_, doc_, listeners_, nextListener_, path_

### Community 63 - "Theme.cpp"
Cohesion: 0.21
Nodes (6): setIconTheme(), darkColors(), darkPalette(), darkStyleSheet(), lightColors(), lightStyleSheet()

### Community 64 - "BodyFrame"
Cohesion: 0.12
Nodes (28): completeEdgeReferences(), completeFaceReferences(), decode(), decodeFaces(), edgeReference(), EdgeSig, full, normals (+20 more)

### Community 65 - "CommandRegistry"
Cohesion: 0.14
Nodes (3): CommandRegistry, cmds_, TEST()

### Community 66 - "Tool"
Cohesion: 0.16
Nodes (6): SketchEditor::SketchEditor(), edges, Tool, op, shape, target

### Community 67 - "BodyFrame"
Cohesion: 0.13
Nodes (14): BodyFrame, diag, dx, dy, dz, x0, y0, z0 (+6 more)

### Community 68 - "Theme"
Cohesion: 0.22
Nodes (4): Theme, colors_, public, styled_

### Community 71 - "ParametersDialog.cpp"
Cohesion: 0.08
Nodes (16): number(), ParametersDialog, building_, error_, filter_, listener_, ParametersDialog::ParametersDialog(), public (+8 more)

### Community 72 - "TEST"
Cohesion: 0.09
Nodes (3): param(), TEST(), tmp()

### Community 73 - "curve"
Cohesion: 0.45
Nodes (8): curve(), curves(), entityCurves(), profileAt(), profiles(), splineHandles(), textShape(), toWorld()

### Community 74 - "Kind"
Cohesion: 0.09
Nodes (21): HudField, edit, editing, kind, locked, value, Kind, Angle (+13 more)

### Community 75 - "InputType"
Cohesion: 0.08
Nodes (21): bindTsr(), fromPy(), toPy(), typeName(), InputType, Axis, Bodies, Body (+13 more)

### Community 76 - "Vec3"
Cohesion: 0.14
Nodes (20): SurfacePoint, normal, point, Vec3, boundingBox(), dot(), edgeMidpoint(), edgesNear() (+12 more)

### Community 77 - "CommandDialog::CommandDialog"
Cohesion: 0.17
Nodes (6): CommandDialog::CommandDialog(), Dimension, Angle, Length, Unitless, dimensionOf()

### Community 79 - "CommandDialog::CommandDialog"
Cohesion: 0.16
Nodes (5): ExpressionSpinBox, eval_, expression_, shown_, formatNumber()

### Community 80 - "SketchDisplay"
Cohesion: 0.12
Nodes (11): ProfileObject, index, sketch, SketchDisplay, construction, curves, fixedCurves, frame (+3 more)

### Community 81 - "Command"
Cohesion: 0.04
Nodes (55): Adding a tool, Command, CommandDef, feature, icon, id, inputs, name (+47 more)

### Community 82 - "Measurement"
Cohesion: 0.11
Nodes (17): Kind, Angle, Area, Length, Volume, Measurement, from, hasLine (+9 more)

### Community 83 - "SketchCurves.cpp"
Cohesion: 0.14
Nodes (17): crossings(), crossingsOf(), Curve2d, curve2d(), periodic, t0, t1, endIsFree() (+9 more)

### Community 84 - "UiCommand"
Cohesion: 0.07
Nodes (19): UiCommand, enabled, icon, id, name, panel, run, shortcut (+11 more)

### Community 85 - "Level"
Cohesion: 0.16
Nodes (13): debug(), error(), info(), Level, Debug, Error, Info, Warning (+5 more)

### Community 86 - "README.md"
Cohesion: 0.11
Nodes (15): Build, Conventions, Development, Tests, Reference parts, Fusion feature checklist, Roadmap, Contents (+7 more)

### Community 87 - "string"
Cohesion: 0.06
Nodes (31): optional, ConstructionPlane, name, spec, bodyNumber(), Document::abortTransaction(), Document::bodies(), Document::body() (+23 more)

### Community 90 - "path"
Cohesion: 0.31
Nodes (11): NamedShape, compoundOf(), exportShapes(), fmt(), formatForPath(), importShape(), meshOf(), scaled() (+3 more)

### Community 91 - "EntityType"
Cohesion: 0.29
Nodes (7): EntityType, Arc, Circle, Ellipse, Line, Spline, isRound()

### Community 92 - "FileFormat"
Cohesion: 0.17
Nodes (12): FileFormat, Brep, Iges, Obj, Step, Stl, ThreeMF, FormatInfo (+4 more)

### Community 93 - "Known differences still to build"
Cohesion: 0.15
Nodes (12): Data and files, Findings from the videos, Fusion study list, Interface, Known differences still to build, Navigation and display, Selection and the canvas, Sketch (+4 more)

### Community 94 - "TEST"
Cohesion: 0.15
Nodes (6): Entry, data, name, slurp(), TEST(), tmp()

### Community 95 - "ReplayStep"
Cohesion: 0.05
Nodes (38): Body, display, name, shape, Component, bodies, name, ConstructionAxis (+30 more)

### Community 96 - "bindAdsk"
Cohesion: 0.29
Nodes (3): bindAdsk(), BRepBody, index

### Community 97 - ".features"
Cohesion: 0.28
Nodes (6): Document::nextAxisName(), Document::nextComponentName(), Document::nextPlaneName(), Document::nextPointName(), Document::nextSketchName(), freeName()

### Community 98 - "FakeDoc"
Cohesion: 0.17
Nodes (6): FakeDoc, aborts, commits, items, open, snapshot

### Community 99 - "includeEdges"
Cohesion: 0.29
Nodes (3): includeEdges(), interiorPoint(), toSketch()

### Community 100 - "MainWindowArrow.cpp"
Cohesion: 0.13
Nodes (8): ArrowPlacement, base, dir, edgePlacement(), facesPlacement(), MainWindow::patternCentre(), MainWindow::pickedFaces(), MainWindow::updateDragArrow()

### Community 102 - "sstream"
Cohesion: 0.18
Nodes (4): doc_(), Document::Document(), ocafApplication(), Document::load()

### Community 103 - "MarkingMenu"
Cohesion: 0.40
Nodes (3): MarkingMenu, enabled, public

### Community 104 - "BoundingBox"
Cohesion: 0.23
Nodes (14): BoundingBox, max, min, WallSide, Center, Side1, Side2, extendedWire() (+6 more)

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
Cohesion: 0.15
Nodes (18): Section, Circular, Square, Triangular, TopologyCounts, edges, faces, shells (+10 more)

### Community 111 - "Document::reevaluateParameters"
Cohesion: 0.33
Nodes (3): Document::reevaluateParameters(), Document::replayContext(), Document::save()

### Community 112 - "MetricSize"
Cohesion: 0.33
Nodes (6): MetricSize, d, loose, name, normal, pitch

### Community 113 - "Mesh"
Cohesion: 0.40
Nodes (3): Mesh, nodes, triangles

### Community 114 - "uninstall.sh"
Cohesion: 0.52
Nodes (6): die(), manifest_for(), refresh(), uninstall.sh script, step(), usage()

### Community 115 - "install.sh"
Cohesion: 0.60
Nodes (5): die(), refresh(), install.sh script, step(), usage()

### Community 116 - "TestFramework.h"
Cohesion: 0.12
Nodes (12): PythonHost, Result, error, ok, output, captured(), PythonHost::exec(), PythonHost::runScript() (+4 more)

### Community 117 - ".rebuild"
Cohesion: 0.08
Nodes (12): hiddenColour(), qc(), rgb(), sharpEdges(), Style, Shaded, ShadedEdges, ShadedHidden (+4 more)

### Community 118 - "Column"
Cohesion: 0.25
Nodes (8): Column, kComment, kExpression, kName, kParameter, kStar, kUnit, kValue

### Community 120 - "Axis"
Cohesion: 0.50
Nodes (4): Axis, X, Y, Z

### Community 121 - "BooleanOp"
Cohesion: 0.50
Nodes (4): BooleanOp, Cut, Intersect, Join

### Community 123 - "Placement"
Cohesion: 0.25
Nodes (7): Placement, angle, cx, cy, dx, dy, scale

### Community 124 - "ChainSegment"
Cohesion: 0.67
Nodes (3): ChainSegment, entity, forward

### Community 126 - "ThreadInfo"
Cohesion: 0.50
Nodes (4): ThreadInfo, diameter, internal, pitch

### Community 128 - ".updatePreview"
Cohesion: 0.07
Nodes (18): ccwContains(), ext(), fixedColor(), freeColor(), lineEntity(), qc(), rgb(), wire() (+10 more)

### Community 129 - "ChamferType"
Cohesion: 0.67
Nodes (3): ChamferType, DistanceAngle, TwoDistances

### Community 131 - "DocCommands.cpp"
Cohesion: 0.11
Nodes (12): axisOf(), makeBox(), makeCone(), makeCylinder(), makeSphere(), makeTorus(), NewComponent, def_ (+4 more)

### Community 132 - "Unit"
Cohesion: 0.13
Nodes (14): MainWindow::lengthUnit(), Unit, Centimeter, Degree, Foot, Inch, Meter, Millimeter (+6 more)

### Community 134 - "src/main.cpp"
Cohesion: 0.06
Nodes (8): QAbstractButton, QAction, QObject, grabWindowWithPanels(), writeLiveGeometry(), Rect, rect(), p

### Community 141 - "Point"
Cohesion: 0.52
Nodes (6): Point, x, y, z, customPlaneSpec(), toDxf()

### Community 142 - "SplineHandle"
Cohesion: 0.29
Nodes (7): SplineHandle, arm, index, tx, ty, x, y

## Knowledge Gaps
- **763 isolated node(s):** `ok`, `output`, `error`, `isReal`, `real` (+758 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 1428 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **25 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `optional` connect `string` to `Viewport`, `DocCommands.cpp`, `MainWindow`, `Unit`, `Feature`, `Expression.cpp`, `optional`, `Kernel.cpp`, `Parser`, `ViewportSketch.cpp`, `Inputs`, `ViewportArrow.cpp`, `Constraint`, `Snap`, `CommandDialog.cpp`, `Pick`, `SketchEditor.cpp`, `AnalysisSettings`, `ParamSet`, `InputDef`, `Session`, `Vec3`, `CommandDialog::CommandDialog`, `SketchCurves.cpp`, `path`, `ReplayStep`, `MainWindowArrow.cpp`, `Joints`?**
  _High betweenness centrality (0.109) - this node is a cross-community bridge._
- **What connects `ok`, `output`, `error` to the rest of the system?**
  _763 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Viewport` be split into smaller, more focused modules?**
  _Cohesion score 0.01624015748031496 - nodes in this community are weakly interconnected._
- **Why does `Viewport` connect `Viewport` to `.initializeGL`, `ViewportArrow.cpp`, `MainWindow`, `Viewport.cpp`, `optional`, `AnalysisSettings`, `AnalysisSettings`, `SketchDisplay`, `.openMarkingMenu`, `SketchCurves.cpp`, `MainWindowTools.cpp`, `.rebuild`, `.toPixels`, `ViewportAnalysis.cpp`, `string`, `ViewportSketch.cpp`?**
  _High betweenness centrality (0.102) - this node is a cross-community bridge._
- **Should `Icons.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.056171735241502686 - nodes in this community are weakly interconnected._
- **Why does `MainWindow` connect `MainWindow` to `ParameterCompleter`, `MainWindowArrow.cpp`, `src/main.cpp`, `ParametersDialog.cpp`, `SectionState`, `optional`, `smoke`, `.openMarkingMenu`, `MainWindowSketch.cpp`, `MainWindowTools.cpp`, `TestFramework.h`, `UiCommand`, `MainWindow.cpp`, `SketchPalette`, `Session`?**
  _High betweenness centrality (0.089) - this node is a cross-community bridge._
- **Should `Session.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.12802275960170698 - nodes in this community are weakly interconnected._