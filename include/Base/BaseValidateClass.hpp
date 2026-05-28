#pragma once
#ifndef DRACO2D_BASE_BASEVALIDATECLASS_H
#define DRACO2D_BASE_BASEVALIDATECLASS_H

class BaseValidateClass
{
    /**
     * @brief isValid param
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
     * @param isValid value, optional (default value: true)
     */
    BaseValidateClass(const bool isValid = true);

    /**
     * @brief Virtual destructor to allow proper cleanup of derived objects.
     */
    virtual ~BaseValidateClass() = default;

    /**
     * @brief Return the isValid value
     *
     * @return the isValid value
     */
    bool isValid() const;
};

#endif  // !DRACO2D_BASE_BASEVALIDATECLASS_H
