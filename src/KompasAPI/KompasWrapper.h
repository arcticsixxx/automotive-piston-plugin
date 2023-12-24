#pragma once

#include "Common/kAPI5.tlh"

#include <memory>

class KompasSketch;

enum MaterialType;

// Class that provides wrapping over kompass API 
class KompasWrapper
{
public:
	// Constructor of KompassWrapper class
	explicit KompasWrapper();

	// Destructor of KompassWrapper class
	~KompasWrapper();

public:
	// This method creates empty 3D document in app
	void createDocument();

public:
	// Builds piston body 
	// @param bodyHeight: height of piston's body
	// @param bottomDiameter: bottom diameter of piston
	// @param pistonHeadHeight: height of piston's head
	// @param ringsCount: quantity of rings ( depends of engine type)
	void buildBody(double bodyHeight, double bottomDiameter, double pistonHeadHeight, 
		double ringHeight, double ringWidth, int ringsCount = 2);

	// Extrudes pin hole on part
	// @param bodyHeight: height of piston's body
	// @param pinHoleDiameter: diameter of piston's pinHole
	void extrudePinHole(double bodyHeight, double pinHoleDiameter);

	// Extrudes notch on piston's skirt
	// @param bottomDiameter: bottom diameter of piston
	void extrudePistonSkirt(double bottomDiameter);
	
	// Changes material of part
	// @param materialType: constant of MaterialType
	void changeMaterial(MaterialType materialType);

private:
	// Provides start of app and prevent of creating more than 
	// one application instance
	void _openApp();

	// Creates and init part
	void _createPart();
	
	// Make operation "element rotation" from Kompas API
	void _rotateEntity();

	// Extrude last sketch operation
	void _extrudeLastSketch();

	// Encapsulates external logic of _extrudeLastSketch method 
	// @param vBool: used for specify direction of extrusion
	void _doExtrude(VARIANT_BOOL vBool);

private:
	// Kompas Application name for COM interfaces
	const LPCWSTR _kompasAppName = L"Kompas.Application.5";

	// Var used for getting result of operation
	HRESULT _hres;

	// Pointer to Kompas Application instance;
	Kompas6API5::KompasObjectPtr _kompasObject;

	// Pointer to 3D Kompas document that creates after the start of app
	Kompas6API5::ksDocument3DPtr _document3D;

	// Pointer to Kompas part
	Kompas6API5::ksPartPtr _kompasPart;

private:
	// Pointer to kompasSketch object that holds sketch info about part
	std::shared_ptr<KompasSketch> _kompasSketch;
};

