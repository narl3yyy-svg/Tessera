# Graph Report - tessera  (2026-11-13)

## Corpus Check
- 355 files · ~213,818 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 43 file(s) not represented in the graph (top: .drive 35, (none) 5, .cmake 1)

## Summary
- 3276 nodes · 8298 edges · 140 communities (111 shown, 29 thin omitted)
- Extraction: 84% EXTRACTED · 16% INFERRED · 0% AMBIGUOUS · INFERRED: 1307 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `afc30c9a`
- Run `git rev-parse HEAD` and compare to check if the graph is stale.
- Run `graphify update .` after code changes (no API cost).

## Community Hubs (Navigation)
- Viewport
- Icons.cpp
- Document.cpp
- MainWindow
- run_oracle.py
- string
- Document
- Viewport.cpp
- SketchEditor
- QString
- optional
- Kernel.cpp
- DocCommands.cpp
- Kind
- MainWindowTools.cpp
- CommandDialog
- Io.cpp
- Parser
- src/main.cpp
- SketchEditor.cpp
- Session
- .updatePreview
- TEST
- Sketch.cpp
- ViewportSketch.cpp
- SketchPalette
- Command
- sketchFor
- AdskModule.cpp
- Colors
- KernelError
- SketchOps.cpp
- Session.cpp
- ParameterCompleter
- Unit
- CommandDialog.cpp
- MainWindow::MainWindow
- solve
- .showDialog
- Constraint
- ConstraintType
- TEST
- Pick
- Snap
- Kind
- Inputs
- Viewport.h
- nameOf
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
- .apply
- src/main.cpp
- .hitTest
- Profile
- InputType
- string
- gp_Ax3
- math
- Value.h
- SketchDisplay
- PYBIND11_EMBEDDED_MODULE
- Measurement
- exportShapes
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
- FeatureEffect
- MarkingMenu
- BodyFrame
- FakeDoc
- TEST
- Zip.cpp
- ParameterCompleter.cpp
- OcafApp.h
- Document::reevaluateParameters
- SketchRecord
- Sketch.h
- SectionState
- Display
- Dimension
- PlaneEdges
- openWallBand
- ConstructionPoint
- Architecture
- main
- uninstall.sh
- install.sh
- Mesh
- Feature
- BooleanOp
- .openMarkingMenu
- ThreadInfo
- cmath
- Placement
- bindAdsk
- Viewport::Viewport
- Column
- Joints
- Icons.h
- MainWindow::setSelectionFilter
- ChamferType
- WallSide
- LAB_NOTES.md
- MassProperties
- build.sh
- live-test.sh

## God Nodes (most connected - your core abstractions)
1. `Viewport` - 227 edges
2. `SketchEditor` - 177 edges
3. `MainWindow` - 172 edges
4. `Inputs` - 136 edges
5. `Document` - 128 edges
6. `render()` - 102 edges
7. `CommandContext` - 102 edges
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

## Communities (140 total, 29 thin omitted)

### Community 0 - "Viewport"
Cohesion: 0.02
Nodes (56): view_, Viewport, analysis_, analysisObjects_, appliedGridStep_, arrowBoxes_, arrowDragging_, arrowGrab_ (+48 more)

### Community 1 - "Icons.cpp"
Cohesion: 0.06
Nodes (106): arc3Icon(), arcIcon(), arrow(), axisIcon(), box(), breakIcon(), centerRectIcon(), chamferIcon() (+98 more)

### Community 2 - "Document.cpp"
Cohesion: 0.10
Nodes (11): Document::features(), Document::historyMarker(), Document::plane(), Document::redo(), Document::removeFeature(), Document::setFeatureSuppressed(), Document::setTimeline(), Document::undo() (+3 more)

### Community 4 - "MainWindow"
Cohesion: 0.03
Nodes (62): CommandDialog, MainWindow, active_, arrowInput_, arrowInput2_, bodiesBeforeCommand_, combEdges_, combPicking_ (+54 more)

### Community 5 - "run_oracle.py"
Cohesion: 0.08
Nodes (54): add_point(), arc_poly(), body_at(), body_list(), build_sketch(), chain(), circumcentre(), cm() (+46 more)

