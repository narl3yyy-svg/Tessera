# Graph Report - tessera  (2026-11-13)

## Corpus Check
- 386 files · ~254,395 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 56 file(s) not represented in the graph (top: .drive 48, (none) 5, .cmake 1)

## Summary
- 3705 nodes · 9487 edges · 136 communities (109 shown, 27 thin omitted)
- Extraction: 85% EXTRACTED · 15% INFERRED · 0% AMBIGUOUS · INFERRED: 1459 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `ce5ff282`
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
- sketchFor
- optional
- Kernel.cpp
- AnalysisSettings
- Kind
- .showDialog
- CommandDialog
- Io.cpp
- Unit
- MainWindowTools.cpp
- Known gaps
- Document
- MainWindow.cpp
- Architecture
- Affine
- ViewportSketch.cpp
- SketchPalette
- .redrawAll
- Inputs
- Document.cpp
- Colors
- KernelError
- SketchOps.cpp
- ViewportArrow.cpp
- ParameterCompleter
- Constraint
- DocCommands.cpp
- .openMarkingMenu
- solve
- Snap
- CommandDialog.cpp
- ConstraintType
- TsrModule.cpp
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
- MarkingMenu.cpp
- Profile
- Entity
- xdrive.py
- Session
- Theme.cpp
- BodyFrame
- CommandRegistry
- validateOperation
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
- UiCommand
- Level
- README.md
- ParamSet
- test_feature_pattern.py
- rect
- MainWindow::MainWindow
- .features
- FileFormat
- Known differences still to build
- TEST
- ReplayStep
- SketchCurves.cpp
- .setTool
- FakeDoc
- fail
- MainWindowArrow.cpp
- .add
- sstream
- MarkingMenu
- BoundingBox
- Joints
- SectionState
- Display
- main
- Kernel.h
- TopologyCounts
- QTimer
- QDialog
- cachedProfiles
- uninstall.sh
- install.sh
- TestFramework.h
- .rebuild
- Column
- Viewport::setDragArrow
- bindAdsk
- test_incremental_replay.py
- Placement
- ChainSegment
- AddUserParameter
- Icons.h
- .updatePreview
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
3. `MainWindow` - 184 edges
4. `Inputs` - 148 edges
5. `Document` - 120 edges
6. `render()` - 119 edges
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

## Communities (136 total, 27 thin omitted)

### Community 0 - "Viewport"
Cohesion: 0.02
Nodes (68): view_, QLineEdit, Viewport, analysis_, analysisObjects_, appliedGridStep_, arrowBoxes_, arrowDragging_ (+60 more)

### Community 1 - "Icons.cpp"
Cohesion: 0.05
Nodes (124): accessibilityIcon(), appearanceIcon(), arc3Icon(), arcIcon(), arcTangentIcon(), arrow(), axisIcon(), box() (+116 more)

### Community 2 - "Session.cpp"
Cohesion: 0.07
Nodes (40): CommandSession, inputs_, CommandRegistry::find(), CommandRegistry::run(), historyEdit(), OwnedCommand, owned, OwningCommandSession (+32 more)

### Community 4 - "MainWindow"
Cohesion: 0.03
Nodes (64): writeLiveGeometry(), CommandDialog, MainWindow, active_, arrowInput_, arrowInput2_, bodiesBeforeCommand_, combEdges_ (+56 more)

### Community 5 - "run_oracle.py"
Cohesion: 0.08
Nodes (54): add_point(), arc_poly(), body_at(), body_list(), build_sketch(), chain(), circumcentre(), cm() (+46 more)

### Community 6 - "Unit"
Cohesion: 0.11
Nodes (27): MainWindow::checkInterference(), MainWindow::driveJoints(), MainWindow::formatLength(), MainWindow::gridSettings(), MainWindow::lengthUnit(), MainWindow::openAnalysis(), MainWindow::openSection(), MainWindow::updateMeasure() (+19 more)

### Community 7 - "Document"
Cohesion: 0.03
Nodes (14): Document, effects_, lastReplayed_, lastReused_, modified_, pendingTools_, registry_, replaying_ (+6 more)

### Community 8 - "Viewport.cpp"
Cohesion: 0.05
Nodes (5): glide(), keys(), QKeyEvent, QtFrameBuffer, Viewport::Viewport()

