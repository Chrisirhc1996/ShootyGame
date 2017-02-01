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

class CBlaster : public CWeapon
{
private:
	// Variables //
	
	float mLifetime;		// Bullet Duration
	float mSpeed;			// Bullet Speed
	float mRateOfFire;		// How often we shoot a bullet
	float mFiringTimer = 0.0f;

	std::list<std::unique_ptr<CAmmo>>& mResetBullets;		// Bullets waiting to be reused
	std::list<std::unique_ptr<CAmmo>>& mAmmoList;			// The full list of all ammo on screen

public:
	// Constructor
	CBlaster(CResourceManager* pResources, std::list<std::unique_ptr<CAmmo>>& ammoList,
		std::list<std::unique_ptr<CAmmo>>& resetBullets, bool enemyShooting = true);
	//  Destructor
	virtual ~CBlaster();

	// If weapon not on cooldown, fire
	inline virtual void ShootWeapon(float xPos, float yPos);
	inline virtual void UpdateTimer(float frameTime) { mFiringTimer += frameTime; }

	// Getters
	inline float GetLifetime() const { return mLifetime; }
	inline float GetSpeed() const { return mSpeed; }

	// Setters
	inline void SetLifetime(float lifetime) { mLifetime = lifetime; }
	inline void SetSpeed(float speed) { mSpeed = speed; }


private:
	// Private Methods //

	void CreateBullet(float xPos, float yPos);
};