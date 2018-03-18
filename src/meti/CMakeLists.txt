cmake_minimum_required (VERSION 2.8)

set(CUSTOM_CMAKE_MODULE_RELPATH "../../macros/cmake/macros.cmake")
include(${CUSTOM_CMAKE_MODULE_RELPATH})
MACRO_INIT_PROJECT("meti")

# find deps
find_package(GLM REQUIRED)
include_directories(${GLM_INCLUDE_DIRS})
add_definitions(-DGLM_FORCE_RADIANS)

MACRO_BUILD_MODULE()


