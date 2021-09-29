cmake_minimum_required(VERSION 3.13.4) 

set(CMAKE_C_COMPILER "/usr/bin/gcc")
set(CMAKE_CXX_COMPILER "/usr/bin/g++")

project(FooProject)

add_subdirectory(source/libraries)
add_subdirectory(source/application)

add_compile_options(-Wall -Wextra -Wpedantic)
