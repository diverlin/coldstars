# collect source
file(GLOB_RECURSE ${PROJECT}_SRC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
file(GLOB_RECURSE ${PROJECT}_HDR RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.hpp)

add_library(freetyperender ../../../../dependencies/freetype2/src/FreeType.cpp)
set_target_properties(freetyperender PROPERTIES COMPILE_FLAGS ${COMPILE_FLAGS})
include_directories(dependencies/freetype2/src)

set(include_dirs
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/..
    ${METI_INCLUDE_DIRS}
    ${CETI_INCLUDE_DIRS}
    )

add_library(${PROJECT_JETI} SHARED
    ${${PROJECT}_SRC}
    ${${PROJECT}_HDR}
    )
target_link_libraries(${PROJECT_JETI}
    ${METI_LIBRARIES}
    ${CETI_LIBRARIES}
    ${SFML_LIBRARIES}
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
    freetyperender
    ${FREETYPE_LIBRARIES}
)
target_include_directories(${PROJECT_JETI} PUBLIC
  ${include_dirs}
)
set_property(TARGET ${PROJECT} PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${include_dirs})

set_target_properties(${PROJECT} PROPERTIES COMPILE_FLAGS ${COMPILE_FLAGS})

# install
install(TARGETS ${PROJECT}
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    )
install(TARGETS freetyperender
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    )
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../"
    DESTINATION include
    FILES_MATCHING
    PATTERN "*.hpp"
    )
install(DIRECTORY shaders
    DESTINATION ${DEPLOY_DIR}
    FILES_MATCHING
    PATTERN "*.vert"
    PATTERN "*.frag"
    )
