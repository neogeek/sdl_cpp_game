#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include <GameObject.h>

class TextRenderObject : public GameObject
{

private:
    TTF_Font *font;

    SDL_Color color;

    const char *text;

public:
    TextRenderObject(SDL_Renderer *_renderer);
    TextRenderObject(SDL_Renderer *_renderer, SDL_Rect *_rect);

    void SetFont(TTF_Font *_font);

    void SetColor(SDL_Color _color);

    void SetText(const char *text);

    void Render() override;

    void Clean() override;
};
