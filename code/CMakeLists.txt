cmake_minimum_required(VERSION 3.16)

set(CMAKE_C_COMPILER "/usr/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
set(CMAKE_LINKER "/usr/bin/clang++")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(CS225_EC)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_GLIBCXX_DEBUG -O0 -gdwarf-4")

find_package(Catch2 REQUIRED)

set(src_dir ${CMAKE_SOURCE_DIR}/src)
set(tests_dir ${CMAKE_SOURCE_DIR}/tests)
set(entry_dir ${CMAKE_SOURCE_DIR}/entry)

find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
  set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
endif(CCACHE_FOUND)

add_subdirectory(${src_dir})

file(GLOB_RECURSE tests_src CONFIGURE_DEPENDS ${tests_dir}/*.cpp)

include(Catch)

add_executable(test ${tests_src})
target_link_libraries(test PRIVATE Catch2::Catch2WithMain src)

catch_discover_tests(test)

add_executable(main ${entry_dir}/main.cpp)
target_link_libraries(main PRIVATE Catch2::Catch2WithMain src)