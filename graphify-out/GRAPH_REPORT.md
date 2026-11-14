# Graph Report - tessera  (2026-11-13)

## Corpus Check
- 382 files · ~243,980 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 56 file(s) not represented in the graph (top: .drive 48, (none) 5, .cmake 1)

## Summary
- 3592 nodes · 9150 edges · 125 communities (103 shown, 22 thin omitted)
- Extraction: 85% EXTRACTED · 15% INFERRED · 0% AMBIGUOUS · INFERRED: 1411 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `367a8ba3`
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
- AnalysisSettings
- Kind
- .openMarkingMenu
- CommandDialog
- Io.cpp
- Parser
- MainWindowTools.cpp
- Unit
- Document
- MainWindow.cpp
- TEST
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
- Expression.cpp
- MainWindow::MainWindow
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
- TEST
- ParamSet
- MainWindowSketch.cpp
- InputDef
- sketchFor
- .toPixels
- MainWindowArrow.cpp
- CommandSession
- Theme.cpp
- CommandRegistry::run
- Entity
- xdrive.py
- SketchGeometry.cpp
- Session
- ViewportArrow.cpp
- BodyFrame
- CommandRegistry
- Feature
- BodyFrame
- Theme
- string
- ParametersDialog.cpp
- TEST
- TEST
- Column
- InputType
- Vec3
- QString
- Command.cpp
- SketchDisplay
- Command
- Measurement
- SketchCurves.cpp
- MarkingMenu.cpp
- Level
- README.md
- string
- test_feature_pattern.py
- .initializeGL
- cachedProfiles
- Sketch.h
- FormatInfo
- Known differences still to build
- bindAdsk
- ReplayStep
- CommandDialog::CommandDialog
- Tool
- FakeDoc
- test_text_box_path.py
- src/main.cpp
- sstream
- SectionState
- Display
- main
- Kernel.h
- uninstall.sh
- install.sh
- TestFramework.h
- .redrawAll
- Value.h
- test_incremental_replay.py
- Placement
- ChainSegment
- .mouseMove
- Session::notifyChanged
- DocCommands.cpp
- LAB_NOTES.md
- MarkingMenu
- Dimension
- build.sh
- live-test.sh
- Point
- SplineHandle

## God Nodes (most connected - your core abstractions)
1. `Viewport` - 251 edges
2. `SketchEditor` - 185 edges
3. `MainWindow` - 180 edges
4. `Inputs` - 140 edges
5. `Document` - 118 edges
6. `render()` - 110 edges
7. `CommandContext` - 102 edges
8. `CommandDialog` - 90 edges
9. `Command` - 63 edges
10. `CommandError` - 57 edges

## Surprising Connections (you probably didn't know these)
- `Tests` --references--> `unit()`  [INFERRED]
  docs/DEVELOPMENT.md → modules/sketch/src/SketchOps.cpp
- `Known gaps` --references--> `QTabWidget`  [INFERRED]
  docs/KNOWN_GAPS.md → modules/app/src/MainWindow.h
- `Architecture` --references--> `InputDef`  [INFERRED]
  docs/ARCHITECTURE.md → modules/core/include/tsr/core/Command.h
- `How a command works` --references--> `CommandDef`  [INFERRED]
  docs/ARCHITECTURE.md → modules/core/include/tsr/core/Command.h
- `Architecture` --references--> `CommandRegistry`  [INFERRED]
  docs/ARCHITECTURE.md → modules/core/include/tsr/core/CommandRegistry.h

## Import Cycles
- None detected.

## Communities (125 total, 22 thin omitted)

### Community 0 - "Viewport"
Cohesion: 0.02
Nodes (67): view_, QLineEdit, Viewport, analysis_, analysisObjects_, appliedGridStep_, arrowBoxes_, arrowDragging_ (+59 more)

### Community 1 - "Icons.cpp"
Cohesion: 0.06
Nodes (115): arc3Icon(), arcIcon(), arcTangentIcon(), arrow(), axisIcon(), box(), breakIcon(), centerRectIcon() (+107 more)

### Community 2 - "Session.cpp"
Cohesion: 0.17
Nodes (24): historyEdit(), plainEdit(), Session::addListener(), Session::addNamedView(), Session::deleteFeature(), Session::deleteNamedView(), Session::deleteParameter(), Session::newDocument() (+16 more)

