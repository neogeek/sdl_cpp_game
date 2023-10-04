#pragma once

#include <functional>

#include <SDL.h>

class GameObject
{

protected:
    SDL_Rect *rect;

    std::function<void(GameObject *, double)> updateFunction;

    std::function<void(GameObject *, double)> fixedUpdateFunction;

public:
    explicit GameObject() {}
    explicit GameObject(SDL_Rect *_rect) : rect(_rect) {}

    ~GameObject() {}

    inline void SetUpdate(std::function<void(GameObject *, double)> _updateFunction = nullptr)
    {
        if (updateFunction)
        {
            std::cerr << "WARNING! Update function has already been set. Overriding with new function.\n";
        }

        updateFunction = _updateFunction;
    }

    inline void SetFixedUpdate(std::function<void(GameObject *, double)> _fixedUpdateFunction = nullptr)
    {
        if (fixedUpdateFunction)
        {
            std::cerr << "WARNING! Fixed update function has already been set. Overriding with new function.\n";
        }

        fixedUpdateFunction = _fixedUpdateFunction;
    }

    inline void Update(double deltaTime)
    {
        if (updateFunction)
        {
            updateFunction(this, deltaTime);
        }
    }

    inline void FixedUpdate(double fixedDeltaTime)
    {
        if (fixedUpdateFunction)
        {
            fixedUpdateFunction(this, fixedDeltaTime);
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
