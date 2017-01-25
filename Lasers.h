#pragma once

// Dependencies
#include "Weapon.h"

class CLasers : public CWeapon
{
private:
	// Variables //


public:
	// Constructor
	CLasers(tle::IMesh* pLaserMesh);
	//  Destructor
	virtual ~CLasers();

private:
	// Private Methods //
};

