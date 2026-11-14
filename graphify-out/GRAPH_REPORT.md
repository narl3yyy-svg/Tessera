# Graph Report - tessera  (2026-11-13)

## Corpus Check
- 383 files · ~247,592 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 56 file(s) not represented in the graph (top: .drive 48, (none) 5, .cmake 1)

## Summary
- 3626 nodes · 9240 edges · 139 communities (114 shown, 25 thin omitted)
- Extraction: 85% EXTRACTED · 15% INFERRED · 0% AMBIGUOUS · INFERRED: 1422 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `2f16c6e7`
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
- CommandDialog
- Io.cpp
- Unit
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
- CommandError
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
- Affine
- ParamSet
- MainWindowSketch.cpp
- CommandDef
- sketchFor
- .toPixels
- ViewportAnalysis.cpp
- CommandSession
- Theme.cpp
- .rebuild
- Entity
- xdrive.py
- Session
- ParametersDialog
- BodyFrame
- CommandRegistry
- Feature
- BodyFrame
- Theme
- Joint
- ParametersDialog.cpp
- TEST
- curve
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
- rect
- cachedProfiles
- EntityType
- FormatInfo
- Known differences still to build
- QDialog
- ReplayStep
- ExpressionSpinBox
- Tool
- FakeDoc
- QMouseEvent
- src/main.cpp
- .add
- sstream
- TsrModule.cpp
- openWallBand
- Joints
- SectionState
- Display
- main
- smoke
- TopologyCounts
- UserParameter
- Axis
- BooleanOp
- uninstall.sh
- install.sh
- TestFramework.h
- ThreadInfo
- fail
- Value.h
- test_incremental_replay.py
- Placement
- ChainSegment
- ChamferType
- Session::addListener
- Placement::apply
- .mouseMove
- Rect
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
- `How a command works` --references--> `CommandDef`  [INFERRED]
  docs/ARCHITECTURE.md → modules/core/include/tsr/core/Command.h
- `Adding a tool` --references--> `CommandDef`  [INFERRED]
  docs/DEVELOPMENT.md → modules/core/include/tsr/core/Command.h
- `Architecture` --references--> `CommandRegistry`  [INFERRED]
  docs/ARCHITECTURE.md → modules/core/include/tsr/core/CommandRegistry.h

## Import Cycles
- None detected.

## Communities (139 total, 25 thin omitted)

### Community 0 - "Viewport"
Cohesion: 0.02
Nodes (67): view_, QLineEdit, Viewport, analysis_, analysisObjects_, appliedGridStep_, arrowBoxes_, arrowDragging_ (+59 more)

### Community 1 - "Icons.cpp"
Cohesion: 0.06
Nodes (115): arc3Icon(), arcIcon(), arcTangentIcon(), arrow(), axisIcon(), box(), breakIcon(), centerRectIcon() (+107 more)

### Community 2 - "Session.cpp"
Cohesion: 0.18
Nodes (23): historyEdit(), plainEdit(), Session::addNamedView(), Session::deleteFeature(), Session::deleteNamedView(), Session::deleteParameter(), Session::newDocument(), Session::open() (+15 more)

### Community 3 - "tsr"
Cohesion: 0.05
Nodes (3): PYBIND11_EMBEDDED_MODULE(), letters(), dist_to_line()

### Community 4 - "MainWindow"
Cohesion: 0.03
Nodes (64): writeLiveGeometry(), CommandDialog, MainWindow, active_, arrowInput_, arrowInput2_, bodiesBeforeCommand_, combEdges_ (+56 more)

### Community 5 - "run_oracle.py"
Cohesion: 0.08
Nodes (54): add_point(), arc_poly(), body_at(), body_list(), build_sketch(), chain(), circumcentre(), cm() (+46 more)

### Community 7 - "Document"
Cohesion: 0.03
Nodes (15): Document, effects_, lastReplayed_, lastReused_, modified_, pendingTools_, registry_, replaying_ (+7 more)

