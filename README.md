# Tessera

*Precision, joined.* A native parametric CAD application for KDE/Kubuntu, built on OpenCASCADE.

Status: **P2, early alpha** (`0.1.0-alpha`). What works today:

- 3D viewport with ViewCube, layout grid, shaded/edges/wireframe styles, standard views and fit/home
- Navigation: middle-drag pans, Shift+middle-drag orbits, wheel zooms at the cursor, left click/drag selects
- **Sketching**: Create Sketch on an origin plane or a flat face; Line (L), Rectangle (R), Circle (C), Arc (A),
  Point (P), construction geometry (X); auto horizontal/vertical; snapping to points
- **Constraints and dimensions**: coincident, horizontal/vertical, parallel, perpendicular, equal, tangent,
  concentric, midpoint, fix; Sketch Dimension (D) for lengths, distances, diameters, radii and angles, edited by
  double-clicking. Blue = free, black = fully constrained. Drag geometry with Select (Q).
- **Extrude (E)**: click the profiles to extrude, one side or symmetric, New Body / Join / Cut / Intersect
- **Revolve**: turn profiles about the sketch's X/Y axis, a construction line, or a world axis; full or partial,
  one side or symmetric
- **Fillet (F)** and **Chamfer**: click edges in the canvas (smoothly connected edges follow); picked edges are found
  again after you change earlier features
- Change a sketch dimension later and every extrude built on it updates
- Box, Cylinder, Sphere, Torus and Cone with New Body / Join / Cut / Intersect, target body picked by clicking it
- Parametric timeline: double-click a feature to change it and everything after it replays; suppress, delete, undo
- Browser (bodies with visibility, origin, parameters), command search (`S`), right-click menu with Repeat
- Ribbon laid out like Fusion: CREATE, MODIFY, ASSEMBLE, CONFIGURE, CONSTRUCT, INSPECT, INSERT, SELECT (planned items
  shown greyed); command panels open inside the canvas
- MODIFY: Fillet (F), Chamfer, Shell, Combine, Split Body, Move/Copy (M), Scale, Remove; CREATE also has Mirror
- INSPECT: Measure (I), Interference, Section Analysis, Center of Mass; INSERT: STEP/IGES/STL/BREP files
- File: Export (STEP, IGES, STL, 3MF, OBJ, BREP, .tsr), 3D Print, Capture Image, Preferences
- Document Settings > Units (mm default, inches, cm, m); typed values while sketching (e.g. 30, 40 x 20) with live
  sizes; grid settings and snap to grid; navigation presets (Fusion / SolidWorks / Tinkercad), orbit type, camera
- Dark theme by default (Display > Dark theme switches to light; remembered between runs)
- `.tsr` files, unlimited practical undo, Python scripting (`tsr.*` and the start of the `adsk.*` API)

Sketching works the way Fusion users expect: after the first click the size boxes appear next to the shape; type
a value, **Tab** to the next box, **Enter** to create it (typed sizes become dimensions). Tools: Line, 2-Point and
Center Rectangle, Circle, Arc, Polygon, Slot, Point, Trim, Sketch Dimension and 11 constraints (including Collinear
and Symmetry). CREATE also has **Hole** (H; simple, counterbore, countersink, at sketch points) and **Rectangular /
Circular Pattern**.

## Planned

Not built yet (menus show these greyed out). Order is roughly the order of work; `ROADMAP.md` has the full checklist.

| Area | Planned |
|---|---|
| Construct | Offset Plane, Plane at Angle, Midplane, Tangent Plane, Axis (cylinder / edge / two points), Point — usable for sketches, Split and Mirror |
| Create | Sweep, Loft, Coil, Pipe, Thread, Rib, Web, Emboss, Thicken, Boundary Fill, Path Pattern, feature patterns |
| Modify | Press Pull (Q), Draft, Offset Face, Replace Face, Split Face, Align, Appearance (A), Physical Material, Change Parameters table |
| Sketch | Extend, Offset (O), sketch Fillet/Chamfer, Spline, Ellipse, Conic, Text, Mirror, Circular/Rectangular sketch patterns, Project/Include (P), Midpoint Line, 3-Point Rectangle/Circle/Arc, Tangent Arc, Sketch Palette (show/hide options, slice), Curvature/Polygon constraints |
| Extrude | Drag arrow in the canvas, To Object / To Face extents, thin extrude |
| Parameters | Expressions and parameter names in every value (`width/2 + 3 mm`) |
| Assemble | Components, Joints (J), As-Built Joints, Rigid Groups, Drive Joints, Motion Links, Contact Sets |
| Inspect | Curvature Comb, Zebra, Draft and Curvature Map analysis, Minimum Radius |
| Insert | SVG / DXF, Canvas, Decal |
| Other workspaces | Surface, Mesh, Sheet Metal, Plastic, Manage, Utilities; Drawings; CAM; Simulation; Render |
| Files | DXF export of sketches; named views; design history tools |

