# Graph Report - tessera  (2026-11-13)

## Corpus Check
- 337 files · ~194,924 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 31 file(s) not represented in the graph (top: .drive 23, (none) 5, .cmake 1)

## Summary
- 3141 nodes · 7856 edges · 125 communities (104 shown, 21 thin omitted)
- Extraction: 85% EXTRACTED · 15% INFERRED · 0% AMBIGUOUS · INFERRED: 1216 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `b8614447`
- Run `git rev-parse HEAD` and compare to check if the graph is stale.
- Run `graphify update .` after code changes (no API cost).

## Community Hubs (Navigation)
- Viewport
- Icons.cpp
- DocCommands.cpp
- MainWindow
- run_oracle.py
- Inputs
- Document
- Viewport.cpp
- SketchEditor
- Dimension
- optional
- Kernel.cpp
- PlaneEdges
- Kind
- MainWindowTools.cpp
- CommandDialog
- Io.cpp
- Unit
- SketchGeometry.cpp
- .press
- fromInternal
- MainWindow.cpp
- TEST
- Sketch.cpp
- ViewportSketch.cpp
- SketchPalette
- sketchFor
- AdskModule.cpp
- Colors
- TopoDS_Shape
- SketchOps.cpp
- Command.cpp
- ParameterCompleter
- string
- .openMarkingMenu
- Viewport.h
- solve
- UiCommand
- src/main.cpp
- ConstraintType
- TEST
- Pick
- Snap
- Kind
- .updatePreview
- AnalysisSettings
- Document.cpp
- QString
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
- TestFramework.h
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
- ViewportAnalysis.cpp
- CommandSession
- SketchDisplay
- string
- Measurement
- rect
- Entity
- Level
- README.md
- cmath
- CommandRegistry::run
- SketchEditor::SketchEditor
- Value.h
- BoundingBox
- Known differences still to build
- .add
- .planeFrame
- BodyFrame
- FakeDoc
- patternFeatures
- Zip.cpp
- DocCommands.h
- .buildNavBar
- sstream
- NavPreset
- ConstructionAxis
- SectionState
- Display
- Profile
- Document::recompute
- Kernel.h
- Session::addListener
- ConstructionPoint
- Mesh
- uninstall.sh
- install.sh
- Session::notifyChanged
- Column
- UserParameter
- MarkingMenu
- ChainSegment
- LAB_NOTES.md
- build.sh
- live-test.sh

## God Nodes (most connected - your core abstractions)
1. `Viewport` - 219 edges
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
- `Architecture` --references--> `InputDef`  [INFERRED]
  docs/ARCHITECTURE.md → modules/core/include/tsr/core/Command.h
- `Architecture` --references--> `CommandDef`  [INFERRED]
  docs/ARCHITECTURE.md → modules/core/include/tsr/core/Command.h
- `Architecture` --references--> `CommandRegistry`  [INFERRED]
  docs/ARCHITECTURE.md → modules/core/include/tsr/core/CommandRegistry.h

## Import Cycles
- None detected.

## Communities (125 total, 21 thin omitted)

### Community 0 - "Viewport"
Cohesion: 0.02
Nodes (53): view_, Viewport, analysis_, analysisObjects_, appliedGridStep_, arrowBoxes_, arrowDragging_, arrowGrab_ (+45 more)

### Community 1 - "Icons.cpp"
Cohesion: 0.07
Nodes (93): arcIcon(), arrow(), axisIcon(), box(), centerRectIcon(), chamferIcon(), circleIcon(), coilIcon() (+85 more)

### Community 2 - "DocCommands.cpp"
Cohesion: 0.04
Nodes (55): Adding a tool, Command, CommandDef, feature, icon, id, inputs, name (+47 more)

### Community 4 - "MainWindow"
Cohesion: 0.03
Nodes (63): Known gaps, CommandDialog, MainWindow, active_, arrowInput_, arrowInput2_, bodiesBeforeCommand_, combEdges_ (+55 more)

### Community 5 - "run_oracle.py"
Cohesion: 0.08
Nodes (54): add_point(), arc_poly(), body_at(), body_list(), build_sketch(), chain(), circumcentre(), cm() (+46 more)

