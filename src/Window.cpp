#include "../include/Window.hpp"

#include <SDL3/SDL_init.h>

Window::~Window()
{
    if (!_window)
    {
        SDL_Quit();
    }
}
