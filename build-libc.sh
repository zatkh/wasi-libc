#!/bin/bash

WASI_DIR=$PWD/../../build/install/opt/wasi-sdk
#sudo cp -a -R $WASI_DIR /opt/wasi-sdk
export PATH=$WASI_DIR/bin:$PATH
make install INSTALL_DIR=/tmp/wasi-libc
