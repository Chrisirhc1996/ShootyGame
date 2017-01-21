#pragma once

// Dependencies
#include <TL-Engine.h>	// TL-Engine include file and namespace

class CGameManager
{


public:
	// Constructor
	CGameManager();
	//  Destructor
	~CGameManager();

	// Main game loop, the game ends when this exits
	void RunGame();

private:
	// Get the horizontal and vertical screen sizes in pixel
	void GetDesktopResolution(int& horizontal, int& vertical);
};