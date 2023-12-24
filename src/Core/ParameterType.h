#pragma once

// Contains parameter type constants
enum ParameterType
{
    PistonHeight = 0,
    PistonHeadHeight,
    PistonBottomDiameter,
    PistonPinHoleDiameter,
    // Depends of engine type
    RingsCount,
    RingHeight,
    RingWidth,
};

// Contains material type constants
enum MaterialType
{
    CastIron = 0,
    Aluminum,
};