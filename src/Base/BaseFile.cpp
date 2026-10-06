#include "../include/Base/BaseFile.hpp"

#include <iostream>

BaseFile::BaseFile(const std::filesystem::path &filepath,
                   const FileAccessMode accesMode)
    : _filepath(filepath)
    , _accesMode(accesMode)

{
    if (_accesMode != FileAccessMode::WRITE) {
        setLastError(FileExist(_filepath));
        if (getLastError() == Errors::DRACO2D_NO_ERROR) {
            _ifStream.open(_filepath);
            setLastError(CanReadFile(&_ifStream));
        }
    }
    if (getLastError() == Errors::DRACO2D_NO_ERROR && _accesMode != FileAccessMode::READ) {
        // READ_WRITE must preserve existing contents; WRITE explicitly truncates.
        const auto mode = _accesMode == FileAccessMode::READ_WRITE
            ? std::ios::out | std::ios::in : std::ios::out | std::ios::trunc;
        _ofStream.open(_filepath, mode);
        setLastError(CanWriteFile(&_ofStream));
    }
    setIsValid(getLastError() == Errors::DRACO2D_NO_ERROR);
    if (!IsValid()) setLastCustomErrorMessage(_filepath.string() + ": " + getLastErrorMessage());
}

ErrorClass::Errors BaseFile::FileExist(const std::filesystem::path &filepath)
{

    return (std::filesystem::is_regular_file(filepath))
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