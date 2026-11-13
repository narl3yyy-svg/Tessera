# Graph Report - tessera  (2026-11-13)

## Corpus Check
- 351 files · ~208,866 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 41 file(s) not represented in the graph (top: .drive 33, (none) 5, .cmake 1)

## Summary
- 3234 nodes · 8149 edges · 131 communities (104 shown, 27 thin omitted)
- Extraction: 84% EXTRACTED · 16% INFERRED · 0% AMBIGUOUS · INFERRED: 1280 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `3435cbce`
- Run `git rev-parse HEAD` and compare to check if the graph is stale.
- Run `graphify update .` after code changes (no API cost).

## Community Hubs (Navigation)
- Viewport
- Icons.cpp
- DocCommands.cpp
- MainWindow
- run_oracle.py
- CommandContext
- Document
- Viewport.cpp
- SketchEditor
- QString
- optional
- Kernel.cpp
- .projectAt
- Kind
- MainWindowTools.cpp
- CommandDialog
- Io.cpp
- Unit
- Session
- SketchEditor.cpp
- CommandDialog::CommandDialog
- .updatePreview
- TEST
- Sketch.cpp
- ViewportSketch.cpp
- SketchPalette
- Constraint
- Inputs
- AdskModule.cpp
- Colors
- KernelError
- SketchOps.cpp
- Session.cpp
- ParameterCompleter
- string
- CommandDialog.cpp
- MainWindow::MainWindow
- solve
- ViewportAnalysis.cpp
- Text
- ConstraintType
- TEST
- Pick
- Snap
- Kind
- Inputs
- Viewport.h
- Document.cpp
- .add
- MainWindowSketch.cpp
- InputDef
- .toPixels
- ViewportAnalysis.cpp
- .rebuild
- Theme.cpp
- MainWindow.cpp
- Entity
- xdrive.py
- SketchGeometry.cpp
- DocCommands.h
- ViewportArrow.cpp
- string
- CommandRegistry
- cmath
- TopoDS_Shape
- Theme
- FileFormat
- .motion
- src/main.cpp
- Icons.h
- QTimer
- Profile
- InputType
- Feature
- ParameterCompleter.cpp
- math
- Value.h
- SketchDisplay
- PYBIND11_EMBEDDED_MODULE
- Measurement
- Architecture
- Axis
- Level
- README.md
- Document.cpp
- test_feature_pattern.py
- SketchEditor::SketchEditor
- UserParameter
- UiCommand
- Known differences still to build
- ChainSegment
- CommandRegistry.cpp
- MarkingMenu
- BodyFrame
- FakeDoc
- TEST
- Zip.cpp
- Handle
- OcafApp.h
- Document::reevaluateParameters
- SketchRecord
- ModelParameter
- SectionState
- Display
- Dimension
- string
- openWallBand
- ConstructionPoint
- ConstructionAxis
- main
- uninstall.sh
- install.sh
- Mesh
- FeatureEffect
- BooleanOp
- ThreadInfo
- cmath
- smoke
- Sketch.h
- LAB_NOTES.md
- build.sh
- live-test.sh

## God Nodes (most connected - your core abstractions)
1. `Viewport` - 227 edges
2. `MainWindow` - 172 edges
3. `SketchEditor` - 168 edges
4. `Inputs` - 136 edges
5. `Document` - 128 edges
6. `CommandContext` - 102 edges
7. `render()` - 96 edges
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

## Communities (131 total, 27 thin omitted)

### Community 0 - "Viewport"
Cohesion: 0.02
Nodes (57): view_, QLineEdit, Viewport, analysis_, analysisObjects_, appliedGridStep_, arrowBoxes_, arrowDragging_ (+49 more)

### Community 1 - "Icons.cpp"
Cohesion: 0.07
Nodes (100): arc3Icon(), arcIcon(), arrow(), axisIcon(), box(), centerRectIcon(), chamferIcon(), circle2Icon() (+92 more)

### Community 2 - "DocCommands.cpp"
Cohesion: 0.10
Nodes (18): ConstructAxisPoint, def_, kind_, evaluateDimensions(), makeBox(), makeCone(), makeCylinder(), makeSphere() (+10 more)

