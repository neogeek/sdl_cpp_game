// Copyright (c) Scott Doxey. All Rights Reserved. Licensed under the MIT
// License. See LICENSE in the project root for license information.

#pragma once

#define HANDCRANK_VERSION_MAJOR 0
#define HANDCRANK_VERSION_MINOR 0
#define HANDCRANK_VERSION_PATCH 0

#include <chrono>
#include <iostream>
#include <list>
#include <memory>

#include <SDL.h>
#include <SDL_ttf.h>

#include "Vector2.hpp"

#include "sdl/SDL_Utilities.hpp"

namespace Handcrank
{

class Game;
class RenderObject;

class Game
{
  private:
    SDL_Window *window;
    SDL_Renderer *renderer;

    SDL_Rect *viewport = new SDL_Rect;
    SDL_FRect *viewportf = new SDL_FRect;

    SDL_Color clearColor{0, 0, 0, 255};

    bool quit = false;

    SDL_Event event;

    std::chrono::steady_clock::time_point previousTime;

    double deltaTime = 0;
    double renderDeltaTime = 0;
    double fixedUpdateDeltaTime = 0;

    double frameRate = 60;

    double fps;

    const double targetFrameTime = 1.0 / frameRate;

    const double fixedFrameTime = 0.02;

    int width = 800;
    int height = 600;

    float dpiScaleX;
    float dpiScaleY;

    bool focused = false;

  public:
    std::unordered_map<SDL_Keycode, bool> keyState;
    std::unordered_map<SDL_Keycode, bool> keyPressedState;
    std::unordered_map<SDL_Keycode, bool> keyReleasedState;

    SDL_FPoint *mousePosition = new SDL_FPoint;

    std::unordered_map<Uint8, bool> mouseState;
    std::unordered_map<Uint8, bool> mousePressedState;
    std::unordered_map<Uint8, bool> mouseReleasedState;

    std::list<std::unique_ptr<RenderObject>> children;

    Game();

    void AddChildObject(std::unique_ptr<RenderObject> child);

    [[nodiscard]] SDL_Window *GetWindow() const;
    [[nodiscard]] SDL_Renderer *GetRenderer() const;
    [[nodiscard]] SDL_FRect *GetViewport() const;

    bool Setup();

    void SetScreenSize(int _width, int _height);

    void SetTitle(const char *name) const;

    void SetClearColor(SDL_Color color);

    [[nodiscard]] int GetWidth() const;
    [[nodiscard]] int GetHeight() const;

    [[nodiscard]] bool HasFocus() const;

    [[nodiscard]] double GetFrameRate() const;

    [[nodiscard]] double GetFPS() const;

    void SetFrameRate(double _frameRate);

    [[nodiscard]] bool GetQuit() const;

    int Run();

    void Loop();

    void HandleInput();

    void CalculateDeltaTime();

    void Update() const;
    void FixedUpdate();

    void Render();

    void DestroyChildObjects();

    void Clean();

    void Quit();
};

class RenderObject
{
  protected:
    SDL_FRect *rect = new SDL_FRect;

    double scale = 1;

    bool hasStarted = false;

    bool isEnabled = true;

    bool isMarkedForDestroy = false;

    bool isInputHovered = false;
    bool isInputActive = false;

    std::list<std::unique_ptr<RenderObject>> children;

    std::function<void(RenderObject *)> startFunction;

    std::function<void(RenderObject *, double)> updateFunction;

    std::function<void(RenderObject *, double)> fixedUpdateFunction;

  public:
    Game *game;

    RenderObject *parent;

    float z;

    RenderObject();
    explicit RenderObject(SDL_FRect *rect) : rect(rect) {}

    ~RenderObject();

    void Enable();
    void Disable();
    [[nodiscard]] const bool IsEnabled() const;

    void AddChildObject(std::unique_ptr<RenderObject> child);

    void SetStart(const std::function<void(RenderObject *)> &_func);
    void SetUpdate(const std::function<void(RenderObject *, double)> &_func);
    void
    SetFixedUpdate(const std::function<void(RenderObject *, double)> &_func);

    virtual void Start();
    virtual void Update(double deltaTime);
    virtual void FixedUpdate(double deltaTime);

    virtual void OnMouseOver();
    virtual void OnMouseOut();
    virtual void OnMouseDown();
    virtual void OnMouseUp();

    void InternalUpdate(double deltaTime);
    void InternalFixedUpdate(double fixedDeltaTime);

    [[nodiscard]] SDL_FRect *GetRect() const;
    void SetRect(SDL_FRect *_rect);
    void SetRect(float x, float y, float w, float h) const;
    void SetRect(float x, float y) const;

    [[nodiscard]] double GetScale() const;
    void SetScale(double _scale);

