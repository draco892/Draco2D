#include "../include/ConfigManager.hpp"

#include <filesystem>

ConfigManager::ConfigManager(const std::string &filepath)
    : _filepath(filepath)
    , _isValid(std::filesystem::exists(filepath))
{

}