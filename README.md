# Tessera

*Precision, joined.* A native parametric CAD application for KDE/Kubuntu, built on OpenCASCADE.

Status: **P0 skeleton** (`0.1.0-alpha`). See `SPEC/DIVERGENCES.md` for every known gap.

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

Only the dependency-free core: `cmake -B build-core -DTSR_WITH_OCCT=OFF -DTSR_WITH_PYTHON=OFF -DTSR_WITH_QT=OFF`.

## Layout

| Path | Contents |
|---|---|
| `modules/core` | units, command framework (metadata, session, registry), ZIP container, logging. No OCCT/Qt. |
| `modules/kernel` | OCCT wrapper. Only value types and `TopoDS_Shape` cross this boundary. |
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
