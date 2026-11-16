# Graph Report - tessera  (2026-11-16)

## Corpus Check
- 410 files · ~273,094 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 66 file(s) not represented in the graph (top: .drive 58, (none) 5, .cmake 1)

## Summary
- 3854 nodes · 9928 edges · 135 communities (110 shown, 25 thin omitted)
- Extraction: 85% EXTRACTED · 15% INFERRED · 0% AMBIGUOUS · INFERRED: 1516 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `f4660737`
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
- Viewport.h
- Kind
- src/main.cpp
- CommandDialog
- Io.cpp
- Parser
- sketchFor
- Entity
- Document
- Snap
- CommandDialog.cpp
- Affine
- ViewportSketch.cpp
- SketchPalette
- Sketch
- DocCommands.cpp
- CommandContext
- Colors
- KernelError
- SketchOps.cpp
- .openMarkingMenu
- ParameterCompleter
- Constraint
- DocCommands.cpp
- MainWindow.cpp
- solve
- .eventFilter
- curve
- ConstraintType
- AdskModule.cpp
- Pick
- Unit
- Zip.cpp
- AnalysisSettings
- Sketch.cpp
- Document.cpp
- MarkingMenu.cpp
- InputDef
- SketchEditor.cpp
- .toPixels
- Document::recompute
- Dimension
- BoundingBox
- Expression.cpp
- xdrive.py
- adsk_core
- Session
- Theme.cpp
- BodyFrame
- CommandRegistry
- TestFramework.h
- TEST
- Theme
- optional
- InputType
- ParametersDialog.cpp
- Kernel.h
- Viewport.h
- TEST
- .mouseMove
- Vec3
- CommandDialog::CommandDialog
- math
- QString
- SketchDisplay
- CommandDef
- Measurement
- SketchCurves.cpp
- rect
- Level
- README.md
- .add
- test_feature_pattern.py
- Sweep
- QDialog
- toDxf
- FileFormat
- Known differences still to build
- TEST
- ReplayStep
- G2End
- Sketch.h
- FakeDoc
- ParamSet
- NamedView
- Viewport::planePoint
- Document::load
- UserParameter
- includeEdges
- test_rigid_group.py
- SectionState
- Display
- cli_main.cpp
- TopologyCounts
- .redrawAll
- MainWindow::lookTargets
- uninstall.sh
- install.sh
- TestFramework.h
- .rebuild
- MarkingMenu
- Known gaps
- Joints
- test_incremental_replay.py
- Placement
- Placement::apply
- Column
- Joint
- Architecture
- LAB_NOTES.md
- build.sh
- live-test.sh
- SplineHandle
- ChainSegment

## God Nodes (most connected - your core abstractions)
1. `Viewport` - 257 edges
2. `SketchEditor` - 198 edges
3. `MainWindow` - 184 edges
4. `Inputs` - 160 edges
5. `render()` - 124 edges
6. `Document` - 121 edges
7. `CommandContext` - 116 edges
8. `CommandDialog` - 95 edges
9. `Command` - 68 edges
10. `CommandError` - 68 edges

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

## Communities (135 total, 25 thin omitted)

### Community 0 - "Viewport"
Cohesion: 0.02
Nodes (68): view_, Viewport, analysis_, analysisObjects_, appliedGridStep_, arrowBoxes_, arrowDragging_, arrowGrab_ (+60 more)

### Community 1 - "Icons.cpp"
Cohesion: 0.05
Nodes (129): accessibilityIcon(), appearanceIcon(), arc3Icon(), arcIcon(), arcTangentIcon(), arrow(), axisIcon(), boundaryFillIcon() (+121 more)

### Community 2 - "Session.cpp"
Cohesion: 0.06
Nodes (46): CommandSession, inputs_, expressionKey(), checkInputValue(), CommandContext::evaluateExpression(), CommandDef::input(), CommandSession::applyInTransaction(), CommandSession::cancel() (+38 more)

### Community 4 - "MainWindow"
Cohesion: 0.03
Nodes (64): CommandDialog, MainWindow, active_, arrowInput_, arrowInput2_, bodiesBeforeCommand_, combEdges_, combPicking_ (+56 more)

