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
  add_test(NAME api_hole_tapped
           COMMAND tessera-cli --script ${CMAKE_CURRENT_SOURCE_DIR}/api/test_hole_tapped.py)
  add_test(NAME api_sketch_patterns
           COMMAND tessera-cli --script ${CMAKE_CURRENT_SOURCE_DIR}/api/test_sketch_patterns.py)
  add_test(NAME api_sketch_text
           COMMAND tessera-cli --script ${CMAKE_CURRENT_SOURCE_DIR}/api/test_sketch_text.py)
  add_test(NAME api_ellipse
           COMMAND tessera-cli --script ${CMAKE_CURRENT_SOURCE_DIR}/api/test_ellipse.py)
  add_test(NAME api_named_views
           COMMAND tessera-cli --script ${CMAKE_CURRENT_SOURCE_DIR}/api/test_named_views.py)
  add_test(NAME api_project_to_surface
           COMMAND tessera-cli --script ${CMAKE_CURRENT_SOURCE_DIR}/api/test_project_to_surface.py)
  add_test(NAME api_sketch_3d
           COMMAND tessera-cli --script ${CMAKE_CURRENT_SOURCE_DIR}/api/test_sketch_3d.py)
  add_test(NAME api_curvature_constraint
           COMMAND tessera-cli --script ${CMAKE_CURRENT_SOURCE_DIR}/api/test_curvature_constraint.py)
  add_test(NAME api_polygon_constraint
           COMMAND tessera-cli --script ${CMAKE_CURRENT_SOURCE_DIR}/api/test_polygon_constraint.py)
  add_test(NAME api_chamfer_arcs
           COMMAND tessera-cli --script ${CMAKE_CURRENT_SOURCE_DIR}/api/test_chamfer_arcs.py)
  add_test(NAME api_extend_curves
           COMMAND tessera-cli --script ${CMAKE_CURRENT_SOURCE_DIR}/api/test_extend_curves.py)
  add_test(NAME api_text_box_path
           COMMAND tessera-cli --script ${CMAKE_CURRENT_SOURCE_DIR}/api/test_text_box_path.py)
  add_test(NAME api_conic_control_spline
           COMMAND tessera-cli --script ${CMAKE_CURRENT_SOURCE_DIR}/api/test_conic_control_spline.py)
  add_test(NAME api_feature_parameters
           COMMAND tessera-cli --script ${CMAKE_CURRENT_SOURCE_DIR}/api/test_feature_parameters.py)
  add_test(NAME api_model_parameters
           COMMAND tessera-cli --script ${CMAKE_CURRENT_SOURCE_DIR}/api/test_model_parameters.py)
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
  add_test(NAME api_rigid_group
           COMMAND tessera-cli --script ${CMAKE_CURRENT_SOURCE_DIR}/api/test_rigid_group.py)
  add_test(NAME api_emboss
           COMMAND tessera-cli --script ${CMAKE_CURRENT_SOURCE_DIR}/api/test_emboss.py)
  add_test(NAME api_face_pattern
           COMMAND tessera-cli --script ${CMAKE_CURRENT_SOURCE_DIR}/api/test_face_pattern.py)
  add_test(NAME api_boundary_fill
           COMMAND tessera-cli --script ${CMAKE_CURRENT_SOURCE_DIR}/api/test_boundary_fill.py)
  add_test(NAME api_extrude_participants
           COMMAND tessera-cli --script ${CMAKE_CURRENT_SOURCE_DIR}/api/test_extrude_participants.py)
  add_test(NAME api_move_triad
           COMMAND tessera-cli --script ${CMAKE_CURRENT_SOURCE_DIR}/api/test_move_triad.py)
  add_test(NAME api_face_appearance
           COMMAND tessera-cli --script ${CMAKE_CURRENT_SOURCE_DIR}/api/test_face_appearance.py)
  add_test(NAME api_fillet_chord
           COMMAND tessera-cli --script ${CMAKE_CURRENT_SOURCE_DIR}/api/test_fillet_chord.py)
  add_test(NAME api_split_face_sketch
           COMMAND tessera-cli --script ${CMAKE_CURRENT_SOURCE_DIR}/api/test_split_face_sketch.py)
  add_test(NAME api_draft_two_sides
           COMMAND tessera-cli --script ${CMAKE_CURRENT_SOURCE_DIR}/api/test_draft_two_sides.py)
  add_test(NAME api_replace_face
           COMMAND tessera-cli --script ${CMAKE_CURRENT_SOURCE_DIR}/api/test_replace_face.py)
  add_test(NAME api_align
           COMMAND tessera-cli --script ${CMAKE_CURRENT_SOURCE_DIR}/api/test_align.py)
  add_test(NAME api_silhouette_split
           COMMAND tessera-cli --script ${CMAKE_CURRENT_SOURCE_DIR}/api/test_silhouette_split.py)
  add_test(NAME api_material_library
           COMMAND tessera-cli --script ${CMAKE_CURRENT_SOURCE_DIR}/api/test_material_library.py)
  add_test(NAME api_plane_along_path
           COMMAND tessera-cli --script ${CMAKE_CURRENT_SOURCE_DIR}/api/test_plane_along_path.py)
  add_test(NAME api_construct_picks
           COMMAND tessera-cli --script ${CMAKE_CURRENT_SOURCE_DIR}/api/test_construct_picks.py)
  add_test(NAME api_sketch_more
           COMMAND tessera-cli --script ${CMAKE_CURRENT_SOURCE_DIR}/api/test_sketch_more.py)
  add_test(NAME api_extrude_to_object
           COMMAND tessera-cli --script ${CMAKE_CURRENT_SOURCE_DIR}/api/test_extrude_to_object.py)
  add_test(NAME api_features
           COMMAND tessera-cli --script ${CMAKE_CURRENT_SOURCE_DIR}/api/test_features.py)
  add_test(NAME api_sketch_curves
           COMMAND tessera-cli --script ${CMAKE_CURRENT_SOURCE_DIR}/api/test_sketch_curves.py)
  add_test(NAME api_construct_planes
           COMMAND tessera-cli --script ${CMAKE_CURRENT_SOURCE_DIR}/api/test_construct_planes.py)
  add_test(NAME api_delete_split_face
           COMMAND tessera-cli --script ${CMAKE_CURRENT_SOURCE_DIR}/api/test_delete_split_face.py)
  add_test(NAME api_sketch_dxf
           COMMAND tessera-cli --script ${CMAKE_CURRENT_SOURCE_DIR}/api/test_sketch_dxf.py)
  add_test(NAME api_thicken
           COMMAND tessera-cli --script ${CMAKE_CURRENT_SOURCE_DIR}/api/test_thicken.py)
  add_test(NAME api_rib_web
           COMMAND tessera-cli --script ${CMAKE_CURRENT_SOURCE_DIR}/api/test_rib_web.py)
  add_test(NAME api_appearance_material
           COMMAND tessera-cli --script ${CMAKE_CURRENT_SOURCE_DIR}/api/test_appearance_material.py)
  add_test(NAME api_robustness
           COMMAND tessera-cli --script ${CMAKE_CURRENT_SOURCE_DIR}/api/test_robustness.py)
  add_test(NAME api_incremental_replay
           COMMAND tessera-cli --script ${CMAKE_CURRENT_SOURCE_DIR}/api/test_incremental_replay.py)
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
    add_test(NAME live_rigid_group
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/rigid_group.drive
                          ${CMAKE_CURRENT_SOURCE_DIR}/live/setup_rigid_group.py ${CMAKE_CURRENT_SOURCE_DIR}/live/rigid_group_check.py)
    add_test(NAME live_emboss
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/emboss.drive
                          ${CMAKE_CURRENT_SOURCE_DIR}/live/setup_emboss.py ${CMAKE_CURRENT_SOURCE_DIR}/live/emboss_check.py)
    add_test(NAME live_face_pattern
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/face_pattern.drive
                          ${CMAKE_CURRENT_SOURCE_DIR}/live/setup_face_pattern.py ${CMAKE_CURRENT_SOURCE_DIR}/live/face_pattern_check.py)
    add_test(NAME live_boundary_fill
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/boundary_fill.drive
                          ${CMAKE_CURRENT_SOURCE_DIR}/live/setup_boundary_fill.py ${CMAKE_CURRENT_SOURCE_DIR}/live/boundary_fill_check.py)
    add_test(NAME live_participants
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/participants.drive
                          ${CMAKE_CURRENT_SOURCE_DIR}/live/setup_participants.py ${CMAKE_CURRENT_SOURCE_DIR}/live/participants_check.py)
    add_test(NAME live_to_face
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/to_face.drive
                          ${CMAKE_CURRENT_SOURCE_DIR}/live/setup_to_face.py ${CMAKE_CURRENT_SOURCE_DIR}/live/to_face_check.py)
    add_test(NAME live_move_triad
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/move_triad.drive
                          ${CMAKE_CURRENT_SOURCE_DIR}/live/setup_face_extrude.py ${CMAKE_CURRENT_SOURCE_DIR}/live/move_triad_check.py)
    add_test(NAME live_face_appearance
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/face_appearance.drive
                          ${CMAKE_CURRENT_SOURCE_DIR}/live/setup_face_extrude.py ${CMAKE_CURRENT_SOURCE_DIR}/live/face_appearance_check.py)
    add_test(NAME live_fillet_chord
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/fillet_chord.drive
                          ${CMAKE_CURRENT_SOURCE_DIR}/live/setup_face_extrude.py ${CMAKE_CURRENT_SOURCE_DIR}/live/fillet_chord_check.py)
    add_test(NAME live_split_sketch
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/split_sketch.drive
                          ${CMAKE_CURRENT_SOURCE_DIR}/live/setup_split_sketch.py ${CMAKE_CURRENT_SOURCE_DIR}/live/split_sketch_check.py)
    add_test(NAME live_draft_sides
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/draft_sides.drive
                          ${CMAKE_CURRENT_SOURCE_DIR}/live/setup_draft_sides.py ${CMAKE_CURRENT_SOURCE_DIR}/live/draft_sides_check.py)
    add_test(NAME live_replace_face
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/replace_face.drive
                          ${CMAKE_CURRENT_SOURCE_DIR}/live/setup_replace_face.py ${CMAKE_CURRENT_SOURCE_DIR}/live/replace_face_check.py)
    add_test(NAME live_align
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/align.drive
                          ${CMAKE_CURRENT_SOURCE_DIR}/live/setup_align.py ${CMAKE_CURRENT_SOURCE_DIR}/live/align_check.py)
    add_test(NAME live_silhouette
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/silhouette.drive
                          ${CMAKE_CURRENT_SOURCE_DIR}/live/setup_silhouette.py ${CMAKE_CURRENT_SOURCE_DIR}/live/silhouette_check.py)
    add_test(NAME live_material_library
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/material_library.drive
                          ${CMAKE_CURRENT_SOURCE_DIR}/live/setup_face_extrude.py ${CMAKE_CURRENT_SOURCE_DIR}/live/material_library_check.py)
    add_test(NAME live_construct_picks
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/construct_picks.drive
                          ${CMAKE_CURRENT_SOURCE_DIR}/live/setup_construct_picks.py ${CMAKE_CURRENT_SOURCE_DIR}/live/construct_picks_check.py)
    add_test(NAME live_plane_path
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/plane_path.drive
                          ${CMAKE_CURRENT_SOURCE_DIR}/live/setup_plane_path.py ${CMAKE_CURRENT_SOURCE_DIR}/live/plane_path_check.py)
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
    add_test(NAME live_fillet_value
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/fillet_value.drive
                          ${CMAKE_CURRENT_SOURCE_DIR}/live/setup_face_extrude.py ${CMAKE_CURRENT_SOURCE_DIR}/live/fillet_value_check.py)
    add_test(NAME live_thin_extrude
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/thin_extrude.drive
                          ${CMAKE_CURRENT_SOURCE_DIR}/live/setup_rect_sketch.py ${CMAKE_CURRENT_SOURCE_DIR}/live/thin_extrude_check.py)
    add_test(NAME live_hole_on_face
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/hole_on_face.drive
                          ${CMAKE_CURRENT_SOURCE_DIR}/live/setup_cylinder.py ${CMAKE_CURRENT_SOURCE_DIR}/live/hole_on_face_check.py)
    add_test(NAME live_browser_rename
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/browser_rename.drive
                          ${CMAKE_CURRENT_SOURCE_DIR}/live/setup_face_extrude.py ${CMAKE_CURRENT_SOURCE_DIR}/live/browser_rename_check.py)
    add_test(NAME live_circular_ring
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/circular_ring.drive
                          ${CMAKE_CURRENT_SOURCE_DIR}/live/setup_offset_box.py ${CMAKE_CURRENT_SOURCE_DIR}/live/circular_ring_check.py)
    add_test(NAME live_revolve_ring
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/revolve_ring.drive
                          ${CMAKE_CURRENT_SOURCE_DIR}/live/setup_revolve_rect.py ${CMAKE_CURRENT_SOURCE_DIR}/live/revolve_ring_check.py)
    add_test(NAME live_shell_arrow
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/shell_arrow.drive
                          ${CMAKE_CURRENT_SOURCE_DIR}/live/setup_face_extrude.py ${CMAKE_CURRENT_SOURCE_DIR}/live/shell_arrow_check.py)
    add_test(NAME live_break_intersect
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/break_intersect.drive
                          ${CMAKE_CURRENT_SOURCE_DIR}/live/setup_sphere.py ${CMAKE_CURRENT_SOURCE_DIR}/live/break_intersect_check.py)
    add_test(NAME live_sketch_pattern
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/sketch_pattern.drive
                          "" ${CMAKE_CURRENT_SOURCE_DIR}/live/sketch_pattern_check.py)
    add_test(NAME live_sketch_text
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/sketch_text.drive
                          "" ${CMAKE_CURRENT_SOURCE_DIR}/live/sketch_text_check.py)
    add_test(NAME live_midpoint_line
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/midpoint_line.drive
                          "" ${CMAKE_CURRENT_SOURCE_DIR}/live/midpoint_line_check.py)
    add_test(NAME live_include_3d
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/include_3d.drive
                          ${CMAKE_CURRENT_SOURCE_DIR}/live/setup_face_extrude.py ${CMAKE_CURRENT_SOURCE_DIR}/live/include_3d_check.py)
    add_test(NAME live_spline_handles_trim
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/spline_handles_trim.drive
                          "" ${CMAKE_CURRENT_SOURCE_DIR}/live/spline_handles_trim_check.py)
    add_test(NAME live_ellipse
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/ellipse.drive
                          "" ${CMAKE_CURRENT_SOURCE_DIR}/live/ellipse_check.py)
    add_test(NAME live_sketch_tangent_slots
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/sketch_tangent_slots.drive
                          "" ${CMAKE_CURRENT_SOURCE_DIR}/live/sketch_tangent_slots_check.py)
    add_test(NAME live_sketch_3pt
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/sketch_3pt.drive
                          "" ${CMAKE_CURRENT_SOURCE_DIR}/live/sketch_3pt_check.py)
    add_test(NAME live_driven_dimension
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/driven_dimension.drive
                          "" ${CMAKE_CURRENT_SOURCE_DIR}/live/driven_dimension_check.py)
    add_test(NAME live_dimension_place
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/dimension_place.drive
                          "" ${CMAKE_CURRENT_SOURCE_DIR}/live/dimension_place_check.py)
    add_test(NAME live_axis_snap
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/axis_snap.drive
                          "" ${CMAKE_CURRENT_SOURCE_DIR}/live/axis_snap_check.py)
    add_test(NAME live_project_surface
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/project_surface.drive
                          ${CMAKE_CURRENT_SOURCE_DIR}/live/setup_sphere.py ${CMAKE_CURRENT_SOURCE_DIR}/live/project_surface_check.py)
    add_test(NAME live_sketch_3d
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/sketch_3d.drive
                          ${CMAKE_CURRENT_SOURCE_DIR}/live/setup_stud_block.py ${CMAKE_CURRENT_SOURCE_DIR}/live/sketch_3d_check.py)
    add_test(NAME live_curvature
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/curvature.drive
                          "" ${CMAKE_CURRENT_SOURCE_DIR}/live/curvature_check.py)
    add_test(NAME live_polygons
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/polygons.drive
                          "" ${CMAKE_CURRENT_SOURCE_DIR}/live/polygons_check.py)
    add_test(NAME live_chamfer_arc
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/chamfer_arc.drive
                          "" ${CMAKE_CURRENT_SOURCE_DIR}/live/chamfer_arc_check.py)
    add_test(NAME live_extend_spline
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/extend_spline.drive
                          "" ${CMAKE_CURRENT_SOURCE_DIR}/live/extend_spline_check.py)
    add_test(NAME live_text_path
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/text_path.drive
                          "" ${CMAKE_CURRENT_SOURCE_DIR}/live/text_path_check.py)
    add_test(NAME live_conic_spline
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/conic_spline.drive
                          "" ${CMAKE_CURRENT_SOURCE_DIR}/live/conic_spline_check.py)
    add_test(NAME live_tangent_arc
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/tangent_arc.drive
                          "" ${CMAKE_CURRENT_SOURCE_DIR}/live/tangent_arc_check.py)
    add_test(NAME live_parameters_table
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/parameters_table.drive
                          ${CMAKE_CURRENT_SOURCE_DIR}/live/setup_stud_block.py ${CMAKE_CURRENT_SOURCE_DIR}/live/parameters_table_check.py)
    add_test(NAME live_viewcube
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/viewcube.drive
                          ${CMAKE_CURRENT_SOURCE_DIR}/live/setup_stud_block.py)
    add_test(NAME live_named_views
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/named_views.drive
                          ${CMAKE_CURRENT_SOURCE_DIR}/live/setup_stud_block.py ${CMAKE_CURRENT_SOURCE_DIR}/live/named_views_check.py)
    add_test(NAME live_visual_styles
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/visual_styles.drive
                          ${CMAKE_CURRENT_SOURCE_DIR}/live/setup_stud_block.py)
    add_test(NAME live_tangent_chain
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/tangent_chain.drive
                          ${CMAKE_CURRENT_SOURCE_DIR}/live/setup_rounded_box.py ${CMAKE_CURRENT_SOURCE_DIR}/live/tangent_chain_check.py)
    add_test(NAME live_select_other
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/select_other.drive
                          ${CMAKE_CURRENT_SOURCE_DIR}/live/setup_face_extrude.py ${CMAKE_CURRENT_SOURCE_DIR}/live/select_other_check.py)
    add_test(NAME live_edge_loop
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/edge_loop.drive
                          ${CMAKE_CURRENT_SOURCE_DIR}/live/setup_face_extrude.py ${CMAKE_CURRENT_SOURCE_DIR}/live/edge_loop_check.py)
    add_test(NAME live_preselect
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/preselect.drive
                          ${CMAKE_CURRENT_SOURCE_DIR}/live/setup_two_rects.py ${CMAKE_CURRENT_SOURCE_DIR}/live/preselect_check.py)
    add_test(NAME live_sketch_box
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/sketch_box.drive
                          "" ${CMAKE_CURRENT_SOURCE_DIR}/live/sketch_box_check.py)
    add_test(NAME live_box_fillet
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/box_fillet.drive
                          ${CMAKE_CURRENT_SOURCE_DIR}/live/setup_face_extrude.py ${CMAKE_CURRENT_SOURCE_DIR}/live/box_fillet_check.py)
    add_test(NAME live_timeline_marker
             COMMAND bash ${PROJECT_SOURCE_DIR}/scripts/live-test.sh ${CMAKE_CURRENT_SOURCE_DIR}/live/timeline_marker.drive
                          ${CMAKE_CURRENT_SOURCE_DIR}/live/setup_rect_extrude.py ${CMAKE_CURRENT_SOURCE_DIR}/live/timeline_marker_check.py)
    set_tests_properties(live_plane_path live_construct_picks live_material_library live_silhouette live_align live_replace_face live_draft_sides live_split_sketch live_fillet_chord live_face_appearance live_move_triad live_participants live_to_face live_fillet_value live_boundary_fill live_face_pattern live_emboss live_rigid_group live_project_surface live_sketch_3d live_curvature live_polygons live_chamfer_arc live_midpoint_line live_include_3d live_spline_handles_trim live_text_path live_conic_spline live_tangent_arc live_parameters_table live_viewcube live_named_views live_visual_styles live_circular_ring live_revolve_ring live_shell_arrow live_break_intersect live_sketch_pattern live_sketch_text live_ellipse live_sketch_tangent_slots live_sketch_3pt live_driven_dimension live_dimension_place live_axis_snap live_tangent_chain live_select_other live_edge_loop live_preselect live_sketch_box live_box_fillet live_timeline_marker live_browser_rename live_hole_on_face live_thin_extrude live_fillet_picks live_thread_arrows live_project live_timeline_delete live_value_suggest live_browser_sketch live_sketch_habits live_feature_pattern live_two_sides live_line_tool live_extrude_section live_sketch_modify live_to_object live_face_extrude live_marking_menu live_assembly PROPERTIES
                         ENVIRONMENT "TSR_APP=$<TARGET_FILE:tessera>;TSR_CLI=$<TARGET_FILE:tessera-cli>"
                         TIMEOUT 240)
  endif()
endif()

# No test reads or writes the user's own settings (~/.config) or material
# library (~/.local/share): each runs with private ones in the build tree,
# so it starts from the defaults.
get_property(_tsr_tests DIRECTORY PROPERTY TESTS)
foreach(_t IN LISTS _tsr_tests)
  set_property(TEST ${_t} APPEND PROPERTY ENVIRONMENT "XDG_CONFIG_HOME=${CMAKE_CURRENT_BINARY_DIR}/test-config")
  set_property(TEST ${_t} APPEND PROPERTY ENVIRONMENT "TESSERA_MATERIALS=${CMAKE_CURRENT_BINARY_DIR}/test-materials.json")
endforeach()
