#pragma once

#include <SDL.h>

#include "sdl/SDL_Image_Utilities.hpp"
#include "sdl/SDL_Utilities.hpp"

#include "GameObject.hpp"

class ImageRenderObject : public GameObject
{
  private:
    SDL_Texture *texture;

    SDL_Rect *srcRect;

  public:
    explicit ImageRenderObject() : GameObject() {}
    explicit ImageRenderObject(SDL_Rect *_rect) : GameObject(_rect) {}

    ~ImageRenderObject() { Clean(); }

    /**
     * Load textures by path.
     * @param path Path to a local texture.
     *
     * @deprecated DEVELOPMENT USE ONLY! Use LoadTextureRW to load textures in a
     * final build.
     */
    void LoadTexture(SDL_Renderer *renderer, const char *path)
    {
        texture = SDL_Image_Utilities::LoadTexture(renderer, path);

        UpdateRectSizeFromTexture();
    }

    /**
     * Load textures from memory buffer.
     * @param mem Pointer to a read-only buffer. (texture loaded in via header
     * file)
     * @param size Length of a buffer in bytes.
     */
    void LoadTextureRW(SDL_Renderer *renderer, const void *mem, int size)
    {
        texture = SDL_Image_Utilities::LoadTextureRW(renderer, mem, size);

        UpdateRectSizeFromTexture();
    }

    void UpdateRectSizeFromTexture()
    {
        int textureWidth;
        int textureHeight;

        SDL_QueryTexture(texture, NULL, NULL, &textureWidth, &textureHeight);

        rect->w = textureWidth;
        rect->h = textureHeight;
    }

    void SetSrcRect(SDL_Rect *srcRect) { this->srcRect = srcRect; }

    void SetSrcRect(int x, int y, int w, int h)
    {
        if (srcRect == nullptr)
        {
            srcRect = new SDL_Rect{x, y, w, h};

            return;
        }

        this->srcRect->x = x;
        this->srcRect->y = y;
        this->srcRect->w = w;
        this->srcRect->h = h;
    }

    /**
     * Render image to the scene.
     */
    void Render(SDL_Renderer *renderer) override
    {
        SDL_RenderCopy(renderer, texture, srcRect, GetScaledRect());
    }

    /**
     * Cleanup function to run after the GameObject is unloaded.
     */
    void Clean() override { SDL_DestroyTexture(texture); }
};
