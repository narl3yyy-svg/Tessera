# Graph Report - tessera  (2026-11-13)

## Corpus Check
- 374 files · ~234,501 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 55 file(s) not represented in the graph (top: .drive 47, (none) 5, .cmake 1)

## Summary
- 3509 nodes · 8849 edges · 149 communities (119 shown, 30 thin omitted)
- Extraction: 85% EXTRACTED · 15% INFERRED · 0% AMBIGUOUS · INFERRED: 1329 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `80b1a6c9`
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
- DocumentError
- Colors
- KernelError
- SketchOps.cpp
- Viewport.h
- ParameterCompleter
- Constraint
- SketchCurves.cpp
- MainWindow.cpp
- solve
- Kind
- QString
- ConstraintType
- AdskModule.cpp
- Pick
- SketchEditor.cpp
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
- Text
- Theme.cpp
- .applyPreSelection
- Entity
- xdrive.py
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
- QTimer
- cmath
- FakeDoc
- CommandDialog.cpp
- .rebuild
- sstream
- string
- BodyFrame
- Joints
- SectionState
- Display
- SketchEditor.h
- PlaneEdges
- openWallBand
- Column
- ViewportAnalysis.cpp
- Axis
- uninstall.sh
- install.sh
- TestFramework.h
- main
- BooleanOp
- ThreadInfo
- ConstructionAxis
- ChamferType
- Placement
- ChainSegment
- curve
- UserParameter
- Value.h
- Tool
- Known gaps
- TEST
- HoleSize
- TEST
- LAB_NOTES.md
- TsrModule.cpp
- .buildShortcuts
- build.sh
- live-test.sh
- Viewport::setDragArrow
- NamedView
- Point
- SplineHandle
- Icons.h
- Profile
- MarkingMenu
- HandleHit
- FormatInfo
- MainWindow::updateDragArrow

## God Nodes (most connected - your core abstractions)
1. `Viewport` - 251 edges
2. `SketchEditor` - 185 edges
3. `MainWindow` - 175 edges
4. `Inputs` - 138 edges
5. `render()` - 107 edges
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

## Communities (149 total, 30 thin omitted)

### Community 0 - "Viewport"
Cohesion: 0.02
Nodes (66): view_, Viewport, analysis_, analysisObjects_, appliedGridStep_, arrowBoxes_, arrowDragging_, arrowGrab_ (+58 more)

### Community 1 - "Icons.cpp"
Cohesion: 0.06
Nodes (112): arc3Icon(), arcIcon(), arcTangentIcon(), arrow(), axisIcon(), box(), breakIcon(), centerRectIcon() (+104 more)

### Community 2 - "Session.cpp"
Cohesion: 0.06
Nodes (46): CommandSession, inputs_, expressionKey(), checkInputValue(), CommandContext::evaluateExpression(), CommandDef::input(), CommandSession::applyInTransaction(), CommandSession::cancel() (+38 more)

### Community 4 - "MainWindow"
Cohesion: 0.03
Nodes (62): CommandDialog, MainWindow, active_, arrowInput_, arrowInput2_, bodiesBeforeCommand_, combEdges_, combPicking_ (+54 more)

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
Nodes (5): glide(), keys(), SelectionBox, crossing, Viewport::Viewport()

### Community 9 - "SketchEditor"
Cohesion: 0.03
Nodes (46): SketchEditor, arcDrag_, arcDragMoved_, arcEndsChain_, arcFrom_, arcRef_, bodyEdges_, boxing_ (+38 more)

### Community 10 - "ext"
Cohesion: 0.14
Nodes (14): SketchRecord, data, name, offset, plane, Document::openTransaction(), Document::recompute(), Document::recordFeature() (+6 more)

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
Cohesion: 0.09
Nodes (19): MainWindow::print3d(), NamedShape, compoundOf(), exportShapes(), fmt(), formatForPath(), fromBrep(), importShape() (+11 more)

### Community 18 - "Unit"
Cohesion: 0.07
Nodes (50): MainWindow::lengthUnit(), ExpressionEnv, lengthUnit, lookup, ExpressionError, Quantity, angle, length (+42 more)

