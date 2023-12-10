#ifndef PISTONBUILDER_H
#define PISTONBUILDER_H

#include <memory>

#include "KompasWrapper.h"


class PistonParameters;

class PistonBuilder
{
public:
    explicit PistonBuilder();

public:
    void setParameters(std::shared_ptr<PistonParameters> pistonParameters);
    
    void build() const;

private:
    void _buildBody() const;
    void _extrudePinHole() const;

private:
    std::unique_ptr<KompasWrapper> _kompasWrapper;
    std::shared_ptr<PistonParameters> _pistonParameters;
};

#endif // PISTONBUILDER_H
