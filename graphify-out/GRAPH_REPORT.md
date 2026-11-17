# Graph Report - tessera  (2026-11-17)

## Corpus Check
- 416 files · ~275,643 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 69 file(s) not represented in the graph (top: .drive 61, (none) 5, .cmake 1)

## Summary
- 3881 nodes · 9990 edges · 140 communities (117 shown, 23 thin omitted)
- Extraction: 85% EXTRACTED · 15% INFERRED · 0% AMBIGUOUS · INFERRED: 1517 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `3dbac6d4`
- Run `git rev-parse HEAD` and compare to check if the graph is stale.
- Run `graphify update .` after code changes (no API cost).

## Community Hubs (Navigation)
- Viewport
- QPainter
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
- stroke
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
- Inputs
- Command
- Colors
- KernelError
- SketchOps.cpp
- MainWindowSketch.cpp
- ParameterCompleter
- Constraint
- Icons.cpp
- MainWindow.cpp
- solve
- QObject
- curve
- ConstraintType
- AdskModule.cpp
- Pick
- Icons.h
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
- adsk_core
- CommandDialog.cpp
- Session
- Theme.cpp
- BodyFrame
- CommandRegistry
- Expression.cpp
- TEST
- Theme
- Feature
- InputType
- ParametersDialog.cpp
- Axis
- Viewport.h
- cachedProfiles
- Text
- Vec3
- BoundaryCell
- math
- CommandDialog::CommandDialog
- SketchDisplay
- Kind
- Measurement
- SketchCurves.cpp
- Level
- README.md
- .showDialog
- test_feature_pattern.py
- Sweep
- QDialog
- toDxf
- FileFormat
- Known differences still to build
- Unit
- ReplayStep
- TsrModule.cpp
- cmath
- FakeDoc
- ModelParameter
- .openMarkingMenu
- Viewport::setDragArrow
- Document::load
- UserParameter
- includeEdges
- test_rigid_group.py
- Entity
- Display
- main
- TopologyCounts
- Known gaps
- .redrawAll
- SectionState
- uninstall.sh
- install.sh
- TestFramework.h
- .rebuild
- Placement
- bindAdsk
- MainWindow::MainWindow
- SelectionBox
- test_incremental_replay.py
- Profile
- Development
- QScrollArea
- BooleanOp
- MassProperties
- ThreadInfo
- Joint
- PYBIND11_EMBEDDED_MODULE
- ellipseIcon
- LAB_NOTES.md
- ChamferType
- build.sh
- live-test.sh
- SplineHandle
- ChainSegment

## God Nodes (most connected - your core abstractions)
1. `Viewport` - 258 edges
2. `SketchEditor` - 198 edges
3. `MainWindow` - 184 edges
4. `Inputs` - 161 edges
5. `render()` - 124 edges
6. `Document` - 121 edges
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

## Communities (140 total, 23 thin omitted)

### Community 0 - "Viewport"
Cohesion: 0.02
Nodes (69): view_, QLineEdit, Viewport, analysis_, analysisObjects_, appliedGridStep_, arrowBoxes_, arrowDragging_ (+61 more)

### Community 1 - "QPainter"
Cohesion: 0.08
Nodes (53): appearanceIcon(), axisIcon(), box(), chamferIcon(), coilIcon(), comIcon(), computeIcon(), cone() (+45 more)

### Community 2 - "Session.cpp"
Cohesion: 0.06
Nodes (50): CommandSession, inputs_, expressionKey(), checkInputValue(), CommandContext::evaluateExpression(), CommandDef::input(), CommandSession::applyInTransaction(), CommandSession::cancel() (+42 more)

### Community 4 - "MainWindow"
Cohesion: 0.03
Nodes (63): CommandDialog, MainWindow, active_, arrowInput_, arrowInput2_, bodiesBeforeCommand_, combEdges_, combPicking_ (+55 more)

### Community 5 - "run_oracle.py"
Cohesion: 0.08
Nodes (54): add_point(), arc_poly(), body_at(), body_list(), build_sketch(), chain(), circumcentre(), cm() (+46 more)

