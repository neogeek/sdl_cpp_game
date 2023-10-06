#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

class SDL_TTF_Utilities
{

public:
    static TTF_Font *LoadFont(const char *path, int ptSize = 24)
    {
        TTF_Font *font = TTF_OpenFont(path, ptSize);

        if (!font)
        {
            return nullptr;
        }

        return font;
    }

    static TTF_Font *LoadFontRW(const void *mem, int size, int ptSize = 24)
    {
        TTF_Font *font = TTF_OpenFontRW(SDL_RWFromConstMem(mem, size), 1, ptSize);

        if (!font)
        {
            return nullptr;
        }

        return font;
    }

    static void RenderText(SDL_Renderer *renderer, TTF_Font *font, SDL_Color color, SDL_Rect rect, const char *content)
    {
        SDL_Surface *textSurface = TTF_RenderText_Solid(font, content, color);

        if (!textSurface)
        {
            return;
        }

        SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

        if (!textTexture)
        {
            return;
        }

        SDL_RenderCopy(renderer, textTexture, nullptr, &rect);

        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
    }
};
