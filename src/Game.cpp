#include <iostream>

#include "Game.h"

#include <SDL.h>

#include "lib/SDL_Utilities.h"

Game::Game()
{
    SDL_CreateWindowAndRenderer(800, 600, SDL_WINDOW_SHOWN, &window, &renderer);
}

void Game::SetScreenSize(int width, int height)
{
    SDL_SetWindowSize(window, width, height);
}

void Game::SetTitle(const char *name)
{
    SDL_SetWindowTitle(window, name);
}

void Game::SetClearColor(SDL_Color _color)
{
    clearColor = _color;
}

bool Game::GetQuit()
{
    return quit;
}

bool Game::HandleInput()
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

    return SDL_PollEvent(&event) != 0;
}

void Game::Update()
{
}

void Game::Render()
{
    SDL_Utilities::ClearRect(renderer, clearColor);

    for (std::list<GameObject *>::iterator iter = gameObjects.begin(); iter != gameObjects.end(); iter++)
    {
        (*iter)->Render(renderer);
    }

    SDL_RenderPresent(renderer);
}

void Game::Clean()
{
    for (std::list<GameObject *>::iterator iter = gameObjects.begin(); iter != gameObjects.end(); iter++)
    {
        (*iter)->Clean();
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
}

void Game::Quit()
{
    quit = true;
}