### Community 6 - "DocCommands.cpp"
Cohesion: 0.06
Nodes (35): AddUserParameter, def_, axisOf(), boundaryFillCells(), checkPattern(), CircularPattern, def_, CreateSketch (+27 more)

### Community 7 - "Document"
Cohesion: 0.03
Nodes (17): Document, effects_, lastReplayed_, lastReused_, modified_, pendingTools_, registry_, replaying_ (+9 more)

### Community 8 - "Viewport.cpp"
Cohesion: 0.05
Nodes (5): glide(), keys(), QKeyEvent, QtFrameBuffer, Viewport::Viewport()

### Community 9 - "SketchEditor"
Cohesion: 0.03
Nodes (49): SketchEditor, arcDrag_, arcDragMoved_, arcEndsChain_, arcFrom_, arcRef_, bodyEdges_, boxing_ (+41 more)

### Community 10 - "DocumentError"
Cohesion: 0.08
Nodes (32): DocumentError, checkViewName(), Document::abortTransaction(), Document::addBody(), Document::addNamedView(), Document::addUserParameter(), Document::axisFrame(), Document::commitTransaction() (+24 more)

### Community 11 - "optional"
Cohesion: 0.10
Nodes (7): optional, isEmpty(), Value, CommandRegistry::all(), Document, fail(), Failure

### Community 12 - "Kernel.cpp"
Cohesion: 0.03
Nodes (7): isoCoarsePitch(), offsetLoop(), offsetRegion(), pointOnFace(), topologyCounts(), touching(), wrapOntoCylinder()

### Community 13 - "AnalysisSettings"
Cohesion: 0.11
Nodes (18): AnalysisKind, Accessibility, CurvatureMap, Draft, Isocurve, MinimumRadius, None, Zebra (+10 more)

### Community 14 - "Kind"
Cohesion: 0.07
Nodes (29): ConstructPlane, def_, kind_, EdgeFeature, def_, kind_, Kind, Angle (+21 more)

### Community 15 - "stroke"
Cohesion: 0.07
Nodes (41): arc3Icon(), arcIcon(), arcTangentIcon(), breakIcon(), centerRectIcon(), circle2Icon(), circle3Icon(), circleIcon() (+33 more)

### Community 16 - "CommandDialog"
Cohesion: 0.04
Nodes (36): CommandDialog, bodiesId_, bodiesLabel_, bodyInput_, buttons_, cellsId_, cellsList_, cmd_ (+28 more)

### Community 17 - "Io.cpp"
Cohesion: 0.10
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

### Community 22 - "Snap"
Cohesion: 0.10
Nodes (18): Snap, alignX, alignY, bodyArc, bodySegment, entity, fromX, fromY (+10 more)

### Community 24 - "Affine"
Cohesion: 0.14
Nodes (13): Affine, a, b, d, e, Builder, byPlace_, k_ (+5 more)

### Community 25 - "ViewportSketch.cpp"
Cohesion: 0.09
Nodes (6): faceStyle(), lineStyle(), rgb(), Viewport::lookAt(), Viewport::planePoint(), Viewport::toWidget()

### Community 26 - "SketchPalette"
Cohesion: 0.06
Nodes (26): flatButton(), QCheckBox, QLabel, QToolButton, QWidget, SketchEditor, SketchPalette, body_ (+18 more)

### Community 27 - "Sketch"
Cohesion: 0.06
Nodes (13): writeLiveGeometry(), Sketch, constraints, entities, points, texts, Sketch::addCircle(), Sketch::addConic() (+5 more)

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
Cohesion: 0.23
Nodes (32): KernelError, asSolid(), boolean(), boundaryCells(), chamfer(), chamferEx(), deleteFaces(), draft() (+24 more)

### Community 32 - "SketchOps.cpp"
Cohesion: 0.16
Nodes (29): at(), chainOf(), chamferCorner(), circularPattern(), copyEntities(), cornerAt(), cross(), dot() (+21 more)

