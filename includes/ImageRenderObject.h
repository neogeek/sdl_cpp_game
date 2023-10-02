#pragma once

#include <SDL.h>

#include <GameObject.h>

class ImageRenderObject : public GameObject
{

private:
    SDL_Texture *texture;

public:
    ImageRenderObject(SDL_Renderer *_renderer);
    ImageRenderObject(SDL_Renderer *_renderer, SDL_Rect *_rect);

    void LoadTexture(const char *path);
    void LoadTextureRW(const void *mem, int size);

    void Render() override;

    void Clean() override;
};
