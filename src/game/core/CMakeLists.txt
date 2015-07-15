cmake_minimum_required (VERSION 2.8)

set(SUBPROJECT ${SUBPROJECT_CORE})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../common)

file(GLOB_RECURSE ${SUBPROJECT}_SOURCE RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
file(GLOB_RECURSE ${SUBPROJECT}_HEADER RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.hpp)

add_executable (${SUBPROJECT} ${${SUBPROJECT}_SOURCE} ${${SUBPROJECT}_HEADER})
target_link_libraries(${SUBPROJECT}
    ${SUBPROJECT_COMMON}
    boost_system
    meti
    ceti
)

#SET_TARGET_PROPERTIES(${SUBPROJECT} PROPERTIES COMPILE_FLAGS "-Wall -Werror -Wno-switch -std=c++11 -std=gnu++11 -pipe")
#SET_TARGET_PROPERTIES(${SUBPROJECT} PROPERTIES COMPILE_FLAGS "-Wall -Wno-switch -std=c++11 -std=gnu++11 -Ofast -march=native")
SET_TARGET_PROPERTIES(${SUBPROJECT} PROPERTIES COMPILE_FLAGS "-Wall -Wno-switch -std=c++11 -std=gnu++11")
   
# deploy
ADD_CUSTOM_COMMAND(
    TARGET ${SUBPROJECT}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink ${SOURCE_ROOT}/config/config.info ${DEPLOY_DIR}/config.info
)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${SUBPROJECT} DESTINATION ${DEPLOY_DIR})
