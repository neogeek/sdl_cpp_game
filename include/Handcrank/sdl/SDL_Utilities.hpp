// Copyright (c) Scott Doxey. All Rights Reserved. Licensed under the MIT
// License. See LICENSE in the project root for license information.

#pragma once

#include <SDL.h>

namespace Handcrank
{

SDL_FRect *PositionRect(const SDL_FRect *rect, const SDL_FRect *parent)
{
    return new SDL_FRect{rect->x + parent->x, rect->y + parent->y, rect->w,
                         rect->h};
}

SDL_FRect *ScaleRect(const SDL_FRect *rect, const float scale)
{
    return new SDL_FRect{rect->x, rect->y, rect->w * scale, rect->h * scale};
}

} // namespace Handcrank