### Community 5 - "run_oracle.py"
Cohesion: 0.08
Nodes (54): add_point(), arc_poly(), body_at(), body_list(), build_sketch(), chain(), circumcentre(), cm() (+46 more)

### Community 6 - "NewComponent"
Cohesion: 0.11
Nodes (9): AddUserParameter, def_, isIdentifier(), Loft, def_, NewComponent, def_, RigidGroup (+1 more)

### Community 7 - "Document"
Cohesion: 0.03
Nodes (13): Document, effects_, lastReplayed_, lastReused_, modified_, pendingTools_, registry_, replaying_ (+5 more)

### Community 8 - "Viewport.cpp"
Cohesion: 0.05
Nodes (5): glide(), keys(), QKeyEvent, QtFrameBuffer, Viewport::Viewport()

### Community 9 - "SketchEditor"
Cohesion: 0.03
Nodes (58): HandleHit, back, index, spline, PlaneEdges, arcs, curves, segments (+50 more)

### Community 10 - "DocumentError"
Cohesion: 0.09
Nodes (30): DocumentError, SketchRecord, data, name, offset, plane, checkViewName(), Document::abortTransaction() (+22 more)

### Community 11 - "optional"
Cohesion: 0.12
Nodes (4): isEmpty(), Value, CommandRegistry::all(), Document

### Community 12 - "Kernel.cpp"
Cohesion: 0.04
Nodes (3): isoCoarsePitch(), topologyCounts(), wrapOntoCylinder()

### Community 13 - "Viewport.h"
Cohesion: 0.06
Nodes (20): AnalysisKind, Accessibility, CurvatureMap, Draft, Isocurve, MinimumRadius, None, Zebra (+12 more)

### Community 14 - "Kind"
Cohesion: 0.06
Nodes (29): ConstructPlane, def_, kind_, EdgeFeature, def_, kind_, Kind, Angle (+21 more)

### Community 15 - "src/main.cpp"
Cohesion: 0.06
Nodes (11): grabWindowWithPanels(), writeLiveGeometry(), ArrowPlacement, base, dir, edgePlacement(), facesPlacement(), MainWindow::attachArrowCompleters() (+3 more)

### Community 16 - "CommandDialog"
Cohesion: 0.05
Nodes (35): CommandDialog, bodiesId_, bodiesLabel_, bodyInput_, buttons_, cellsId_, cellsList_, cmd_ (+27 more)

### Community 17 - "Io.cpp"
Cohesion: 0.09
Nodes (20): MainWindow::print3d(), NamedShape, compoundOf(), exportShapes(), fmt(), formatForPath(), fromBrep(), importShape() (+12 more)

### Community 18 - "Parser"
Cohesion: 0.16
Nodes (18): ExpressionError, Quantity, angle, length, value, describe(), evaluateExpression(), isIdentChar() (+10 more)

### Community 19 - "sketchFor"
Cohesion: 0.13
Nodes (11): Emboss, def_, Extrude, def_, Pipe, def_, Revolve, def_ (+3 more)

### Community 20 - "Entity"
Cohesion: 0.09
Nodes (11): Entity, a, b, center, construction, fit, handles, included (+3 more)

### Community 21 - "Document"
Cohesion: 0.19
Nodes (6): ConstructAxisPoint, def_, kind_, JointPick, frame, revolveAxis()

### Community 22 - "Snap"
Cohesion: 0.05
Nodes (39): HudField, edit, editing, kind, locked, value, Kind, Angle (+31 more)

### Community 24 - "Affine"
Cohesion: 0.13
Nodes (13): Affine, a, b, d, e, Builder, byPlace_, k_ (+5 more)

### Community 25 - "ViewportSketch.cpp"
Cohesion: 0.04
Nodes (13): bindTsr(), fromPy(), toPy(), typeName(), packed(), ramp(), shade(), Viewport::buildAnalysis() (+5 more)

### Community 26 - "SketchPalette"
Cohesion: 0.04
Nodes (40): QAbstractButton, QAction, MainWindow::cancelSketch(), MainWindow::editSketch(), MainWindow::finishSketch(), MainWindow::onEdgeClicked(), MainWindow::onProfileClicked(), MainWindow::originalShape() (+32 more)