### Community 8 - "Viewport.cpp"
Cohesion: 0.06
Nodes (4): glide(), keys(), QtFrameBuffer, Viewport::Viewport()

### Community 9 - "SketchEditor"
Cohesion: 0.03
Nodes (55): HandleHit, back, index, spline, PlaneEdges, arcs, curves, segments (+47 more)

### Community 10 - "Document::recompute"
Cohesion: 0.18
Nodes (8): Document::expressionEnv(), Document::recompute(), Document::recordFeature(), Document::removeFeature(), Document::setFeatureInputs(), Document::setFeatureSuppressed(), featureData(), toJson()

### Community 11 - "optional"
Cohesion: 0.11
Nodes (3): optional, CommandRegistry::all(), Document

### Community 12 - "Kernel.cpp"
Cohesion: 0.04
Nodes (6): dot(), faceScore(), isoCoarsePitch(), score(), topologyCounts(), vec()

### Community 13 - "AnalysisSettings"
Cohesion: 0.15
Nodes (13): AnalysisKind, CurvatureMap, Draft, None, Zebra, AnalysisSettings, curvatureScale, draftAngle (+5 more)

### Community 14 - "Kind"
Cohesion: 0.07
Nodes (29): ConstructPlane, def_, kind_, EdgeFeature, def_, kind_, FaceFeature, def_ (+21 more)

### Community 16 - "CommandDialog"
Cohesion: 0.05
Nodes (31): CommandDialog, bodiesId_, bodiesLabel_, bodyInput_, buttons_, cmd_, conditional_, edgesId_ (+23 more)

### Community 17 - "Io.cpp"
Cohesion: 0.08
Nodes (26): MainWindow::print3d(), FileFormat, Brep, Iges, Obj, Step, Stl, ThreeMF (+18 more)

### Community 18 - "Unit"
Cohesion: 0.07
Nodes (45): MainWindow::lengthUnit(), ExpressionEnv, lengthUnit, lookup, ExpressionError, Quantity, angle, length (+37 more)

### Community 19 - "MainWindowTools.cpp"
Cohesion: 0.09
Nodes (7): MainWindow::chooseUnits(), MainWindow::insertFile(), MainWindow::sectionFrame(), MainWindow::sectionPlane(), MainWindow::setSelectionFilter(), MainWindow::showParameters(), MainWindow::updateSectionArrow()

### Community 20 - "Unit"
Cohesion: 0.17
Nodes (12): MainWindow::checkInterference(), MainWindow::driveJoints(), MainWindow::formatLength(), MainWindow::gridSettings(), MainWindow::openSection(), MainWindow::showCenterOfMass(), MainWindow::updateMeasure(), qs() (+4 more)

### Community 21 - "Document"
Cohesion: 0.20
Nodes (9): applyOperation(), ConstructAxisPoint, def_, kind_, jointOrigin(), JointPick, frame, revolveAxis() (+1 more)

### Community 22 - "MainWindow.cpp"
Cohesion: 0.09
Nodes (3): commandIcon(), qs(), MainWindow::applySection()

### Community 23 - "TEST"
Cohesion: 0.07
Nodes (19): Sketch, constraints, entities, points, texts, Text, angle, corner (+11 more)

### Community 24 - "Sketch.cpp"
Cohesion: 0.08
Nodes (20): SketchError, SplineKind, Conic, Control, Fit, entityTypeName(), isDimension(), Sketch::addConstraint() (+12 more)

### Community 25 - "ViewportSketch.cpp"
Cohesion: 0.06
Nodes (9): QLabel, faceStyle(), lineStyle(), rgb(), Profile, area, face, x (+1 more)

### Community 26 - "SketchPalette"
Cohesion: 0.06
Nodes (27): flatButton(), QCheckBox, QLabel, QToolButton, QWidget, SketchEditor, SketchPalette, body_ (+19 more)

### Community 27 - "Kind"
Cohesion: 0.07
Nodes (24): Hit, index, kind, HudField, edit, editing, kind, locked (+16 more)

