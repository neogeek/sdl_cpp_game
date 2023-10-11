#pragma once

#include "../fonts/Emulogic.h"

#include "sdl/SDL_TTF_Utilities.hpp"

#include "Game.hpp"
#include "TextRenderObject.hpp"
#include "Utilities.hpp"

#include "Galaga/GalagaEnemy.hpp"
#include "Galaga/GalagaShip.hpp"

class GameManager
{

  private:
    Game *game;

    int score = 0;

    TTF_Font *font;

    const int fontSize = 100;

  public:
    std::unique_ptr<TextRenderObject> highScoreText;

    GalagaShip *galagaShip;
    GalagaEnemy *galagaEnemy;
    GalagaBullet *galagaBullet;

    GameManager(Game *_game) : game(_game)
    {
        game->SetTitle("Galaga");

        highScoreText = std::make_unique<TextRenderObject>();

        font = SDL_TTF_Utilities::LoadFontRW(fonts_Emulogic_ttf,
                                             fonts_Emulogic_ttf_len, 100);

        highScoreText->SetFont(font);

        highScoreText->SetRect((game->GetWidth() / 2) - 100, 50, 200, 50);

        highScoreText->SetUpdate(
            [this](GameObject *ref, double deltaTime)
            {
                TextRenderObject *textObj =
                    dynamic_cast<TextRenderObject *>(ref);

                textObj->SetText(
                    Utilities::LeftPad(std::to_string(score), '0', 5));
            });

        game->gameObjects.push_back(std::move(highScoreText));

        galagaEnemy = new GalagaEnemy(game);

        game->gameObjects.push_back(std::move(galagaEnemy->image));

        galagaShip = new GalagaShip(game);

        game->gameObjects.push_back(std::move(galagaShip->image));
    }
};
