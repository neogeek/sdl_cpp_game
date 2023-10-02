#include <SDL.h>

#include "Game.h"

#include "RectRenderObject.h"

Game game;

int main()
{
    game.SetTitle("My Super Cool Game");

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return 1;
    }

    SDL_Rect temp{0, 0, 100, 100};

    RectRenderObject square(&temp);

    square.SetColor({255, 255, 255});

    game.gameObjects.push_back(&square);

    while (!game.GetQuit())
    {
        while (game.HandleInput())
        {
            game.Render();
        }
    }

    game.Clean();

    return 0;
}
