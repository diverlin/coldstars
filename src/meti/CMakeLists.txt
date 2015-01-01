cmake_minimum_required (VERSION 2.8)

set(PROJECT meti)
project (${PROJECT})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../../macros/cmake")

file(GLOB_RECURSE ${PROJECT}_SOURCE RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
file(GLOB_RECURSE ${PROJECT}_HEADER RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.hpp)

#SET(GLOBAL_COMPILE_FLAGS "-Wall -Werror -Wno-switch -std=c++11 -std=gnu++11 -pipe")
#SET(GLOBAL_COMPILE_FLAGS "-Wall -Wno-switch -std=c++11 -std=gnu++11 -Ofast -march=native")
SET(GLOBAL_COMPILE_FLAGS "-Wall -Wno-switch -std=c++11 -std=gnu++11")

find_package(GLM REQUIRED)   
include_directories(${GLM_INCLUDE_DIRS})
add_definitions(-DGLM_FORCE_RADIANS)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(${PROJECT} ${${PROJECT}_SOURCE} ${${PROJECT}_HEADER})
SET_TARGET_PROPERTIES(${PROJECT} PROPERTIES COMPILE_FLAGS "-Wall -Wno-switch -std=c++11 -std=gnu++11")

