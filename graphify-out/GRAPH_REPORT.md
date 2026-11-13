# Graph Report - tessera  (2026-11-13)

## Corpus Check
- 363 files · ~220,732 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 48 file(s) not represented in the graph (top: .drive 40, (none) 5, .cmake 1)

## Summary
- 3380 nodes · 8464 edges · 131 communities (106 shown, 25 thin omitted)
- Extraction: 85% EXTRACTED · 15% INFERRED · 0% AMBIGUOUS · INFERRED: 1251 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `c0dafb07`
- Run `git rev-parse HEAD` and compare to check if the graph is stale.
- Run `graphify update .` after code changes (no API cost).

## Community Hubs (Navigation)
- Viewport
- Icons.cpp
- .notifyChanged
- MainWindow
- run_oracle.py
- Inputs
- Document
- Viewport.cpp
- SketchEditor
- .updatePreview
- optional
- Kernel.cpp
- vector
- Kind
- MarkingMenu
- CommandDialog
- Io.cpp
- Unit
- MainWindowTools.cpp
- .hitTest
- Document
- isInputVisible
- TEST
- Sketch.cpp
- ViewportSketch.cpp
- SketchPalette
- Profile
- CommandError
- AdskModule.cpp
- Colors
- KernelError
- SketchOps.cpp
- Command.cpp
- ParameterCompleter
- Constraint
- MainWindow.cpp
- solve
- ViewportAnalysis.cpp
- CommandSession
- ConstraintType
- TEST
- Pick
- Snap
- Kind
- Zip.cpp
- AnalysisSettings
- Document.cpp
- SketchRecord
- MainWindowSketch.cpp
- InputDef
- DocCommands.h
- .toPixels
- MainWindowArrow.cpp
- Viewport.h
- Theme.cpp
- TEST
- Entity
- xdrive.py
- SketchGeometry.cpp
- Session
- ViewportArrow.cpp
- BodyFrame
- CommandRegistry
- cmath
- TopoDS_Shape
- Theme
- Session.cpp
- Document::reevaluateParameters
- src/main.cpp
- src/main.cpp
- FileFormat
- InputType
- string
- CommandDialog::CommandDialog
- math
- QTimer
- SketchDisplay
- DocCommands.cpp
- Measurement
- .redrawAll
- Kernel.h
- Level
- README.md
- DocumentError
- test_feature_pattern.py
- QObject
- EntityType
- MarkingMenu.cpp
- ConstructionPlane
- Known differences still to build
- Value.h
- FeatureEffect
- UserParameter
- WallSide
- FakeDoc
- smoke
- Development
- string
- sstream
- Rect
- Architecture
- SectionState
- Display
- TestFramework.h
- PlaneEdges
- openWallBand
- ConstructionPoint
- ConstructionAxis
- uninstall.sh
- install.sh
- PYBIND11_EMBEDDED_MODULE
- main
- Feature
- Push
- Placement
- ChainSegment
- .rebuild
- Joints
- LAB_NOTES.md
- build.sh
- live-test.sh
- CommandDialog::CommandDialog

## God Nodes (most connected - your core abstractions)
1. `Viewport` - 248 edges
2. `SketchEditor` - 177 edges
3. `MainWindow` - 175 edges
4. `Inputs` - 137 edges
5. `render()` - 102 edges
6. `CommandContext` - 102 edges
7. `Document` - 100 edges
8. `CommandDialog` - 90 edges
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

## Communities (131 total, 25 thin omitted)

### Community 0 - "Viewport"
Cohesion: 0.02
Nodes (64): view_, Viewport, analysis_, analysisObjects_, appliedGridStep_, arrowBoxes_, arrowDragging_, arrowGrab_ (+56 more)

### Community 1 - "Icons.cpp"
Cohesion: 0.06
Nodes (107): arc3Icon(), arcIcon(), arrow(), axisIcon(), box(), breakIcon(), centerRectIcon(), chamferIcon() (+99 more)

### Community 2 - ".notifyChanged"
Cohesion: 0.20
Nodes (17): historyEdit(), plainEdit(), Session::addNamedView(), Session::deleteFeature(), Session::deleteNamedView(), Session::deleteParameter(), Session::newDocument(), Session::redo() (+9 more)

