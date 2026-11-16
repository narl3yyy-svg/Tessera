# Graph Report - tessera  (2026-11-16)

## Corpus Check
- 394 files · ~263,061 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 60 file(s) not represented in the graph (top: .drive 52, (none) 5, .cmake 1)

## Summary
- 3754 nodes · 9620 edges · 139 communities (116 shown, 23 thin omitted)
- Extraction: 85% EXTRACTED · 15% INFERRED · 0% AMBIGUOUS · INFERRED: 1477 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `585761cc`
- Run `git rev-parse HEAD` and compare to check if the graph is stale.
- Run `graphify update .` after code changes (no API cost).

## Community Hubs (Navigation)
- Viewport
- Icons.cpp
- Session.cpp
- MainWindow
- run_oracle.py
- src/main.cpp
- Document
- Viewport.cpp
- SketchEditor
- sketchFor
- optional
- Kernel.cpp
- AnalysisSettings
- Kind
- MainWindowArrow.cpp
- CommandDialog
- Io.cpp
- Parser
- Kind
- Document
- .openMarkingMenu
- MainWindowTools.cpp
- Affine
- ViewportSketch.cpp
- SketchPalette
- .updatePreview
- Inputs
- NewComponent
- Colors
- KernelError
- SketchOps.cpp
- ViewportArrow.cpp
- ParameterCompleter
- Constraint
- DocCommands.cpp
- MainWindow.cpp
- solve
- Snap
- isInputVisible
- ConstraintType
- AdskModule.cpp
- Pick
- SketchEditor.cpp
- Profile
- Zip.cpp
- AnalysisSettings
- Sketch.cpp
- Document.cpp
- MainWindowSketch.cpp
- InputDef
- string
- .toPixels
- curve
- Document::recompute
- MarkingMenu.cpp
- Command.cpp
- Entity
- xdrive.py
- Session
- Theme.cpp
- BodyFrame
- CommandRegistry
- TEST
- Feature
- Theme
- PlaneEdges
- InputType
- ParametersDialog.cpp
- Axis
- ViewportAnalysis.cpp
- CommandSession
- bindAdsk
- Vec3
- .add
- math
- QString
- SketchDisplay
- Command
- Measurement
- SketchCurves.cpp
- Level
- README.md
- string
- test_feature_pattern.py
- TsrModule.cpp
- Unit
- QTimer
- FileFormat
- Known differences still to build
- TEST
- ReplayStep
- Joints
- FakeDoc
- ParamSet
- BooleanOp
- MainWindow::MainWindow
- sstream
- ThreadInfo
- BoundingBox
- cachedProfiles
- SectionState
- Display
- cli_main.cpp
- smoke
- TopologyCounts
- Column
- .redrawAll
- toDxf
- uninstall.sh
- install.sh
- TestFramework.h
- .rebuild
- MarkingMenu
- .displayText
- SketchEditor.h
- test_incremental_replay.py
- Placement
- ChainSegment
- ChamferType
- Known gaps
- Architecture
- TEST
- Joint
- fail
- Value.h
- test_text_box_path.py
- LAB_NOTES.md
- Development
- build.sh
- live-test.sh
- SplineHandle

## God Nodes (most connected - your core abstractions)
1. `Viewport` - 257 edges
2. `SketchEditor` - 185 edges
3. `MainWindow` - 184 edges
4. `Inputs` - 152 edges
5. `render()` - 121 edges
6. `Document` - 120 edges
7. `CommandContext` - 111 edges
8. `CommandDialog` - 90 edges
9. `Command` - 66 edges
10. `CommandError` - 61 edges

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

## Communities (139 total, 23 thin omitted)

### Community 0 - "Viewport"
Cohesion: 0.02
Nodes (69): view_, QLineEdit, Viewport, analysis_, analysisObjects_, appliedGridStep_, arrowBoxes_, arrowDragging_ (+61 more)

