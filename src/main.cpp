#include "../fonts/Emulogic.h"

#include "Game.h"
#include "TextRenderObject.h"
#include "Utilities.h"

#include "GalagaEnemy.hpp"
#include "GalagaShip.hpp"
#include "ScottPilgrim.hpp"

Game *game = new Game();

int score = 0;

std::unique_ptr<TextRenderObject> create_highscore()
{
    auto font = SDL_TTF_Utilities::LoadFontRW(fonts_Emulogic_ttf,
                                              fonts_Emulogic_ttf_len, 100);

    std::unique_ptr<TextRenderObject> highScore(new TextRenderObject);

    auto highScoreRect =
        new SDL_Rect{(game->GetWidth() / 2) - 100, 50, 200, 50};

    highScore->SetFont(font);

    highScore->SetRect(highScoreRect);

    highScore->SetUpdate(
        [](GameObject *ref, double deltaTime)
        {
            TextRenderObject *textObj = dynamic_cast<TextRenderObject *>(ref);

            textObj->SetText(Utilities::LeftPad(std::to_string(score), '0', 5));
        });

    return highScore;
}

int main()
{
    game->SetTitle("My Super Cool Game");

    auto highscore = create_highscore();

    game->gameObjects.push_back(std::move(highscore));

    auto scott = new ScottPilgrim(game);

    game->gameObjects.push_back(std::move(scott->image));

    auto enemy = new GalagaEnemy(game);

    game->gameObjects.push_back(std::move(enemy->image));

    auto ship = new GalagaShip(game);

    game->gameObjects.push_back(std::move(ship->image));

    return game->Run();
}
