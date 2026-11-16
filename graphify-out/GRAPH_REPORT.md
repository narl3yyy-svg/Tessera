# Graph Report - tessera  (2026-11-16)

## Corpus Check
- 398 files · ~265,404 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 62 file(s) not represented in the graph (top: .drive 54, (none) 5, .cmake 1)

## Summary
- 3779 nodes · 9698 edges · 136 communities (114 shown, 22 thin omitted)
- Extraction: 85% EXTRACTED · 15% INFERRED · 0% AMBIGUOUS · INFERRED: 1491 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `eed2ec60`
- Run `git rev-parse HEAD` and compare to check if the graph is stale.
- Run `graphify update .` after code changes (no API cost).

## Community Hubs (Navigation)
- Viewport
- Icons.cpp
- Session.cpp
- MainWindow
- run_oracle.py
- Expression.cpp
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
- Snap
- src/main.cpp
- Document
- .openMarkingMenu
- MainWindowTools.cpp
- Affine
- ViewportSketch.cpp
- SketchPalette
- Sketch
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
- QObject
- CommandDialog.cpp
- ConstraintType
- AdskModule.cpp
- Pick
- SketchEditor.cpp
- Profile
- Zip.cpp
- AnalysisSettings
- Sketch.cpp
- Document.cpp
- MainWindowSketch.cpp
- InputDef
- string
- .toPixels
- curve
- Document::recompute
- MarkingMenu.cpp
- Command.cpp
- Entity
- xdrive.py
- adsk_core
- Session
- Theme.cpp
- BodyFrame
- CommandRegistry
- TEST
- MainWindow::enterSketchMode
- Theme
- optional
- InputType
- ParametersDialog.cpp
- Kernel.h
- ViewportAnalysis.cpp
- CommandRegistry::run
- .mouseMove
- Vec3
- .add
- math
- QString
- SketchDisplay
- Command
- Measurement
- SketchCurves.cpp
- Level
- README.md
- string
- test_feature_pattern.py
- BodyFrame
- Unit
- .initializeGL
- FileFormat
- Known differences still to build
- TEST
- ReplayStep
- Joints
- cachedProfiles
- FakeDoc
- ParamSet
- .features
- MainWindow::MainWindow
- sstream
- ExpressionEnv
- BoundingBox
- Value.h
- SectionState
- Display
- cli_main.cpp
- Architecture
- TopologyCounts
- fail
- .redrawAll
- toDxf
- uninstall.sh
- install.sh
- TestFramework.h
- .rebuild
- MarkingMenu
- UserParameter
- cmath
- test_incremental_replay.py
- copyEntities
- ChainSegment
- Known gaps
- Viewport::Viewport
- TEST
- Joint
- dimensionOf
- LAB_NOTES.md
- build.sh
- live-test.sh
- SplineHandle

## God Nodes (most connected - your core abstractions)
1. `Viewport` - 257 edges
2. `SketchEditor` - 198 edges
3. `MainWindow` - 184 edges
4. `Inputs` - 152 edges
5. `render()` - 122 edges
6. `Document` - 120 edges
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

## Communities (136 total, 22 thin omitted)

### Community 0 - "Viewport"
Cohesion: 0.02
Nodes (69): view_, QLineEdit, Viewport, analysis_, analysisObjects_, appliedGridStep_, arrowBoxes_, arrowDragging_ (+61 more)

### Community 1 - "Icons.cpp"
Cohesion: 0.05
Nodes (127): accessibilityIcon(), appearanceIcon(), arc3Icon(), arcIcon(), arcTangentIcon(), arrow(), axisIcon(), box() (+119 more)

### Community 2 - "Session.cpp"
Cohesion: 0.12
Nodes (33): historyEdit(), OwnedCommand, owned, OwningCommandSession, plainEdit(), Session::addListener(), Session::addNamedView(), Session::begin() (+25 more)

### Community 4 - "MainWindow"
Cohesion: 0.03
Nodes (64): CommandDialog, MainWindow, active_, arrowInput_, arrowInput2_, bodiesBeforeCommand_, combEdges_, combPicking_ (+56 more)

