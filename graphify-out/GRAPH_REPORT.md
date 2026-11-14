# Graph Report - tessera  (2026-11-13)

## Corpus Check
- 377 files · ~235,491 words
- Verdict: corpus is large enough that graph structure adds value.
- Unclassified: 55 file(s) not represented in the graph (top: .drive 47, (none) 5, .cmake 1)

## Summary
- 3520 nodes · 8882 edges · 132 communities (110 shown, 22 thin omitted)
- Extraction: 85% EXTRACTED · 15% INFERRED · 0% AMBIGUOUS · INFERRED: 1336 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Graph Freshness
- Built from commit: `c9816c8f`
- Run `git rev-parse HEAD` and compare to check if the graph is stale.
- Run `graphify update .` after code changes (no API cost).

## Community Hubs (Navigation)
- Viewport
- Icons.cpp
- Session.cpp
- tsr
- MainWindow
- run_oracle.py
- CommandContext
- Document
- Viewport.cpp
- SketchEditor
- Document::recompute
- optional
- Kernel.cpp
- .features
- Kind
- TEST
- CommandDialog
- Io.cpp
- Unit
- MainWindowTools.cpp
- Handle
- Document
- SketchCurves.cpp
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
- rect
- Zip.cpp
- AnalysisSettings
- ConstructionPoint
- SketchRecord
- MainWindowSketch.cpp
- InputDef
- sketchFor
- .toPixels
- MainWindowArrow.cpp
- .userParameters
- Theme.cpp
- Development
- Entity
- xdrive.py
- Session
- ViewportArrow.cpp
- BodyFrame
- CommandRegistry
- cmath
- requirePositive
- Theme
- PYBIND11_EMBEDDED_MODULE
- ParametersDialog.cpp
- smoke
- test_text_box_path.py
- SketchEditor.cpp
- InputType
- Vec3
- CommandDialog::CommandDialog
- Architecture
- SketchDisplay
- DocCommands.cpp
- Measurement
- .redrawAll
- Level
- README.md
- Document.cpp
- test_feature_pattern.py
- Joint
- .add
- Known differences still to build
- Feature
- cmath
- FakeDoc
- CommandDialog.cpp
- .rebuild
- sstream
- Document::nameFeatureParameters
- BodyFrame
- Joints
- SectionState
- Display
- EntityType
- PlaneEdges
- openWallBand
- ViewportAnalysis.cpp
- Axis
- uninstall.sh
- install.sh
- TestFramework.h
- main
- BooleanOp
- ThreadInfo
- ConstructionAxis
- Placement
- ChainSegment
- curve
- UserParameter
- Value.h
- Tool
- Known gaps
- DocCommands.cpp
- TEST
- LAB_NOTES.md
- build.sh
- live-test.sh
- Point
- SplineHandle
- cachedProfiles

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

## Communities (132 total, 22 thin omitted)

### Community 0 - "Viewport"
Cohesion: 0.02
Nodes (67): view_, QLineEdit, Viewport, analysis_, analysisObjects_, appliedGridStep_, arrowBoxes_, arrowDragging_ (+59 more)

### Community 1 - "Icons.cpp"
Cohesion: 0.06
Nodes (112): arc3Icon(), arcIcon(), arcTangentIcon(), arrow(), axisIcon(), box(), breakIcon(), centerRectIcon() (+104 more)

### Community 2 - "Session.cpp"
Cohesion: 0.06
Nodes (43): CommandSession, inputs_, expressionKey(), checkInputValue(), CommandContext::evaluateExpression(), CommandDef::input(), CommandSession::applyInTransaction(), CommandSession::cancel() (+35 more)

### Community 4 - "MainWindow"
Cohesion: 0.03
Nodes (63): CommandDialog, MainWindow, active_, arrowInput_, arrowInput2_, bodiesBeforeCommand_, combEdges_, combPicking_ (+55 more)

### Community 5 - "run_oracle.py"
Cohesion: 0.08
Nodes (54): add_point(), arc_poly(), body_at(), body_list(), build_sketch(), chain(), circumcentre(), cm() (+46 more)

### Community 6 - "CommandContext"
Cohesion: 0.09
Nodes (11): CommandContext, AddUserParameter, def_, checkBody(), checkPattern(), isIdentifier(), Loft, def_ (+3 more)

### Community 7 - "Document"
Cohesion: 0.03
Nodes (11): Document, effects_, modified_, pendingTools_, registry_, replaying_, txnBodies_, FromOcaf (+3 more)

### Community 8 - "Viewport.cpp"
Cohesion: 0.06
Nodes (6): glide(), keys(), qc(), QKeyEvent, rgb(), Viewport::Viewport()

