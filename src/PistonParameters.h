#ifndef PISTONPARAMETERS_H
#define PISTONPARAMETERS_H

#include <QMap>

#include "Parameter.h"


enum ParameterType
{
    PistonHeight = 0,
    PistonHeadHeight,
    PistonBottomDiameter,
    PistonPinHoleDiameter,
    RingsCount,                  // EngineType
};

class PistonParameters
{
public:
    explicit PistonParameters();
    ~PistonParameters();

public:
    double getValue(ParameterType key) const;
    void setValue(ParameterType key, double value);

private:
    QMap<ParameterType, Parameter> _parameters;
};

#endif // PISTONPARAMETERS_H
