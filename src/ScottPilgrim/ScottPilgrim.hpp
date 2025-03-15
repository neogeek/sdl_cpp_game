#pragma once

#include "../images/scott-pilgrim-idle.h"
#include "../images/scott-pilgrim-run.h"

#include "Handcrank/Handcrank.hpp"
#include "Handcrank/SpriteRenderObject.hpp"

using namespace Handcrank;

class ScottPilgrim : public SpriteRenderObject
{
  private:
    std::shared_ptr<SDL_Texture> idleTexture;
    std::shared_ptr<SDL_Texture> runTexture;

    bool isRunning = false;

  public:
    void Start() override
    {
        idleTexture = SDL_LoadTextureRW(game->GetRenderer(),
                                        images_scott_pilgrim_idle_png,
                                        images_scott_pilgrim_idle_png_len);

        runTexture =
            SDL_LoadTextureRW(game->GetRenderer(), images_scott_pilgrim_run_png,
                              images_scott_pilgrim_run_png_len);

        SetIdleTexture();

        SetScale(4);

        SetRect(200, 600);

        Play();
    }
    void Update(double deltaTime) override
    {
        auto transformedRect = GetTransformedRect();

        auto movementSpeed = 600;

        auto rect = GetRect();

        if (game->keyState[SDLK_RIGHT])
        {
            rect->x += movementSpeed * deltaTime;

            SetFlip(SDL_FLIP_NONE);
        }
        else if (game->keyState[SDLK_LEFT])
        {
            rect->x -= movementSpeed * deltaTime;

            SetFlip(SDL_FLIP_HORIZONTAL);
        }

        if (game->keyState[SDLK_RIGHT] || game->keyState[SDLK_LEFT])
        {
            if (!isRunning)
            {
                isRunning = true;

                SetRunTexture();
            }
        }
        else
        {
            if (isRunning)
            {
                isRunning = false;

                SetIdleTexture();
            }
        }

        if (game->keyState[SDLK_UP])
        {
            rect->y -= movementSpeed * deltaTime;
        }
        else if (game->keyState[SDLK_DOWN])
        {
            rect->y += movementSpeed * deltaTime;
        }
    }
    void SetIdleTexture()
    {
        SetTexture(idleTexture);
        CalculateFrames(288, 59, 8, 1, Vector2(0, 0), Vector2(0, 0));
    }
    void SetRunTexture()
    {
        SetTexture(runTexture);
        CalculateFrames(424, 60, 8, 1, Vector2(0, 0), Vector2(0, 0));
    }
};
