# Graph Report - tessera  (2026-11-16)

## Corpus Check
- 390 files · ~258,459 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 58 file(s) not represented in the graph (top: .drive 50, (none) 5, .cmake 1)

## Summary
- 3725 nodes · 9555 edges · 137 communities (113 shown, 24 thin omitted)
- Extraction: 85% EXTRACTED · 15% INFERRED · 0% AMBIGUOUS · INFERRED: 1468 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `61b2ca4e`
- Run `git rev-parse HEAD` and compare to check if the graph is stale.
- Run `graphify update .` after code changes (no API cost).

## Community Hubs (Navigation)
- Viewport
- Icons.cpp
- Session.cpp
- MainWindow
- run_oracle.py
- QMouseEvent
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
- .setTool
- Document
- MainWindow.cpp
- MainWindowTools.cpp
- Affine
- ViewportSketch.cpp
- SketchPalette
- .mouseMove
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
- CommandDialog.cpp
- ConstraintType
- TsrModule.cpp
- Pick
- SketchEditor.cpp
- string
- Zip.cpp
- AnalysisSettings
- Sketch.cpp
- ParamSet
- MainWindowSketch.cpp
- InputDef
- string
- .toPixels
- UserParameter
- Document::recompute
- MarkingMenu.cpp
- TsrModule.cpp
- Entity
- xdrive.py
- adsk_core
- SketchGeometry.cpp
- Session
- Theme.cpp
- BodyFrame
- CommandRegistry
- TEST
- BodyFrame
- Theme
- PlaneEdges
- Expression.cpp
- ParametersDialog.cpp
- Kernel.h
- ViewportAnalysis.cpp
- Kind
- InputType
- Vec3
- CommandDialog::CommandDialog
- math
- ExpressionSpinBox
- SketchDisplay
- Command
- Measurement
- SketchCurves.cpp
- Level
- README.md
- Document.cpp
- test_feature_pattern.py
- rect
- Unit
- QTimer
- FormatInfo
- Known differences still to build
- TEST
- ReplayStep
- SketchRecord
- UiCommand
- FakeDoc
- ModelParameter
- TEST
- .buildNavBar
- sstream
- BoundingBox
- cachedProfiles
- SectionState
- Display
- cli_main.cpp
- smoke
- TopologyCounts
- Column
- .redrawAll
- uninstall.sh
- install.sh
- TestFramework.h
- .rebuild
- MarkingMenu
- .eventFilter
- EntityType
- test_incremental_replay.py
- Placement
- ChainSegment
- Icons.h
- Known gaps
- Architecture
- .updatePreview
- Joint
- fail
- Value.h
- LAB_NOTES.md
- build.sh
- live-test.sh
- SplineHandle

## God Nodes (most connected - your core abstractions)
1. `Viewport` - 257 edges
2. `SketchEditor` - 185 edges
3. `MainWindow` - 184 edges
4. `Inputs` - 152 edges
5. `Document` - 120 edges
6. `render()` - 119 edges
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

## Communities (137 total, 24 thin omitted)

### Community 0 - "Viewport"
Cohesion: 0.02
Nodes (68): view_, Viewport, analysis_, analysisObjects_, appliedGridStep_, arrowBoxes_, arrowDragging_, arrowGrab_ (+60 more)

### Community 1 - "Icons.cpp"
Cohesion: 0.05
Nodes (124): accessibilityIcon(), appearanceIcon(), arc3Icon(), arcIcon(), arcTangentIcon(), arrow(), axisIcon(), box() (+116 more)

### Community 2 - "Session.cpp"
Cohesion: 0.06
Nodes (46): CommandSession, inputs_, expressionKey(), checkInputValue(), CommandContext::evaluateExpression(), CommandDef::input(), CommandSession::applyInTransaction(), CommandSession::cancel() (+38 more)

### Community 4 - "MainWindow"
Cohesion: 0.03
Nodes (65): CommandDialog, MainWindow, active_, arrowInput_, arrowInput2_, bodiesBeforeCommand_, combEdges_, combPicking_ (+57 more)

### Community 5 - "run_oracle.py"
Cohesion: 0.08
Nodes (54): add_point(), arc_poly(), body_at(), body_list(), build_sketch(), chain(), circumcentre(), cm() (+46 more)

