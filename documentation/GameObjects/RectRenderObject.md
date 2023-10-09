# RectRenderObject

````cpp

## RectRenderObject

```cpp
#include <iostream>

#include "Game.hpp"
#include "RectRenderObject.hpp"

Game game;

int main()
{
    std::unique_ptr<RectRenderObject> square(new RectRenderObject);

    square->SetStart(
        [](GameObject *ref)
        {
            std::cout << "start" << std::endl;

            RectRenderObject *rectObj = dynamic_cast<RectRenderObject *>(ref);

            rectObj->GetRect()->w = 100;
            rectObj->GetRect()->h = 100;
        });

    square->SetUpdate(
        [](GameObject *ref, double deltaTime)
        {
            std::cout << "update" << std::endl;

            RectRenderObject *rectObj = dynamic_cast<RectRenderObject *>(ref);

            rectObj->GetRect()->x += 1;
        });

    square->SetFixedUpdate([](GameObject *ref, double deltaTime)
                           { std::cout << "fixed update" << std::endl; });

    square->SetColor({255, 255, 255, 255});

    game.gameObjects.push_back(std::move(square));

    return game.Run();
}
````
