cmake_minimum_required(VERSION 3.13.4) 

project(simple VERSION 1.0)     # add version number
configure_file(version.h.in version.h)
include_directories(${PROJECT_BINARY_DIR})

add_compile_options(-Wall -Wextra -Wpedantic)

add_executable(${PROJECT_NAME} main.cpp)