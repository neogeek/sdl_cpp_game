#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

class SDL_TTF_Utilities
{

  public:
    /**
     * Load font from a path.
     *
     * @param path File path to font file.
     * @param ptSize The size of the font.
     */
    [[nodiscard]] static TTF_Font *LoadFont(const char *path, int ptSize = 24)
    {
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
    [[nodiscard]] static TTF_Font *LoadFontRW(const void *mem, int size,
                                              int ptSize = 24)
    {
        TTF_Font *font =
            TTF_OpenFontRW(SDL_RWFromConstMem(mem, size), 1, ptSize);

        if (!font)
        {
            return nullptr;
        }

        return font;
    }

    /**
     * Render text with a color.
     *
     * @param renderer A structure representing rendering state.
     * @param font The internal structure containing font information.
     * @param color A structure that represents a color.
     * @param rect A rectangle, with the origin at the upper left (integer).
     * @param content The text to render.
     */
    static void RenderText(SDL_Renderer *renderer, TTF_Font *font,
                           SDL_Color color, SDL_Rect rect, const char *content)
    {
        SDL_Surface *textSurface = TTF_RenderText_Solid(font, content, color);

        if (!textSurface)
        {
            return;
        }

        SDL_Texture *textTexture =
            SDL_CreateTextureFromSurface(renderer, textSurface);

        if (!textTexture)
        {
            return;
        }

        SDL_RenderCopy(renderer, textTexture, nullptr, &rect);

        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
    }
};
