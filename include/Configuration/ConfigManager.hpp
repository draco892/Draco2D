#pragma once
#ifndef DRACO2D_CONFIGMANAGER_H
#define DRACO2D_CONFIGMANAGER_H

#include "Base/ErrorClass.hpp"
#include "../Application/ConfigApplication.hpp"
#include "../Render/ConfigRenderer2D.hpp"
#include "../Window/ConfigWindow.hpp"

#include <string>

class ConfigManager : public ErrorClass
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

    /**
     * @brief Internal structure to hold window graphics data.
     */
    struct GraphicsConfig {
        bool vsync;
        unsigned char default_color_r;
        unsigned char default_color_g;
        unsigned char default_color_b;
    };

    /**
     * @brief Internal structure to hold Draco2D general configuration data.
     */
    struct Draco2DConfig {
        WindowSettings window;
        GraphicsConfig graphics;
    };


    /**
     * @brief Stores the loaded window settings.
     */
    WindowSettings _window;

    /**
     * @brief Json configuration filepath
     */
    const std::string _filepath;

    /**
     * @brief Json configuration filepath
     */
    bool _isValid;

public:
    /**
     * @brief Default constructor. Initializes settings to default values.
     */
    explicit ConfigManager(const std::string &filepath );

    /**
     * @brief Attempts to load and parse configuration settings from a JSON file.
     *
     * @return True if loading and parsing were successful, false otherwise.
     */
    bool load();

    /**
     * @brief Retrieves the currently loaded window settings.
     * @return A const reference to the WindowSettings struct.
     */
    const WindowSettings& getWindowSettings() const
    {
        return _window;
    }

    /**
     * @brief Retrieves the currently isValid value
     * @return isValid bool value
     */
    bool isValid() const
    {
        return _isValid;
    }
};

#endif // !DRACO2D_CONFIGMANAGER_H
