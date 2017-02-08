#pragma once

// Dependencies
#include "Weapon.h"

#include <TL-Engine.h>
#include <list>
#include <memory>
#include "Globals.h"
#include "Ammo.h"

class CResourceManager;
//class CEnemy;


class CRocketLauncher : public CWeapon
{
private:
	// Variables //

	float mLifetime;		// Bullet Duration
	float mSpeed;			// Bullet Speed
	float mRateOfFire;		// How often we shoot a bullet
	float mExplosionRadius; // The area of splash damage around the rocket
	float mFiringTimer = 0.0f;

	std::list<std::unique_ptr<CAmmo>>& mResetRockets;		// Bullets waiting to be reused
	std::list<std::unique_ptr<CAmmo>>& mAmmoList;			// The full list of all ammo on screen

public:
	// Constructor
	CRocketLauncher(CResourceManager* pResources, std::list<std::unique_ptr<CAmmo>>& ammoList,
		std::list<std::unique_ptr<CAmmo>>& resetRockets, bool enemyShooting = true);
	//  Destructor
	virtual ~CRocketLauncher();

	// If weapon not on cooldown, fire
	inline virtual void ShootWeapon(float xPos, float yPos);
	inline virtual void UpdateTimer(float frameTime) { mFiringTimer += frameTime; }

	// Getters
	inline float GetLifetime() const { return mLifetime; }
	inline float GetSpeed() const { return mSpeed; }
	inline float SetExplosiveRadius() const { return mRateOfFire; }

	// Setters
	inline void SetLifetime(float lifetime) { mLifetime = lifetime; }
	inline void SetSpeed(float speed) { mSpeed = speed; }
	inline void SetExplosiveRadius(float radius) { mExplosionRadius = radius; }

private:
	// Private Methods //

	void CreateRocket(float xPos, float yPos);
};

