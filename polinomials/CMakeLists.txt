cmake_minimum_required(VERSION 3.22)

set(project "polinomials")
project(${project})

set(${project}_SOURCES
        polinomials.cpp)

set(${project}_HEADERS
        polinomials.h)

set(${project}_SOURCE_LIST
        ${${project}_SOURCES}
        ${${project}_HEADERS})

add_library(${project}
        STATIC
        ${${project}_SOURCE_LIST})

# Линкуем с библиотекой vector
target_link_libraries(${project} myvector)