### Community 6 - "Inputs"
Cohesion: 0.08
Nodes (23): CommandContext, CommandError, Inputs, CommandSession::CommandSession(), getBool(), applyOperation(), bodyCentre(), bodyName() (+15 more)

### Community 7 - "Document"
Cohesion: 0.04
Nodes (16): Document, effects_, modified_, pendingTools_, registry_, replaying_, txnBodies_, FromOcaf (+8 more)

### Community 8 - "Viewport.cpp"
Cohesion: 0.06
Nodes (6): keys(), qc(), QtFrameBuffer, rgb(), Viewport::Viewport(), Viewport::setInteractor()

### Community 9 - "SketchEditor"
Cohesion: 0.03
Nodes (41): SketchEditor, arcDrag_, arcDragMoved_, arcEndsChain_, arcFrom_, arcRef_, bodyEdges_, boxing_ (+33 more)

### Community 10 - "Dimension"
Cohesion: 0.50
Nodes (4): Dimension, Angle, Length, Unitless

### Community 11 - "optional"
Cohesion: 0.16
Nodes (5): QComboBox, QDialogButtonBox, QFormLayout, QLabel, optional

### Community 13 - "PlaneEdges"
Cohesion: 0.29
Nodes (4): PlaneEdges, arcs, segments, vertices

### Community 14 - "Kind"
Cohesion: 0.11
Nodes (19): EdgeFeature, def_, kind_, Kind, Angle, AxisCylinder, AxisEdge, AxisTwoPlanes (+11 more)

### Community 15 - "MainWindowTools.cpp"
Cohesion: 0.07
Nodes (11): MainWindow::chooseUnits(), MainWindow::measurePick(), MainWindow::openAnalysis(), MainWindow::openMeasure(), MainWindow::sectionFrame(), MainWindow::sectionPlane(), MainWindow::setSelectionFilter(), MainWindow::showCenterOfMass() (+3 more)

### Community 16 - "CommandDialog"
Cohesion: 0.05
Nodes (27): CommandDialog, bodiesId_, bodiesLabel_, bodyInput_, buttons_, cmd_, conditional_, edgesId_ (+19 more)

### Community 17 - "Io.cpp"
Cohesion: 0.11
Nodes (15): MainWindow::print3d(), NamedShape, compoundOf(), exportShapes(), fmt(), formatForPath(), fromBrep(), importShape() (+7 more)

### Community 18 - "Unit"
Cohesion: 0.07
Nodes (44): MainWindow::lengthUnit(), ExpressionEnv, lengthUnit, lookup, ExpressionError, Quantity, angle, length (+36 more)

### Community 19 - "SketchGeometry.cpp"
Cohesion: 0.12
Nodes (9): curve(), curves(), customPlaneSpec(), interiorPoint(), planeFrame(), profileAt(), profiles(), toSketch() (+1 more)

### Community 21 - "fromInternal"
Cohesion: 0.15
Nodes (13): MainWindow::checkInterference(), MainWindow::driveJoints(), MainWindow::exportDesign(), MainWindow::formatLength(), MainWindow::gridSettings(), MainWindow::insertFile(), MainWindow::openSection(), MainWindow::updateMeasure() (+5 more)

### Community 22 - "MainWindow.cpp"
Cohesion: 0.10
Nodes (4): commandIcon(), qs(), run, MainWindow::applySection()

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
Nodes (25): QCheckBox, QLabel, QToolButton, QWidget, SketchEditor, SketchPalette, body_, constraints_ (+17 more)

### Community 28 - "sketchFor"
Cohesion: 0.16
Nodes (9): Hole, def_, Pipe, def_, Revolve, def_, sectionOf(), sketchFor() (+1 more)

### Community 29 - "AdskModule.cpp"
Cohesion: 0.09
Nodes (16): Application, bindAdsk(), BRepBodies, BRepBody, index, Component, Design, Product (+8 more)

### Community 30 - "Colors"
Cohesion: 0.07
Nodes (28): Colors, base, border, cubeBox, cubeText, errorBackground, grid, gridMajor (+20 more)