### Community 5 - "run_oracle.py"
Cohesion: 0.08
Nodes (54): add_point(), arc_poly(), body_at(), body_list(), build_sketch(), chain(), circumcentre(), cm() (+46 more)

### Community 6 - "Expression.cpp"
Cohesion: 0.14
Nodes (13): ExpressionError, evaluateExpression(), evaluateQuantity(), expressionReferences(), isConstantName(), isFunctionName(), isPlainQuantity(), isValidParameterName() (+5 more)

### Community 7 - "Document"
Cohesion: 0.03
Nodes (14): Document, effects_, lastReplayed_, lastReused_, modified_, pendingTools_, registry_, replaying_ (+6 more)

### Community 8 - "Viewport.cpp"
Cohesion: 0.05
Nodes (4): glide(), QKeyEvent, QLabel, QtFrameBuffer

### Community 9 - "SketchEditor"
Cohesion: 0.03
Nodes (58): HandleHit, back, index, spline, PlaneEdges, arcs, curves, segments (+50 more)

### Community 10 - "sketchFor"
Cohesion: 0.13
Nodes (11): Extrude, def_, Pipe, def_, Primitive, build_, def_, Revolve (+3 more)

### Community 11 - "optional"
Cohesion: 0.10
Nodes (5): QComboBox, QDialogButtonBox, QFormLayout, QLabel, Document

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
Cohesion: 0.06
Nodes (27): CommandDialog, bodiesId_, bodiesLabel_, bodyInput_, buttons_, cmd_, conditional_, edgesId_ (+19 more)

### Community 17 - "Io.cpp"
Cohesion: 0.08
Nodes (20): MainWindow::print3d(), NamedShape, compoundOf(), exportShapes(), fmt(), formatForPath(), fromBrep(), importShape() (+12 more)

### Community 18 - "Parser"
Cohesion: 0.18
Nodes (14): Quantity, angle, length, value, describe(), isIdentChar(), isIdentStart(), Parser (+6 more)

### Community 19 - "Snap"
Cohesion: 0.05
Nodes (39): HudField, edit, editing, kind, locked, value, Kind, Angle (+31 more)

### Community 20 - "src/main.cpp"
Cohesion: 0.10
Nodes (4): QAbstractButton, QAction, grabWindowWithPanels(), writeLiveGeometry()

### Community 21 - "Document"
Cohesion: 0.23
Nodes (5): bodyCentre(), ConstructAxisPoint, def_, kind_, storeBodies()

### Community 23 - "MainWindowTools.cpp"
Cohesion: 0.05
Nodes (16): QDialog, MainWindow::chooseUnits(), MainWindow::editAppearance(), MainWindow::editMaterial(), MainWindow::exportDesign(), MainWindow::insertFile(), MainWindow::lookTargets(), MainWindow::measurePick() (+8 more)

### Community 24 - "Affine"
Cohesion: 0.13
Nodes (13): Affine, a, b, d, e, Builder, byPlace_, k_ (+5 more)

### Community 25 - "ViewportSketch.cpp"
Cohesion: 0.09
Nodes (6): faceStyle(), lineStyle(), rgb(), Viewport::lookAt(), Viewport::planePoint(), Viewport::toWidget()

### Community 26 - "SketchPalette"
Cohesion: 0.06
Nodes (26): flatButton(), QCheckBox, QLabel, QToolButton, QWidget, SketchEditor, SketchPalette, body_ (+18 more)

### Community 27 - "Sketch"
Cohesion: 0.08
Nodes (17): Sketch, constraints, entities, points, texts, Text, angle, corner (+9 more)

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
Cohesion: 0.20
Nodes (32): KernelError, asSolid(), boolean(), chamfer(), chamferEx(), deleteFaces(), draft(), extrude() (+24 more)

### Community 32 - "SketchOps.cpp"
Cohesion: 0.28
Nodes (19): at(), chainOf(), chamferCorner(), circularPattern(), cross(), dot(), extendLine(), filletCorner() (+11 more)