### Community 6 - "string"
Cohesion: 0.15
Nodes (7): AddUserParameter, def_, CreateSketch, def_, isIdentifier(), NewComponent, def_

### Community 7 - "Document"
Cohesion: 0.04
Nodes (15): Document, effects_, modified_, pendingTools_, registry_, replaying_, txnBodies_, FromOcaf (+7 more)

### Community 8 - "Viewport.cpp"
Cohesion: 0.05
Nodes (7): qc(), QtFrameBuffer, rgb(), Viewport::setCurvatureComb(), Viewport::clearDragArrow(), Viewport::clearSecondArrow(), Viewport::setInteractor()

### Community 9 - "SketchEditor"
Cohesion: 0.03
Nodes (45): SketchEditor, arcDrag_, arcDragMoved_, arcEndsChain_, arcFrom_, arcRef_, bodyEdges_, boxing_ (+37 more)

### Community 10 - "QString"
Cohesion: 0.11
Nodes (6): ExpressionSpinBox, eval_, expression_, shown_, formatNumber(), dimensionOf()

### Community 12 - "Kernel.cpp"
Cohesion: 0.04
Nodes (6): dot(), faceScore(), isoCoarsePitch(), score(), topologyCounts(), vec()

### Community 13 - "DocCommands.cpp"
Cohesion: 0.10
Nodes (21): axisOf(), bodyCentre(), checkPattern(), CopyFn, differenceOrNull(), InsertGeometry, def_, Mirror (+13 more)

### Community 14 - "Kind"
Cohesion: 0.07
Nodes (25): ConstructPlane, def_, kind_, EdgeFeature, def_, kind_, FaceFeature, def_ (+17 more)

### Community 15 - "MainWindowTools.cpp"
Cohesion: 0.07
Nodes (24): QDialog, MainWindow::checkInterference(), MainWindow::chooseUnits(), MainWindow::driveJoints(), MainWindow::exportDesign(), MainWindow::formatLength(), MainWindow::gridSettings(), MainWindow::insertFile() (+16 more)

### Community 16 - "CommandDialog"
Cohesion: 0.05
Nodes (31): CommandDialog, bodiesId_, bodiesLabel_, bodyInput_, buttons_, cmd_, conditional_, edgesId_ (+23 more)

### Community 17 - "Io.cpp"
Cohesion: 0.12
Nodes (4): fromBrep(), lower(), toBrep(), xmlEscape()

### Community 18 - "Parser"
Cohesion: 0.09
Nodes (30): ExpressionEnv, lengthUnit, lookup, ExpressionError, Quantity, angle, length, value (+22 more)

### Community 21 - "Session"
Cohesion: 0.09
Nodes (10): PythonHost::PythonHost(), main(), smoke(), Session, commands_, doc_, listeners_, nextListener_ (+2 more)

### Community 23 - "TEST"
Cohesion: 0.07
Nodes (8): Sketch, constraints, entities, points, texts, Sketch::addCircle(), Sketch::addLine(), TEST()

### Community 24 - "Sketch.cpp"
Cohesion: 0.09
Nodes (18): Point, x, y, SketchError, entityTypeName(), isDimension(), Sketch::addConstraint(), Sketch::addSpline() (+10 more)

### Community 25 - "ViewportSketch.cpp"
Cohesion: 0.08
Nodes (6): faceStyle(), lineStyle(), rgb(), Viewport::lookAt(), Viewport::planePoint(), Viewport::toWidget()

### Community 26 - "SketchPalette"
Cohesion: 0.06
Nodes (25): QCheckBox, QLabel, QToolButton, QWidget, SketchEditor, SketchPalette, body_, constraints_ (+17 more)

### Community 27 - "Command"
Cohesion: 0.15
Nodes (19): Adding a tool, Command, getReal(), makeBox(), makeCone(), makeCylinder(), makeSphere(), makeTorus() (+11 more)

### Community 28 - "sketchFor"
Cohesion: 0.11
Nodes (14): Hole, def_, Loft, def_, Pipe, def_, profilesOf(), sectionOf() (+6 more)

