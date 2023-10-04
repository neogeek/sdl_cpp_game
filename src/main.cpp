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

    SDL_Rect temp{0, 0, 100, 100};

    RectRenderObject square(&temp);

    square.SetUpdate([&temp](double deltaTime)
                     {
                         if (temp.x > 400)
                         {
                             temp.x = 0;
                         }

                         if (temp.y > 400)
                         {
                             temp.y = 0;
                         }

                        //  std::printf("%f\n", deltaTime);

                         temp.x += 1;
                         temp.y += 1; });

    square.SetColor({255, 255, 255});

    game.gameObjects.push_back(&square);

    while (!game.GetQuit())
    {
        game.HandleInput();

        game.Update();
        game.Render();
    }

    game.Clean();

    return 0;
}
