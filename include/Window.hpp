#ifndef DRACO2D_WINDOW_H
#define DRACO2D_WINDOW_H

#include <SDL3/SDL_video.h>
#include <string>

/**
 * @brief Small RAII-style wrapper around an SDL window handle.
 *
 * This class owns an SDL_Window pointer and provides a minimal C++
 * interface for window creation and access.
 */
class Window
{
    /**
     * @brief Pointer to the SDL window owned by this wrapper.
     *
     * SDL exposes SDL_Window as an opaque type, so it is stored and
     * passed around through a pointer.
     */
    SDL_Window* _window;

public:
    /**
     * @brief Creates a new SDL window.
     *
     * This constructor forwards the provided arguments to SDL_CreateWindow().
     * The caller is expected to have initialized SDL before creating
     * an instance of this class.
     *
     * @param title Title of the window, passed to SDL in UTF-8 form.
     * @param w Width of the window.
     * @param h Height of the window.
     * @param flags Window creation flags used by SDL_CreateWindow().
     */
    explicit Window(const std::string& title,
                    const int w,
                    const int h,
                    const SDL_WindowFlags flags)
        : _window(SDL_CreateWindow(title.c_str(), w, h, flags))
    {}

    /**
     * @brief Wraps an already existing SDL window pointer.
     *
     * Use this constructor only when ownership is clear, since this class
     * may be responsible for destroying the wrapped SDL_Window.
     *
     * @param window Pointer to an existing SDL_Window instance.
     */
    explicit Window(SDL_Window* window)
        : _window(window)
    {}

    /**
     * @brief Destroys the owned SDL window.
     *
     * The implementation is expected to release the underlying SDL resource
     * if the stored pointer is valid.
     */
    ~Window();

    /**
     * @brief Returns the raw SDL window handle.
     *
     * This is useful when calling lower-level SDL APIs that still require
     * direct access to SDL_Window*.
     *
     * @return The raw SDL_Window pointer owned by this object.
     */
    SDL_Window* getWindow() const
    {
        return _window;
    }
};

#endif  // !DRACO2D_WINDOW_H
