// Copyright (c) Scott Doxey. All Rights Reserved. Licensed under the MIT
// License. See LICENSE in the project root for license information.

#pragma once

#include <SDL.h>

namespace Handcrank
{

class SDL_Utilities
{
  public:
    /**
     * Clears a rect with a color.
     *
     * @param renderer A structure representing rendering state.
     * @param color A structure that represents a color.
     */
    static void ClearRect(SDL_Renderer *renderer, SDL_Color color)
    {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

        SDL_RenderClear(renderer);
    }

    /**
     * Render a rect with a color.
     *
     * @param renderer A structure representing rendering state.
     * @param rect A rectangle, with the origin at the upper left (integer).
     * @param color A structure that represents a color.
     */
    static void RenderRect(SDL_Renderer *renderer, SDL_FRect *rect,
                           SDL_Color color)
    {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

        SDL_RenderFillRectF(renderer, rect);
    }

    [[nodiscard]] static SDL_FRect *PositionRect(SDL_FRect *rect,
                                                 SDL_FRect *parent)
    {
        return new SDL_FRect{(*rect).x + (*parent).x, (*rect).y + (*parent).y,
                             (*rect).w, (*rect).h};
    }

    [[nodiscard]] static SDL_FRect *ScaleRect(SDL_FRect *rect, float scale)
    {
        return new SDL_FRect{(*rect).x, (*rect).y, (*rect).w * scale,
                             (*rect).h * scale};
    }
};

} // namespace Handcrank
