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
	CRocketLauncher(CResourceManager* pResources);
	//  Destructor
	virtual ~CRocketLauncher();

private:
	// Private Methods //
};

