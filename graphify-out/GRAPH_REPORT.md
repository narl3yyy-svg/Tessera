# Graph Report - tessera  (2026-11-13)

## Corpus Check
- 386 files · ~253,344 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 56 file(s) not represented in the graph (top: .drive 48, (none) 5, .cmake 1)

## Summary
- 3698 nodes · 9469 edges · 131 communities (105 shown, 26 thin omitted)
- Extraction: 85% EXTRACTED · 15% INFERRED · 0% AMBIGUOUS · INFERRED: 1457 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `30f969d4`
- Run `git rev-parse HEAD` and compare to check if the graph is stale.
- Run `graphify update .` after code changes (no API cost).

## Community Hubs (Navigation)
- Viewport
- Icons.cpp
- Session.cpp
- tsr
- MainWindow
- run_oracle.py
- Feature
- Document
- Viewport.cpp
- SketchEditor
- sketchFor
- optional
- Kernel.cpp
- AnalysisSettings
- Kind
- Viewport.h
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
- string
- Colors
- KernelError
- SketchOps.cpp
- ViewportArrow.cpp
- ParameterCompleter
- Constraint
- DocCommands.cpp
- NamedView
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
- Text
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
- ParametersDialog.cpp
- TEST
- curve
- Kind
- InputType
- Vec3
- Dimension
- CommandDialog::CommandDialog
- SketchDisplay
- Command
- Measurement
- SketchCurves.cpp
- UiCommand
- Level
- README.md
- string
- test_feature_pattern.py
- rect
- UserParameter
- EntityType
- FileFormat
- Known differences still to build
- TEST
- ReplayStep
- Value.h
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
- uninstall.sh
- install.sh
- TestFramework.h
- .rebuild
- Column
- test_incremental_replay.py
- Placement
- ChainSegment
- AddUserParameter
- .updatePreview
- Placement::apply
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
6. `render()` - 118 edges
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

## Communities (131 total, 26 thin omitted)

### Community 0 - "Viewport"
Cohesion: 0.02
Nodes (68): view_, QLineEdit, Viewport, analysis_, analysisObjects_, appliedGridStep_, arrowBoxes_, arrowDragging_ (+60 more)

### Community 1 - "Icons.cpp"
Cohesion: 0.05
Nodes (123): accessibilityIcon(), appearanceIcon(), arc3Icon(), arcIcon(), arcTangentIcon(), arrow(), axisIcon(), box() (+115 more)

### Community 2 - "Session.cpp"
Cohesion: 0.06
Nodes (49): CommandSession, inputs_, expressionKey(), checkInputValue(), CommandContext::evaluateExpression(), CommandDef::input(), CommandSession::applyInTransaction(), CommandSession::cancel() (+41 more)

### Community 4 - "MainWindow"
Cohesion: 0.03
Nodes (65): CommandDialog, MainWindow, active_, arrowInput_, arrowInput2_, bodiesBeforeCommand_, combEdges_, combPicking_ (+57 more)

### Community 5 - "run_oracle.py"
Cohesion: 0.08
Nodes (54): add_point(), arc_poly(), body_at(), body_list(), build_sketch(), chain(), circumcentre(), cm() (+46 more)

### Community 6 - "Feature"
Cohesion: 0.17
Nodes (10): Feature, commandId, error, id, inputs, name, parameterNames, rolledBack (+2 more)

### Community 7 - "Document"
Cohesion: 0.03
Nodes (15): Document, effects_, lastReplayed_, lastReused_, modified_, pendingTools_, registry_, replaying_ (+7 more)

### Community 9 - "SketchEditor"
Cohesion: 0.03
Nodes (54): HandleHit, back, index, spline, SketchEditor, arcDrag_, arcDragMoved_, arcEndsChain_ (+46 more)

### Community 10 - "sketchFor"
Cohesion: 0.12
Nodes (14): Extrude, def_, Pipe, def_, Revolve, def_, RibWeb, def_ (+6 more)

