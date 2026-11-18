# Graph Report - tessera  (2026-11-17)

## Corpus Check
- 423 files · ~281,255 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 72 file(s) not represented in the graph (top: .drive 64, (none) 5, .cmake 1)

## Summary
- 3968 nodes · 10199 edges · 138 communities (114 shown, 24 thin omitted)
- Extraction: 85% EXTRACTED · 15% INFERRED · 0% AMBIGUOUS · INFERRED: 1563 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `d88554a2`
- Run `git rev-parse HEAD` and compare to check if the graph is stale.
- Run `graphify update .` after code changes (no API cost).

## Community Hubs (Navigation)
- Viewport
- Icons.cpp
- Session.cpp
- MainWindow
- run_oracle.py
- DocCommands.cpp
- Document
- Viewport.cpp
- SketchEditor
- DocumentError
- optional
- Kernel.cpp
- AnalysisSettings
- Kind
- QMouseEvent
- CommandDialog
- Io.cpp
- Parser
- sketchFor
- Document
- TEST
- CommandDialog.cpp
- Affine
- ViewportSketch.cpp
- SketchPalette
- Constraint
- Inputs
- Command
- Colors
- KernelError
- SketchOps.cpp
- .rebuild
- ParameterCompleter
- Pick
- MainWindow.cpp
- solve
- validateOperation
- curve
- ConstraintType
- AdskModule.cpp
- QPointF
- TopologyCounts
- Zip.cpp
- AnalysisSettings
- Sketch
- Document.cpp
- MainWindowSketch.cpp
- InputDef
- SketchEditor.cpp
- .toPixels
- Development
- .features
- Command.cpp
- BoundingBox
- TsrModule.cpp
- xdrive.py
- adsk_core
- CommandDialog.cpp
- Session
- Theme.cpp
- BodyFrame
- CommandRegistry
- Expression.cpp
- CommandSession
- Theme
- Feature
- InputType
- ParametersDialog.cpp
- UiCommand
- ViewportArrow.cpp
- .add
- .updatePreview
- Vec3
- BoundaryCell
- math
- CommandDialog::CommandDialog
- SketchDisplay
- Kind
- Measurement
- SketchCurves.cpp
- cachedProfiles
- Level
- README.md
- .showDialog
- test_feature_pattern.py
- QDialog
- TEST
- FileFormat
- Known differences still to build
- Unit
- ReplayStep
- src/main.cpp
- MainWindowArrow.cpp
- FakeDoc
- ModelParameter
- .openMarkingMenu
- Viewport::setDragArrow
- Document::load
- toDxf
- Placement
- test_rigid_group.py
- Entity
- Display
- Joints
- Kernel.h
- Known gaps
- .redrawAll
- SectionState
- uninstall.sh
- install.sh
- TestFramework.h
- bindAdsk
- Profile
- MainWindow::lookTargets
- MainWindow::MainWindow
- SelectionBox
- test_incremental_replay.py
- MarkingMenu
- HandleHit
- QScrollArea
- ROADMAP.md
- Joint
- LAB_NOTES.md
- build.sh
- live-test.sh
- SplineHandle
- ChainSegment
- BodyFrame
- EntityType
- Architecture
- fail

## God Nodes (most connected - your core abstractions)
1. `Viewport` - 286 edges
2. `SketchEditor` - 198 edges
3. `MainWindow` - 189 edges
4. `Inputs` - 161 edges
5. `render()` - 124 edges
6. `Document` - 122 edges
7. `CommandContext` - 116 edges
8. `CommandDialog` - 98 edges
9. `CommandError` - 70 edges
10. `Command` - 68 edges

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

## Communities (138 total, 24 thin omitted)

### Community 0 - "Viewport"
Cohesion: 0.01
Nodes (79): view_, QLineEdit, Viewport, analysis_, analysisObjects_, appliedGridStep_, arrowBoxes_, arrowDragging_ (+71 more)

