cmake_minimum_required(VERSION 3.13)
project(matrix_core)

find_package(Threads)

set(CMAKE_CXX_STANDARD 14)

include_directories(
        ../include
        ../lib)

set(SOURCE_FILES main.cpp ServiceUtils.cpp MatrixManager.cpp CommandParser.cpp ../lib/property/Property.cpp)

add_executable(matrix_core ${SOURCE_FILES})
add_subdirectory(Commands)
set_target_properties(matrix_core PROPERTIES OUTPUT_NAME matrix)

target_link_libraries(matrix_core ${CMAKE_THREAD_LIBS_INIT} ${CMAKE_DL_LIBS} ws281x)

install(TARGETS matrix_core
        RUNTIME DESTINATION /usr/local/bin)

install(FILES ../config/matrix.service
        DESTINATION /etc/systemd/system)