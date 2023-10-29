#pragma once

#include "../images/galaga_bullet_1.h"

#include "Handcrank/Handcrank.hpp"
#include "Handcrank/ImageRenderObject.hpp"

using namespace Handcrank;

class GalagaBullet : public ImageRenderObject
{

  private:
    double speed = 1000;

  public:
    void Start() override
    {
        LoadTextureRW(game->GetRenderer(), images_galaga_bullet_1_png,
                      images_galaga_bullet_1_png_len);

        SetScale(5);
    }

    void Update(double deltaTime) override
    {
        if (!game->HasFocus())
        {
            return;
        }

        auto position = GetRect();

        position->y -= speed * deltaTime;

        if (position->y < 100)
        {
            Destroy();
        }
    }
};
