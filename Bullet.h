#pragma once

// Dependencies
#include "Ammo.h"


class CBullet : public CAmmo
{
private:
	float mSpeed;

public:
	CBullet(CResourceManager* pResources, float lifetime, float speed, float xPos, float yPos, bool isEnemyWeapon);
	virtual ~CBullet();

	virtual bool Move(float frameTime);

	// Getters
	
	// Setters
	inline virtual void SetSpeed(float speed) { mSpeed = speed; }
};