### Community 6 - "QMouseEvent"
Cohesion: 0.14
Nodes (8): MarkingMenu::mouseMoveEvent(), QMouseEvent, ViewInteractor, Viewport::arrowMouseMove(), Viewport::arrowMousePress(), Viewport::arrowMouseRelease(), Viewport::dragArrowForTest(), Viewport::rebuildArrows()

### Community 7 - "Document"
Cohesion: 0.03
Nodes (15): Document, effects_, lastReplayed_, lastReused_, modified_, pendingTools_, registry_, replaying_ (+7 more)

### Community 8 - "Viewport.cpp"
Cohesion: 0.06
Nodes (4): glide(), QKeyEvent, QtFrameBuffer, Viewport::frontEdgeOwner()

### Community 9 - "SketchEditor"
Cohesion: 0.03
Nodes (50): HandleHit, back, index, spline, SketchEditor, arcDrag_, arcDragMoved_, arcEndsChain_ (+42 more)

### Community 10 - "sketchFor"
Cohesion: 0.13
Nodes (11): Extrude, def_, Pipe, def_, Primitive, build_, def_, Revolve (+3 more)

### Community 11 - "optional"
Cohesion: 0.11
Nodes (3): optional, CommandRegistry::all(), Document

### Community 13 - "AnalysisSettings"
Cohesion: 0.06
Nodes (20): AnalysisKind, Accessibility, CurvatureMap, Draft, Isocurve, MinimumRadius, None, Zebra (+12 more)

### Community 14 - "Kind"
Cohesion: 0.06
Nodes (32): ConstructPlane, def_, kind_, EdgeFeature, def_, kind_, FaceFeature, def_ (+24 more)

### Community 15 - "MainWindowArrow.cpp"
Cohesion: 0.12
Nodes (8): ArrowPlacement, base, dir, edgePlacement(), facesPlacement(), MainWindow::attachArrowCompleters(), MainWindow::patternCentre(), MainWindow::pickedFaces()

### Community 16 - "CommandDialog"
Cohesion: 0.05
Nodes (31): CommandDialog, bodiesId_, bodiesLabel_, bodyInput_, buttons_, cmd_, conditional_, edgesId_ (+23 more)

### Community 17 - "Io.cpp"
Cohesion: 0.08
Nodes (25): FileFormat, Brep, Iges, Obj, Step, Stl, ThreeMF, NamedShape (+17 more)

### Community 18 - "Parser"
Cohesion: 0.19
Nodes (14): Quantity, angle, length, value, describe(), Parser, ang_, env_ (+6 more)

### Community 19 - ".setTool"
Cohesion: 0.16
Nodes (6): SketchEditor::SketchEditor(), edges, Tool, op, shape, target

### Community 21 - "Document"
Cohesion: 0.23
Nodes (5): bodyCentre(), ConstructAxisPoint, def_, kind_, storeBodies()

### Community 22 - "MainWindow.cpp"
Cohesion: 0.07
Nodes (9): commandIcon(), MainWindow::MainWindow(), qs(), run, MainWindow::beginSketch(), MainWindow::enterSketchMode(), MainWindow::exitSketchMode(), MainWindow::onEdgeClicked() (+1 more)

### Community 23 - "MainWindowTools.cpp"
Cohesion: 0.05
Nodes (30): QDialog, MainWindow::applySection(), MainWindow::checkInterference(), MainWindow::chooseUnits(), MainWindow::driveJoints(), MainWindow::editAppearance(), MainWindow::editMaterial(), MainWindow::exportDesign() (+22 more)

### Community 24 - "Affine"
Cohesion: 0.14
Nodes (13): Affine, a, b, d, e, Builder, byPlace_, k_ (+5 more)

### Community 25 - "ViewportSketch.cpp"
Cohesion: 0.08
Nodes (7): faceStyle(), lineStyle(), rgb(), Viewport::lookAt(), Viewport::planePoint(), Viewport::toWidget(), height

### Community 26 - "SketchPalette"
Cohesion: 0.05
Nodes (27): flatButton(), MainWindow::buildSketchTab(), QCheckBox, QLabel, QToolButton, QWidget, SketchEditor, SketchPalette (+19 more)