### Community 33 - "MainWindowSketch.cpp"
Cohesion: 0.04
Nodes (20): grabWindowWithPanels(), MainWindow::cancelSketch(), MainWindow::finishSketch(), MainWindow::sketchPalette(), MarkingMenu, enabled, MarkingMenu::keyPressEvent(), MarkingMenu::MarkingMenu() (+12 more)

### Community 34 - "ParameterCompleter"
Cohesion: 0.12
Nodes (8): ParameterCompleter, completer_, edit_, names_, ParameterCompleter::ParameterCompleter(), public, QCompleter, QLineEdit

### Community 35 - "Constraint"
Cohesion: 0.08
Nodes (20): Constraint, driven, entities, expression, hasLabel, labelX, labelY, name (+12 more)

### Community 36 - "Icons.cpp"
Cohesion: 0.09
Nodes (25): accessibilityIcon(), arrow(), boundaryFillIcon(), combineIcon(), componentIcon(), constructionIcon(), cube(), curvatureIcon() (+17 more)

### Community 37 - "MainWindow.cpp"
Cohesion: 0.09
Nodes (3): commandIcon(), qs(), MainWindow::applySection()

### Community 38 - "solve"
Cohesion: 0.12
Nodes (14): addConstraintChecked(), Layout, n, px, py, rad, makeLayout(), pack() (+6 more)

### Community 39 - "QObject"
Cohesion: 0.16
Nodes (6): QObject, SketchEditor::SketchEditor(), Tool, op, shape, target

### Community 40 - "curve"
Cohesion: 0.16
Nodes (19): conditionedSpline(), curve(), curves(), entityCurves(), G2End, d1, d2, set (+11 more)

### Community 41 - "ConstraintType"
Cohesion: 0.07
Nodes (26): ConstraintType, Angle, Coincident, Collinear, Concentric, Curvature, Diameter, Distance (+18 more)

### Community 42 - "AdskModule.cpp"
Cohesion: 0.12
Nodes (13): Application, BRepBodies, Component, Design, Product, raiseIfError(), UserParameter, name (+5 more)

### Community 43 - "Pick"
Cohesion: 0.07
Nodes (21): Pick, bodyArc, bodyPoint, bodySegment, hit, midpointOf, onEntity, onXAxis (+13 more)

### Community 45 - "Icons.h"
Cohesion: 0.19
Nodes (9): constraintIcon(), fallback(), filterIcon(), icon(), QAbstractButton, QAction, retintIcons(), setIcon() (+1 more)

### Community 46 - "Zip.cpp"
Cohesion: 0.11
Nodes (16): Entry, data, name, ZipError, crc32(), deflateRaw(), get16(), get32() (+8 more)

### Community 47 - "AnalysisSettings"
Cohesion: 0.10
Nodes (16): DragArrow, base, dir, radius, ref, ring, value, PendingLook (+8 more)

### Community 48 - "Sketch.cpp"
Cohesion: 0.08
Nodes (20): SketchError, SplineKind, Conic, Control, Fit, entityTypeName(), isDimension(), Sketch::addConstraint() (+12 more)

### Community 49 - "Document.cpp"
Cohesion: 0.06
Nodes (47): ConstructionPlane, name, spec, ParamSet, env, text, SketchRecord, data (+39 more)

### Community 50 - "MarkingMenu.cpp"
Cohesion: 0.13
Nodes (12): UiCommand, enabled, icon, id, name, panel, run, shortcut (+4 more)

### Community 51 - "InputDef"
Cohesion: 0.09
Nodes (22): InputDef, choices, defaultValue, id, label, max, min, minExclusive (+14 more)

### Community 52 - ".updatePreview"
Cohesion: 0.16
Nodes (6): ccwContains(), circumcircle(), HandleHit, back, index, spline

