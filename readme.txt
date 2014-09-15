
Build on linux (tested on ubuntu 14.04):

1) external dependencies <glew>, <glm>, <sfml2> must be installed (tested on ubuntu 14.04)

OR manually compiled by:

1.1) all deps can be build form coldstars_thirdparty(the package can be found in sourceforge section download in tar.gz) subproject just by running in terminal
        <cmake . && make> 
        from root folder, or each package can be installed via packagemanager or compiled from source and installed separatelly (with using make install)

1.2) in coldstars root folder in file CMakeLists.txt override variable COLDSTARS_DEPENDENCIES_ROOT where you external libraries are
   set(COLDSTARS_DEPENDENCIES_ROOT "/home/balda/workspace/cold_star/coldstars_thirdparty_build/dist")

2) build with QtCreator, just open CMakeLists.txt

3) run ./run from the build directory
 
