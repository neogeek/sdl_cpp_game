// Copyright (c) Scott Doxey. All Rights Reserved. Licensed under the MIT
// License. See LICENSE in the project root for license information.

#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

namespace Handcrank
{

/**
 * Load font from a path.
 *
 * @param path File path to font file.
 * @param ptSize The size of the font.
 *
 * @deprecated DEVELOPMENT USE ONLY! Use SDL_LoadFontRW to load
 * fonts in a release build.
 */
TTF_Font *SDL_LoadFont(const char *path, const int ptSize = 24)
{
    if (!TTF_WasInit())
    {
        TTF_Init();
    }

    TTF_Font *font = TTF_OpenFont(path, ptSize);

    if (!font)
    {
        return nullptr;
    }

    return font;
}

/**
 * Load font from a read-only buffer.
 *
 * @param mem A pointer to a read-only buffer.
 * @param size The buffer size, in bytes.
 * @param ptSize The size of the font.
 */
TTF_Font *SDL_LoadFontRW(const void *mem, const int size, const int ptSize = 24)
{
    if (!TTF_WasInit())
    {
        TTF_Init();
    }

    TTF_Font *font = TTF_OpenFontRW(SDL_RWFromConstMem(mem, size), 1, ptSize);

    if (!font)
    {
        return nullptr;
    }

    return font;
}

} // namespace Handcrank
