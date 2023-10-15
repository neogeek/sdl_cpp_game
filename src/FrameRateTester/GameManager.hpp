#pragma once

#include "Handcrank/Game.hpp"
#include "Handcrank/GameObject.hpp"

using namespace Handcrank;

class GameManager
{

  private:
    Game *game;

    int score = 0;

    TTF_Font *font;

    const int fontSize = 100;

  public:
    GameManager(Game *_game) : game(_game)
    {
        game->SetTitle("Frame Rate Tester");

        auto temp = std::make_unique<GameObject>();

        temp->SetUpdate([](GameObject *ref, double deltaTime)
                        { std::cout << "updated " << deltaTime << std::endl; });

        temp->SetFixedUpdate(
            [](GameObject *ref, double deltaTime)
            { std::cout << "fixed updated " << deltaTime << std::endl; });

        game->gameObjects.push_back(std::move(temp));
    }
};