### Community 27 - ".mouseMove"
Cohesion: 0.15
Nodes (7): ext(), fixedColor(), freeColor(), lineEntity(), qc(), rgb(), wire()

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
Cohesion: 0.23
Nodes (33): KernelError, asSolid(), boolean(), chamfer(), chamferEx(), curveMiddles(), deleteFaces(), draft() (+25 more)

### Community 32 - "SketchOps.cpp"
Cohesion: 0.17
Nodes (29): at(), chainOf(), chamferCorner(), circularPattern(), copyEntities(), cornerAt(), cross(), dot() (+21 more)

### Community 33 - "ViewportArrow.cpp"
Cohesion: 0.09
Nodes (10): rgb(), segmentDistance(), Viewport::arrowAt(), Viewport::arrowParam(), Viewport::DragArrow::handle(), Viewport::dragArrowHandle(), Viewport::emitArrow(), Viewport::placeArrowBoxes() (+2 more)

### Community 34 - "ParameterCompleter"
Cohesion: 0.13
Nodes (9): QObject, ParameterCompleter, completer_, edit_, names_, ParameterCompleter::ParameterCompleter(), public, QCompleter (+1 more)

### Community 35 - "Constraint"
Cohesion: 0.08
Nodes (20): Constraint, driven, entities, expression, hasLabel, labelX, labelY, name (+12 more)

### Community 36 - "DocCommands.cpp"
Cohesion: 0.10
Nodes (30): axisOf(), CopyFn, differenceOrNull(), evaluateDimensions(), HoleSize, modeled, pitch, radius (+22 more)

### Community 38 - "solve"
Cohesion: 0.11
Nodes (15): set, addConstraintChecked(), Layout, n, px, py, rad, makeLayout() (+7 more)

### Community 39 - "Snap"
Cohesion: 0.11
Nodes (18): Snap, alignX, alignY, bodyArc, bodySegment, entity, fromX, fromY (+10 more)

### Community 41 - "ConstraintType"
Cohesion: 0.08
Nodes (25): ConstraintType, Angle, Coincident, Collinear, Concentric, Diameter, Distance, Equal (+17 more)

### Community 42 - "TsrModule.cpp"
Cohesion: 0.09
Nodes (16): Application, bindAdsk(), BRepBodies, BRepBody, index, Component, Design, Product (+8 more)

### Community 43 - "Pick"
Cohesion: 0.11
Nodes (17): Hit, index, kind, Pick, bodyArc, bodyPoint, bodySegment, hit (+9 more)

### Community 44 - "SketchEditor.cpp"
Cohesion: 0.13
Nodes (4): angleInArc(), ccwContains(), circumcircle(), segDistance()

### Community 45 - "string"
Cohesion: 0.10
Nodes (23): bodyNumber(), Document::axisFrame(), Document::bodyShapes(), Document::evaluate(), Document::nameFeatureParameters(), Document::nextAxisName(), Document::nextBodyName(), Document::nextComponentName() (+15 more)

### Community 46 - "Zip.cpp"
Cohesion: 0.20
Nodes (13): Entry, data, name, ZipError, crc32(), deflateRaw(), get16(), get32() (+5 more)

### Community 47 - "AnalysisSettings"
Cohesion: 0.10
Nodes (16): DragArrow, base, dir, radius, ref, ring, value, PendingLook (+8 more)

### Community 48 - "Sketch.cpp"
Cohesion: 0.07
Nodes (20): SketchError, SplineKind, Conic, Control, Fit, entityTypeName(), isDimension(), Sketch::addConstraint() (+12 more)

### Community 49 - "ParamSet"
Cohesion: 0.10
Nodes (32): ConstructionPlane, name, spec, NamedView, eye, name, size, target (+24 more)

### Community 50 - "MainWindowSketch.cpp"
Cohesion: 0.08
Nodes (12): MainWindow::cancelSketch(), MainWindow::editSketch(), MainWindow::finishSketch(), MainWindow::onProfileClicked(), MainWindow::originalShape(), MainWindow::sketchPalette(), MainWindow::sketchVisible(), MainWindow::startSketch() (+4 more)

### Community 51 - "InputDef"
Cohesion: 0.09
Nodes (21): InputDef, choices, defaultValue, id, label, max, min, minExclusive (+13 more)

