#include "../include/Base/BaseValidateClass.hpp"

// Protected

void BaseValidateClass::setIsValid(const bool isValid)
{
    _isValid = isValid;
}

// Public

BaseValidateClass::BaseValidateClass(const bool isValid)
    : _isValid(isValid)
{}

bool BaseValidateClass::IsValid() const
{
    return _isValid;
}