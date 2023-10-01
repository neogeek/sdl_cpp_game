#include <iostream>
#include <string>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "RenderObject.h"

const Uint32 SCREEN_WIDTH = 800;
const Uint32 SCREEN_HEIGHT = 600;

SDL_Window *window;
SDL_Renderer *renderer;

void input()
{
}

void update()
{
}

void render()
{
}

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

/**
 * Fills the screen with a color.
 *
 * @param renderer A structure representing rendering state.
 * @param color Color struct.
 */
void clearRect(SDL_Renderer *renderer, SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    SDL_RenderClear(renderer);
}

/**
 * Render a rect with a color.
 *
 * @param renderer A structure representing rendering state.
 * @param rect A rectangle, with the origin at the upper left (integer).
 * @param color Color struct.
 */
void renderRect(SDL_Renderer *renderer, SDL_Rect rect, SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    SDL_RenderFillRect(renderer, &rect);
}

SDL_Texture *loadTexture(SDL_Renderer *renderer, const char *path)
{
    SDL_Surface *surface = IMG_Load(path);

    if (!surface)
    {
        return NULL;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!texture)
    {
        return NULL;
    }

    return texture;
}

TTF_Font *loadFont(const char *path, int ptSize = 24)
{
    TTF_Font *font = TTF_OpenFont(path, ptSize);

    if (!font)
    {
        return NULL;
    }

    return font;
}

void renderText(SDL_Renderer *renderer, TTF_Font *font, SDL_Color color, SDL_Rect rect, const char *content)
{
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, content, color);

    if (!textSurface)
    {
        return;
    }

    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    if (!textTexture)
    {
        return;
    }

    SDL_RenderCopy(renderer, textTexture, NULL, &rect);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

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

    SDL_Event event;

    Uint32 prevTicks = SDL_GetTicks();
    Uint32 frameTime = 1000 / 60;

    SDL_Rect rect = {100, 100, 200, 150};
    SDL_Rect rect2 = {90, 90, 200, 150};

    SDL_Texture *galagaShipTexture = loadTexture(renderer, "../images/galaga_ship.png");
    SDL_Rect galagaShipRect = {0, 0, 15 * 4, 16 * 4};

    SDL_Rect textRect = {100, 0, 250, 50};

    TTF_Font *font = loadFont("../fonts/Roboto/Roboto-Regular.ttf", 200);

    RenderObject square(renderer, rect2);

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

        clearRect(renderer, Black);

        renderRect(renderer, rect, Red);

        SDL_RenderCopy(renderer, galagaShipTexture, NULL, &galagaShipRect);

        renderText(renderer, font, White, textRect, "Hello World");

        square.Render();

        SDL_RenderPresent(renderer);

        Uint32 currentTicks = SDL_GetTicks();
        Uint32 elapsedTicks = currentTicks - prevTicks;

        if (elapsedTicks < frameTime)
        {
            SDL_Delay(frameTime - elapsedTicks);
        }

        prevTicks = currentTicks;
    }

    SDL_DestroyTexture(galagaShipTexture);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
