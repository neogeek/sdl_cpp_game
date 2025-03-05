// Copyright (c) Scott Doxey. All Rights Reserved. Licensed under the MIT
// License. See LICENSE in the project root for license information.

#pragma once

#include <SDL.h>

#include "sdl/SDL_Image_Utilities.hpp"

#include "Handcrank.hpp"

namespace Handcrank
{

class ImageRenderObject : public RenderObject
{
  private:
    SDL_Texture *texture;

    SDL_Rect *srcRect;

    SDL_FPoint *centerPoint;

    SDL_RendererFlip flip = SDL_FLIP_NONE;

  public:
    explicit ImageRenderObject() {}
    explicit ImageRenderObject(SDL_FRect *rect) : RenderObject(rect) {}

    ~ImageRenderObject() { SDL_DestroyTexture(texture); }

    /**
     * Load texture from a path.
     *
     * @param renderer A structure representing rendering state.
     * @param path File path to texture file.
     *
     * @deprecated DEVELOPMENT USE ONLY! Use LoadTextureRW to load textures in a
     * release build.
     */
    void LoadTexture(SDL_Renderer *renderer, const char *path)
    {
        texture = SDL_LoadTexture(renderer, path);

        UpdateRectSizeFromTexture();
    }

    /**
     * Load texture from a read-only buffer.
     *
     * @param renderer A structure representing rendering state.
     * @param mem A pointer to a read-only buffer.
     * @param size The buffer size, in bytes.
     */
    void LoadTextureRW(SDL_Renderer *renderer, const void *mem, const int size)
    {
        texture = SDL_LoadTextureRW(renderer, mem, size);

        UpdateRectSizeFromTexture();
    }

    void UpdateRectSizeFromTexture() const
    {
        int textureWidth;
        int textureHeight;

        SDL_QueryTexture(texture, nullptr, nullptr, &textureWidth,
                         &textureHeight);

        rect->w = textureWidth;
        rect->h = textureHeight;
    }

    void SetSrcRect(SDL_Rect *srcRect) { this->srcRect = srcRect; }

    void SetSrcRect(const int x, const int y, const int w, const int h)
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

    void SetFlip(const SDL_RendererFlip flip) { this->flip = flip; }

    /**
     * Render image to the scene.
     *
     * @param renderer A structure representing rendering state.
     */
    void Render(SDL_Renderer *renderer) override
    {
        SDL_RenderCopyExF(renderer, texture, srcRect, GetTransformedRect(), 0,
                          centerPoint, flip);

        RenderObject::Render(renderer);
    }

    /**
     * Cleanup function to run after the ImageRenderObject is unloaded.
     */
    void Clean() override { SDL_DestroyTexture(texture); }
};

} // namespace Handcrank
