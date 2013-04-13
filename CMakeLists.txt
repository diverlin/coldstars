cmake_minimum_required (VERSION 2.8)

set(PROJECT cs)

project (${PROJECT})

add_definitions(-Wall -pedantic -std=c++0x -std=gnu++0x -pedantic-errors -Wextra -w -Waddress -Wc++0x-compat)

include_directories(dependencies/SFML2/include/)

add_subdirectory(src/game)

ADD_CUSTOM_COMMAND(
TARGET ${PROJECT}
POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT} ../bin/${PROJECT}
)
