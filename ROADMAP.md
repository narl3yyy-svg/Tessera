# Roadmap

Goal: a native Kubuntu/KDE parametric CAD application that works the way people who know Fusion expect (same
workflow, same concepts, compatible scripting API), built only from original code and artwork. PCB/electronics is out
of scope.

Each phase ends with something usable; nothing below is promised by date.

| Phase | Delivers | State |
|---|---|---|
| P0 | Command framework, OCAF document, undo, `.tsr` files, Python API, app shell | done |
| P1 | 3D viewport, ViewCube, navigation, primitives with booleans, parametric timeline (edit/suppress/delete) | **done (this release)** |
| P2 | **Sketching**: sketch on a plane or face; line, rectangle, circle, arc, spline, offset, trim; constraints and dimensions (planegcs solver); fully-constrained colouring | next |
| P3 | **Sketch-based features**: Extrude, Revolve, Sweep, Loft, Hole, Thread (cosmetic), Shell, Fillet, Chamfer, Draft; in-canvas drag arrows; face/edge selection; topological naming so edits keep references | |
| P4 | **Construction and patterns**: offset/angle/midplane planes, axes, points; rectangular/circular/path patterns; mirror; Combine, Split Body, Move/Copy, Press Pull | |
| P5 | **Parameters and expressions**: `d1 = width/2 + 3 mm`, parameter table, every input accepts expressions | |
| P6 | **Components and assemblies**: components, joints (rigid, revolute, slider, ...), motion, interference | |
| P7 | **Import/export**: STEP, IGES, STL, 3MF, OBJ, DXF; 3D-print export | |
| P8 | **Drawings**: 2D drawings from the model with views, sections, dimensions, PDF/DXF output | |
| P9 | **Inspect and appearance**: measure, section analysis, materials and appearances, physical properties | |
| P10 | **Scripting parity**: the `adsk.core` / `adsk.fusion` API surface needed to run typical Fusion add-ins | |
| later | Surface and mesh workspaces, sheet metal, CAM toolpaths, simulation, rendering | |

Not planned: cloud storage/collaboration (designs are local files), anything that copies Autodesk branding,
icons, file formats that are not publicly documented, or product names.
