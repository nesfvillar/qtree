cmake_minimum_required(VERSION 3.26.0)

project("QTree")
set(CMAKE_CXX_STANDARD 20)

enable_testing()

include_directories(inc)

add_subdirectory(src)
add_subdirectory(test)
