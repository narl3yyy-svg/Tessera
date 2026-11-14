# Graph Report - tessera  (2026-11-13)

## Corpus Check
- 385 files · ~251,109 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 56 file(s) not represented in the graph (top: .drive 48, (none) 5, .cmake 1)

## Summary
- 3656 nodes · 9376 edges · 145 communities (112 shown, 33 thin omitted)
- Extraction: 85% EXTRACTED · 15% INFERRED · 0% AMBIGUOUS · INFERRED: 1440 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `44c790f6`
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
- FeatureEffect
- optional
- Kernel.cpp
- AnalysisSettings
- Kind
- .openMarkingMenu
- CommandDialog
- Io.cpp
- Unit
- MainWindowTools.cpp
- Known gaps
- Document
- Architecture
- Affine
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
- sketchFor
- test_text_box_path.py
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
- Sketch.cpp
- ModelParameter
- MainWindowSketch.cpp
- InputDef
- .apply
- .toPixels
- ViewportAnalysis.cpp
- .rebuild
- string
- Viewport.h
- Entity
- xdrive.py
- Session
- PlaneEdges
- BodyFrame
- CommandRegistry
- optional
- BodyFrame
- Theme
- validateOperation
- ParametersDialog.cpp
- TEST
- curve
- .showDialog
- InputType
- Vec3
- QString
- CommandDialog::CommandDialog
- SketchDisplay
- Command
- Measurement
- SketchCurves.cpp
- MarkingMenu.cpp
- Level
- README.md
- string
- test_feature_pattern.py
- Viewport::Viewport
- cachedProfiles
- EntityType
- FileFormat
- Known differences still to build
- MainWindow::MainWindow
- ReplayStep
- qs
- .press
- FakeDoc
- UiCommand
- MainWindowArrow.cpp
- .add
- sstream
- TsrModule.cpp
- BoundingBox
- Joints
- SectionState
- Display
- main
- Kernel.h
- TopologyCounts
- UserParameter
- path
- TEST
- uninstall.sh
- install.sh
- TestFramework.h
- Column
- TEST
- test_incremental_replay.py
- Placement
- ChainSegment
- AddUserParameter
- Value.h
- Placement::apply
- Text
- HandleHit
- Mesh
- DocCommands.cpp
- Dimension
- LAB_NOTES.md
- src/main.cpp
- Entry
- build.sh
- live-test.sh
- PYBIND11_EMBEDDED_MODULE
- Point
- SplineHandle
- MainWindow::setSelectionFilter

## God Nodes (most connected - your core abstractions)
1. `Viewport` - 251 edges
2. `SketchEditor` - 185 edges
3. `MainWindow` - 180 edges
4. `Inputs` - 148 edges
5. `Document` - 118 edges
6. `render()` - 113 edges
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

## Communities (145 total, 33 thin omitted)

### Community 0 - "Viewport"
Cohesion: 0.02
Nodes (67): view_, QLineEdit, Viewport, analysis_, analysisObjects_, appliedGridStep_, arrowBoxes_, arrowDragging_ (+59 more)

### Community 1 - "Icons.cpp"
Cohesion: 0.06
Nodes (118): arc3Icon(), arcIcon(), arcTangentIcon(), arrow(), axisIcon(), box(), breakIcon(), centerRectIcon() (+110 more)

### Community 2 - "Session.cpp"
Cohesion: 0.06
Nodes (48): CommandSession, inputs_, expressionKey(), checkInputValue(), CommandContext::evaluateExpression(), CommandDef::input(), CommandSession::applyInTransaction(), CommandSession::cancel() (+40 more)

### Community 4 - "MainWindow"
Cohesion: 0.03
Nodes (62): CommandDialog, MainWindow, active_, arrowInput_, arrowInput2_, bodiesBeforeCommand_, combEdges_, combPicking_ (+54 more)

### Community 5 - "run_oracle.py"
Cohesion: 0.08
Nodes (54): add_point(), arc_poly(), body_at(), body_list(), build_sketch(), chain(), circumcentre(), cm() (+46 more)

