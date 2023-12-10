#include "PistonBuilder.h"

#include "PistonParameters.h"

#include <QDebug>

PistonBuilder::PistonBuilder()
{
    _kompasWrapper = std::make_unique<KompasWrapper>();
}

void PistonBuilder::setParameters(std::shared_ptr<PistonParameters> pistonParameters)
{
    _pistonParameters = pistonParameters;
}

void PistonBuilder::build() const
{
    _kompasWrapper->createDocument();
    
    _buildBody();
    _extrudePinHole();
}

void PistonBuilder::_buildBody() const 
{
    const double bodyHeight = _pistonParameters->getValue(ParameterType::PistonHeight);
    const double bottomDiameter = _pistonParameters->getValue(ParameterType::PistonBottomDiameter);
    const int ringsCount = _pistonParameters->getValue(ParameterType::RingsCount);
    
    _kompasWrapper->buildBody(bodyHeight, bottomDiameter, ringsCount);
}

void PistonBuilder::_extrudePinHole() const
{
    const double bodyHeight = _pistonParameters->getValue(ParameterType::PistonHeight);
    const double pinHoleDiameter = _pistonParameters->getValue(ParameterType::PistonPinHoleDiameter);

    _kompasWrapper->extrudePinHole(bodyHeight, pinHoleDiameter);
}


