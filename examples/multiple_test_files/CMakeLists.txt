cmake_minimum_required(VERSION 3.0)
project(flawed_multiple_tests)

set(FLAWED_PATH ${CMAKE_HOME_DIRECTORY}/../..)
include(${FLAWED_PATH}/FlawedTest.cmake)

add_definitions("-std=c++2a")

flawed_add_tests(test0.cpp test1.cpp)

flawed_write_test_target()
