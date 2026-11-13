# Graph Report - tessera  (2026-11-13)

## Corpus Check
- 370 files · ~227,881 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 53 file(s) not represented in the graph (top: .drive 45, (none) 5, .cmake 1)

## Summary
- 3446 nodes · 8673 edges · 140 communities (110 shown, 30 thin omitted)
- Extraction: 85% EXTRACTED · 15% INFERRED · 0% AMBIGUOUS · INFERRED: 1300 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `c400ec0d`
- Run `git rev-parse HEAD` and compare to check if the graph is stale.
- Run `graphify update .` after code changes (no API cost).

## Community Hubs (Navigation)
- Viewport
- Icons.cpp
- Session.cpp
- MainWindow
- run_oracle.py
- Inputs
- Document
- Viewport.cpp
- SketchEditor
- Document::recompute
- optional
- Kernel.cpp
- NewComponent
- Kind
- TEST
- CommandDialog
- Io.cpp
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
- string
- Colors
- KernelError
- SketchOps.cpp
- Dimension
- ParameterCompleter
- Constraint
- .userParameters
- MainWindow.cpp
- solve
- Kind
- QString
- ConstraintType
- AdskModule.cpp
- Pick
- .openMarkingMenu
- Zip.cpp
- AnalysisSettings
- ConstructionPoint
- SketchRecord
- MainWindowSketch.cpp
- InputDef
- ParametersDialog
- .toPixels
- MainWindowArrow.cpp
- .features
- Theme.cpp
- .applyPreSelection
- Entity
- xdrive.py
- SketchGeometry.cpp
- Session
- ViewportArrow.cpp
- BodyFrame
- CommandRegistry
- cmath
- requirePositive
- Theme
- src/main.cpp
- ParametersDialog.cpp
- smoke
- FileFormat
- SketchEditor.cpp
- InputType
- Vec3
- CommandDialog::CommandDialog
- math
- Architecture
- SketchDisplay
- DocCommands.cpp
- Measurement
- .redrawAll
- AddUserParameter
- Level
- README.md
- Document.cpp
- test_feature_pattern.py
- .bodyFaces
- .add
- MarkingMenu.cpp
- QDialog
- Known differences still to build
- MainWindow::setSelectionFilter
- Feature
- .initializeGL
- EdgeSig
- FakeDoc
- MainWindow::buildUiCommands
- sstream
- Document::nameFeatureParameters
- gp_Pnt
- Joints
- SectionState
- Display
- EntityType
- PlaneEdges
- openWallBand
- Column
- Axis
- uninstall.sh
- install.sh
- PYBIND11_EMBEDDED_MODULE
- main
- BooleanOp
- ThreadInfo
- ConstructionAxis
- ChamferType
- Placement
- ChainSegment
- UserParameter
- Value.h
- Development
- Known gaps
- TEST
- HoleSize
- test_text_box_path.py
- LAB_NOTES.md
- build.sh
- live-test.sh

## God Nodes (most connected - your core abstractions)
1. `Viewport` - 251 edges
2. `SketchEditor` - 178 edges
3. `MainWindow` - 175 edges
4. `Inputs` - 138 edges
5. `render()` - 106 edges
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

## Communities (140 total, 30 thin omitted)

### Community 0 - "Viewport"
Cohesion: 0.02
Nodes (67): view_, QLineEdit, Viewport, analysis_, analysisObjects_, appliedGridStep_, arrowBoxes_, arrowDragging_ (+59 more)

### Community 1 - "Icons.cpp"
Cohesion: 0.06
Nodes (113): arc3Icon(), arcIcon(), arcTangentIcon(), arrow(), axisIcon(), box(), breakIcon(), centerRectIcon() (+105 more)

### Community 2 - "Session.cpp"
Cohesion: 0.06
Nodes (48): CommandSession, inputs_, expressionKey(), checkInputValue(), CommandContext::evaluateExpression(), CommandDef::input(), CommandSession::applyInTransaction(), CommandSession::cancel() (+40 more)