### Community 7 - "Document"
Cohesion: 0.03
Nodes (17): Document, effects_, lastReplayed_, lastReused_, modified_, pendingTools_, registry_, replaying_ (+9 more)

### Community 8 - "Viewport.cpp"
Cohesion: 0.05
Nodes (3): glide(), QKeyEvent, QtFrameBuffer

### Community 9 - "SketchEditor"
Cohesion: 0.03
Nodes (50): SketchEditor, arcDrag_, arcDragMoved_, arcEndsChain_, arcFrom_, arcRef_, bodyEdges_, boxing_ (+42 more)

### Community 10 - "FeatureEffect"
Cohesion: 0.11
Nodes (14): ExpressionEnv, lengthUnit, lookup, dimensionOf(), FeatureEffect, bodies, tools, Document::bodyShapes() (+6 more)

### Community 11 - "optional"
Cohesion: 0.10
Nodes (4): CommandRegistry::all(), Document, fail(), Failure

### Community 12 - "Kernel.cpp"
Cohesion: 0.04
Nodes (5): isoCoarsePitch(), massProperties(), measure(), polygonToCircleLoft(), topologyCounts()

### Community 13 - "AnalysisSettings"
Cohesion: 0.15
Nodes (13): AnalysisKind, CurvatureMap, Draft, None, Zebra, AnalysisSettings, curvatureScale, draftAngle (+5 more)

### Community 14 - "Kind"
Cohesion: 0.07
Nodes (26): EdgeFeature, def_, kind_, FaceFeature, def_, kind_, Kind, Angle (+18 more)

### Community 15 - ".openMarkingMenu"
Cohesion: 0.08
Nodes (7): run, MainWindow::buildSketchTab(), MainWindow::enterSketchMode(), MainWindow::buildUiCommands(), MarkingMenu::mouseReleaseEvent(), QTimer, Viewport::selectArrowValue()

### Community 16 - "CommandDialog"
Cohesion: 0.05
Nodes (31): CommandDialog, bodiesId_, bodiesLabel_, bodyInput_, buttons_, cmd_, conditional_, edgesId_ (+23 more)

### Community 17 - "Io.cpp"
Cohesion: 0.11
Nodes (8): formatForPath(), fromBrep(), importShape(), lower(), meshOf(), scaled(), toBrep(), xmlEscape()

### Community 18 - "Unit"
Cohesion: 0.08
Nodes (42): MainWindow::lengthUnit(), ExpressionError, Quantity, angle, length, value, Unit, Centimeter (+34 more)

### Community 19 - "MainWindowTools.cpp"
Cohesion: 0.07
Nodes (22): QDialog, MainWindow::checkInterference(), MainWindow::chooseUnits(), MainWindow::driveJoints(), MainWindow::exportDesign(), MainWindow::formatLength(), MainWindow::gridSettings(), MainWindow::insertFile() (+14 more)

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
Cohesion: 0.09
Nodes (6): faceStyle(), lineStyle(), rgb(), Viewport::lookAt(), Viewport::planePoint(), Viewport::toWidget()

### Community 26 - "SketchPalette"
Cohesion: 0.06
Nodes (26): flatButton(), QCheckBox, QLabel, QToolButton, QWidget, SketchEditor, SketchPalette, body_ (+18 more)

### Community 27 - "Kind"
Cohesion: 0.09
Nodes (21): HudField, edit, editing, kind, locked, value, Kind, Angle (+13 more)

### Community 28 - "Inputs"
Cohesion: 0.08
Nodes (14): CommandContext, CommandError, Inputs, CommandSession::CommandSession(), getBool(), getInt(), bodyCentre(), bodyName() (+6 more)

### Community 29 - "string"
Cohesion: 0.09
Nodes (26): DocumentError, checkViewName(), Document::abortTransaction(), Document::addBody(), Document::addNamedView(), Document::addUserParameter(), Document::commitTransaction(), Document::openTransaction() (+18 more)

### Community 30 - "Colors"
Cohesion: 0.06
Nodes (34): setIconTheme(), Colors, base, border, cubeBox, cubeText, errorBackground, grid (+26 more)

