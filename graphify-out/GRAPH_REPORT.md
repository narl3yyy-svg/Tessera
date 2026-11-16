# Graph Report - tessera  (2026-11-16)

## Corpus Check
- 404 files · ~268,993 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 64 file(s) not represented in the graph (top: .drive 56, (none) 5, .cmake 1)

## Summary
- 3810 nodes · 9784 edges · 146 communities (120 shown, 26 thin omitted)
- Extraction: 85% EXTRACTED · 15% INFERRED · 0% AMBIGUOUS · INFERRED: 1500 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `55f72c69`
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
- DocumentError
- optional
- Kernel.cpp
- AnalysisSettings
- Kind
- MainWindowArrow.cpp
- CommandDialog
- Io.cpp
- Parser
- Snap
- Document
- Snap
- MainWindow::lookTargets
- Affine
- ViewportSketch.cpp
- SketchPalette
- Sketch
- Inputs
- CommandContext
- Colors
- KernelError
- SketchOps.cpp
- Viewport::setDragArrow
- ParameterCompleter
- Constraint
- DocCommands.cpp
- qs
- solve
- .eventFilter
- CommandDialog.cpp
- ConstraintType
- AdskModule.cpp
- Pick
- SketchEditor.cpp
- Unit
- Zip.cpp
- AnalysisSettings
- Sketch.cpp
- Document.cpp
- MainWindowSketch.cpp
- InputDef
- .updatePreview
- .toPixels
- Document::recompute
- MetricSize
- curve
- Entity
- xdrive.py
- UiCommand
- Session
- Theme.cpp
- BodyFrame
- CommandRegistry
- path
- TEST
- Theme
- Feature
- InputType
- ParametersDialog.cpp
- smoke
- Viewport.h
- QMouseEvent
- .mouseMove
- Vec3
- MainWindow::MainWindow
- math
- QString
- SketchDisplay
- Command
- Measurement
- SketchCurves.cpp
- Level
- README.md
- .OnSelectionChanged
- test_feature_pattern.py
- BodyFrame
- QDialog
- rect
- FileFormat
- Known differences still to build
- TEST
- ReplayStep
- SketchRecord
- cachedProfiles
- FakeDoc
- ParamSet
- .openMarkingMenu
- Document::load
- MainWindow::onEdgeClicked
- BoundingBox
- test_rigid_group.py
- SectionState
- Display
- cli_main.cpp
- Mesh
- TopologyCounts
- .initializeGL
- .redrawAll
- toDxf
- uninstall.sh
- install.sh
- TestFramework.h
- .rebuild
- MainWindow.cpp
- Known gaps
- EntityType
- test_incremental_replay.py
- Placement
- includeEdges
- CommandDialog::CommandDialog
- Column
- ExpressionEnv
- .bodyFaces
- Profile
- Architecture
- BRepBody
- LAB_NOTES.md
- Axis
- BooleanOp
- build.sh
- live-test.sh
- ThreadInfo
- PYBIND11_EMBEDDED_MODULE
- SplineHandle
- ChamferType
- ChainSegment
- test_text_box_path.py

## God Nodes (most connected - your core abstractions)
1. `Viewport` - 257 edges
2. `SketchEditor` - 198 edges
3. `MainWindow` - 184 edges
4. `Inputs` - 155 edges
5. `render()` - 123 edges
6. `Document` - 121 edges
7. `CommandContext` - 114 edges
8. `CommandDialog` - 90 edges
9. `Command` - 67 edges
10. `CommandError` - 64 edges

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

## Communities (146 total, 26 thin omitted)

### Community 0 - "Viewport"
Cohesion: 0.02
Nodes (69): view_, QLineEdit, Viewport, analysis_, analysisObjects_, appliedGridStep_, arrowBoxes_, arrowDragging_ (+61 more)

### Community 1 - "Icons.cpp"
Cohesion: 0.05
Nodes (128): accessibilityIcon(), appearanceIcon(), arc3Icon(), arcIcon(), arcTangentIcon(), arrow(), axisIcon(), box() (+120 more)

### Community 2 - "Session.cpp"
Cohesion: 0.06
Nodes (50): CommandSession, inputs_, expressionKey(), checkInputValue(), CommandContext::evaluateExpression(), CommandDef::input(), CommandSession::applyInTransaction(), CommandSession::cancel() (+42 more)

