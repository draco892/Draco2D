#pragma once
#ifndef DRACO2D_BASE_BASEOBJECT_H
#define DRACO2D_BASE_BASEOBJECT_H

#include <SDL3/SDL.h>

class BaseObject
{
public:
    /**
     * @brief Virtual destructor to allow proper cleanup of derived objects.
     */
    virtual ~BaseObject() = default;

    /**
     * @brief Pure virtual function for rendering the object.
     *
     * Must be implemented by derived classes.
     *
     * @param renderer The SDL_Renderer to render onto.
     */
    virtual void render(SDL_Renderer* renderer) const = 0;
};

#endif  // !DRACO2D_BASE_BASEOBJECT_H
