#!/usr/bin/env bash

set -ex

# As recommended by https://apt.llvm.org/
wget https://apt.llvm.org/llvm.sh
chmod +x llvm.sh
sudo ./llvm.sh $LLVM_VERSION
