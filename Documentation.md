# Documentation

## RectRenderObject

```cpp
RectRenderObject square;

square.SetStart([](GameObject *ref)
                {
                    std::cout << "start" << std::endl;

                    ref->GetRect()->w = 100;
                    ref->GetRect()->h = 100;
                });

square.SetUpdate([](GameObject *ref, double deltaTime)
                    {
                        std::cout << "update" << std::endl;

                        ref->GetRect()->x += 1;
                    });

square.SetFixedUpdate([](GameObject *ref, double deltaTime)
                        {
                            std::cout << "fixed update" << std::endl;
                        });

square.SetColor({255, 255, 255});

game.gameObjects.push_back(&square);
```
