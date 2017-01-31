#pragma once

// Dependencies
#include "Weapon.h"

class CResourceManager;

class CRocketLauncher : public CWeapon
{
private:
	// Variables //


public:
	// Constructor
	CRocketLauncher(CResourceManager* pResources, bool enemyShooting = true);
	//  Destructor
	virtual ~CRocketLauncher();

private:
	// Private Methods //
};

