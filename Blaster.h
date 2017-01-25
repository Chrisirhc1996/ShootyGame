#pragma once

// Dependencies
#include <TL-Engine.h>
#include <deque>
#include <memory>
#include "Weapon.h"
#include "Globals.h"

class CBlaster : public CWeapon
{
private:
	// Variables //
	
	float mLifetime;		// Bullet Duration
	float mSpeed;			// Speed
	float mRateOfFire;		// How often we shoot a bullet
	float mFiringTimer = 0.0f;

	struct SBullet			// Individual bullet
	{
		tle::IModel* mpBulletModel;
		float mLifeLeft;
		float mSpeed;

		SBullet(tle::IMesh* pBulletMesh, float lifetime, float speed, float xPos, float yPos) :
			mLifeLeft{ lifetime }, mSpeed{ speed }
		{
			mpBulletModel = pBulletMesh->CreateModel(xPos, yPos);
			mpBulletModel->SetSkin(BULLET_SPRITE);
			mpBulletModel->Scale(0.1f);
		}
	};

	std::deque<std::unique_ptr<SBullet>> bullets;			// All bullets
	std::deque<std::unique_ptr<SBullet>> resetBullets;		// Bullets waiting to be reused

public:
	// Constructor
	CBlaster(tle::IMesh* pBulletMesh);
	//  Destructor
	virtual ~CBlaster();

	// Moves projectiles and age them
	virtual void MoveWeaponParticles(float frameTime);

	virtual void ShootWeapon(float xPos, float yPos);

	// Getters
	float GetLifetime() const { return mLifetime; }
	float GetSpeed() const { return mSpeed; }

	// Setters
	void SetLifetime(float lifetime) { mLifetime = lifetime; }
	void SetSpeed(float speed) { mSpeed = speed; }
	

private:
	// Private Methods //

	void CreateBullet(float xPos, float yPos);
};