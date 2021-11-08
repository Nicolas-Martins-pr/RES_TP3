cmake_minimum_required(VERSION 3.19)

set(${PROJECT_NAME}_Version ${Version})

set(${PROJECT_NAME}_SRC 
                        
                        "src/network/uqacNetwork.cpp"  "src/network/Connection.cpp" "src/network/Terminal.cpp"
                        src/ClassRegistry.cpp  src/Enemy.cpp  src/LinkingContext.cpp  src/NetworkObject.cpp  src/Player.cpp  src/ReplicationManager.cpp  src/Serializer.cpp  src/Deserializer.cpp
)

set(${PROJECT_NAME}_HEADERS 
                           "headers/network/uqacNetwork.hpp"  "headers/network/config.hpp" "headers/network/Terminal.hpp" "headers/network/Connection.hpp"  "headers/network/NetworkFramework.hpp"
                           headers/NetworkObject.h  headers/ClassRegistry.h headers/Player.h  "headers/Framework.h"  headers/LinkingContext.h  headers/Enemy.h  headers/ReplicationManager.h 
                           headers/Serializer.h  headers/Deserializer.h
)

add_library(${PROJECT_NAME} STATIC ${${PROJECT_NAME}_SRC} ${${PROJECT_NAME}_HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC include)