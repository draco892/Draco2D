#include "Base/BaseConfiguration.hpp"

BaseConfiguration::BaseConfiguration(const std::filesystem::path& filepath)
    : BaseFile(filepath, FileAccessMode::READ)
{
    if (!IsValid()) return;
    try {
        _jsonP = nlohmann::json::parse(*GetReadFile());
    } catch (const nlohmann::json::exception& error) {
        setIsValid(false);
        setLastError(Errors::DRACO2D_CONFIG_BAD_PARAMETERS);
        setLastCustomErrorMessage(filepath.string() + ": " + error.what());
    }
}

const nlohmann::json* BaseConfiguration::GetParsedJson() const
{
    return IsValid() ? &_jsonP : nullptr;
}