### Community 4 - "MainWindow"
Cohesion: 0.03
Nodes (64): writeLiveGeometry(), CommandDialog, MainWindow, active_, arrowInput_, arrowInput2_, bodiesBeforeCommand_, combEdges_ (+56 more)

### Community 5 - "run_oracle.py"
Cohesion: 0.08
Nodes (54): add_point(), arc_poly(), body_at(), body_list(), build_sketch(), chain(), circumcentre(), cm() (+46 more)

### Community 6 - "Expression.cpp"
Cohesion: 0.16
Nodes (12): ExpressionError, evaluateExpression(), evaluateQuantity(), expressionReferences(), isConstantName(), isFunctionName(), isPlainQuantity(), isValidParameterName() (+4 more)

### Community 7 - "Document"
Cohesion: 0.03
Nodes (15): Document, effects_, lastReplayed_, lastReused_, modified_, pendingTools_, registry_, replaying_ (+7 more)

### Community 8 - "Viewport.cpp"
Cohesion: 0.06
Nodes (5): glide(), keys(), QKeyEvent, Viewport::frontEdgeOwner(), Viewport::Viewport()

### Community 9 - "SketchEditor"
Cohesion: 0.03
Nodes (60): HandleHit, back, index, spline, Hit, index, kind, SketchEditor (+52 more)

### Community 10 - "DocumentError"
Cohesion: 0.09
Nodes (29): DocumentError, PhysicalMaterial, color, density, name, checkViewName(), Document::abortTransaction(), Document::addBody() (+21 more)

### Community 11 - "optional"
Cohesion: 0.08
Nodes (6): optional, isEmpty(), Value, CommandRegistry::all(), fail(), Failure

### Community 12 - "Kernel.cpp"
Cohesion: 0.04
Nodes (3): isoCoarsePitch(), topologyCounts(), wrapOntoCylinder()

### Community 13 - "AnalysisSettings"
Cohesion: 0.11
Nodes (18): AnalysisKind, Accessibility, CurvatureMap, Draft, Isocurve, MinimumRadius, None, Zebra (+10 more)

### Community 14 - "Kind"
Cohesion: 0.06
Nodes (32): ConstructPlane, def_, kind_, EdgeFeature, def_, kind_, FaceFeature, def_ (+24 more)

### Community 15 - "MainWindowArrow.cpp"
Cohesion: 0.14
Nodes (8): ArrowPlacement, base, dir, edgePlacement(), facesPlacement(), MainWindow::attachArrowCompleters(), MainWindow::patternCentre(), MainWindow::pickedFaces()

### Community 16 - "CommandDialog"
Cohesion: 0.05
Nodes (31): CommandDialog, bodiesId_, bodiesLabel_, bodyInput_, buttons_, cmd_, conditional_, edgesId_ (+23 more)

### Community 17 - "Io.cpp"
Cohesion: 0.10
Nodes (8): formatForPath(), fromBrep(), importShape(), lower(), meshOf(), scaled(), toBrep(), xmlEscape()

### Community 18 - "Parser"
Cohesion: 0.18
Nodes (15): Quantity, angle, length, value, describe(), isIdentChar(), isIdentStart(), Parser (+7 more)

### Community 19 - "Snap"
Cohesion: 0.09
Nodes (21): HudField, edit, editing, kind, locked, value, Kind, Angle (+13 more)

### Community 21 - "Document"
Cohesion: 0.24
Nodes (7): ConstructAxisPoint, def_, kind_, jointOrigin(), JointPick, frame, revolveAxis()

### Community 22 - "Snap"
Cohesion: 0.11
Nodes (18): Snap, alignX, alignY, bodyArc, bodySegment, entity, fromX, fromY (+10 more)

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

### Community 28 - "Inputs"
Cohesion: 0.12
Nodes (22): CommandError, Inputs, getBool(), getInt(), getReal(), applyOperation(), bodyCentre(), bodyName() (+14 more)

### Community 29 - "CommandContext"
Cohesion: 0.06
Nodes (18): CommandContext, AddUserParameter, def_, checkBody(), checkPattern(), isIdentifier(), NewComponent, def_ (+10 more)

### Community 30 - "Colors"
Cohesion: 0.07
Nodes (28): Colors, base, border, cubeBox, cubeText, errorBackground, grid, gridMajor (+20 more)

