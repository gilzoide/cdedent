cmake_minimum_required(VERSION 3.0)

project(cdedent C CXX)

option(DEDENT_BUILD_TEST "Whether to build automated tests" OFF)

add_library(cdedent
  cdedent.c
  cdedent.cpp
  cdedent.h
  cdedent.hpp
)
target_include_directories(cdedent INTERFACE .)

if (DEDENT_BUILD_TEST)
  target_compile_features(cdedent PUBLIC cxx_std_17)

  add_executable(test tests/main.cpp)
  target_link_libraries(test cdedent)
endif ()
