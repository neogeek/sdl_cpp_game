#!/bin/bash

[[ ! -d "${SDL2_PATH}" && -d "/opt/homebrew/Cellar/sdl2" ]] &&
    export SDL2_PATH=$(find /opt/homebrew/Cellar/sdl2 -name "2.*" -type d | head -n 1)
[[ ! -d "${SDL2_PATH}" && -d "/tmp/.sdl/" ]] &&
    export SDL2_PATH=$(find /tmp/.sdl/ -name "SDL2-2.*" -type d | head -n 1)

[ ! -d "${SDL2_PATH}" ] && echo "SDL2 not found!" && exit 1

echo "SDL2 found at ${SDL2_PATH}"

[[ ! -d "${SDL2_IMAGE_PATH}" && -d "/opt/homebrew/Cellar/sdl2_image" ]] &&
    export SDL2_IMAGE_PATH=$(find /opt/homebrew/Cellar/sdl2_image -name "2.*" -type d | head -n 1)
[[ ! -d "${SDL2_IMAGE_PATH}" && -d "/tmp/.sdl/" ]] &&
    export SDL2_IMAGE_PATH=$(find /tmp/.sdl/ -name "SDL2_image-2.*" -type d | head -n 1)

[ ! -d "${SDL2_IMAGE_PATH}" ] && echo "SDL2_image not found!" && exit 1

echo "SDL2_image found at ${SDL2_IMAGE_PATH}"

[[ ! -d "${SDL2_TTF_PATH}" && -d "/opt/homebrew/Cellar/sdl2_ttf" ]] &&
    export SDL2_TTF_PATH=$(find /opt/homebrew/Cellar/sdl2_ttf -name "2.*" -type d | head -n 1)
[[ ! -d "${SDL2_TTF_PATH}" && -d "/tmp/.sdl/" ]] &&
    export SDL2_TTF_PATH=$(find /tmp/.sdl/ -name "SDL2_ttf-2.*" -type d | head -n 1)

[ ! -d "${SDL2_TTF_PATH}" ] && echo "SDL2_ttf not found!" && exit 1

echo "SDL2_ttf found at ${SDL2_TTF_PATH}"
