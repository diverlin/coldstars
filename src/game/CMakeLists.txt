cmake_minimum_required (VERSION 2.8)

set(SUBPROJECT_COMMON   ${PROJECT}_common)
set(SUBPROJECT_CORE     ${PROJECT}_core)
set(SUBPROJECT_CLIENT   ${PROJECT}_client)

add_subdirectory(common)
add_subdirectory(core)
add_subdirectory(client)
