cmake_minimum_required(VERSION 3.7)

project(sparkles)

include_directories(${PROJECT_SOURCE_DIR})

add_library(sparkles SHARED sparkles.cpp)

target_link_libraries(sparkles property)

install(TARGETS sparkles
        LIBRARY DESTINATION /usr/local/share/matrix/apps)