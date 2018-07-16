cmake_minimum_required (VERSION 2.8)

set(PROJECT sandbox_demo)
project(${PROJECT})

add_executable(${PROJECT} main.cpp)
set_target_properties(${PROJECT} PROPERTIES COMPILE_FLAGS ${COMPILE_FLAGS})

target_link_libraries(${PROJECT} ${PROJECT_CORE} ${PROJECT_CLIENT})

# symlinks
add_custom_target(data_symlinks2 ALL
    COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/src/jeti/src/jeti/shaders ${CMAKE_CURRENT_BINARY_DIR}/shaders # inject to jeti
    COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/data ${CMAKE_CURRENT_BINARY_DIR}/data
    COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/config/config.info ${CMAKE_CURRENT_BINARY_DIR}/config.info # inject to data
    )

# deploy
#install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_CLIENT} DESTINATION ${DEPLOY_DIR})
#install(DIRECTORY ${CMAKE_SOURCE_DIR}/data DESTINATION ${DEPLOY_DIR})
#install(FILES ${CMAKE_SOURCE_DIR}/config/config.info DESTINATION ${DEPLOY_DIR}) # inject to data