### Community 4 - "MainWindow"
Cohesion: 0.03
Nodes (64): CommandDialog, MainWindow, active_, arrowInput_, arrowInput2_, bodiesBeforeCommand_, combEdges_, combPicking_ (+56 more)

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
Cohesion: 0.05
Nodes (6): glide(), keys(), QtFrameBuffer, SelectionBox, crossing, Viewport::Viewport()

### Community 9 - "SketchEditor"
Cohesion: 0.03
Nodes (45): SketchEditor, arcDrag_, arcDragMoved_, arcEndsChain_, arcFrom_, arcRef_, bodyEdges_, boxing_ (+37 more)

### Community 13 - "vector"
Cohesion: 0.13
Nodes (13): Loft, def_, NewComponent, def_, openChains(), parsePoints(), pickedFaces(), profilesOf() (+5 more)

### Community 14 - "Kind"
Cohesion: 0.09
Nodes (22): ConstructPlane, def_, kind_, EdgeFeature, def_, kind_, Kind, Angle (+14 more)

### Community 15 - "MarkingMenu"
Cohesion: 0.40
Nodes (3): MarkingMenu, enabled, public

### Community 16 - "CommandDialog"
Cohesion: 0.04
Nodes (31): CommandDialog, bodiesId_, bodiesLabel_, bodyInput_, buttons_, cmd_, conditional_, edgesId_ (+23 more)

### Community 17 - "Io.cpp"
Cohesion: 0.10
Nodes (18): MainWindow::print3d(), NamedShape, compoundOf(), exportShapes(), fmt(), formatForPath(), fromBrep(), importShape() (+10 more)

### Community 18 - "Unit"
Cohesion: 0.07
Nodes (45): MainWindow::lengthUnit(), ExpressionEnv, lengthUnit, lookup, ExpressionError, Quantity, angle, length (+37 more)

### Community 19 - "MainWindowTools.cpp"
Cohesion: 0.06
Nodes (25): MainWindow::applySection(), MainWindow::checkInterference(), MainWindow::chooseUnits(), MainWindow::driveJoints(), MainWindow::exportDesign(), MainWindow::formatLength(), MainWindow::gridSettings(), MainWindow::insertFile() (+17 more)

### Community 20 - ".hitTest"
Cohesion: 0.22
Nodes (5): angleInArc(), Hit, index, kind, segDistance()

### Community 21 - "Document"
Cohesion: 0.19
Nodes (7): ConstructAxisPoint, def_, kind_, differenceOrNull(), JointPick, frame, revolveAxis()

### Community 23 - "TEST"
Cohesion: 0.07
Nodes (9): Sketch, constraints, entities, points, texts, Sketch::addCircle(), Sketch::addLine(), rect() (+1 more)

### Community 24 - "Sketch.cpp"
Cohesion: 0.09
Nodes (18): Point, x, y, SketchError, entityTypeName(), isDimension(), Sketch::addConstraint(), Sketch::addSpline() (+10 more)

### Community 25 - "ViewportSketch.cpp"
Cohesion: 0.08
Nodes (7): faceStyle(), lineStyle(), rgb(), Viewport::lookAt(), Viewport::planePoint(), Viewport::toWidget(), height

### Community 26 - "SketchPalette"
Cohesion: 0.06
Nodes (26): flatButton(), QCheckBox, QLabel, QToolButton, QWidget, SketchEditor, SketchPalette, body_ (+18 more)

### Community 27 - "Profile"
Cohesion: 0.33
Nodes (5): Profile, area, face, x, y

### Community 28 - "CommandError"
Cohesion: 0.09
Nodes (29): CommandError, getBool(), getReal(), applyOperation(), bodyCentre(), bodyName(), Coil, def_ (+21 more)

### Community 29 - "AdskModule.cpp"
Cohesion: 0.10
Nodes (16): Application, bindAdsk(), BRepBodies, BRepBody, index, Component, Design, Product (+8 more)

### Community 30 - "Colors"
Cohesion: 0.07
Nodes (28): Colors, base, border, cubeBox, cubeText, errorBackground, grid, gridMajor (+20 more)

### Community 31 - "KernelError"
Cohesion: 0.21
Nodes (31): KernelError, vertices, asSolid(), boolean(), boundingBox(), chamfer(), chamferEx(), draft() (+23 more)

