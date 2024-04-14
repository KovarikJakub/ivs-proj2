cmake_minimum_required(VERSION 3.14)
project(deviation)

# For Windows: Prevent overriding the parent project's compiler/linker settings


include_directories(${CMAKE_SOURCE_DIR}/../lib)

add_library(math_lib STATIC ../lib/math_lib.cpp)

add_executable(
  deviation
  deviation.cpp
)

target_link_libraries(
    deviation
    math_lib
)
