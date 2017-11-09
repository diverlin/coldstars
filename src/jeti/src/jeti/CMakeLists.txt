cmake_minimum_required (VERSION 2.8)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/../../macros/cmake")

file(GLOB_RECURSE ${PROJECT}_SRC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
file(GLOB_RECURSE ${PROJECT}_HDR RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.hpp)

file(GLOB_RECURSE ${PROJECT}_FRAG RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/shaders *.frag)
file(GLOB_RECURSE ${PROJECT}_VERT RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/shaders *.vert)

set(GTEST_ROOT "/workspace/dist/gtest")

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
#add_definitions(-DGL_GLEXT_PROTOTYPES -DGL3_PROTOTYPES)

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

set(GLM_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../../../dependencies/glm-0.9.7.5")
find_package(GLM REQUIRED)   
include_directories(${GLM_INCLUDE_DIRS})
add_definitions(-DGLM_FORCE_RADIANS)

#free type
find_package(Freetype REQUIRED)
include_directories(${FREETYPE_INCLUDE_DIRS})
#message("${FREETYPE_LIBRARIES}")
#message("${FREETYPE_INCLUDE_DIRS}")

add_library(freetyperender ../../../../dependencies/freetype2/src/FreeType.cpp)
include_directories(dependencies/freetype2/src)

SET_TARGET_PROPERTIES(freetyperender PROPERTIES COMPILE_FLAGS "-std=c++11 -std=gnu++11")

list(APPEND CMAKE_PREFIX_PATH "/media/yeti/ext_workspace/dist_gcc54/SFML-2.4.2")
find_package(SFML COMPONENTS system graphics window REQUIRED)
include_directories(${SFML_INCLUDE_DIR})
message("${SFML_INCLUDE_DIR}")
message("${SFML_LIBRARIES}")

set(CETI_ROOT )
set(include_dirs
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/..
    ${CMAKE_SOURCE_DIR}/src/ceti/src # hack
    )

add_library(${PROJECT} SHARED
    ${${PROJECT}_SRC}
    ${${PROJECT}_HDR}
#    ${${PROJECT}_FRAG}
#    ${${PROJECT}_VERT}
    )
target_link_libraries(${PROJECT}
    ${CETI_PROJECT}
    ${SFML_LIBRARIES}
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
    freetyperender
    ${FREETYPE_LIBRARIES}
)
target_include_directories(${PROJECT} PUBLIC
  ${include_dirs}
)
set_property(TARGET ${PROJECT} PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${include_dirs})

set_target_properties(${PROJECT} PROPERTIES COMPILE_FLAGS ${COMPILE_FLAGS})

