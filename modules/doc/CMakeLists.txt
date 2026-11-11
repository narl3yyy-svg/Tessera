add_library(tsr_doc
  src/Document.cpp
  src/TsrFile.cpp
  src/DocCommands.cpp
  src/Session.cpp)
add_library(tsr::doc ALIAS tsr_doc)
target_include_directories(tsr_doc PUBLIC include)
target_link_libraries(tsr_doc
  PUBLIC  tsr::core tsr::kernel tsr::sketch TKLCAF TKCAF TKCDF
  PRIVATE TKBin TKBinL)
set_target_properties(tsr_doc PROPERTIES POSITION_INDEPENDENT_CODE ON)
