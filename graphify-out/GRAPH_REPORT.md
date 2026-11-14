# Graph Report - tessera  (2026-11-13)

## Corpus Check
- 381 files · ~241,101 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 56 file(s) not represented in the graph (top: .drive 48, (none) 5, .cmake 1)

## Summary
- 3584 nodes · 9087 edges · 140 communities (114 shown, 26 thin omitted)
- Extraction: 85% EXTRACTED · 15% INFERRED · 0% AMBIGUOUS · INFERRED: 1383 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `a210e559`
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
- Unit
- MainWindowTools.cpp
- Unit
- Document
- MainWindow.cpp
- TEST
- Sketch.cpp
- ViewportSketch.cpp
- SketchPalette
- Snap
- Inputs
- string
- Colors
- KernelError
- SketchOps.cpp
- QMouseEvent
- ParameterCompleter
- Constraint
- trimCurve
- .applyPreSelection
- solve
- Kind
- CommandDialog::CommandDialog
- ConstraintType
- AdskModule.cpp
- Pick
- SketchEditor.cpp
- rect
- Zip.cpp
- AnalysisSettings
- .rebuild
- ModelParameter
- MainWindowSketch.cpp
- InputDef
- sketchFor
- .toPixels
- MainWindowArrow.cpp
- CommandSession
- Theme.cpp
- Feature
- Entity
- xdrive.py
- Session
- ViewportArrow.cpp
- BodyFrame
- CommandRegistry
- MainWindow::MainWindow
- openWallBand
- Theme
- string
- ParametersDialog.cpp
- TEST
- FeatureEffect
- Column
- InputType
- Vec3
- QString
- Command.cpp
- SketchDisplay
- CommandDef
- Measurement
- SketchCurves.cpp
- MarkingMenu.cpp
- Level
- README.md
- string
- test_feature_pattern.py
- .initializeGL
- .add
- EntityType
- FileFormat
- Known differences still to build
- Viewport::setDragArrow
- ReplayStep
- QObject
- FakeDoc
- isInputVisible
- src/main.cpp
- .redrawAll
- sstream
- cachedProfiles
- QTimer
- Joints
- SectionState
- Display
- main
- PlaneEdges
- openWallBand
- Viewport.h
- Session::addListener
- Axis
- uninstall.sh
- install.sh
- TestFramework.h
- BooleanOp
- ThreadInfo
- SketchRecord
- test_incremental_replay.py
- Placement
- ChainSegment
- curve
- bindAdsk
- smoke
- .mouseMove
- Rect
- ChamferType
- DocCommands.cpp
- Placement::apply
- LAB_NOTES.md
- MarkingMenu
- build.sh
- live-test.sh
- Point
- SplineHandle

## God Nodes (most connected - your core abstractions)
1. `Viewport` - 251 edges
2. `SketchEditor` - 185 edges
3. `MainWindow` - 175 edges
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

## Communities (140 total, 26 thin omitted)

### Community 0 - "Viewport"
Cohesion: 0.02
Nodes (67): view_, QLineEdit, Viewport, analysis_, analysisObjects_, appliedGridStep_, arrowBoxes_, arrowDragging_ (+59 more)

### Community 1 - "Icons.cpp"
Cohesion: 0.06
Nodes (117): arc3Icon(), arcIcon(), arcTangentIcon(), arrow(), axisIcon(), box(), breakIcon(), centerRectIcon() (+109 more)

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
Nodes (14): Document, effects_, lastReplayed_, lastReused_, modified_, pendingTools_, registry_, replaying_ (+6 more)

### Community 8 - "Viewport.cpp"
Cohesion: 0.05
Nodes (4): glide(), QKeyEvent, QtFrameBuffer, Viewport::frontEdgeOwner()

### Community 9 - "SketchEditor"
Cohesion: 0.03
Nodes (50): HandleHit, back, index, spline, SketchEditor, arcDrag_, arcDragMoved_, arcEndsChain_ (+42 more)

### Community 10 - "Document::recompute"
Cohesion: 0.20
Nodes (6): Document::openTransaction(), Document::recompute(), Document::recordFeature(), Document::replayKey(), Document::setFeatureInputs(), toJson()

### Community 11 - "optional"
Cohesion: 0.10
Nodes (7): optional, isEmpty(), Value, CommandRegistry::all(), Document, fail(), Failure

