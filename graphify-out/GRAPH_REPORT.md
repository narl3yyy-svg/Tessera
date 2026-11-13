# Graph Report - tessera  (2026-11-13)

## Corpus Check
- 368 files · ~226,024 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 52 file(s) not represented in the graph (top: .drive 44, (none) 5, .cmake 1)

## Summary
- 3440 nodes · 8647 edges · 133 communities (108 shown, 25 thin omitted)
- Extraction: 85% EXTRACTED · 15% INFERRED · 0% AMBIGUOUS · INFERRED: 1298 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `6938d9c3`
- Run `git rev-parse HEAD` and compare to check if the graph is stale.
- Run `graphify update .` after code changes (no API cost).

## Community Hubs (Navigation)
- Viewport
- Icons.cpp
- Session.cpp
- tsr
- MainWindow
- run_oracle.py
- Inputs
- Document
- Viewport.cpp
- SketchEditor
- ext
- optional
- Kernel.cpp
- vector
- Kind
- TEST
- CommandDialog
- exportShapes
- Unit
- MainWindowTools.cpp
- Handle
- Document
- MainWindow::MainWindow
- TEST
- Sketch.cpp
- ViewportSketch.cpp
- SketchPalette
- Snap
- CommandError
- DocumentError
- Colors
- KernelError
- SketchOps.cpp
- Unit
- ParameterCompleter
- Constraint
- Expression.cpp
- MainWindow.cpp
- solve
- QString
- ConstraintType
- AdskModule.cpp
- Pick
- .updatePreview
- .openMarkingMenu
- Zip.cpp
- AnalysisSettings
- Document.cpp
- SketchRecord
- MainWindowSketch.cpp
- InputDef
- .rebuild
- .toPixels
- MainWindowArrow.cpp
- Viewport.h
- Theme.cpp
- .applyPreSelection
- Entity
- xdrive.py
- SketchGeometry.cpp
- Session
- QMouseEvent
- BodyFrame
- CommandRegistry
- cmath
- requirePositive
- Theme
- src/main.cpp
- src/main.cpp
- smoke
- FileFormat
- SketchEditor.cpp
- InputType
- Vec3
- CommandDialog::CommandDialog
- Architecture
- SketchDisplay
- DocCommands.cpp
- Measurement
- .redrawAll
- Push
- Level
- README.md
- Document.cpp
- test_feature_pattern.py
- Tool
- .add
- MarkingMenu.cpp
- gp_Ax3
- Known differences still to build
- MainWindowTools.cpp
- Feature
- .initializeGL
- EdgeSig
- FakeDoc
- CommandDialog.cpp
- Viewport::setDragArrow
- sstream
- rect
- gp_Pnt
- Joints
- SectionState
- Display
- EntityType
- PlaneEdges
- openWallBand
- Profile
- Mesh
- Axis
- uninstall.sh
- install.sh
- PYBIND11_EMBEDDED_MODULE
- main
- BooleanOp
- ThreadInfo
- fail
- ChamferType
- Placement
- ChainSegment
- LAB_NOTES.md
- ParameterCompleter.cpp
- bindAdsk
- build.sh
- live-test.sh
- MarkingMenu.cpp

## God Nodes (most connected - your core abstractions)
1. `Viewport` - 251 edges
2. `SketchEditor` - 178 edges
3. `MainWindow` - 175 edges
4. `Inputs` - 138 edges
5. `render()` - 105 edges
6. `Document` - 104 edges
7. `CommandContext` - 102 edges
8. `CommandDialog` - 90 edges
9. `Command` - 63 edges
10. `CommandDef` - 56 edges

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

## Communities (133 total, 25 thin omitted)

### Community 0 - "Viewport"
Cohesion: 0.02
Nodes (67): view_, QLineEdit, Viewport, analysis_, analysisObjects_, appliedGridStep_, arrowBoxes_, arrowDragging_ (+59 more)

### Community 1 - "Icons.cpp"
Cohesion: 0.06
Nodes (110): arc3Icon(), arcIcon(), arcTangentIcon(), arrow(), axisIcon(), box(), breakIcon(), centerRectIcon() (+102 more)

### Community 2 - "Session.cpp"
Cohesion: 0.06
Nodes (48): CommandSession, inputs_, expressionKey(), checkInputValue(), CommandContext::evaluateExpression(), CommandDef::input(), CommandSession::applyInTransaction(), CommandSession::cancel() (+40 more)

