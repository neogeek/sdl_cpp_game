// Copyright (c) Scott Doxey. All Rights Reserved. Licensed under the MIT
// License. See LICENSE in the project root for license information.

#pragma once

#include <functional>
#include <iostream>

#include <SDL.h>

namespace Handcrank
{

class RenderObject
{
  protected:
    SDL_FRect *rect;

    std::function<void(RenderObject *)> startFunction;

    std::function<void(RenderObject *, double)> updateFunction;

    std::function<void(RenderObject *, double)> fixedUpdateFunction;

    bool hasStarted = false;

    bool isMarkedForDestroy = false;

    double scale = 1;

  public:
    std::list<std::unique_ptr<RenderObject>> children;

    RenderObject *parent;

    explicit RenderObject()
    {
        rect = new SDL_FRect;
        rect->x = 0;
        rect->y = 0;
        rect->w = 100;
        rect->h = 100;
    }
    explicit RenderObject(SDL_FRect *_rect) : rect(_rect) {}

    ~RenderObject() = default;

    void SetStart(std::function<void(RenderObject *)> _startFunction = nullptr)
    {
        if (startFunction)
        {
            std::cerr << "WARNING! Start function has already been set. "
                         "Overriding with new function.\n";
        }

        startFunction = std::move(_startFunction);
    }

    void SetUpdate(
        std::function<void(RenderObject *, double)> _updateFunction = nullptr)
    {
        if (updateFunction)
        {
            std::cerr << "WARNING! Update function has already been set. "
                         "Overriding with new function.\n";
        }

        updateFunction = std::move(_updateFunction);
    }

    void SetFixedUpdate(std::function<void(RenderObject *, double)>
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

    [[nodiscard]] SDL_FRect *GetRect() { return rect; }

    [[nodiscard]] SDL_FRect *GetTransformedRect()
    {
        SDL_FRect *transformedRect;

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
     * Set rect position and size of the RenderObject.
     * @param rect A rectangle, with the origin at the upper left (integer).
     */
    void SetRect(SDL_FRect *_rect) { rect = _rect; }

    /**
     * Set rect position and size of the RenderObject.
     * @param x X position.
     * @param y Y position.
     * @param w Width of rect.
     * @param h Height of rect.
     */
    void SetRect(float x, float y, float w, float h)
    {
        this->rect->x = x;
        this->rect->y = y;
        this->rect->w = w;
        this->rect->h = h;
    }

    /**
     * Set rect position of the RenderObject.
     * @param x X position.
     * @param y Y position.
     */
    void SetRect(float x, float y)
    {
        this->rect->x = x;
        this->rect->y = y;
    }

    [[nodiscard]] double GetScale() const { return scale; }

    void SetScale(double _scale) { scale = _scale; }

    /**
     * Render RenderObject to the scene.
     */
    virtual void Render(SDL_Renderer *_renderer)
    {
        for (auto &iter : children)
        {
            auto child = iter.get();

            if (child != nullptr)
            {
                child->Render(_renderer);
            }
        }
    }

    void AddChildObject(std::unique_ptr<RenderObject> child)
    {
        child->parent = this;

        children.push_back(std::move(child));
    }

    template <typename T> std::vector<T *> GetChildrenByType()
    {
        static_assert(std::is_base_of<RenderObject, T>::value,
                      "T must be derived from RenderObject");

        std::vector<T *> results;

        for (auto &iter : children)
        {
            auto child = iter.get();

            if (child != nullptr && typeid(*child) == typeid(T))
            {
                auto castedChild = dynamic_cast<T *>(child);

                if (castedChild != nullptr)
                {
                    results.push_back(castedChild);
                }
            }
        }

        return results;
    }

    template <typename T> T *GetChildByType()
    {
        static_assert(std::is_base_of<RenderObject, T>::value,
                      "T must be derived from RenderObject");

        auto children = GetChildrenByType<T>();

        if (!children.empty())
        {
            return children.front();
        }

        return nullptr;
    }

    SDL_FRect *CalculateBoundingBox()
    {
        auto boundingBox = GetTransformedRect();

        for (auto &iter : children)
        {
            auto child = iter.get();

            if (child != nullptr)
            {
                auto childBoundingBox = child->CalculateBoundingBox();

                (*boundingBox).x =
                    fminf((*boundingBox).x, (*childBoundingBox).x);
                (*boundingBox).y =
                    fminf((*boundingBox).y, (*childBoundingBox).y);
                (*boundingBox).w =
                    fmaxf((*boundingBox).w, (*childBoundingBox).w);
                (*boundingBox).h =
                    fmaxf((*boundingBox).h, (*childBoundingBox).h);
            }
        }

        return boundingBox;
    }

    void DestroyChildObjects()
    {
        for (auto iter = children.begin(); iter != children.end();)
        {
            auto child = iter->get();

            if (child != nullptr)
            {
                child->DestroyChildObjects();

                if (child->HasBeenMarkedForDestroy())
                {
                    iter = children.erase(iter);
                }
                else
                {
                    ++iter;
                }
            }
        }
    }

    /**
     * Cleanup function to run after the RenderObject is unloaded.
     */
    virtual void Clean() {}

    [[nodiscard]] bool HasBeenMarkedForDestroy() const
    {
        return isMarkedForDestroy;
    }

    void Destroy() { isMarkedForDestroy = true; }
};

} // namespace Handcrank
