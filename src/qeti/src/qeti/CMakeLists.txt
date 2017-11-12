# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

include_directories(
    ../src
    )

file(GLOB_RECURSE ${PROJECT}_SRC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
file(GLOB_RECURSE ${PROJECT}_HDR RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.hpp)

# create target
add_library(${PROJECT} SHARED
    ${${PROJECT}_SRC}
    ${${PROJECT}_HDR}
    )
set_target_properties(${PROJECT} PROPERTIES COMPILE_FLAGS ${COMPILE_FLAGS})

# link
target_link_libraries(${PROJECT}
    Qt5::Core
    Qt5::Widgets
    Qt5::OpenGL
    )


# install
install(TARGETS ${PROJECT}
    RUNTIME DESTINATION bin
	ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    )
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../"
    DESTINATION include
    FILES_MATCHING
    PATTERN "*.hpp"
    )
