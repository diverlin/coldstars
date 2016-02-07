cmake_minimum_required (VERSION 2.8)

set(PROJECT ${PROJECT_CORE})

file(GLOB_RECURSE ${PROJECT}_SOURCE RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
file(GLOB_RECURSE ${PROJECT}_HEADER RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.hpp)

if (NOT ENABLE_MODULES)
    file(GLOB_RECURSE ${PROJECT}_MODULES_SOURCE RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} builder/items/modules/*.cpp;items/modules/*.cpp)
    file(GLOB_RECURSE ${PROJECT}_MODULES_HEADER RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} builder/items/modules/*.hpp;items/modules/*.hpp)
    list(REMOVE_ITEM ${PROJECT}_SOURCE ${${PROJECT}_MODULES_SOURCE})
    list(REMOVE_ITEM ${PROJECT}_HEADER ${${PROJECT}_MODULES_HEADER})
endif()
if (NOT ENABLE_ARTEFACTS)
    file(GLOB_RECURSE ${PROJECT}_ARTEFACTS_SOURCE RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} builder/items/artefacts/*.cpp;items/artefacts/*.cpp)
    file(GLOB_RECURSE ${PROJECT}_ARTEFACTS_HEADER RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} builder/items/artefacts/*.hpp;items/artefacts/*.hpp)
    list(REMOVE_ITEM ${PROJECT}_SOURCE ${${PROJECT}_ARTEFACTS_SOURCE})
    list(REMOVE_ITEM ${PROJECT}_HEADER ${${PROJECT}_ARTEFACTS_HEADER})
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

if (NOT COMPILE_FLAGS)
    set(COMPILE_FLAGS "-Wall -Wno-switch -std=c++11 -std=gnu++11")
endif ()

find_package(SFML COMPONENTS system REQUIRED)
include_directories(${SFML_INCLUDE_DIR})
#message("SFML_LIBRARIES = ${SFML_LIBRARIES}")
#message("SFML_INCLUDE_DIR = ${SFML_INCLUDE_DIR}")

add_library (${PROJECT} SHARED ${${PROJECT}_SOURCE} ${${PROJECT}_HEADER})
target_link_libraries(${PROJECT}
    boost_system
    boost_serialization
    ${PROJECT_METI}
    ${PROJECT_CETI}
    ${SFML_LIBRARIES}
)
set_target_properties(${PROJECT} PROPERTIES COMPILE_FLAGS ${COMPILE_FLAGS})

