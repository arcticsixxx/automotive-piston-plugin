#include "PistonBuilder.h"

#include "PistonParameters.h"
#include "ParameterType.h"

PistonBuilder::PistonBuilder(std::shared_ptr<PistonParameters> pistonParameters) : 
    _pistonParameters(pistonParameters)
{
    _kompasWrapper = std::make_unique<KompasWrapper>();
}

void PistonBuilder::setParameters(std::shared_ptr<PistonParameters> pistonParameters)
{
    _pistonParameters = pistonParameters;
}

void PistonBuilder::setMaterial(MaterialType materialType)
{
    _materialType = materialType;
}

void PistonBuilder::build() const
{
    _kompasWrapper->createDocument();
    
    _buildBody();
    _extrudePinHole();
    _extrudePistonSkirt();
    _changeMaterial();
}

void PistonBuilder::_buildBody() const 
{
    if (!_pistonParameters)
    {
        return;
    }

    const double bodyHeight = _pistonParameters->getValue(ParameterType::PistonHeight);
    const double bottomDiameter = _pistonParameters->getValue(ParameterType::PistonBottomDiameter);
    const double pistonHeadHeight = _pistonParameters->getValue(ParameterType::PistonHeadHeight);
    const double ringHeigth = _pistonParameters->getValue(ParameterType::RingHeight);
    const double ringWidth = _pistonParameters->getValue(ParameterType::RingWidth);

    const int ringsCount = _pistonParameters->getValue(ParameterType::RingsCount);
    
    _kompasWrapper->buildBody(bodyHeight, bottomDiameter, pistonHeadHeight, ringHeigth, ringWidth, ringsCount);
}

void PistonBuilder::_extrudePinHole() const
{
    if (!_pistonParameters)
    {
        return;
    }

    const double bodyHeight = _pistonParameters->getValue(ParameterType::PistonHeight);
    const double pinHoleDiameter = _pistonParameters->getValue(ParameterType::PistonPinHoleDiameter);

    _kompasWrapper->extrudePinHole(bodyHeight, pinHoleDiameter);
}

void PistonBuilder::_extrudePistonSkirt() const
{
    if (!_pistonParameters)
    {
        return;
    }

    const double bottomDiameter = _pistonParameters->getValue(ParameterType::PistonBottomDiameter);
    
    _kompasWrapper->extrudePistonSkirt(bottomDiameter);
}

void PistonBuilder::_changeMaterial() const
{
    _kompasWrapper->changeMaterial(_materialType);
}