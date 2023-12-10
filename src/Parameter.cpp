#include "Parameter.h"

#include "Validator.h"

#include <exception>

Parameter::Parameter(double value, double minValue, double maxValue)
{
    if ( ! Validator::Validate(value, minValue, maxValue))
    {
        throw std::exception("Minimum value is bigger than maximum");
    }

    setValue(value);
    setMinValue(minValue);
    setMaxValue(maxValue);
}

void Parameter::setValue(double value)
{
// TO-DO validator
    _value = value;
}

double Parameter::getValue() const
{
    return _value;
}

void Parameter::setMaxValue(double maxValue)
{
    _maxValue = maxValue;
}

double Parameter::getMaxValue() const
{
    return _maxValue;
}

void Parameter::setMinValue(double minValue)
{
    _minValue = minValue;
}

double Parameter::getMinValue() const
{
    return _minValue;
}
