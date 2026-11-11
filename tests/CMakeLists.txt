add_executable(tsr_unit_tests
  unit/main.cpp
  unit/test_units.cpp
  unit/test_command.cpp
  unit/test_zip.cpp)
target_include_directories(tsr_unit_tests PRIVATE .)
target_link_libraries(tsr_unit_tests PRIVATE tsr::core)
add_test(NAME unit COMMAND tsr_unit_tests)

if(TSR_WITH_OCCT)
  add_executable(tsr_integration_tests
    unit/main.cpp
    integration/test_document.cpp)
  target_include_directories(tsr_integration_tests PRIVATE .)
  target_link_libraries(tsr_integration_tests PRIVATE tsr::doc)
  add_test(NAME integration COMMAND tsr_integration_tests)
  set_tests_properties(integration PROPERTIES WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
endif()

if(TSR_WITH_PYTHON)
  # Same API path real Fusion scripts use; also round-trips a .tsr.
  add_test(NAME api_user_parameters
           COMMAND tessera-cli --script ${CMAKE_CURRENT_SOURCE_DIR}/api/test_user_parameters.py
                               --save ${CMAKE_CURRENT_BINARY_DIR}/api_out.tsr
                               --open ${CMAKE_CURRENT_BINARY_DIR}/api_out.tsr
                               --script ${CMAKE_CURRENT_SOURCE_DIR}/api/check_reopened.py)
  add_test(NAME api_commands
           COMMAND tessera-cli --script ${CMAKE_CURRENT_SOURCE_DIR}/api/test_commands.py)
endif()

if(TSR_WITH_QT)
  add_test(NAME gui_smoke COMMAND tessera --smoke)
  set_tests_properties(gui_smoke PROPERTIES ENVIRONMENT "QT_QPA_PLATFORM=offscreen")
endif()
