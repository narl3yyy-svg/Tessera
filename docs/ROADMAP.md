# Roadmap

Goal: a native Kubuntu/KDE parametric CAD application that works the way people who know Fusion expect (same
workflow, same concepts, compatible scripting API), built only from original code and artwork. PCB/electronics is out
of scope.

Each phase ends with something usable; nothing below is promised by date.

| Phase | Delivers | State |
|---|---|---|
| P0 | Command framework, OCAF document, undo, `.tsr` files, Python API, app shell | done |
| P1 | 3D viewport, ViewCube, navigation, primitives with booleans, parametric timeline (edit/suppress/delete) | done |
| P2 | **Sketching + Extrude**: sketch on a plane or face; line, rectangle, circle, arc, point, construction; constraints and dimensions with our own solver; fully-constrained colouring; Extrude with profile picking | **done (this release)** |
| P3a | **Revolve, Fillet, Chamfer** with edge picking that survives edits | **done (this release)** |
| P3b | **More features**: Shell, Hole, Sweep, Loft, Draft; extrude To Object/All/taper; trim/offset/spline/fillet in sketches ✅; in-canvas drag arrows ✅ (Extrude, Press Pull, Fillet, Chamfer); topological naming | next |
| P4 | **Construction and patterns**: offset/angle/midplane planes, axes, points; rectangular/circular/path patterns; mirror; Combine, Split Body, Move/Copy, Press Pull | |
| P5 | **Parameters and expressions**: `d1 = width/2 + 3 mm`, parameter table, every input accepts expressions | **done** (sketch dimensions and feature values are named model parameters; rename, favourites, filter) |
| P6 | **Components and assemblies**: components, joints (rigid, revolute, slider, ...), motion, interference | |
| P7 | **Import/export**: STEP, IGES, STL, 3MF, OBJ, DXF; 3D-print export | |
| P8 | **Drawings**: 2D drawings from the model with views, sections, dimensions, PDF/DXF output | |
| P9 | **Inspect and appearance**: measure, section analysis, materials and appearances, physical properties | |
| P10 | **Scripting parity**: the `adsk.core` / `adsk.fusion` API surface needed to run typical Fusion add-ins | |
| later | Surface and mesh workspaces, sheet metal, CAM toolpaths, simulation, rendering | |

Not planned: cloud storage/collaboration (designs are local files), anything that copies Autodesk branding,
icons, file formats that are not publicly documented, or product names.

## Fusion feature checklist

Tracked against the menus people know. Done = usable today.

**Create**: Sketch ✅ · Extrude ✅ (distance, all, two sides, symmetric, start offset, taper, thin (Side 1 / Center / Side 2; profiles or open curves), body faces, drag arrow (a second arrow for Two Sides), to object) · Revolve ✅ · Box/Cylinder/Sphere/Torus/Cone ✅ · Mirror ✅ (bodies or features) · Hole ✅ (on any face by clicking, or at sketch points; simple, counterbore, countersink; 118° drill point) · Rectangular Pattern ✅ (features or bodies, Extent / Spacing, drag arrows) · Circular Pattern ✅ (features or bodies) · Sweep ✅ · Loft ✅ (exact polygon-to-circle, to a point) · Rib · Web · Emboss · Thread ✅ (ISO metric; cosmetic or modeled) · Coil ✅ · Pipe ✅ · Pattern on Path ✅ (spacing / extent, identical / path direction) · Thicken · Boundary Fill · Create Form (T-splines, later)

**Modify**: Fillet ✅ (lines, arcs) · Chamfer ✅ (lines) · Shell ✅ · Combine ✅ · Split Body ✅ · Move/Copy ✅ · Scale ✅ · Remove ✅ · Press Pull ✅ · Draft ✅ · Offset Face ✅ · Replace Face · Split Face ✅ (by a plane) · Silhouette Split · Align · Delete (faces) ✅ · Physical Material · Appearance · Change Parameters (table) ✅ · Compute All

**Assemble**: New Component ✅ · Joint ✅ (rigid, revolute, slider, cylindrical) · As-Built Joint · Joint Origin · Rigid Group · Drive Joints ✅ · Motion Link · Motion Study · Contact Sets

**Construct**: Offset Plane ✅ · Plane at Angle ✅ · Midplane ✅ · Tangent Plane ✅ (cylinders) · Plane through three points ✅ · Plane through two edges · Plane tangent to face at point · Axis ✅ (cylinder/cone/torus, edge, two points, two planes) · Point ✅ (vertex, two edges, three planes, centre, edge and plane)

**Inspect**: Measure ✅ · Interference ✅ · Section Analysis ✅ · Center of Mass ✅ · Curvature Comb ✅ · Zebra ✅ · Draft Analysis ✅ · Curvature Map ✅ · Isocurve · Minimum Radius · Accessibility

**Display**: ViewCube ✅ (faces, edges, corners, drag to orbit) · Named Views ✅ · Visual Style ✅ (all six, hidden-line wireframes) · Orthographic / Perspective ✅ · Environment · Ground shadow · Layout grid

**Insert**: Insert Mesh / CAD (STEP, IGES, STL, BREP) ✅ · Insert SVG · Insert DXF · Canvas · Decal · McMaster-style part libraries (no)

**Select**: Select ✅ · Selection filters (bodies, faces, edges, vertices) ✅ · Window/Freeform/Paint selection · Select through

**Sketch**: Line ✅ · Rectangle ✅ · Circle ✅ · Arc ✅ · Point ✅ · Construction ✅ · Dimension ✅ · on-canvas size boxes (Tab / Enter) ✅ · Center Rectangle ✅ · Polygon ✅ · Slot ✅ · Trim ✅ (lines, arcs, circles, ellipses, splines, conics) · Midpoint Line ✅ · 3-Point Rectangle ✅ · 2-Point / 3-Point / Tangent circles ✅ · 3-Point / Tangent arcs ✅ · Ellipse ✅ · Spline ✅ (fit point, control point, tangent handles) · Conic ✅ · Text ✅ (point, box, path) · Mirror ✅ · Circular/Rectangular Pattern ✅ · Project ✅ / Intersect ✅ / Include 3D Geometry ✅ · Project to Surface · 3D Sketch · Fillet ✅ · Chamfer ✅ · Offset ✅ (chains, ellipses, splines) · Extend ✅ (lines, arcs) · Break ✅ · Sketch Scale ✅ · Move/Copy ✅

**Sketch constraints**: Horizontal/Vertical ✅ · Coincident ✅ · Tangent ✅ · Equal ✅ · Parallel ✅ · Perpendicular ✅ · Fix ✅ · Midpoint ✅ · Concentric ✅ · Collinear ✅ · Symmetry ✅ · Curvature · Polygon; Sketch Palette ✅ (feature options, linetype, Look At, grid, snap, slice, show profiles/points/dimensions/constraints/construction)

**File and settings**: Document units ✅ · Recent designs ✅ · Sketch to DXF ✅ · Export (STEP, IGES, STL, 3MF, OBJ, BREP) ✅ · 3D Print ✅ · Capture Image ✅ · Preferences: navigation presets, zoom direction, orbit type, camera ✅ · Grid settings and snap ✅ · Named Views · Incremental Move · Design history import/export