### Community 9 - "SketchEditor"
Cohesion: 0.03
Nodes (50): HandleHit, back, index, spline, SketchEditor, arcDrag_, arcDragMoved_, arcEndsChain_ (+42 more)

### Community 10 - "sketchFor"
Cohesion: 0.12
Nodes (14): Extrude, def_, Pipe, def_, Revolve, def_, RibWeb, def_ (+6 more)

### Community 11 - "optional"
Cohesion: 0.09
Nodes (4): optional, isEmpty(), Value, CommandRegistry::all()

### Community 12 - "Kernel.cpp"
Cohesion: 0.04
Nodes (5): isoCoarsePitch(), massProperties(), measure(), polygonToCircleLoft(), topologyCounts()

### Community 13 - "AnalysisSettings"
Cohesion: 0.11
Nodes (18): AnalysisKind, Accessibility, CurvatureMap, Draft, Isocurve, MinimumRadius, None, Zebra (+10 more)

### Community 14 - "Kind"
Cohesion: 0.07
Nodes (26): EdgeFeature, def_, kind_, FaceFeature, def_, kind_, Kind, Angle (+18 more)

### Community 16 - "CommandDialog"
Cohesion: 0.04
Nodes (31): CommandDialog, bodiesId_, bodiesLabel_, bodyInput_, buttons_, cmd_, conditional_, edgesId_ (+23 more)

### Community 17 - "Io.cpp"
Cohesion: 0.10
Nodes (19): MainWindow::print3d(), NamedShape, compoundOf(), exportShapes(), fmt(), formatForPath(), fromBrep(), importShape() (+11 more)

### Community 18 - "Unit"
Cohesion: 0.09
Nodes (31): ExpressionEnv, lengthUnit, lookup, ExpressionError, Quantity, angle, length, value (+23 more)

### Community 19 - "MainWindowTools.cpp"
Cohesion: 0.07
Nodes (11): MainWindow::chooseUnits(), MainWindow::editAppearance(), MainWindow::editMaterial(), MainWindow::insertFile(), MainWindow::lookTargets(), MainWindow::sectionFrame(), MainWindow::sectionPlane(), MainWindow::setSelectionFilter() (+3 more)

### Community 20 - "Known gaps"
Cohesion: 0.33
Nodes (5): Include 3D Geometry, Known gaps, Sketch text, Splines and conics, Visual styles

### Community 21 - "Document"
Cohesion: 0.16
Nodes (11): ConstructAxisPoint, def_, kind_, ConstructPlane, def_, kind_, jointOrigin(), JointPick (+3 more)

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
Cohesion: 0.06
Nodes (26): flatButton(), QCheckBox, QLabel, QToolButton, QWidget, SketchEditor, SketchPalette, body_ (+18 more)

### Community 27 - ".redrawAll"
Cohesion: 0.11
Nodes (7): NavPreset, Fusion, SolidWorks, Tinkercad, Viewport::clearDragArrow(), Viewport::clearSecondArrow(), Viewport::setInteractor()

### Community 28 - "Inputs"
Cohesion: 0.08
Nodes (14): CommandContext, CommandError, Inputs, CommandSession::CommandSession(), getBool(), getInt(), bodyCentre(), bodyName() (+6 more)

### Community 29 - "Document.cpp"
Cohesion: 0.06
Nodes (55): DocumentError, bodyNumber(), checkViewName(), Document::abortTransaction(), Document::addBody(), Document::addNamedView(), Document::addUserParameter(), Document::axisFrame() (+47 more)

### Community 30 - "Colors"
Cohesion: 0.07
Nodes (28): Colors, base, border, cubeBox, cubeText, errorBackground, grid, gridMajor (+20 more)

### Community 31 - "KernelError"
Cohesion: 0.25
Nodes (28): KernelError, asSolid(), boolean(), chamfer(), chamferEx(), deleteFaces(), draft(), extrude() (+20 more)

### Community 32 - "SketchOps.cpp"
Cohesion: 0.22
Nodes (27): at(), chainOf(), chamferCorner(), circularPattern(), copyEntities(), cornerAt(), cross(), dot() (+19 more)

### Community 33 - "ViewportArrow.cpp"
Cohesion: 0.05
Nodes (18): MarkingMenu::mouseMoveEvent(), QLabel, QMouseEvent, ViewInteractor, Viewport::frontEdgeOwner(), rgb(), segmentDistance(), Viewport::arrowAt() (+10 more)