### Community 4 - "MainWindow"
Cohesion: 0.03
Nodes (64): writeLiveGeometry(), CommandDialog, MainWindow, active_, arrowInput_, arrowInput2_, bodiesBeforeCommand_, combEdges_ (+56 more)

### Community 5 - "run_oracle.py"
Cohesion: 0.08
Nodes (54): add_point(), arc_poly(), body_at(), body_list(), build_sketch(), chain(), circumcentre(), cm() (+46 more)

### Community 6 - "Inputs"
Cohesion: 0.07
Nodes (19): CommandContext, Inputs, CommandSession::CommandSession(), getInt(), AddUserParameter, def_, checkBody(), checkPattern() (+11 more)

### Community 7 - "Document"
Cohesion: 0.03
Nodes (11): Document, effects_, modified_, pendingTools_, registry_, replaying_, txnBodies_, FromOcaf (+3 more)

### Community 8 - "Viewport.cpp"
Cohesion: 0.06
Nodes (4): keys(), QKeyEvent, Viewport::frontEdgeOwner(), Viewport::Viewport()

### Community 9 - "SketchEditor"
Cohesion: 0.03
Nodes (52): HudField, edit, editing, kind, locked, value, QLineEdit, SketchEditor (+44 more)

### Community 10 - "ext"
Cohesion: 0.08
Nodes (24): SketchRecord, data, name, offset, plane, Document::feature(), Document::historyMarker(), Document::nextPlaneName() (+16 more)

### Community 11 - "optional"
Cohesion: 0.10
Nodes (4): optional, isEmpty(), Value, CommandRegistry::all()

### Community 12 - "Kernel.cpp"
Cohesion: 0.04
Nodes (5): isoCoarsePitch(), massProperties(), measure(), polygonToCircleLoft(), topologyCounts()

### Community 13 - "vector"
Cohesion: 0.13
Nodes (13): Loft, def_, NewComponent, def_, openChains(), parsePoints(), pickedFaces(), profilesOf() (+5 more)

### Community 14 - "Kind"
Cohesion: 0.09
Nodes (22): ConstructPlane, def_, kind_, EdgeFeature, def_, kind_, Kind, Angle (+14 more)

### Community 15 - "TEST"
Cohesion: 0.09
Nodes (3): param(), TEST(), tmp()

### Community 16 - "CommandDialog"
Cohesion: 0.05
Nodes (31): CommandDialog, bodiesId_, bodiesLabel_, bodyInput_, buttons_, cmd_, conditional_, edgesId_ (+23 more)

### Community 17 - "exportShapes"
Cohesion: 0.22
Nodes (15): MainWindow::print3d(), NamedShape, compoundOf(), exportShapes(), fmt(), formatForPath(), fromBrep(), importShape() (+7 more)

### Community 18 - "Unit"
Cohesion: 0.18
Nodes (14): Quantity, angle, length, value, describe(), isIdentChar(), isIdentStart(), Parser (+6 more)

### Community 19 - "MainWindowTools.cpp"
Cohesion: 0.10
Nodes (19): QDialog, MainWindow::checkInterference(), MainWindow::chooseUnits(), MainWindow::driveJoints(), MainWindow::exportDesign(), MainWindow::formatLength(), MainWindow::gridSettings(), MainWindow::openAnalysis() (+11 more)

### Community 21 - "Document"
Cohesion: 0.19
Nodes (7): ConstructAxisPoint, def_, kind_, differenceOrNull(), JointPick, frame, revolveAxis()

### Community 22 - "MainWindow::MainWindow"
Cohesion: 0.13
Nodes (4): PythonHost, MainWindow::MainWindow(), MainWindow::exitSketchMode(), MainWindow::showPreferences()

### Community 23 - "TEST"
Cohesion: 0.06
Nodes (11): Point, x, y, Sketch, constraints, entities, points, texts (+3 more)

### Community 24 - "Sketch.cpp"
Cohesion: 0.08
Nodes (19): SketchError, SplineKind, Conic, Control, Fit, entityTypeName(), isDimension(), Sketch::addConstraint() (+11 more)

### Community 25 - "ViewportSketch.cpp"
Cohesion: 0.06
Nodes (12): segmentDistance(), Viewport::arrowAt(), Viewport::arrowParam(), Viewport::dragArrowHandle(), Viewport::placeArrowBoxes(), faceStyle(), lineStyle(), rgb() (+4 more)

