#pragma once

// Dependencies
#include "Entity.h"

#include <TL-Engine.h>
#include <memory>
#include <list>

class CResourceManager;
class CAmmo;


class CPlayer : public CEntity
{
private:
	// Variables //

	int mLives = 3;			// How many lives the player has left

public:
	// Constructor
	CPlayer(CResourceManager* pResources, std::list<std::unique_ptr<CAmmo>>& ammoList,
		std::list<std::unique_ptr<CAmmo>>& resetlist);
	//  Destructor
	virtual ~CPlayer();

	// Movement within a restricted area (up, down, left or right)
	virtual void Move(float frameTime);

	// Setters
	inline int LoseALife() { return --mLives; }


private:
	// Private Methods //
};