### Community 31 - "TopoDS_Shape"
Cohesion: 0.24
Nodes (28): KernelError, asSolid(), boolean(), chamfer(), chamferEx(), draft(), extrude(), extrudeEx() (+20 more)

### Community 32 - "SketchOps.cpp"
Cohesion: 0.21
Nodes (19): at(), chainOf(), chamferCorner(), cornerAt(), cross(), dot(), extendLine(), filletCorner() (+11 more)

### Community 33 - "Command.cpp"
Cohesion: 0.22
Nodes (11): expressionKey(), checkInputValue(), CommandContext::evaluateExpression(), CommandDef::input(), CommandSession::applyInTransaction(), CommandSession::cancel(), CommandSession::execute(), CommandSession::preview() (+3 more)

### Community 34 - "ParameterCompleter"
Cohesion: 0.12
Nodes (9): MainWindow::attachArrowCompleters(), ParameterCompleter, completer_, edit_, names_, ParameterCompleter::ParameterCompleter(), public, QCompleter (+1 more)

### Community 35 - "string"
Cohesion: 0.10
Nodes (28): boundingBox(), completeEdgeReferences(), completeFaceReferences(), decode(), decodeFaces(), edgeReference(), EdgeSig, full (+20 more)

### Community 36 - ".openMarkingMenu"
Cohesion: 0.09
Nodes (4): MainWindow::beginSketch(), MainWindow::buildSketchTab(), MainWindow::enterSketchMode(), MainWindow::buildUiCommands()

### Community 37 - "Viewport.h"
Cohesion: 0.08
Nodes (6): MarkingMenu::keyPressEvent(), QKeyEvent, QLabel, QLineEdit, QMouseEvent, ViewInteractor

### Community 38 - "solve"
Cohesion: 0.18
Nodes (12): addConstraintChecked(), Layout, n, px, py, rad, makeLayout(), pack() (+4 more)

### Community 39 - "UiCommand"
Cohesion: 0.18
Nodes (9): UiCommand, enabled, icon, id, name, panel, shortcut, tab (+1 more)

### Community 40 - "src/main.cpp"
Cohesion: 0.09
Nodes (8): listCommands(), main(), usage(), grabWindowWithPanels(), main(), smoke(), writeLiveGeometry(), volume

### Community 41 - "ConstraintType"
Cohesion: 0.09
Nodes (23): ConstraintType, Angle, Coincident, Collinear, Concentric, Diameter, Distance, Equal (+15 more)

### Community 42 - "TEST"
Cohesion: 0.06
Nodes (9): Session, commands_, doc_, listeners_, nextListener_, path_, param(), TEST() (+1 more)

### Community 43 - "Pick"
Cohesion: 0.12
Nodes (15): Hit, index, kind, Pick, bodyArc, bodyPoint, bodySegment, hit (+7 more)

### Community 44 - "Snap"
Cohesion: 0.10
Nodes (18): Snap, alignX, alignY, bodyArc, bodySegment, entity, fromX, fromY (+10 more)

### Community 45 - "Kind"
Cohesion: 0.09
Nodes (21): HudField, edit, editing, kind, locked, value, Kind, Angle (+13 more)

### Community 46 - ".updatePreview"
Cohesion: 0.15
Nodes (7): ext(), fixedColor(), freeColor(), qc(), rgb(), wire(), Sketch::addLine()

### Community 47 - "AnalysisSettings"
Cohesion: 0.08
Nodes (21): AnalysisKind, CurvatureMap, Draft, None, Zebra, AnalysisSettings, curvatureScale, draftAngle (+13 more)

### Community 48 - "Document.cpp"
Cohesion: 0.08
Nodes (29): ConstructionPlane, name, spec, Document::axes(), Document::bodies(), Document::body(), Document::bodyName(), Document::components() (+21 more)

### Community 50 - "MainWindowSketch.cpp"
Cohesion: 0.06
Nodes (17): MainWindow::cancelSketch(), MainWindow::editSketch(), MainWindow::exitSketchMode(), MainWindow::finishSketch(), MainWindow::sketchPalette(), MainWindow::sketchVisible(), MainWindow::startSketch(), MainWindow::updateProfilePicking() (+9 more)