### Community 27 - "Sketch"
Cohesion: 0.08
Nodes (17): Sketch, constraints, entities, points, texts, Text, angle, corner (+9 more)

### Community 28 - "DocCommands.cpp"
Cohesion: 0.13
Nodes (29): CommandError, getBool(), getInt(), getReal(), applyOperation(), bodyCentre(), bodyName(), boundaryFillCells() (+21 more)

### Community 29 - "CommandContext"
Cohesion: 0.04
Nodes (45): Adding a tool, Command, CommandContext, Inputs, CommandSession::CommandSession(), checkBody(), checkPattern(), CircularPattern (+37 more)

### Community 30 - "Colors"
Cohesion: 0.07
Nodes (28): Colors, base, border, cubeBox, cubeText, errorBackground, grid, gridMajor (+20 more)

### Community 31 - "KernelError"
Cohesion: 0.20
Nodes (36): KernelError, asSolid(), boolean(), boundaryCells(), chamfer(), chamferEx(), deleteFaces(), draft() (+28 more)

### Community 32 - "SketchOps.cpp"
Cohesion: 0.22
Nodes (25): at(), chainOf(), chamferCorner(), circularPattern(), copyEntities(), cornerAt(), cross(), dot() (+17 more)

### Community 33 - ".openMarkingMenu"
Cohesion: 0.12
Nodes (5): MainWindow::beginSketch(), MainWindow::buildSketchTab(), MainWindow::enterSketchMode(), QTimer, Viewport::selectArrowValue()

### Community 34 - "ParameterCompleter"
Cohesion: 0.12
Nodes (8): ParameterCompleter, completer_, edit_, names_, ParameterCompleter::ParameterCompleter(), public, QCompleter, QLineEdit

### Community 35 - "Constraint"
Cohesion: 0.09
Nodes (21): Constraint, driven, entities, expression, hasLabel, labelX, labelY, name (+13 more)

### Community 36 - "DocCommands.cpp"
Cohesion: 0.12
Nodes (21): axisOf(), CreateSketch, def_, evaluateDimensions(), HoleSize, modeled, pitch, radius (+13 more)

### Community 37 - "MainWindow.cpp"
Cohesion: 0.05
Nodes (8): PythonHost, commandIcon(), flatButton(), MainWindow::MainWindow(), qs(), MainWindow::exitSketchMode(), MainWindow::applySection(), MainWindow::showPreferences()

### Community 38 - "solve"
Cohesion: 0.18
Nodes (13): addConstraintChecked(), Layout, n, px, py, rad, makeLayout(), pack() (+5 more)

### Community 39 - ".eventFilter"
Cohesion: 0.11
Nodes (8): QObject, SketchEditor::SketchEditor(), edges, Tool, op, shape, target, type

### Community 40 - "curve"
Cohesion: 0.24
Nodes (13): conditionedSpline(), curve(), curves(), entityCurves(), interiorPoint(), offPlane(), profileAt(), profiles() (+5 more)

### Community 41 - "ConstraintType"
Cohesion: 0.08
Nodes (26): ConstraintType, Angle, Coincident, Collinear, Concentric, Curvature, Diameter, Distance (+18 more)

### Community 42 - "AdskModule.cpp"
Cohesion: 0.12
Nodes (13): Application, BRepBodies, Component, Design, Product, raiseIfError(), UserParameter, name (+5 more)

### Community 43 - "Pick"
Cohesion: 0.08
Nodes (18): Hit, index, kind, Pick, bodyArc, bodyPoint, bodySegment, hit (+10 more)

### Community 45 - "Unit"
Cohesion: 0.12
Nodes (16): bindAdsk(), BRepBody, index, MainWindow::lengthUnit(), Unit, Centimeter, Degree, Foot (+8 more)

### Community 46 - "Zip.cpp"
Cohesion: 0.20
Nodes (13): Entry, data, name, ZipError, crc32(), deflateRaw(), get16(), get32() (+5 more)

### Community 47 - "AnalysisSettings"
Cohesion: 0.10
Nodes (16): DragArrow, base, dir, radius, ref, ring, value, PendingLook (+8 more)

