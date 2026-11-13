# Graph Report - tessera  (2026-11-13)

## Corpus Check
- 366 files · ~224,211 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 51 file(s) not represented in the graph (top: .drive 43, (none) 5, .cmake 1)

## Summary
- 3420 nodes · 8591 edges · 128 communities (99 shown, 29 thin omitted)
- Extraction: 85% EXTRACTED · 15% INFERRED · 0% AMBIGUOUS · INFERRED: 1281 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `95196103`
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
- SketchEditor.cpp
- optional
- Kernel.cpp
- vector
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
- ValueInput
- Colors
- KernelError
- SketchOps.cpp
- Unit
- ParameterCompleter
- Constraint
- Expression.cpp
- MainWindow.cpp
- solve
- ViewportAnalysis.cpp
- QString
- ConstraintType
- AdskModule.cpp
- Pick
- .mouseMove
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
- Icons.h
- src/main.cpp
- Kernel.h
- FileFormat
- InputType
- NavPreset
- CommandDialog::CommandDialog
- math
- Architecture
- SketchDisplay
- DocCommands.cpp
- Measurement
- Push
- Level
- README.md
- Document.cpp
- test_feature_pattern.py
- Tool
- .add
- MarkingMenu.cpp
- Dimension
- Known differences still to build
- MainWindow::setSelectionFilter
- Feature
- Placement::apply
- FakeDoc
- CommandDialog.cpp
- KernelError
- sstream
- rect
- SectionState
- Display
- PlaneEdges
- openWallBand
- ConstructionPoint
- ConstructionAxis
- uninstall.sh
- install.sh
- PYBIND11_EMBEDDED_MODULE
- main
- Column
- Text
- Placement
- ChainSegment
- LAB_NOTES.md
- ParameterCompleter.cpp
- bindAdsk
- build.sh
- live-test.sh
- MarkingMenu

## God Nodes (most connected - your core abstractions)
1. `Viewport` - 251 edges
2. `SketchEditor` - 177 edges
3. `MainWindow` - 175 edges
4. `Inputs` - 138 edges
5. `Document` - 104 edges
6. `render()` - 103 edges
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

## Communities (128 total, 29 thin omitted)

### Community 0 - "Viewport"
Cohesion: 0.02
Nodes (66): view_, Viewport, analysis_, analysisObjects_, appliedGridStep_, arrowBoxes_, arrowDragging_, arrowGrab_ (+58 more)

### Community 1 - "Icons.cpp"
Cohesion: 0.06
Nodes (107): arc3Icon(), arcIcon(), arcTangentIcon(), arrow(), axisIcon(), box(), breakIcon(), centerRectIcon() (+99 more)

### Community 2 - "Session.cpp"
Cohesion: 0.06
Nodes (48): CommandSession, inputs_, expressionKey(), checkInputValue(), CommandContext::evaluateExpression(), CommandDef::input(), CommandSession::applyInTransaction(), CommandSession::cancel() (+40 more)

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
Nodes (13): Document, effects_, modified_, pendingTools_, registry_, replaying_, txnBodies_, FromOcaf (+5 more)

### Community 8 - "Viewport.cpp"
Cohesion: 0.05
Nodes (8): hiddenColour(), keys(), qc(), QKeyEvent, rgb(), sharpEdges(), Viewport::Viewport(), wireColour()

### Community 9 - "SketchEditor"
Cohesion: 0.03
Nodes (45): SketchEditor, arcDrag_, arcDragMoved_, arcEndsChain_, arcFrom_, arcRef_, bodyEdges_, boxing_ (+37 more)

### Community 10 - "SketchEditor.cpp"
Cohesion: 0.13
Nodes (4): angleInArc(), ccwContains(), circumcircle(), segDistance()

### Community 11 - "optional"
Cohesion: 0.07
Nodes (13): PythonHost::PythonHost(), optional, isEmpty(), Value, CommandRegistry::all(), Document, Profile, area (+5 more)

### Community 12 - "Kernel.cpp"
Cohesion: 0.04
Nodes (4): dot(), faceScore(), score(), vec()

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

