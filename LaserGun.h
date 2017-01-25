#pragma once

// Dependencies
#include "Weapon.h"

class CLaserGun : public CWeapon
{
private:
	// Variables //


public:
	// Constructor
	CLaserGun(tle::IMesh* pLaserMesh);
	//  Destructor
	virtual ~CLaserGun();

private:
	// Private Methods //
};

