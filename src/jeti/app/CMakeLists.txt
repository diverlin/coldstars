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

set(SRC 
main.cpp 
openglwindow.cpp)

set(HDR
openglwindow.hpp)

# create target
add_executable(${PROJECT} ${SRC} ${HDR})

# link
target_link_libraries(${PROJECT} Qt5::Core Qt5::Widgets)