### Community 17 - "Io.cpp"
Cohesion: 0.10
Nodes (17): NamedShape, compoundOf(), exportShapes(), fmt(), formatForPath(), fromBrep(), importShape(), lower() (+9 more)

### Community 18 - "Unit"
Cohesion: 0.16
Nodes (18): ExpressionError, Quantity, angle, length, value, describe(), evaluateExpression(), isIdentChar() (+10 more)

### Community 19 - "MainWindowTools.cpp"
Cohesion: 0.07
Nodes (26): QDialog, MainWindow::checkInterference(), MainWindow::chooseUnits(), MainWindow::driveJoints(), MainWindow::exportDesign(), MainWindow::formatLength(), MainWindow::gridSettings(), MainWindow::insertFile() (+18 more)

### Community 21 - "Document"
Cohesion: 0.19
Nodes (7): ConstructAxisPoint, def_, kind_, differenceOrNull(), JointPick, frame, revolveAxis()

### Community 22 - "MainWindow::MainWindow"
Cohesion: 0.12
Nodes (5): PythonHost, MainWindow::MainWindow(), MainWindow::beginSketch(), MainWindow::exitSketchMode(), MainWindow::showPreferences()

### Community 23 - "TEST"
Cohesion: 0.07
Nodes (9): Point, x, y, Sketch, constraints, entities, points, texts (+1 more)

### Community 24 - "Sketch.cpp"
Cohesion: 0.09
Nodes (16): SketchError, entityTypeName(), isDimension(), Sketch::addCircle(), Sketch::addConstraint(), Sketch::addSpline(), Sketch::addText(), Sketch::checkIndices() (+8 more)

### Community 25 - "ViewportSketch.cpp"
Cohesion: 0.08
Nodes (6): faceStyle(), lineStyle(), rgb(), Viewport::lookAt(), Viewport::planePoint(), Viewport::toWidget()

### Community 26 - "SketchPalette"
Cohesion: 0.05
Nodes (27): setIcon(), flatButton(), QCheckBox, QLabel, QToolButton, QWidget, SketchEditor, SketchPalette (+19 more)

### Community 27 - "Snap"
Cohesion: 0.11
Nodes (18): Snap, alignX, alignY, bodyArc, bodySegment, entity, fromX, fromY (+10 more)

### Community 28 - "CommandError"
Cohesion: 0.09
Nodes (29): CommandError, getBool(), getReal(), applyOperation(), bodyCentre(), bodyName(), Coil, def_ (+21 more)

### Community 29 - "ValueInput"
Cohesion: 0.22
Nodes (7): raiseIfError(), UserParameter, name, ValueInput, isReal, real, text

### Community 30 - "Colors"
Cohesion: 0.07
Nodes (28): Colors, base, border, cubeBox, cubeText, errorBackground, grid, gridMajor (+20 more)

### Community 31 - "KernelError"
Cohesion: 0.15
Nodes (37): Vec3, asSolid(), boolean(), boundingBox(), chamfer(), draft(), edgeMidpoint(), edgesNear() (+29 more)

### Community 32 - "SketchOps.cpp"
Cohesion: 0.17
Nodes (29): at(), chainOf(), chamferCorner(), circularPattern(), copyEntities(), cornerAt(), cross(), dot() (+21 more)

### Community 33 - "Unit"
Cohesion: 0.12
Nodes (15): bindAdsk(), MainWindow::lengthUnit(), Unit, Centimeter, Degree, Foot, Inch, Meter (+7 more)

### Community 34 - "ParameterCompleter"
Cohesion: 0.19
Nodes (8): QObject, ParameterCompleter, completer_, edit_, names_, public, QCompleter, QLineEdit

### Community 35 - "Constraint"
Cohesion: 0.08
Nodes (20): Constraint, driven, entities, expression, hasLabel, labelX, labelY, name (+12 more)

### Community 36 - "Expression.cpp"
Cohesion: 0.14
Nodes (12): ExpressionEnv, lengthUnit, lookup, evaluateQuantity(), expressionReferences(), isConstantName(), isFunctionName(), isPlainQuantity() (+4 more)

