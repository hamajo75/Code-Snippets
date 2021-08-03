cmake_minimum_required(VERSION 3.13.4) 

add_compile_options(-Wall -Wextra -Wpedantic)

project(main)
add_executable(${PROJECT_NAME} main.cc)

