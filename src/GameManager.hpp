#pragma once

#include "../fonts/Emulogic.h"

#include "sdl/SDL_TTF_Utilities.hpp"

#include "Game.hpp"
#include "RectRenderObject.hpp"
#include "TextRenderObject.hpp"
#include "Utilities.hpp"

class GameManager
{

  private:
    Game *game;

    int score = 0;

    TTF_Font *font;

    const int fontSize = 100;

  public:
    std::unique_ptr<TextRenderObject> highScoreText;

    GameManager(Game *_game) : game(_game)
    {
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
    }
};
