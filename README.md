# SDL C++ Game

## Dependencies

```bash
brew install cmake
brew install clang-format
brew install emscripten
brew install SDL2
brew install SDL2_image
brew install SDL2_ttf
```

## Build

Using CMake

```bash
cmake .
make
```

or using g++

```bash
./bin/build.sh
```

## Format

```bash
clang-format -i src/*.cpp includes/**/*.h
```
