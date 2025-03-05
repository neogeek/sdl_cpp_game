#pragma once

#include "Handcrank/Handcrank.hpp"
#include "Handcrank/RectRenderObject.hpp"

using namespace Handcrank;

class Ball : public RectRenderObject
{

  private:
    int xDirection = 1;
    int yDirection = -1;

    int movementSpeed = 500;

  public:
    void Update(double deltaTime) override
    {
        if (!game->HasFocus())
        {
            return;
        }

        const auto transformedRect = GetTransformedRect();

        const auto rect = GetRect();

        const auto minX = 0;
        const auto minY = 0;

        const auto maxX = game->GetWidth() - transformedRect->w;
        const auto maxY = game->GetHeight() - transformedRect->h;

        rect->x += movementSpeed * xDirection * deltaTime;
        rect->y += movementSpeed * yDirection * deltaTime;

        if (rect->x > maxX || rect->x < minX)
        {
            xDirection = -xDirection;
        }

        if (rect->y > maxY || rect->y < minY)
        {
            yDirection = -yDirection;
        }

        rect->x = std::clamp<float>(rect->x, minX, maxX);
        rect->y = std::clamp<float>(rect->y, minY, maxY);
    }

    void ChangeDirection()
    {
        // xDirection = -xDirection;
        yDirection = -yDirection;
    }
};
