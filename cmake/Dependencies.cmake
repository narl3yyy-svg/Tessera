# Prefer system packages (Kubuntu: nlohmann-json3-dev, pybind11-dev, qt6-base-dev,
# libocct-*-dev); fall back to FetchContent only for header-only libraries.
include(FetchContent)

find_package(nlohmann_json 3.11 QUIET)
if(NOT nlohmann_json_FOUND)
  FetchContent_Declare(nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG        v3.11.3
    GIT_SHALLOW    TRUE)
  FetchContent_MakeAvailable(nlohmann_json)
endif()

if(TSR_WITH_OCCT)
  # OCCT 8.0 is the target; 7.7+ is accepted until Kubuntu packages 8.x.
  # OCCT's version file only accepts an exact minor match, so check by hand.
  find_package(OpenCASCADE REQUIRED CONFIG)
  if(OpenCASCADE_VERSION VERSION_LESS 7.7)
    message(FATAL_ERROR "OpenCASCADE >= 7.7 required, found ${OpenCASCADE_VERSION}")
  endif()
  message(STATUS "OpenCASCADE ${OpenCASCADE_VERSION} at ${OpenCASCADE_DIR}")
endif()

if(TSR_WITH_PYTHON)
  find_package(Python 3.11 REQUIRED COMPONENTS Interpreter Development.Embed)
  find_package(pybind11 2.11 REQUIRED CONFIG)
endif()

if(TSR_WITH_QT)
  find_package(Qt6 6.6 REQUIRED COMPONENTS Core Gui Widgets OpenGL OpenGLWidgets)
  # KDDockWidgets is the target dock system (SPEC/DIVERGENCES.md, P0 item 2).
endif()
