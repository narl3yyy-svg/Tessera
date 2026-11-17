# Graph Report - tessera  (2026-11-17)

## Corpus Check
- 411 files · ~273,370 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 67 file(s) not represented in the graph (top: .drive 59, (none) 5, .cmake 1)

## Summary
- 3856 nodes · 9931 edges · 136 communities (109 shown, 27 thin omitted)
- Extraction: 85% EXTRACTED · 15% INFERRED · 0% AMBIGUOUS · INFERRED: 1517 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `84d199d6`
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
- MainWindowArrow.cpp
- CommandDialog
- Io.cpp
- Parser
- sketchFor
- Entity
- Document
- Snap
- Affine
- ViewportSketch.cpp
- SketchPalette
- Sketch
- DocCommands.cpp
- CommandContext
- Colors
- KernelError
- SketchOps.cpp
- MainWindowSketch.cpp
- ParameterCompleter
- Constraint
- DocCommands.cpp
- MainWindow.cpp
- solve
- Pick
- curve
- ConstraintType
- AdskModule.cpp
- Pick
- src/main.cpp
- Zip.cpp
- AnalysisSettings
- Sketch.cpp
- Document.cpp
- MarkingMenu.cpp
- InputDef
- .updatePreview
- .toPixels
- string
- dimensionOf
- BoundingBox
- ViewportAnalysis.cpp
- xdrive.py
- isInputVisible
- Session
- Theme.cpp
- BodyFrame
- CommandRegistry
- TestFramework.h
- TEST
- Theme
- Feature
- InputType
- ParametersDialog.cpp
- Kernel.h
- Viewport.h
- Command.cpp
- SketchEditor.cpp
- Vec3
- BoundaryCell
- math
- CommandDialog::CommandDialog
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
- Viewport.h
- FakeDoc
- ModelParameter
- CommandSession
- Document::load
- UserParameter
- includeEdges
- test_rigid_group.py
- .eventFilter
- Display
- cli_main.cpp
- TopologyCounts
- Session::editFeature
- .redrawAll
- EntityType
- uninstall.sh
- install.sh
- TestFramework.h
- .rebuild
- MarkingMenu
- Value.h
- PythonHost
- Joints
- test_incremental_replay.py
- Placement::apply
- test_text_box_path.py
- Session::addListener
- Joint
- Architecture
- LAB_NOTES.md
- build.sh
- live-test.sh
- SplineHandle
- ChainSegment

## God Nodes (most connected - your core abstractions)
1. `Viewport` - 258 edges
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

## Communities (136 total, 27 thin omitted)

### Community 0 - "Viewport"
Cohesion: 0.02
Nodes (69): view_, QLineEdit, Viewport, analysis_, analysisObjects_, appliedGridStep_, arrowBoxes_, arrowDragging_ (+61 more)

### Community 1 - "Icons.cpp"
Cohesion: 0.05
Nodes (129): accessibilityIcon(), appearanceIcon(), arc3Icon(), arcIcon(), arcTangentIcon(), arrow(), axisIcon(), boundaryFillIcon() (+121 more)

### Community 2 - "Session.cpp"
Cohesion: 0.18
Nodes (25): historyEdit(), plainEdit(), Session::addNamedView(), Session::computeAll(), Session::deleteFeature(), Session::deleteNamedView(), Session::deleteParameter(), Session::newDocument() (+17 more)

### Community 4 - "MainWindow"
Cohesion: 0.02
Nodes (72): CommandDialog, MainWindow, active_, arrowInput_, arrowInput2_, bodiesBeforeCommand_, combEdges_, combPicking_ (+64 more)

### Community 5 - "run_oracle.py"
Cohesion: 0.08
Nodes (54): add_point(), arc_poly(), body_at(), body_list(), build_sketch(), chain(), circumcentre(), cm() (+46 more)

### Community 6 - "NewComponent"
Cohesion: 0.11
Nodes (9): AddUserParameter, def_, isIdentifier(), Loft, def_, NewComponent, def_, RigidGroup (+1 more)

### Community 7 - "Document"
Cohesion: 0.03
Nodes (17): Document, effects_, lastReplayed_, lastReused_, modified_, pendingTools_, registry_, replaying_ (+9 more)

### Community 8 - "Viewport.cpp"
Cohesion: 0.05
Nodes (5): glide(), keys(), QKeyEvent, QtFrameBuffer, Viewport::Viewport()

