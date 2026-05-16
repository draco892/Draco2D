#ifndef DRACO2D_BASE_ERRORCLASS_H
#define DRACO2D_BASE_ERRORCLASS_H

#include <string>

class ErrorClass
{
    std::string _errorString;

public:

    enum class Errors : std::uint8_t
    {
        DRACO2D_NO_ERROR                        = 0,

        // SDL error Section
        DRACO2D_SDL_INIT_FAILED_ERROR           = 1,
        DRACO2D_SDL_CREATE_WINDOW_FAIL_ERROR    = 2,
        DRACO2D_SDL_CREATE_RENDER_FAIL_ERROR    = 3,

        // Config File Section
        DRACO2D_CONFIG_MISSING_FILE             = 4,
        DRACO2D_CONFIG_BAD_PARAMETERS           = 5,

        //Application Section
        DRACO2D_CANNOT_INIZIALIZE_APPLICATION   = 6
    };

    /**
     * @brief Class Costructor.
     */
    ErrorClass() = default;

    /**
     * @brief Virtual destructor to allow proper cleanup of derived objects.
     */
    virtual ~ErrorClass() = default;

    /**
     * @brief Set the last error message
     *
     * @param The last error message to set
     */
    void setLastError(const std::string errorMessage)
    {
        _errorString = errorMessage;
    }

    /**
     * @brief Get the last error message
     */
    std::string getTlastError() const
    {
        return _errorString;
    }

    std::string ErrorDescription(const Errors &error)
    {
        switch (error)
        {
        case Errors::DRACO2D_NO_ERROR:
            return std::string("No Error");

        case Errors::DRACO2D_SDL_INIT_FAILED_ERROR:
            return std::string("SDL_Init failed");

        case Errors::DRACO2D_SDL_CREATE_WINDOW_FAIL_ERROR:
            return std::string("The SDL window cannot be created");

        case Errors::DRACO2D_SDL_CREATE_RENDER_FAIL_ERROR:
            return std::string("The SDL render cannot be created");

        case Errors::DRACO2D_CONFIG_MISSING_FILE:
            return std::string("Cannot acces to the json config file");

        case Errors::DRACO2D_CONFIG_BAD_PARAMETERS:
            return std::string("Bad configuration");

        case Errors::DRACO2D_CANNOT_INIZIALIZE_APPLICATION:
            return std::string("Failed to initialize application.");

        default:
            return std::string("UNKNOW ERROR");
        }

        return std::string();
    }
};

#endif  // !DRACO2D_BASE_ERRORCLASS_H
