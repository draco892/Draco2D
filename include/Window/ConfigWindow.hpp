#pragma once
#ifndef DRACO2D_CONFIG_WINDOW_H
#define DRACO2D_CONFIG_WINDOW_H

#include <string>

#include "../Base/BaseConfiguration.hpp"

class ConfigWindow : public BaseConfiguration
{
    /**
     * @brief Internal structure to hold window configuration data.
     */
    struct WindowSettings
    {
        std::string title;
        int width;
        int height;
        std::string flags;
    };
public:

    /**
     * @brief Explicit window configuration class costructor.
     *
     * @param filepath The window configuration filePath.
     */
    explicit ConfigWindow(const std::string &filepath)
        : BaseConfiguration(filepath)
    {}

    /**
     * @brief Attempts to load and parse configuration settings from a JSON file.
     *
     * @return True if loading and parsing were successful, false otherwise.
     */
    virtual bool load() final;
};

#endif  // !DRACO2D_CONFIG_WINDOW_H