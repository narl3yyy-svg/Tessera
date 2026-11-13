add_executable(tsr_unit_tests
  unit/main.cpp
  unit/test_units.cpp
  unit/test_expression.cpp
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

  add_executable(tsr_sketch_tests unit/main.cpp sketch/test_sketch.cpp)
  target_include_directories(tsr_sketch_tests PRIVATE .)
  target_link_libraries(tsr_sketch_tests PRIVATE tsr::sketch)
  add_test(NAME sketch COMMAND tsr_sketch_tests)
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
  add_test(NAME api_sketch_extrude
           COMMAND tessera-cli --script ${CMAKE_CURRENT_SOURCE_DIR}/api/test_sketch_extrude.py)
  add_test(NAME api_fillet_revolve
           COMMAND tessera-cli --script ${CMAKE_CURRENT_SOURCE_DIR}/api/test_fillet_revolve.py)
  add_test(NAME api_modify
           COMMAND tessera-cli --script ${CMAKE_CURRENT_SOURCE_DIR}/api/test_modify.py)
  add_test(NAME api_io_units
           COMMAND tessera-cli --script ${CMAKE_CURRENT_SOURCE_DIR}/api/test_io_units.py)
  add_test(NAME api_hole_pattern
           COMMAND tessera-cli --script ${CMAKE_CURRENT_SOURCE_DIR}/api/test_hole_pattern.py)
  # Reference parts (tests/oracle): every case that passes today must keep passing.
  add_test(NAME oracle
           COMMAND tessera-cli --script ${CMAKE_CURRENT_SOURCE_DIR}/oracle/run_oracle.py)
  set_tests_properties(oracle PROPERTIES TIMEOUT 900 ENVIRONMENT
                       "TSR_ORACLE_CASES=${CMAKE_CURRENT_SOURCE_DIR}/oracle/cases;TSR_ORACLE_REQUIRE_FILE=${CMAKE_CURRENT_SOURCE_DIR}/oracle/required.txt")
  add_test(NAME api_thin_extrude
           COMMAND tessera-cli --script ${CMAKE_CURRENT_SOURCE_DIR}/api/test_thin_extrude.py)
  add_test(NAME api_rename
           COMMAND tessera-cli --script ${CMAKE_CURRENT_SOURCE_DIR}/api/test_rename.py)
  add_test(NAME api_timeline
           COMMAND tessera-cli --script ${CMAKE_CURRENT_SOURCE_DIR}/api/test_timeline.py)
  add_test(NAME api_chamfer_types
           COMMAND tessera-cli --script ${CMAKE_CURRENT_SOURCE_DIR}/api/test_chamfer_types.py)
  add_test(NAME api_feature_pattern
           COMMAND tessera-cli --script ${CMAKE_CURRENT_SOURCE_DIR}/api/test_feature_pattern.py)
  add_test(NAME api_construct
           COMMAND tessera-cli --script ${CMAKE_CURRENT_SOURCE_DIR}/api/test_construct.py)
  add_test(NAME api_sweep_loft_presspull
           COMMAND tessera-cli --script ${CMAKE_CURRENT_SOURCE_DIR}/api/test_sweep_loft_presspull.py)
  add_test(NAME api_parameters_expressions
           COMMAND tessera-cli --script ${CMAKE_CURRENT_SOURCE_DIR}/api/test_parameters_expressions.py
                               --save ${CMAKE_CURRENT_BINARY_DIR}/api_params.tsr
                               --open ${CMAKE_CURRENT_BINARY_DIR}/api_params.tsr
                               --script ${CMAKE_CURRENT_SOURCE_DIR}/api/check_parameters_reopened.py)
  add_test(NAME api_extrude_faces
           COMMAND tessera-cli --script ${CMAKE_CURRENT_SOURCE_DIR}/api/test_extrude_faces.py)
  add_test(NAME api_sketch_tools
           COMMAND tessera-cli --script ${CMAKE_CURRENT_SOURCE_DIR}/api/test_sketch_tools.py)
  add_test(NAME api_construct_axes_points
           COMMAND tessera-cli --script ${CMAKE_CURRENT_SOURCE_DIR}/api/test_construct_axes_points.py)
  add_test(NAME api_pipe_coil
           COMMAND tessera-cli --script ${CMAKE_CURRENT_SOURCE_DIR}/api/test_pipe_coil.py)
  add_test(NAME api_offset_face_draft
           COMMAND tessera-cli --script ${CMAKE_CURRENT_SOURCE_DIR}/api/test_offset_face_draft.py)
  add_test(NAME api_thread
           COMMAND tessera-cli --script ${CMAKE_CURRENT_SOURCE_DIR}/api/test_thread.py)
  add_test(NAME api_assembly
           COMMAND tessera-cli --script ${CMAKE_CURRENT_SOURCE_DIR}/api/test_assembly.py)
  add_test(NAME api_sketch_more
           COMMAND tessera-cli --script ${CMAKE_CURRENT_SOURCE_DIR}/api/test_sketch_more.py)
  add_test(NAME api_extrude_to_object
           COMMAND tessera-cli --script ${CMAKE_CURRENT_SOURCE_DIR}/api/test_extrude_to_object.py)
  add_test(NAME api_features
           COMMAND tessera-cli --script ${CMAKE_CURRENT_SOURCE_DIR}/api/test_features.py)
endif()

if(TSR_WITH_QT)
  add_test(NAME gui_smoke COMMAND tessera --smoke)
  set_tests_properties(gui_smoke PROPERTIES ENVIRONMENT "QT_QPA_PLATFORM=offscreen")
  # Real OpenGL rendering of a model on a virtual X server, when available.
  find_program(XVFB_RUN xvfb-run)
  if(XVFB_RUN)
    add_test(NAME gui_render
             COMMAND ${XVFB_RUN} -a -s "-screen 0 1600x1000x24"
                     $<TARGET_FILE:tessera> --script ${PROJECT_SOURCE_DIR}/examples/demo_model.py
                                            --screenshot ${CMAKE_CURRENT_BINARY_DIR}/gui_render.png)
    set_tests_properties(gui_render PROPERTIES ENVIRONMENT "QT_QPA_PLATFORM=xcb;LIBGL_ALWAYS_SOFTWARE=1")
    # Live tests: the real app on Xvfb driven by real X11 mouse/keyboard input
    # (scripts/xdrive.py, XTest), with the saved design checked afterwards.
    add_test(NAME live_line_tool
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/line_tool.drive ""
                          ${CMAKE_CURRENT_SOURCE_DIR}/live/line_tool_check.py)
    add_test(NAME live_extrude_section
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/extrude_arrow.drive
                          ${CMAKE_CURRENT_SOURCE_DIR}/live/setup_rect_sketch.py ${CMAKE_CURRENT_SOURCE_DIR}/live/extrude_arrow_check.py)
    add_test(NAME live_sketch_modify
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/sketch_modify.drive ""
                          ${CMAKE_CURRENT_SOURCE_DIR}/live/sketch_modify_check.py)
    add_test(NAME live_to_object
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/to_object.drive
                          ${CMAKE_CURRENT_SOURCE_DIR}/live/setup_to_object.py ${CMAKE_CURRENT_SOURCE_DIR}/live/to_object_check.py)
    add_test(NAME live_face_extrude
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/face_extrude.drive
                          ${CMAKE_CURRENT_SOURCE_DIR}/live/setup_face_extrude.py ${CMAKE_CURRENT_SOURCE_DIR}/live/face_extrude_check.py)
    add_test(NAME live_marking_menu
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/marking_menu.drive
                          ${CMAKE_CURRENT_SOURCE_DIR}/live/setup_face_extrude.py ${CMAKE_CURRENT_SOURCE_DIR}/live/marking_menu_check.py)
    add_test(NAME live_assembly
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/assembly.drive
                          ${CMAKE_CURRENT_SOURCE_DIR}/live/setup_assembly.py ${CMAKE_CURRENT_SOURCE_DIR}/live/assembly_check.py)
    add_test(NAME live_two_sides
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/two_sides.drive
                          ${CMAKE_CURRENT_SOURCE_DIR}/live/setup_rect_sketch.py ${CMAKE_CURRENT_SOURCE_DIR}/live/two_sides_check.py)
    add_test(NAME live_feature_pattern
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/feature_pattern.drive
                          ${CMAKE_CURRENT_SOURCE_DIR}/live/setup_stud_block.py ${CMAKE_CURRENT_SOURCE_DIR}/live/feature_pattern_check.py)
    add_test(NAME live_sketch_habits
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/sketch_habits.drive
                          ${CMAKE_CURRENT_SOURCE_DIR}/live/setup_face_extrude.py ${CMAKE_CURRENT_SOURCE_DIR}/live/sketch_habits_check.py)
    add_test(NAME live_browser_sketch
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/browser_sketch.drive
                          ${CMAKE_CURRENT_SOURCE_DIR}/live/setup_empty.py ${CMAKE_CURRENT_SOURCE_DIR}/live/browser_sketch_check.py)
    add_test(NAME live_value_suggest
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/value_suggest.drive
                          ${CMAKE_CURRENT_SOURCE_DIR}/live/setup_param_rect.py ${CMAKE_CURRENT_SOURCE_DIR}/live/value_suggest_check.py)
    add_test(NAME live_timeline_delete
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/timeline_delete.drive
                          ${CMAKE_CURRENT_SOURCE_DIR}/live/setup_rect_extrude.py ${CMAKE_CURRENT_SOURCE_DIR}/live/timeline_delete_check.py)
    add_test(NAME live_project
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/project.drive
                          ${CMAKE_CURRENT_SOURCE_DIR}/live/setup_face_extrude.py ${CMAKE_CURRENT_SOURCE_DIR}/live/project_check.py)
    add_test(NAME live_thread_arrows
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/thread_arrows.drive
                          ${CMAKE_CURRENT_SOURCE_DIR}/live/setup_cylinder.py ${CMAKE_CURRENT_SOURCE_DIR}/live/thread_arrows_check.py)
    add_test(NAME live_fillet_picks
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/fillet_picks.drive
                          ${CMAKE_CURRENT_SOURCE_DIR}/live/setup_face_extrude.py ${CMAKE_CURRENT_SOURCE_DIR}/live/fillet_picks_check.py)
    add_test(NAME live_thin_extrude
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/thin_extrude.drive
                          ${CMAKE_CURRENT_SOURCE_DIR}/live/setup_rect_sketch.py ${CMAKE_CURRENT_SOURCE_DIR}/live/thin_extrude_check.py)
    add_test(NAME live_hole_on_face
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/hole_on_face.drive
                          ${CMAKE_CURRENT_SOURCE_DIR}/live/setup_cylinder.py ${CMAKE_CURRENT_SOURCE_DIR}/live/hole_on_face_check.py)
    add_test(NAME live_browser_rename
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/browser_rename.drive
                          ${CMAKE_CURRENT_SOURCE_DIR}/live/setup_face_extrude.py ${CMAKE_CURRENT_SOURCE_DIR}/live/browser_rename_check.py)
    add_test(NAME live_sketch_box
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/sketch_box.drive
                          "" ${CMAKE_CURRENT_SOURCE_DIR}/live/sketch_box_check.py)
    add_test(NAME live_box_fillet
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/box_fillet.drive
                          ${CMAKE_CURRENT_SOURCE_DIR}/live/setup_face_extrude.py ${CMAKE_CURRENT_SOURCE_DIR}/live/box_fillet_check.py)
    add_test(NAME live_timeline_marker
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/timeline_marker.drive
                          ${CMAKE_CURRENT_SOURCE_DIR}/live/setup_rect_extrude.py ${CMAKE_CURRENT_SOURCE_DIR}/live/timeline_marker_check.py)
    set_tests_properties(live_sketch_box live_box_fillet live_timeline_marker live_browser_rename live_hole_on_face live_thin_extrude live_fillet_picks live_thread_arrows live_project live_timeline_delete live_value_suggest live_browser_sketch live_sketch_habits live_feature_pattern live_two_sides live_line_tool live_extrude_section live_sketch_modify live_to_object live_face_extrude live_marking_menu live_assembly PROPERTIES
                         ENVIRONMENT "TSR_APP=$<TARGET_FILE:tessera>;TSR_CLI=$<TARGET_FILE:tessera-cli>"
                         TIMEOUT 240)
  endif()
endif()

# No test reads or writes the user's own settings (~/.config): each runs with
# a private settings folder in the build tree, so it starts from the defaults.
get_property(_tsr_tests DIRECTORY PROPERTY TESTS)
foreach(_t IN LISTS _tsr_tests)
  set_property(TEST ${_t} APPEND PROPERTY ENVIRONMENT "XDG_CONFIG_HOME=${CMAKE_CURRENT_BINARY_DIR}/test-config")
endforeach()