### Community 4 - "MainWindow"
Cohesion: 0.03
Nodes (63): CommandDialog, MainWindow, active_, arrowInput_, arrowInput2_, bodiesBeforeCommand_, combEdges_, combPicking_ (+55 more)

### Community 5 - "run_oracle.py"
Cohesion: 0.08
Nodes (54): add_point(), arc_poly(), body_at(), body_list(), build_sketch(), chain(), circumcentre(), cm() (+46 more)

### Community 7 - "Document"
Cohesion: 0.03
Nodes (16): Document, effects_, lastReplayed_, lastReused_, modified_, pendingTools_, registry_, replaying_ (+8 more)

### Community 8 - "Viewport.cpp"
Cohesion: 0.04
Nodes (9): glide(), hiddenColour(), keys(), qc(), QtFrameBuffer, rgb(), sharpEdges(), Viewport::Viewport() (+1 more)

### Community 9 - "SketchEditor"
Cohesion: 0.03
Nodes (55): HandleHit, back, index, spline, PlaneEdges, arcs, curves, segments (+47 more)

### Community 10 - "Document::recompute"
Cohesion: 0.15
Nodes (8): Document::captureStep(), Document::currentParams(), Document::expressionEnv(), Document::modelParameters(), Document::recompute(), Document::recordFeature(), Document::removeFeature(), toJson()

### Community 11 - "optional"
Cohesion: 0.10
Nodes (7): QComboBox, QDialogButtonBox, QFormLayout, QLabel, tmp(), fail(), Failure

### Community 12 - "Kernel.cpp"
Cohesion: 0.04
Nodes (6): dot(), faceScore(), isoCoarsePitch(), score(), topologyCounts(), vec()

### Community 13 - "AnalysisSettings"
Cohesion: 0.07
Nodes (15): AnalysisKind, CurvatureMap, Draft, None, Zebra, AnalysisSettings, curvatureScale, draftAngle (+7 more)

### Community 14 - "Kind"
Cohesion: 0.07
Nodes (26): EdgeFeature, def_, kind_, FaceFeature, def_, kind_, Kind, Angle (+18 more)

### Community 15 - ".openMarkingMenu"
Cohesion: 0.10
Nodes (4): MainWindow::beginSketch(), MainWindow::buildSketchTab(), MainWindow::enterSketchMode(), MainWindow::buildUiCommands()

### Community 16 - "CommandDialog"
Cohesion: 0.06
Nodes (27): CommandDialog, bodiesId_, bodiesLabel_, bodyInput_, buttons_, cmd_, conditional_, edgesId_ (+19 more)

### Community 17 - "Io.cpp"
Cohesion: 0.07
Nodes (26): MainWindow::print3d(), FileFormat, Brep, Iges, Obj, Step, Stl, ThreeMF (+18 more)

### Community 18 - "Parser"
Cohesion: 0.18
Nodes (15): Quantity, angle, length, value, describe(), isIdentChar(), Parser, ang_ (+7 more)

### Community 19 - "MainWindowTools.cpp"
Cohesion: 0.06
Nodes (12): QDialog, MainWindow::chooseUnits(), MainWindow::exportDesign(), MainWindow::measurePick(), MainWindow::openAnalysis(), MainWindow::openMeasure(), MainWindow::sectionFrame(), MainWindow::sectionPlane() (+4 more)

### Community 20 - "Unit"
Cohesion: 0.10
Nodes (28): MainWindow::checkInterference(), MainWindow::driveJoints(), MainWindow::formatLength(), MainWindow::gridSettings(), MainWindow::insertFile(), MainWindow::lengthUnit(), MainWindow::openSection(), MainWindow::showCenterOfMass() (+20 more)

### Community 21 - "Document"
Cohesion: 0.20
Nodes (7): ConstructAxisPoint, def_, kind_, jointOrigin(), JointPick, frame, revolveAxis()

### Community 22 - "MainWindow.cpp"
Cohesion: 0.09
Nodes (3): commandIcon(), qs(), MainWindow::applySection()

### Community 23 - "TEST"
Cohesion: 0.08
Nodes (19): Sketch, constraints, entities, points, texts, Text, angle, corner (+11 more)

### Community 24 - "Sketch.cpp"
Cohesion: 0.09
Nodes (16): SplineKind, Conic, Control, Fit, entityTypeName(), isDimension(), Sketch::addConstraint(), Sketch::addSpline() (+8 more)

