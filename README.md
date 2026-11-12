<h1 align="center">Tessera</h1>

<p align="center"><b>Parametric 3D CAD for Linux, built to feel like Fusion.</b><br>
Native on KDE / Kubuntu · fully offline · no accounts · no cloud · free software (GPL-3.0)</p>

<p align="center"><img src="docs/images/model.png" alt="Tessera with a lofted, swept and press-pulled model" width="860"></p>

Tessera is a desktop CAD application for designing parts: sketch, constrain, extrude, fillet, and change any
dimension later while the whole model updates. The layout, tools, shortcuts and workflow follow Fusion closely, so
people who know Fusion can work in Tessera straight away. Everything runs locally: there is no login, no cloud
storage, no telemetry, and nothing needs the internet once it is installed. Electronics / PCB design is out of
scope.

> **Status: alpha (0.1).** The core modelling workflow works and is tested; many tools are still to come (see
> [Planned](#planned)). Save often and keep backups of important designs.

## Contents

- [Features](#features) · [Install](#install) · [Using Tessera](#using-tessera) · [Planned](#planned)
- [Project layout](#project-layout) · [Development](#development) · [License](#license)

## Features

| Area | What you get |
|---|---|
| **Interface** | Ribbon in the familiar order (CREATE · MODIFY · ASSEMBLE · CONFIGURE · CONSTRUCT · INSPECT · INSERT · SELECT), browser, timeline, ViewCube, navigation bar, command panels inside the canvas, dark and light themes |
| **Sketch** | Line, 2-Point / Center Rectangle, Circle, Arc, Polygon, Slot, Point, construction lines, Trim, Sketch Dimension; on-canvas size boxes (type a value, **Tab**, **Enter**); live sizes; snap to points and grid |
| **Constraints** | Coincident, Horizontal/Vertical, Parallel, Perpendicular, Equal, Tangent, Concentric, Midpoint, Collinear, Symmetry, Fix; blue = free, white/black = fully constrained |
| **Create** | Extrude (one side / two sides / symmetric, distance or through all, start offset, taper), Revolve, Sweep, Loft, Hole (simple / counterbore / countersink), Rectangular and Circular Pattern, Mirror, Box / Cylinder / Sphere / Torus / Cone |
| **Modify** | Press Pull, Fillet, Chamfer, Shell, Combine (join / cut / intersect), Split Body, Move/Copy, Scale, Remove |
| **Construct** | Offset Plane, Plane at Angle, Midplane — usable for sketches, Split Body and Mirror |
| **Inspect** | Measure, Interference, Section Analysis, Center of Mass |
| **Files** | `.tsr` designs; export STEP, IGES, STL, 3MF, OBJ, BREP; insert STEP, IGES, STL, BREP; 3D Print; Capture Image |
| **Parametric** | Every step is in the timeline: double-click to change it and everything after it rebuilds; suppress, delete, unlimited undo |
| **Settings** | Document units (mm default, inches, cm, m), grid spacing and snap, Fusion / SolidWorks / Tinkercad mouse schemes, zoom direction, free or constrained orbit, orthographic or perspective camera |
| **Scripting** | Python with a Fusion-style `adsk` API subset and `tsr` helpers; headless `tessera-cli` |

<p align="center">
<img src="docs/images/sketch-size-boxes.png" alt="Typing a rectangle's size before it is created" width="420">
<img src="docs/images/extrude-panel.png" alt="The Extrude panel" width="420">
</p>

## Install

Kubuntu / Ubuntu 26.04. From the top of the source folder, as your normal user (not `sudo`):

```bash
./install.sh            # build, test and install to /usr/local (asks for sudo only to copy the files)
./install.sh --user     # or install to ~/.local without sudo
./install.sh --deps     # also install missing build packages first
```

Tessera then appears in the application menu under **Graphics**, and `.tsr` files open with it.
To remove it: `./uninstall.sh` (or `./uninstall.sh --user`; `--dry-run` lists the files first).

For a machine without internet access, run `--deps` through a proxy (`APT_PROXY=socks5h://127.0.0.1:1080`) or
install the packages listed in [docs/DEVELOPMENT.md](docs/DEVELOPMENT.md) beforehand. After installation Tessera
never needs the network.

## Using Tessera

| Action | How |
|---|---|
| Orbit / pan / zoom | **Shift + middle drag** / **middle drag** / **wheel** (other schemes in *File → Preferences*) |
| Standard views | Click the ViewCube, or *Views* on the navigation bar; **F6** fits, **Home** resets |
| Sketch | *Create Sketch*, click a plane or flat face, draw, **FINISH SKETCH** |
| Give a shape exact sizes | After the first click type the value, **Tab** to the next box, **Enter** |
| Edit a feature | Double-click it in the timeline (or a sketch in the browser) |
| Command search | **S** |

**Shortcuts:** E Extrude · H Hole · Q Press Pull · F Fillet · M Move/Copy · I Measure · Delete · Ctrl+Z / Ctrl+Y.
**In a sketch:** L Line · R Rectangle · C Circle · A Arc · P Point · D Dimension · T Trim · X Construction ·
Q Select · Esc cancels.

## Planned

Shown greyed out in the menus until they are built. Roughly in order of work; the full checklist is in
[docs/ROADMAP.md](docs/ROADMAP.md) and the known limits of what exists are in
[docs/KNOWN_GAPS.md](docs/KNOWN_GAPS.md).

| Area | Planned |
|---|---|
| **Parameters** | Parameters table; expressions in every value (`width / 2 + 3 mm`) |
| **Sketch** | Offset, Extend, Fillet / Chamfer, Spline, Ellipse, Conic, Text, Mirror and patterns, Project / Include, 3-point shapes, Tangent Arc, Sketch Palette options |
| **Create** | Thread, Coil, Pipe, Rib, Web, Emboss, Thicken, Boundary Fill, Path Pattern, feature patterns |
| **Modify** | Draft, Offset Face, Replace Face, Split Face, Align, Appearance, Physical Material |
| **Extrude** | Drag arrow in the canvas, To Object / To Face, thin walls |
| **Construct** | Tangent Plane, Plane Through Points, Axis, Point |
| **Assemble** | Components, Joints, As-Built Joints, Rigid Groups, Drive Joints, Motion Links, Contact Sets |
| **Inspect** | Curvature Comb, Zebra, Draft and Curvature Map analysis, Minimum Radius |
| **Insert** | SVG / DXF, Canvas, Decal |
| **Workspaces** | Surface, Mesh, Sheet Metal, Plastic, Manage, Utilities; Drawings; CAM; Simulation; Render |
| **Files** | DXF export of sketches, named views |

**Not planned:** cloud storage or collaboration, user accounts and logins, telemetry, electronics / PCB design.

## Project layout

```
tessera/
├── modules/            C++ source, one library per layer
│   ├── core/           units, command framework, ZIP container (no CAD dependencies)
│   ├── kernel/         OpenCASCADE wrapper: solids, booleans, fillets, file import/export
│   ├── sketch/         sketch model, constraint solver, profiles
│   ├── doc/            the design document: features, timeline, undo, .tsr files, all commands
│   ├── api/            embedded Python (adsk / tsr modules) and tessera-cli
│   └── app/            the Qt application: window, ribbon, canvas, sketch editor, dialogs
├── tests/              unit, integration, Python API and GUI tests (run with ctest)
├── examples/           example Python scripts that build models
├── docs/               roadmap, known gaps, architecture and development guides
├── packaging/          desktop entry, icon, MIME type for .tsr
├── cmake/  scripts/    build helpers
└── install.sh  uninstall.sh
```

Read [docs/ARCHITECTURE.md](docs/ARCHITECTURE.md) for how the pieces fit together.

## Development

```bash
scripts/build.sh                       # configure, build and run all tests in build/
build/modules/app/tessera              # run from the build tree
build/modules/api/tessera-cli --help   # headless scripting
```

Adding a tool, the test layout and the conventions are in [docs/DEVELOPMENT.md](docs/DEVELOPMENT.md).

## License

GPL-3.0-or-later. See [LICENSE](LICENSE). Tessera is an independent project and is not affiliated with Autodesk;
"Fusion" is mentioned only to describe the workflow Tessera follows.
