#include <iostream>
#include <list>
#include <string>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "GameObject.h"
#include "ImageRenderObject.h"
#include "RectRenderObject.h"
#include "TextRenderObject.h"

#include "Roboto/Roboto-Regular.h"

#include "galaga_ship.h"

#include "lib/SDL_Utilities.h"
#include "lib/SDL_Image_Utilities.h"
#include "lib/SDL_TTF_Utilities.h"

const Uint32 SCREEN_WIDTH = 800;
const Uint32 SCREEN_HEIGHT = 600;

SDL_Window *window;
SDL_Renderer *renderer;

const SDL_Color Black = {};
const SDL_Color White = {255, 255, 255};
const SDL_Color Red = {255, 0, 0};

typedef struct Keybindings
{
    SDL_KeyCode up = SDLK_UP;
    SDL_KeyCode down = SDLK_DOWN;
    SDL_KeyCode left = SDLK_LEFT;
    SDL_KeyCode right = SDLK_RIGHT;
    SDL_KeyCode quit = SDLK_ESCAPE;
} Keybindings;

const Keybindings LocalKeybindings = {};

int main()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return 1;
    }

    if (TTF_Init() == -1)
    {
        return 1;
    }

    SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN, &window, &renderer);

    SDL_SetWindowTitle(window, "My Super Cool Game");

    bool quit = false;

    std::list<GameObject *> gos;

    SDL_Event event;

    Uint32 prevTicks = SDL_GetTicks();
    Uint32 frameTime = 1000 / 60;

    SDL_Rect rect = {100, 100, 200, 150};
    SDL_Rect rect2 = {90, 90, 200, 150};

    SDL_Rect galagaShipRect = {0, 0, 15 * 4, 16 * 4};

    ImageRenderObject galagaShip(renderer, &galagaShipRect);
    galagaShip.LoadTextureRW(images_galaga_ship_png, images_galaga_ship_png_len);

    gos.push_back(&galagaShip);

    SDL_Rect textRect = {100, 0, 250, 50};

    TTF_Font *font = SDL_TTF_Utilities::LoadFontRW(fonts_Roboto_Roboto_Regular_ttf, fonts_Roboto_Roboto_Regular_ttf_len, 200);

    TextRenderObject label(renderer, &textRect);
    label.SetFont(font);
    label.SetColor(White);
    label.SetText("Hello, World!");

    gos.push_back(&label);

    RectRenderObject square1(renderer, &rect);
    square1.SetColor(Red);

    RectRenderObject square2(renderer, &rect2);
    square2.SetColor(White);

    gos.push_back(&square1);
    gos.push_back(&square2);

    while (!quit)
    {
        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                SDL_Keycode key = event.key.keysym.sym;

                if (key == LocalKeybindings.up)
                {
                    rect.y -= 10;
                }
                else if (key == LocalKeybindings.down)
                {
                    rect.y += 10;
                }

                if (key == LocalKeybindings.left)
                {
                    rect.x -= 10;
                }
                else if (key == LocalKeybindings.right)
                {
                    rect.x += 10;
                }

                if (key == LocalKeybindings.quit)
                {
                    quit = true;
                }
            }
        }

        if (rect.x + rect.w > SCREEN_WIDTH)
        {
            rect.x = SCREEN_WIDTH - rect.w;
        }
        else if (rect.x < 0)
        {
            rect.x = 0;
        }

        if (rect.y + rect.h > SCREEN_HEIGHT)
        {
            rect.y = SCREEN_HEIGHT - rect.h;
        }
        else if (rect.y < 0)
        {
            rect.y = 0;
        }

        SDL_Utilities::ClearRect(renderer, Black);

        for (std::list<GameObject *>::iterator iter = gos.begin(); iter != gos.end(); iter++)
        {
            (*iter)->Render();
        }

        SDL_RenderPresent(renderer);

        Uint32 currentTicks = SDL_GetTicks();
        Uint32 elapsedTicks = currentTicks - prevTicks;

        if (elapsedTicks < frameTime)
        {
            SDL_Delay(frameTime - elapsedTicks);
        }

        prevTicks = currentTicks;
    }

    for (std::list<GameObject *>::iterator iter = gos.begin(); iter != gos.end(); iter++)
    {
        (*iter)->Clean();
    }

    TTF_CloseFont(font);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
