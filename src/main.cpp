#include <SDL3/SDL.h>
#include <iostream>

#include "../include/errors.h"

void DestroyWindow(SDL_Window &window)
{
    SDL_DestroyWindow(&window);
    SDL_Quit();
    return;
}

void DestroyWindowAndRender(SDL_Window &window,
                            SDL_Renderer &render)
{
    SDL_DestroyRenderer(&render);
    DestroyWindow(window);
    return;
}

int main()
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << '\n';
        return DRACO2D_SDL_INIT_FAILED_ERROR;
    }
    
    // Window
    SDL_Window* window = SDL_CreateWindow("Draco2D",
                                          1280,
                                          720,
                                          SDL_WINDOW_RESIZABLE);
    if (!window)
    {
        std::cerr << "SDL_CreateWindow failed: " << SDL_GetError() << '\n';
        SDL_Quit();
        return DRACO2D_SDL_CREATE_WINDOW_FAIL_ERROR;
    }
    
    // Render
    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);
    if (!renderer)
    {
        std::cerr << "SDL_CreateRenderer failed: " << SDL_GetError() << '\n';
        DestroyWindow(*window);
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
    
    DestroyWindowAndRender(*window, *renderer);
    return DRACO2D_NO_ERROR;
}