### Community 29 - "AdskModule.cpp"
Cohesion: 0.13
Nodes (13): Application, BRepBodies, Component, Design, Product, raiseIfError(), UserParameter, name (+5 more)

### Community 30 - "Colors"
Cohesion: 0.07
Nodes (28): Colors, base, border, cubeBox, cubeText, errorBackground, grid, gridMajor (+20 more)

### Community 31 - "KernelError"
Cohesion: 0.23
Nodes (29): KernelError, asSolid(), boolean(), chamfer(), chamferEx(), draft(), extrude(), extrudeEx() (+21 more)

### Community 32 - "SketchOps.cpp"
Cohesion: 0.22
Nodes (25): at(), chainOf(), chamferCorner(), circularPattern(), copyEntities(), cross(), dot(), extendLine() (+17 more)

### Community 33 - "Session.cpp"
Cohesion: 0.06
Nodes (42): CommandSession, inputs_, expressionKey(), checkInputValue(), CommandContext::evaluateExpression(), CommandDef::input(), CommandSession::applyInTransaction(), CommandSession::cancel() (+34 more)

### Community 34 - "ParameterCompleter"
Cohesion: 0.19
Nodes (8): QObject, ParameterCompleter, completer_, edit_, names_, public, QCompleter, QLineEdit

### Community 35 - "Unit"
Cohesion: 0.14
Nodes (16): MainWindow::lengthUnit(), Unit, Centimeter, Degree, Foot, Inch, Meter, Millimeter (+8 more)

### Community 37 - "MainWindow::MainWindow"
Cohesion: 0.14
Nodes (4): PythonHost, flatButton(), MainWindow::MainWindow(), MainWindow::showPreferences()

### Community 38 - "solve"
Cohesion: 0.18
Nodes (12): addConstraintChecked(), Layout, n, px, py, rad, makeLayout(), pack() (+4 more)

### Community 40 - "Constraint"
Cohesion: 0.10
Nodes (20): Constraint, driven, entities, expression, hasLabel, labelX, labelY, name (+12 more)

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
Cohesion: 0.11
Nodes (18): Snap, alignX, alignY, bodyArc, bodySegment, entity, fromX, fromY (+10 more)

### Community 45 - "Kind"
Cohesion: 0.09
Nodes (21): HudField, edit, editing, kind, locked, value, Kind, Angle (+13 more)

### Community 46 - "Inputs"
Cohesion: 0.07
Nodes (18): CommandContext, CommandError, Inputs, CommandSession::CommandSession(), getBool(), bodyName(), checkBody(), CircularPattern (+10 more)

### Community 47 - "Viewport.h"
Cohesion: 0.06
Nodes (17): MarkingMenu::keyPressEvent(), AnalysisKind, CurvatureMap, Draft, None, Zebra, AnalysisSettings, curvatureScale (+9 more)

### Community 48 - "nameOf"
Cohesion: 0.13
Nodes (20): ConstructionPlane, name, spec, Document::axes(), Document::bodies(), Document::body(), Document::bodyName(), Document::components() (+12 more)

### Community 50 - "MainWindowSketch.cpp"
Cohesion: 0.06
Nodes (16): MainWindow::cancelSketch(), MainWindow::editSketch(), MainWindow::finishSketch(), MainWindow::onProfileClicked(), MainWindow::originalShape(), MainWindow::sketchPalette(), MainWindow::sketchVisible(), MainWindow::startSketch() (+8 more)

### Community 51 - "InputDef"
Cohesion: 0.04
Nodes (52): CommandDef, feature, icon, id, inputs, name, nameInput, panel (+44 more)

### Community 54 - "ViewportAnalysis.cpp"
Cohesion: 0.07
Nodes (12): ArrowPlacement, base, dir, edgePlacement(), facesPlacement(), MainWindow::attachArrowCompleters(), MainWindow::patternCentre(), MainWindow::pickedFaces() (+4 more)