### Community 32 - "SketchOps.cpp"
Cohesion: 0.19
Nodes (26): at(), chainOf(), chamferCorner(), circularPattern(), copyEntities(), cornerAt(), cross(), dot() (+18 more)

### Community 33 - "Command.cpp"
Cohesion: 0.14
Nodes (16): expressionKey(), Dimension, Angle, Length, Unitless, checkInputValue(), CommandContext::evaluateExpression(), CommandDef::input() (+8 more)

### Community 34 - "ParameterCompleter"
Cohesion: 0.12
Nodes (8): ParameterCompleter, completer_, edit_, names_, ParameterCompleter::ParameterCompleter(), public, QCompleter, QLineEdit

### Community 35 - "Constraint"
Cohesion: 0.13
Nodes (12): Constraint, driven, entities, expression, hasLabel, labelX, labelY, name (+4 more)

### Community 37 - "MainWindow.cpp"
Cohesion: 0.05
Nodes (9): PythonHost, commandIcon(), MainWindow::MainWindow(), qs(), MainWindow::beginSketch(), MainWindow::buildSketchTab(), MainWindow::enterSketchMode(), MainWindow::exitSketchMode() (+1 more)

### Community 38 - "solve"
Cohesion: 0.12
Nodes (14): addConstraintChecked(), Layout, n, px, py, rad, makeLayout(), pack() (+6 more)

### Community 39 - "ViewportAnalysis.cpp"
Cohesion: 0.15
Nodes (4): packed(), ramp(), shade(), Viewport::buildAnalysis()

### Community 40 - "CommandSession"
Cohesion: 0.14
Nodes (6): CommandSession, inputs_, CommandRegistry::find(), CommandRegistry::run(), Session::begin(), Session::editFeature()

### Community 41 - "ConstraintType"
Cohesion: 0.08
Nodes (25): ConstraintType, Angle, Coincident, Collinear, Concentric, Diameter, Distance, Equal (+17 more)

### Community 42 - "TEST"
Cohesion: 0.09
Nodes (3): param(), TEST(), tmp()

### Community 43 - "Pick"
Cohesion: 0.13
Nodes (14): Pick, bodyArc, bodyPoint, bodySegment, hit, midpointOf, onEntity, onXAxis (+6 more)

### Community 44 - "Snap"
Cohesion: 0.06
Nodes (29): ext(), fixedColor(), freeColor(), qc(), rgb(), Snap, alignX, alignY (+21 more)

### Community 45 - "Kind"
Cohesion: 0.09
Nodes (21): HudField, edit, editing, kind, locked, value, Kind, Angle (+13 more)

### Community 46 - "Zip.cpp"
Cohesion: 0.20
Nodes (11): Entry, data, name, ZipError, crc32(), get16(), get32(), put16() (+3 more)

### Community 47 - "AnalysisSettings"
Cohesion: 0.10
Nodes (16): DragArrow, base, dir, radius, ref, ring, value, PendingLook (+8 more)

### Community 48 - "Document.cpp"
Cohesion: 0.12
Nodes (23): Document::axes(), Document::bodies(), Document::body(), Document::bodyName(), Document::components(), Document::features(), Document::historyMarker(), Document::lengthUnit() (+15 more)

### Community 49 - "SketchRecord"
Cohesion: 0.13
Nodes (14): ModelParameter, angle, expression, name, owner, value, SketchRecord, data (+6 more)

### Community 50 - "MainWindowSketch.cpp"
Cohesion: 0.08
Nodes (13): MainWindow::cancelSketch(), MainWindow::editSketch(), MainWindow::finishSketch(), MainWindow::onEdgeClicked(), MainWindow::onProfileClicked(), MainWindow::originalShape(), MainWindow::sketchPalette(), MainWindow::sketchVisible() (+5 more)

### Community 51 - "InputDef"
Cohesion: 0.08
Nodes (24): InputDef, choices, defaultValue, id, label, max, min, minExclusive (+16 more)

### Community 52 - "DocCommands.h"
Cohesion: 0.19
Nodes (5): bindTsr(), fromPy(), toPy(), typeName(), Document

