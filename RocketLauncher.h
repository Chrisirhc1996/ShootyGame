#pragma once

// Dependencies
#include "Weapon.h"

class CRocketLauncher : public CWeapon
{
private:
	// Variables //


public:
	// Constructor
	CRocketLauncher(tle::IMesh* pRocketMesh);
	//  Destructor
	virtual ~CRocketLauncher();

private:
	// Private Methods //
};