### Community 33 - "ViewportArrow.cpp"
Cohesion: 0.06
Nodes (22): MarkingMenu::mouseMoveEvent(), QMouseEvent, QTimer, ViewInteractor, Viewport::frontEdgeOwner(), rgb(), segmentDistance(), Viewport::arrowAt() (+14 more)

### Community 34 - "ParameterCompleter"
Cohesion: 0.12
Nodes (8): ParameterCompleter, completer_, edit_, names_, ParameterCompleter::ParameterCompleter(), public, QCompleter, QLineEdit

### Community 35 - "Constraint"
Cohesion: 0.09
Nodes (21): Constraint, driven, entities, expression, hasLabel, labelX, labelY, name (+13 more)

### Community 36 - "DocCommands.cpp"
Cohesion: 0.10
Nodes (30): axisOf(), CopyFn, differenceOrNull(), evaluateDimensions(), HoleSize, modeled, pitch, radius (+22 more)

### Community 37 - "MainWindow.cpp"
Cohesion: 0.09
Nodes (3): commandIcon(), qs(), MainWindow::applySection()

### Community 38 - "solve"
Cohesion: 0.18
Nodes (12): addConstraintChecked(), Layout, n, px, py, rad, makeLayout(), pack() (+4 more)

### Community 39 - "QObject"
Cohesion: 0.11
Nodes (8): QObject, SketchEditor::SketchEditor(), edges, Tool, op, shape, target, type

### Community 41 - "ConstraintType"
Cohesion: 0.08
Nodes (25): ConstraintType, Angle, Coincident, Collinear, Concentric, Curvature, Diameter, Distance (+17 more)

### Community 42 - "AdskModule.cpp"
Cohesion: 0.09
Nodes (15): Application, BRepBodies, BRepBody, index, Component, Design, Product, raiseIfError() (+7 more)

### Community 43 - "Pick"
Cohesion: 0.08
Nodes (18): Hit, index, kind, Pick, bodyArc, bodyPoint, bodySegment, hit (+10 more)

### Community 44 - "SketchEditor.cpp"
Cohesion: 0.11
Nodes (4): angleInArc(), ccwContains(), circumcircle(), segDistance()

### Community 45 - "Profile"
Cohesion: 0.33
Nodes (5): Profile, area, face, x, y

### Community 46 - "Zip.cpp"
Cohesion: 0.20
Nodes (13): Entry, data, name, ZipError, crc32(), deflateRaw(), get16(), get32() (+5 more)

### Community 47 - "AnalysisSettings"
Cohesion: 0.10
Nodes (16): DragArrow, base, dir, radius, ref, ring, value, PendingLook (+8 more)

### Community 48 - "Sketch.cpp"
Cohesion: 0.07
Nodes (22): SketchError, SplineKind, Conic, Control, Fit, entityTypeName(), isDimension(), Sketch::addConic() (+14 more)

### Community 49 - "Document.cpp"
Cohesion: 0.06
Nodes (46): ConstructionPlane, name, spec, bodyNumber(), Document::addBody(), Document::axisFrame(), Document::bodies(), Document::body() (+38 more)

### Community 50 - "MainWindowSketch.cpp"
Cohesion: 0.07
Nodes (15): MainWindow::cancelSketch(), MainWindow::editSketch(), MainWindow::finishSketch(), MainWindow::onEdgeClicked(), MainWindow::originalShape(), MainWindow::sketchPalette(), MainWindow::sketchVisible(), MainWindow::startSketch() (+7 more)

### Community 51 - "InputDef"
Cohesion: 0.09
Nodes (21): InputDef, choices, defaultValue, id, label, max, min, minExclusive (+13 more)

### Community 52 - "string"
Cohesion: 0.08
Nodes (24): checkBody(), checkPattern(), CircularPattern, def_, Hole, def_, jointOrigin(), JointPick (+16 more)

### Community 54 - "curve"
Cohesion: 0.16
Nodes (18): conditionedSpline(), curve(), curves(), entityCurves(), G2End, d1, d2, set (+10 more)

### Community 55 - "Document::recompute"
Cohesion: 0.22
Nodes (5): Document::openTransaction(), Document::recompute(), Document::recordFeature(), Document::setFeatureInputs(), toJson()

