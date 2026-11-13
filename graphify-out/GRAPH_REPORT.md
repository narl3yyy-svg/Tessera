# Graph Report - tessera  (2026-11-13)

## Corpus Check
- 337 files · ~195,267 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 31 file(s) not represented in the graph (top: .drive 23, (none) 5, .cmake 1)

## Summary
- 3146 nodes · 7868 edges · 128 communities (100 shown, 28 thin omitted)
- Extraction: 84% EXTRACTED · 16% INFERRED · 0% AMBIGUOUS · INFERRED: 1221 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `d61b26a5`
- Run `git rev-parse HEAD` and compare to check if the graph is stale.
- Run `graphify update .` after code changes (no API cost).

## Community Hubs (Navigation)
- Viewport
- Icons.cpp
- DocCommands.cpp
- tsr
- MainWindow
- run_oracle.py
- Inputs
- Document
- Viewport.cpp
- SketchEditor
- Dimension
- optional
- Kernel.cpp
- .projectAt
- Kind
- MainWindowTools.cpp
- CommandDialog
- Io.cpp
- Unit
- ViewportAnalysis.cpp
- .rebuild
- TEST
- MainWindow.cpp
- TEST
- Sketch.cpp
- ViewportSketch.cpp
- SketchPalette
- .hitTest
- sketchFor
- AdskModule.cpp
- Colors
- TopoDS_Shape
- SketchOps.cpp
- Command.cpp
- ParameterCompleter
- string
- Viewport.h
- solve
- MarkingMenu.cpp
- src/main.cpp
- ConstraintType
- TEST
- Pick
- Snap
- Kind
- .press
- AnalysisSettings
- Document.cpp
- Session
- MainWindowSketch.cpp
- Session.cpp
- InputDef
- .toPixels
- MainWindowArrow.cpp
- string
- Theme.cpp
- FeatureEffect
- Constraint
- xdrive.py
- DocumentError
- fail
- ViewportArrow.cpp
- ext
- CommandRegistry
- PythonHost.cpp
- Vec3
- Theme
- FileFormat
- CommandDialog.cpp
- ParametersDialog.cpp
- MainWindow::MainWindow
- TopologyCounts
- ExpressionSpinBox
- InputType
- ConstructAxisPoint
- .initializeGL
- ParameterCompleter.cpp
- SketchDisplay
- string
- Measurement
- rect
- Entity
- Level
- README.md
- Handle
- Icons.h
- Value.h
- EdgeSig
- Known differences still to build
- SketchEditor.cpp
- .add
- .planeFrame
- BodyFrame
- FakeDoc
- patternFeatures
- Zip.cpp
- Feature
- Axis
- sstream
- BooleanOp
- ConstructionAxis
- SectionState
- Display
- ThreadInfo
- Document::recompute
- openWallBand
- Session::addListener
- ConstructionPoint
- MainWindow::setSelectionFilter
- uninstall.sh
- install.sh
- Rect
- Column
- ChamferType
- ChainSegment
- LAB_NOTES.md
- build.sh
- live-test.sh

## God Nodes (most connected - your core abstractions)
1. `Viewport` - 224 edges
2. `MainWindow` - 172 edges
3. `SketchEditor` - 157 edges
4. `Inputs` - 136 edges
5. `Document` - 126 edges
6. `CommandContext` - 102 edges
7. `CommandDialog` - 90 edges
8. `render()` - 87 edges
9. `Command` - 62 edges
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

## Communities (128 total, 28 thin omitted)

### Community 0 - "Viewport"
Cohesion: 0.02
Nodes (56): view_, QLineEdit, Viewport, analysis_, analysisObjects_, appliedGridStep_, arrowBoxes_, arrowDragging_ (+48 more)

### Community 1 - "Icons.cpp"
Cohesion: 0.07
Nodes (91): arcIcon(), arrow(), axisIcon(), box(), centerRectIcon(), chamferIcon(), circleIcon(), coilIcon() (+83 more)

### Community 2 - "DocCommands.cpp"
Cohesion: 0.04
Nodes (66): Adding a tool, Command, CommandDef, feature, icon, id, inputs, name (+58 more)

