# Graph Report - tessera  (2026-11-13)

## Corpus Check
- 386 files · ~255,910 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 56 file(s) not represented in the graph (top: .drive 48, (none) 5, .cmake 1)

## Summary
- 3713 nodes · 9515 edges · 139 communities (111 shown, 28 thin omitted)
- Extraction: 85% EXTRACTED · 15% INFERRED · 0% AMBIGUOUS · INFERRED: 1463 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `98a0b5cb`
- Run `git rev-parse HEAD` and compare to check if the graph is stale.
- Run `graphify update .` after code changes (no API cost).

## Community Hubs (Navigation)
- Viewport
- Icons.cpp
- Session.cpp
- tsr
- MainWindow
- run_oracle.py
- Unit
- Document
- Viewport.cpp
- SketchEditor
- CommandError
- optional
- Kernel.cpp
- AnalysisSettings
- Kind
- MainWindowArrow.cpp
- CommandDialog
- Io.cpp
- Unit
- .setTool
- Known gaps
- Document
- MainWindow.cpp
- MainWindowTools.cpp
- Affine
- ViewportSketch.cpp
- SketchPalette
- Inputs
- string
- Colors
- KernelError
- SketchOps.cpp
- ViewportArrow.cpp
- ParameterCompleter
- Constraint
- DocCommands.cpp
- src/main.cpp
- solve
- Snap
- CommandDialog.cpp
- ConstraintType
- TsrModule.cpp
- Pick
- SketchEditor.cpp
- .showDialog
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
- MarkingMenu.cpp
- SketchEditor.h
- Entity
- xdrive.py
- Session
- Theme.cpp
- BodyFrame
- CommandRegistry
- .openMarkingMenu
- BodyFrame
- Theme
- PlaneEdges
- Command.cpp
- ParametersDialog.cpp
- TEST
- curve
- Kind
- InputType
- Vec3
- Dimension
- QString
- SketchDisplay
- Command
- Measurement
- SketchCurves.cpp
- Level
- README.md
- Document.cpp
- test_feature_pattern.py
- rect
- MainWindow::MainWindow
- TEST
- FileFormat
- Known differences still to build
- TEST
- ReplayStep
- .refresh
- Feature
- FakeDoc
- ModelParameter
- QDialog
- .add
- sstream
- cachedProfiles
- BoundingBox
- Joints
- SectionState
- Display
- main
- Kernel.h
- TopologyCounts
- Column
- .redrawAll
- ParametersDialog.h
- uninstall.sh
- install.sh
- TestFramework.h
- .rebuild
- MarkingMenu
- CommandRegistry::run
- path
- test_incremental_replay.py
- Placement
- ChainSegment
- Icons.h
- Mesh
- Entry
- .updatePreview
- Joint
- fail
- Value.h
- LAB_NOTES.md
- build.sh
- live-test.sh
- PYBIND11_EMBEDDED_MODULE
- Point
- SplineHandle

## God Nodes (most connected - your core abstractions)
1. `Viewport` - 257 edges
2. `SketchEditor` - 185 edges
3. `MainWindow` - 184 edges
4. `Inputs` - 149 edges
5. `Document` - 120 edges
6. `render()` - 119 edges
7. `CommandContext` - 108 edges
8. `CommandDialog` - 90 edges
9. `Command` - 65 edges
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

## Communities (139 total, 28 thin omitted)

### Community 0 - "Viewport"
Cohesion: 0.02
Nodes (69): view_, QLineEdit, Viewport, analysis_, analysisObjects_, appliedGridStep_, arrowBoxes_, arrowDragging_ (+61 more)

### Community 1 - "Icons.cpp"
Cohesion: 0.05
Nodes (124): accessibilityIcon(), appearanceIcon(), arc3Icon(), arcIcon(), arcTangentIcon(), arrow(), axisIcon(), box() (+116 more)

### Community 2 - "Session.cpp"
Cohesion: 0.11
Nodes (34): historyEdit(), OwnedCommand, owned, OwningCommandSession, plainEdit(), Session::addListener(), Session::addNamedView(), Session::begin() (+26 more)

### Community 4 - "MainWindow"
Cohesion: 0.03
Nodes (64): writeLiveGeometry(), CommandDialog, MainWindow, active_, arrowInput_, arrowInput2_, bodiesBeforeCommand_, combEdges_ (+56 more)