### Community 4 - "MainWindow"
Cohesion: 0.03
Nodes (62): CommandDialog, MainWindow, active_, arrowInput_, arrowInput2_, bodiesBeforeCommand_, combEdges_, combPicking_ (+54 more)

### Community 5 - "run_oracle.py"
Cohesion: 0.08
Nodes (54): add_point(), arc_poly(), body_at(), body_list(), build_sketch(), chain(), circumcentre(), cm() (+46 more)

### Community 6 - "CommandContext"
Cohesion: 0.03
Nodes (55): Adding a tool, Command, CommandContext, CommandDef, feature, icon, id, inputs (+47 more)

### Community 7 - "Document"
Cohesion: 0.03
Nodes (11): Document, effects_, modified_, pendingTools_, registry_, replaying_, txnBodies_, FromOcaf (+3 more)

### Community 8 - "Viewport.cpp"
Cohesion: 0.05
Nodes (11): keys(), NavPreset, Fusion, SolidWorks, Tinkercad, qc(), rgb(), Viewport::Viewport() (+3 more)

### Community 9 - "SketchEditor"
Cohesion: 0.03
Nodes (44): SketchEditor, arcDrag_, arcDragMoved_, arcEndsChain_, arcFrom_, arcRef_, bodyEdges_, boxing_ (+36 more)

### Community 11 - "optional"
Cohesion: 0.15
Nodes (4): optional, ChamferType, DistanceAngle, TwoDistances

### Community 13 - ".projectAt"
Cohesion: 0.16
Nodes (4): PlaneEdges, arcs, segments, vertices

### Community 14 - "Kind"
Cohesion: 0.10
Nodes (19): EdgeFeature, def_, kind_, Kind, Angle, AxisCylinder, AxisEdge, AxisTwoPlanes (+11 more)

### Community 15 - "MainWindowTools.cpp"
Cohesion: 0.06
Nodes (26): QDialog, MainWindow::checkInterference(), MainWindow::chooseUnits(), MainWindow::driveJoints(), MainWindow::exportDesign(), MainWindow::formatLength(), MainWindow::gridSettings(), MainWindow::insertFile() (+18 more)

### Community 16 - "CommandDialog"
Cohesion: 0.05
Nodes (31): CommandDialog, bodiesId_, bodiesLabel_, bodyInput_, buttons_, cmd_, conditional_, edgesId_ (+23 more)

### Community 17 - "Io.cpp"
Cohesion: 0.12
Nodes (14): NamedShape, compoundOf(), exportShapes(), fmt(), formatForPath(), fromBrep(), importShape(), lower() (+6 more)

### Community 18 - "Unit"
Cohesion: 0.07
Nodes (45): MainWindow::lengthUnit(), ExpressionEnv, lengthUnit, lookup, ExpressionError, Quantity, angle, length (+37 more)

### Community 19 - "Session"
Cohesion: 0.09
Nodes (10): PythonHost::PythonHost(), main(), smoke(), Session, commands_, doc_, listeners_, nextListener_ (+2 more)

### Community 21 - "CommandDialog::CommandDialog"
Cohesion: 0.13
Nodes (5): CommandDialog::CommandDialog(), ExpressionSpinBox, eval_, expression_, shown_

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
Cohesion: 0.06
Nodes (26): flatButton(), QCheckBox, QLabel, QToolButton, QWidget, SketchEditor, SketchPalette, body_ (+18 more)

### Community 27 - "Constraint"
Cohesion: 0.14
Nodes (12): Constraint, driven, entities, expression, hasLabel, labelX, labelY, name (+4 more)

### Community 28 - "Inputs"
Cohesion: 0.11
Nodes (17): Inputs, axisOf(), Hole, def_, Loft, def_, Pipe, def_ (+9 more)

### Community 29 - "AdskModule.cpp"
Cohesion: 0.09
Nodes (16): Application, bindAdsk(), BRepBodies, BRepBody, index, Component, Design, Product (+8 more)

