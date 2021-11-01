cmake_minimum_required(VERSION 3.7)

project(glow)

include_directories(${PROJECT_SOURCE_DIR})

add_library(glow SHARED glow.cpp)
target_link_libraries(glow property)

install(TARGETS glow
        LIBRARY DESTINATION /usr/local/share/matrix/apps)