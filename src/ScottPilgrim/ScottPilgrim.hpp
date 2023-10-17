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

        image->SetSrcRect(0, 0, 36, 59);

        image->SetRect(25, 25, 36, 59);

        image->SetUpdate(
            [this](RenderObject *ref, double deltaTime)
            {
                nextTick += deltaTime;

                if (nextTick < frameSpeed)
                {
                    return;
                }

                ImageRenderObject *imageObj =
                    dynamic_cast<ImageRenderObject *>(ref);

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
