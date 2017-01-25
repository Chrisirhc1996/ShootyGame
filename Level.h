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
	
	//tle::ISprite* mpBackdrop;
	tle::ISprite* mpUIBorder;

	tle::IMesh* mpPlayerMesh;			// The players ship
	tle::IMesh* mpParticleMesh;			// For bullets

	std::unique_ptr<CPlayer> mpPlayer;

public:
	// Constructor
	CLevel(tle::I3DEngine* pMyEngine);
	//  Destructor	
	~CLevel();

	// Play the current level
	void PlayLevel(float frameTime);

private:
	// Private Methods //
};

