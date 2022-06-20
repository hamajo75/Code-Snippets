cmake_minimum_required (VERSION 3.20)

project(executable.exe CXX)

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
find_package(Threads REQUIRED)

file(GLOB SOURCES "*.cc")

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} pthread)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR})