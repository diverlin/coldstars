cmake_minimum_required (VERSION 2.8)

file(GLOB_RECURSE ${PROJECT_CLIENT}_SRC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
file(GLOB_RECURSE ${PROJECT_CLIENT}_HDR RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.hpp;ALL)
list(REMOVE_ITEM ${PROJECT_CLIENT}_SRC "main.cpp")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)

if (COMPILE_FLAGS)
    set(COMPILE_FLAGS ${COMPILE_FLAGS})
else ()
    set(COMPILE_FLAGS "-Wall -Wno-switch -std=c++11 -std=gnu++11")
endif ()

add_library (${PROJECT_CLIENT} SHARED
    ${${PROJECT_CLIENT}_SRC}
    ${${PROJECT_CLIENT}_HDR}
    )

target_link_libraries(${PROJECT_CLIENT}
    ${PROJECT_CORE}
    ${PROJECT_JETI}
    ${PROJECT_METI}
    ${PROJECT_CETI}
    pthread
    #"/media/yeti/ext_workspace/dist_gcc54/TGUI-0.7.4/lib/libtgui.so"
    "/media/yeti/ext_workspace/dist_gcc54/SFGUI-0.3.2/lib/libsfgui-d.so"
)
set_target_properties(${PROJECT_CLIENT} PROPERTIES COMPILE_FLAGS ${COMPILE_FLAGS})
add_executable(${PROJECT_CLIENT}_exec main.cpp)
target_link_libraries(${PROJECT_CLIENT}_exec
    ${PROJECT_CLIENT}
    ${PROJECT_CORE}
    ${PROJECT_JETI}
    ${PROJECT_METI}
    ${PROJECT_CETI}
    pthread
    )
set_target_properties(${PROJECT_CLIENT}_exec PROPERTIES COMPILE_FLAGS ${COMPILE_FLAGS})
set_target_properties(${PROJECT_CLIENT}_exec PROPERTIES OUTPUT_NAME "${PROJECT_CLIENT}")

# symlinks
add_custom_target(data_symlinks ALL
    COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/src/jeti/src/jeti/shaders ${CMAKE_CURRENT_BINARY_DIR}/shaders # inject to jeti
    COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/data ${CMAKE_CURRENT_BINARY_DIR}/data
    COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/config/config.info ${CMAKE_CURRENT_BINARY_DIR}/config.info # inject to data
    )

# deploy
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_CLIENT} DESTINATION ${DEPLOY_DIR})
install(DIRECTORY ${CMAKE_SOURCE_DIR}/src/jeti/shaders DESTINATION ${DEPLOY_DIR}) # inject to jeti
install(DIRECTORY ${CMAKE_SOURCE_DIR}/data DESTINATION ${DEPLOY_DIR})
install(FILES ${CMAKE_SOURCE_DIR}/config/config.info DESTINATION ${DEPLOY_DIR}) # inject to data
