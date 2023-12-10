#include "PistonParameters.h"

#include <QDebug>

PistonParameters::PistonParameters()
{
    try
    {
        _parameters.insert(ParameterType::PistonHeight,
                           Parameter(55, 36, 60));
        _parameters.insert(ParameterType::PistonHeadHeight,
                           Parameter(20, 18, 27.5));
        _parameters.insert(ParameterType::PistonBottomDiameter,
                           Parameter(100, 92, 106));
        _parameters.insert(ParameterType::PistonPinHoleDiameter,
                           Parameter(18, 16, 22));
        _parameters.insert(ParameterType::RingsCount,
                           Parameter(2, 2, 3));
    }

    catch (std::exception& ex)
    {
        qDebug() << ex.what();
    }
}

PistonParameters::~PistonParameters()
{
}

double PistonParameters::getValue(ParameterType key) const
{
    return _parameters.value(key).getValue();
}

void PistonParameters::setValue(ParameterType key, double value)
{
    qDebug() << &key << value;
    _parameters[key].setValue(value);
}
