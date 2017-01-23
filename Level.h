#pragma once

// Dependencies
#include <TL-Engine.h>
#include <memory>
#include "Player.h"

class CLevel
{
private:
	// Variables //

	tle::I3DEngine* mpMyEngine;
	tle::IMesh* mpPlayerMesh;
	std::unique_ptr<CPlayer> mpPlayer;

	//tle::ISprite* mpBackdrop;
	tle::ISprite* mpUIBorder;

public:
	// Constructor
	CLevel(tle::I3DEngine* pMyEngine, tle::IMesh* pPlayerMesh);
	//  Destructor	
	~CLevel();

	// Play the current level
	void PlayLevel(float frameTime);

private:
	// Private Methods //
};

