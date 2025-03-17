// Copyright (c) Scott Doxey. All Rights Reserved. Licensed under the MIT
// License. See LICENSE in the project root for license information.

#pragma once

#define HANDCRANK_VERSION_MAJOR 0
#define HANDCRANK_VERSION_MINOR 0
#define HANDCRANK_VERSION_PATCH 0

#include <chrono>
#include <functional>
#include <iostream>
#include <list>
#include <memory>

#include <SDL.h>
#include <SDL_ttf.h>

namespace Handcrank
{

class Game;
class RenderObject;

class Game
{
  private:
    std::shared_ptr<SDL_Window> window;
    std::shared_ptr<SDL_Renderer> renderer;

    SDL_Rect viewport{};
    SDL_FRect viewportf{};

    SDL_Color clearColor{0, 0, 0, 255};

    bool quit = false;

    SDL_Event event;

    std::chrono::steady_clock::time_point previousTime;

    double deltaTime = 0;
    double renderDeltaTime = 0;
    double fixedUpdateDeltaTime = 0;

    double frameRate = 60;

    double fps = 0;

    double targetFrameTime = 1.0 / frameRate;

    const double fixedFrameTime = 0.02;

    int width = 800;
    int height = 600;

    float dpiScaleX = 1;
    float dpiScaleY = 1;

    bool focused = false;

  public:
    std::unordered_map<SDL_Keycode, bool> keyState;
    std::unordered_map<SDL_Keycode, bool> keyPressedState;
    std::unordered_map<SDL_Keycode, bool> keyReleasedState;

    std::shared_ptr<SDL_FPoint> mousePosition = std::make_shared<SDL_FPoint>();

    std::unordered_map<Uint8, bool> mouseState;
    std::unordered_map<Uint8, bool> mousePressedState;
    std::unordered_map<Uint8, bool> mouseReleasedState;

    std::list<std::shared_ptr<RenderObject>> children;

    inline Game();
    inline ~Game();

    inline void AddChildObject(std::shared_ptr<RenderObject> child);

    template <typename T>
    inline std::vector<std::shared_ptr<T>>
    GetChildrenByType(bool nested = false);
    template <typename T>
    inline std::shared_ptr<T> GetChildByType(bool nested = false);

    inline std::shared_ptr<SDL_Window> GetWindow() const;
    inline std::shared_ptr<SDL_Renderer> GetRenderer() const;
    inline SDL_FRect GetViewport() const;

    inline bool Setup();

    inline void SetScreenSize(int _width, int _height);

    inline void SetTitle(const char *name);

    inline void SetClearColor(SDL_Color color);

    inline int GetWidth() const;
    inline int GetHeight() const;

    inline bool HasFocus() const;

    inline double GetFrameRate() const;

    inline double GetFPS() const;

    inline void SetFrameRate(double _frameRate);

    inline bool GetQuit() const;

    inline int Run();

    inline void Loop();

    inline void HandleInput();

    inline void CalculateDeltaTime();

    inline void Update();
    inline void FixedUpdate();

    inline void Render();

    inline void DestroyChildObjects();

    inline void Quit();
};

class RenderObject
{
  protected:
    std::shared_ptr<SDL_FRect> rect = std::make_shared<SDL_FRect>();

    double scale = 1;

    bool hasStarted = false;

    bool isEnabled = true;

    bool isMarkedForDestroy = false;

    bool isInputHovered = false;
    bool isInputActive = false;

    std::list<std::shared_ptr<RenderObject>> children;

    std::function<void(RenderObject *)> startFunction;

    std::function<void(RenderObject *, double)> updateFunction;

    std::function<void(RenderObject *, double)> fixedUpdateFunction;

  public:
    Game *game;

    RenderObject *parent;

    float z;

    inline RenderObject();
    explicit inline RenderObject(const SDL_FRect _rect) { SetRect(_rect); }

    inline ~RenderObject();

    inline void Enable();
    inline void Disable();
    inline const bool IsEnabled() const;

    inline void AddChildObject(std::shared_ptr<RenderObject> child);

    template <typename T>
    inline std::vector<std::shared_ptr<T>>
    GetChildrenByType(bool nested = false);
    template <typename T>
    inline std::shared_ptr<T> GetChildByType(bool nested = false);

    inline void SetStart(const std::function<void(RenderObject *)> &_func);
    inline void
    SetUpdate(const std::function<void(RenderObject *, double)> &_func);
    inline void
    SetFixedUpdate(const std::function<void(RenderObject *, double)> &_func);

    virtual inline void Start();
    virtual inline void Update(double deltaTime);
    virtual inline void FixedUpdate(double deltaTime);

    virtual inline void OnMouseOver();
    virtual inline void OnMouseOut();
    virtual inline void OnMouseDown();
    virtual inline void OnMouseUp();

    virtual inline void InternalUpdate(double deltaTime);
    virtual inline void InternalFixedUpdate(double fixedDeltaTime);

    inline std::shared_ptr<SDL_FRect> GetRect() const;
    inline void SetRect(const SDL_FRect _rect);
    inline void SetRect(float x, float y, float w, float h);
    inline void SetRect(float x, float y);

