#pragma once

#include "../images/roxzilla-idle.h"

#include "Handcrank/Handcrank.hpp"
#include "Handcrank/ImageRenderObject.hpp"

using namespace Handcrank;

class Roxzilla
{

  private:
    Game *game;

    int frame = 1;

    double nextTick;

    const double frameSpeed = 0.15;

  public:
    std::unique_ptr<ImageRenderObject> image;

    Roxzilla(Game *_game) : game(_game)
    {
        image = std::make_unique<ImageRenderObject>();

        image->LoadTextureRW(game->GetRenderer(), images_roxzilla_idle_png,
                             images_roxzilla_idle_png_len);

        image->SetScale(5);

        image->SetSrcRect(0, 0, 65, 83);

        image->SetRect(25, 25, 65, 83);

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

                imageObj->SetSrcRect(59 * (frame - 1), 0, 59, 80);

                frame += 1;

                if (frame > 6)
                {
                    frame = 1;
                }

                nextTick = 0;
            });
    }
};
