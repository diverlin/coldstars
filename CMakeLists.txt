cmake_minimum_required (VERSION 2.8)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/macros/cmake")

set(PROJECT run)

project (${PROJECT})

#set( CMAKE_VERBOSE_MAKEFILE true )
set(CMAKE_BUILD_TYPE Debug)

set(DEPLOY_DIR "${CMAKE_CURRENT_BINARY_DIR}")
set(SOURCE_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")

#SET(GLOBAL_COMPILE_FLAGS "-Wall -Werror -Wno-switch -std=c++11 -std=gnu++11 -pipe")
#SET(GLOBAL_COMPILE_FLAGS "-Wall -Wno-switch -std=c++11 -std=gnu++11 -Ofast -march=native")
SET(GLOBAL_COMPILE_FLAGS "-Wall -Wno-switch -std=c++11 -std=gnu++11")
   

set(COLDSTARS_DEPENDENCIES_ROOT "/home/diverlin/coldstars/coldstars_thirdparty_build/dist")
set(SFML_ROOT ${COLDSTARS_DEPENDENCIES_ROOT})
set(GLEW_ROOT ${COLDSTARS_DEPENDENCIES_ROOT})
set(GLM_ROOT_DIR ${COLDSTARS_DEPENDENCIES_ROOT})

include_directories(src/)
include_directories(src/jeti)
include_directories(src/meti)
include_directories(src/ceti)
include_directories(src/game)


add_subdirectory(src/jeti)
add_subdirectory(src/meti)
add_subdirectory(src/ceti)
add_subdirectory(src/game)
                                
