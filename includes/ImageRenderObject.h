#pragma once

#include <SDL.h>

#include <GameObject.h>

class ImageRenderObject : public GameObject
{

private:
    SDL_Texture *texture;

public:
    explicit ImageRenderObject(SDL_Rect *_rect);

    ~ImageRenderObject();

    void LoadTexture(SDL_Renderer *renderer, const char *path);
    void LoadTextureRW(SDL_Renderer *renderer, const void *mem, int size);

    void Render(SDL_Renderer *renderer) override;

    void Clean() override;
};
