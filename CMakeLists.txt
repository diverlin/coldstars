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
	include.hpp

	src/config/config.hpp	
	src/common/SaveLoadManager.hpp
	src/pilots/WeaponSelector.hpp
	src/spaceobjects/Vehicle.hpp
)

set (SOURCES
	src/common/Logger.cpp
	src/config/config.cpp
	src/common/SaveLoadManager.cpp
	src/pilots/WeaponSelector.cpp
	src/spaceobjects/Vehicle.cpp

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
