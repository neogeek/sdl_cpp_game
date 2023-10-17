// Copyright (c) Scott Doxey. All Rights Reserved. Licensed under the MIT
// License. See LICENSE in the project root for license information.

#pragma once

#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

#include "sdl/SDL_TTF_Utilities.hpp"
#include "sdl/SDL_Utilities.hpp"

#include "RenderObject.hpp"

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
    explicit TextRenderObject() : RenderObject()
    {
        if (!TTF_WasInit())
        {
            TTF_Init();
        }
    }
    explicit TextRenderObject(SDL_FRect *_rect) : RenderObject(_rect) {}

    ~TextRenderObject()
    {
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
    };

    /**
     * Set text font.
     * @param font Font value to set.
     */
    void SetFont(TTF_Font *_font) { font = _font; }

    /**
     * Set text color.
     * @param color Color value to set.
     */
    void SetColor(SDL_Color _color) { color = _color; }

    /**
     * Set text content.
     * @param text Text value to set.
     */
    void SetText(std::string _text)
    {
        text = std::move(_text);

        textSurface = TTF_RenderText_Blended(font, text.c_str(), color);

        rect->w = textSurface->w;
        rect->h = textSurface->h;

        textTexture = nullptr;
    }

    /**
     * Set text content.
     * @param text Text value to set.
     */
    void SetWrappedText(std::string _text)
    {
        text = std::move(_text);

        textSurface =
            TTF_RenderText_Blended_Wrapped(font, text.c_str(), color, rect->w);

        rect->w = textSurface->w;
        rect->h = textSurface->h;

        textTexture = nullptr;
    }

    std::string GetText() { return text; }

    /**
     * Render text to the scene.
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
     * Cleanup function to run after the RenderObject is unloaded.
     */
    void Clean() override
    {
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
    }
};

} // namespace Handcrank