### Community 31 - "KernelError"
Cohesion: 0.25
Nodes (28): KernelError, asSolid(), boolean(), chamfer(), chamferEx(), deleteFaces(), draft(), extrude() (+20 more)

### Community 32 - "SketchOps.cpp"
Cohesion: 0.22
Nodes (27): at(), chainOf(), chamferCorner(), circularPattern(), copyEntities(), cornerAt(), cross(), dot() (+19 more)

### Community 33 - "ViewportArrow.cpp"
Cohesion: 0.05
Nodes (24): MarkingMenu::mouseMoveEvent(), QMouseEvent, ViewInteractor, Viewport::frontEdgeOwner(), rgb(), segmentDistance(), Viewport::arrowAt(), Viewport::arrowMouseMove() (+16 more)

### Community 34 - "ParameterCompleter"
Cohesion: 0.12
Nodes (8): ParameterCompleter, completer_, edit_, names_, ParameterCompleter::ParameterCompleter(), public, QCompleter, QLineEdit

### Community 35 - "Constraint"
Cohesion: 0.10
Nodes (20): Constraint, driven, entities, expression, hasLabel, labelX, labelY, name (+12 more)

### Community 36 - "sketchFor"
Cohesion: 0.12
Nodes (14): Extrude, def_, Pipe, def_, Revolve, def_, RibWeb, def_ (+6 more)

### Community 38 - "solve"
Cohesion: 0.18
Nodes (13): set, addConstraintChecked(), Layout, n, px, py, rad, makeLayout() (+5 more)

### Community 39 - "Snap"
Cohesion: 0.08
Nodes (25): ext(), fixedColor(), freeColor(), lineEntity(), qc(), rgb(), Snap, alignX (+17 more)

### Community 41 - "ConstraintType"
Cohesion: 0.08
Nodes (24): ConstraintType, Angle, Coincident, Collinear, Concentric, Diameter, Distance, Equal (+16 more)

### Community 42 - "AdskModule.cpp"
Cohesion: 0.09
Nodes (16): Application, bindAdsk(), BRepBodies, BRepBody, index, Component, Design, Product (+8 more)

### Community 43 - "Pick"
Cohesion: 0.10
Nodes (17): Hit, index, kind, Pick, bodyArc, bodyPoint, bodySegment, hit (+9 more)

### Community 45 - "TEST"
Cohesion: 0.08
Nodes (7): Sketch, constraints, entities, points, texts, Sketch::addConic(), TEST()

### Community 46 - "Zip.cpp"
Cohesion: 0.25
Nodes (8): ZipError, crc32(), get16(), get32(), put16(), put32(), read(), write()

### Community 47 - "AnalysisSettings"
Cohesion: 0.10
Nodes (16): DragArrow, base, dir, radius, ref, ring, value, PendingLook (+8 more)

### Community 48 - "Sketch.cpp"
Cohesion: 0.09
Nodes (17): SplineKind, Conic, Control, Fit, entityTypeName(), isDimension(), Sketch::addConstraint(), Sketch::addSpline() (+9 more)

### Community 49 - "ModelParameter"
Cohesion: 0.13
Nodes (13): ModelParameter, angle, expression, input, label, name, owner, unit (+5 more)

### Community 50 - "MainWindowSketch.cpp"
Cohesion: 0.10
Nodes (11): MainWindow::cancelSketch(), MainWindow::editSketch(), MainWindow::finishSketch(), MainWindow::onProfileClicked(), MainWindow::originalShape(), MainWindow::sketchPalette(), MainWindow::sketchVisible(), MainWindow::startSketch() (+3 more)

### Community 51 - "InputDef"
Cohesion: 0.09
Nodes (21): InputDef, choices, defaultValue, id, label, max, min, minExclusive (+13 more)

### Community 52 - ".apply"
Cohesion: 0.26
Nodes (8): Hole, def_, HoleSize, holeSize(), modeled, pitch, radius, stringOr()

### Community 54 - "ViewportAnalysis.cpp"
Cohesion: 0.12
Nodes (6): packed(), ramp(), shade(), Viewport::buildAnalysis(), Viewport::setCurvatureComb(), f