### Community 4 - "MainWindow"
Cohesion: 0.03
Nodes (65): writeLiveGeometry(), CommandDialog, MainWindow, active_, arrowInput_, arrowInput2_, bodiesBeforeCommand_, combEdges_ (+57 more)

### Community 5 - "run_oracle.py"
Cohesion: 0.08
Nodes (54): add_point(), arc_poly(), body_at(), body_list(), build_sketch(), chain(), circumcentre(), cm() (+46 more)

### Community 6 - "Inputs"
Cohesion: 0.08
Nodes (19): CommandContext, CommandError, Inputs, CommandSession::CommandSession(), getBool(), getReal(), applyOperation(), bodyName() (+11 more)

### Community 7 - "Document"
Cohesion: 0.03
Nodes (13): Document, effects_, modified_, pendingTools_, registry_, replaying_, txnBodies_, FromOcaf (+5 more)

### Community 8 - "Viewport.cpp"
Cohesion: 0.06
Nodes (9): keys(), NavPreset, Fusion, SolidWorks, Tinkercad, qc(), rgb(), Viewport::Viewport() (+1 more)

### Community 9 - "SketchEditor"
Cohesion: 0.03
Nodes (41): SketchEditor, arcDrag_, arcDragMoved_, arcEndsChain_, arcFrom_, arcRef_, bodyEdges_, boxing_ (+33 more)

### Community 10 - "Dimension"
Cohesion: 0.40
Nodes (5): Dimension, Angle, Length, Unitless, dimensionOf()

### Community 11 - "optional"
Cohesion: 0.10
Nodes (7): optional, EntityType, Arc, Circle, Line, Spline, isRound()

### Community 13 - ".projectAt"
Cohesion: 0.14
Nodes (5): PlaneEdges, arcs, segments, vertices, edges

### Community 14 - "Kind"
Cohesion: 0.09
Nodes (22): ConstructPlane, def_, kind_, EdgeFeature, def_, kind_, Kind, Angle (+14 more)

### Community 15 - "MainWindowTools.cpp"
Cohesion: 0.07
Nodes (23): QDialog, MainWindow::checkInterference(), MainWindow::chooseUnits(), MainWindow::driveJoints(), MainWindow::exportDesign(), MainWindow::formatLength(), MainWindow::gridSettings(), MainWindow::insertFile() (+15 more)

### Community 16 - "CommandDialog"
Cohesion: 0.04
Nodes (32): CommandDialog, bodiesId_, bodiesLabel_, bodyInput_, buttons_, cmd_, conditional_, edgesId_ (+24 more)

### Community 17 - "Io.cpp"
Cohesion: 0.09
Nodes (18): MainWindow::print3d(), NamedShape, compoundOf(), exportShapes(), fmt(), formatForPath(), fromBrep(), importShape() (+10 more)

### Community 18 - "Unit"
Cohesion: 0.07
Nodes (46): MainWindow::lengthUnit(), ExpressionEnv, lengthUnit, lookup, ExpressionError, Quantity, angle, length (+38 more)

### Community 19 - "ViewportAnalysis.cpp"
Cohesion: 0.06
Nodes (19): packed(), ramp(), shade(), Viewport::buildAnalysis(), Viewport::setCurvatureComb(), Profile, area, face (+11 more)

### Community 20 - ".rebuild"
Cohesion: 0.27
Nodes (5): fixedColor(), freeColor(), qc(), rgb(), wire()

### Community 22 - "MainWindow.cpp"
Cohesion: 0.08
Nodes (3): commandIcon(), qs(), MainWindow::enterSketchMode()

### Community 23 - "TEST"
Cohesion: 0.09
Nodes (6): Sketch, constraints, entities, points, Sketch::addCircle(), TEST()

### Community 24 - "Sketch.cpp"
Cohesion: 0.09
Nodes (16): Point, x, y, SketchError, entityTypeName(), isDimension(), Sketch::addSpline(), Sketch::checkIndices() (+8 more)

### Community 25 - "ViewportSketch.cpp"
Cohesion: 0.09
Nodes (6): faceStyle(), lineStyle(), rgb(), Viewport::lookAt(), Viewport::planePoint(), Viewport::toWidget()