### Community 9 - "SketchEditor"
Cohesion: 0.03
Nodes (56): HudField, edit, editing, kind, locked, value, QLineEdit, SketchEditor (+48 more)

### Community 10 - "DocumentError"
Cohesion: 0.08
Nodes (32): DocumentError, checkViewName(), Document::abortTransaction(), Document::addBody(), Document::addNamedView(), Document::addUserParameter(), Document::axisFrame(), Document::commitTransaction() (+24 more)

### Community 11 - "optional"
Cohesion: 0.14
Nodes (3): optional, CommandRegistry::all(), Document

### Community 12 - "Kernel.cpp"
Cohesion: 0.04
Nodes (3): isoCoarsePitch(), topologyCounts(), wrapOntoCylinder()

### Community 13 - "AnalysisSettings"
Cohesion: 0.11
Nodes (18): AnalysisKind, Accessibility, CurvatureMap, Draft, Isocurve, MinimumRadius, None, Zebra (+10 more)

### Community 14 - "Kind"
Cohesion: 0.06
Nodes (29): ConstructPlane, def_, kind_, EdgeFeature, def_, kind_, Kind, Angle (+21 more)

### Community 15 - "MainWindowArrow.cpp"
Cohesion: 0.13
Nodes (8): ArrowPlacement, base, dir, edgePlacement(), facesPlacement(), MainWindow::attachArrowCompleters(), MainWindow::patternCentre(), MainWindow::pickedFaces()

### Community 16 - "CommandDialog"
Cohesion: 0.04
Nodes (35): CommandDialog, bodiesId_, bodiesLabel_, bodyInput_, buttons_, cellsId_, cellsList_, cmd_ (+27 more)

### Community 17 - "Io.cpp"
Cohesion: 0.10
Nodes (18): NamedShape, compoundOf(), exportShapes(), fmt(), formatForPath(), fromBrep(), importShape(), lower() (+10 more)

### Community 18 - "Parser"
Cohesion: 0.07
Nodes (45): MainWindow::lengthUnit(), ExpressionEnv, lengthUnit, lookup, ExpressionError, Quantity, angle, length (+37 more)

### Community 19 - "sketchFor"
Cohesion: 0.13
Nodes (11): Emboss, def_, Extrude, def_, Pipe, def_, Revolve, def_ (+3 more)

### Community 20 - "Entity"
Cohesion: 0.08
Nodes (11): Entity, a, b, center, construction, fit, handles, included (+3 more)

### Community 21 - "Document"
Cohesion: 0.19
Nodes (6): ConstructAxisPoint, def_, kind_, JointPick, frame, revolveAxis()

### Community 22 - "Snap"
Cohesion: 0.06
Nodes (32): Kind, Angle, BodyEdge, BodyVertex, Count, Entity, Free, Grid (+24 more)

### Community 24 - "Affine"
Cohesion: 0.14
Nodes (13): Affine, a, b, d, e, Builder, byPlace_, k_ (+5 more)

### Community 25 - "ViewportSketch.cpp"
Cohesion: 0.08
Nodes (6): faceStyle(), lineStyle(), rgb(), Viewport::lookAt(), Viewport::planePoint(), Viewport::toWidget()

### Community 26 - "SketchPalette"
Cohesion: 0.06
Nodes (26): flatButton(), QCheckBox, QLabel, QToolButton, QWidget, SketchEditor, SketchPalette, body_ (+18 more)

### Community 27 - "Sketch"
Cohesion: 0.07
Nodes (10): Sketch, constraints, entities, points, texts, Sketch::addCircle(), Sketch::addConic(), Sketch::addEllipticalArc() (+2 more)

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
Cohesion: 0.15
Nodes (32): Placement, angle, cx, cy, dx, dy, scale, at() (+24 more)

### Community 33 - "MainWindowSketch.cpp"
Cohesion: 0.05
Nodes (19): MainWindow::cancelSketch(), MainWindow::editSketch(), MainWindow::exitSketchMode(), MainWindow::finishSketch(), MainWindow::onEdgeClicked(), MainWindow::onProfileClicked(), MainWindow::originalShape(), MainWindow::sketchPalette() (+11 more)

### Community 34 - "ParameterCompleter"
Cohesion: 0.11
Nodes (9): QObject, ParameterCompleter, completer_, edit_, names_, ParameterCompleter::ParameterCompleter(), public, QCompleter (+1 more)

