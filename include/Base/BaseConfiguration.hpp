#pragma once
#ifndef DRACO2D_BASE_CONFIG_H
#define DRACO2D_BASE_CONFIG_H

#include "BaseFile.hpp"

#include <nlohmann/json.hpp>

class BaseConfiguration : public BaseFile
{
    /**
     * @brief the parsed json
     */
    const nlohmann::json _jsonP;

public:
    /**
     * @brief Default class costructor.
     *
     * @param filepath The configuration filePath.
     */
    explicit BaseConfiguration(const std::filesystem::path &filepath);

    /**
     * @brief Virtual destructor to allow proper cleanup of derived objects.
     */
    virtual ~BaseConfiguration() = default;

    /**
     * @brief Load the json configuration.
     *
     * @return ErrorClass::ErrorsDRACO2D_NO_ERROR if loading and parsing were successful, the respective error otherwise.
     */
    virtual ErrorClass::Errors load() = 0;

    /**
     * @brief Get the parsed json pointer
     *
     * @return the parsed json pointer
     * (NOTE: can be nullptr)
     */
    const nlohmann::json* GetParsedJson() const;

};

#endif  // !DRACO2D_BASE_CONFIG_H