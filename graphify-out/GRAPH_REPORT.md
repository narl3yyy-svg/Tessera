# Graph Report - tessera  (2026-11-13)

## Corpus Check
- 386 files · ~255,620 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 56 file(s) not represented in the graph (top: .drive 48, (none) 5, .cmake 1)

## Summary
- 3712 nodes · 9514 edges · 138 communities (111 shown, 27 thin omitted)
- Extraction: 85% EXTRACTED · 15% INFERRED · 0% AMBIGUOUS · INFERRED: 1463 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `d6d02a8f`
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
- Architecture
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
- Text
- Zip.cpp
- AnalysisSettings
- Sketch.cpp
- ParamSet
- MainWindowSketch.cpp
- InputDef
- HoleSize
- .toPixels
- ViewportAnalysis.cpp
- Document::recompute
- MarkingMenu.cpp
- Viewport.h
- Entity
- xdrive.py
- Session
- Theme.cpp
- BodyFrame
- CommandRegistry
- Sweep
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
- dimensionOf
- ExpressionSpinBox
- SketchDisplay
- Command
- Measurement
- SketchCurves.cpp
- Unit
- Level
- README.md
- Document.cpp
- test_feature_pattern.py
- rect
- MainWindow::MainWindow
- FileFormat
- Known differences still to build
- TEST
- ReplayStep
- SketchCurves.cpp
- Feature
- FakeDoc
- ParameterCompleter.cpp
- Expression.cpp
- .add
- sstream
- Sketch.h
- BoundingBox
- Joints
- SectionState
- Display
- main
- Kernel.h
- TopologyCounts
- Column
- NavPreset
- uninstall.sh
- install.sh
- TestFramework.h
- .rebuild
- MarkingMenu
- Placement::apply
- bindAdsk
- test_incremental_replay.py
- Placement
- ChainSegment
- AddUserParameter
- TEST
- TEST
- Joint
- Value.h
- Curve2d
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

## Communities (138 total, 27 thin omitted)

### Community 0 - "Viewport"
Cohesion: 0.02
Nodes (69): view_, QLineEdit, Viewport, analysis_, analysisObjects_, appliedGridStep_, arrowBoxes_, arrowDragging_ (+61 more)

### Community 1 - "Icons.cpp"
Cohesion: 0.05
Nodes (124): accessibilityIcon(), appearanceIcon(), arc3Icon(), arcIcon(), arcTangentIcon(), arrow(), axisIcon(), box() (+116 more)

### Community 2 - "Session.cpp"
Cohesion: 0.08
Nodes (35): CommandSession, inputs_, CommandRegistry::find(), CommandRegistry::run(), historyEdit(), OwnedCommand, owned, OwningCommandSession (+27 more)

### Community 4 - "MainWindow"
Cohesion: 0.03
Nodes (65): CommandDialog, MainWindow, active_, arrowInput_, arrowInput2_, bodiesBeforeCommand_, combEdges_, combPicking_ (+57 more)

### Community 5 - "run_oracle.py"
Cohesion: 0.08
Nodes (54): add_point(), arc_poly(), body_at(), body_list(), build_sketch(), chain(), circumcentre(), cm() (+46 more)

### Community 6 - "Unit"
Cohesion: 0.12
Nodes (18): MainWindow::checkInterference(), MainWindow::chooseUnits(), MainWindow::driveJoints(), MainWindow::editAppearance(), MainWindow::editMaterial(), MainWindow::formatLength(), MainWindow::gridSettings(), MainWindow::openAnalysis() (+10 more)

### Community 7 - "Document"
Cohesion: 0.03
Nodes (15): Document, effects_, lastReplayed_, lastReused_, modified_, pendingTools_, registry_, replaying_ (+7 more)

### Community 8 - "Viewport.cpp"
Cohesion: 0.05
Nodes (5): glide(), keys(), QKeyEvent, QtFrameBuffer, Viewport::Viewport()

### Community 9 - "SketchEditor"
Cohesion: 0.03
Nodes (50): HandleHit, back, index, spline, SketchEditor, arcDrag_, arcDragMoved_, arcEndsChain_ (+42 more)

