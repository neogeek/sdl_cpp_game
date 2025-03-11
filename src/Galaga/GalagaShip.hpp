#pragma once

#include "../images/galaga_ship.h"

#include "Handcrank/Handcrank.hpp"
#include "Handcrank/ImageRenderObject.hpp"

using namespace Handcrank;

#include "GalagaBullet.hpp"

class GalagaShip : public ImageRenderObject
{

  private:
    double speed = 500;

    double nextFireDelay;

    const double fireRate = 0.1;

  public:
    void Start() override
    {
        LoadTextureRW(game->GetRenderer(), images_galaga_ship_png,
                      images_galaga_ship_png_len);

        SetScale(5);

        SetRect((game->GetWidth() / 2) - 50, game->GetHeight() - 150);
    }

    void Update(double deltaTime) override
    {
        if (!game->HasFocus())
        {
            return;
        }

        if (game->keyState[SDLK_LEFT])
        {
            GetRect()->x -= speed * deltaTime;
        }

        if (game->keyState[SDLK_RIGHT])
        {
            GetRect()->x += speed * deltaTime;
        }

        if (game->keyState[SDLK_SPACE])
        {
            nextFireDelay -= deltaTime;

            if (nextFireDelay <= 0)
            {
                auto bullet = std::make_unique<GalagaBullet>();

                auto transformedRect = GetTransformedRect();

                bullet->SetRect(GetRect()->x + (transformedRect.w / 2) -
                                    (GetRect()->w / 2),
                                GetRect()->y - transformedRect.h);

                game->AddChildObject(std::move(bullet));

                nextFireDelay = fireRate;
            }
        }
    }
};