### Community 26 - "SketchPalette"
Cohesion: 0.07
Nodes (24): QCheckBox, QLabel, QWidget, SketchEditor, SketchPalette, body_, constraints_, construction_ (+16 more)

### Community 27 - "Snap"
Cohesion: 0.05
Nodes (35): Hit, index, kind, Kind, Angle, BodyEdge, BodyVertex, Count (+27 more)

### Community 28 - "CommandError"
Cohesion: 0.09
Nodes (29): CommandError, getBool(), getReal(), applyOperation(), bodyCentre(), bodyName(), Coil, def_ (+21 more)

### Community 29 - "DocumentError"
Cohesion: 0.12
Nodes (22): DocumentError, checkViewName(), Document::abortTransaction(), Document::addNamedView(), Document::addUserParameter(), Document::commitTransaction(), Document::removeBody(), Document::removeNamedView() (+14 more)

### Community 30 - "Colors"
Cohesion: 0.07
Nodes (28): Colors, base, border, cubeBox, cubeText, errorBackground, grid, gridMajor (+20 more)

### Community 31 - "KernelError"
Cohesion: 0.28
Nodes (25): KernelError, asSolid(), boolean(), chamfer(), chamferEx(), draft(), extrude(), extrudeEx() (+17 more)

### Community 32 - "SketchOps.cpp"
Cohesion: 0.22
Nodes (25): at(), chainOf(), chamferCorner(), circularPattern(), copyEntities(), cross(), dot(), extendLine() (+17 more)

### Community 33 - "Unit"
Cohesion: 0.13
Nodes (19): formatNumber(), MainWindow::lengthUnit(), Dimension, Angle, Length, Unitless, Unit, Centimeter (+11 more)

### Community 34 - "ParameterCompleter"
Cohesion: 0.21
Nodes (8): QObject, ParameterCompleter, completer_, edit_, names_, public, QCompleter, QLineEdit

### Community 35 - "Constraint"
Cohesion: 0.07
Nodes (25): Constraint, driven, entities, expression, hasLabel, labelX, labelY, name (+17 more)

### Community 36 - "Expression.cpp"
Cohesion: 0.13
Nodes (17): ExpressionEnv, lengthUnit, lookup, ExpressionError, evaluateExpression(), evaluateQuantity(), expressionReferences(), isConstantName() (+9 more)

### Community 37 - "MainWindow.cpp"
Cohesion: 0.12
Nodes (5): commandIcon(), flatButton(), qs(), MainWindow::applySection(), QToolButton

### Community 38 - "solve"
Cohesion: 0.18
Nodes (12): addConstraintChecked(), Layout, n, px, py, rad, makeLayout(), pack() (+4 more)

### Community 40 - "QString"
Cohesion: 0.13
Nodes (4): ExpressionSpinBox, eval_, expression_, shown_

### Community 41 - "ConstraintType"
Cohesion: 0.08
Nodes (25): ConstraintType, Angle, Coincident, Collinear, Concentric, Diameter, Distance, Equal (+17 more)

### Community 42 - "AdskModule.cpp"
Cohesion: 0.08
Nodes (18): Application, BRepBodies, Component, Design, Product, raiseIfError(), UserParameter, name (+10 more)

### Community 43 - "Pick"
Cohesion: 0.12
Nodes (14): Pick, bodyArc, bodyPoint, bodySegment, hit, midpointOf, onEntity, onXAxis (+6 more)

### Community 44 - ".updatePreview"
Cohesion: 0.09
Nodes (8): ext(), fixedColor(), freeColor(), lineEntity(), qc(), rgb(), wire(), Sketch::addLine()

### Community 45 - ".openMarkingMenu"
Cohesion: 0.08
Nodes (6): MainWindow::beginSketch(), MainWindow::buildSketchTab(), MainWindow::enterSketchMode(), MainWindow::buildUiCommands(), QTimer, Viewport::selectArrowValue()

### Community 46 - "Zip.cpp"
Cohesion: 0.10
Nodes (14): Entry, data, name, ZipError, crc32(), get16(), get32(), put16() (+6 more)

### Community 47 - "AnalysisSettings"
Cohesion: 0.10
Nodes (16): DragArrow, base, dir, radius, ref, ring, value, PendingLook (+8 more)

### Community 48 - "Document.cpp"
Cohesion: 0.06
Nodes (33): ConstructionAxis, axis, name, ConstructionPlane, name, spec, ConstructionPoint, name (+25 more)

