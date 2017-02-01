#pragma once

// Dependencies
#include <TL-Engine.h>
#include "ResourceManager.h"

class CEnemy;


class CWeapon
{
private:
	// Variables //

	CResourceManager* mpResources;

	bool mEnemyWeapon;

public:
	// Constructor
	CWeapon(CResourceManager* pResources, bool enemyWeapon);
	//  Destructor
	virtual ~CWeapon();

	virtual void ShootWeapon(float xPos, float yPos) = 0;
	virtual void UpdateTimer(float frameTime) = 0;

	// Getters
	bool IsEnemyWeapon() const { return mEnemyWeapon; }

protected:
	// Protected Methods //
	CResourceManager* GetResources() { return mpResources; }
};

