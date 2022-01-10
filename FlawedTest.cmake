
set(_FLAWED_TEST_LIST "")
set(_FLAWED_PREFIXED_TEST_LIST "")

if (NOT FLAWED_OUTPUT_PATH)
  set(FLAWED_OUTPUT_PATH flawed_tests)
endif()

if (NOT FLAWED_PATH)
  message(FATAL_ERROR "FLAWED_PATH must be defined!")
endif()

link_directories(${FLAWED_PATH}/lib)
include_directories(${FLAWED_PATH}/include)

function(flawed_add_test FILE_NAME)

  string(REPLACE ".cpp" "" TEST_NAME ${FILE_NAME})

  add_executable(${TEST_NAME} ${FILE_NAME})

  target_link_libraries(${TEST_NAME} flawed_testing flawed)

  message(">>>> " ${TEST_NAME})

  get_target_property(TARGET_NAME ${TEST_NAME} NAME)

  message("Target name = " ${TARGET_NAME})


  # list(APPEND _FLAWED_TEST_LIST ${TEST_NAME})

  message("Flawed output path = " ${FLAWED_OUTPUT_PATH})

  # Append test with prepended path
  set(_FLAWED_TEST_LIST ${_FLAWED_TEST_LIST} ${TEST_NAME} PARENT_SCOPE)
  set(_FLAWED_PREFIXED_TEST_LIST ${_FLAWED_PREFIXED_TEST_LIST} ${FLAWED_OUTPUT_PATH}/${TEST_NAME} PARENT_SCOPE)

  message(">>>>>" ${_FLAWED_TEST_LIST})

  set_target_properties(${TEST_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${FLAWED_OUTPUT_PATH})
  set_target_properties(${TEST_NAME} PROPERTIES EXCLUDE_FROM_ALL true)

  get_target_property(OUTPUT_DIR ${TEST_NAME} RUNTIME_OUTPUT_DIRECTORY)

  message("AAAHHHH" ${OUTPUT_DIR})
endfunction()


function(flawed_write_test_target)

  add_custom_target(flawed_test "python3" ${FLAWED_PATH}/flawed_run_tests.py ${_FLAWED_PREFIXED_TEST_LIST})

  message(">>>" ${_FLAWED_TEST_LIST})
  add_dependencies(flawed_test ${_FLAWED_TEST_LIST})

endfunction()