### Community 28 - "Inputs"
Cohesion: 0.07
Nodes (10): CommandContext, Inputs, CommandSession::CommandSession(), AddUserParameter, def_, checkBody(), checkPattern(), defaultBody() (+2 more)

### Community 29 - "string"
Cohesion: 0.10
Nodes (24): DocumentError, checkViewName(), Document::abortTransaction(), Document::addBody(), Document::addNamedView(), Document::addUserParameter(), Document::commitTransaction(), Document::openTransaction() (+16 more)

### Community 30 - "Colors"
Cohesion: 0.07
Nodes (28): Colors, base, border, cubeBox, cubeText, errorBackground, grid, gridMajor (+20 more)

### Community 31 - "KernelError"
Cohesion: 0.23
Nodes (30): KernelError, asSolid(), boolean(), chamfer(), chamferEx(), deleteFaces(), draft(), extrude() (+22 more)

### Community 32 - "SketchOps.cpp"
Cohesion: 0.24
Nodes (26): at(), chainOf(), chamferCorner(), circularPattern(), copyEntities(), cross(), dot(), extendLine() (+18 more)

### Community 33 - "ViewportArrow.cpp"
Cohesion: 0.05
Nodes (23): NavPreset, Fusion, SolidWorks, Tinkercad, Viewport::frontEdgeOwner(), rgb(), segmentDistance(), Viewport::arrowAt() (+15 more)

### Community 34 - "ParameterCompleter"
Cohesion: 0.12
Nodes (8): ParameterCompleter, completer_, edit_, names_, ParameterCompleter::ParameterCompleter(), public, QCompleter, QLineEdit

### Community 35 - "Constraint"
Cohesion: 0.09
Nodes (20): Constraint, driven, entities, expression, hasLabel, labelX, labelY, name (+12 more)

### Community 36 - "CommandError"
Cohesion: 0.15
Nodes (13): CommandError, getBool(), bodyCentre(), bodyName(), Extrude, def_, body, planeOf() (+5 more)

### Community 37 - "MainWindow::MainWindow"
Cohesion: 0.09
Nodes (8): PythonHost, retintIcons(), setIcon(), MainWindow::MainWindow(), MainWindow::beginSketch(), MainWindow::buildSketchTab(), MainWindow::enterSketchMode(), MainWindow::exitSketchMode()

### Community 38 - "solve"
Cohesion: 0.18
Nodes (13): set, addConstraintChecked(), Layout, n, px, py, rad, makeLayout() (+5 more)

### Community 39 - "Snap"
Cohesion: 0.11
Nodes (18): Snap, alignX, alignY, bodyArc, bodySegment, entity, fromX, fromY (+10 more)

### Community 41 - "ConstraintType"
Cohesion: 0.09
Nodes (23): ConstraintType, Angle, Coincident, Collinear, Concentric, Diameter, Distance, Equal (+15 more)

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

### Community 48 - "Affine"
Cohesion: 0.14
Nodes (13): Affine, a, b, d, e, Builder, byPlace_, k_ (+5 more)

### Community 49 - "ParamSet"
Cohesion: 0.08
Nodes (28): dimensionOf(), ModelParameter, angle, expression, input, label, name, owner (+20 more)

### Community 50 - "MainWindowSketch.cpp"
Cohesion: 0.06
Nodes (16): MainWindow::cancelSketch(), MainWindow::editSketch(), MainWindow::finishSketch(), MainWindow::onEdgeClicked(), MainWindow::onProfileClicked(), MainWindow::originalShape(), MainWindow::sketchPalette(), MainWindow::sketchVisible() (+8 more)

### Community 51 - "CommandDef"
Cohesion: 0.04
Nodes (66): Architecture, How a command works, The document, Units, CommandDef, feature, icon, id (+58 more)

### Community 52 - "sketchFor"
Cohesion: 0.13
Nodes (13): getInt(), Hole, def_, HoleSize, holeSize(), modeled, pitch, radius (+5 more)

### Community 54 - "ViewportAnalysis.cpp"
Cohesion: 0.06
Nodes (14): ArrowPlacement, base, dir, edgePlacement(), facesPlacement(), MainWindow::attachArrowCompleters(), MainWindow::patternCentre(), MainWindow::pickedFaces() (+6 more)