### Community 25 - "ViewportSketch.cpp"
Cohesion: 0.07
Nodes (9): SelectionBox, crossing, faceStyle(), lineStyle(), rgb(), Viewport::lookAt(), Viewport::planePoint(), Viewport::toWidget() (+1 more)

### Community 26 - "SketchPalette"
Cohesion: 0.06
Nodes (26): flatButton(), QCheckBox, QLabel, QToolButton, QWidget, SketchEditor, SketchPalette, body_ (+18 more)

### Community 27 - "Kind"
Cohesion: 0.07
Nodes (24): Hit, index, kind, HudField, edit, editing, kind, locked (+16 more)

### Community 28 - "Inputs"
Cohesion: 0.07
Nodes (19): CommandContext, CommandError, Inputs, CommandSession::CommandSession(), getBool(), getInt(), getReal(), applyOperation() (+11 more)

### Community 29 - "string"
Cohesion: 0.09
Nodes (30): DocumentError, checkViewName(), Document::abortTransaction(), Document::addNamedView(), Document::addUserParameter(), Document::commitTransaction(), Document::openTransaction(), Document::reevaluateParameters() (+22 more)

### Community 30 - "Colors"
Cohesion: 0.07
Nodes (28): Colors, base, border, cubeBox, cubeText, errorBackground, grid, gridMajor (+20 more)

### Community 31 - "KernelError"
Cohesion: 0.19
Nodes (37): KernelError, vertices, asSolid(), boolean(), chamfer(), chamferEx(), deleteFaces(), draft() (+29 more)

### Community 32 - "SketchOps.cpp"
Cohesion: 0.16
Nodes (30): at(), chainOf(), chamferCorner(), circularPattern(), copyEntities(), cornerAt(), cross(), dot() (+22 more)

### Community 33 - "ViewportArrow.cpp"
Cohesion: 0.06
Nodes (20): MarkingMenu::mouseMoveEvent(), QMouseEvent, ViewInteractor, Viewport::frontEdgeOwner(), rgb(), segmentDistance(), Viewport::arrowAt(), Viewport::arrowMouseMove() (+12 more)

### Community 34 - "ParameterCompleter"
Cohesion: 0.12
Nodes (8): ParameterCompleter, completer_, edit_, names_, ParameterCompleter::ParameterCompleter(), public, QCompleter, QLineEdit

### Community 35 - "Constraint"
Cohesion: 0.09
Nodes (20): Constraint, driven, entities, expression, hasLabel, labelX, labelY, name (+12 more)

### Community 36 - "Expression.cpp"
Cohesion: 0.20
Nodes (12): ExpressionEnv, lengthUnit, lookup, ExpressionError, evaluateExpression(), evaluateQuantity(), expressionReferences(), isConstantName() (+4 more)

### Community 37 - "MainWindow::MainWindow"
Cohesion: 0.08
Nodes (5): PythonHost, MainWindow::MainWindow(), MainWindow::exitSketchMode(), MainWindow::onEdgeClicked(), MainWindow::showPreferences()

### Community 38 - "solve"
Cohesion: 0.11
Nodes (15): set, addConstraintChecked(), Layout, n, px, py, rad, makeLayout() (+7 more)

### Community 39 - "Snap"
Cohesion: 0.11
Nodes (18): Snap, alignX, alignY, bodyArc, bodySegment, entity, fromX, fromY (+10 more)

### Community 41 - "ConstraintType"
Cohesion: 0.09
Nodes (23): ConstraintType, Angle, Coincident, Collinear, Concentric, Diameter, Distance, Equal (+15 more)

### Community 42 - "AdskModule.cpp"
Cohesion: 0.07
Nodes (18): Application, BRepBodies, Component, Design, Product, raiseIfError(), UserParameter, name (+10 more)

### Community 43 - "Pick"
Cohesion: 0.13
Nodes (14): Pick, bodyArc, bodyPoint, bodySegment, hit, midpointOf, onEntity, onXAxis (+6 more)

### Community 46 - "Zip.cpp"
Cohesion: 0.17
Nodes (11): Entry, data, name, ZipError, crc32(), get16(), get32(), put16() (+3 more)

### Community 47 - "AnalysisSettings"
Cohesion: 0.10
Nodes (16): DragArrow, base, dir, radius, ref, ring, value, PendingLook (+8 more)

### Community 48 - "TEST"
Cohesion: 0.22
Nodes (3): slurp(), TEST(), tmp()

