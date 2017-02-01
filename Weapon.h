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

	inline virtual void ShootWeapon(float xPos, float yPos) = 0;
	inline virtual void UpdateTimer(float frameTime) {};

	// Getters
	inline bool IsEnemyWeapon() const { return mEnemyWeapon; }

protected:
	// Protected Methods //
	inline CResourceManager* GetResources() { return mpResources; }
};