### Community 12 - "Kernel.cpp"
Cohesion: 0.04
Nodes (6): dot(), faceScore(), isoCoarsePitch(), score(), topologyCounts(), vec()

### Community 13 - "AnalysisSettings"
Cohesion: 0.15
Nodes (13): AnalysisKind, CurvatureMap, Draft, None, Zebra, AnalysisSettings, curvatureScale, draftAngle (+5 more)

### Community 14 - "Kind"
Cohesion: 0.07
Nodes (26): EdgeFeature, def_, kind_, FaceFeature, def_, kind_, Kind, Angle (+18 more)

### Community 15 - ".openMarkingMenu"
Cohesion: 0.09
Nodes (4): MainWindow::beginSketch(), MainWindow::buildSketchTab(), MainWindow::enterSketchMode(), MainWindow::buildUiCommands()

### Community 16 - "CommandDialog"
Cohesion: 0.04
Nodes (31): CommandDialog, bodiesId_, bodiesLabel_, bodyInput_, buttons_, cmd_, conditional_, edgesId_ (+23 more)

### Community 17 - "Io.cpp"
Cohesion: 0.09
Nodes (19): MainWindow::print3d(), NamedShape, compoundOf(), exportShapes(), fmt(), formatForPath(), fromBrep(), importShape() (+11 more)

### Community 18 - "Unit"
Cohesion: 0.09
Nodes (32): ExpressionEnv, lengthUnit, lookup, ExpressionError, Quantity, angle, length, value (+24 more)

### Community 19 - "MainWindowTools.cpp"
Cohesion: 0.06
Nodes (13): QDialog, MainWindow::chooseUnits(), MainWindow::exportDesign(), MainWindow::insertFile(), MainWindow::measurePick(), MainWindow::openMeasure(), MainWindow::sectionFrame(), MainWindow::sectionPlane() (+5 more)

### Community 20 - "Unit"
Cohesion: 0.10
Nodes (27): MainWindow::checkInterference(), MainWindow::driveJoints(), MainWindow::formatLength(), MainWindow::gridSettings(), MainWindow::lengthUnit(), MainWindow::openAnalysis(), MainWindow::openSection(), MainWindow::updateMeasure() (+19 more)

### Community 21 - "Document"
Cohesion: 0.20
Nodes (7): ConstructAxisPoint, def_, kind_, jointOrigin(), JointPick, frame, revolveAxis()

### Community 22 - "MainWindow.cpp"
Cohesion: 0.16
Nodes (3): commandIcon(), qs(), MainWindow::applySection()

### Community 23 - "TEST"
Cohesion: 0.08
Nodes (7): Sketch, constraints, entities, points, texts, Sketch::addConic(), TEST()

### Community 24 - "Sketch.cpp"
Cohesion: 0.07
Nodes (21): SketchError, SplineKind, Conic, Control, Fit, entityTypeName(), isDimension(), Sketch::addCircle() (+13 more)

### Community 25 - "ViewportSketch.cpp"
Cohesion: 0.07
Nodes (6): faceStyle(), lineStyle(), rgb(), Viewport::lookAt(), Viewport::planePoint(), Viewport::toWidget()

### Community 26 - "SketchPalette"
Cohesion: 0.06
Nodes (26): flatButton(), QCheckBox, QLabel, QToolButton, QWidget, SketchEditor, SketchPalette, body_ (+18 more)

### Community 27 - "Snap"
Cohesion: 0.11
Nodes (18): Snap, alignX, alignY, bodyArc, bodySegment, entity, fromX, fromY (+10 more)

### Community 28 - "Inputs"
Cohesion: 0.07
Nodes (19): CommandContext, CommandError, Inputs, CommandSession::CommandSession(), getBool(), getInt(), getReal(), applyOperation() (+11 more)

### Community 29 - "string"
Cohesion: 0.06
Nodes (35): DocumentError, bodyNumber(), checkViewName(), Document::abortTransaction(), Document::addBody(), Document::addNamedView(), Document::addUserParameter(), Document::axisFrame() (+27 more)

### Community 30 - "Colors"
Cohesion: 0.07
Nodes (28): Colors, base, border, cubeBox, cubeText, errorBackground, grid, gridMajor (+20 more)