### Community 56 - "MarkingMenu.cpp"
Cohesion: 0.07
Nodes (22): UiCommand, enabled, icon, id, name, panel, run, shortcut (+14 more)

### Community 57 - "Command.cpp"
Cohesion: 0.14
Nodes (12): CommandSession, inputs_, expressionKey(), checkInputValue(), CommandDef::input(), CommandSession::applyInTransaction(), CommandSession::cancel(), CommandSession::execute() (+4 more)

### Community 58 - "Entity"
Cohesion: 0.09
Nodes (11): Entity, a, b, center, construction, fit, handles, included (+3 more)

### Community 59 - "xdrive.py"
Cohesion: 0.28
Nodes (15): button(), canvas(), click(), drag(), flush(), geometry(), key(), keycode() (+7 more)

### Community 62 - "Session"
Cohesion: 0.07
Nodes (6): Session, commands_, doc_, listeners_, nextListener_, path_

### Community 63 - "Theme.cpp"
Cohesion: 0.19
Nodes (6): setIconTheme(), darkColors(), darkPalette(), darkStyleSheet(), lightColors(), lightStyleSheet()

### Community 64 - "BodyFrame"
Cohesion: 0.10
Nodes (31): completeEdgeReferences(), completeFaceReferences(), decode(), decodeFaces(), dot(), edgeReference(), EdgeSig, full (+23 more)

### Community 65 - "CommandRegistry"
Cohesion: 0.14
Nodes (3): CommandRegistry, cmds_, TEST()

### Community 68 - "Theme"
Cohesion: 0.22
Nodes (4): Theme, colors_, public, styled_

### Community 69 - "optional"
Cohesion: 0.11
Nodes (18): optional, ConstructionPoint, name, point, Feature, commandId, error, id (+10 more)

### Community 70 - "InputType"
Cohesion: 0.07
Nodes (21): bindTsr(), fromPy(), toPy(), typeName(), InputType, Axis, Bodies, Body (+13 more)

### Community 71 - "ParametersDialog.cpp"
Cohesion: 0.07
Nodes (24): Column, kComment, kExpression, kName, kParameter, kStar, kUnit, kValue (+16 more)

### Community 72 - "Kernel.h"
Cohesion: 0.10
Nodes (19): Axis, X, Y, Z, BooleanOp, Cut, Intersect, Join (+11 more)

### Community 73 - "ViewportAnalysis.cpp"
Cohesion: 0.13
Nodes (5): packed(), ramp(), shade(), Viewport::buildAnalysis(), f

### Community 74 - "CommandRegistry::run"
Cohesion: 0.22
Nodes (4): CommandRegistry::add(), CommandRegistry::all(), CommandRegistry::find(), CommandRegistry::run()

### Community 75 - ".mouseMove"
Cohesion: 0.16
Nodes (7): ext(), fixedColor(), freeColor(), lineEntity(), qc(), rgb(), wire()

### Community 76 - "Vec3"
Cohesion: 0.18
Nodes (20): SurfacePoint, normal, point, Vec3, boundingBox(), edgeMidpoint(), edgesNear(), frame() (+12 more)

### Community 78 - "math"
Cohesion: 0.07
Nodes (3): dist(), check_regular(), dist_to_line()

### Community 79 - "QString"
Cohesion: 0.12
Nodes (5): ExpressionSpinBox, eval_, expression_, shown_, formatNumber()

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
Cohesion: 0.12
Nodes (19): crossings(), crossingsOf(), Curve2d, curve2d(), periodic, t0, t1, endIsFree() (+11 more)

### Community 85 - "Level"
Cohesion: 0.12
Nodes (13): debug(), error(), info(), Level, Debug, Error, Info, Warning (+5 more)

### Community 86 - "README.md"
Cohesion: 0.11
Nodes (15): Build, Conventions, Development, Tests, Reference parts, Fusion feature checklist, Roadmap, Contents (+7 more)

### Community 87 - "string"
Cohesion: 0.09
Nodes (32): DocumentError, PhysicalMaterial, color, density, name, SketchRecord, data, name (+24 more)