### Community 52 - "string"
Cohesion: 0.08
Nodes (24): checkBody(), checkPattern(), CircularPattern, def_, Hole, def_, jointOrigin(), JointPick (+16 more)

### Community 54 - "UserParameter"
Cohesion: 0.33
Nodes (6): UserParameter, comment, expression, name, unit, value

### Community 55 - "Document::recompute"
Cohesion: 0.20
Nodes (6): Document::expressionEnv(), Document::openTransaction(), Document::recompute(), Document::recordFeature(), Document::setFeatureInputs(), toJson()

### Community 56 - "MarkingMenu.cpp"
Cohesion: 0.09
Nodes (14): MarkingMenu::keyPressEvent(), MarkingMenu::MarkingMenu(), MarkingMenu::paintEvent(), MarkingMenu::popupAt(), MarkingMenu::ringIndexAt(), MarkingMenu::run(), MarkingMenu::triggerForTest(), MetricSize (+6 more)

### Community 57 - "TsrModule.cpp"
Cohesion: 0.29
Nodes (4): bindTsr(), fromPy(), toPy(), typeName()

### Community 58 - "Entity"
Cohesion: 0.08
Nodes (20): Entity, a, b, center, construction, fit, handles, included (+12 more)

### Community 59 - "xdrive.py"
Cohesion: 0.28
Nodes (15): button(), canvas(), click(), drag(), flush(), geometry(), key(), keycode() (+7 more)

### Community 61 - "SketchGeometry.cpp"
Cohesion: 0.07
Nodes (21): Point, x, y, z, Profile, area, face, x (+13 more)

### Community 62 - "Session"
Cohesion: 0.07
Nodes (7): PythonHost::PythonHost(), Session, commands_, doc_, listeners_, nextListener_, path_

### Community 63 - "Theme.cpp"
Cohesion: 0.19
Nodes (6): setIconTheme(), darkColors(), darkPalette(), darkStyleSheet(), lightColors(), lightStyleSheet()

### Community 64 - "BodyFrame"
Cohesion: 0.17
Nodes (21): completeEdgeReferences(), completeFaceReferences(), decode(), decodeFaces(), edgeReference(), encode(), encodeFace(), faceReference() (+13 more)

### Community 65 - "CommandRegistry"
Cohesion: 0.12
Nodes (4): CommandRegistry, cmds_, CommandRegistry::add(), TEST()

### Community 66 - "TEST"
Cohesion: 0.09
Nodes (3): param(), TEST(), tmp()

### Community 67 - "BodyFrame"
Cohesion: 0.14
Nodes (13): BodyFrame, diag, dx, dy, dz, x0, y0, z0 (+5 more)

### Community 68 - "Theme"
Cohesion: 0.22
Nodes (4): Theme, colors_, public, styled_

### Community 69 - "PlaneEdges"
Cohesion: 0.16
Nodes (5): PlaneEdges, arcs, curves, segments, vertices

### Community 70 - "Expression.cpp"
Cohesion: 0.19
Nodes (14): ExpressionEnv, lengthUnit, lookup, ExpressionError, evaluateExpression(), evaluateQuantity(), expressionReferences(), isConstantName() (+6 more)

### Community 71 - "ParametersDialog.cpp"
Cohesion: 0.09
Nodes (16): number(), ParametersDialog, building_, error_, filter_, listener_, ParametersDialog::ParametersDialog(), public (+8 more)

### Community 72 - "Kernel.h"
Cohesion: 0.10
Nodes (19): Axis, X, Y, Z, BooleanOp, Cut, Intersect, Join (+11 more)

### Community 73 - "ViewportAnalysis.cpp"
Cohesion: 0.12
Nodes (6): packed(), ramp(), shade(), Viewport::buildAnalysis(), Viewport::setCurvatureComb(), f

### Community 74 - "Kind"
Cohesion: 0.09
Nodes (21): HudField, edit, editing, kind, locked, value, Kind, Angle (+13 more)

### Community 75 - "InputType"
Cohesion: 0.12
Nodes (17): InputType, Axis, Bodies, Body, Bool, Choice, Edges, Faces (+9 more)

### Community 76 - "Vec3"
Cohesion: 0.17
Nodes (19): SurfacePoint, normal, point, Vec3, boundingBox(), edgeMidpoint(), edgesNear(), frame() (+11 more)

