#include "Handcrank/Handcrank.hpp"

using namespace Handcrank;

// #include "FrameRateTester/GameManager.hpp"
// #include "Galaga/GameManager.hpp"
#include "ScottPilgrim/GameManager.hpp"

Game *game = new Game();

int main()
{
    auto gamemanager = new GameManager(game);

    return game->Run();
}
