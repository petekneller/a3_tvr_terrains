#! /bin/env sh

mkdir -p out/tacview
mkdir -p out/mod

bin/generate_elev_config.py
bin/generate_map_config.py
bin/generate_world_config.py