### Community 55 - "CommandSession"
Cohesion: 0.12
Nodes (9): CommandSession, inputs_, CommandRegistry::find(), CommandRegistry::run(), OwnedCommand, owned, OwningCommandSession, Session::begin() (+1 more)

### Community 56 - "Theme.cpp"
Cohesion: 0.21
Nodes (6): setIconTheme(), darkColors(), darkPalette(), darkStyleSheet(), lightColors(), lightStyleSheet()

### Community 57 - ".rebuild"
Cohesion: 0.12
Nodes (5): hiddenColour(), qc(), rgb(), sharpEdges(), wireColour()

### Community 58 - "Entity"
Cohesion: 0.10
Nodes (13): QObject, Entity, a, b, center, construction, fit, handles (+5 more)

### Community 59 - "xdrive.py"
Cohesion: 0.28
Nodes (15): button(), canvas(), click(), drag(), flush(), geometry(), key(), keycode() (+7 more)

### Community 62 - "Session"
Cohesion: 0.08
Nodes (7): PythonHost::PythonHost(), Session, commands_, doc_, listeners_, nextListener_, path_

### Community 63 - "ParametersDialog"
Cohesion: 0.12
Nodes (12): ParametersDialog, building_, error_, filter_, listener_, public, rebuildPending_, tree_ (+4 more)

### Community 64 - "BodyFrame"
Cohesion: 0.11
Nodes (29): boundingBox(), completeEdgeReferences(), completeFaceReferences(), decode(), decodeFaces(), edgeReference(), EdgeSig, full (+21 more)

### Community 65 - "CommandRegistry"
Cohesion: 0.12
Nodes (4): CommandRegistry, cmds_, CommandRegistry::add(), TEST()

### Community 66 - "Feature"
Cohesion: 0.12
Nodes (16): Feature, commandId, error, id, inputs, name, parameterNames, rolledBack (+8 more)

### Community 67 - "BodyFrame"
Cohesion: 0.14
Nodes (13): BodyFrame, diag, dx, dy, dz, x0, y0, z0 (+5 more)

### Community 68 - "Theme"
Cohesion: 0.20
Nodes (5): MainWindow::showPreferences(), Theme, colors_, public, styled_

### Community 69 - "Joint"
Cohesion: 0.16
Nodes (6): Coil, def_, Joint, def_, Sweep, def_

### Community 71 - "ParametersDialog.cpp"
Cohesion: 0.13
Nodes (4): number(), ParametersDialog::ParametersDialog(), qs(), withUnit()

### Community 72 - "TEST"
Cohesion: 0.09
Nodes (3): param(), TEST(), tmp()

### Community 73 - "curve"
Cohesion: 0.31
Nodes (10): curve(), curves(), entityCurves(), interiorPoint(), profileAt(), profiles(), splineHandles(), textShape() (+2 more)

### Community 74 - "Column"
Cohesion: 0.25
Nodes (8): Column, kComment, kExpression, kName, kParameter, kStar, kUnit, kValue

### Community 75 - "InputType"
Cohesion: 0.12
Nodes (17): InputType, Axis, Bodies, Body, Bool, Choice, Edges, Faces (+9 more)

### Community 76 - "Vec3"
Cohesion: 0.19
Nodes (19): SurfacePoint, normal, point, Vec3, edgeMidpoint(), edgesNear(), frame(), makeBox() (+11 more)

### Community 79 - "Command.cpp"
Cohesion: 0.22
Nodes (11): expressionKey(), checkInputValue(), CommandContext::evaluateExpression(), CommandDef::input(), CommandSession::applyInTransaction(), CommandSession::cancel(), CommandSession::execute(), CommandSession::preview() (+3 more)

### Community 80 - "SketchDisplay"
Cohesion: 0.12
Nodes (11): ProfileObject, index, sketch, SketchDisplay, construction, curves, fixedCurves, frame (+3 more)