### Community 48 - "Sketch.cpp"
Cohesion: 0.08
Nodes (20): SketchError, SplineKind, Conic, Control, Fit, entityTypeName(), isDimension(), Sketch::addConic() (+12 more)

### Community 49 - "Document.cpp"
Cohesion: 0.06
Nodes (48): ConstructionPlane, name, spec, bodyNumber(), Document::addBody(), Document::axisFrame(), Document::bodies(), Document::body() (+40 more)

### Community 50 - "MarkingMenu.cpp"
Cohesion: 0.06
Nodes (25): UiCommand, enabled, icon, id, name, panel, run, shortcut (+17 more)

### Community 51 - "InputDef"
Cohesion: 0.09
Nodes (22): InputDef, choices, defaultValue, id, label, max, min, minExclusive (+14 more)

### Community 52 - "SketchEditor.cpp"
Cohesion: 0.11
Nodes (4): angleInArc(), ccwContains(), circumcircle(), segDistance()

### Community 55 - "Document::recompute"
Cohesion: 0.18
Nodes (8): Document::openTransaction(), Document::recompute(), Document::recordFeature(), Document::removeFeature(), Document::setFeatureInputs(), Document::setFeatureSuppressed(), featureData(), toJson()

### Community 56 - "Dimension"
Cohesion: 0.50
Nodes (4): Dimension, Angle, Length, Unitless

### Community 57 - "BoundingBox"
Cohesion: 0.19
Nodes (15): BoundingBox, max, min, WallSide, Center, Side1, Side2, curveMiddles() (+7 more)

### Community 58 - "Expression.cpp"
Cohesion: 0.18
Nodes (9): evaluateQuantity(), expressionReferences(), isConstantName(), isFunctionName(), isPlainQuantity(), isValidParameterName(), env(), mm() (+1 more)

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
Cohesion: 0.07
Nodes (43): BodyFrame, diag, dx, dy, dz, x0, y0, z0 (+35 more)

### Community 65 - "CommandRegistry"
Cohesion: 0.12
Nodes (4): CommandRegistry, cmds_, CommandRegistry::add(), TEST()

### Community 66 - "TestFramework.h"
Cohesion: 0.12
Nodes (6): Case, fn, name, fail(), Failure, Register

### Community 68 - "Theme"
Cohesion: 0.22
Nodes (4): Theme, colors_, public, styled_

### Community 69 - "optional"
Cohesion: 0.08
Nodes (22): optional, ExpressionEnv, lengthUnit, lookup, ConstructionPoint, name, point, Feature (+14 more)

### Community 70 - "InputType"
Cohesion: 0.12
Nodes (17): InputType, Axis, Bodies, Body, Bool, Choice, Edges, Faces (+9 more)

### Community 71 - "ParametersDialog.cpp"
Cohesion: 0.08
Nodes (16): number(), ParametersDialog, building_, error_, filter_, listener_, ParametersDialog::ParametersDialog(), public (+8 more)

### Community 72 - "Kernel.h"
Cohesion: 0.10
Nodes (19): Axis, X, Y, Z, BooleanOp, Cut, Intersect, Join (+11 more)

### Community 73 - "Viewport.h"
Cohesion: 0.06
Nodes (21): MarkingMenu::mouseMoveEvent(), QMouseEvent, ViewInteractor, Viewport::frontEdgeOwner(), rgb(), segmentDistance(), Viewport::arrowAt(), Viewport::arrowMouseMove() (+13 more)

### Community 75 - ".mouseMove"
Cohesion: 0.16
Nodes (7): ext(), fixedColor(), freeColor(), lineEntity(), qc(), rgb(), wire()

### Community 76 - "Vec3"
Cohesion: 0.17
Nodes (21): SurfacePoint, normal, point, Vec3, containsPoint(), edgeMidpoint(), edgesNear(), frame() (+13 more)

### Community 77 - "CommandDialog::CommandDialog"
Cohesion: 0.14
Nodes (5): CommandDialog::CommandDialog(), BoundaryCell, ref, shape, volume

### Community 78 - "math"
Cohesion: 0.06
Nodes (3): dist(), check_regular(), dist_to_line()

### Community 79 - "QString"
Cohesion: 0.12
Nodes (6): ExpressionSpinBox, eval_, expression_, shown_, formatNumber(), dimensionOf()

