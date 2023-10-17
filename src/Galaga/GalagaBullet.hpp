#pragma once

#include "../images/galaga_bullet_1.h"

#include "Handcrank/Game.hpp"
#include "Handcrank/ImageRenderObject.hpp"

using namespace Handcrank;

class GalagaBullet
{

  private:
    Game *game;

    RenderObject *spawner;

  public:
    std::unique_ptr<ImageRenderObject> image;

    GalagaBullet(Game *_game, RenderObject *_spawner)
        : game(_game), spawner(_spawner)
    {
        image = std::make_unique<ImageRenderObject>();

        image->LoadTextureRW(game->GetRenderer(), images_galaga_bullet_1_png,
                             images_galaga_bullet_1_png_len);

        image->SetScale(5);

        image->SetRect(
            spawner->GetRect()->x + spawner->GetTransformedRect()->w / 2 -
                (3 * image->GetScale() / 2),
            spawner->GetRect()->y - spawner->GetTransformedRect()->h);

        image->SetUpdate(
            [this](RenderObject *ref, double deltaTime)
            {
                if (!game->HasFocus())
                {
                    return;
                }

                auto position = ref->GetRect();

                position->y -= 20;

                if (position->y < 100)
                {
                    ref->Destroy();
                }
            });
    }
};