### Community 31 - "KernelError"
Cohesion: 0.23
Nodes (30): KernelError, asSolid(), boolean(), chamfer(), chamferEx(), deleteFaces(), draft(), extrude() (+22 more)

### Community 32 - "SketchOps.cpp"
Cohesion: 0.23
Nodes (26): at(), chainOf(), chamferCorner(), circularPattern(), copyEntities(), cornerAt(), cross(), dot() (+18 more)

### Community 33 - "QMouseEvent"
Cohesion: 0.14
Nodes (8): MarkingMenu::mouseMoveEvent(), QMouseEvent, ViewInteractor, Viewport::arrowMouseMove(), Viewport::arrowMousePress(), Viewport::arrowMouseRelease(), Viewport::dragArrowForTest(), Viewport::rebuildArrows()

### Community 34 - "ParameterCompleter"
Cohesion: 0.12
Nodes (8): ParameterCompleter, completer_, edit_, names_, ParameterCompleter::ParameterCompleter(), public, QCompleter, QLineEdit

### Community 35 - "Constraint"
Cohesion: 0.08
Nodes (20): Constraint, driven, entities, expression, hasLabel, labelX, labelY, name (+12 more)

### Community 36 - "trimCurve"
Cohesion: 0.21
Nodes (8): Curve2d, periodic, t0, t1, makePiece(), newPoint(), paramOf(), trimCurve()

### Community 38 - "solve"
Cohesion: 0.18
Nodes (13): set, addConstraintChecked(), Layout, n, px, py, rad, makeLayout() (+5 more)

### Community 39 - "Kind"
Cohesion: 0.09
Nodes (21): HudField, edit, editing, kind, locked, value, Kind, Angle (+13 more)

### Community 41 - "ConstraintType"
Cohesion: 0.08
Nodes (25): ConstraintType, Angle, Coincident, Collinear, Concentric, Diameter, Distance, Equal (+17 more)

### Community 42 - "AdskModule.cpp"
Cohesion: 0.12
Nodes (13): Application, BRepBodies, Component, Design, Product, raiseIfError(), UserParameter, name (+5 more)

### Community 43 - "Pick"
Cohesion: 0.13
Nodes (14): Pick, bodyArc, bodyPoint, bodySegment, hit, midpointOf, onEntity, onXAxis (+6 more)

### Community 44 - "SketchEditor.cpp"
Cohesion: 0.12
Nodes (5): angleInArc(), ccwContains(), circumcircle(), lineEntity(), segDistance()

### Community 45 - "rect"
Cohesion: 0.28
Nodes (3): SelectionBox, crossing, rect()

### Community 46 - "Zip.cpp"
Cohesion: 0.11
Nodes (14): Entry, data, name, ZipError, crc32(), get16(), get32(), put16() (+6 more)

### Community 47 - "AnalysisSettings"
Cohesion: 0.10
Nodes (16): DragArrow, base, dir, radius, ref, ring, value, PendingLook (+8 more)

### Community 48 - ".rebuild"
Cohesion: 0.13
Nodes (5): hiddenColour(), qc(), rgb(), sharpEdges(), wireColour()

### Community 49 - "ModelParameter"
Cohesion: 0.13
Nodes (13): ModelParameter, angle, expression, input, label, name, owner, unit (+5 more)

### Community 50 - "MainWindowSketch.cpp"
Cohesion: 0.05
Nodes (24): MainWindow::cancelSketch(), MainWindow::editSketch(), MainWindow::finishSketch(), MainWindow::onProfileClicked(), MainWindow::originalShape(), MainWindow::sketchPalette(), MainWindow::sketchVisible(), MainWindow::startSketch() (+16 more)

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
Cohesion: 0.12
Nodes (9): CommandSession, inputs_, CommandRegistry::find(), CommandRegistry::run(), OwnedCommand, owned, OwningCommandSession, Session::begin() (+1 more)

### Community 56 - "Theme.cpp"
Cohesion: 0.19
Nodes (6): setIconTheme(), darkColors(), darkPalette(), darkStyleSheet(), lightColors(), lightStyleSheet()

### Community 57 - "Feature"
Cohesion: 0.12
Nodes (16): Feature, commandId, error, id, inputs, name, parameterNames, rolledBack (+8 more)

