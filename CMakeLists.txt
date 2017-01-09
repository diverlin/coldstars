cmake_minimum_required (VERSION 2.8)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/macros/cmake")

set(PROJECT coldstars)

project(${PROJECT})

set(USE_TEST ON)
set(DUMP_DESCRIPTORS OFF)
if(DUMP_DESCRIPTORS)
    add_definitions(-DDUMP_DESCRIPTORS)
endif()

set(GTEST_ROOT "/workspace/dist/gtest")
set(GLM_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glm-0.9.7.5/")

set(CMAKE_BUILD_TYPE "Debug")

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG)
endif ()

#set( CMAKE_VERBOSE_MAKEFILE true )

set(DEPLOY_DIR "${CMAKE_CURRENT_BINARY_DIR}")

#SET(COMPILE_FLAGS "-Wall -Werror -Wno-switch -std=c++11 -std=gnu++11 -pipe")
#SET(COMPILE_FLAGS "-Wall -Wno-switch -std=c++11 -std=gnu++11 -Ofast -march=native")
#SET(COMPILE_FLAGS "-Wall -Wno-switch -std=c++11 -std=gnu++11 -O0 -fPIC -rdynamic")
SET(COMPILE_FLAGS "-Wall -Wno-switch -std=c++11 -std=gnu++11 -fPIC")


set(CMAKE_PREFIX_PATH ${COLDSTARS_DEPENDENCIES_ROOT})
set(SFML_ROOT ${COLDSTARS_DEPENDENCIES_ROOT})
set(GLEW_ROOT ${COLDSTARS_DEPENDENCIES_ROOT})
set(GLM_ROOT_DIR ${COLDSTARS_DEPENDENCIES_ROOT})

set(USE_FAILBACK_RESOURCES ON)
if(USE_FAILBACK_RESOURCES)
    add_definitions(-DUSE_FAILBACK_RESOURCES)
endif()

include_directories(src/)
include_directories(src/jeti)
include_directories(src/meti)
include_directories(src/meti/src)
include_directories(src/ceti)
include_directories(src/game/client/src)
include_directories(src/game/core)
include_directories(src/game)

set(PROJECT_JETI jeti)
set(PROJECT_METI meti)
set(PROJECT_CETI ceti)

add_subdirectory(src/jeti)
add_subdirectory(src/meti)
add_subdirectory(src/ceti)
add_subdirectory(src/game)
                                
