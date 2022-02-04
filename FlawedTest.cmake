
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


# Takes files containing test util code (.cpp) as arguments
function(flawed_add_test_utils ...)
  set(_FLAWED_TEST_UTIL_LIST ${_FLAWED_TEST_UTIL_LIST} ${ARGV} PARENT_SCOPE)

endfunction()


function(flawed_add_test FILE_NAME)

  get_filename_component(STRIPPED_FILE_NAME ${FILE_NAME} NAME)

  string(REPLACE ".cpp" "" TEST_NAME ${STRIPPED_FILE_NAME})

  add_executable(${TEST_NAME} ${FILE_NAME})

  target_link_libraries(${TEST_NAME} flawed_testing flawed)

  # Append test with prepended path
  set(PREFIXED_TEST_NAME ${FLAWED_OUTPUT_PATH}/${TEST_NAME})

  set(_FLAWED_TEST_LIST ${_FLAWED_TEST_LIST} ${TEST_NAME} PARENT_SCOPE)
  set(_FLAWED_PREFIXED_TEST_LIST ${_FLAWED_PREFIXED_TEST_LIST} ${PREFIXED_TEST_NAME} PARENT_SCOPE)

  set_target_properties(${TEST_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${FLAWED_OUTPUT_PATH})
  set_target_properties(${TEST_NAME} PROPERTIES EXCLUDE_FROM_ALL true)

  add_custom_target(flawed_run_${TEST_NAME} "python3" ${FLAWED_PATH}/flawed_run_tests.py ${PREFIXED_TEST_NAME})
  add_dependencies(flawed_run_${TEST_NAME} ${TEST_NAME})
endfunction()


function(flawed_add_tests ...)
  set(_FLAWED_TEST_LIST "")
  set(_FLAWED_PREFIXED_TEST_LIST "")

  foreach(TEST ${ARGV})
    flawed_add_test(${TEST})
  endforeach()

  set(_FLAWED_TEST_LIST ${_FLAWED_TEST_LIST} PARENT_SCOPE)
  set(_FLAWED_PREFIXED_TEST_LIST ${_FLAWED_PREFIXED_TEST_LIST} PARENT_SCOPE)
endfunction()


# Takes libraries to link to tests as arguments
function(flawed_write_test_target ...)

  set(FLAWED_TEST_UTIL_LIB flawed_test_utils)
  set(TMP_ARCHIVE ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${FLAWED_OUTPUT_PATH})

  add_library(${FLAWED_TEST_UTIL_LIB} STATIC ${_FLAWED_TEST_UTIL_LIST})

  foreach(TEST_TARGET ${_FLAWED_TEST_LIST})
    target_link_libraries(${TEST_TARGET} ${ARGV} ${FLAWED_TEST_UTIL_LIB})
  endforeach()

  add_custom_target(flawed_test "python3" ${FLAWED_PATH}/flawed_run_tests.py ${_FLAWED_PREFIXED_TEST_LIST})

  add_dependencies(flawed_test ${_FLAWED_TEST_LIST})

  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${TMP_ARCHIVE})
endfunction()