### Community 12 - "Kernel.cpp"
Cohesion: 0.04
Nodes (5): isoCoarsePitch(), massProperties(), measure(), polygonToCircleLoft(), topologyCounts()

### Community 13 - "AnalysisSettings"
Cohesion: 0.11
Nodes (18): AnalysisKind, Accessibility, CurvatureMap, Draft, Isocurve, MinimumRadius, None, Zebra (+10 more)

### Community 14 - "Kind"
Cohesion: 0.07
Nodes (26): EdgeFeature, def_, kind_, FaceFeature, def_, kind_, Kind, Angle (+18 more)

### Community 15 - "Viewport.h"
Cohesion: 0.08
Nodes (5): MarkingMenu::mouseMoveEvent(), QKeyEvent, QLabel, QMouseEvent, ViewInteractor

### Community 16 - "CommandDialog"
Cohesion: 0.05
Nodes (31): CommandDialog, bodiesId_, bodiesLabel_, bodyInput_, buttons_, cmd_, conditional_, edgesId_ (+23 more)

### Community 17 - "Io.cpp"
Cohesion: 0.10
Nodes (19): MainWindow::print3d(), NamedShape, compoundOf(), exportShapes(), fmt(), formatForPath(), fromBrep(), importShape() (+11 more)

### Community 18 - "Unit"
Cohesion: 0.07
Nodes (45): MainWindow::lengthUnit(), ExpressionEnv, lengthUnit, lookup, ExpressionError, Quantity, angle, length (+37 more)

### Community 19 - "MainWindowTools.cpp"
Cohesion: 0.05
Nodes (30): QDialog, MainWindow::applySection(), MainWindow::checkInterference(), MainWindow::chooseUnits(), MainWindow::driveJoints(), MainWindow::editAppearance(), MainWindow::editMaterial(), MainWindow::exportDesign() (+22 more)

### Community 20 - "Known gaps"
Cohesion: 0.33
Nodes (5): Include 3D Geometry, Known gaps, Sketch text, Splines and conics, Visual styles

### Community 21 - "Document"
Cohesion: 0.16
Nodes (11): ConstructAxisPoint, def_, kind_, ConstructPlane, def_, kind_, jointOrigin(), JointPick (+3 more)

### Community 22 - "MainWindow.cpp"
Cohesion: 0.04
Nodes (10): PythonHost, commandIcon(), MainWindow::MainWindow(), qs(), MainWindow::beginSketch(), MainWindow::enterSketchMode(), MainWindow::exitSketchMode(), MainWindow::onEdgeClicked() (+2 more)

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
Cohesion: 0.05
Nodes (27): flatButton(), MainWindow::buildSketchTab(), QCheckBox, QLabel, QToolButton, QWidget, SketchEditor, SketchPalette (+19 more)

### Community 27 - ".redrawAll"
Cohesion: 0.11
Nodes (9): keys(), NavPreset, Fusion, SolidWorks, Tinkercad, Viewport::Viewport(), Viewport::clearDragArrow(), Viewport::clearSecondArrow() (+1 more)

### Community 28 - "Inputs"
Cohesion: 0.08
Nodes (14): CommandContext, CommandError, Inputs, CommandSession::CommandSession(), getBool(), getInt(), bodyCentre(), bodyName() (+6 more)

### Community 29 - "string"
Cohesion: 0.09
Nodes (30): DocumentError, PhysicalMaterial, color, density, name, checkViewName(), Document::abortTransaction(), Document::addBody() (+22 more)

### Community 30 - "Colors"
Cohesion: 0.07
Nodes (28): Colors, base, border, cubeBox, cubeText, errorBackground, grid, gridMajor (+20 more)

### Community 31 - "KernelError"
Cohesion: 0.25
Nodes (28): KernelError, asSolid(), boolean(), chamfer(), chamferEx(), deleteFaces(), draft(), extrude() (+20 more)

