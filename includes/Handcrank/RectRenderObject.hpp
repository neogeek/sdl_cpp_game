// Copyright (c) Scott Doxey. All Rights Reserved. Licensed under the MIT
// License. See LICENSE in the project root for license information.

#pragma once

#include <SDL.h>

#include "sdl/SDL_Utilities.hpp"

#include "Handcrank.hpp"

namespace Handcrank
{

class RectRenderObject : public RenderObject
{
  private:
    SDL_Color color{255, 255, 255, 255};

  public:
    explicit RectRenderObject() : RenderObject() {}
    explicit RectRenderObject(SDL_FRect *_rect) : RenderObject(_rect) {}

    ~RectRenderObject() = default;

    /**
     * Set rect color.
     * @param color Color value to set.
     */
    void SetColor(SDL_Color _color) { color = _color; }

    /**
     * Render rect to the scene.
     */
    void Render(SDL_Renderer *renderer) override
    {
        SDL_Utilities::RenderRect(renderer, GetTransformedRect(), color);

        RenderObject::Render(renderer);
    }

    /**
     * Cleanup function to run after the RenderObject is unloaded.
     */
    void Clean() override {}
};

} // namespace Handcrank
