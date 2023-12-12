#pragma once

#include <QMap>

#include "Parameter.h"

enum ParameterType
{
    PistonHeight = 0,
    PistonHeadHeight,
    PistonBottomDiameter,
    PistonPinHoleDiameter,
    // TODO: комментарий установить над нужной строке
    RingsCount,                  // EngineType
};

enum MaterialType
{
    CastIron = 0,
    Aluminum,
};

class PistonParameters
{
public:
    explicit PistonParameters();

public:
    double getValue(ParameterType key) const;
    bool setValue(ParameterType key, double value);
   
    Parameter getParameter(ParameterType key) const;

private:
    void _updateParametersExtremums(ParameterType key, double value);

private:
    QMap<ParameterType, Parameter> _parameters;
};
