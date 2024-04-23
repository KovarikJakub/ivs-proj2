cmake_minimum_required(VERSION 3.14)
project(stddev)

include_directories(${CMAKE_SOURCE_DIR}/../lib)

add_library(math_lib STATIC ../lib/math_lib.cpp)

add_executable(
  stddev
  stddev.cpp
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")

target_link_libraries(
    stddev
    math_lib
)
