#!/bin/bash

#WASI_DIR=/opt/wasi-sdk
IWASM_DIR=../../wasm-micro-runtime/product-mini/platforms/linux/build
#sudo cp -a -R $WASI_DIR /opt/wasi-sdk
# PATH=$WASI_DIR/bin:$PATH


WASM_SYSROOT=/usr/local/vwasm/llvm-sysroot/
WASM_TOOLCHAIN_BIN=/usr/local/vwasm/toolchain/bin

WASM_CC=$WASM_TOOLCHAIN_BIN/clang
WASM_CXX=$WASM_TOOLCHAIN_BIN/clang++
WASM_CPP=$WASM_TOOLCHAIN_BIN/clang-cpp
WASM_AR=$WASM_TOOLCHAIN_BIN/llvm-ar
WASM_NM=$WASM_TOOLCHAIN_BIN/llvm.nm
WASM_RANLIB=$WASM_TOOLCHAIN_BIN/llvm-ranlib
WASM_LD=$WASM_TOOLCHAIN_BIN/wasm-ld
WASM_LDSHARED=$WASM_TOOLCHAIN_BIN/wasm-ld
SNMALLOC=../snmalloc/build/libsnmallocshim-static.a
WASM_LDFLAGS="-Xlinker --stack-first -Xlinker --no-check-features"

 WASM_BUILD=wasm32
 WASM_HOST=wasm32-unknown-wasi
 WASM_HOST_UNKNOWN=wasm32-unknown-unknown

# Note potential performance gains from unimplemented-simd128 here.
# May not be necessary in future.
WASM_CFLAGS_NO_QUOTES=-O3 --sysroot=$WASM_SYSROOT -msimd128 -munimplemented-simd128 -mno-atomics -D__vwasm
 WASM_CXXFLAGS_NO_QUOTES=$WASM_CFLAGS_NO_QUOTES
 WASM_CFLAGS=$WASM_CFLAGS_NO_QUOTES
 WASM_CXXFLAGS=$WASM_CXXFLAGS_NO_QUOTES

$WASM_CC --target=wasm32-wasi -O3 --sysroot $WASM_SYSROOT -msimd128 -munimplemented-simd128 -mno-atomics -D__vwasm -o test.wasm test.c $SNMALLOC

#$WASM_CXX --target=wasm32-wasi -O3 --sysroot $WASM_SYSROOT -msimd128 -munimplemented-simd128 -mno-atomics -D__vwasm -o test-cpp.wasm test.cpp
  
$IWASM_DIR/iwasm test.wasm  
#IWASM_DIR/iwasm test-cpp.wasm 
