#pragma once

#include "kAPI5.tlh"

#include <memory>

enum LineType
{
	Auxillary = 0,
	Main = 1,
	RotationAxes = 3,
};

// This class provides creation of part
// sketch 
class KompasSketch
{
public:
	// Constructor that takes part;
	explicit KompasSketch(Kompas6API5::ksPartPtr part);

public:
	void drawBody(double bodyHeight, double bodyWidth, int ringsCount = 2);
	void drawPinHole(double bodyHeight, double pinHoleDiameter);
	void drawPistonSkirt(double bodyWidth);

	Kompas6API5::ksEntityPtr getSketchEntity() const;

private:
	// Method used for creating sketch
	void _createSketch();

	// drawRings ( 2 or 3 ) depends of engine type
	void _drawRings(double& x, double& y, int ringsCount = 2);

private:
	Kompas6API5::ksEntityPtr _sketchEntity;

	// Pointer to sketch definition
	Kompas6API5::ksSketchDefinitionPtr _sketchDefinition;

	// Pointer to sketch
	Kompas6API5::ksDocument2DPtr _document2D;

	// Pointer to part from KompasWrapper
	Kompas6API5::ksPartPtr _part;
};

