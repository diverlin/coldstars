cmake_minimum_required (VERSION 2.8)

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

add_executable (${PROJECT} ${SOURCES})
target_link_libraries(${PROJECT} sfml-system sfml-graphics sfml-window  ${OPENGL_LIBRARIES} glew boost_system freetyperender)
SET_TARGET_PROPERTIES(${PROJECT} PROPERTIES COMPILE_FLAGS "-Wall -Wno-switch -std=c++11 -std=gnu++11 -pipe")
#SET_TARGET_PROPERTIES(${PROJECT} PROPERTIES COMPILE_FLAGS "-Wall -Werror -Wno-switch -std=c++11 -std=gnu++11 -pipe")
#SET_TARGET_PROPERTIES(${PROJECT} PROPERTIES COMPILE_FLAGS "-Wall -Wno-switch -std=c++11 -std=gnu++11 -Ofast -march=native")
#SET_TARGET_PROPERTIES(${PROJECT} PROPERTIES COMPILE_FLAGS "-Wall -Wno-switch -std=c++11 -std=gnu++11")
   
ADD_CUSTOM_COMMAND(
TARGET ${PROJECT}
POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT} ${BIN_DIR}
)

