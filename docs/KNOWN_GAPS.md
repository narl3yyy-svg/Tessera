# Known gaps

Every known difference between Tessera and the behaviour it aims for. One row per item; closed items are struck
through and kept for history.
One line per item: id, what differs, why, and the phase that closes it.

| Id | Divergence | Reason | Closes in |
|---|---|---|---|
| P0-1 | ~~Expressions accept only `number [unit]`~~ Closed: arithmetic, `^`, parentheses, parameters, `pi`, and sqrt/sin/cos/tan/asin/acos/atan/atan2/abs/sign/floor/ceil/round/min/max/exp/ln/log/pow | | closed (P5) |
| P0-2 | The ribbon is a `QTabWidget` in a fixed toolbar with code-painted icons; no KDDockWidgets | P0 scope; icons must be rebuilt from spec, not copied | P0 follow-up / R2 |
| P0-3 | `.tsr` members are all STORED (no deflate) | No compression dependency in core yet | before 1.0 |
| P0-4 | Undo depth is capped at 1,000,000 steps, not unbounded | OCAF needs a numeric limit | accepted |
| P0-5 | ~~No 3D viewport~~ Closed: OCCT AIS viewport with ViewCube, grid, selection and standard views | | closed (P1) |
| P0-6 | adsk shim covers only `Application.get/activeProduct/version`, `ValueInput.createByReal/createByString`, `Design.cast/userParameters/rootComponent`, `UserParameters.add/count/item/itemByName`, `UserParameter` name/unit, settable `expression`/`value`/`comment`, `isDeletable`, `deleteMe()`, `Component.bRepBodies`, `BRepBody.name/volume/area` | P0 scope | R6 / P10 |
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
| P2-3 | Sketch tools: ~~trim, offset, fillet, spline, polygon, slot~~ done; still no extend, chamfer, mirror/pattern, text, or projecting body edges | P2 scope | P8 |
| P9-1 | Spline: fit-point splines only (no control-point splines, tangency handles or curvature constraints); constraints act on its points, not the curve; Trim and Offset skip splines | P9 scope | later |
| P9-2 | Sketch Fillet: line-line corners only (not line-arc or arc-arc); the two lines' length dimensions are removed because the corner they measured is gone | P9 scope | later |
| P9-3 | Sketch Offset: the copy of a line chain gets parallel constraints and one offset dimension (not Fusion's offset constraint that keeps every curve at the distance); offset arcs share their originals' centres; the side is chosen by where the cursor is | P9 scope | later |
| P2-4 | ~~Dimension values are numbers only~~ Closed: sketch dimensions and size boxes take expressions; a dimension keeps its expression and follows parameter changes (size boxes use the value once) | | closed (P5) |
| P2-5 | Extrude extents: distance only (one side / symmetric); no To Object, All, taper or thin | P2 scope | P3 |
| P2-6 | Dimensions show as value labels without arrows/extension lines; constraint glyphs are letters | P2 scope | R2 |
| P2-7 | ~~Snapping to points only~~ Partly closed: drawing snaps to points, line midpoints, curves (with a point-on-curve constraint), body vertices and edges in the sketch plane, horizontal/vertical from the previous point, alignment with other points, and the grid (on by default). Still missing: tangent / perpendicular inference, click-and-drag from a line end for a tangent arc, and body edges are snapped to but not projected into the sketch | P2 scope | P11 |
| P2-8 | The constraint solver is our own Gauss-Newton solver, not planegcs; very large sketches (hundreds of entities) will be slow | Avoids an extra dependency; numeric Jacobian | when needed |
| P3-1 | Fillet/chamfer edges are found again on replay by a signature (curve type, direction, adjacent face normals, position relative to the body's bounding box), not by full topological naming; big changes can pick a different edge or report it missing | Real topological naming is a larger project | P3 (topological naming) |
| P3-2 | Fillet: constant radius only (no variable radius, setback or rule-based selection); Chamfer: equal distance only (no two-distance or distance-angle) | P3 scope | P4 |
| P3-3 | Revolve axis: sketch X/Y axis, the sketch's first construction line, or a world axis; no picking an arbitrary edge as the axis | P3 scope | P4 |
| P3-4 | While a Fillet/Chamfer dialog previews, edges are picked on the previewed body | Preview replaces the body | when the preview uses an overlay |
| P4-1 | ~~No in-canvas drag arrow~~ Closed: Extrude, Press Pull, Fillet and Chamfer have a drag arrow and a value box. Still open: extents are Distance and All (no To Object / To Face); taper works on one-sided extrudes; no second arrow for Two Sides | P4 scope | P8 |
| P8-1 | The drag arrow moves in steps of whatever the mouse gives (no snapping to grid or round values while dragging); Fillet/Chamfer arrows start at the first picked edge and point toward the body's centre, not along the exact fillet bisector | P8 scope | later |
| P8-2 | Extruding body faces: the faces must be flat and face the same way; the result joins / cuts the body the faces belong to (Fusion can also extrude faces into a new body or other bodies) | P8 scope | later |
| P8-3 | Create Sketch shows the origin planes, axes and point with hover highlight, but there is no preview of the sketch grid on the hovered plane before clicking | P8 scope | later |
| P8-5 | Sketch Palette: Feature Options exist for Rectangle (2-point, center) only; Projected Geometries and 3D Sketch are shown disabled (no projection or 3D sketches yet); the palette's settings are not saved with the sketch | P8 scope | with Project / 3-point tools |
| P10-1 | Construction axes/points are chosen from a list in Revolve and Circular Pattern (not by clicking them in the canvas); no Axis Perpendicular at Point / to Face, Point Along Path, Tangent Plane or Plane Through Three Points yet; vertex picks are stored by position | P10 scope | later |
| P8-4 | A ribbon wider than the window scrolls sideways with the mouse wheel; Fusion instead folds panels into their menus | Simpler | later |
| P4-2 | ~~Split Body and Mirror use origin planes only~~ Closed: they take origin planes, construction planes or a picked flat face | | closed |
| P4-3 | Section Analysis is an app setting, not saved in the document; it starts from a clicked face or plane with a drag arrow for the depth and an angle field (no rotation ring in the canvas yet) | P4 scope | later |
| P4-4 | Export writes mm for mesh and STEP/IGES files; F3D, IPT, SKP, SAT, DWG, USD are not available (proprietary or unsupported by the kernel) | Formats | accepted |
| P4-5 | ASSEMBLE, CONFIGURE, CONSTRUCT and several INSPECT/INSERT entries, and the SURFACE/MESH/SHEET METAL/PLASTIC/MANAGE/UTILITIES tabs, are shown disabled | Not built yet | see ROADMAP.md |
| P5-1 | Hole places holes at a sketch's points (not by clicking on a face); the direction is opposite the sketch plane's normal unless flipped | P5 scope | P6 (face point placement) |
| P5-2 | Patterns copy whole bodies (not features or faces); circular patterns turn about a world axis through the origin | P5 scope | P6 |
| P5-3 | Trim removes up to the nearest crossings; trimmed pieces do not get coincident constraints to the crossing curves | P5 scope | P6 |
| P5-4 | Size boxes exist for Line (length, angle), Rectangle, Center Rectangle (width, height), Circle (diameter), Polygon (diameter, sides) and Slot (length, width); not yet for arcs | P5 scope | P6 |
| P5-5 | Construction planes are built from origin or other construction planes (offset, angle about the plane's X/Y axis, midplane of two parallel planes); not yet tangent to faces or through points/edges | P5 scope | P6 |
| P5-6 | A plane picked from a body face is copied when picked (not associative to the face) | Needs topological naming | P6 |
| P6-1 | Sweep: the path is all curves of one sketch (one connected chain); no guide rails, twist or scaling; the profile must sit at the start of the path | P6 scope | later |
| P6-2 | Loft: one profile per sketch (its largest region), no rails or centre line, no point sections | P6 scope | later |
| P6-3 | Press Pull moves flat faces only (offset of curved faces is planned with Offset Face) | P6 scope | P7 |
| P7-1 | Model parameters (feature values) are listed and editable in Change Parameters but have no names (`d1`, `d2`) that other expressions can use; only user parameters can be referenced | Needs stable per-input names | P8 |
| P7-2 | Expression rules: a bare number takes the unit of what it meets (the field's unit, the parameter's unit, or the length it is added to); trig functions read bare numbers as degrees; floor/ceil/round work in the display unit. Fusion's exact rules for mixed units are not yet checked against the reference | Not yet probed in the reference (R6) | R6 |
| P7-3 | In command panels, expressions are typed into numeric fields (Real inputs); whole-number fields (pattern quantities) take expressions from scripts and Change Parameters but the panel's spin box takes digits only | Qt spin box | P8 |
| P7-4 | Change Parameters has no favourites, filter or search, and parameters cannot be renamed | P7 scope | P8 |
