#pragma once

#include "Common/kAPI5.tlh"
// TODO: не используется + 

// TODO: вынести в отдельный файл +-
// Я считаю что данный енум следует оставить в KompasSketch.h
// поскольку, он инкапсулирует информацию о типах линий, которая 
// используется исключительно в данном классе, похожая ситуация и 
// с PistonParameters. В качестве компромисса поместил в тело класса.

// This class provides creation of part's sketch
class KompasSketch
{
public:
	// TODO: добавить комментарий для всех элементов всех классов, перечислений и т.д.

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
	// @param ringsCount: quantity of rings ( depends of engine type)
	void drawBody(double bodyHeight, double bodyWidth, double pistonHeadHeight, int ringsCount = 2);
	
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
	// @param ringsCount: quantity of rings ( depends of engine type)
	void _drawRings(double& x, double& y, double pistonHeadHeight, int ringsCount = 2);

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

