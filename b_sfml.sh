#!/bin/sh

SOURCE_ROOT=/workspace/src
BUILD_ROOT=/media/yeti/ext_workspace/build_gcc54
DIST_ROOT=/media/yeti/ext_workspace/dist_gcc54
THREADS_NUM=8

PROJECT=SFML-2.4.2

SOURCE_DIR=${SOURCE_ROOT}/${PROJECT}
BUILD_DIR=${BUILD_ROOT}/${PROJECT}
DIST_DIR=${DIST_ROOT}/${PROJECT}

mkdir -p ${BUILD_DIR}

cd ${BUILD_DIR} &&
cmake \
-DSFML_BUILD_EXAMPLES:BOOL=1 \
-DCMAKE_INSTALL_PREFIX:PATH=${DIST_DIR} \
${SOURCE_DIR} &&

make -j${THREADS_NUM} &&
make install


