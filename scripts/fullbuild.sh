#!/bin/bash 
src_dir=`pwd`
build_dir=/mnt/ramdisk/build-coldstars
rm -Rf ${build_dir}
mkdir -p ${build_dir}
cd ${build_dir}
cmake ${src_dir}
make -j5

