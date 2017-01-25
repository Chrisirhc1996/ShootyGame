#pragma once

// Dependencies
#include <TL-Engine.h>
#include <memory>
#include "Weapon.h"

class CPlayer
{
private:
	// Variables //

	tle::I3DEngine* mpMyEngine;

	tle::IMesh* mpParticleMesh;			// For bullets

	tle::IModel* mpPlayerModel;

	std::unique_ptr<CWeapon> mpWeaponSystem;
	
	int mHealth;		// How much health remaining this life
	int mLives;			// How many lives the player has left

public:
	// Constructor
	CPlayer(tle::I3DEngine* pMyEngine, tle::IMesh* pPlayerMesh, tle::IMesh* pParticleMesh);
	//  Destructor
	~CPlayer();

	// Movement within a restricted area (up, down, left or right)
	void MovePlayer(float frameTime);

	
	// Getters
	float GetXPos() const { return mpPlayerModel->GetX(); }
	float GetYPos() const { return mpPlayerModel->GetY(); }
	tle::IModel* GetModel() { return mpPlayerModel; }
	CWeapon* GetWeaponSystem() { return mpWeaponSystem.get(); }
	
	// Setters
	void SetXPos(float xPos) { mpPlayerModel->SetX(xPos); }
	void SetYPos(float yPos) { mpPlayerModel->SetY(yPos); }

private:
	// Private Methods //
};

