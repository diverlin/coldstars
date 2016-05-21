cmake_minimum_required (VERSION 2.8)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/macros/cmake")

set(PROJECT coldstars)

project (${PROJECT})

set(CMAKE_BUILD_TYPE "Debug")

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG)
endif ()

#set( CMAKE_VERBOSE_MAKEFILE true )
set(CMAKE_BUILD_TYPE Debug)

set(DEPLOY_DIR "${CMAKE_CURRENT_BINARY_DIR}")

#SET(COMPILE_FLAGS "-Wall -Werror -Wno-switch -std=c++11 -std=gnu++11 -pipe")
#SET(COMPILE_FLAGS "-Wall -Wno-switch -std=c++11 -std=gnu++11 -Ofast -march=native")
SET(COMPILE_FLAGS "-Wall -Wno-switch -std=c++11 -std=gnu++11 -fPIC -rdynamic")
   

set(COLDSTARS_DEPENDENCIES_ROOT "/home/yeti/mnt/workspace/dist/thirdparty_1.0.24/")
set(CMAKE_PREFIX_PATH ${COLDSTARS_DEPENDENCIES_ROOT})
set(SFML_ROOT ${COLDSTARS_DEPENDENCIES_ROOT})
set(GLEW_ROOT ${COLDSTARS_DEPENDENCIES_ROOT})
set(GLM_ROOT_DIR ${COLDSTARS_DEPENDENCIES_ROOT})

include_directories(src/)
include_directories(src/jeti)
include_directories(src/meti)
include_directories(src/ceti)
include_directories(src/game)
include_directories(src/game/core)

set(PROJECT_JETI jeti)
set(PROJECT_METI meti)
set(PROJECT_CETI ceti)

add_subdirectory(src/jeti)
add_subdirectory(src/meti)
add_subdirectory(src/ceti)
add_subdirectory(src/game)
                                
