#pragma once
#include "Configuration/ConfigManager.hpp"

// Compatibility facade for callers that only need window settings.
class ConfigWindow : public ConfigManager
{
public:
    using WindowSettings = ::WindowSettings;
    using ConfigManager::ConfigManager;
    WindowSettings GetWindowSettings() const { return getWindowSettings(); }
};