### Community 55 - ".rebuild"
Cohesion: 0.12
Nodes (5): hiddenColour(), qc(), rgb(), sharpEdges(), wireColour()

### Community 56 - "string"
Cohesion: 0.13
Nodes (16): bodyNumber(), Document::axisFrame(), Document::nextAxisName(), Document::nextBodyName(), Document::nextComponentName(), Document::nextDimensionName(), Document::nextPlaneName(), Document::nextPointName() (+8 more)

### Community 57 - "Viewport.h"
Cohesion: 0.10
Nodes (6): QLabel, Profile, area, face, x, y

### Community 58 - "Entity"
Cohesion: 0.08
Nodes (15): QObject, SketchEditor::SketchEditor(), edges, Entity, a, b, center, construction (+7 more)

### Community 59 - "xdrive.py"
Cohesion: 0.28
Nodes (15): button(), canvas(), click(), drag(), flush(), geometry(), key(), keycode() (+7 more)

### Community 62 - "Session"
Cohesion: 0.08
Nodes (7): PythonHost::PythonHost(), Session, commands_, doc_, listeners_, nextListener_, path_

### Community 63 - "PlaneEdges"
Cohesion: 0.13
Nodes (5): PlaneEdges, arcs, curves, segments, vertices

### Community 64 - "BodyFrame"
Cohesion: 0.10
Nodes (31): completeEdgeReferences(), completeFaceReferences(), decode(), decodeFaces(), dot(), edgeReference(), EdgeSig, full (+23 more)

### Community 65 - "CommandRegistry"
Cohesion: 0.12
Nodes (4): CommandRegistry, cmds_, CommandRegistry::add(), TEST()

### Community 66 - "optional"
Cohesion: 0.10
Nodes (19): optional, ConstructionAxis, axis, name, Feature, commandId, error, id (+11 more)

### Community 67 - "BodyFrame"
Cohesion: 0.14
Nodes (15): BodyFrame, diag, dx, dy, dz, x0, y0, z0 (+7 more)

### Community 68 - "Theme"
Cohesion: 0.22
Nodes (4): Theme, colors_, public, styled_

### Community 69 - "validateOperation"
Cohesion: 0.16
Nodes (8): Coil, def_, Primitive, build_, def_, Sweep, def_, validateOperation()

### Community 71 - "ParametersDialog.cpp"
Cohesion: 0.09
Nodes (16): number(), ParametersDialog, building_, error_, filter_, listener_, ParametersDialog::ParametersDialog(), public (+8 more)

### Community 72 - "TEST"
Cohesion: 0.09
Nodes (3): param(), TEST(), tmp()

### Community 73 - "curve"
Cohesion: 0.31
Nodes (10): curve(), curves(), entityCurves(), interiorPoint(), profileAt(), profiles(), splineHandles(), textShape() (+2 more)

### Community 75 - "InputType"
Cohesion: 0.12
Nodes (17): InputType, Axis, Bodies, Body, Bool, Choice, Edges, Faces (+9 more)

### Community 76 - "Vec3"
Cohesion: 0.18
Nodes (20): SurfacePoint, normal, point, Vec3, boundingBox(), edgeMidpoint(), edgesNear(), frame() (+12 more)

### Community 79 - "CommandDialog::CommandDialog"
Cohesion: 0.13
Nodes (5): CommandDialog::CommandDialog(), ExpressionSpinBox, eval_, expression_, shown_

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
Cohesion: 0.13
Nodes (18): crossings(), crossingsOf(), Curve2d, curve2d(), periodic, t0, t1, endIsFree() (+10 more)

### Community 84 - "MarkingMenu.cpp"
Cohesion: 0.07
Nodes (17): MarkingMenu, enabled, MarkingMenu::keyPressEvent(), MarkingMenu::MarkingMenu(), MarkingMenu::paintEvent(), MarkingMenu::popupAt(), public, MarkingMenu::ringIndexAt() (+9 more)

