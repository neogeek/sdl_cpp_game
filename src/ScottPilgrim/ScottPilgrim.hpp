#pragma once

#include "../images/scott-pilgrim-idle.h"

#include "Handcrank/Handcrank.hpp"
#include "Handcrank/ImageRenderObject.hpp"

using namespace Handcrank;

class ScottPilgrim : public ImageRenderObject
{

  private:
    int frame = 1;

    double nextTick;

    const double frameSpeed = 0.15;

  public:
    void Start() override
    {
        LoadTextureRW(game->GetRenderer(), images_scott_pilgrim_idle_png,
                      images_scott_pilgrim_idle_png_len);

        SetScale(5);

        z = 1;

        SetSrcRect(0, 0, 36, 59);

        SetRect(rect->x, rect->y, 36, 59);
    }

    void Update(double deltaTime) override
    {
        auto transformedRect = GetTransformedRect();

        auto movementSpeed = 500;

        auto minX = 0;
        auto maxX = game->GetWidth() - transformedRect->w;

        auto minY = 475;
        auto maxY = 825;

        auto rect = GetRect();

        if (game->keyState[SDLK_RIGHT])
        {
            rect->x += movementSpeed * deltaTime;

            SetFlip(SDL_FLIP_NONE);
        }
        else if (game->keyState[SDLK_LEFT])
        {
            rect->x -= movementSpeed * deltaTime;

            SetFlip(SDL_FLIP_HORIZONTAL);
        }

        if (game->keyState[SDLK_UP])
        {
            rect->y -= movementSpeed * deltaTime;
        }
        else if (game->keyState[SDLK_DOWN])
        {
            rect->y += movementSpeed * deltaTime;
        }

        rect->x = std::clamp<float>(rect->x, minX, maxX);
        rect->y = std::clamp<float>(rect->y, minY, maxY);

        nextTick += deltaTime;

        if (nextTick < frameSpeed)
        {
            return;
        }

        SetSrcRect(36 * (frame - 1), 0, 36, 59);

        frame += 1;

        if (frame > 8)
        {
            frame = 1;
        }

        nextTick = 0;
    }
};