### Community 31 - "KernelError"
Cohesion: 0.21
Nodes (32): KernelError, asSolid(), boolean(), chamfer(), chamferEx(), deleteFaces(), draft(), embossTool() (+24 more)

### Community 32 - "SketchOps.cpp"
Cohesion: 0.17
Nodes (28): at(), chainOf(), chamferCorner(), circularPattern(), copyEntities(), cornerAt(), cross(), dot() (+20 more)

### Community 33 - "Viewport::setDragArrow"
Cohesion: 0.18
Nodes (4): Viewport::DragArrow::handle(), Viewport::emitArrow(), Viewport::setDragArrow(), Viewport::setDragRing()

### Community 34 - "ParameterCompleter"
Cohesion: 0.12
Nodes (8): ParameterCompleter, completer_, edit_, names_, ParameterCompleter::ParameterCompleter(), public, QCompleter, QLineEdit

### Community 35 - "Constraint"
Cohesion: 0.07
Nodes (29): Constraint, driven, entities, expression, hasLabel, labelX, labelY, name (+21 more)

### Community 36 - "DocCommands.cpp"
Cohesion: 0.10
Nodes (30): axisOf(), CopyFn, differenceOrNull(), evaluateDimensions(), HoleSize, modeled, pitch, radius (+22 more)

### Community 37 - "qs"
Cohesion: 0.11
Nodes (3): commandIcon(), qs(), MainWindow::applySection()

### Community 38 - "solve"
Cohesion: 0.12
Nodes (14): addConstraintChecked(), Layout, n, px, py, rad, makeLayout(), pack() (+6 more)

### Community 39 - ".eventFilter"
Cohesion: 0.13
Nodes (4): QObject, SketchEditor::SketchEditor(), edges, type

### Community 41 - "ConstraintType"
Cohesion: 0.07
Nodes (27): ConstraintType, Angle, Coincident, Collinear, Concentric, Curvature, Diameter, Distance (+19 more)

### Community 42 - "AdskModule.cpp"
Cohesion: 0.10
Nodes (14): Application, BRepBodies, Component, Design, Product, raiseIfError(), UserParameter, name (+6 more)

### Community 43 - "Pick"
Cohesion: 0.08
Nodes (20): Pick, bodyArc, bodyPoint, bodySegment, hit, midpointOf, onEntity, onXAxis (+12 more)

### Community 45 - "Unit"
Cohesion: 0.11
Nodes (16): bindAdsk(), MainWindow::lengthUnit(), Unit, Centimeter, Degree, Foot, Inch, Meter (+8 more)

### Community 46 - "Zip.cpp"
Cohesion: 0.25
Nodes (10): ZipError, crc32(), deflateRaw(), get16(), get32(), inflateRaw(), put16(), put32() (+2 more)

### Community 47 - "AnalysisSettings"
Cohesion: 0.10
Nodes (16): DragArrow, base, dir, radius, ref, ring, value, PendingLook (+8 more)

### Community 48 - "Sketch.cpp"
Cohesion: 0.08
Nodes (19): SketchError, SplineKind, Conic, Control, Fit, entityTypeName(), isDimension(), Sketch::addConstraint() (+11 more)

### Community 49 - "Document.cpp"
Cohesion: 0.07
Nodes (40): ConstructionPlane, name, spec, bodyNumber(), Document::axisFrame(), Document::bodies(), Document::body(), Document::bodyName() (+32 more)

### Community 50 - "MainWindowSketch.cpp"
Cohesion: 0.10
Nodes (8): MainWindow::cancelSketch(), MainWindow::editSketch(), MainWindow::finishSketch(), MainWindow::sketchPalette(), MainWindow::sketchVisible(), MainWindow::startSketch(), MainWindow::updateProfilePicking(), qs()

### Community 51 - "InputDef"
Cohesion: 0.09
Nodes (21): InputDef, choices, defaultValue, id, label, max, min, minExclusive (+13 more)

### Community 52 - ".updatePreview"
Cohesion: 0.14
Nodes (4): ccwContains(), circumcircle(), ext(), Sketch::addLine()

### Community 55 - "Document::recompute"
Cohesion: 0.17
Nodes (9): Document::feature(), Document::nextPlaneName(), Document::recompute(), Document::recordFeature(), Document::removeFeature(), Document::setFeatureInputs(), Document::setFeatureSuppressed(), featureData() (+1 more)

