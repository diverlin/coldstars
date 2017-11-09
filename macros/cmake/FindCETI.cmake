# FindCETI - attempts to locate the ceti library.
#
# This module defines the following variables (on success):
#   CETI_LIBRARIES     - meti libraries
#   CETI_INCLUDE_DIRS  - meti/meti.hpp location
#   CETI_FOUND         - if the library was successfully located
#
# It is trying a few standard installation locations, but can be customized
# with the following variables:
#   COLDSTARS_DEPLOY_DIR - root directory

set(_project "CETI")
set(_header "ceti/ceti.hpp")
set(_library "ceti")

include(FindYETI)
