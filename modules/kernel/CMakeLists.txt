add_library(tsr_kernel src/Kernel.cpp)
add_library(tsr::kernel ALIAS tsr_kernel)
target_include_directories(tsr_kernel PUBLIC include ${OpenCASCADE_INCLUDE_DIR})
# Kernel boundary (plan §4.2): only value types and TopoDS_Shape cross it.
target_link_libraries(tsr_kernel
  PUBLIC  tsr::core TKernel TKMath TKBRep
  PRIVATE TKG3d TKGeomBase TKTopAlgo TKPrim TKBO TKBool TKShHealing TKFillet)
set_target_properties(tsr_kernel PROPERTIES POSITION_INDEPENDENT_CODE ON)