### Community 55 - ".rebuild"
Cohesion: 0.13
Nodes (11): ext(), fixedColor(), freeColor(), qc(), rgb(), wire(), Text, angle (+3 more)

### Community 56 - "Theme.cpp"
Cohesion: 0.19
Nodes (6): setIconTheme(), darkColors(), darkPalette(), darkStyleSheet(), lightColors(), lightStyleSheet()

### Community 57 - "MainWindow.cpp"
Cohesion: 0.09
Nodes (4): commandIcon(), qs(), MainWindow::exitSketchMode(), MainWindow::applySection()

### Community 58 - "Entity"
Cohesion: 0.22
Nodes (9): Entity, a, b, center, construction, fit, projected, radius (+1 more)

### Community 59 - "xdrive.py"
Cohesion: 0.32
Nodes (14): button(), canvas(), click(), drag(), flush(), geometry(), key(), keycode() (+6 more)

### Community 62 - "DocCommands.h"
Cohesion: 0.25
Nodes (4): bindTsr(), fromPy(), toPy(), typeName()

### Community 63 - "ViewportArrow.cpp"
Cohesion: 0.07
Nodes (18): MarkingMenu::mouseMoveEvent(), QMouseEvent, ViewInteractor, Viewport::frontEdgeOwner(), rgb(), segmentDistance(), Viewport::arrowAt(), Viewport::arrowMouseMove() (+10 more)

### Community 64 - "string"
Cohesion: 0.16
Nodes (20): boundingBox(), completeEdgeReferences(), completeFaceReferences(), decode(), decodeFaces(), edgeReference(), EdgeSig, full (+12 more)

### Community 65 - "CommandRegistry"
Cohesion: 0.12
Nodes (4): CommandRegistry, cmds_, CommandRegistry::add(), TEST()

### Community 66 - "cmath"
Cohesion: 0.25
Nodes (7): Result, error, ok, output, captured(), PythonHost::exec(), PythonHost::runScript()

### Community 67 - "TopoDS_Shape"
Cohesion: 0.20
Nodes (18): SurfacePoint, normal, point, Vec3, edgeMidpoint(), edgesNear(), frame(), makeCone() (+10 more)

### Community 68 - "Theme"
Cohesion: 0.22
Nodes (4): Theme, colors_, public, styled_

### Community 69 - "FileFormat"
Cohesion: 0.17
Nodes (12): FileFormat, Brep, Iges, Obj, Step, Stl, ThreeMF, FormatInfo (+4 more)

### Community 70 - ".apply"
Cohesion: 0.13
Nodes (12): applyOperation(), Coil, def_, Extrude, def_, Joint, def_, jointOrigin() (+4 more)

### Community 71 - "src/main.cpp"
Cohesion: 0.11
Nodes (14): number(), ParametersDialog, building_, error_, listener_, ParametersDialog::ParametersDialog(), public, rebuildPending_ (+6 more)

### Community 72 - ".hitTest"
Cohesion: 0.17
Nodes (4): Hit, index, kind, segDistance()

### Community 74 - "Profile"
Cohesion: 0.33
Nodes (5): Profile, area, face, x, y

### Community 75 - "InputType"
Cohesion: 0.12
Nodes (17): InputType, Axis, Bodies, Body, Bool, Choice, Edges, Faces (+9 more)

### Community 76 - "string"
Cohesion: 0.17
Nodes (15): bodyNumber(), Document::component(), Document::componentOfBody(), Document::nextAxisName(), Document::nextBodyName(), Document::nextComponentName(), Document::nextDimensionName(), Document::nextPlaneName() (+7 more)

### Community 77 - "gp_Ax3"
Cohesion: 0.31
Nodes (9): curve(), curves(), entityCurves(), interiorPoint(), profileAt(), profiles(), textShape(), toSketch() (+1 more)

### Community 80 - "SketchDisplay"
Cohesion: 0.08
Nodes (18): DragArrow, base, dir, value, PendingLook, center, frame, size (+10 more)

### Community 82 - "Measurement"
Cohesion: 0.13
Nodes (14): Kind, Angle, Area, Length, Volume, Measurement, from, hasLine (+6 more)

