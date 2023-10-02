#pragma once

#include <list>

#include <SDL.h>

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

    Game();

    bool Setup();

    void SetScreenSize(int width, int height);

    void SetTitle(const char *name);

    void SetClearColor(SDL_Color _color);

    bool GetQuit();

    void HandleInput();

    void Update();

    void Render();

    void Clean();

    void Quit();
};
