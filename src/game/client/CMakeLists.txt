cmake_minimum_required (VERSION 2.8)

set(PROJECT ${PROJECT_CLIENT})
project (${PROJECT})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/../../macros/cmake")

add_subdirectory(src/client)

if (USE_TEST)
    add_subdirectory(test)
endif ()