### Community 5 - "run_oracle.py"
Cohesion: 0.08
Nodes (54): add_point(), arc_poly(), body_at(), body_list(), build_sketch(), chain(), circumcentre(), cm() (+46 more)

### Community 6 - "Unit"
Cohesion: 0.16
Nodes (13): MainWindow::checkInterference(), MainWindow::driveJoints(), MainWindow::formatLength(), MainWindow::gridSettings(), MainWindow::openAnalysis(), MainWindow::openSection(), MainWindow::showCenterOfMass(), MainWindow::updateMeasure() (+5 more)

### Community 7 - "Document"
Cohesion: 0.03
Nodes (16): Document, effects_, lastReplayed_, lastReused_, modified_, pendingTools_, registry_, replaying_ (+8 more)

### Community 8 - "Viewport.cpp"
Cohesion: 0.06
Nodes (3): glide(), QKeyEvent, QtFrameBuffer

### Community 9 - "SketchEditor"
Cohesion: 0.03
Nodes (50): HandleHit, back, index, spline, SketchEditor, arcDrag_, arcDragMoved_, arcEndsChain_ (+42 more)

### Community 10 - "CommandError"
Cohesion: 0.16
Nodes (13): CommandError, getBool(), getReal(), applyOperation(), bodyName(), Extrude, def_, body (+5 more)

### Community 13 - "AnalysisSettings"
Cohesion: 0.07
Nodes (19): AnalysisKind, Accessibility, CurvatureMap, Draft, Isocurve, MinimumRadius, None, Zebra (+11 more)

### Community 14 - "Kind"
Cohesion: 0.07
Nodes (29): ConstructPlane, def_, kind_, EdgeFeature, def_, kind_, Kind, Angle (+21 more)

### Community 15 - "MainWindowArrow.cpp"
Cohesion: 0.12
Nodes (8): ArrowPlacement, base, dir, edgePlacement(), facesPlacement(), MainWindow::attachArrowCompleters(), MainWindow::patternCentre(), MainWindow::pickedFaces()

### Community 16 - "CommandDialog"
Cohesion: 0.05
Nodes (31): CommandDialog, bodiesId_, bodiesLabel_, bodyInput_, buttons_, cmd_, conditional_, edgesId_ (+23 more)

### Community 17 - "Io.cpp"
Cohesion: 0.12
Nodes (8): formatForPath(), fromBrep(), importShape(), lower(), meshOf(), scaled(), toBrep(), xmlEscape()

### Community 18 - "Unit"
Cohesion: 0.07
Nodes (45): MainWindow::lengthUnit(), ExpressionEnv, lengthUnit, lookup, ExpressionError, Quantity, angle, length (+37 more)

### Community 19 - ".setTool"
Cohesion: 0.15
Nodes (5): Hit, index, kind, SketchEditor::SketchEditor(), edges

### Community 20 - "Known gaps"
Cohesion: 0.33
Nodes (5): Include 3D Geometry, Known gaps, Sketch text, Splines and conics, Visual styles

### Community 21 - "Document"
Cohesion: 0.21
Nodes (7): ConstructAxisPoint, def_, kind_, jointOrigin(), JointPick, frame, revolveAxis()

### Community 23 - "MainWindowTools.cpp"
Cohesion: 0.07
Nodes (10): MainWindow::chooseUnits(), MainWindow::editAppearance(), MainWindow::editMaterial(), MainWindow::insertFile(), MainWindow::lookTargets(), MainWindow::sectionFrame(), MainWindow::sectionPlane(), MainWindow::setSelectionFilter() (+2 more)

### Community 24 - "Affine"
Cohesion: 0.14
Nodes (13): Affine, a, b, d, e, Builder, byPlace_, k_ (+5 more)

### Community 25 - "ViewportSketch.cpp"
Cohesion: 0.09
Nodes (6): faceStyle(), lineStyle(), rgb(), Viewport::lookAt(), Viewport::planePoint(), Viewport::toWidget()

### Community 26 - "SketchPalette"
Cohesion: 0.06
Nodes (26): flatButton(), QCheckBox, QLabel, QToolButton, QWidget, SketchEditor, SketchPalette, body_ (+18 more)

