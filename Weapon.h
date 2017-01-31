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

	virtual void MoveWeaponParticles(float frameTime) = 0;
	virtual void ShootWeapon(float xPos, float yPos) = 0;
	virtual bool CollisionCheck(CEnemy* enemy) = 0;

protected:
	// Protected Methods //

	tle::IMesh* GetWeaponMesh() { return mpResources->GetQuadMesh(); }
};

