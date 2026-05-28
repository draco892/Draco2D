#pragma once
#ifndef DRACO2D_BASE_BASEFILE_H
#define DRACO2D_BASE_BASEFILE_H

#include <string>
#include <cstdint>

#include "BaseValidateClass.hpp"
#include "ErrorClass.hpp"

class BaseFile : public BaseValidateClass,
                 public ErrorClass
{
public:
    /**
     * @brief file access mode types
     */
    enum class FileAccessMode : uint8_t
    {
        READ,
        WRITE,
        READ_WRITE
    };

    /**
     * @brief Default class costructor.
     *
     * @param filepath The file filePath.
     * @param accesMode The file access mode
     */
    explicit BaseFile(const std::string &filepath,
                      const FileAccessMode accesMode = BaseFile::FileAccessMode::READ);

    /**
     * @brief Virtual destructor to allow proper cleanup of derived objects.
     */
    virtual ~BaseFile() = default;

private:
    /**
     * @brief file FilePath
     */
    const std::string _filepath;

    /**
     * @brief file access mode
     */
    const FileAccessMode _accesMode;
};

#endif  // !DRACO2D_BASE_BASEFILE_H