### Community 89 - "BodyFrame"
Cohesion: 0.14
Nodes (15): BodyFrame, diag, dx, dy, dz, x0, y0, z0 (+7 more)

### Community 90 - "Unit"
Cohesion: 0.10
Nodes (28): bindAdsk(), MainWindow::checkInterference(), MainWindow::driveJoints(), MainWindow::formatLength(), MainWindow::gridSettings(), MainWindow::lengthUnit(), MainWindow::openAnalysis(), MainWindow::openSection() (+20 more)

### Community 91 - ".initializeGL"
Cohesion: 0.15
Nodes (3): SelectionBox, crossing, height

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
Nodes (35): Body, color, display, material, name, shape, Component, bodies (+27 more)

### Community 96 - "Joints"
Cohesion: 0.36
Nodes (3): cornerAt(), Joints, parent_

### Community 97 - "cachedProfiles"
Cohesion: 0.24
Nodes (3): MainWindow::updateDragArrow(), cachedProfiles(), keyOf()

### Community 98 - "FakeDoc"
Cohesion: 0.17
Nodes (6): FakeDoc, aborts, commits, items, open, snapshot

### Community 99 - "ParamSet"
Cohesion: 0.09
Nodes (27): ModelParameter, angle, expression, input, label, name, owner, unit (+19 more)

### Community 100 - ".features"
Cohesion: 0.24
Nodes (7): Document::featureValueParameters(), Document::nextAxisName(), Document::nextComponentName(), Document::nextPlaneName(), Document::nextPointName(), Document::nextSketchName(), freeName()

### Community 101 - "MainWindow::MainWindow"
Cohesion: 0.13
Nodes (4): PythonHost, MainWindow::MainWindow(), MainWindow::exitSketchMode(), MainWindow::showPreferences()

### Community 102 - "sstream"
Cohesion: 0.22
Nodes (5): doc_(), Document::Document(), Document::ocafBytes(), ocafApplication(), Document::load()

### Community 103 - "ExpressionEnv"
Cohesion: 0.25
Nodes (5): ExpressionEnv, lengthUnit, lookup, Document::evaluateFeatureExpressions(), Document::expressionEnv()

### Community 104 - "BoundingBox"
Cohesion: 0.23
Nodes (14): BoundingBox, max, min, WallSide, Center, Side1, Side2, extendedWire() (+6 more)

### Community 106 - "SectionState"
Cohesion: 0.25
Nodes (7): SectionState, active, angle, flip, offset, plane, visible

### Community 107 - "Display"
Cohesion: 0.25
Nodes (7): Display, constraints, construction, dimensions, points, profiles, projected

### Community 108 - "cli_main.cpp"
Cohesion: 0.27
Nodes (6): listCommands(), main(), usage(), main(), smoke(), key

### Community 109 - "Architecture"
Cohesion: 0.40
Nodes (4): Architecture, How a command works, The document, Units

### Community 110 - "TopologyCounts"
Cohesion: 0.18
Nodes (16): Section, Circular, Square, Triangular, TopologyCounts, edges, faces, shells (+8 more)

### Community 112 - ".redrawAll"
Cohesion: 0.12
Nodes (4): Viewport::setCurvatureComb(), Viewport::clearDragArrow(), Viewport::clearSecondArrow(), Viewport::setInteractor()

### Community 113 - "toDxf"
Cohesion: 0.52
Nodes (6): Point, x, y, z, customPlaneSpec(), toDxf()

### Community 114 - "uninstall.sh"
Cohesion: 0.52
Nodes (6): die(), manifest_for(), refresh(), uninstall.sh script, step(), usage()

### Community 115 - "install.sh"
Cohesion: 0.60
Nodes (5): die(), refresh(), install.sh script, step(), usage()

### Community 116 - "TestFramework.h"
Cohesion: 0.12
Nodes (13): Result, error, ok, output, captured(), PYBIND11_EMBEDDED_MODULE(), PythonHost::exec(), PythonHost::PythonHost() (+5 more)

