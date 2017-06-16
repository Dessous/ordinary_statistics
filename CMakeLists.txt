cmake_minimum_required(VERSION 3.6)
project(ordinary_statistics)

set(CMAKE_CXX_STANDARD 11)
enable_testing()
include_directories(include)

add_subdirectory(src)
add_subdirectory(tests)
