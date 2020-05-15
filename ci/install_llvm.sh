#!/usr/bin/env bash

set -ex

wget -O llvm-$LLVM_VERSION.tar.xz https://releases.llvm.org/$LLVM_VERSION/clang+llvm-$LLVM_VERSION-x86_64-linux-gnu-ubuntu-16.04.tar.xz

echo "Installing LLVM $LLVM_VERSION -> $LLVM_ROOT_DIR"
mkdir -p $LLVM_ROOT_DIR
tar xf llvm-$LLVM_VERSION.tar.xz --directory $LLVM_ROOT_DIR --strip 1
rm -f llvm-$LLVM_VERSION.tar.xz