### Community 85 - "Level"
Cohesion: 0.16
Nodes (13): debug(), error(), info(), Level, Debug, Error, Info, Warning (+5 more)

### Community 86 - "README.md"
Cohesion: 0.11
Nodes (15): Build, Conventions, Development, Tests, Reference parts, Fusion feature checklist, Roadmap, Contents (+7 more)

### Community 87 - "string"
Cohesion: 0.06
Nodes (46): ConstructionPlane, name, spec, ParamSet, env, text, SketchRecord, data (+38 more)

### Community 89 - "Viewport::Viewport"
Cohesion: 0.11
Nodes (9): keys(), NavPreset, Fusion, SolidWorks, Tinkercad, SelectionBox, crossing, Viewport::Viewport() (+1 more)

### Community 90 - "cachedProfiles"
Cohesion: 0.20
Nodes (3): MainWindow::updateDragArrow(), cachedProfiles(), keyOf()

### Community 91 - "EntityType"
Cohesion: 0.29
Nodes (7): EntityType, Arc, Circle, Ellipse, Line, Spline, isRound()

### Community 92 - "FileFormat"
Cohesion: 0.17
Nodes (12): FileFormat, Brep, Iges, Obj, Step, Stl, ThreeMF, FormatInfo (+4 more)

### Community 93 - "Known differences still to build"
Cohesion: 0.15
Nodes (12): Data and files, Findings from the videos, Fusion study list, Interface, Known differences still to build, Navigation and display, Selection and the canvas, Sketch (+4 more)

### Community 94 - "MainWindow::MainWindow"
Cohesion: 0.13
Nodes (5): PythonHost, MainWindow::MainWindow(), MainWindow::beginSketch(), MainWindow::exitSketchMode(), MainWindow::showPreferences()

### Community 95 - "ReplayStep"
Cohesion: 0.06
Nodes (29): Body, display, name, shape, Component, bodies, name, ConstructionPoint (+21 more)

### Community 96 - "qs"
Cohesion: 0.25
Nodes (3): commandIcon(), qs(), MainWindow::applySection()

### Community 98 - "FakeDoc"
Cohesion: 0.17
Nodes (6): FakeDoc, aborts, commits, items, open, snapshot

### Community 99 - "UiCommand"
Cohesion: 0.18
Nodes (9): UiCommand, enabled, icon, id, name, panel, shortcut, tab (+1 more)

### Community 100 - "MainWindowArrow.cpp"
Cohesion: 0.12
Nodes (8): ArrowPlacement, base, dir, edgePlacement(), facesPlacement(), MainWindow::attachArrowCompleters(), MainWindow::patternCentre(), MainWindow::pickedFaces()

### Community 102 - "sstream"
Cohesion: 0.17
Nodes (5): doc_(), Document::Document(), Document::ocafBytes(), ocafApplication(), Document::load()

### Community 103 - "TsrModule.cpp"
Cohesion: 0.23
Nodes (4): bindTsr(), fromPy(), toPy(), typeName()

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

### Community 111 - "UserParameter"
Cohesion: 0.33
Nodes (6): UserParameter, comment, expression, name, unit, value

### Community 112 - "path"
Cohesion: 0.47
Nodes (8): MainWindow::print3d(), NamedShape, compoundOf(), exportShapes(), fmt(), write3mf(), writeObj(), path

### Community 113 - "TEST"
Cohesion: 0.22
Nodes (3): slurp(), TEST(), tmp()

### Community 114 - "uninstall.sh"
Cohesion: 0.52
Nodes (6): die(), manifest_for(), refresh(), uninstall.sh script, step(), usage()

### Community 115 - "install.sh"
Cohesion: 0.60
Nodes (5): die(), refresh(), install.sh script, step(), usage()

### Community 116 - "TestFramework.h"
Cohesion: 0.16
Nodes (11): Result, error, ok, output, captured(), PythonHost::exec(), PythonHost::runScript(), Case (+3 more)

### Community 118 - "Column"
Cohesion: 0.25
Nodes (8): Column, kComment, kExpression, kName, kParameter, kStar, kUnit, kValue

