#ifndef DRACO2D_BASE_ERRORCLASS_H
#define DRACO2D_BASE_ERRORCLASS_H

#include <string>
#include <cstdint> // Use cstdint for fixed-width integers

/**
 * @brief Base class for centralized error handling and error code description.
 *
 * This class provides a standardized way to define, store, and retrieve
 * human-readable descriptions for various application error codes.
 */
class ErrorClass
{
private:
    /**
     * @brief Stores the most recently encountered error message.
     */
    std::string _lastErrorMessage;

public:
    /**
     * @brief Enumeration of all defined application error codes.
     *
     * Using an enum class provides strong type safety.
     */
    enum class Errors : std::uint8_t
    {
        // Success/No Error
        DRACO2D_NO_ERROR                        = 0,

        // SDL Error Codes
        DRACO2D_SDL_INIT_FAILED_ERROR           = 1,
        DRACO2D_SDL_CREATE_WINDOW_FAIL_ERROR    = 2,
        DRACO2D_SDL_CREATE_RENDER_FAIL_ERROR    = 3,

        // Configuration Error Codes
        DRACO2D_CONFIG_MISSING_FILE             = 4,
        DRACO2D_CONFIG_BAD_PARAMETERS           = 5,

        // Application Logic Error Codes
        DRACO2D_CANNOT_INITIALIZE_APPLICATION   = 6
    };

    /**
     * @brief Default constructor. Initializes the error state to "No Error".
     */
    ErrorClass() = default;

    /**
     * @brief Virtual destructor. Ensures proper cleanup when derived classes are deleted.
     */
    virtual ~ErrorClass() = default;

    /**
     * @brief Sets the last encountered error message string.
     *
     * @param errorMessage The descriptive message associated with the error.
     */
    void setLastError(const std::string& errorMessage)
    {
        _lastErrorMessage = errorMessage;
    }

    /**
     * @brief Retrieves the last error message that was set.
     *
     * @return The stored error message string.
     */
    std::string getLastError() const
    {
        return _lastErrorMessage;
    }

    /**
     * @brief Converts an error enum code into a descriptive, human-readable string.
     *
     * @param error The error code to describe.
     * @return A string containing the description of the error.
     */
    std::string ErrorDescription(const Errors& error) const
    {
        switch (error)
        {
        case Errors::DRACO2D_NO_ERROR:
            return std::string("No Error");

        case Errors::DRACO2D_SDL_INIT_FAILED_ERROR:
            return std::string("SDL_Init failed");

        case Errors::DRACO2D_SDL_CREATE_WINDOW_FAIL_ERROR:
            return std::string("The SDL window could not be created");

        case Errors::DRACO2D_SDL_CREATE_RENDER_FAIL_ERROR:
            return std::string("The SDL renderer could not be created");

        case Errors::DRACO2D_CONFIG_MISSING_FILE:
            return std::string("Cannot access the JSON configuration file.");

        case Errors::DRACO2D_CONFIG_BAD_PARAMETERS:
            return std::string("Invalid or missing configuration parameters.");

        case Errors::DRACO2D_CANNOT_INITIALIZE_APPLICATION:
            return std::string("Failed to initialize the application.");

        default:
            return std::string("UNKNOWN ERROR CODE");
        }
    }
};

#endif  // !DRACO2D_BASE_ERRORCLASS_H