### Community 51 - "Session.cpp"
Cohesion: 0.19
Nodes (18): historyEdit(), Session::deleteFeature(), Session::deleteParameter(), Session::editFeature(), Session::newDocument(), Session::open(), Session::redo(), Session::renameBody() (+10 more)

### Community 52 - "InputDef"
Cohesion: 0.08
Nodes (24): InputDef, choices, defaultValue, id, label, max, min, minExclusive (+16 more)

### Community 54 - "MainWindowArrow.cpp"
Cohesion: 0.12
Nodes (7): ArrowPlacement, base, dir, edgePlacement(), facesPlacement(), MainWindow::patternCentre(), MainWindow::pickedFaces()

### Community 55 - "string"
Cohesion: 0.10
Nodes (12): AddUserParameter, def_, checkPattern(), CircularPattern, def_, isIdentifier(), Mirror, def_ (+4 more)

### Community 56 - "Theme.cpp"
Cohesion: 0.19
Nodes (6): setIconTheme(), darkColors(), darkPalette(), darkStyleSheet(), lightColors(), lightStyleSheet()

### Community 57 - "FeatureEffect"
Cohesion: 0.07
Nodes (22): Body, display, name, shape, Component, bodies, name, Feature (+14 more)

### Community 58 - "Constraint"
Cohesion: 0.11
Nodes (17): Constraint, entities, expression, points, type, value, value2, SolveResult (+9 more)

### Community 59 - "xdrive.py"
Cohesion: 0.32
Nodes (14): button(), canvas(), click(), drag(), flush(), geometry(), key(), keycode() (+6 more)

### Community 61 - "DocumentError"
Cohesion: 0.11
Nodes (18): DocumentError, Document::abortTransaction(), Document::addBody(), Document::addUserParameter(), Document::axisFrame(), Document::bodyShapes(), Document::commitTransaction(), Document::effectOf() (+10 more)

### Community 62 - "TestFramework.h"
Cohesion: 0.13
Nodes (9): Rect, p, Case, name, fail(), Failure, Register, env() (+1 more)

### Community 63 - "ViewportArrow.cpp"
Cohesion: 0.08
Nodes (17): Viewport::frontEdgeOwner(), rgb(), segmentDistance(), Viewport::arrowAt(), Viewport::arrowMouseMove(), Viewport::arrowMousePress(), Viewport::arrowMouseRelease(), Viewport::arrowParam() (+9 more)

### Community 64 - "ext"
Cohesion: 0.24
Nodes (10): SketchRecord, data, name, offset, plane, Document::setSketch(), Document::setTimeline(), Document::sketch() (+2 more)

### Community 65 - "CommandRegistry"
Cohesion: 0.14
Nodes (3): CommandRegistry, cmds_, TEST()

### Community 66 - "PythonHost.cpp"
Cohesion: 0.15
Nodes (10): Result, error, ok, output, captured(), PYBIND11_EMBEDDED_MODULE(), PythonHost::exec(), PythonHost::PythonHost() (+2 more)

### Community 67 - "Vec3"
Cohesion: 0.20
Nodes (18): SurfacePoint, normal, point, Vec3, edgeMidpoint(), edgesNear(), frame(), makeCone() (+10 more)

### Community 68 - "Theme"
Cohesion: 0.22
Nodes (4): Theme, colors_, public, styled_

### Community 69 - "FileFormat"
Cohesion: 0.17
Nodes (12): FileFormat, Brep, Iges, Obj, Step, Stl, ThreeMF, FormatInfo (+4 more)

### Community 71 - "ParametersDialog.cpp"
Cohesion: 0.08
Nodes (16): QDialog, number(), ParametersDialog, building_, error_, listener_, ParametersDialog::ParametersDialog(), public (+8 more)

### Community 72 - "MainWindow::MainWindow"
Cohesion: 0.09
Nodes (7): PythonHost, MainWindow::MainWindow(), MainWindow::onEdgeClicked(), MainWindow::onProfileClicked(), MainWindow::originalShape(), MainWindow::syncPickedShapes(), MainWindow::toOriginal()

