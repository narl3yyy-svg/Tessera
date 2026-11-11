cmake_minimum_required(VERSION 3.28)
project(Tessera VERSION 0.1.0 LANGUAGES CXX)
set(TSR_VERSION_STRING "0.1.0-alpha")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Layered build: core is dependency-free (besides nlohmann_json) so the command
# framework and container format can be built/tested anywhere. Everything above
# it needs OCCT / Qt / Python and is switched on by default for real builds.
option(TSR_WITH_OCCT   "Build kernel + doc (OpenCASCADE)"        ON)
option(TSR_WITH_PYTHON "Build api (embedded CPython + adsk shim)" ON)
option(TSR_WITH_QT     "Build the Qt application shell"           ON)
option(TSR_BUILD_TESTS "Build tests"                              ON)

if(TSR_WITH_PYTHON AND NOT TSR_WITH_OCCT)
  message(FATAL_ERROR "TSR_WITH_PYTHON requires TSR_WITH_OCCT")
endif()
if(TSR_WITH_QT AND NOT TSR_WITH_PYTHON)
  message(FATAL_ERROR "TSR_WITH_QT requires TSR_WITH_PYTHON (every UI command must be API-callable)")
endif()

include(cmake/Dependencies.cmake)

if(MSVC)
  add_compile_options(/W4 /permissive-)
else()
  # Designated initializers deliberately omit defaulted members (InputDef).
  add_compile_options(-Wall -Wextra -Wpedantic -Wno-missing-field-initializers)
endif()

add_subdirectory(modules/core)
if(TSR_WITH_OCCT)
  add_subdirectory(modules/kernel)
  add_subdirectory(modules/doc)
endif()
if(TSR_WITH_PYTHON)
  add_subdirectory(modules/api)
endif()
if(TSR_WITH_QT)
  add_subdirectory(modules/app)
endif()

if(TSR_BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()
