Build on linux (tested on ubuntu 14.04):

####################
### DEPENDENCIES ###
####################
* install external dependencies from repository (tested on ubuntu 14.04):
    sudo apt-get install libglew-dev libglm-dev libsfml-dev

* OR manually compiled by:
    all deps can be build form coldstars_thirdparty(the package can be found in sourceforge section download in tar.gz) subproject just by running in terminal
    <cmake . && make>, from root folder

Note: you need override variable COLDSTARS_DEPENDENCIES_ROOT pointing to external libs
    For example: set(COLDSTARS_DEPENDENCIES_ROOT "/home/username/workspace/coldstars/coldstars_thirdparty_build/dist")
####################

#######################
### BUILD COLDSTARS ###
#######################
build coldstars with QtCreator, just open CMakeLists.txt
#######################

#####################
### RUN COLDSTARS ###
#####################
just execute ./run from the build directory
#####################