### Community 34 - "ParameterCompleter"
Cohesion: 0.13
Nodes (9): QObject, ParameterCompleter, completer_, edit_, names_, ParameterCompleter::ParameterCompleter(), public, QCompleter (+1 more)

### Community 35 - "Constraint"
Cohesion: 0.08
Nodes (20): Constraint, driven, entities, expression, hasLabel, labelX, labelY, name (+12 more)

### Community 36 - "DocCommands.cpp"
Cohesion: 0.07
Nodes (37): applyOperation(), axisOf(), checkBody(), checkPattern(), CircularPattern, def_, CopyFn, differenceOrNull() (+29 more)

### Community 37 - ".openMarkingMenu"
Cohesion: 0.10
Nodes (4): MainWindow::beginSketch(), MainWindow::buildSketchTab(), MainWindow::enterSketchMode(), MainWindow::buildUiCommands()

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
Cohesion: 0.07
Nodes (19): Application, BRepBodies, Component, Design, Product, raiseIfError(), UserParameter, name (+11 more)

### Community 43 - "Pick"
Cohesion: 0.13
Nodes (14): Pick, bodyArc, bodyPoint, bodySegment, hit, midpointOf, onEntity, onXAxis (+6 more)

### Community 44 - "SketchEditor.cpp"
Cohesion: 0.12
Nodes (4): angleInArc(), ccwContains(), circumcircle(), segDistance()

### Community 46 - "Zip.cpp"
Cohesion: 0.20
Nodes (13): Entry, data, name, ZipError, crc32(), deflateRaw(), get16(), get32() (+5 more)

### Community 47 - "AnalysisSettings"
Cohesion: 0.10
Nodes (16): DragArrow, base, dir, radius, ref, ring, value, PendingLook (+8 more)

### Community 48 - "Sketch.cpp"
Cohesion: 0.06
Nodes (29): EntityType, Arc, Circle, Ellipse, Line, Spline, isRound(), SketchError (+21 more)

### Community 49 - "ParamSet"
Cohesion: 0.09
Nodes (21): ModelParameter, angle, expression, input, label, name, owner, unit (+13 more)

### Community 50 - "MainWindowSketch.cpp"
Cohesion: 0.09
Nodes (12): MainWindow::cancelSketch(), MainWindow::editSketch(), MainWindow::finishSketch(), MainWindow::onProfileClicked(), MainWindow::originalShape(), MainWindow::sketchPalette(), MainWindow::sketchVisible(), MainWindow::startSketch() (+4 more)

### Community 51 - "InputDef"
Cohesion: 0.09
Nodes (21): InputDef, choices, defaultValue, id, label, max, min, minExclusive (+13 more)

### Community 52 - ".apply"
Cohesion: 0.26
Nodes (8): Hole, def_, HoleSize, holeSize(), modeled, pitch, radius, stringOr()

### Community 54 - "ViewportAnalysis.cpp"
Cohesion: 0.12
Nodes (6): packed(), ramp(), shade(), Viewport::buildAnalysis(), Viewport::setCurvatureComb(), f

### Community 55 - "Document::recompute"
Cohesion: 0.18
Nodes (7): Document::recompute(), Document::recordFeature(), Document::removeFeature(), Document::setFeatureInputs(), Document::setFeatureSuppressed(), featureData(), toJson()

### Community 56 - "MarkingMenu.cpp"
Cohesion: 0.09
Nodes (13): MarkingMenu::keyPressEvent(), MarkingMenu::MarkingMenu(), MarkingMenu::paintEvent(), MarkingMenu::popupAt(), MarkingMenu::ringIndexAt(), MarkingMenu::run(), MetricSize, close (+5 more)

### Community 57 - "Profile"
Cohesion: 0.33
Nodes (5): Profile, area, face, x, y

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
Cohesion: 0.10
Nodes (31): completeEdgeReferences(), completeFaceReferences(), decode(), decodeFaces(), dot(), edgeReference(), EdgeSig, full (+23 more)

### Community 65 - "CommandRegistry"
Cohesion: 0.12
Nodes (4): CommandRegistry, cmds_, CommandRegistry::add(), TEST()

### Community 66 - "validateOperation"
Cohesion: 0.16
Nodes (8): Coil, def_, Primitive, build_, def_, Sweep, def_, validateOperation()

### Community 67 - "BodyFrame"
Cohesion: 0.14
Nodes (15): BodyFrame, diag, dx, dy, dz, x0, y0, z0 (+7 more)

