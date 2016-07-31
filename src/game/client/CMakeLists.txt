cmake_minimum_required (VERSION 2.8)

file(GLOB_RECURSE ${PROJECT_CLIENT}_SRC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
file(GLOB_RECURSE ${PROJECT_CLIENT}_HDR RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.hpp;ALL)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../common)

if (COMPILE_FLAGS)
    set(COMPILE_FLAGS ${COMPILE_FLAGS})
else ()
    set(COMPILE_FLAGS "-Wall -Wno-switch -std=c++11 -std=gnu++11")
endif ()

add_executable (${PROJECT_CLIENT} ${${PROJECT_CLIENT}_SRC} ${${PROJECT_CLIENT}_HDR})
target_link_libraries(${PROJECT_CLIENT}
    ${PROJECT_CORE}
    boost_system
    ${PROJECT_JETI}
    ${PROJECT_METI}
    ${PROJECT_CETI}
)
set_target_properties(${PROJECT_CLIENT} PROPERTIES COMPILE_FLAGS ${COMPILE_FLAGS})

# symlinks
add_custom_target(symlinks
    COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/src/jeti/shaders ${CMAKE_CURRENT_BINARY_DIR}/shaders # inject to jeti
    COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/data ${CMAKE_CURRENT_BINARY_DIR}/data
    COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/config/config.info ${CMAKE_CURRENT_BINARY_DIR}/config.info # inject to data
    )

# deploy
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_CLIENT} DESTINATION ${DEPLOY_DIR})
install(DIRECTORY ${CMAKE_SOURCE_DIR}/src/jeti/shaders DESTINATION ${DEPLOY_DIR}) # inject to jeti
install(DIRECTORY ${CMAKE_SOURCE_DIR}/data DESTINATION ${DEPLOY_DIR})
install(FILES ${CMAKE_SOURCE_DIR}/config/config.info DESTINATION ${DEPLOY_DIR}) # inject to data
