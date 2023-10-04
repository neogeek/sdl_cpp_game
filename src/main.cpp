#include <iostream>

#include <SDL.h>

#include "Game.h"

#include "GameObject.h"
#include "RectRenderObject.h"

Game game;

int main()
{
    game.SetTitle("My Super Cool Game");

    if (!game.Setup())
    {
        return 1;
    }

    GameObject spawner;

    std::list<GameObject *> gameObjects;

    double nextTick;

    spawner.SetUpdate([&nextTick](GameObject *ref, double deltaTime)
                      {
        nextTick += deltaTime;

        if (nextTick < 0.2)
        {
            return;
        }

        SDL_Rect *rect = new SDL_Rect{800-5, 1200, 10, 10};

        RectRenderObject *bullet = new RectRenderObject;

        (*bullet).SetRect(rect);

        (*bullet).SetFixedUpdate([](GameObject *ref, double deltaTime)
                                 {
                                     SDL_Rect *position = ref->GetRect();

                                     position->y -= 10;

                                     if (position->y < 100) {
                                        ref->Destroy();
                                     }
                                 });

        game.gameObjects.push_back(bullet);

        nextTick = 0; });

    game.gameObjects.push_back(&spawner);

    while (!game.GetQuit())
    {
        game.HandleInput();

        game.Update();
        game.FixedUpdate();
        game.Render();

        game.DestroyGameObjects();
    }

    game.Clean();

    return 0;
}