### Community 35 - "Constraint"
Cohesion: 0.06
Nodes (29): Constraint, driven, entities, expression, hasLabel, labelX, labelY, name (+21 more)

### Community 36 - "DocCommands.cpp"
Cohesion: 0.12
Nodes (21): axisOf(), CreateSketch, def_, evaluateDimensions(), HoleSize, modeled, pitch, radius (+13 more)

### Community 37 - "MainWindow.cpp"
Cohesion: 0.06
Nodes (8): commandIcon(), MainWindow::MainWindow(), qs(), MainWindow::beginSketch(), MainWindow::buildSketchTab(), MainWindow::enterSketchMode(), QTimer, Viewport::selectArrowValue()

### Community 38 - "solve"
Cohesion: 0.16
Nodes (12): addConstraintChecked(), Layout, n, px, py, rad, makeLayout(), pack() (+4 more)

### Community 39 - "Pick"
Cohesion: 0.07
Nodes (22): Hit, index, kind, Pick, bodyArc, bodyPoint, bodySegment, hit (+14 more)

### Community 40 - "curve"
Cohesion: 0.24
Nodes (13): conditionedSpline(), curve(), curves(), entityCurves(), interiorPoint(), offPlane(), profileAt(), profiles() (+5 more)

### Community 41 - "ConstraintType"
Cohesion: 0.07
Nodes (27): ConstraintType, Angle, Coincident, Collinear, Concentric, Curvature, Diameter, Distance (+19 more)

### Community 42 - "AdskModule.cpp"
Cohesion: 0.09
Nodes (16): Application, bindAdsk(), BRepBodies, BRepBody, index, Component, Design, Product (+8 more)

### Community 43 - "Pick"
Cohesion: 0.09
Nodes (7): x, y, PlaneEdges, arcs, curves, segments, vertices

### Community 45 - "src/main.cpp"
Cohesion: 0.09
Nodes (4): QAbstractButton, QAction, grabWindowWithPanels(), writeLiveGeometry()

### Community 46 - "Zip.cpp"
Cohesion: 0.20
Nodes (13): Entry, data, name, ZipError, crc32(), deflateRaw(), get16(), get32() (+5 more)

### Community 47 - "AnalysisSettings"
Cohesion: 0.10
Nodes (16): DragArrow, base, dir, radius, ref, ring, value, PendingLook (+8 more)

### Community 48 - "Sketch.cpp"
Cohesion: 0.08
Nodes (19): SketchError, SplineKind, Conic, Control, Fit, entityTypeName(), isDimension(), Sketch::addConstraint() (+11 more)

### Community 49 - "Document.cpp"
Cohesion: 0.06
Nodes (47): ConstructionPlane, name, spec, ParamSet, env, text, SketchRecord, data (+39 more)

### Community 50 - "MarkingMenu.cpp"
Cohesion: 0.07
Nodes (22): UiCommand, enabled, icon, id, name, panel, run, shortcut (+14 more)

### Community 51 - "InputDef"
Cohesion: 0.09
Nodes (22): InputDef, choices, defaultValue, id, label, max, min, minExclusive (+14 more)

### Community 52 - ".updatePreview"
Cohesion: 0.20
Nodes (3): ccwContains(), circumcircle(), segDistance()

### Community 55 - "string"
Cohesion: 0.15
Nodes (15): bodyNumber(), Document::componentOfBody(), Document::nextAxisName(), Document::nextBodyName(), Document::nextComponentName(), Document::nextDimensionName(), Document::nextPlaneName(), Document::nextPointName() (+7 more)

### Community 56 - "dimensionOf"
Cohesion: 0.20
Nodes (6): formatNumber(), Dimension, Angle, Length, Unitless, dimensionOf()

### Community 57 - "BoundingBox"
Cohesion: 0.19
Nodes (15): BoundingBox, max, min, WallSide, Center, Side1, Side2, curveMiddles() (+7 more)

### Community 58 - "ViewportAnalysis.cpp"
Cohesion: 0.11
Nodes (6): packed(), ramp(), shade(), Viewport::buildAnalysis(), Viewport::setCurvatureComb(), f

### Community 59 - "xdrive.py"
Cohesion: 0.28
Nodes (15): button(), canvas(), click(), drag(), flush(), geometry(), key(), keycode() (+7 more)

### Community 62 - "Session"
Cohesion: 0.07
Nodes (10): PythonHost::PythonHost(), main(), smoke(), key, Session, commands_, doc_, listeners_ (+2 more)

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

