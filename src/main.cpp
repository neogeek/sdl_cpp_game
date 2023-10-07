#include <memory>

// #include <emscripten.h>

#include "../images/galaga_ship.h"

#include <SDL.h>

#include "Game.h"
#include "GameObject.h"
#include "ImageRenderObject.h"
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
        new SDL_Rect{spawner->GetRect()->x + 50 - 5, spawner->GetRect()->y - 40, 10, 10};

    std::unique_ptr<RectRenderObject> bullet(new RectRenderObject());

    bullet->SetRect(rect);

    bullet->SetFixedUpdate(
        [](GameObject *ref, double deltaTime)
        {
            if (!game.HasFocus())
            {
                return;
            }

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

    std::unique_ptr<ImageRenderObject> ship(new ImageRenderObject());

    ship->LoadTextureRW(game.GetRenderer(), images_galaga_ship_png, images_galaga_ship_png_len);

    auto spawnerRect =
        new SDL_Rect{(game.GetWidth() / 2) - 50, game.GetHeight() - 150, 100, 100};

    ship->SetRect(spawnerRect);

    double nextTick;

    int spawnedBullets = 0;

    ship->SetUpdate(
        [&nextTick, &spawnedBullets](GameObject *ref, double deltaTime)
        {
            if (game.keyState[SDLK_SPACE])
            {
                spawn_bullet(ref);
            }

            if (game.keyState[SDLK_LEFT])
            {
                ref->GetRect()->x -= 5;
            }

            if (game.keyState[SDLK_RIGHT])
            {
                ref->GetRect()->x += 5;
            }
        });

    game.gameObjects.push_back(std::move(ship));

    // game.Setup();

    // emscripten_set_main_loop(main_loop, 0, 1);

    // game.Clean();

    // return 0;

    return game.Run();
}
