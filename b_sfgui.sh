#!/bin/sh

SOURCE_ROOT=/workspace/src
BUILD_ROOT=/media/yeti/ext_workspace/build_gcc54
DIST_ROOT=/media/yeti/ext_workspace/dist_gcc54
THREADS_NUM=8

PROJECT=SFGUI-0.3.2

SOURCE_DIR=${SOURCE_ROOT}/${PROJECT}
BUILD_DIR=${BUILD_ROOT}/${PROJECT}
DIST_DIR=${DIST_ROOT}/${PROJECT}

mkdir -p ${BUILD_DIR}

cd ${BUILD_DIR} &&
cmake \
-DCMAKE_PREFIX_PATH:STRING=${DIST_ROOT}/SFML-2.4.2 \
-DCMAKE_INSTALL_PREFIX:PATH=${DIST_DIR} \
${SOURCE_DIR} &&

make -j${THREADS_NUM} &&
make install