### Community 1 - "Icons.cpp"
Cohesion: 0.05
Nodes (126): accessibilityIcon(), appearanceIcon(), arc3Icon(), arcIcon(), arcTangentIcon(), arrow(), axisIcon(), box() (+118 more)

### Community 2 - "Session.cpp"
Cohesion: 0.12
Nodes (33): historyEdit(), OwnedCommand, owned, OwningCommandSession, plainEdit(), Session::addListener(), Session::addNamedView(), Session::begin() (+25 more)

### Community 4 - "MainWindow"
Cohesion: 0.03
Nodes (65): writeLiveGeometry(), CommandDialog, MainWindow, active_, arrowInput_, arrowInput2_, bodiesBeforeCommand_, combEdges_ (+57 more)

### Community 5 - "run_oracle.py"
Cohesion: 0.08
Nodes (54): add_point(), arc_poly(), body_at(), body_list(), build_sketch(), chain(), circumcentre(), cm() (+46 more)

### Community 6 - "src/main.cpp"
Cohesion: 0.11
Nodes (3): QAbstractButton, QAction, grabWindowWithPanels()

### Community 7 - "Document"
Cohesion: 0.03
Nodes (15): Document, effects_, lastReplayed_, lastReused_, modified_, pendingTools_, registry_, replaying_ (+7 more)

### Community 8 - "Viewport.cpp"
Cohesion: 0.05
Nodes (4): glide(), QKeyEvent, QLabel, QtFrameBuffer

### Community 9 - "SketchEditor"
Cohesion: 0.03
Nodes (50): HandleHit, back, index, spline, SketchEditor, arcDrag_, arcDragMoved_, arcEndsChain_ (+42 more)

### Community 10 - "sketchFor"
Cohesion: 0.13
Nodes (11): Extrude, def_, Pipe, def_, Primitive, build_, def_, Revolve (+3 more)

### Community 11 - "optional"
Cohesion: 0.15
Nodes (3): optional, CommandRegistry::all(), Document

### Community 12 - "Kernel.cpp"
Cohesion: 0.04
Nodes (5): isoCoarsePitch(), massProperties(), measure(), polygonToCircleLoft(), topologyCounts()

### Community 13 - "AnalysisSettings"
Cohesion: 0.11
Nodes (18): AnalysisKind, Accessibility, CurvatureMap, Draft, Isocurve, MinimumRadius, None, Zebra (+10 more)

### Community 14 - "Kind"
Cohesion: 0.06
Nodes (32): ConstructPlane, def_, kind_, EdgeFeature, def_, kind_, FaceFeature, def_ (+24 more)

### Community 15 - "MainWindowArrow.cpp"
Cohesion: 0.12
Nodes (8): ArrowPlacement, base, dir, edgePlacement(), facesPlacement(), MainWindow::attachArrowCompleters(), MainWindow::patternCentre(), MainWindow::pickedFaces()

### Community 16 - "CommandDialog"
Cohesion: 0.04
Nodes (31): CommandDialog, bodiesId_, bodiesLabel_, bodyInput_, buttons_, cmd_, conditional_, edgesId_ (+23 more)

### Community 17 - "Io.cpp"
Cohesion: 0.10
Nodes (18): NamedShape, compoundOf(), exportShapes(), fmt(), formatForPath(), fromBrep(), importShape(), lower() (+10 more)

### Community 18 - "Parser"
Cohesion: 0.09
Nodes (31): ExpressionEnv, lengthUnit, lookup, ExpressionError, Quantity, angle, length, value (+23 more)

### Community 19 - "Kind"
Cohesion: 0.07
Nodes (24): Hit, index, kind, HudField, edit, editing, kind, locked (+16 more)

### Community 21 - "Document"
Cohesion: 0.23
Nodes (5): bodyCentre(), ConstructAxisPoint, def_, kind_, storeBodies()