### Community 9 - "SketchEditor"
Cohesion: 0.03
Nodes (50): HandleHit, back, index, spline, SketchEditor, arcDrag_, arcDragMoved_, arcEndsChain_ (+42 more)

### Community 10 - "Document::recompute"
Cohesion: 0.20
Nodes (7): Document::recompute(), Document::recordFeature(), Document::removeFeature(), Document::setFeatureInputs(), Document::setFeatureSuppressed(), featureData(), toJson()

### Community 11 - "optional"
Cohesion: 0.12
Nodes (5): optional, CommandRegistry::all(), ChamferType, DistanceAngle, TwoDistances

### Community 12 - "Kernel.cpp"
Cohesion: 0.05
Nodes (6): dot(), faceScore(), isoCoarsePitch(), score(), topologyCounts(), vec()

### Community 13 - ".features"
Cohesion: 0.12
Nodes (16): Feature, commandId, error, id, inputs, name, parameterNames, rolledBack (+8 more)

### Community 14 - "Kind"
Cohesion: 0.07
Nodes (25): ConstructPlane, def_, kind_, EdgeFeature, def_, kind_, FaceFeature, def_ (+17 more)

### Community 15 - "TEST"
Cohesion: 0.09
Nodes (3): param(), TEST(), tmp()

### Community 16 - "CommandDialog"
Cohesion: 0.05
Nodes (31): CommandDialog, bodiesId_, bodiesLabel_, bodyInput_, buttons_, cmd_, conditional_, edgesId_ (+23 more)

### Community 17 - "Io.cpp"
Cohesion: 0.07
Nodes (31): MainWindow::print3d(), FileFormat, Brep, Iges, Obj, Step, Stl, ThreeMF (+23 more)

### Community 18 - "Unit"
Cohesion: 0.07
Nodes (50): MainWindow::lengthUnit(), ExpressionEnv, lengthUnit, lookup, ExpressionError, Quantity, angle, length (+42 more)

### Community 19 - "MainWindowTools.cpp"
Cohesion: 0.05
Nodes (26): QDialog, MainWindow::applySection(), MainWindow::checkInterference(), MainWindow::chooseUnits(), MainWindow::driveJoints(), MainWindow::exportDesign(), MainWindow::formatLength(), MainWindow::gridSettings() (+18 more)

### Community 21 - "Document"
Cohesion: 0.17
Nodes (13): ConstructAxisPoint, def_, kind_, jointOrigin(), JointPick, frame, parsePoints(), pickedFaces() (+5 more)

### Community 23 - "TEST"
Cohesion: 0.07
Nodes (8): Sketch, constraints, entities, points, texts, Sketch::addCircle(), Sketch::addConic(), TEST()

### Community 24 - "Sketch.cpp"
Cohesion: 0.07
Nodes (20): SketchError, SplineKind, Conic, Control, Fit, set, entityTypeName(), Sketch::addConstraint() (+12 more)

### Community 25 - "ViewportSketch.cpp"
Cohesion: 0.08
Nodes (6): faceStyle(), lineStyle(), rgb(), Viewport::lookAt(), Viewport::planePoint(), Viewport::toWidget()

### Community 26 - "SketchPalette"
Cohesion: 0.04
Nodes (30): QAbstractButton, QAction, grabWindowWithPanels(), writeLiveGeometry(), flatButton(), QCheckBox, QLabel, QToolButton (+22 more)

### Community 27 - "Snap"
Cohesion: 0.07
Nodes (25): ext(), fixedColor(), freeColor(), qc(), rgb(), Snap, alignX, alignY (+17 more)

### Community 28 - "CommandError"
Cohesion: 0.12
Nodes (24): CommandError, Inputs, getBool(), getInt(), getReal(), applyOperation(), bodyCentre(), bodyName() (+16 more)

### Community 29 - "string"
Cohesion: 0.14
Nodes (28): DocumentError, bodyNumber(), checkViewName(), Document::addBody(), Document::addNamedView(), Document::addUserParameter(), Document::axisFrame(), Document::nextBodyName() (+20 more)

### Community 30 - "Colors"
Cohesion: 0.07
Nodes (28): Colors, base, border, cubeBox, cubeText, errorBackground, grid, gridMajor (+20 more)

### Community 31 - "KernelError"
Cohesion: 0.23
Nodes (28): KernelError, asSolid(), boolean(), chamfer(), chamferEx(), draft(), extrude(), extrudeEx() (+20 more)