### Community 1 - "Icons.cpp"
Cohesion: 0.05
Nodes (131): accessibilityIcon(), appearanceIcon(), arc3Icon(), arcIcon(), arcTangentIcon(), arrow(), axisIcon(), boundaryFillIcon() (+123 more)

### Community 2 - "Session.cpp"
Cohesion: 0.13
Nodes (32): historyEdit(), OwnedCommand, owned, OwningCommandSession, plainEdit(), Session::addListener(), Session::addNamedView(), Session::begin() (+24 more)

### Community 4 - "MainWindow"
Cohesion: 0.03
Nodes (67): CommandDialog, MainWindow, active_, appearanceColour_, appearanceFaces_, appearancePanel_, arrowInput_, arrowInput2_ (+59 more)

### Community 5 - "run_oracle.py"
Cohesion: 0.08
Nodes (54): add_point(), arc_poly(), body_at(), body_list(), build_sketch(), chain(), circumcentre(), cm() (+46 more)

### Community 6 - "DocCommands.cpp"
Cohesion: 0.06
Nodes (35): AddUserParameter, def_, axisOf(), boundaryFillCells(), checkPattern(), CircularPattern, def_, CreateSketch (+27 more)

### Community 7 - "Document"
Cohesion: 0.03
Nodes (14): Document, effects_, lastReplayed_, lastReused_, modified_, pendingTools_, registry_, replaying_ (+6 more)

### Community 8 - "Viewport.cpp"
Cohesion: 0.04
Nodes (10): glide(), keys(), NavPreset, Fusion, SolidWorks, Tinkercad, QKeyEvent, QtFrameBuffer (+2 more)

### Community 9 - "SketchEditor"
Cohesion: 0.03
Nodes (49): SketchEditor, arcDrag_, arcDragMoved_, arcEndsChain_, arcFrom_, arcRef_, bodyEdges_, boxing_ (+41 more)

### Community 10 - "DocumentError"
Cohesion: 0.09
Nodes (30): DocumentError, checkViewName(), Document::abortTransaction(), Document::addNamedView(), Document::addUserParameter(), Document::commitTransaction(), Document::expressionEnv(), Document::openTransaction() (+22 more)

### Community 11 - "optional"
Cohesion: 0.09
Nodes (14): QComboBox, QDialogButtonBox, QFormLayout, QLabel, QListWidget, optional, Document, UserParameter (+6 more)

### Community 12 - "Kernel.cpp"
Cohesion: 0.03
Nodes (4): isoCoarsePitch(), topologyCounts(), touching(), wrapOntoCylinder()

### Community 13 - "AnalysisSettings"
Cohesion: 0.11
Nodes (18): AnalysisKind, Accessibility, CurvatureMap, Draft, Isocurve, MinimumRadius, None, Zebra (+10 more)

### Community 14 - "Kind"
Cohesion: 0.07
Nodes (29): ConstructPlane, def_, kind_, EdgeFeature, def_, kind_, Kind, Angle (+21 more)

### Community 15 - "QMouseEvent"
Cohesion: 0.06
Nodes (18): MarkingMenu::mouseMoveEvent(), MarkingMenu::mouseReleaseEvent(), QMouseEvent, QTimer, ViewInteractor, rgb(), Viewport::arrowMouseMove(), Viewport::arrowMousePress() (+10 more)

### Community 16 - "CommandDialog"
Cohesion: 0.05
Nodes (31): CommandDialog, bodiesId_, bodiesLabel_, bodyInput_, buttons_, cellsId_, cellsList_, cmd_ (+23 more)

### Community 17 - "Io.cpp"
Cohesion: 0.09
Nodes (19): MainWindow::print3d(), NamedShape, compoundOf(), exportShapes(), fmt(), formatForPath(), fromBrep(), importShape() (+11 more)

### Community 18 - "Parser"
Cohesion: 0.18
Nodes (15): Quantity, angle, length, value, describe(), isIdentChar(), Parser, ang_ (+7 more)

### Community 19 - "sketchFor"
Cohesion: 0.12
Nodes (14): Extrude, def_, Pipe, def_, Revolve, def_, RibWeb, def_ (+6 more)

