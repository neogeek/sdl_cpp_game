#!/bin/bash

mkdir -p build/webgl

emcc -std=c++17 -o build/webgl/index.html src/*.cpp -Ifonts -Iimages -Iincludes \
    -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]' -s USE_SDL_TTF=2
