#pragma once

// Dependencies
#include "Weapon.h"

class CPlasmaCannon : public CWeapon
{
private:
	// Variables //


public:
	// Constructor
	CPlasmaCannon(tle::IMesh* pPlasmaMesh);
	//  Destructor
	virtual ~CPlasmaCannon();

private:
	// Private Methods //
};

