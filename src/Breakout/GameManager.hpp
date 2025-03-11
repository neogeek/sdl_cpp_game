#pragma once

#include "Handcrank/Handcrank.hpp"
#include "Handcrank/RectRenderObject.hpp"

#include "Ball.hpp"
#include "Paddle.hpp"

using namespace Handcrank;

class GameManager : public RenderObject
{

  private:
    std::shared_ptr<Ball> ball = std::make_shared<Ball>();
    std::shared_ptr<Paddle> paddle = std::make_shared<Paddle>();
    std::vector<std::shared_ptr<RectRenderObject>> bricks;

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

                auto brick = std::make_shared<RectRenderObject>();
                brick->SetRect((width + padding) * x + padding,
                               (height + padding) * y + padding, width, height);

                brick->SetFillColor(255, 255 - (x * colorStep),
                                    255 - (y * colorStep), 255);

                game->AddChildObject(brick);

                bricks.push_back(brick);
            }
        }

        ball->SetRect(100, 800, 25, 25);
        ball->SetFillColor(255, 255, 255, 255);

        game->AddChildObject(ball);

        paddle = std::make_shared<Paddle>();

        game->AddChildObject(paddle);
    }

    void Update(double deltaTime) override
    {
        if (!game->HasFocus())
        {
            return;
        }

        for (auto i = 0; i < bricks.size(); i += 1)
        {
            if (bricks[i]->CheckCollisionAABB(ball))
            {
                ball->ChangeDirection();

                bricks[i]->Destroy();

                std::swap(bricks[i], bricks.back());

                bricks.pop_back();

                break;
            }
        }

        if (paddle->CheckCollisionAABB(ball))
        {
            ball->ChangeDirection();
        }
    }
};
