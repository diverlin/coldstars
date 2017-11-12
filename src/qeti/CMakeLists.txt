cmake_minimum_required (VERSION 2.8)

if (NOT PROJECT_METI)
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/../../macros/cmake")

    set(PROJECT_QETI "qeti")
    project(${PROJECT_QETI})

    if(NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE "Debug")
    endif()

    if(NOT COMPILE_FLAGS)
        set(COMPILE_FLAGS "-Wall -Wno-switch -std=c++11 -std=gnu++11")
    endif ()

    if(COLDSTARS_DEPLOY_DIR)
        set(CMAKE_INSTALL_PREFIX "${COLDSTARS_DEPLOY_DIR}")
    endif()
endif()

# vars
set(PROJECT ${PROJECT_QETI})

# find deps
find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5OpenGL REQUIRED)

# add modules
add_subdirectory(src/qeti)
