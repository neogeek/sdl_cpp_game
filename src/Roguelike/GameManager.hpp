#pragma once

#include "Handcrank/Handcrank.hpp"

#include "Dungeon.hpp"
#include "Player.hpp"

using namespace Handcrank;

class GameManager : public RenderObject
{

  public:
    void Start() override
    {
        game->SetTitle("Yet Another Roguelike Tutorial");

        game->AddChildObject(std::move(std::make_unique<Dungeon>()));
        game->AddChildObject(std::move(std::make_unique<Player>()));
    }

    void Update(double deltaTime) override
    {
        if (game->keyState[SDLK_ESCAPE])
        {
            game->Quit();
        }
    }
};
