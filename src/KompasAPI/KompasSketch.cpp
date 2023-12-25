#include "KompasSketch.h"

#include "Common/ksConstants3D.tlh"
KompasSketch::KompasSketch(Kompas6API5::ksPartPtr part) :
    _part(part)
{
    _createSketch();
}

void KompasSketch::_createSketch()
{
    _sketchEntity = _part->NewEntity(Kompas6Constants3D::o3d_sketch);

    _sketchDefinition = _sketchEntity->GetDefinition();
    _sketchDefinition->SetPlane(_part->GetDefaultEntity(Kompas6Constants3D::o3d_planeXOZ));

    _sketchEntity->Create();
}

void KompasSketch::_drawRings(double& x, double& y, double pistonHeadHeight, 
	double ringHeight, double ringWidth, int ringsCount)
{
	if (ringsCount == 2) pistonHeadHeight -= 8;
	if (ringsCount == 3) pistonHeadHeight -= 12;

	y += pistonHeadHeight;
	_document2D->ksPoint(x, y, LineType::Auxillary);
	
	for (int i = 0; i < ringsCount; ++i)
	{
		_document2D->ksPoint(x, y, LineType::Auxillary);
		_document2D->ksPoint(x, y + ringHeight, LineType::Auxillary);
		_document2D->ksPoint(x + ringWidth, y + ringHeight, LineType::Auxillary);
		_document2D->ksPoint(x + ringWidth, y + (2 * ringHeight), LineType::Auxillary);

		y += 2 * ringHeight;
	}
}

void KompasSketch::drawBody(double bodyHeight, double bodyWidth, double pistonHeadHeight, 
	double ringHeight, double ringWidth, int ringsCount)
{
	bodyHeight = (-1) * bodyHeight;
	bodyWidth = (-1) * (bodyWidth / 2);

	_document2D = _sketchDefinition->BeginEdit();

	// axes of rotation
	_document2D->ksLineSeg(0, 0, 0, bodyHeight, LineType::RotationAxes);
	
	// draws rings of piston
	_document2D->ksPolyline(LineType::Main);
	
	_document2D->ksPoint(0, bodyHeight, LineType::Main);
	_document2D->ksPoint(bodyWidth, bodyHeight, LineType::Main);
	_drawRings(bodyWidth, bodyHeight, pistonHeadHeight, ringHeight,
		ringWidth, ringsCount);

	// remaining part of piston
	_document2D->ksPoint(bodyWidth, bodyHeight, LineType::Main);
	_document2D->ksPoint(bodyWidth, 0, LineType::Main);
	_document2D->ksPoint(0, 0, LineType::Main);

	_document2D->ksEndObj();

	_sketchDefinition->EndEdit();
}

void KompasSketch::drawPinHole(double bodyHeight, double pinHoleDiameter)
{
	bodyHeight = (-1) * bodyHeight;

	constexpr double pinHolePosX = 0;
	const double pinHolePosY = 0.4f * bodyHeight;

	_createSketch();

	_document2D = _sketchDefinition->BeginEdit();
	
	_document2D->ksCircle(pinHolePosX, pinHolePosY,
		pinHoleDiameter / 2, LineType::Main);

	_sketchDefinition->EndEdit();
}

void KompasSketch::drawPistonSkirt(double bodyWidth)
{	
	const double xPos = bodyWidth / 2;
	constexpr double heightSkirt = -5;
	constexpr double widthSkirt = 8;

	_createSketch();

	_document2D = _sketchDefinition->BeginEdit();

	_document2D->ksPolyline(LineType::Main);

	_document2D->ksPoint(xPos, 0,	LineType::Main);
	_document2D->ksPoint(xPos - widthSkirt, heightSkirt, LineType::Main);
	_document2D->ksPoint((-1) * xPos + widthSkirt, heightSkirt, LineType::Main);
	_document2D->ksPoint((-1) * xPos, 0, LineType::Main);

	_document2D->ksEndObj();

	_document2D->ksLineSeg(xPos, 0, (-1) * xPos, 0, LineType::Main);

	_sketchDefinition->EndEdit();
}

Kompas6API5::ksEntityPtr KompasSketch::getSketchEntity() const noexcept
{
	return _sketchEntity;
}
