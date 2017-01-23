#pragma once

#include <TL-Engine.h>

// Dependencies

class CPlayer
{
private:
	// Variables //

	tle::I3DEngine* mpMyEngine;
	tle::IModel* mpPlayerModel;
	
	float mXPos;		// X position on screen
	float mYPos;		// Y position on screen
	
	int mHealth;		// How much health remaining this life
	int mLives;			// How many lives the player has left

public:
	// Constructor
	CPlayer(tle::I3DEngine* pMyEngine, tle::IMesh* pPlayerMesh, float xPos, float yPos);
	//  Destructor
	~CPlayer();

	// Movement within a restricted area (up, down, left or right)
	void MovePlayer(float frameTime);

	
	// Getters
	float GetXPos() const { return mXPos; }
	float GetYPos() const { return mYPos; }
	tle::IModel* GetModel() { return mpPlayerModel; }
	
	// Setters
	void SetXPos(float xPos) { mXPos = xPos; }
	void SetYPos(float yPos) { mYPos = yPos; }

private:
	// Private Methods //
};

