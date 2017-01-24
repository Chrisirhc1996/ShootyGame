#pragma once

// Dependencies
#include "Weapon.h"

class CBullets : public CWeapon
{
private:
	// Variables //
	tle::I3DEngine* mpMyEngine;	
	tle::IMesh* mMesh;
	tle::IModel* mModel;
	float mLifetime;		// Bullet Duration
	float mSpeed;			// Speed
	float mRadius;			// Hitbox

public:
	// Constructor
	CBullets(tle::I3DEngine* mpMyEngine, tle::IMesh* mMesh, string type, float mLifetime, float mSpeed, float mRadius);
	//  Destructor
	virtual ~CBullets();

	// Moves projectile and ages it
	void MoveBullet(float frameTime);

	tle::IMesh* GetMesh() { return mMesh; }
	tle::IModel* GetModel() { return mModel; }
	float GetLifetime() { return mLifetime; }
	float GetSpeed() { return mSpeed; }
	float GetRadius() { return mRadius; }

	void SetSpeed(float speed) { mSpeed = speed; }
	void SetLifetime(float lifetime) { mLifetime = lifetime; }
	void SetRadius(float radius) { mRadius = radius; }

private:
	// Private Methods //
};
