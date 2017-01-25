#pragma once

// Dependencies
#include "Weapon.h"

class CRockets : public CWeapon
{
private:
	// Variables //


public:
	// Constructor
	CRockets(tle::IMesh* pRocketMesh);
	//  Destructor
	virtual ~CRockets();

private:
	// Private Methods //
};

