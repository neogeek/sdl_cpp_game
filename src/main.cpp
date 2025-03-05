#include "Handcrank/Handcrank.hpp"

using namespace Handcrank;

// #include "FrameRateTester/GameManager.hpp"
// #include "Galaga/GameManager.hpp"
// #include "ScottPilgrim/GameManager.hpp"
// #include "Roguelike/GameManager.hpp"
// #include "MidiGame/GameManager.hpp"
#include "Breakout/GameManager.hpp"

Game *game = new Game();

int main()
{
    game->AddChildObject(std::make_unique<GameManager>());

    return game->Run();
}
