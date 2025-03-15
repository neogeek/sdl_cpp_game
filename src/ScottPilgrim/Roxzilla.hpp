#pragma once

#include "../images/roxzilla-idle.h"

#include "Handcrank/Handcrank.hpp"
#include "Handcrank/SpriteRenderObject.hpp"

using namespace Handcrank;

class Roxzilla : public SpriteRenderObject
{

  public:
    void Start() override
    {
        LoadTextureRW(game->GetRenderer(), images_roxzilla_idle_png,
                      images_roxzilla_idle_png_len);

        SetScale(4);

        z = 1;

        SetRect(700, 600);

        CalculateFrames(348, 80, 6, 1, Vector2(0, 0), Vector2(0, 0));

        Play();
    }
};
