add_library(tsr_api
  src/PythonHost.cpp
  src/AdskModule.cpp
  src/TsrModule.cpp)
add_library(tsr::api ALIAS tsr_api)
target_include_directories(tsr_api PUBLIC include PRIVATE src)
target_link_libraries(tsr_api PUBLIC tsr::doc PRIVATE pybind11::embed)
set_target_properties(tsr_api PROPERTIES POSITION_INDEPENDENT_CODE ON)

# Headless runner: the scripted-test and parity-harness entry point.
add_executable(tessera-cli src/cli_main.cpp)
target_link_libraries(tessera-cli PRIVATE tsr::api)
