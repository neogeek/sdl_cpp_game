#!/bin/bash

mkdir -p build/

g++ -std=c++17 -o build/sdl_cpp_game src/*.cpp -Ifonts -Iimages -Iincludes -Isrc \
    -I/opt/homebrew/Cellar/sdl2/2.30.6/include/SDL2 -L/opt/homebrew/Cellar/sdl2/2.30.6/lib \
    -I/opt/homebrew/Cellar/sdl2_image/2.8.2_1/include/SDL2 -L/opt/homebrew/Cellar/sdl2_image/2.8.2_1/lib \
    -I/opt/homebrew/Cellar/sdl2_ttf/2.22.0/include/SDL2 -L/opt/homebrew/Cellar/sdl2_ttf/2.22.0/lib \
    -framework CoreMIDI -framework CoreFoundation \
    -lSDL2 -lSDL2_image -lSDL2_ttf