### Community 56 - "MetricSize"
Cohesion: 0.15
Nodes (10): MarkingMenu::keyPressEvent(), MarkingMenu::MarkingMenu(), MarkingMenu::run(), MetricSize, close, d, loose, name (+2 more)

### Community 57 - "curve"
Cohesion: 0.19
Nodes (17): conditionedSpline(), curve(), curves(), entityCurves(), G2End, d1, d2, set (+9 more)

### Community 58 - "Entity"
Cohesion: 0.10
Nodes (11): Entity, a, b, center, construction, fit, handles, included (+3 more)

### Community 59 - "xdrive.py"
Cohesion: 0.28
Nodes (15): button(), canvas(), click(), drag(), flush(), geometry(), key(), keycode() (+7 more)

### Community 61 - "UiCommand"
Cohesion: 0.13
Nodes (12): UiCommand, enabled, icon, id, name, panel, run, shortcut (+4 more)

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

### Community 66 - "path"
Cohesion: 0.47
Nodes (8): MainWindow::print3d(), NamedShape, compoundOf(), exportShapes(), fmt(), write3mf(), writeObj(), path

### Community 67 - "TEST"
Cohesion: 0.09
Nodes (3): param(), TEST(), tmp()

### Community 68 - "Theme"
Cohesion: 0.22
Nodes (4): Theme, colors_, public, styled_

### Community 69 - "Feature"
Cohesion: 0.10
Nodes (15): Feature, commandId, error, id, inputs, name, parameterNames, rolledBack (+7 more)

### Community 70 - "InputType"
Cohesion: 0.08
Nodes (21): bindTsr(), fromPy(), toPy(), typeName(), InputType, Axis, Bodies, Body (+13 more)

### Community 71 - "ParametersDialog.cpp"
Cohesion: 0.08
Nodes (14): ParametersDialog, building_, error_, filter_, listener_, ParametersDialog::ParametersDialog(), public, rebuildPending_ (+6 more)

### Community 72 - "smoke"
Cohesion: 0.33
Nodes (6): smoke(), key, MassProperties, area, centerOfMass, volume

### Community 73 - "Viewport.h"
Cohesion: 0.05
Nodes (12): QLabel, packed(), ramp(), shade(), Viewport::buildAnalysis(), segmentDistance(), Viewport::arrowAt(), Viewport::arrowParam() (+4 more)

### Community 74 - "QMouseEvent"
Cohesion: 0.14
Nodes (8): QMouseEvent, ViewInteractor, Viewport::arrowMouseMove(), Viewport::arrowMousePress(), Viewport::arrowMouseRelease(), Viewport::dragArrowForTest(), Viewport::rebuildArrows(), Viewport::setInteractor()

### Community 75 - ".mouseMove"
Cohesion: 0.20
Nodes (6): fixedColor(), freeColor(), lineEntity(), qc(), rgb(), wire()

### Community 76 - "Vec3"
Cohesion: 0.18
Nodes (20): SurfacePoint, normal, point, Vec3, boundingBox(), edgeMidpoint(), edgesNear(), frame() (+12 more)

### Community 77 - "MainWindow::MainWindow"
Cohesion: 0.13
Nodes (4): PythonHost, MainWindow::MainWindow(), MainWindow::exitSketchMode(), MainWindow::showPreferences()

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
Cohesion: 0.03
Nodes (58): Adding a tool, Command, CommandDef, feature, icon, id, inputs, name (+50 more)

### Community 82 - "Measurement"
Cohesion: 0.13
Nodes (14): Kind, Angle, Area, Length, Volume, Measurement, from, hasLine (+6 more)

### Community 83 - "SketchCurves.cpp"
Cohesion: 0.14
Nodes (17): crossings(), crossingsOf(), Curve2d, curve2d(), periodic, t0, t1, endIsFree() (+9 more)

### Community 85 - "Level"
Cohesion: 0.16
Nodes (13): debug(), error(), info(), Level, Debug, Error, Info, Warning (+5 more)

### Community 86 - "README.md"
Cohesion: 0.11
Nodes (15): Build, Conventions, Development, Tests, Reference parts, Fusion feature checklist, Roadmap, Contents (+7 more)

### Community 89 - "BodyFrame"
Cohesion: 0.14
Nodes (15): BodyFrame, diag, dx, dy, dz, x0, y0, z0 (+7 more)