### Community 67 - "TEST"
Cohesion: 0.10
Nodes (3): param(), TEST(), tmp()

### Community 68 - "Theme"
Cohesion: 0.22
Nodes (4): Theme, colors_, public, styled_

### Community 69 - "Feature"
Cohesion: 0.08
Nodes (19): Feature, commandId, error, id, inputs, name, parameterNames, rolledBack (+11 more)

### Community 70 - "InputType"
Cohesion: 0.09
Nodes (21): bindTsr(), fromPy(), toPy(), typeName(), InputType, Axis, Bodies, Body (+13 more)

### Community 71 - "ParametersDialog.cpp"
Cohesion: 0.06
Nodes (24): Column, kComment, kExpression, kName, kParameter, kStar, kUnit, kValue (+16 more)

### Community 72 - "Kernel.h"
Cohesion: 0.10
Nodes (19): Axis, X, Y, Z, BooleanOp, Cut, Intersect, Join (+11 more)

### Community 73 - "Viewport.h"
Cohesion: 0.06
Nodes (18): MarkingMenu::mouseMoveEvent(), QMouseEvent, ViewInteractor, Viewport::frontEdgeOwner(), segmentDistance(), Viewport::arrowAt(), Viewport::arrowMouseMove(), Viewport::arrowMousePress() (+10 more)

### Community 74 - "Command.cpp"
Cohesion: 0.24
Nodes (11): expressionKey(), checkInputValue(), CommandContext::evaluateExpression(), CommandDef::input(), CommandSession::applyInTransaction(), CommandSession::cancel(), CommandSession::execute(), CommandSession::preview() (+3 more)

### Community 75 - "SketchEditor.cpp"
Cohesion: 0.08
Nodes (13): angleInArc(), ext(), fixedColor(), freeColor(), HandleHit, back, index, spline (+5 more)

### Community 76 - "Vec3"
Cohesion: 0.17
Nodes (21): SurfacePoint, normal, point, Vec3, containsPoint(), edgeMidpoint(), edgesNear(), frame() (+13 more)

### Community 77 - "BoundaryCell"
Cohesion: 0.29
Nodes (4): BoundaryCell, ref, shape, volume

### Community 78 - "math"
Cohesion: 0.07
Nodes (3): dist(), check_regular(), dist_to_line()

### Community 79 - "CommandDialog::CommandDialog"
Cohesion: 0.13
Nodes (5): CommandDialog::CommandDialog(), ExpressionSpinBox, eval_, expression_, shown_

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
Cohesion: 0.11
Nodes (8): SelectionBox, crossing, Session::notifyChanged(), height, Rect, rect(), l, p

### Community 85 - "Level"
Cohesion: 0.16
Nodes (13): debug(), error(), info(), Level, Debug, Error, Info, Warning (+5 more)

### Community 86 - "README.md"
Cohesion: 0.06
Nodes (26): Build, Conventions, Development, Tests, 3D Sketch, Boundary Fill, Curvature (G2), Emboss (+18 more)

### Community 89 - "Sweep"
Cohesion: 0.27
Nodes (4): Coil, def_, Sweep, def_

### Community 90 - "QDialog"
Cohesion: 0.05
Nodes (31): QDialog, MainWindow::applySection(), MainWindow::checkInterference(), MainWindow::chooseUnits(), MainWindow::driveJoints(), MainWindow::editAppearance(), MainWindow::editMaterial(), MainWindow::exportDesign() (+23 more)

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
Nodes (43): Body, color, display, material, name, shape, Component, bodies (+35 more)

### Community 96 - "G2End"
Cohesion: 0.29
Nodes (6): G2End, d1, d2, set, g2Ends(), signedCurvature()

### Community 97 - "Viewport.h"
Cohesion: 0.08
Nodes (6): QLabel, Profile, area, face, x, y

### Community 98 - "FakeDoc"
Cohesion: 0.17
Nodes (6): FakeDoc, aborts, commits, items, open, snapshot

### Community 99 - "ModelParameter"
Cohesion: 0.13
Nodes (13): ModelParameter, angle, expression, input, label, name, owner, unit (+5 more)

### Community 101 - "CommandSession"
Cohesion: 0.15
Nodes (4): CommandSession, inputs_, CommandRegistry::find(), CommandRegistry::run()

### Community 102 - "Document::load"
Cohesion: 0.17
Nodes (5): doc_(), Document::Document(), Document::ocafBytes(), ocafApplication(), Document::load()