### Community 49 - "ParamSet"
Cohesion: 0.07
Nodes (43): ModelParameter, angle, expression, input, label, name, owner, unit (+35 more)

### Community 50 - "MainWindowSketch.cpp"
Cohesion: 0.09
Nodes (12): MainWindow::cancelSketch(), MainWindow::editSketch(), MainWindow::finishSketch(), MainWindow::onProfileClicked(), MainWindow::originalShape(), MainWindow::sketchPalette(), MainWindow::sketchVisible(), MainWindow::startSketch() (+4 more)

### Community 51 - "InputDef"
Cohesion: 0.08
Nodes (24): InputDef, choices, defaultValue, id, label, max, min, minExclusive (+16 more)

### Community 52 - "sketchFor"
Cohesion: 0.14
Nodes (13): Hole, def_, HoleSize, holeSize(), modeled, pitch, radius, Pipe (+5 more)

### Community 54 - "MainWindowArrow.cpp"
Cohesion: 0.12
Nodes (8): ArrowPlacement, base, dir, edgePlacement(), facesPlacement(), MainWindow::attachArrowCompleters(), MainWindow::patternCentre(), MainWindow::pickedFaces()

### Community 55 - "CommandSession"
Cohesion: 0.16
Nodes (7): CommandSession, inputs_, OwnedCommand, owned, OwningCommandSession, Session::begin(), Session::editFeature()

### Community 56 - "Theme.cpp"
Cohesion: 0.19
Nodes (6): setIconTheme(), darkColors(), darkPalette(), darkStyleSheet(), lightColors(), lightStyleSheet()

### Community 57 - "CommandRegistry::run"
Cohesion: 0.22
Nodes (4): CommandRegistry::add(), CommandRegistry::all(), CommandRegistry::find(), CommandRegistry::run()

### Community 58 - "Entity"
Cohesion: 0.10
Nodes (13): QObject, Entity, a, b, center, construction, fit, handles (+5 more)

### Community 59 - "xdrive.py"
Cohesion: 0.28
Nodes (15): button(), canvas(), click(), drag(), flush(), geometry(), key(), keycode() (+7 more)

### Community 61 - "SketchGeometry.cpp"
Cohesion: 0.07
Nodes (15): Profile, area, face, x, y, curve(), curves(), entityCurves() (+7 more)

### Community 62 - "Session"
Cohesion: 0.08
Nodes (6): Session, commands_, doc_, listeners_, nextListener_, path_

### Community 63 - "ViewportArrow.cpp"
Cohesion: 0.14
Nodes (4): packed(), ramp(), shade(), Viewport::buildAnalysis()

### Community 64 - "BodyFrame"
Cohesion: 0.11
Nodes (29): boundingBox(), completeEdgeReferences(), completeFaceReferences(), decode(), decodeFaces(), edgeReference(), EdgeSig, full (+21 more)

### Community 65 - "CommandRegistry"
Cohesion: 0.12
Nodes (6): CommandRegistry, cmds_, EditFeature, def_, featureId_, TEST()

### Community 66 - "Feature"
Cohesion: 0.18
Nodes (10): Feature, commandId, error, id, inputs, name, parameterNames, rolledBack (+2 more)

### Community 67 - "BodyFrame"
Cohesion: 0.12
Nodes (16): BoundingBox, max, min, BodyFrame, diag, dx, dy, dz (+8 more)

### Community 68 - "Theme"
Cohesion: 0.22
Nodes (4): Theme, colors_, public, styled_

### Community 69 - "string"
Cohesion: 0.14
Nodes (9): AddUserParameter, def_, isIdentifier(), NewComponent, def_, sectionOf(), Sweep, def_ (+1 more)

### Community 71 - "ParametersDialog.cpp"
Cohesion: 0.08
Nodes (16): number(), ParametersDialog, building_, error_, filter_, listener_, ParametersDialog::ParametersDialog(), public (+8 more)

### Community 73 - "TEST"
Cohesion: 0.31
Nodes (3): env(), mm(), TEST()

### Community 74 - "Column"
Cohesion: 0.25
Nodes (8): Column, kComment, kExpression, kName, kParameter, kStar, kUnit, kValue

### Community 75 - "InputType"
Cohesion: 0.12
Nodes (17): InputType, Axis, Bodies, Body, Bool, Choice, Edges, Faces (+9 more)

