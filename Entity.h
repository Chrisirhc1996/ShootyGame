#pragma once

// Dependencies
#include <TL-Engine.h>
#include <memory>
#include "Weapon.h"

class CResourceManager;


class CEntity
{
private:
	// Variables //

	CResourceManager* mpResources;

	tle::IModel* mpModel;

	std::unique_ptr<CWeapon> mpWeaponSystem;

	int mHealth;		// How much health remaining

public:
	// Constructor
	CEntity(CResourceManager* pResources);
	//  Destructor
	virtual ~CEntity();

	// Movement within a restricted area (up, down, left or right)
	virtual void Move(float frameTime) {}


	// Getters
	CResourceManager* GetResources() { return mpResources; }
	float GetXPos() const { return mpModel->GetX(); }
	float GetYPos() const { return mpModel->GetY(); }
	tle::IModel* GetModel() { return mpModel; }
	CWeapon* GetWeaponSystem() { return mpWeaponSystem.get(); }

	// Setters
	void SetXPos(float xPos) { mpModel->SetX(xPos); }
	void SetYPos(float yPos) { mpModel->SetY(yPos); }
	void SetModel(tle::IModel* model) { mpModel = model; }
	void SetWeaponSystem(std::unique_ptr<CWeapon>& weaponSystem) { mpWeaponSystem = move(weaponSystem); }

private:
	// Private Methods //
};