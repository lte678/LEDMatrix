cmake_minimum_required(VERSION 3.10)

project(lightspeed)

include_directories(${PROJECT_SOURCE_DIR})

add_library(lightspeed SHARED lightspeed.cpp)

target_link_libraries(lightspeed property)

install(TARGETS lightspeed
        LIBRARY DESTINATION /usr/local/share/matrix/apps)