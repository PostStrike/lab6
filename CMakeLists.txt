cmake_minimum_required(VERSION 3.22)

set(project "lab6")
project(${project})

set(${project}_SOURCES
        main.cpp)
 
add_subdirectory(polinomials)       
add_subdirectory(myvector)    

set(${project}_SOURCE_LIST
        ${${project}_SOURCES})

add_executable(${project}
        ${${project}_SOURCE_LIST})

target_link_libraries(${project} polinomials)