### Community 23 - "MainWindowTools.cpp"
Cohesion: 0.06
Nodes (18): QDialog, MainWindow::chooseUnits(), MainWindow::editAppearance(), MainWindow::editMaterial(), MainWindow::exportDesign(), MainWindow::insertFile(), MainWindow::lookTargets(), MainWindow::measurePick() (+10 more)

### Community 24 - "Affine"
Cohesion: 0.13
Nodes (13): Affine, a, b, d, e, Builder, byPlace_, k_ (+5 more)

### Community 25 - "ViewportSketch.cpp"
Cohesion: 0.08
Nodes (6): faceStyle(), lineStyle(), rgb(), Viewport::lookAt(), Viewport::planePoint(), Viewport::toWidget()

### Community 26 - "SketchPalette"
Cohesion: 0.06
Nodes (24): QCheckBox, QLabel, QWidget, SketchEditor, SketchPalette, body_, constraints_, construction_ (+16 more)

### Community 27 - ".updatePreview"
Cohesion: 0.06
Nodes (26): ccwContains(), circumcircle(), ext(), fixedColor(), freeColor(), lineEntity(), qc(), rgb() (+18 more)

### Community 28 - "Inputs"
Cohesion: 0.09
Nodes (16): CommandContext, CommandError, Inputs, CommandSession::CommandSession(), getBool(), getInt(), getReal(), applyOperation() (+8 more)

### Community 29 - "NewComponent"
Cohesion: 0.14
Nodes (7): AddUserParameter, def_, isIdentifier(), NewComponent, def_, RigidGroup, def_

### Community 30 - "Colors"
Cohesion: 0.07
Nodes (28): Colors, base, border, cubeBox, cubeText, errorBackground, grid, gridMajor (+20 more)

### Community 31 - "KernelError"
Cohesion: 0.25
Nodes (29): KernelError, asSolid(), boolean(), chamfer(), chamferEx(), deleteFaces(), draft(), extrude() (+21 more)

### Community 32 - "SketchOps.cpp"
Cohesion: 0.23
Nodes (25): at(), chainOf(), chamferCorner(), circularPattern(), copyEntities(), cross(), dot(), extendLine() (+17 more)

### Community 33 - "ViewportArrow.cpp"
Cohesion: 0.06
Nodes (19): MarkingMenu::mouseMoveEvent(), QMouseEvent, ViewInteractor, Viewport::frontEdgeOwner(), rgb(), segmentDistance(), Viewport::arrowAt(), Viewport::arrowMouseMove() (+11 more)

### Community 34 - "ParameterCompleter"
Cohesion: 0.12
Nodes (8): ParameterCompleter, completer_, edit_, names_, ParameterCompleter::ParameterCompleter(), public, QCompleter, QLineEdit

### Community 35 - "Constraint"
Cohesion: 0.08
Nodes (20): Constraint, driven, entities, expression, hasLabel, labelX, labelY, name (+12 more)

### Community 36 - "DocCommands.cpp"
Cohesion: 0.10
Nodes (30): axisOf(), CopyFn, differenceOrNull(), evaluateDimensions(), HoleSize, modeled, pitch, radius (+22 more)

### Community 37 - "MainWindow.cpp"
Cohesion: 0.08
Nodes (5): commandIcon(), flatButton(), qs(), MainWindow::applySection(), QToolButton

### Community 38 - "solve"
Cohesion: 0.19
Nodes (12): addConstraintChecked(), Layout, n, px, py, rad, makeLayout(), pack() (+4 more)

### Community 39 - "Snap"
Cohesion: 0.11
Nodes (18): Snap, alignX, alignY, bodyArc, bodySegment, entity, fromX, fromY (+10 more)

### Community 41 - "ConstraintType"
Cohesion: 0.08
Nodes (26): ConstraintType, Angle, Coincident, Collinear, Concentric, Curvature, Diameter, Distance (+18 more)

### Community 42 - "AdskModule.cpp"
Cohesion: 0.13
Nodes (13): Application, BRepBodies, Component, Design, Product, raiseIfError(), UserParameter, name (+5 more)

