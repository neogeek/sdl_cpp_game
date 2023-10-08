# Documentation

## Game

```cpp
#include "Game.h"

Game game;

int main()
{
    return game.Run();
}
```

## RectRenderObject

```cpp
#include "RectRenderObject.h"

std::unique_ptr<RectRenderObject> square(new RectRenderObject);

square->SetStart(
    [](GameObject *ref)
    {
        std::cout << "start" << std::endl;

        TextRenderObject *rectObj = dynamic_cast<TextRenderObject *>(ref);

        rectObj->GetRect()->w = 100;
        rectObj->GetRect()->h = 100;
    });

square->SetUpdate(
    [](GameObject *ref, double deltaTime)
    {
        std::cout << "update" << std::endl;

        TextRenderObject *rectObj = dynamic_cast<TextRenderObject *>(ref);

        rectObj->GetRect()->x += 1;
    });

square->SetFixedUpdate([](GameObject *ref, double deltaTime)
                        { std::cout << "fixed update" << std::endl; });

square->SetColor({255, 255, 255, 255});

game.gameObjects.push_back(std::move(square));
```
