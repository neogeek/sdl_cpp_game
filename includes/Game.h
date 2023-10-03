#pragma once

#include <list>

#include <SDL.h>

#include "lib/SDL_Utilities.h"

#include "GameObject.h"

class Game
{

private:
    SDL_Color clearColor{0, 0, 0, 255};

    bool quit;

    SDL_Event event;

public:
    SDL_Window *window;
    SDL_Renderer *renderer;

    std::list<GameObject *> gameObjects;

    Game()
    {
        SDL_CreateWindowAndRenderer(800, 600, SDL_WINDOW_SHOWN, &window, &renderer);
    }

    bool Setup()
    {
        if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        {
            return false;
        }

        return true;
    }

    void SetScreenSize(int width, int height)
    {
        SDL_SetWindowSize(window, width, height);
    }

    void SetTitle(const char *name)
    {
        SDL_SetWindowTitle(window, name);
    }

    void SetClearColor(SDL_Color _color)
    {
        clearColor = _color;
    }

    bool GetQuit()
    {
        return quit;
    }

    void HandleInput()
    {
        if (SDL_PollEvent(&event) == 0)
        {
            return;
        }

        if (event.type == SDL_QUIT)
        {
            quit = true;
        }
        else if (event.type == SDL_KEYDOWN)
        {
            SDL_Keycode key = event.key.keysym.sym;

            if (key == SDLK_ESCAPE)
            {
                quit = true;
            }
        }
    }

    void Update()
    {
    }

    void Render()
    {
        SDL_Utilities::ClearRect(renderer, clearColor);

        for (std::list<GameObject *>::iterator iter = gameObjects.begin(); iter != gameObjects.end(); iter++)
        {
            (*iter)->Render(renderer);
        }

        SDL_RenderPresent(renderer);
    }

    void Clean()
    {
        for (std::list<GameObject *>::iterator iter = gameObjects.begin(); iter != gameObjects.end(); iter++)
        {
            (*iter)->Clean();
        }

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);

        SDL_Quit();
    }

    void Quit()
    {
        quit = true;
    }
};
