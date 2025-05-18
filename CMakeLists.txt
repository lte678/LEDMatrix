cmake_minimum_required(VERSION 3.10)

project(matrix)

#include_directories(
#        ${PROJECT_SOURCE_DIR}/src
#        ${PROJECT_SOURCE_DIR}/include
#        ${PROJECT_SOURCE_DIR}/lib
#)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

add_subdirectory(lib/ws281x)
add_subdirectory(lib/property)
add_subdirectory(apps)
add_subdirectory(core)

