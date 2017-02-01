#pragma once

// Dependencies
#include "Ammo.h"

#include <TL-Engine.h>


class CLaserBeam : public CAmmo
{
private:
	// Variables //

	tle::IModel* mpBeam;		// For rotations
	float mDistance;

public:
	// Constructor
	CLaserBeam(CResourceManager* pResources, float distance, float angle, float xPos, float yPos, bool isEnemyWeapon);
	// Destructor
	virtual ~CLaserBeam();

	virtual bool Move(float frameTime);

	// Getters
	inline virtual tle::IModel* GetBeam() { return mpBeam; }
	inline virtual float GetDistance() const { return mDistance; }
};