    [[nodiscard]] SDL_FRect *GetTransformedRect() const;

    virtual void Render(SDL_Renderer *_renderer);

    template <typename T> std::vector<T *> GetChildrenByType();
    template <typename T> T *GetChildByType();

    SDL_FRect *CalculateBoundingBox() const;

    void DestroyChildObjects();

    virtual void Clean();

    [[nodiscard]] bool HasBeenMarkedForDestroy() const;

    void Destroy();
};

Game::Game()
{
    window = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, width, height,
                              SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI);

    renderer = SDL_CreateRenderer(
        window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SetScreenSize(width, height);
}

void Game::AddChildObject(std::unique_ptr<RenderObject> child)
{
    child->parent = nullptr;

    child->game = this;

    children.push_back(std::move(child));
}

[[nodiscard]] SDL_Window *Game::GetWindow() const { return window; }

[[nodiscard]] SDL_Renderer *Game::GetRenderer() const { return renderer; }

[[nodiscard]] SDL_FRect *Game::GetViewport() const { return viewportf; }

inline bool Game::Setup()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return false;
    }

    return true;
}

void Game::SetScreenSize(const int _width, const int _height)
{
    SDL_SetWindowSize(window, _width, _height);

    SDL_GL_GetDrawableSize(window, &width, &height);

    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED,
                          SDL_WINDOWPOS_CENTERED);

    viewport->w = width;
    viewport->h = height;

    viewportf->w = static_cast<float>(width);
    viewportf->h = static_cast<float>(height);

    dpiScaleX = width / _width;
    dpiScaleY = height / _height;
}

inline void Game::SetTitle(const char *name) const
{
    SDL_SetWindowTitle(window, name);
}

void Game::SetClearColor(const SDL_Color color) { this->clearColor = color; }

[[nodiscard]] int Game::GetWidth() const { return width; }

[[nodiscard]] int Game::GetHeight() const { return height; }

[[nodiscard]] bool Game::HasFocus() const { return focused; }

[[nodiscard]] double Game::GetFrameRate() const { return frameRate; }

[[nodiscard]] double Game::GetFPS() const { return fps; }

void Game::SetFrameRate(double _frameRate) { frameRate = _frameRate; }

[[nodiscard]] bool Game::GetQuit() const { return quit; }

int Game::Run()
{
    if (!Setup())
    {
        return 1;
    }

    while (!GetQuit())
    {
        Loop();
    }

    Clean();

    return 0;
}

void Game::Loop()
{
    HandleInput();

    CalculateDeltaTime();

    Update();
    FixedUpdate();

    Render();

    DestroyChildObjects();

    SDL_Delay(1);
}

void Game::HandleInput()
{
    keyPressedState.clear();
    keyReleasedState.clear();

    mousePressedState.clear();
    mouseReleasedState.clear();

    while (SDL_PollEvent(&event) != 0)
    {
        SDL_Keycode keyCode = event.key.keysym.sym;

        Uint8 mouseButtonIndex = event.button.button;

        switch (event.type)
        {
        case SDL_QUIT:
            Quit();
            break;

        case SDL_WINDOWEVENT:
            if (event.window.event == SDL_WINDOWEVENT_RESIZED ||
                event.window.event == SDL_WINDOWEVENT_RESTORED ||
                event.window.event == SDL_WINDOWEVENT_MAXIMIZED ||
                event.window.event == SDL_WINDOWEVENT_MINIMIZED)
            {
                SDL_GL_GetDrawableSize(window, &width, &height);
            }
            else if (event.window.event == SDL_WINDOWEVENT_FOCUS_LOST)
            {
                focused = false;
            }
            else if (event.window.event == SDL_WINDOWEVENT_FOCUS_GAINED)
            {
                focused = true;
            }
            break;

        case SDL_KEYDOWN:
            keyPressedState[keyCode] = !keyState[keyCode];
            keyState[keyCode] = true;
            break;

        case SDL_KEYUP:
            keyState[keyCode] = false;
            keyPressedState[keyCode] = false;
            keyReleasedState[keyCode] = true;
            break;

        case SDL_MOUSEMOTION:
            mousePosition->x = event.motion.x * dpiScaleX;
            mousePosition->y = event.motion.y * dpiScaleY;
            break;

        case SDL_MOUSEBUTTONDOWN:
            mousePressedState[mouseButtonIndex] = !mouseState[mouseButtonIndex];
            mouseState[mouseButtonIndex] = true;
            break;

        case SDL_MOUSEBUTTONUP:
            mouseState[mouseButtonIndex] = false;
            mousePressedState[mouseButtonIndex] = false;
            mouseReleasedState[mouseButtonIndex] = true;
            break;

        default:
            break;
        }
    }
}

