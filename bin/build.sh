#!/bin/bash

mkdir -p build/

g++ -std=c++17 -o build/sdl_cpp_game src/*.cpp -Ifonts -Iimages -Iincludes -Isrc \
    -I/opt/homebrew/Cellar/sdl2/2.28.4/include/SDL2 -L/opt/homebrew/Cellar/sdl2/2.28.4/lib \
    -I/opt/homebrew/Cellar/sdl2_image/2.6.3_2/include/SDL2 -L/opt/homebrew/Cellar/sdl2_image/2.6.3_2/lib \
    -I/opt/homebrew/Cellar/sdl2_ttf/2.20.2/include/SDL2 -L/opt/homebrew/Cellar/sdl2_ttf/2.20.2/lib \
    -lSDL2 -lSDL2_image -lSDL2_ttf