### Community 28 - "Inputs"
Cohesion: 0.07
Nodes (13): CommandContext, Inputs, CommandSession::CommandSession(), AddUserParameter, def_, checkBody(), checkPattern(), defaultBody() (+5 more)

### Community 29 - "string"
Cohesion: 0.10
Nodes (25): bodyNumber(), Document::addBody(), Document::bodyName(), Document::bodyShapes(), Document::componentOfBody(), Document::effectOf(), Document::evaluate(), Document::favoriteParameters() (+17 more)

### Community 30 - "Colors"
Cohesion: 0.07
Nodes (28): Colors, base, border, cubeBox, cubeText, errorBackground, grid, gridMajor (+20 more)

### Community 31 - "KernelError"
Cohesion: 0.22
Nodes (34): KernelError, asSolid(), boolean(), chamfer(), chamferEx(), curveMiddles(), deleteFaces(), draft() (+26 more)

### Community 32 - "SketchOps.cpp"
Cohesion: 0.19
Nodes (28): at(), chainOf(), chamferCorner(), circularPattern(), copyEntities(), cornerAt(), cross(), dot() (+20 more)

### Community 33 - "ViewportArrow.cpp"
Cohesion: 0.06
Nodes (20): MarkingMenu::mouseMoveEvent(), QMouseEvent, ViewInteractor, Viewport::frontEdgeOwner(), rgb(), segmentDistance(), Viewport::arrowAt(), Viewport::arrowMouseMove() (+12 more)

### Community 34 - "ParameterCompleter"
Cohesion: 0.13
Nodes (9): QObject, ParameterCompleter, completer_, edit_, names_, ParameterCompleter::ParameterCompleter(), public, QCompleter (+1 more)

### Community 35 - "Constraint"
Cohesion: 0.08
Nodes (20): Constraint, driven, entities, expression, hasLabel, labelX, labelY, name (+12 more)

### Community 36 - "DocCommands.cpp"
Cohesion: 0.08
Nodes (35): axisOf(), bodyCentre(), Combine, def_, CopyFn, differenceOrNull(), evaluateDimensions(), Loft (+27 more)

### Community 38 - "solve"
Cohesion: 0.18
Nodes (13): set, addConstraintChecked(), Layout, n, px, py, rad, makeLayout() (+5 more)

### Community 39 - "Snap"
Cohesion: 0.10
Nodes (18): Snap, alignX, alignY, bodyArc, bodySegment, entity, fromX, fromY (+10 more)

### Community 41 - "ConstraintType"
Cohesion: 0.09
Nodes (23): ConstraintType, Angle, Coincident, Collinear, Concentric, Diameter, Distance, Equal (+15 more)

### Community 42 - "TsrModule.cpp"
Cohesion: 0.09
Nodes (16): Application, bindAdsk(), BRepBodies, BRepBody, index, Component, Design, Product (+8 more)

### Community 43 - "Pick"
Cohesion: 0.13
Nodes (14): Pick, bodyArc, bodyPoint, bodySegment, hit, midpointOf, onEntity, onXAxis (+6 more)

### Community 44 - "SketchEditor.cpp"
Cohesion: 0.12
Nodes (4): angleInArc(), ccwContains(), circumcircle(), segDistance()

### Community 46 - "Zip.cpp"
Cohesion: 0.25
Nodes (10): ZipError, crc32(), deflateRaw(), get16(), get32(), inflateRaw(), put16(), put32() (+2 more)

### Community 47 - "AnalysisSettings"
Cohesion: 0.10
Nodes (16): DragArrow, base, dir, radius, ref, ring, value, PendingLook (+8 more)

### Community 48 - "Sketch.cpp"
Cohesion: 0.07
Nodes (22): SketchError, SplineKind, Conic, Control, Fit, entityTypeName(), isDimension(), Sketch::addConic() (+14 more)

### Community 49 - "ParamSet"
Cohesion: 0.08
Nodes (34): ConstructionPlane, name, spec, NamedView, eye, name, size, target (+26 more)

### Community 50 - "MainWindowSketch.cpp"
Cohesion: 0.07
Nodes (15): MainWindow::cancelSketch(), MainWindow::editSketch(), MainWindow::finishSketch(), MainWindow::onProfileClicked(), MainWindow::originalShape(), MainWindow::sketchPalette(), MainWindow::sketchVisible(), MainWindow::startSketch() (+7 more)

