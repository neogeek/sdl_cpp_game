#pragma once

#include "Handcrank/Handcrank.hpp"

using namespace Handcrank;

class GameManager : public RenderObject
{

  public:
    void Start() override { game->SetTitle("Yet Another Roguelike Tutorial"); }

    void Update(double deltaTime) override
    {
        if (game->keyState[SDLK_ESCAPE])
        {
            game->Quit();
        }
    }
};
