#pragma once

// Dependencies
#include <TL-Engine.h>

class CWeapon
{
private:
	// Variables //

	tle::IMesh* mpWeaponMesh;

public:
	// Constructor
	CWeapon(tle::IMesh* pWeaponMesh);
	//  Destructor
	virtual ~CWeapon();

	virtual void MoveWeaponParticles(float frameTime) = 0;
	virtual void ShootWeapon(float xPos, float yPos) = 0;

protected:
	// Protected Methods //

	tle::IMesh* GetWeaponMesh() { return mpWeaponMesh; }
};