### Community 32 - "SketchOps.cpp"
Cohesion: 0.23
Nodes (26): at(), chainOf(), chamferCorner(), circularPattern(), copyEntities(), cornerAt(), cross(), dot() (+18 more)

### Community 33 - "ViewportArrow.cpp"
Cohesion: 0.07
Nodes (18): Viewport::frontEdgeOwner(), rgb(), segmentDistance(), Viewport::arrowAt(), Viewport::arrowMouseMove(), Viewport::arrowMousePress(), Viewport::arrowMouseRelease(), Viewport::arrowParam() (+10 more)

### Community 34 - "ParameterCompleter"
Cohesion: 0.09
Nodes (11): QObject, ParameterCompleter, completer_, edit_, names_, ParameterCompleter::ParameterCompleter(), public, QCompleter (+3 more)

### Community 35 - "Constraint"
Cohesion: 0.08
Nodes (21): Constraint, driven, entities, expression, hasLabel, labelX, labelY, name (+13 more)

### Community 36 - "DocCommands.cpp"
Cohesion: 0.07
Nodes (37): applyOperation(), axisOf(), checkBody(), checkPattern(), CircularPattern, def_, CopyFn, differenceOrNull() (+29 more)

### Community 37 - "NamedView"
Cohesion: 0.12
Nodes (15): NamedView, eye, name, size, target, up, Document::bodyShapes(), Document::effectOf() (+7 more)

### Community 38 - "solve"
Cohesion: 0.18
Nodes (13): set, addConstraintChecked(), Layout, n, px, py, rad, makeLayout() (+5 more)

### Community 39 - "Snap"
Cohesion: 0.11
Nodes (18): Snap, alignX, alignY, bodyArc, bodySegment, entity, fromX, fromY (+10 more)

### Community 41 - "ConstraintType"
Cohesion: 0.08
Nodes (24): ConstraintType, Angle, Coincident, Collinear, Concentric, Diameter, Distance, Equal (+16 more)

### Community 42 - "TsrModule.cpp"
Cohesion: 0.06
Nodes (21): Application, bindAdsk(), BRepBodies, BRepBody, index, Component, Design, Product (+13 more)

### Community 43 - "Pick"
Cohesion: 0.09
Nodes (17): Hit, index, kind, Pick, bodyArc, bodyPoint, bodySegment, hit (+9 more)

### Community 46 - "Zip.cpp"
Cohesion: 0.20
Nodes (11): Entry, data, name, ZipError, crc32(), get16(), get32(), put16() (+3 more)

### Community 47 - "AnalysisSettings"
Cohesion: 0.10
Nodes (16): DragArrow, base, dir, radius, ref, ring, value, PendingLook (+8 more)

### Community 48 - "Sketch.cpp"
Cohesion: 0.08
Nodes (19): SketchError, SplineKind, Conic, Control, Fit, entityTypeName(), isDimension(), Sketch::addSpline() (+11 more)

### Community 49 - "ParamSet"
Cohesion: 0.07
Nodes (35): ModelParameter, angle, expression, input, label, name, owner, unit (+27 more)

### Community 50 - "MainWindowSketch.cpp"
Cohesion: 0.06
Nodes (17): MainWindow::cancelSketch(), MainWindow::editSketch(), MainWindow::finishSketch(), MainWindow::onProfileClicked(), MainWindow::originalShape(), MainWindow::sketchPalette(), MainWindow::sketchVisible(), MainWindow::startSketch() (+9 more)

### Community 51 - "InputDef"
Cohesion: 0.09
Nodes (21): InputDef, choices, defaultValue, id, label, max, min, minExclusive (+13 more)

### Community 52 - ".apply"
Cohesion: 0.26
Nodes (8): Hole, def_, HoleSize, holeSize(), modeled, pitch, radius, stringOr()

