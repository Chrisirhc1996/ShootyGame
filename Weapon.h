#pragma once

// Dependencies
#include <TL-Engine.h>
#include "ResourceManager.h"

class CWeapon
{
private:
	// Variables //

	CResourceManager* mpResources;

public:
	// Constructor
	CWeapon(CResourceManager* pResources);
	//  Destructor
	virtual ~CWeapon();

	virtual void MoveWeaponParticles(float frameTime) = 0;
	virtual void ShootWeapon(float xPos, float yPos) = 0;

protected:
	// Protected Methods //

	tle::IMesh* GetWeaponMesh() { return mpResources->GetQuadMesh(); }
};