### Community 43 - "Pick"
Cohesion: 0.09
Nodes (17): QObject, Pick, bodyArc, bodyPoint, bodySegment, hit, midpointOf, onEntity (+9 more)

### Community 45 - "Profile"
Cohesion: 0.33
Nodes (5): Profile, area, face, x, y

### Community 46 - "Zip.cpp"
Cohesion: 0.20
Nodes (13): Entry, data, name, ZipError, crc32(), deflateRaw(), get16(), get32() (+5 more)

### Community 47 - "AnalysisSettings"
Cohesion: 0.10
Nodes (16): DragArrow, base, dir, radius, ref, ring, value, PendingLook (+8 more)

### Community 48 - "Sketch.cpp"
Cohesion: 0.07
Nodes (22): SketchError, SplineKind, Conic, Control, Fit, entityTypeName(), isDimension(), Sketch::addConic() (+14 more)

### Community 49 - "Document.cpp"
Cohesion: 0.05
Nodes (39): ConstructionPlane, name, spec, SketchRecord, data, name, offset, plane (+31 more)

### Community 50 - "MainWindowSketch.cpp"
Cohesion: 0.08
Nodes (13): MainWindow::cancelSketch(), MainWindow::editSketch(), MainWindow::finishSketch(), MainWindow::onEdgeClicked(), MainWindow::onProfileClicked(), MainWindow::originalShape(), MainWindow::sketchPalette(), MainWindow::sketchVisible() (+5 more)

### Community 51 - "InputDef"
Cohesion: 0.09
Nodes (21): InputDef, choices, defaultValue, id, label, max, min, minExclusive (+13 more)

### Community 52 - "string"
Cohesion: 0.08
Nodes (24): checkBody(), checkPattern(), CircularPattern, def_, Hole, def_, jointOrigin(), JointPick (+16 more)

### Community 54 - "curve"
Cohesion: 0.16
Nodes (18): conditionedSpline(), curve(), curves(), entityCurves(), G2End, d1, d2, set (+10 more)

### Community 55 - "Document::recompute"
Cohesion: 0.20
Nodes (7): Document::recompute(), Document::recordFeature(), Document::removeFeature(), Document::setFeatureInputs(), Document::setFeatureSuppressed(), featureData(), toJson()

### Community 56 - "MarkingMenu.cpp"
Cohesion: 0.06
Nodes (25): UiCommand, enabled, icon, id, name, panel, run, shortcut (+17 more)

### Community 57 - "Command.cpp"
Cohesion: 0.15
Nodes (16): expressionKey(), Dimension, Angle, Length, Unitless, checkInputValue(), CommandContext::evaluateExpression(), CommandDef::input() (+8 more)

### Community 58 - "Entity"
Cohesion: 0.11
Nodes (12): Entity, a, b, center, construction, fit, handles, included (+4 more)

### Community 59 - "xdrive.py"
Cohesion: 0.28
Nodes (15): button(), canvas(), click(), drag(), flush(), geometry(), key(), keycode() (+7 more)

### Community 62 - "Session"
Cohesion: 0.07
Nodes (6): Session, commands_, doc_, listeners_, nextListener_, path_

### Community 63 - "Theme.cpp"
Cohesion: 0.19
Nodes (6): setIconTheme(), darkColors(), darkPalette(), darkStyleSheet(), lightColors(), lightStyleSheet()

### Community 64 - "BodyFrame"
Cohesion: 0.07
Nodes (40): BodyFrame, diag, dx, dy, dz, x0, y0, z0 (+32 more)

### Community 65 - "CommandRegistry"
Cohesion: 0.12
Nodes (4): CommandRegistry, cmds_, CommandRegistry::add(), TEST()

### Community 66 - "TEST"
Cohesion: 0.09
Nodes (3): param(), TEST(), tmp()

