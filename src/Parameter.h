#pragma once 

class Parameter
{
public:
    explicit Parameter() = default;
    explicit Parameter(double value, double minValue, double maxValue);

public:
    bool setValue(double value);
    double getValue() const;

    void setMaxValue(double maxValue);
    double getMaxValue() const;

    void setMinValue(double minValue);
    double getMinValue() const;

private:
    double _maxValue;
    double _minValue;
    double _value;
};
