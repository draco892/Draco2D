#ifndef DRACO2D_RENDER2D_H
#define DRACO2D_RENDER2D_H

#include <SDL3/SDL_render.h>

/**
 * @brief Small RAII-style wrapper around an SDL renderer handle.
 *
 * This class owns an SDL_Renderer pointer and provides a minimal C++
 * interface for creating and accessing a 2D rendering context.
 */
class Renderer2D
{
    /**
     * @brief Pointer to the SDL renderer owned by this wrapper.
     *
     * SDL exposes SDL_Renderer as an opaque type, so it is stored
     * and accessed through a pointer.
     */
    SDL_Renderer* _renderer;

public:
    /**
     * @brief Creates a new SDL renderer for the given window.
     *
     * This constructor forwards its arguments to SDL_CreateRenderer().
     * The caller is expected to pass a valid SDL_Window pointer.
     *
     * @param window Pointer to the SDL window where rendering will be displayed.
     * @param name Name of the rendering driver to initialize, or nullptr to let
     * SDL choose the most appropriate renderer automatically.
     */
    explicit Renderer2D(SDL_Window* window,
                        const char* name = nullptr)
        : _renderer(SDL_CreateRenderer(window, name))
    {}

    /**
     * @brief Destroys the owned SDL renderer.
     *
     * The implementation is expected to release the underlying SDL
     * renderer resource if the stored pointer is valid.
     */
    ~Renderer2D();

    /**
     * @brief Returns the raw SDL renderer handle.
     *
     * This is useful when calling lower-level SDL APIs that require
     * direct access to SDL_Renderer*.
     *
     * @return The raw SDL_Renderer pointer owned by this object.
     */
    SDL_Renderer* getRenderer() const
    {
        return _renderer;
    }
};

#endif  // !DRACO2D_RENDER2D_H
