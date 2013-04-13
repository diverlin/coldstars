#!/bin/bash 
rm -Rf build
mkdir build
cd build
cmake ..
make -j5
