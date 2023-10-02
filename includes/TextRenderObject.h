#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include <GameObject.h>

class TextRenderObject : public GameObject
{

private:
    TTF_Font *font;

    SDL_Color color{255, 255, 255, 255};

    const char *text;

public:
    explicit TextRenderObject(SDL_Rect *_rect);

    void SetFont(TTF_Font *_font);

    void SetColor(SDL_Color _color);

    void SetText(const char *text);

    void Render(SDL_Renderer *renderer) override;

    void Clean() override;
};