### Community 32 - "SketchOps.cpp"
Cohesion: 0.22
Nodes (26): at(), chainOf(), chamferCorner(), circularPattern(), copyEntities(), cross(), dot(), extendLine() (+18 more)

### Community 33 - "Viewport.h"
Cohesion: 0.08
Nodes (14): AnalysisKind, CurvatureMap, Draft, None, Zebra, AnalysisSettings, curvatureScale, draftAngle (+6 more)

### Community 34 - "ParameterCompleter"
Cohesion: 0.12
Nodes (8): ParameterCompleter, completer_, edit_, names_, ParameterCompleter::ParameterCompleter(), public, QCompleter, QLineEdit

### Community 35 - "Constraint"
Cohesion: 0.09
Nodes (20): Constraint, driven, entities, expression, hasLabel, labelX, labelY, name (+12 more)

### Community 36 - "SketchCurves.cpp"
Cohesion: 0.19
Nodes (14): crossings(), crossingsOf(), Curve2d, curve2d(), periodic, t0, t1, flattened() (+6 more)

### Community 37 - "MainWindow.cpp"
Cohesion: 0.06
Nodes (10): commandIcon(), MainWindow::MainWindow(), qs(), MainWindow::beginSketch(), MainWindow::buildSketchTab(), MainWindow::enterSketchMode(), MainWindow::exitSketchMode(), MainWindow::showPreferences() (+2 more)

### Community 38 - "solve"
Cohesion: 0.19
Nodes (12): addConstraintChecked(), Layout, n, px, py, rad, makeLayout(), pack() (+4 more)

### Community 39 - "Kind"
Cohesion: 0.09
Nodes (21): HudField, edit, editing, kind, locked, value, Kind, Angle (+13 more)

### Community 40 - "QString"
Cohesion: 0.12
Nodes (5): ExpressionSpinBox, eval_, expression_, shown_, formatNumber()

### Community 41 - "ConstraintType"
Cohesion: 0.08
Nodes (25): ConstraintType, Angle, Coincident, Collinear, Concentric, Diameter, Distance, Equal (+17 more)

### Community 42 - "AdskModule.cpp"
Cohesion: 0.07
Nodes (21): Application, bindAdsk(), BRepBodies, BRepBody, index, Component, Design, Product (+13 more)

### Community 43 - "Pick"
Cohesion: 0.11
Nodes (17): Hit, index, kind, Pick, bodyArc, bodyPoint, bodySegment, hit (+9 more)

### Community 45 - "rect"
Cohesion: 0.18
Nodes (7): SelectionBox, crossing, Session::notifyChanged(), Rect, rect(), l, p

### Community 46 - "Zip.cpp"
Cohesion: 0.20
Nodes (11): Entry, data, name, ZipError, crc32(), get16(), get32(), put16() (+3 more)

### Community 47 - "AnalysisSettings"
Cohesion: 0.10
Nodes (16): DragArrow, base, dir, radius, ref, ring, value, PendingLook (+8 more)

### Community 48 - "ConstructionPoint"
Cohesion: 0.29
Nodes (5): ConstructionPoint, name, point, Document::point(), Document::setPoint()

### Community 49 - "SketchRecord"
Cohesion: 0.11
Nodes (17): ModelParameter, angle, expression, input, label, name, owner, unit (+9 more)

### Community 50 - "MainWindowSketch.cpp"
Cohesion: 0.06
Nodes (17): MainWindow::cancelSketch(), MainWindow::editSketch(), MainWindow::finishSketch(), MainWindow::onEdgeClicked(), MainWindow::onProfileClicked(), MainWindow::originalShape(), MainWindow::sketchPalette(), MainWindow::sketchVisible() (+9 more)

### Community 51 - "InputDef"
Cohesion: 0.08
Nodes (24): InputDef, choices, defaultValue, id, label, max, min, minExclusive (+16 more)

### Community 52 - "sketchFor"
Cohesion: 0.21
Nodes (7): Hole, def_, Pipe, def_, Revolve, def_, sketchFor()

### Community 54 - "MainWindowArrow.cpp"
Cohesion: 0.11
Nodes (9): ArrowPlacement, base, dir, edgePlacement(), facesPlacement(), MainWindow::attachArrowCompleters(), MainWindow::patternCentre(), MainWindow::pickedFaces() (+1 more)

### Community 55 - ".userParameters"
Cohesion: 0.24
Nodes (5): Document::expressionEnv(), Document::nextDimensionName(), Document::parameterUsers(), Document::reevaluateParameters(), Document::save()

### Community 56 - "Theme.cpp"
Cohesion: 0.19
Nodes (6): setIconTheme(), darkColors(), darkPalette(), darkStyleSheet(), lightColors(), lightStyleSheet()

