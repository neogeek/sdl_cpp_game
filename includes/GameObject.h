#pragma once

#include <functional>

#include <SDL.h>

class GameObject
{

protected:
    SDL_Rect *rect;

    std::function<void(GameObject *)> startFunction;

    std::function<void(GameObject *, double)> updateFunction;

    std::function<void(GameObject *, double)> fixedUpdateFunction;

    bool hasStarted;

    bool isMarkedForDestroy;

public:
    explicit GameObject()
    {
        rect = new SDL_Rect;
        rect->x = 0;
        rect->y = 0;
        rect->w = 100;
        rect->h = 100;
    }
    explicit GameObject(SDL_Rect *_rect) : rect(_rect) {}

    ~GameObject() {}

    inline void SetStart(std::function<void(GameObject *)> _startFunction = nullptr)
    {
        if (startFunction)
        {
            std::cerr << "WARNING! Start function has already been set. Overriding with new function.\n";
        }

        startFunction = _startFunction;
    }

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
        if (!hasStarted)
        {
            if (startFunction)
            {
                startFunction(this);
            }

            hasStarted = true;
        }

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

    inline bool HasBeenMarkedForDestroy() const
    {
        return isMarkedForDestroy;
    }

    inline void Destroy()
    {
        isMarkedForDestroy = true;
    }
};
