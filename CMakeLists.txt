cmake_minimum_required (VERSION 2.6)

set (PROJECT game)

project (${PROJECT})

#include_directories (share/)

set (LIBRARIES
  )
#foreach (LIBRARY ${LIBRARIES})
  #  add_subdirectory (share/${LIBRARY}/ bin/${LIBRARY})
  #endforeach()

add_definitions (-Wall -pedantic -std=c++0x -std=gnu++0x -pedantic-errors -Wextra -w -Waddress -Wc++0x-compat)

set (HEADERS
	src/config/config.hpp
	
	src/gui/Window.hpp
	include.hpp
)

set (SOURCES
	src/config/config.cpp
	src/gui/Window.cpp
  main.cpp
)

add_executable (${PROJECT} ${HEADERS} ${SOURCES})
target_link_libraries (${PROJECT} ${LIBRARIES} sfml-system sfml-graphics sfml-graphics sfml-window GL GLU GLEW)
target_link_libraries (${PROJECT})

ADD_CUSTOM_COMMAND(
  TARGET ${PROJECT}
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT} ../install/${PROJECT}
  )