### Community 49 - "SketchRecord"
Cohesion: 0.17
Nodes (11): ModelParameter, angle, expression, input, label, name, owner, unit (+3 more)

### Community 50 - "MainWindowSketch.cpp"
Cohesion: 0.10
Nodes (12): MainWindow::cancelSketch(), MainWindow::editSketch(), MainWindow::finishSketch(), MainWindow::onProfileClicked(), MainWindow::originalShape(), MainWindow::sketchPalette(), MainWindow::sketchVisible(), MainWindow::startSketch() (+4 more)

### Community 51 - "InputDef"
Cohesion: 0.08
Nodes (24): InputDef, choices, defaultValue, id, label, max, min, minExclusive (+16 more)

### Community 52 - ".rebuild"
Cohesion: 0.12
Nodes (5): hiddenColour(), qc(), rgb(), sharpEdges(), wireColour()

### Community 54 - "MainWindowArrow.cpp"
Cohesion: 0.08
Nodes (12): ArrowPlacement, base, dir, edgePlacement(), facesPlacement(), MainWindow::attachArrowCompleters(), MainWindow::patternCentre(), MainWindow::pickedFaces() (+4 more)

### Community 55 - "Viewport.h"
Cohesion: 0.09
Nodes (14): AnalysisKind, CurvatureMap, Draft, None, Zebra, AnalysisSettings, curvatureScale, draftAngle (+6 more)

### Community 56 - "Theme.cpp"
Cohesion: 0.19
Nodes (6): setIconTheme(), darkColors(), darkPalette(), darkStyleSheet(), lightColors(), lightStyleSheet()

### Community 58 - "Entity"
Cohesion: 0.13
Nodes (10): Entity, a, b, center, construction, fit, kind, projected (+2 more)

### Community 59 - "xdrive.py"
Cohesion: 0.32
Nodes (14): button(), canvas(), click(), drag(), flush(), geometry(), key(), keycode() (+6 more)

### Community 62 - "Session"
Cohesion: 0.07
Nodes (7): PythonHost::PythonHost(), Session, commands_, doc_, listeners_, nextListener_, path_

### Community 63 - "QMouseEvent"
Cohesion: 0.14
Nodes (8): MarkingMenu::mouseMoveEvent(), QMouseEvent, ViewInteractor, Viewport::arrowMouseMove(), Viewport::arrowMousePress(), Viewport::arrowMouseRelease(), Viewport::dragArrowForTest(), Viewport::rebuildArrows()

### Community 64 - "BodyFrame"
Cohesion: 0.11
Nodes (29): BodyFrame, diag, dx, dy, dz, x0, y0, z0 (+21 more)

### Community 65 - "CommandRegistry"
Cohesion: 0.12
Nodes (4): CommandRegistry, cmds_, CommandRegistry::add(), TEST()

### Community 66 - "cmath"
Cohesion: 0.15
Nodes (11): Result, error, ok, output, captured(), PythonHost::exec(), PythonHost::runScript(), Case (+3 more)

### Community 67 - "requirePositive"
Cohesion: 0.25
Nodes (9): BoundingBox, max, min, WallSide, Center, Side1, Side2, offsetOpenWire() (+1 more)

### Community 68 - "Theme"
Cohesion: 0.18
Nodes (4): Theme, colors_, public, styled_

### Community 69 - "src/main.cpp"
Cohesion: 0.11
Nodes (3): QAbstractButton, QAction, grabWindowWithPanels()

### Community 71 - "src/main.cpp"
Cohesion: 0.06
Nodes (26): MainWindow::measurePick(), MainWindow::openMeasure(), Column, kComment, kExpression, kName, kParameter, kStar (+18 more)

### Community 72 - "smoke"
Cohesion: 0.40
Nodes (5): smoke(), MassProperties, area, centerOfMass, volume

### Community 73 - "FileFormat"
Cohesion: 0.17
Nodes (12): FileFormat, Brep, Iges, Obj, Step, Stl, ThreeMF, FormatInfo (+4 more)

### Community 74 - "SketchEditor.cpp"
Cohesion: 0.10
Nodes (4): angleInArc(), ccwContains(), circumcircle(), segDistance()

### Community 75 - "InputType"
Cohesion: 0.12
Nodes (17): InputType, Axis, Bodies, Body, Bool, Choice, Edges, Faces (+9 more)

### Community 76 - "Vec3"
Cohesion: 0.18
Nodes (20): SurfacePoint, normal, point, Vec3, boundingBox(), edgeMidpoint(), edgesNear(), frame() (+12 more)

