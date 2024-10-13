cmake_minimum_required(VERSION 3.0)

project(dedent C CXX)

option(DEDENT_BUILD_TEST "Whether to build automated tests" OFF)

add_library(dedent.h INTERFACE dedent.h)
target_include_directories(dedent.h INTERFACE .)

if (DEDENT_BUILD_TEST)
  add_executable(test tests/main.cpp)
  target_compile_features(test PRIVATE cxx_std_11)
  target_link_libraries(test dedent.h)
endif ()
