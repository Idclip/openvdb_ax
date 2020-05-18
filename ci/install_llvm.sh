#!/usr/bin/env bash

set -ex

LLVM_VERSION=$1
LLVM_ROOT_DIR=$2
if [ -z $LLVM_VERSION ]; then
    echo "No LLVM version provided for LLVM installation"
    exit -1
fi
if [ -z $LLVM_ROOT_DIR ]; then
    echo "No installation directory provided for LLVM installation"
    exit -1
fi

wget -O llvm-$LLVM_VERSION.tar.xz https://releases.llvm.org/$LLVM_VERSION/clang+llvm-$LLVM_VERSION-x86_64-linux-gnu-ubuntu-18.04.tar.xz

echo "Installing LLVM $LLVM_VERSION -> $LLVM_ROOT_DIR"
mkdir -p $LLVM_ROOT_DIR
tar xf llvm-$LLVM_VERSION.tar.xz --directory $LLVM_ROOT_DIR --strip 1
rm -f llvm-$LLVM_VERSION.tar.xz
