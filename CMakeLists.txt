cmake_minimum_required(VERSION 3.19)

project(Res_TP3)

set(CMAKE_CXX_STANDARD 17)


add_executable("${PROJECT_NAME}" "Ressources/src/main.cpp" )

add_subdirectory(Ressources)
target_include_directories("${PROJECT_NAME}" PUBLIC
                          "Ressources/headers"
                          "Ressources/src"
			  include/)


target_sources("${PROJECT_NAME}" PUBLIC Ressources/headers/NetworkObject.h  Ressources/headers/ClassRegistry.h 
                Ressources/headers/Player.h  "Ressources/headers/Framework.h"  Ressources/headers/LinkingContext.h  Ressources/headers/Enemy.h  Ressources/headers/ReplicationManager.h  Ressources/headers/Serializer.h  Ressources/headers/Deserializer.h
Ressources/src/ClassRegistry.cpp  Ressources/src/Enemy.cpp  Ressources/src/LinkingContext.cpp  Ressources/src/NetworkObject.cpp  Ressources/src/Player.cpp  Ressources/src/ReplicationManager.cpp  Ressources/src/Serializer.cpp  Ressources/src/Deserializer.cpp) 


