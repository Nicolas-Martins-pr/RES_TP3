cmake_minimum_required(VERSION 3.19)

set(${PROJECT_NAME}_EXAMPLE_BASIC_SRC   "main.cpp")


add_executable(${PROJECT_NAME}_EXAMPLE_BASIC ${${PROJECT_NAME}_EXAMPLE_BASIC_SRC})
target_link_libraries(${PROJECT_NAME}_EXAMPLE_BASIC PUBLIC ${PROJECT_NAME})