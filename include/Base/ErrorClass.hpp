#pragma once
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
public:
    /**
     * @brief Enumeration of all defined application error codes.
     *
     * Using an enum class provides strong type safety.
     */
    enum class Errors : std::uint8_t
    {
        // Success/No Error
        DRACO2D_NO_ERROR                        = std::uint8_t(0),

        // SDL Error Codes
        DRACO2D_SDL_INIT_FAILED_ERROR           = DRACO2D_NO_ERROR + std::uint8_t(1),
        DRACO2D_SDL_CREATE_WINDOW_FAIL_ERROR    = DRACO2D_NO_ERROR + std::uint8_t(2),
        DRACO2D_SDL_CREATE_RENDER_FAIL_ERROR    = DRACO2D_NO_ERROR + std::uint8_t(3),

        // Configuration Error Codes
        DRACO2D_CONFIG_BASE_ERROR               = 20,
        DRACO2D_CONFIG_MISSING_FILE             = DRACO2D_CONFIG_BASE_ERROR + std::uint8_t(1),
        DRACO2D_CONFIG_BAD_PARAMETERS           = DRACO2D_CONFIG_BASE_ERROR + std::uint8_t(2),
        DRACO2D_CONFIG_MISSING_PARAMETERS       = DRACO2D_CONFIG_BASE_ERROR + std::uint8_t(3),

        // Application Logic Error Codes
        DRACO2D_APPLICATION_BASE_ERROR          = 40,
        DRACO2D_CANNOT_INITIALIZE_APPLICATION   = DRACO2D_APPLICATION_BASE_ERROR + std::uint8_t(1)
    };

private:

    /**
     * @brief Stores the most recently encountered error message.
     */
    std::string _lastErrorMessage;

    /**
     * @brief Stores the most recently encountered error.
     */
    Errors _error;

public:

    /**
     * @brief Default constructor. Initializes the error state to "No Error".
     */
    ErrorClass()
        : _error(Errors::DRACO2D_NO_ERROR)
    {}

    /**
     * @brief Virtual destructor. Ensures proper cleanup when derived classes are deleted.
     */
    virtual ~ErrorClass() = default;

    /**
     * @brief Sets the last encountered error and relative error messages.
     *
     * @param error The standard ErrorClass::Errors type error
     */
    void setLastError(const Errors error);

    /**
     * @brief Sets the last custom encountered error message string.
     *
     * @param errorMessage The descriptive message associated with the error.
     */
    void setLastCustomErrorMessage(const std::string& errorMessage)
    {
        _lastErrorMessage = errorMessage;
    }

    /**
     * @brief Retrieves the last error message that was set.
     *
     * @return The stored error message string.
     */
    std::string getLastErrorMessage() const
    {
        return _lastErrorMessage;
    }

    /**
     * @brief Retrieves the last ErrorClass::Errors error that was set.
     *
     * @return The stored ErrorClass::Errors error.
     */
    ErrorClass::Errors getLastError() const
    {
        return _error;
    }

    /**
     * @brief Converts an error enum code into a descriptive, human-readable string.
     *
     * @param error The error code to describe.
     * @return A string containing the description of the error.
     */
    std::string ErrorDescription(const Errors& error) const;
};

#endif  // !DRACO2D_BASE_ERRORCLASS_H
