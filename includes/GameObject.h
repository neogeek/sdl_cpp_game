#pragma once

#include <functional>

#include <SDL.h>

class GameObject
{

protected:
    SDL_Rect *rect;

    std::function<void(int)> updateFunction;

    std::function<void(int)> fixedUpdateFunction;

public:
    explicit GameObject() {}
    explicit GameObject(SDL_Rect *_rect) : rect(_rect) {}

    ~GameObject() {}

    inline void SetUpdate(std::function<void(double)> _updateFunction = nullptr)
    {
        updateFunction = _updateFunction;
    }

    inline void SetFixedUpdate(std::function<void(double)> _fixedUpdateFunction = nullptr)
    {
        fixedUpdateFunction = _fixedUpdateFunction;
    }

    inline void Update(double deltaTime)
    {
        if (updateFunction)
        {
            updateFunction(deltaTime);
        }
    }

    inline void FixedUpdate(double fixedDeltaTime)
    {
        if (fixedUpdateFunction)
        {
            fixedUpdateFunction(fixedDeltaTime);
        }
    }

    inline SDL_Rect *GetRect()
    {
        return rect;
    }

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