### Community 10 - "CommandError"
Cohesion: 0.16
Nodes (16): CommandError, getBool(), getReal(), applyOperation(), bodyCentre(), bodyName(), holeSize(), body (+8 more)

### Community 11 - "optional"
Cohesion: 0.11
Nodes (5): optional, CommandRegistry::all(), Document, fail(), Failure

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
Nodes (19): MainWindow::print3d(), NamedShape, compoundOf(), exportShapes(), fmt(), formatForPath(), fromBrep(), importShape() (+11 more)

### Community 18 - "Unit"
Cohesion: 0.18
Nodes (15): Quantity, angle, length, value, describe(), isIdentChar(), Parser, ang_ (+7 more)

### Community 19 - ".setTool"
Cohesion: 0.12
Nodes (3): SketchEditor::SketchEditor(), edges, type

### Community 20 - "Known gaps"
Cohesion: 0.33
Nodes (5): Include 3D Geometry, Known gaps, Sketch text, Splines and conics, Visual styles

### Community 21 - "Document"
Cohesion: 0.18
Nodes (7): ConstructAxisPoint, def_, kind_, jointOrigin(), JointPick, frame, revolveAxis()

### Community 22 - "MainWindow.cpp"
Cohesion: 0.06
Nodes (5): commandIcon(), qs(), MainWindow::enterSketchMode(), QTimer, Viewport::selectArrowValue()

### Community 23 - "Architecture"
Cohesion: 0.40
Nodes (4): Architecture, How a command works, The document, Units

### Community 24 - "Affine"
Cohesion: 0.14
Nodes (13): Affine, a, b, d, e, Builder, byPlace_, k_ (+5 more)

### Community 25 - "ViewportSketch.cpp"
Cohesion: 0.08
Nodes (6): faceStyle(), lineStyle(), rgb(), Viewport::lookAt(), Viewport::planePoint(), Viewport::toWidget()

### Community 26 - "SketchPalette"
Cohesion: 0.03
Nodes (38): QAbstractButton, QAction, flatButton(), MainWindow::buildSketchTab(), MainWindow::applySection(), MainWindow::insertFile(), MainWindow::lookTargets(), MainWindow::measurePick() (+30 more)

### Community 28 - "Inputs"
Cohesion: 0.07
Nodes (19): CommandContext, Inputs, CommandSession::CommandSession(), getInt(), checkBody(), checkPattern(), CircularPattern, def_ (+11 more)

### Community 29 - "string"
Cohesion: 0.07
Nodes (39): SketchRecord, data, name, offset, plane, bodyNumber(), Document::addBody(), Document::bodyName() (+31 more)

### Community 30 - "Colors"
Cohesion: 0.07
Nodes (28): Colors, base, border, cubeBox, cubeText, errorBackground, grid, gridMajor (+20 more)

### Community 31 - "KernelError"
Cohesion: 0.22
Nodes (34): KernelError, asSolid(), boolean(), chamfer(), chamferEx(), curveMiddles(), deleteFaces(), draft() (+26 more)

### Community 32 - "SketchOps.cpp"
Cohesion: 0.25
Nodes (27): at(), chainOf(), chamferCorner(), circularPattern(), copyEntities(), cross(), dot(), extendLine() (+19 more)

### Community 33 - "ViewportArrow.cpp"
Cohesion: 0.05
Nodes (23): MarkingMenu::mouseMoveEvent(), QMouseEvent, ViewInteractor, Viewport::frontEdgeOwner(), rgb(), segmentDistance(), Viewport::arrowAt(), Viewport::arrowMouseMove() (+15 more)

### Community 34 - "ParameterCompleter"
Cohesion: 0.21
Nodes (8): QObject, ParameterCompleter, completer_, edit_, names_, public, QCompleter, QLineEdit

### Community 35 - "Constraint"
Cohesion: 0.09
Nodes (19): ext(), fixedColor(), freeColor(), qc(), rgb(), wire(), Constraint, driven (+11 more)

### Community 36 - "DocCommands.cpp"
Cohesion: 0.09
Nodes (30): axisOf(), CopyFn, differenceOrNull(), evaluateDimensions(), Loft, def_, makeBox(), makeCone() (+22 more)