### Community 67 - "Feature"
Cohesion: 0.11
Nodes (17): Feature, commandId, error, id, inputs, name, parameterNames, rolledBack (+9 more)

### Community 68 - "Theme"
Cohesion: 0.22
Nodes (4): Theme, colors_, public, styled_

### Community 69 - "PlaneEdges"
Cohesion: 0.15
Nodes (5): PlaneEdges, arcs, curves, segments, vertices

### Community 70 - "InputType"
Cohesion: 0.12
Nodes (17): InputType, Axis, Bodies, Body, Bool, Choice, Edges, Faces (+9 more)

### Community 71 - "ParametersDialog.cpp"
Cohesion: 0.08
Nodes (16): number(), ParametersDialog, building_, error_, filter_, listener_, ParametersDialog::ParametersDialog(), public (+8 more)

### Community 72 - "Axis"
Cohesion: 0.50
Nodes (4): Axis, X, Y, Z

### Community 73 - "ViewportAnalysis.cpp"
Cohesion: 0.13
Nodes (5): packed(), ramp(), shade(), Viewport::buildAnalysis(), f

### Community 74 - "CommandSession"
Cohesion: 0.17
Nodes (4): CommandSession, inputs_, CommandRegistry::find(), CommandRegistry::run()

### Community 75 - "bindAdsk"
Cohesion: 0.29
Nodes (3): bindAdsk(), BRepBody, index

### Community 76 - "Vec3"
Cohesion: 0.18
Nodes (20): SurfacePoint, normal, point, Vec3, boundingBox(), edgeMidpoint(), edgesNear(), frame() (+12 more)

### Community 78 - "math"
Cohesion: 0.07
Nodes (3): dist(), check_regular(), dist_to_line()

### Community 79 - "QString"
Cohesion: 0.12
Nodes (5): CommandDialog::CommandDialog(), ExpressionSpinBox, eval_, expression_, shown_

### Community 80 - "SketchDisplay"
Cohesion: 0.12
Nodes (11): ProfileObject, index, sketch, SketchDisplay, construction, curves, fixedCurves, frame (+3 more)

### Community 81 - "Command"
Cohesion: 0.04
Nodes (42): Adding a tool, Command, CommandDef, feature, icon, id, inputs, name (+34 more)

### Community 82 - "Measurement"
Cohesion: 0.13
Nodes (14): Kind, Angle, Area, Length, Volume, Measurement, from, hasLine (+6 more)

### Community 83 - "SketchCurves.cpp"
Cohesion: 0.14
Nodes (18): crossings(), crossingsOf(), Curve2d, curve2d(), periodic, t0, t1, endIsFree() (+10 more)

### Community 85 - "Level"
Cohesion: 0.16
Nodes (13): debug(), error(), info(), Level, Debug, Error, Info, Warning (+5 more)

### Community 86 - "README.md"
Cohesion: 0.14
Nodes (11): Reference parts, Fusion feature checklist, Roadmap, Contents, Development, Features, Install, License (+3 more)

### Community 87 - "string"
Cohesion: 0.09
Nodes (38): DocumentError, PhysicalMaterial, color, density, name, checkViewName(), Document::abortTransaction(), Document::addBody() (+30 more)

### Community 89 - "TsrModule.cpp"
Cohesion: 0.23
Nodes (4): bindTsr(), fromPy(), toPy(), typeName()

### Community 90 - "Unit"
Cohesion: 0.11
Nodes (27): MainWindow::checkInterference(), MainWindow::driveJoints(), MainWindow::formatLength(), MainWindow::gridSettings(), MainWindow::lengthUnit(), MainWindow::openAnalysis(), MainWindow::openSection(), MainWindow::updateMeasure() (+19 more)

### Community 91 - "QTimer"
Cohesion: 0.10
Nodes (6): QTimer, SelectionBox, crossing, Viewport::placeArrowBoxes(), Viewport::selectArrowValue(), height