### Community 19 - "MainWindowTools.cpp"
Cohesion: 0.09
Nodes (18): MainWindow::checkInterference(), MainWindow::chooseUnits(), MainWindow::driveJoints(), MainWindow::formatLength(), MainWindow::gridSettings(), MainWindow::insertFile(), MainWindow::openAnalysis(), MainWindow::openSection() (+10 more)

### Community 21 - "Document"
Cohesion: 0.11
Nodes (18): ConstructAxisPoint, def_, kind_, jointOrigin(), JointPick, frame, Loft, def_ (+10 more)

### Community 22 - "MainWindow::MainWindow"
Cohesion: 0.18
Nodes (4): MainWindow::MainWindow(), MainWindow::beginSketch(), MainWindow::exitSketchMode(), MainWindow::showPreferences()

### Community 23 - "TEST"
Cohesion: 0.06
Nodes (13): writeLiveGeometry(), Sketch, constraints, entities, points, texts, Sketch::addCircle(), Sketch::addLine() (+5 more)

### Community 24 - "Sketch.cpp"
Cohesion: 0.07
Nodes (21): SketchError, SplineKind, Conic, Control, Fit, entityTypeName(), isDimension(), Sketch::addConic() (+13 more)

### Community 25 - "ViewportSketch.cpp"
Cohesion: 0.10
Nodes (6): faceStyle(), lineStyle(), rgb(), Viewport::lookAt(), Viewport::planePoint(), Viewport::toWidget()

### Community 26 - "SketchPalette"
Cohesion: 0.06
Nodes (26): flatButton(), QCheckBox, QLabel, QToolButton, QWidget, SketchEditor, SketchPalette, body_ (+18 more)

### Community 27 - "Snap"
Cohesion: 0.11
Nodes (18): Snap, alignX, alignY, bodyArc, bodySegment, entity, fromX, fromY (+10 more)

### Community 28 - "CommandError"
Cohesion: 0.13
Nodes (21): CommandError, getBool(), getInt(), getReal(), applyOperation(), bodyCentre(), bodyName(), CopyFn (+13 more)

### Community 29 - "DocumentError"
Cohesion: 0.11
Nodes (21): DocumentError, checkViewName(), Document::abortTransaction(), Document::addNamedView(), Document::addUserParameter(), Document::axisFrame(), Document::commitTransaction(), Document::removeBody() (+13 more)

### Community 30 - "Colors"
Cohesion: 0.07
Nodes (28): Colors, base, border, cubeBox, cubeText, errorBackground, grid, gridMajor (+20 more)

### Community 31 - "KernelError"
Cohesion: 0.18
Nodes (33): KernelError, vertices, asSolid(), boolean(), boundingBox(), chamfer(), chamferEx(), draft() (+25 more)

### Community 32 - "SketchOps.cpp"
Cohesion: 0.22
Nodes (26): at(), chainOf(), chamferCorner(), circularPattern(), copyEntities(), cross(), dot(), extendLine() (+18 more)

### Community 33 - "Viewport.h"
Cohesion: 0.06
Nodes (19): AnalysisKind, CurvatureMap, Draft, None, Zebra, AnalysisSettings, curvatureScale, draftAngle (+11 more)

### Community 34 - "ParameterCompleter"
Cohesion: 0.13
Nodes (9): QObject, ParameterCompleter, completer_, edit_, names_, ParameterCompleter::ParameterCompleter(), public, QCompleter (+1 more)

### Community 35 - "Constraint"
Cohesion: 0.08
Nodes (20): Constraint, driven, entities, expression, hasLabel, labelX, labelY, name (+12 more)

### Community 36 - "SketchCurves.cpp"
Cohesion: 0.13
Nodes (15): crossings(), crossingsOf(), Curve2d, curve2d(), periodic, t0, t1, flattened() (+7 more)

### Community 37 - "MainWindow.cpp"
Cohesion: 0.13
Nodes (3): commandIcon(), qs(), MainWindow::applySection()

### Community 38 - "solve"
Cohesion: 0.18
Nodes (13): set, addConstraintChecked(), Layout, n, px, py, rad, makeLayout() (+5 more)