### Community 21 - "Document"
Cohesion: 0.22
Nodes (8): ConstructAxisPoint, def_, kind_, jointOrigin(), JointPick, frame, planeOf(), revolveAxis()

### Community 22 - "TEST"
Cohesion: 0.07
Nodes (11): Sketch, constraints, entities, points, texts, Sketch::addCircle(), Sketch::addConic(), Sketch::addEllipticalArc() (+3 more)

### Community 24 - "Affine"
Cohesion: 0.13
Nodes (13): Affine, a, b, d, e, Builder, byPlace_, k_ (+5 more)

### Community 25 - "ViewportSketch.cpp"
Cohesion: 0.05
Nodes (7): QLabel, faceStyle(), lineStyle(), rgb(), Viewport::lookAt(), Viewport::planePoint(), Viewport::toWidget()

### Community 26 - "SketchPalette"
Cohesion: 0.06
Nodes (26): flatButton(), QCheckBox, QLabel, QToolButton, QWidget, SketchEditor, SketchPalette, body_ (+18 more)

### Community 27 - "Constraint"
Cohesion: 0.09
Nodes (20): Constraint, driven, entities, expression, hasLabel, labelX, labelY, name (+12 more)

### Community 28 - "Inputs"
Cohesion: 0.07
Nodes (26): CommandContext, CommandError, Inputs, CommandSession::CommandSession(), getBool(), getInt(), applyOperation(), applyToParticipants() (+18 more)

### Community 29 - "Command"
Cohesion: 0.04
Nodes (56): Adding a tool, Command, CommandDef, feature, icon, id, inputs, name (+48 more)

### Community 30 - "Colors"
Cohesion: 0.07
Nodes (28): Colors, base, border, cubeBox, cubeText, errorBackground, grid, gridMajor (+20 more)

### Community 31 - "KernelError"
Cohesion: 0.21
Nodes (35): KernelError, asSolid(), boolean(), boundaryCells(), chamfer(), chamferEx(), deleteFaces(), draft() (+27 more)

### Community 32 - "SketchOps.cpp"
Cohesion: 0.23
Nodes (25): at(), chainOf(), chamferCorner(), circularPattern(), copyEntities(), cross(), dot(), extendLine() (+17 more)

### Community 33 - ".rebuild"
Cohesion: 0.10
Nodes (12): hiddenColour(), qc(), rgb(), sharpEdges(), Style, Shaded, ShadedEdges, ShadedHidden (+4 more)

### Community 34 - "ParameterCompleter"
Cohesion: 0.12
Nodes (8): ParameterCompleter, completer_, edit_, names_, ParameterCompleter::ParameterCompleter(), public, QCompleter, QLineEdit

### Community 35 - "Pick"
Cohesion: 0.07
Nodes (21): QObject, Hit, index, kind, Pick, bodyArc, bodyPoint, bodySegment (+13 more)

### Community 37 - "MainWindow.cpp"
Cohesion: 0.10
Nodes (3): commandIcon(), qs(), MainWindow::applySection()

### Community 38 - "solve"
Cohesion: 0.18
Nodes (12): addConstraintChecked(), Layout, n, px, py, rad, makeLayout(), pack() (+4 more)

### Community 39 - "validateOperation"
Cohesion: 0.13
Nodes (10): Coil, def_, Primitive, build_, def_, Sweep, def_, Thicken (+2 more)

### Community 40 - "curve"
Cohesion: 0.16
Nodes (19): conditionedSpline(), curve(), curves(), entityCurves(), G2End, d1, d2, set (+11 more)

### Community 41 - "ConstraintType"
Cohesion: 0.07
Nodes (27): ConstraintType, Angle, Coincident, Collinear, Concentric, Curvature, Diameter, Distance (+19 more)

### Community 42 - "AdskModule.cpp"
Cohesion: 0.12
Nodes (13): Application, BRepBodies, Component, Design, Product, raiseIfError(), UserParameter, name (+5 more)