### Community 73 - "TopologyCounts"
Cohesion: 0.17
Nodes (17): Section, Circular, Square, Triangular, TopologyCounts, edges, faces, shells (+9 more)

### Community 74 - "ExpressionSpinBox"
Cohesion: 0.17
Nodes (4): ExpressionSpinBox, eval_, expression_, shown_

### Community 75 - "InputType"
Cohesion: 0.08
Nodes (21): bindTsr(), fromPy(), toPy(), typeName(), InputType, Axis, Bodies, Body (+13 more)

### Community 76 - "ConstructAxisPoint"
Cohesion: 0.17
Nodes (5): ConstructAxisPoint, def_, kind_, JointPick, frame

### Community 78 - "ViewportAnalysis.cpp"
Cohesion: 0.13
Nodes (5): packed(), ramp(), shade(), Viewport::buildAnalysis(), Viewport::setCurvatureComb()

### Community 79 - "CommandSession"
Cohesion: 0.17
Nodes (6): CommandSession, inputs_, OwnedCommand, owned, OwningCommandSession, Session::begin()

### Community 80 - "SketchDisplay"
Cohesion: 0.13
Nodes (10): ProfileObject, index, sketch, SketchDisplay, construction, curves, frame, name (+2 more)

### Community 81 - "string"
Cohesion: 0.17
Nodes (14): bodyNumber(), Document::component(), Document::componentOfBody(), Document::nextAxisName(), Document::nextBodyName(), Document::nextComponentName(), Document::nextPlaneName(), Document::nextPointName() (+6 more)

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
Nodes (19): Architecture, How a command works, The document, Units, Build, Conventions, Development, Tests (+11 more)

### Community 87 - "cmath"
Cohesion: 0.29
Nodes (6): EntityType, Arc, Circle, Line, Spline, isRound()

### Community 88 - "CommandRegistry::run"
Cohesion: 0.22
Nodes (4): CommandRegistry::add(), CommandRegistry::all(), CommandRegistry::find(), CommandRegistry::run()

### Community 89 - "SketchEditor::SketchEditor"
Cohesion: 0.14
Nodes (7): QObject, SketchEditor::SketchEditor(), edges, Tool, op, shape, target

### Community 91 - "BoundingBox"
Cohesion: 0.29
Nodes (7): BoundingBox, max, min, dot(), faceScore(), score(), vec()

### Community 93 - "Known differences still to build"
Cohesion: 0.15
Nodes (12): Data and files, Findings from the videos, Fusion study list, Interface, Known differences still to build, Navigation and display, Selection and the canvas, Sketch (+4 more)

### Community 96 - ".planeFrame"
Cohesion: 0.21
Nodes (6): Loft, def_, profilesOf(), profiles, Sweep, def_

### Community 97 - "BodyFrame"
Cohesion: 0.15
Nodes (14): BodyFrame, diag, dx, dy, dz, x0, y0, z0 (+6 more)

### Community 98 - "FakeDoc"
Cohesion: 0.17
Nodes (6): FakeDoc, aborts, commits, items, open, snapshot

### Community 99 - "patternFeatures"
Cohesion: 0.15
Nodes (14): getInt(), CopyFn, differenceOrNull(), openChains(), parsePoints(), PathPattern, def_, patternFeatures() (+6 more)

### Community 100 - "Zip.cpp"
Cohesion: 0.20
Nodes (11): Entry, data, name, ZipError, crc32(), get16(), get32(), put16() (+3 more)

### Community 101 - "DocCommands.h"
Cohesion: 0.19
Nodes (3): slurp(), TEST(), tmp()

### Community 103 - "sstream"
Cohesion: 0.11
Nodes (8): doc_(), Document::Document(), Document::expressionEnv(), Document::ocafBytes(), Document::reevaluateParameters(), ocafApplication(), Document::load(), Document::save()

### Community 104 - "NavPreset"
Cohesion: 0.33
Nodes (4): NavPreset, Fusion, SolidWorks, Tinkercad

