#pragma once

#include "Common/kAPI5.tlh"

// This class provides creation of part's sketch
class KompasSketch
{
public:
	// Constructor of KompasSketch
	// @param part: pointer to part for which sketch will be built
	explicit KompasSketch(Kompas6API5::ksPartPtr part);

public:
	// Set of line types constants
	enum LineType
	{
		Auxillary = 0,
		Main = 1,
		RotationAxes = 3,
	};

public:
	// Draws body of piston on sketch
	// @param bodyHeight: height of piston's body
	// @param bodyWidth: bottom diameter of piston
	// @param pistonHeadHeight: height of piston's head
	// @param ringhHeight: height of ring
	// @param ringWidth: width of ring
	// @param ringsCount: quantity of rings ( depends of engine type)
	void drawBody(double bodyHeight, double bodyWidth, double pistonHeadHeight, 
		double ringHeight, double ringWidth, int ringsCount = 2);
	
	// Draws pin hole of piston on sketch 
	// @param bodyHeight: height of piston's body
	// @param pinHoleDiameter: diameter of piston's pinHole
	void drawPinHole(double bodyHeight, double pinHoleDiameter);
	
	// Draws Piston skirt
	// @param bodyWidth: bottom diameter of piston
	void drawPistonSkirt(double bodyWidth);

public:
	// Returns pointer to interface of sketch
	// @return: pointer to sketch's entity
	Kompas6API5::ksEntityPtr getSketchEntity() const noexcept;

private:
	// Method used for creating sketch
	void _createSketch();

	// drawRings ( 2 or 3 ) depends of engine type
	// @param x: current position of polyline by x
	// @param y: current position of polyline by y
	// @param pistonHeadHeight: height of piston's head
	// @param ringhHeight: height of ring
	// @param ringWidth: width of ring
	// @param ringsCount: quantity of rings ( depends of engine type)
	void _drawRings(double& x, double& y, double pistonHeadHeight, 
		double ringHeight, double ringWidth, int ringsCount = 2);

private:
	// Interface of sketch entity
	Kompas6API5::ksEntityPtr _sketchEntity;

	// Pointer to sketch definition
	Kompas6API5::ksSketchDefinitionPtr _sketchDefinition;

	// Pointer to sketch
	Kompas6API5::ksDocument2DPtr _document2D;

	// Pointer to part from KompasWrapper
	Kompas6API5::ksPartPtr _part;
};

