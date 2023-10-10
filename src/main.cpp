#include "Game.hpp"

#include "GalagaEnemy.hpp"
#include "GalagaShip.hpp"
#include "GameManager.hpp"
#include "ScottPilgrim.hpp"

Game *game = new Game();

int main()
{
    game->SetTitle("My Super Cool Game");

    auto gamemanager = new GameManager(game);

    game->gameObjects.push_back(std::move(gamemanager->highScoreText));

    auto scott = new ScottPilgrim(game);

    game->gameObjects.push_back(std::move(scott->image));

    auto enemy = new GalagaEnemy(game);

    game->gameObjects.push_back(std::move(enemy->image));

    auto ship = new GalagaShip(game);

    game->gameObjects.push_back(std::move(ship->image));

    return game->Run();
}