### Community 37 - "MainWindow.cpp"
Cohesion: 0.08
Nodes (5): commandIcon(), qs(), MainWindow::buildSketchTab(), MainWindow::enterSketchMode(), MainWindow::applySection()

### Community 38 - "solve"
Cohesion: 0.15
Nodes (12): addConstraintChecked(), Layout, n, px, py, rad, makeLayout(), pack() (+4 more)

### Community 39 - "ViewportAnalysis.cpp"
Cohesion: 0.12
Nodes (5): packed(), ramp(), shade(), Viewport::buildAnalysis(), Viewport::setCurvatureComb()

### Community 41 - "ConstraintType"
Cohesion: 0.08
Nodes (24): ConstraintType, Angle, Coincident, Collinear, Concentric, Diameter, Distance, Equal (+16 more)

### Community 42 - "AdskModule.cpp"
Cohesion: 0.22
Nodes (6): Application, BRepBodies, Component, Design, Product, UserParameters

### Community 43 - "Pick"
Cohesion: 0.11
Nodes (17): Hit, index, kind, Pick, bodyArc, bodyPoint, bodySegment, hit (+9 more)

### Community 44 - ".mouseMove"
Cohesion: 0.16
Nodes (7): ext(), fixedColor(), freeColor(), qc(), rgb(), wire(), Sketch::addLine()

### Community 45 - "Kind"
Cohesion: 0.09
Nodes (21): HudField, edit, editing, kind, locked, value, Kind, Angle (+13 more)

### Community 46 - "Zip.cpp"
Cohesion: 0.11
Nodes (14): Entry, data, name, ZipError, crc32(), get16(), get32(), put16() (+6 more)

### Community 47 - "AnalysisSettings"
Cohesion: 0.10
Nodes (16): DragArrow, base, dir, radius, ref, ring, value, PendingLook (+8 more)

### Community 48 - "Document.cpp"
Cohesion: 0.09
Nodes (32): ConstructionPlane, name, spec, NamedView, eye, name, size, target (+24 more)

### Community 49 - "SketchRecord"
Cohesion: 0.22
Nodes (9): ModelParameter, angle, expression, input, label, name, owner, unit (+1 more)

### Community 50 - "MainWindowSketch.cpp"
Cohesion: 0.07
Nodes (16): MainWindow::cancelSketch(), MainWindow::editSketch(), MainWindow::finishSketch(), MainWindow::onProfileClicked(), MainWindow::originalShape(), MainWindow::sketchPalette(), MainWindow::sketchVisible(), MainWindow::startSketch() (+8 more)

### Community 51 - "InputDef"
Cohesion: 0.08
Nodes (24): InputDef, choices, defaultValue, id, label, max, min, minExclusive (+16 more)

### Community 52 - "DocCommands.h"
Cohesion: 0.25
Nodes (4): bindTsr(), fromPy(), toPy(), typeName()

### Community 54 - "MainWindowArrow.cpp"
Cohesion: 0.12
Nodes (8): ArrowPlacement, base, dir, edgePlacement(), facesPlacement(), MainWindow::attachArrowCompleters(), MainWindow::patternCentre(), MainWindow::pickedFaces()

### Community 55 - "Viewport.h"
Cohesion: 0.07
Nodes (15): AnalysisKind, CurvatureMap, Draft, None, Zebra, AnalysisSettings, curvatureScale, draftAngle (+7 more)

### Community 56 - "Theme.cpp"
Cohesion: 0.19
Nodes (6): setIconTheme(), darkColors(), darkPalette(), darkStyleSheet(), lightColors(), lightStyleSheet()

### Community 58 - "Entity"
Cohesion: 0.12
Nodes (16): Entity, a, b, center, construction, fit, projected, radius (+8 more)

### Community 59 - "xdrive.py"
Cohesion: 0.32
Nodes (14): button(), canvas(), click(), drag(), flush(), geometry(), key(), keycode() (+6 more)

### Community 61 - "SketchGeometry.cpp"
Cohesion: 0.12
Nodes (11): curve(), curves(), customPlaneSpec(), entityCurves(), interiorPoint(), planeFrame(), profileAt(), profiles() (+3 more)

