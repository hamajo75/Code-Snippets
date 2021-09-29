add_executable(fooapp main.cc)

target_include_directories(fooapp PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(fooapp lib_my_lib)  # specify which libraries are used

#install(TARGETS fooapp DESTINATION bin)