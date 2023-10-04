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

    double previousTime;
    double previousFixedTime;

    const double frameRate = 60;

    const double targetFrameTime = 1.0 / frameRate;

    const double fixedFrameTime = 0.02;

public:
    SDL_Window *window;
    SDL_Renderer *renderer;

    std::list<GameObject *> gameObjects;

    Game()
    {
        window = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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
        while (SDL_PollEvent(&event) != 0)
        {
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
    }

    void Update()
    {
        double currentTime = static_cast<double>(SDL_GetPerformanceCounter());

        double deltaTime = (currentTime - previousTime) / static_cast<double>(SDL_GetPerformanceFrequency());

        previousTime = currentTime;

        for (std::list<GameObject *>::iterator iter = gameObjects.begin(); iter != gameObjects.end(); iter++)
        {
            (*iter)->Update(deltaTime);
        }

        double frameTime = (static_cast<double>(SDL_GetPerformanceCounter()) - currentTime) / static_cast<double>(SDL_GetPerformanceFrequency());

        if (frameTime < targetFrameTime)
        {
            double delayTime = targetFrameTime - frameTime;
            double delayMilliseconds = delayTime * 1000.0;

            SDL_Delay(delayMilliseconds);
        }
    }

    void FixedUpdate()
    {
        double currentTime = static_cast<double>(SDL_GetTicks64()) / 1000;

        double elapsedTime = currentTime - previousFixedTime;

        if (elapsedTime >= fixedFrameTime)
        {
            std::cout << elapsedTime << std::endl;

            for (std::list<GameObject *>::iterator iter = gameObjects.begin(); iter != gameObjects.end(); iter++)
            {
                (*iter)->FixedUpdate(elapsedTime);
            }

            previousFixedTime = currentTime;
        }
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
