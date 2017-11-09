# FindMETI - attempts to locate the meti library.
#
# This module defines the following variables (on success):
#   METI_LIBRARIES     - meti libraries
#   METI_INCLUDE_DIRS  - meti/meti.hpp location
#   METI_FOUND         - if the library was successfully located
#
# It is trying a few standard installation locations, but can be customized
# with the following variables:
#   COLDSTARS_DEPLOY_DIR - root directory

set(_project "METI")
set(_header "meti/meti.hpp")
set(_library "meti")

include(FindYETI)