### Community 68 - "Theme"
Cohesion: 0.22
Nodes (4): Theme, colors_, public, styled_

### Community 69 - "PlaneEdges"
Cohesion: 0.17
Nodes (5): PlaneEdges, arcs, curves, segments, vertices

### Community 70 - "Command.cpp"
Cohesion: 0.18
Nodes (13): expressionKey(), checkInputValue(), CommandContext::evaluateExpression(), CommandDef::input(), CommandSession::applyInTransaction(), CommandSession::cancel(), CommandSession::execute(), CommandSession::preview() (+5 more)

### Community 71 - "ParametersDialog.cpp"
Cohesion: 0.08
Nodes (16): number(), ParametersDialog, building_, error_, filter_, listener_, ParametersDialog::ParametersDialog(), public (+8 more)

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
Cohesion: 0.18
Nodes (20): SurfacePoint, normal, point, Vec3, boundingBox(), edgeMidpoint(), edgesNear(), frame() (+12 more)

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
Cohesion: 0.05
Nodes (46): Adding a tool, Command, CommandDef, feature, icon, id, inputs, name (+38 more)

### Community 82 - "Measurement"
Cohesion: 0.13
Nodes (14): Kind, Angle, Area, Length, Volume, Measurement, from, hasLine (+6 more)

### Community 83 - "SketchCurves.cpp"
Cohesion: 0.17
Nodes (17): crossings(), crossingsOf(), Curve2d, curve2d(), periodic, t0, t1, endIsFree() (+9 more)

### Community 84 - "UiCommand"
Cohesion: 0.13
Nodes (12): UiCommand, enabled, icon, id, name, panel, run, shortcut (+4 more)

### Community 85 - "Level"
Cohesion: 0.16
Nodes (13): debug(), error(), info(), Level, Debug, Error, Info, Warning (+5 more)

### Community 86 - "README.md"
Cohesion: 0.11
Nodes (15): Build, Conventions, Development, Tests, Reference parts, Fusion feature checklist, Roadmap, Contents (+7 more)

### Community 87 - "ParamSet"
Cohesion: 0.09
Nodes (29): ConstructionPlane, name, spec, NamedView, eye, name, size, target (+21 more)

### Community 90 - "MainWindow::MainWindow"
Cohesion: 0.13
Nodes (4): PythonHost, MainWindow::MainWindow(), MainWindow::exitSketchMode(), MainWindow::showPreferences()

### Community 91 - ".features"
Cohesion: 0.15
Nodes (10): Document::nextAxisName(), Document::nextComponentName(), Document::nextDimensionName(), Document::nextPlaneName(), Document::nextPointName(), Document::nextSketchName(), Document::parameterUsers(), Document::reevaluateParameters() (+2 more)

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
Cohesion: 0.03
Nodes (57): Body, color, display, material, name, shape, Component, bodies (+49 more)

### Community 97 - ".setTool"
Cohesion: 0.15
Nodes (5): Hit, index, kind, SketchEditor::SketchEditor(), edges

### Community 98 - "FakeDoc"
Cohesion: 0.17
Nodes (6): FakeDoc, aborts, commits, items, open, snapshot

### Community 100 - "MainWindowArrow.cpp"
Cohesion: 0.13
Nodes (8): ArrowPlacement, base, dir, edgePlacement(), facesPlacement(), MainWindow::attachArrowCompleters(), MainWindow::patternCentre(), MainWindow::pickedFaces()

### Community 102 - "sstream"
Cohesion: 0.17
Nodes (5): doc_(), Document::Document(), Document::ocafBytes(), ocafApplication(), Document::load()

### Community 103 - "MarkingMenu"
Cohesion: 0.40
Nodes (3): MarkingMenu, enabled, public

### Community 104 - "BoundingBox"
Cohesion: 0.24
Nodes (13): BoundingBox, max, min, WallSide, Center, Side1, Side2, extendedWire() (+5 more)

### Community 106 - "SectionState"
Cohesion: 0.25
Nodes (7): SectionState, active, angle, flip, offset, plane, visible

### Community 107 - "Display"
Cohesion: 0.25
Nodes (7): Display, constraints, construction, dimensions, points, profiles, projected

### Community 108 - "main"
Cohesion: 0.31
Nodes (5): listCommands(), main(), usage(), main(), smoke()