### Community 38 - "solve"
Cohesion: 0.13
Nodes (14): set, Sketch::removeImpl(), addConstraintChecked(), Layout, n, px, py, rad (+6 more)

### Community 39 - "Snap"
Cohesion: 0.11
Nodes (18): Snap, alignX, alignY, bodyArc, bodySegment, entity, fromX, fromY (+10 more)

### Community 41 - "ConstraintType"
Cohesion: 0.08
Nodes (24): ConstraintType, Angle, Coincident, Collinear, Concentric, Diameter, Distance, Equal (+16 more)

### Community 42 - "TsrModule.cpp"
Cohesion: 0.09
Nodes (17): Application, BRepBodies, Component, Design, Product, raiseIfError(), UserParameter, name (+9 more)

### Community 43 - "Pick"
Cohesion: 0.11
Nodes (17): Hit, index, kind, Pick, bodyArc, bodyPoint, bodySegment, hit (+9 more)

### Community 44 - "SketchEditor.cpp"
Cohesion: 0.14
Nodes (5): angleInArc(), ccwContains(), circumcircle(), lineEntity(), segDistance()

### Community 45 - "Text"
Cohesion: 0.11
Nodes (17): SolveResult, dof, entityFixed, iterations, message, ok, pointFixed, residual (+9 more)

### Community 46 - "Zip.cpp"
Cohesion: 0.20
Nodes (13): Entry, data, name, ZipError, crc32(), deflateRaw(), get16(), get32() (+5 more)

### Community 47 - "AnalysisSettings"
Cohesion: 0.10
Nodes (16): DragArrow, base, dir, radius, ref, ring, value, PendingLook (+8 more)

### Community 48 - "Sketch.cpp"
Cohesion: 0.09
Nodes (18): SketchError, SplineKind, Conic, Control, Fit, entityTypeName(), isDimension(), Sketch::addSpline() (+10 more)

### Community 49 - "ParamSet"
Cohesion: 0.08
Nodes (29): ModelParameter, angle, expression, input, label, name, owner, unit (+21 more)

### Community 50 - "MainWindowSketch.cpp"
Cohesion: 0.07
Nodes (15): MainWindow::cancelSketch(), MainWindow::editSketch(), MainWindow::finishSketch(), MainWindow::onEdgeClicked(), MainWindow::onProfileClicked(), MainWindow::originalShape(), MainWindow::sketchPalette(), MainWindow::sketchVisible() (+7 more)

### Community 51 - "InputDef"
Cohesion: 0.09
Nodes (21): InputDef, choices, defaultValue, id, label, max, min, minExclusive (+13 more)

### Community 52 - "HoleSize"
Cohesion: 0.50
Nodes (4): HoleSize, modeled, pitch, radius

### Community 54 - "ViewportAnalysis.cpp"
Cohesion: 0.11
Nodes (6): packed(), ramp(), shade(), Viewport::buildAnalysis(), Viewport::setCurvatureComb(), f

### Community 55 - "Document::recompute"
Cohesion: 0.18
Nodes (6): Document::openTransaction(), Document::recompute(), Document::recordFeature(), Document::replayKey(), Document::setFeatureInputs(), toJson()

### Community 56 - "MarkingMenu.cpp"
Cohesion: 0.06
Nodes (25): UiCommand, enabled, icon, id, name, panel, run, shortcut (+17 more)

### Community 57 - "Viewport.h"
Cohesion: 0.09
Nodes (6): QLabel, Profile, area, face, x, y

### Community 58 - "Entity"
Cohesion: 0.09
Nodes (11): Entity, a, b, center, construction, fit, handles, included (+3 more)

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
Cohesion: 0.12
Nodes (4): CommandRegistry, cmds_, CommandRegistry::add(), TEST()

### Community 67 - "BodyFrame"
Cohesion: 0.15
Nodes (14): BodyFrame, diag, dx, dy, dz, x0, y0, z0 (+6 more)

### Community 68 - "Theme"
Cohesion: 0.18
Nodes (4): Theme, colors_, public, styled_

