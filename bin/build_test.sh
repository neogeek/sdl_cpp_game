#!/bin/bash

mkdir -p build/

g++ -std=c++17 -o build/sdl_cpp_game_test src/*.cpp -Ifonts -Iimages -Iincludes \
    -I/opt/homebrew/Cellar/sdl2/2.30.4/include/SDL2 -L/opt/homebrew/Cellar/sdl2/2.30.4/lib \
    -I/opt/homebrew/Cellar/sdl2_image/2.8.2_1/include/SDL2 -L/opt/homebrew/Cellar/sdl2_image/2.8.2_1/lib \
    -I/opt/homebrew/Cellar/sdl2_ttf/2.22.0/include/SDL2 -L/opt/homebrew/Cellar/sdl2_ttf/2.22.0/lib \
    -lSDL2 -lSDL2_image -lSDL2_ttf \
    -fsanitize=address
