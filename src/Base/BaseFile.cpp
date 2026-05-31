#include "../include/Base/BaseFile.hpp"

#include <iostream>

BaseFile::BaseFile(const std::filesystem::path &filepath,
                   const FileAccessMode accesMode)
    : _filepath(filepath)
    , _accesMode(accesMode)
    , _ifStream(filepath)
    , _ofStream(filepath)
{
    // Check if the file exist
    ErrorClass::setLastError(FileExist(_filepath));

    if (ErrorClass::getLastError() != ErrorClass::Errors::DRACO2D_FILE_MISSING)
    {
        std::cerr << ErrorClass::getLastErrorMessage() << std::endl;
        BaseValidateClass::setIsValid(false);
        return;
    }

    // Check if i can read the file
    if (_accesMode == FileAccessMode::READ
        || _accesMode == FileAccessMode::READ_WRITE)
    {
        ErrorClass::setLastError(CanReadFile(&_ifStream));

        if (ErrorClass::getLastError() != ErrorClass::Errors::DRACO2D_FILE_MISSING)
        {
            std::cerr << ErrorClass::getLastErrorMessage() << std::endl;
            BaseValidateClass::setIsValid(false);
            return;
        }
    }

    // Check if i can read the file
    if (_accesMode == FileAccessMode::WRITE
        || _accesMode == FileAccessMode::READ_WRITE)
    {
        ErrorClass::setLastError(CanWriteFile(&_ofStream));

        if (ErrorClass::getLastError() != ErrorClass::Errors::DRACO2D_FILE_MISSING)
        {
            std::cerr << ErrorClass::getLastErrorMessage() << std::endl;
            BaseValidateClass::setIsValid(false);
            return;
        }
    }
}

ErrorClass::Errors BaseFile::FileExist(const std::filesystem::path &filepath)
{

    return (std::filesystem::exists(filepath))
               ? ErrorClass::Errors::DRACO2D_NO_ERROR
               : ErrorClass::Errors::DRACO2D_FILE_MISSING;
}


ErrorClass::Errors BaseFile::CanReadFile(const std::ifstream *ifStreamptr)
{
    if (ifStreamptr == nullptr)
    {
        return ErrorClass::Errors::DRACO2D_FILE_NULLPTR;
    }

    return (!ifStreamptr->is_open())
               ? ErrorClass::Errors::DRACO2D_FILE_CANNOT_READ
               : ErrorClass::Errors::DRACO2D_NO_ERROR;
}


ErrorClass::Errors BaseFile::CanWriteFile(const std::ofstream *ofStreamptr)
{
    if (ofStreamptr == nullptr)
    {
        return ErrorClass::Errors::DRACO2D_FILE_NULLPTR;
    }

    return (!ofStreamptr->is_open())
               ? ErrorClass::Errors::DRACO2D_FILE_CANNOT_WRITE
               : ErrorClass::Errors::DRACO2D_NO_ERROR;
}

std::filesystem::path BaseFile::GetFilePath() const
{
    return _filepath;
}

BaseFile::FileAccessMode BaseFile::GetAccessMode() const
{
    return _accesMode;
}

std::ifstream* BaseFile::GetReadFile()
{
    return &_ifStream;
}

std::ofstream* BaseFile::GetWriteFile()
{
    return &_ofStream;
}