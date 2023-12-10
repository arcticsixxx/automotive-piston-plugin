#include "KompasWrapper.h"

#include "KompasSketch.h"

#include <exception>

#include <QDebug>

#include <atlbase.h>

#include "ksConstants3D.tlh"

KompasWrapper::KompasWrapper()
{
	_hres = CoInitialize(NULL);

	if (FAILED(_hres))
	{
		qDebug() << "[KompassWrapper::KompasWrapper] Error: "
				  << GetLastError();
		throw std::exception("Can't Initialize KompassWrapper");
	}
}

KompasWrapper::~KompasWrapper()
{
	CoUninitialize();
}

void KompasWrapper::_openApp()
{
	_hres = _kompasObject.GetActiveObject(_kompasAppName);

	if (FAILED(_hres))
	{
		_kompasObject.CreateInstance(_kompasAppName);
	}
	_kompasObject->Visible = true;
}

void KompasWrapper::_createPart()
{
    _kompasPart = _document3D->GetPart(Kompas6Constants3D::pTop_Part);
}

void KompasWrapper::createDocument()
{
	_openApp();

	if (!_kompasObject)
	{
		throw std::exception("Kompass object not initialized");
	}

	_document3D = _kompasObject->Document3D();

	// false - makeInvisible; true - this doc not part of assembly
	_document3D->Create(false, true);
	_document3D = _kompasObject->ActiveDocument3D();
}

void KompasWrapper::buildBody(double bodyHeight, double bottomDiameter, int ringsCount)
{
	_createPart();

	if (!_kompasPart)
	{
		qDebug() << "[KompasWrapper::buildBody] !part";
		return;
	}

	_kompasSketch = std::make_shared<KompasSketch>(_kompasPart);
	_kompasSketch->drawBody(bodyHeight, bottomDiameter, ringsCount);

	_rotateEntity();

	_kompasSketch->drawPistonSkirt(bottomDiameter);
}

void KompasWrapper::extrudePinHole(double bodyHeight, double pinHoleDiameter)
{
	_createPart();

	if (!_kompasPart)
	{
		qDebug() << "[KompasWrapper::extrudePinHole] !part";
		return;
	}

	_kompasSketch->drawPinHole(bodyHeight, pinHoleDiameter);
	
	_doExtrudePinHole(FALSE);
	_doExtrudePinHole(TRUE);
}

void KompasWrapper::_doExtrudePinHole(VARIANT_BOOL vBool)
{
	Kompas6API5::ksEntityPtr pinHoleExtr = _kompasPart->NewEntity(Kompas6Constants3D::o3d_cutExtrusion);
	
	Kompas6API5::ksCutExtrusionDefinitionPtr pinHoleExtrDef = pinHoleExtr->GetDefinition();
	pinHoleExtrDef->cut = true;
	pinHoleExtrDef->directionType = static_cast<short>(Kompas6Constants3D::dtBoth);

	pinHoleExtrDef->SetSideParam(vBool, Kompas6Constants3D::etBlind, 155, 0, FALSE);

	pinHoleExtrDef->SetSketch(_kompasSketch->getSketchEntity());
	pinHoleExtr->Create();
}

void KompasWrapper::_rotateEntity()
{
	Kompas6API5::ksEntityPtr entityRotate = _kompasPart->NewEntity(Kompas6Constants3D::o3d_bossRotated);

	if (!entityRotate)
	{
		qDebug() << "!entityRotate";
		return;
	}

	Kompas6API5::ksBossRotatedDefinitionPtr rotateDef = entityRotate->GetDefinition();

	if (!rotateDef)
	{
		qDebug() << "!entityRotate";
		return;
	}

	Kompas6API5::ksRotatedParamPtr rotproperty(rotateDef->RotatedParam());

	if (!rotproperty)
	{
		qDebug() << "!roproperty";
		return;
	}

	rotproperty->direction = Kompas6Constants3D::dtBoth;
	rotateDef->SetSideParam(TRUE, 360);
	rotateDef->SetSketch(_kompasSketch->getSketchEntity());
	entityRotate->Create();
}

KompasSketch* KompasWrapper::createNewSketch() const
{
	return new KompasSketch(_kompasPart);
}