### Community 83 - "exportShapes"
Cohesion: 0.35
Nodes (10): NamedShape, compoundOf(), exportShapes(), fmt(), formatForPath(), importShape(), meshOf(), scaled() (+2 more)

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
Cohesion: 0.11
Nodes (21): DocumentError, Document::abortTransaction(), Document::addBody(), Document::addUserParameter(), Document::axisFrame(), Document::bodyShapes(), Document::commitTransaction(), Document::effectOf() (+13 more)

### Community 89 - "SketchEditor::SketchEditor"
Cohesion: 0.11
Nodes (6): SketchEditor::SketchEditor(), edges, Tool, op, shape, target

### Community 90 - "UserParameter"
Cohesion: 0.33
Nodes (6): UserParameter, comment, expression, name, unit, value

### Community 91 - "UiCommand"
Cohesion: 0.10
Nodes (14): UiCommand, enabled, icon, id, name, panel, run, shortcut (+6 more)

### Community 93 - "Known differences still to build"
Cohesion: 0.15
Nodes (12): Data and files, Findings from the videos, Fusion study list, Interface, Known differences still to build, Navigation and display, Selection and the canvas, Sketch (+4 more)

### Community 94 - "ChainSegment"
Cohesion: 0.67
Nodes (3): ChainSegment, entity, forward

### Community 95 - "FeatureEffect"
Cohesion: 0.10
Nodes (10): Component, bodies, name, FeatureEffect, bodies, tools, Document::featureEffect(), Document::openTransaction() (+2 more)

### Community 96 - "MarkingMenu"
Cohesion: 0.29
Nodes (3): MarkingMenu, enabled, public

### Community 97 - "BodyFrame"
Cohesion: 0.09
Nodes (22): BodyFrame, diag, dx, dy, dz, x0, y0, z0 (+14 more)

### Community 98 - "FakeDoc"
Cohesion: 0.17
Nodes (6): FakeDoc, aborts, commits, items, open, snapshot

### Community 99 - "TEST"
Cohesion: 0.16
Nodes (3): slurp(), TEST(), tmp()

### Community 100 - "Zip.cpp"
Cohesion: 0.21
Nodes (11): Entry, data, name, ZipError, crc32(), get16(), get32(), put16() (+3 more)

### Community 102 - "OcafApp.h"
Cohesion: 0.17
Nodes (5): doc_(), Document::Document(), Document::ocafBytes(), ocafApplication(), Document::load()

### Community 103 - "Document::reevaluateParameters"
Cohesion: 0.32
Nodes (3): Document::expressionEnv(), Document::reevaluateParameters(), Document::save()

### Community 104 - "SketchRecord"
Cohesion: 0.22
Nodes (8): SketchRecord, data, name, offset, plane, Document::setSketch(), Document::sketch(), utf8()

### Community 105 - "Sketch.h"
Cohesion: 0.25
Nodes (7): EntityType, Arc, Circle, Ellipse, Line, Spline, isRound()

### Community 106 - "SectionState"
Cohesion: 0.25
Nodes (7): SectionState, active, angle, flip, offset, plane, visible

### Community 107 - "Display"
Cohesion: 0.25
Nodes (7): Display, constraints, construction, dimensions, points, profiles, projected

### Community 108 - "Dimension"
Cohesion: 0.50
Nodes (4): Dimension, Angle, Length, Unitless

### Community 109 - "PlaneEdges"
Cohesion: 0.25
Nodes (5): PlaneEdges, arcs, curves, segments, vertices

### Community 110 - "openWallBand"
Cohesion: 0.14
Nodes (20): BoundingBox, max, min, Section, Circular, Square, Triangular, TopologyCounts (+12 more)

### Community 111 - "ConstructionPoint"
Cohesion: 0.33
Nodes (4): ConstructionPoint, name, point, Document::point()

### Community 112 - "Architecture"
Cohesion: 0.40
Nodes (4): Architecture, How a command works, The document, Units

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

### Community 118 - "Feature"
Cohesion: 0.07
Nodes (24): Body, display, name, shape, ConstructionAxis, axis, name, Feature (+16 more)

