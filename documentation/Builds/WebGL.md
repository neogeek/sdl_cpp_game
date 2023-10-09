# WebGL Build

## Code

```cpp
#include <emscripten.h>

#include "Game.hpp"

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

## Build Command

```bash
./bin/build_webgl.sh
```