### Community 81 - "Command"
Cohesion: 0.12
Nodes (21): Adding a tool, Command, getReal(), CircularPattern, def_, CreateSketch, def_, evaluateDimensions() (+13 more)

### Community 82 - "Measurement"
Cohesion: 0.13
Nodes (14): Kind, Angle, Area, Length, Volume, Measurement, from, hasLine (+6 more)

### Community 83 - "SketchCurves.cpp"
Cohesion: 0.13
Nodes (18): crossings(), crossingsOf(), Curve2d, curve2d(), periodic, t0, t1, endIsFree() (+10 more)

### Community 84 - "MarkingMenu.cpp"
Cohesion: 0.07
Nodes (21): UiCommand, enabled, icon, id, name, panel, run, shortcut (+13 more)

### Community 85 - "Level"
Cohesion: 0.12
Nodes (13): debug(), error(), info(), Level, Debug, Error, Info, Warning (+5 more)

### Community 86 - "README.md"
Cohesion: 0.08
Nodes (20): Build, Conventions, Development, Tests, Include 3D Geometry, Known gaps, Sketch text, Splines and conics (+12 more)

### Community 87 - "string"
Cohesion: 0.06
Nodes (45): ConstructionPlane, name, spec, SketchRecord, data, name, offset, plane (+37 more)

### Community 89 - "rect"
Cohesion: 0.10
Nodes (8): SelectionBox, crossing, Viewport::placeArrowBoxes(), Viewport::lookAt(), Viewport::planePoint(), Viewport::toWidget(), height, rect()

### Community 90 - "cachedProfiles"
Cohesion: 0.20
Nodes (3): MainWindow::updateDragArrow(), cachedProfiles(), keyOf()

### Community 91 - "EntityType"
Cohesion: 0.29
Nodes (7): EntityType, Arc, Circle, Ellipse, Line, Spline, isRound()

### Community 92 - "FormatInfo"
Cohesion: 0.40
Nodes (5): FormatInfo, canImport, extensions, format, name

### Community 93 - "Known differences still to build"
Cohesion: 0.15
Nodes (12): Data and files, Findings from the videos, Fusion study list, Interface, Known differences still to build, Navigation and display, Selection and the canvas, Sketch (+4 more)

### Community 94 - "QDialog"
Cohesion: 0.14
Nodes (6): QDialog, MainWindow::exportDesign(), MainWindow::measurePick(), MainWindow::openAnalysis(), MainWindow::openMeasure(), toolWindow()

### Community 95 - "ReplayStep"
Cohesion: 0.05
Nodes (40): Body, display, name, shape, Component, bodies, name, ConstructionAxis (+32 more)

### Community 96 - "ExpressionSpinBox"
Cohesion: 0.16
Nodes (4): ExpressionSpinBox, eval_, expression_, shown_

### Community 97 - "Tool"
Cohesion: 0.16
Nodes (6): SketchEditor::SketchEditor(), edges, Tool, op, shape, target

### Community 98 - "FakeDoc"
Cohesion: 0.17
Nodes (6): FakeDoc, aborts, commits, items, open, snapshot

### Community 99 - "QMouseEvent"
Cohesion: 0.16
Nodes (6): MarkingMenu::mouseMoveEvent(), MarkingMenu::mouseReleaseEvent(), QKeyEvent, QMouseEvent, ViewInteractor, Viewport::setInteractor()

### Community 102 - "sstream"
Cohesion: 0.17
Nodes (5): doc_(), Document::Document(), Document::ocafBytes(), ocafApplication(), Document::load()

### Community 103 - "TsrModule.cpp"
Cohesion: 0.23
Nodes (4): bindTsr(), fromPy(), toPy(), typeName()

### Community 104 - "openWallBand"
Cohesion: 0.25
Nodes (9): BoundingBox, max, min, WallSide, Center, Side1, Side2, offsetOpenWire() (+1 more)

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
Cohesion: 0.18
Nodes (16): Section, Circular, Square, Triangular, TopologyCounts, edges, faces, shells (+8 more)