### Community 51 - "InputDef"
Cohesion: 0.09
Nodes (21): InputDef, choices, defaultValue, id, label, max, min, minExclusive (+13 more)

### Community 52 - ".apply"
Cohesion: 0.15
Nodes (11): getInt(), CircularPattern, def_, Hole, def_, HoleSize, holeSize(), modeled (+3 more)

### Community 54 - "ViewportAnalysis.cpp"
Cohesion: 0.11
Nodes (6): packed(), ramp(), shade(), Viewport::buildAnalysis(), Viewport::setCurvatureComb(), f

### Community 55 - "Document::recompute"
Cohesion: 0.22
Nodes (5): Document::expressionEnv(), Document::recompute(), Document::recordFeature(), Document::setFeatureInputs(), toJson()

### Community 56 - "MarkingMenu.cpp"
Cohesion: 0.07
Nodes (22): UiCommand, enabled, icon, id, name, panel, run, shortcut (+14 more)

### Community 57 - "SketchEditor.h"
Cohesion: 0.10
Nodes (12): EntityType, Arc, Circle, Ellipse, Line, Spline, isRound(), Profile (+4 more)

### Community 58 - "Entity"
Cohesion: 0.08
Nodes (12): Entity, a, b, center, construction, fit, handles, included (+4 more)

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
Nodes (32): completeEdgeReferences(), completeFaceReferences(), decode(), decodeFaces(), dot(), edgeReference(), EdgeSig, full (+24 more)

### Community 65 - "CommandRegistry"
Cohesion: 0.11
Nodes (7): Architecture, How a command works, The document, Units, CommandRegistry, cmds_, TEST()

### Community 67 - "BodyFrame"
Cohesion: 0.15
Nodes (14): BodyFrame, diag, dx, dy, dz, x0, y0, z0 (+6 more)

### Community 68 - "Theme"
Cohesion: 0.22
Nodes (4): Theme, colors_, public, styled_

### Community 69 - "PlaneEdges"
Cohesion: 0.17
Nodes (5): PlaneEdges, arcs, curves, segments, vertices

### Community 70 - "Command.cpp"
Cohesion: 0.13
Nodes (14): CommandSession, inputs_, expressionKey(), checkInputValue(), CommandContext::evaluateExpression(), CommandDef::input(), CommandSession::applyInTransaction(), CommandSession::cancel() (+6 more)

### Community 71 - "ParametersDialog.cpp"
Cohesion: 0.10
Nodes (12): number(), ParametersDialog, building_, error_, filter_, listener_, ParametersDialog::ParametersDialog(), public (+4 more)

### Community 72 - "TEST"
Cohesion: 0.09
Nodes (3): param(), TEST(), tmp()

### Community 73 - "curve"
Cohesion: 0.31
Nodes (10): curve(), curves(), entityCurves(), interiorPoint(), profileAt(), profiles(), splineHandles(), textShape() (+2 more)

### Community 74 - "Kind"
Cohesion: 0.09
Nodes (21): HudField, edit, editing, kind, locked, value, Kind, Angle (+13 more)

### Community 75 - "InputType"
Cohesion: 0.08
Nodes (21): bindTsr(), fromPy(), toPy(), typeName(), InputType, Axis, Bodies, Body (+13 more)

### Community 76 - "Vec3"
Cohesion: 0.17
Nodes (19): SurfacePoint, normal, point, Vec3, boundingBox(), edgeMidpoint(), edgesNear(), frame() (+11 more)

### Community 77 - "Dimension"
Cohesion: 0.50
Nodes (4): Dimension, Angle, Length, Unitless

### Community 79 - "QString"
Cohesion: 0.11
Nodes (7): CommandDialog::CommandDialog(), ExpressionSpinBox, eval_, expression_, shown_, formatNumber(), dimensionOf()

### Community 80 - "SketchDisplay"
Cohesion: 0.12
Nodes (11): ProfileObject, index, sketch, SketchDisplay, construction, curves, fixedCurves, frame (+3 more)

### Community 81 - "Command"
Cohesion: 0.04
Nodes (59): Adding a tool, Command, CommandDef, feature, icon, id, inputs, name (+51 more)

### Community 82 - "Measurement"
Cohesion: 0.13
Nodes (14): Kind, Angle, Area, Length, Volume, Measurement, from, hasLine (+6 more)

