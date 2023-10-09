#pragma once

#include <SDL.h>

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

    static SDL_Rect *ScaleRect(SDL_Rect *rect, int scale)
    {
        SDL_Rect *scaledRect = new SDL_Rect{
            (*rect).x, (*rect).y, (*rect).w * scale, (*rect).h * scale};

        return scaledRect;
    }
};
