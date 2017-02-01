#pragma once

// Dependencies
#include "Weapon.h"

#include <TL-Engine.h>
#include <list>
#include <memory>
#include "Globals.h"
#include "Ammo.h"

class CResourceManager;

class CLaserGun : public CWeapon
{
private:
	// Variables //

	std::list<std::unique_ptr<CAmmo>>& mResetBeams;			// Bullets waiting to be reused
	std::list<std::unique_ptr<CAmmo>>& mAmmoList;			// The full list of all ammo on screen

public:
	// Constructor
	CLaserGun(CResourceManager* pResources, std::list<std::unique_ptr<CAmmo>>& ammoList,
		std::list<std::unique_ptr<CAmmo>>& resetBeams, bool enemyShooting = true);
	//  Destructor
	virtual ~CLaserGun();

	inline virtual void ShootWeapon(float xPos, float yPos);

private:
	// Private Methods //

	void CreateBeam(float xPos, float yPos, float distance = 10.0f, float angle = 0.0f);
};

