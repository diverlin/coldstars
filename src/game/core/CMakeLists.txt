cmake_minimum_required (VERSION 2.8)

file(GLOB_RECURSE ${PROJECT}_CORE_SOURCE RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
file(GLOB_RECURSE ${PROJECT}_CORE_HEADER RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.hpp)

add_executable (${PROJECT} ${${PROJECT}_CORE_SOURCE} ${${PROJECT}_CORE_HEADER})
target_link_libraries(${PROJECT}
    boost_system
    meti
    ceti
)

#SET_TARGET_PROPERTIES(${PROJECT} PROPERTIES COMPILE_FLAGS "-Wall -Werror -Wno-switch -std=c++11 -std=gnu++11 -pipe")
#SET_TARGET_PROPERTIES(${PROJECT} PROPERTIES COMPILE_FLAGS "-Wall -Wno-switch -std=c++11 -std=gnu++11 -Ofast -march=native")
SET_TARGET_PROPERTIES(${PROJECT} PROPERTIES COMPILE_FLAGS "-Wall -Wno-switch -std=c++11 -std=gnu++11")
   
# deploy
ADD_CUSTOM_COMMAND(
    TARGET ${PROJECT}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink ${SOURCE_ROOT}/config/config.info ${DEPLOY_DIR}/config.info
)
install(FILES ${CMAKE_BINARY_DIR}/${PROJECT} DESTINATION ${DEPLOY_DIR})
