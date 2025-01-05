cmake_minimum_required(VERSION 3.10)

project(lab7)

# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(lab7 src/main.cpp)
add_executable(lab7_benchmark src/benchmark.cpp)
