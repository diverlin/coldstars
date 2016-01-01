cmake_minimum_required (VERSION 2.8)

set(PROJECT ${PROJECT_CORE})

file(GLOB_RECURSE ${PROJECT}_SOURCE RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
file(GLOB_RECURSE ${PROJECT}_HEADER RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.hpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

if (NOT COMPILE_FLAGS)
    set(COMPILE_FLAGS "-Wall -Wno-switch -std=c++11 -std=gnu++11")
endif ()

find_package(SFML COMPONENTS system REQUIRED)
include_directories(${SFML_INCLUDE_DIR})
message("SFML_LIBRARIES = ${SFML_LIBRARIES}")
message("SFML_INCLUDE_DIR = ${SFML_INCLUDE_DIR}")

add_library (${PROJECT} SHARED ${${PROJECT}_SOURCE} ${${PROJECT}_HEADER})
target_link_libraries(${PROJECT}
    boost_system
    boost_serialization
    ${PROJECT_METI}
    ${PROJECT_CETI}
    ${SFML_LIBRARIES}
)
set_target_properties(${PROJECT} PROPERTIES COMPILE_FLAGS ${COMPILE_FLAGS})

