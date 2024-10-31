cmake_minimum_required(VERSION 3.10)

project(Hello VERSION 1.0)

set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_C_COMPILER "clang")

add_compile_options("-fsanitize=address" "-g")
add_link_options("-fsanitize=address")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)


add_executable(hello main.cpp)
target_include_directories(hello PRIVATE .)