### Community 4 - "MainWindow"
Cohesion: 0.03
Nodes (63): CommandDialog, MainWindow, active_, arrowInput_, arrowInput2_, bodiesBeforeCommand_, combEdges_, combPicking_ (+55 more)

### Community 5 - "run_oracle.py"
Cohesion: 0.08
Nodes (54): add_point(), arc_poly(), body_at(), body_list(), build_sketch(), chain(), circumcentre(), cm() (+46 more)

### Community 6 - "Inputs"
Cohesion: 0.07
Nodes (16): CommandContext, Inputs, CommandSession::CommandSession(), checkBody(), checkPattern(), defaultBody(), isIdentifier(), Pipe (+8 more)

### Community 7 - "Document"
Cohesion: 0.03
Nodes (11): Document, effects_, modified_, pendingTools_, registry_, replaying_, txnBodies_, FromOcaf (+3 more)

### Community 8 - "Viewport.cpp"
Cohesion: 0.05
Nodes (8): hiddenColour(), keys(), qc(), QKeyEvent, rgb(), sharpEdges(), Viewport::Viewport(), wireColour()

### Community 9 - "SketchEditor"
Cohesion: 0.03
Nodes (49): SketchEditor, arcDrag_, arcDragMoved_, arcEndsChain_, arcFrom_, arcRef_, bodyEdges_, boxing_ (+41 more)

### Community 10 - "Document::recompute"
Cohesion: 0.20
Nodes (7): Document::recompute(), Document::recordFeature(), Document::removeFeature(), Document::setFeatureInputs(), Document::setFeatureSuppressed(), featureData(), toJson()

### Community 11 - "optional"
Cohesion: 0.10
Nodes (4): optional, CommandRegistry::all(), fail(), Failure

### Community 12 - "Kernel.cpp"
Cohesion: 0.04
Nodes (5): isoCoarsePitch(), massProperties(), measure(), polygonToCircleLoft(), topologyCounts()

### Community 14 - "Kind"
Cohesion: 0.09
Nodes (22): ConstructPlane, def_, kind_, EdgeFeature, def_, kind_, Kind, Angle (+14 more)

### Community 15 - "TEST"
Cohesion: 0.09
Nodes (3): param(), TEST(), tmp()

### Community 16 - "CommandDialog"
Cohesion: 0.05
Nodes (31): CommandDialog, bodiesId_, bodiesLabel_, bodyInput_, buttons_, cmd_, conditional_, edgesId_ (+23 more)

### Community 17 - "Io.cpp"
Cohesion: 0.10
Nodes (18): NamedShape, compoundOf(), exportShapes(), fmt(), formatForPath(), fromBrep(), importShape(), lower() (+10 more)

### Community 18 - "Unit"
Cohesion: 0.07
Nodes (45): MainWindow::lengthUnit(), ExpressionEnv, lengthUnit, lookup, ExpressionError, Quantity, angle, length (+37 more)

### Community 19 - "MainWindowTools.cpp"
Cohesion: 0.08
Nodes (19): MainWindow::checkInterference(), MainWindow::chooseUnits(), MainWindow::driveJoints(), MainWindow::formatLength(), MainWindow::gridSettings(), MainWindow::insertFile(), MainWindow::openAnalysis(), MainWindow::openSection() (+11 more)

### Community 21 - "Document"
Cohesion: 0.11
Nodes (18): ConstructAxisPoint, def_, kind_, jointOrigin(), JointPick, frame, Loft, def_ (+10 more)

### Community 22 - "MainWindow::MainWindow"
Cohesion: 0.13
Nodes (4): PythonHost, MainWindow::MainWindow(), MainWindow::exitSketchMode(), MainWindow::showPreferences()

### Community 23 - "TEST"
Cohesion: 0.07
Nodes (10): writeLiveGeometry(), Sketch, constraints, entities, points, texts, Sketch::addCircle(), Sketch::addLine() (+2 more)

