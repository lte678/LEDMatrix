cmake_minimum_required(VERSION 3.10)

project(scrolltext)

include_directories(${PROJECT_SOURCE_DIR})

add_library(scrolltext SHARED scrolltext.cpp)

target_link_libraries(scrolltext property)

install(TARGETS scrolltext
        LIBRARY DESTINATION /usr/local/share/matrix/apps)