#pragma once

#include "../images/galaga_bullet_1.h"

#include "Game.h"
#include "ImageRenderObject.h"

class GalagaBullet
{

  private:
    Game *game;

    GameObject *spawner;

  public:
    std::unique_ptr<ImageRenderObject> image;

    GalagaBullet(Game *_game, GameObject *_spawner)
        : game(_game), spawner(_spawner)
    {
        image = std::make_unique<ImageRenderObject>();

        image->LoadTextureRW(game->GetRenderer(), images_galaga_bullet_1_png,
                             images_galaga_bullet_1_png_len);

        image->SetScale(5);

        image->SetRect(spawner->GetRect()->x + spawner->GetScaledRect()->w / 2 -
                           (3 * image->GetScale() / 2),
                       spawner->GetRect()->y - spawner->GetScaledRect()->h);

        image->SetUpdate(
            [this](GameObject *ref, double deltaTime)
            {
                if (!game->HasFocus())
                {
                    return;
                }

                SDL_Rect *position = ref->GetRect();

                position->y -= 20;

                if (position->y < 100)
                {
                    ref->Destroy();
                }
            });
    }
};
