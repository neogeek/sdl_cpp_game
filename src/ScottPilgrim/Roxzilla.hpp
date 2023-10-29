#pragma once

#include "../images/roxzilla-idle.h"

#include "Handcrank/Handcrank.hpp"
#include "Handcrank/ImageRenderObject.hpp"

using namespace Handcrank;

class Roxzilla : public ImageRenderObject
{

  private:
    int frame = 1;

    double nextTick;

    const double frameSpeed = 0.15;

  public:
    void Start() override
    {
        LoadTextureRW(game->GetRenderer(), images_roxzilla_idle_png,
                      images_roxzilla_idle_png_len);

        SetScale(5);

        SetSrcRect(0, 0, 65, 83);

        SetRect(rect->x, rect->y, 65, 83);
    }

    void Update(double deltaTime) override
    {
        nextTick += deltaTime;

        if (nextTick < frameSpeed)
        {
            return;
        }

        SetSrcRect(59 * (frame - 1), 0, 59, 80);

        frame += 1;

        if (frame > 6)
        {
            frame = 1;
        }

        nextTick = 0;
    }
};
