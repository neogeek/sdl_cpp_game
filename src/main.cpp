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

    RectRenderObject square;

    square.SetStart([](GameObject *ref)
                    {
                        std::cout << "start" << std::endl;

                        (*ref).GetRect()->w = 100;
                        (*ref).GetRect()->h = 100; });

    square.SetUpdate([](GameObject *ref, double deltaTime)
                     {
                         std::cout << "update" << std::endl;

                         (*ref).GetRect()->x += 1; });

    square.SetFixedUpdate([](GameObject *ref, double deltaTime)
                          { std::cout << "fixed update" << std::endl; });

    square.SetColor({255, 255, 255});

    game.gameObjects.push_back(&square);

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