### Community 26 - "SketchPalette"
Cohesion: 0.06
Nodes (27): flatButton(), MainWindow::buildSketchTab(), QCheckBox, QLabel, QToolButton, QWidget, SketchEditor, SketchPalette (+19 more)

### Community 27 - ".hitTest"
Cohesion: 0.11
Nodes (5): angleInArc(), Hit, index, kind, segDistance()

### Community 28 - "sketchFor"
Cohesion: 0.42
Nodes (4): Hole, def_, sketchFor(), stringOr()

### Community 29 - "AdskModule.cpp"
Cohesion: 0.09
Nodes (16): Application, bindAdsk(), BRepBodies, BRepBody, index, Component, Design, Product (+8 more)

### Community 30 - "Colors"
Cohesion: 0.07
Nodes (28): Colors, base, border, cubeBox, cubeText, errorBackground, grid, gridMajor (+20 more)

### Community 31 - "TopoDS_Shape"
Cohesion: 0.26
Nodes (26): KernelError, asSolid(), boolean(), chamfer(), chamferEx(), draft(), extrude(), extrudeEx() (+18 more)

### Community 32 - "SketchOps.cpp"
Cohesion: 0.21
Nodes (19): at(), chainOf(), chamferCorner(), cornerAt(), cross(), dot(), extendLine(), filletCorner() (+11 more)

### Community 33 - "Command.cpp"
Cohesion: 0.09
Nodes (15): CommandSession, inputs_, expressionKey(), checkInputValue(), CommandContext::evaluateExpression(), CommandDef::input(), CommandSession::applyInTransaction(), CommandSession::cancel() (+7 more)

### Community 34 - "ParameterCompleter"
Cohesion: 0.18
Nodes (8): QObject, ParameterCompleter, completer_, edit_, names_, public, QCompleter, QLineEdit

### Community 35 - "string"
Cohesion: 0.31
Nodes (12): completeEdgeReferences(), completeFaceReferences(), decode(), decodeFaces(), edgeReference(), encode(), encodeFace(), faceReference() (+4 more)

### Community 37 - "Viewport.h"
Cohesion: 0.09
Nodes (5): MarkingMenu::keyPressEvent(), QKeyEvent, QLabel, QMouseEvent, ViewInteractor

### Community 38 - "solve"
Cohesion: 0.18
Nodes (12): addConstraintChecked(), Layout, n, px, py, rad, makeLayout(), pack() (+4 more)

### Community 39 - "MarkingMenu.cpp"
Cohesion: 0.07
Nodes (18): UiCommand, enabled, icon, id, name, panel, run, shortcut (+10 more)

### Community 40 - "src/main.cpp"
Cohesion: 0.10
Nodes (4): grabWindowWithPanels(), MarkingMenu, enabled, public

### Community 41 - "ConstraintType"
Cohesion: 0.09
Nodes (23): ConstraintType, Angle, Coincident, Collinear, Concentric, Diameter, Distance, Equal (+15 more)

### Community 42 - "TEST"
Cohesion: 0.09
Nodes (3): param(), TEST(), tmp()

### Community 43 - "Pick"
Cohesion: 0.15
Nodes (12): Pick, bodyArc, bodyPoint, bodySegment, hit, midpointOf, onEntity, parallelTo (+4 more)

### Community 44 - "Snap"
Cohesion: 0.11
Nodes (18): Snap, alignX, alignY, bodyArc, bodySegment, entity, fromX, fromY (+10 more)

### Community 45 - "Kind"
Cohesion: 0.09
Nodes (21): HudField, edit, editing, kind, locked, value, Kind, Angle (+13 more)

### Community 47 - "AnalysisSettings"
Cohesion: 0.08
Nodes (21): AnalysisKind, CurvatureMap, Draft, None, Zebra, AnalysisSettings, curvatureScale, draftAngle (+13 more)

### Community 48 - "Document.cpp"
Cohesion: 0.09
Nodes (28): ConstructionPlane, name, spec, Document::axes(), Document::bodies(), Document::body(), Document::bodyName(), Document::components() (+20 more)

### Community 49 - "Session"
Cohesion: 0.08
Nodes (13): listCommands(), main(), usage(), PythonHost::PythonHost(), main(), smoke(), Session, commands_ (+5 more)

