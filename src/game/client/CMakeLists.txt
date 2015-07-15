cmake_minimum_required (VERSION 2.8)

set(SUBPROJECT ${PROJECT}_CLIENT)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB_RECURSE ${SUBPROJECT}_SOURCE RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
file(GLOB_RECURSE ${SUBPROJECT}_HEADER RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.hpp)

#message("${${subproject}_SOURCE}")
#message("${${subproject}_HEADER}")

add_executable (${SUBPROJECT} ${${SUBPROJECT}_SOURCE} ${${SUBPROJECT}_HEADER})
target_link_libraries(${SUBPROJECT}
    boost_system
    jeti
    meti
    ceti
)

#SET_TARGET_PROPERTIES(${SUBPROJECT}_CLIENT PROPERTIES COMPILE_FLAGS "-Wall -Werror -Wno-switch -std=c++11 -std=gnu++11 -pipe")
#SET_TARGET_PROPERTIES(${SUBPROJECT}_CLIENT PROPERTIES COMPILE_FLAGS "-Wall -Wno-switch -std=c++11 -std=gnu++11 -Ofast -march=native")
SET_TARGET_PROPERTIES(${SUBPROJECT} PROPERTIES COMPILE_FLAGS "-Wall -Wno-switch -std=c++11 -std=gnu++11")
   
# deploy
#ADD_CUSTOM_COMMAND(
    #TARGET ${SUBPROJECT}
    #POST_BUILD
    #COMMAND ${CMAKE_COMMAND} -E create_symlink ${SOURCE_ROOT}/data ${DEPLOY_DIR}/data
    #COMMAND ${CMAKE_COMMAND} -E create_symlink ${SOURCE_ROOT}/config/config.info ${DEPLOY_DIR}/config.info
#)

#install(FILES ${CMAKE_BINARY_DIR}/${SUBPROJECT} DESTINATION ${DEPLOY_DIR})
#install(DIRECTORY ${CMAKE_SOURCE_DIR}/src/jeti/shaders DESTINATION ${DEPLOY_DIR})
