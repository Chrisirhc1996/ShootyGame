#pragma once

// Dependencies
#include <TL-Engine.h>	// TL-Engine include file and namespace

class CGameManager
{
private:
	// Variables //

	tle::I3DEngine* mpMyEngine;
	tle::ICamera* mpMyCamera;

	int mHorizontal;			// desktop X resolution
	int mVertical;				// desktop Y resolution

	bool mFullscreen = false;

	float mFrameTime;			// the time in seconds since the last update

public:
	// Constructor
	CGameManager();
	//  Destructor
	~CGameManager();

	// Main game loop, the game ends when this exits
	void RunGame();

private:
	// Private Methods //

	// Get the horizontal and vertical screen sizes in pixel
	void GetDesktopResolution(int& horizontal, int& vertical);
	bool CreateEngine();
	void AddMediaFolders();
};