### Community 57 - "Development"
Cohesion: 0.40
Nodes (4): Build, Conventions, Development, Tests

### Community 58 - "Entity"
Cohesion: 0.07
Nodes (22): QObject, Entity, a, b, center, construction, fit, handles (+14 more)

### Community 59 - "xdrive.py"
Cohesion: 0.28
Nodes (15): button(), canvas(), click(), drag(), flush(), geometry(), key(), keycode() (+7 more)

### Community 62 - "Session"
Cohesion: 0.08
Nodes (7): PythonHost::PythonHost(), Session, commands_, doc_, listeners_, nextListener_, path_

### Community 63 - "ViewportArrow.cpp"
Cohesion: 0.06
Nodes (20): MarkingMenu::mouseMoveEvent(), QMouseEvent, ViewInteractor, Viewport::frontEdgeOwner(), rgb(), segmentDistance(), Viewport::arrowAt(), Viewport::arrowMouseMove() (+12 more)

### Community 64 - "BodyFrame"
Cohesion: 0.12
Nodes (28): completeEdgeReferences(), completeFaceReferences(), decode(), decodeFaces(), edgeReference(), EdgeSig, full, normals (+20 more)

### Community 65 - "CommandRegistry"
Cohesion: 0.12
Nodes (4): CommandRegistry, cmds_, CommandRegistry::add(), TEST()

### Community 66 - "cmath"
Cohesion: 0.16
Nodes (8): PythonHost, Result, error, ok, output, captured(), PythonHost::exec(), PythonHost::runScript()

### Community 67 - "requirePositive"
Cohesion: 0.25
Nodes (9): BoundingBox, max, min, WallSide, Center, Side1, Side2, offsetOpenWire() (+1 more)

### Community 68 - "Theme"
Cohesion: 0.22
Nodes (4): Theme, colors_, public, styled_

### Community 71 - "ParametersDialog.cpp"
Cohesion: 0.06
Nodes (24): Column, kComment, kExpression, kName, kParameter, kStar, kUnit, kValue (+16 more)

### Community 72 - "smoke"
Cohesion: 0.40
Nodes (5): smoke(), MassProperties, area, centerOfMass, volume

### Community 74 - "SketchEditor.cpp"
Cohesion: 0.13
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
Cohesion: 0.03
Nodes (51): Adding a tool, Command, CommandDef, feature, icon, id, inputs, name (+43 more)

### Community 82 - "Measurement"
Cohesion: 0.13
Nodes (14): Kind, Angle, Area, Length, Volume, Measurement, from, hasLine (+6 more)

### Community 83 - ".redrawAll"
Cohesion: 0.14
Nodes (8): NavPreset, Fusion, SolidWorks, Tinkercad, Viewport::setCurvatureComb(), Viewport::clearDragArrow(), Viewport::clearSecondArrow(), Viewport::setInteractor()

### Community 85 - "Level"
Cohesion: 0.16
Nodes (13): debug(), error(), info(), Level, Debug, Error, Info, Warning (+5 more)

### Community 86 - "README.md"
Cohesion: 0.14
Nodes (11): Reference parts, Fusion feature checklist, Roadmap, Contents, Development, Features, Install, License (+3 more)

### Community 87 - "Document.cpp"
Cohesion: 0.07
Nodes (36): ConstructionPlane, name, spec, Document::abortTransaction(), Document::axes(), Document::bodies(), Document::body(), Document::bodyName() (+28 more)

### Community 89 - "Joint"
Cohesion: 0.25
Nodes (4): Joint, def_, Sweep, def_

### Community 93 - "Known differences still to build"
Cohesion: 0.15
Nodes (12): Data and files, Findings from the videos, Fusion study list, Interface, Known differences still to build, Navigation and display, Selection and the canvas, Sketch (+4 more)

### Community 95 - "Feature"
Cohesion: 0.09
Nodes (18): Body, display, name, shape, Component, bodies, name, FeatureEffect (+10 more)

### Community 97 - "cmath"
Cohesion: 0.07
Nodes (22): UiCommand, enabled, icon, id, name, panel, run, shortcut (+14 more)

### Community 98 - "FakeDoc"
Cohesion: 0.17
Nodes (6): FakeDoc, aborts, commits, items, open, snapshot

### Community 101 - ".rebuild"
Cohesion: 0.10
Nodes (3): hiddenColour(), sharpEdges(), wireColour()

### Community 102 - "sstream"
Cohesion: 0.18
Nodes (4): doc_(), Document::Document(), ocafApplication(), Document::load()

