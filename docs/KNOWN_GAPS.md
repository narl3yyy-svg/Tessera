# Known gaps

Every known difference between Tessera and the behaviour it aims for. One row per item; closed items are struck
through and kept for history.
One line per item: id, what differs, why, and the phase that closes it.

| Id | Divergence | Reason | Closes in |
|---|---|---|---|
| P0-1 | ~~Expressions accept only `number [unit]`~~ Closed: arithmetic, `^`, parentheses, parameters, `pi`, and sqrt/sin/cos/tan/asin/acos/atan/atan2/abs/sign/floor/ceil/round/min/max/exp/ln/log/pow | | closed (P5) |
| P0-2 | The ribbon is a `QTabWidget` in a fixed toolbar with code-painted icons; no KDDockWidgets | P0 scope; icons must be rebuilt from spec, not copied | P0 follow-up / R2 |
| P0-3 | ~~`.tsr` members are all STORED~~ Closed: members are deflated when that is smaller (older STORED files still open) | | closed |
| P0-4 | Undo depth is capped at 1,000,000 steps, not unbounded | OCAF needs a numeric limit | accepted |
| P0-5 | ~~No 3D viewport~~ Closed: OCCT AIS viewport with ViewCube, grid, selection and standard views | | closed (P1) |
| P0-6 | adsk shim covers only `Application.get/activeProduct/version`, `ValueInput.createByReal/createByString`, `Design.cast/userParameters/rootComponent`, `UserParameters.add/count/item/itemByName`, `UserParameter` name/unit, settable `expression`/`value`/`comment`, `isDeletable`, `deleteMe()`, `Component.bRepBodies`, `BRepBody.name/volume/area` | P0 scope | R6 / P10 |
| P0-7 | adsk error behaviour (exception type and text) is assumed to be `RuntimeError` with a message; not yet checked against the reference | Not yet probed in the reference (R6) | R6 |
| P0-8 | Builds against OCCT 7.9.2 (the Kubuntu 26.04 package), not 8.0 | 8.0 not packaged | when packaged, or a source build |
| P0-9 | Lab 10.0.60.100 is 4 cores / 15 GB / iGPU, not the plan's 32 cores / 128 GB; it cannot host the Windows reference VM | Hardware | Hardware decision pending |
| P1-1 | Primitives are placed by typed X/Y/Z and an axis choice, not by clicking a sketch plane and point in the canvas | Sketching and in-canvas manipulators not built yet | P2 (sketch) |
| P1-2 | Z is up and the grid is the XY plane; there is no Y-up option | Simplicity | P2 (preferences) |
| P1-3 | Timeline has the history marker, drag-to-reorder and ~~no~~ playback buttons (start / step / end), but no feature groups | P1 scope | P2 |
| P1-4 | ~~Recompute replays every feature~~ Partly closed: an edit replays from the first changed feature on (what the features before it made is restored from memory; a design just opened replays fully once). Features after the changed one still all replay, even ones that do not depend on it (no dependency tracking), and body references are by name, not topological naming | P1 scope | P3 (topological naming) |
| P1-5 | Body visibility is view state, not saved in the document | P1 scope | P2 |
| P1-6 | The 3D view needs X11/XWayland (OCCT's Kubuntu build uses GLX); the app forces `QT_QPA_PLATFORM=xcb` on Wayland | Distro OCCT build | when OCCT is built with EGL |
| P1-7 | ~~Right click opens a plain context menu~~ Closed: a radial marking menu with the full menu below it | | closed |
| P2-1 | A sketch on a body face copies the face's plane when created; it does not follow the face if the body changes | Associative references need topological naming | P3 |
| P2-2 | Extrude remembers each picked profile by a point inside it; a large sketch edit can make it pick a different or no region (reported as an error) | No persistent profile identity yet | P3 |
| P2-3 | Sketch tools: ~~trim, offset, fillet, spline, polygon, slot, extend, chamfer, mirror~~ done; sketch patterns, text, Project / Intersect / Include 3D Geometry, Break and Sketch Scale are done too. Extend works on lines and arcs (not splines or ellipses); Chamfer is equal-distance and lines only; Mirror ties copies with symmetry constraints | P2 scope | P13 |
| P9-1 | Spline: ~~fit points only, no tangent handles; Trim and Offset skip splines~~ control point splines, tangent handles, Trim / Break / Offset done. Still no curvature constraints, and constraints act on its points, not the curve | P9 scope | later |
| P9-2 | Sketch Fillet: ~~line-line corners only~~ lines and arcs (not splines or ellipses); the two lines' length dimensions are removed because the corner they measured is gone | P9 scope | later |
| P9-3 | Sketch Offset: the copy of a line chain gets parallel constraints and one offset dimension (not Fusion's offset constraint that keeps every curve at the distance); offset arcs share their originals' centres; the side is chosen by where the cursor is | P9 scope | later |
| P2-4 | ~~Dimension values are numbers only~~ Closed: sketch dimensions and size boxes take expressions; a dimension keeps its expression and follows parameter changes (size boxes use the value once) | | closed (P5) |
| P2-5 | ~~Extrude extents: distance only~~ Closed: To Object, All, taper, two sides and thin are done (To Object: see P4-1) | | closed |
| P2-6 | ~~Dimensions show as value labels only~~ Closed: dimensions have arrows and extension lines; constraint glyphs are still letters | P2 scope | R2 |
| P2-7 | ~~Snapping to points only~~ Partly closed: drawing snaps to points, line midpoints, curves (with a point-on-curve constraint), body vertices and edges in the sketch plane, horizontal/vertical from the previous point, alignment with other points, and the grid (on by default). Lines leaving a curve snap tangent (T) or perpendicular (⟂) and get that constraint; pressing on the chain's last point and dragging draws a tangent arc; snapping onto a straight body edge projects it (purple, fixed), onto other body geometry gives a fixed point. Lines also snap parallel (∥) or perpendicular to other lines in the sketch; curved body edges project as fixed arcs/circles. Still missing: projected geometry does not follow later changes to the body | P2 scope | P11 |
| P2-8 | The constraint solver is our own Gauss-Newton solver, not planegcs; very large sketches (hundreds of entities) will be slow | Avoids an extra dependency; numeric Jacobian | when needed |
| P3-1 | Fillet/chamfer edges are found again on replay by a signature (curve type, direction, adjacent face normals, position relative to the body's bounding box), not by full topological naming; big changes can pick a different edge or report it missing | Real topological naming is a larger project | P3 (topological naming) |
| P3-2 | Fillet: constant or variable (start to end of each edge) radius; no setback, chord length or rule-based selection; ~~Chamfer: equal distance only~~ Chamfer has equal, two distances, and distance and angle | P3 scope | later |
| P3-3 | Revolve axis: sketch X/Y axis, the sketch's first construction line, or a world axis; no picking an arbitrary edge as the axis | P3 scope | P4 |
| P3-4 | While a Fillet/Chamfer dialog previews, edges are picked on the previewed body | Preview replaces the body | when the preview uses an overlay |
| P4-1 | ~~No in-canvas drag arrow~~ Closed: Extrude, Press Pull, Fillet and Chamfer have a drag arrow and a value box. Still open: To Object reaches flat faces and planes only (not curved faces or whole bodies); taper works on one-sided extrudes | P4 scope | P8 |
| P8-1 | The drag arrow moves in steps of whatever the mouse gives (no snapping to grid or round values while dragging); Fillet/Chamfer arrows start at the first picked edge and point toward the body's centre, not along the exact fillet bisector | P8 scope | later |
| P8-2 | Extruding body faces: the faces must be flat and face the same way; the result joins / cuts the body the faces belong to (Fusion can also extrude faces into a new body or other bodies) | P8 scope | later |
| P8-3 | Create Sketch shows the origin planes, axes and point with hover highlight, but there is no preview of the sketch grid on the hovered plane before clicking | P8 scope | later |
| P8-5 | Sketch Palette: Feature Options exist for Rectangle (2-point, center) only; 3D Sketch is shown disabled (no 3D sketches yet); the palette's settings are not saved with the sketch | P8 scope | with Project / 3-point tools |
| P10-1 | Construction axes/points are chosen from a list in Revolve and Circular Pattern (not by clicking them in the canvas); no Axis Perpendicular at Point / to Face, Point Along Path, Tangent Plane or Plane Through Three Points yet; vertex picks are stored by position | P10 scope | later |
| P11-1 | Reference parts not yet matching (docs/ORACLE.md): one fillet whose radius narrows to fit a tapering face follows a cubic B-spline radius law in the reference; Tessera keeps the radius constant (area 0.12% off). Lofts from a polygon to an offset (not coaxial) circle use the general loft | Variable-radius laws | P12 |
| P11-2 | Recipe features Tessera lacks: sheet metal, variable / chord / spline-radius fillets, boundary surface and thicken (~~thin extrude, holes on curved faces~~ done) | Not built yet | later |
| P12-1 | Assemblies: components group bodies of one design (no separate component files or per-component timelines, no Activate Component); joints move the component's bodies as a timeline step. Joint types: rigid, revolute, slider, cylindrical, pin-slot, planar, ball, with rotation / slide limits (Drive Joints moves the main motion only: the turn, or a slider's travel; no ball, planar, pin-slot), no limits, no as-built joints or joint origins, no contact. Joint origins snap to face centre / circle centre / edge midpoint / vertex only | P12 scope | later |
| P8-4 | A ribbon wider than the window scrolls sideways with the mouse wheel; Fusion instead folds panels into their menus | Simpler | later |
| P4-2 | ~~Split Body and Mirror use origin planes only~~ Closed: they take origin planes, construction planes or a picked flat face | | closed |
| P4-3 | Section Analysis is an app setting, not saved in the document; it starts from a clicked face or plane with a drag arrow for the depth and an angle field (no rotation ring in the canvas yet) | P4 scope | later |
| P4-4 | Export writes mm for mesh and STEP/IGES files; F3D, IPT, SKP, SAT, DWG, USD are not available (proprietary or unsupported by the kernel) | Formats | accepted |
| P4-5 | ASSEMBLE, CONFIGURE, CONSTRUCT and several INSPECT/INSERT entries, and the SURFACE/MESH/SHEET METAL/PLASTIC/MANAGE/UTILITIES tabs, are shown disabled | Not built yet | see ROADMAP.md |
| P5-1 | Hole places holes at a sketch's points (not by clicking on a face); the direction is opposite the sketch plane's normal unless flipped | P5 scope | P6 (face point placement) |
| P5-2 | Patterns copy features (what they added or cut, as one shape: "Identical", not "Adjust") or whole bodies, not faces or components; directions are world or construction axes (not picked edges) | P5 scope | P6 |
| P5-3 | Trim removes up to the nearest crossings; trimmed pieces do not get coincident constraints to the crossing curves | P5 scope | P6 |
| P5-4 | Size boxes exist for Line (length, angle), Rectangle, Center Rectangle (width, height), Circle (diameter), Polygon (diameter, sides) and Slot (length, width); not yet for arcs | P5 scope | P6 |
| P5-5 | Construction planes: offset, angle about the plane's X/Y axis, midplane of two parallel planes, through three vertices, tangent to a cylinder (~~not tangent to faces or through points~~). Still no plane through two edges, tangent to other curved faces, or at a point on a face; three-point planes take body vertices, not construction points | P5 scope | P6 |
| P5-6 | A plane picked from a body face is copied when picked (not associative to the face) | Needs topological naming | P6 |
| P6-1 | Sweep: the path is all curves of one sketch (one connected chain); no guide rails, twist or scaling; the profile must sit at the start of the path | P6 scope | later |
| P6-2 | Loft: one profile per sketch (its largest region), no rails or centre line, no point sections | P6 scope | later |
| P6-3 | ~~Press Pull moves flat faces only~~ Closed: curved faces are offset. Draft has one pull direction and neutral plane for all faces (no parting line or two-sided draft) | | closed |
| P7-1 | ~~Model parameters have no names~~ Closed: feature values get names (d1, d2 ...) when made, usable in any expression. A value that only appears later (Extent changed to Distance) gets the next free name then. Sketches made by script may give a dimension a name a feature already has; the first one wins in expressions | | closed (P8) |
| P7-2 | Expression rules: a bare number takes the unit of what it meets (the field's unit, the parameter's unit, or the length it is added to); trig functions read bare numbers as degrees; floor/ceil/round work in the display unit. Fusion's exact rules for mixed units are not yet checked against the reference | Not yet probed in the reference (R6) | R6 |
| P7-3 | In command panels, expressions are typed into numeric fields (Real inputs); whole-number fields (pattern quantities) take expressions from scripts and Change Parameters but the panel's spin box takes digits only | Qt spin box | P8 |
| P7-4 | ~~Change Parameters has no favourites, filter or renaming~~ Closed: star column, Favorites group, filter box, rename by double-clicking the name. A sketch dimension's value is still changed in the sketch, not in the table | | closed (P8) |
| P11-1 | Reference parts not yet matching (docs/ORACLE.md): loft of a rectangle into a circle gives 7 faces instead of 6 (volume 0.14% high); shells of an L-bracket and a boss plate keep one extra face; overlapping feature patterns leave unmerged faces (62 vs 39) and slightly more volume; a fillet on a boss plate's base edges fails; a gear-tooth sketch solves to a slightly different shape; a fillet whose radius must shrink to fit differs in area by 0.1% | Kernel face merging and solver | P11 |
| P11-2 | Recipe features Tessera lacks: sheet metal, variable / chord / spline-radius fillets, boundary surface and thicken, plane at an angle about an edge (~~mirror of features, path pattern, thin extrude, drill-point tips, loft to a point~~ done) | Not built yet | later |

## Visual styles

- Wireframe with Hidden Edges / Visible Edges Only compute exact hidden lines in orthographic views only. In a perspective view they draw every edge, hidden ones dashed through the see-through faces only where the depth allows, so the result is approximate.
- Hidden lines are recomputed as the view turns; very large models may orbit slowly in these two styles.

## Splines and conics

- A conic's rho is set when drawn (0.5) and changed by double-clicking the curve; it cannot yet be a dimension or an expression.
- Control point splines are cubic (fewer frame points: lower degree) and cannot be closed.
- Tangent handles set a fit point's direction and fullness (handle length); they cannot yet be dimensioned or tied to other curves (no tangent or curvature constraint on a handle).
- Trimming or breaking a spline makes fit point splines through the original's points on each piece, with the original's directions at the cut; the shape between can shift slightly (a control point spline or conic piece is fitted through points sampled along it). Pieces are not tied to the curves that cut them (as with lines, P5-3).
- Offset of a spline or ellipse is a fit point spline through offset points (24 round a closed curve); it does not follow later changes to the original, and an ellipse offset inward past its tightest curve is refused.
- Extend does not reach to or from splines and ellipses yet.

## Include 3D Geometry

- Body edges come in as they are in space, fixed (purple) and never part of a profile; lines and circles / arcs parallel to the sketch plane stay exact, other edges become fit point splines through 33 points along them.
- Like projected geometry, included edges do not follow later changes to the body.
- Included points can be snapped to and constrained; the sketch uses their position seen along its normal (as the familiar tool does when a sketch point is tied to them).

## Sketch text

- A text box aligns its lines between the corners but does not wrap or shrink text to fit; text longer than the box runs past it.
- Text on Path starts at the curve's start (a circle: its rightmost point, anticlockwise); letters past the curve's end pile up at the end. No character spacing, bold or italic yet.
