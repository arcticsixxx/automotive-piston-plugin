#include "PistonParameters.h"

#include <QDebug>

PistonParameters::PistonParameters()
{
    _parameters.insert(ParameterType::PistonHeight,
                        Parameter(55, 50, 65));
    _parameters.insert(ParameterType::PistonHeadHeight,
                        Parameter(16, 13.75, 17.6));
    _parameters.insert(ParameterType::PistonBottomDiameter,
                        Parameter(100, 92, 106));
    _parameters.insert(ParameterType::PistonPinHoleDiameter,
                        Parameter(18, 16, 22));
    _parameters.insert(ParameterType::RingsCount,
                        Parameter(2, 2, 3)); 
}

double PistonParameters::getValue(ParameterType key) const
{
    return _parameters.value(key).getValue();
}

bool PistonParameters::setValue(ParameterType key, double value)
{
    if (_parameters[key].setValue(value))
    {
        _updateParametersExtremums(key, value);
        return true;
    }

    return false;
}

Parameter PistonParameters::getParameter(ParameterType key) const
{
    return _parameters[key];
}

void PistonParameters::_updateParametersExtremums(ParameterType key, double value)
{
    constexpr double minPistonHeadScaling = 0.25f;
    constexpr double maxPistonHeadScaling = 0.32f;

    constexpr double minPinHoleScaling = 0.16f;
    constexpr double maxPinHoleScaling = 0.22f;

    switch (key)
    {
    case ParameterType::PistonHeight:
        _parameters[PistonHeadHeight].setMinValue(value * minPistonHeadScaling);
        _parameters[PistonHeadHeight].setMaxValue(value * maxPistonHeadScaling);
        break;
    case ParameterType::PistonBottomDiameter:
        _parameters[PistonPinHoleDiameter].setMinValue(value * minPinHoleScaling);
        _parameters[PistonPinHoleDiameter].setMaxValue(value * maxPinHoleScaling);
        break;
    default:
        return;
    }
}

