#include "../include/Window/Window.hpp"

#include <SDL3/SDL_init.h>

Window::~Window()
{
    if (_window)
    {
        SDL_DestroyWindow(_window);
    }
}