### Community 92 - "FileFormat"
Cohesion: 0.17
Nodes (12): FileFormat, Brep, Iges, Obj, Step, Stl, ThreeMF, FormatInfo (+4 more)

### Community 93 - "Known differences still to build"
Cohesion: 0.15
Nodes (12): Data and files, Findings from the videos, Fusion study list, Interface, Known differences still to build, Navigation and display, Selection and the canvas, Sketch (+4 more)

### Community 94 - "TEST"
Cohesion: 0.20
Nodes (3): slurp(), TEST(), tmp()

### Community 95 - "ReplayStep"
Cohesion: 0.04
Nodes (45): Body, color, display, material, name, shape, Component, bodies (+37 more)

### Community 96 - "Joints"
Cohesion: 0.36
Nodes (3): cornerAt(), Joints, parent_

### Community 98 - "FakeDoc"
Cohesion: 0.17
Nodes (6): FakeDoc, aborts, commits, items, open, snapshot

### Community 99 - "ParamSet"
Cohesion: 0.07
Nodes (33): ModelParameter, angle, expression, input, label, name, owner, unit (+25 more)

### Community 100 - "BooleanOp"
Cohesion: 0.50
Nodes (4): BooleanOp, Cut, Intersect, Join

### Community 101 - "MainWindow::MainWindow"
Cohesion: 0.16
Nodes (3): MainWindow::MainWindow(), MainWindow::beginSketch(), MainWindow::exitSketchMode()

### Community 102 - "sstream"
Cohesion: 0.17
Nodes (5): doc_(), Document::Document(), Document::ocafBytes(), ocafApplication(), Document::load()

### Community 103 - "ThreadInfo"
Cohesion: 0.50
Nodes (4): ThreadInfo, diameter, internal, pitch

### Community 104 - "BoundingBox"
Cohesion: 0.15
Nodes (18): BoundingBox, max, min, WallSide, Center, Side1, Side2, curveMiddles() (+10 more)

### Community 105 - "cachedProfiles"
Cohesion: 0.20
Nodes (3): MainWindow::updateDragArrow(), cachedProfiles(), keyOf()

### Community 106 - "SectionState"
Cohesion: 0.25
Nodes (7): SectionState, active, angle, flip, offset, plane, visible

### Community 107 - "Display"
Cohesion: 0.25
Nodes (7): Display, constraints, construction, dimensions, points, profiles, projected

### Community 108 - "cli_main.cpp"
Cohesion: 0.36
Nodes (4): listCommands(), main(), usage(), main()

### Community 109 - "smoke"
Cohesion: 0.33
Nodes (6): smoke(), key, MassProperties, area, centerOfMass, volume

### Community 110 - "TopologyCounts"
Cohesion: 0.14
Nodes (18): Section, Circular, Square, Triangular, TopologyCounts, edges, faces, shells (+10 more)

### Community 111 - "Column"
Cohesion: 0.25
Nodes (8): Column, kComment, kExpression, kName, kParameter, kStar, kUnit, kValue

### Community 112 - ".redrawAll"
Cohesion: 0.10
Nodes (10): keys(), NavPreset, Fusion, SolidWorks, Tinkercad, Viewport::Viewport(), Viewport::setCurvatureComb(), Viewport::clearDragArrow() (+2 more)

### Community 113 - "toDxf"
Cohesion: 0.52
Nodes (6): Point, x, y, z, customPlaneSpec(), toDxf()

### Community 114 - "uninstall.sh"
Cohesion: 0.52
Nodes (6): die(), manifest_for(), refresh(), uninstall.sh script, step(), usage()

### Community 115 - "install.sh"
Cohesion: 0.60
Nodes (5): die(), refresh(), install.sh script, step(), usage()

### Community 116 - "TestFramework.h"
Cohesion: 0.09
Nodes (14): PythonHost, Result, error, ok, output, captured(), PYBIND11_EMBEDDED_MODULE(), PythonHost::exec() (+6 more)

