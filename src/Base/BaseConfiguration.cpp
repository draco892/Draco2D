#include "../include/Base/BaseConfiguration.hpp"

#include <filesystem>

BaseConfiguration::BaseConfiguration(const std::filesystem::path &filepath)
    : BaseFile(filepath, BaseFile::FileAccessMode::READ)
    , _jsonP(nlohmann::json::parse(*BaseFile::GetReadFile()))
{}


const nlohmann::json* BaseConfiguration::GetParsedJson() const
{
    return &_jsonP;
}