### Community 24 - "Sketch.cpp"
Cohesion: 0.07
Nodes (23): Point, x, y, SketchError, SplineKind, Conic, Control, Fit (+15 more)

### Community 25 - "ViewportSketch.cpp"
Cohesion: 0.06
Nodes (7): QLabel, faceStyle(), lineStyle(), rgb(), Viewport::lookAt(), Viewport::planePoint(), Viewport::toWidget()

### Community 26 - "SketchPalette"
Cohesion: 0.06
Nodes (26): flatButton(), QCheckBox, QLabel, QToolButton, QWidget, SketchEditor, SketchPalette, body_ (+18 more)

### Community 27 - "Snap"
Cohesion: 0.09
Nodes (24): ext(), fixedColor(), freeColor(), qc(), rgb(), Snap, alignX, alignY (+16 more)

### Community 28 - "CommandError"
Cohesion: 0.13
Nodes (21): CommandError, getBool(), getInt(), getReal(), applyOperation(), bodyCentre(), bodyName(), CopyFn (+13 more)

### Community 29 - "string"
Cohesion: 0.14
Nodes (28): DocumentError, bodyNumber(), checkViewName(), Document::addBody(), Document::addNamedView(), Document::addUserParameter(), Document::axisFrame(), Document::nextBodyName() (+20 more)

### Community 30 - "Colors"
Cohesion: 0.07
Nodes (28): Colors, base, border, cubeBox, cubeText, errorBackground, grid, gridMajor (+20 more)

### Community 31 - "KernelError"
Cohesion: 0.28
Nodes (25): KernelError, asSolid(), boolean(), chamfer(), chamferEx(), draft(), extrude(), extrudeEx() (+17 more)

### Community 32 - "SketchOps.cpp"
Cohesion: 0.21
Nodes (26): at(), chainOf(), chamferCorner(), circularPattern(), copyEntities(), cross(), dot(), extendLine() (+18 more)

### Community 33 - "Dimension"
Cohesion: 0.50
Nodes (4): Dimension, Angle, Length, Unitless

### Community 34 - "ParameterCompleter"
Cohesion: 0.12
Nodes (8): ParameterCompleter, completer_, edit_, names_, ParameterCompleter::ParameterCompleter(), public, QCompleter, QLineEdit

### Community 35 - "Constraint"
Cohesion: 0.08
Nodes (20): Constraint, driven, entities, expression, hasLabel, labelX, labelY, name (+12 more)

### Community 36 - ".userParameters"
Cohesion: 0.24
Nodes (5): Document::expressionEnv(), Document::nextDimensionName(), Document::parameterUsers(), Document::reevaluateParameters(), Document::save()

### Community 37 - "MainWindow.cpp"
Cohesion: 0.14
Nodes (3): commandIcon(), qs(), MainWindow::applySection()

### Community 38 - "solve"
Cohesion: 0.18
Nodes (12): addConstraintChecked(), Layout, n, px, py, rad, makeLayout(), pack() (+4 more)

### Community 39 - "Kind"
Cohesion: 0.09
Nodes (21): HudField, edit, editing, kind, locked, value, Kind, Angle (+13 more)

### Community 40 - "QString"
Cohesion: 0.12
Nodes (6): ExpressionSpinBox, eval_, expression_, shown_, formatNumber(), dimensionOf()

### Community 41 - "ConstraintType"
Cohesion: 0.08
Nodes (24): ConstraintType, Angle, Coincident, Collinear, Concentric, Diameter, Distance, Equal (+16 more)

### Community 42 - "AdskModule.cpp"
Cohesion: 0.07
Nodes (21): Application, bindAdsk(), BRepBodies, BRepBody, index, Component, Design, Product (+13 more)

### Community 43 - "Pick"
Cohesion: 0.10
Nodes (17): Hit, index, kind, Pick, bodyArc, bodyPoint, bodySegment, hit (+9 more)