### Community 109 - "Kernel.h"
Cohesion: 0.10
Nodes (19): Axis, X, Y, Z, BooleanOp, Cut, Intersect, Join (+11 more)

### Community 110 - "TopologyCounts"
Cohesion: 0.17
Nodes (17): Section, Circular, Square, Triangular, TopologyCounts, edges, faces, shells (+9 more)

### Community 112 - "QDialog"
Cohesion: 0.18
Nodes (5): QDialog, MainWindow::exportDesign(), MainWindow::measurePick(), MainWindow::openMeasure(), toolWindow()

### Community 113 - "cachedProfiles"
Cohesion: 0.20
Nodes (3): MainWindow::updateDragArrow(), cachedProfiles(), keyOf()

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

### Community 118 - "Column"
Cohesion: 0.25
Nodes (8): Column, kComment, kExpression, kName, kParameter, kStar, kUnit, kValue

### Community 120 - "Viewport::setDragArrow"
Cohesion: 0.18
Nodes (4): Viewport::DragArrow::handle(), Viewport::emitArrow(), Viewport::setDragArrow(), Viewport::setDragRing()

### Community 121 - "bindAdsk"
Cohesion: 0.29
Nodes (3): bindAdsk(), BRepBody, index

### Community 123 - "Placement"
Cohesion: 0.25
Nodes (7): Placement, angle, cx, cy, dx, dy, scale

### Community 124 - "ChainSegment"
Cohesion: 0.30
Nodes (4): ChainSegment, entity, forward, Placement::apply()

### Community 128 - ".updatePreview"
Cohesion: 0.06
Nodes (24): ext(), fixedColor(), freeColor(), lineEntity(), qc(), rgb(), wire(), Sketch (+16 more)

### Community 141 - "Point"
Cohesion: 0.52
Nodes (6): Point, x, y, z, customPlaneSpec(), toDxf()

### Community 142 - "SplineHandle"
Cohesion: 0.29
Nodes (7): SplineHandle, arm, index, tx, ty, x, y

## Knowledge Gaps
- **769 isolated node(s):** `ok`, `output`, `error`, `isReal`, `real` (+764 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 1438 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **27 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `optional` connect `optional` to `Viewport`, `MainWindow`, `Unit`, `sketchFor`, `Kernel.cpp`, `Io.cpp`, `Unit`, `ViewportSketch.cpp`, `Document.cpp`, `SketchOps.cpp`, `ViewportArrow.cpp`, `Constraint`, `DocCommands.cpp`, `CommandDialog.cpp`, `SketchEditor.cpp`, `AnalysisSettings`, `ParamSet`, `InputDef`, `Entity`, `Session`, `Vec3`, `dimensionOf`, `ExpressionSpinBox`, `SketchCurves.cpp`, `ParamSet`, `ReplayStep`, `SketchCurves.cpp`, `MainWindowArrow.cpp`, `Kernel.h`?**
  _High betweenness centrality (0.109) - this node is a cross-community bridge._
- **What connects `ok`, `output`, `error` to the rest of the system?**
  _769 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Viewport` be split into smaller, more focused modules?**
  _Cohesion score 0.01624015748031496 - nodes in this community are weakly interconnected._
- **Why does `Viewport` connect `Viewport` to `ViewportArrow.cpp`, `MainWindow`, `Unit`, `Viewport.cpp`, `TsrModule.cpp`, `optional`, `AnalysisSettings`, `AnalysisSettings`, `SketchDisplay`, `QTimer`, `SketchCurves.cpp`, `.rebuild`, `.toPixels`, `ViewportAnalysis.cpp`, `Viewport::setDragArrow`, `rect`, `.redrawAll`?**
  _High betweenness centrality (0.093) - this node is a cross-community bridge._
- **Should `Icons.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.05337690631808279 - nodes in this community are weakly interconnected._
- **Why does `SketchEditor` connect `SketchEditor` to `.updatePreview`, `.setTool`, `ParameterCompleter`, `Constraint`, `Viewport`, `PlaneEdges`, `ViewportArrow.cpp`, `Snap`, `Unit`, `Kind`, `Display`, `optional`, `Pick`, `SketchEditor.cpp`, `Entity`, `Session`, `ReplayStep`?**
  _High betweenness centrality (0.087) - this node is a cross-community bridge._
- **Should `Session.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.06954997077732321 - nodes in this community are weakly interconnected._