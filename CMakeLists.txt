cmake_minimum_required(VERSION 3.19)

project(Res_TP3)

set(CMAKE_CXX_STANDARD 17)


option(BUILD_EXAMPLES "build examples" ON)
option(BUILD_TESTS "build tests" ON)

add_subdirectory(main)
add_subdirectory(examples)