### Community 79 - "Architecture"
Cohesion: 0.40
Nodes (4): Architecture, How a command works, The document, Units

### Community 80 - "SketchDisplay"
Cohesion: 0.12
Nodes (11): ProfileObject, index, sketch, SketchDisplay, construction, curves, fixedCurves, frame (+3 more)

### Community 81 - "DocCommands.cpp"
Cohesion: 0.04
Nodes (61): Adding a tool, Command, CommandDef, feature, icon, id, inputs, name (+53 more)

### Community 82 - "Measurement"
Cohesion: 0.13
Nodes (14): Kind, Angle, Area, Length, Volume, Measurement, from, hasLine (+6 more)

### Community 83 - ".redrawAll"
Cohesion: 0.09
Nodes (8): NavPreset, Fusion, SolidWorks, Tinkercad, Viewport::setCurvatureComb(), Viewport::clearDragArrow(), Viewport::clearSecondArrow(), Viewport::setInteractor()

### Community 85 - "Level"
Cohesion: 0.12
Nodes (13): debug(), error(), info(), Level, Debug, Error, Info, Warning (+5 more)

### Community 86 - "README.md"
Cohesion: 0.09
Nodes (18): Build, Conventions, Development, Tests, Known gaps, Splines and conics, Visual styles, Reference parts (+10 more)

### Community 87 - "Document.cpp"
Cohesion: 0.08
Nodes (27): bodyNumber(), Document::addBody(), Document::axis(), Document::axisFrame(), Document::bodies(), Document::body(), Document::bodyName(), Document::bodyShapes() (+19 more)

### Community 89 - "Tool"
Cohesion: 0.16
Nodes (6): SketchEditor::SketchEditor(), edges, Tool, op, shape, target

### Community 91 - "MarkingMenu.cpp"
Cohesion: 0.13
Nodes (12): UiCommand, enabled, icon, id, name, panel, run, shortcut (+4 more)

### Community 92 - "gp_Ax3"
Cohesion: 0.31
Nodes (9): curve(), curves(), entityCurves(), interiorPoint(), profileAt(), profiles(), textShape(), toSketch() (+1 more)

### Community 93 - "Known differences still to build"
Cohesion: 0.15
Nodes (12): Data and files, Findings from the videos, Fusion study list, Interface, Known differences still to build, Navigation and display, Selection and the canvas, Sketch (+4 more)

### Community 94 - "MainWindowTools.cpp"
Cohesion: 0.08
Nodes (6): MainWindow::insertFile(), MainWindow::sectionFrame(), MainWindow::sectionPlane(), MainWindow::setSelectionFilter(), MainWindow::showParameters(), MainWindow::updateSectionArrow()

### Community 95 - "Feature"
Cohesion: 0.06
Nodes (27): Body, display, name, shape, Component, bodies, name, Feature (+19 more)

### Community 97 - "EdgeSig"
Cohesion: 0.18
Nodes (11): dot(), EdgeSig, full, normals, point, rel, tangent, type (+3 more)

### Community 98 - "FakeDoc"
Cohesion: 0.17
Nodes (6): FakeDoc, aborts, commits, items, open, snapshot

### Community 101 - "Viewport::setDragArrow"
Cohesion: 0.18
Nodes (4): Viewport::DragArrow::handle(), Viewport::emitArrow(), Viewport::setDragArrow(), Viewport::setDragRing()

### Community 102 - "sstream"
Cohesion: 0.13
Nodes (6): doc_(), Document::Document(), Document::ocafBytes(), ocafApplication(), Document::load(), Document::save()

### Community 103 - "rect"
Cohesion: 0.28
Nodes (3): SelectionBox, crossing, rect()

### Community 104 - "gp_Pnt"
Cohesion: 0.32
Nodes (5): faceNormalAt(), nearestFace(), offsetLoop(), offsetRegion(), pointOnFace()

### Community 105 - "Joints"
Cohesion: 0.36
Nodes (3): cornerAt(), Joints, parent_

### Community 106 - "SectionState"
Cohesion: 0.25
Nodes (7): SectionState, active, angle, flip, offset, plane, visible

### Community 107 - "Display"
Cohesion: 0.25
Nodes (7): Display, constraints, construction, dimensions, points, profiles, projected

### Community 108 - "EntityType"
Cohesion: 0.29
Nodes (7): EntityType, Arc, Circle, Ellipse, Line, Spline, isRound()

