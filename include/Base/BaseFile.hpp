#pragma once
#ifndef DRACO2D_BASE_BASEFILE_H
#define DRACO2D_BASE_BASEFILE_H

#include <filesystem>
#include <fstream>

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
    explicit BaseFile(const std::filesystem::path &filepath,
                      const FileAccessMode accesMode = BaseFile::FileAccessMode::READ);

    /**
     * @brief Virtual destructor to allow proper cleanup of derived objects.
     */
    virtual ~BaseFile() = default;

    /**
     * @brief check if the file exist (return ErrorClass::Errors::DRACO2D_NO_ERROR in case)
     *
     * @param filepath The file filePath.
     */
    static ErrorClass::Errors FileExist(const std::filesystem::path &filepath);

    /**
     * @brief check if i can read the file (return ErrorClass::Errors::DRACO2D_NO_ERROR in case)
     *
     * @param ifstream file pointer
     */
    static ErrorClass::Errors CanReadFile(const std::ifstream *ifStreamptr);

    /**
     * @brief check if i can write the file (return ErrorClass::Errors::DRACO2D_NO_ERROR in case)
     *
     * @param ofstream file pointer
     */
    static ErrorClass::Errors CanWriteFile(const std::ofstream *ofStreamptr);

    /**
     * @brief return the file path
     */
    std::filesystem::path GetFilePath() const;

    /**
     * @brief return the access mode
     */
    FileAccessMode GetAccessMode() const;

    /**
     * @brief return the ifstream file pointer
     * (NOTE: can be nullptr)
     */
    std::ifstream* GetReadFile() const;

private:
    /**
     * @brief file FilePath
     */
    const std::filesystem::path _filepath;

    /**
     * @brief file access mode
     */
    const FileAccessMode _accesMode;

    /**
     * @brief file ifstream
     */
    const std::ifstream _ifStream;

    /**
     * @brief file ofstream
     */
    const std::ofstream _ofStream;
};

#endif  // !DRACO2D_BASE_BASEFILE_H