### Community 62 - "Session"
Cohesion: 0.07
Nodes (8): main(), smoke(), Session, commands_, doc_, listeners_, nextListener_, path_

### Community 63 - "ViewportArrow.cpp"
Cohesion: 0.05
Nodes (23): QMouseEvent, QTimer, ViewInteractor, Viewport::frontEdgeOwner(), rgb(), segmentDistance(), Viewport::arrowAt(), Viewport::arrowMouseMove() (+15 more)

### Community 64 - "BodyFrame"
Cohesion: 0.07
Nodes (29): BodyFrame, diag, dx, dy, dz, x0, y0, z0 (+21 more)

### Community 65 - "CommandRegistry"
Cohesion: 0.12
Nodes (4): CommandRegistry, cmds_, CommandRegistry::add(), TEST()

### Community 66 - "cmath"
Cohesion: 0.15
Nodes (11): Result, error, ok, output, captured(), PythonHost::exec(), PythonHost::runScript(), Case (+3 more)

### Community 67 - "requirePositive"
Cohesion: 0.17
Nodes (15): BoundingBox, max, min, WallSide, Center, Side1, Side2, frame() (+7 more)

### Community 68 - "Theme"
Cohesion: 0.22
Nodes (4): Theme, colors_, public, styled_

### Community 71 - "src/main.cpp"
Cohesion: 0.05
Nodes (18): grabWindowWithPanels(), writeLiveGeometry(), number(), ParametersDialog, building_, error_, filter_, listener_ (+10 more)

### Community 72 - "Kernel.h"
Cohesion: 0.08
Nodes (25): Axis, X, Y, Z, BooleanOp, Cut, Intersect, Join (+17 more)

### Community 73 - "FileFormat"
Cohesion: 0.17
Nodes (12): FileFormat, Brep, Iges, Obj, Step, Stl, ThreeMF, FormatInfo (+4 more)

### Community 75 - "InputType"
Cohesion: 0.12
Nodes (17): InputType, Axis, Bodies, Body, Bool, Choice, Edges, Faces (+9 more)

### Community 76 - "NavPreset"
Cohesion: 0.33
Nodes (4): NavPreset, Fusion, SolidWorks, Tinkercad

### Community 77 - "CommandDialog::CommandDialog"
Cohesion: 0.13
Nodes (5): CommandDialog::CommandDialog(), ExpressionSpinBox, eval_, expression_, shown_

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

### Community 85 - "Level"
Cohesion: 0.16
Nodes (13): debug(), error(), info(), Level, Debug, Error, Info, Warning (+5 more)

### Community 86 - "README.md"
Cohesion: 0.09
Nodes (17): Build, Conventions, Development, Tests, Known gaps, Visual styles, Reference parts, Fusion feature checklist (+9 more)

### Community 87 - "Document.cpp"
Cohesion: 0.05
Nodes (65): DocumentError, SketchRecord, data, name, offset, plane, bodyNumber(), checkViewName() (+57 more)

### Community 89 - "Tool"
Cohesion: 0.19
Nodes (5): SketchEditor::SketchEditor(), Tool, op, shape, target

### Community 91 - "MarkingMenu.cpp"
Cohesion: 0.07
Nodes (22): UiCommand, enabled, icon, id, name, panel, run, shortcut (+14 more)

### Community 92 - "Dimension"
Cohesion: 0.50
Nodes (4): Dimension, Angle, Length, Unitless

### Community 93 - "Known differences still to build"
Cohesion: 0.15
Nodes (12): Data and files, Findings from the videos, Fusion study list, Interface, Known differences still to build, Navigation and display, Selection and the canvas, Sketch (+4 more)

### Community 95 - "Feature"
Cohesion: 0.06
Nodes (28): Body, display, name, shape, Component, bodies, name, Feature (+20 more)

### Community 98 - "FakeDoc"
Cohesion: 0.17
Nodes (6): FakeDoc, aborts, commits, items, open, snapshot

### Community 101 - "KernelError"
Cohesion: 0.29
Nodes (14): KernelError, completeEdgeReferences(), completeFaceReferences(), decode(), decodeFaces(), edgeReference(), encode(), encodeFace() (+6 more)