### Community 77 - "CommandDialog::CommandDialog"
Cohesion: 0.14
Nodes (7): CommandDialog::CommandDialog(), formatNumber(), Dimension, Angle, Length, Unitless, dimensionOf()

### Community 79 - "ExpressionSpinBox"
Cohesion: 0.17
Nodes (4): ExpressionSpinBox, eval_, expression_, shown_

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
Cohesion: 0.12
Nodes (13): debug(), error(), info(), Level, Debug, Error, Info, Warning (+5 more)

### Community 86 - "README.md"
Cohesion: 0.11
Nodes (15): Build, Conventions, Development, Tests, Reference parts, Fusion feature checklist, Roadmap, Contents (+7 more)

### Community 87 - "Document.cpp"
Cohesion: 0.07
Nodes (40): DocumentError, PhysicalMaterial, color, density, name, checkViewName(), Document::abortTransaction(), Document::addBody() (+32 more)

### Community 89 - "rect"
Cohesion: 0.18
Nodes (7): SelectionBox, crossing, Session::notifyChanged(), Rect, rect(), l, p

### Community 90 - "Unit"
Cohesion: 0.16
Nodes (14): MainWindow::lengthUnit(), Unit, Centimeter, Degree, Foot, Inch, Meter, Millimeter (+6 more)

### Community 91 - "QTimer"
Cohesion: 0.15
Nodes (3): QTimer, Viewport::rebuildArrow(), Viewport::selectArrowValue()

### Community 92 - "FormatInfo"
Cohesion: 0.40
Nodes (5): FormatInfo, canImport, extensions, format, name

### Community 93 - "Known differences still to build"
Cohesion: 0.15
Nodes (12): Data and files, Findings from the videos, Fusion study list, Interface, Known differences still to build, Navigation and display, Selection and the canvas, Sketch (+4 more)

### Community 94 - "TEST"
Cohesion: 0.18
Nodes (3): slurp(), TEST(), tmp()

### Community 95 - "ReplayStep"
Cohesion: 0.04
Nodes (44): Body, color, display, material, name, shape, Component, bodies (+36 more)

### Community 96 - "SketchRecord"
Cohesion: 0.13
Nodes (11): SketchRecord, data, name, offset, plane, Document::reevaluateParameters(), Document::replayContext(), Document::setSketch() (+3 more)

### Community 97 - "UiCommand"
Cohesion: 0.18
Nodes (9): UiCommand, enabled, icon, id, name, panel, shortcut, tab (+1 more)

### Community 98 - "FakeDoc"
Cohesion: 0.17
Nodes (6): FakeDoc, aborts, commits, items, open, snapshot

### Community 99 - "ModelParameter"
Cohesion: 0.13
Nodes (13): ModelParameter, angle, expression, input, label, name, owner, unit (+5 more)

### Community 100 - "TEST"
Cohesion: 0.27
Nodes (3): env(), mm(), TEST()

### Community 102 - "sstream"
Cohesion: 0.17
Nodes (5): doc_(), Document::Document(), Document::ocafBytes(), ocafApplication(), Document::load()

### Community 104 - "BoundingBox"
Cohesion: 0.09
Nodes (21): BoundingBox, max, min, dot(), EdgeSig, full, normals, point (+13 more)

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
Cohesion: 0.17
Nodes (17): Section, Circular, Square, Triangular, TopologyCounts, edges, faces, shells (+9 more)

### Community 111 - "Column"
Cohesion: 0.25
Nodes (8): Column, kComment, kExpression, kName, kParameter, kStar, kUnit, kValue

### Community 112 - ".redrawAll"
Cohesion: 0.11
Nodes (9): keys(), NavPreset, Fusion, SolidWorks, Tinkercad, Viewport::Viewport(), Viewport::clearDragArrow(), Viewport::clearSecondArrow() (+1 more)

### Community 114 - "uninstall.sh"
Cohesion: 0.52
Nodes (6): die(), manifest_for(), refresh(), uninstall.sh script, step(), usage()

### Community 115 - "install.sh"
Cohesion: 0.60
Nodes (5): die(), refresh(), install.sh script, step(), usage()

