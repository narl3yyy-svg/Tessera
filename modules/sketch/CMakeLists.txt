find_package(Eigen3 3.3 REQUIRED NO_MODULE)

add_library(tsr_sketch
  src/Sketch.cpp
  src/Solver.cpp
  src/SketchGeometry.cpp
  src/SketchOps.cpp
  src/SketchCurves.cpp
  src/SketchSvg.cpp)
add_library(tsr::sketch ALIAS tsr_sketch)
target_include_directories(tsr_sketch PUBLIC include ${OpenCASCADE_INCLUDE_DIR})
target_link_libraries(tsr_sketch
  PUBLIC  tsr::core TKernel TKMath TKBRep
  PRIVATE Eigen3::Eigen TKG2d TKG3d TKGeomBase TKGeomAlgo TKTopAlgo TKBO TKMesh TKService TKV3d)
set_target_properties(tsr_sketch PROPERTIES POSITION_INDEPENDENT_CODE ON)
