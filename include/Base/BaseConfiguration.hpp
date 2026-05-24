#pragma once
#ifndef DRACO2D_BASE_CONFIG_H
#define DRACO2D_BASE_CONFIG_H

#include <string>
#include <filesystem>

#include "ErrorClass.hpp"

class BaseConfiguration : public ErrorClass
{
    /**
     * @brief Json configuration filepath
     */
    const std::string _filepath;

    /**
     * @brief Json configuration filepath
     */
    bool _isValid;

protected:
    /**
     * @brief Set the isValid param value
     *
     * @param isValid param value to set
     */
    void setIsValid(const bool isValid);

public:
    /**
     * @brief Default class costructor.
     *
     * @param filepath The configuration filePath.
     */
    BaseConfiguration(const std::string &filepath);

    /**
     * @brief Virtual destructor to allow proper cleanup of derived objects.
     */
    virtual ~BaseConfiguration() = default;

    /**
     * @brief Attempts to load and parse configuration settings from a JSON file.
     *
     * @return True if loading and parsing were successful, false otherwise.
     */
    virtual bool load() = 0;

    /**
     * @brief Return the json file configuration filepath
     *
     * @return The json file configuration filepath
     */
    std::string getFilePath() const;

    /**
     * @brief Return the json file configuration filepath
     *
     * @return The json file configuration filepath
     */
    bool isValid() const;
};

#endif  // !DRACO2D_BASE_CONFIG_H