### Community 111 - "UserParameter"
Cohesion: 0.33
Nodes (6): UserParameter, comment, expression, name, unit, value

### Community 112 - "Axis"
Cohesion: 0.50
Nodes (4): Axis, X, Y, Z

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
Cohesion: 0.14
Nodes (11): Result, error, ok, output, captured(), PythonHost::exec(), PythonHost::runScript(), Case (+3 more)

### Community 118 - "ThreadInfo"
Cohesion: 0.50
Nodes (4): ThreadInfo, diameter, internal, pitch

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
Cohesion: 0.11
Nodes (9): ccwContains(), circumcircle(), ext(), fixedColor(), freeColor(), lineEntity(), qc(), rgb() (+1 more)

### Community 129 - "Rect"
Cohesion: 0.50
Nodes (4): Session::notifyChanged(), Rect, l, p

### Community 131 - "DocCommands.cpp"
Cohesion: 0.11
Nodes (19): axisOf(), CopyFn, differenceOrNull(), Loft, def_, NewComponent, def_, openChains() (+11 more)

### Community 134 - "MarkingMenu"
Cohesion: 0.40
Nodes (3): MarkingMenu, enabled, public

### Community 135 - "Dimension"
Cohesion: 0.50
Nodes (4): Dimension, Angle, Length, Unitless

### Community 141 - "Point"
Cohesion: 0.52
Nodes (6): Point, x, y, z, customPlaneSpec(), toDxf()

### Community 142 - "SplineHandle"
Cohesion: 0.29
Nodes (7): SplineHandle, arm, index, tx, ty, x, y

## Knowledge Gaps
- **748 isolated node(s):** `ok`, `output`, `error`, `isReal`, `real` (+743 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 1413 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **25 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `optional` connect `optional` to `Viewport`, `DocCommands.cpp`, `MainWindow`, `Kernel.cpp`, `Io.cpp`, `Unit`, `ViewportSketch.cpp`, `ViewportArrow.cpp`, `Constraint`, `CommandError`, `CommandDialog.cpp`, `SketchEditor.cpp`, `AnalysisSettings`, `ParamSet`, `CommandDef`, `ViewportAnalysis.cpp`, `Entity`, `Session`, `Feature`, `Vec3`, `QString`, `SketchCurves.cpp`, `string`, `rect`, `ReplayStep`, `ExpressionSpinBox`, `Joints`?**
  _High betweenness centrality (0.103) - this node is a cross-community bridge._
- **What connects `ok`, `output`, `error` to the rest of the system?**
  _748 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Viewport` be split into smaller, more focused modules?**
  _Cohesion score 0.01664516129032258 - nodes in this community are weakly interconnected._
- **Why does `Viewport` connect `Viewport` to `rect`, `ViewportArrow.cpp`, `QMouseEvent`, `MainWindow`, `src/main.cpp`, `Viewport.cpp`, `optional`, `AnalysisSettings`, `AnalysisSettings`, `SketchDisplay`, `SketchCurves.cpp`, `.toPixels`, `.setSelectionFilter`, `ViewportAnalysis.cpp`, `ViewportSketch.cpp`, `SketchPalette`, `QDialog`, `.rebuild`?**
  _High betweenness centrality (0.093) - this node is a cross-community bridge._
- **Should `Icons.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.057777777777777775 - nodes in this community are weakly interconnected._
- **Why does `MainWindow` connect `MainWindow` to `ParameterCompleter`, `MainWindow::MainWindow`, `cachedProfiles`, `SectionState`, `optional`, `smoke`, `.openMarkingMenu`, `MainWindowSketch.cpp`, `MainWindowTools.cpp`, `MarkingMenu.cpp`, `Unit`, `MainWindow.cpp`, `Session`, `SketchPalette`, `QDialog`, `ParametersDialog`?**
  _High betweenness centrality (0.086) - this node is a cross-community bridge._
- **Should `tsr` be split into smaller, more focused modules?**
  _Cohesion score 0.04522144522144522 - nodes in this community are weakly interconnected._