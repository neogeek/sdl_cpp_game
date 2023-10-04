#pragma once

#include <SDL.h>

#include "sdl/SDL_Utilities.h"

#include <GameObject.h>

class RectRenderObject : public GameObject
{

private:
    SDL_Color color{0, 0, 0, 255};

public:
    explicit RectRenderObject() : GameObject() {}
    explicit RectRenderObject(SDL_Rect *_rect) : GameObject(_rect) {}

    ~RectRenderObject()
    {
    }

    /**
     * Set rect color.
     * @param color Color value to set.
     */
    inline void SetColor(SDL_Color _color)
    {
        color = _color;
    }

    /**
     * Render rect to the scene.
     */
    inline void Render(SDL_Renderer *renderer)
    {
        SDL_Utilities::RenderRect(renderer, rect, color);
    }

    /**
     * Cleanup function to run after the scene is unloaded.
     */
    inline void Clean()
    {
    }
};
