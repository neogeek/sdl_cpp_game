// Copyright (c) Scott Doxey. All Rights Reserved. Licensed under the MIT
// License. See LICENSE in the project root for license information.

#pragma once

#include <SDL.h>

#include "Handcrank.hpp"

namespace Handcrank
{

class RectRenderObject : public RenderObject
{
  private:
    SDL_Color *borderColor;
    SDL_Color *fillColor;

    SDL_BlendMode blendMode = SDL_BLENDMODE_BLEND;

  public:
    explicit RectRenderObject() : RenderObject() {}
    explicit RectRenderObject(SDL_FRect *_rect) : RenderObject(_rect) {}

    ~RectRenderObject() = default;

    /**
     * Set rect border color.
     * @param color Color value to set.
     */
    void SetBorderColor(SDL_Color _borderColor)
    {
        if (borderColor == nullptr)
        {
            borderColor = new SDL_Color();
        }

        borderColor->r = _borderColor.r;
        borderColor->g = _borderColor.g;
        borderColor->b = _borderColor.b;
        borderColor->a = _borderColor.a;
    }

    void SetBorderColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
    {
        if (borderColor == nullptr)
        {
            borderColor = new SDL_Color();
        }

        borderColor->r = r;
        borderColor->g = g;
        borderColor->b = b;
        borderColor->a = a;
    }

    SDL_Color *GetBorderColor()
    {
        if (borderColor == nullptr)
        {
            return nullptr;
        }

        return borderColor;
    }

    /**
     * Set rect fill color.
     * @param color Color value to set.
     */
    void SetFillColor(SDL_Color _fillColor)
    {
        if (fillColor == nullptr)
        {
            fillColor = new SDL_Color();
        }

        fillColor->r = _fillColor.r;
        fillColor->g = _fillColor.g;
        fillColor->b = _fillColor.b;
        fillColor->a = _fillColor.a;
    }

    void SetFillColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
    {
        if (fillColor == nullptr)
        {
            fillColor = new SDL_Color();
        }

        fillColor->r = r;
        fillColor->g = g;
        fillColor->b = b;
        fillColor->a = a;
    }

    SDL_Color *GetFillColor()
    {
        if (fillColor == nullptr)
        {
            return nullptr;
        }

        return fillColor;
    }

    /**
     * Render rect to the scene.
     */
    void Render(SDL_Renderer *renderer) override
    {
        SDL_SetRenderDrawBlendMode(renderer, blendMode);

        if (fillColor != nullptr)
        {
            SDL_SetRenderDrawColor(renderer, fillColor->r, fillColor->g,
                                   fillColor->b, fillColor->a);

            SDL_RenderFillRectF(renderer, GetTransformedRect());
        }

        if (borderColor != nullptr)
        {
            SDL_SetRenderDrawColor(renderer, borderColor->r, borderColor->g,
                                   borderColor->b, borderColor->a);

            SDL_RenderDrawRectF(renderer, GetTransformedRect());
        }

        RenderObject::Render(renderer);
    }

    /**
     * Cleanup function to run after the RenderObject is unloaded.
     */
    void Clean() override {}
};

} // namespace Handcrank
