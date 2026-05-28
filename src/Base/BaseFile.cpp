#include "../include/Base/BaseFile.hpp"

BaseFile::BaseFile(const std::string &filepath,
                   const FileAccessMode accesMode)
    : _filepath(filepath)
    , _accesMode(accesMode)
{}