### Community 45 - ".openMarkingMenu"
Cohesion: 0.14
Nodes (5): MainWindow::beginSketch(), MainWindow::buildSketchTab(), MainWindow::enterSketchMode(), QTimer, Viewport::selectArrowValue()

### Community 46 - "Zip.cpp"
Cohesion: 0.10
Nodes (14): Entry, data, name, ZipError, crc32(), get16(), get32(), put16() (+6 more)

### Community 47 - "AnalysisSettings"
Cohesion: 0.06
Nodes (29): AnalysisKind, CurvatureMap, Draft, None, Zebra, AnalysisSettings, curvatureScale, draftAngle (+21 more)

### Community 48 - "ConstructionPoint"
Cohesion: 0.29
Nodes (5): ConstructionPoint, name, point, Document::point(), Document::setPoint()

### Community 49 - "SketchRecord"
Cohesion: 0.11
Nodes (17): ModelParameter, angle, expression, input, label, name, owner, unit (+9 more)

### Community 50 - "MainWindowSketch.cpp"
Cohesion: 0.05
Nodes (25): MainWindow::cancelSketch(), MainWindow::editSketch(), MainWindow::finishSketch(), MainWindow::onProfileClicked(), MainWindow::originalShape(), MainWindow::sketchPalette(), MainWindow::sketchVisible(), MainWindow::startSketch() (+17 more)

### Community 51 - "InputDef"
Cohesion: 0.08
Nodes (24): InputDef, choices, defaultValue, id, label, max, min, minExclusive (+16 more)

### Community 52 - "ParametersDialog"
Cohesion: 0.12
Nodes (12): ParametersDialog, building_, error_, filter_, listener_, public, rebuildPending_, tree_ (+4 more)

### Community 54 - "MainWindowArrow.cpp"
Cohesion: 0.07
Nodes (12): ArrowPlacement, base, dir, edgePlacement(), facesPlacement(), MainWindow::attachArrowCompleters(), MainWindow::patternCentre(), MainWindow::pickedFaces() (+4 more)

### Community 55 - ".features"
Cohesion: 0.12
Nodes (16): Feature, commandId, error, id, inputs, name, parameterNames, rolledBack (+8 more)

### Community 56 - "Theme.cpp"
Cohesion: 0.19
Nodes (6): setIconTheme(), darkColors(), darkPalette(), darkStyleSheet(), lightColors(), lightStyleSheet()

### Community 58 - "Entity"
Cohesion: 0.06
Nodes (22): QObject, SketchEditor::SketchEditor(), edges, Entity, a, b, center, construction (+14 more)

### Community 59 - "xdrive.py"
Cohesion: 0.32
Nodes (14): button(), canvas(), click(), drag(), flush(), geometry(), key(), keycode() (+6 more)

### Community 61 - "SketchGeometry.cpp"
Cohesion: 0.08
Nodes (16): Profile, area, face, x, y, curve(), curves(), customPlaneSpec() (+8 more)

### Community 62 - "Session"
Cohesion: 0.08
Nodes (7): PythonHost::PythonHost(), Session, commands_, doc_, listeners_, nextListener_, path_

### Community 63 - "ViewportArrow.cpp"
Cohesion: 0.06
Nodes (20): MarkingMenu::mouseMoveEvent(), QMouseEvent, ViewInteractor, Viewport::frontEdgeOwner(), rgb(), segmentDistance(), Viewport::arrowAt(), Viewport::arrowMouseMove() (+12 more)

### Community 64 - "BodyFrame"
Cohesion: 0.11
Nodes (29): BodyFrame, diag, dx, dy, dz, x0, y0, z0 (+21 more)

### Community 65 - "CommandRegistry"
Cohesion: 0.12
Nodes (4): CommandRegistry, cmds_, CommandRegistry::add(), TEST()

### Community 66 - "cmath"
Cohesion: 0.16
Nodes (11): Result, error, ok, output, captured(), PythonHost::exec(), PythonHost::runScript(), Case (+3 more)

