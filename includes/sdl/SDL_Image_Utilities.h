#pragma once

#include <SDL.h>
#include <SDL_image.h>

class SDL_Image_Utilities
{

public:
    static SDL_Texture *LoadTexture(SDL_Renderer *renderer, const char *path)
    {
        SDL_Surface *surface = IMG_Load(path);

        if (!surface)
        {
            return nullptr;
        }

        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

        SDL_FreeSurface(surface);

        if (!texture)
        {
            return nullptr;
        }

        return texture;
    }

    static SDL_Texture *LoadTextureRW(SDL_Renderer *renderer, const void *mem, int size)
    {
        SDL_RWops *rw = SDL_RWFromConstMem(mem, size);

        SDL_Surface *surface = IMG_Load_RW(rw, 1);

        if (!surface)
        {
            return nullptr;
        }

        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

        SDL_FreeSurface(surface);

        if (!texture)
        {
            return nullptr;
        }

        return texture;
    }
};
