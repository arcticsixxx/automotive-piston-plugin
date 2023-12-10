#include "Validator.h"

bool Validator::Validate(double value, double minValue, double maxValue)
{
    return minValue <= value && value <= maxValue;
}