### Community 109 - "PlaneEdges"
Cohesion: 0.22
Nodes (5): PlaneEdges, arcs, curves, segments, vertices

### Community 110 - "openWallBand"
Cohesion: 0.15
Nodes (16): Section, Circular, Square, Triangular, TopologyCounts, edges, faces, shells (+8 more)

### Community 111 - "Profile"
Cohesion: 0.33
Nodes (5): Profile, area, face, x, y

### Community 112 - "Mesh"
Cohesion: 0.40
Nodes (3): Mesh, nodes, triangles

### Community 113 - "Axis"
Cohesion: 0.50
Nodes (4): Axis, X, Y, Z

### Community 114 - "uninstall.sh"
Cohesion: 0.52
Nodes (6): die(), manifest_for(), refresh(), uninstall.sh script, step(), usage()

### Community 115 - "install.sh"
Cohesion: 0.60
Nodes (5): die(), refresh(), install.sh script, step(), usage()

### Community 117 - "main"
Cohesion: 0.36
Nodes (4): listCommands(), main(), usage(), main()

### Community 118 - "BooleanOp"
Cohesion: 0.50
Nodes (4): BooleanOp, Cut, Intersect, Join

### Community 119 - "ThreadInfo"
Cohesion: 0.50
Nodes (4): ThreadInfo, diameter, internal, pitch

### Community 122 - "ChamferType"
Cohesion: 0.67
Nodes (3): ChamferType, DistanceAngle, TwoDistances

### Community 123 - "Placement"
Cohesion: 0.25
Nodes (7): Placement, angle, cx, cy, dx, dy, scale

### Community 124 - "ChainSegment"
Cohesion: 0.67
Nodes (3): ChainSegment, entity, forward

### Community 135 - "bindAdsk"
Cohesion: 0.29
Nodes (3): bindAdsk(), BRepBody, index

### Community 142 - "MarkingMenu.cpp"
Cohesion: 0.07
Nodes (16): MarkingMenu, enabled, MarkingMenu::keyPressEvent(), MarkingMenu::MarkingMenu(), MarkingMenu::paintEvent(), MarkingMenu::popupAt(), public, MarkingMenu::ringIndexAt() (+8 more)

## Knowledge Gaps
- **707 isolated node(s):** `ok`, `output`, `error`, `isReal`, `real` (+702 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 1344 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **25 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `optional` connect `optional` to `Viewport`, `MainWindow`, `Inputs`, `ext`, `Kernel.cpp`, `exportShapes`, `Unit`, `ViewportSketch.cpp`, `Unit`, `Expression.cpp`, `QString`, `.updatePreview`, `AnalysisSettings`, `Document.cpp`, `SketchRecord`, `InputDef`, `MainWindowArrow.cpp`, `Viewport.h`, `Session`, `SketchEditor.cpp`, `Vec3`, `DocCommands.cpp`, `Document.cpp`, `CommandDialog.cpp`, `Joints`?**
  _High betweenness centrality (0.122) - this node is a cross-community bridge._
- **What connects `ok`, `output`, `error` to the rest of the system?**
  _707 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Viewport` be split into smaller, more focused modules?**
  _Cohesion score 0.01650793650793651 - nodes in this community are weakly interconnected._
- **Why does `SketchEditor` connect `SketchEditor` to `Viewport`, `Unit`, `ParameterCompleter`, `Constraint`, `SketchEditor.cpp`, `Display`, `optional`, `PlaneEdges`, `Pick`, `.updatePreview`, `Tool`, `Entity`, `Snap`, `Session`, `QMouseEvent`?**
  _High betweenness centrality (0.106) - this node is a cross-community bridge._
- **Should `Icons.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.059748001625795966 - nodes in this community are weakly interconnected._
- **Why does `Viewport` connect `Viewport` to `MainWindow`, `Viewport.cpp`, `optional`, `MainWindowTools.cpp`, `Handle`, `ViewportSketch.cpp`, `AdskModule.cpp`, `.openMarkingMenu`, `AnalysisSettings`, `.rebuild`, `.toPixels`, `MainWindowArrow.cpp`, `Viewport.h`, `QMouseEvent`, `SketchDisplay`, `.redrawAll`, `.initializeGL`, `Viewport::setDragArrow`, `rect`?**
  _High betweenness centrality (0.103) - this node is a cross-community bridge._
- **Should `Session.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.05593607305936073 - nodes in this community are weakly interconnected._