### Community 30 - "Colors"
Cohesion: 0.07
Nodes (28): Colors, base, border, cubeBox, cubeText, errorBackground, grid, gridMajor (+20 more)

### Community 31 - "KernelError"
Cohesion: 0.24
Nodes (25): KernelError, WallSide, Center, Side1, Side2, boolean(), chamfer(), chamferEx() (+17 more)

### Community 32 - "SketchOps.cpp"
Cohesion: 0.21
Nodes (19): at(), chainOf(), chamferCorner(), cornerAt(), cross(), dot(), extendLine(), filletCorner() (+11 more)

### Community 33 - "Session.cpp"
Cohesion: 0.06
Nodes (42): CommandSession, inputs_, expressionKey(), checkInputValue(), CommandContext::evaluateExpression(), CommandDef::input(), CommandSession::applyInTransaction(), CommandSession::cancel() (+34 more)

### Community 34 - "ParameterCompleter"
Cohesion: 0.18
Nodes (8): QObject, ParameterCompleter, completer_, edit_, names_, public, QCompleter, QLineEdit

### Community 35 - "string"
Cohesion: 0.12
Nodes (10): AddUserParameter, def_, Combine, def_, isIdentifier(), jointOrigin(), JointPick, frame (+2 more)

### Community 37 - "MainWindow::MainWindow"
Cohesion: 0.15
Nodes (4): PythonHost, MainWindow::MainWindow(), MainWindow::exitSketchMode(), MainWindow::showPreferences()

### Community 38 - "solve"
Cohesion: 0.17
Nodes (13): addConstraintChecked(), Layout, n, px, py, rad, makeLayout(), pack() (+5 more)

### Community 39 - "ViewportAnalysis.cpp"
Cohesion: 0.13
Nodes (5): packed(), ramp(), shade(), Viewport::buildAnalysis(), Viewport::setCurvatureComb()

### Community 40 - "Text"
Cohesion: 0.14
Nodes (5): Text, angle, font, point, text

### Community 41 - "ConstraintType"
Cohesion: 0.08
Nodes (24): ConstraintType, Angle, Coincident, Collinear, Concentric, Diameter, Distance, Equal (+16 more)

### Community 42 - "TEST"
Cohesion: 0.09
Nodes (3): param(), TEST(), tmp()

### Community 43 - "Pick"
Cohesion: 0.09
Nodes (17): Hit, index, kind, Pick, bodyArc, bodyPoint, bodySegment, hit (+9 more)

### Community 44 - "Snap"
Cohesion: 0.11
Nodes (18): Snap, alignX, alignY, bodyArc, bodySegment, entity, fromX, fromY (+10 more)

### Community 45 - "Kind"
Cohesion: 0.09
Nodes (21): HudField, edit, editing, kind, locked, value, Kind, Angle (+13 more)

### Community 46 - "Inputs"
Cohesion: 0.12
Nodes (21): CommandError, getBool(), getInt(), getReal(), applyOperation(), bodyCentre(), bodyName(), CopyFn (+13 more)

### Community 47 - "Viewport.h"
Cohesion: 0.06
Nodes (16): MarkingMenu::keyPressEvent(), AnalysisKind, CurvatureMap, Draft, None, Zebra, AnalysisSettings, curvatureScale (+8 more)

### Community 48 - "Document.cpp"
Cohesion: 0.09
Nodes (28): ConstructionPlane, name, spec, Document::axes(), Document::bodies(), Document::body(), Document::bodyName(), Document::components() (+20 more)

### Community 50 - "MainWindowSketch.cpp"
Cohesion: 0.06
Nodes (15): MainWindow::cancelSketch(), MainWindow::editSketch(), MainWindow::finishSketch(), MainWindow::onEdgeClicked(), MainWindow::originalShape(), MainWindow::sketchPalette(), MainWindow::sketchVisible(), MainWindow::startSketch() (+7 more)

### Community 51 - "InputDef"
Cohesion: 0.08
Nodes (24): InputDef, choices, defaultValue, id, label, max, min, minExclusive (+16 more)

