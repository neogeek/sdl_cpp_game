#!/bin/bash

SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)

(

    mkdir -p build/

    cd "${SCRIPT_DIR}" || exit

    . find-sdl.sh

    cd ..

    g++ -std=c++17 -o build/sdl_cpp_game src/*.cpp -Ifonts -Iimages -Iinclude -Isrc \
        -I"${SDL2_PATH}/include/SDL2" -L"${SDL2_PATH}/lib" \
        -I"${SDL2_IMAGE_PATH}/include/SDL2" -L"${SDL2_IMAGE_PATH}/lib" \
        -I"${SDL2_TTF_PATH}/include/SDL2" -L"${SDL2_TTF_PATH}/lib" \
        -lSDL2 -lSDL2_image -lSDL2_ttf

)
