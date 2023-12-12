#pragma once

#include <memory>

#include "KompasWrapper.h"

class PistonParameters;

enum MaterialType;

class PistonBuilder
{
public:
    explicit PistonBuilder(std::shared_ptr<PistonParameters> pistonParameters);
   
public:
    void setParameters(std::shared_ptr<PistonParameters> pistonParameters);
    void setMaterial(MaterialType materialType);

    void build() const;

private:
    void _buildBody() const;
    void _extrudePinHole() const;
    void _extrudePistonSkirt() const;
    void _changeMaterial() const;

private:
    std::unique_ptr<KompasWrapper> _kompasWrapper;
    std::shared_ptr<PistonParameters> _pistonParameters;

private:
    MaterialType _materialType;
};

