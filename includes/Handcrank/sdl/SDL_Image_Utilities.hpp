// Copyright (c) Scott Doxey. All Rights Reserved. Licensed under the MIT
// License. See LICENSE in the project root for license information.

#pragma once

#include <SDL.h>
#include <SDL_image.h>

/**
 * Load texture from a path.
 *
 * @param renderer A structure representing rendering state.
 * @param path File path to texture file.
 */
extern SDL_Texture *SDL_LoadTexture(SDL_Renderer *renderer, const char *path)
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

/**
 * Load texture from a read-only buffer.
 *
 * @param renderer A structure representing rendering state.
 * @param mem A pointer to a read-only buffer.
 * @param size The buffer size, in bytes.
 */
extern SDL_Texture *SDL_LoadTextureRW(SDL_Renderer *renderer, const void *mem,
                                      int size)
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
