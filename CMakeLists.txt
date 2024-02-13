cmake_minimum_required(VERSION 3.27)
project(watchdog)

set(CMAKE_CXX_STANDARD 17)

set(BUILD_TEST ON)

include_directories(3rd)

add_subdirectory(bite)
add_subdirectory(dog)