### Community 54 - "ViewportAnalysis.cpp"
Cohesion: 0.11
Nodes (6): packed(), ramp(), shade(), Viewport::buildAnalysis(), Viewport::setCurvatureComb(), f

### Community 55 - "Document::recompute"
Cohesion: 0.18
Nodes (8): Document::expressionEnv(), Document::recompute(), Document::recordFeature(), Document::removeFeature(), Document::setFeatureInputs(), Document::setFeatureSuppressed(), featureData(), toJson()

### Community 56 - "Text"
Cohesion: 0.12
Nodes (9): Text, angle, corner, flip, font, hAlign, point, text (+1 more)

### Community 57 - "Profile"
Cohesion: 0.33
Nodes (5): Profile, area, face, x, y

### Community 58 - "Entity"
Cohesion: 0.12
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
Cohesion: 0.15
Nodes (5): PlaneEdges, arcs, curves, segments, vertices

### Community 71 - "ParametersDialog.cpp"
Cohesion: 0.09
Nodes (16): number(), ParametersDialog, building_, error_, filter_, listener_, ParametersDialog::ParametersDialog(), public (+8 more)

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
Cohesion: 0.18
Nodes (20): SurfacePoint, normal, point, Vec3, boundingBox(), edgeMidpoint(), edgesNear(), frame() (+12 more)

### Community 77 - "Dimension"
Cohesion: 0.50
Nodes (4): Dimension, Angle, Length, Unitless

### Community 79 - "CommandDialog::CommandDialog"
Cohesion: 0.11
Nodes (6): ExpressionSpinBox, eval_, expression_, shown_, formatNumber(), dimensionOf()

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
Cohesion: 0.11
Nodes (18): crossings(), crossingsOf(), Curve2d, curve2d(), periodic, t0, t1, endIsFree() (+10 more)

### Community 84 - "UiCommand"
Cohesion: 0.07
Nodes (22): UiCommand, enabled, icon, id, name, panel, run, shortcut (+14 more)

### Community 85 - "Level"
Cohesion: 0.16
Nodes (13): debug(), error(), info(), Level, Debug, Error, Info, Warning (+5 more)

### Community 86 - "README.md"
Cohesion: 0.11
Nodes (15): Build, Conventions, Development, Tests, Reference parts, Fusion feature checklist, Roadmap, Contents (+7 more)

### Community 87 - "string"
Cohesion: 0.07
Nodes (37): ConstructionPlane, name, spec, bodyNumber(), Document::axisFrame(), Document::bodies(), Document::body(), Document::bodyName() (+29 more)

### Community 89 - "rect"
Cohesion: 0.28
Nodes (3): SelectionBox, crossing, rect()

### Community 90 - "UserParameter"
Cohesion: 0.33
Nodes (6): UserParameter, comment, expression, name, unit, value

### Community 91 - "EntityType"
Cohesion: 0.29
Nodes (7): EntityType, Arc, Circle, Ellipse, Line, Spline, isRound()

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
Cohesion: 0.06
Nodes (34): Body, color, display, material, name, shape, Component, bodies (+26 more)

### Community 98 - "FakeDoc"
Cohesion: 0.17
Nodes (6): FakeDoc, aborts, commits, items, open, snapshot

### Community 100 - "MainWindowArrow.cpp"
Cohesion: 0.12
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
Cohesion: 0.27
Nodes (6): listCommands(), main(), usage(), main(), smoke(), key

### Community 109 - "Kernel.h"
Cohesion: 0.10
Nodes (19): Axis, X, Y, Z, BooleanOp, Cut, Intersect, Join (+11 more)

### Community 110 - "TopologyCounts"
Cohesion: 0.17
Nodes (17): Section, Circular, Square, Triangular, TopologyCounts, edges, faces, shells (+9 more)

### Community 114 - "uninstall.sh"
Cohesion: 0.52
Nodes (6): die(), manifest_for(), refresh(), uninstall.sh script, step(), usage()

