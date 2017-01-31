#pragma once

// Dependencies
#include "Ammo.h"


class CBullets : public CAmmo
{
private:
	float mLifeLeft;
	float mSpeed;

public:
	CBullets(tle::IMesh* pBulletMesh, float lifetime, float speed, float xPos, float yPos);
	virtual ~CBullets();
};