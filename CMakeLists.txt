cmake_minimum_required (VERSION 2.8)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/macros/cmake")

set(PROJECT run)

project (${PROJECT})

#set ( CMAKE_VERBOSE_MAKEFILE true )

set(DEPLOY_DIR "${CMAKE_CURRENT_BINARY_DIR}")
set(SOURCE_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
#add_definitions(-DGL_GLEXT_PROTOTYPES -DGL3_PROTOTYPES)

set(COLDSTARS_DEPENDENCIES_ROOT "/home/balda/workspace/cold_star/coldstars_thirdparty_build/dist")

set(SFML_ROOT ${COLDSTARS_DEPENDENCIES_ROOT})
set(GLEW_ROOT ${COLDSTARS_DEPENDENCIES_ROOT})
set(GLM_ROOT_DIR ${COLDSTARS_DEPENDENCIES_ROOT})

find_package(SFML COMPONENTS system graphics window REQUIRED)
include_directories(${SFML_INCLUDE_DIR})
message("${SFML_LIBRARIES}")

find_package(GLEW REQUIRED)   
include_directories(${GLEW_INCLUDE_DIRS})

find_package(GLM REQUIRED)   
include_directories(${GLM_INCLUDE_DIRS})
add_definitions(-DGLM_FORCE_RADIANS)

#free type
find_package(Freetype REQUIRED)
include_directories(${FREETYPE_INCLUDE_DIRS})
message("${FREETYPE_LIBRARIES}")
message("${FREETYPE_INCLUDE_DIRS}")

add_library(freetyperender dependencies/freetype2/src/FreeType.cpp)
include_directories(dependencies/freetype2/src)

SET_TARGET_PROPERTIES(freetyperender PROPERTIES COMPILE_FLAGS "-std=c++11 -std=gnu++11")

include_directories(src/game/)

add_subdirectory(src/game)

                                
