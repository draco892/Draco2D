#include "../include/Application.hpp"
#include "../include/Base/ErrorClass.hpp"

#include "../include/Objects/Rectangle.hpp"
#include "../include/Objects/Square.hpp"
#include "../include/Objects/Triangle.hpp"

#include <iostream>

Application::Application(const std::string &title,
                         const int w,
                         const int h,
                         const SDL_WindowFlags flags)
: _window(title, w, h, flags)
, _renderer(_window.getWindow())
, _running(true)
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        std::cerr << ErrorDescription(Errors::DRACO2D_SDL_INIT_FAILED_ERROR)
                  << ": " << SDL_GetError() << std::endl;
        _running = false; // Signal failure
        return;
    }

    if (!Initialize())
    {
        std::cerr << ErrorDescription(Errors::DRACO2D_CANNOT_INIZIALIZE_APPLICATION)
                  << std::endl;
        Cleanup();
        _running = false;
    }
}

Application::~Application()
{
    Cleanup();
}

bool Application::Initialize()
{
    // Init SDL check
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        std::cerr << ErrorDescription(Errors::DRACO2D_SDL_INIT_FAILED_ERROR)
                  <<": " << SDL_GetError() << '\n';
        return false;
    }
    
    // Check if window was created successfully
    if (!_window.getWindow())
    {
        std::cerr << ErrorDescription(Errors::DRACO2D_SDL_CREATE_WINDOW_FAIL_ERROR)
                  <<": " << SDL_GetError() << '\n';
        return false;
    }
    
    // Check if renderer was created successfully
    if (!_renderer.getRenderer())
    {
        std::cerr << ErrorDescription(Errors::DRACO2D_SDL_CREATE_RENDER_FAIL_ERROR)
                  << ": " << SDL_GetError() << '\n';
        return false;
    }

    _objects.emplace_back(std::make_unique<Triangle>());
    _objects.emplace_back(std::make_unique<Square>());
    _objects.emplace_back(std::make_unique<Rectangle>());
    
    return true;
}

void Application::Cleanup()
{
    // 1. Destroy resources owned by the application
    SDL_DestroyRenderer(_renderer.getRenderer());
    SDL_DestroyWindow(_window.getWindow());

    // 2. Quit SDL only once, here.
    SDL_Quit();
}

// Renders all drawable objects
void Application::Render(SDL_Renderer* renderer)
{
    for (const auto& obj : _objects) {
        obj->render(renderer); // Call render method of each object
    }
}

int Application::run()
{
    while (_running) {
        while (SDL_PollEvent(&_event)) {
            if (_event.type == SDL_EventType::SDL_EVENT_QUIT)
            {
                _running = false;
            }
        }

        // Rendering logic
        SDL_SetRenderDrawColor(_renderer.getRenderer(), 18, 18, 24, 255);
        SDL_RenderClear(_renderer.getRenderer());

        Render(_renderer.getRenderer()); // Render all objects

        SDL_RenderPresent(_renderer.getRenderer());
    }

    return static_cast<int>(ErrorClass::Errors::DRACO2D_NO_ERROR);
}