### Community 58 - "Entity"
Cohesion: 0.08
Nodes (20): Entity, a, b, center, construction, fit, handles, included (+12 more)

### Community 59 - "xdrive.py"
Cohesion: 0.28
Nodes (15): button(), canvas(), click(), drag(), flush(), geometry(), key(), keycode() (+7 more)

### Community 62 - "Session"
Cohesion: 0.08
Nodes (7): PythonHost::PythonHost(), Session, commands_, doc_, listeners_, nextListener_, path_

### Community 63 - "ViewportArrow.cpp"
Cohesion: 0.07
Nodes (12): packed(), ramp(), shade(), Viewport::buildAnalysis(), Viewport::setCurvatureComb(), rgb(), segmentDistance(), Viewport::arrowAt() (+4 more)

### Community 64 - "BodyFrame"
Cohesion: 0.08
Nodes (36): BodyFrame, diag, dx, dy, dz, x0, y0, z0 (+28 more)

### Community 65 - "CommandRegistry"
Cohesion: 0.10
Nodes (7): CommandRegistry, cmds_, CommandRegistry::add(), EditFeature, def_, featureId_, TEST()

### Community 66 - "MainWindow::MainWindow"
Cohesion: 0.13
Nodes (4): PythonHost, MainWindow::MainWindow(), MainWindow::exitSketchMode(), MainWindow::showPreferences()

### Community 67 - "openWallBand"
Cohesion: 0.14
Nodes (13): BoundingBox, max, min, WallSide, Center, Side1, Side2, faceNormalAt() (+5 more)

### Community 68 - "Theme"
Cohesion: 0.22
Nodes (4): Theme, colors_, public, styled_

### Community 69 - "string"
Cohesion: 0.14
Nodes (9): AddUserParameter, def_, isIdentifier(), NewComponent, def_, sectionOf(), Sweep, def_ (+1 more)

### Community 71 - "ParametersDialog.cpp"
Cohesion: 0.08
Nodes (16): number(), ParametersDialog, building_, error_, filter_, listener_, ParametersDialog::ParametersDialog(), public (+8 more)

### Community 72 - "TEST"
Cohesion: 0.09
Nodes (3): param(), TEST(), tmp()

### Community 73 - "FeatureEffect"
Cohesion: 0.14
Nodes (9): FeatureEffect, bodies, tools, Document::effectOf(), Document::evaluate(), Document::nameFeatureParameters(), Document::planeFrame(), joinNames() (+1 more)

### Community 74 - "Column"
Cohesion: 0.25
Nodes (8): Column, kComment, kExpression, kName, kParameter, kStar, kUnit, kValue

### Community 75 - "InputType"
Cohesion: 0.08
Nodes (21): bindTsr(), fromPy(), toPy(), typeName(), InputType, Axis, Bodies, Body (+13 more)

### Community 76 - "Vec3"
Cohesion: 0.18
Nodes (20): SurfacePoint, normal, point, Vec3, boundingBox(), edgeMidpoint(), edgesNear(), frame() (+12 more)

### Community 77 - "QString"
Cohesion: 0.11
Nodes (5): ExpressionSpinBox, eval_, expression_, shown_, formatNumber()

### Community 79 - "Command.cpp"
Cohesion: 0.14
Nodes (17): expressionKey(), Dimension, Angle, Length, Unitless, checkInputValue(), CommandContext::evaluateExpression(), CommandDef::input() (+9 more)

### Community 80 - "SketchDisplay"
Cohesion: 0.12
Nodes (11): ProfileObject, index, sketch, SketchDisplay, construction, curves, fixedCurves, frame (+3 more)

### Community 81 - "CommandDef"
Cohesion: 0.03
Nodes (56): Architecture, How a command works, The document, Units, Adding a tool, Command, CommandDef, feature (+48 more)

### Community 82 - "Measurement"
Cohesion: 0.13
Nodes (14): Kind, Angle, Area, Length, Volume, Measurement, from, hasLine (+6 more)

### Community 83 - "SketchCurves.cpp"
Cohesion: 0.18
Nodes (8): crossings(), crossingsOf(), curve2d(), endIsFree(), extendCurve(), finishExtend(), includeEdges(), setSplineHandle()

### Community 84 - "MarkingMenu.cpp"
Cohesion: 0.13
Nodes (12): UiCommand, enabled, icon, id, name, panel, run, shortcut (+4 more)