### Community 123 - "Placement"
Cohesion: 0.25
Nodes (7): Placement, angle, cx, cy, dx, dy, scale

### Community 124 - "ChainSegment"
Cohesion: 0.67
Nodes (3): ChainSegment, entity, forward

### Community 128 - "Text"
Cohesion: 0.11
Nodes (13): Text, angle, corner, flip, font, hAlign, point, text (+5 more)

### Community 129 - "HandleHit"
Cohesion: 0.40
Nodes (4): HandleHit, back, index, spline

### Community 130 - "Mesh"
Cohesion: 0.40
Nodes (3): Mesh, nodes, triangles

### Community 131 - "DocCommands.cpp"
Cohesion: 0.07
Nodes (37): applyOperation(), axisOf(), checkBody(), checkPattern(), CircularPattern, def_, CopyFn, differenceOrNull() (+29 more)

### Community 132 - "Dimension"
Cohesion: 0.50
Nodes (4): Dimension, Angle, Length, Unitless

### Community 134 - "src/main.cpp"
Cohesion: 0.10
Nodes (4): QAbstractButton, QAction, grabWindowWithPanels(), writeLiveGeometry()

### Community 135 - "Entry"
Cohesion: 0.50
Nodes (3): Entry, data, name

### Community 141 - "Point"
Cohesion: 0.27
Nodes (9): Point, x, y, z, SketchError, Sketch::checkIndices(), customPlaneSpec(), planeFrame() (+1 more)

### Community 142 - "SplineHandle"
Cohesion: 0.29
Nodes (7): SplineHandle, arm, index, tx, ty, x, y

## Knowledge Gaps
- **751 isolated node(s):** `ok`, `output`, `error`, `isReal`, `real` (+746 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 1418 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **33 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `optional` connect `optional` to `Viewport`, `DocCommands.cpp`, `MainWindow`, `FeatureEffect`, `optional`, `Kernel.cpp`, `Io.cpp`, `Unit`, `ViewportSketch.cpp`, `SketchOps.cpp`, `ViewportArrow.cpp`, `sketchFor`, `CommandDialog.cpp`, `SketchEditor.cpp`, `AnalysisSettings`, `InputDef`, `Viewport.h`, `Entity`, `Session`, `Vec3`, `QString`, `CommandDialog::CommandDialog`, `SketchCurves.cpp`, `string`, `ReplayStep`, `.press`, `MainWindowArrow.cpp`, `Kernel.h`?**
  _High betweenness centrality (0.107) - this node is a cross-community bridge._
- **What connects `ok`, `output`, `error` to the rest of the system?**
  _751 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Viewport` be split into smaller, more focused modules?**
  _Cohesion score 0.01664516129032258 - nodes in this community are weakly interconnected._
- **Why does `Viewport` connect `Viewport` to `Viewport::Viewport`, `ViewportArrow.cpp`, `optional`, `MainWindow`, `Viewport.cpp`, `optional`, `.initializeGL`, `AnalysisSettings`, `AnalysisSettings`, `SketchDisplay`, `.openMarkingMenu`, `SketchCurves.cpp`, `MainWindowTools.cpp`, `.toPixels`, `.setSelectionFilter`, `.rebuild`, `ViewportAnalysis.cpp`, `Viewport.h`?**
  _High betweenness centrality (0.102) - this node is a cross-community bridge._
- **Should `Icons.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.05605247465712582 - nodes in this community are weakly interconnected._
- **Why does `MainWindow` connect `MainWindow` to `qs`, `ParameterCompleter`, `UiCommand`, `cachedProfiles`, `src/main.cpp`, `ParametersDialog.cpp`, `SectionState`, `optional`, `main`, `.showDialog`, `.openMarkingMenu`, `MainWindowSketch.cpp`, `MainWindowTools.cpp`, `MainWindow.cpp`, `Session`, `Viewport.h`, `SketchPalette`, `MainWindow::MainWindow`?**
  _High betweenness centrality (0.090) - this node is a cross-community bridge._
- **Should `Session.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.05672926447574335 - nodes in this community are weakly interconnected._