### Community 83 - "SketchCurves.cpp"
Cohesion: 0.13
Nodes (18): crossings(), crossingsOf(), Curve2d, curve2d(), periodic, t0, t1, endIsFree() (+10 more)

### Community 85 - "Level"
Cohesion: 0.16
Nodes (13): debug(), error(), info(), Level, Debug, Error, Info, Warning (+5 more)

### Community 86 - "README.md"
Cohesion: 0.11
Nodes (15): Build, Conventions, Development, Tests, Reference parts, Fusion feature checklist, Roadmap, Contents (+7 more)

### Community 87 - "Document.cpp"
Cohesion: 0.06
Nodes (43): DocumentError, SketchRecord, data, name, offset, plane, checkViewName(), Document::abortTransaction() (+35 more)

### Community 89 - "rect"
Cohesion: 0.10
Nodes (6): QTimer, SelectionBox, crossing, Viewport::selectArrowValue(), height, rect()

### Community 90 - "MainWindow::MainWindow"
Cohesion: 0.15
Nodes (3): PythonHost, MainWindow::MainWindow(), MainWindow::showPreferences()

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

### Community 96 - ".refresh"
Cohesion: 0.14
Nodes (4): MainWindow::buildSketchTab(), MainWindow::enterSketchMode(), MainWindow::exitSketchMode(), MainWindow::applySection()

### Community 97 - "Feature"
Cohesion: 0.17
Nodes (11): Feature, commandId, error, id, inputs, name, parameterNames, rolledBack (+3 more)

### Community 98 - "FakeDoc"
Cohesion: 0.17
Nodes (6): FakeDoc, aborts, commits, items, open, snapshot

### Community 99 - "ModelParameter"
Cohesion: 0.13
Nodes (13): ModelParameter, angle, expression, input, label, name, owner, unit (+5 more)

### Community 100 - "QDialog"
Cohesion: 0.17
Nodes (5): QDialog, MainWindow::exportDesign(), MainWindow::measurePick(), MainWindow::openMeasure(), toolWindow()

### Community 102 - "sstream"
Cohesion: 0.17
Nodes (5): doc_(), Document::Document(), Document::ocafBytes(), ocafApplication(), Document::load()

### Community 103 - "cachedProfiles"
Cohesion: 0.20
Nodes (3): MainWindow::updateDragArrow(), cachedProfiles(), keyOf()

### Community 104 - "BoundingBox"
Cohesion: 0.22
Nodes (9): BoundingBox, max, min, extendedWire(), massProperties(), measure(), offsetOpenWire(), polygonToCircleLoft() (+1 more)

### Community 106 - "SectionState"
Cohesion: 0.25
Nodes (7): SectionState, active, angle, flip, offset, plane, visible

### Community 107 - "Display"
Cohesion: 0.25
Nodes (7): Display, constraints, construction, dimensions, points, profiles, projected

### Community 108 - "main"
Cohesion: 0.27
Nodes (6): listCommands(), main(), usage(), main(), smoke(), key

### Community 109 - "Kernel.h"
Cohesion: 0.08
Nodes (23): Axis, X, Y, Z, BooleanOp, Cut, Intersect, Join (+15 more)

### Community 110 - "TopologyCounts"
Cohesion: 0.18
Nodes (16): Section, Circular, Square, Triangular, TopologyCounts, edges, faces, shells (+8 more)

### Community 111 - "Column"
Cohesion: 0.25
Nodes (8): Column, kComment, kExpression, kName, kParameter, kStar, kUnit, kValue

### Community 112 - ".redrawAll"
Cohesion: 0.11
Nodes (9): keys(), NavPreset, Fusion, SolidWorks, Tinkercad, Viewport::Viewport(), Viewport::clearDragArrow(), Viewport::clearSecondArrow() (+1 more)

### Community 113 - "ParametersDialog.h"
Cohesion: 0.20
Nodes (4): QLabel, QLineEdit, QTreeWidget, QTreeWidgetItem

### Community 114 - "uninstall.sh"
Cohesion: 0.52
Nodes (6): die(), manifest_for(), refresh(), uninstall.sh script, step(), usage()

### Community 115 - "install.sh"
Cohesion: 0.60
Nodes (5): die(), refresh(), install.sh script, step(), usage()