### Community 69 - "PlaneEdges"
Cohesion: 0.16
Nodes (5): PlaneEdges, arcs, curves, segments, vertices

### Community 70 - "Command.cpp"
Cohesion: 0.18
Nodes (13): expressionKey(), checkInputValue(), CommandContext::evaluateExpression(), CommandDef::input(), CommandSession::applyInTransaction(), CommandSession::cancel(), CommandSession::execute(), CommandSession::preview() (+5 more)

### Community 71 - "ParametersDialog.cpp"
Cohesion: 0.07
Nodes (20): QDialog, MainWindow::exportDesign(), MainWindow::openMeasure(), toolWindow(), number(), ParametersDialog, building_, error_ (+12 more)

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
Cohesion: 0.12
Nodes (17): InputType, Axis, Bodies, Body, Bool, Choice, Edges, Faces (+9 more)

### Community 76 - "Vec3"
Cohesion: 0.17
Nodes (19): SurfacePoint, normal, point, Vec3, boundingBox(), edgeMidpoint(), edgesNear(), frame() (+11 more)

### Community 77 - "dimensionOf"
Cohesion: 0.20
Nodes (6): formatNumber(), Dimension, Angle, Length, Unitless, dimensionOf()

### Community 79 - "ExpressionSpinBox"
Cohesion: 0.16
Nodes (4): ExpressionSpinBox, eval_, expression_, shown_

### Community 80 - "SketchDisplay"
Cohesion: 0.12
Nodes (11): ProfileObject, index, sketch, SketchDisplay, construction, curves, fixedCurves, frame (+3 more)

### Community 81 - "Command"
Cohesion: 0.04
Nodes (55): Adding a tool, Command, CommandDef, feature, icon, id, inputs, name (+47 more)

### Community 82 - "Measurement"
Cohesion: 0.13
Nodes (14): Kind, Angle, Area, Length, Volume, Measurement, from, hasLine (+6 more)

### Community 83 - "SketchCurves.cpp"
Cohesion: 0.28
Nodes (11): crossings(), crossingsOf(), curve2d(), endIsFree(), extendCurve(), finishExtend(), flattened(), newPoint() (+3 more)

### Community 84 - "Unit"
Cohesion: 0.17
Nodes (13): MainWindow::lengthUnit(), Unit, Centimeter, Degree, Foot, Inch, Meter, Millimeter (+5 more)

### Community 85 - "Level"
Cohesion: 0.16
Nodes (13): debug(), error(), info(), Level, Debug, Error, Info, Warning (+5 more)

### Community 86 - "README.md"
Cohesion: 0.11
Nodes (15): Build, Conventions, Development, Tests, Reference parts, Fusion feature checklist, Roadmap, Contents (+7 more)

### Community 87 - "Document.cpp"
Cohesion: 0.07
Nodes (37): ConstructionPlane, name, spec, DocumentError, checkViewName(), Document::abortTransaction(), Document::addNamedView(), Document::addUserParameter() (+29 more)

### Community 89 - "rect"
Cohesion: 0.10
Nodes (8): SelectionBox, crossing, Session::notifyChanged(), height, Rect, rect(), l, p

### Community 90 - "MainWindow::MainWindow"
Cohesion: 0.12
Nodes (5): PythonHost, MainWindow::MainWindow(), MainWindow::beginSketch(), MainWindow::exitSketchMode(), MainWindow::showPreferences()

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

### Community 97 - "Feature"
Cohesion: 0.10
Nodes (21): Feature, commandId, error, id, inputs, name, parameterNames, rolledBack (+13 more)

### Community 98 - "FakeDoc"
Cohesion: 0.17
Nodes (6): FakeDoc, aborts, commits, items, open, snapshot

### Community 100 - "Expression.cpp"
Cohesion: 0.20
Nodes (13): ExpressionEnv, lengthUnit, lookup, ExpressionError, evaluateExpression(), evaluateQuantity(), expressionReferences(), isConstantName() (+5 more)

### Community 102 - "sstream"
Cohesion: 0.17
Nodes (5): doc_(), Document::Document(), Document::ocafBytes(), ocafApplication(), Document::load()

