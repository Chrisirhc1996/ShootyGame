#pragma once

// Dependencies
#include "Weapon.h"

class CPlasma : public CWeapon
{
private:
	// Variables //


public:
	// Constructor
	CPlasma(tle::IMesh* pPlasmaMesh);
	//  Destructor
	virtual ~CPlasma();

private:
	// Private Methods //
};

