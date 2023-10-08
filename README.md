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

### Native

Using CMake

```bash
cmake .
make
```

or using g++

```bash
./bin/build.sh
```

### WebGL

```bash
./bin/build_webgl.sh
```

### macOS

```bash
cmake . -G Xcode
```

## Format

```bash
clang-format -i src/*.cpp includes/**/*.h
```
