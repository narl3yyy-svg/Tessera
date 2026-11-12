# Development

## Build

Packages (Kubuntu / Ubuntu 26.04):

```bash
sudo apt install -y build-essential cmake ninja-build qt6-base-dev \
  libocct-foundation-dev libocct-modeling-data-dev libocct-modeling-algorithms-dev \
  libocct-ocaf-dev libocct-visualization-dev libocct-data-exchange-dev \
  pybind11-dev python3-dev nlohmann-json3-dev libeigen3-dev libtbb-dev
```

```bash
scripts/build.sh            # configure + build + ctest in build/ (RelWithDebInfo)
```

The build must have **zero compiler warnings**. Only the dependency-free core:
`cmake -B build-core -DTSR_WITH_OCCT=OFF -DTSR_WITH_PYTHON=OFF -DTSR_WITH_QT=OFF`.

## Tests

| Test | What it covers |
|---|---|
| `unit` | units, expressions, command framework, ZIP |
| `sketch` | solver, constraints, profiles, sketch editing operations |
| `integration` | document, features, kernel operations, `.tsr` round trips |
| `api_*` | Python scripts in `tests/api/` run through `tessera-cli`, one per feature area |
| `gui_smoke` | the real window driven through commands, sketch mode and panels (offscreen) |
| `gui_render` | an OpenGL render of `examples/demo_model.py` under `xvfb-run` |
| `live_*` | the real app on Xvfb driven by real X11 mouse and keyboard input (`scripts/xdrive.py`, XTest), the saved design then checked with a Python script; scripts in `tests/live/` |

Live tests: `scripts/live-test.sh tests/live/<name>.drive [setup.py] [check.py]`. The app runs with
`--live-geometry FILE`, which keeps writing where its named widgets, the canvas, the drag arrow, the origin planes
(while picking) and the open sketch are on screen, so a `.drive` script can say `click tsr.feature.extrude`,
`sclick 40 0` (sketch mm), `adrag 0 -120` (the arrow) or `plane XY`; `shot FILE` saves a screenshot. Needs
`xvfb-run` and libXtst (no other packages).

Screenshots for visual checks: `tessera --script examples/<demo>.py --screenshot out.png`; add
`--start-command <id>`, `--edit-sketch <name>` or `--demo-hud` to show a panel, sketch mode or the size boxes.
On a headless machine run it inside `kwin_wayland --virtual --xwayland --exit-with-session <script>`.

## Adding a tool

1. In `modules/doc/src/DocCommands.cpp`, add a `Command` subclass: fill `CommandDef` (id `tsr.feature.<name>`,
   name, tooltip, panel, icon, shortcut, `feature = true` for timeline steps) and its inputs. Use
   `visibleWhen` for inputs that only apply to some options.
2. Put the geometry in `modules/kernel` so it can be tested without the document.
3. Register it in `registerDocCommands`; the ribbon, panel, Python and undo follow automatically.
4. Paint an icon in `modules/app/src/Icons.cpp` (original artwork only).
5. Add an `api_*` test and, for interactive behaviour, a step in the GUI smoke test (`modules/app/src/main.cpp`).
6. Record any limitation in `docs/KNOWN_GAPS.md` and tick the item in `docs/ROADMAP.md`.

## Conventions

- C++20, Qt 6, OpenCASCADE 7.9; 2-space indent, 120 columns.
- Internal units: cm and radians. Display units come from the document.
- Everything works offline. No network access, accounts or telemetry.
- Artwork and icons are drawn in code or made for this project; never copied from other products.
- Git: commits are authored as `narl3yyy-svg <283486160+narl3yyy-svg@users.noreply.github.com>` with no
  co-author trailer.
