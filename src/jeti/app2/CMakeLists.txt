cmake_minimum_required(VERSION 2.8)

set(PROJECT jeti_animator2d)
project(${PROJECT})

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5OpenGL REQUIRED)

# other deps
find_package(METI REQUIRED)
find_package(CETI REQUIRED)
find_package(JETI REQUIRED)
find_package(QETI REQUIRED)
include_directories(
    ${METI_INCLUDE_DIRS}
    ${CETI_INCLUDE_DIRS}
    ${JETI_INCLUDE_DIRS}
    ${QETI_INCLUDE_DIRS}
    ../src
    )

file(GLOB_RECURSE ${PROJECT}_SRC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
file(GLOB_RECURSE ${PROJECT}_HDR RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.hpp)

# create target
add_executable(${PROJECT}
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

target_link_libraries(${PROJECT}
    ${SFML_LIBRARIES}
    ${METI_LIBRARIES}
    ${CETI_LIBRARIES}
    ${JETI_LIBRARIES}
    ${QETI_LIBRARIES}
    )

# install
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../src/jeti/shaders"
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
    )

install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../../data"
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
    )