### Community 119 - "BooleanOp"
Cohesion: 0.50
Nodes (4): BooleanOp, Cut, Intersect, Join

### Community 120 - ".openMarkingMenu"
Cohesion: 0.09
Nodes (5): MainWindow::beginSketch(), MainWindow::buildSketchTab(), MainWindow::enterSketchMode(), MainWindow::buildUiCommands(), QTimer

### Community 121 - "ThreadInfo"
Cohesion: 0.50
Nodes (4): ThreadInfo, diameter, internal, pitch

### Community 122 - "cmath"
Cohesion: 0.15
Nodes (6): Case, fn, name, fail(), Failure, Register

### Community 123 - "Placement"
Cohesion: 0.25
Nodes (7): Placement, angle, cx, cy, dx, dy, scale

### Community 124 - "bindAdsk"
Cohesion: 0.29
Nodes (3): bindAdsk(), BRepBody, index

### Community 125 - "Viewport::Viewport"
Cohesion: 0.11
Nodes (9): keys(), NavPreset, Fusion, SolidWorks, Tinkercad, SelectionBox, crossing, Viewport::Viewport() (+1 more)

### Community 126 - "Column"
Cohesion: 0.33
Nodes (6): Column, kComment, kExpression, kParameter, kUnit, kValue

### Community 127 - "Joints"
Cohesion: 0.36
Nodes (3): cornerAt(), Joints, parent_

### Community 130 - "ChamferType"
Cohesion: 0.67
Nodes (3): ChamferType, DistanceAngle, TwoDistances

### Community 132 - "WallSide"
Cohesion: 0.50
Nodes (4): WallSide, Center, Side1, Side2

### Community 134 - "MassProperties"
Cohesion: 0.67
Nodes (3): MassProperties, area, centerOfMass

## Knowledge Gaps
- **665 isolated node(s):** `ok`, `output`, `error`, `isReal`, `real` (+660 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 1254 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **29 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `Viewport` connect `Viewport` to `.leaveEvent`, `Viewport.cpp`, `QTimer`, `optional`, `Viewport.h`, `SketchDisplay`, `MainWindowTools.cpp`, `.toPixels`, `ViewportAnalysis.cpp`, `.openMarkingMenu`, `.selectedSubShapes`, `Viewport::Viewport`, `ViewportArrow.cpp`?**
  _High betweenness centrality (0.099) - this node is a cross-community bridge._
- **What connects `ok`, `output`, `error` to the rest of the system?**
  _665 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Viewport` be split into smaller, more focused modules?**
  _Cohesion score 0.01815408085430969 - nodes in this community are weakly interconnected._
- **Why does `SketchEditor` connect `SketchEditor` to `Viewport`, `ParameterCompleter`, `Unit`, `.hitTest`, `Constraint`, `Display`, `optional`, `Kind`, `PlaneEdges`, `Pick`, `Snap`, `SketchEditor.cpp`, `Session`, `.updatePreview`, `.rebuild`, `SketchEditor::SketchEditor`, `ViewportArrow.cpp`?**
  _High betweenness centrality (0.092) - this node is a cross-community bridge._
- **Should `Icons.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.062481579722959035 - nodes in this community are weakly interconnected._
- **Why does `optional` connect `optional` to `Viewport`, `Document.cpp`, `MainWindow`, `QString`, `Kernel.cpp`, `DocCommands.cpp`, `Parser`, `SketchEditor.cpp`, `Session`, `.updatePreview`, `ViewportSketch.cpp`, `sketchFor`, `Unit`, `CommandDialog.cpp`, `Viewport.h`, `nameOf`, `InputDef`, `ViewportAnalysis.cpp`, `ViewportArrow.cpp`, `TopoDS_Shape`, `.hitTest`, `string`, `SketchDisplay`, `exportShapes`, `SketchRecord`, `ConstructionPoint`, `Feature`, `Joints`?**
  _High betweenness centrality (0.090) - this node is a cross-community bridge._
- **Should `Document.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.09538461538461539 - nodes in this community are weakly interconnected._