#include <iostream>
#include "../include/Application.hpp"
#include "../include/errors.h"

int main()
{
    // Amo il mio gechino <3

    // Create the application object
    Application app("Draco2D", 1280, 720, SDL_WINDOW_RESIZABLE);

    // Check if the application successfully initialized
    int res(DRACO2D_NO_ERROR);
    if ((res = app.run()) != DRACO2D_NO_ERROR)
    {   // Assuming run() returns false on failure
        std::cerr << "Application failed to run." << '\n';
    }

    return res;
}
