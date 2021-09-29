add_library(lib_my_lib SHARED my_lib.cc)

target_include_directories(lib_my_lib PUBLIC ${CMAKE_SOURCE_DIR})
#install(TARGETS util DESTINATION lib)