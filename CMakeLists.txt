cmake_minimum_required(VERSION 3.10)

project(matrix)

option(USE_SOFTWARE_MATRIX "If enabled, uses a SDL to render the matrix instead of physical hardware." OFF)


set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

if(NOT USE_SOFTWARE_MATRIX)
    add_subdirectory(lib/ws281x)
else()
    add_compile_definitions(USE_SOFTWARE_MATRIX)
endif()

add_subdirectory(lib/property)
add_subdirectory(apps)
add_subdirectory(core)

