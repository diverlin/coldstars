#!/bin/sh



PROJECT=$1

SOURCE_ROOT=/workspace/projects/coldstars/src
BUILD_ROOT=/media/yeti/ext_workspace/build_gcc54
DIST_ROOT=/media/yeti/ext_workspace/dist_gcc54/coldstars
THREADS_NUM=8

SOURCE_DIR=${SOURCE_ROOT}/${PROJECT}
BUILD_DIR=${BUILD_ROOT}/${PROJECT}
DIST_DIR=${DIST_ROOT}/${PROJECT}

mkdir -p ${BUILD_DIR}

cd ${BUILD_DIR} &&
cmake \
-DCOLDSTARS_DEPLOY_DIR:STRING=${DIST_ROOT} \
${SOURCE_DIR} &&

make -j${THREADS_NUM} &&
make install


