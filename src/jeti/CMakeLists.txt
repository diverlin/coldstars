cmake_minimum_required (VERSION 2.8)

if (NOT PROJECT_CETI)
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/../../macros/cmake")

    set(PROJECT_JETI "jeti")
    project(${PROJECT_JETI})

    if(NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE "Debug")
    endif()

    if(NOT COMPILE_FLAGS)
        set(COMPILE_FLAGS "-Wall -Wno-switch -std=c++11 -std=gnu++11")
    endif()

    if(COLDSTARS_DEPLOY_DIR)
        set(COLDSTARS_DEPLOY_DIR ${COLDSTARS_DEPLOY_DIR} CACHE INTERNAL "" FORCE)
        set(CMAKE_INSTALL_PREFIX "${COLDSTARS_DEPLOY_DIR}")
    endif()
endif()

# vars
set(PROJECT ${PROJECT_JETI})

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
add_subdirectory(src/jeti)

set(USE_APP ON)
if (USE_APP)
    add_subdirectory(app)
endif()

if (USE_TEST)
    add_subdirectory(test)
endif ()