### Community 105 - "ConstructionAxis"
Cohesion: 0.29
Nodes (5): ConstructionAxis, axis, name, Document::axis(), Document::setAxis()

### Community 106 - "SectionState"
Cohesion: 0.25
Nodes (7): SectionState, active, angle, flip, offset, plane, visible

### Community 107 - "Display"
Cohesion: 0.25
Nodes (7): Display, constraints, construction, dimensions, points, profiles, projected

### Community 108 - "Profile"
Cohesion: 0.33
Nodes (5): Profile, area, face, x, y

### Community 110 - "Kernel.h"
Cohesion: 0.09
Nodes (22): Axis, X, Y, Z, BooleanOp, Cut, Intersect, Join (+14 more)

### Community 112 - "ConstructionPoint"
Cohesion: 0.29
Nodes (5): ConstructionPoint, name, point, Document::point(), Document::setPoint()

### Community 113 - "Mesh"
Cohesion: 0.40
Nodes (3): Mesh, nodes, triangles

### Community 114 - "uninstall.sh"
Cohesion: 0.52
Nodes (6): die(), manifest_for(), refresh(), uninstall.sh script, step(), usage()

### Community 115 - "install.sh"
Cohesion: 0.60
Nodes (5): die(), refresh(), install.sh script, step(), usage()

### Community 117 - "Column"
Cohesion: 0.33
Nodes (6): Column, kComment, kExpression, kParameter, kUnit, kValue

### Community 119 - "UserParameter"
Cohesion: 0.33
Nodes (6): UserParameter, comment, expression, name, unit, value

### Community 123 - "MarkingMenu"
Cohesion: 0.25
Nodes (3): MarkingMenu, enabled, public

### Community 132 - "ChainSegment"
Cohesion: 0.67
Nodes (3): ChainSegment, entity, forward

## Knowledge Gaps
- **635 isolated node(s):** `ok`, `output`, `error`, `isReal`, `real` (+630 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 1202 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **21 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `optional` connect `optional` to `Viewport`, `DocCommands.cpp`, `MainWindow`, `Kernel.cpp`, `Io.cpp`, `Unit`, `.press`, `ViewportSketch.cpp`, `SketchEditor.cpp`, `sketchFor`, `SketchOps.cpp`, `Viewport.h`, `TEST`, `AnalysisSettings`, `Document.cpp`, `QString`, `InputDef`, `MainWindowArrow.cpp`, `FeatureEffect`, `ViewportArrow.cpp`, `ext`, `Vec3`, `CommandDialog.cpp`, `ExpressionSpinBox`, `InputType`, `string`, `ConstructionAxis`, `Kernel.h`, `ConstructionPoint`?**
  _High betweenness centrality (0.129) - this node is a cross-community bridge._
- **What connects `ok`, `output`, `error` to the rest of the system?**
  _635 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Viewport` be split into smaller, more focused modules?**
  _Cohesion score 0.01847539201987269 - nodes in this community are weakly interconnected._
- **Why does `Viewport` connect `Viewport` to `Viewport.h`, `ParametersDialog.cpp`, `NavPreset`, `Viewport.cpp`, `optional`, `.initializeGL`, `ViewportAnalysis.cpp`, `AnalysisSettings`, `SketchDisplay`, `MainWindowTools.cpp`, `rect`, `.toPixels`, `.selectedSubShapes`, `ViewportArrow.cpp`?**
  _High betweenness centrality (0.127) - this node is a cross-community bridge._
- **Should `Icons.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.06538461538461539 - nodes in this community are weakly interconnected._
- **Why does `MainWindow` connect `MainWindow` to `ParameterCompleter`, `.openMarkingMenu`, `.buildNavBar`, `UiCommand`, `src/main.cpp`, `MainWindow::MainWindow`, `SectionState`, `optional`, `InputType`, `ParametersDialog.cpp`, `TEST`, `MainWindowTools.cpp`, `MainWindowSketch.cpp`, `fromInternal`, `MainWindow.cpp`, `SketchPalette`?**
  _High betweenness centrality (0.098) - this node is a cross-community bridge._
- **Should `DocCommands.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.044564890093345376 - nodes in this community are weakly interconnected._