### Community 39 - "Kind"
Cohesion: 0.09
Nodes (21): HudField, edit, editing, kind, locked, value, Kind, Angle (+13 more)

### Community 40 - "QString"
Cohesion: 0.11
Nodes (5): ExpressionSpinBox, eval_, expression_, shown_, formatNumber()

### Community 41 - "ConstraintType"
Cohesion: 0.09
Nodes (23): ConstraintType, Angle, Coincident, Collinear, Concentric, Diameter, Distance, Equal (+15 more)

### Community 42 - "AdskModule.cpp"
Cohesion: 0.10
Nodes (16): Application, bindAdsk(), BRepBodies, BRepBody, index, Component, Design, Product (+8 more)

### Community 43 - "Pick"
Cohesion: 0.11
Nodes (17): Hit, index, kind, Pick, bodyArc, bodyPoint, bodySegment, hit (+9 more)

### Community 46 - "Zip.cpp"
Cohesion: 0.20
Nodes (11): Entry, data, name, ZipError, crc32(), get16(), get32(), put16() (+3 more)

### Community 47 - "AnalysisSettings"
Cohesion: 0.10
Nodes (16): DragArrow, base, dir, radius, ref, ring, value, PendingLook (+8 more)

### Community 48 - "ConstructionPoint"
Cohesion: 0.33
Nodes (4): ConstructionPoint, name, point, Document::point()

### Community 49 - "SketchRecord"
Cohesion: 0.17
Nodes (11): ModelParameter, angle, expression, input, label, name, owner, unit (+3 more)

### Community 50 - "MainWindowSketch.cpp"
Cohesion: 0.10
Nodes (12): MainWindow::cancelSketch(), MainWindow::editSketch(), MainWindow::finishSketch(), MainWindow::onProfileClicked(), MainWindow::originalShape(), MainWindow::sketchPalette(), MainWindow::sketchVisible(), MainWindow::startSketch() (+4 more)

### Community 51 - "InputDef"
Cohesion: 0.08
Nodes (24): InputDef, choices, defaultValue, id, label, max, min, minExclusive (+16 more)

### Community 52 - "ParametersDialog"
Cohesion: 0.20
Nodes (4): QLabel, QLineEdit, QTreeWidget, QTreeWidgetItem

### Community 54 - "MainWindowArrow.cpp"
Cohesion: 0.12
Nodes (8): ArrowPlacement, base, dir, edgePlacement(), facesPlacement(), MainWindow::attachArrowCompleters(), MainWindow::patternCentre(), MainWindow::pickedFaces()

### Community 55 - "Text"
Cohesion: 0.10
Nodes (16): ext(), fixedColor(), freeColor(), lineEntity(), qc(), rgb(), wire(), Text (+8 more)

### Community 56 - "Theme.cpp"
Cohesion: 0.19
Nodes (6): setIconTheme(), darkColors(), darkPalette(), darkStyleSheet(), lightColors(), lightStyleSheet()

### Community 58 - "Entity"
Cohesion: 0.12
Nodes (12): Entity, a, b, center, construction, fit, handles, included (+4 more)

### Community 59 - "xdrive.py"
Cohesion: 0.32
Nodes (14): button(), canvas(), click(), drag(), flush(), geometry(), key(), keycode() (+6 more)

### Community 62 - "Session"
Cohesion: 0.08
Nodes (6): Session, commands_, doc_, listeners_, nextListener_, path_

### Community 63 - "ViewportArrow.cpp"
Cohesion: 0.11
Nodes (8): rgb(), segmentDistance(), Viewport::arrowAt(), Viewport::arrowParam(), Viewport::DragArrow::handle(), Viewport::dragArrowHandle(), Viewport::placeArrowBoxes(), height

### Community 64 - "BodyFrame"
Cohesion: 0.10
Nodes (32): completeEdgeReferences(), completeFaceReferences(), decode(), decodeFaces(), dot(), edgeReference(), EdgeSig, full (+24 more)

### Community 65 - "CommandRegistry"
Cohesion: 0.12
Nodes (4): CommandRegistry, cmds_, CommandRegistry::add(), TEST()

