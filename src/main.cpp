#include <iostream>
#include "../include/Application.hpp"
#include "../include/Base/ErrorClass.hpp"

int main()
{
    // Amo il mio gechino <3

    // Create the application object
    Application app("Draco2D", 1280, 720, SDL_WINDOW_RESIZABLE);

    // Check if the application successfully initialized
    int res(static_cast<int>(ErrorClass::Errors::DRACO2D_NO_ERROR));
    if ((res = app.run()) != static_cast<int>(ErrorClass::Errors::DRACO2D_NO_ERROR))
    {   // Assuming run() returns false on failure
        std::cerr << "Application failed to run." << '\n';
    }

    return res;
}
