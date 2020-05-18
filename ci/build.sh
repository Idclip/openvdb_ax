#!/usr/bin/env bash

set -e

mkdir build
mkdir -p $HOME/install
cd build

cmake --version
cmake \
    -D OPENVDB_BUILD_AX=ON \
    -D OPENVDB_BUILD_AX_UNITTESTS=ON \
    -D OPENVDB_BUILD_AX_BINARIES=ON \
    -D OPENVDB_BUILD_AX_DOCS=OFF \
    -D OPENVDB_BUILD_AX_GRAMMAR=OFF \
    -D OPENVDB_BUILD_AX_PYTHON_MODULE=OFF \
    -D OPENVDB_CXX_STRICT=ON \
    -D CMAKE_INSTALL_PREFIX=$HOME/install \
    $@ \
    ../

make -j2
make install -j2
