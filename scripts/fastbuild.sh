#!/bin/bash 
src_dir=`pwd`
build_dir=/mnt/ramdisk/build-coldstars
mkdir -p ${build_dir}
cd ${build_dir}
cmake ${src_dir}
make -j5

