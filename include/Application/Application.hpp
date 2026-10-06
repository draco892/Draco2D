#pragma once

#include "Configuration/ConfigManager.hpp"
#include "Window/Window.hpp"
#include "Render/Renderer2D.hpp"
#include "Base/BaseObject.hpp"
#include <memory>
#include <vector>

class Application : public ErrorClass
{
public:
    explicit Application(const EngineConfig& settings);
    ~Application();
    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;
    int run();

private:
    bool Initialize();
    void Cleanup();
    EngineConfig _settings;
    std::unique_ptr<Window> _window;
    std::unique_ptr<Renderer2D> _renderer;
    std::vector<std::unique_ptr<BaseObject>> _objects;
    bool _sdlInitialized = false;
    bool _running = false;
};
