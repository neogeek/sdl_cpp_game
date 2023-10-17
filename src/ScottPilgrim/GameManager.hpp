#pragma once

#include "../images/level.h"

#include "Handcrank/Game.hpp"
#include "Handcrank/ImageRenderObject.hpp"
#include "Handcrank/Utilities.hpp"

using namespace Handcrank;

#include "Roxzilla.hpp"
#include "ScottPilgrim.hpp"

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

        game->AddChildObject(std::move(image));

        auto scott = new ScottPilgrim(game);

        scott->image->SetRect(200, 600);

        game->AddChildObject(std::move(scott->image));

        auto roxzilla = new Roxzilla(game);

        roxzilla->image->SetRect(700, 600);

        game->AddChildObject(std::move(roxzilla->image));
    }
};
