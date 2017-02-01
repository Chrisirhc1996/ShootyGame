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

public:
	CAmmo(CResourceManager* pResources, bool isEnemyWeapon);
	virtual ~CAmmo();

	virtual bool Move(float frameTime) { return false; };
	virtual void SetLifetime(float life) {};
	virtual void SetSpeed(float speed) {};

	// Getters
	CResourceManager* GetResources() { return mpResources; }
	float GetXPos() const { return mpModel->GetX(); }
	float GetYPos() const { return mpModel->GetY(); }
	tle::IModel* GetModel() { return mpModel; }
	bool FromEnemy() const { return mFromEnemyWeapon; }
	int GetAmmoType() const { return mAmmoType; }

	// Setters
	void SetXPos(float xPos) { mpModel->SetX(xPos); }
	void SetYPos(float yPos) { mpModel->SetY(yPos); }
	void SetModel(tle::IModel* model) { mpModel = model; }
	void SetFromEnemy(bool isEnemy) { mFromEnemyWeapon = isEnemy; }
	void SetAmmoType(int type) { mAmmoType = type; }
};