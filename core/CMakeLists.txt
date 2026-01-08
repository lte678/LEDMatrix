cmake_minimum_required(VERSION 3.13)
project(matrix_core)

find_package(Threads)

set(CMAKE_CXX_STANDARD 14)

include_directories(
        ../include
        ../lib)

set(SOURCE_FILES main.cpp Globals.cpp TcpServer.cpp ServiceUtils.cpp MatrixManager.cpp CommandParser.cpp ../lib/property/Property.cpp)
if(USE_SOFTWARE_MATRIX)
        list(APPEND SOURCE_FILES SoftwareMatrix.cpp)
else()
        list(APPEND SOURCE_FILES HardwareMatrix.cpp)
endif()

add_executable(matrix_core ${SOURCE_FILES})
add_subdirectory(Commands)
set_target_properties(matrix_core PROPERTIES OUTPUT_NAME matrix)

if(USE_SOFTWARE_MATRIX)
        target_link_libraries(matrix_core PRIVATE SDL3::SDL3)
else()
        target_link_libraries(matrix_core ${CMAKE_THREAD_LIBS_INIT} ${CMAKE_DL_LIBS} ws281x)
endif()

install(TARGETS matrix_core
        RUNTIME DESTINATION /usr/local/bin)

install(FILES ../config/matrix.service
        DESTINATION /etc/systemd/system)