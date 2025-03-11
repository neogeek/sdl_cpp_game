#pragma once

#include "Handcrank/Handcrank.hpp"

using namespace Handcrank;

class Dungeon : public RenderObject
{
  private:
    SDL_BlendMode blendMode = SDL_BLENDMODE_BLEND;

  public:
    std::vector<std::vector<int>> grid;

    explicit Dungeon() { Generate(20, 20); }
    explicit Dungeon(const SDL_FRect _rect) : RenderObject(_rect) {}

    ~Dungeon() = default;

    void Generate(int width, int height)
    {
        grid.resize(width);

        for (int x = 0; x < width; x += 1)
        {
            grid[x].resize(height);

            for (int y = 0; y < height; y += 1)
            {
                if (x == 0 || x == width - 1 || y == 0 || y == height - 1)
                {
                    grid[x][y] = 1;
                }
                else
                {
                    grid[x][y] = 0;
                }
            }
        }
    };

    void Render(std::shared_ptr<SDL_Renderer> renderer) override
    {
        SDL_SetRenderDrawBlendMode(renderer.get(), blendMode);

        auto fillColor = new SDL_Color{255, 255, 255, 255};

        const int width = 20;
        const int height = 20;

        SDL_SetRenderDrawColor(renderer.get(), fillColor->r, fillColor->g,
                               fillColor->b, fillColor->a);

        for (int x = 0; x < size(grid); x += 1)
        {
            for (int y = 0; y < size(grid[x]); y += 1)
            {
                if (grid[x][y] == 1)
                {
                    SDL_Rect rect = {x * width, y * width, width, height};

                    SDL_RenderFillRect(renderer.get(), &rect);
                }
            }
        }
    }
};