### Community 43 - "QPointF"
Cohesion: 0.13
Nodes (5): PlaneEdges, arcs, curves, segments, vertices

### Community 45 - "TopologyCounts"
Cohesion: 0.16
Nodes (17): Section, Circular, Square, Triangular, TopologyCounts, edges, faces, shells (+9 more)

### Community 46 - "Zip.cpp"
Cohesion: 0.09
Nodes (18): isEmpty(), Value, Entry, data, name, ZipError, crc32(), deflateRaw() (+10 more)

### Community 47 - "AnalysisSettings"
Cohesion: 0.08
Nodes (20): DragArrow, base, dir, radius, ref, ring, value, PendingLook (+12 more)

### Community 48 - "Sketch"
Cohesion: 0.08
Nodes (19): SketchError, SplineKind, Conic, Control, Fit, entityTypeName(), isDimension(), Sketch::addConstraint() (+11 more)

### Community 49 - "Document.cpp"
Cohesion: 0.05
Nodes (51): ConstructionPlane, name, spec, SketchRecord, data, name, offset, plane (+43 more)

### Community 50 - "MainWindowSketch.cpp"
Cohesion: 0.06
Nodes (21): MainWindow::cancelSketch(), MainWindow::editSketch(), MainWindow::finishSketch(), MainWindow::sketchPalette(), MainWindow::sketchVisible(), MainWindow::startSketch(), MainWindow::updateProfilePicking(), qs() (+13 more)

### Community 51 - "InputDef"
Cohesion: 0.09
Nodes (22): InputDef, choices, defaultValue, id, label, max, min, minExclusive (+14 more)

### Community 52 - "SketchEditor.cpp"
Cohesion: 0.13
Nodes (4): angleInArc(), ccwContains(), circumcircle(), segDistance()

### Community 54 - "Development"
Cohesion: 0.40
Nodes (4): Build, Conventions, Development, Tests

### Community 55 - ".features"
Cohesion: 0.24
Nodes (7): Document::nextAxisName(), Document::nextComponentName(), Document::nextPlaneName(), Document::nextPointName(), Document::nextSketchName(), Document::renameSketch(), freeName()

### Community 56 - "Command.cpp"
Cohesion: 0.13
Nodes (17): expressionKey(), Dimension, Angle, Length, Unitless, checkInputValue(), CommandContext::evaluateExpression(), CommandDef::input() (+9 more)

### Community 57 - "BoundingBox"
Cohesion: 0.23
Nodes (14): BoundingBox, max, min, WallSide, Center, Side1, Side2, extendedWire() (+6 more)

### Community 58 - "TsrModule.cpp"
Cohesion: 0.17
Nodes (4): bindTsr(), fromPy(), toPy(), typeName()

### Community 59 - "xdrive.py"
Cohesion: 0.28
Nodes (15): button(), canvas(), click(), drag(), flush(), geometry(), key(), keycode() (+7 more)

### Community 62 - "Session"
Cohesion: 0.05
Nodes (8): Session, commands_, doc_, listeners_, nextListener_, path_, param(), TEST()

### Community 63 - "Theme.cpp"
Cohesion: 0.19
Nodes (6): setIconTheme(), darkColors(), darkPalette(), darkStyleSheet(), lightColors(), lightStyleSheet()

### Community 64 - "BodyFrame"
Cohesion: 0.11
Nodes (26): boundingBox(), completeEdgeReferences(), completeFaceReferences(), decode(), decodeFaces(), dot(), edgeReference(), EdgeSig (+18 more)

### Community 65 - "CommandRegistry"
Cohesion: 0.20
Nodes (3): CommandRegistry, cmds_, CommandRegistry::add()

### Community 66 - "Expression.cpp"
Cohesion: 0.13
Nodes (15): ExpressionEnv, lengthUnit, lookup, ExpressionError, evaluateExpression(), evaluateQuantity(), expressionReferences(), isConstantName() (+7 more)

### Community 67 - "CommandSession"
Cohesion: 0.14
Nodes (5): CommandSession, inputs_, CommandRegistry::all(), CommandRegistry::find(), CommandRegistry::run()

