cmake_minimum_required (VERSION 2.8)

set(PROJECT sandbox_demo)
project(${PROJECT})

add_executable(${PROJECT} main.hpp main.cpp)
set_target_properties(${PROJECT} PROPERTIES COMPILE_FLAGS ${COMPILE_FLAGS})

