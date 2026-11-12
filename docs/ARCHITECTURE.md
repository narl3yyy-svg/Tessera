# Architecture

Tessera is a C++20 application in layers; each layer only depends on the ones below it.

```
app (Qt)  ──►  api (Python)  ──►  doc  ──►  sketch  ──►  kernel  ──►  core
                                   │                       │
                                   └──── OCAF (OCCT) ──────┘
```

| Module | Responsibility | Key files |
|---|---|---|
| `core` | Units, quantity parsing and the expression evaluator, the command framework (`CommandDef`, `InputDef`, `CommandSession`, `CommandRegistry`), ZIP container. No CAD or GUI code. | `Command.h`, `Units.h`, `Expression.h`, `Zip.h` |
| `kernel` | Everything that calls OpenCASCADE modelling: primitives, booleans, extrude/revolve/sweep/loft, fillet/chamfer/shell, press pull, edge and face references, measurement, file import/export. Only `TopoDS_Shape` and plain values cross this boundary. | `Kernel.h`, `Io.h` |
| `sketch` | Sketch geometry and JSON format, the constraint solver (Gauss-Newton, minimum-norm steps, degree-of-freedom analysis), sketch planes, profiles (closed regions). | `Sketch.h`, `Solver.cpp`, `SketchGeometry.h` |
| `doc` | The design document on OCAF: bodies, sketches, construction planes, the feature timeline, recompute, undo, `.tsr` files, and every command. `Session` holds the registry and the active document. | `Document.h`, `DocCommands.cpp`, `Session.h` |
| `api` | Embedded Python: `adsk.core` / `adsk.fusion` subset and `tsr` helpers; `tessera-cli` for scripts and tests. | `AdskModule.cpp`, `TsrModule.cpp` |
| `app` | The Qt window: ribbon, browser, timeline, OCCT viewport, sketch editor, command panels, tools (measure, section, export), theme and icons. | `MainWindow*.cpp`, `Viewport*.cpp`, `SketchEditor.cpp` |

## How a command works

1. A command is a class with a `CommandDef` (id, name, panel, icon, shortcut, inputs with units, ranges and
   visibility rules) and `validate()` / `prepare()` / `apply()`.
2. The ribbon button, the in-canvas panel, the Python call `tsr.run_command(id, ...)` and undo are all generated
   from that definition.
3. Feature commands (`CommandDef::feature`) are recorded in the timeline with their inputs. Editing a feature
   replaces its inputs and **recompute** replays the whole timeline, so later features follow.
   A Real/Integer input given as text (`"width / 2"`) is evaluated against the user parameters and the text is kept
   under the key `=<input id>`; recompute evaluates it again before replaying the feature, and sketch dimensions
   keep theirs in the sketch JSON (`expr`). Changing a parameter re-evaluates all parameters (cycles are rejected)
   and recomputes, as one undo step.
4. `prepare()` fills in derived inputs before they are recorded: generated names, the sketch or body meant, and
   signatures for picked edges and faces so they can be found again after earlier features change.

## The document

`.tsr` is a ZIP with `manifest.json`, `document/ocaf.xbf` (the OCAF document) and a readable `params.json`.
OCAF label layout is documented at the top of `Document.h`. Bodies, sketches and planes are results of the
features and are rebuilt by recompute; features and their inputs are the source of truth.

## Units

Internally lengths are centimetres and angles radians (the same as the `adsk` API). The document's display unit
(mm by default) is applied only when showing or parsing values. Exported files are written in millimetres.