### Community 80 - "SketchDisplay"
Cohesion: 0.12
Nodes (11): ProfileObject, index, sketch, SketchDisplay, construction, curves, fixedCurves, frame (+3 more)

### Community 81 - "CommandDef"
Cohesion: 0.07
Nodes (23): CommandDef, feature, icon, id, inputs, name, nameInput, panel (+15 more)

### Community 82 - "Measurement"
Cohesion: 0.13
Nodes (14): Kind, Angle, Area, Length, Volume, Measurement, from, hasLine (+6 more)

### Community 83 - "SketchCurves.cpp"
Cohesion: 0.14
Nodes (17): crossings(), crossingsOf(), Curve2d, curve2d(), periodic, t0, t1, endIsFree() (+9 more)

### Community 84 - "rect"
Cohesion: 0.18
Nodes (7): SelectionBox, crossing, Session::notifyChanged(), Rect, rect(), l, p

### Community 85 - "Level"
Cohesion: 0.16
Nodes (13): debug(), error(), info(), Level, Debug, Error, Info, Warning (+5 more)

### Community 86 - "README.md"
Cohesion: 0.11
Nodes (15): Build, Conventions, Development, Tests, Reference parts, Fusion feature checklist, Roadmap, Contents (+7 more)

### Community 89 - "Sweep"
Cohesion: 0.27
Nodes (4): Coil, def_, Sweep, def_

### Community 90 - "QDialog"
Cohesion: 0.06
Nodes (28): QDialog, MainWindow::checkInterference(), MainWindow::chooseUnits(), MainWindow::driveJoints(), MainWindow::editAppearance(), MainWindow::editMaterial(), MainWindow::exportDesign(), MainWindow::formatLength() (+20 more)

### Community 91 - "toDxf"
Cohesion: 0.43
Nodes (7): Point, x, y, z, customPlaneSpec(), planeFrame(), toDxf()

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
Cohesion: 0.05
Nodes (34): Body, color, display, material, name, shape, Component, bodies (+26 more)

### Community 96 - "G2End"
Cohesion: 0.29
Nodes (6): G2End, d1, d2, set, g2Ends(), signedCurvature()

### Community 97 - "Sketch.h"
Cohesion: 0.09
Nodes (14): cachedProfiles(), keyOf(), EntityType, Arc, Circle, Ellipse, Line, Spline (+6 more)

### Community 98 - "FakeDoc"
Cohesion: 0.17
Nodes (6): FakeDoc, aborts, commits, items, open, snapshot

### Community 99 - "ParamSet"
Cohesion: 0.08
Nodes (29): ModelParameter, angle, expression, input, label, name, owner, unit (+21 more)

### Community 100 - "NamedView"
Cohesion: 0.29
Nodes (7): NamedView, eye, name, size, target, up, Document::namedViews()

### Community 101 - "Viewport::planePoint"
Cohesion: 0.47
Nodes (3): Viewport::lookAt(), Viewport::planePoint(), Viewport::toWidget()

### Community 102 - "Document::load"
Cohesion: 0.17
Nodes (5): doc_(), Document::Document(), Document::ocafBytes(), ocafApplication(), Document::load()

### Community 103 - "UserParameter"
Cohesion: 0.33
Nodes (6): UserParameter, comment, expression, name, unit, value

### Community 106 - "SectionState"
Cohesion: 0.25
Nodes (7): SectionState, active, angle, flip, offset, plane, visible

### Community 107 - "Display"
Cohesion: 0.25
Nodes (7): Display, constraints, construction, dimensions, points, profiles, projected

### Community 108 - "cli_main.cpp"
Cohesion: 0.31
Nodes (5): listCommands(), main(), usage(), main(), smoke()

### Community 110 - "TopologyCounts"
Cohesion: 0.16
Nodes (18): Section, Circular, Square, Triangular, TopologyCounts, edges, faces, shells (+10 more)

### Community 112 - ".redrawAll"
Cohesion: 0.11
Nodes (7): NavPreset, Fusion, SolidWorks, Tinkercad, Viewport::clearDragArrow(), Viewport::clearSecondArrow(), Viewport::setInteractor()