### Community 50 - "MainWindowSketch.cpp"
Cohesion: 0.08
Nodes (13): MainWindow::cancelSketch(), MainWindow::editSketch(), MainWindow::finishSketch(), MainWindow::onEdgeClicked(), MainWindow::onProfileClicked(), MainWindow::originalShape(), MainWindow::sketchPalette(), MainWindow::sketchVisible() (+5 more)

### Community 51 - "Session.cpp"
Cohesion: 0.15
Nodes (22): historyEdit(), OwnedCommand, owned, OwningCommandSession, Session::begin(), Session::deleteFeature(), Session::deleteParameter(), Session::editFeature() (+14 more)

### Community 52 - "InputDef"
Cohesion: 0.08
Nodes (24): InputDef, choices, defaultValue, id, label, max, min, minExclusive (+16 more)

### Community 54 - "MainWindowArrow.cpp"
Cohesion: 0.14
Nodes (7): ArrowPlacement, base, dir, edgePlacement(), facesPlacement(), MainWindow::patternCentre(), MainWindow::pickedFaces()

### Community 55 - "string"
Cohesion: 0.11
Nodes (11): AddUserParameter, def_, checkBody(), checkPattern(), isIdentifier(), openChains(), parsePoints(), pickedFaces() (+3 more)

### Community 56 - "Theme.cpp"
Cohesion: 0.19
Nodes (6): setIconTheme(), darkColors(), darkPalette(), darkStyleSheet(), lightColors(), lightStyleSheet()

### Community 57 - "FeatureEffect"
Cohesion: 0.07
Nodes (23): Body, display, name, shape, Component, bodies, name, FeatureEffect (+15 more)

### Community 58 - "Constraint"
Cohesion: 0.11
Nodes (17): Constraint, entities, expression, points, type, value, value2, SolveResult (+9 more)

### Community 59 - "xdrive.py"
Cohesion: 0.32
Nodes (14): button(), canvas(), click(), drag(), flush(), geometry(), key(), keycode() (+6 more)

### Community 61 - "DocumentError"
Cohesion: 0.15
Nodes (19): DocumentError, Document::abortTransaction(), Document::addBody(), Document::addUserParameter(), Document::bodyShapes(), Document::commitTransaction(), Document::effectOf(), Document::removeBody() (+11 more)

### Community 63 - "ViewportArrow.cpp"
Cohesion: 0.08
Nodes (17): Viewport::frontEdgeOwner(), rgb(), segmentDistance(), Viewport::arrowAt(), Viewport::arrowMouseMove(), Viewport::arrowMousePress(), Viewport::arrowMouseRelease(), Viewport::arrowParam() (+9 more)

### Community 64 - "ext"
Cohesion: 0.22
Nodes (8): SketchRecord, data, name, offset, plane, Document::setSketch(), Document::sketch(), utf8()

### Community 65 - "CommandRegistry"
Cohesion: 0.12
Nodes (4): CommandRegistry, cmds_, CommandRegistry::add(), TEST()

### Community 66 - "PythonHost.cpp"
Cohesion: 0.15
Nodes (11): Result, error, ok, output, captured(), PythonHost::exec(), PythonHost::runScript(), Case (+3 more)

### Community 67 - "Vec3"
Cohesion: 0.15
Nodes (23): MassProperties, area, centerOfMass, SurfacePoint, normal, point, Vec3, boundingBox() (+15 more)

### Community 68 - "Theme"
Cohesion: 0.22
Nodes (4): Theme, colors_, public, styled_

### Community 69 - "FileFormat"
Cohesion: 0.17
Nodes (12): FileFormat, Brep, Iges, Obj, Step, Stl, ThreeMF, FormatInfo (+4 more)

### Community 70 - "CommandDialog.cpp"
Cohesion: 0.10
Nodes (3): CommandDialog::CommandDialog(), formatNumber(), inputExpression()

### Community 71 - "ParametersDialog.cpp"
Cohesion: 0.09
Nodes (14): number(), ParametersDialog, building_, error_, listener_, ParametersDialog::ParametersDialog(), public, rebuildPending_ (+6 more)

