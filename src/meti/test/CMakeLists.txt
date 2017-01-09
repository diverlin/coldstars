cmake_minimum_required (VERSION 2.8)

set(PROJECT_TESTS "meti_test")
set(PROJECT ${PROJECT_TESTS})

file(GLOB_RECURSE ${PROJECT}_SRC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
file(GLOB_RECURSE ${PROJECT}_HDR RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.hpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

if (NOT COMPILE_FLAGS)
    set(COMPILE_FLAGS "-Wall -Wno-switch -std=c++11 -std=gnu++11")
endif ()

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
    
include_directories(../src)
add_executable (${PROJECT} ${${PROJECT}_SRC} ${${PROJECT}_HDR})
target_link_libraries(${PROJECT}
    ${PROJECT_METI}
    ${PROJECT_CETI}
    ${GTEST_MAIN_LIBRARIES}
    ${GTEST_LIBRARIES}
    pthread
)
set_target_properties(${PROJECT} PROPERTIES COMPILE_FLAGS ${COMPILE_FLAGS})


#--gtest_filter=descriptor.*
