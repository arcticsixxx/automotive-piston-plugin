#include "Validator.h"

bool Validator::ValidateParameter(double value, double minValue, double maxValue)
{
    return minValue <= value and value <= maxValue;
}
