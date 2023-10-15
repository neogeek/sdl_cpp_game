#pragma once

#include "../images/galaga_enemy_1.h"

#include "Handcrank/Game.hpp"
#include "Handcrank/ImageRenderObject.hpp"

using namespace Handcrank;

class GalagaEnemy
{

  private:
    Game *game;

    int enemyDirection = 1;

  public:
    std::unique_ptr<ImageRenderObject> image;

    GalagaEnemy(Game *_game) : game(_game)
    {
        image = std::make_unique<ImageRenderObject>();

        image->LoadTextureRW(game->GetRenderer(), images_galaga_enemy_1_png,
                             images_galaga_enemy_1_png_len);

        image->SetScale(5);

        image->SetRect((game->GetWidth() / 2) - 50, 150);

        image->SetUpdate(
            [this](GameObject *ref, double deltaTime)
            {
                if (!game->HasFocus())
                {
                    return;
                }

                auto rect = ref->GetRect();

                rect->x += enemyDirection * 5;

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
            });
    }
};
