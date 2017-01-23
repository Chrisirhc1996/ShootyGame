#pragma once

// Dependencies

class CPlayer
{
private:
	// Variables //
	
	float mXPos;		// X position on screen
	float mYPos;		// Y position on screen
	
	int mHealth;		// How much health remaining this life
	int mLives;		// How many lives the player has left

public:
	// Constructor
	CPlayer(float xPos, float yPos);
	//  Destructor
	~CPlayer();
	
	// Getters
	float GetXPos() const { return mXPos; }
	float GetYPos() const { return mYPos; }
	
	// Setters
	void SetXPos(float xPos) { mXPos = xPos; }
	void SetYPos(float yPos) { mYPos = yPos; }

private:
	// Private Methods //
};

