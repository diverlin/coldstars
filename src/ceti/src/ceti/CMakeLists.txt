cmake_minimum_required (VERSION 2.8)

set(PROJECT ${PROJECT_CETI})
project (${PROJECT})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../../macros/cmake")

file(GLOB_RECURSE ${PROJECT}_SRC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
file(GLOB_RECURSE ${PROJECT}_HDR RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.hpp)

set(GLM_ROOT_DIR "../../../dependencies/glm-0.9.7.5/")
find_package(GLM REQUIRED)
include_directories(${GLM_INCLUDE_DIRS})
add_definitions(-DGLM_FORCE_RADIANS)

set(include_dirs ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/..)

if (NOT COMPILE_FLAGS)
    set(COMPILE_FLAGS "-Wall -Wno-switch -std=c++11 -std=gnu++11")
endif ()

add_library(${PROJECT} SHARED ${${PROJECT}_SRC} ${${PROJECT}_HDR})
target_link_libraries(${PROJECT} ${PROJECT_METI})

set_target_properties(${PROJECT} PROPERTIES COMPILE_FLAGS ${COMPILE_FLAGS})
target_include_directories(${PROJECT} PUBLIC
  ${include_dirs}
)
set_property(TARGET ${PROJECT} PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${include_dirs})