### Community 54 - "ViewportAnalysis.cpp"
Cohesion: 0.10
Nodes (8): ArrowPlacement, base, dir, edgePlacement(), facesPlacement(), MainWindow::patternCentre(), MainWindow::pickedFaces(), MainWindow::updateDragArrow()

### Community 55 - ".rebuild"
Cohesion: 0.14
Nodes (8): ext(), fixedColor(), freeColor(), qc(), rgb(), wire(), Sketch::addLine(), rect()

### Community 56 - "Theme.cpp"
Cohesion: 0.19
Nodes (6): setIconTheme(), darkColors(), darkPalette(), darkStyleSheet(), lightColors(), lightStyleSheet()

### Community 57 - "MainWindow.cpp"
Cohesion: 0.06
Nodes (7): commandIcon(), qs(), MainWindow::beginSketch(), MainWindow::buildSketchTab(), MainWindow::enterSketchMode(), MainWindow::onProfileClicked(), MainWindow::applySection()

### Community 58 - "Entity"
Cohesion: 0.11
Nodes (17): Entity, a, b, center, construction, fit, projected, radius (+9 more)

### Community 59 - "xdrive.py"
Cohesion: 0.32
Nodes (14): button(), canvas(), click(), drag(), flush(), geometry(), key(), keycode() (+6 more)

### Community 61 - "SketchGeometry.cpp"
Cohesion: 0.12
Nodes (11): curve(), curves(), customPlaneSpec(), entityCurves(), interiorPoint(), planeFrame(), profileAt(), profiles() (+3 more)

### Community 62 - "DocCommands.h"
Cohesion: 0.23
Nodes (4): bindTsr(), fromPy(), toPy(), typeName()

### Community 63 - "ViewportArrow.cpp"
Cohesion: 0.07
Nodes (18): MarkingMenu::mouseMoveEvent(), QMouseEvent, ViewInteractor, Viewport::frontEdgeOwner(), rgb(), segmentDistance(), Viewport::arrowAt(), Viewport::arrowMouseMove() (+10 more)

### Community 64 - "string"
Cohesion: 0.10
Nodes (30): completeEdgeReferences(), completeFaceReferences(), decode(), decodeFaces(), dot(), edgeReference(), EdgeSig, full (+22 more)

### Community 65 - "CommandRegistry"
Cohesion: 0.12
Nodes (4): CommandRegistry, cmds_, CommandRegistry::add(), TEST()

### Community 66 - "cmath"
Cohesion: 0.25
Nodes (7): Result, error, ok, output, captured(), PythonHost::exec(), PythonHost::runScript()

### Community 67 - "TopoDS_Shape"
Cohesion: 0.15
Nodes (24): SurfacePoint, normal, point, Vec3, asSolid(), boundingBox(), edgeMidpoint(), edgesNear() (+16 more)

### Community 68 - "Theme"
Cohesion: 0.22
Nodes (4): Theme, colors_, public, styled_

### Community 69 - "FileFormat"
Cohesion: 0.17
Nodes (12): FileFormat, Brep, Iges, Obj, Step, Stl, ThreeMF, FormatInfo (+4 more)

### Community 70 - ".motion"
Cohesion: 0.21
Nodes (4): Coil, def_, Joint, def_

### Community 71 - "src/main.cpp"
Cohesion: 0.05
Nodes (22): grabWindowWithPanels(), writeLiveGeometry(), Column, kComment, kExpression, kParameter, kUnit, kValue (+14 more)

### Community 73 - "QTimer"
Cohesion: 0.09
Nodes (6): MarkingMenu::popupAt(), MarkingMenu::ringIndexAt(), QTimer, SelectionBox, crossing, height

### Community 74 - "Profile"
Cohesion: 0.33
Nodes (5): Profile, area, face, x, y

### Community 75 - "InputType"
Cohesion: 0.12
Nodes (17): InputType, Axis, Bodies, Body, Bool, Choice, Edges, Faces (+9 more)

### Community 76 - "Feature"
Cohesion: 0.22
Nodes (9): Feature, commandId, error, id, inputs, name, rolledBack, suppressed (+1 more)

### Community 80 - "SketchDisplay"
Cohesion: 0.08
Nodes (18): DragArrow, base, dir, value, PendingLook, center, frame, size (+10 more)

