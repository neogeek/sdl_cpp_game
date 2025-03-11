#pragma once

#include "../fonts/Emulogic.h"

#include "Handcrank/sdl/SDL_TTF_Utilities.hpp"

#include "Handcrank/Handcrank.hpp"
#include "Handcrank/TextRenderObject.hpp"
#include "Handcrank/Utilities.hpp"

using namespace Handcrank;

#include "GalagaEnemy.hpp"
#include "GalagaShip.hpp"

class GameManager : public RenderObject
{

  private:
    int score = 0;

    TTF_Font *font;

  public:
    std::unique_ptr<TextRenderObject> highScoreText;

    GalagaShip *galagaShip;
    GalagaEnemy *galagaEnemy;
    GalagaBullet *galagaBullet;

    void Start() override
    {
        game->SetTitle("Galaga");

        highScoreText = std::make_unique<TextRenderObject>();

        highScoreText->LoadFontRW(fonts_Emulogic_ttf, fonts_Emulogic_ttf_len,
                                  30);

        highScoreText->SetRect((game->GetWidth() / 2) - 100, 50, 200, 50);

        highScoreText->SetUpdate(
            [this](RenderObject *ref, double deltaTime)
            {
                TextRenderObject *textObj =
                    dynamic_cast<TextRenderObject *>(ref);

                textObj->SetText(LeftPad(std::to_string(score), '0', 5));
            });

        game->AddChildObject(std::move(highScoreText));

        game->AddChildObject(std::move(std::make_unique<GalagaEnemy>()));
        game->AddChildObject(std::move(std::make_unique<GalagaShip>()));
    }
};
