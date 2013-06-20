cmake_minimum_required (VERSION 2.8)

set(PROJECT run)

project (${PROJECT})
set(BIN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bin/ )

#add_definitions(-Wall -Wextra -std=c++11 -std=gnu++11)
add_definitions(-std=c++11 -std=gnu++11)

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
#add_definitions(-DGL_GLEXT_PROTOTYPES -DGL3_PROTOTYPES)

include_directories(dependencies/SFML2/include/)
include_directories(dependencies/glew/include/)
include_directories(dependencies/glm-0.9.4.0/)
include_directories(dependencies/freetype2/)

add_subdirectory(dependencies/SFML2)
set(GLEW_STATIC 1)
add_subdirectory(dependencies/glew)

add_subdirectory(src/game)