### Community 82 - "Measurement"
Cohesion: 0.09
Nodes (20): BoundingBox, max, min, Kind, Angle, Area, Length, Volume (+12 more)

### Community 83 - "Architecture"
Cohesion: 0.40
Nodes (4): Architecture, How a command works, The document, Units

### Community 84 - "Axis"
Cohesion: 0.50
Nodes (4): Axis, X, Y, Z

### Community 85 - "Level"
Cohesion: 0.16
Nodes (13): debug(), error(), info(), Level, Debug, Error, Info, Warning (+5 more)

### Community 86 - "README.md"
Cohesion: 0.10
Nodes (16): Build, Conventions, Development, Tests, Known gaps, Reference parts, Fusion feature checklist, Roadmap (+8 more)

### Community 87 - "Document.cpp"
Cohesion: 0.12
Nodes (25): DocumentError, Document::abortTransaction(), Document::addBody(), Document::addUserParameter(), Document::commitTransaction(), Document::openTransaction(), Document::recompute(), Document::recordFeature() (+17 more)

### Community 89 - "SketchEditor::SketchEditor"
Cohesion: 0.16
Nodes (6): SketchEditor::SketchEditor(), edges, Tool, op, shape, target

### Community 90 - "UserParameter"
Cohesion: 0.33
Nodes (6): UserParameter, comment, expression, name, unit, value

### Community 91 - "UiCommand"
Cohesion: 0.13
Nodes (12): UiCommand, enabled, icon, id, name, panel, run, shortcut (+4 more)

### Community 93 - "Known differences still to build"
Cohesion: 0.15
Nodes (12): Data and files, Findings from the videos, Fusion study list, Interface, Known differences still to build, Navigation and display, Selection and the canvas, Sketch (+4 more)

### Community 94 - "ChainSegment"
Cohesion: 0.67
Nodes (3): ChainSegment, entity, forward

### Community 96 - "MarkingMenu"
Cohesion: 0.29
Nodes (3): MarkingMenu, enabled, public

### Community 97 - "BodyFrame"
Cohesion: 0.15
Nodes (14): BodyFrame, diag, dx, dy, dz, x0, y0, z0 (+6 more)

### Community 98 - "FakeDoc"
Cohesion: 0.17
Nodes (6): FakeDoc, aborts, commits, items, open, snapshot

### Community 99 - "TEST"
Cohesion: 0.21
Nodes (3): slurp(), TEST(), tmp()

### Community 100 - "Zip.cpp"
Cohesion: 0.21
Nodes (11): Entry, data, name, ZipError, crc32(), get16(), get32(), put16() (+3 more)

### Community 102 - "OcafApp.h"
Cohesion: 0.22
Nodes (4): doc_(), Document::Document(), Document::ocafBytes(), ocafApplication()

### Community 103 - "Document::reevaluateParameters"
Cohesion: 0.24
Nodes (5): Document::expressionEnv(), Document::reevaluateParameters(), Document::userParameter(), Document::load(), Document::save()

### Community 104 - "SketchRecord"
Cohesion: 0.22
Nodes (8): SketchRecord, data, name, offset, plane, Document::setSketch(), Document::sketch(), utf8()

### Community 105 - "ModelParameter"
Cohesion: 0.29
Nodes (7): ModelParameter, angle, expression, name, owner, value, Document::modelParameters()

### Community 106 - "SectionState"
Cohesion: 0.25
Nodes (7): SectionState, active, angle, flip, offset, plane, visible

### Community 107 - "Display"
Cohesion: 0.25
Nodes (7): Display, constraints, construction, dimensions, points, profiles, projected

### Community 108 - "Dimension"
Cohesion: 0.50
Nodes (4): Dimension, Angle, Length, Unitless

### Community 109 - "string"
Cohesion: 0.20
Nodes (13): bodyNumber(), Document::axisFrame(), Document::component(), Document::componentOfBody(), Document::nextAxisName(), Document::nextBodyName(), Document::nextComponentName(), Document::nextDimensionName() (+5 more)