### Community 117 - ".rebuild"
Cohesion: 0.08
Nodes (12): hiddenColour(), qc(), rgb(), sharpEdges(), Style, Shaded, ShadedEdges, ShadedHidden (+4 more)

### Community 118 - "MarkingMenu"
Cohesion: 0.40
Nodes (3): MarkingMenu, enabled, public

### Community 121 - "SketchEditor.h"
Cohesion: 0.11
Nodes (10): EntityType, Arc, Circle, Ellipse, Line, Spline, isRound(), Rect (+2 more)

### Community 123 - "Placement"
Cohesion: 0.25
Nodes (7): Placement, angle, cx, cy, dx, dy, scale

### Community 124 - "ChainSegment"
Cohesion: 0.67
Nodes (3): ChainSegment, entity, forward

### Community 125 - "ChamferType"
Cohesion: 0.67
Nodes (3): ChamferType, DistanceAngle, TwoDistances

### Community 126 - "Known gaps"
Cohesion: 0.29
Nodes (6): Curvature (G2), Include 3D Geometry, Known gaps, Sketch text, Splines and conics, Visual styles

### Community 127 - "Architecture"
Cohesion: 0.40
Nodes (4): Architecture, How a command works, The document, Units

### Community 129 - "Joint"
Cohesion: 0.21
Nodes (5): Joint, asBuilt_, def_, Sweep, def_

### Community 134 - "Development"
Cohesion: 0.40
Nodes (4): Build, Conventions, Development, Tests

### Community 142 - "SplineHandle"
Cohesion: 0.25
Nodes (8): SplineHandle, arm, index, set, tx, ty, x, y

## Knowledge Gaps
- **778 isolated node(s):** `ok`, `output`, `error`, `isReal`, `real` (+773 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 1454 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **23 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `optional` connect `optional` to `Viewport`, `MainWindow`, `Viewport.cpp`, `sketchFor`, `Kernel.cpp`, `MainWindowArrow.cpp`, `Io.cpp`, `Parser`, `ViewportSketch.cpp`, `ViewportArrow.cpp`, `Constraint`, `DocCommands.cpp`, `SketchEditor.cpp`, `AnalysisSettings`, `Document.cpp`, `InputDef`, `SketchGeometry.cpp`, `Session`, `Feature`, `PlaneEdges`, `Vec3`, `QString`, `SketchCurves.cpp`, `CommandDialog.cpp`, `Unit`, `ReplayStep`, `Joints`, `ParamSet`, `.displayText`, `SketchEditor.h`?**
  _High betweenness centrality (0.120) - this node is a cross-community bridge._
- **What connects `ok`, `output`, `error` to the rest of the system?**
  _778 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Viewport` be split into smaller, more focused modules?**
  _Cohesion score 0.015845477677538748 - nodes in this community are weakly interconnected._
- **Why does `SketchEditor` connect `SketchEditor` to `Viewport`, `ViewportArrow.cpp`, `Constraint`, `PlaneEdges`, `Unit`, `Snap`, `Display`, `Pick`, `SketchEditor.cpp`, `Kind`, `.localDimensions`, `SketchEditor.h`, `Entity`, `.updatePreview`, `Session`, `ReplayStep`?**
  _High betweenness centrality (0.116) - this node is a cross-community bridge._
- **Should `Icons.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.05289326139849783 - nodes in this community are weakly interconnected._
- **Why does `Viewport` connect `Viewport` to `ViewportArrow.cpp`, `Viewport.cpp`, `ViewportAnalysis.cpp`, `optional`, `AnalysisSettings`, `AnalysisSettings`, `SketchDisplay`, `.redrawAll`, `SketchCurves.cpp`, `.rebuild`, `.toPixels`, `Unit`, `QTimer`?**
  _High betweenness centrality (0.103) - this node is a cross-community bridge._
- **Should `Session.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.11951219512195121 - nodes in this community are weakly interconnected._