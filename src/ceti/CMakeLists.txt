cmake_minimum_required (VERSION 2.8)

if (NOT PROJECT_CETI)
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/../../macros/cmake")

    set(PROJECT_CETI "ceti")
    project(${PROJECT_CETI})

    if(NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE "Debug")
    endif()

    if(NOT COMPILE_FLAGS)
        set(COMPILE_FLAGS "-Wall -Wno-switch -std=c++11 -std=gnu++11")
    endif()

    if(COLDSTARS_DEPLOY_DIR)
        set(CMAKE_INSTALL_PREFIX "${COLDSTARS_DEPLOY_DIR}")
    endif()
endif()

# vars
set(PROJECT ${PROJECT_CETI})

### find deps

# glm
set(GLM_ROOT_DIR "../../../dependencies/glm-0.9.7.5/")
find_package(GLM REQUIRED)
include_directories(${GLM_INCLUDE_DIRS})
add_definitions(-DGLM_FORCE_RADIANS)

# meti
find_package(METI REQUIRED)

# add modules
add_subdirectory(src/ceti)

if(USE_TEST)
    add_subdirectory(test)
endif()


