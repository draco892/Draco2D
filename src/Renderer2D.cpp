#include "../include/Renderer2D.hpp"

Renderer2D::~Renderer2D()
{
    SDL_DestroyRenderer(_renderer);
}
