cmake_minimum_required(VERSION 3.19)

project(Res_TP3)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(Ressources)

set(ASIO_DIR "${CMAKE_SOURCE_DIR}/Ressources/asio/include/asio.hpp")
add_library(asio INTERFACE)


add_executable("${PROJECT_NAME}" main.cpp )
target_include_directories(asio INTERFACE "${CMAKE_SOURCE_DIR}/Ressources/asio/include")

target_include_directories("${PROJECT_NAME}" PUBLIC
                          "Ressources/headers"
                          "Ressources/src"
			  include/)
              


target_sources("${PROJECT_NAME}" PUBLIC Ressources/headers/NetworkObject.h  Ressources/headers/ClassRegistry.h 
                Ressources/headers/Player.h  "Ressources/headers/Framework.h"  Ressources/headers/LinkingContext.h  Ressources/headers/Enemy.h  Ressources/headers/ReplicationManager.h  Ressources/headers/Serializer.h  Ressources/headers/Deserializer.h
Ressources/src/ClassRegistry.cpp  Ressources/src/Enemy.cpp  Ressources/src/LinkingContext.cpp  Ressources/src/NetworkObject.cpp  Ressources/src/Player.cpp  Ressources/src/ReplicationManager.cpp  Ressources/src/Serializer.cpp  Ressources/src/Deserializer.cpp) 



target_link_libraries("${PROJECT_NAME}" asio)

