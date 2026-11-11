#pragma once
#include <pybind11/pybind11.h>

namespace tsr::api {
void bindAdsk(pybind11::module_& adsk);  // adsk, adsk.core, adsk.fusion
void bindTsr(pybind11::module_& tsr);    // tessera-only helpers (commands, undo, files)
} // namespace tsr::api
