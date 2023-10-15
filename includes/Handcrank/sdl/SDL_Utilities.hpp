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
    static void RenderRect(SDL_Renderer *renderer, SDL_Rect *rect,
                           SDL_Color color)
    {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

        SDL_RenderFillRect(renderer, rect);
    }

    [[nodiscard]] static SDL_Rect *PositionRect(SDL_Rect *rect,
                                                SDL_Rect *parent)
    {
        return new SDL_Rect{(*rect).x + (*parent).x, (*rect).y + (*parent).y,
                            (*rect).w, (*rect).h};
    }

    [[nodiscard]] static SDL_Rect *ScaleRect(SDL_Rect *rect, double scale)
    {
        return new SDL_Rect{(*rect).x, (*rect).y,
                            static_cast<int>((*rect).w * scale),
                            static_cast<int>((*rect).h * scale)};
    }
};

} // namespace Handcrank
