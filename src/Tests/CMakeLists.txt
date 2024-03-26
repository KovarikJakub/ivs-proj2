cmake_minimum_required(VERSION 3.14)
project(math_lib_test_proj)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Download GoogleTest using git
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

include_directories(${CMAKE_SOURCE_DIR}/../lib)

add_library(math_lib STATIC ../lib/math_lib.cpp)

add_executable(
  math_lib_tests
  math_lib_tests.cpp
)

target_link_libraries(
  math_lib_tests
  GTest::gtest_main
  math_lib
)

include(GoogleTest)
gtest_discover_tests(math_lib_tests)