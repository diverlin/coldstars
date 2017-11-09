# FindJETI - attempts to locate the jeti library.
#
# This module defines the following variables (on success):
#   JETI_LIBRARIES     - jeti libraries
#   JETI_INCLUDE_DIRS  - jeti/jeti.hpp location
#   JETI_FOUND         - if the library was successfully located
#
# It is trying a few standard installation locations, but can be customized
# with the following variables:
#   COLDSTARS_DEPLOY_DIR      - root directory

set(_project "JETI")
set(_header "jeti/jeti.hpp")
set(_library "jeti")

include(FindYETI)