### Community 103 - "UserParameter"
Cohesion: 0.33
Nodes (6): UserParameter, comment, expression, name, unit, value

### Community 107 - "Display"
Cohesion: 0.25
Nodes (7): Display, constraints, construction, dimensions, points, profiles, projected

### Community 108 - "cli_main.cpp"
Cohesion: 0.60
Nodes (3): listCommands(), main(), usage()

### Community 110 - "TopologyCounts"
Cohesion: 0.16
Nodes (18): Section, Circular, Square, Triangular, TopologyCounts, edges, faces, shells (+10 more)

### Community 111 - "Session::editFeature"
Cohesion: 0.29
Nodes (5): OwnedCommand, owned, OwningCommandSession, Session::begin(), Session::editFeature()

### Community 112 - ".redrawAll"
Cohesion: 0.09
Nodes (9): NavPreset, Fusion, SolidWorks, Tinkercad, rgb(), Viewport::clearDragArrow(), Viewport::clearSecondArrow(), Viewport::rebuildArrow() (+1 more)

### Community 113 - "EntityType"
Cohesion: 0.29
Nodes (7): EntityType, Arc, Circle, Ellipse, Line, Spline, isRound()

### Community 114 - "uninstall.sh"
Cohesion: 0.52
Nodes (6): die(), manifest_for(), refresh(), uninstall.sh script, step(), usage()

### Community 115 - "install.sh"
Cohesion: 0.60
Nodes (5): die(), refresh(), install.sh script, step(), usage()

### Community 116 - "TestFramework.h"
Cohesion: 0.17
Nodes (8): Result, error, ok, output, captured(), PYBIND11_EMBEDDED_MODULE(), PythonHost::exec(), PythonHost::runScript()

### Community 117 - ".rebuild"
Cohesion: 0.10
Nodes (12): hiddenColour(), qc(), rgb(), sharpEdges(), Style, Shaded, ShadedEdges, ShadedHidden (+4 more)

### Community 118 - "MarkingMenu"
Cohesion: 0.40
Nodes (3): MarkingMenu, enabled, public

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
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 1503 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **27 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `optional` connect `optional` to `Viewport`, `MainWindow`, `SketchEditor`, `Kernel.cpp`, `MainWindowArrow.cpp`, `Io.cpp`, `Parser`, `sketchFor`, `Entity`, `CommandDialog.cpp`, `ViewportSketch.cpp`, `SketchOps.cpp`, `DocCommands.cpp`, `Pick`, `AnalysisSettings`, `Document.cpp`, `InputDef`, `SketchGeometry.cpp`, `string`, `dimensionOf`, `Session`, `Feature`, `Kernel.h`, `Viewport.h`, `SketchEditor.cpp`, `Vec3`, `CommandDialog::CommandDialog`, `SketchCurves.cpp`, `ReplayStep`, `Viewport.h`?**
  _High betweenness centrality (0.133) - this node is a cross-community bridge._
- **What connects `ok`, `output`, `error` to the rest of the system?**
  _791 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Viewport` be split into smaller, more focused modules?**
  _Cohesion score 0.015854374633000587 - nodes in this community are weakly interconnected._
- **Why does `Viewport` connect `Viewport` to `Viewport.h`, `MainWindow`, `MainWindow.cpp`, `QDialog`, `Viewport.cpp`, `Viewport.h`, `optional`, `AnalysisSettings`, `src/main.cpp`, `AnalysisSettings`, `SketchDisplay`, `.redrawAll`, `SketchCurves.cpp`, `rect`, `.rebuild`, `.toPixels`, `ViewportAnalysis.cpp`?**
  _High betweenness centrality (0.110) - this node is a cross-community bridge._
- **Should `Icons.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.05167173252279635 - nodes in this community are weakly interconnected._
- **Why does `SketchEditor` connect `SketchEditor` to `Viewport`, `Viewport.h`, `ParameterCompleter`, `Constraint`, `Pick`, `Viewport.h`, `.eventFilter`, `SketchEditor.cpp`, `Display`, `Pick`, `optional`, `Parser`, `Entity`, `.updatePreview`, `Snap`, `Session`?**
  _High betweenness centrality (0.105) - this node is a cross-community bridge._
- **Should `tsr` be split into smaller, more focused modules?**
  _Cohesion score 0.04390451832907076 - nodes in this community are weakly interconnected._