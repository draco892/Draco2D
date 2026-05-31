#pragma once
#ifndef DRACO2D_CONFIG_WINDOW_H
#define DRACO2D_CONFIG_WINDOW_H

#include <string>

#include "../Base/BaseConfiguration.hpp"

/**
     * @brief Internal structure to hold window configuration data.
     */


class ConfigWindow : public BaseConfiguration
{
public:
    struct WindowSettings
    {
        std::string title;
        int width;
        int height;
        std::string flags;
    };

    /**
     * @brief Explicit window configuration class costructor.
     *
     * @param filepath The window configuration filePath.
     */
    explicit ConfigWindow(const std::string &filepath);

    /**
     * @brief Attempts to load and parse configuration settings from a JSON file.
     *
     * @return ErrorClass::ErrorsDRACO2D_NO_ERROR if loading and parsing were successful, the respective error otherwise.
     */
    virtual ErrorClass::Errors load() final;

    WindowSettings GetWindowSettings() const;

private:
    WindowSettings _ws;
};

#endif  // !DRACO2D_CONFIG_WINDOW_H