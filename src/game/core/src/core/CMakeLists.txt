cmake_minimum_required (VERSION 2.8)

file(GLOB_RECURSE ${PROJECT}_SRC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
file(GLOB_RECURSE ${PROJECT}_HDR RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.hpp;ALL)

if (NOT USE_MODULES)
    file(GLOB_RECURSE ${PROJECT}_MODULES_SOURCE RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} builder/item/module/*.cpp;item/module/*.cpp)
    file(GLOB_RECURSE ${PROJECT}_MODULES_HEADER RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} builder/item/module/*.hpp;item/module/*.hpp)
    list(REMOVE_ITEM ${PROJECT}_SRC ${${PROJECT}_MODULES_SOURCE})
    list(REMOVE_ITEM ${PROJECT}_HDR ${${PROJECT}_MODULES_HEADER})
endif()
if (NOT USE_ARTEFACTS)
    file(GLOB_RECURSE ${PROJECT}_ARTEFACTS_SOURCE RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} builder/item/artefact/*.cpp;item/artefact/*.cpp)
    file(GLOB_RECURSE ${PROJECT}_ARTEFACTS_HEADER RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} builder/item/artefact/*.hpp;item/artefact/*.hpp)
    list(REMOVE_ITEM ${PROJECT}_SRC ${${PROJECT}_ARTEFACTS_SOURCE})
    list(REMOVE_ITEM ${PROJECT}_HDR ${${PROJECT}_ARTEFACTS_HEADER})
endif()
if (NOT USE_EXTRA_EQUIPMENT)
    file(GLOB_RECURSE ${PROJECT}_EXTRA_EQUIPMENT_SOURCE RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
        item/equipment/Energizer.cpp;
        item/equipment/Freezer.cpp
        builder/item/equipment/EnergizerBuilder.cpp;
        builder/item/equipment/FreezerBuilder.cpp
    )
    file(GLOB_RECURSE ${PROJECT}_EXTRA_EQUIPMENT_HEADER RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
        item/equipment/Energizer.hpp;
        item/equipment/Freezer.hpp;
        builder/item/equipment/EnergizerBuilder.hpp;
        builder/item/equipment/FreezerBuilder.hpp
    )

#    message("_EXTRA_EQUIPMENT_SOURCE=${${PROJECT}_EXTRA_EQUIPMENT_SOURCE}")
#    message("_EXTRA_EQUIPMENT_HEADER=${${PROJECT}_EXTRA_EQUIPMENT_HEADER}")

    list(REMOVE_ITEM ${PROJECT}_SRC ${${PROJECT}_EXTRA_EQUIPMENT_SOURCE})
    list(REMOVE_ITEM ${PROJECT}_HDR ${${PROJECT}_EXTRA_EQUIPMENT_HEADER})
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
#hack
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../client) # needs to load resources
#hack

if (NOT COMPILE_FLAGS)
    set(COMPILE_FLAGS "-Wall -Wno-switch -std=c++11 -std=gnu++11")
endif ()

find_package(SFML COMPONENTS system REQUIRED)
include_directories(${SFML_INCLUDE_DIR})
#message("SFML_LIBRARIES = ${SFML_LIBRARIES}")
#message("SFML_INCLUDE_DIR = ${SFML_INCLUDE_DIR}")

add_library (${PROJECT} SHARED ${${PROJECT}_SRC} ${${PROJECT}_HDR})
target_link_libraries(${PROJECT}
    boost_system
    boost_filesystem
    boost_serialization
    ${PROJECT_METI}
    ${PROJECT_CETI}
    ${SFML_LIBRARIES}
)
set_target_properties(${PROJECT} PROPERTIES COMPILE_FLAGS ${COMPILE_FLAGS})

