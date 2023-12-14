#pragma once

#include <map>

#include "Parameter.h"

// Contains parameter type constants
// TODO: вынести отдельный файл или поместить внутрь класс, если используется только в текущем классе
enum ParameterType
{
    PistonHeight = 0,
    PistonHeadHeight,
    PistonBottomDiameter,
    PistonPinHoleDiameter,
    // Depends of engine type
    RingsCount,                  
};

// Contains material type constants
enum MaterialType
{
    CastIron = 0,
    Aluminum,
};

// Holds collection of piston parameters
class PistonParameters
{
public:
    // Default constructor that initialize parameters with default values
    explicit PistonParameters();

public:
    // Returns value of specified parameter
    // @param key: key that specify parameter
    // @return: value of parameter
    double getValue(ParameterType key) const;

    // Sets value of parameter
    // @param key: key that specify parameter
    // @param value: value of parameter
    // @return: bool value that depends of parameter's validation result
    bool setValue(ParameterType key, double value);
   
    // Returns Parameter object
    // @param key: key that specify parameter
    // @return: parameter object by specified key
    Parameter getParameter(ParameterType key) const;

private:
    // Updates parameter's extremums
    // @param key: key that specify parameter
    // @param value: value for multiplication 
    void _updateParametersExtremums(ParameterType key, double value);

private:
    // Map collection of params
    std::map<ParameterType, Parameter> _parameters;
};
