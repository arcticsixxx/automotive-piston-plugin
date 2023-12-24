#include "PistonParameters.h"
#include "ParameterType.h"

PistonParameters::PistonParameters()
{
    _parameters.insert(std::make_pair(ParameterType::PistonHeight,
        Parameter(55, 50, 65)));
    _parameters.insert(std::make_pair(ParameterType::PistonHeadHeight,
        Parameter(16, 13.75, 17.6)));
    _parameters.insert(std::make_pair(ParameterType::PistonBottomDiameter,
        Parameter(100, 92, 106)));
    _parameters.insert(std::make_pair(ParameterType::PistonPinHoleDiameter,
        Parameter(18, 16, 22)));
    _parameters.insert(std::make_pair(ParameterType::RingsCount,
        Parameter(2, 2, 3))); 
    _parameters.insert(std::make_pair(ParameterType::RingHeight,
        Parameter(2, 1, 3)));
    _parameters.insert(std::make_pair(ParameterType::RingWidth,
        Parameter(1, 0.8, 2.5)));
}

double PistonParameters::getValue(ParameterType key) const
{
    return _parameters.at(key).getValue();
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
    return _parameters.at(key);
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
        _parameters[PistonHeadHeight].setMinValue(round(value * minPistonHeadScaling * 10.0) / 10.0);
        _parameters[PistonHeadHeight].setMaxValue(round(value * maxPistonHeadScaling * 10.0) / 10.0);
        break;
    case ParameterType::PistonBottomDiameter:
        _parameters[PistonPinHoleDiameter].setMinValue(round(value * minPinHoleScaling * 10.0) / 10.0);
        _parameters[PistonPinHoleDiameter].setMaxValue(round(value * maxPinHoleScaling * 10.0) / 10.0);
        break;
    default:
        return;
    }
}

