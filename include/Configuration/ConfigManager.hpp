#pragma once

#include "Base/BaseConfiguration.hpp"
#include "Application/ConfigApplication.hpp"
#include "Render/ConfigRenderer2D.hpp"
#include <SDL3/SDL.h>

struct WindowSettings
{
    std::string title = "Draco2D Engine";
    int width = 1280;
    int height = 720;
    SDL_WindowFlags flags = SDL_WINDOW_RESIZABLE;
};

struct InputSettings
{
    SDL_Scancode up = SDL_SCANCODE_UP;
    SDL_Scancode down = SDL_SCANCODE_DOWN;
    SDL_Scancode left = SDL_SCANCODE_LEFT;
    SDL_Scancode right = SDL_SCANCODE_RIGHT;
    SDL_Scancode quit = SDL_SCANCODE_ESCAPE;
};

struct TriangleSettings
{
    SDL_FRect bounds{240, 100, 800, 420};
    SDL_Color color{255, 0, 0, 255};
    float speed = 120;
};

struct RectangleSettings
{
    SDL_FRect bounds{470, 285, 300, 150};
    SDL_Color color{0, 0, 255, 255};
    float vx = 120;
    float vy = 120;
};

struct EngineConfig
{
    WindowSettings window;
    ConfigApplication application;
    ConfigRenderer2D graphics;
    InputSettings input;
    TriangleSettings triangle;
    RectangleSettings square{{540, 260, 200, 200}, {0, 255, 0, 255}, 120, 120};
    RectangleSettings rectangle;
};

class ConfigManager : public BaseConfiguration
{
public:
    explicit ConfigManager(const std::filesystem::path& filepath);
    Errors load() override;
    const EngineConfig& settings() const { return _settings; }
    const WindowSettings& getWindowSettings() const { return _settings.window; }
    bool isValid() const { return IsValid(); }

    // Missing fields keep defaults; invalid or unknown fields throw with a JSON path.
    static EngineConfig Parse(const nlohmann::json& json);

private:
    EngineConfig _settings;
};
