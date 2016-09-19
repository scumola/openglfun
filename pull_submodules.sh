#!/bin/sh

git submodule init
git submodule update

# build glfw
cd submodules/glfw
cmake .
mkdir glfw-build
cd glfw-build
cmake ..

