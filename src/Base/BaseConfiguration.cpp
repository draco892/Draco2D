#include "../include/Base/BaseConfiguration.hpp"


std::string BaseConfiguration::getFilePath() const
{
    return _filepath;
}


bool BaseConfiguration::isValid() const
{
    return _isValid;
}