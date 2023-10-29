// Copyright (c) Scott Doxey. All Rights Reserved. Licensed under the MIT
// License. See LICENSE in the project root for license information.

#pragma once

#include <SDL.h>

extern SDL_FRect *PositionRect(SDL_FRect *rect, SDL_FRect *parent)
{
    return new SDL_FRect{rect->x + parent->x, rect->y + parent->y, rect->w,
                         rect->h};
}

extern SDL_FRect *ScaleRect(SDL_FRect *rect, float scale)
{
    return new SDL_FRect{rect->x, rect->y, rect->w * scale, rect->h * scale};
}
