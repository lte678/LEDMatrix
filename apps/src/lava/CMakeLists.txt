cmake_minimum_required(VERSION 3.7)

project(lava)

include_directories(${PROJECT_SOURCE_DIR})

add_library(lava SHARED lava.cpp)

target_link_libraries(lava property)

install(TARGETS lava
        LIBRARY DESTINATION /usr/local/share/matrix/apps)