### Community 68 - "Theme"
Cohesion: 0.20
Nodes (5): MainWindow::showPreferences(), Theme, colors_, public, styled_

### Community 69 - "Feature"
Cohesion: 0.11
Nodes (16): Feature, commandId, error, id, inputs, name, parameterNames, rolledBack (+8 more)

### Community 70 - "InputType"
Cohesion: 0.12
Nodes (17): InputType, Axis, Bodies, Body, Bool, Choice, Edges, Faces (+9 more)

### Community 71 - "ParametersDialog.cpp"
Cohesion: 0.06
Nodes (24): Column, kComment, kExpression, kName, kParameter, kStar, kUnit, kValue (+16 more)

### Community 72 - "UiCommand"
Cohesion: 0.14
Nodes (11): UiCommand, enabled, icon, id, name, panel, run, shortcut (+3 more)

### Community 73 - "ViewportArrow.cpp"
Cohesion: 0.06
Nodes (24): Viewport::frontEdgeOwner(), packed(), ramp(), shade(), Viewport::buildAnalysis(), segmentDistance(), Viewport::arrowAt(), Viewport::arrowParam() (+16 more)

### Community 75 - ".updatePreview"
Cohesion: 0.08
Nodes (16): ext(), fixedColor(), freeColor(), lineEntity(), qc(), rgb(), wire(), Text (+8 more)

### Community 76 - "Vec3"
Cohesion: 0.18
Nodes (20): SurfacePoint, normal, point, Vec3, containsPoint(), edgeMidpoint(), edgesNear(), frame() (+12 more)

### Community 77 - "BoundaryCell"
Cohesion: 0.29
Nodes (4): BoundaryCell, ref, shape, volume

### Community 78 - "math"
Cohesion: 0.05
Nodes (4): dist(), up_to_underside(), check_regular(), dist_to_line()

### Community 79 - "CommandDialog::CommandDialog"
Cohesion: 0.12
Nodes (5): CommandDialog::CommandDialog(), ExpressionSpinBox, eval_, expression_, shown_

### Community 80 - "SketchDisplay"
Cohesion: 0.12
Nodes (11): ProfileObject, index, sketch, SketchDisplay, construction, curves, fixedCurves, frame (+3 more)

### Community 81 - "Kind"
Cohesion: 0.05
Nodes (39): HudField, edit, editing, kind, locked, value, Kind, Angle (+31 more)

### Community 82 - "Measurement"
Cohesion: 0.12
Nodes (15): Kind, Angle, Area, Length, Volume, Measurement, from, hasLine (+7 more)

### Community 83 - "SketchCurves.cpp"
Cohesion: 0.13
Nodes (19): crossings(), crossingsOf(), Curve2d, curve2d(), periodic, t0, t1, endIsFree() (+11 more)

### Community 84 - "cachedProfiles"
Cohesion: 0.20
Nodes (3): MainWindow::updateDragArrow(), cachedProfiles(), keyOf()

### Community 85 - "Level"
Cohesion: 0.16
Nodes (13): debug(), error(), info(), Level, Debug, Error, Info, Warning (+5 more)

### Community 86 - "README.md"
Cohesion: 0.17
Nodes (9): Reference parts, Contents, Development, Features, Install, License, Planned, Project layout (+1 more)

### Community 87 - ".showDialog"
Cohesion: 0.11
Nodes (5): MainWindow::onEdgeClicked(), MainWindow::onProfileClicked(), MainWindow::originalShape(), MainWindow::syncPickedShapes(), MainWindow::toOriginal()

### Community 90 - "QDialog"
Cohesion: 0.06
Nodes (29): QDialog, MainWindow::checkInterference(), MainWindow::chooseUnits(), MainWindow::driveJoints(), MainWindow::editAppearance(), MainWindow::editMaterial(), MainWindow::exportDesign(), MainWindow::formatLength() (+21 more)

### Community 92 - "FileFormat"
Cohesion: 0.17
Nodes (12): FileFormat, Brep, Iges, Obj, Step, Stl, ThreeMF, FormatInfo (+4 more)

