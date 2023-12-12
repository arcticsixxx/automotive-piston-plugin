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
		qDebug() << "[KompassWrapper::KompasWrapper] Error: " << GetLastError();
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

void KompasWrapper::buildBody(double bodyHeight, double bottomDiameter, double pistonHeadHeight, int ringsCount)
{
	_createPart();

	if (!_kompasPart)
	{
		qDebug() << "[KompasWrapper::buildBody] !part";
		return;
	}

	_kompasSketch = std::shared_ptr<KompasSketch>(new KompasSketch(_kompasPart));
	_kompasSketch->drawBody(bodyHeight, bottomDiameter, pistonHeadHeight, ringsCount);

	_rotateEntity();
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
	
	_extrudeLastSketch();
}

void KompasWrapper::extrudePistonSkirt(double bottomDiameter)
{
	_createPart();

	if (!_kompasPart)
	{
		qDebug() << "[KompasWrapper::buildPistonSkirt] !part";
		return;
	}

	_kompasSketch->drawPistonSkirt(bottomDiameter);

	_extrudeLastSketch();
}

void KompasWrapper::changeMaterial(MaterialType mType)
{
	if (!_kompasPart)
	{
		_createPart();
	}

	switch (mType)
	{
	case 0:
		_kompasPart->SetMaterial(L"Ñ×10 ÃÎÑÒ 1412-85", 6.8f);
		break;
	case 1:
		_kompasPart->SetMaterial(L"ÀÄ0 ÃÎÑÒ 4784-2019", 2.71f);
		break;
	}

	_kompasPart->Update();
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

void KompasWrapper::_extrudeLastSketch()
{
	_doExtrude(FALSE);
	_doExtrude(TRUE);
}

void KompasWrapper::_doExtrude(VARIANT_BOOL vBool)
{
	Kompas6API5::ksEntityPtr pinHoleExtr = _kompasPart->NewEntity(Kompas6Constants3D::o3d_cutExtrusion);

	Kompas6API5::ksCutExtrusionDefinitionPtr pinHoleExtrDef = pinHoleExtr->GetDefinition();
	pinHoleExtrDef->directionType = static_cast<short>(Kompas6Constants3D::dtBoth);

	pinHoleExtrDef->SetSideParam(vBool, Kompas6Constants3D::etBlind, 155, 0, FALSE);

	pinHoleExtrDef->SetSketch(_kompasSketch->getSketchEntity());
	pinHoleExtr->Create();
}

