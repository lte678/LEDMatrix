cmake_minimum_required(VERSION 3.10)

project(pong)

include_directories(${PROJECT_SOURCE_DIR})

add_library(pong SHARED pong.cpp)

target_link_libraries(pong m)

install(TARGETS pong
        LIBRARY DESTINATION /usr/local/share/matrix/apps)