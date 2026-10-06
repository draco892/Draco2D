#include "Application/Application.hpp"
#include "Objects/Rectangle.hpp"
#include "Objects/Square.hpp"
#include "Objects/Triangle.hpp"
#include <algorithm>
#include <iostream>

Application::Application(const EngineConfig& settings) : _settings(settings)
{
    try {
        _running = Initialize();
    } catch (...) {
        Cleanup();
        throw;
    }
    if (!_running) {
        std::cerr << getLastErrorMessage() << ": " << SDL_GetError() << '\n';
        Cleanup();
    }
}

Application::~Application() { Cleanup(); }

bool Application::Initialize()
{
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        setLastError(Errors::DRACO2D_SDL_INIT_FAILED_ERROR);
        return false;
    }
    _sdlInitialized = true;
    const auto& w = _settings.window;
    _window = std::make_unique<Window>(w.title, w.width, w.height, w.flags);
    if (!_window->getWindow()) {
        setLastError(Errors::DRACO2D_SDL_CREATE_WINDOW_FAIL_ERROR);
        return false;
    }
    _renderer = std::make_unique<Renderer2D>(_window->getWindow());
    if (!_renderer->getRenderer()) {
        setLastError(Errors::DRACO2D_SDL_CREATE_RENDER_FAIL_ERROR);
        return false;
    }
    auto* renderer = _renderer->getRenderer();
    if (!SDL_SetRenderVSync(renderer, _settings.graphics.vsync ? 1 : 0))
        std::cerr << "Requested VSync is unavailable; using max_fps: " << SDL_GetError() << '\n';
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    _objects.emplace_back(std::make_unique<Triangle>(_settings.triangle, _settings.input));
    _objects.emplace_back(std::make_unique<Square>(_settings.square));
    _objects.emplace_back(std::make_unique<Rectangle>(_settings.rectangle));
    return true;
}

void Application::Cleanup()
{
    _running = false;
    _objects.clear();
    _renderer.reset();
    _window.reset();
    if (_sdlInitialized) { SDL_Quit(); _sdlInitialized = false; }
}

int Application::run()
{
    Uint64 previous = SDL_GetTicksNS();
    const Uint64 frameDuration = 1000000000ULL / _settings.application.maxFps;
    while (_running) {
        const Uint64 start = SDL_GetTicksNS();
        // Avoid large jumps after a pause or while dragging/resizing the window.
        const float seconds = std::min(static_cast<float>(start - previous) / 1.0e9f, 0.05f);
        previous = start;
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT ||
                (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == _settings.input.quit))
                _running = false;
        }
        if (!_running) break;
        auto* renderer = _renderer->getRenderer();
        int width = 0, height = 0;
        if (!SDL_GetRenderOutputSize(renderer, &width, &height)) {
            setLastError(Errors::DRACO2D_CANNOT_INITIALIZE_APPLICATION);
            std::cerr << "Cannot determine render dimensions: " << SDL_GetError() << '\n';
            break;
        }
        const UpdateContext context{seconds, static_cast<float>(width), static_cast<float>(height),
                                    SDL_GetKeyboardState(nullptr)};
        for (const auto& object : _objects) object->update(context);
        const auto& color = _settings.graphics.background;
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderClear(renderer);
        for (const auto& object : _objects) object->render(renderer);
        SDL_RenderPresent(renderer);
        const Uint64 elapsed = SDL_GetTicksNS() - start;
        if (elapsed < frameDuration) SDL_DelayNS(frameDuration - elapsed);
    }
    return static_cast<int>(getLastError());
}