### Community 54 - "MainWindowArrow.cpp"
Cohesion: 0.11
Nodes (8): ArrowPlacement, base, dir, edgePlacement(), facesPlacement(), MainWindow::attachArrowCompleters(), MainWindow::patternCentre(), MainWindow::pickedFaces()

### Community 55 - "Viewport.h"
Cohesion: 0.06
Nodes (19): AnalysisKind, CurvatureMap, Draft, None, Zebra, AnalysisSettings, curvatureScale, draftAngle (+11 more)

### Community 56 - "Theme.cpp"
Cohesion: 0.19
Nodes (6): setIconTheme(), darkColors(), darkPalette(), darkStyleSheet(), lightColors(), lightStyleSheet()

### Community 57 - "TEST"
Cohesion: 0.19
Nodes (3): slurp(), TEST(), tmp()

### Community 58 - "Entity"
Cohesion: 0.11
Nodes (17): Entity, a, b, center, construction, fit, projected, radius (+9 more)

### Community 59 - "xdrive.py"
Cohesion: 0.32
Nodes (14): button(), canvas(), click(), drag(), flush(), geometry(), key(), keycode() (+6 more)

### Community 61 - "SketchGeometry.cpp"
Cohesion: 0.12
Nodes (11): curve(), curves(), customPlaneSpec(), entityCurves(), interiorPoint(), planeFrame(), profileAt(), profiles() (+3 more)

### Community 62 - "Session"
Cohesion: 0.08
Nodes (7): PythonHost::PythonHost(), Session, commands_, doc_, listeners_, nextListener_, path_

### Community 63 - "ViewportArrow.cpp"
Cohesion: 0.07
Nodes (17): Viewport::frontEdgeOwner(), rgb(), segmentDistance(), Viewport::arrowAt(), Viewport::arrowMouseMove(), Viewport::arrowMousePress(), Viewport::arrowMouseRelease(), Viewport::arrowParam() (+9 more)

### Community 64 - "BodyFrame"
Cohesion: 0.15
Nodes (14): BodyFrame, diag, dx, dy, dz, x0, y0, z0 (+6 more)

### Community 65 - "CommandRegistry"
Cohesion: 0.12
Nodes (4): CommandRegistry, cmds_, CommandRegistry::add(), TEST()

### Community 66 - "cmath"
Cohesion: 0.21
Nodes (7): Result, error, ok, output, captured(), PythonHost::exec(), PythonHost::runScript()

### Community 67 - "TopoDS_Shape"
Cohesion: 0.19
Nodes (17): SurfacePoint, normal, point, Vec3, edgeMidpoint(), edgesNear(), frame(), makeBox() (+9 more)

### Community 68 - "Theme"
Cohesion: 0.22
Nodes (4): Theme, colors_, public, styled_

### Community 69 - "Session.cpp"
Cohesion: 0.20
Nodes (8): OwnedCommand, owned, OwningCommandSession, Session::addListener(), Session::open(), Session::rollHistory(), Session::save(), Session::Session()

### Community 70 - "Document::reevaluateParameters"
Cohesion: 0.28
Nodes (4): Document::expressionEnv(), Document::reevaluateParameters(), Document::userParameter(), Document::save()

### Community 71 - "src/main.cpp"
Cohesion: 0.07
Nodes (21): QDialog, Column, kComment, kExpression, kParameter, kUnit, kValue, number() (+13 more)

### Community 72 - "src/main.cpp"
Cohesion: 0.10
Nodes (4): QAbstractButton, QAction, grabWindowWithPanels(), writeLiveGeometry()

### Community 73 - "FileFormat"
Cohesion: 0.17
Nodes (12): FileFormat, Brep, Iges, Obj, Step, Stl, ThreeMF, FormatInfo (+4 more)

### Community 75 - "InputType"
Cohesion: 0.12
Nodes (17): InputType, Axis, Bodies, Body, Bool, Choice, Edges, Faces (+9 more)

### Community 76 - "string"
Cohesion: 0.13
Nodes (16): bodyNumber(), Document::axisFrame(), Document::component(), Document::componentOfBody(), Document::nextAxisName(), Document::nextBodyName(), Document::nextComponentName(), Document::nextDimensionName() (+8 more)

### Community 77 - "CommandDialog::CommandDialog"
Cohesion: 0.11
Nodes (5): ExpressionSpinBox, eval_, expression_, shown_, formatNumber()

