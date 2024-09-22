cmake_minimum_required(VERSION 3.10)

project(OneWayList)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(onewaylist main.cpp)
target_include_directories(onewaylist PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
