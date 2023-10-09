#pragma once

#include "../images/galaga_ship.h"

#include "Game.h"
#include "ImageRenderObject.h"

#include "GalagaBullet.hpp"

class GalagaShip
{

  private:
    Game *game;

    double nextTick;

  public:
    std::unique_ptr<ImageRenderObject> image;

    GalagaShip(Game *_game) : game(_game)
    {
        image = std::make_unique<ImageRenderObject>();

        image->LoadTextureRW(game->GetRenderer(), images_galaga_ship_png,
                             images_galaga_ship_png_len);

        image->SetScale(5);

        image->SetRect((game->GetWidth() / 2) - 50, game->GetHeight() - 150);

        image->SetUpdate(
            [this](GameObject *ref, double deltaTime)
            {
                if (!game->HasFocus())
                {
                    return;
                }

                if (game->keyState[SDLK_LEFT])
                {
                    ref->GetRect()->x -= 5;
                }

                if (game->keyState[SDLK_RIGHT])
                {
                    ref->GetRect()->x += 5;
                }

                if (game->keyState[SDLK_SPACE])
                {
                    nextTick += deltaTime;

                    if (nextTick > 0.15)
                    {
                        auto bullet = new GalagaBullet(game, ref);

                        game->gameObjects.push_back(std::move(bullet->image));

                        nextTick = 0;
                    }
                }
                else if (!game->keyState[SDLK_SPACE])
                {
                    nextTick = 0;
                }
            });
    }
};