### Community 80 - "SketchDisplay"
Cohesion: 0.12
Nodes (11): ProfileObject, index, sketch, SketchDisplay, construction, curves, fixedCurves, frame (+3 more)

### Community 81 - "DocCommands.cpp"
Cohesion: 0.04
Nodes (61): Adding a tool, Command, CommandDef, feature, icon, id, inputs, name (+53 more)

### Community 82 - "Measurement"
Cohesion: 0.09
Nodes (20): BoundingBox, max, min, Kind, Angle, Area, Length, Volume (+12 more)

### Community 83 - ".redrawAll"
Cohesion: 0.10
Nodes (7): NavPreset, Fusion, SolidWorks, Tinkercad, Viewport::setCurvatureComb(), Viewport::clearDragArrow(), Viewport::clearSecondArrow()

### Community 84 - "Kernel.h"
Cohesion: 0.10
Nodes (16): CommandRegistry::all(), Axis, X, Y, Z, BooleanOp, Cut, Intersect (+8 more)

### Community 85 - "Level"
Cohesion: 0.12
Nodes (13): debug(), error(), info(), Level, Debug, Error, Info, Warning (+5 more)

### Community 86 - "README.md"
Cohesion: 0.12
Nodes (13): Known gaps, Visual styles, Reference parts, Fusion feature checklist, Roadmap, Contents, Development, Features (+5 more)

### Community 87 - "DocumentError"
Cohesion: 0.10
Nodes (26): DocumentError, checkViewName(), Document::abortTransaction(), Document::addBody(), Document::addNamedView(), Document::addUserParameter(), Document::commitTransaction(), Document::openTransaction() (+18 more)

### Community 89 - "QObject"
Cohesion: 0.14
Nodes (7): QObject, SketchEditor::SketchEditor(), edges, Tool, op, shape, target

### Community 90 - "EntityType"
Cohesion: 0.29
Nodes (7): EntityType, Arc, Circle, Ellipse, Line, Spline, isRound()

### Community 91 - "MarkingMenu.cpp"
Cohesion: 0.06
Nodes (26): UiCommand, enabled, icon, id, name, panel, run, shortcut (+18 more)

### Community 92 - "ConstructionPlane"
Cohesion: 0.33
Nodes (5): ConstructionPlane, name, spec, Document::plane(), Document::setPlane()

### Community 93 - "Known differences still to build"
Cohesion: 0.15
Nodes (12): Data and files, Findings from the videos, Fusion study list, Interface, Known differences still to build, Navigation and display, Selection and the canvas, Sketch (+4 more)

### Community 95 - "FeatureEffect"
Cohesion: 0.07
Nodes (22): Body, display, name, shape, Component, bodies, name, FeatureEffect (+14 more)

### Community 96 - "UserParameter"
Cohesion: 0.33
Nodes (6): UserParameter, comment, expression, name, unit, value

### Community 97 - "WallSide"
Cohesion: 0.50
Nodes (4): WallSide, Center, Side1, Side2

### Community 98 - "FakeDoc"
Cohesion: 0.17
Nodes (6): FakeDoc, aborts, commits, items, open, snapshot

### Community 99 - "smoke"
Cohesion: 0.40
Nodes (5): smoke(), MassProperties, area, centerOfMass, volume

### Community 100 - "Development"
Cohesion: 0.40
Nodes (4): Build, Conventions, Development, Tests

### Community 101 - "string"
Cohesion: 0.10
Nodes (30): completeEdgeReferences(), completeFaceReferences(), decode(), decodeFaces(), dot(), edgeReference(), EdgeSig, full (+22 more)

### Community 102 - "sstream"
Cohesion: 0.15
Nodes (5): doc_(), Document::Document(), Document::ocafBytes(), ocafApplication(), Document::load()

### Community 103 - "Rect"
Cohesion: 0.50
Nodes (4): Session::notifyChanged(), Rect, l, p

### Community 104 - "Architecture"
Cohesion: 0.40
Nodes (4): Architecture, How a command works, The document, Units

### Community 106 - "SectionState"
Cohesion: 0.25
Nodes (7): SectionState, active, angle, flip, offset, plane, visible

