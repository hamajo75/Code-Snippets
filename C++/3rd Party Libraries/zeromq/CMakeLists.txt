cmake_minimum_required (VERSION 3.20)

project(zeromq CXX)

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
find_package(Threads REQUIRED)
find_package(cppzmq)

set(SERVER server)
add_executable(${SERVER} server.cc)
target_link_libraries(${SERVER} pthread)
target_link_libraries(${SERVER} cppzmq)

set(CLIENT client)
add_executable(${CLIENT} client.cc)
target_link_libraries(${CLIENT} pthread)
target_link_libraries(${CLIENT} cppzmq)