### Community 85 - "Level"
Cohesion: 0.16
Nodes (13): debug(), error(), info(), Level, Debug, Error, Info, Warning (+5 more)

### Community 86 - "README.md"
Cohesion: 0.08
Nodes (20): Build, Conventions, Development, Tests, Include 3D Geometry, Known gaps, Sketch text, Splines and conics (+12 more)

### Community 87 - "string"
Cohesion: 0.10
Nodes (37): ConstructionPlane, name, spec, ParamSet, env, text, Document::axes(), Document::bodies() (+29 more)

### Community 91 - "EntityType"
Cohesion: 0.29
Nodes (7): EntityType, Arc, Circle, Ellipse, Line, Spline, isRound()

### Community 92 - "FileFormat"
Cohesion: 0.17
Nodes (12): FileFormat, Brep, Iges, Obj, Step, Stl, ThreeMF, FormatInfo (+4 more)

### Community 93 - "Known differences still to build"
Cohesion: 0.15
Nodes (12): Data and files, Findings from the videos, Fusion study list, Interface, Known differences still to build, Navigation and display, Selection and the canvas, Sketch (+4 more)

### Community 94 - "Viewport::setDragArrow"
Cohesion: 0.18
Nodes (4): Viewport::DragArrow::handle(), Viewport::emitArrow(), Viewport::setDragArrow(), Viewport::setDragRing()

### Community 95 - "ReplayStep"
Cohesion: 0.04
Nodes (44): Body, display, name, shape, Component, bodies, name, ConstructionAxis (+36 more)

### Community 97 - "QObject"
Cohesion: 0.11
Nodes (7): QObject, Hit, index, kind, SketchEditor::SketchEditor(), edges, type

### Community 98 - "FakeDoc"
Cohesion: 0.17
Nodes (6): FakeDoc, aborts, commits, items, open, snapshot

### Community 101 - ".redrawAll"
Cohesion: 0.12
Nodes (9): keys(), NavPreset, Fusion, SolidWorks, Tinkercad, Viewport::Viewport(), Viewport::clearDragArrow(), Viewport::clearSecondArrow() (+1 more)

### Community 102 - "sstream"
Cohesion: 0.17
Nodes (5): doc_(), Document::Document(), Document::ocafBytes(), ocafApplication(), Document::load()

### Community 106 - "SectionState"
Cohesion: 0.25
Nodes (7): SectionState, active, angle, flip, offset, plane, visible

### Community 107 - "Display"
Cohesion: 0.25
Nodes (7): Display, constraints, construction, dimensions, points, profiles, projected

### Community 108 - "main"
Cohesion: 0.36
Nodes (4): listCommands(), main(), usage(), main()

### Community 109 - "PlaneEdges"
Cohesion: 0.15
Nodes (5): PlaneEdges, arcs, curves, segments, vertices

### Community 110 - "openWallBand"
Cohesion: 0.15
Nodes (17): Section, Circular, Square, Triangular, TopologyCounts, edges, faces, shells (+9 more)

### Community 111 - "Viewport.h"
Cohesion: 0.11
Nodes (6): QLabel, Profile, area, face, x, y

### Community 113 - "Axis"
Cohesion: 0.50
Nodes (4): Axis, X, Y, Z

### Community 114 - "uninstall.sh"
Cohesion: 0.52
Nodes (6): die(), manifest_for(), refresh(), uninstall.sh script, step(), usage()

### Community 115 - "install.sh"
Cohesion: 0.60
Nodes (5): die(), refresh(), install.sh script, step(), usage()

### Community 116 - "TestFramework.h"
Cohesion: 0.16
Nodes (11): Result, error, ok, output, captured(), PythonHost::exec(), PythonHost::runScript(), Case (+3 more)

### Community 118 - "BooleanOp"
Cohesion: 0.50
Nodes (4): BooleanOp, Cut, Intersect, Join

### Community 119 - "ThreadInfo"
Cohesion: 0.50
Nodes (4): ThreadInfo, diameter, internal, pitch

### Community 121 - "SketchRecord"
Cohesion: 0.25
Nodes (8): SketchRecord, data, name, offset, plane, Document::setSketch(), Document::sketch(), Document::sketches()

