cmake_minimum_required (VERSION 2.8)

set(PROJECT jeti)
project (${PROJECT})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/../../macros/cmake")

file(GLOB_RECURSE ${PROJECT}_SOURCE RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
file(GLOB_RECURSE ${PROJECT}_HEADER RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.hpp)

#SET(GLOBAL_COMPILE_FLAGS "-Wall -Werror -Wno-switch -std=c++11 -std=gnu++11 -pipe")
#SET(GLOBAL_COMPILE_FLAGS "-Wall -Wno-switch -std=c++11 -std=gnu++11 -Ofast -march=native")
SET(GLOBAL_COMPILE_FLAGS "-Wall -Wno-switch -std=c++11 -std=gnu++11")

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
#add_definitions(-DGL_GLEXT_PROTOTYPES -DGL3_PROTOTYPES)

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

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


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../jeti)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../game)


add_library(${PROJECT} ${${PROJECT}_SOURCE} ${${PROJECT}_HEADER})
target_link_libraries(${PROJECT}
    ${SFML_LIBRARIES}
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
    freetyperender
    ${FREETYPE_LIBRARIES}
)
SET_TARGET_PROPERTIES(${PROJECT} PROPERTIES COMPILE_FLAGS "-Wall -Wno-switch -std=c++11 -std=gnu++11")


# deploy
#ADD_CUSTOM_COMMAND(
#    TARGET ${PROJECT}
#    POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT} ${DEPLOY_DIR}
#)