### Community 66 - "cmath"
Cohesion: 0.14
Nodes (10): PythonHost, Result, error, ok, output, captured(), PYBIND11_EMBEDDED_MODULE(), PythonHost::exec() (+2 more)

### Community 67 - "requirePositive"
Cohesion: 0.25
Nodes (9): BoundingBox, max, min, WallSide, Center, Side1, Side2, offsetOpenWire() (+1 more)

### Community 68 - "Theme"
Cohesion: 0.22
Nodes (4): Theme, colors_, public, styled_

### Community 71 - "ParametersDialog.cpp"
Cohesion: 0.10
Nodes (12): number(), ParametersDialog, building_, error_, filter_, listener_, ParametersDialog::ParametersDialog(), public (+4 more)

### Community 72 - "smoke"
Cohesion: 0.40
Nodes (5): smoke(), MassProperties, area, centerOfMass, volume

### Community 73 - "FileFormat"
Cohesion: 0.29
Nodes (7): FileFormat, Brep, Iges, Obj, Step, Stl, ThreeMF

### Community 75 - "InputType"
Cohesion: 0.12
Nodes (17): InputType, Axis, Bodies, Body, Bool, Choice, Edges, Faces (+9 more)

### Community 76 - "Vec3"
Cohesion: 0.22
Nodes (17): SurfacePoint, normal, point, Vec3, edgesNear(), frame(), makeBox(), makeCone() (+9 more)

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
Cohesion: 0.11
Nodes (6): NavPreset, Fusion, SolidWorks, Tinkercad, Viewport::clearDragArrow(), Viewport::clearSecondArrow()

### Community 84 - "AddUserParameter"
Cohesion: 0.22
Nodes (4): AddUserParameter, def_, Push, d

### Community 85 - "Level"
Cohesion: 0.16
Nodes (13): debug(), error(), info(), Level, Debug, Error, Info, Warning (+5 more)

### Community 86 - "README.md"
Cohesion: 0.11
Nodes (15): Build, Conventions, Development, Tests, Reference parts, Fusion feature checklist, Roadmap, Contents (+7 more)

### Community 87 - "Document.cpp"
Cohesion: 0.08
Nodes (29): ConstructionPlane, name, spec, Document::axes(), Document::bodies(), Document::body(), Document::bodyName(), Document::component() (+21 more)

### Community 89 - ".bodyFaces"
Cohesion: 0.17
Nodes (6): Coil, def_, Extrude, def_, Joint, def_

### Community 91 - "MarkingMenu.cpp"
Cohesion: 0.18
Nodes (9): UiCommand, enabled, icon, id, name, panel, shortcut, tab (+1 more)

### Community 92 - "QDialog"
Cohesion: 0.18
Nodes (5): QDialog, MainWindow::exportDesign(), MainWindow::measurePick(), MainWindow::openMeasure(), toolWindow()

### Community 93 - "Known differences still to build"
Cohesion: 0.15
Nodes (12): Data and files, Findings from the videos, Fusion study list, Interface, Known differences still to build, Navigation and display, Selection and the canvas, Sketch (+4 more)

### Community 95 - "Feature"
Cohesion: 0.07
Nodes (24): Body, display, name, shape, Component, bodies, name, Feature (+16 more)

### Community 96 - "QTimer"
Cohesion: 0.09
Nodes (9): QTimer, Viewport::frontEdgeOwner(), Viewport::arrowMouseMove(), Viewport::arrowMousePress(), Viewport::arrowMouseRelease(), Viewport::dragArrowForTest(), Viewport::rebuildArrow(), Viewport::rebuildArrows() (+1 more)

### Community 97 - "cmath"
Cohesion: 0.08
Nodes (15): MarkingMenu::keyPressEvent(), MarkingMenu::MarkingMenu(), MarkingMenu::mouseMoveEvent(), MarkingMenu::paintEvent(), MarkingMenu::popupAt(), MarkingMenu::ringIndexAt(), MarkingMenu::run(), MarkingMenu::triggerForTest() (+7 more)

### Community 98 - "FakeDoc"
Cohesion: 0.17
Nodes (6): FakeDoc, aborts, commits, items, open, snapshot

