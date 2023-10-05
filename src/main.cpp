#include <iostream>

#include <SDL.h>

#include "Game.h"

#include "GameObject.h"
#include "RectRenderObject.h"

Game game;

int main()
{
    game.SetTitle("My Super Cool Game");

    GameObject spawner;

    std::list<GameObject *> gameObjects;

    double nextTick;

    int spawnedBullets = 0;

    spawner.SetUpdate([&nextTick, &spawnedBullets](GameObject *ref, double deltaTime)
                      {
        nextTick += deltaTime;

        if (nextTick < 0.02)
        {
            return;
        }

        SDL_Rect *rect = new SDL_Rect{800-5, 1200, 10, 10};

        RectRenderObject *bullet = new RectRenderObject;

        bullet->SetRect(rect);

        bullet->SetFixedUpdate([](GameObject *ref, double deltaTime)
                                 {
                                     SDL_Rect *position = ref->GetRect();

                                     position->y -= 20;

                                     if (position->y < 100) {
                                        ref->Destroy();
                                     }
                                 });

        game.gameObjects.push_back(bullet);

        nextTick = 0;

        spawnedBullets++; });

    game.gameObjects.push_back(&spawner);

    return game.Run();
}
