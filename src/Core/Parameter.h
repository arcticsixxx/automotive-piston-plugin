#pragma once 

// Class encapsulates information about min and max possible value of parameter
class Parameter
{
public:
    // Default Parameter constructor
    Parameter() = default;

    // Parameter constructor
    // @param value: value of parameter
    // @param minValue: minimal value 
    // @param maxValue: maximal value
    explicit Parameter(double value, double minValue, double maxValue);

public:
    // Setter for value
    // @param value: value of parameter
    // @return: bool value that depends of value's result validation 
    bool setValue(double value);

    // Getter for value
    // @return: value
    double getValue() const;

    // Setter for maximal value
    // @param maxValue: maximal value of parameter
    void setMaxValue(double maxValue);

    // Getter for maximal value
    // @return: maximal value
    double getMaxValue() const;

    // Setter for minimal value
    // @param minValue: minimal value of parameter
    void setMinValue(double minValue);
    
    // Getter for minimal value
    // @return: minimal value
    double getMinValue() const;

private:
    // Holds maxValue
    double _maxValue;
    // Holds minValue
    double _minValue;
    // Holds value
    double _value;
};
