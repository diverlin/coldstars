cmake_minimum_required (VERSION 2.8)

set(PROJECT_CORE     ${PROJECT}_core)
set(PROJECT_SERVER   ${PROJECT}_server)
set(PROJECT_CLIENT   ${PROJECT}_client)
set(PROJECT_TESTS    ${PROJECT}_tests)

add_subdirectory(core)
add_subdirectory(server)
#add_subdirectory(client)
add_subdirectory(tests)
