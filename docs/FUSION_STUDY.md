# Fusion study list

Tessera aims to work the way Fusion users expect. This file tracks (1) the tutorial videos to study and (2) the
behaviours found there that Tessera does not match yet. Each finding moves to `docs/ROADMAP.md` or
`docs/KNOWN_GAPS.md` once it is built or scheduled.

## Videos

| # | Video | Studied |
|---|---|---|
| 1 | https://www.youtube.com/watch?v=d3qGQ2utl2A || transcript |
| 2 | https://www.youtube.com/watch?v=DfAfxae8aRc || transcript |
| 3 | https://www.youtube.com/watch?v=ZReXmjT42DM || transcript |
| 4 | https://www.youtube.com/watch?v=9Y-3W-Pr64U || transcript |
| 5 | https://www.youtube.com/watch?v=zN44hW9zX1I || transcript |
| 6 | https://www.youtube.com/watch?v=AfeCRrYsAys || transcript |
| 7 | https://www.youtube.com/watch?v=Mv54UfwYYos || transcript |
| 8 | https://www.youtube.com/watch?v=o5rcAv7xVUo || transcript |
| 9 | https://www.youtube.com/watch?v=2YaMulL4dZY || transcript |
| 10 | https://www.youtube.com/watch?v=BUH3WiUjMXw || transcript |
| 11 | https://www.youtube.com/watch?v=pa6VWGFoZ2Q || transcript |
| 12 | https://www.youtube.com/watch?v=J3rPwne4lWY || transcript |
| 13 | https://www.youtube.com/watch?v=zLL6foqTdJg || transcript |
| 14 | https://www.youtube.com/watch?v=xmAGzRBDccs || transcript |
| 15 | https://www.youtube.com/watch?v=QnDJl9W5Uso || transcript |
| 16 | https://www.youtube.com/watch?v=vr_zPVEsyjs || transcript |
| 17 | https://www.youtube.com/watch?v=DJULiA1aTtM || transcript |
| 18 | https://www.youtube.com/watch?v=fYDJLdOV_zE || transcript |
| 19 | https://www.youtube.com/watch?v=smbb4rJPBGg | |
| 20 | https://www.youtube.com/watch?v=Q1Thdrt40MA | |
| 21 | https://www.youtube.com/watch?v=OsdL0VoaGl0 || transcript |
| 22 | https://www.youtube.com/watch?v=5PsR8bL-Wv4 | |
| 23 | https://www.youtube.com/watch?v=EzJMWLX0IbU | |
| 24 | https://www.youtube.com/watch?v=WtEWbNIaK9Q | |
| 25 | https://www.youtube.com/watch?v=NqjbJZ2ekRU | |
| 26 | https://www.youtube.com/watch?v=ShmSm9vjKpI | |
| 27 | https://www.youtube.com/watch?v=NweBvuVYuQo | |
| 28 | https://www.youtube.com/watch?v=ePEypa1kB-g | |
| 29 | Playlist: https://www.youtube.com/playlist?list=PLLm7Yjr9z_z07ohtjFGkA5w-j_NMj8B3J (every video) | all 40 transcripts fetched; lessons 3, 8, 9 read |
| 30 | Autodesk tutorial index: https://www.autodesk.com/solutions/design-manufacturing/fusion-tutorials | |

## Known differences still to build

Behaviour already known to differ, before the videos; findings from the videos are added below it.

### Selection and the canvas
- [x] Window selection left-to-right (fully inside, solid blue box) vs right-to-left (crossing, dashed green box), in the canvas, in sketches and while a command picks edges / faces / profiles; Shift adds, Ctrl removes.
- [x] Selection priority (SELECT menu: No Selection Priority, Select Body / Face / Edge / Vertex Priority) and the click-and-hold Select Other list (everything under the cursor, front to back; hovering an entry highlights it).
- [ ] Freeform and paint selection; Selection Filters as check items (sketches, construction, components).
- [x] Marking menu (right-click radial menu) with Repeat, Undo, Sketch, Extrude, Hole, Press Pull, Fillet, Move/Copy; a sketch-mode ring; OK / Cancel inside a command.
- [x] Pre-selection: selected items carried into the next command: click a profile (no command running), then E; select edges (Select Edges filter), then F; selected bodies go into body inputs. A click picks the face or edge under the cursor by default (near an edge of the front face the edge wins, on hover too); Select Bodies picks whole bodies.
- [x] Hovering a body shows its name tooltip (its Browser name, renames included).
- [x] Double-click an edge selects the loop round the face the cursor is on (with no command running, or adding to Fillet / Chamfer picks).
- [x] Tangent chain: a Fillet / Chamfer pick takes the edge's whole tangent chain (shown and listed), clicking any edge of it again drops the chain. Not yet: the Tangent Chain checkbox to turn it off (OCCT's fillet always follows tangent edges).
- [x] Timeline: drag the rollback marker; drag features to reorder (blue drop bar; refused if it breaks a feature); right-click Edit Feature / Edit Profile Sketch / Suppress / Delete / Roll History Marker Here / Roll to End. Not yet: feature groups, playback buttons.

