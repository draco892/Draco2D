#ifndef DRACO2D_APPLICATION_H
#define DRACO2D_APPLICATION_H

#include <SDL3/SDL.h>
#include <string>
#include <vector>
#include <memory>

#include "Window.hpp"
#include "Renderer2D.hpp"
#include "Base/BaseObject.hpp"
#include "Base/ErrorClass.hpp"

/**
 * @brief Main application class for managing the game loop and resources.
 */
class Application : public ErrorClass
{
    /**
     * @brief Window instance used by the application.
     */
    Window _window;
    
    /**
     * @brief Renderer instance used for rendering 2D graphics.
     */
    Renderer2D _renderer;
    
    /**
     * @brief Event structure to handle SDL events.
     */
    SDL_Event _event;
    
    /**
     * @brief Flag indicating whether the application is currently running.
     */
    bool _running;

    /**
     * @brief Collection of drawable objects
     */
    std::vector<std::unique_ptr<BaseObject>> _objects;

public:
    
    /**
     * @brief Constructs a new Application instance.
     *
     * Initializes an SDL window and renderer with the specified parameters.
     *
     * @param title Title of the window.
     * @param w Width of the window in pixels.
     * @param h Height of the window in pixels.
     * @param flags Additional SDL window flags (e.g., SDL_WINDOW_RESIZABLE).
     */
    Application(const std::string &title = std::string("Draco2D"),
                const int w = 1280,
                const int h = 720,
                const SDL_WindowFlags flags = SDL_WINDOW_RESIZABLE);
    
    /**
     * @brief Destructor for the Application class.
     *
     * Cleans up all allocated resources and quits SDL.
     */
    ~Application();
    
    /**
     * @brief Runs the main application loop.
     *
     * Handles events and renders the game frame by frame.
     *
     * @return Integer representing the exit status of the application.
     */
    int run();
    
private:
    /**
     * @brief Initializes SDL and creates necessary resources.
     *
     * Initializes SDL, creates a window, and a renderer. Returns true on success, false otherwise.
     *
     * @return True if initialization is successful, false otherwise.
     */
    bool Initialize();
    
    /**
     * @brief Cleans up all allocated resources.
     *
     * Destroys the renderer and window, and quits SDL.
     */
    void Cleanup();

    /**
     * @brief Renders all drawable objects in the application.
     *
     * Iterates through each object and calls its render method.
     *
     * @param renderer The SDL_Renderer to render onto.
     */
    void Render(SDL_Renderer* renderer);
};

#endif  // !DRACO2D_APPLICATION_H