### Community 93 - "Known differences still to build"
Cohesion: 0.15
Nodes (12): Data and files, Findings from the videos, Fusion study list, Interface, Known differences still to build, Navigation and display, Selection and the canvas, Sketch (+4 more)

### Community 94 - "Unit"
Cohesion: 0.13
Nodes (14): MainWindow::lengthUnit(), Unit, Centimeter, Degree, Foot, Inch, Meter, Millimeter (+6 more)

### Community 95 - "ReplayStep"
Cohesion: 0.05
Nodes (39): Body, color, display, faceColors, material, name, shape, Component (+31 more)

### Community 96 - "src/main.cpp"
Cohesion: 0.08
Nodes (8): listCommands(), main(), usage(), grabWindowWithPanels(), main(), smoke(), writeLiveGeometry(), key

### Community 97 - "MainWindowArrow.cpp"
Cohesion: 0.13
Nodes (8): ArrowPlacement, base, dir, edgePlacement(), facesPlacement(), MainWindow::attachArrowCompleters(), MainWindow::patternCentre(), MainWindow::pickedFaces()

### Community 98 - "FakeDoc"
Cohesion: 0.17
Nodes (6): FakeDoc, aborts, commits, items, open, snapshot

### Community 99 - "ModelParameter"
Cohesion: 0.07
Nodes (34): ModelParameter, angle, expression, input, label, name, owner, unit (+26 more)

### Community 101 - "Viewport::setDragArrow"
Cohesion: 0.18
Nodes (4): Viewport::DragArrow::handle(), Viewport::emitArrow(), Viewport::setDragArrow(), Viewport::setDragRing()

### Community 102 - "Document::load"
Cohesion: 0.22
Nodes (5): doc_(), Document::Document(), Document::ocafBytes(), ocafApplication(), Document::load()

### Community 103 - "toDxf"
Cohesion: 0.43
Nodes (7): Point, x, y, z, customPlaneSpec(), planeFrame(), toDxf()

### Community 104 - "Placement"
Cohesion: 0.25
Nodes (7): Placement, angle, cx, cy, dx, dy, scale

### Community 106 - "Entity"
Cohesion: 0.11
Nodes (12): Entity, a, b, center, construction, fit, handles, included (+4 more)

### Community 107 - "Display"
Cohesion: 0.25
Nodes (7): Display, constraints, construction, dimensions, points, profiles, projected

### Community 108 - "Joints"
Cohesion: 0.36
Nodes (3): cornerAt(), Joints, parent_

### Community 110 - "Kernel.h"
Cohesion: 0.10
Nodes (19): Axis, X, Y, Z, BooleanOp, Cut, Intersect, Join (+11 more)

### Community 111 - "Known gaps"
Cohesion: 0.14
Nodes (14): 3D Sketch, Appearance, Boundary Fill, Curvature (G2), Emboss, Face patterns, Fillet, Include 3D Geometry (+6 more)

### Community 112 - ".redrawAll"
Cohesion: 0.12
Nodes (5): Viewport::setCurvatureComb(), Viewport::clearDragArrow(), Viewport::clearSecondArrow(), Viewport::setInteractor(), Viewport::clearTriad()

### Community 113 - "SectionState"
Cohesion: 0.25
Nodes (7): SectionState, active, angle, flip, offset, plane, visible

### Community 114 - "uninstall.sh"
Cohesion: 0.52
Nodes (6): die(), manifest_for(), refresh(), uninstall.sh script, step(), usage()

### Community 115 - "install.sh"
Cohesion: 0.60
Nodes (5): die(), refresh(), install.sh script, step(), usage()

### Community 116 - "TestFramework.h"
Cohesion: 0.09
Nodes (13): Result, error, ok, output, captured(), PYBIND11_EMBEDDED_MODULE(), PythonHost::exec(), PythonHost::PythonHost() (+5 more)

### Community 117 - "bindAdsk"
Cohesion: 0.29
Nodes (3): bindAdsk(), BRepBody, index

