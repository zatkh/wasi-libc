#!/bin/bash

WASI_DIR=$PWD/../../build/install/opt/wasi-sdk
IWASM_DIR=/home/zt/Documents/git/verona-mc/verona/src/rt/external/wasm-micro-runtime/product-mini/platforms/linux/build
#sudo cp -a -R $WASI_DIR /opt/wasi-sdk
export PATH=$WASI_DIR/bin:$PATH

clang --target=wasm32-unknown-wasi --sysroot /tmp/wasi-libc \
  -O2 -s -o test.wasm test.c

$IWASM_DIR/iwasm test.wasm  
