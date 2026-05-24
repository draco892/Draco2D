#include "../include/Base/ErrorClass.hpp"

void ErrorClass::setLastError(const Errors error)
{
    _error = error;
    _lastErrorMessage = ErrorDescription(error);
}

std::string ErrorClass::ErrorDescription(const Errors& error) const
{
    switch (error)
    {
        // Success/No Error
    case Errors::DRACO2D_NO_ERROR:
        return std::string("No Error");

        // SDL Error Codes
    case Errors::DRACO2D_SDL_INIT_FAILED_ERROR:
        return std::string("SDL_Init failed");

    case Errors::DRACO2D_SDL_CREATE_WINDOW_FAIL_ERROR:
        return std::string("The SDL window could not be created");

    case Errors::DRACO2D_SDL_CREATE_RENDER_FAIL_ERROR:
        return std::string("The SDL renderer could not be created");

        // Configuration Error Codes
    case Errors::DRACO2D_FILE_MISSING:
        return std::string("File Missing.");

    case Errors::DRACO2D_CONFIG_BAD_PARAMETERS:
        return std::string("Invalid configuration parameters.");

    case Errors::DRACO2D_CONFIG_MISSING_PARAMETERS:
        return std::string("Missing configuration parameters.");

        // Application Logic Error Codes
    case Errors::DRACO2D_CANNOT_INITIALIZE_APPLICATION:
        return std::string("Failed to initialize the application.");

    default:
        return std::string("UNKNOWN ERROR CODE");
    }
}