#pragma once

#include <SDL.h>
#include <SDL_image.h>

class SDL_Image_Utilities
{

public:
    static SDL_Texture *loadTexture(SDL_Renderer *renderer, const char *path)
    {
        SDL_Surface *surface = IMG_Load(path);

        if (!surface)
        {
            return NULL;
        }

        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);

        if (!texture)
        {
            return NULL;
        }

        return texture;
    }
};
