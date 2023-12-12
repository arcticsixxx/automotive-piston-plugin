#pragma once

#include "kAPI5.tlh"

#include <memory>

class KompasSketch;

enum MaterialType;

// Class that provides wrapping over kompass API 
class KompasWrapper
{
public:
	explicit KompasWrapper();

	~KompasWrapper();

public:
	// This method creates empty 
	// 3D document in app
	void createDocument();

public:
	void buildBody(double bodyHeight, double bottomDiameter, double pistonHeadHeight, int ringsCount = 2);

	void extrudePinHole(double bodyHeight, double pinHoleDiameter);

	void extrudePistonSkirt(double bottomDiameter);
	
	void changeMaterial(MaterialType mType);

private:
	// This method provides start of app 
	// and prevent of creating more than 
	// one application instance
	void _openApp();

	// This method creates and init part
	void _createPart();
	
	void _rotateEntity();

	// CALL ONLY THIS METHOD
	void _extrudeLastSketch();

	// NOT FOR CALLING MANUALLY
	void _doExtrude(VARIANT_BOOL vBool);

private:
	// Kompas Application name 
	// for COM interfaces
	const LPCWSTR _kompasAppName = L"Kompas.Application.5";

	// Var used for getting result of operation
	HRESULT _hres;

	// Pointer to Kompas Application instance;
	Kompas6API5::KompasObjectPtr _kompasObject;

	// Pointer to 3D Kompas document that creates 
	// after the start of App
	Kompas6API5::ksDocument3DPtr _document3D;

	// Pointer to Kompas part
	Kompas6API5::ksPartPtr _kompasPart;

	std::shared_ptr<KompasSketch> _kompasSketch;
};