### Community 55 - "string"
Cohesion: 0.15
Nodes (15): bodyNumber(), Document::componentOfBody(), Document::nextAxisName(), Document::nextBodyName(), Document::nextComponentName(), Document::nextDimensionName(), Document::nextPlaneName(), Document::nextPointName() (+7 more)

### Community 56 - "dimensionOf"
Cohesion: 0.20
Nodes (6): formatNumber(), Dimension, Angle, Length, Unitless, dimensionOf()

### Community 57 - "BoundingBox"
Cohesion: 0.20
Nodes (15): BoundingBox, max, min, WallSide, Center, Side1, Side2, extendedWire() (+7 more)

### Community 58 - "ViewportAnalysis.cpp"
Cohesion: 0.07
Nodes (14): ArrowPlacement, base, dir, edgePlacement(), facesPlacement(), MainWindow::attachArrowCompleters(), MainWindow::patternCentre(), MainWindow::pickedFaces() (+6 more)

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
Nodes (42): BodyFrame, diag, dx, dy, dz, x0, y0, z0 (+34 more)

### Community 65 - "CommandRegistry"
Cohesion: 0.12
Nodes (4): CommandRegistry, cmds_, CommandRegistry::add(), TEST()

### Community 66 - "Expression.cpp"
Cohesion: 0.13
Nodes (15): ExpressionEnv, lengthUnit, lookup, ExpressionError, evaluateExpression(), evaluateQuantity(), expressionReferences(), isConstantName() (+7 more)

### Community 67 - "TEST"
Cohesion: 0.09
Nodes (3): param(), TEST(), tmp()

### Community 68 - "Theme"
Cohesion: 0.22
Nodes (4): Theme, colors_, public, styled_

### Community 69 - "Feature"
Cohesion: 0.08
Nodes (19): Feature, commandId, error, id, inputs, name, parameterNames, rolledBack (+11 more)

### Community 70 - "InputType"
Cohesion: 0.12
Nodes (17): InputType, Axis, Bodies, Body, Bool, Choice, Edges, Faces (+9 more)

### Community 71 - "ParametersDialog.cpp"
Cohesion: 0.06
Nodes (24): Column, kComment, kExpression, kName, kParameter, kStar, kUnit, kValue (+16 more)

### Community 72 - "Axis"
Cohesion: 0.50
Nodes (4): Axis, X, Y, Z

### Community 73 - "Viewport.h"
Cohesion: 0.05
Nodes (20): MarkingMenu::mouseMoveEvent(), QLabel, QMouseEvent, QTimer, ViewInteractor, Viewport::frontEdgeOwner(), rgb(), segmentDistance() (+12 more)

### Community 74 - "cachedProfiles"
Cohesion: 0.10
Nodes (12): MainWindow::updateDragArrow(), MainWindow::editSketch(), MainWindow::onProfileClicked(), MainWindow::originalShape(), MainWindow::sketchVisible(), MainWindow::startSketch(), MainWindow::syncPickedShapes(), MainWindow::toOriginal() (+4 more)

### Community 75 - "Text"
Cohesion: 0.10
Nodes (16): ext(), fixedColor(), freeColor(), lineEntity(), qc(), rgb(), wire(), Text (+8 more)

### Community 76 - "Vec3"
Cohesion: 0.16
Nodes (23): SurfacePoint, normal, point, Vec3, containsPoint(), edgeMidpoint(), edgesNear(), extrudeToFace() (+15 more)

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
Cohesion: 0.08
Nodes (24): Hit, index, kind, HudField, edit, editing, kind, locked (+16 more)

### Community 82 - "Measurement"
Cohesion: 0.12
Nodes (15): Kind, Angle, Area, Length, Volume, Measurement, from, hasLine (+7 more)

### Community 83 - "SketchCurves.cpp"
Cohesion: 0.15
Nodes (17): crossings(), crossingsOf(), Curve2d, curve2d(), periodic, t0, t1, endIsFree() (+9 more)

### Community 85 - "Level"
Cohesion: 0.12
Nodes (13): debug(), error(), info(), Level, Debug, Error, Info, Warning (+5 more)

