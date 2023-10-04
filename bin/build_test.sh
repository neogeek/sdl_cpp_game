#!/bin/bash

mkdir -p build/

g++ -std=c++17 -o build/sdl_cpp_game_test src/*.cpp -Ifonts -Iimages -Iincludes \
    -I/opt/homebrew/Cellar/sdl2/2.28.3/include/SDL2 -L/opt/homebrew/Cellar/sdl2/2.28.3/lib \
    -I/opt/homebrew/Cellar/sdl2_image/2.6.3_2/include/SDL2 -L/opt/homebrew/Cellar/sdl2_image/2.6.3_2/lib \
    -I/opt/homebrew/Cellar/sdl2_ttf/2.20.2/include/SDL2 -L/opt/homebrew/Cellar/sdl2_ttf/2.20.2/lib \
    -lSDL2 -lSDL2_image -lSDL2_ttf \
    -fsanitize=address
