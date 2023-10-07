#pragma once

#include <list>
#include <memory>

#include <SDL.h>

#include "sdl/SDL_Utilities.h"

#include "GameObject.h"

class Game
{

  private:
    SDL_Window *window;
    SDL_Renderer *renderer;

    SDL_Color clearColor{0, 0, 0, 255};

    bool quit = false;

    SDL_Event event;

    double previousTime = 0;
    double previousFixedTime = 0;

    const double frameRate = 60;

    const double targetFrameTime = 1.0 / frameRate;

    const double fixedFrameTime = 0.02;

    int width;
    int height;

  public:
    std::unordered_map<SDL_Keycode, bool> keyState;

    std::list<std::unique_ptr<GameObject>> gameObjects;

    Game()
    {
        window = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED, 800, 600,
                                  SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI);
        renderer = SDL_CreateRenderer(
            window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        SDL_GL_GetDrawableSize(window, &width, &height);
    }

    [[nodiscard]] SDL_Window *GetWindow() const { return window; }

    [[nodiscard]] SDL_Renderer *GetRenderer() const { return renderer; }

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

    void SetTitle(const char *name) { SDL_SetWindowTitle(window, name); }

    void SetClearColor(SDL_Color _color) { clearColor = _color; }

    int GetWidth() const { return width; }

    int GetHeight() const { return height; }

    [[nodiscard]] bool GetQuit() const { return quit; }

    int Run()
    {
        if (!Setup())
        {
            return 1;
        }

        while (!GetQuit())
        {
            Loop();
        }

        Clean();

        return 0;
    }

    void Loop()
    {
        HandleInput();

        Update();
        FixedUpdate();
        Render();

        DestroyGameObjects();
    }

    void HandleInput()
    {
        while (SDL_PollEvent(&event) != 0)
        {
            SDL_Keycode key = event.key.keysym.sym;

            switch (event.type)
            {
            case SDL_QUIT:
                Quit();
                break;
            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_RESIZED ||
                    event.window.event == SDL_WINDOWEVENT_RESTORED ||
                    event.window.event == SDL_WINDOWEVENT_MAXIMIZED ||
                    event.window.event == SDL_WINDOWEVENT_MINIMIZED)
                {
                    SDL_GL_GetDrawableSize(window, &width, &height);
                }
                break;

            case SDL_KEYDOWN:
                keyState[key] = true;
                break;

            case SDL_KEYUP:
                keyState[key] = false;
                break;

            default:
                break;
            }
        }
    }

    void Update()
    {
        auto currentTime = static_cast<double>(SDL_GetPerformanceCounter());

        double deltaTime = (currentTime - previousTime) /
                           static_cast<double>(SDL_GetPerformanceFrequency());

        previousTime = currentTime;

        for (auto iter = gameObjects.begin(); iter != gameObjects.end(); iter++)
        {
            auto gameObject = iter->get();

            if (gameObject != nullptr)
            {
                gameObject->Update(deltaTime);
            }
        }

        double frameTime =
            (static_cast<double>(SDL_GetPerformanceCounter()) - currentTime) /
            static_cast<double>(SDL_GetPerformanceFrequency());

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
            for (auto iter = gameObjects.begin(); iter != gameObjects.end();
                 iter++)
            {
                auto gameObject = iter->get();

                if (gameObject != nullptr)
                {
                    gameObject->FixedUpdate(elapsedTime);
                }
            }

            previousFixedTime = currentTime;
        }
    }

    void Render()
    {
        SDL_Utilities::ClearRect(renderer, clearColor);

        for (auto iter = gameObjects.begin(); iter != gameObjects.end(); iter++)
        {
            auto gameObject = iter->get();

            if (gameObject != nullptr)
            {
                gameObject->Render(renderer);
            }
        }

        SDL_RenderPresent(renderer);
    }

    void DestroyGameObjects()
    {
        for (auto iter = gameObjects.begin(); iter != gameObjects.end();)
        {
            auto gameObject = iter->get();

            if (gameObject != nullptr && gameObject->HasBeenMarkedForDestroy())
            {
                iter = gameObjects.erase(iter);
            }
            else
            {
                ++iter;
            }
        }
    }

    void Clean()
    {
        for (auto iter = gameObjects.begin(); iter != gameObjects.end(); iter++)
        {
            auto gameObject = iter->get();

            if (gameObject != nullptr)
            {
                gameObject->Clean();
            }
        }

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);

        SDL_Quit();
    }

    void Quit() { quit = true; }
};