### Community 107 - "Display"
Cohesion: 0.25
Nodes (7): Display, constraints, construction, dimensions, points, profiles, projected

### Community 108 - "TestFramework.h"
Cohesion: 0.15
Nodes (6): Case, fn, name, fail(), Failure, Register

### Community 109 - "PlaneEdges"
Cohesion: 0.22
Nodes (5): PlaneEdges, arcs, curves, segments, vertices

### Community 110 - "openWallBand"
Cohesion: 0.17
Nodes (17): Section, Circular, Square, Triangular, TopologyCounts, edges, faces, shells (+9 more)

### Community 111 - "ConstructionPoint"
Cohesion: 0.29
Nodes (5): ConstructionPoint, name, point, Document::point(), Document::setPoint()

### Community 113 - "ConstructionAxis"
Cohesion: 0.29
Nodes (5): ConstructionAxis, axis, name, Document::axis(), Document::setAxis()

### Community 114 - "uninstall.sh"
Cohesion: 0.52
Nodes (6): die(), manifest_for(), refresh(), uninstall.sh script, step(), usage()

### Community 115 - "install.sh"
Cohesion: 0.60
Nodes (5): die(), refresh(), install.sh script, step(), usage()

### Community 117 - "main"
Cohesion: 0.36
Nodes (4): listCommands(), main(), usage(), main()

### Community 118 - "Feature"
Cohesion: 0.22
Nodes (9): Feature, commandId, error, id, inputs, name, rolledBack, suppressed (+1 more)

### Community 123 - "Placement"
Cohesion: 0.25
Nodes (7): Placement, angle, cx, cy, dx, dy, scale

### Community 124 - "ChainSegment"
Cohesion: 0.67
Nodes (3): ChainSegment, entity, forward

### Community 125 - ".rebuild"
Cohesion: 0.13
Nodes (5): hiddenColour(), qc(), rgb(), sharpEdges(), wireColour()

## Knowledge Gaps
- **695 isolated node(s):** `ok`, `output`, `error`, `isReal`, `real` (+690 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 1322 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **25 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `optional` connect `optional` to `Viewport`, `MainWindow`, `Inputs`, `.updatePreview`, `Kernel.cpp`, `Io.cpp`, `Unit`, `ViewportSketch.cpp`, `SketchOps.cpp`, `.updateProfilesLabel`, `Snap`, `AnalysisSettings`, `Document.cpp`, `SketchRecord`, `InputDef`, `MainWindowArrow.cpp`, `Viewport.h`, `Session`, `ViewportArrow.cpp`, `TopoDS_Shape`, `Document::reevaluateParameters`, `SketchEditor.cpp`, `string`, `CommandDialog::CommandDialog`, `DocCommands.cpp`, `Kernel.h`, `ConstructionPlane`, `ConstructionPoint`, `ConstructionAxis`, `Feature`?**
  _High betweenness centrality (0.115) - this node is a cross-community bridge._
- **What connects `ok`, `output`, `error` to the rest of the system?**
  _695 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Viewport` be split into smaller, more focused modules?**
  _Cohesion score 0.016935374610486383 - nodes in this community are weakly interconnected._
- **Why does `Viewport` connect `Viewport` to `ViewportAnalysis.cpp`, `Viewport.cpp`, `optional`, `AnalysisSettings`, `SketchDisplay`, `QTimer`, `.redrawAll`, `DocCommands.h`, `.toPixels`, `TEST`, `Viewport.h`, `MainWindowTools.cpp`, `.rebuild`, `ViewportArrow.cpp`?**
  _High betweenness centrality (0.109) - this node is a cross-community bridge._
- **Should `Icons.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.06081754735792622 - nodes in this community are weakly interconnected._
- **Why does `SketchEditor` connect `SketchEditor` to `Viewport`, `Constraint`, `SketchEditor.cpp`, `Display`, `optional`, `PlaneEdges`, `Kind`, `Pick`, `Snap`, `.updatePreview`, `Unit`, `.hitTest`, `Viewport.h`, `QObject`, `Entity`, `Session`?**
  _High betweenness centrality (0.090) - this node is a cross-community bridge._
- **Should `tsr` be split into smaller, more focused modules?**
  _Cohesion score 0.06666666666666667 - nodes in this community are weakly interconnected._