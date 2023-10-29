#pragma once

#include "../images/galaga_enemy_1.h"

#include "Handcrank/Handcrank.hpp"
#include "Handcrank/ImageRenderObject.hpp"

using namespace Handcrank;

class GalagaEnemy : public ImageRenderObject
{

  private:
    double speed = 400;

    int enemyDirection = 1;

  public:
    void Start() override
    {
        LoadTextureRW(game->GetRenderer(), images_galaga_enemy_1_png,
                      images_galaga_enemy_1_png_len);

        SetScale(5);

        SetRect((game->GetWidth() / 2) - 50, 150);
    }

    void Update(double deltaTime) override
    {
        if (!game->HasFocus())
        {
            return;
        }

        auto rect = GetRect();

        rect->x += enemyDirection * speed * deltaTime;

        if (enemyDirection == 1 && rect->x > game->GetWidth() - 200)
        {
            rect->x = game->GetWidth() - 200;

            enemyDirection = -1;
        }
        else if (enemyDirection == -1 && rect->x < 100)
        {
            rect->x = 100;

            enemyDirection = 1;
        }
    }
};