    inline double GetScale() const;
    inline void SetScale(double _scale);

    inline const SDL_FRect GetTransformedRect();

    inline bool CanRender();
    virtual inline void Render(std::shared_ptr<SDL_Renderer> renderer);

    inline bool
    CheckCollisionAABB(std::shared_ptr<RenderObject> otherRenderObject);

    inline const SDL_FRect CalculateBoundingBox();

    inline void DestroyChildObjects();

    inline bool HasBeenMarkedForDestroy() const;

    inline void Destroy();
};

Game::Game() { Setup(); }

Game::~Game()
{
    for (auto child : children)
    {
        child.reset();
    }

    children.clear();

    for (auto i = 0; i < TTF_WasInit(); i += 1)
    {
        TTF_Quit();
    }

    renderer.reset();
    window.reset();

    SDL_Quit();
};

void Game::AddChildObject(std::shared_ptr<RenderObject> child)
{
    child->parent = nullptr;

    child->game = this;

    children.push_back(child);
}

template <typename T>
std::vector<std::shared_ptr<T>> Game::GetChildrenByType(bool nested)
{
    static_assert(std::is_base_of_v<RenderObject, T>,
                  "T must be derived from RenderObject");

    std::vector<std::shared_ptr<T>> results;

    for (auto child : children)
    {
        if (auto castedChild = std::dynamic_pointer_cast<T>(child))
        {
            results.push_back(castedChild);
        }

        if (nested)
        {
            auto childResults = child->GetChildrenByType<T>(nested);

            results.insert(results.end(), childResults.begin(),
                           childResults.end());
        }
    }

    return results;
}

template <typename T> std::shared_ptr<T> Game::GetChildByType(bool nested)
{
    static_assert(std::is_base_of_v<RenderObject, T>,
                  "T must be derived from RenderObject");

    if (auto children = GetChildrenByType<T>(nested); !children.empty())
    {
        return children.front();
    }

    return nullptr;
}

std::shared_ptr<SDL_Window> Game::GetWindow() const { return window; }

std::shared_ptr<SDL_Renderer> Game::GetRenderer() const { return renderer; }

SDL_FRect Game::GetViewport() const { return viewportf; }

bool Game::Setup()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return false;
    }

    if (window != nullptr)
    {
        SDL_DestroyWindow(window.get());
    }

    window = std::shared_ptr<SDL_Window>(
        SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                         width, height,
                         SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI),
        SDL_DestroyWindow);

    if (window == nullptr)
    {
        SDL_Log("SDL_CreateWindow %s", SDL_GetError());
        return false;
    }

    if (renderer != nullptr)
    {
        SDL_DestroyRenderer(renderer.get());
    }

    renderer = std::shared_ptr<SDL_Renderer>(
        SDL_CreateRenderer(window.get(), -1,
                           SDL_RENDERER_ACCELERATED |
                               SDL_RENDERER_PRESENTVSYNC),
        SDL_DestroyRenderer);

    if (renderer == nullptr)
    {
        SDL_Log("SDL_CreateRenderer %s", SDL_GetError());
        return false;
    }

    SetScreenSize(width, height);

    return true;
}

void Game::SetScreenSize(const int _width, const int _height)
{
    SDL_SetWindowSize(window.get(), _width, _height);

    SDL_GL_GetDrawableSize(window.get(), &width, &height);

    SDL_SetWindowPosition(window.get(), SDL_WINDOWPOS_CENTERED,
                          SDL_WINDOWPOS_CENTERED);

    viewport.w = width;
    viewport.h = height;

    viewportf.w = static_cast<float>(width);
    viewportf.h = static_cast<float>(height);

    dpiScaleX = (float)width / _width;
    dpiScaleY = (float)height / _height;
}

void Game::SetTitle(const char *name)
{
    SDL_SetWindowTitle(window.get(), name);
}

void Game::SetClearColor(const SDL_Color color) { this->clearColor = color; }

int Game::GetWidth() const { return width; }

int Game::GetHeight() const { return height; }

bool Game::HasFocus() const { return focused; }

double Game::GetFrameRate() const { return frameRate; }

double Game::GetFPS() const { return fps; }

void Game::SetFrameRate(double _frameRate) { frameRate = _frameRate; }

bool Game::GetQuit() const { return quit; }