### Community 123 - "Placement"
Cohesion: 0.25
Nodes (7): Placement, angle, cx, cy, dx, dy, scale

### Community 124 - "ChainSegment"
Cohesion: 0.67
Nodes (3): ChainSegment, entity, forward

### Community 125 - "curve"
Cohesion: 0.31
Nodes (10): curve(), curves(), entityCurves(), interiorPoint(), profileAt(), profiles(), splineHandles(), textShape() (+2 more)

### Community 126 - "bindAdsk"
Cohesion: 0.29
Nodes (3): bindAdsk(), BRepBody, index

### Community 127 - "smoke"
Cohesion: 0.33
Nodes (6): smoke(), key, MassProperties, area, centerOfMass, volume

### Community 128 - ".mouseMove"
Cohesion: 0.15
Nodes (7): ext(), fixedColor(), freeColor(), qc(), rgb(), wire(), Sketch::addLine()

### Community 129 - "Rect"
Cohesion: 0.50
Nodes (4): Session::notifyChanged(), Rect, l, p

### Community 130 - "ChamferType"
Cohesion: 0.67
Nodes (3): ChamferType, DistanceAngle, TwoDistances

### Community 131 - "DocCommands.cpp"
Cohesion: 0.11
Nodes (28): axisOf(), bodyCentre(), checkPattern(), CopyFn, differenceOrNull(), evaluateDimensions(), Loft, def_ (+20 more)

### Community 134 - "MarkingMenu"
Cohesion: 0.40
Nodes (3): MarkingMenu, enabled, public

### Community 141 - "Point"
Cohesion: 0.31
Nodes (8): Point, x, y, z, flattened(), offsetCurve(), customPlaneSpec(), planeFrame()

### Community 142 - "SplineHandle"
Cohesion: 0.29
Nodes (7): SplineHandle, arm, index, tx, ty, x, y

## Knowledge Gaps
- **741 isolated node(s):** `ok`, `output`, `error`, `isReal`, `real` (+736 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 1403 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **26 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `SketchEditor` connect `SketchEditor` to `.mouseMove`, `QObject`, `Viewport`, `Constraint`, `QMouseEvent`, `.solveAndShow`, `Kind`, `Display`, `optional`, `PlaneEdges`, `Pick`, `Viewport.h`, `SketchEditor.cpp`, `Unit`, `Entity`, `Snap`, `Session`, `ReplayStep`?**
  _High betweenness centrality (0.110) - this node is a cross-community bridge._
- **What connects `ok`, `output`, `error` to the rest of the system?**
  _741 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Viewport` be split into smaller, more focused modules?**
  _Cohesion score 0.01664516129032258 - nodes in this community are weakly interconnected._
- **Why does `Viewport` connect `Viewport` to `MainWindow`, `Viewport.cpp`, `optional`, `AnalysisSettings`, `Unit`, `QMouseEvent`, `trimCurve`, `rect`, `AnalysisSettings`, `.rebuild`, `.toPixels`, `ViewportArrow.cpp`, `SketchDisplay`, `.initializeGL`, `Viewport::setDragArrow`, `src/main.cpp`, `.redrawAll`, `QTimer`, `Viewport.h`, `.setSelectionFilter`?**
  _High betweenness centrality (0.098) - this node is a cross-community bridge._
- **Should `Icons.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.055456171735241505 - nodes in this community are weakly interconnected._
- **Why does `optional` connect `optional` to `Viewport`, `DocCommands.cpp`, `MainWindow`, `Document::recompute`, `Kernel.cpp`, `Io.cpp`, `Unit`, `Unit`, `ViewportSketch.cpp`, `SketchOps.cpp`, `Constraint`, `SketchEditor.cpp`, `AnalysisSettings`, `InputDef`, `sketchFor`, `MainWindowArrow.cpp`, `Feature`, `Entity`, `Session`, `ViewportArrow.cpp`, `.updateProfilesLabel`, `Vec3`, `QString`, `SketchCurves.cpp`, `string`, `ReplayStep`, `Viewport.h`, `SketchRecord`?**
  _High betweenness centrality (0.096) - this node is a cross-community bridge._
- **Should `tsr` be split into smaller, more focused modules?**
  _Cohesion score 0.04522144522144522 - nodes in this community are weakly interconnected._