#pragma once

#include <SDL.h>

#include <RenderObject.h>

class ImageRenderObject : public RenderObject
{

private:
    SDL_Texture *texture;

public:
    ImageRenderObject(SDL_Renderer *_renderer);
    ImageRenderObject(SDL_Renderer *_renderer, SDL_Rect *_rect);

    void Render();

    void LoadTexture(const char *path);

    void Clean();
};
