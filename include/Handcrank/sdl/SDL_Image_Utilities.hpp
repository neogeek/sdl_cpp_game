// Copyright (c) Scott Doxey. All Rights Reserved. Licensed under the MIT
// License. See LICENSE in the project root for license information.

#pragma once

#include <memory>

#include <SDL.h>
#include <SDL_image.h>

namespace Handcrank
{

/**
 * Load texture from a path.
 *
 * @param renderer A structure representing rendering state.
 * @param path File path to texture file.
 *
 * @deprecated DEVELOPMENT USE ONLY! Use SDL_LoadTextureRW to load textures in a
 * release build.
 */
inline std::shared_ptr<SDL_Texture>
SDL_LoadTexture(std::shared_ptr<SDL_Renderer> renderer, const char *path)
{
    auto surface = IMG_Load(path);

    if (!surface)
    {
        return nullptr;
    }

    auto texture = std::shared_ptr<SDL_Texture>(
        SDL_CreateTextureFromSurface(renderer.get(), surface),
        SDL_DestroyTexture);

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
inline std::shared_ptr<SDL_Texture>
SDL_LoadTextureRW(std::shared_ptr<SDL_Renderer> renderer, const void *mem,
                  const int size)
{
    auto rw = SDL_RWFromConstMem(mem, size);

    auto surface = IMG_Load_RW(rw, 1);

    if (!surface)
    {
        return nullptr;
    }

    auto texture = std::shared_ptr<SDL_Texture>(
        SDL_CreateTextureFromSurface(renderer.get(), surface),
        SDL_DestroyTexture);

    SDL_FreeSurface(surface);

    if (!texture)
    {
        return nullptr;
    }

    return texture;
}

} // namespace Handcrank
