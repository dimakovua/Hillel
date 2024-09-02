cmake_minimum_required(VERSION 3.10)

project(MathHarded)

add_library(lib STATIC lib.cpp)

target_include_directories(lib PUBLIC .)

add_executable(math_app main.cpp)

target_link_libraries(math_app PRIVATE lib)
