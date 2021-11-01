cmake_minimum_required(VERSION 3.7)

project(colorwave)

include_directories(${PROJECT_SOURCE_DIR})

add_library(colorwave SHARED colorwave.cpp)
target_link_libraries(colorwave fastnoise property)

install(TARGETS colorwave
        LIBRARY DESTINATION /usr/local/share/matrix/apps)