void Game::CalculateDeltaTime()
{
    auto currentTime = std::chrono::steady_clock::now();

    deltaTime =
        std::chrono::duration<double>(currentTime - previousTime).count();

    previousTime = currentTime;
}

inline void Game::Update() const
{
    for (auto &iter : children)
    {
        auto child = iter.get();

        if (child != nullptr)
        {
            if (child->IsEnabled())
            {
                child->InternalUpdate(deltaTime);
            }
        }
    }
}

void Game::FixedUpdate()
{
    fixedUpdateDeltaTime += deltaTime;

    if (fixedUpdateDeltaTime > fixedFrameTime)
    {
        for (auto &iter : children)
        {
            if (const auto child = iter.get(); child != nullptr)
            {
                if (child->IsEnabled())
                {
                    child->InternalFixedUpdate(fixedUpdateDeltaTime);
                }
            }
        }

        fixedUpdateDeltaTime = 0;
    }
}

void Game::Render()
{
    renderDeltaTime += deltaTime;

    if (renderDeltaTime > targetFrameTime)
    {
        SDL_SetRenderDrawColor(renderer, clearColor.r, clearColor.g,
                               clearColor.b, clearColor.a);

        SDL_RenderClear(renderer);

        SDL_RenderSetViewport(renderer, viewport);

        children.sort([](const std::unique_ptr<RenderObject> &a,
                         const std::unique_ptr<RenderObject> &b)
                      { return a->z < b->z; });

        for (auto &iter : children)
        {
            if (const auto child = iter.get(); child != nullptr)
            {
                if (child->IsEnabled())
                {
                    child->Render(renderer);
                }
            }
        }

        SDL_RenderPresent(renderer);

        fps = 1.0 / renderDeltaTime;

        renderDeltaTime = 0;
    }
}

void Game::DestroyChildObjects()
{
    for (auto iter = children.begin(); iter != children.end();)
    {
        auto child = iter->get();

        if (child != nullptr)
        {
            child->DestroyChildObjects();

            if (child->HasBeenMarkedForDestroy())
            {
                iter = children.erase(iter);
            }
            else
            {
                ++iter;
            }
        }
    }
}

