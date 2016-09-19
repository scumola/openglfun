#!/bin/sh

git submodule init
git submodule update

# build glfw
cd submodules/glfw
cmake .
make -j4

