cmake_minimum_required(VERSION 3.10)

project(WeatherFetcher)

find_package(Boost REQUIRED)

add_executable(weather_fetcher main.cpp)
target_link_libraries(weather_fetcher Boost::boost)