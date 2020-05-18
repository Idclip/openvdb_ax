#!/usr/bin/env bash

set -ex

echo "Building openvdb_ax..."

mkdir build
mkdir -p $HOME/install
cd build

echo "Testing aginst LLVM version $LLVM_VERSION"

LLVM_DIR="/usr/lib/llvm-$LLVM_VERSION/share/llvm/cmake"
if [ "$TRAVIS_OS_NAME" = "osx" ]; then
    LLVM_DIR="/usr/local/opt/llvm@$LLVM_VERSION/lib/cmake/llvm"
fi

cmake --version
cmake \
    -D OPENVDB_BUILD_AX=ON \
    -D OPENVDB_BUILD_AX_DOCS=ON \
    -D OPENVDB_BUILD_AX_UNITTESTS=ON \
    -D OPENVDB_BUILD_AX_BINARIES=ON \
    -D OPENVDB_BUILD_AX_GRAMMAR=OFF \
    -D OPENVDB_BUILD_AX_PYTHON_MODULE=OFF \
    -D OPENVDB_CXX_STRICT=ON \
    -D LLVM_DIR=$LLVM_DIR \
    -D OPENVDB_ROOT=$HOME/openvdb/install \
    -D CMAKE_INSTALL_PREFIX=$HOME/install \
    ../

make -j2
make install -j2

ctest -V
