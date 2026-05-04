#include <SDL3/SDL.h>
#include <iostream>

#include "../include/Window.hpp"

#include "../include/errors.h"

void DestroyRender(SDL_Renderer &render)
{
    SDL_DestroyRenderer(&render);
    return;
}

int main()
{
    // Init SDL check
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << '\n';
        return DRACO2D_SDL_INIT_FAILED_ERROR;
    }
    
    // Window
    Window window("Draco2D",
                  1280,
                  720,
                  SDL_WINDOW_RESIZABLE);
    
    if (!window.getWindow())
    {
        std::cerr << "SDL_CreateWindow failed: " << SDL_GetError() << '\n';
        return DRACO2D_SDL_CREATE_WINDOW_FAIL_ERROR;
    }
    
    // Render
    SDL_Renderer* renderer = SDL_CreateRenderer(window.getWindow(), nullptr);
    if (!renderer)
    {
        std::cerr << "SDL_CreateRenderer failed: " << SDL_GetError() << '\n';
        return 1;
    }
    
    // Run
    bool running = true;
    SDL_Event event;
    
    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                running = false;
            }
        }
        SDL_SetRenderDrawColor(renderer, 18, 18, 24, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }
    
    DestroyRender(*renderer);
    return DRACO2D_NO_ERROR;
}
