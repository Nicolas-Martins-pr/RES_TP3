cmake_minimum_required(VERSION 3.19)

project(Res_TP3)

set(CMAKE_CXX_STANDARD 17)


add_executable("${PROJECT_NAME}" main.cpp)

add_subdirectory(Ressources)
target_include_directories("${PROJECT_NAME}" PUBLIC
                          "Ressources/headers"
                          "Ressources/src"
			  include/)


target_sources("${PROJECT_NAME}" PUBLIC ) 


