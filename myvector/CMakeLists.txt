cmake_minimum_required(VERSION 3.22)

set(project "myvector")
project(${project})

set(CMAKE_CXX_STANDARD 17)

set(${project}_HEADERS
        myvector.h)

set(${project}_SOURCE_LIST
        ${${project}_HEADERS})

add_library(${project}
        INTERFACE
        ${${project}_SOURCE_LIST})

target_include_directories(${project} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
