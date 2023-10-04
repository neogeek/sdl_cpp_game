#include <iostream>

#include <SDL.h>

#include "Game.h"

#include "RectRenderObject.h"

Game game;

int main()
{
    game.SetTitle("My Super Cool Game");

    if (!game.Setup())
    {
        return 1;
    }

    while (!game.GetQuit())
    {
        game.HandleInput();

        game.Update();
        game.FixedUpdate();
        game.Render();
    }

    game.Clean();

    return 0;
}
