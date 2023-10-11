#pragma once

#include "../images/level.h"

#include "ScottPilgrim/Roxzilla.hpp"
#include "ScottPilgrim/ScottPilgrim.hpp"

#include "Game.hpp"
#include "ImageRenderObject.hpp"
#include "Utilities.hpp"

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
        game->SetTitle("Scott Pilgrim");

        game->SetScreenSize(1200, 568);

        auto image = std::make_unique<ImageRenderObject>();

        image->LoadTextureRW(game->GetRenderer(), images_level_png,
                             images_level_png_len);

        image->SetScale(4);

        game->gameObjects.push_back(std::move(image));

        auto scott = new ScottPilgrim(game);

        scott->image->SetRect(200, 600);

        game->gameObjects.push_back(std::move(scott->image));

        auto roxzilla = new Roxzilla(game);

        roxzilla->image->SetRect(700, 600);

        game->gameObjects.push_back(std::move(roxzilla->image));
    }
};
