#pragma once

#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

#include "sdl/SDL_TTF_Utilities.hpp"
#include "sdl/SDL_Utilities.hpp"

#include "GameObject.hpp"

class TextRenderObject : public GameObject
{
  private:
    TTF_Font *font;

    SDL_Color color{255, 255, 255, 255};

    std::string text;

    SDL_Surface *textSurface;

    SDL_Texture *textTexture;

  public:
    explicit TextRenderObject() : GameObject()
    {
        if (!TTF_WasInit())
        {
            TTF_Init();
        }
    }
    explicit TextRenderObject(SDL_Rect *_rect) : GameObject(_rect) {}

    ~TextRenderObject() { Clean(); };

    /**
     * Set text font.
     * @param font Font value to set.
     */
    void SetFont(TTF_Font *font) { this->font = font; }

    /**
     * Set text color.
     * @param color Color value to set.
     */
    void SetColor(SDL_Color color) { this->color = color; }

    /**
     * Set text content.
     * @param text Text value to set.
     */
    void SetText(std::string text)
    {
        this->text = text;

        textSurface = TTF_RenderText_Solid(font, text.c_str(), color);

        textTexture = nullptr;
    }

    std::string GetText() { return text; }

    /**
     * Render text to the scene.
     */
    void Render(SDL_Renderer *renderer) override
    {
        if (textTexture == nullptr)
        {
            textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        }

        SDL_RenderCopy(renderer, textTexture, nullptr, GetScaledRect());
    }

    /**
     * Cleanup function to run after the GameObject is unloaded.
     */
    void Clean() override
    {
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
    }
};
