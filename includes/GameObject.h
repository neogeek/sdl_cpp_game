#pragma once

#include <functional>
#include <iostream>
#include <utility>

#include <SDL.h>

class GameObject
{
  protected:
    SDL_Rect *rect;

    std::function<void(GameObject *)> startFunction;

    std::function<void(GameObject *, double)> updateFunction;

    std::function<void(GameObject *, double)> fixedUpdateFunction;

    bool hasStarted = false;

    bool isMarkedForDestroy = false;

    double scale = 1;

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

    ~GameObject() = default;

    void SetStart(std::function<void(GameObject *)> _startFunction = nullptr)
    {
        if (startFunction)
        {
            std::cerr << "WARNING! Start function has already been set. "
                         "Overriding with new function.\n";
        }

        startFunction = std::move(_startFunction);
    }

    void SetUpdate(
        std::function<void(GameObject *, double)> _updateFunction = nullptr)
    {
        if (updateFunction)
        {
            std::cerr << "WARNING! Update function has already been set. "
                         "Overriding with new function.\n";
        }

        updateFunction = std::move(_updateFunction);
    }

    void SetFixedUpdate(std::function<void(GameObject *, double)>
                            _fixedUpdateFunction = nullptr)
    {
        if (fixedUpdateFunction)
        {
            std::cerr << "WARNING! Fixed update function has already been set. "
                         "Overriding with new function.\n";
        }

        fixedUpdateFunction = std::move(_fixedUpdateFunction);
    }

    void Update(double deltaTime)
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

    void FixedUpdate(double fixedDeltaTime)
    {
        if (fixedUpdateFunction)
        {
            fixedUpdateFunction(this, fixedDeltaTime);
        }
    }

    [[nodiscard]] SDL_Rect *GetRect() { return rect; }

    /**
     * Set rect position and size of the GameObject.
     * @param rect A rectangle, with the origin at the upper left (integer).
     */
    void SetRect(SDL_Rect *rect) { this->rect = rect; }

    /**
     * Set rect position and size of the GameObject.
     * @param x X position.
     * @param y Y position.
     * @param w Width of rect.
     * @param h Height of rect.
     */
    void SetRect(int x, int y, int w, int h)
    {
        this->rect->x = x;
        this->rect->y = y;
        this->rect->w = w;
        this->rect->h = h;
    }

    /**
     * Set rect position of the GameObject.
     * @param x X position.
     * @param y Y position.
     */
    void SetRect(int x, int y)
    {
        this->rect->x = x;
        this->rect->y = y;
    }

    void SetScale(double scale) { this->scale = scale; }

    /**
     * Render GameObject to the scene.
     */
    virtual void Render(SDL_Renderer *_renderer) {}

    /**
     * Cleanup function to run after the scene is unloaded.
     */
    virtual void Clean() {}

    [[nodiscard]] bool HasBeenMarkedForDestroy() const
    {
        return isMarkedForDestroy;
    }

    void Destroy() { isMarkedForDestroy = true; }
};