### Community 114 - "uninstall.sh"
Cohesion: 0.52
Nodes (6): die(), manifest_for(), refresh(), uninstall.sh script, step(), usage()

### Community 115 - "install.sh"
Cohesion: 0.60
Nodes (5): die(), refresh(), install.sh script, step(), usage()

### Community 116 - "TestFramework.h"
Cohesion: 0.21
Nodes (8): Result, error, ok, output, captured(), PYBIND11_EMBEDDED_MODULE(), PythonHost::exec(), PythonHost::runScript()

### Community 117 - ".rebuild"
Cohesion: 0.10
Nodes (12): hiddenColour(), qc(), rgb(), sharpEdges(), Style, Shaded, ShadedEdges, ShadedHidden (+4 more)

### Community 118 - "MarkingMenu"
Cohesion: 0.40
Nodes (3): MarkingMenu, enabled, public

### Community 120 - "Known gaps"
Cohesion: 0.17
Nodes (11): 3D Sketch, Boundary Fill, Curvature (G2), Emboss, Face patterns, Include 3D Geometry, Known gaps, Project to Surface (+3 more)

### Community 123 - "Placement"
Cohesion: 0.25
Nodes (7): Placement, angle, cx, cy, dx, dy, scale

### Community 126 - "Column"
Cohesion: 0.25
Nodes (8): Column, kComment, kExpression, kName, kParameter, kStar, kUnit, kValue

### Community 129 - "Joint"
Cohesion: 0.36
Nodes (3): Joint, asBuilt_, def_

### Community 131 - "Architecture"
Cohesion: 0.40
Nodes (4): Architecture, How a command works, The document, Units

### Community 142 - "SplineHandle"
Cohesion: 0.25
Nodes (8): SplineHandle, arm, index, set, tx, ty, x, y

### Community 144 - "ChainSegment"
Cohesion: 0.67
Nodes (3): ChainSegment, entity, forward

## Knowledge Gaps
- **791 isolated node(s):** `ok`, `output`, `error`, `isReal`, `real` (+786 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 1501 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **25 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `optional` connect `optional` to `Viewport`, `MainWindow`, `SketchEditor`, `optional`, `Kernel.cpp`, `Viewport.h`, `src/main.cpp`, `CommandDialog`, `Io.cpp`, `Parser`, `sketchFor`, `Entity`, `CommandDialog.cpp`, `SketchOps.cpp`, `DocCommands.cpp`, `Pick`, `Unit`, `AnalysisSettings`, `Document.cpp`, `InputDef`, `SketchEditor.cpp`, `SketchGeometry.cpp`, `Session`, `Kernel.h`, `Viewport.h`, `Vec3`, `QString`, `SketchCurves.cpp`, `ReplayStep`, `Sketch.h`, `ParamSet`, `Viewport::planePoint`?**
  _High betweenness centrality (0.148) - this node is a cross-community bridge._
- **What connects `ok`, `output`, `error` to the rest of the system?**
  _791 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Viewport` be split into smaller, more focused modules?**
  _Cohesion score 0.016117125984251968 - nodes in this community are weakly interconnected._
- **Why does `Viewport` connect `Viewport` to `.openMarkingMenu`, `optional`, `Viewport.cpp`, `Viewport.h`, `optional`, `Viewport.h`, `AnalysisSettings`, `SketchDisplay`, `.redrawAll`, `.initializeGL`, `SketchCurves.cpp`, `rect`, `.rebuild`, `.toPixels`, `ViewportSketch.cpp`, `QDialog`?**
  _High betweenness centrality (0.118) - this node is a cross-community bridge._
- **Should `Icons.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.05167173252279635 - nodes in this community are weakly interconnected._
- **Why does `SketchEditor` connect `SketchEditor` to `Viewport`, `Constraint`, `MainWindow`, `optional`, `.eventFilter`, `Viewport.h`, `Display`, `optional`, `Pick`, `.mouseMove`, `Unit`, `SketchEditor.cpp`, `Entity`, `Snap`, `Session`?**
  _High betweenness centrality (0.108) - this node is a cross-community bridge._
- **Should `Session.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.06128364389233954 - nodes in this community are weakly interconnected._