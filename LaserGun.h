#pragma once

// Dependencies
#include "Weapon.h"

class CResourceManager;

class CLaserGun : public CWeapon
{
private:
	// Variables //


public:
	// Constructor
	CLaserGun(CResourceManager* pResources);
	//  Destructor
	virtual ~CLaserGun();

private:
	// Private Methods //
};

