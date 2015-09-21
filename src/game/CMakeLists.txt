cmake_minimum_required (VERSION 2.8)

set(PROJECT_CORE     ${PROJECT}_core)
set(PROJECT_SERVER   ${PROJECT}_server)
set(PROJECT_CLIENT   ${PROJECT}_client)

add_subdirectory(core)
add_subdirectory(server)
#add_subdirectory(client)