int Game::Run()
{
    while (!GetQuit())
    {
        Loop();
    }

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
        auto keyCode = event.key.keysym.sym;

        auto mouseButtonIndex = event.button.button;

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
                SDL_GL_GetDrawableSize(window.get(), &width, &height);
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

void Game::Update()
{
    for (auto iter : children)
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
        for (auto iter : children)
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
        SDL_SetRenderDrawColor(renderer.get(), clearColor.r, clearColor.g,
                               clearColor.b, clearColor.a);

        SDL_RenderClear(renderer.get());

        SDL_RenderSetViewport(renderer.get(), &viewport);

        children.sort([](const std::shared_ptr<RenderObject> a,
                         const std::shared_ptr<RenderObject> b)
                      { return a->z < b->z; });

        for (auto iter : children)
        {
            if (const auto child = iter.get(); child != nullptr)
            {
                if (child->IsEnabled())
                {
                    child->Render(renderer);
                }
            }
        }

        SDL_RenderPresent(renderer.get());

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

void Game::Quit() { quit = true; }

RenderObject::RenderObject()
{
    rect->x = 0;
    rect->y = 0;
    rect->w = 100;
    rect->h = 100;
}

RenderObject::~RenderObject()
{
    for (auto child : children)
    {
        child.reset();
    }

    children.clear();
}

void RenderObject::Enable() { isEnabled = true; }

void RenderObject::Disable() { isEnabled = false; }

const bool RenderObject::IsEnabled() const { return isEnabled; }

void RenderObject::AddChildObject(std::shared_ptr<RenderObject> child)
{
    child->parent = this;

    child->game = game;

    children.push_back(child);
}

template <typename T>
std::vector<std::shared_ptr<T>> RenderObject::GetChildrenByType(bool nested)
{
    static_assert(std::is_base_of_v<RenderObject, T>,
                  "T must be derived from RenderObject");

    std::vector<std::shared_ptr<T>> results;

    for (auto child : children)
    {
        if (auto castedChild = std::dynamic_pointer_cast<T>(child))
        {
            results.push_back(castedChild);
        }

        if (nested)
        {
            auto childResults = child->GetChildrenByType<T>(nested);

            results.insert(results.end(), childResults.begin(),
                           childResults.end());
        }
    }

    return results;
}

template <typename T>
std::shared_ptr<T> RenderObject::GetChildByType(bool nested)
{
    static_assert(std::is_base_of_v<RenderObject, T>,
                  "T must be derived from RenderObject");

    if (auto children = GetChildrenByType<T>(nested); !children.empty())
    {
        return children.front();
    }

    return nullptr;
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

    auto transformedRect = GetTransformedRect();

    if (SDL_PointInFRect(game->mousePosition.get(), &transformedRect))
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

    for (auto iter : children)
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

    for (auto iter : children)
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

std::shared_ptr<SDL_FRect> RenderObject::GetRect() const { return rect; }

void RenderObject::SetRect(const SDL_FRect _rect)
{
    rect->x = _rect.x;
    rect->y = _rect.y;
    rect->w = _rect.w;
    rect->h = _rect.h;
}

void RenderObject::SetRect(const float x, const float y, const float w,
                           const float h)
{
    rect->x = x;
    rect->y = y;
    rect->w = w;
    rect->h = h;
}

void RenderObject::SetRect(const float x, const float y)
{
    rect->x = x;
    rect->y = y;
}

double RenderObject::GetScale() const { return scale; }

void RenderObject::SetScale(double _scale) { scale = _scale; }

const SDL_FRect RenderObject::GetTransformedRect()
{
    SDL_FRect transformedRect = {rect->x, rect->y, rect->w, rect->h};

    transformedRect.w *= scale;
    transformedRect.h *= scale;

    if (parent != nullptr)
    {
        transformedRect.x += parent->GetRect()->x;
        transformedRect.y += parent->GetRect()->y;

        transformedRect.w *= parent->scale;
        transformedRect.h *= parent->scale;
    }

    return transformedRect;
}

bool RenderObject::CanRender()
{
    auto boundingBox = CalculateBoundingBox();

    auto viewport = game->GetViewport();

    return SDL_HasIntersectionF(&boundingBox, &viewport);
}

void RenderObject::Render(std::shared_ptr<SDL_Renderer> renderer)
{
    if (!CanRender())
    {
        return;
    }

    children.sort([](const std::shared_ptr<RenderObject> a,
                     const std::shared_ptr<RenderObject> b)
                  { return a->z < b->z; });

    for (auto iter : children)
    {
        if (const auto child = iter.get(); child != nullptr)
        {
            if (child->IsEnabled())
            {
                child->Render(renderer);
            }
        }
    }
}

[[nodiscard]] const SDL_FRect RenderObject::CalculateBoundingBox()
{
    auto boundingBox = GetTransformedRect();

    for (auto iter : children)
    {
        if (const auto child = iter.get(); child != nullptr)
        {
            const auto childBoundingBox = child->CalculateBoundingBox();

            boundingBox.x = fminf(boundingBox.x, childBoundingBox.x);
            boundingBox.y = fminf(boundingBox.y, childBoundingBox.y);
            boundingBox.w = fmaxf(boundingBox.w, childBoundingBox.w);
            boundingBox.h = fmaxf(boundingBox.h, childBoundingBox.h);
        }
    }

    return boundingBox;
}

bool RenderObject::CheckCollisionAABB(
    std::shared_ptr<RenderObject> otherRenderObject)
{
    return SDL_HasIntersectionF(rect.get(), otherRenderObject->GetRect().get());
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

[[nodiscard]] bool RenderObject::HasBeenMarkedForDestroy() const
{
    return isMarkedForDestroy;
}

void RenderObject::Destroy() { isMarkedForDestroy = true; }

} // namespace Handcrank
