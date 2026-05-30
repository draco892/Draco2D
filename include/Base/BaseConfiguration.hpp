#pragma once
#ifndef DRACO2D_BASE_CONFIG_H
#define DRACO2D_BASE_CONFIG_H

#include "BaseFile.hpp"

class BaseConfiguration : public BaseFile
{
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
     * @brief Attempts to load and parse configuration settings from a JSON file.
     *
     * @return ErrorClass::ErrorsDRACO2D_NO_ERROR if loading and parsing were successful, the respective error otherwise.
     */
    virtual ErrorClass::Errors load() = 0;
};

#endif  // !DRACO2D_BASE_CONFIG_H