See `ROADMAP.md` for the phases and `SPEC/DIVERGENCES.md` for every known gap in what is already built.

## Install (Kubuntu 26.04)

From the top of the checkout, as your normal user (not `sudo`):

```bash
./install.sh            # build, test, install to /usr/local (sudo only for the copy step)
./install.sh --user     # or install to ~/.local without sudo
./install.sh --deps     # also apt-install missing build packages (APT_PROXY=socks5h://... if offline)
```

Tessera then appears in the KDE menu under Graphics, `.tsr` files open with it, and `tessera` / `tessera-cli` are on
the PATH. Remove it with `./uninstall.sh` (or `./uninstall.sh --user`); `--dry-run` lists the files first. Only files the
installer recorded are removed, never your designs.

## Build for development

```bash
sudo apt install -y build-essential cmake ninja-build qt6-base-dev \
  libocct-foundation-dev libocct-modeling-data-dev libocct-modeling-algorithms-dev \
  libocct-ocaf-dev libocct-visualization-dev libocct-data-exchange-dev \
  pybind11-dev python3-dev nlohmann-json3-dev libeigen3-dev libtbb-dev
scripts/build.sh            # configure + build + ctest in build/
```

Run: `build/modules/app/tessera [file.tsr]`. Headless: `build/modules/api/tessera-cli --help`.
Screenshot a scripted model: `tessera --script tests/gui/demo_model.py --screenshot out.png`.

Only the dependency-free core: `cmake -B build-core -DTSR_WITH_OCCT=OFF -DTSR_WITH_PYTHON=OFF -DTSR_WITH_QT=OFF`.

## Layout

| Path | Contents |
|---|---|
| `modules/core` | units, command framework (metadata, session, registry), ZIP container, logging. No OCCT/Qt. |
| `modules/kernel` | OCCT wrapper. Only value types and `TopoDS_Shape` cross this boundary. |
| `modules/sketch` | Sketch model and JSON format, the constraint solver (Eigen), profiles and plane frames (OCCT). |
| `modules/doc` | OCAF document, transactions/undo, `.tsr` save/load, P0 commands, `Session`. |
| `modules/api` | Embedded CPython: `adsk.core` / `adsk.fusion` shim, `tsr` helpers, `tessera-cli`. |
| `modules/app` | Qt shell: ribbon, browser and dialogs generated from command metadata. |
| `tests/` | unit (core), integration (doc+kernel), api (Python scripts via `tessera-cli`), gui smoke. |
| `SPEC/`, `EVIDENCE/`, `PARITY/` | Specifications, evidence ledger, parity harness. |

The other modules in the plan (view, sketch, assembly, draw, cam, sim, render, io) get added in the phase that needs them.

## Adding a command

1. Subclass `tsr::Command` and fill its `CommandDef` (id, name, tab, panel, inputs with units/ranges).
2. Implement `apply()` (runs inside a transaction) and optionally `validate()`.
3. Register it. The ribbon button, the dialog, `tsr.run_command(...)` and undo all follow automatically.

## P0 exit criteria (plan §6)

| Criterion | Covered by |
|---|---|
| Launches on Kubuntu | `gui_smoke` (offscreen) and a manual launch |
| Create/open/save `.tsr` | `integration` (`doc_tsr_round_trip`), `api_user_parameters` |
| OCAF undo/redo | `integration`, `api_commands`, `gui_smoke` |
| Ribbon and browser tree from command metadata | `gui_smoke` |
| A command round-trips through API and UI | `api_commands` and `gui_smoke` use the same `tsr.primitive.box` |

## License

GPL-3.0-or-later. See `LICENSE`.