### Community 117 - ".rebuild"
Cohesion: 0.10
Nodes (12): hiddenColour(), qc(), rgb(), sharpEdges(), Style, Shaded, ShadedEdges, ShadedHidden (+4 more)

### Community 118 - "MarkingMenu"
Cohesion: 0.40
Nodes (3): MarkingMenu, enabled, public

### Community 120 - "UserParameter"
Cohesion: 0.33
Nodes (6): UserParameter, comment, expression, name, unit, value

### Community 121 - "cmath"
Cohesion: 0.15
Nodes (10): EntityType, Arc, Circle, Ellipse, Line, Spline, isRound(), Rect (+2 more)

### Community 123 - "copyEntities"
Cohesion: 0.17
Nodes (14): Placement, angle, cx, cy, dx, dy, scale, copyEntities() (+6 more)

### Community 124 - "ChainSegment"
Cohesion: 0.67
Nodes (3): ChainSegment, entity, forward

### Community 126 - "Known gaps"
Cohesion: 0.22
Nodes (8): 3D Sketch, Curvature (G2), Include 3D Geometry, Known gaps, Project to Surface, Sketch text, Splines and conics, Visual styles

### Community 127 - "Viewport::Viewport"
Cohesion: 0.18
Nodes (6): keys(), NavPreset, Fusion, SolidWorks, Tinkercad, Viewport::Viewport()

### Community 129 - "Joint"
Cohesion: 0.21
Nodes (5): Joint, asBuilt_, def_, Sweep, def_

### Community 130 - "dimensionOf"
Cohesion: 0.25
Nodes (6): Dimension, Angle, Length, Unitless, CommandContext::evaluateExpression(), dimensionOf()

### Community 142 - "SplineHandle"
Cohesion: 0.25
Nodes (8): SplineHandle, arm, index, set, tx, ty, x, y

## Knowledge Gaps
- **782 isolated node(s):** `ok`, `output`, `error`, `isReal`, `real` (+777 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 1465 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **22 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `optional` connect `optional` to `Viewport`, `dimensionOf`, `MainWindow`, `Viewport.cpp`, `SketchEditor`, `sketchFor`, `optional`, `Kernel.cpp`, `MainWindowArrow.cpp`, `Io.cpp`, `Parser`, `ViewportSketch.cpp`, `ViewportArrow.cpp`, `DocCommands.cpp`, `CommandDialog.cpp`, `Pick`, `SketchEditor.cpp`, `AnalysisSettings`, `Document.cpp`, `InputDef`, `Entity`, `SketchGeometry.cpp`, `Session`, `Kernel.h`, `Vec3`, `QString`, `SketchCurves.cpp`, `Unit`, `ReplayStep`, `Joints`, `ParamSet`, `ExpressionEnv`?**
  _High betweenness centrality (0.142) - this node is a cross-community bridge._
- **What connects `ok`, `output`, `error` to the rest of the system?**
  _782 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Viewport` be split into smaller, more focused modules?**
  _Cohesion score 0.015845477677538748 - nodes in this community are weakly interconnected._
- **Why does `Viewport` connect `Viewport` to `ViewportArrow.cpp`, `MainWindow`, `optional`, `Viewport.cpp`, `ViewportAnalysis.cpp`, `optional`, `AnalysisSettings`, `AnalysisSettings`, `SketchDisplay`, `.redrawAll`, `SketchCurves.cpp`, `.rebuild`, `.toPixels`, `Unit`, `.initializeGL`, `Viewport::Viewport`?**
  _High betweenness centrality (0.123) - this node is a cross-community bridge._
- **Should `Icons.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.05254926493587739 - nodes in this community are weakly interconnected._
- **Why does `SketchEditor` connect `SketchEditor` to `Viewport`, `ViewportArrow.cpp`, `Constraint`, `optional`, `Unit`, `QObject`, `Display`, `optional`, `Pick`, `.mouseMove`, `SketchEditor.cpp`, `Snap`, `Entity`, `Session`?**
  _High betweenness centrality (0.109) - this node is a cross-community bridge._
- **Should `Session.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.11951219512195121 - nodes in this community are weakly interconnected._