### Sketch
- [x] Line tool: click-drag from an end makes a tangent arc; automatic midpoint / perpendicular / parallel / tangent inference; dashed inference lines to points however far away (no constraint added); a point dropped on the sketch's origin axes stays on them (tied to the origin).
- [x] Dimension tool: the dimension follows the cursor after the pick and a click places it (beside a sloped line or point pair: horizontal / vertical, else aligned); dimensions drawn with extension lines, arrows, leaders and angle arcs; the value can be dragged with Select; angle between two lines by clicking both.
- [x] Driven (reference) dimensions, offered when a dimension would over-constrain the sketch: shown in brackets, following the geometry, ignored by the solver.
- [ ] Dimension text drawn along sloped dimension lines (Tessera's text is always level).
- [x] 3-Point Rectangle (square corners kept), 2-Point Circle, 3-Point Circle, 3-Point Arc; clicks on existing geometry stay on the new circle.
- [x] 2-Tangent Circle (placed in the corner by the cursor), 3-Tangent Circle (the one nearest the picks: a triangle's incircle), Overall Slot, Center Point Arc Slot.
- [x] Ellipse (centre, one axis end, the other half axis): a closed profile; points can be kept on it.
- [x] Ellipse dimensions: the Dimension tool gives the half axis the cursor is along (the drawn one, or the other as a radius).
- [x] Sketch text: the Text tool's panel (text, height, angle, font); the letters stand on a point (moves and constrains like any point), are profiles (each letter with its holes) and extrude into solid letters; double-click a text to change it.
- [ ] Text along a path, text box (multi-line, alignment); trim and offset of ellipses; conic curve.
- [x] Rectangular and Circular sketch patterns, Move/Copy (M; turn about the picked curves' middle, Create Copy) and Sketch Scale: pick curves (or start with them selected), Enter, then the values; constraints that still hold come along.
- [x] CREATE panel as split buttons (Rectangle, Circle, Arc, Slot): the button runs the tool it shows, its arrow lists the others.
- [ ] Patterns kept parametric (edit count / spacing later); Project / Include and Intersect; Break.
- [ ] Fully constrained sketches turn black (dark theme: white); under-defined geometry stays blue (partly done).

### Solid
- [ ] Extrude: two arrows for Two Sides (done); thin extrude (done: profiles and open curves); extent To Object for curved faces and bodies; Participant Bodies; Extrude from a sketch curve (open profile -> thin wall).
- [ ] Revolve, Sweep, Loft, Hole, Fillet, Chamfer, Shell, Press Pull: in-canvas manipulators everywhere (rotation ring for Revolve angle, Hole depth arrow, Shell thickness arrow).
- [ ] Hole: thread options (tapped holes); hole types table.
- [ ] Rib, Web, Emboss, Thicken, Boundary Fill, Rule fillet / setback.
- [ ] Combine with Keep Tools (done) and New Component output.
- [ ] Appearance (drag materials onto faces) and Physical Material (affects mass in Properties).

### Navigation and display
- [ ] Orbit around a picked point (Shift + middle on a point); continuous orbit; free orbit vs constrained.
- [ ] Display settings: Visual style (shaded, shaded with hidden edges, wireframe), environment, ground shadow, layout grid.
- [ ] Named views; Home view; Fit (F6) (done); ViewCube corners and edges, drag to orbit.

### Data and files
- [ ] Recent files / Data Panel replacement for local files; Save / Save As versions; Export F3D-like archive of the local design (open format).

## Findings from the videos

Gathered from the captions (the narrators describe each click); `[x]` is built and tested in Tessera.

### Sketch
- [x] Holding Ctrl while sketching turns off snapping and automatic constraints (Day 14).
- [x] Select geometry first (Shift adds), then press a constraint: it applies to the selection and the tool ends (Day 14).
- [x] Right-click a curve, point or constraint: Delete; Normal / Construction toggles the curve (Day 14).
- [x] X turns the selected curves into construction (or back); with nothing selected it switches the drawing mode (Days 1, 14).
- [x] The grid adapts to the zoom and snapping follows it (Snap is on by default).
- [x] Double-click ends a line chain but keeps the Line tool (Day 14).
- [x] P is Project: click a body edge to copy it into the sketch (seen along the sketch normal), or inside a face for all its edges (Days 6, 7, 10, 15, 20). Point has no key, as in the familiar tool.
- [ ] Project: other curve types (splines, tilted circles); Projection Link that follows body changes; points.
- [ ] A is Appearance (Tessera: Arc in the sketch).
- [ ] Intersect (Project / Include menu) puts body edges that cross the sketch plane into it (Days 4, 7).
- [ ] Dragging a circle centre onto a line midpoint (triangle glyph) adds the midpoint constraint on release (Day 14).
- [ ] The constraint toolbar greys out constraints that cannot apply to the selection (Day 14).
- [x] Fully defined sketch shows a lock icon in the Browser (Days 6, 7, 8).
- [x] Fully defined curves change colour (black in the light theme, near-white in the dark one); under-defined stay blue.
- [ ] Circumscribed / inscribed polygon with the side count typed after Tab (Day 6); Text with a draggable box (Day 7: text on a point done, the box not); Centerline linetype (Day 8). (3-point arc: done.)
- [ ] Spline: Enter or the green check commits, Esc deletes an unfinished spline; drag fit points and handles (Days 2, 4).
- [x] Dimension: where the cursor is dragged decides horizontal / vertical / aligned (Day 5).
- [x] Dimensions named d1, d2 ... (model parameters, listed under their sketch in Change Parameters, named on hover) and used in other dimensions and feature values, e.g. d1 / 2 (Day 8).
- [ ] Feature values (extrude distance, fillet radius ...) as named model parameters too; renaming d-parameters.

### Solid
- [x] Rectangular / Circular Pattern of Features picked in the timeline, Extent / Spacing, a drag arrow per direction (Days 1, 5, 8).
- [x] Right-click a flat face > Create Sketch sketches on that face (Days 1, 5, 7).
- [x] Two Sides extrude: an arrow per side.
- [ ] Pattern directions picked as model edges, and an arrow drag before typing values (Day 1).
- [x] Right-click an origin or construction plane in the Browser > Create Sketch (Days 2, 3, 6).
- [x] Thread: Full Length off gives a length arrow and an offset arrow on the cylinder (Days 4, 9).
- [ ] Thread: Modeled checkbox (cosmetic threads), more thread types.
- [x] Hole: click a face (flat or curved) to place it; the hole follows the face normal (Day 6).
- [x] Hole positions show as "N selected" with Clear.
- [ ] Hole: drag the placed centre; snap it to circle centres; dimension it to edges.
- [x] Chamfer types: Equal Distance, Two Distances, Distance and Angle, with Flip (Day 8).
- [ ] Fillet: several radius sets in one fillet (+ in the panel) (Days 8, 9).
- [ ] Sweep path: Chain Selection checkbox, on by default (Day 3); Loft rails (Day 4).
- [ ] Emboss / Deboss (Days 7, 8); Cylinder primitive: pick a plane, click the centre, drag the size (Day 9).
- [x] Click and hold on overlapping geometry opens a "select other" list (Day 6).
- [x] Drag the timeline marker back to insert a feature earlier, then forward again (Day 7).
- [x] Select a feature in the timeline and press Delete (Day 20); right-click > Edit Profile Sketch.
- [ ] Ground / Unground components (thumbtack in the Browser); drag components in the canvas; As-Built Joint (Shift+J); joint limits with drag flags; right-click a joint > Animate / Lock (Day 23).
- [x] V hides / shows the selected bodies, or the Browser item (Day 6).
- [ ] Shift-click a range of bodies in the Browser (Day 7).
- [ ] Appearance (A): drag a material onto a body or onto selected faces (Days 2, 7, 9).
- [ ] Insert > Canvas (reference image) with Calibrate (Day 2).
- [ ] Capture Design History on an imported STEP file; Create Components from Bodies (Day 10).

### Interface
- [x] Space repeats the last command; in a sketch, the last sketch tool after Esc (Day 11).
- [x] Typing in a value box suggests matching parameter names; Enter takes one, Enter again applies (Day 17).
- [ ] Hover a dimension to see its name (d1, d2 ...); click a constraint glyph to see its name in the status bar (Day 13).
- [ ] Fillet selection sets: + adds another set of edges with its own radius (Days 8, 9, 11, 12).
- [ ] Components: the activate radio button in the Browser; Copy / Paste New; Unground from Parent (Days 11, 12, 13, 15).
- [ ] Hold Ctrl over a face to snap to points on it when placing joints (Day 17).
- [x] Marking menu changes with what is under the cursor (Lesson 3).
- [ ] Pin to Toolbar: the ⋮ beside a menu entry adds it to the ribbon (Lesson 3).
- [x] Rename a sketch or body in the Browser: click once to select, again (or F2) to edit (Days 3, 6); timeline right-click > Rename.