### Community 101 - ".rebuild"
Cohesion: 0.13
Nodes (5): hiddenColour(), qc(), rgb(), sharpEdges(), wireColour()

### Community 102 - "sstream"
Cohesion: 0.15
Nodes (5): doc_(), Document::Document(), Document::ocafBytes(), ocafApplication(), Document::load()

### Community 103 - "string"
Cohesion: 0.10
Nodes (25): bodyNumber(), Document::addBody(), Document::bodyShapes(), Document::effectOf(), Document::evaluate(), Document::expressionEnv(), Document::nameFeatureParameters(), Document::nextAxisName() (+17 more)

### Community 104 - "BodyFrame"
Cohesion: 0.14
Nodes (13): BodyFrame, diag, dx, dy, dz, x0, y0, z0 (+5 more)

### Community 105 - "Joints"
Cohesion: 0.36
Nodes (3): cornerAt(), Joints, parent_

### Community 106 - "SectionState"
Cohesion: 0.25
Nodes (7): SectionState, active, angle, flip, offset, plane, visible

### Community 107 - "Display"
Cohesion: 0.25
Nodes (7): Display, constraints, construction, dimensions, points, profiles, projected

### Community 108 - "SketchEditor.h"
Cohesion: 0.14
Nodes (7): EntityType, Arc, Circle, Ellipse, Line, Spline, isRound()

### Community 109 - "PlaneEdges"
Cohesion: 0.22
Nodes (5): PlaneEdges, arcs, curves, segments, vertices

### Community 110 - "openWallBand"
Cohesion: 0.18
Nodes (16): Section, Circular, Square, Triangular, TopologyCounts, edges, faces, shells (+8 more)

### Community 111 - "Column"
Cohesion: 0.25
Nodes (8): Column, kComment, kExpression, kName, kParameter, kStar, kUnit, kValue

### Community 112 - "ViewportAnalysis.cpp"
Cohesion: 0.13
Nodes (5): packed(), ramp(), shade(), Viewport::buildAnalysis(), Viewport::setCurvatureComb()

### Community 113 - "Axis"
Cohesion: 0.50
Nodes (4): Axis, X, Y, Z

### Community 114 - "uninstall.sh"
Cohesion: 0.52
Nodes (6): die(), manifest_for(), refresh(), uninstall.sh script, step(), usage()

### Community 115 - "install.sh"
Cohesion: 0.60
Nodes (5): die(), refresh(), install.sh script, step(), usage()

### Community 116 - "TestFramework.h"
Cohesion: 0.13
Nodes (7): CommandRegistry::all(), Case, fn, name, fail(), Failure, Register

### Community 117 - "main"
Cohesion: 0.21
Nodes (4): listCommands(), main(), usage(), main()

### Community 118 - "BooleanOp"
Cohesion: 0.50
Nodes (4): BooleanOp, Cut, Intersect, Join

### Community 119 - "ThreadInfo"
Cohesion: 0.50
Nodes (4): ThreadInfo, diameter, internal, pitch

### Community 121 - "ConstructionAxis"
Cohesion: 0.29
Nodes (5): ConstructionAxis, axis, name, Document::axis(), Document::setAxis()

### Community 122 - "ChamferType"
Cohesion: 0.67
Nodes (3): ChamferType, DistanceAngle, TwoDistances

### Community 123 - "Placement"
Cohesion: 0.25
Nodes (7): Placement, angle, cx, cy, dx, dy, scale

### Community 124 - "ChainSegment"
Cohesion: 0.67
Nodes (3): ChainSegment, entity, forward

### Community 125 - "curve"
Cohesion: 0.31
Nodes (10): curve(), curves(), entityCurves(), interiorPoint(), profileAt(), profiles(), splineHandles(), textShape() (+2 more)

### Community 126 - "UserParameter"
Cohesion: 0.33
Nodes (6): UserParameter, comment, expression, name, unit, value

### Community 128 - "Tool"
Cohesion: 0.16
Nodes (6): SketchEditor::SketchEditor(), edges, Tool, op, shape, target

