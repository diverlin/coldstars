#!/bin/bash 
rm -Rf ../coldstars_build
mkdir ../coldstars_build
cd ../coldstars_build
cmake ../coldstars
make -j5

