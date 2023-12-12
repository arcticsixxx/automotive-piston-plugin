#pragma once

// Provides validation of parameter
class Validator
{
public: 
	// Validation operation
    // @param value: value of parameter
    // @param minValue: minimal value 
    // @param maxValue: maximal value
    // @return: bool value that depends of parameter's validation result
	static bool ValidateParameter(double value, double minValue, double maxValue);
};

