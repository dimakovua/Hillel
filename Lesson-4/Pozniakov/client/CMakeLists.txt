
find_package(Boost REQUIRED)


add_library(OpenWeatherMapClient  OpenWeatherMapClient.cpp)
target_include_directories(OpenWeatherMapClient PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(OpenWeatherMapClient Boost::boost)


