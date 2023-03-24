#!/bin/bash
workdir=$(pwd)
# Raygui
echo 'Building raygui...'
cd ${workdir}/submodules/raygui
cp src/raygui.h src/raygui.c
gcc -o raygui.dynlib src/raygui.c -shared -fpic -DRAYGUI_IMPLEMENTATION -framework OpenGL -lm -lpthread -ldl $(pkg-config --libs --cflags raylib)
cp raygui.dynlib ${workdir}/libs
echo 'raygui done'

# logger
echo 'Building logger...'
cd ${workdir}/submodules/logger
rm -rf build
mkdir build && cd build
cmake .. && make -j
cp ${workdir}/submodules/logger/build/libspdlog.a ${workdir}/libs
echo 'logger done.'