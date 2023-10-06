#include <iostream>

// #include <emscripten.h>

#include <SDL.h>

#include "Game.h"

#include "GameObject.h"
#include "RectRenderObject.h"

Game game;

// void main_loop()
// {
//     if (game.GetQuit())
//     {
//         emscripten_cancel_main_loop();

//         return;
//     }

//     game.Loop();
// }

void spawn_bullet()
{
    auto *rect = new SDL_Rect{800-5, 1200, 10, 10};

    auto *bullet = new RectRenderObject;

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
}

int main()
{
    game.SetTitle("My Super Cool Game");

    auto *spawner = new GameObject;

    std::list<GameObject *> gameObjects;

    double nextTick;

    int spawnedBullets = 0;

    spawner->SetUpdate([&nextTick, &spawnedBullets](GameObject *ref, double deltaTime)
                       {
        nextTick += deltaTime;

        if (nextTick < 0.02)
        {
            return;
        }

        spawn_bullet();

        nextTick = 0;

        spawnedBullets++; });

    game.gameObjects.push_back(spawner);

    // game.Setup();

    // emscripten_set_main_loop(main_loop, 0, 1);

    // game.Clean();

    // return 0;

    return game.Run();
}