void Game::Clean()
{
    for (auto &iter : children)
    {
        if (const auto child = iter.get(); child != nullptr)
        {
            child->Clean();
        }
    }

    for (int i = 0; i < TTF_WasInit(); i += 1)
    {
        TTF_Quit();
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
}

void Game::Quit() { quit = true; }

RenderObject::RenderObject()
{
    rect->x = 0;
    rect->y = 0;
    rect->w = 100;
    rect->h = 100;
}

inline RenderObject::~RenderObject() = default;

void RenderObject::Enable() { isEnabled = true; }

void RenderObject::Disable() { isEnabled = false; }

const bool RenderObject::IsEnabled() const { return isEnabled; }

void RenderObject::AddChildObject(std::unique_ptr<RenderObject> child)
{
    child->parent = this;

    child->game = game;

    children.push_back(std::move(child));
}

void RenderObject::SetStart(
    const std::function<void(RenderObject *)> &_func = nullptr)
{
    if (startFunction)
    {
        std::cerr << "WARNING! Start function has already been set. "
                     "Overriding with new function.\n";
    }

    startFunction = _func;
}

void RenderObject::SetUpdate(
    const std::function<void(RenderObject *, double)> &_func = nullptr)
{
    if (updateFunction)
    {
        std::cerr << "WARNING! Update function has already been set. "
                     "Overriding with new function.\n";
    }

    updateFunction = _func;
}

void RenderObject::SetFixedUpdate(
    const std::function<void(RenderObject *, double)> &_func = nullptr)
{
    if (fixedUpdateFunction)
    {
        std::cerr << "WARNING! Fixed update function has already been set. "
                     "Overriding with new function.\n";
    }

    fixedUpdateFunction = _func;
}

void RenderObject::Start() {}

void RenderObject::Update(double deltaTime) {}

void RenderObject::FixedUpdate(double deltaTime) {}

void RenderObject::OnMouseOver() {}

void RenderObject::OnMouseOut() {}

void RenderObject::OnMouseDown() {}

void RenderObject::OnMouseUp() {}

void RenderObject::InternalUpdate(const double deltaTime)
{
    if (!hasStarted)
    {
        Start();

        if (startFunction)
        {
            startFunction(this);
        }

        hasStarted = true;
    }

    if (SDL_PointInFRect(game->mousePosition, GetTransformedRect()))
    {
        if (game->mousePressedState[SDL_BUTTON_LEFT])
        {
            OnMouseDown();

            isInputActive = true;
        }

        if (!isInputHovered)
        {
            OnMouseOver();

            isInputHovered = true;
        }
    }
    else if (isInputHovered)
    {
        OnMouseOut();

        isInputHovered = false;
    }

    if (isInputActive && game->mouseReleasedState[SDL_BUTTON_LEFT])
    {
        OnMouseUp();

        isInputActive = false;
    }

    Update(deltaTime);

    if (updateFunction)
    {
        updateFunction(this, deltaTime);
    }

    for (auto &iter : children)
    {
        if (const auto child = iter.get(); child != nullptr)
        {
            if (child->IsEnabled())
            {
                child->InternalUpdate(deltaTime);
            }
        }
    }
}

void RenderObject::InternalFixedUpdate(const double fixedDeltaTime)
{
    FixedUpdate(fixedDeltaTime);

    if (fixedUpdateFunction)
    {
        fixedUpdateFunction(this, fixedDeltaTime);
    }

    for (auto &iter : children)
    {
        if (const auto child = iter.get(); child != nullptr)
        {
            if (child->IsEnabled())
            {
                child->InternalFixedUpdate(fixedDeltaTime);
            }
        }
    }
}

[[nodiscard]] inline SDL_FRect *RenderObject::GetRect() const { return rect; }

void RenderObject::SetRect(SDL_FRect *_rect) { rect = _rect; }

inline void RenderObject::SetRect(const float x, const float y, const float w,
                                  const float h) const
{
    rect->x = x;
    rect->y = y;
    rect->w = w;
    rect->h = h;
}

inline void RenderObject::SetRect(const float x, const float y) const
{
    rect->x = x;
    rect->y = y;
}

[[nodiscard]] double RenderObject::GetScale() const { return scale; }

void RenderObject::SetScale(double _scale) { scale = _scale; }

[[nodiscard]] SDL_FRect *RenderObject::GetTransformedRect() const
{
    SDL_FRect *transformedRect = ScaleRect(rect, scale);

    if (parent != nullptr)
    {
        transformedRect = PositionRect(transformedRect, parent->rect);

        transformedRect = ScaleRect(transformedRect, parent->scale);
    }

    return transformedRect;
}

void RenderObject::Render(SDL_Renderer *_renderer)
{
    children.sort([](const std::unique_ptr<RenderObject> &a,
                     const std::unique_ptr<RenderObject> &b)
                  { return a->z < b->z; });

    auto boundingBox = CalculateBoundingBox();

    if (!SDL_HasIntersectionF(boundingBox, game->GetViewport()))
    {
        return;
    }

    for (auto &iter : children)
    {
        if (const auto child = iter.get(); child != nullptr)
        {
            if (child->IsEnabled())
            {
                child->Render(_renderer);
            }
        }
    }
}

template <typename T> std::vector<T *> RenderObject::GetChildrenByType()
{
    static_assert(std::is_base_of_v<RenderObject, T>,
                  "T must be derived from RenderObject");

    std::vector<T *> results;

    for (auto &iter : children)
    {
        if (auto child = iter.get();
            child != nullptr && typeid(*child) == typeid(T))
        {
            auto castedChild = dynamic_cast<T *>(child);

            if (castedChild != nullptr)
            {
                results.push_back(castedChild);
            }
        }
    }

    return results;
}

template <typename T> T *RenderObject::GetChildByType()
{
    static_assert(std::is_base_of_v<RenderObject, T>,
                  "T must be derived from RenderObject");

    if (auto children = GetChildrenByType<T>(); !children.empty())
    {
        return children.front();
    }

    return nullptr;
}

SDL_FRect *RenderObject::CalculateBoundingBox() const
{
    const auto boundingBox = GetTransformedRect();

    for (auto &iter : children)
    {
        if (const auto child = iter.get(); child != nullptr)
        {
            const auto childBoundingBox = child->CalculateBoundingBox();

            boundingBox->x = fminf(boundingBox->x, childBoundingBox->x);
            boundingBox->y = fminf(boundingBox->y, childBoundingBox->y);
            boundingBox->w = fmaxf(boundingBox->w, childBoundingBox->w);
            boundingBox->h = fmaxf(boundingBox->h, childBoundingBox->h);
        }
    }

    return boundingBox;
}

void RenderObject::DestroyChildObjects()
{
    for (auto iter = children.begin(); iter != children.end();)
    {
        if (const auto child = iter->get(); child != nullptr)
        {
            child->DestroyChildObjects();

            if (child->HasBeenMarkedForDestroy())
            {
                iter = children.erase(iter);
            }
            else
            {
                ++iter;
            }
        }
    }
}

void RenderObject::Clean() {}

[[nodiscard]] bool RenderObject::HasBeenMarkedForDestroy() const
{
    return isMarkedForDestroy;
}

void RenderObject::Destroy() { isMarkedForDestroy = true; }

} // namespace Handcrank
