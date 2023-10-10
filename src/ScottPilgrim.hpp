#pragma once

#include "../images/scott-pilgrim-idle.h"

#include "Game.hpp"
#include "ImageRenderObject.hpp"

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
            [this](GameObject *ref, double deltaTime)
            {
                nextTick += deltaTime;

                if (nextTick < frameSpeed)
                {
                    return;
                }

                ImageRenderObject *imageObj =
                    dynamic_cast<ImageRenderObject *>(ref);

                switch (frame)
                {
                case 1:
                    imageObj->SetSrcRect(0, 0, 36, 59);
                    break;
                case 2:
                    imageObj->SetSrcRect(36, 0, 36, 59);
                    break;
                case 3:
                    imageObj->SetSrcRect(72, 0, 36, 59);
                    break;
                case 4:
                    imageObj->SetSrcRect(108, 0, 36, 59);
                    break;
                case 5:
                    imageObj->SetSrcRect(144, 0, 36, 59);
                    break;
                case 6:
                    imageObj->SetSrcRect(180, 0, 36, 59);
                    break;
                case 7:
                    imageObj->SetSrcRect(216, 0, 36, 59);
                    break;
                case 8:
                    imageObj->SetSrcRect(252, 0, 36, 59);
                    break;
                }

                frame += 1;

                if (frame > 8)
                {
                    frame = 1;
                }

                nextTick = 0;
            });
    }
};
