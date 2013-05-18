cmake_minimum_required (VERSION 2.8)

set(PROJECT run)

project (${PROJECT})
set(BIN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bin/ )

add_definitions(-Wall -pedantic -std=c++0x -std=gnu++0x -pedantic-errors -Wextra -w -Waddress -Wc++0x-compat)

include_directories(dependencies/SFML2/include/)

add_subdirectory(src/game)





