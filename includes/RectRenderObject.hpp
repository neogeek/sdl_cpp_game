#pragma once

#include <SDL.h>

#include "sdl/SDL_Utilities.hpp"

#include "GameObject.hpp"

class RectRenderObject : public GameObject
{
  private:
    SDL_Color color{255, 255, 255, 255};

  public:
    explicit RectRenderObject() : GameObject() {}
    explicit RectRenderObject(SDL_Rect *_rect) : GameObject(_rect) {}

    ~RectRenderObject() = default;

    /**
     * Set rect color.
     * @param color Color value to set.
     */
    void SetColor(SDL_Color color) { this->color = color; }

    /**
     * Render rect to the scene.
     */
    void Render(SDL_Renderer *renderer) override
    {
        SDL_Utilities::RenderRect(renderer, GetScaledRect(), color);
    }

    /**
     * Cleanup function to run after the GameObject is unloaded.
     */
    void Clean() override {}
};
