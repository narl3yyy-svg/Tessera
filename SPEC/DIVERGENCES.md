# Known divergences

Every gap between Tessera and the plan or the reference behaviour goes here (plan §9).
One line per item: id, what differs, why, and the phase that closes it.

| Id | Divergence | Reason | Closes in |
|---|---|---|---|
| P0-1 | Expressions accept only `number [unit]`: no arithmetic, functions or parameter references | P0 scope | P1 (expression engine) |
| P0-2 | The ribbon is a `QTabWidget` in a fixed toolbar with code-painted icons; no KDDockWidgets | P0 scope; icons must be rebuilt from spec, not copied | P0 follow-up / R2 |
| P0-3 | `.tsr` members are all STORED (no deflate) | No compression dependency in core yet | before 1.0 |
| P0-4 | Undo depth is capped at 1,000,000 steps, not unbounded | OCAF needs a numeric limit | accepted |
| P0-5 | ~~No 3D viewport~~ Closed: OCCT AIS viewport with ViewCube, grid, selection and standard views | | closed (P1) |
| P0-6 | adsk shim covers only `Application.get/activeProduct/version`, `ValueInput.createByReal/createByString`, `Design.cast/userParameters/rootComponent`, `UserParameters.add/count/item/itemByName`, `UserParameter` read-only properties, `Component.bRepBodies`, `BRepBody.name/volume/area` | P0 scope | R6 / P10 |
| P0-7 | adsk error behaviour (exception type and text) is assumed to be `RuntimeError` with a message; not yet checked against the reference | Not yet probed in the reference (R6) | R6 |
| P0-8 | Builds against OCCT 7.9.2 (the Kubuntu 26.04 package), not 8.0 | 8.0 not packaged | when packaged, or a source build |
| P0-9 | Lab 10.0.60.100 is 4 cores / 15 GB / iGPU, not the plan's 32 cores / 128 GB; it cannot host the Windows reference VM | Hardware | Hardware decision pending |
| P1-1 | Primitives are placed by typed X/Y/Z and an axis choice, not by clicking a sketch plane and point in the canvas | Sketching and in-canvas manipulators not built yet | P2 (sketch) |
| P1-2 | Z is up and the grid is the XY plane; there is no Y-up option | Simplicity | P2 (preferences) |
| P1-3 | No timeline rollback marker or playback; features can be edited, suppressed and deleted only | P1 scope | P2 |
| P1-4 | Recompute replays every feature (no dependency tracking) and body references are by name, not topological naming | P1 scope | P3 (topological naming) |
| P1-5 | Body visibility is view state, not saved in the document | P1 scope | P2 |
| P1-6 | The 3D view needs X11/XWayland (OCCT's Kubuntu build uses GLX); the app forces `QT_QPA_PLATFORM=xcb` on Wayland | Distro OCCT build | when OCCT is built with EGL |
| P1-7 | Right click opens a plain context menu, not a radial marking menu | P1 scope | R2 |
| P2-1 | A sketch on a body face copies the face's plane when created; it does not follow the face if the body changes | Associative references need topological naming | P3 |
| P2-2 | Extrude remembers each picked profile by a point inside it; a large sketch edit can make it pick a different or no region (reported as an error) | No persistent profile identity yet | P3 |
| P2-3 | Sketch tools: no trim/extend, offset, fillet, spline, polygon, slot, mirror/pattern, text, or projecting body edges | P2 scope | P3/P4 |
| P2-4 | Dimension values are numbers with optional units; parameter names and expressions are not accepted yet | Expression engine is P5 | P5 |
| P2-5 | Extrude extents: distance only (one side / symmetric); no To Object, All, taper or thin | P2 scope | P3 |
| P2-6 | Dimensions show as value labels without arrows/extension lines; constraint glyphs are letters | P2 scope | R2 |
| P2-7 | While drawing, snapping is to points only (no automatic point-on-curve, tangent or perpendicular inference) | P2 scope | P3 |
| P2-8 | The constraint solver is our own Gauss-Newton solver, not planegcs; very large sketches (hundreds of entities) will be slow | Avoids an extra dependency; numeric Jacobian | when needed |
| P3-1 | Fillet/chamfer edges are found again on replay by a signature (curve type, direction, adjacent face normals, position relative to the body's bounding box), not by full topological naming; big changes can pick a different edge or report it missing | Real topological naming is a larger project | P3 (topological naming) |
| P3-2 | Fillet: constant radius only (no variable radius, setback or rule-based selection); Chamfer: equal distance only (no two-distance or distance-angle) | P3 scope | P4 |
| P3-3 | Revolve axis: sketch X/Y axis, the sketch's first construction line, or a world axis; no picking an arbitrary edge as the axis | P3 scope | P4 |
| P3-4 | While a Fillet/Chamfer dialog previews, edges are picked on the previewed body | Preview replaces the body | when the preview uses an overlay |
| P4-1 | Extrude: no in-canvas drag arrow yet (values are typed in the panel); extents are Distance and All (no To Object / To Face); taper works on one-sided extrudes | P4 scope | P5 |
| P4-2 | Split Body and Mirror use origin planes plus an offset, not picked faces or construction planes | Construction planes not built yet | P5 (CONSTRUCT) |
| P4-3 | Section Analysis and the units choice for new designs are app settings; section analysis is not saved in the document | P4 scope | later |
| P4-4 | Export writes mm for mesh and STEP/IGES files; F3D, IPT, SKP, SAT, DWG, USD are not available (proprietary or unsupported by the kernel) | Formats | accepted |
| P4-5 | ASSEMBLE, CONFIGURE, CONSTRUCT and several INSPECT/INSERT entries, and the SURFACE/MESH/SHEET METAL/PLASTIC/MANAGE/UTILITIES tabs, are shown disabled | Not built yet | see ROADMAP.md |
