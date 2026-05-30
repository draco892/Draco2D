#include "../include/Window/ConfigWindow.hpp"

#include <iostream>

ConfigWindow::ConfigWindow(const std::string &filepath)
    : BaseConfiguration(filepath)
{
    ErrorClass::setLastError(load());
    if (ErrorClass::getLastError() != ErrorClass::Errors::DRACO2D_FILE_MISSING)
    {
        std::cerr << ErrorClass::getLastErrorMessage() << std::endl;
        BaseValidateClass::setIsValid(false);
        return;
    }
}

ErrorClass::Errors ConfigWindow::load()
{
    // File Check
    if (!BaseValidateClass::IsValid())
    {
        return ErrorClass::getLastError();
    }



    return ErrorClass::Errors::DRACO2D_NO_ERROR;
}