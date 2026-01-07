#! /bin/env sh

MAP_NAME=$1

mkdir -p out
unzip -p src/${MAP_NAME}.elev.zip | bin/postprocess_elev.py > out/tacview/${MAP_NAME}.dat
