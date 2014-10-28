cmake_minimum_required (VERSION 2.8)

set(PROJECT jeti)
project (${PROJECT})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/../../macros/cmake")

file(GLOB_RECURSE ${PROJECT}_SOURCE RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
file(GLOB_RECURSE ${PROJECT}_HEADER RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.hpp)

add_library(${PROJECT} ${${PROJECT}_SOURCE} ${${PROJECT}_HEADER})
target_link_libraries(${PROJECT} ${OPENGL_LIBRARIES})

#SET(GLOBAL_COMPILE_FLAGS "-Wall -Werror -Wno-switch -std=c++11 -std=gnu++11 -pipe")
#SET(GLOBAL_COMPILE_FLAGS "-Wall -Wno-switch -std=c++11 -std=gnu++11 -Ofast -march=native")
SET(GLOBAL_COMPILE_FLAGS "-Wall -Wno-switch -std=c++11 -std=gnu++11")
SET_TARGET_PROPERTIES(${PROJECT} PROPERTIES COMPILE_FLAGS ${GLOBAL_COMPILE_FLAGS})

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
#add_definitions(-DGL_GLEXT_PROTOTYPES -DGL3_PROTOTYPES)

find_package(GLM REQUIRED)   
include_directories(${GLM_INCLUDE_DIRS})
add_definitions(-DGLM_FORCE_RADIANS)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../jeti)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../game)

# deploy
#ADD_CUSTOM_COMMAND(
#    TARGET ${PROJECT}
#    POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT} ${DEPLOY_DIR}
#)
