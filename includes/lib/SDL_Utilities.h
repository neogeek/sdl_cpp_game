#pragma once

#include <SDL.h>

class SDL_Utilities
{

public:
    static void clearRect(SDL_Renderer *renderer, SDL_Color color)
    {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

        SDL_RenderClear(renderer);
    }

    /**
     * Render a rect with a color.
     *
     * @param renderer A structure representing rendering state.
     * @param rect A rectangle, with the origin at the upper left (integer).
     * @param color Color struct.
     */
    static void renderRect(SDL_Renderer *renderer, SDL_Rect rect, SDL_Color color)
    {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

        SDL_RenderFillRect(renderer, &rect);
    }

    static SDL_Texture *loadTexture(SDL_Renderer *renderer, const char *path)
    {
        SDL_Surface *surface = IMG_Load(path);

        if (!surface)
        {
            return NULL;
        }

        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);

        if (!texture)
        {
            return NULL;
        }

        return texture;
    }
};
