cmake_minimum_required(VERSION 3.10)

project(MathSimple)

add_executable(math_app main.cpp mathHillel.cpp)

target_include_directories(math_app PRIVATE .)