### Community 129 - "Known gaps"
Cohesion: 0.33
Nodes (5): Include 3D Geometry, Known gaps, Sketch text, Splines and conics, Visual styles

### Community 131 - "HoleSize"
Cohesion: 0.50
Nodes (4): HoleSize, modeled, pitch, radius

### Community 132 - "TEST"
Cohesion: 0.20
Nodes (3): slurp(), TEST(), tmp()

### Community 134 - "TsrModule.cpp"
Cohesion: 0.25
Nodes (4): bindTsr(), fromPy(), toPy(), typeName()

### Community 135 - ".buildShortcuts"
Cohesion: 0.20
Nodes (3): run, MainWindow::enterSketchMode(), MarkingMenu::mouseReleaseEvent()

### Community 139 - "Viewport::setDragArrow"
Cohesion: 0.22
Nodes (3): Viewport::emitArrow(), Viewport::setDragArrow(), Viewport::setDragRing()

### Community 140 - "NamedView"
Cohesion: 0.29
Nodes (7): NamedView, eye, name, size, target, up, Document::namedViews()

### Community 141 - "Point"
Cohesion: 0.38
Nodes (6): Point, x, y, z, customPlaneSpec(), planeFrame()

### Community 142 - "SplineHandle"
Cohesion: 0.29
Nodes (7): SplineHandle, arm, index, tx, ty, x, y

### Community 144 - "Profile"
Cohesion: 0.33
Nodes (5): Profile, area, face, x, y

### Community 145 - "MarkingMenu"
Cohesion: 0.40
Nodes (3): MarkingMenu, enabled, public

### Community 146 - "HandleHit"
Cohesion: 0.40
Nodes (4): HandleHit, back, index, spline

### Community 147 - "FormatInfo"
Cohesion: 0.40
Nodes (5): FormatInfo, canImport, extensions, format, name

## Knowledge Gaps
- **724 isolated node(s):** `ok`, `output`, `error`, `isReal`, `real` (+719 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 1376 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **30 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `Viewport` connect `Viewport` to `QTimer`, `Viewport.h`, `SketchCurves.cpp`, `.rebuild`, `Viewport.cpp`, `optional`, `Viewport::setDragArrow`, `AnalysisSettings`, `SketchDisplay`, `ViewportAnalysis.cpp`, `.redrawAll`, `Handle`, `.toPixels`, `MainWindowTools.cpp`, `ViewportArrow.cpp`?**
  _High betweenness centrality (0.113) - this node is a cross-community bridge._
- **What connects `ok`, `output`, `error` to the rest of the system?**
  _724 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Viewport` be split into smaller, more focused modules?**
  _Cohesion score 0.01664516129032258 - nodes in this community are weakly interconnected._
- **Why does `optional` connect `optional` to `Viewport`, `MainWindow`, `Inputs`, `Kernel.cpp`, `Io.cpp`, `Unit`, `ViewportSketch.cpp`, `Viewport.h`, `Constraint`, `SketchCurves.cpp`, `QString`, `SketchEditor.cpp`, `AnalysisSettings`, `ConstructionPoint`, `SketchRecord`, `InputDef`, `MainWindowArrow.cpp`, `Session`, `ViewportArrow.cpp`, `SketchEditor.cpp`, `Vec3`, `DocCommands.cpp`, `Document.cpp`, `Feature`, `CommandDialog.cpp`, `string`, `Joints`, `SketchEditor.h`, `ConstructionAxis`?**
  _High betweenness centrality (0.109) - this node is a cross-community bridge._
- **Should `Icons.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.05887752425911356 - nodes in this community are weakly interconnected._
- **Why does `SketchEditor` connect `SketchEditor` to `Tool`, `Viewport`, `ParameterCompleter`, `Constraint`, `Viewport.h`, `Kind`, `SketchEditor.cpp`, `Display`, `SketchEditor.h`, `PlaneEdges`, `Pick`, `SketchEditor.cpp`, `HandleHit`, `Unit`, `Text`, `Entity`, `Snap`, `Session`?**
  _High betweenness centrality (0.099) - this node is a cross-community bridge._
- **Should `Session.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.05921325051759834 - nodes in this community are weakly interconnected._