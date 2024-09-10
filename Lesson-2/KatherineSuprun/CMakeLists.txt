cmake_minimum_required(VERSION 3.10)

project(StackTemplateProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(project main.cpp)
target_include_directories(project PUBLIC ${CMAKE_SOURCE_DIR})
add_executable(main_app main.cpp)

