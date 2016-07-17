cmake_minimum_required (VERSION 2.8)

set(PROJECT ${PROJECT_JETI})
project (${PROJECT})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/../../macros/cmake")

file(GLOB_RECURSE ${PROJECT}_SRC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
file(GLOB_RECURSE ${PROJECT}_HDR RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.hpp)

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
#add_definitions(-DGL_GLEXT_PROTOTYPES -DGL3_PROTOTYPES)

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

set(GLM_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../dependencies/glm-0.9.7.5/")
find_package(GLM REQUIRED)   
include_directories(${GLM_INCLUDE_DIRS})
add_definitions(-DGLM_FORCE_RADIANS)

#free type
find_package(Freetype REQUIRED)
include_directories(${FREETYPE_INCLUDE_DIRS})
#message("${FREETYPE_LIBRARIES}")
#message("${FREETYPE_INCLUDE_DIRS}")

add_library(freetyperender ../../dependencies/freetype2/src/FreeType.cpp)
include_directories(dependencies/freetype2/src)

SET_TARGET_PROPERTIES(freetyperender PROPERTIES COMPILE_FLAGS "-std=c++11 -std=gnu++11")

find_package(SFML COMPONENTS system graphics window REQUIRED)
include_directories(${SFML_INCLUDE_DIR})
message("${SFML_LIBRARIES}")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)

if (NOT COMPILE_FLAGS)
    set(COMPILE_FLAGS "-Wall -Wno-switch -std=c++11 -std=gnu++11")
endif ()

add_library(${PROJECT} SHARED ${${PROJECT}_SRC} ${${PROJECT}_HDR})
target_link_libraries(${PROJECT}
    ${SFML_LIBRARIES}
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
    freetyperender
    ${FREETYPE_LIBRARIES}
)
set_target_properties(${PROJECT} PROPERTIES COMPILE_FLAGS ${COMPILE_FLAGS})

