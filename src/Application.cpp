#include "../include/Application.hpp"

#include <iostream>

Application::Application(const std::string &title,
                         const int w,
                         const int h,
                         const SDL_WindowFlags flags)
: _window(title, w, h, flags)
, _renderer(_window.getWindow())
, _running(true)
{
    if (!Initialize())
    {
        std::cerr << "Failed to initialize application." << '\n';
        Cleanup();
        exit(DRACO2D_SDL_INIT_FAILED_ERROR);
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
        std::cerr << "SDL_Init failed: " << SDL_GetError() << '\n';
        return false;
    }
    
    // Check if window was created successfully
    if (!_window.getWindow())
    {
        std::cerr << "SDL_CreateWindow failed: " << SDL_GetError() << '\n';
        return false;
    }
    
    // Check if renderer was created successfully
    if (!_renderer.getRenderer())
    {
        std::cerr << "SDL_CreateRenderer failed: " << SDL_GetError() << '\n';
        return false;
    }
    
    return true;
}

void Application::Cleanup()
{
    SDL_DestroyRenderer(_renderer.getRenderer());
    SDL_DestroyWindow(_window.getWindow());
    SDL_Quit();
}

int Application::run()
{
    while (_running) {
        while (SDL_PollEvent(&_event)) {
            if (_event.type == SDL_EVENT_QUIT) {
                _running = false;
            }
        }

        // Rendering logic
        SDL_SetRenderDrawColor(_renderer.getRenderer(), 18, 18, 24, 255);
        SDL_RenderClear(_renderer.getRenderer());
        SDL_RenderPresent(_renderer.getRenderer());
    }

    return DRACO2D_NO_ERROR;
}
