#pragma once

// Dependencies
#include <TL-Engine.h>
#include <memory>
#include "Player.h"
#include "ResourceManager.h"


class CLevel
{
private:
	// Variables //

	CResourceManager* mpResources;
	
	//tle::ISprite* mpBackdrop;
	tle::ISprite* mpUIBorder;

	std::unique_ptr<CPlayer> mpPlayer;

public:
	// Constructor
	CLevel(CResourceManager* pResources);
	//  Destructor	
	~CLevel();

	// Play the current level
	void PlayLevel(float frameTime);

private:
	// Private Methods //
};

