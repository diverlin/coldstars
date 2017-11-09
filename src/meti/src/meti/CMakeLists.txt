# collect sources
file(GLOB_RECURSE ${PROJECT}_SRC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
file(GLOB_RECURSE ${PROJECT}_HDR RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.hpp)

set(include_dirs ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/..)

# lib
add_library(${PROJECT} SHARED ${${PROJECT}_SRC} ${${PROJECT}_HDR})

# include dirs
include_directories(${include_dirs})

# target properties
set_target_properties(${PROJECT} PROPERTIES COMPILE_FLAGS ${COMPILE_FLAGS})

# install
install(TARGETS ${PROJECT}
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    )
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../"
    DESTINATION include
    FILES_MATCHING
    PATTERN "*.hpp"
    )

