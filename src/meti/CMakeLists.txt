cmake_minimum_required (VERSION 2.8)

if (NOT PROJECT_METI)
    set(PROJECT_METI ceti)
endif()

set(PROJECT ${PROJECT_METI})
project (${PROJECT})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/../../macros/cmake")

add_subdirectory(src/meti)

if (USE_TEST)
    add_subdirectory(test)
endif ()