### Community 90 - "QDialog"
Cohesion: 0.09
Nodes (23): QDialog, MainWindow::checkInterference(), MainWindow::chooseUnits(), MainWindow::driveJoints(), MainWindow::editAppearance(), MainWindow::editMaterial(), MainWindow::exportDesign(), MainWindow::formatLength() (+15 more)

### Community 91 - "rect"
Cohesion: 0.28
Nodes (3): SelectionBox, crossing, rect()

### Community 92 - "FileFormat"
Cohesion: 0.17
Nodes (12): FileFormat, Brep, Iges, Obj, Step, Stl, ThreeMF, FormatInfo (+4 more)

### Community 93 - "Known differences still to build"
Cohesion: 0.15
Nodes (12): Data and files, Findings from the videos, Fusion study list, Interface, Known differences still to build, Navigation and display, Selection and the canvas, Sketch (+4 more)

### Community 94 - "TEST"
Cohesion: 0.14
Nodes (6): Entry, data, name, slurp(), TEST(), tmp()

### Community 95 - "ReplayStep"
Cohesion: 0.05
Nodes (43): Body, color, display, material, name, shape, Component, bodies (+35 more)

### Community 96 - "SketchRecord"
Cohesion: 0.14
Nodes (11): SketchRecord, data, name, offset, plane, Document::nextSketchName(), Document::renameSketch(), Document::setSketch() (+3 more)

### Community 97 - "cachedProfiles"
Cohesion: 0.20
Nodes (3): MainWindow::updateDragArrow(), cachedProfiles(), keyOf()

### Community 98 - "FakeDoc"
Cohesion: 0.17
Nodes (6): FakeDoc, aborts, commits, items, open, snapshot

### Community 99 - "ParamSet"
Cohesion: 0.07
Nodes (33): Dimension, Angle, Length, Unitless, dimensionOf(), ModelParameter, angle, expression (+25 more)

### Community 101 - ".openMarkingMenu"
Cohesion: 0.08
Nodes (6): MainWindow::beginSketch(), MainWindow::buildSketchTab(), MainWindow::enterSketchMode(), MainWindow::buildUiCommands(), QTimer, Viewport::selectArrowValue()

### Community 102 - "Document::load"
Cohesion: 0.17
Nodes (5): doc_(), Document::Document(), Document::ocafBytes(), ocafApplication(), Document::load()

### Community 103 - "MainWindow::onEdgeClicked"
Cohesion: 0.21
Nodes (5): MainWindow::onEdgeClicked(), MainWindow::onProfileClicked(), MainWindow::originalShape(), MainWindow::syncPickedShapes(), MainWindow::toOriginal()

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
Cohesion: 0.36
Nodes (4): listCommands(), main(), usage(), main()

### Community 109 - "Mesh"
Cohesion: 0.40
Nodes (3): Mesh, nodes, triangles

### Community 110 - "TopologyCounts"
Cohesion: 0.16
Nodes (17): Section, Circular, Square, Triangular, TopologyCounts, edges, faces, shells (+9 more)

### Community 112 - ".redrawAll"
Cohesion: 0.11
Nodes (7): NavPreset, Fusion, SolidWorks, Tinkercad, Viewport::setCurvatureComb(), Viewport::clearDragArrow(), Viewport::clearSecondArrow()

### Community 113 - "toDxf"
Cohesion: 0.43
Nodes (7): Point, x, y, z, customPlaneSpec(), planeFrame(), toDxf()

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
Cohesion: 0.09
Nodes (12): hiddenColour(), qc(), rgb(), sharpEdges(), Style, Shaded, ShadedEdges, ShadedHidden (+4 more)

### Community 118 - "MainWindow.cpp"
Cohesion: 0.04
Nodes (15): QAbstractButton, QAction, grabWindowWithPanels(), MainWindow::insertFile(), MainWindow::sectionFrame(), MainWindow::sectionPlane(), MainWindow::showParameters(), MainWindow::updateSectionArrow() (+7 more)

### Community 120 - "Known gaps"
Cohesion: 0.20
Nodes (9): 3D Sketch, Curvature (G2), Emboss, Include 3D Geometry, Known gaps, Project to Surface, Sketch text, Splines and conics (+1 more)

### Community 121 - "EntityType"
Cohesion: 0.29
Nodes (7): EntityType, Arc, Circle, Ellipse, Line, Spline, isRound()

