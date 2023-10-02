#pragma once

#include <list>

#include <SDL.h>

#include "GameObject.h"

class Game
{

private:
    SDL_Color clearColor;

    bool quit;

    SDL_Event event;

public:
    SDL_Window *window;
    SDL_Renderer *renderer;

    std::list<GameObject *> gameObjects;

    Game();

    void SetScreenSize(int width, int height);

    void SetTitle(const char *name);

    void SetClearColor(SDL_Color _color);

    bool GetQuit();

    bool HandleInput();

    void Update();

    void Render();

    void Clean();

    void Quit();
};
