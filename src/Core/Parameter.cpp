#include "Parameter.h"

#include "Validator.h"

#include <exception>

Parameter::Parameter(double value, double minValue, double maxValue)
{
    if (!Validator::ValidateParameter(value, minValue, maxValue))
    {
        throw std::exception("Minimum value is bigger than maximum");
    }

    _value = value;
    setMinValue(minValue);
    setMaxValue(maxValue);
}

bool Parameter::setValue(double value)
{
    if (value < _minValue or value > _maxValue)
    {
        return false;
    }

    _value = value;

    return true;
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