### Community 72 - "MainWindow::MainWindow"
Cohesion: 0.13
Nodes (5): PythonHost, MainWindow::MainWindow(), MainWindow::beginSketch(), MainWindow::exitSketchMode(), MainWindow::showPreferences()

### Community 73 - "TopologyCounts"
Cohesion: 0.18
Nodes (16): Section, Circular, Square, Triangular, TopologyCounts, edges, faces, shells (+8 more)

### Community 74 - "ExpressionSpinBox"
Cohesion: 0.16
Nodes (4): ExpressionSpinBox, eval_, expression_, shown_

### Community 75 - "InputType"
Cohesion: 0.08
Nodes (21): bindTsr(), fromPy(), toPy(), typeName(), InputType, Axis, Bodies, Body (+13 more)

### Community 76 - "ConstructAxisPoint"
Cohesion: 0.22
Nodes (5): ConstructAxisPoint, def_, kind_, JointPick, frame

### Community 80 - "SketchDisplay"
Cohesion: 0.13
Nodes (10): ProfileObject, index, sketch, SketchDisplay, construction, curves, frame, name (+2 more)

### Community 81 - "string"
Cohesion: 0.21
Nodes (12): bodyNumber(), Document::axisFrame(), Document::component(), Document::componentOfBody(), Document::nextAxisName(), Document::nextBodyName(), Document::nextComponentName(), Document::nextPlaneName() (+4 more)

### Community 82 - "Measurement"
Cohesion: 0.13
Nodes (14): Kind, Angle, Area, Length, Volume, Measurement, from, hasLine (+6 more)

### Community 83 - "rect"
Cohesion: 0.28
Nodes (3): SelectionBox, crossing, rect()

### Community 84 - "Entity"
Cohesion: 0.22
Nodes (9): Entity, a, b, center, construction, fit, projected, radius (+1 more)

### Community 85 - "Level"
Cohesion: 0.12
Nodes (13): debug(), error(), info(), Level, Debug, Error, Info, Warning (+5 more)

### Community 86 - "README.md"
Cohesion: 0.08
Nodes (20): Architecture, How a command works, The document, Units, Build, Conventions, Development, Tests (+12 more)

### Community 91 - "EdgeSig"
Cohesion: 0.18
Nodes (11): dot(), EdgeSig, full, normals, point, rel, tangent, type (+3 more)

### Community 93 - "Known differences still to build"
Cohesion: 0.15
Nodes (12): Data and files, Findings from the videos, Fusion study list, Interface, Known differences still to build, Navigation and display, Selection and the canvas, Sketch (+4 more)

### Community 96 - ".planeFrame"
Cohesion: 0.21
Nodes (6): Loft, def_, profilesOf(), profiles, Sweep, def_

### Community 97 - "BodyFrame"
Cohesion: 0.09
Nodes (22): BodyFrame, diag, dx, dy, dz, x0, y0, z0 (+14 more)

### Community 98 - "FakeDoc"
Cohesion: 0.17
Nodes (6): FakeDoc, aborts, commits, items, open, snapshot

### Community 99 - "patternFeatures"
Cohesion: 0.16
Nodes (10): getInt(), bodyCentre(), CopyFn, differenceOrNull(), PathPattern, def_, patternFeatures(), placeCopies() (+2 more)

### Community 100 - "Zip.cpp"
Cohesion: 0.11
Nodes (14): Entry, data, name, ZipError, crc32(), get16(), get32(), put16() (+6 more)

### Community 101 - "Feature"
Cohesion: 0.22
Nodes (9): Feature, commandId, error, id, inputs, name, rolledBack, suppressed (+1 more)

### Community 102 - "Axis"
Cohesion: 0.50
Nodes (4): Axis, X, Y, Z

### Community 103 - "sstream"
Cohesion: 0.11
Nodes (8): doc_(), Document::Document(), Document::ocafBytes(), Document::reevaluateParameters(), Document::userParameter(), ocafApplication(), Document::load(), Document::save()

### Community 104 - "BooleanOp"
Cohesion: 0.50
Nodes (4): BooleanOp, Cut, Intersect, Join

