#include "../include/Window/ConfigWindow.hpp"

#include <iostream>
#include <string>
#include <boost/describe.hpp>
#include <boost/mp11.hpp>

BOOST_DESCRIBE_STRUCT(ConfigWindow::WindowSettings, (), (title, width, height, flags))

static const std::string WindowsSectionName("window");

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
    if (!IsValid())
    {
        return ErrorClass::getLastError();
    }

    boost::mp11::mp_for_each<boost::describe::describe_members<WindowSettings,
                                                               boost::describe::mod_public>>([this](auto D)
    {
        _ws.*D.pointer = (*GetParsedJson())[WindowsSectionName][D.name];
    });

    return ErrorClass::Errors::DRACO2D_NO_ERROR;
}

ConfigWindow::WindowSettings ConfigWindow::GetWindowSettings() const
{
    return _ws;
}