#pragma once

// Dependencies
#include "Ammo.h"


class CRocket : public CAmmo
{
private:
	float mSpeed;

public:
	CRocket(CResourceManager* pResources, float lifetime, float speed, float xPos, float yPos, bool isEnemyWeapon);
	virtual ~CRocket();

	virtual bool Move(float frameTime);

	// Getters

	// Setters
	inline virtual void SetSpeed(float speed) { mSpeed = speed; }
};