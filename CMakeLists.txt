cmake_minimum_required(VERSION 3.6)
project(ordinary_statistics)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES test/main.cpp src/ordinary_statistics.cpp include/ordinary_statistics.h)
add_executable(ordinary_statistics ${SOURCE_FILES})
include_directories(include)
