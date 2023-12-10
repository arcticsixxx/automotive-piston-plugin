#include "KompasSketch.h"

#include "ksConstants3D.tlh"
#include "ksConstants.tlh"


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

void KompasSketch::_drawRings(double& x, double& y, int ringsCount)
{
	const double ringDepth = 1;
	const double ringHeigth = 2;

	// Height of Head
	y += 10;
	_document2D->ksPoint(x, y, LineType::Auxillary);
	
	for (int i = 0; i < ringsCount; ++i)
	{
		_document2D->ksPoint(x, y, LineType::Auxillary);
		_document2D->ksPoint(x, y + ringHeigth, LineType::Auxillary);
		_document2D->ksPoint(x + 1, y + ringHeigth, LineType::Auxillary);
		_document2D->ksPoint(x+ 1, y + (2 * ringHeigth), LineType::Auxillary);

		y += 2 * ringHeigth;
	}
}

void KompasSketch::drawBody(double bodyHeight, double bodyWidth, int ringsCount)
{
	bodyHeight = (-1) * bodyHeight;
	bodyWidth = (-1) * (bodyWidth / 2);

	_document2D = _sketchDefinition->BeginEdit();

	// ÎÑÜ ÂÐÀÙÅÍÈß
	_document2D->ksLineSeg(0, 0, 0, bodyHeight, LineType::RotationAxes);
	
	// ÎÒÐÈÑÎÂÊÀ ÊÎËÅÖ
	_document2D->ksPolyline(LineType::Main);
	
	_document2D->ksPoint(0, bodyHeight, LineType::Main);
	_document2D->ksPoint(bodyWidth, bodyHeight, LineType::Main);
	_drawRings(bodyWidth, bodyHeight, ringsCount);

	// ÎÒÐÈÑÎÂÊÀ ÎÑÒÀÂØÅÉÑß ×ÀÑÒÈ ÏÎÐØÍß
	_document2D->ksPoint(bodyWidth, bodyHeight, LineType::Main);
	_document2D->ksPoint(bodyWidth, 0, LineType::Main);
	_document2D->ksPoint(0, 0, LineType::Main);

	_document2D->ksEndObj();

	_sketchDefinition->EndEdit();
}

void KompasSketch::drawPinHole(double bodyHeight, double pinHoleDiameter)
{
	bodyHeight = (-1) * bodyHeight;
	
	_createSketch();

	_document2D = _sketchDefinition->BeginEdit();
	
	_document2D->ksCircle(0, (0.4f) * bodyHeight, pinHoleDiameter / 2, 1);

	_sketchDefinition->EndEdit();
}

void KompasSketch::drawPistonSkirt(double bodyWidth)
{	
	_createSketch();

	_document2D = _sketchDefinition->BeginEdit();

	_document2D->ksPolyline(LineType::Main);

	_document2D->ksPoint(bodyWidth / 2, 0, LineType::Main);
	_document2D->ksPoint((bodyWidth / 2) - 8, -5, LineType::Main);
	_document2D->ksPoint((-1) * (bodyWidth / 2) + 8, -5, LineType::Main);
	_document2D->ksPoint((-1) * (bodyWidth / 2), 0, LineType::Main);

	_document2D->ksEndObj();

	_document2D->ksLineSeg(bodyWidth / 2, 0, (-1) * (bodyWidth / 2), 0, LineType::Main);


	_sketchDefinition->EndEdit();
}

Kompas6API5::ksEntityPtr KompasSketch::getSketchEntity() const
{
	return _sketchEntity;
}
