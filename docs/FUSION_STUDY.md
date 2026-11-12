# Fusion study list

Tessera aims to work the way Fusion users expect. This file tracks (1) the tutorial videos to study and (2) the
behaviours found there that Tessera does not match yet. Each finding moves to `docs/ROADMAP.md` or
`docs/KNOWN_GAPS.md` once it is built or scheduled.

## Videos

| # | Video | Studied |
|---|---|---|
| 1 | https://www.youtube.com/watch?v=d3qGQ2utl2A | |
| 2 | https://www.youtube.com/watch?v=DfAfxae8aRc | |
| 3 | https://www.youtube.com/watch?v=ZReXmjT42DM | |
| 4 | https://www.youtube.com/watch?v=9Y-3W-Pr64U | |
| 5 | https://www.youtube.com/watch?v=zN44hW9zX1I | |
| 6 | https://www.youtube.com/watch?v=AfeCRrYsAys | |
| 7 | https://www.youtube.com/watch?v=Mv54UfwYYos | |
| 8 | https://www.youtube.com/watch?v=o5rcAv7xVUo | |
| 9 | https://www.youtube.com/watch?v=2YaMulL4dZY | |
| 10 | https://www.youtube.com/watch?v=BUH3WiUjMXw | |
| 11 | https://www.youtube.com/watch?v=pa6VWGFoZ2Q | |
| 12 | https://www.youtube.com/watch?v=J3rPwne4lWY | |
| 13 | https://www.youtube.com/watch?v=zLL6foqTdJg | |
| 14 | https://www.youtube.com/watch?v=xmAGzRBDccs | |
| 15 | https://www.youtube.com/watch?v=QnDJl9W5Uso | |
| 16 | https://www.youtube.com/watch?v=vr_zPVEsyjs | |
| 17 | https://www.youtube.com/watch?v=DJULiA1aTtM | |
| 18 | https://www.youtube.com/watch?v=fYDJLdOV_zE | |
| 19 | https://www.youtube.com/watch?v=smbb4rJPBGg | |
| 20 | https://www.youtube.com/watch?v=Q1Thdrt40MA | |
| 21 | https://www.youtube.com/watch?v=OsdL0VoaGl0 | |
| 22 | https://www.youtube.com/watch?v=5PsR8bL-Wv4 | |
| 23 | https://www.youtube.com/watch?v=EzJMWLX0IbU | |
| 24 | https://www.youtube.com/watch?v=WtEWbNIaK9Q | |
| 25 | https://www.youtube.com/watch?v=NqjbJZ2ekRU | |
| 26 | https://www.youtube.com/watch?v=ShmSm9vjKpI | |
| 27 | https://www.youtube.com/watch?v=NweBvuVYuQo | |
| 28 | https://www.youtube.com/watch?v=ePEypa1kB-g | |
| 29 | Playlist: https://www.youtube.com/playlist?list=PLLm7Yjr9z_z07ohtjFGkA5w-j_NMj8B3J (every video) | |
| 30 | Autodesk tutorial index: https://www.autodesk.com/solutions/design-manufacturing/fusion-tutorials | |

## Known differences still to build

Behaviour already known to differ, before the videos; findings from the videos are added below it.

### Selection and the canvas
- [ ] Window selection left-to-right (fully inside) vs right-to-left (crossing); selection priority (bodies / faces / edges / sketch) and the select-through hold.
- [ ] Marking menu (right-click radial menu) with Repeat, Undo, Sketch, Extrude, Hole, Press Pull, Fillet, Move/Copy.
- [ ] Pre-selection: selected items carried into the next command (select a face, then press E).
- [ ] Hovering a body shows its name tooltip; double-click selects a tangent chain / loop.
- [ ] Timeline: drag the rollback marker; drag features to reorder; right-click Edit Feature / Edit Profile Sketch / Suppress / Delete; feature groups.

### Sketch
- [ ] Line tool: click-drag from an end makes a tangent arc (done); automatic midpoint / perpendicular / parallel / tangent inference (done); dashed inference lines to points far away; snap to the sketch's own projected origin axes.
- [ ] Dimension tool: placing a dimension follows the cursor before the click; driven (reference) dimensions; angular dimension between lines by clicking both.
- [ ] Sketch text, ellipse, conic, 3-point rectangle / circle / arc, tangent circle, centre-point arc slot, overall slot.
- [ ] Rectangular and circular sketch patterns; Project / Include and Intersect; Break; Sketch Scale; Move/Copy in the sketch.
- [ ] Fully constrained sketches turn black (dark theme: white); under-defined geometry stays blue (partly done).

### Solid
- [ ] Extrude: two arrows for Two Sides; thin extrude; extent To Object for curved faces and bodies; Participant Bodies; Extrude from a sketch curve (open profile -> thin wall).
- [ ] Revolve, Sweep, Loft, Hole, Fillet, Chamfer, Shell, Press Pull: in-canvas manipulators everywhere (rotation ring for Revolve angle, Hole depth arrow, Shell thickness arrow).
- [ ] Hole: place on a face by clicking points; thread options; hole types table.
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

(added as each video is studied)
