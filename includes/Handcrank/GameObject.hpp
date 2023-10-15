// Copyright (c) Scott Doxey. All Rights Reserved. Licensed under the MIT
// License. See LICENSE in the project root for license information.

#pragma once

#include <functional>
#include <iostream>

#include <SDL.h>

namespace Handcrank
{

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
    std::list<std::unique_ptr<GameObject>> children;

    GameObject *parent;

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

    [[nodiscard]] SDL_Rect *GetTransformedRect()
    {
        SDL_Rect *transformedRect;

        transformedRect = SDL_Utilities::ScaleRect(rect, scale);

        if (parent != nullptr)
        {
            transformedRect =
                SDL_Utilities::PositionRect(transformedRect, parent->rect);

            transformedRect =
                SDL_Utilities::ScaleRect(transformedRect, parent->scale);
        }

        return transformedRect;
    }

    /**
     * Set rect position and size of the GameObject.
     * @param rect A rectangle, with the origin at the upper left (integer).
     */
    void SetRect(SDL_Rect *_rect) { rect = _rect; }

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

    [[nodiscard]] double GetScale() const { return scale; }

    void SetScale(double _scale) { scale = _scale; }

    /**
     * Render GameObject to the scene.
     */
    virtual void Render(SDL_Renderer *_renderer)
    {
        for (auto &iter : children)
        {
            auto gameObject = iter.get();

            if (gameObject != nullptr)
            {
                gameObject->Render(_renderer);
            }
        }
    }

    void AddChildGameObject(std::unique_ptr<GameObject> gameObject)
    {
        gameObject->parent = this;

        children.push_back(std::move(gameObject));
    }

    template <typename T> std::vector<T *> GetChildrenByType()
    {
        static_assert(std::is_base_of<GameObject, T>::value,
                      "T must be derived from GameObject");

        std::vector<T *> results;

        for (auto &iter : children)
        {
            auto gameObject = iter.get();

            if (gameObject != nullptr && typeid(*gameObject) == typeid(T))
            {
                auto castedGameObject = dynamic_cast<T *>(gameObject);

                if (castedGameObject != nullptr)
                {
                    results.push_back(castedGameObject);
                }
            }
        }

        return results;
    }

    template <typename T> T *GetChildByType()
    {
        static_assert(std::is_base_of<GameObject, T>::value,
                      "T must be derived from GameObject");

        auto children = GetChildrenByType<T>();

        if (!children.empty())
        {
            return children.front();
        }

        return nullptr;
    }

    /**
     * Cleanup function to run after the GameObject is unloaded.
     */
    virtual void Clean() {}

    [[nodiscard]] bool HasBeenMarkedForDestroy() const
    {
        return isMarkedForDestroy;
    }

    void Destroy() { isMarkedForDestroy = true; }
};

} // namespace Handcrank