### Community 115 - "install.sh"
Cohesion: 0.60
Nodes (5): die(), refresh(), install.sh script, step(), usage()

### Community 116 - "TestFramework.h"
Cohesion: 0.15
Nodes (11): Result, error, ok, output, captured(), PythonHost::exec(), PythonHost::runScript(), Case (+3 more)

### Community 117 - ".rebuild"
Cohesion: 0.08
Nodes (12): hiddenColour(), qc(), rgb(), sharpEdges(), Style, Shaded, ShadedEdges, ShadedHidden (+4 more)

### Community 118 - "Column"
Cohesion: 0.25
Nodes (8): Column, kComment, kExpression, kName, kParameter, kStar, kUnit, kValue

### Community 123 - "Placement"
Cohesion: 0.25
Nodes (7): Placement, angle, cx, cy, dx, dy, scale

### Community 124 - "ChainSegment"
Cohesion: 0.67
Nodes (3): ChainSegment, entity, forward

### Community 128 - ".updatePreview"
Cohesion: 0.06
Nodes (19): ccwContains(), circumcircle(), ext(), fixedColor(), freeColor(), lineEntity(), qc(), rgb() (+11 more)

### Community 134 - "src/main.cpp"
Cohesion: 0.09
Nodes (4): QAbstractButton, QAction, grabWindowWithPanels(), writeLiveGeometry()

### Community 141 - "Point"
Cohesion: 0.52
Nodes (6): Point, x, y, z, customPlaneSpec(), toDxf()

### Community 142 - "SplineHandle"
Cohesion: 0.29
Nodes (7): SplineHandle, arm, index, tx, ty, x, y

## Knowledge Gaps
- **769 isolated node(s):** `ok`, `output`, `error`, `isReal`, `real` (+764 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 1435 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **26 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `optional` connect `optional` to `Viewport`, `MainWindow`, `Feature`, `sketchFor`, `Kernel.cpp`, `Viewport.h`, `Io.cpp`, `Unit`, `ViewportSketch.cpp`, `SketchOps.cpp`, `ViewportArrow.cpp`, `Constraint`, `DocCommands.cpp`, `CommandDialog.cpp`, `Pick`, `SketchEditor.cpp`, `AnalysisSettings`, `ParamSet`, `InputDef`, `Session`, `Vec3`, `CommandDialog::CommandDialog`, `SketchCurves.cpp`, `string`, `ReplayStep`, `MainWindowArrow.cpp`, `Kernel.h`?**
  _High betweenness centrality (0.129) - this node is a cross-community bridge._
- **What connects `ok`, `output`, `error` to the rest of the system?**
  _769 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Viewport` be split into smaller, more focused modules?**
  _Cohesion score 0.01624015748031496 - nodes in this community are weakly interconnected._
- **Why does `Viewport` connect `Viewport` to `ViewportArrow.cpp`, `MainWindow`, `Viewport.cpp`, `TsrModule.cpp`, `optional`, `AnalysisSettings`, `AnalysisSettings`, `SketchDisplay`, `Viewport.h`, `SketchCurves.cpp`, `MainWindowTools.cpp`, `.rebuild`, `MainWindow.cpp`, `.toPixels`, `ViewportAnalysis.cpp`, `rect`, `.redrawAll`?**
  _High betweenness centrality (0.106) - this node is a cross-community bridge._
- **Should `Icons.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.053841901603095633 - nodes in this community are weakly interconnected._
- **Why does `SketchEditor` connect `SketchEditor` to `.updatePreview`, `Viewport`, `ParameterCompleter`, `Constraint`, `PlaneEdges`, `Snap`, `Kind`, `Display`, `optional`, `Pick`, `SketchEditor.cpp`, `Viewport.h`, `Unit`, `Text`, `Entity`, `Session`?**
  _High betweenness centrality (0.094) - this node is a cross-community bridge._
- **Should `Session.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.05669710806697108 - nodes in this community are weakly interconnected._