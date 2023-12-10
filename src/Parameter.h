#ifndef PARAMETER_H
#define PARAMETER_H


class Parameter
{
public:
    explicit Parameter() = default;
    explicit Parameter(double value, double minValue, double maxValue);

public:
    void setValue(double value);
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

#endif // PARAMETER_H
