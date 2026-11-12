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
| P5 | **Parameters and expressions**: `d1 = width/2 + 3 mm`, parameter table, every input accepts expressions | **done** (model parameter names `d1` still to come) |
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

**Create**: Sketch ✅ · Extrude ✅ (distance, all, two sides, symmetric, start offset, taper, body faces, drag arrow) · Revolve ✅ · Box/Cylinder/Sphere/Torus/Cone ✅ · Mirror ✅ (body) · Hole ✅ (simple, counterbore, countersink) · Rectangular Pattern ✅ · Circular Pattern ✅ · Sweep ✅ · Loft ✅ · Rib · Web · Emboss · Thread · Coil · Pipe · Path Pattern · Thicken · Boundary Fill · Create Form (T-splines, later)

**Modify**: Fillet ✅ · Chamfer ✅ · Shell ✅ · Combine ✅ · Split Body ✅ · Move/Copy ✅ · Scale ✅ · Remove ✅ · Press Pull ✅ · Draft · Offset Face · Replace Face · Split Face · Silhouette Split · Align · Delete (faces) · Physical Material · Appearance · Change Parameters (table) ✅ · Compute All

**Assemble**: New Component · Joint · As-Built Joint · Joint Origin · Rigid Group · Drive Joints · Motion Link · Motion Study · Contact Sets

**Construct**: Offset Plane ✅ · Plane at Angle ✅ · Midplane ✅ · Tangent Plane · Plane through points · Axis ✅ (cylinder/cone/torus, edge, two points, two planes) · Point ✅ (vertex, two edges, three planes, centre, edge and plane)

**Inspect**: Measure ✅ · Interference ✅ · Section Analysis ✅ · Center of Mass ✅ · Curvature Comb · Zebra · Draft Analysis · Curvature Map · Isocurve · Minimum Radius · Accessibility

**Insert**: Insert Mesh / CAD (STEP, IGES, STL, BREP) ✅ · Insert SVG · Insert DXF · Canvas · Decal · McMaster-style part libraries (no)

**Select**: Select ✅ · Selection filters (bodies, faces, edges, vertices) ✅ · Window/Freeform/Paint selection · Select through

**Sketch**: Line ✅ · Rectangle ✅ · Circle ✅ · Arc ✅ · Point ✅ · Construction ✅ · Dimension ✅ · on-canvas size boxes (Tab / Enter) ✅ · Center Rectangle ✅ · Polygon ✅ · Slot ✅ · Trim ✅ · Midpoint Line · 3-Point Rectangle · 2-Point / 3-Point / Tangent circles · 3-Point / Tangent arcs · Ellipse · Spline ✅ (fit point) · Conic · Text · Mirror · Circular/Rectangular Pattern · Project/Include · Fillet ✅ · Chamfer · Offset ✅ · Extend · Break · Sketch Scale · Move/Copy

**Sketch constraints**: Horizontal/Vertical ✅ · Coincident ✅ · Tangent ✅ · Equal ✅ · Parallel ✅ · Perpendicular ✅ · Fix ✅ · Midpoint ✅ · Concentric ✅ · Collinear ✅ · Symmetry ✅ · Curvature · Polygon; Sketch Palette ✅ (feature options, linetype, Look At, grid, snap, slice, show profiles/points/dimensions/constraints/construction)

**File and settings**: Document units ✅ · Export (STEP, IGES, STL, 3MF, OBJ, BREP) ✅ · 3D Print ✅ · Capture Image ✅ · Preferences: navigation presets, zoom direction, orbit type, camera ✅ · Grid settings and snap ✅ · Named Views · Incremental Move · Design history import/export
