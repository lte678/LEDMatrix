cmake_minimum_required(VERSION 3.7)

project(wipe)

include_directories(${PROJECT_SOURCE_DIR})

add_library(wipe SHARED lava.cpp)

target_link_libraries(wipe property)

install(TARGETS wipe
        LIBRARY DESTINATION /usr/local/share/matrix/apps)