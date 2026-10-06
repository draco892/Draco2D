#pragma once
#include <SDL3/SDL.h>

struct UpdateContext
{
    float seconds;
    float width;
    float height;
    const bool* keyboard;
};

class BaseObject
{
public:
    virtual ~BaseObject() = default;
    virtual void update(const UpdateContext& context) = 0;
    virtual void render(SDL_Renderer* renderer) const = 0;
};
