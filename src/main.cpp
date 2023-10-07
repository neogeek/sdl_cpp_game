#include <iostream>
#include <memory>

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

void spawn_bullet(GameObject *spawner)
{
    auto *rect =
        new SDL_Rect{spawner->GetRect()->x + 5, spawner->GetRect()->y, 10, 10};

    std::unique_ptr<RectRenderObject> bullet(new RectRenderObject());

    bullet->SetRect(rect);

    bullet->SetFixedUpdate(
        [](GameObject *ref, double deltaTime)
        {
            SDL_Rect *position = ref->GetRect();

            position->y -= 20;

            if (position->y < 100)
            {
                ref->Destroy();
            }
        });

    game.gameObjects.push_back(std::move(bullet));
}

int main()
{
    game.SetTitle("My Super Cool Game");

    std::unique_ptr<RectRenderObject> spawner(new RectRenderObject());

    auto spawnerRect =
        new SDL_Rect{game.GetWidth() / 2 - 10, game.GetHeight() - 40, 20, 20};

    spawner->SetRect(spawnerRect);

    double nextTick;

    int spawnedBullets = 0;

    spawner->SetUpdate(
        [&nextTick, &spawnedBullets](GameObject *ref, double deltaTime)
        {
            if (game.isSpacePressed)
            {
                spawn_bullet(ref);
            }

            if (game.isLeftPressed)
            {
                ref->GetRect()->x -= 5;
            }

            if (game.isRightPressed)
            {
                ref->GetRect()->x += 5;
            }
        });

    game.gameObjects.push_back(std::move(spawner));

    // game.Setup();

    // emscripten_set_main_loop(main_loop, 0, 1);

    // game.Clean();

    // return 0;

    return game.Run();
}
