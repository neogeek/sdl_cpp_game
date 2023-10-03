#pragma once

#include <SDL.h>

class GameObject
{

protected:
    SDL_Rect *rect;

public:
    explicit GameObject(SDL_Rect *_rect) : rect(_rect) {}

    ~GameObject() {}

    /**
     * Set rect position and size to the GameObject.
     * @param rect A rectangle, with the origin at the upper left (integer).
     */
    inline void SetRect(SDL_Rect *_rect)
    {
        rect = _rect;
    }

    /**
     * Render GameObject to the scene.
     */
    inline virtual void Render(SDL_Renderer *_renderer)
    {
    }

    /**
     * Cleanup function to run after the scene is unloaded.
     */
    inline virtual void Clean()
    {
    }
};
