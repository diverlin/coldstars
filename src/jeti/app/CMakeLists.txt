cmake_minimum_required(VERSION 2.8)

set(PROJECT jeti_demo)
project(${PROJECT})

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)

# jeti
find_package(METI REQUIRED)
find_package(CETI REQUIRED)
find_package(JETI REQUIRED)
include_directories(
    ${METI_INCLUDE_DIRS}
    ${CETI_INCLUDE_DIRS}
    ${JETI_INCLUDE_DIRS}
    ../src
    )

set(SRC 
    main.cpp
    openglwindow.cpp)

set(HDR
    openglwindow.hpp)

# create target
add_executable(${PROJECT} ${SRC} ${HDR})
set_target_properties(${PROJECT} PROPERTIES COMPILE_FLAGS ${COMPILE_FLAGS})

# link
target_link_libraries(${PROJECT}
    Qt5::Core
    Qt5::Widgets
    )

target_link_libraries(${PROJECT}
#    boost_system
#    boost_filesystem
#    boost_serialization
    ${SFML_LIBRARIES}
    ${METI_LIBRARIES}
    ${CETI_LIBRARIES}
    ${JETI_LIBRARIES}
    )

install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../src/jeti/shaders"
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
    )
