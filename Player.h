#pragma once

// Dependencies
#include "Entity.h"

#include <TL-Engine.h>
#include <memory>

class CResourceManager;


class CPlayer : public CEntity
{
private:
	// Variables //

	int mLives;			// How many lives the player has left

public:
	// Constructor
	CPlayer(CResourceManager* pResources);
	//  Destructor
	virtual ~CPlayer();

	// Movement within a restricted area (up, down, left or right)
	virtual void Move(float frameTime);


private:
	// Private Methods //
};

