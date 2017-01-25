#pragma once

// Dependencies
#include "Weapon.h"

class CResourceManager;

class CPlasmaCannon : public CWeapon
{
private:
	// Variables //


public:
	// Constructor
	CPlasmaCannon(CResourceManager* pResources);
	//  Destructor
	virtual ~CPlasmaCannon();

private:
	// Private Methods //
};

