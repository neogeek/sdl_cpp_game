// Copyright (c) Scott Doxey. All Rights Reserved. Licensed under the MIT
// License. See LICENSE in the project root for license information.

#pragma once

#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

#include "sdl/SDL_TTF_Utilities.hpp"

#include "Handcrank.hpp"

namespace Handcrank
{

class TextRenderObject : public RenderObject
{
  private:
    TTF_Font *font;

    SDL_Color color{255, 255, 255, 255};

    std::string text;

    SDL_Surface *textSurface;

    SDL_Texture *textTexture;

  public:
    explicit TextRenderObject()
    {
        if (!TTF_WasInit())
        {
            TTF_Init();
        }
    }
    explicit TextRenderObject(SDL_FRect *rect) : RenderObject(rect) {}

    ~TextRenderObject()
    {
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
    }

    /**
     * Set text font.
     *
     * @param font Font value to set.
     */
    void SetFont(TTF_Font *font) { this->font = font; }

    /**
     * Load font from a path.
     *
     * @param path File path to font file.
     * @param ptSize The size of the font.
     *
     * @deprecated DEVELOPMENT USE ONLY! Use SDL_LoadFontRW to load
     * fonts in a release build.
     */
    void LoadFont(const char *path, const int ptSize = 24)
    {
        font = SDL_LoadFont(path, ptSize);
    }

    /**
     * Load font from a read-only buffer.
     *
     * @param mem A pointer to a read-only buffer.
     * @param size The buffer size, in bytes.
     * @param ptSize The size of the font.
     */
    void LoadFontRW(const void *mem, const int size, const int ptSize = 24)
    {
        font = SDL_LoadFontRW(mem, size, ptSize);
    }

    /**
     * Set text color.
     *
     * @param color Color value to set.
     */
    void SetColor(const SDL_Color color) { this->color = color; }

    /**
     * Set text content.
     *
     * @param text Text value to set.
     */
    void SetText(std::string text)
    {
        this->text = std::move(text);

        if (font == nullptr)
        {
            std::cerr << "ERROR! Missing font reference." << std::endl;

            return;
        }

        textSurface = TTF_RenderText_Blended(font, this->text.c_str(), color);

        rect->w = textSurface->w;
        rect->h = textSurface->h;

        textTexture = nullptr;
    }

    /**
     * Set text content.
     *
     * @param text Text value to set.
     */
    void SetWrappedText(std::string text)
    {
        this->text = std::move(text);

        textSurface =
            TTF_RenderText_Blended_Wrapped(font, text.c_str(), color, rect->w);

        rect->w = textSurface->w;
        rect->h = textSurface->h;

        textTexture = nullptr;
    }

    std::string GetText() { return text; }

    /**
     * Render text to the scene.
     *
     * @param renderer A structure representing rendering state.
     */
    void Render(SDL_Renderer *renderer) override
    {
        if (textTexture == nullptr)
        {
            textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        }

        SDL_RenderCopyF(renderer, textTexture, nullptr, GetTransformedRect());

        RenderObject::Render(renderer);
    }

    /**
     * Cleanup function to run after the TextRenderObject is unloaded.
     */
    void Clean() override
    {
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
    }
};

} // namespace Handcrank
