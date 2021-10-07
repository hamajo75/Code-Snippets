cmake_minimum_required(VERSION 3.13.4)

project(simple VERSION 1.0)     # add version number
configure_file(version.h.in version.h)
include_directories(${PROJECT_BINARY_DIR})

add_compile_options(-Wall -Wextra -Wpedantic)

# main application
add_executable(${PROJECT_NAME} main.cpp)

# macro definition (use like #define in the code)
target_compile_definitions(${PROJECT_NAME} PRIVATE TEST_MSG_PATH=${CMAKE_SOURCE_DIR})