#pragma once

#include "Handcrank/Handcrank.hpp"
#include "Handcrank/RectRenderObject.hpp"

#include "Entity.hpp"

using namespace Handcrank;

class Player : public Entity
{

  public:
    void Start() override
    {
        Entity::Start();

        SetRect(width, height, width, height);

        SetFillColor(255, 0, 0, 255);
    }

    void Update(double deltaTime) override
    {
        auto transformedRect = GetTransformedRect();

        auto rect = GetRect();

        if (game->keyPressedState[SDLK_RIGHT])
            rect->x += rect->w;
        else if (game->keyPressedState[SDLK_LEFT])
            rect->x -= rect->w;

        if (game->keyPressedState[SDLK_UP])
            rect->y -= rect->h;
        else if (game->keyPressedState[SDLK_DOWN])
            rect->y += rect->h;

        rect->x = std::clamp<float>(rect->x, minX, maxX);
        rect->y = std::clamp<float>(rect->y, minY, maxY);
    }
};
