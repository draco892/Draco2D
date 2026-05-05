#include "../include/Window.hpp"

#include <SDL3/SDL_init.h>

Window::~Window()
{
    SDL_DestroyWindow(_window);
    SDL_Quit();
}