### Community 76 - "Vec3"
Cohesion: 0.18
Nodes (14): MassProperties, area, centerOfMass, volume, SurfacePoint, normal, point, Vec3 (+6 more)

### Community 77 - "QString"
Cohesion: 0.11
Nodes (6): ExpressionSpinBox, eval_, expression_, shown_, formatNumber(), dimensionOf()

### Community 79 - "Command.cpp"
Cohesion: 0.22
Nodes (11): expressionKey(), checkInputValue(), CommandContext::evaluateExpression(), CommandDef::input(), CommandSession::applyInTransaction(), CommandSession::cancel(), CommandSession::execute(), CommandSession::preview() (+3 more)

### Community 80 - "SketchDisplay"
Cohesion: 0.12
Nodes (11): ProfileObject, index, sketch, SketchDisplay, construction, curves, fixedCurves, frame (+3 more)

### Community 81 - "Command"
Cohesion: 0.03
Nodes (56): Architecture, How a command works, The document, Units, Adding a tool, Command, CommandDef, feature (+48 more)

### Community 82 - "Measurement"
Cohesion: 0.11
Nodes (17): Kind, Angle, Area, Length, Volume, Measurement, from, hasLine (+9 more)

### Community 83 - "SketchCurves.cpp"
Cohesion: 0.13
Nodes (18): crossings(), crossingsOf(), Curve2d, curve2d(), periodic, t0, t1, endIsFree() (+10 more)

### Community 84 - "MarkingMenu.cpp"
Cohesion: 0.06
Nodes (25): UiCommand, enabled, icon, id, name, panel, run, shortcut (+17 more)

### Community 85 - "Level"
Cohesion: 0.12
Nodes (13): debug(), error(), info(), Level, Debug, Error, Info, Warning (+5 more)

### Community 86 - "README.md"
Cohesion: 0.08
Nodes (20): Build, Conventions, Development, Tests, Include 3D Geometry, Known gaps, Sketch text, Splines and conics (+12 more)

### Community 87 - "string"
Cohesion: 0.07
Nodes (33): optional, bodyNumber(), Document::addBody(), Document::axisFrame(), Document::bodies(), Document::body(), Document::bodyName(), Document::bodyShapes() (+25 more)

### Community 91 - "Sketch.h"
Cohesion: 0.16
Nodes (10): EntityType, Arc, Circle, Ellipse, Line, Spline, isRound(), Rect (+2 more)

### Community 92 - "FormatInfo"
Cohesion: 0.40
Nodes (5): FormatInfo, canImport, extensions, format, name

### Community 93 - "Known differences still to build"
Cohesion: 0.15
Nodes (12): Data and files, Findings from the videos, Fusion study list, Interface, Known differences still to build, Navigation and display, Selection and the canvas, Sketch (+4 more)

### Community 94 - "bindAdsk"
Cohesion: 0.29
Nodes (3): bindAdsk(), BRepBody, index

### Community 95 - "ReplayStep"
Cohesion: 0.05
Nodes (42): Body, display, name, shape, Component, bodies, name, ConstructionAxis (+34 more)

### Community 97 - "Tool"
Cohesion: 0.16
Nodes (6): SketchEditor::SketchEditor(), edges, Tool, op, shape, target

### Community 98 - "FakeDoc"
Cohesion: 0.17
Nodes (6): FakeDoc, aborts, commits, items, open, snapshot

### Community 100 - "src/main.cpp"
Cohesion: 0.10
Nodes (4): QAbstractButton, QAction, grabWindowWithPanels(), writeLiveGeometry()

### Community 102 - "sstream"
Cohesion: 0.15
Nodes (5): doc_(), Document::Document(), Document::ocafBytes(), ocafApplication(), Document::load()

### Community 106 - "SectionState"
Cohesion: 0.25
Nodes (7): SectionState, active, angle, flip, offset, plane, visible

### Community 107 - "Display"
Cohesion: 0.25
Nodes (7): Display, constraints, construction, dimensions, points, profiles, projected

### Community 108 - "main"
Cohesion: 0.27
Nodes (6): listCommands(), main(), usage(), main(), smoke(), key

### Community 110 - "Kernel.h"
Cohesion: 0.07
Nodes (36): Axis, X, Y, Z, BooleanOp, Cut, Intersect, Join (+28 more)

### Community 114 - "uninstall.sh"
Cohesion: 0.52
Nodes (6): die(), manifest_for(), refresh(), uninstall.sh script, step(), usage()