### Community 105 - "ConstructionAxis"
Cohesion: 0.33
Nodes (5): ConstructionAxis, axis, name, Document::axis(), Document::setAxis()

### Community 106 - "SectionState"
Cohesion: 0.25
Nodes (7): SectionState, active, angle, flip, offset, plane, visible

### Community 107 - "Display"
Cohesion: 0.25
Nodes (7): Display, constraints, construction, dimensions, points, profiles, projected

### Community 108 - "ThreadInfo"
Cohesion: 0.50
Nodes (4): ThreadInfo, diameter, internal, pitch

### Community 109 - "Document::recompute"
Cohesion: 0.23
Nodes (8): Document::openTransaction(), Document::recompute(), Document::recordFeature(), Document::removeFeature(), Document::setFeatureInputs(), Document::setFeatureSuppressed(), featureData(), toJson()

### Community 110 - "openWallBand"
Cohesion: 0.25
Nodes (9): BoundingBox, max, min, WallSide, Center, Side1, Side2, offsetOpenWire() (+1 more)

### Community 112 - "ConstructionPoint"
Cohesion: 0.33
Nodes (5): ConstructionPoint, name, point, Document::point(), Document::setPoint()

### Community 114 - "uninstall.sh"
Cohesion: 0.52
Nodes (6): die(), manifest_for(), refresh(), uninstall.sh script, step(), usage()

### Community 115 - "install.sh"
Cohesion: 0.60
Nodes (5): die(), refresh(), install.sh script, step(), usage()

### Community 116 - "Rect"
Cohesion: 0.50
Nodes (4): Session::notifyChanged(), Rect, l, p

### Community 117 - "Column"
Cohesion: 0.33
Nodes (6): Column, kComment, kExpression, kParameter, kUnit, kValue

### Community 118 - "ChamferType"
Cohesion: 0.67
Nodes (3): ChamferType, DistanceAngle, TwoDistances

### Community 132 - "ChainSegment"
Cohesion: 0.67
Nodes (3): ChainSegment, entity, forward

## Knowledge Gaps
- **637 isolated node(s):** `ok`, `output`, `error`, `isReal`, `real` (+632 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 1205 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **28 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `Viewport` connect `Viewport` to `MainWindow`, `Viewport.h`, `Viewport.cpp`, `optional`, `.initializeGL`, `AnalysisSettings`, `SketchDisplay`, `MainWindowTools.cpp`, `ViewportAnalysis.cpp`, `rect`, `.toPixels`, `Handle`, `.selectedSubShapes`, `ViewportArrow.cpp`?**
  _High betweenness centrality (0.129) - this node is a cross-community bridge._
- **What connects `ok`, `output`, `error` to the rest of the system?**
  _637 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Viewport` be split into smaller, more focused modules?**
  _Cohesion score 0.018140929535232383 - nodes in this community are weakly interconnected._
- **Why does `optional` connect `optional` to `Viewport`, `DocCommands.cpp`, `MainWindow`, `Kernel.cpp`, `Io.cpp`, `Unit`, `.rebuild`, `ViewportSketch.cpp`, `sketchFor`, `SketchOps.cpp`, `Viewport.h`, `.press`, `AnalysisSettings`, `Document.cpp`, `Session`, `InputDef`, `MainWindowArrow.cpp`, `ViewportArrow.cpp`, `ext`, `Vec3`, `CommandDialog.cpp`, `ExpressionSpinBox`, `string`, `SketchEditor.cpp`, `Feature`, `sstream`, `ConstructionAxis`, `ConstructionPoint`?**
  _High betweenness centrality (0.124) - this node is a cross-community bridge._
- **Should `Icons.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.06853038245000971 - nodes in this community are weakly interconnected._
- **Why does `MainWindow` connect `MainWindow` to `ParameterCompleter`, `.buildAppBar`, `MarkingMenu.cpp`, `MainWindow::MainWindow`, `SectionState`, `optional`, `MainWindowTools.cpp`, `Session`, `MainWindowSketch.cpp`, `MainWindow.cpp`, `SketchPalette`?**
  _High betweenness centrality (0.098) - this node is a cross-community bridge._
- **Should `DocCommands.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.03944618599791014 - nodes in this community are weakly interconnected._