### Community 102 - "sstream"
Cohesion: 0.15
Nodes (5): doc_(), Document::Document(), Document::ocafBytes(), ocafApplication(), Document::load()

### Community 103 - "rect"
Cohesion: 0.13
Nodes (5): SelectionBox, crossing, Viewport::placeArrowBoxes(), height, rect()

### Community 106 - "SectionState"
Cohesion: 0.25
Nodes (7): SectionState, active, angle, flip, offset, plane, visible

### Community 107 - "Display"
Cohesion: 0.25
Nodes (7): Display, constraints, construction, dimensions, points, profiles, projected

### Community 109 - "PlaneEdges"
Cohesion: 0.12
Nodes (6): PlaneEdges, arcs, curves, segments, vertices, edges

### Community 110 - "openWallBand"
Cohesion: 0.19
Nodes (15): Section, Circular, Square, Triangular, TopologyCounts, edges, shells, solids (+7 more)

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
Cohesion: 0.28
Nodes (3): listCommands(), main(), usage()

### Community 120 - "Column"
Cohesion: 0.25
Nodes (8): Column, kComment, kExpression, kName, kParameter, kStar, kUnit, kValue

### Community 121 - "Text"
Cohesion: 0.15
Nodes (5): Text, angle, font, point, text

### Community 123 - "Placement"
Cohesion: 0.25
Nodes (7): Placement, angle, cx, cy, dx, dy, scale

### Community 124 - "ChainSegment"
Cohesion: 0.67
Nodes (3): ChainSegment, entity, forward

### Community 142 - "MarkingMenu"
Cohesion: 0.40
Nodes (3): MarkingMenu, enabled, public

## Knowledge Gaps
- **704 isolated node(s):** `ok`, `output`, `error`, `isReal`, `real` (+699 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 1337 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **29 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `optional` connect `optional` to `Viewport`, `MainWindow`, `Inputs`, `SketchEditor.cpp`, `Kernel.cpp`, `CommandDialog`, `Io.cpp`, `Unit`, `ViewportSketch.cpp`, `KernelError`, `SketchOps.cpp`, `Unit`, `Expression.cpp`, `QString`, `.mouseMove`, `AnalysisSettings`, `Document.cpp`, `InputDef`, `MainWindowArrow.cpp`, `Viewport.h`, `Session`, `ViewportArrow.cpp`, `Kernel.h`, `SketchEditor.cpp`, `CommandDialog::CommandDialog`, `DocCommands.cpp`, `Document.cpp`, `Feature`, `CommandDialog.cpp`, `ConstructionPoint`, `ConstructionAxis`, `Text`?**
  _High betweenness centrality (0.119) - this node is a cross-community bridge._
- **What connects `ok`, `output`, `error` to the rest of the system?**
  _704 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Viewport` be split into smaller, more focused modules?**
  _Cohesion score 0.01650793650793651 - nodes in this community are weakly interconnected._
- **Why does `SketchEditor` connect `SketchEditor` to `Tool`, `Viewport`, `ParameterCompleter`, `Constraint`, `Unit`, `SketchEditor.cpp`, `Display`, `optional`, `Kind`, `PlaneEdges`, `Pick`, `.mouseMove`, `SketchEditor.cpp`, `Text`, `Snap`, `Session`, `ViewportArrow.cpp`?**
  _High betweenness centrality (0.117) - this node is a cross-community bridge._
- **Should `Icons.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.062481579722959035 - nodes in this community are weakly interconnected._
- **Why does `Viewport` connect `Viewport` to `rect`, `Viewport.cpp`, `ViewportAnalysis.cpp`, `optional`, `NavPreset`, `AnalysisSettings`, `SketchDisplay`, `.setSelectionFilter`, `Handle`, `.toPixels`, `MainWindowTools.cpp`, `Viewport.h`, `ViewportArrow.cpp`?**
  _High betweenness centrality (0.113) - this node is a cross-community bridge._
- **Should `Session.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.05593607305936073 - nodes in this community are weakly interconnected._