### Community 116 - "TestFramework.h"
Cohesion: 0.12
Nodes (12): Result, error, ok, output, captured(), PYBIND11_EMBEDDED_MODULE(), PythonHost::exec(), PythonHost::runScript() (+4 more)

### Community 117 - ".rebuild"
Cohesion: 0.10
Nodes (12): hiddenColour(), qc(), rgb(), sharpEdges(), Style, Shaded, ShadedEdges, ShadedHidden (+4 more)

### Community 118 - "MarkingMenu"
Cohesion: 0.40
Nodes (3): MarkingMenu, enabled, public

### Community 121 - "EntityType"
Cohesion: 0.29
Nodes (7): EntityType, Arc, Circle, Ellipse, Line, Spline, isRound()

### Community 123 - "Placement"
Cohesion: 0.25
Nodes (7): Placement, angle, cx, cy, dx, dy, scale

### Community 124 - "ChainSegment"
Cohesion: 0.67
Nodes (3): ChainSegment, entity, forward

### Community 126 - "Known gaps"
Cohesion: 0.33
Nodes (5): Include 3D Geometry, Known gaps, Sketch text, Splines and conics, Visual styles

### Community 127 - "Architecture"
Cohesion: 0.40
Nodes (4): Architecture, How a command works, The document, Units

### Community 128 - ".updatePreview"
Cohesion: 0.07
Nodes (11): Sketch, constraints, entities, points, texts, Sketch::addCircle(), Sketch::addConic(), Sketch::addEllipticalArc() (+3 more)

### Community 129 - "Joint"
Cohesion: 0.21
Nodes (5): Joint, asBuilt_, def_, Sweep, def_

### Community 142 - "SplineHandle"
Cohesion: 0.29
Nodes (7): SplineHandle, arm, index, tx, ty, x, y

## Knowledge Gaps
- **775 isolated node(s):** `ok`, `output`, `error`, `isReal`, `real` (+770 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 1443 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **24 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `optional` connect `optional` to `Viewport`, `MainWindow`, `sketchFor`, `Kernel.cpp`, `AnalysisSettings`, `MainWindowArrow.cpp`, `Io.cpp`, `Parser`, `ViewportSketch.cpp`, `SketchOps.cpp`, `ViewportArrow.cpp`, `Constraint`, `DocCommands.cpp`, `CommandDialog.cpp`, `SketchEditor.cpp`, `string`, `AnalysisSettings`, `ParamSet`, `InputDef`, `Entity`, `Session`, `Expression.cpp`, `Kernel.h`, `Vec3`, `CommandDialog::CommandDialog`, `ExpressionSpinBox`, `SketchCurves.cpp`, `QString`, `Document.cpp`, `Unit`, `ReplayStep`, `SketchRecord`?**
  _High betweenness centrality (0.107) - this node is a cross-community bridge._
- **What connects `ok`, `output`, `error` to the rest of the system?**
  _775 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Viewport` be split into smaller, more focused modules?**
  _Cohesion score 0.016117125984251968 - nodes in this community are weakly interconnected._
- **Why does `Viewport` connect `Viewport` to `ViewportArrow.cpp`, `MainWindow`, `QMouseEvent`, `Viewport.cpp`, `ViewportAnalysis.cpp`, `optional`, `AnalysisSettings`, `AnalysisSettings`, `SketchDisplay`, `.redrawAll`, `.setSelectionFilter`, `SketchCurves.cpp`, `.rebuild`, `.toPixels`, `MainWindowTools.cpp`, `rect`, `QTimer`?**
  _High betweenness centrality (0.099) - this node is a cross-community bridge._
- **Should `Icons.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.05337690631808279 - nodes in this community are weakly interconnected._
- **Why does `SketchEditor` connect `SketchEditor` to `Viewport`, `ParameterCompleter`, `Constraint`, `PlaneEdges`, `QMouseEvent`, `Snap`, `Unit`, `Kind`, `Display`, `optional`, `Pick`, `SketchEditor.cpp`, `.setTool`, `.solveAndShow`, `.eventFilter`, `Entity`, `.mouseMove`, `Session`?**
  _High betweenness centrality (0.086) - this node is a cross-community bridge._
- **Should `Session.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.06128364389233954 - nodes in this community are weakly interconnected._