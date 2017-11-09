cmake_minimum_required (VERSION 2.8)

set(PROJECT "jeti")
project (${PROJECT})

# vars
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/../../macros/cmake")

# default flags
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

if (NOT COMPILE_FLAGS)
    set(COMPILE_FLAGS "-Wall -Wno-switch -std=c++11 -std=gnu++11")
endif ()


# add
add_subdirectory(src/jeti)

if (USE_APP)
    add_subdirectory(app)
endif()

if (USE_TEST)
    add_subdirectory(test)
endif ()

