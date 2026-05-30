#include "../include/Base/BaseConfiguration.hpp"

#include <filesystem>

BaseConfiguration::BaseConfiguration(const std::filesystem::path &filepath)
    : BaseFile(filepath, BaseFile::FileAccessMode::READ)
{}
