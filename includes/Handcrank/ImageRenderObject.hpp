// Copyright (c) Scott Doxey. All Rights Reserved. Licensed under the MIT
// License. See LICENSE in the project root for license information.

#pragma once

#include <SDL.h>

#include "sdl/SDL_Image_Utilities.hpp"
#include "sdl/SDL_Utilities.hpp"

#include "GameObject.hpp"

namespace Handcrank
{

class ImageRenderObject : public GameObject
{
  private:
    SDL_Texture *texture;

    SDL_Rect *srcRect;

    SDL_FPoint *centerPoint;

    SDL_RendererFlip flip = SDL_FLIP_NONE;

  public:
    explicit ImageRenderObject() : GameObject() {}
    explicit ImageRenderObject(SDL_FRect *_rect) : GameObject(_rect) {}

    ~ImageRenderObject() { SDL_DestroyTexture(texture); }

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

        SDL_QueryTexture(texture, nullptr, nullptr, &textureWidth,
                         &textureHeight);

        rect->w = textureWidth;
        rect->h = textureHeight;
    }

    void SetSrcRect(SDL_Rect *_srcRect) { srcRect = _srcRect; }

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

    void SetFlip(SDL_RendererFlip _flip) { flip = _flip; }

    /**
     * Render image to the scene.
     */
    void Render(SDL_Renderer *renderer) override
    {
        SDL_RenderCopyExF(renderer, texture, srcRect, GetTransformedRect(), 0,
                          centerPoint, flip);

        GameObject::Render(renderer);
    }

    /**
     * Cleanup function to run after the GameObject is unloaded.
     */
    void Clean() override { SDL_DestroyTexture(texture); }
};

} // namespace Handcrank
