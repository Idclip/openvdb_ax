#!/usr/bin/env bash

set -ex
apt-get update
apt-get install -y llvm-$LLVM_VERSION-dev