### Community 67 - "requirePositive"
Cohesion: 0.25
Nodes (9): BoundingBox, max, min, WallSide, Center, Side1, Side2, offsetOpenWire() (+1 more)

### Community 68 - "Theme"
Cohesion: 0.22
Nodes (4): Theme, colors_, public, styled_

### Community 69 - "src/main.cpp"
Cohesion: 0.08
Nodes (4): grabWindowWithPanels(), MarkingMenu, enabled, public

### Community 71 - "ParametersDialog.cpp"
Cohesion: 0.13
Nodes (4): number(), ParametersDialog::ParametersDialog(), qs(), withUnit()

### Community 72 - "smoke"
Cohesion: 0.40
Nodes (5): smoke(), MassProperties, area, centerOfMass, volume

### Community 73 - "FileFormat"
Cohesion: 0.17
Nodes (12): FileFormat, Brep, Iges, Obj, Step, Stl, ThreeMF, FormatInfo (+4 more)

### Community 74 - "SketchEditor.cpp"
Cohesion: 0.11
Nodes (5): angleInArc(), ccwContains(), circumcircle(), lineEntity(), segDistance()

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
Nodes (60): Adding a tool, Command, CommandDef, feature, icon, id, inputs, name (+52 more)

### Community 82 - "Measurement"
Cohesion: 0.13
Nodes (14): Kind, Angle, Area, Length, Volume, Measurement, from, hasLine (+6 more)

### Community 83 - ".redrawAll"
Cohesion: 0.09
Nodes (8): NavPreset, Fusion, SolidWorks, Tinkercad, Viewport::setCurvatureComb(), Viewport::clearDragArrow(), Viewport::clearSecondArrow(), Viewport::setInteractor()

### Community 84 - "AddUserParameter"
Cohesion: 0.22
Nodes (4): AddUserParameter, def_, Push, d

### Community 85 - "Level"
Cohesion: 0.16
Nodes (13): debug(), error(), info(), Level, Debug, Error, Info, Warning (+5 more)

### Community 86 - "README.md"
Cohesion: 0.14
Nodes (11): Reference parts, Fusion feature checklist, Roadmap, Contents, Development, Features, Install, License (+3 more)

### Community 87 - "Document.cpp"
Cohesion: 0.07
Nodes (36): ConstructionPlane, name, spec, Document::abortTransaction(), Document::axes(), Document::bodies(), Document::body(), Document::bodyName() (+28 more)

### Community 89 - ".bodyFaces"
Cohesion: 0.17
Nodes (6): Coil, def_, Extrude, def_, Joint, def_

### Community 91 - "MarkingMenu.cpp"
Cohesion: 0.13
Nodes (12): UiCommand, enabled, icon, id, name, panel, run, shortcut (+4 more)

### Community 92 - "QDialog"
Cohesion: 0.17
Nodes (5): QDialog, MainWindow::exportDesign(), MainWindow::measurePick(), MainWindow::openMeasure(), toolWindow()

### Community 93 - "Known differences still to build"
Cohesion: 0.15
Nodes (12): Data and files, Findings from the videos, Fusion study list, Interface, Known differences still to build, Navigation and display, Selection and the canvas, Sketch (+4 more)

### Community 95 - "Feature"
Cohesion: 0.09
Nodes (18): Body, display, name, shape, Component, bodies, name, FeatureEffect (+10 more)

### Community 96 - ".initializeGL"
Cohesion: 0.12
Nodes (3): SelectionBox, crossing, height

### Community 97 - "EdgeSig"
Cohesion: 0.18
Nodes (11): dot(), EdgeSig, full, normals, point, rel, tangent, type (+3 more)

### Community 98 - "FakeDoc"
Cohesion: 0.17
Nodes (6): FakeDoc, aborts, commits, items, open, snapshot

### Community 102 - "sstream"
Cohesion: 0.18
Nodes (4): doc_(), Document::Document(), ocafApplication(), Document::load()

