cmake_minimum_required (VERSION 2.8)

set(PROJECT ${PROJECT_TESTS})

file(GLOB_RECURSE ${PROJECT}_SOURCE RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
file(GLOB_RECURSE ${PROJECT}_HEADER RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.hpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

if (NOT COMPILE_FLAGS)
    set(COMPILE_FLAGS "-Wall -Wno-switch -std=c++11 -std=gnu++11")
endif ()

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
#message("GTEST_MAIN_LIBRARIES=${GTEST_MAIN_LIBRARIES}")
#message("GTEST_LIBRARIES=${GTEST_LIBRARIES}")
    
    
add_executable (${PROJECT} ${${PROJECT}_SOURCE} ${${PROJECT}_HEADER})
target_link_libraries(${PROJECT}
    ${PROJECT_CORE}
    ${GTEST_MAIN_LIBRARIES}
    ${GTEST_LIBRARIES}
    pthread
)
set_target_properties(${PROJECT} PROPERTIES COMPILE_FLAGS ${COMPILE_FLAGS})

# deploy
install(TARGETS ${PROJECT} DESTINATION ${DEPLOY_DIR})