### Community 116 - "TestFramework.h"
Cohesion: 0.16
Nodes (11): Result, error, ok, output, captured(), PythonHost::exec(), PythonHost::runScript(), Case (+3 more)

### Community 117 - ".rebuild"
Cohesion: 0.10
Nodes (12): hiddenColour(), qc(), rgb(), sharpEdges(), Style, Shaded, ShadedEdges, ShadedHidden (+4 more)

### Community 118 - "MarkingMenu"
Cohesion: 0.40
Nodes (3): MarkingMenu, enabled, public

### Community 120 - "CommandRegistry::run"
Cohesion: 0.22
Nodes (4): CommandRegistry::add(), CommandRegistry::all(), CommandRegistry::find(), CommandRegistry::run()

### Community 121 - "path"
Cohesion: 0.47
Nodes (8): MainWindow::print3d(), NamedShape, compoundOf(), exportShapes(), fmt(), write3mf(), writeObj(), path

### Community 123 - "Placement"
Cohesion: 0.25
Nodes (7): Placement, angle, cx, cy, dx, dy, scale

### Community 124 - "ChainSegment"
Cohesion: 0.67
Nodes (3): ChainSegment, entity, forward

### Community 126 - "Mesh"
Cohesion: 0.40
Nodes (3): Mesh, nodes, triangles

### Community 127 - "Entry"
Cohesion: 0.50
Nodes (3): Entry, data, name

### Community 128 - ".updatePreview"
Cohesion: 0.06
Nodes (24): ext(), fixedColor(), freeColor(), lineEntity(), qc(), rgb(), wire(), Sketch (+16 more)

### Community 129 - "Joint"
Cohesion: 0.22
Nodes (5): Joint, asBuilt_, def_, Sweep, def_

### Community 141 - "Point"
Cohesion: 0.52
Nodes (6): Point, x, y, z, customPlaneSpec(), toDxf()

### Community 142 - "SplineHandle"
Cohesion: 0.29
Nodes (7): SplineHandle, arm, index, tx, ty, x, y

## Knowledge Gaps
- **774 isolated node(s):** `ok`, `output`, `error`, `isReal`, `real` (+769 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 1442 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **28 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `optional` connect `optional` to `Viewport`, `MainWindow`, `Kernel.cpp`, `AnalysisSettings`, `MainWindowArrow.cpp`, `Io.cpp`, `Unit`, `ViewportSketch.cpp`, `Inputs`, `string`, `SketchOps.cpp`, `ViewportArrow.cpp`, `Constraint`, `DocCommands.cpp`, `CommandDialog.cpp`, `SketchEditor.cpp`, `AnalysisSettings`, `ParamSet`, `InputDef`, `SketchEditor.h`, `Entity`, `Session`, `Vec3`, `QString`, `SketchCurves.cpp`, `Document.cpp`, `ReplayStep`, `Feature`, `Kernel.h`?**
  _High betweenness centrality (0.112) - this node is a cross-community bridge._
- **What connects `ok`, `output`, `error` to the rest of the system?**
  _774 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Viewport` be split into smaller, more focused modules?**
  _Cohesion score 0.015845477677538748 - nodes in this community are weakly interconnected._
- **Why does `Viewport` connect `Viewport` to `ViewportArrow.cpp`, `MainWindow`, `src/main.cpp`, `Unit`, `Viewport.cpp`, `optional`, `AnalysisSettings`, `AnalysisSettings`, `SketchDisplay`, `.redrawAll`, `SketchCurves.cpp`, `.rebuild`, `.toPixels`, `ViewportAnalysis.cpp`, `rect`, `.setSelectionFilter`?**
  _High betweenness centrality (0.099) - this node is a cross-community bridge._
- **Should `Icons.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.05337690631808279 - nodes in this community are weakly interconnected._
- **Why does `SketchEditor` connect `SketchEditor` to `.updatePreview`, `Viewport`, `ParameterCompleter`, `Constraint`, `ViewportArrow.cpp`, `PlaneEdges`, `Snap`, `Kind`, `Display`, `Pick`, `AnalysisSettings`, `SketchEditor.cpp`, `Unit`, `.setTool`, `SketchEditor.h`, `Entity`, `Session`, `ReplayStep`?**
  _High betweenness centrality (0.086) - this node is a cross-community bridge._
- **Should `Session.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.11498257839721254 - nodes in this community are weakly interconnected._