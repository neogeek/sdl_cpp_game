#include <memory>

// #include <emscripten.h>

#include "../images/galaga_bullet_1.h"
#include "../images/galaga_enemy_1.h"
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

std::unique_ptr<ImageRenderObject> create_bullet(GameObject *spawner)
{
    std::unique_ptr<ImageRenderObject> bullet(new ImageRenderObject());

    bullet->LoadTextureRW(game.GetRenderer(), images_galaga_bullet_1_png,
                          images_galaga_bullet_1_png_len);

    const int scale = 5;

    auto *rect = new SDL_Rect{spawner->GetRect()->x + 50 - (3 * scale) / 2,
                              spawner->GetRect()->y - 40, 3 * scale, 8 * scale};

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

    return bullet;
}

int enemyDirection = 1;

std::unique_ptr<ImageRenderObject> create_enemy()
{
    std::unique_ptr<ImageRenderObject> enemy(new ImageRenderObject());

    enemy->LoadTextureRW(game.GetRenderer(), images_galaga_enemy_1_png,
                         images_galaga_enemy_1_png_len);

    auto enemyRect = new SDL_Rect{(game.GetWidth() / 2) - 50, 150, 100, 100};

    enemy->SetRect(enemyRect);

    enemy->SetUpdate(
        [](GameObject *ref, double deltaTime)
        {
            auto rect = ref->GetRect();

            rect->x += enemyDirection * 5;

            if (enemyDirection == 1 && rect->x > game.GetWidth() - 200)
            {
                rect->x = game.GetWidth() - 200;
                enemyDirection = -1;
            }
            else if (enemyDirection == -1 && rect->x < 100)
            {
                rect->x = 100;
                enemyDirection = 1;
            }
        });

    return enemy;
}

double nextTick;

std::unique_ptr<ImageRenderObject> create_ship()
{
    std::unique_ptr<ImageRenderObject> ship(new ImageRenderObject());

    ship->LoadTextureRW(game.GetRenderer(), images_galaga_ship_png,
                        images_galaga_ship_png_len);

    auto spawnerRect = new SDL_Rect{(game.GetWidth() / 2) - 50,
                                    game.GetHeight() - 150, 100, 100};

    ship->SetRect(spawnerRect);

    ship->SetUpdate(
        [](GameObject *ref, double deltaTime)
        {
            if (game.keyState[SDLK_LEFT])
            {
                ref->GetRect()->x -= 5;
            }

            if (game.keyState[SDLK_RIGHT])
            {
                ref->GetRect()->x += 5;
            }

            if (game.keyState[SDLK_SPACE])
            {
                nextTick += deltaTime;

                if (nextTick > 0.15)
                {
                    auto bullet = create_bullet(ref);

                    game.gameObjects.push_back(std::move(bullet));

                    nextTick = 0;
                }
            }
        });

    game.gameObjects.push_back(std::move(ship));

    return ship;
}

int main()
{
    game.SetTitle("My Super Cool Game");

    auto enemy = create_enemy();

    game.gameObjects.push_back(std::move(enemy));

    auto ship = create_ship();

    game.gameObjects.push_back(std::move(ship));

    // game.Setup();

    // emscripten_set_main_loop(main_loop, 0, 1);

    // game.Clean();

    // return 0;

    return game.Run();
}
