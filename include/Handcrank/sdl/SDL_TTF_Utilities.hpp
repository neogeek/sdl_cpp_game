// Copyright (c) Scott Doxey. All Rights Reserved. Licensed under the MIT
// License. See LICENSE in the project root for license information.

#pragma once

#include <memory>

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
inline std::shared_ptr<TTF_Font> SDL_LoadFont(const char *path,
                                              const int ptSize = 24)
{
    if (!TTF_WasInit())
    {
        TTF_Init();
    }

    auto font = TTF_OpenFont(path, ptSize);

    if (!font)
    {
        return nullptr;
    }

    return std::shared_ptr<TTF_Font>(font, TTF_CloseFont);
}

/**
 * Load font from a read-only buffer.
 *
 * @param mem A pointer to a read-only buffer.
 * @param size The buffer size, in bytes.
 * @param ptSize The size of the font.
 */
inline std::shared_ptr<TTF_Font> SDL_LoadFontRW(const void *mem, const int size,
                                                const int ptSize = 24)
{
    if (!TTF_WasInit())
    {
        TTF_Init();
    }

    auto rw = SDL_RWFromConstMem(mem, size);

    if (!rw)
    {
        return nullptr;
    }

    auto font = TTF_OpenFontRW(rw, 1, ptSize);

    if (!font)
    {
        SDL_RWclose(rw);
        return nullptr;
    }

    return std::shared_ptr<TTF_Font>(font, TTF_CloseFont);
}

} // namespace Handcrank