### Community 86 - "README.md"
Cohesion: 0.10
Nodes (15): Architecture, How a command works, The document, Units, Reference parts, Fusion feature checklist, Roadmap, Contents (+7 more)

### Community 89 - "Sweep"
Cohesion: 0.13
Nodes (10): Coil, def_, Primitive, build_, def_, Sweep, def_, Thicken (+2 more)

### Community 90 - "QDialog"
Cohesion: 0.06
Nodes (29): QDialog, MainWindow::checkInterference(), MainWindow::chooseUnits(), MainWindow::driveJoints(), MainWindow::editAppearance(), MainWindow::editMaterial(), MainWindow::exportDesign(), MainWindow::formatLength() (+21 more)

### Community 91 - "toDxf"
Cohesion: 0.52
Nodes (6): Point, x, y, z, customPlaneSpec(), toDxf()

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
Nodes (43): Body, color, display, material, name, shape, Component, bodies (+35 more)

### Community 96 - "TsrModule.cpp"
Cohesion: 0.19
Nodes (4): bindTsr(), fromPy(), toPy(), typeName()

### Community 97 - "cmath"
Cohesion: 0.11
Nodes (7): EntityType, Arc, Circle, Ellipse, Line, Spline, isRound()

### Community 98 - "FakeDoc"
Cohesion: 0.17
Nodes (6): FakeDoc, aborts, commits, items, open, snapshot

### Community 99 - "ModelParameter"
Cohesion: 0.13
Nodes (13): ModelParameter, angle, expression, input, label, name, owner, unit (+5 more)

### Community 100 - ".openMarkingMenu"
Cohesion: 0.08
Nodes (4): MainWindow::beginSketch(), MainWindow::buildSketchTab(), MainWindow::enterSketchMode(), MainWindow::buildUiCommands()

### Community 101 - "Viewport::setDragArrow"
Cohesion: 0.18
Nodes (4): Viewport::DragArrow::handle(), Viewport::emitArrow(), Viewport::setDragArrow(), Viewport::setDragRing()

### Community 102 - "Document::load"
Cohesion: 0.17
Nodes (5): doc_(), Document::Document(), Document::ocafBytes(), ocafApplication(), Document::load()

### Community 103 - "UserParameter"
Cohesion: 0.33
Nodes (6): UserParameter, comment, expression, name, unit, value

### Community 106 - "Entity"
Cohesion: 0.12
Nodes (12): Entity, a, b, center, construction, fit, handles, included (+4 more)

### Community 107 - "Display"
Cohesion: 0.25
Nodes (7): Display, constraints, construction, dimensions, points, profiles, projected

### Community 108 - "main"
Cohesion: 0.27
Nodes (6): listCommands(), main(), usage(), main(), smoke(), key

### Community 110 - "TopologyCounts"
Cohesion: 0.12
Nodes (18): Section, Circular, Square, Triangular, TopologyCounts, edges, faces, shells (+10 more)

### Community 111 - "Known gaps"
Cohesion: 0.18
Nodes (11): 3D Sketch, Boundary Fill, Curvature (G2), Emboss, Face patterns, Include 3D Geometry, Known gaps, Project to Surface (+3 more)

### Community 112 - ".redrawAll"
Cohesion: 0.11
Nodes (7): NavPreset, Fusion, SolidWorks, Tinkercad, Viewport::clearDragArrow(), Viewport::clearSecondArrow(), Viewport::setInteractor()

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
Cohesion: 0.16
Nodes (11): Result, error, ok, output, captured(), PythonHost::exec(), PythonHost::runScript(), Case (+3 more)

### Community 117 - ".rebuild"
Cohesion: 0.10
Nodes (12): hiddenColour(), qc(), rgb(), sharpEdges(), Style, Shaded, ShadedEdges, ShadedHidden (+4 more)

### Community 118 - "Placement"
Cohesion: 0.25
Nodes (7): Placement, angle, cx, cy, dx, dy, scale

