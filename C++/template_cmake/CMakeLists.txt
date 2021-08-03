##########################################################################
#   COPYRIGHT: Mission Embedded GmbH - All rights reserved.
#              Registered with Commercial Court Vienna,
#              reg.no. FN 410566 z
#     PROJECT: MEI005 Common Components
#      AUTHOR: gpi@mission-embedded.com
#  SUBSTITUTE: crr@mission-embedded.com
##########################################################################
cmake_minimum_required (VERSION 3.20)

project(main CXX)

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
find_package(Threads REQUIRED)

file(GLOB SOURCES "*.cc")

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} pthread)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR})