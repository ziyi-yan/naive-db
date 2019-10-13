cmake_minimum_required(VERSION 3.7)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(naive-db)

# Process Abseil's CMake build system
add_subdirectory(abseil-cpp)

add_executable(naive-db src/main.cc)

# Declare dependency on the absl::strings library
target_link_libraries(naive-db absl::str_format)
