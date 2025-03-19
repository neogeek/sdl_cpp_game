// Copyright (c) Scott Doxey. All Rights Reserved. Licensed under the MIT
// License. See LICENSE in the project root for license information.

#pragma once

#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

#include "Handcrank.hpp"

namespace Handcrank
{

/**
 * Load font from a path.
 *
 * @param path File path to font file.
 * @param ptSize The size of the font.
 *
 * @deprecated DEVELOPMENT USE ONLY! Use SDL_LoadFontRW to load
 * fonts in a release build.
 */
inline auto SDL_LoadFont(const char *path, const int ptSize = 24)
    -> std::shared_ptr<TTF_Font>
{
    if (TTF_WasInit() == 0)
    {
        TTF_Init();
    }

    auto *font = TTF_OpenFont(path, ptSize);

    if (font == nullptr)
    {
        return nullptr;
    }

    return std::shared_ptr<TTF_Font>(font, TTF_CloseFont);
}

/**
 * Load font from a read-only buffer.
 *
 * @param mem A pointer to a read-only buffer.
 * @param size The buffer size, in bytes.
 * @param ptSize The size of the font.
 */
inline auto SDL_LoadFontRW(const void *mem, const int size,
                           const int ptSize = 24) -> std::shared_ptr<TTF_Font>
{
    if (TTF_WasInit() == 0)
    {
        TTF_Init();
    }

    auto *rw = SDL_RWFromConstMem(mem, size);

    if (rw == nullptr)
    {
        return nullptr;
    }

    auto *font = TTF_OpenFontRW(rw, 1, ptSize);

    if (font == nullptr)
    {
        SDL_RWclose(rw);
        return nullptr;
    }

    return std::shared_ptr<TTF_Font>(font, TTF_CloseFont);
}

class TextRenderObject : public RenderObject
{
  protected:
    std::shared_ptr<TTF_Font> font;

    SDL_Color color{255, 255, 255, 255};

    std::string text;

    std::shared_ptr<SDL_Surface> textSurface;

    std::shared_ptr<SDL_Texture> textTexture;

  public:
    explicit TextRenderObject()
    {
        if (TTF_WasInit() == 0)
        {
            TTF_Init();
        }
    }
    explicit TextRenderObject(const SDL_FRect _rect) { SetRect(_rect); }

    ~TextRenderObject() = default;

    /**
     * Set text font.
     *
     * @param font Font value to set.
     */
    void SetFont(std::shared_ptr<TTF_Font> font) { this->font = font; }

    /**
     * Load font from a path.
     *
     * @param path File path to font file.
     * @param ptSize The size of the font.
     *
     * @deprecated DEVELOPMENT USE ONLY! Use SDL_LoadFontRW to load
     * fonts in a release build.
     */
    void LoadFont(const char *path, const int ptSize = 24)
    {
        font = SDL_LoadFont(path, ptSize);
    }

    /**
     * Load font from a read-only buffer.
     *
     * @param mem A pointer to a read-only buffer.
     * @param size The buffer size, in bytes.
     * @param ptSize The size of the font.
     */
    void LoadFontRW(const void *mem, const int size, const int ptSize = 24)
    {
        font = SDL_LoadFontRW(mem, size, ptSize);
    }

    /**
     * Set text color.
     *
     * @param color Color value to set.
     */
    void SetColor(const SDL_Color color) { this->color = color; }

    /**
     * Set text content.
     *
     * @param text Text value to set.
     */
    void SetText(std::string text)
    {
        if (font == nullptr)
        {
            std::cerr << "ERROR! Missing font reference.\n";

            return;
        }

        this->text = std::move(text);

        textSurface.reset();
        textTexture.reset();

        textSurface = std::shared_ptr<SDL_Surface>(
            TTF_RenderText_Blended(font.get(), this->text.c_str(), color),
            SDL_FreeSurface);

        if (!textSurface)
        {
            std::cerr << "ERROR! Failed to generate text surface.\n";

            return;
        }

        rect->w = textSurface->w;
        rect->h = textSurface->h;

        textTexture = nullptr;
    }

    /**
     * Set text content.
     *
     * @param text Text value to set.
     */
    void SetWrappedText(std::string text)
    {
        if (font == nullptr)
        {
            std::cerr << "ERROR! Missing font reference.\n";

            return;
        }

        this->text = std::move(text);

        textSurface.reset();
        textTexture.reset();

        textSurface = std::shared_ptr<SDL_Surface>(
            TTF_RenderText_Blended_Wrapped(font.get(), this->text.c_str(),
                                           color, rect->w),
            SDL_FreeSurface);

        if (!textSurface)
        {
            std::cerr << "ERROR! Failed to generate text surface.\n";

            return;
        }

        rect->w = textSurface->w;
        rect->h = textSurface->h;

        textTexture = nullptr;
    }

    auto GetText() -> std::string { return text; }

    /**
     * Render text to the scene.
     *
     * @param renderer A structure representing rendering state.
     */
    void Render(std::shared_ptr<SDL_Renderer> renderer) override
    {
        if (!CanRender())
        {
            return;
        }

        if (textTexture == nullptr)
        {
            textTexture = std::shared_ptr<SDL_Texture>(
                SDL_CreateTextureFromSurface(renderer.get(), textSurface.get()),
                SDL_DestroyTexture);
        }

        auto transformedRect = GetTransformedRect();

        SDL_RenderCopyF(renderer.get(), textTexture.get(), nullptr,
                        &transformedRect);

        RenderObject::Render(renderer);
    }
};

} // namespace Handcrank