### Community 103 - "Document::nameFeatureParameters"
Cohesion: 0.25
Nodes (5): Document::bodyShapes(), Document::effectOf(), Document::evaluate(), Document::nameFeatureParameters(), joinNames()

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
Cohesion: 0.16
Nodes (5): PlaneEdges, arcs, curves, segments, vertices

### Community 110 - "openWallBand"
Cohesion: 0.15
Nodes (16): Section, Circular, Square, Triangular, TopologyCounts, edges, faces, shells (+8 more)

### Community 111 - "Column"
Cohesion: 0.25
Nodes (8): Column, kComment, kExpression, kName, kParameter, kStar, kUnit, kValue

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

### Community 121 - "ConstructionAxis"
Cohesion: 0.33
Nodes (4): ConstructionAxis, axis, name, Document::axis()

### Community 122 - "ChamferType"
Cohesion: 0.67
Nodes (3): ChamferType, DistanceAngle, TwoDistances

### Community 123 - "Placement"
Cohesion: 0.25
Nodes (7): Placement, angle, cx, cy, dx, dy, scale

### Community 124 - "ChainSegment"
Cohesion: 0.67
Nodes (3): ChainSegment, entity, forward

### Community 126 - "UserParameter"
Cohesion: 0.33
Nodes (6): UserParameter, comment, expression, name, unit, value

### Community 128 - "Development"
Cohesion: 0.40
Nodes (4): Build, Conventions, Development, Tests

### Community 129 - "Known gaps"
Cohesion: 0.40
Nodes (4): Known gaps, Sketch text, Splines and conics, Visual styles

### Community 131 - "HoleSize"
Cohesion: 0.50
Nodes (4): HoleSize, modeled, pitch, radius

## Knowledge Gaps
- **711 isolated node(s):** `ok`, `output`, `error`, `isReal`, `real` (+706 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 1349 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **30 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `optional` connect `optional` to `Viewport`, `MainWindow`, `Inputs`, `Kernel.cpp`, `Io.cpp`, `Unit`, `ViewportSketch.cpp`, `Constraint`, `QString`, `AnalysisSettings`, `ConstructionPoint`, `SketchRecord`, `InputDef`, `MainWindowArrow.cpp`, `.features`, `Entity`, `Session`, `ViewportArrow.cpp`, `SketchEditor.cpp`, `Vec3`, `DocCommands.cpp`, `Document.cpp`, `CommandDialog.cpp`, `Joints`, `ConstructionAxis`?**
  _High betweenness centrality (0.128) - this node is a cross-community bridge._
- **What connects `ok`, `output`, `error` to the rest of the system?**
  _711 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Viewport` be split into smaller, more focused modules?**
  _Cohesion score 0.01636318897637795 - nodes in this community are weakly interconnected._
- **Why does `SketchEditor` connect `SketchEditor` to `Viewport`, `Constraint`, `Kind`, `SketchEditor.cpp`, `Display`, `optional`, `PlaneEdges`, `Pick`, `.solveAndShow`, `Unit`, `Entity`, `Snap`, `Session`, `ViewportArrow.cpp`?**
  _High betweenness centrality (0.105) - this node is a cross-community bridge._
- **Should `Icons.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.05701587301587301 - nodes in this community are weakly interconnected._
- **Why does `Viewport` connect `Viewport` to `.initializeGL`, `MainWindow`, `Viewport.cpp`, `AdskModule.cpp`, `optional`, `.openMarkingMenu`, `AnalysisSettings`, `SketchDisplay`, `.redrawAll`, `Handle`, `.toPixels`, `MainWindowArrow.cpp`, `MainWindowTools.cpp`, `ViewportSketch.cpp`, `ViewportArrow.cpp`?**
  _High betweenness centrality (0.103) - this node is a cross-community bridge._
- **Should `Session.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.05672926447574335 - nodes in this community are weakly interconnected._