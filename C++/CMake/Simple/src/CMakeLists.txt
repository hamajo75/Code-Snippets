#------------------------------------------------------------------------------
# The absolute minimum CMakeLists.txt file for a C++ project.
cmake_minimum_required(VERSION 3.13.4)

project(simple VERSION 1.0)     # add version number
add_compile_options(-Wall -Wextra -Wpedantic)

# main application
add_executable(${PROJECT_NAME} main.cpp)
#------------------------------------------------------------------------------

configure_file(version_template.h ../src/version.h)