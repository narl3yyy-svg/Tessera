add_library(tsr_core
  src/Units.cpp
  src/Command.cpp
  src/CommandRegistry.cpp
  src/Zip.cpp
  src/Log.cpp)
add_library(tsr::core ALIAS tsr_core)
target_include_directories(tsr_core PUBLIC include)
target_link_libraries(tsr_core PUBLIC nlohmann_json::nlohmann_json)
target_compile_definitions(tsr_core PUBLIC TSR_VERSION_STRING="${TSR_VERSION_STRING}")
set_target_properties(tsr_core PROPERTIES POSITION_INDEPENDENT_CODE ON)
