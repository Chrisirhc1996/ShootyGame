#pragma once

// Dependencies
#include <TL-Engine.h>

class CResourceManager;

enum EAmmoType
{
	BULLETS,
	LASERS,
	ROCKETS,
	PLASMA
};


class CAmmo
{
private:
	CResourceManager*  mpResources;
	tle::IModel* mpModel;

	bool mFromEnemyWeapon;
	int mAmmoType = BULLETS;
	float mLifetimeLeft;

public:
	CAmmo(CResourceManager* pResources, bool isEnemyWeapon, float lifetime);
	virtual ~CAmmo();

	inline virtual bool Move(float frameTime) { return false; };
	inline virtual void SetSpeed(float speed) {};
	inline virtual tle::IModel* GetBeam() { return nullptr; };
	inline virtual float GetDistance() const { return 0.0f; };

	// Getters
	inline CResourceManager* GetResources() { return mpResources; }
	inline float GetXPos() const { return mpModel->GetX(); }
	inline float GetYPos() const { return mpModel->GetY(); }
	inline tle::IModel* GetModel() { return mpModel; }
	inline bool FromEnemy() const { return mFromEnemyWeapon; }
	inline int GetAmmoType() const { return mAmmoType; }
	inline float GetLifeTimeRemaining() const { return mLifetimeLeft; }

	// Setters
	inline void SetXPos(float xPos) { mpModel->SetX(xPos); }
	inline void SetYPos(float yPos) { mpModel->SetY(yPos); }
	inline void SetModel(tle::IModel* model) { mpModel = model; }
	inline void SetFromEnemy(bool isEnemy) { mFromEnemyWeapon = isEnemy; }
	inline void SetAmmoType(int type) { mAmmoType = type; }
	inline void SetLifetime(float life) { mLifetimeLeft = life; };
};