find_package(Eigen3 3.3 REQUIRED NO_MODULE)

add_library(tsr_sketch
  src/Sketch.cpp
  src/Solver.cpp
  src/SketchGeometry.cpp)
add_library(tsr::sketch ALIAS tsr_sketch)
target_include_directories(tsr_sketch PUBLIC include ${OpenCASCADE_INCLUDE_DIR})
target_link_libraries(tsr_sketch
  PUBLIC  tsr::core TKernel TKMath TKBRep
  PRIVATE Eigen3::Eigen TKG2d TKG3d TKGeomBase TKTopAlgo TKBO TKMesh)
set_target_properties(tsr_sketch PROPERTIES POSITION_INDEPENDENT_CODE ON)
