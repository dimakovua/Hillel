add_library(math_functions STATIC math_functions.cpp)

target_include_directories(math_functions PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})