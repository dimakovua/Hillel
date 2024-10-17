cmake_minimum_required(VERSION 3.10)
project(MyProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "/MDd") 

# Add the main executable
add_executable(MyProject main.cpp)

add_subdirectory(googletest)

set_target_properties(gtest PROPERTIES
  COMPILE_FLAGS "/MDd"  
)

target_link_libraries(MyProject gtest gtest_main)

add_executable(MyProjectTest test.cpp)

target_link_libraries(MyProjectTest gtest gtest_main)

enable_testing()

add_test(NAME MyProjectTest COMMAND MyProjectTest)
