# collect source
file(GLOB_RECURSE ${PROJECT}_SRC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
file(GLOB_RECURSE ${PROJECT}_HDR RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.hpp)

include_directories(${METI_INCLUDE_DIRS})

# create library
add_library(${PROJECT} SHARED ${${PROJECT}_SRC} ${${PROJECT}_HDR})

# link
target_link_libraries(${PROJECT} 
    boost_system
    boost_filesystem
    boost_serialization
    ${METI_LIBRARIES}
    )

# target properties
set(include_dirs
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/..
    )
set_target_properties(${PROJECT} PROPERTIES COMPILE_FLAGS ${COMPILE_FLAGS})
target_include_directories(${PROJECT} PUBLIC
  ${include_dirs}
)
set_property(TARGET ${PROJECT} PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${include_dirs})

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
