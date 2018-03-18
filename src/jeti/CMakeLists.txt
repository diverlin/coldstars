cmake_minimum_required (VERSION 2.8)

set(CUSTOM_CMAKE_MODULE_RELPATH "../../macros/cmake/macros.cmake")
include(${CUSTOM_CMAKE_MODULE_RELPATH})
MACRO_INIT_PROJECT("jeti")

### deps
# opengl
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

# glew
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

# glm
set(GLM_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../../../dependencies/glm-0.9.7.5")
find_package(GLM REQUIRED)
include_directories(${GLM_INCLUDE_DIRS})
add_definitions(-DGLM_FORCE_RADIANS)

#free type
find_package(Freetype REQUIRED)
include_directories(${FREETYPE_INCLUDE_DIRS})

# sfml
list(APPEND CMAKE_PREFIX_PATH "/media/yeti/ext_workspace/dist_gcc54/SFML-2.4.2")
find_package(SFML COMPONENTS system graphics window REQUIRED)
include_directories(${SFML_INCLUDE_DIR})
message("${SFML_INCLUDE_DIR}")
message("${SFML_LIBRARIES}")

# meti
find_package(METI REQUIRED)
#include_directories(${METI_INCLUDE_DIRS})

# ceti
find_package(CETI REQUIRED)
#include_directories(${CETI_INCLUDE_DIRS})

# add
MACRO_BUILD_MODULE()

set(USE_APP OFF)
if (USE_APP)
    add_subdirectory(app)
endif()

set(USE_APP2 OFF)
if (USE_APP2)
    add_subdirectory(app2)
endif()