### Community 103 - "Sketch.h"
Cohesion: 0.25
Nodes (7): EntityType, Arc, Circle, Ellipse, Line, Spline, isRound()

### Community 104 - "BoundingBox"
Cohesion: 0.22
Nodes (9): BoundingBox, max, min, extendedWire(), massProperties(), measure(), offsetOpenWire(), polygonToCircleLoft() (+1 more)

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

### Community 112 - "NavPreset"
Cohesion: 0.33
Nodes (4): NavPreset, Fusion, SolidWorks, Tinkercad

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

### Community 121 - "bindAdsk"
Cohesion: 0.29
Nodes (3): bindAdsk(), BRepBody, index

### Community 123 - "Placement"
Cohesion: 0.25
Nodes (7): Placement, angle, cx, cy, dx, dy, scale

### Community 124 - "ChainSegment"
Cohesion: 0.67
Nodes (3): ChainSegment, entity, forward

### Community 127 - "TEST"
Cohesion: 0.27
Nodes (3): env(), mm(), TEST()

### Community 128 - "TEST"
Cohesion: 0.07
Nodes (11): Sketch, constraints, entities, points, texts, Sketch::addCircle(), Sketch::addConic(), Sketch::addEllipticalArc() (+3 more)

### Community 132 - "Curve2d"
Cohesion: 0.29
Nodes (6): Curve2d, periodic, t0, t1, makePiece(), paramOf()

### Community 141 - "Point"
Cohesion: 0.52
Nodes (6): Point, x, y, z, customPlaneSpec(), toDxf()

### Community 142 - "SplineHandle"
Cohesion: 0.29
Nodes (7): SplineHandle, arm, index, tx, ty, x, y

## Knowledge Gaps
- **773 isolated node(s):** `ok`, `output`, `error`, `isReal`, `real` (+768 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 1441 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **27 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `optional` connect `optional` to `Viewport`, `MainWindow`, `Kernel.cpp`, `MainWindowArrow.cpp`, `Io.cpp`, `Unit`, `.setTool`, `ViewportSketch.cpp`, `Inputs`, `string`, `ViewportArrow.cpp`, `Constraint`, `DocCommands.cpp`, `CommandDialog.cpp`, `SketchEditor.cpp`, `AnalysisSettings`, `ParamSet`, `InputDef`, `Document::recompute`, `Viewport.h`, `Session`, `Vec3`, `dimensionOf`, `ExpressionSpinBox`, `SketchCurves.cpp`, `Unit`, `Document.cpp`, `ReplayStep`, `SketchCurves.cpp`, `Feature`, `Expression.cpp`, `Joints`, `Kernel.h`?**
  _High betweenness centrality (0.113) - this node is a cross-community bridge._
- **What connects `ok`, `output`, `error` to the rest of the system?**
  _773 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Viewport` be split into smaller, more focused modules?**
  _Cohesion score 0.0159809183064997 - nodes in this community are weakly interconnected._
- **Why does `Viewport` connect `Viewport` to `rect`, `ViewportArrow.cpp`, `MainWindow`, `Unit`, `Viewport.cpp`, `optional`, `AnalysisSettings`, `AnalysisSettings`, `SketchDisplay`, `NavPreset`, `SketchCurves.cpp`, `.rebuild`, `MainWindow.cpp`, `.toPixels`, `ViewportAnalysis.cpp`, `Viewport.h`, `.setSelectionFilter`?**
  _High betweenness centrality (0.099) - this node is a cross-community bridge._
- **Should `Icons.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.05337690631808279 - nodes in this community are weakly interconnected._
- **Why does `SketchEditor` connect `SketchEditor` to `Viewport`, `ViewportArrow.cpp`, `ParameterCompleter`, `Constraint`, `PlaneEdges`, `Snap`, `Kind`, `Display`, `Pick`, `SketchEditor.cpp`, `Text`, `.setTool`, `Unit`, `Viewport.h`, `Entity`, `.solveAndShow`, `Session`, `ReplayStep`?**
  _High betweenness centrality (0.087) - this node is a cross-community bridge._
- **Should `Session.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.08200290275761973 - nodes in this community are weakly interconnected._