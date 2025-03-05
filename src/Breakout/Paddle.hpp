#pragma once

#include "Handcrank/Handcrank.hpp"
#include "Handcrank/RectRenderObject.hpp"

using namespace Handcrank;

class Paddle : public RectRenderObject
{

  private:
    int movementSpeed = 1000;

  public:
    void Start() override
    {
        SetFillColor(255, 255, 255, 255);
        SetRect(0, game->GetHeight() - 50, 200, 25);
    }

    void Update(double deltaTime) override
    {
        if (!game->HasFocus())
        {
            return;
        }

        const auto transformedRect = GetTransformedRect();

        const auto minX = 0;
        const auto minY = 0;

        const auto maxX = game->GetWidth() - transformedRect->w;
        const auto maxY = game->GetHeight() - transformedRect->h;

        if (game->keyState[SDLK_RIGHT])
        {
            rect->x += movementSpeed * deltaTime;
        }
        else if (game->keyState[SDLK_LEFT])
        {
            rect->x -= movementSpeed * deltaTime;
        }

        rect->x = std::clamp<float>(rect->x, minX, maxX);
        rect->y = std::clamp<float>(rect->y, minY, maxY);
    }
};
