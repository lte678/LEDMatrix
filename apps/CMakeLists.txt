cmake_minimum_required(VERSION 3.10)

project(matrix_apps)

set(CMAKE_CXX_STANDARD 14)

#since the apps are only pseudo shared libraries and not really libs
set(CMAKE_SHARED_LIBRARY_PREFIX app)

include_directories(
        ${PROJECT_SOURCE_DIR}/../include
        ${PROJECT_SOURCE_DIR}/../include/ws281x
        ${PROJECT_SOURCE_DIR}/../lib/
        ${PROJECT_SOURCE_DIR}/lib/
)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

add_subdirectory(lib/fastnoise)

add_subdirectory(src/colorwave)
add_subdirectory(src/sparkles)
add_subdirectory(src/scrolltext)
add_subdirectory(src/glow)
add_subdirectory(src/wipe)
#add_subdirectory(src/lightspeed)
add_subdirectory(src/lava)
#add_subdirectory(src/pong)