### Community 119 - "bindAdsk"
Cohesion: 0.29
Nodes (3): bindAdsk(), BRepBody, index

### Community 120 - "MainWindow::MainWindow"
Cohesion: 0.13
Nodes (4): PythonHost, MainWindow::MainWindow(), MainWindow::exitSketchMode(), MainWindow::showPreferences()

### Community 123 - "Profile"
Cohesion: 0.33
Nodes (5): Profile, area, face, x, y

### Community 124 - "Development"
Cohesion: 0.40
Nodes (4): Build, Conventions, Development, Tests

### Community 126 - "BooleanOp"
Cohesion: 0.50
Nodes (4): BooleanOp, Cut, Intersect, Join

### Community 127 - "MassProperties"
Cohesion: 0.50
Nodes (4): MassProperties, area, centerOfMass, volume

### Community 128 - "ThreadInfo"
Cohesion: 0.50
Nodes (4): ThreadInfo, diameter, internal, pitch

### Community 129 - "Joint"
Cohesion: 0.42
Nodes (3): Joint, asBuilt_, def_

### Community 132 - "ellipseIcon"
Cohesion: 0.67
Nodes (3): ellipseIcon(), patternIcon(), save()

### Community 134 - "ChamferType"
Cohesion: 0.67
Nodes (3): ChamferType, DistanceAngle, TwoDistances

### Community 142 - "SplineHandle"
Cohesion: 0.25
Nodes (8): SplineHandle, arm, index, set, tx, ty, x, y

### Community 144 - "ChainSegment"
Cohesion: 0.67
Nodes (3): ChainSegment, entity, forward

## Knowledge Gaps
- **792 isolated node(s):** `ok`, `output`, `error`, `isReal`, `real` (+787 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 1512 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **23 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `optional` connect `optional` to `Viewport`, `MainWindow`, `DocCommands.cpp`, `SketchEditor`, `Kernel.cpp`, `Io.cpp`, `Parser`, `sketchFor`, `Entity`, `CommandDialog.cpp`, `ViewportSketch.cpp`, `SketchOps.cpp`, `Constraint`, `Pick`, `AnalysisSettings`, `Document.cpp`, `InputDef`, `.updatePreview`, `SketchGeometry.cpp`, `string`, `dimensionOf`, `ViewportAnalysis.cpp`, `CommandDialog.cpp`, `Session`, `Expression.cpp`, `Feature`, `Viewport.h`, `Vec3`, `CommandDialog::CommandDialog`, `SketchCurves.cpp`, `Unit`, `ReplayStep`, `cmath`?**
  _High betweenness centrality (0.155) - this node is a cross-community bridge._
- **What connects `ok`, `output`, `error` to the rest of the system?**
  _792 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Viewport` be split into smaller, more focused modules?**
  _Cohesion score 0.015854374633000587 - nodes in this community are weakly interconnected._
- **Why does `Viewport` connect `Viewport` to `MainWindow`, `Viewport::setDragArrow`, `QDialog`, `Viewport.cpp`, `Viewport.h`, `optional`, `AnalysisSettings`, `AnalysisSettings`, `SketchDisplay`, `.redrawAll`, `SketchCurves.cpp`, `.initializeGL`, `.rebuild`, `.toPixels`, `SelectionBox`, `ViewportAnalysis.cpp`?**
  _High betweenness centrality (0.122) - this node is a cross-community bridge._
- **Should `QPainter` be split into smaller, more focused modules?**
  _Cohesion score 0.08417508417508418 - nodes in this community are weakly interconnected._
- **Why does `SketchEditor` connect `SketchEditor` to `Viewport`, `cmath`, `Constraint`, `QObject`, `Viewport.h`, `Entity`, `Display`, `Pick`, `Text`, `optional`, `Kind`, `.updatePreview`, `Entity`, `Snap`, `Session`, `Unit`?**
  _High betweenness centrality (0.106) - this node is a cross-community bridge._
- **Should `Session.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.05627545353572751 - nodes in this community are weakly interconnected._