### Community 110 - "openWallBand"
Cohesion: 0.15
Nodes (19): Section, Circular, Square, Triangular, TopologyCounts, edges, faces, shells (+11 more)

### Community 111 - "ConstructionPoint"
Cohesion: 0.33
Nodes (5): ConstructionPoint, name, point, Document::point(), Document::setPoint()

### Community 112 - "ConstructionAxis"
Cohesion: 0.33
Nodes (5): ConstructionAxis, axis, name, Document::axis(), Document::setAxis()

### Community 113 - "main"
Cohesion: 0.24
Nodes (3): listCommands(), main(), usage()

### Community 114 - "uninstall.sh"
Cohesion: 0.52
Nodes (6): die(), manifest_for(), refresh(), uninstall.sh script, step(), usage()

### Community 115 - "install.sh"
Cohesion: 0.60
Nodes (5): die(), refresh(), install.sh script, step(), usage()

### Community 117 - "Mesh"
Cohesion: 0.40
Nodes (3): Mesh, nodes, triangles

### Community 118 - "FeatureEffect"
Cohesion: 0.09
Nodes (16): Body, display, name, shape, Component, bodies, name, FeatureEffect (+8 more)

### Community 119 - "BooleanOp"
Cohesion: 0.50
Nodes (4): BooleanOp, Cut, Intersect, Join

### Community 121 - "ThreadInfo"
Cohesion: 0.50
Nodes (4): ThreadInfo, diameter, internal, pitch

### Community 122 - "cmath"
Cohesion: 0.14
Nodes (6): Case, fn, name, fail(), Failure, Register

### Community 123 - "smoke"
Cohesion: 0.67
Nodes (3): MassProperties, area, centerOfMass

### Community 124 - "Sketch.h"
Cohesion: 0.25
Nodes (7): EntityType, Arc, Circle, Ellipse, Line, Spline, isRound()

## Knowledge Gaps
- **659 isolated node(s):** `ok`, `output`, `error`, `isReal`, `real` (+654 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 1243 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **27 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `optional` connect `optional` to `Viewport`, `DocCommands.cpp`, `MainWindow`, `QString`, `Kernel.cpp`, `Io.cpp`, `Unit`, `Session`, `SketchEditor.cpp`, `CommandDialog::CommandDialog`, `ViewportSketch.cpp`, `Constraint`, `Inputs`, `SketchOps.cpp`, `CommandDialog.cpp`, `Viewport.h`, `Document.cpp`, `InputDef`, `ViewportAnalysis.cpp`, `ViewportArrow.cpp`, `TopoDS_Shape`, `Feature`, `SketchDisplay`, `Document::reevaluateParameters`, `SketchRecord`, `string`, `ConstructionPoint`, `ConstructionAxis`?**
  _High betweenness centrality (0.109) - this node is a cross-community bridge._
- **What connects `ok`, `output`, `error` to the rest of the system?**
  _659 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Viewport` be split into smaller, more focused modules?**
  _Cohesion score 0.01780373166215639 - nodes in this community are weakly interconnected._
- **Why does `SketchEditor` connect `SketchEditor` to `Viewport`, `ParameterCompleter`, `Text`, `Display`, `optional`, `Kind`, `.projectAt`, `Pick`, `Snap`, `Unit`, `Session`, `SketchEditor.cpp`, `.updatePreview`, `.rebuild`, `SketchEditor::SketchEditor`, `Entity`, `Constraint`, `ViewportArrow.cpp`?**
  _High betweenness centrality (0.100) - this node is a cross-community bridge._
- **Should `Icons.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.06519246519246519 - nodes in this community are weakly interconnected._
- **Why does `Viewport` connect `Viewport` to `MainWindow`, `Handle`, `ViewportAnalysis.cpp`, `Viewport.cpp`, `QTimer`, `optional`, `Viewport.h`, `SketchDisplay`, `MainWindowTools.cpp`, `.toPixels`, `.selectedSubShapes`, `ViewportArrow.cpp`?**
  _High betweenness centrality (0.093) - this node is a cross-community bridge._
- **Should `DocCommands.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.10283687943262411 - nodes in this community are weakly interconnected._