### Community 118 - "Profile"
Cohesion: 0.33
Nodes (5): Profile, area, face, x, y

### Community 120 - "MainWindow::MainWindow"
Cohesion: 0.12
Nodes (4): PythonHost, MainWindow::MainWindow(), MainWindow::beginSketch(), MainWindow::exitSketchMode()

### Community 121 - "SelectionBox"
Cohesion: 0.18
Nodes (7): SelectionBox, crossing, Session::notifyChanged(), Rect, rect(), l, p

### Community 123 - "MarkingMenu"
Cohesion: 0.40
Nodes (3): MarkingMenu, enabled, public

### Community 124 - "HandleHit"
Cohesion: 0.40
Nodes (4): HandleHit, back, index, spline

### Community 129 - "Joint"
Cohesion: 0.42
Nodes (3): Joint, asBuilt_, def_

### Community 142 - "SplineHandle"
Cohesion: 0.25
Nodes (8): SplineHandle, arm, index, set, tx, ty, x, y

### Community 144 - "ChainSegment"
Cohesion: 0.67
Nodes (3): ChainSegment, entity, forward

### Community 145 - "BodyFrame"
Cohesion: 0.10
Nodes (22): BodyFrame, diag, dx, dy, dz, x0, y0, z0 (+14 more)

### Community 147 - "EntityType"
Cohesion: 0.29
Nodes (7): EntityType, Arc, Circle, Ellipse, Line, Spline, isRound()

### Community 152 - "Architecture"
Cohesion: 0.40
Nodes (4): Architecture, How a command works, The document, Units

## Knowledge Gaps
- **808 isolated node(s):** `ok`, `output`, `error`, `isReal`, `real` (+803 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 1548 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **24 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `Viewport` connect `Viewport` to `.rebuild`, `SelectionBox`, `MainWindow`, `Viewport::setDragArrow`, `Viewport.cpp`, `ViewportArrow.cpp`, `optional`, `AnalysisSettings`, `AnalysisSettings`, `SketchDisplay`, `QMouseEvent`, `.redrawAll`, `SketchCurves.cpp`, `.toPixels`, `ViewportSketch.cpp`, `QDialog`?**
  _High betweenness centrality (0.132) - this node is a cross-community bridge._
- **What connects `ok`, `output`, `error` to the rest of the system?**
  _808 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Viewport` be split into smaller, more focused modules?**
  _Cohesion score 0.014071381977448514 - nodes in this community are weakly interconnected._
- **Why does `optional` connect `optional` to `Viewport`, `MainWindow`, `DocCommands.cpp`, `SketchEditor`, `Kernel.cpp`, `Io.cpp`, `Parser`, `sketchFor`, `ViewportSketch.cpp`, `SketchGeometry.cpp`, `QPointF`, `AnalysisSettings`, `Document.cpp`, `InputDef`, `SketchEditor.cpp`, `Command.cpp`, `CommandDialog.cpp`, `Session`, `Expression.cpp`, `Feature`, `ViewportArrow.cpp`, `.updatePreview`, `Vec3`, `CommandDialog::CommandDialog`, `SketchCurves.cpp`, `Unit`, `ReplayStep`, `MainWindowArrow.cpp`, `ModelParameter`, `Entity`, `Joints`, `Kernel.h`?**
  _High betweenness centrality (0.122) - this node is a cross-community bridge._
- **Should `Icons.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.05052693785088151 - nodes in this community are weakly interconnected._
- **Why does `SketchEditor` connect `SketchEditor` to `Viewport`, `Pick`, `MainWindow`, `Entity`, `Display`, `optional`, `QPointF`, `.updatePreview`, `QMouseEvent`, `Kind`, `Entity`, `SketchEditor.cpp`, `Session`, `Constraint`, `HandleHit`, `Unit`, `ReplayStep`?**
  _High betweenness centrality (0.091) - this node is a cross-community bridge._
- **Should `Session.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.12692307692307692 - nodes in this community are weakly interconnected._