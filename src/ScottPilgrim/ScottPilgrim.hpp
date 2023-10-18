#pragma once

#include "../images/scott-pilgrim-idle.h"

#include "Handcrank/Game.hpp"
#include "Handcrank/ImageRenderObject.hpp"

using namespace Handcrank;

class ScottPilgrim
{

  private:
    Game *game;

    int frame = 1;

    double nextTick;

    const double frameSpeed = 0.15;

  public:
    std::unique_ptr<ImageRenderObject> image;

    ScottPilgrim(Game *_game) : game(_game)
    {
        image = std::make_unique<ImageRenderObject>();

        image->LoadTextureRW(game->GetRenderer(), images_scott_pilgrim_idle_png,
                             images_scott_pilgrim_idle_png_len);

        image->SetScale(5);

        image->z = 1;

        image->SetSrcRect(0, 0, 36, 59);

        image->SetRect(25, 25, 36, 59);

        image->SetUpdate(
            [this](RenderObject *ref, double deltaTime)
            {
                auto transformedRect = ref->GetTransformedRect();

                auto movementSpeed = 500;

                auto minY = 475;
                auto maxY = 825;

                auto rect = ref->GetRect();

                ImageRenderObject *imageObj =
                    dynamic_cast<ImageRenderObject *>(ref);

                if (game->keyState[SDLK_RIGHT])
                {
                    rect->x += movementSpeed * deltaTime;

                    imageObj->SetFlip(SDL_FLIP_NONE);
                }
                else if (game->keyState[SDLK_LEFT])
                {
                    rect->x -= movementSpeed * deltaTime;

                    imageObj->SetFlip(SDL_FLIP_HORIZONTAL);
                }

                if (game->keyState[SDLK_UP])
                {
                    rect->y -= movementSpeed * deltaTime;
                }
                else if (game->keyState[SDLK_DOWN])
                {
                    rect->y += movementSpeed * deltaTime;
                }

                rect->x = std::clamp<float>(
                    rect->x, 0, game->GetWidth() - transformedRect->w);
                rect->y = std::clamp<float>(rect->y, minY, maxY);

                nextTick += deltaTime;

                if (nextTick < frameSpeed)
                {
                    return;
                }

                imageObj->SetSrcRect(36 * (frame - 1), 0, 36, 59);

                frame += 1;

                if (frame > 8)
                {
                    frame = 1;
                }

                nextTick = 0;
            });
    }
};
