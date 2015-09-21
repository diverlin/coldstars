cmake_minimum_required (VERSION 2.8)

set(PROJECT ${PROJECT_CETI})
project (${PROJECT})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../../macros/cmake")

file(GLOB_RECURSE ${PROJECT}_SOURCE RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
file(GLOB_RECURSE ${PROJECT}_HEADER RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.hpp)

find_package(GLM REQUIRED)
include_directories(${GLM_INCLUDE_DIRS})
add_definitions(-DGLM_FORCE_RADIANS)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)

if (COMPILE_FLAGS)
    set(COMPILE_FLAGS ${COMPILE_FLAGS})
else ()
    set(COMPILE_FLAGS "-Wall -Wno-switch -std=c++11 -std=gnu++11")
endif ()

add_library(${PROJECT} ${${PROJECT}_SOURCE} ${${PROJECT}_HEADER})
set_target_properties(${PROJECT} PROPERTIES COMPILE_FLAGS ${COMPILE_FLAGS})

