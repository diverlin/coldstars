cmake_minimum_required (VERSION 2.8)

if (NOT PROJECT_CETI)
    set(PROJECT_CETI ceti)
endif()

set(PROJECT ${PROJECT_CETI})
project (${PROJECT})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/../../macros/cmake")

add_subdirectory(src/ceti)

if (USE_TEST)
    add_subdirectory(test)
endif ()

