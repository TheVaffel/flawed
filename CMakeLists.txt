cmake_minimum_required(VERSION 3.0)
project(flawed)

add_definitions("-std=c++2a -fPIC -g")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/lib)

set(SRC_DIR ${CMAKE_HOME_DIRECTORY}/src)

set(UTILS_DIR ${SRC_DIR}/utils)
set(ASSERT_DIR ${SRC_DIR}/assert)
set(TESTING_DIR ${SRC_DIR}/testing)
set(STRING_DIR ${SRC_DIR}/strings)
set(COMPARATORS_DIR ${SRC_DIR}/comparators)

set(UTIL_SOURCES
  ${UTILS_DIR}/utils.cpp
  ${UTILS_DIR}/error.cpp)

set(ASSERT_SOURCES
  ${ASSERT_DIR}/assert_handlers.cpp
  ${ASSERT_DIR}/asserts.cpp)

set(TESTING_SOURCES
  ${TESTING_DIR}/testing.cpp)

set(STRING_SOURCES
  ${STRING_DIR}/colors.cpp
  ${STRING_DIR}/abbrev.cpp)

set(COMPARATORS_SOURCES
  ${COMPARATORS_DIR}/comparator_registry.cpp)


add_library(${CMAKE_PROJECT_NAME}
  ${UTIL_SOURCES}
  ${ASSERT_SOURCES}
  ${TESTING_SOURCES}
  ${STRING_SOURCES}
  ${COMPARATORS_SOURCES})
