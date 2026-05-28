#include "../include/Base/BaseConfiguration.hpp"

// Protected

void BaseConfiguration::setIsValid(const bool isValid)
{
    _isValid = isValid;
}

//Public

BaseConfiguration::BaseConfiguration(const std::string &filepath)
    : _filepath(filepath)
    , _isValid(true)
{
    if (!std::filesystem::exists(_filepath))
    {

    }
}

std::string BaseConfiguration::getFilePath() const
{
    return _filepath;
}


bool BaseConfiguration::isValid() const
{
    return _isValid;
}