### Community 123 - "Placement"
Cohesion: 0.25
Nodes (7): Placement, angle, cx, cy, dx, dy, scale

### Community 124 - "includeEdges"
Cohesion: 0.24
Nodes (4): includeEdges(), projectToSurface(), interiorPoint(), toSketch()

### Community 126 - "Column"
Cohesion: 0.25
Nodes (8): Column, kComment, kExpression, kName, kParameter, kStar, kUnit, kValue

### Community 127 - "ExpressionEnv"
Cohesion: 0.25
Nodes (5): ExpressionEnv, lengthUnit, lookup, Document::evaluateFeatureExpressions(), Document::expressionEnv()

### Community 129 - ".bodyFaces"
Cohesion: 0.15
Nodes (7): Extrude, def_, Joint, asBuilt_, def_, Sweep, def_

### Community 130 - "Profile"
Cohesion: 0.33
Nodes (5): Profile, area, face, x, y

### Community 131 - "Architecture"
Cohesion: 0.40
Nodes (4): Architecture, How a command works, The document, Units

### Community 134 - "Axis"
Cohesion: 0.50
Nodes (4): Axis, X, Y, Z

### Community 135 - "BooleanOp"
Cohesion: 0.50
Nodes (4): BooleanOp, Cut, Intersect, Join

### Community 139 - "ThreadInfo"
Cohesion: 0.50
Nodes (4): ThreadInfo, diameter, internal, pitch

### Community 142 - "SplineHandle"
Cohesion: 0.25
Nodes (8): SplineHandle, arm, index, set, tx, ty, x, y

### Community 143 - "ChamferType"
Cohesion: 0.67
Nodes (3): ChamferType, DistanceAngle, TwoDistances

### Community 144 - "ChainSegment"
Cohesion: 0.67
Nodes (3): ChainSegment, entity, forward

## Knowledge Gaps
- **783 isolated node(s):** `ok`, `output`, `error`, `isReal`, `real` (+778 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 1479 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **26 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `optional` connect `optional` to `Viewport`, `MainWindow`, `SketchEditor`, `Kernel.cpp`, `MainWindowArrow.cpp`, `Io.cpp`, `Parser`, `ViewportSketch.cpp`, `CommandContext`, `SketchOps.cpp`, `DocCommands.cpp`, `.eventFilter`, `CommandDialog.cpp`, `SketchEditor.cpp`, `Unit`, `AnalysisSettings`, `Document.cpp`, `InputDef`, `.updatePreview`, `SketchGeometry.cpp`, `Document::recompute`, `Entity`, `Session`, `Feature`, `Viewport.h`, `.mouseMove`, `Vec3`, `QString`, `SketchCurves.cpp`, `ReplayStep`, `SketchRecord`, `ParamSet`, `ExpressionEnv`?**
  _High betweenness centrality (0.143) - this node is a cross-community bridge._
- **What connects `ok`, `output`, `error` to the rest of the system?**
  _783 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Viewport` be split into smaller, more focused modules?**
  _Cohesion score 0.0159809183064997 - nodes in this community are weakly interconnected._
- **Why does `Viewport` connect `Viewport` to `MainWindow`, `Viewport.cpp`, `optional`, `AnalysisSettings`, `Viewport::setDragArrow`, `AdskModule.cpp`, `AnalysisSettings`, `.toPixels`, `Viewport.h`, `QMouseEvent`, `SketchDisplay`, `SketchCurves.cpp`, `.OnSelectionChanged`, `QDialog`, `rect`, `.openMarkingMenu`, `.initializeGL`, `.redrawAll`, `.rebuild`?**
  _High betweenness centrality (0.125) - this node is a cross-community bridge._
- **Should `Icons.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.05210688591983556 - nodes in this community are weakly interconnected._
- **Why does `SketchEditor` connect `SketchEditor` to `Viewport`, `Constraint`, `.eventFilter`, `QMouseEvent`, `Display`, `Pick`, `optional`, `.mouseMove`, `SketchEditor.cpp`, `Unit`, `Snap`, `.solveAndShow`, `.updatePreview`, `Snap`, `Entity`, `Session`?**
  _High betweenness centrality (0.112) - this node is a cross-community bridge._
- **Should `Session.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.05627545353572751 - nodes in this community are weakly interconnected._