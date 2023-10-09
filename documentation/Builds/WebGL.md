# WebGL Build

```cpp
#include <emscripten.h>

#include "Game.h"

Game game;

void main_loop()
{
    if (game.GetQuit())
    {
        emscripten_cancel_main_loop();

        return;
    }

    game.Loop();
}

int main()
{
    game.Setup();

    emscripten_set_main_loop(main_loop, 0, 1);

    game.Clean();

    return 0;
}
```
