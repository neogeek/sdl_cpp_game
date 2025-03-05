#pragma once

#include "Handcrank/Handcrank.hpp"
#include "Handcrank/RectRenderObject.hpp"

#include "Ball.hpp"

using namespace Handcrank;

struct Brick
{
    std::shared_ptr<RectRenderObject> rectRenderObject;

    int x;
    int y;
    int width;
    int height;

    inline bool CheckCollisionAABB(SDL_FRect *rect)
    {
        auto test = !(rect->x > x + width || rect->x + rect->w < x ||
                      rect->y > y + height || rect->y + rect->h < y);

        return test;
    }
};

class GameManager : public RenderObject
{

  private:
    std::shared_ptr<Ball> ball = std::make_shared<Ball>();
    std::vector<Brick> bricks;

  public:
    void Start() override
    {
        game->SetTitle("Breakout");

        auto width = 125;
        auto height = 50;
        auto padding = 20;
        auto colorStep = 25;

        for (auto y = 0; y < 10; y += 1)
        {
            for (auto x = 0; x < 10; x += 1)
            {
                Brick brick;

                brick.rectRenderObject = std::make_shared<RectRenderObject>();
                brick.x = (width + padding) * x + padding;
                brick.y = (height + padding) * y + padding;
                brick.width = width;
                brick.height = height;

                brick.rectRenderObject->SetRect(brick.x, brick.y, brick.width,
                                                brick.height);

                brick.rectRenderObject->SetFillColor(
                    255, 255 - (x * colorStep), 255 - (y * colorStep), 255);

                game->AddChildObject(brick.rectRenderObject);

                bricks.push_back(brick);
            }
        }

        ball->SetRect(100, 800, 25, 25);
        ball->SetFillColor(255, 255, 255, 255);

        game->AddChildObject(ball);
    }

    void Update(double deltaTime) override
    {
        if (!game->HasFocus())
        {
            return;
        }

        for (auto i = 0; i < bricks.size(); i += 1)
        {
            if (bricks[i].CheckCollisionAABB(ball->GetRect()))
            {
                ball->ChangeDirection();

                bricks[i].rectRenderObject->Destroy();

                std::swap(bricks[i], bricks.back());

                bricks.pop_back();

                break;
            }
        }
    }
    void FixedUpdate(double deltaTime) override {}
};
