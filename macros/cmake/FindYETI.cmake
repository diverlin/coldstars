# check loc
if(NOT COLDSTARS_DEPLOY_DIR)
    message(FATAL_ERROR "cmake var COLDSTARS_DEPLOY_DIR=${COLDSTARS_DEPLOY_DIR} is not set, but needed")
endif()

# default search dirs
set(${_project}_HEADER_SEARCH_DIRS
    "${COLDSTARS_DEPLOY_DIR}"
    "${COLDSTARS_DEPLOY_DIR}/include"
    )

# default search libs
set(${_project}_LIBRARY_SEARCH_DIRS
    "${COLDSTARS_DEPLOY_DIR}"
    "${COLDSTARS_DEPLOY_DIR}/lib"
    )

# locate header
find_path(${_project}_INCLUDE_DIR "${_header}"
    PATHS ${${_project}_HEADER_SEARCH_DIRS})

# locate library
find_library(${_project}_LIBRARY NAMES "${_library}"
    PATHS ${${_project}_LIBRARY_SEARCH_DIRS}
    )

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(${_project} DEFAULT_MSG
    ${_project}_INCLUDE_DIR
    ${_project}_LIBRARY
    )

if(${_project}_FOUND)
    set(${_project}_INCLUDE_DIRS "${${_project}_INCLUDE_DIR}")
    set(${_project}_LIBRARIES "${${_project}_LIBRARY}")
    message(STATUS "${_project}_LIBRARIES = ${${_project}_LIBRARIES}")
    message(STATUS "${_project}_INCLUDE_DIRS = ${${_project}_INCLUDE_DIRS}")
endif()
