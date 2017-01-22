cmake_minimum_required (VERSION 2.8)

set(PROJECT ${PROJECT_TESTS})

file(GLOB_RECURSE ${PROJECT}_SRC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
file(GLOB_RECURSE ${PROJECT}_HDR RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.hpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

if (NOT COMPILE_FLAGS)
    set(COMPILE_FLAGS "-Wall -Wno-switch -std=c++11 -std=gnu++11")
endif ()

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
#message(FATAL_ERROR "GTEST_INCLUDE_DIRS=${GTEST_INCLUDE_DIRS}")
#message("GTEST_MAIN_LIBRARIES=${GTEST_MAIN_LIBRARIES}")
#message("GTEST_LIBRARIES=${GTEST_LIBRARIES}")
    
    
add_executable (${PROJECT} ${${PROJECT}_SRC} ${${PROJECT}_HDR})
target_link_libraries(${PROJECT}
    ${PROJECT_CORE}
    ${GTEST_MAIN_LIBRARIES}
    ${GTEST_LIBRARIES}
    pthread
)
set_target_properties(${PROJECT} PROPERTIES COMPILE_FLAGS ${COMPILE_FLAGS})

# deploy
install(TARGETS ${PROJECT} DESTINATION ${DEPLOY_DIR})
if (NOT EXISTS ${DEPLOY_DIR}/descriptors.txt)
    install(FILES ${CMAKE_SOURCE_DIR}/data/descriptors.txt DESTINATION ${DEPLOY_DIR})
endif()


#--gtest_filter=descriptor.*
