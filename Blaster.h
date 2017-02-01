#pragma once

// Dependencies
#include "Weapon.h"

#include <TL-Engine.h>
#include <list>
#include <memory>
#include "Globals.h"
#include "Ammo.h"

class CResourceManager;
class CEnemy;

class CBlaster : public CWeapon
{
private:
	// Variables //
	
	float mLifetime;		// Bullet Duration
	float mSpeed;			// Bullet Speed
	float mRateOfFire;		// How often we shoot a bullet
	float mFiringTimer = 0.0f;

	static std::list<std::unique_ptr<CAmmo>> mResetBullets;		// Bullets waiting to be reused
	std::list<std::unique_ptr<CAmmo>>& mAmmoList;

public:
	// Constructor
	CBlaster(CResourceManager* pResources, std::list<std::unique_ptr<CAmmo>>& ammoList, bool enemyShooting = true);
	//  Destructor
	virtual ~CBlaster();

	// If weapon not on cooldown, fire
	virtual void ShootWeapon(float xPos, float yPos);
	virtual void UpdateTimer(float frameTime) { mFiringTimer += frameTime; }

	// Getters
	float GetLifetime() const { return mLifetime; }
	float GetSpeed() const { return mSpeed; }
	static std::list<std::unique_ptr<CAmmo>>& GetBulletReserve() { return mResetBullets; }

	// Setters
	void SetLifetime(float lifetime) { mLifetime = lifetime; }
	void SetSpeed(float speed) { mSpeed = speed; }


private:
	// Private Methods //

	void CreateBullet(float xPos, float yPos);
};