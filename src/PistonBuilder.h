#pragma once

#include <memory>

#include "KompasWrapper.h"

class PistonParameters;

enum MaterialType;

// Class builds piston part
class PistonBuilder
{
public:
    // PistonBuilder constructor
    // @param pistonParameters: pointer to parameters of piston
    explicit PistonBuilder(std::shared_ptr<PistonParameters> pistonParameters);
   
public:
    // Setter for piston's parameters
    // @param pistonParameters: pointer to parameters of piston
    void setParameters(std::shared_ptr<PistonParameters> pistonParameters);

    // Setter for material of piston
    // @param materialType: constant of MaterialType
    void setMaterial(MaterialType materialType);

    // Build piston
    void build() const;

private:
    // Builds body
    void _buildBody() const;

    // Extrudes pin hole
    void _extrudePinHole() const;

    // Extrudes piston skirt
    void _extrudePistonSkirt() const;

    // Changes material
    void _changeMaterial() const;

private:
    // Pointer to KompasWrapper 
    std::unique_ptr<KompasWrapper> _kompasWrapper;

    // Pointer to piston parameter
    std::shared_ptr<PistonParameters> _pistonParameters;

private:
    // MaterialType constant
    MaterialType _materialType;
};