### Community 103 - "Document::nameFeatureParameters"
Cohesion: 0.25
Nodes (5): Document::bodyShapes(), Document::effectOf(), Document::evaluate(), Document::nameFeatureParameters(), joinNames()

### Community 104 - "BodyFrame"
Cohesion: 0.14
Nodes (12): BodyFrame, diag, dx, dy, dz, x0, y0, z0 (+4 more)

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
Cohesion: 0.15
Nodes (5): PlaneEdges, arcs, curves, segments, vertices

### Community 110 - "openWallBand"
Cohesion: 0.14
Nodes (17): Section, Circular, Square, Triangular, TopologyCounts, edges, faces, shells (+9 more)

### Community 112 - "ViewportAnalysis.cpp"
Cohesion: 0.13
Nodes (4): packed(), ramp(), shade(), Viewport::buildAnalysis()

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
Cohesion: 0.09
Nodes (9): MarkingMenu, enabled, public, Case, fn, name, fail(), Failure (+1 more)

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

### Community 131 - "DocCommands.cpp"
Cohesion: 0.10
Nodes (19): axisOf(), Combine, def_, evaluateDimensions(), HoleSize, modeled, pitch, radius (+11 more)

### Community 132 - "TEST"
Cohesion: 0.20
Nodes (3): slurp(), TEST(), tmp()

### Community 141 - "Point"
Cohesion: 0.38
Nodes (6): Point, x, y, z, customPlaneSpec(), planeFrame()

### Community 142 - "SplineHandle"
Cohesion: 0.29
Nodes (7): SplineHandle, arm, index, tx, ty, x, y

### Community 144 - "cachedProfiles"
Cohesion: 0.18
Nodes (7): cachedProfiles(), keyOf(), Profile, area, face, x, y

## Knowledge Gaps
- **724 isolated node(s):** `ok`, `output`, `error`, `isReal`, `real` (+719 more)
  These have ≤1 connection - possible missing edges or undocumented components. (Counts symbols only; 1379 node(s) total have ≤1 connection when file, concept and rationale nodes are included.)
- **22 thin communities (<3 nodes) omitted from report** — run `graphify query` to explore isolated nodes.

## Suggested Questions
_Questions this graph is uniquely positioned to answer:_

- **Why does `Viewport` connect `Viewport` to `.initializeGL`, `Viewport.h`, `MainWindow`, `.rebuild`, `MainWindow.cpp`, `SketchCurves.cpp`, `Viewport.cpp`, `AdskModule.cpp`, `optional`, `rect`, `AnalysisSettings`, `SketchDisplay`, `ViewportAnalysis.cpp`, `.redrawAll`, `Handle`, `.toPixels`, `MainWindowTools.cpp`, `ViewportArrow.cpp`?**
  _High betweenness centrality (0.108) - this node is a cross-community bridge._
- **What connects `ok`, `output`, `error` to the rest of the system?**
  _724 weakly-connected nodes found - possible documentation gaps or missing edges._
- **Should `Viewport` be split into smaller, more focused modules?**
  _Cohesion score 0.01664516129032258 - nodes in this community are weakly interconnected._
- **Why does `optional` connect `optional` to `Viewport`, `DocCommands.cpp`, `MainWindow`, `Kernel.cpp`, `.features`, `Io.cpp`, `Unit`, `SketchCurves.cpp`, `ViewportSketch.cpp`, `Snap`, `Viewport.h`, `SketchCurves.cpp`, `QString`, `AnalysisSettings`, `ConstructionPoint`, `SketchRecord`, `InputDef`, `sketchFor`, `MainWindowArrow.cpp`, `Entity`, `Session`, `ViewportArrow.cpp`, `SketchEditor.cpp`, `Vec3`, `Document.cpp`, `CommandDialog.cpp`, `Joints`, `ConstructionAxis`?**
  _High betweenness centrality (0.107) - this node is a cross-community bridge._
- **Should `Icons.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.05887752425911356 - nodes in this community are weakly interconnected._
- **Why does `SketchEditor` connect `SketchEditor` to `Tool`, `Viewport.h`, `Viewport`, `Constraint`, `Kind`, `SketchEditor.cpp`, `Display`, `optional`, `PlaneEdges`, `Pick`, `.solveAndShow`, `Unit`, `Entity`, `Snap`, `Session`, `ViewportArrow.cpp`?**
  _High betweenness centrality (0.098) - this node is a cross-community bridge._
- **Should `Session.cpp` be split into smaller, more focused modules?**
  _Cohesion score 0.06331976481230213 - nodes in this community are weakly interconnected._