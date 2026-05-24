#include "../include/Configuration/ConfigManager.hpp"

#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>

ConfigManager::ConfigManager(const std::string &filepath)
    : _filepath(filepath)
    , _isValid(std::filesystem::exists(filepath))
{
    if (!_isValid)
    {
        //setLastError(Errors::DRACO2D_CONFIG_MISSING_FILE);
        return;
    }


}