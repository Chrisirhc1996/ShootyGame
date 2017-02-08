#pragma once

// Dependencies
#include "Ammo.h"


class CPlasmaShot : public CAmmo
{
private:
	float mSpeed;

public:
	CPlasmaShot(CResourceManager* pResources, float lifetime, float speed, float xPos, float yPos, bool isEnemyWeapon);
	virtual ~CPlasmaShot();

	virtual bool Move(float frameTime);

	// Getters

	// Setters
	inline virtual void SetSpeed(float speed) { mSpeed = speed; }
};