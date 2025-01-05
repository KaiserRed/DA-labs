cmake_minimum_required(VERSION 3.10)

project(lab9)

# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(lab9 main.cpp)
add_executable(lab9_bench benchmark.cpp)
add_executable(lab9_contest single_file.cpp)


add_library(graph INTERFACE)
target_include_directories(graph INTERFACE src)

target_link_libraries(lab9 PRIVATE graph)
target_link_libraries(lab9_bench graph)
