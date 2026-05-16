#ifndef DRACO2D_CONFIGMANAGER_H
#define DRACO2D_CONFIGMANAGER_H

#include <string>

class ConfigManager
{
    /**
     * @brief Internal structure to hold window configuration data.
     */
    struct WindowSettings
    {
        std::string title = "Draco2D";
        int width = 1280;
        int height = 720;
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