### Community 115 - "install.sh"
Cohesion: 0.60
Nodes (5): die(), refresh(), install.sh script, step(), usage()

### Community 116 - "TestFramework.h"
Cohesion: 0.12
Nodes (13): Result, error, ok, output, captured(), PYBIND11_EMBEDDED_MODULE(), PythonHost::exec(), PythonHost::PythonHost() (+5 more)

### Community 117 - ".redrawAll"
Cohesion: 0.09
Nodes (8): NavPreset, Fusion, SolidWorks, Tinkercad, Viewport::setCurvatureComb(), Viewport::clearDragArrow(), Viewport::clearSecondArrow(), Viewport::setInteractor()

### Community 123 - "Placement"
Cohesion: 0.25
Nodes (7): Placement, angle, cx, cy, dx, dy, scale

### Community 124 - "ChainSegment"
Cohesion: 0.67
Nodes (3): ChainSegment, entity, forward

### Community 128 - ".mouseMove"
Cohesion: 0.11
Nodes (9): ccwContains(), circumcircle(), ext(), fixedColor(), freeColor(), lineEntity(), qc(), rgb() (+1 more)

### Community 131 - "DocCommands.cpp"
Cohesion: 0.11
Nodes (28): axisOf(), bodyCentre(), checkPattern(), CopyFn, differenceOrNull(), evaluateDimensions(), Loft, def_ (+20 more)

### Community 134 - "MarkingMenu"
Cohesion: 0.40
Nodes (3): MarkingMenu, enabled, public

### Community 135 - "Dimension"
Cohesion: 0.50
Nodes (4): Dimension, Angle, Length, Unitless

### Community 141 - "Point"
Cohesion: 0.23
Nodes (10): Point, x, y, z, SketchError, Sketch::checkIndices(), Sketch::fromJson(), customPlaneSpec() (+2 more)

### Community 142 - "SplineHandle"
Cohesion: 0.29
Nodes (7): SplineHandle, arm, index, tx, ty, x, y

## Knowledge Gaps
- **740 isolated node(s):** `ok`, `output`, `error`, `isReal`, `real` (+735 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 1400 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **22 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `optional` connect `string` to `Viewport`, `DocCommands.cpp`, `MainWindow`, `optional`, `Kernel.cpp`, `AnalysisSettings`, `Io.cpp`, `Parser`, `Unit`, `ViewportSketch.cpp`, `SketchOps.cpp`, `ViewportArrow.cpp`, `Constraint`, `Expression.cpp`, `CommandDialog.cpp`, `SketchEditor.cpp`, `AnalysisSettings`, `ParamSet`, `InputDef`, `sketchFor`, `MainWindowArrow.cpp`, `Entity`, `Session`, `Feature`, `Vec3`, `QString`, `SketchCurves.cpp`, `ReplayStep`, `Kernel.h`?**
  _High betweenness centrality (0.102) - this node is a cross-community bridge._
- **What connects `ok`, `output`, `error` to the rest of the system?**
  _740 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Viewport` be split into smaller, more focused modules?**
  _Cohesion score 0.01664516129032258 - nodes in this community are weakly interconnected._
- **Why does `Viewport` connect `Viewport` to `ViewportArrow.cpp`, `Viewport.cpp`, `AdskModule.cpp`, `AnalysisSettings`, `AnalysisSettings`, `SketchDisplay`, `SketchCurves.cpp`, `MainWindowTools.cpp`, `.redrawAll`, `.toPixels`, `string`, `.initializeGL`, `ViewportSketch.cpp`, `ViewportArrow.cpp`?**
  _High betweenness centrality (0.092) - this node is a cross-community bridge._
- **Should `Icons.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.05761779777527809 - nodes in this community are weakly interconnected._
- **Why does `MainWindow` connect `MainWindow` to `ParameterCompleter`, `src/main.cpp`, `MainWindow::MainWindow`, `cachedProfiles`, `ParametersDialog.cpp`, `SectionState`, `optional`, `main`, `.openMarkingMenu`, `MainWindowSketch.cpp`, `MainWindowTools.cpp`, `MarkingMenu.cpp`, `Unit`, `MainWindow.cpp`, `SketchPalette`, `Session`?**
  _High betweenness centrality (0.087) - this node is a cross-community bridge._
- **Should `tsr` be split into smaller, more focused modules?**
  _Cohesion score 0.04712301587301587 - nodes in this community are weakly interconnected._